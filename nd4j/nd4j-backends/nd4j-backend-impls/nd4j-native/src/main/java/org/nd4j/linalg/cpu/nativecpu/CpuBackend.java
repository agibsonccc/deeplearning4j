/*
 *  ******************************************************************************
 *  *
 *  *
 *  * This program and the accompanying materials are made available under the
 *  * terms of the Apache License, Version 2.0 which is available at
 *  * https://www.apache.org/licenses/LICENSE-2.0.
 *  *
 *  *  See the NOTICE file distributed with this work for additional
 *  *  information regarding copyright ownership.
 *  * Unless required by applicable law or agreed to in writing, software
 *  * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 *  * License for the specific language governing permissions and limitations
 *  * under the License.
 *  *
 *  * SPDX-License-Identifier: Apache-2.0
 *  *****************************************************************************
 */

package org.nd4j.linalg.cpu.nativecpu;

import lombok.extern.slf4j.Slf4j;
import org.nd4j.common.config.ND4JSystemProperties;
import org.nd4j.linalg.factory.Environment;
import org.nd4j.linalg.factory.Nd4j;
import org.nd4j.linalg.factory.Nd4jBackend;
import org.nd4j.common.io.ClassPathResource;
import org.nd4j.common.io.Resource;
@Slf4j
public class CpuBackend extends Nd4jBackend {


    private final static String LINALG_PROPS = "/nd4j-native.properties";

    @Override
    public boolean isAvailable() {
        return true;
    }

    @Override
    public boolean canRun() {
        //no reliable way (yet!) to determine if running
        return true;
    }

    @Override
    public boolean allowsOrder() {
        return false;
    }

    @Override
    public int getPriority() {
        return BACKEND_PRIORITY_CPU;
    }

    @Override
    public Resource getConfigurationResource() {
        return new ClassPathResource(LINALG_PROPS, CpuBackend.class.getClassLoader());
    }

    @Override
    public Class getNDArrayClass() {
        return NDArray.class;
    }

    @Override
    public Environment getEnvironment() {
        return CpuEnvironment.getInstance();
    }

    @Override
    public String buildInfo() {
        StringBuilder sb = new StringBuilder();
        sb.append("PID: " + ProcessHandle.current().pid() + "\n");
        sb.append(Nd4j.getNativeOps().buildInfo());
        return sb.toString();
    }

    @Override
    public void logBackendInit() {
        String logInitProperty = System.getProperty(ND4JSystemProperties.LOG_INITIALIZATION, "true");
        boolean logInit = Boolean.parseBoolean(logInitProperty);

        if(logInit) {
            try {
                log.info("Backend build information:\n {} IP: {}", buildInfo(),ProcessHandle.current().pid());
            } catch (Throwable t) {
                log.debug("Error logging CPU backend ", t);
            }
        }
    }

}

