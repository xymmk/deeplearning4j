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

package org.deeplearning4j.datasets;

import org.deeplearning4j.BaseDL4JTest;
import org.deeplearning4j.base.MnistFetcher;
import org.deeplearning4j.common.resources.DL4JResources;
import org.deeplearning4j.datasets.iterator.impl.MnistDataSetIterator;
import org.junit.AfterClass;
import org.junit.BeforeClass;
import org.junit.ClassRule;
import org.junit.Test;
import org.junit.rules.TemporaryFolder;
import org.nd4j.linalg.api.ndarray.INDArray;
import org.nd4j.linalg.api.ops.impl.accum.MatchCondition;
import org.nd4j.linalg.dataset.DataSet;
import org.nd4j.linalg.dataset.api.iterator.DataSetIterator;
import org.nd4j.linalg.factory.Nd4j;
import org.nd4j.linalg.indexing.conditions.Conditions;

import java.io.File;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

/**
 * @author Justin Long (crockpotveggies)
 */
public class MnistFetcherTest extends BaseDL4JTest {

    @ClassRule
    public static TemporaryFolder testDir = new TemporaryFolder();

    @BeforeClass
    public static void setup() throws Exception {
        DL4JResources.setBaseDirectory(testDir.newFolder());
    }

    @AfterClass
    public static void after() {
        DL4JResources.resetBaseDirectoryLocation();
    }

    @Test
    public void testMnist() throws Exception {
        DataSetIterator iter = new MnistDataSetIterator(32, 60000, false, true, false, -1);
        int count = 0;
        while(iter.hasNext()){
            DataSet ds = iter.next();
            INDArray arr = ds.getFeatures().sum(1);
            int countMatch = Nd4j.getExecutioner().execAndReturn(new MatchCondition(arr, Conditions.equals(0))).z().getInt(0);
            assertEquals(0, countMatch);
            count++;
        }
        assertEquals(60000/32, count);

        count = 0;
        iter = new MnistDataSetIterator(32, false, 12345);
        while(iter.hasNext()){
            DataSet ds = iter.next();
            INDArray arr = ds.getFeatures().sum(1);
            int countMatch = Nd4j.getExecutioner().execAndReturn(new MatchCondition(arr, Conditions.equals(0))).z().getInt(0);
            assertEquals(0, countMatch);
            count++;
        }
        assertEquals((int)Math.ceil(10000/32.0), count);
    }

    @Test
    public void testMnistDataFetcher() throws Exception {
        MnistFetcher mnistFetcher = new MnistFetcher();
        File mnistDir = mnistFetcher.downloadAndUntar();

        assertTrue(mnistDir.isDirectory());
    }
}
