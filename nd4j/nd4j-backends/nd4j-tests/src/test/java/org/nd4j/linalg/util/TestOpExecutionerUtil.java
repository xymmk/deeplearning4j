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

package org.nd4j.linalg.util;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;
import org.nd4j.linalg.BaseNd4jTest;
import org.nd4j.linalg.api.ndarray.INDArray;
import org.nd4j.linalg.api.ops.executioner.OpExecutionerUtil;
import org.nd4j.linalg.factory.Nd4j;
import org.nd4j.linalg.factory.Nd4jBackend;

import static org.junit.Assert.*;

@RunWith(Parameterized.class)
public class TestOpExecutionerUtil extends BaseNd4jTest {

    public TestOpExecutionerUtil(Nd4jBackend backend) {
        super(backend);
    }

    @Test
    public void testCanDoDirectly() {
        INDArray f1_100 = Nd4j.create(new int[] {1, 100}, 'f');
        INDArray f100_1 = Nd4j.create(new int[] {100, 1}, 'f');
        INDArray c1_100 = Nd4j.create(new int[] {1, 100}, 'c');
        INDArray c100_1 = Nd4j.create(new int[] {100, 1}, 'c');
        INDArray f100_100 = Nd4j.create(new int[] {100, 100}, 'f');
        INDArray c100_100 = Nd4j.create(new int[] {100, 100}, 'c');
        INDArray f20_20_20 = Nd4j.create(new int[] {20, 20, 20}, 'f');
        INDArray c20_20_20 = Nd4j.create(new int[] {20, 20, 20}, 'c');

        //Trivial cases that can obviously be done directly
        assertTrue(OpExecutionerUtil.canDoOpDirectly(f1_100));
        assertTrue(OpExecutionerUtil.canDoOpDirectly(f100_1));
        assertTrue(OpExecutionerUtil.canDoOpDirectly(c1_100));
        assertTrue(OpExecutionerUtil.canDoOpDirectly(c100_1));
        assertTrue(OpExecutionerUtil.canDoOpDirectly(f100_100));
        assertTrue(OpExecutionerUtil.canDoOpDirectly(c100_100));
        assertTrue(OpExecutionerUtil.canDoOpDirectly(f20_20_20));
        assertTrue(OpExecutionerUtil.canDoOpDirectly(c20_20_20));

        assertTrue(OpExecutionerUtil.canDoOpDirectly(f1_100, f1_100));
        assertTrue(OpExecutionerUtil.canDoOpDirectly(f100_1, f100_1));
        assertTrue(OpExecutionerUtil.canDoOpDirectly(f100_100, f100_100));
        assertTrue(OpExecutionerUtil.canDoOpDirectly(f20_20_20, f20_20_20));
        assertTrue(OpExecutionerUtil.canDoOpDirectly(c1_100, c1_100));
        assertTrue(OpExecutionerUtil.canDoOpDirectly(c100_1, c100_1));
        assertTrue(OpExecutionerUtil.canDoOpDirectly(c100_100, c100_100));
        assertTrue(OpExecutionerUtil.canDoOpDirectly(c20_20_20, c20_20_20));
        assertTrue(OpExecutionerUtil.canDoOpDirectly(f1_100, c1_100));
        assertTrue(OpExecutionerUtil.canDoOpDirectly(f100_1, c100_1));

        assertTrue(OpExecutionerUtil.canDoOpDirectly(f1_100, f1_100, f1_100));
        assertTrue(OpExecutionerUtil.canDoOpDirectly(f100_1, f100_1, f100_1));
        assertTrue(OpExecutionerUtil.canDoOpDirectly(f100_100, f100_100, f100_100));
        assertTrue(OpExecutionerUtil.canDoOpDirectly(f20_20_20, f20_20_20, f20_20_20));
        assertTrue(OpExecutionerUtil.canDoOpDirectly(c1_100, c1_100, c1_100));
        assertTrue(OpExecutionerUtil.canDoOpDirectly(c100_1, c100_1, c100_1));
        assertTrue(OpExecutionerUtil.canDoOpDirectly(c100_100, c100_100, c100_100));
        assertTrue(OpExecutionerUtil.canDoOpDirectly(c20_20_20, c20_20_20, c20_20_20));
        assertTrue(OpExecutionerUtil.canDoOpDirectly(f1_100, c1_100, c1_100));
        assertTrue(OpExecutionerUtil.canDoOpDirectly(c1_100, c1_100, f1_100));
        assertTrue(OpExecutionerUtil.canDoOpDirectly(f100_1, c100_1, c100_1));
        assertTrue(OpExecutionerUtil.canDoOpDirectly(c100_1, c100_1, f100_1));

        //Cases that we don't expect to be doable directly (elements don't line up in buffer)
        assertFalse(OpExecutionerUtil.canDoOpDirectly(f100_100, c100_100));
        assertFalse(OpExecutionerUtil.canDoOpDirectly(f20_20_20, c20_20_20));
        assertFalse(OpExecutionerUtil.canDoOpDirectly(f100_100, c100_100, f100_100));
        assertFalse(OpExecutionerUtil.canDoOpDirectly(c20_20_20, f20_20_20, f20_20_20));
        assertFalse(OpExecutionerUtil.canDoOpDirectly(c100_100, c100_100, f100_100));
        assertFalse(OpExecutionerUtil.canDoOpDirectly(f20_20_20, c20_20_20, c20_20_20));
    }

    @Test
    public void testChooseElementWiseTensorDimension() {
        INDArray f1_100 = Nd4j.create(new int[] {1, 100}, 'f');
        INDArray f3_100 = Nd4j.create(new int[] {3, 100}, 'f');
        INDArray f100_1 = Nd4j.create(new int[] {100, 1}, 'f');
        INDArray f100_3 = Nd4j.create(new int[] {100, 3}, 'f');

        INDArray c1_100 = Nd4j.create(new int[] {1, 100}, 'c');
        INDArray c3_100 = Nd4j.create(new int[] {3, 100}, 'c');
        INDArray c100_1 = Nd4j.create(new int[] {100, 1}, 'c');
        INDArray c100_3 = Nd4j.create(new int[] {100, 3}, 'c');

        //Test selection for row vectors and NDArrays that are nearly-row vectors
        //In such cases, it is obvious which the best dimension is
        //However, in other cases it is not immediately clear
        assertEquals(OpExecutionerUtil.chooseElementWiseTensorDimension(f1_100), 1);
        assertEquals(OpExecutionerUtil.chooseElementWiseTensorDimension(f3_100), 1);
        assertEquals(OpExecutionerUtil.chooseElementWiseTensorDimension(f100_1), 0);
        assertEquals(OpExecutionerUtil.chooseElementWiseTensorDimension(f100_3), 0);
        assertEquals(OpExecutionerUtil.chooseElementWiseTensorDimension(f1_100, f1_100), 1);
        assertEquals(OpExecutionerUtil.chooseElementWiseTensorDimension(f3_100, f3_100), 1);
        assertEquals(OpExecutionerUtil.chooseElementWiseTensorDimension(f100_1, f100_1), 0);
        assertEquals(OpExecutionerUtil.chooseElementWiseTensorDimension(f100_3, f100_3), 0);
        assertEquals(OpExecutionerUtil.chooseElementWiseTensorDimension(f1_100, f1_100, f1_100), 1);
        assertEquals(OpExecutionerUtil.chooseElementWiseTensorDimension(f3_100, f3_100, f3_100), 1);
        assertEquals(OpExecutionerUtil.chooseElementWiseTensorDimension(f100_1, f100_1, f100_1), 0);
        assertEquals(OpExecutionerUtil.chooseElementWiseTensorDimension(f100_3, f100_3, f100_3), 0);

        assertEquals(OpExecutionerUtil.chooseElementWiseTensorDimension(c1_100), 1);
        assertEquals(OpExecutionerUtil.chooseElementWiseTensorDimension(c3_100), 1);
        assertEquals(OpExecutionerUtil.chooseElementWiseTensorDimension(c100_1), 0);
        assertEquals(OpExecutionerUtil.chooseElementWiseTensorDimension(c100_3), 0);
        assertEquals(OpExecutionerUtil.chooseElementWiseTensorDimension(c1_100, c1_100), 1);
        assertEquals(OpExecutionerUtil.chooseElementWiseTensorDimension(c3_100, c3_100), 1);
        assertEquals(OpExecutionerUtil.chooseElementWiseTensorDimension(c100_1, c100_1), 0);
        assertEquals(OpExecutionerUtil.chooseElementWiseTensorDimension(c100_3, c100_3), 0);
        assertEquals(OpExecutionerUtil.chooseElementWiseTensorDimension(c1_100, c1_100, c1_100), 1);
        assertEquals(OpExecutionerUtil.chooseElementWiseTensorDimension(c3_100, c3_100, c3_100), 1);
        assertEquals(OpExecutionerUtil.chooseElementWiseTensorDimension(c100_1, c100_1, c100_1), 0);
        assertEquals(OpExecutionerUtil.chooseElementWiseTensorDimension(c100_3, c100_3, c100_3), 0);
    }

    @Override
    public char ordering() {
        return 'c';
    }

}
