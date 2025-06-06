/*
 *  ******************************************************************************
 *  *
 *  *
 *  * This program and the accompanying materials are made available under the
 *  * terms of the Apache License, Version 2.0 which is available at
 *  * https://www.apache.org/licenses/LICENSE-2.0.
 *  *
 *  * See the NOTICE file distributed with this work for additional
 *  * information regarding copyright ownership.
 *  * Unless required by applicable law or agreed to in writing, software
 *  * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 *  * License for the specific language governing permissions and limitations
 *  * under the License.
 *  *
 *  * SPDX-License-Identifier: Apache-2.0
 *  *****************************************************************************
 */

//
//  @author GS <sgazeos@gmail.com>
//
#ifndef __TRIANGULAR_SOLVE__H_HELPERS__
#define __TRIANGULAR_SOLVE__H_HELPERS__
#include <array/NDArray.h>
#include <system/op_boilerplate.h>

namespace sd {
namespace ops {
namespace helpers {

SD_LIB_HIDDEN Status triangularSolveFunctor(LaunchContext* context, NDArray* leftInput, NDArray* rightInput,
                                                bool lower, bool unitsOnDiag, NDArray* output);
template <typename T>
SD_LIB_HIDDEN void triangularSolve2D(LaunchContext* context, NDArray& leftInput, NDArray& rightInput,
                                     const bool lower, const bool unitsOnDiag, NDArray& output);
SD_LIB_HIDDEN void adjointMatrix(LaunchContext* context, NDArray * input, bool const lower, NDArray* output);
}  // namespace helpers
}  // namespace ops
}  // namespace sd
#endif
