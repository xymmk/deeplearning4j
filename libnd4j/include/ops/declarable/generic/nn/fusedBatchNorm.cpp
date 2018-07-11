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
// Created by raver119 on 29/10/17.
//

#include <op_boilerplate.h>
#if NOT_EXCLUDED(OP_fused_batch_norm)

#include <ops/declarable/CustomOperations.h>

namespace nd4j {
namespace ops {

CUSTOM_OP_IMPL(fused_batch_norm, 3, 1, false, 0, 2) {

    NDArray<T>* x      = INPUT_VARIABLE(0);                 // [bS,iH,iW,iD] (NHWC) or [bS,iD,iH,iW] (NCHW)
    NDArray<T>* scale  = INPUT_VARIABLE(1);                 // [iD]
    NDArray<T>* offset = INPUT_VARIABLE(2);                 // [iD]

    NDArray<T>* y = OUTPUT_VARIABLE(0);                     // [bS,iH,iW,iD] (NHWC) or [bS,iD,iH,iW] (NCHW)
    NDArray<T>* batchMean = OUTPUT_VARIABLE(1);             // [iD]
    NDArray<T>* batchVar  = OUTPUT_VARIABLE(2);             // [iD]

    const bool dataFormat = (bool)INT_ARG(0);               // 0->NHWC, 1->NCHW
    const bool isTraining = (bool)INT_ARG(1);    

    REQUIRE_TRUE(x->rankOf() == 4, 0, "CUSTOM_OP fused_batch_norm: the rank of input x array must be equal to 4, but got %i instead !", x->rankOf());    

    int bS = x->sizeAt(0);              // batch size
    int iH, iW, iD;                     // input height, input width, input depth(number of channels)        
    if(dataFormat) {
        iD = x->sizeAt(1);
        iH = x->sizeAt(2);
        iW = x->sizeAt(3);
    }
    else {
        iD = x->sizeAt(3);   
        iH = x->sizeAt(1);
        iW = x->sizeAt(2);        
    }    

    REQUIRE_TRUE(scale->rankOf() == 1  && scale->sizeAt(0)  == iD, 0, "CUSTOM_OP fused_batch_norm: wrong shape of input scale array, expected is [%i], but got %s instead", iD, ShapeUtils<T>::shapeAsString(scale).c_str());
    REQUIRE_TRUE(offset->rankOf() == 1 && offset->sizeAt(0) == iD, 0, "CUSTOM_OP fused_batch_norm: wrong shape of input offset array, expected is [%i], but got %s instead", iD, ShapeUtils<T>::shapeAsString(offset).c_str());

    NDArray<T>* mean(nullptr), *variance(nullptr);
    if(!isTraining){
        mean     = INPUT_VARIABLE(3);   
        variance = INPUT_VARIABLE(4);   
        REQUIRE_TRUE(mean->rankOf() == 1     && mean->sizeAt(0) == iD,     0, "CUSTOM_OP fused_batch_norm: wrong shape of input mean array, expected is [%i], but got %s instead", iD, ShapeUtils<T>::shapeAsString(mean).c_str());
        REQUIRE_TRUE(variance->rankOf() == 1 && variance->sizeAt(0) == iD, 0, "CUSTOM_OP fused_batch_norm: wrong shape of input variance array, expected is [%i], but got %s instead", iD, ShapeUtils<T>::shapeAsString(variance).c_str());
    }
    else {
        REQUIRE_TRUE(block.width() == 3, 0, "CUSTOM_OP fused_batch_norm: when isTraining=true then number of input arrays must be equal to 3, but got %i instead !", block.width());   
        std::vector<Nd4jLong> shape = {iD};
        mean = new NDArray<T>(scale->ordering(), shape, block.getWorkspace());
        variance = new NDArray<T>(scale->ordering(), shape, block.getWorkspace());        
    }

    T epsilon;
    if(block.getTArguments()->size() > 0)         
        epsilon = T_ARG(0) > (T)1.001e-5 ? T_ARG(0) : (T)1.001e-5;    
    else 
        epsilon = 0.001;
    
    const int restSize = x->lengthOf() / iD;    
    NDArray<T> xAffected(x->ordering(), {restSize, iD}, block.getWorkspace());
    xAffected.assign(x);

    const int restSizeMinusOne = (restSize > 1) ? (restSize - 1) : 1;
    const T restSizeInv = (T)1.0 / restSize;
    const T restSizeAdjust = (T)restSize / restSizeMinusOne;

    if(isTraining) {
        NDArray<T>* sum = xAffected.sum({0});
        mean->assign((*sum) * restSizeInv);
        *batchMean = *mean;
        delete sum;
    }
    else 
        *batchMean = 0.;
    
    xAffected -= *mean;

    if(isTraining) {        
        T power = 2.;
        NDArray<T>* sum = xAffected.template transform<simdOps::Pow<T>>(&power).sum({0});
        variance->assign((*sum) * restSizeInv);
        *batchVar  = (*variance) * restSizeAdjust;
        delete sum;
    }
    else 
        *batchVar  = 0.;      

    y->assign( xAffected * (*variance + epsilon).template transform<simdOps::RSqrt<T>>() * (*scale) + (*offset) );    

    if(isTraining) {
        delete mean;
        delete variance;
    }

    return Status::OK();
}



DECLARE_SHAPE_FN(fused_batch_norm) {
    auto xShapeInfo     = inputShape->at(0);
    auto scaleShapeInfo = inputShape->at(1);

    const bool dataFormat = (bool)INT_ARG(0);               // 0->NHWC, 1->NCHW
    const int iD = dataFormat ? xShapeInfo[2] : xShapeInfo[4];

    REQUIRE_TRUE(scaleShapeInfo[0] == 1  && scaleShapeInfo[1] == iD, 0, "CUSTOM_OP fused_batch_norm: wrong shape of input scale array, expected is [%i], but got %s instead", iD, ShapeUtils<T>::shapeAsString(scaleShapeInfo).c_str());
    
    Nd4jLong* outShapeInfo(nullptr), *batchMeanShapeInfo(nullptr), *batchVarShapeInfo(nullptr);
    
    COPY_SHAPE(xShapeInfo, outShapeInfo);
    COPY_SHAPE(scaleShapeInfo, batchMeanShapeInfo);
    COPY_SHAPE(scaleShapeInfo, batchVarShapeInfo);    
    
    return SHAPELIST(outShapeInfo, batchMeanShapeInfo, batchVarShapeInfo);
}




}
}

#endif