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

import org.nd4j.autodiff.functions.DifferentialFunction;
import org.nd4j.autodiff.samediff.SDVariable;
import org.nd4j.autodiff.samediff.SameDiff;
import org.nd4j.imports.NoOpNameFoundException;
import org.nd4j.linalg.api.ndarray.INDArray;
import org.nd4j.linalg.api.ops.BaseAccumulation;

import java.util.List;

/**
 * Non-normalized Shannon Entropy Op - returns the entropy (information gain, or uncertainty of a random variable).
 *
 * @author raver119@gmail.com
 */
public class ShannonEntropy extends BaseAccumulation {
    public ShannonEntropy(SameDiff sameDiff, SDVariable i_v, int[] dimensions) {
        super(sameDiff, i_v, dimensions);
    }

    public ShannonEntropy(SameDiff sameDiff, SDVariable i_v, SDVariable i_v2, int[] dimensions) {
        super(sameDiff, i_v, i_v2, dimensions);
    }

    public ShannonEntropy() {}

    public ShannonEntropy(INDArray x, INDArray y, INDArray z, long n) {
        super(x, y, z, n);
    }

    public ShannonEntropy(INDArray x, INDArray y, long n) {
        super(x, y, n);
    }

    public ShannonEntropy(INDArray x) {
        super(x);
    }

    public ShannonEntropy(INDArray x, INDArray y) {
        super(x, y);
    }

    public ShannonEntropy(INDArray x, INDArray y, INDArray z) {
        super(x, y, z, x.lengthLong());
    }
    @Override
    public int opNum() {
        return 18;
    }

    @Override
    public String opName() {
        return "shannonentropy";
    }


    @Override
    public List<SDVariable> doDiff(List<SDVariable> f1) {
        return null;
    }

    @Override
    public String onnxName() {
        throw new NoOpNameFoundException("No onnx op opName found for " +  opName());
    }

    @Override
    public String tensorflowName() {
        return "entropy_shannon";
    }


    @Override
    public Type getOpType() {
        return Type.REDUCE;
    }
}
