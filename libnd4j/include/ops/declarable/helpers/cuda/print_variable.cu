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
//  @author raver119@gmail.com
//
#include <helpers/PointersManager.h>
#include <ops/declarable/helpers/print_variable.h>

#include "execution/cuda/LaunchDims.h"


namespace sd {
namespace ops {
namespace helpers {
template <typename T>
static SD_KERNEL void print_device(const void *special, const LongType *shapeInfo) {
  __shared__ LongType length;
  __shared__ LongType rank;
  __shared__ const LongType *shape, *stride;
  const auto x = reinterpret_cast<const T *>(special);

  if (threadIdx.x == 0) {
    length = shape::length(shapeInfo);
    rank = shape::rank(shapeInfo);
    shape = shape::shapeOf(shapeInfo);
    stride = shape::stride(shapeInfo);
  }
  __syncthreads();

  if (threadIdx.x == 0 && blockIdx.x == 0) {
    printf("[");

    LongType coords[SD_MAX_RANK];
    LongType offset;

    for (LongType e = 0; e < length; e++) {
      INDEX2COORDS(e, rank, shape, coords);
      COORDS2INDEX(rank, stride, coords, offset);

      printf("%f", static_cast<float>(x[offset]));
      if (e < length - 1) printf(", ");
    }

    printf("]\n");
  }
}


template <typename T>
static SD_HOST void exec_print_device(LaunchContext &ctx, const void *special, const LongType *shapeInfo) {
  dim3 launchDims = getLaunchDims("print");
  print_device<T><<<launchDims.x, launchDims.y, launchDims.z, *ctx.getCudaStream()>>>(special, shapeInfo);
  sd::DebugHelper::checkErrorCode(ctx.getCudaStream(), "print_device failed");

}

void print_special(LaunchContext &ctx, NDArray&array, const std::string &message) {
  NDArray::prepareSpecialUse({}, {&array});

  PointersManager pm(&ctx, "print_device");
  BUILD_SINGLE_SELECTOR(array.dataType(), exec_print_device, (ctx, array.specialBuffer(), array.specialShapeInfo()),
                        SD_COMMON_TYPES)
  pm.synchronize();

  NDArray::registerSpecialUse({}, {&array});
}
}  // namespace helpers
}  // namespace ops
}  // namespace sd
