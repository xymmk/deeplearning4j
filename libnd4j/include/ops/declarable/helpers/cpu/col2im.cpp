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
// Created by raver119 on 30.11.17.
//

#include <ops/declarable/helpers/col2im.h>

namespace nd4j {
namespace ops {
namespace helpers {

// [bS, iC, kH, kW, oH, oW] is de-convoluted to [bS, iC, iH, iW]
template <typename T>
void _col2im(nd4j::graph::LaunchContext& context, T *imBuff, T *colBuff, Nd4jLong *imShapeBuffer, Nd4jLong *colShapeBuffer, int sH, int sW, int pH, int pW, int iH, int iW, int dH, int dW) {

    T extraParams[] = {(T)sH, (T)sW, (T)pH, (T)pW, (T)iH, (T)iW, (T)dH, (T)dW};         
    functions::transform::Transform<T>::template exec<simdOps::Col2Im<T>>(colBuff, colShapeBuffer, imBuff, imShapeBuffer, extraParams, nullptr, nullptr);    
}

template void _col2im<float>(nd4j::graph::LaunchContext& context, float *in, float *output, Nd4jLong *outShapeInfo, Nd4jLong *inShapeInfo, int sH, int sW, int pH, int pW, int iH, int iW, int dH, int dW);
template void _col2im<float16>(nd4j::graph::LaunchContext& context, float16 *in, float16 *output, Nd4jLong *outShapeInfo, Nd4jLong *inShapeInfo, int sH, int sW, int pH, int pW, int iH, int iW, int dH, int dW);
template void _col2im<double>(nd4j::graph::LaunchContext& context, double *in, double *output, Nd4jLong *outShapeInfo, Nd4jLong *inShapeInfo, int sH, int sW, int pH, int pW, int iH, int iW, int dH, int dW);

}
}
}
