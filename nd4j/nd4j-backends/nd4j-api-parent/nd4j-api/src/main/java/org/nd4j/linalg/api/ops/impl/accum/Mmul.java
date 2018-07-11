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

package org.nd4j.linalg.api.ops.impl.accum;

import lombok.EqualsAndHashCode;
import lombok.val;
import onnx.OnnxProto3;
import org.nd4j.autodiff.samediff.SDVariable;
import org.nd4j.autodiff.samediff.SameDiff;
import org.nd4j.imports.descriptors.properties.PropertyMapping;
import org.nd4j.linalg.api.blas.params.MMulTranspose;
import org.nd4j.linalg.api.ndarray.INDArray;
import org.nd4j.linalg.api.ops.DynamicCustomOp;
import org.nd4j.linalg.api.shape.Shape;
import org.nd4j.linalg.exception.ND4JIllegalStateException;
import org.nd4j.linalg.util.ArrayUtil;
import org.tensorflow.framework.AttrValue;
import org.tensorflow.framework.GraphDef;
import org.tensorflow.framework.NodeDef;

import java.util.*;

/**
 * Matrix multiplication/dot product
 *
 * @author Adam Gibson
 */
@EqualsAndHashCode
public class Mmul extends DynamicCustomOp {

    protected MMulTranspose mt;

    /**
     *
     * @param sameDiff
     * @param i_v1
     * @param i_v2
     * @param mt
     */
    public Mmul(SameDiff sameDiff,
                SDVariable i_v1,
                SDVariable i_v2,
                MMulTranspose mt) {
        super(null,sameDiff,new SDVariable[]{i_v1,i_v2});
        this.mt = mt;
        addIArgument(ArrayUtil.fromBoolean(mt.isTransposeA()), ArrayUtil.fromBoolean(mt.isTransposeB()));
    }


    /**
     *
     * @param sameDiff
     * @param i_v1
     * @param i_v2
     */
    public Mmul(SameDiff sameDiff,
                SDVariable i_v1,
                SDVariable i_v2) {
        this(sameDiff,i_v1,i_v2,MMulTranspose.allFalse());
    }

    /**
     *
     * @param x
     * @param y
     * @param z
     */
    public Mmul(INDArray x,
                INDArray y,
                INDArray z,
                MMulTranspose mt) {
        super(null, new INDArray[]{x, y}, z == null ? null : new INDArray[]{z});
        if (mt != null) {
          this.mt = mt;
          addIArgument(ArrayUtil.fromBoolean(mt.isTransposeA()),
                       ArrayUtil.fromBoolean(mt.isTransposeB()));
        }
    }


    public Mmul() {}


    @Override
    public List<long[]> calculateOutputShape() {
        if(mt == null)
            mt = MMulTranspose.allFalse();

        long[] aShape = mt.isTransposeA() ? ArrayUtil.reverseCopy(larg().getShape()) : larg().getShape();
        long[] bShape = mt.isTransposeB() ? ArrayUtil.reverseCopy(rarg().getShape()) : rarg().getShape();
        if(Shape.isPlaceholderShape(aShape) || Shape.isPlaceholderShape(bShape))
            return Collections.emptyList();

        long[] shape =  Shape.getMatrixMultiplyShape(aShape,bShape);
        if(mt.isTransposeResult())
            shape = ArrayUtil.reverseCopy(shape);

        for(int i = 0; i < shape.length; i++) {
            if(shape[i] < 1)
                throw new ND4JIllegalStateException("Invalid shape computed at index " +  i + ": shape " + Arrays.toString(shape));
        }

        return Collections.singletonList(shape);
    }


    @Override
    public String onnxName() {
        return "MatMul";
    }

    @Override
    public String tensorflowName() {
        return "MatMul";
    }



    @Override
    public String opName() {
        return "mmul";
    }



    @Override
    public void initFromTensorFlow(NodeDef nodeDef, SameDiff initWith, Map<String, AttrValue> attributesForNode, GraphDef graph) {
        super.initFromTensorFlow(nodeDef, initWith, attributesForNode, graph);
        val isTransposeA = attributesForNode.get("transpose_a").getB();
        val isTransposeB = attributesForNode.get("transpose_b").getB();
        MMulTranspose mMulTranspose = MMulTranspose.builder()
                .transposeA(isTransposeA).transposeB(isTransposeB)
                .build();
        this.mt = mMulTranspose;
        val args = args();
        for(val arg : args) {
            if(sameDiff.isPlaceHolder(arg.getVarName()) || arg.getShape() == null) {
                sameDiff.addPropertyToResolve(this,arg.getVarName());
            }
        }
    }

    @Override
    public void initFromOnnx(OnnxProto3.NodeProto node, SameDiff initWith, Map<String, OnnxProto3.AttributeProto> attributesForNode, OnnxProto3.GraphProto graph) {
        val isTransposeA = !attributesForNode.containsKey("transA") ? false : attributesForNode.get("transA").getI() > 0;
        val isTransposeB = !attributesForNode.containsKey("transB") ? false : attributesForNode.get("transB").getI() > 0;
        MMulTranspose mMulTranspose = MMulTranspose.builder()
                .transposeA(isTransposeA).transposeB(isTransposeB)
                .build();
        this.mt = mMulTranspose;
    }





    @Override
    public List<SDVariable> doDiff(List<SDVariable> i_v1) {
//        List<SDVariable> ret = new ArrayList<>();
//        SDVariable dLdOut = i_v1.get(0);
//
//        SDVariable dLdx = sameDiff.mmul(dLdOut, rarg(), MMulTranspose.builder()
//                .transposeB(true)
//                .build());
//
//        SDVariable dLdy = sameDiff.mmul(larg(), dLdOut, MMulTranspose.builder()
//                .transposeA(true)
//                .build());
//
//        ret.add(dLdx);
//        ret.add(dLdy);
//        return ret;

        List<SDVariable> ret = new ArrayList<>();
        SDVariable dLdOut = i_v1.get(0);
        /*
        In: x=[a,b], y=[b,c]
        tX  tY  tZ  x       y       z       dz          dLdx
        F   F   F   [a,b]   [b,c]   [a,c]   [a,c]       [a,c]*[b,c]T = [a,b]
        T   F   F   [b,a]   [b,c]   [a,c]   [a,c]       ([a,c]*[b,c]T)T = [b,a]
        F   T   F   [a,b]   [c,b]   [a,c]   [a,c]       ([a,c]*[c,b]) = [a,b]
        T   T   F   [b,a]   [c,b]   [a,c]   [a,c]       ([a,c]*[c,b])T = [b,a]
        F   F   T   [a,b]   [b,c]   [c,a]   [c,a]

         */

        //If x=[a,b] and y=[b,c] then x*y=[a,c] - no transpose case
        SDVariable dLdx = sameDiff.mmul(dLdOut, rarg(), MMulTranspose.builder() //No transpose: [a,c]*[b,c]^T = [a,b]
                .transposeA(mt.isTransposeResult()) //Transpose gradient if fwd result was transposed
                .transposeB(!mt.isTransposeB())
                .transposeResult(mt.isTransposeA())
                .build());

        SDVariable dLdy = sameDiff.mmul(larg(), dLdOut, MMulTranspose.builder() //No transpose: [a,b]^T * [a,c] = [b,c]
                .transposeA(!mt.isTransposeA())
                .transposeB(mt.isTransposeResult()) //Transpose gradient if fwd result was transposed
                .transposeResult(mt.isTransposeB())
                .build());

        ret.add(dLdx);
        ret.add(dLdy);
        return ret;
    }


    @Override
    public Map<String, Map<String, PropertyMapping>> mappingsForFunction() {
        Map<String,Map<String,PropertyMapping>> ret = new HashMap<>();
        Map<String,PropertyMapping> map = new HashMap<>();

        val transposeA = PropertyMapping.builder()
                .onnxAttrName("transA")
                .tfAttrName("transpose_a")
                .propertyNames(new String[]{"transposeA"})
                .build();

        val transposeB = PropertyMapping.builder()
                .onnxAttrName("transB")
                .tfAttrName("transpose_b")
                .propertyNames(new String[]{"transposeB"})
                .build();

        map.put("transposeA",transposeA);
        map.put("transposeB",transposeB);

        ret.put(tensorflowName(),map);
        ret.put(onnxName(),map);

        return ret;
    }
}

