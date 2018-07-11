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
// @author raver119@gmail.com
//

#include <ops/declarable/OpDescriptor.h>
#include <ops/declarable/DeclarableListOp.h>
#include <graph/Context.h>
#include <graph/Variable.h>
#include <graph/VariableSpace.h>

namespace nd4j {
    namespace ops {
        template <typename T>
        DeclarableListOp<T>::~DeclarableListOp() {
            //
        }

        template <typename T>
        DeclarableListOp<T>::DeclarableListOp(int numInputs, int numOutputs, const char* opName, int tArgs, int iArgs) : DeclarableOp<T>::DeclarableOp(numInputs, numOutputs, opName, false, tArgs, iArgs) {
            // This kind of operations work with sets: NDArrayList
            this->getOpDescriptor()->setInputType(InputType_NUMERIC_SET);
        }
/*
        template <typename T>
        void DeclarableListOp<T>::execute(Block<T>& block)  {
            //
        }
*/
        /**
         * This method just outputs scalar buffer
         *
         * @tparam T
         * @param inputShape
         * @param block
         * @return
         */
        template <typename T>
        ShapeList* DeclarableListOp<T>::calculateOutputShape(ShapeList* inputShape, nd4j::graph::Context<T>& block) {
            // TODO: ensure this method isn't ever called

            std::vector<Nd4jLong> shape({1, 1});
            Nd4jLong *newShape;
            ALLOCATE(newShape, block.getWorkspace(), shape::shapeInfoLength(2), Nd4jLong);
            shape::shapeBuffer(2, shape.data(), newShape);

            return SHAPELIST(newShape);
        }

        template <typename T>
        nd4j::NDArray<T>* nd4j::ops::DeclarableListOp<T>::getZ(Context<T>& block, int inputId) {
            //nd4j_printf("wow\n","");
            return nullptr;
        }

        template <typename T>
        ResultSet<T>* DeclarableListOp<T>::execute(NDArrayList<T>* list, std::initializer_list<NDArray<T>*> inputs, std::initializer_list<T> tArgs, std::initializer_list<int> iArgs) {
            std::vector<NDArray<T>*> ins(inputs);
            std::vector<T> tas(tArgs);
            std::vector<int> ias(iArgs);
            return this->execute(list, ins, tas, ias);
        }

        template <typename T>
        Nd4jStatus DeclarableListOp<T>::execute(Context<T>* block) {
            if (block == nullptr)
                throw std::invalid_argument("Block is NULL");

            nd4j_debug("Executing list op: [%s]\n", this->getOpName()->c_str());

            // ensure number of IArgs, TArgs match our expectations
            REQUIRE_OK(this->validateArguments(*block));

            // we shouldn't call for this in ListOp
            //this->prepareOutputs(*block);

            auto timeStart = std::chrono::system_clock::now();

            Nd4jStatus status = this->validateAndExecute(*block);

            auto timeEnd = std::chrono::system_clock::now();
            auto outerTime = std::chrono::duration_cast<std::chrono::nanoseconds> (timeEnd - timeStart).count();
            block->setInnerTime(outerTime);

            return status;
        }

        template <typename T>
        ResultSet<T>* DeclarableListOp<T>::execute(NDArrayList<T>* list, std::vector<NDArray<T>*>& inputs, std::vector<T>& tArgs, std::vector<int>& iArgs) {
            VariableSpace<T> varSpace;
            int nodeId = 119;

            // should be never used in practice, since in-graph NDArrayList should have id set
            int cnt = -1;
            std::vector<int> in;
            if (list != nullptr) {
                if (list->id().first == 0)
                    list->id().first = -1;

                auto listVar = new Variable<T>(nullptr, nullptr, -119, 0);
                listVar->setNDArrayList(list);
                varSpace.putVariable(-1, listVar);
                in.push_back(-1);
                cnt--;
            }


            for (auto v: inputs) {
                auto var = new Variable<T>(v);
                var->markRemovable(false);
                in.push_back(cnt);
                varSpace.putVariable(cnt--, var);
            }

            Context<T> block(1, &varSpace, false);
            block.fillInputs(in);

            for (int e = 0; e < tArgs.size(); e++)
                block.getTArguments()->emplace_back(tArgs.at(e));


            for (int e = 0; e < iArgs.size(); e++)
                block.getIArguments()->emplace_back(iArgs.at(e));


            Nd4jStatus result = this->validateAndExecute(block);
            auto res = new ResultSet<T>();
            res->setStatus(result);

            for (int e = 0; e < 65536; e++) {
                std::pair<int,int> pair(1, e);
                if (varSpace.hasVariable(pair)) {
                    auto var = varSpace.getVariable(pair);
                    if (var->getNDArray() != nullptr) {
                        var->markRemovable(false);
                        res->push_back(var->getNDArray());
                    }
                } else
                    break;
            }

            return res;
        }

        template class ND4J_EXPORT DeclarableListOp<float>;
        template class ND4J_EXPORT DeclarableListOp<float16>;
        template class ND4J_EXPORT DeclarableListOp<double>;
    }
}