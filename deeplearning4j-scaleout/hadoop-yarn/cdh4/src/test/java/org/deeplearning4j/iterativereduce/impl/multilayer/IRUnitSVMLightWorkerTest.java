/*
 *
 *  * Copyright 2015 Skymind,Inc.
 *  *
 *  *    Licensed under the Apache License, Version 2.0 (the "License");
 *  *    you may not use this file except in compliance with the License.
 *  *    You may obtain a copy of the License at
 *  *
 *  *        http://www.apache.org/licenses/LICENSE-2.0
 *  *
 *  *    Unless required by applicable law or agreed to in writing, software
 *  *    distributed under the License is distributed on an "AS IS" BASIS,
 *  *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  *    See the License for the specific language governing permissions and
 *  *    limitations under the License.
 *
 */

package org.deeplearning4j.iterativereduce.impl.multilayer;

import static org.junit.Assert.*;

import org.deeplearning4j.iterativereduce.irunit.IRUnitDriver;
import org.deeplearning4j.nn.conf.MultiLayerConfiguration;
import org.deeplearning4j.nn.conf.NeuralNetConfiguration;
import org.deeplearning4j.nn.conf.layers.RBM;
import org.junit.Test;


public class IRUnitSVMLightWorkerTest {
	@Test
	public void testLearnIrisFunctionViaIRNN_MLP() throws Exception {
		IRUnitDriver polr_ir = new IRUnitDriver("src/test/resources/yarn/configurations/svmLightWorkerIRUnitTest.properties");
		polr_ir.setup();
		polr_ir.simulateRun();
	}

}
