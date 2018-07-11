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

#ifndef LIBND4J_DECLARABLE_LIST_OP_H
#define LIBND4J_DECLARABLE_LIST_OP_H

#include <array/ResultSet.h>
#include <graph/Context.h>
#include <ops/declarable/OpRegistrator.h>
#include <ops/declarable/DeclarableOp.h>

using namespace nd4j::graph;

namespace nd4j {
    namespace ops {
        template <typename T>
        class ND4J_EXPORT DeclarableListOp : public nd4j::ops::DeclarableOp<T> {
        protected:
            virtual Nd4jStatus validateAndExecute(Context<T>& block) = 0;

            nd4j::NDArray<T>* getZ(Context<T>& block, int inputId);
        public:
            DeclarableListOp(int numInputs, int numOutputs, const char* opName, int tArgs, int iArgs);
            ~DeclarableListOp();

            
            Nd4jStatus execute(Context<T>* block) override;
            

            ResultSet<T>* execute(NDArrayList<T>* list, std::initializer_list<NDArray<T>*> inputs, std::initializer_list<T> tArgs, std::initializer_list<int> iArgs);
            ResultSet<T>* execute(NDArrayList<T>* list, std::vector<NDArray<T>*>& inputs, std::vector<T>& tArgs, std::vector<int>& iArgs);

            ShapeList* calculateOutputShape(ShapeList* inputShape, nd4j::graph::Context<T>& block) override;
        };
    }
}

#endif