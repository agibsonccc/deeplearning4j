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
// Created by raver119 on 06.11.2017.
//

#include <system/op_boilerplate.h>
#if NOT_EXCLUDED(OP_create_list)

#include <ops/declarable/CustomOperations.h>

namespace sd {
namespace ops {
LIST_OP_IMPL(create_list, -2, 2, 0, -2) {
  int height = 0;
  bool expandable = false;
  if (block.numI() == 2) {
    height = INT_ARG(0);
    expandable = (bool)INT_ARG(1);
  } else if (block.numI() == 1) {
    height = INT_ARG(0);
  } else if (block.width() == 1) {
    height = INPUT_VARIABLE(0)->e<int>(0);
    expandable = true;
  } else {
    height = 0;
    expandable = true;
  }




  auto list = new NDArrayList(height, expandable);
  // we receive input array for graph integrity purposes only
  //mainly a marker for now, representing the fixed shape the elements can be

  setupResultList(list, block);
  auto scalar = NDArrayFactory::create_(list->counter());
  block.pushNDArrayToVariableSpace(block.getNodeId(), 1, scalar);

  return Status::OK;
}
DECLARE_SYN(TensorArrayV3, create_list);
DECLARE_SYN(tensorarrayv3, create_list);
DECLARE_SYN(TensorArrayCreateV3, create_list);
DECLARE_SYN(tensorarraycreatev3, create_list);
}  // namespace ops
}  // namespace sd

#endif
