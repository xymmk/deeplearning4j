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
// Created by raver119 on 08.10.2017.
//

#include <op_boilerplate.h>
#if NOT_EXCLUDED(OP_avgpool3d)

#include <ops/declarable/CustomOperations.h>
#include <ops/declarable/generic/helpers/convolutions.h>

namespace nd4j {
    namespace ops {
        DECLARE_SHAPE_FN(avgpool3d) {
            auto input = inputShape->at(0);

            int kT = INT_ARG(0);
            int kW = INT_ARG(1);
            int kH = INT_ARG(2);
            int dT = INT_ARG(3);
            int dW = INT_ARG(4);
            int dH = INT_ARG(5);
            int padT = INT_ARG(6);
            int padW = INT_ARG(7);
            int padH = INT_ARG(8);
            bool ceil_mode = INT_ARG(9) != 0;

            REQUIRE_TRUE(dT != 0 && dH != 0 && dW != 0, 0, "AVGPOOL3D op: dilation must not be zero, but got instead {%i, %i, %i}", dT, dH, dW);

            Nd4jLong nslices;
            Nd4jLong itime;
            Nd4jLong iheight;
            Nd4jLong iwidth;
            Nd4jLong otime;
            Nd4jLong oheight;
            Nd4jLong owidth;

            int dimN = 2;
            int dimt = 3;
            int dimh = 4;
            int dimw = 5;

            int nBatch = input[1];
            nslices = input[dimN];
            itime   = input[dimt];
            iheight = input[dimh];
            iwidth  = input[dimw];

            if (ceil_mode)
            {
                otime   = (Nd4jLong)(nd4j::math::nd4j_ceil<T>((T)(itime   - kT + 2*padT) / dT)) + 1;
                oheight = (Nd4jLong)(nd4j::math::nd4j_ceil<T>((T)(iheight - kH + 2*padH) / dH)) + 1;
                owidth  = (Nd4jLong)(nd4j::math::nd4j_ceil<T>((T)(iwidth  - kW + 2*padW) / dW)) + 1;
            }
            else
            {
                otime   = (Nd4jLong)(nd4j::math::nd4j_floor<T>((T)(itime   - kT + 2*padT) / dT)) + 1;
                oheight = (Nd4jLong)(nd4j::math::nd4j_floor<T>((T)(iheight - kH + 2*padH) / dH)) + 1;
                owidth  = (Nd4jLong)(nd4j::math::nd4j_floor<T>((T)(iwidth  - kW + 2*padW) / dW)) + 1;
            }
            if (padT || padH || padW)
            {
                // ensure that the last pooling starts inside the image
                // needed to avoid problems in ceil mode
                if ((otime   - 1)*dT >= itime   + padT)
                    --otime;
                if ((oheight - 1)*dH >= iheight + padH)
                    --oheight;
                if ((owidth  - 1)*dW >= iwidth  + padW)
                    --owidth;
            }

            Nd4jLong *shapeOf;
            Nd4jLong *newShape;
            ALLOCATE(shapeOf, block.getWorkspace(), 5, Nd4jLong);
            ALLOCATE(newShape, block.getWorkspace(), shape::shapeInfoLength(5), Nd4jLong);

            nd4j::ArrayUtils::toLongPtr({nBatch, (Nd4jLong) nslices, (Nd4jLong)otime, (Nd4jLong)oheight, (Nd4jLong)owidth}, shapeOf);

            shape::shapeBuffer(5, shapeOf, newShape);

            RELEASE(shapeOf, block.getWorkspace());
            return SHAPELIST(newShape);
        }


//////////////////////////////////////////////////////////////////////////
        CUSTOM_OP_IMPL(avgpool3d_bp, 2, 1, true, 0, 11) {
            NDArray<T> *input = INPUT_VARIABLE(0);
            NDArray<T> *gradNext = INPUT_VARIABLE(1);

            NDArray<T> *output = this->getZ(block);

            REQUIRE_TRUE(input->rankOf() == 5, 0, "Input should be 5D, got %i instead", input->rankOf());

            Nd4jLong nslices;
            Nd4jLong itime;
            Nd4jLong iheight;
            Nd4jLong iwidth;
            Nd4jLong otime;
            Nd4jLong oheight;
            Nd4jLong owidth;
            T *gradInput_data;
            T *gradOutput_data;
            int kT = INT_ARG(0);
            int kW = INT_ARG(1);
            int kH = INT_ARG(2);
            int dT = INT_ARG(3);
            int dW = INT_ARG(4);
            int dH = INT_ARG(5);
            int padT = INT_ARG(6);
            int padW = INT_ARG(7);
            int padH = INT_ARG(8);
            bool ceil_mode = INT_ARG(9) != 0;
            bool count_include_pad  = INT_ARG(10) != 0;

            REQUIRE_TRUE(output->isSameShape(input), 0, "Output gradients should have the same dimensionality as input");
            REQUIRE_TRUE(dT != 0 && dH != 0 && dW != 0, 0, "AVGPOOL3D_BP op: dilation must not be zero, but got instead {%i, %i, %i}", dT, dH, dW);

            int dimN = 1;
            int dimt = 2;
            int dimh = 3;
            int dimw = 4;

            ConvolutionUtils<T>::avgPool3DBP(*gradNext, *output,  kT, kW, kH, dT, dW, dH, padT, padW, padH, count_include_pad);

            STORE_RESULT(*output);

            return ND4J_STATUS_OK;
        }
        DECLARE_SHAPE_FN(avgpool3d_bp) {
            // output shape equals to input shape, all out of sudden
            Nd4jLong* newShape;
            COPY_SHAPE(inputShape->at(0), newShape);
            return SHAPELIST(newShape);
        }


        //////////////////////////////////////////////////////////////////////////
        CUSTOM_OP_IMPL(avgpool3d, 1, 1, true, 0, 11) {

            NDArray<T> *input = INPUT_VARIABLE(0);
            NDArray<T> *output = OUTPUT_VARIABLE(0);

            REQUIRE_TRUE(input->rankOf() == 5, 0, "Input should be 5D, got %i instead", input->rankOf());

            int kT = INT_ARG(0);
            int kW = INT_ARG(1);
            int kH = INT_ARG(2);
            int dT = INT_ARG(3);
            int dW = INT_ARG(4);
            int dH = INT_ARG(5);
            int padT = INT_ARG(6);
            int padW = INT_ARG(7);
            int padH = INT_ARG(8);
            bool ceil_mode = INT_ARG(9) != 0;
            bool count_include_pad  = INT_ARG(10) != 0;

            REQUIRE_TRUE(dT != 0 && dH != 0 && dW != 0, 0, "AVGPOOL3D op: dilation must not be zero, but got instead {%i, %i, %i}", dT, dH, dW);

            Nd4jLong bS;
            Nd4jLong nslices;
            Nd4jLong itime;
            Nd4jLong iheight;
            Nd4jLong iwidth;
            Nd4jLong otime;
            Nd4jLong oheight;
            Nd4jLong owidth;
            T *input_data;
            T *output_data;

            int dimN = 1;
            int dimt = 2;
            int dimh = 3;
            int dimw = 4;

            bS      = input->sizeAt(0);
            nslices = input->sizeAt(dimN);
            itime   = input->sizeAt(dimt);
            iheight = input->sizeAt(dimh);
            iwidth  = input->sizeAt(dimw);

            if (ceil_mode)
            {
                otime   = (Nd4jLong)(nd4j::math::nd4j_ceil<T>((T)(itime   - kT + 2*padT) / dT)) + 1;
                oheight = (Nd4jLong)(nd4j::math::nd4j_ceil<T>((T)(iheight - kH + 2*padH) / dH)) + 1;
                owidth  = (Nd4jLong)(nd4j::math::nd4j_ceil<T>((T)(iwidth  - kW + 2*padW) / dW)) + 1;
            }
            else
            {
                otime   = (Nd4jLong)(nd4j::math::nd4j_floor<T>((T)(itime   - kT + 2*padT) / dT)) + 1;
                oheight = (Nd4jLong)(nd4j::math::nd4j_floor<T>((T)(iheight - kH + 2*padH) / dH)) + 1;
                owidth  = (Nd4jLong)(nd4j::math::nd4j_floor<T>((T)(iwidth  - kW + 2*padW) / dW)) + 1;
            }
            if (padT || padH || padW)
            {
                // ensure that the last pooling starts inside the image
                // needed to avoid problems in ceil mode
                if ((otime   - 1)*dT >= itime   + padT)
                    --otime;
                if ((oheight - 1)*dH >= iheight + padH)
                    --oheight;
                if ((owidth  - 1)*dW >= iwidth  + padW)
                    --owidth;
            }

            int nBatch = input->sizeAt(0);

            Nd4jLong istride = nslices * itime * iwidth * iheight;
            Nd4jLong ostride = nslices * otime * owidth * oheight;

            REQUIRE_TRUE(output->isSameShape({nBatch, (int) nslices, (int)otime, (int)oheight, (int)owidth}), 0, "Output should have shape of [%i, %i, %i, %i, %i], but got [%i, %i, %i, %i, %i] instead", nBatch, nslices, otime, oheight, owidth, output->sizeAt(0), output->sizeAt(1), output->sizeAt(2), output->sizeAt(3), output->sizeAt(4));

            ConvolutionUtils<T>::avgPool3D(*input, *output,  kT, kH, kW, dT, dH, dW, padT, padH, padW, count_include_pad);

            STORE_RESULT(*output);

            return ND4J_STATUS_OK;
        }



//////////////////////////////////////////////////////////////////////////
        CUSTOM_OP_IMPL(maxpool3d, 1, 2, true, 0, 13) {

            NDArray<T> *input = INPUT_VARIABLE(0);

            NDArray<T> *output = OUTPUT_VARIABLE(0);

            // FIXME: we want to stash this one
            NDArray<T> *indices = OUTPUT_VARIABLE(1);

            REQUIRE_TRUE(input->sizeOfT() > 2, 0, "MaxPool3D can't be used in HALF precision")
            REQUIRE_TRUE(input->rankOf() == 5, 0, "Input should be 5D, got rank %i instead", input->rankOf());
            REQUIRE_TRUE(output->rankOf() == 5, 0, "Output should be 5D, got rank %i instead", output->rankOf());

            // TODO change width/height order  height/width
            int kT = INT_ARG(0);
            int kW = INT_ARG(1);
            int kH = INT_ARG(2);
            int dT = INT_ARG(3);
            int dW = INT_ARG(4);
            int dH = INT_ARG(5);
            int pT = INT_ARG(6);
            int pW = INT_ARG(7);
            int pH = INT_ARG(8);
            int dilationT = INT_ARG(9);
            int dilationW = INT_ARG(10);
            int dilationH = INT_ARG(11);
            bool ceilMode = INT_ARG(12) != 0;


            REQUIRE_TRUE(kT > 0 && kW > 0 && kH > 0, 0,
                         "Kernel size should be greater than zero, but got kT: %d kH: %d kW: %d",
                         kT, kH, kW);

            REQUIRE_TRUE(dT > 0 && dW > 0 && dH > 0, 8,
                         "stride should be greater than zero, but got dT: %d dH: %d dW: %d",
                         dT, dH, dW);

            REQUIRE_TRUE(dilationT > 0 && dilationW > 0 && dilationH > 0, 14,
                         "dilation should be greater than 0, but got dilationT: %d dilationH: %d dilationW: %d",
                         dilationT, dilationH, dilationW);

            REQUIRE_TRUE(kT/2 >= pT && kW/2 >= pW && kH/2 >= pH, 2,
                         "pad should be smaller than half of kernel size, but got "
                                 "kT: %d kW: %d, kH: %d, padT: %d, padW: %d, padH: %d",
                         kT, kW, kH, pT, pW, pH);

            Nd4jLong nslices;
            Nd4jLong itime;
            Nd4jLong iheight;
            Nd4jLong iwidth;
            Nd4jLong otime;
            Nd4jLong oheight;
            Nd4jLong owidth;
            T *input_data(nullptr);
            T *output_data(nullptr);

            ////////////
            T *indices_data(nullptr);


            int dimN = 1;
            int dimt = 2;
            int dimh = 3;
            int dimw = 4;


            nslices = input->sizeAt(dimN);
            itime   = input->sizeAt(dimt);
            iheight = input->sizeAt(dimh);
            iwidth  = input->sizeAt(dimw);

            if (ceilMode) {
                otime = (int)(nd4j::math::nd4j_ceil<T>((T)(itime - (dilationT * (kT - 1) + 1) + 2*pT) / dT)) + 1;
                oheight = (int)(nd4j::math::nd4j_ceil<T>((T)(iheight - (dilationH * (kH - 1) + 1) + 2*pH) / dH)) + 1;
                owidth  = (int)(nd4j::math::nd4j_ceil<T>((T)(iwidth  - (dilationW * (kW - 1) + 1) + 2*pW) / dW)) + 1;
            } else {
                otime = (int)(nd4j::math::nd4j_floor<T>((T)(itime - (dilationT * (kT - 1) + 1) + 2*pT) / dT)) + 1;
                oheight = (int)(nd4j::math::nd4j_floor<T>((T)(iheight - (dilationH * (kH - 1) + 1) + 2*pH) / dH)) + 1;
                owidth  = (int)(nd4j::math::nd4j_floor<T>((T)(iwidth  - (dilationW * (kW - 1) + 1) + 2*pW) / dW)) + 1;
            }

            if (pT > 0 || pW > 0 || pH > 0) {
                // ensure that the last pooling starts inside the image
                if ((otime - 1)*dT >= itime + pT)
                    --otime;
                if ((oheight - 1)*dH >= iheight + pH)
                    --oheight;
                if ((owidth  - 1)*dW >= iwidth  + pW)
                    --owidth;
            }

            REQUIRE_TRUE(otime >= 1 && owidth >= 1 && oheight >= 1, 0, "Output size is too small: [%i, %i, %i]", otime, oheight, owidth);

            NDArray<T>* _input;
            if (!input->isContiguous())
                _input = input->dup(input->ordering());
            else
                _input = input;

            Nd4jLong istride = nslices * itime * iwidth * iheight;
            Nd4jLong ostride = nslices * otime * owidth * oheight;

            input_data = _input->getBuffer();
            output_data = output->getBuffer();
            indices_data = indices->getBuffer();

            for (int n = 0; n < input->sizeAt(0); n++) {
                ConvolutionUtils<T>::_dilatedMaxPool3D(
                        input_data   + n * istride,
                        output_data  + n * ostride,
                        indices_data + n * ostride,
                        nslices,
                        itime, iwidth, iheight,
                        otime, owidth, oheight,
                        kT, kW, kH,
                        dT, dW, dH,
                        pT, pW, pH,
                        dilationT, dilationW, dilationH);
            }

            if (_input != input)
                delete _input;

            STORE_RESULT(*output);

            return ND4J_STATUS_OK;
        }
        DECLARE_SYN(MaxPool3D, maxpool3d);
        DECLARE_SYN(MaxPool3d, maxpool3d);

        
        DECLARE_SHAPE_FN(maxpool3d) {

            // REQUIRE_TRUE(output->sizeAt(0) == input->sizeAt(0) && output->sizeAt(1) == nslices && output->sizeAt(2) == otime && output->sizeAt(3) == oheight && output->sizeAt(4) == owidth, 0,
            // "Output shape expected to be [%i, %i, %i, %i, %i], but got [%i, %i, %i, %i, %i] instead", input->sizeAt(0), nslices, otime, oheight, owidth, output->sizeAt(0), output->sizeAt(1), output->sizeAt(2), output->sizeAt(3), output->sizeAt(4));
            // REQUIRE_TRUE(indices->isSameShape(output), 0, "Output and Indices shapes should be equal");

            Nd4jLong* inputShapeInfo = inputShape->at(0);   
                
            int rank = inputShapeInfo[0];       // = 5
            int bS = inputShapeInfo[1];
            int nslices = inputShapeInfo[2];
            int itime   = inputShapeInfo[3];
            int iheight = inputShapeInfo[4];
            int iwidth  = inputShapeInfo[5];
            int dilationT = INT_ARG(9);
            int dilationW = INT_ARG(10);
            int dilationH = INT_ARG(11);
            int kT = INT_ARG(0);
            int kW = INT_ARG(1);
            int kH = INT_ARG(2);
            int dT = INT_ARG(3);
            int dW = INT_ARG(4);
            int dH = INT_ARG(5);
            int pT = INT_ARG(6);
            int pW = INT_ARG(7);
            int pH = INT_ARG(8);

            REQUIRE_TRUE(dilationT != 0 && dilationH != 0 && dilationW != 0, 0, "MAXPOOL3D op: dilation must not be zero, but got instead {%i, %i, %i}", dilationT, dilationH, dilationW);

            bool ceilMode = INT_ARG(12) != 0;
            
            int otime, oheight, owidth;
            if (ceilMode) {
                otime = (int)(nd4j::math::nd4j_ceil<T>((T)(itime - (dilationT * (kT - 1) + 1) + 2*pT) / dT)) + 1;
                oheight = (int)(nd4j::math::nd4j_ceil<T>((T)(iheight - (dilationH * (kH - 1) + 1) + 2*pH) / dH)) + 1;
                owidth  = (int)(nd4j::math::nd4j_ceil<T>((T)(iwidth  - (dilationW * (kW - 1) + 1) + 2*pW) / dW)) + 1;
            } else {
                otime = (int)(nd4j::math::nd4j_floor<T>((T)(itime - (dilationT * (kT - 1) + 1) + 2*pT) / dT)) + 1;
                oheight = (int)(nd4j::math::nd4j_floor<T>((T)(iheight - (dilationH * (kH - 1) + 1) + 2*pH) / dH)) + 1;
                owidth  = (int)(nd4j::math::nd4j_floor<T>((T)(iwidth  - (dilationW * (kW - 1) + 1) + 2*pW) / dW)) + 1;
            }


            int shapeInfoLength = rank*2 + 4;        
            char order = (char)(inputShapeInfo[shapeInfoLength-1]);
        
            Nd4jLong* newShapeInfo0(nullptr), *newShapeInfo1(nullptr);
            ALLOCATE(newShapeInfo0, block.getWorkspace(), shapeInfoLength, Nd4jLong);
            ALLOCATE(newShapeInfo1, block.getWorkspace(), shapeInfoLength, Nd4jLong);

            newShapeInfo0[0] = rank;
            newShapeInfo0[1] = bS;
            newShapeInfo0[2] = nslices;
            newShapeInfo0[3] = otime;
            newShapeInfo0[4] = oheight;
            newShapeInfo0[5] = owidth;

            shape::updateStrides(newShapeInfo0, order);

            memcpy(newShapeInfo1, newShapeInfo0, shape::shapeInfoByteLength(newShapeInfo0));

            return SHAPELIST(newShapeInfo0, newShapeInfo1);

        }   


//////////////////////////////////////////////////////////////////////////
        CUSTOM_OP_IMPL(maxpool3d_bp, 3, 1, true, 0, 13) {

            NDArray<T> *input = INPUT_VARIABLE(0);
            NDArray<T> *gradNext = INPUT_VARIABLE(1);
            NDArray<T> *indices = INPUT_VARIABLE(2);

            NDArray<T> *output = this->getZ(block);

            REQUIRE_TRUE(input->rankOf() == 5, 0, "Input should be 5D, got %i instead", input->rankOf());
            REQUIRE_TRUE(indices->isSameShape(input), 1, "Indices should have the same dimensionality as input");
            REQUIRE_TRUE(output->isSameShape(input), 1, "Output gradient should have the same dimensionality as input");


            int kT = INT_ARG(0);
            int kW = INT_ARG(1);
            int kH = INT_ARG(2);
            int dT = INT_ARG(3);
            int dW = INT_ARG(4);
            int dH = INT_ARG(5);
            int pT = INT_ARG(6);
            int pW = INT_ARG(7);
            int pH = INT_ARG(8);
            int dilationT = INT_ARG(9);
            int dilationW = INT_ARG(10);
            int dilationH = INT_ARG(11);
            bool ceilMode = INT_ARG(12) != 0;


            REQUIRE_TRUE(kT > 0 && kW > 0 && kH > 0, 0,
                         "Kernel size should be greater than zero, but got kT: %d kH: %d kW: %d",
                         kT, kH, kW);

            REQUIRE_TRUE(dT > 0 && dW > 0 && dH > 0, 8,
                         "stride should be greater than zero, but got dT: %d dH: %d dW: %d",
                         dT, dH, dW);

            REQUIRE_TRUE(dilationT > 0 && dilationW > 0 && dilationH > 0, 14,
                         "dilation should be greater than 0, but got dilationT: %d dilationH: %d dilationW: %d",
                         dilationT, dilationH, dilationW);

            REQUIRE_TRUE(kT/2 >= pT && kW/2 >= pW && kH/2 >= pH, 2,
                         "pad should be smaller than half of kernel size, but got "
                                 "kT: %d kW: %d, kH: %d, padT: %d, padW: %d, padH: %d",
                         kT, kW, kH, pT, pW, pH);


            int nslices;
            int itime;
            int iheight;
            int iwidth;
            int otime;
            int oheight;
            int owidth;
            T *gradInput_data;
            T *gradOutput_data;
            T *indices_data;

            int dimN = 1;
            int dimt = 2;
            int dimh = 3;
            int dimw = 4;

            /* sizes */
            nslices = input->sizeAt(dimN);
            itime = input->sizeAt(dimt);
            iheight = input->sizeAt(dimh);
            iwidth = input->sizeAt(dimw);
            otime = gradNext->sizeAt(dimt);
            oheight = gradNext->sizeAt(dimh);
            owidth = gradNext->sizeAt(dimw);

            /* get raw pointers */
            gradInput_data = output->getBuffer();
            gradOutput_data = gradNext->getBuffer();
            indices_data = indices->getBuffer();

            int nBatch = input->sizeAt(0);

            Nd4jLong istride = nslices * itime * iwidth * iheight;
            Nd4jLong ostride = nslices * otime * owidth * oheight;

            for (int p = 0; p < nBatch; p++) {
                ConvolutionUtils<T>::_dilatedMaxPool3D_bp(
                        gradInput_data + p * istride,
                        gradOutput_data + p * ostride,
                        indices_data + p * ostride,
                        nslices,
                        itime, iwidth, iheight,
                        otime, owidth, oheight,
                        dT, dW, dH,
                        pT, pW, pH,
                        dilationT, dilationW, dilationH
                );
            }

            STORE_RESULT(*output);

            return ND4J_STATUS_OK;
        }
        DECLARE_SHAPE_FN(maxpool3d_bp) {
            // output shape equals to input shape, all out of sudden
            // FIXME: remove memcpy here
            Nd4jLong* newShape;
            COPY_SHAPE(inputShape->at(0), newShape);
            return SHAPELIST(newShape);
        }
    }
}

#endif