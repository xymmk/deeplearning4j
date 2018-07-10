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

package org.deeplearning4j.nn.modelimport.keras.utils;

import org.deeplearning4j.nn.modelimport.keras.config.KerasLayerConfiguration;
import org.deeplearning4j.nn.modelimport.keras.exceptions.InvalidKerasConfigurationException;
import org.deeplearning4j.nn.modelimport.keras.exceptions.UnsupportedKerasConfigurationException;
import org.nd4j.linalg.activations.IActivation;
import org.nd4j.linalg.activations.impl.*;

import java.util.Map;

/**
 * Utility functionality for Keras activation functions.
 *
 * @author Max Pumperla
 */
public class KerasActivationUtils {

    /**
     * Map Keras to DL4J activation functions.
     *
     * @param kerasActivation String containing Keras activation function name
     * @return String containing DL4J activation function name
     */
    public static IActivation mapActivation(String kerasActivation, KerasLayerConfiguration conf)
            throws UnsupportedKerasConfigurationException {
        IActivation dl4jActivation;
        if (kerasActivation.equals(conf.getKERAS_ACTIVATION_SOFTMAX())) {
            dl4jActivation = new ActivationSoftmax();
        } else if (kerasActivation.equals(conf.getKERAS_ACTIVATION_SOFTPLUS())) {
            dl4jActivation = new ActivationSoftPlus();
        } else if (kerasActivation.equals(conf.getKERAS_ACTIVATION_SOFTSIGN())) {
            dl4jActivation = new ActivationSoftSign();
        } else if (kerasActivation.equals(conf.getKERAS_ACTIVATION_RELU())) {
            dl4jActivation = new ActivationReLU();
        } else if (kerasActivation.equals(conf.getKERAS_ACTIVATION_RELU6())) {
            // TODO: map to relu6
            dl4jActivation = new ActivationReLU();
        } else if (kerasActivation.equals(conf.getKERAS_ACTIVATION_ELU())) {
            dl4jActivation = new ActivationELU();
        } else if (kerasActivation.equals(conf.getKERAS_ACTIVATION_SELU())) {
            dl4jActivation = new ActivationSELU();
        } else if (kerasActivation.equals(conf.getKERAS_ACTIVATION_TANH())) {
            dl4jActivation = new ActivationTanH();
        } else if (kerasActivation.equals(conf.getKERAS_ACTIVATION_SIGMOID())) {
            dl4jActivation = new ActivationSigmoid();
        } else if (kerasActivation.equals(conf.getKERAS_ACTIVATION_HARD_SIGMOID())) {
            dl4jActivation = new ActivationHardSigmoid();
        } else if (kerasActivation.equals(conf.getKERAS_ACTIVATION_LINEAR())) {
            dl4jActivation = new ActivationIdentity();
        } else {
            throw new UnsupportedKerasConfigurationException(
                    "Unknown Keras activation function " + kerasActivation);
        }
        return dl4jActivation;
    }

    /**
     * Get activation function from Keras layer configuration.
     *
     * @param layerConfig dictionary containing Keras layer configuration
     * @return DL4J activation function
     * @throws InvalidKerasConfigurationException     Invalid Keras config
     * @throws UnsupportedKerasConfigurationException Unsupported Keras config
     */
    public static IActivation getActivationFromConfig(Map<String, Object> layerConfig, KerasLayerConfiguration conf)
            throws InvalidKerasConfigurationException, UnsupportedKerasConfigurationException {
        Map<String, Object> innerConfig = KerasLayerUtils.getInnerLayerConfigFromConfig(layerConfig, conf);
        if (!innerConfig.containsKey(conf.getLAYER_FIELD_ACTIVATION()))
            throw new InvalidKerasConfigurationException("Keras layer is missing "
                    + conf.getLAYER_FIELD_ACTIVATION() + " field");
        return mapActivation((String) innerConfig.get(conf.getLAYER_FIELD_ACTIVATION()), conf);
    }
}
