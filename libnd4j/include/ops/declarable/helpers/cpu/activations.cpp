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
// @author Yurii Shyrma (iuriish@yahoo.com), created on 19.04.2018
// @author raver119@gmail.com
//

#include<ops/declarable/helpers/activations.h>


namespace nd4j    {
namespace ops     {
namespace helpers {


///////////////////////////////////////////////////////////////////
template <typename T>
void softMaxForVector(const NDArray<T>& input, NDArray<T>& output) {

    if(!input.isVector() || !output.isVector())
        throw std::runtime_error("ops::helpers::softMaxForVector function: input and output arrays must be vectors !");

    T* inBuff  = const_cast<NDArray<T>&>(input).getBuffer();
    T* outBuff = output.getBuffer();
    auto inShapeInfo  = input.getShapeInfo();
    auto outShapeInfo = output.getShapeInfo();

    T max = -FLOAT_MAX_VALUE;
    T sum = 0.;
    int inEWS = shape::elementWiseStride(inShapeInfo);
    int outEWS = shape::elementWiseStride(outShapeInfo);
    int length = shape::length(inShapeInfo);
    
    if (inEWS >= 1 && outEWS >= 1) {

        if (inEWS == 1 && outEWS == 1) {

#pragma omp simd reduction(maxT:max)
            for (int i = 0; i < length; i++)
                max = nd4j::math::nd4j_max<T>(max, inBuff[i]);                      

#pragma omp parallel for simd reduction(sumT:sum)
            for (int i = 0; i < length; i++) {
                outBuff[i] = nd4j::math::nd4j_exp<T>(inBuff[i] - max);
                sum += outBuff[i];
            }
#pragma omp simd
            for (int i = 0; i < length; i++)
                outBuff[i] /= sum;
        }
        else {

#pragma omp simd reduction(maxT:max)
            for (int i = 0; i < length; i++)
                max = nd4j::math::nd4j_max<T>(max, inBuff[i * inEWS]);

#pragma omp parallel for simd reduction(sumT:sum)
            for (int i = 0; i < length; i++) {
                T r = nd4j::math::nd4j_exp<T>(inBuff[i * inEWS] - max);
                outBuff[i * outEWS] = r;
                sum += r;
            }
#pragma omp simd
            for (int i = 0; i < length; i++)
                outBuff[i * outEWS] /= sum;                     
        }
    }
}


///////////////////////////////////////////////////////////////////
template <typename T>
void logSoftMaxForVector(const NDArray<T>& input, NDArray<T>& output) {

    if(!input.isVector() || !output.isVector())
        throw std::runtime_error("ops::helpers::logSoftMaxForVector function input and output arrays must be vectors !");

    T* inBuff  = const_cast<NDArray<T>&>(input).getBuffer();
    T* outBuff = output.getBuffer();
    auto inShapeInfo  = input.getShapeInfo();
    auto outShapeInfo = output.getShapeInfo();

    T max = -FLOAT_MAX_VALUE;
    T sum = 0;

    auto inEWS  = shape::elementWiseStride(inShapeInfo);
    auto length = shape::length(inShapeInfo);
    
    if (inEWS == 1) {
#pragma omp simd reduction(maxT:max)
        for (int i = 0; i < length; i++)
            max = nd4j::math::nd4j_max<T>(max, outBuff[i]);

#pragma omp simd reduction(sumT:sum)
        for (int i = 0; i < length; i++) {
            outBuff[i] = nd4j::math::nd4j_exp<T>(inBuff[i] - max);
            sum += outBuff[i];
        }
#pragma omp simd
        for (int i = 0; i < length; i++) {
            outBuff[i] /= sum;
            outBuff[i] = nd4j::math::nd4j_log<T>(outBuff[i]);
        }
    }
    else if (inEWS > 1) {

#pragma omp simd reduction(maxT:max)
        for (int i = 0; i < length; i++)
            max = nd4j::math::nd4j_max<T>(max, outBuff[i * inEWS]);

#pragma omp simd reduction(sumT:sum)
        for (int i = 0; i < length; i++) {
            outBuff[i * inEWS] = nd4j::math::nd4j_exp<T>(inBuff[i * inEWS] - max);
            sum += outBuff[i * inEWS];
        }
#pragma omp simd
        for (int i = 0; i < length; i++) {
            outBuff[i * inEWS] /= sum;
            outBuff[i * inEWS] = nd4j::math::nd4j_log<T>(outBuff[i * inEWS]);
        }
    }   
}


//////////////////////////////////////////////////////////////////////////
template <typename T>
void softmax(const NDArray<T>& input, NDArray<T>& output, const int dimension) {

    const int rank = input.rankOf();

    if(input.isVector()) {
        
        if(rank == 1 || input.sizeAt(dimension) != 1)
            softMaxForVector<T>(input, output);
        else
            output = 1.;
    }
    else {
        
        NDArray<T> exponents = const_cast<NDArray<T>&>(input).template transform<simdOps::Exp<T>>();
        NDArray<T> sumAlongDim = exponents.template reduceAlongDims<simdOps::Sum<T>>({dimension}, true);        
        output.assign(exponents / sumAlongDim);
    }
}


template void softMaxForVector<float>  (const NDArray<float  >& input, NDArray<float  >& output);
template void softMaxForVector<float16>(const NDArray<float16>& input, NDArray<float16>& output);
template void softMaxForVector<double> (const NDArray<double >& input, NDArray<double >& output);

template void logSoftMaxForVector<float>  (const NDArray<float  >& input, NDArray<float  >& output);
template void logSoftMaxForVector<float16>(const NDArray<float16>& input, NDArray<float16>& output);
template void logSoftMaxForVector<double> (const NDArray<double >& input, NDArray<double >& output);

template void softmax<float>(const NDArray<float>& input, NDArray<float>& output, const int dimension);
template void softmax<float16>(const NDArray<float16>& input, NDArray<float16>& output, const int dimension);
template void softmax<double>(const NDArray<double>& input, NDArray<double>& output, const int dimension);


}
}
}

