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

package org.nd4j.linalg.api.ops.impl.accum.bp;

import org.nd4j.autodiff.samediff.SDVariable;
import org.nd4j.autodiff.samediff.SameDiff;
import org.nd4j.linalg.api.ndarray.INDArray;


/**
 * Backprop op for cumulative product operation
 *
 * @author Alex Black
 */

public class CumProdBp extends BaseReductionBp {

    private boolean exclusive;
    private boolean reverse;

    public CumProdBp(SameDiff sameDiff, SDVariable origInput, SDVariable axis, SDVariable gradAtOutput, boolean exclusive, boolean reverse) {
        super(sameDiff, origInput, gradAtOutput, false);
        this.exclusive = exclusive;
        this.reverse = reverse;
        addArgs();
    }

    public CumProdBp(INDArray origInput, INDArray axis, INDArray gradAtOutput, INDArray output, boolean exclusive, boolean reverse){
        super(origInput, gradAtOutput, output, false);
        this.exclusive = exclusive;
        this.reverse = reverse;
        addArgs();
    }

    public CumProdBp(){}

    @Override
    protected void addArgs(){
        addTArgument(exclusive ? 1.0 : 0.0);
        addTArgument(reverse ? 1.0 : 0.0);
        if(dimensions != null && dimensions.length > 0){
            addIArgument(dimensions);
        }
    }

    @Override
    public String opName() {
        return "cumprod_bp";
    }
}
