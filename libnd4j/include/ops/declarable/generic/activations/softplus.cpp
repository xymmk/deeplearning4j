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

//
//  @author raver119@gmail.com
//

#include <op_boilerplate.h>
#if NOT_EXCLUDED(OP_softplus)

#include <ops/declarable/CustomOperations.h>

namespace nd4j {
    namespace ops {
        CONFIGURABLE_OP_IMPL(softplus, 1, 1, true, 0, 0) {
            NDArray<T> *first = INPUT_VARIABLE(0);
            auto z = this->getZ(block);

            first->template applyTransform<simdOps::SoftPlus<T>>(z, nullptr);

            STORE_RESULT(*z);

            return ND4J_STATUS_OK;
        }

        CONFIGURABLE_OP_IMPL(softplus_bp, 2, 1, true, 0, 0) {
            NDArray<T>* input = INPUT_VARIABLE(0);
            NDArray<T>* epsilon = INPUT_VARIABLE(1);

            auto z = OUTPUT_VARIABLE(0);

            auto lambda = LAMBDA_TT(_x, _e) {
                T p = nd4j::math::nd4j_pow<T>((T) M_E, _x);
                return _e * (p / (p + 1.));
            };

            input->applyPairwiseLambda(epsilon, lambda, z);  

            return ND4J_STATUS_OK;
        }
        DECLARE_SYN(SoftplusGrad, softplus_bp);
    }
}

#endif