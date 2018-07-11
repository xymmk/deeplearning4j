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
// @author Yurii Shyrma (iuriish@yahoo.com), created on 10.06.2018
//


#include "testlayers.h"
#include <ops/declarable/CustomOperations.h>
#include <NDArray.h>
// #include <array/NDArrayList.h>

using namespace nd4j;


class DeclarableOpsTests8 : public testing::Test {
public:

    DeclarableOpsTests8() {
        printf("\n");
        fflush(stdout);
    }
};


////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, reduceVariance_test1) {

    NDArray<float> x('c', {2,3,4}, {27.f,34.f,5.f,4.f,54.f,6.f,65.f,8.f,37.f,45.f,8.f,67.f,96.f,10.f,65.f,41.f,33.f,85.f,92.f,24.f,25.f,55.f,49.f,76.f});
    NDArray<float> exp('c', {4}, {602.2222f, 727.13885f, 993.5555f, 755.8889f});
        
    nd4j::ops::reduce_variance<float> op;
    auto result = op.execute({&x}, {}, {0,1});
    auto output = result->at(0);    

    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, reduceVariance_test2) {

    NDArray<float> x('c', {2,3,4}, {27.f,34.f,5.f,4.f,54.f,6.f,65.f,8.f,37.f,45.f,8.f,67.f,96.f,10.f,65.f,41.f,33.f,85.f,92.f,24.f,25.f,55.f,49.f,76.f});
    NDArray<float> exp('c', {1,1,4}, {602.2222f, 727.13885f, 993.5555f, 755.8889f});
    
    nd4j::ops::reduce_variance<float> op;
    auto result = op.execute({&x}, {1.}, {0,1});
    auto output = result->at(0);    

    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, reduceVariance_test3) {

    NDArray<float> x('c', {2,3,4}, {27.f,34.f,5.f,4.f,54.f,6.f,65.f,8.f,37.f,45.f,8.f,67.f,96.f,10.f,65.f,41.f,33.f,85.f,92.f,24.f,25.f,55.f,49.f,76.f});
    NDArray<float> exp('c', {3}, {900.9375f, 969.8594f, 424.1875f});
        
    nd4j::ops::reduce_variance<float> op;
    auto result = op.execute({&x}, {}, {0,2});
    auto output = result->at(0);    

    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, reduceVariance_test4) {

    NDArray<float> x('c', {2,3,4}, {27.f,34.f,5.f,4.f,54.f,6.f,65.f,8.f,37.f,45.f,8.f,67.f,96.f,10.f,65.f,41.f,33.f,85.f,92.f,24.f,25.f,55.f,49.f,76.f});
    NDArray<float> exp('c', {1,3,1}, {900.9375f, 969.8594f, 424.1875f});  
        
    nd4j::ops::reduce_variance<float> op;
    auto result = op.execute({&x}, {1.}, {0,2});
    auto output = result->at(0);    

    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, reduceVariance_test5) {

    NDArray<float> x('c', {2,3,4}, {27.f,34.f,5.f,4.f,54.f,6.f,65.f,8.f,37.f,45.f,8.f,67.f,96.f,10.f,65.f,41.f,33.f,85.f,92.f,24.f,25.f,55.f,49.f,76.f});
    NDArray<float> exp(788.6927f);
        
    nd4j::ops::reduce_variance<float> op;
    auto result = op.execute({&x}, {}, {});
    auto output = result->at(0);    

    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, reduceVariance_test6) {

    NDArray<float> x('c', {2,3,4}, {27.f,34.f,5.f,4.f,54.f,6.f,65.f,8.f,37.f,45.f,8.f,67.f,96.f,10.f,65.f,41.f,33.f,85.f,92.f,24.f,25.f,55.f,49.f,76.});
    NDArray<float> exp(788.6927f);
           
    nd4j::ops::reduce_variance<float> op;
    auto result = op.execute({&x}, {}, {0,1,2});
    auto output = result->at(0);    

    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, reduceVariance_test7) {

    NDArray<float> x('c', {2,3,4}, {27.f,34.f,5.f,4.f,54.f,6.f,65.f,8.f,37.f,45.f,8.f,67.f,96.f,10.f,65.f,41.f,33.f,85.f,92.f,24.f,25.f,55.f,49.f,76.});
    NDArray<float> exp('c', {1,1,1}, {788.6927f});
           
    nd4j::ops::reduce_variance<float> op;
    auto result = op.execute({&x}, {1.}, {0,1,2});
    auto output = result->at(0);    

    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, reduceStDev_test1) {

    NDArray<float> x('c', {2,3,4}, {27.f,34.f,5.f,4.f,54.f,6.f,65.f,8.f,37.f,45.f,8.f,67.f,96.f,10.f,65.f,41.f,33.f,85.f,92.f,24.f,25.f,55.f,49.f,76.});
    NDArray<float> exp('c', {4}, {24.54022f, 26.96551f, 31.52072f, 27.49343f});
        
    nd4j::ops::reduce_stdev<float> op;
    auto result = op.execute({&x}, {}, {0,1});
    auto output = result->at(0);    

    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, reduceStDev_test2) {

    NDArray<float> x('c', {2,3,4}, {27.f,34.f,5.f,4.f,54.f,6.f,65.f,8.f,37.f,45.f,8.f,67.f,96.f,10.f,65.f,41.f,33.f,85.f,92.f,24.f,25.f,55.f,49.f,76.});
    NDArray<float> exp('c', {1,1,4}, {24.54022f, 26.96551f, 31.52072f, 27.49343f});
    
    nd4j::ops::reduce_stdev<float> op;
    auto result = op.execute({&x}, {1.}, {0,1});
    auto output = result->at(0);    

    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, reduceStDev_test3) {

    NDArray<float> x('c', {2,3,4}, {27.f,34.f,5.f,4.f,54.f,6.f,65.f,8.f,37.f,45.f,8.f,67.f,96.f,10.f,65.f,41.f,33.f,85.f,92.f,24.f,25.f,55.f,49.f,76.});
    NDArray<float> exp('c', {3}, {30.01562f, 31.14257f, 20.59581f});
        
    nd4j::ops::reduce_stdev<float> op;
    auto result = op.execute({&x}, {}, {0,2});
    auto output = result->at(0);    

    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, reduceStDev_test4) {

    NDArray<float> x('c', {2,3,4}, {27.f,34.f,5.f,4.f,54.f,6.f,65.f,8.f,37.f,45.f,8.f,67.f,96.f,10.f,65.f,41.f,33.f,85.f,92.f,24.f,25.f,55.f,49.f,76.});
    NDArray<float> exp('c', {1,3,1}, {30.01562f, 31.14257f, 20.59581f});  
        
    nd4j::ops::reduce_stdev<float> op;
    auto result = op.execute({&x}, {1.}, {0,2});
    auto output = result->at(0);    

    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, reduceStDev_test5) {

    NDArray<float> x('c', {2,3,4}, {27.f,34.f,5.f,4.f,54.f,6.f,65.f,8.f,37.f,45.f,8.f,67.f,96.f,10.f,65.f,41.f,33.f,85.f,92.f,24.f,25.f,55.f,49.f,76.});
    NDArray<float> exp(28.08367f);
        
    nd4j::ops::reduce_stdev<float> op;
    auto result = op.execute({&x}, {}, {});
    auto output = result->at(0);    

    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, reduceStDev_test6) {

    NDArray<float> x('c', {2,3,4}, {27.f,34.f,5.f,4.f,54.f,6.f,65.f,8.f,37.f,45.f,8.f,67.f,96.f,10.f,65.f,41.f,33.f,85.f,92.f,24.f,25.f,55.f,49.f,76.});
    NDArray<float> exp(28.08367f);
           
    nd4j::ops::reduce_stdev<float> op;
    auto result = op.execute({&x}, {}, {0,1,2});
    auto output = result->at(0);    

    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, reduceStDev_test7) {

    NDArray<float> x('c', {2,3,4}, {27.f,34.f,5.f,4.f,54.f,6.f,65.f,8.f,37.f,45.f,8.f,67.f,96.f,10.f,65.f,41.f,33.f,85.f,92.f,24.f,25.f,55.f,49.f,76.});
    NDArray<float> exp('c', {1,1,1}, {28.08367f});
           
    nd4j::ops::reduce_stdev<float> op;
    auto result = op.execute({&x}, {1.f}, {0,1,2});
    auto output = result->at(0);    

    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, reduceStDev_test8) {

    NDArray<float> x('c', {2,3,4}, {27.f,34.f,5.f,4.f,54.f,6.f,65.f,8.f,37.f,45.f,8.f,67.f,96.f,10.f,65.f,41.f,33.f,85.f,92.f,24.f,25.f,55.f,49.f,76.});
    NDArray<float> exp('c', {4}, {26.88246f, 29.53924f, 34.52921f, 30.11755f});
        
    nd4j::ops::reduce_stdev<float> op;
    auto result = op.execute({&x}, {0.f,1.f}, {0,1});
    auto output = result->at(0);    

    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, reduceVarianceBP_test1) {

    NDArray<float> x('c', {3,4});
    NDArray<float> gradO1('c', {1,1}, {0.5f});
    NDArray<float> gradO2(0.5f);
    NDArray<float> exp12('c', {3,4}, {-0.5f, -0.4090909f, -0.3181818f, -0.22727273f, -0.13636364f, -0.045454547f, 0.045454547f, 0.13636364f, 0.22727273f, 0.3181818f, 0.4090909f, 0.5f});
    NDArray<float> exp34('c', {3,4}, {-0.45833334f, -0.375f, -0.29166666f, -0.20833333f, -0.125f, -0.041666668f, 0.041666668f, 0.125f, 0.20833333f, 0.29166666f, 0.375f, 0.45833334f});

    x.linspace(1);
            
    nd4j::ops::reduce_variance_bp<float> op;

    auto result = op.execute({&x, &gradO2}, {0,1}, {});
    ASSERT_EQ(ND4J_STATUS_OK, result->status());    
    auto output = result->at(0);
    ASSERT_TRUE(exp12.isSameShape(output));
    ASSERT_TRUE(exp12.equalsTo(output));
    delete result;

    result = op.execute({&x, &gradO1}, {1,1}, {});
    ASSERT_EQ(ND4J_STATUS_OK, result->status());    
    output = result->at(0);
    ASSERT_TRUE(exp12.isSameShape(output));
    ASSERT_TRUE(exp12.equalsTo(output));
    delete result;    

    result = op.execute({&x, &gradO2}, {0,0}, {});
    ASSERT_EQ(ND4J_STATUS_OK, result->status());    
    output = result->at(0);
    ASSERT_TRUE(exp34.isSameShape(output));
    ASSERT_TRUE(exp34.equalsTo(output));
    delete result;    

    result = op.execute({&x, &gradO1}, {1,0}, {});
    ASSERT_EQ(ND4J_STATUS_OK, result->status());    
    output = result->at(0);
    ASSERT_TRUE(exp34.isSameShape(output));
    ASSERT_TRUE(exp34.equalsTo(output));
    delete result;   

}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, reduceVarianceBP_test2) {

    NDArray<float> x('c', {3,4});
    NDArray<float> gradO1('c', {1,4}, {1.f,2.f,3.f,4.f});
    NDArray<float> gradO2('c', {4}, {1.f,2.f,3.f,4.f});
    NDArray<float> exp12('c', {3,4}, {-2.666667f, -5.333333f, -8.000000f,  -10.666667f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 2.666667f, 5.333333f,  8.000000f, 10.666667f});
    NDArray<float> exp34('c', {3,4}, {-4.000000f, -8.000000f, -12.000000f, -16.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 4.000000f, 8.000000f, 12.000000f, 16.000000f});

    x.linspace(1);
            
    nd4j::ops::reduce_variance_bp<float> op;

    auto result = op.execute({&x, &gradO2}, {0,0}, {0});
    ASSERT_EQ(ND4J_STATUS_OK, result->status());    
    auto output = result->at(0);    
    ASSERT_TRUE(exp12.isSameShape(output));
    ASSERT_TRUE(exp12.equalsTo(output));
    delete result;

    result = op.execute({&x, &gradO1}, {1,0}, {0});
    ASSERT_EQ(ND4J_STATUS_OK, result->status());    
    output = result->at(0);        
    ASSERT_TRUE(exp12.isSameShape(output));
    ASSERT_TRUE(exp12.equalsTo(output)); 
    delete result;    

    result = op.execute({&x, &gradO2}, {0,1}, {0});
    ASSERT_EQ(ND4J_STATUS_OK, result->status());    
    output = result->at(0);    
    ASSERT_TRUE(exp34.isSameShape(output));
    ASSERT_TRUE(exp34.equalsTo(output));
    delete result;    

    result = op.execute({&x, &gradO1}, {1,1}, {0});
    ASSERT_EQ(ND4J_STATUS_OK, result->status());    
    output = result->at(0);
    ASSERT_TRUE(exp34.isSameShape(output));
    ASSERT_TRUE(exp34.equalsTo(output));
    delete result;   

}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, reduceVarianceBP_test3) {

    NDArray<float> x('c', {3,4});
    NDArray<float> gradO1('c', {3,1}, {1.f,2.f,3.f});
    NDArray<float> gradO2('c', {3}, {1.f,2.f,3.f});
    NDArray<float> exp12('c', {3,4}, {-0.750000f, -0.250000f, 0.250000f, 0.750000f, -1.500000f, -0.500000f, 0.500000f, 1.500000f, -2.250000f, -0.750000f, 0.750000f, 2.250000f});
    NDArray<float> exp34('c', {3,4}, {-1.000000f, -0.333333f, 0.333333f, 1.000000f, -2.000000f, -0.666667f, 0.666667f, 2.000000f, -3.000000f, -1.000000f, 1.000000f, 3.000000f});

    x.linspace(1);
            
    nd4j::ops::reduce_variance_bp<float> op;

    auto result = op.execute({&x, &gradO2}, {0,0}, {1});
    ASSERT_EQ(ND4J_STATUS_OK, result->status());    
    auto output = result->at(0);    
    ASSERT_TRUE(exp12.isSameShape(output));
    ASSERT_TRUE(exp12.equalsTo(output));
    delete result;

    result = op.execute({&x, &gradO1}, {1,0}, {1});
    ASSERT_EQ(ND4J_STATUS_OK, result->status());    
    output = result->at(0);        
    ASSERT_TRUE(exp12.isSameShape(output));
    ASSERT_TRUE(exp12.equalsTo(output)); 
    delete result;    

    result = op.execute({&x, &gradO2}, {0,1}, {1});
    ASSERT_EQ(ND4J_STATUS_OK, result->status());    
    output = result->at(0);    
    ASSERT_TRUE(exp34.isSameShape(output));
    ASSERT_TRUE(exp34.equalsTo(output));
    delete result;    

    result = op.execute({&x, &gradO1}, {1,1}, {1});
    ASSERT_EQ(ND4J_STATUS_OK, result->status());    
    output = result->at(0);
    ASSERT_TRUE(exp34.isSameShape(output));
    ASSERT_TRUE(exp34.equalsTo(output));
    delete result;   

}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, reduceStDevBP_test1) {

    NDArray<float> x('c', {3,4});
    NDArray<float> gradO1('c', {1,1}, {0.5f});
    NDArray<float> gradO2(0.5f);
    NDArray<float> exp12('c', {3,4}, {-0.069337524f, -0.056730703f, -0.04412388f, -0.031517055f, -0.018910235f, -0.0063034114f, 0.0063034114f, 0.018910235f, 0.031517055f, 0.04412388f, 0.056730703f, 0.069337524f});     
    NDArray<float> exp34('c', {3,4}, {-0.06638563f, -0.05431551f, -0.0422454f, -0.030175284f, -0.01810517f, -0.006035057f, 0.006035057f, 0.01810517f, 0.030175284f, 0.0422454f, 0.05431551f, 0.06638563f});

    x.linspace(1);
            
    nd4j::ops::reduce_stdev_bp<float> op;

    auto result = op.execute({&x, &gradO2}, {0,1}, {});
    ASSERT_EQ(ND4J_STATUS_OK, result->status());    
    auto output = result->at(0);
    // output->printIndexedBuffer();
    ASSERT_TRUE(exp12.isSameShape(output));
    ASSERT_TRUE(exp12.equalsTo(output));
    delete result;

    result = op.execute({&x, &gradO1}, {1,1}, {});
    ASSERT_EQ(ND4J_STATUS_OK, result->status());    
    output = result->at(0);
    ASSERT_TRUE(exp12.isSameShape(output));
    ASSERT_TRUE(exp12.equalsTo(output));
    delete result;

    result = op.execute({&x, &gradO2}, {0,0}, {});
    ASSERT_EQ(ND4J_STATUS_OK, result->status());    
    output = result->at(0);
    ASSERT_TRUE(exp34.isSameShape(output));
    ASSERT_TRUE(exp34.equalsTo(output));
    delete result;

    result = op.execute({&x, &gradO1}, {1,0}, {});
    ASSERT_EQ(ND4J_STATUS_OK, result->status());    
    output = result->at(0);
    ASSERT_TRUE(exp34.isSameShape(output));
    ASSERT_TRUE(exp34.equalsTo(output));
    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, reduceStDevBP_test2) {

    NDArray<float> x('c', {3,4});
    NDArray<float> gradO1('c', {1,4}, {1.f,2.f,3.f,4.f});
    NDArray<float> gradO2('c', {4}, {1.f,2.f,3.f,4.f});
    NDArray<float> exp12('c', {3,4}, {-0.4082483f, -0.8164966f, -1.2247449f, -1.6329932f, 0.0, 0.0, 0.0, 0.0, 0.4082483f, 0.8164966f, 1.2247449f, 1.6329932f});
    NDArray<float> exp34('c', {3,4}, {-0.5f, -1.0f, -1.5f, -2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 1.0f, 1.5f, 2.0f});

    x.linspace(1);
            
    nd4j::ops::reduce_stdev_bp<float> op;

    auto result = op.execute({&x, &gradO2}, {0,0}, {0});
    ASSERT_EQ(ND4J_STATUS_OK, result->status());    
    auto output = result->at(0);        
    ASSERT_TRUE(exp12.isSameShape(output));
    ASSERT_TRUE(exp12.equalsTo(output));
    delete result;

    result = op.execute({&x, &gradO1}, {1,0}, {0});
    ASSERT_EQ(ND4J_STATUS_OK, result->status());    
    output = result->at(0);        
    ASSERT_TRUE(exp12.isSameShape(output));
    ASSERT_TRUE(exp12.equalsTo(output)); 
    delete result;    

    result = op.execute({&x, &gradO2}, {0,1}, {0});
    ASSERT_EQ(ND4J_STATUS_OK, result->status());    
    output = result->at(0);    
    ASSERT_TRUE(exp34.isSameShape(output));
    ASSERT_TRUE(exp34.equalsTo(output));
    delete result;    

    result = op.execute({&x, &gradO1}, {1,1}, {0});
    ASSERT_EQ(ND4J_STATUS_OK, result->status());    
    output = result->at(0);
    ASSERT_TRUE(exp34.isSameShape(output));
    ASSERT_TRUE(exp34.equalsTo(output));
    delete result;   
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, reduceStDevBP_test3) {

    NDArray<float> x('c', {3,4});
    NDArray<float> gradO1('c', {3,1}, {1.f,2.f,3.f});
    NDArray<float> gradO2('c', {3}, {1.f,2.f,3.f});
    NDArray<float> exp12('c', {3,4}, {-0.3354102f, -0.1118034f, 0.1118034f, 0.3354102f, -0.6708204f, -0.2236068f, 0.2236068f, 0.6708204f, -1.0062306f, -0.3354102f, 0.3354102f, 1.0062306f});
    NDArray<float> exp34('c', {3,4}, {-0.38729835f, -0.12909944f, 0.12909944f, 0.38729835f, -0.7745967f, -0.2581989f, 0.2581989f, 0.7745967f, -1.161895f, -0.38729835f, 0.38729835f, 1.161895f});

    x.linspace(1);
            
    nd4j::ops::reduce_stdev_bp<float> op;

    auto result = op.execute({&x, &gradO2}, {0,0}, {1});
    ASSERT_EQ(ND4J_STATUS_OK, result->status());    
    auto output = result->at(0);    
    ASSERT_TRUE(exp12.isSameShape(output));
    ASSERT_TRUE(exp12.equalsTo(output));
    delete result;

    result = op.execute({&x, &gradO1}, {1,0}, {1});
    ASSERT_EQ(ND4J_STATUS_OK, result->status());    
    output = result->at(0);        
    ASSERT_TRUE(exp12.isSameShape(output));
    ASSERT_TRUE(exp12.equalsTo(output)); 
    delete result;    

    result = op.execute({&x, &gradO2}, {0,1}, {1});
    ASSERT_EQ(ND4J_STATUS_OK, result->status());    
    output = result->at(0);    
    ASSERT_TRUE(exp34.isSameShape(output));
    ASSERT_TRUE(exp34.equalsTo(output));
    delete result;    

    result = op.execute({&x, &gradO1}, {1,1}, {1});
    ASSERT_EQ(ND4J_STATUS_OK, result->status());    
    output = result->at(0);
    ASSERT_TRUE(exp34.isSameShape(output));
    ASSERT_TRUE(exp34.equalsTo(output));
    delete result;   

}


////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Reduce_Sum_1) {
    
    NDArray<float> input('c', {3, 5},   {1., 2., 3., 4., 5., 6., 7., 8., 9., 10., 11., 12., 13., 14., 15.});    
    NDArray<float> exp(120.f);
    //************************************//

    nd4j::ops::reduce_sum<float> op;
    auto result = op.execute({&input}, {}, {});

    ASSERT_EQ(Status::OK(), result->status());
    auto z = result->at(0);    
    //z->printIndexedBuffer("Result is ");
    ASSERT_TRUE(exp.equalsTo(z));
    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Reduce_Sum_2) {
    
    NDArray<float> input('c', {3, 5},   {1., 2., 3., 4., 5., 6., 7., 8., 9., 10., 11., 12., 13., 14., 15.});    
    NDArray<float> exp({15.f, 40.f, 65.f});
    //************************************//

    nd4j::ops::reduce_sum<float> op;
    auto result = op.execute({&input}, {}, {1});

    ASSERT_EQ(Status::OK(), result->status());
    auto z = result->at(0);    
//    z->printIndexedBuffer("Result is ");
    ASSERT_TRUE(exp.equalsTo(z));
    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Reduce_Prod_1) {
    
    NDArray<float> input('c', {3, 5},   {1., 2., 3., 4., 5., 6., 7., 8., 9., 10., 11., 12., 13., 14., 15.});    
    NDArray<float> exp(1307674368000.f);
    //************************************//

    nd4j::ops::reduce_prod<float> op;
    auto result = op.execute({&input}, {}, {});

    ASSERT_EQ(Status::OK(), result->status());
    auto z = result->at(0);    
    //z->printIndexedBuffer("Result is ");
    ASSERT_TRUE(exp.equalsTo(z));
    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Reduce_Prod_2) {
    
    NDArray<float> input('c', {3, 5},   {1., 2., 3., 4., 5., 6., 7., 8., 9., 10., 11., 12., 13., 14., 15.});    
    NDArray<float> exp({120.f, 30240.f, 360360.f});
    //************************************//

    nd4j::ops::reduce_prod<float> op;
    auto result = op.execute({&input}, {}, {1});

    ASSERT_EQ(Status::OK(), result->status());
    auto z = result->at(0);    
//    z->printIndexedBuffer("Result is ");
    ASSERT_TRUE(exp.equalsTo(z));
    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Reduce_Sum_01) {

    NDArray<float> x('c', {2,3,4});
    NDArray<float> exp('c', {4}, {66.f, 72.f, 78.f, 84.f});
    x.linspace(1);

    nd4j::ops::reduce_sum<float> op;
    auto result = op.execute({&x}, {}, {0,1});
    auto output = result->at(0);    
//    output->printIndexedBuffer("Result is");
    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Reduce_Sum_02) {

    NDArray<float> x('c', {2,3,4});
    NDArray<float> exp('c', {1,1,4}, {66.f, 72.f, 78.f, 84.f});
    x.linspace(1);

    nd4j::ops::reduce_sum<float> op;
    auto result = op.execute({&x}, {1.}, {0, 1});
    auto output = result->at(0);    
//    output->printIndexedBuffer("Result is");

    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Reduce_Sum_3) {

    NDArray<float> x('c', {2,3,4});
    NDArray<float> exp('c', {3}, {68.f, 100.f, 132.f});
    x.linspace(1);

    nd4j::ops::reduce_sum<float> op;
    auto result = op.execute({&x}, {}, {0, 2});
    auto output = result->at(0);    
//    output->printIndexedBuffer("Result is");

    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Reduce_Sum_4) {

    NDArray<float> x('c', {2,3,4});
    NDArray<float> exp('c', {1,3,1}, {68.f, 100.f, 132.f});
    x.linspace(1);

    nd4j::ops::reduce_sum<float> op;
    auto result = op.execute({&x}, {1.}, {0, 2});
    auto output = result->at(0);    
//    output->printIndexedBuffer("Result is");

    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Reduce_Sum_5) {

    NDArray<float> x('c', {2,3,4});
    NDArray<float> exp(300.f);
    x.linspace(1);

    nd4j::ops::reduce_sum<float> op;
    auto result = op.execute({&x}, {}, {});
    auto output = result->at(0);    
//    output->printIndexedBuffer("Result is");

    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Reduce_Sum_6) {

    NDArray<float> x('c', {2,3,4});
    NDArray<float> exp(300.f);
    x.linspace(1);
           
    nd4j::ops::reduce_sum<float> op;
    auto result = op.execute({&x}, {}, {0,1,2});
    auto output = result->at(0);    
//    output->printIndexedBuffer("Result is");

    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Reduce_Sum_7) {

    NDArray<float> x('c', {2,3,4});
    NDArray<float> exp('c', {1,1,1}, {300.f});
    x.linspace(1);
//    x.printIndexedBuffer("Input with shape (2, 3, 4) is");       
    nd4j::ops::reduce_sum<float> op;
    auto result = op.execute({&x}, {1.}, {0,1,2});
    auto output = result->at(0);    
//    output->printIndexedBuffer("Result is");

    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Reduce_Prod_01) {

    NDArray<float> x('c', {2,3,2});
    NDArray<float> exp('c', {2}, {10395.f, 46080.f});
    x.linspace(1);

    nd4j::ops::reduce_prod<float> op;
    auto result = op.execute({&x}, {}, {0,1});
    auto output = result->at(0);    
//    output->printIndexedBuffer("Result is");
    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Reduce_Prod_02) {

    NDArray<float> x('c', {2,3,2});
    NDArray<float> exp('c', {1,1,2}, {10395.f, 46080.f});
    x.linspace(1);

    nd4j::ops::reduce_prod<float> op;
    auto result = op.execute({&x}, {1.}, {0, 1});
    auto output = result->at(0);    
//    output->printIndexedBuffer("Result is");

    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Reduce_Prod_3) {

    NDArray<float> x('c', {2,3,2});
    NDArray<float> exp('c', {3}, {112.f, 1080.f, 3960.f});
    x.linspace(1);

    nd4j::ops::reduce_prod<float> op;
    auto result = op.execute({&x}, {}, {0, 2});
    auto output = result->at(0);    
//    output->printIndexedBuffer("Result is");

    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Reduce_Prod_4) {

    NDArray<float> x('c', {2,3,2});
    NDArray<float> exp('c', {1,3,1}, {112.f, 1080.f, 3960.f});
    x.linspace(1);

    nd4j::ops::reduce_prod<float> op;
    auto result = op.execute({&x}, {1.}, {0, 2});
    auto output = result->at(0);    
//    output->printIndexedBuffer("Result is");

    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Reduce_Prod_5) {

    NDArray<float> x('c', {2,3,2});
    NDArray<float> exp(479001600.f);
    x.linspace(1);
    
    nd4j::ops::reduce_prod<float> op;
    auto result = op.execute({&x}, {}, {});
    auto output = result->at(0);    
//    output->printIndexedBuffer("Result is");

    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Reduce_Prod_6) {

    NDArray<float> x('c', {2,3,2});
    NDArray<float> exp(479001600.f);
    x.linspace(1);
           
    nd4j::ops::reduce_prod<float> op;
    auto result = op.execute({&x}, {}, {0,1,2});
    auto output = result->at(0);    
//    output->printIndexedBuffer("Result is");

    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Reduce_Prod_7) {

    NDArray<float> x('c', {2,3,2});
    NDArray<float> exp('c', {1, 1, 1}, {479001600.f});
    x.linspace(1);
//    x.printIndexedBuffer("Input with shape (2, 3, 4) is");       
    nd4j::ops::reduce_prod<float> op;
    auto result = op.execute({&x}, {1.}, {0,1,2});
    auto output = result->at(0);    
//    output->printIndexedBuffer("Result is");

    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Reduce_Min_1) {

    NDArray<float> x('c', {2, 3, 4});
    NDArray<float> exp('c', {4}, {1.f, 2.f, 3.f, 4.f});
    x.linspace(1);

    nd4j::ops::reduce_min<float> op;
    auto result = op.execute({&x}, {}, {0, 1});
    auto output = result->at(0);    
    // output->printIndexedBuffer("Result is");
    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Reduce_Min_2) {

    NDArray<float> x('c', {2, 3, 4});
    NDArray<float> exp('c', {1,1,4}, {1.f, 2.f, 3.f, 4.f});
    x.linspace(1);

    nd4j::ops::reduce_min<float> op;
    auto result = op.execute({&x}, {1.}, {0, 1});
    auto output = result->at(0);    
    // output->printIndexedBuffer("Result is");

    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Reduce_Min_3) {

    NDArray<float> x('c', {2, 3, 4});
    NDArray<float> exp('c', {3}, {1.f, 5.f, 9.f});
    x.linspace(1);

    nd4j::ops::reduce_min<float> op;
    auto result = op.execute({&x}, {}, {0, 2});
    auto output = result->at(0);    
    // output->printIndexedBuffer("Result is");

    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Reduce_Min_4) {

    NDArray<float> x('c', {2, 3, 4});
    NDArray<float> exp('c', {1,3,1}, {1.f, 5.f, 9.f});
    x.linspace(1);

    nd4j::ops::reduce_min<float> op;
    auto result = op.execute({&x}, {1.}, {0, 2});
    auto output = result->at(0);    
    // output->printIndexedBuffer("Result is");

    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Reduce_Min_5) {

    NDArray<float> x('c', {2, 3, 4});
    NDArray<float> exp(1.f);
    x.linspace(1);
    
    nd4j::ops::reduce_min<float> op;
    auto result = op.execute({&x}, {}, {});
    auto output = result->at(0);    
//    output->printIndexedBuffer("Result is");

    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Reduce_Min_6) {

    NDArray<float> x('c', {2, 3, 4});
    NDArray<float> exp(1.f);
    x.linspace(1);
           
    nd4j::ops::reduce_min<float> op;
    auto result = op.execute({&x}, {}, {0,1,2});
    auto output = result->at(0);    
//    output->printIndexedBuffer("Result is");

    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Reduce_Min_7) {

    NDArray<float> x('c', {2, 3, 4});
    NDArray<float> exp('c', {1, 1, 1}, {1.f});
    x.linspace(1);
    // x.printIndexedBuffer("Input with shape (2, 3, 4) is");       
    nd4j::ops::reduce_min<float> op;
    auto result = op.execute({&x}, {1.}, {0,1,2});
    auto output = result->at(0);    
//    output->printIndexedBuffer("Result is");

    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Reduce_Max_1) {

    NDArray<float> x('c', {2, 3, 4});
    NDArray<float> exp('c', {4}, {21.f, 22.f, 23.f, 24.f});
    x.linspace(1);

    nd4j::ops::reduce_max<float> op;
    auto result = op.execute({&x}, {}, {0,1});
    auto output = result->at(0);    
    // output->printIndexedBuffer("Result is");
    // output->printShapeInfo("Output shape");
    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Reduce_Max_2) {

    NDArray<float> x('c', {2,3,4});
    NDArray<float> exp('c', {1,1,4}, {21.f, 22.f, 23.f, 24.f});
    x.linspace(1);

    nd4j::ops::reduce_max<float> op;
    auto result = op.execute({&x}, {1.}, {0, 1});
    auto output = result->at(0);    
    // output->printIndexedBuffer("Result is");

    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Reduce_Max_3) {

    NDArray<float> x('c', {2, 3, 4});
    NDArray<float> exp('c', {3}, {16.f, 20.f, 24.f});
    x.linspace(1);

    nd4j::ops::reduce_max<float> op;
    auto result = op.execute({&x}, {}, {0, 2});
    auto output = result->at(0);    
    // output->printIndexedBuffer("Result is");

    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Reduce_Max_4) {

    NDArray<float> x('c', {2, 3, 4});
    NDArray<float> exp('c', {1,3,1}, {16.f, 20.f, 24.f});
    x.linspace(1);

    nd4j::ops::reduce_max<float> op;
    auto result = op.execute({&x}, {1.}, {0, 2});
    auto output = result->at(0);    
    // output->printIndexedBuffer("Result is");

    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Reduce_Max_5) {

    NDArray<float> x('c', {2, 3, 4});
    NDArray<float> exp(24.f);
    x.linspace(1);
    
    nd4j::ops::reduce_max<float> op;
    auto result = op.execute({&x}, {}, {});
    auto output = result->at(0);    
    // output->printIndexedBuffer("Result is");

    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Reduce_Max_6) {

    NDArray<float> x('c', {2, 3, 4});
    NDArray<float> exp(24.f);
    x.linspace(1);
           
    nd4j::ops::reduce_max<float> op;
    auto result = op.execute({&x}, {}, {0,1,2});
    auto output = result->at(0);    
    // output->printIndexedBuffer("Result is");

    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Reduce_Max_7) {

	NDArray<float> x('c', {2, 3, 4});
    NDArray<float> exp('c', {1, 1, 1}, {24.f});
    x.linspace(1);
//    x.printIndexedBuffer("Input with shape (2, 3, 4) is");       
    nd4j::ops::reduce_max<float> op;
    auto result = op.execute({&x}, {1.}, {0,1,2});
    auto output = result->at(0);    
    // output->printIndexedBuffer("Result is");

    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

TEST_F(DeclarableOpsTests8, Test_Reduce_Norm1_1) {

    NDArray<float> x('c', {2, 3, 4});
    NDArray<float> exp('c', {4}, {66.f, 72.f, 78.f, 84.f});
    x.linspace(1);

    nd4j::ops::reduce_norm1<float> op;
    auto result = op.execute({&x}, {}, {0,1});
    auto output = result->at(0);
//    output->printIndexedBuffer("Result is");
    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Reduce_Norm1_2) {

    NDArray<float> x('c', {2,3,4});
    NDArray<float> exp('c', {1,1,4}, {66.f, 72.f, 78.f, 84.f});
    x.linspace(1);

    nd4j::ops::reduce_norm1<float> op;
    auto result = op.execute({&x}, {1.}, {0, 1});
    auto output = result->at(0);    
//    output->printIndexedBuffer("Result is");

    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Reduce_Norm1_3) {

    NDArray<float> x('c', {2, 3, 4});
    NDArray<float> exp('c', {3}, {68.f, 100.f, 132.f});
    x.linspace(1);

    nd4j::ops::reduce_norm1<float> op;
    auto result = op.execute({&x}, {}, {0, 2});
    auto output = result->at(0);    
//    output->printIndexedBuffer("Result is");

    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Reduce_Norm1_4) {

    NDArray<float> x('c', {2, 3, 4});
    NDArray<float> exp('c', {1,3,1}, {68.f, 100.f, 132.f});
    x.linspace(1);

    nd4j::ops::reduce_norm1<float> op;
    auto result = op.execute({&x}, {1.}, {0, 2});
    auto output = result->at(0);    
//    output->printIndexedBuffer("Result is");

    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Reduce_Norm1_5) {

    NDArray<float> x('c', {2, 3, 4});
    NDArray<float> exp(300.f);
    x.linspace(1);
    
    nd4j::ops::reduce_norm1<float> op;
    auto result = op.execute({&x}, {}, {});
    auto output = result->at(0);    
//    output->printIndexedBuffer("Result is");

    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Reduce_Norm1_6) {

    NDArray<float> x('c', {2, 3, 4});
    NDArray<float> exp(300.f);
    x.linspace(1);
           
    nd4j::ops::reduce_norm1<float> op;
    auto result = op.execute({&x}, {}, {0,1,2});
    auto output = result->at(0);    
//    output->printIndexedBuffer("Result is");

    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Reduce_Norm1_7) {

    NDArray<float> x('c', {2, 3, 4});
    NDArray<float> exp('c', {1, 1, 1}, {300.f});
    x.linspace(1);
//    x.printIndexedBuffer("Input with shape (2, 3, 4) is");       
    nd4j::ops::reduce_norm1<float> op;
    auto result = op.execute({&x}, {1.}, {0,1,2});
    auto output = result->at(0);    
//    output->printIndexedBuffer("Result is");

    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

TEST_F(DeclarableOpsTests8, Test_Reduce_Norm2_1) {

    NDArray<float> x('c', {2, 3, 4});
    NDArray<float> exp('c', {4}, {31.7175f, 33.823071f, 35.97221f, 38.15757f});
    x.linspace(1);

    nd4j::ops::reduce_norm2<float> op;
    auto result = op.execute({&x}, {}, {0,1});
    auto output = result->at(0);
//    output->printIndexedBuffer("Result is");
    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Reduce_Norm2_2) {

    NDArray<float> x('c', {2,3,4});
    NDArray<float> exp('c', {1,1,4}, {31.7175f, 33.823071f, 35.97221f, 38.15757f});
    x.linspace(1);

    nd4j::ops::reduce_norm2<float> op;
    auto result = op.execute({&x}, {1.}, {0, 1});
    auto output = result->at(0);    
//    output->printIndexedBuffer("Result is");

    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Reduce_Norm2_3) {

    NDArray<float> x('c', {2, 3, 4});
    NDArray<float> exp('c', {3}, {29.597298f, 39.344631f, 49.759422f});
    x.linspace(1);

    nd4j::ops::reduce_norm2<float> op;
    auto result = op.execute({&x}, {}, {0, 2});
    auto output = result->at(0);    
//    output->printIndexedBuffer("Result is");

    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Reduce_Norm2_4) {

    NDArray<float> x('c', {2, 3, 4});
    NDArray<float> exp('c', {1,3,1}, {29.597298f, 39.344631f, 49.759422f});
    x.linspace(1);

    nd4j::ops::reduce_norm2<float> op;
    auto result = op.execute({&x}, {1.}, {0, 2});
    auto output = result->at(0);    
//    output->printIndexedBuffer("Result is");

    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Reduce_Norm2_5) {

    NDArray<float> x('c', {2, 3, 4});
    NDArray<float> exp(70.f);
    x.linspace(1);
    
    nd4j::ops::reduce_norm2<float> op;
    auto result = op.execute({&x}, {}, {});
    auto output = result->at(0);    
//    output->printIndexedBuffer("Result is");

    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Reduce_Norm2_6) {

    NDArray<float> x('c', {2, 3, 4});
    NDArray<float> exp(70.f);
    x.linspace(1);
           
    nd4j::ops::reduce_norm2<float> op;
    auto result = op.execute({&x}, {}, {0,1,2});
    auto output = result->at(0);    
//    output->printIndexedBuffer("Result is");

    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Reduce_Norm2_7) {

    NDArray<float> x('c', {2, 3, 4});
    NDArray<float> exp('c', {1, 1, 1}, {70.f});
    x.linspace(1);
//    x.printIndexedBuffer("Input with shape (2, 3, 4) is");       
    nd4j::ops::reduce_norm2<float> op;
    auto result = op.execute({&x}, {1.}, {0,1,2});
    auto output = result->at(0);    
//    output->printIndexedBuffer("Result is");

    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Reduce_NormMax_1) {

    NDArray<float> x('c', {2, 3, 4});
    NDArray<float> exp('c', {4}, {21.f, 22.f, 23.f, 24.f});
    x.linspace(1);

    nd4j::ops::reduce_norm_max<float> op;
    auto result = op.execute({&x}, {}, {0,1});
    auto output = result->at(0);
//    output->printIndexedBuffer("Result is");
    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Reduce_NormMax_2) {

    NDArray<float> x('c', {2, 3, 4});
    NDArray<float> exp('c', {1,1,4}, {21.f, 22.f, 23.f, 24.f});
    x.linspace(1);

    nd4j::ops::reduce_norm_max<float> op;
    auto result = op.execute({&x}, {1.f}, {0,1});
    auto output = result->at(0);
//    output->printIndexedBuffer("Result is");
    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Reduce_NormMax_3) {

    NDArray<float> x('c', {2, 3, 4});
    NDArray<float> exp('c', {3}, {16.f, 20.f, 24.f});
    x.linspace(1);

    nd4j::ops::reduce_norm_max<float> op;
    auto result = op.execute({&x}, {}, {0,2});
    auto output = result->at(0);
//    output->printIndexedBuffer("Result is");
    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Reduce_NormMax_4) {

    NDArray<float> x('c', {2, 3, 4});
    NDArray<float> exp('c', {1, 3, 1}, {16.f, 20.f, 24.f});
    x.linspace(1);

    nd4j::ops::reduce_norm_max<float> op;
    auto result = op.execute({&x}, {1.f}, {0,2});
    auto output = result->at(0);
//    output->printIndexedBuffer("Result is");
    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Reduce_NormMax_5) {

    NDArray<float> x('c', {2, 3, 4});
    NDArray<float> exp(24.f);
    x.linspace(1);
    
    nd4j::ops::reduce_norm_max<float> op;
    auto result = op.execute({&x}, {}, {});
    auto output = result->at(0);    
//    output->printIndexedBuffer("Result is");

    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Reduce_NormMax_6) {

    NDArray<float> x('c', {2, 3, 4});
    NDArray<float> exp(24.f);
    x.linspace(1);
    
    nd4j::ops::reduce_norm_max<float> op;
    auto result = op.execute({&x}, {}, {0, 1, 2});
    auto output = result->at(0);    
//    output->printIndexedBuffer("Result is");

    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Reduce_NormMax_7) {

    NDArray<float> x('c', {2, 3, 4});
    NDArray<float> exp('c', {1, 1, 1}, {24.f});
    x.linspace(1);
    
    nd4j::ops::reduce_norm_max<float> op;
    auto result = op.execute({&x}, {1.f}, {});
    auto output = result->at(0);    
//    output->printIndexedBuffer("Result is");

    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Reduce_SquaredNorm_1) {

    NDArray<float> x('c', {2, 3, 4});
    NDArray<float> exp('c', {4}, {1006.f, 1144.f, 1294.f, 1456.f});
    x.linspace(1);

    nd4j::ops::reduce_sqnorm<float> op;
    auto result = op.execute({&x}, {}, {0,1});
    auto output = result->at(0);
//    output->printIndexedBuffer("Result is");
    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Reduce_SquaredNorm_2) {

    NDArray<float> x('c', {2, 3, 4});
    NDArray<float> exp('c', {1,1,4}, {1006.f, 1144.f, 1294.f, 1456.f});
    x.linspace(1);

    nd4j::ops::reduce_sqnorm<float> op;
    auto result = op.execute({&x}, {1.f}, {0,1});
    auto output = result->at(0);
//    output->printIndexedBuffer("Result is");
    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Reduce_SquaredNorm_3) {

    NDArray<float> x('c', {2, 3, 4});
    NDArray<float> exp('c', {3}, {876.f, 1548.f, 2476.f});
    x.linspace(1);

    nd4j::ops::reduce_sqnorm<float> op;
    auto result = op.execute({&x}, {}, {0,2});
    auto output = result->at(0);
//    output->printIndexedBuffer("Result is");
    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Reduce_SquaredNorm_4) {

    NDArray<float> x('c', {2, 3, 4});
    NDArray<float> exp('c', {1, 3, 1}, {876.f, 1548.f, 2476.f});
    x.linspace(1);

    nd4j::ops::reduce_sqnorm<float> op;
    auto result = op.execute({&x}, {1.f}, {0,2});
    auto output = result->at(0);
//    output->printIndexedBuffer("Result is");
    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Reduce_SquaredNorm_5) {

    NDArray<float> x('c', {2, 3, 4});
    NDArray<float> exp(4900.f);
    x.linspace(1);
    
    nd4j::ops::reduce_sqnorm<float> op;
    auto result = op.execute({&x}, {}, {});
    auto output = result->at(0);    
//    output->printIndexedBuffer("Result is");

    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Reduce_SquaredNorm_6) {

    NDArray<float> x('c', {2, 3, 4});
    NDArray<float> exp(4900.f);
    x.linspace(1);
    
    nd4j::ops::reduce_sqnorm<float> op;
    auto result = op.execute({&x}, {}, {0, 1, 2});
    auto output = result->at(0);    
//    output->printIndexedBuffer("Result is");

    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Reduce_SquaredNorm_7) {

    NDArray<float> x('c', {2, 3, 4});
    NDArray<float> exp('c', {1, 1, 1}, {4900.f});
    x.linspace(1);
    
    nd4j::ops::reduce_sqnorm<float> op;
    auto result = op.execute({&x}, {1.f}, {});
    auto output = result->at(0);    
//    output->printIndexedBuffer("Result is");

    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Reduce_Sum_BP_1) {
    
    NDArray<float> input('c', {3, 4},   {1., 2., 3., 4., 5., 6., 7., 8., 9., 10., 11., 12.});    
    NDArray<float> eps(0.5f);
    NDArray<float> exp('c', {3, 4}, {0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f,0.5f});
    //************************************//

    nd4j::ops::reduce_sum_bp<float> op;
    auto result = op.execute({&input, &eps}, {}, {});

    ASSERT_EQ(Status::OK(), result->status());
    auto z = result->at(0);    
//    z->printIndexedBuffer("Result is ");
//    z->printShapeInfo();
    ASSERT_TRUE(exp.equalsTo(z));
    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Reduce_Sum_BP_2) {
    
    NDArray<float> input('c', {3, 4},   {1., 2., 3., 4., 5., 6., 7., 8., 9., 10., 11., 12.});    
    NDArray<float> eps('c', {1, 1}, {0.5f});
    NDArray<float> exp('c', {3, 4}, {0.5f, 0.5f, 0.5f, 0.5f, 
                                     0.5f, 0.5f, 0.5f, 0.5f, 
                                     0.5f, 0.5f, 0.5f,0.5f});
    //************************************//

    nd4j::ops::reduce_sum_bp<float> op;
    auto result = op.execute({&input, &eps}, {1.f}, {});

    ASSERT_EQ(Status::OK(), result->status());
    auto z = result->at(0);    
//  z->printIndexedBuffer("Result is ");
//  z->printShapeInfo();
    ASSERT_TRUE(exp.equalsTo(z));
    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Reduce_Sum_BP_3) {
    
    NDArray<float> input('c', {3, 4},   {1., 2., 3., 4., 5., 6., 7., 8., 9., 10., 11., 12.});    
    NDArray<float> eps('c', {4}, {1.f, 2.f, 3.f, 4.f});
    NDArray<float> exp('c', {3, 4}, {1.f, 2.f, 3.f, 4.f, 
                                     1.f, 2.f, 3.f, 4.f, 
                                     1.f, 2.f, 3.f, 4.f});
    //************************************//

    nd4j::ops::reduce_sum_bp<float> op;
    auto result = op.execute({&input, &eps}, {}, {0});

    ASSERT_EQ(Status::OK(), result->status());
    auto z = result->at(0);    
//    z->printIndexedBuffer("Result is ");
//    z->printShapeInfo();
    ASSERT_TRUE(exp.equalsTo(z));
    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Reduce_Sum_BP_4) {
    
    NDArray<float> input('c', {3, 4},   {1., 2., 3., 4., 5., 6., 7., 8., 9., 10., 11., 12.});    
    NDArray<float> eps('c', {1, 4}, {1.f, 2.f, 3.f, 4.f});
    NDArray<float> exp('c', {3, 4}, {1.f, 2.f, 3.f, 4.f, 
                                     1.f, 2.f, 3.f, 4.f, 
                                     1.f, 2.f, 3.f, 4.f});
    //************************************//

    nd4j::ops::reduce_sum_bp<float> op;
    auto result = op.execute({&input, &eps}, {1.f}, {0});

    ASSERT_EQ(Status::OK(), result->status());
    auto z = result->at(0);    
//    z->printIndexedBuffer("Result is ");
//    z->printShapeInfo();
    ASSERT_TRUE(exp.equalsTo(z));
    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Reduce_Prod_BP_1) {
    
    NDArray<float> input('c', {3, 5},   {1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f});    
    NDArray<float> eps(1307674368000.f);
    //************************************//
//    NDArray<float> exp('c', {3, 4}, {0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f,0.5f});
    //************************************//
    NDArray<float> exp('c', {3, 5},   {1710012166826558903812096.f, 855006083413279451906048.f, 570004067618451974258688.f, 
                                       427503041706639725953024.f, 342002454982589992140800.f, 285002033809225987129344.f, 
                                       244287457550765131825152.f, 213751520853319862976512.f, 190001355872817324752896.f, 
                                       171001227491294996070400.f, 155455648254341989531648.f, 142501016904612993564672.f, 
                                       131539399526781282156544.f, 122143728775382565912576.f, 114000815325130245799936.f});    

    nd4j::ops::reduce_prod_bp<float> op;
    auto result = op.execute({&input, &eps}, {}, {});

    ASSERT_EQ(Status::OK(), result->status());
    auto z = result->at(0);    
//    z->printIndexedBuffer("Result is ");
//    z->printShapeInfo();
    ASSERT_TRUE(exp.equalsTo(z));
    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, reduceMean_test1) {

    NDArray<float> x('c', {2,3,4});
    NDArray<float> exp('c', {4}, {11.f, 12.f, 13.f, 14.f});
    x.linspace(1);
    
        
    nd4j::ops::reduce_mean<float> op;
    auto result = op.execute({&x}, {}, {0,1});
    auto output = result->at(0);    

    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, reduceMean_test2) {

    NDArray<float> x('c', {2,3,4});
    NDArray<float> exp('c', {1,1,4}, {11.f, 12.f, 13.f, 14.f});
    x.linspace(1);
    
        
    nd4j::ops::reduce_mean<float> op;
    auto result = op.execute({&x}, {1.}, {0,1});
    auto output = result->at(0);    

    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, reduceMean_test3) {

    NDArray<float> x('c', {2,3,4});
    NDArray<float> exp('c', {3}, {8.5f, 12.5f, 16.5f});
    x.linspace(1);
    
        
    nd4j::ops::reduce_mean<float> op;
    auto result = op.execute({&x}, {}, {0,2});
    auto output = result->at(0);    

    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, reduceMean_test4) {

    NDArray<float> x('c', {2,3,4});
    NDArray<float> exp('c', {1,3,1}, {8.5f, 12.5f, 16.5f});
    x.linspace(1);
    
        
    nd4j::ops::reduce_mean<float> op;
    auto result = op.execute({&x}, {1.f}, {0,2});
    auto output = result->at(0);    

    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, reduceMean_test5) {

    NDArray<float> x('c', {2,3,4});
    NDArray<float> exp(12.5f);
    x.linspace(1);
    
        
    nd4j::ops::reduce_mean<float> op;
    auto result = op.execute({&x}, {}, {});
    auto output = result->at(0);    

    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, reduceMean_test6) {

    NDArray<float> x('c', {2,3,4});
    NDArray<float> exp(12.5f);
    x.linspace(1);
           
    nd4j::ops::reduce_mean<float> op;
    auto result = op.execute({&x}, {}, {0,1,2});
    auto output = result->at(0);    

    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, reduceMean_test7) {

    NDArray<float> x('c', {2,3,4});
    NDArray<float> exp('c', {1,1,1}, {12.5f});
    x.linspace(1);
           
    nd4j::ops::reduce_mean<float> op;
    auto result = op.execute({&x}, {1.}, {0,1,2});
    auto output = result->at(0);    

    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, reduceMeanBP_test1) {

    NDArray<float> x('c', {3,4});
    NDArray<float> gradO1(0.5f);
    NDArray<float> gradO2('c', {1,1}, {0.5f});
    NDArray<float> exp('c', {3,4}, {1./24, 1./24, 1./24, 1./24, 1./24, 1./24, 1./24, 1./24, 1./24, 1./24, 1./24, 1./24});

    x.linspace(1);
            
    nd4j::ops::reduce_mean_bp<float> op;

    auto result = op.execute({&x, &gradO1}, {0}, {});
    ASSERT_EQ(ND4J_STATUS_OK, result->status());    
    auto output = result->at(0);
    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));
    delete result;

    result = op.execute({&x, &gradO2}, {1}, {});
    ASSERT_EQ(ND4J_STATUS_OK, result->status());    
    output = result->at(0);
    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));
    delete result;
}


////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, reduceMeanBP_test2) {

    NDArray<float> x('c', {3,4});
    NDArray<float> gradO1('c', {4},  {1.f, 2.f, 3.f, 4.f});
    NDArray<float> gradO2('c', {1,4}, {1.f, 2.f, 3.f, 4.f});
    NDArray<float> exp('c', {3,4}, {1.f/3.f, 2.f/3.f, 1.f, 4.f/3.f, 1.f/3.f, 2.f/3.f, 1.f, 4.f/3.f, 1.f/3.f, 2.f/3.f, 1.f, 4.f/3.f});

    x.linspace(1);
            
    nd4j::ops::reduce_mean_bp<float> op;

    auto result = op.execute({&x, &gradO1}, {0}, {0});
    ASSERT_EQ(ND4J_STATUS_OK, result->status());    
    auto output = result->at(0);
    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));
    delete result;

    result = op.execute({&x, &gradO2}, {1}, {0});
    ASSERT_EQ(ND4J_STATUS_OK, result->status());    
    output = result->at(0);
    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));
    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, reduceMeanBP_test3) {

    NDArray<float> x('c', {3,4});
    NDArray<float> gradO1('c', {3}, {1.f, 2.f, 3.f});
    NDArray<float> gradO2('c', {3,1}, {1.f, 2.f, 3.f});
    NDArray<float> exp('c', {3,4}, {0.25f, 0.25f, 0.25f, 0.25f, 0.5f, 0.5f, 0.5f, 0.5f, 0.75f, 0.75f, 0.75f, 0.75f});

    x.linspace(1);
            
    nd4j::ops::reduce_mean_bp<float> op;

    auto result = op.execute({&x, &gradO1}, {0}, {1});
    ASSERT_EQ(ND4J_STATUS_OK, result->status());    
    auto output = result->at(0);
    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output)); 
    delete result;

    result = op.execute({&x, &gradO2}, {1}, {1});
    ASSERT_EQ(ND4J_STATUS_OK, result->status());    
    output = result->at(0);
    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));
    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, reduceStDevBP_test4) {

    NDArray<float> x('c', {3}, {2.f, 3.f, 4.f});
    NDArray<float> gradO(0.5f);    
    NDArray<float> exp('c', {3}, {-0.25f, 0.f, 0.25f});    
            
    nd4j::ops::reduce_stdev_bp<float> op;

    auto result = op.execute({&x, &gradO}, {0,1}, {});
    ASSERT_EQ(ND4J_STATUS_OK, result->status());        
    auto output = result->at(0);        

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));
    delete result;

}

//////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, avgpool2d_test13) {

    int bS=4, iH=10,iW=10,  iC=3,  kH=3,kW=3,  sH=3,sW=3,  pH=0,pW=0,  dH=1,dW=1;
    int       oH=4, oW=4;
    int paddingMode = 1;             // 1-SAME,  0-VALID
    int dataFormat  = 1;             // 1-NDHWC, 0-NCDHW

    NDArray<double> input   ('c', {bS, iH, iW, iC});
    NDArray<double> expected('c', {bS, oH, oW, iC}, { 17.5,   18.5,   19.5,  25. ,   26. ,   27. ,  34. ,   35. ,   36. ,  41.5,   42.5,   43.5,  92.5,   93.5,   94.5, 100. ,  101. ,  102. , 109. ,  110. ,  111. , 116.5,  117.5,  118.5,
                                                      182.5,  183.5,  184.5, 190. ,  191. ,  192. , 199. ,  200. ,  201. , 206.5,  207.5,  208.5, 257.5,  258.5,  259.5, 265. ,  266. ,  267. , 274. ,  275. ,  276. , 281.5,  282.5,  283.5,
                                                      317.5,  318.5,  319.5, 325. ,  326. ,  327. , 334. ,  335. ,  336. , 341.5,  342.5,  343.5, 392.5,  393.5,  394.5, 400. ,  401. ,  402. , 409. ,  410. ,  411. , 416.5,  417.5,  418.5,
                                                      482.5,  483.5,  484.5, 490. ,  491. ,  492. , 499. ,  500. ,  501. , 506.5,  507.5,  508.5, 557.5,  558.5,  559.5, 565. ,  566. ,  567. , 574. ,  575. ,  576. , 581.5,  582.5,  583.5,
                                                      617.5,  618.5,  619.5, 625. ,  626. ,  627. , 634. ,  635. ,  636. , 641.5,  642.5,  643.5, 692.5,  693.5,  694.5, 700. ,  701. ,  702. , 709. ,  710. ,  711. , 716.5,  717.5,  718.5,
                                                      782.5,  783.5,  784.5, 790. ,  791. ,  792. , 799. ,  800. ,  801. , 806.5,  807.5,  808.5, 857.5,  858.5,  859.5, 865. ,  866. ,  867. , 874. ,  875. ,  876. , 881.5,  882.5,  883.5,
                                                      917.5,  918.5,  919.5, 925. ,  926. ,  927. , 934. ,  935. ,  936. , 941.5,  942.5,  943.5, 992.5,  993.5,  994.5,1000. , 1001. , 1002. ,1009. , 1010. , 1011. ,1016.5, 1017.5, 1018.5,
                                                     1082.5, 1083.5, 1084.5,1090. , 1091. , 1092. ,1099. , 1100. , 1101. ,1106.5, 1107.5, 1108.5,1157.5, 1158.5, 1159.5,1165. , 1166. , 1167. ,1174. , 1175. , 1176. ,1181.5, 1182.5, 1183.5});
    input.linspace(1.);    

    nd4j::ops::avgpool2d<double> op;
    ResultSet<double>* results = op.execute({&input}, {}, {kH,kW,  sH,sW,  pH,pW,  dH,dW,  paddingMode, 0, dataFormat});
    NDArray<double>* output = results->at(0);    

    ASSERT_EQ(Status::OK(), results->status());
    ASSERT_TRUE(expected.isSameShape(output));
    ASSERT_TRUE(expected.equalsTo(output));    
 
    delete results;
}

 
///////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, softmax_cross_entropy_loss_with_logits_test1) {
    
    NDArray<double> labels('c', {2,3,4},{0,1,1,0,0,0,1,0,1,0,1,1,1,0,1,0,1,0,0,1,1,0,1,0});
    NDArray<double> logits('c', {2,3,4});
    NDArray<double> expected('c', {2,3}, {2.78507, 1.34254, 4.12761, 2.88507, 2.78507, 2.88507});
                                            
    logits.linspace(0.1, 0.1);

    nd4j::ops::softmax_cross_entropy_loss_with_logits<double> op;
    nd4j::ResultSet<double>* results = op.execute({&logits, &labels}, {}, {});

    ASSERT_EQ(ND4J_STATUS_OK, results->status());

    NDArray<double> *output = results->at(0);    

    ASSERT_TRUE(expected.isSameShape(output));
    ASSERT_TRUE(expected.equalsTo(output));

    delete results;
}

///////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, softmax_cross_entropy_loss_with_logits_test2) {
    
    NDArray<double> labels('c', {2,3,4},{0,1,1,0,0,0,1,0,1,0,1,1,1,0,1,0,1,0,0,1,1,0,1,0});
    NDArray<double> logits('c', {2,3,4});
    NDArray<double> expected('c', {3,4}, {0.26328, 1.46328, 1.72656, 0.     , 0.26328, 0.     , 1.46328, 0.26328, 1.72656, 0.     , 1.72656, 1.46328});
                                            
    logits.linspace(0.1, 0.1);

    nd4j::ops::softmax_cross_entropy_loss_with_logits<double> op;
    nd4j::ResultSet<double>* results = op.execute({&logits, &labels}, {}, {0});

    ASSERT_EQ(ND4J_STATUS_OK, results->status());

    NDArray<double> *output = results->at(0);    

    ASSERT_TRUE(expected.isSameShape(output));
    ASSERT_TRUE(expected.equalsTo(output));

    delete results;
}

///////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, softmax_cross_entropy_loss_with_logits_test3) {
    
    NDArray<double> labels('c', {2,3,4},{0,1,1,0,0,0,1,0,1,0,1,1,1,0,1,0,1,0,0,1,1,0,1,0});
    NDArray<double> logits('c', {2,3,4});
    NDArray<double> expected('c', {2,4}, {0.75125, 1.55125, 3.45375, 0.75125, 3.45375, 0.     , 2.3025 , 1.15125});
                                            
    logits.linspace(0.1, 0.1);

    nd4j::ops::softmax_cross_entropy_loss_with_logits<double> op;
    nd4j::ResultSet<double>* results = op.execute({&logits, &labels}, {}, {1});

    ASSERT_EQ(ND4J_STATUS_OK, results->status());

    NDArray<double> *output = results->at(0);    

    ASSERT_TRUE(expected.isSameShape(output));
    ASSERT_TRUE(expected.equalsTo(output));

    delete results;
}

///////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, softmax_cross_entropy_loss_with_logits_test4) {
    
    NDArray<double> labels('c', {2,3},{0,1,1,0,0,1});
    NDArray<double> logits('c', {2,3});
    NDArray<double> expected('c', {2}, {2.10389, 1.00194});
                                            
    logits.linspace(0.1, 0.1);

    nd4j::ops::softmax_cross_entropy_loss_with_logits<double> op;
    nd4j::ResultSet<double>* results = op.execute({&logits, &labels}, {}, {});

    ASSERT_EQ(ND4J_STATUS_OK, results->status());

    NDArray<double> *output = results->at(0);    

    ASSERT_TRUE(expected.isSameShape(output));
    ASSERT_TRUE(expected.equalsTo(output));

    delete results;
}

///////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, softmax_cross_entropy_loss_with_logits_test5) {
    
    NDArray<double> labels('c', {2,3},{0,1,1,0,0,1});
    NDArray<double> logits('c', {2,3});
    NDArray<double> expected('c', {3}, {0., 0.85436, 1.40871});
                                            
    logits.linspace(0.1, 0.1);

    nd4j::ops::softmax_cross_entropy_loss_with_logits<double> op;
    nd4j::ResultSet<double>* results = op.execute({&logits, &labels}, {}, {0});

    ASSERT_EQ(ND4J_STATUS_OK, results->status());

    NDArray<double> *output = results->at(0);    

    ASSERT_TRUE(expected.isSameShape(output));
    ASSERT_TRUE(expected.equalsTo(output));

    delete results;
}

///////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, softmax_cross_entropy_loss_with_logits_test6) {
    
    NDArray<double> labels('c', {2,1}, {0,1});
    NDArray<double> logits('c', {2,1});
    NDArray<double> expected('c', {1}, {0.6444});
                                            
    logits.linspace(0.1, 0.1);

    nd4j::ops::softmax_cross_entropy_loss_with_logits<double> op;
    nd4j::ResultSet<double>* results = op.execute({&logits, &labels}, {}, {0});

    ASSERT_EQ(ND4J_STATUS_OK, results->status());

    NDArray<double> *output = results->at(0);    

    ASSERT_TRUE(expected.isSameShape(output));
    ASSERT_TRUE(expected.equalsTo(output));

    delete results;
}

///////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, softmax_cross_entropy_loss_with_logits_test7) {
    
    NDArray<double> labels('c', {2,1}, {0,1});
    NDArray<double> logits('c', {2,1});
    NDArray<double> expected('c', {2}, {0., 0.});
                                            
    logits.linspace(0.1, 0.1);

    nd4j::ops::softmax_cross_entropy_loss_with_logits<double> op;
    nd4j::ResultSet<double>* results = op.execute({&logits, &labels}, {}, {1});

    ASSERT_EQ(ND4J_STATUS_OK, results->status());

    NDArray<double> *output = results->at(0);    

    ASSERT_TRUE(expected.isSameShape(output));
    ASSERT_TRUE(expected.equalsTo(output));

    delete results;
}

///////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, softmax_cross_entropy_loss_with_logits_test8) {
    
    NDArray<double> labels('c', {2}, {0,1});
    NDArray<double> logits('c', {2});
    NDArray<double> expected(0.6444);
                                            
    logits.linspace(0.1, 0.1);

    nd4j::ops::softmax_cross_entropy_loss_with_logits<double> op;
    nd4j::ResultSet<double>* results = op.execute({&logits, &labels}, {}, {});

    ASSERT_EQ(ND4J_STATUS_OK, results->status());

    NDArray<double> *output = results->at(0);    

    ASSERT_TRUE(expected.isSameShape(output));
    ASSERT_TRUE(expected.equalsTo(output));

    delete results;
}

///////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, softmax_cross_entropy_loss_with_logits_test9) {
    
    NDArray<double> labels('c', {1}, {0});
    NDArray<double> logits('c', {1}, {0.2});
    NDArray<double> expected(0.);
                                               
    nd4j::ops::softmax_cross_entropy_loss_with_logits<double> op;
    nd4j::ResultSet<double>* results = op.execute({&logits, &labels}, {}, {});

    ASSERT_EQ(ND4J_STATUS_OK, results->status());

    NDArray<double> *output = results->at(0);    

    ASSERT_TRUE(expected.isSameShape(output));
    ASSERT_TRUE(expected.equalsTo(output));

    delete results;
}

///////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, softmax_cross_entropy_loss_with_logits_test10) {
    
    NDArray<double> labels('c', {1,2}, {0,1});
    NDArray<double> logits('c', {1,2});
    NDArray<double> expected('c', {2}, {0., 0.});
                                            
    logits.linspace(0.1, 0.1);

    nd4j::ops::softmax_cross_entropy_loss_with_logits<double> op;
    nd4j::ResultSet<double>* results = op.execute({&logits, &labels}, {}, {0});

    ASSERT_EQ(ND4J_STATUS_OK, results->status());

    NDArray<double> *output = results->at(0);    

    ASSERT_TRUE(expected.isSameShape(output));
    ASSERT_TRUE(expected.equalsTo(output));

    delete results;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, clipbynorm_test4) {
    
    NDArray<double> x('c', {3, 5}, {0.7044955, 0.55606544, 0.15833677, 0.001874401, 0.61595726, 0.3924779, 0.7414847, 0.4127324, 0.24026828, 0.26093036, 0.46741188, 0.01863421, 0.08528871, 0.529365, 0.5510694});
    NDArray<double> exp('c', {3, 5}, {0.405392, 0.319980, 0.091113, 0.001079, 0.354444, 0.225846, 0.426676, 0.237501, 0.138259, 0.150149, 0.268965, 0.010723, 0.049078, 0.304615, 0.317105});    

    nd4j::ops::clipbynorm<double> op;
    auto result = op.execute({&x}, {1.f}, {});
    auto output = result->at(0);
        
    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, clipbynorm_test5) {
    
    NDArray<double> x('c', {3, 5});
    NDArray<double> exp('c', {3, 5}, {1.,  2.,  2.89271,  3.50524,  4.00892, 6.,  7.,  7.71389,  7.88678,  8.01784, 11., 12., 12.53507, 12.26833, 12.02676});    

    x.linspace(1);

    nd4j::ops::clipbynorm<double> op;
    auto result = op.execute({&x}, {15.f}, {0});
    auto output = result->at(0);
        
    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, clipbynorm_test6) {
    
    NDArray<double> x('c', {3, 5});
    NDArray<double> exp('c', {3, 5}, {1., 2., 3., 4., 5., 4.95434, 5.78006, 6.60578, 7.43151, 8.25723, 5.64288, 6.15587, 6.66886, 7.18185, 7.69484});    

    x.linspace(1);

    nd4j::ops::clipbynorm<double> op;
    auto result = op.execute({&x}, {15.f}, {1});
    auto output = result->at(0);
        
    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}
 
////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, clipbynorm_test7) {
    
    NDArray<double> x('c', {3, 5});
    NDArray<double> exp('c', {3, 5}, {0.42597, 0.85194, 1.27791, 1.70389, 2.12986, 2.55583, 2.9818 , 3.40777, 3.83374, 4.25971, 4.68569, 5.11166, 5.53763, 5.9636 , 6.38957});

    x.linspace(1);

    nd4j::ops::clipbynorm<double> op;
    auto result = op.execute({&x}, {15.f}, {0,1});
    auto output = result->at(0);

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}
 
////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, clipbynorm_test8) {
    
    NDArray<double> x('c', {3, 5});
    NDArray<double> exp('c', {3, 5}, {0.42597, 0.85194, 1.27791, 1.70389, 2.12986, 2.55583, 2.9818 , 3.40777, 3.83374, 4.25971, 4.68569, 5.11166, 5.53763, 5.9636 , 6.38957});

    x.linspace(1);

    nd4j::ops::clipbynorm<double> op;
    auto result = op.execute({&x}, {15.}, {});
    auto output = result->at(0);

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}
 
////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, clipbynorm_test9) {
    
    NDArray<double> x('c', {2}, {3., 4.});
    NDArray<double> exp('c', {2}, {2.4, 3.2});    

    nd4j::ops::clipbynorm<double> op;
    auto result = op.execute({&x}, {4.}, {});
    auto output = result->at(0);

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}
 
////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, clipbynorm_test10) {
    
    NDArray<double> x(6.);
    NDArray<double> exp(5.);    

    nd4j::ops::clipbynorm<double> op;
    auto result = op.execute({&x}, {5.}, {});
    auto output = result->at(0);

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}
 
////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, clipbynorm_test11) {
    
    NDArray<double> x('c', {2, 3, 4});
    NDArray<double> exp('c', {2, 3, 4}, {1.,  2.,  3.,  4.,  4.44787,  5.33745,  6.22702,  7.1166 , 6.33046,  7.03384,  7.73723,  8.44061,
                                        13., 14., 15., 16., 15.12277, 16.01235, 16.90192, 17.7915 ,14.77107, 15.47446, 16.17784, 16.88123});

    x.linspace(1);

    nd4j::ops::clipbynorm<double> op;
    auto result = op.execute({&x}, {35.}, {0, 2});
    auto output = result->at(0);

    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));

    delete result;
}
 

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, reduceMeanBP_test4) {

    NDArray<double> x('c', {3, 4}, {1., 2., 3., 4., 5., 6., 7., 8., 9., 10., 11., 12. });
    NDArray<double> gradO1('c', {4}, {1., 2., 3., 4.});
    NDArray<double> gradO2('c', {1, 4}, {1., 2., 3., 4.});
    NDArray<double> exp('c', {3,4}, {0.333333, 0.666667, 1.000000, 1.333333, 0.333333, 0.666667, 1.000000, 1.333333, 0.333333, 0.666667, 1.000000, 1.333333});
                                     
    nd4j::ops::reduce_mean_bp<double> op;

    auto result = op.execute({&x, &gradO1}, {0}, {0});
    ASSERT_EQ(ND4J_STATUS_OK, result->status());    
    auto output = result->at(0);    
    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));
    delete result;

    result = op.execute({&x, &gradO2}, {1}, {0});
    ASSERT_EQ(ND4J_STATUS_OK, result->status());    
    output = result->at(0);    
    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));
    delete result;
}


////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, reduceMeanBP_test5) {

    NDArray<double> x('c', {3, 4}, {1., 2., 3., 4., 5., 6., 7., 8., 9., 10., 11., 12. });
    NDArray<double> gradO1('c', {3}, {1., 2., 3.});
    NDArray<double> gradO2('c', {3, 1}, {1., 2., 3.});
    NDArray<double> exp('c', {3,4}, {0.2500,0.2500,0.2500,0.2500, 0.5000,0.5000,0.5000,0.5000, 0.7500,0.7500,0.7500,0.7500});
                                     
    nd4j::ops::reduce_mean_bp<double> op;
    
    auto result = op.execute({&x, &gradO1}, {0}, {1});
    ASSERT_EQ(ND4J_STATUS_OK, result->status());    
    auto output = result->at(0);    
    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));
    delete result;

    result = op.execute({&x, &gradO2}, {1}, {1});
    ASSERT_EQ(ND4J_STATUS_OK, result->status());    
    output = result->at(0);    
    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));
    delete result;
}


////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, reduceStDevBP_test5) {

    NDArray<double> x('c', {3, 4}, {1., 2., 3., 4., 5., 6., 7., 8., 9., 10., 11., 12. });
    NDArray<double> gradO1('c', {4}, {1., 2., 3., 4.});
    NDArray<double> gradO2('c', {1, 4}, {1., 2., 3., 4.});
    NDArray<double> exp('c', {3,4}, {-0.408248, -0.816497, -1.224745, -1.632993, 0.000000, 0.000000, 0.000000, 0.000000, 0.408248, 0.816497, 1.224745, 1.632993});
                                                                          
    nd4j::ops::reduce_stdev_bp<double> op;

    auto result = op.execute({&x, &gradO1}, {0}, {0});
    ASSERT_EQ(ND4J_STATUS_OK, result->status());    
    auto output = result->at(0);        
    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));
    delete result;

    result = op.execute({&x, &gradO2}, {1}, {0});
    ASSERT_EQ(ND4J_STATUS_OK, result->status());    
    output = result->at(0);    
    ASSERT_TRUE(exp.isSameShape(output));
    ASSERT_TRUE(exp.equalsTo(output));
    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, zeros_as_test1) {

    NDArray<double> x(10.);
    NDArray<double> y(100.);
    NDArray<double> exp(0.);
                                                                          
    nd4j::ops::zeros_as<double> op;

    Nd4jStatus status = op.execute({&x}, {&y}, {}, {});
    ASSERT_EQ(ND4J_STATUS_OK, status);    
    
    ASSERT_TRUE(y.isSameShape(exp));
    ASSERT_TRUE(y.equalsTo(exp));

}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, ones_as_test1) {

    NDArray<double> x(10.);
    NDArray<double> y(100.);
    NDArray<double> exp(1.);

    nd4j::ops::ones_as<double> op;

    Nd4jStatus status = op.execute({&x}, {&y}, {}, {});
    ASSERT_EQ(ND4J_STATUS_OK, status);    
    
    ASSERT_TRUE(y.isSameShape(exp));
    ASSERT_TRUE(y.equalsTo(exp));
        
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, NormalizeMoments_SGO_1) {

    NDArray<double> data  ('c', {10, 10});
    data.linspace(1);
    
    NDArray<double>* means = data.sum({0});
    NDArray<double>* deviance = data.varianceAlongDimension<simdOps::SummaryStatsVariance<double>>(true, {0}); //('c', {10, 10});

    NDArray<double> counts(10.0);

//    NDArray<double> expMeans('c', {10, 10});

//    NDArray<double> expDeviance('c', {10, 10});

    nd4j::ops::normalize_moments<double> op;
    ResultSet<double>* results = op.execute({&counts, means, deviance}, {0.0}, {});

    ASSERT_EQ(Status::OK(), results->status());
    ASSERT_EQ(results->size(), 2);

    NDArray<double>* outputMeans = results->at(0);    
    NDArray<double>* outputDeviance = results->at(1);    

//    outputMeans->printIndexedBuffer("Means");
//    outputDeviance->printIndexedBuffer("Variance");
    delete means;
    delete deviance;
//    ASSERT_TRUE(expMeans.isSameShape(outputMeans));
//    ASSERT_TRUE(expMeans.equalsTo(outputMeans));    
//    ASSERT_TRUE(expMeans.isSameShape(outputDeviance));
//    ASSERT_TRUE(expDeviance.equalsTo(outputDeviance));    

    delete results;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Moments_1) {

    NDArray<float> x('c', {2, 3, 4});
    NDArray<float> expMeans('c', {4}, {11.f, 12.f, 13.f, 14.f});
    NDArray<float> expVariance('c', {4}, {46.666668f, 46.666668f, 46.66666f, 46.666668f});
    x.linspace(1);

    nd4j::ops::moments<float> op;
    auto result = op.execute({&x}, {}, {0, 1});

    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    NDArray<float>* outputMeans = result->at(0);    
    NDArray<float>* outputVariance = result->at(1);    

//    outputMeans->printIndexedBuffer("Means");
//    outputVariance->printIndexedBuffer("Variance");
//    outputMeans->printShapeInfo("Result shape");


//    ASSERT_TRUE(exp.isSameShape(output));
//    ASSERT_TRUE(exp.equalsTo(output));
    ASSERT_TRUE(expMeans.isSameShape(outputMeans));
    ASSERT_TRUE(expMeans.equalsTo(outputMeans));
    ASSERT_TRUE(expVariance.isSameShape(outputVariance));
    ASSERT_TRUE(expVariance.equalsTo(outputVariance));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Moments_2) {

    NDArray<float> x('c', {2, 3, 4});
    NDArray<float> expMeans('c', {1,1,4}, {11.f, 12.f, 13.f, 14.f});
    NDArray<float> expVariance('c', {1,1,4}, {46.666668f, 46.666668f, 46.66666f, 46.666668f});
    x.linspace(1);

    nd4j::ops::moments<float> op;
    auto result = op.execute({&x}, {1.}, {0, 1});
    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    NDArray<float>* outputMeans = result->at(0);    
    NDArray<float>* outputVariance = result->at(1);    

//    outputMeans->printIndexedBuffer("Means");
//    outputVariance->printIndexedBuffer("Variance");
//    outputMeans->printShapeInfo("Result shape");

//    ASSERT_TRUE(exp.isSameShape(output));
//    ASSERT_TRUE(exp.equalsTo(output));
    ASSERT_TRUE(expMeans.isSameShape(outputMeans));
    ASSERT_TRUE(expMeans.equalsTo(outputMeans));
    ASSERT_TRUE(expVariance.isSameShape(outputVariance));
    ASSERT_TRUE(expVariance.equalsTo(outputVariance));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Moments_3) {

    NDArray<float> x('c', {2, 3, 4});
    NDArray<float> expMeans('c', {3}, {8.5f, 12.5f, 16.5f});
    NDArray<float> expVariance('c', {3}, {37.25f, 37.25f, 37.25f});
    x.linspace(1);

    nd4j::ops::moments<float> op;
    auto result = op.execute({&x}, {}, {0, 2});
    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    NDArray<float>* outputMeans = result->at(0);    
    NDArray<float>* outputVariance = result->at(1);    

//    outputMeans->printIndexedBuffer("Means");
//    outputVariance->printIndexedBuffer("Variance");
//    outputMeans->printShapeInfo("Result shape");

//    ASSERT_TRUE(exp.isSameShape(output));
//    ASSERT_TRUE(exp.equalsTo(output));
    ASSERT_TRUE(expMeans.isSameShape(outputMeans));
    ASSERT_TRUE(expMeans.equalsTo(outputMeans));
    ASSERT_TRUE(expVariance.isSameShape(outputVariance));
    ASSERT_TRUE(expVariance.equalsTo(outputVariance));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Moments_4) {

    NDArray<float> x('c', {2, 3, 4});
    NDArray<float> expMeans('c', {1,3,1}, {8.5f, 12.5f, 16.5f});
    NDArray<float> expVariance('c', {1,3,1}, {37.25f, 37.25f, 37.25f});
    x.linspace(1);

    nd4j::ops::moments<float> op;
    auto result = op.execute({&x}, {1.}, {0, 2});
    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    NDArray<float>* outputMeans = result->at(0);    
    NDArray<float>* outputVariance = result->at(1);    

//    outputMeans->printIndexedBuffer("Means");
//    outputVariance->printIndexedBuffer("Variance");
//    outputMeans->printShapeInfo("Result shape");

//    ASSERT_TRUE(exp.isSameShape(output));
//    ASSERT_TRUE(exp.equalsTo(output));
    ASSERT_TRUE(expMeans.isSameShape(outputMeans));
    ASSERT_TRUE(expMeans.equalsTo(outputMeans));
    ASSERT_TRUE(expVariance.isSameShape(outputVariance));
    ASSERT_TRUE(expVariance.equalsTo(outputVariance));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Moments_6) {
    NDArray<float> expMeans(12.5f);
    NDArray<float> expVariance(47.916668f);

    NDArray<float> x('c', {2, 3, 4});
    x.linspace(1);
           
    nd4j::ops::moments<float> op;
    auto result = op.execute({&x}, {}, {0,1,2});
    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    NDArray<float>* outputMeans = result->at(0);    
    NDArray<float>* outputVariance = result->at(1);    

//    outputMeans->printIndexedBuffer("Means");
//    outputVariance->printIndexedBuffer("Variance");
//    outputMeans->printShapeInfo("Result shape");

    ASSERT_TRUE(expMeans.isSameShape(outputMeans));
    ASSERT_TRUE(expMeans.equalsTo(outputMeans));
    ASSERT_TRUE(expVariance.isSameShape(outputVariance));
    ASSERT_TRUE(expVariance.equalsTo(outputVariance));

    delete result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests8, Test_Moments_7) {

    NDArray<float> x('c', {2, 3, 4});

    NDArray<float> expMeans('c', {1,1,1}, {12.5f});
    NDArray<float> expVariance('c', {1,1,1}, {47.916668f});

    x.linspace(1);
    // x.printIndexedBuffer("Input with shape (2, 3, 4) is");       
    nd4j::ops::moments<float> op;
    auto result = op.execute({&x}, {1.}, {0,1,2});
    ASSERT_EQ(ND4J_STATUS_OK, result->status());    

    NDArray<float>* outputMeans = result->at(0);    
    NDArray<float>* outputVariance = result->at(1);    

//    outputMeans->printIndexedBuffer("Means");
//    outputVariance->printIndexedBuffer("Variance");
//    outputMeans->printShapeInfo("Result shape");
    ASSERT_TRUE(expMeans.isSameShape(outputMeans));
    ASSERT_TRUE(expMeans.equalsTo(outputMeans));
    ASSERT_TRUE(expVariance.isSameShape(outputVariance));
    ASSERT_TRUE(expVariance.equalsTo(outputVariance));

    delete result;
}
