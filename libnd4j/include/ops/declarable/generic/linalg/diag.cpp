/* ******************************************************************************
 *
 *
 * This program and the accompanying materials are made available under the
 * terms of the Apache License, Version 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 *
 *  See the NOTICE file distributed with this work for additional
 *  information regarding copyright ownership.
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 * SPDX-License-Identifier: Apache-2.0
 ******************************************************************************/

//
// @author Yurii Shyrma (iuriish@yahoo.com), created on 06.12.2017
//

#include <system/op_boilerplate.h>
#if NOT_EXCLUDED(OP_diag)

#include <ops/declarable/CustomOperations.h>
#include <ops/declarable/helpers/diag.h>

namespace sd {
namespace ops {

//////////////////////////////////////////////////////////////////////////
CUSTOM_OP_IMPL(diag, 1, 1, false, 0, 0) {
  auto input = INPUT_VARIABLE(0);
  auto output = OUTPUT_VARIABLE(0);

  // input validation
  REQUIRE_TRUE(input->rankOf() <= 3, 0, "CUSTOM_OP diag: rank of input array must be <= 3 !, but got %i instead",
               input->rankOf());
  int zero = 0;
  output->assign(zero);

  helpers::diagFunctor(block.launchContext(), input, output);

  return Status::OK;
}

DECLARE_SYN(MatrixDiag, diag);

DECLARE_TYPES(diag) { getOpDescriptor()->setAllowedInputTypes(ANY)->setSameMode(true); }

//////////////////////////////////////////////////////////////////////////
DECLARE_SHAPE_FN(diag) {
  LongType* inputShapeInfo = inputShape->at(0);

  return SHAPELIST(ShapeUtils::evalDiagShapeInfo(inputShapeInfo, block.workspace()));
}

}  // namespace ops
}  // namespace sd

#endif
