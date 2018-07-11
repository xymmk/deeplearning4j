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

package org.deeplearning4j.integration;

import org.deeplearning4j.integration.testcases.*;
import org.junit.AfterClass;
import org.junit.Ignore;
import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.TemporaryFolder;

public class IntegrationTests extends BaseDL4JTest {

    @Rule
    public TemporaryFolder testDir = new TemporaryFolder();

    @AfterClass
    public static void afterClass(){
        IntegrationTestRunner.printCoverageInformation();
    }

    // ***** MLPTestCases *****
    @Test(timeout = 20000L)
    public void testMLPMnist() throws Exception {
        IntegrationTestRunner.runTest(MLPTestCases.getMLPMnist(), testDir);
    }

    @Test(timeout = 30000L)
    public void testMlpMoon() throws Exception {
        IntegrationTestRunner.runTest(MLPTestCases.getMLPMoon(), testDir);
    }

    // ***** RNNTestCases *****
    @Test(timeout = 30000L)
    public void testRnnSeqClassification1() throws Exception {
        IntegrationTestRunner.runTest(RNNTestCases.getRnnCsvSequenceClassificationTestCase1(), testDir);
    }

    @Test(timeout = 30000L)
    public void testRnnSeqClassification2() throws Exception {
        IntegrationTestRunner.runTest(RNNTestCases.getRnnCsvSequenceClassificationTestCase2(), testDir);
    }

    @Test(timeout = 120000L)
    public void testRnnCharacter() throws Exception {
        IntegrationTestRunner.runTest(RNNTestCases.getRnnCharacterTestCase(), testDir);
    }


    // ***** CNN1DTestCases *****
    @Ignore //TODO: NOT YET IMPLEMENTED
    @Test(timeout = 180000L)
    public void testCnn1dSynthetic() throws Exception {
        IntegrationTestRunner.runTest(CNN1DTestCases.getCnn1dTestCaseSynthetic(), testDir);
    }


    // ***** CNN2DTestCases *****
    @Ignore //TODO: NOT YET IMPLEMENTED
    @Test(timeout = 120000L)
    public void testLenetMnist() throws Exception {
        IntegrationTestRunner.runTest(CNN2DTestCases.getLenetMnist(), testDir);
    }

    @Ignore //https://github.com/deeplearning4j/deeplearning4j/issues/5309
    @Test(timeout = 360000L)
    public void testVgg16Transfer() throws Exception {
        IntegrationTestRunner.runTest(CNN2DTestCases.getVGG16TransferTinyImagenet(), testDir);
    }

    @Ignore //TODO: NOT YET IMPLEMENTED
    @Test(timeout = 180000L)
    public void testYoloHouseNumbers() throws Exception {
        IntegrationTestRunner.runTest(CNN2DTestCases.getYoloHouseNumbers(), testDir);
    }

    @Ignore //TODO: NOT YET IMPLEMENTED
    @Test(timeout = 120000L)
    public void testCnn2DSynthetic() throws Exception {
        IntegrationTestRunner.runTest(CNN2DTestCases.getCnn2DSynthetic(), testDir);
    }

    @Ignore //TODO: NOT YET IMPLEMENTED
    @Test(timeout = 120000L)
    public void testCnn2DLenetTransferDropoutRepeatability() throws Exception {
        IntegrationTestRunner.runTest(CNN2DTestCases.testLenetTransferDropoutRepeatability(), testDir);
    }


    // ***** CNN3DTestCases *****

    @Ignore //TODO: NOT YET IMPLEMENTED
    @Test(timeout = 180000L)
    public void testCnn3dSynthetic() throws Exception {
        IntegrationTestRunner.runTest(CNN3DTestCases.getCnn3dTestCaseSynthetic(), testDir);
    }


    // ***** UnsupervisedTestCases *****
    @Test(timeout = 120000L)
    public void testVAEMnistAnomaly() throws Exception {
        IntegrationTestRunner.runTest(UnsupervisedTestCases.getVAEMnistAnomaly(), testDir);
    }

    // ***** TransferLearningTestCases *****
    @Ignore //TODO: NOT YET IMPLEMENTED
    @Test(timeout = 180000L)
    public void testTransferResnet() throws Exception {
        IntegrationTestRunner.runTest(TransferLearningTestCases.testPartFrozenResNet50(), testDir);
    }

    @Ignore //TODO: NOT YET IMPLEMENTED
    @Test(timeout = 180000L)
    public void testTransferNASNET() throws Exception {
        IntegrationTestRunner.runTest(TransferLearningTestCases.testPartFrozenNASNET(), testDir);
    }


    // ***** KerasImportTestCases *****


}
