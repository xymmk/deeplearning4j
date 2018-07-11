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
#if NOT_EXCLUDED(OP_unique)

#include <ops/declarable/CustomOperations.h>
#include <ops/declarable/helpers/unique.h>

namespace nd4j {
    namespace ops {
        CUSTOM_OP_IMPL(unique, 1, 2, false, 0, 0) {
            auto x = INPUT_VARIABLE(0);
            auto values = OUTPUT_VARIABLE(0);
            auto indices = OUTPUT_VARIABLE(1);

            return helpers::uniqueFunctor(x, values, indices,  (NDArray<T>*)nullptr);
        }

        DECLARE_SHAPE_FN(unique) {
/*
            auto shapeList = SHAPELIST(); 
            for (int e = 0; e < 2; e++) {
                int* newshape;
                ALLOCATE(newshape, block.getWorkspace(), shape::shapeInfoLength(inputShape->at(0)), int);
                if (shape::order(inputShape->at(0)) == 'c')
                    shape::shapeBuffer(shape::rank(inputShape->at(0)), shape::shapeOf(inputShape->at(0)), newshape);
                else 
                    shape::shapeBufferFortran(shape::rank(inputShape->at(0)), shape::shapeOf(inputShape->at(0)), newshape);
                shapeList->push_back(newshape); 

            }
            return shapeList;
*/
            auto in = inputShape->at(0);
            auto source = INPUT_VARIABLE(0);
//            auto shapeList = SHAPELIST(); 
            Nd4jLong* valuesShape;
            Nd4jLong* indicesShape;

            int uniqueCount = helpers::uniqueCount(source);

            // all output shapes are 1D arrays (vectors)
            ALLOCATE(valuesShape, block.getWorkspace(), shape::shapeInfoLength(1), Nd4jLong);
            shape::shapeVector(uniqueCount, valuesShape);

            ALLOCATE(indicesShape, block.getWorkspace(), shape::shapeInfoLength(1), Nd4jLong);
            shape::shapeVector(source->lengthOf(), indicesShape);

            //COPY_SHAPE_EX(in, indicesShape, block.getWorkspace());

            return SHAPELIST(valuesShape, indicesShape);

        }

        CUSTOM_OP_IMPL(unique_with_counts, 1, 3, false, 0, 0) {
            NDArray<T>* input = INPUT_VARIABLE(0);
            NDArray<T>* values = OUTPUT_VARIABLE(0);
            NDArray<T>* indices = OUTPUT_VARIABLE(1);
            NDArray<T>* counts = OUTPUT_VARIABLE(2);

            return helpers::uniqueFunctor(input, values, indices, counts);
        }

        DECLARE_SHAPE_FN(unique_with_counts) {
            auto in = inputShape->at(0);
            auto source = INPUT_VARIABLE(0);
            auto shapeList = SHAPELIST(); 

            Nd4jLong* valuesShape;
            Nd4jLong* indicesShape;
            Nd4jLong* countsShape;

            int uniqueCount = helpers::uniqueCount(source);
            // all output shapes are 1D arrays (vectors)
            ALLOCATE(valuesShape, block.getWorkspace(), shape::shapeInfoLength(1), Nd4jLong);
            shape::shapeVector(uniqueCount, valuesShape);

            ALLOCATE(indicesShape, block.getWorkspace(), shape::shapeInfoLength(1), Nd4jLong);
            shape::shapeVector(source->lengthOf(), indicesShape);

            ALLOCATE(countsShape, block.getWorkspace(), shape::shapeInfoLength(1), Nd4jLong);
            shape::shapeVector(uniqueCount, countsShape);

            shapeList->push_back(valuesShape); 
            shapeList->push_back(indicesShape); 
            shapeList->push_back(countsShape); 

            return shapeList;
        }

    }
}

#endif