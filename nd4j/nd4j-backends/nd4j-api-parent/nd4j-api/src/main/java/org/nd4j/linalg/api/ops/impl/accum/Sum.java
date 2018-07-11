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

import lombok.extern.slf4j.Slf4j;
import org.nd4j.autodiff.samediff.SDVariable;
import org.nd4j.autodiff.samediff.SameDiff;
import org.nd4j.linalg.api.ndarray.INDArray;
import org.nd4j.linalg.api.ops.BaseAccumulation;
import org.nd4j.linalg.api.shape.Shape;

import java.util.Arrays;
import java.util.Collections;
import java.util.List;

/**
 * Sum the components
 *
 * @author Adam Gibson
 */
@Slf4j
public class Sum extends BaseAccumulation {
    public Sum(SameDiff sameDiff, SDVariable i_v, boolean keepDims, int[] dimensions) {
        super(sameDiff, i_v, dimensions, keepDims);
    }

    public Sum(SameDiff sameDiff, SDVariable i_v, SDVariable i_v2, int[] dimensions) {
        super(sameDiff, i_v, i_v2, dimensions);
    }


    public Sum() {
    }

    public Sum(INDArray x, INDArray y, INDArray z, long n) {
        super(x, y, z, n);
    }

    public Sum(INDArray x, INDArray y, long n) {
        super(x, y, n);
    }

    public Sum(INDArray x) {
        super(x);
    }

    public Sum(INDArray x, INDArray y) {
        super(x, y);
    }

    public Sum(INDArray x, INDArray y, INDArray z) {
        super(x, y, z, x.lengthLong());
    }

    public Sum(INDArray x, INDArray y, INDArray z, boolean newFormat, boolean keepDims, int[] dimensions) {
        super(x, y, z, newFormat, keepDims, dimensions);
    }

    @Override
    public int opNum() {
        return 1;
    }

    @Override
    public String opName() {
        return "reduce_sum";
    }

    @Override
    public List<SDVariable> doDiff(List<SDVariable> i_v1) {
        //Out = sum(in)
        // dL/dIn = dL/dOut * dOut/dIn
        //        = dL/dOut * 1
        // But broadcast to shape of the input
        return Collections.singletonList(f().sumBp(arg(), i_v1.get(0), keepDims, dimensions));
    }


    @Override
    public String onnxName() {
        return "Sum";
    }

    @Override
    public String tensorflowName() {
        return "Sum";
    }

    @Override
    public Type getOpType() {
        return Type.REDUCE;
    }
}
