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

package org.nd4j.linalg.api.ops.impl.transforms;

import org.nd4j.autodiff.samediff.SDVariable;
import org.nd4j.autodiff.samediff.SameDiff;
import org.nd4j.linalg.api.ops.DynamicCustomOp;

import java.util.Arrays;
import java.util.List;

public class MatrixSetDiag extends DynamicCustomOp {

    public MatrixSetDiag(SameDiff sameDiff, SDVariable in, SDVariable diag, boolean inPlace) {
        super(null, sameDiff, new SDVariable[]{in, diag}, inPlace);
    }

    public MatrixSetDiag(){ }

    @Override
    public String tensorflowName() {
        return "MatrixSetDiag";
    }

    @Override
    public String opName() {
        return "matrix_set_diag";
    }

    @Override
    public List<SDVariable> doDiff(List<SDVariable> i_v) {
        SDVariable grad = i_v.get(0);
        SDVariable in1Grad = f().setDiag(grad, sameDiff.zerosLike(arg(1)));
        SDVariable in2Grad = f().diagPart(grad);
        return Arrays.asList(in1Grad, in2Grad);
    }
}
