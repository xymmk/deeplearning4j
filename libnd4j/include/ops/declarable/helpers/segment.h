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
//  @author sgazeos@gmail.com
//  @brief helpers fuctions for segment_* ops (segment_max, segment_min, segment_mean, segment_sum and segment_prod)
//
#ifndef __SEGMENT_HELPERS__
#define __SEGMENT_HELPERS__
#include <op_boilerplate.h>
#include <NDArray.h>

namespace nd4j {
namespace ops {
namespace helpers {

    template <typename T>
    bool segmentIndicesValidate(NDArray<T>* indices, T& expected, T& output);

    template <typename T>
    void segmentMaxFunctor(NDArray<T>* input, NDArray<T>* indices, NDArray<T>* output);

    template <typename T>
    void segmentMinFunctor(NDArray<T>* input, NDArray<T>* indices, NDArray<T>* output);

    template <typename T>
    void segmentMeanFunctor(NDArray<T>* input, NDArray<T>* indices, NDArray<T>* output);

    template <typename T>
    void segmentSumFunctor(NDArray<T>* input, NDArray<T>* indices, NDArray<T>* output);

    template <typename T>
    void segmentProdFunctor(NDArray<T>* input, NDArray<T>* indices, NDArray<T>* output);

}
}
}
#endif
