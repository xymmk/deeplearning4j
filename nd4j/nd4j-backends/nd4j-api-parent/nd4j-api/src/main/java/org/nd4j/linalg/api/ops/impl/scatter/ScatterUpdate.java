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

package org.nd4j.linalg.api.ops.impl.scatter;

import org.nd4j.autodiff.samediff.SDVariable;
import org.nd4j.autodiff.samediff.SameDiff;
import org.nd4j.imports.NoOpNameFoundException;
import org.nd4j.linalg.api.ops.DynamicCustomOp;

import java.util.ArrayList;
import java.util.List;


/**
 * Scatter update op
 *
 * @author Alex Black
 */

public class ScatterUpdate extends DynamicCustomOp {

    public ScatterUpdate(SameDiff sameDiff, SDVariable ref, SDVariable indices, SDVariable updates) {
        super(null, sameDiff, new SDVariable[]{ref, indices, updates}, false);
    }

    public ScatterUpdate(){}

    @Override
    public String opName() {
        return "scatter_upd";
    }

    @Override
    public String onnxName() {
        throw new NoOpNameFoundException("No onnx op opName found for " + opName());
    }

    @Override
    public String tensorflowName() {
        return "ScatterUpdate";
    }

    @Override
    public List<SDVariable> doDiff(List<SDVariable> gradOut){
        //3 args: ref, indices, updates
        //For non-modified indices, input gradient (reference) is same as output gradient
        //For modified indices, dL/dref = dL/dOut * dOut/dRef = dL/dOut * d(update)/dRef = 0
        //And for updates, dL/du = dL/dOut * dOut/du = dL/dOut * d(update)/du = dL/dOut -> gather op

        SDVariable indices = arg(1);
        SDVariable updates = arg(2);

        List<SDVariable> ret = new ArrayList<>(3);
        SDVariable zerosUpdate = f().zerosLike(updates);
        SDVariable gradRef = f().scatterMul(gradOut.get(0), indices, zerosUpdate);  //TODO optimize
        ret.add(gradRef);            //Reference array gradient
        ret.add(f().zerosLike(arg(1)));  //Indices

        SDVariable gather = f().gather(gradOut.get(0), indices, 0);       //Updates
        ret.add(gather);

        return ret;
    }

}
