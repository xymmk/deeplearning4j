/*******************************************************************************
 * Copyright (c) 2015-2018 Skymind, Inc.
 *
 * This program and the accompanying materials are made available under the
 * terms of the Apache License, Version 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 * SPDX-License-Identifier: Apache-2.0
 ******************************************************************************/

package org.nd4j.imports.graphmapper;

import com.github.os72.protobuf351.Message;
import com.github.os72.protobuf351.TextFormat;
import lombok.extern.slf4j.Slf4j;
import lombok.val;
import org.apache.commons.io.IOUtils;
import org.nd4j.autodiff.functions.DifferentialFunction;
import org.nd4j.autodiff.samediff.SameDiff;
import org.nd4j.imports.NoOpNameFoundException;
import org.nd4j.imports.descriptors.properties.PropertyMapping;
import org.nd4j.linalg.api.buffer.DataBuffer;
import org.nd4j.linalg.api.ops.Op;
import org.nd4j.linalg.exception.ND4JIllegalStateException;
import org.nd4j.weightinit.impl.ZeroInitScheme;

import java.io.*;
import java.util.HashMap;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;

/**
 * Base implementation for importing a graph
 * @param <GRAPH_TYPE> the type of graph
 * @param <NODE_TYPE> the type of node
 * @param <ATTR_TYPE> the attribute type
 */
@Slf4j
public abstract class BaseGraphMapper<GRAPH_TYPE,NODE_TYPE,ATTR_TYPE,TENSOR_TYPE> implements GraphMapper<GRAPH_TYPE,NODE_TYPE,ATTR_TYPE,TENSOR_TYPE> {



    @Override
    public Op.Type opTypeForNode(NODE_TYPE nodeDef) {
        DifferentialFunction opWithTensorflowName = getMappedOp(getOpType(nodeDef));
        if(opWithTensorflowName == null)
            throw new NoOpNameFoundException("No op found with name " + getOpType(nodeDef));
        Op.Type type = opWithTensorflowName.opType();
        return type;

    }



    @Override
    public void mapProperties(DifferentialFunction on, NODE_TYPE node, GRAPH_TYPE graph, SameDiff sameDiff, Map<String, Map<String, PropertyMapping>> propertyMappings) {
        val mappings = propertyMappings.get(getOpType(node));
        if(mappings == null || mappings.isEmpty()) {
            return;
        }


        for(val entry : mappings.entrySet()) {
            mapProperty(entry.getKey(),on,node,graph,sameDiff,propertyMappings);
        }
    }



    /**
     *
     * @param inputStream
     * @return
     */
    @Override
    public  SameDiff importGraph(InputStream inputStream) {
        GRAPH_TYPE def = readGraph(inputStream);
        return importGraph(def);
    }

    protected GRAPH_TYPE readGraph(InputStream inputStream) {
        byte[] bytes = null;
        GRAPH_TYPE def = null;
        try {
            bytes = IOUtils.toByteArray(inputStream);
            def = parseGraphFrom(bytes);
        } catch (IOException e) {
            try (BufferedInputStream bis2 = new BufferedInputStream(new ByteArrayInputStream(bytes)); BufferedReader reader = new BufferedReader(new InputStreamReader(bis2))) {
                Message.Builder builder = getNewGraphBuilder();

                StringBuilder str = new StringBuilder();
                String line = null;
                while ((line = reader.readLine()) != null) {
                    str.append(line);//.append("\n");
                }

                TextFormat.getParser().merge(str.toString(), builder);
                def = (GRAPH_TYPE) builder.build();
            } catch (Exception e2) {
                e2.printStackTrace();
            }
        }

        return def;
    }

    /**
     *
     * @param graphFile
     * @return
     */
    @Override
    public  SameDiff importGraph(File graphFile) {
        GRAPH_TYPE def = null;
        try (FileInputStream fis = new FileInputStream(graphFile)) {
            return importGraph(fis);
        } catch (Exception e) {
            e.printStackTrace();

        }

        if (def == null)
            throw new ND4JIllegalStateException("Unknown format: " + graphFile.getAbsolutePath());


        return importGraph(def);
    }

    @Override
    public Map<String, NODE_TYPE> nameIndexForGraph(GRAPH_TYPE graph) {
        List<NODE_TYPE> nodes = getNodeList(graph);
        Map<String,NODE_TYPE> ret = new HashMap<>();
        for(NODE_TYPE node : nodes) {
            ret.put(getName(node),node);
        }
        return ret;
    }

    @Override
    public Map<String, NODE_TYPE> nodesByName(GRAPH_TYPE graph) {
        val nodeTypes = getNodeList(graph);
        Map<String,NODE_TYPE> ret = new LinkedHashMap<>();
        for(int i = 0; i < nodeTypes.size(); i++) {
            ret.put(getName(nodeTypes.get(i)),nodeTypes.get(i));
        }
        return ret;
    }

    /**
     * This method converts given TF
     * @param tfGraph
     * @return
     */
    @Override
    public SameDiff importGraph(GRAPH_TYPE tfGraph) {
        SameDiff diff = SameDiff.create();
        ImportState<GRAPH_TYPE,TENSOR_TYPE> importState = new ImportState<>();
        importState.setSameDiff(diff);
        importState.setGraph(tfGraph);

        val variablesForGraph = variablesForGraph(tfGraph);
        importState.setVariables(variablesForGraph);


        //map the names of the nodes while accumulating the vertex ids
        //for each variable
        for(Map.Entry<String,TENSOR_TYPE> entry : variablesForGraph.entrySet()) {
            if(dataTypeForTensor(entry.getValue()) == DataBuffer.Type.UNKNOWN) {
                val var = importState.getSameDiff().var(entry.getKey(),null,new ZeroInitScheme('c'));
                //mark as place holder for validating resolution later.
                if(isPlaceHolder(entry.getValue())) {
                    importState.getSameDiff().addAsPlaceHolder(var.getVarName());
                    if(var.getShape() != null)
                        importState.getSameDiff().setOriginalPlaceHolderShape(var.getVarName(),var.getShape());
                }

                continue;
            }

            val arr = getNDArrayFromTensor(entry.getKey(), entry.getValue(), tfGraph);
            if(arr != null) {
                val var = importState.getSameDiff().var(entry.getKey(),arr);
                //ensure the array is made available for later processing
                diff.associateArrayWithVariable(arr,var);
            }
            else if(getShapeFromTensor(entry.getValue()) == null) {
                val var = importState.getSameDiff().var(entry.getKey(),null,new ZeroInitScheme('c'));
                //mark as place holder for validating resolution later.

                //note that this vertex id can still be a place holder
                //with a -1 shape. Just because a shape is "known" doesn't mean
                //that it isn't  a place holder.
                if(isPlaceHolder(entry.getValue())) {
                    val originalShape = getShapeFromTensor(entry.getValue());
                    importState.getSameDiff().addAsPlaceHolder(var.getVarName());
                    if(var.getShape() != null)
                        importState.getSameDiff().setOriginalPlaceHolderShape(var.getVarName(),originalShape);

                }

            }
            else {
                val originalShape = getShapeFromTensor(entry.getValue());
                val var = importState.getSameDiff().var(entry.getKey(),originalShape);
                //mark as place holder for validating resolution later.

                //note that this vertex id can still be a place holder
                //with a -1 shape. Just because a shape is "known" doesn't mean
                //that it isn't  a place holder.
                if(isPlaceHolder(entry.getValue())) {
                    importState.getSameDiff().addAsPlaceHolder(var.getVarName());
                    importState.getSameDiff().setOriginalPlaceHolderShape(var.getVarName(),originalShape);
                }

            }

        }

        //setup vertex ids for  names


        //handle mapping vertex ids properly


        val tfNodesList = getNodeList(tfGraph);
        for (NODE_TYPE tfNode : tfNodesList) {
            if(!opsToIgnore().contains(getOpType(tfNode)) || isOpIgnoreException(tfNode))
                mapNodeType(tfNode,importState);
        }

        return diff;
    }




    @Override
    public boolean validTensorDataType(TENSOR_TYPE tensorType) {
        return dataTypeForTensor(tensorType) != DataBuffer.Type.UNKNOWN;
    }

}
