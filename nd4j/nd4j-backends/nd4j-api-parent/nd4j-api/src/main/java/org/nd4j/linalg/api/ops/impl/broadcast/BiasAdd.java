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

package org.nd4j.linalg.api.ops.impl.broadcast;

import lombok.NoArgsConstructor;
import lombok.val;
import org.nd4j.autodiff.samediff.SDVariable;
import org.nd4j.autodiff.samediff.SameDiff;
import org.nd4j.linalg.api.ops.DynamicCustomOp;
import org.nd4j.linalg.util.ArrayUtil;
import org.tensorflow.framework.AttrValue;
import org.tensorflow.framework.GraphDef;
import org.tensorflow.framework.NodeDef;

import java.util.*;

/**
 * Bias addition gradient operation.
 */
@NoArgsConstructor
public class BiasAdd extends DynamicCustomOp {


    public BiasAdd(SameDiff sameDiff, SDVariable input, SDVariable bias) {
        super(null, sameDiff, new SDVariable[] {input, bias}, false);
    }

    @Override
    public String opName() {
        return "biasadd";
    }

    @Override
    public void initFromTensorFlow(NodeDef nodeDef, SameDiff initWith, Map<String, AttrValue> attributesForNode, GraphDef graph) {
        super.initFromTensorFlow(nodeDef, initWith, attributesForNode, graph);

    }

    @Override
    public List<long[]> calculateOutputShape() {
        val args = args();
        for(int i = 0; i < args.length; i++)
            if(args[i].getShape() == null)
                return Collections.emptyList();
        val firstShape = ArrayUtil.prod(args[0].getShape());
        val secondShape = ArrayUtil.prod(args[1].getShape());

        if(firstShape > secondShape)
            return Arrays.asList(args[0].getShape());
        else
            return Arrays.asList(args[1].getShape());
    }


    @Override
    public String onnxName() {
        return "BiasAdd";
    }

    @Override
    public String tensorflowName() {
        return "BiasAdd";
    }

    @Override
    public List<SDVariable> doDiff(List<SDVariable> gradient){
        return Arrays.asList(f().biasAddBp(arg(0), arg(1), gradient.get(0)));
    }
}
