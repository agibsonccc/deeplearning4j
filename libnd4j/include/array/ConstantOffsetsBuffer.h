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
// @author raver119@gmail.com
//

#ifndef SD_ARRAY_CONSTANTOFFSETSBUFFER_H_
#define SD_ARRAY_CONSTANTOFFSETSBUFFER_H_

#include <array/PointerWrapper.h>
#include <system/common.h>

#include <memory>

namespace sd {

class SD_LIB_EXPORT ConstantOffsetsBuffer {
 private:
  std::shared_ptr<PointerWrapper> _primaryOffsets;
  std::shared_ptr<PointerWrapper> _specialOffsets;

 public:
  ConstantOffsetsBuffer(const std::shared_ptr<PointerWrapper> &primary);
  ConstantOffsetsBuffer(const std::shared_ptr<PointerWrapper> &primary, const std::shared_ptr<PointerWrapper> &special);
  ConstantOffsetsBuffer() = default;
  ~ConstantOffsetsBuffer() = default;

  LongType *primary();
  LongType *special();
  LongType *platform();
};

}  // namespace sd

#endif  // SD_ARRAY_CONSTANTOFFSETSBUFFER_H_
