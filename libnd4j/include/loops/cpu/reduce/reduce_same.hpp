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
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See
 * the License for the specific language governing permissions and limitations
 * under the License.
 *
 * SPDX-License-Identifier: Apache-2.0
 ******************************************************************************/

//
//  @author raver119@gmail.com
//  @author Yurii Shyrma (iuriish@yahoo.com)
//
#include <helpers/ConstantTadHelper.h>
#include <helpers/Loops.h>
#include <helpers/OmpLaunchHelper.h>
#include <loops/legacy_ops.h>
#include <loops/reduce_same.h>
#include <system/op_boilerplate.h>
#include <types/types.h>

#include <chrono>

using namespace simdOps;

namespace functions {
namespace reduce {
template <typename X>
template <typename OpType>
void SD_HOST ReduceSameFunction<X>::execScalar(const void *vx, const sd::LongType *xShapeInfo, void *vextraParams,
                                               void *vz, const sd::LongType *zShapeInfo) {
  auto x = reinterpret_cast<const X *>(vx);
  auto z = reinterpret_cast<X *>(vz);
  auto extraParams = reinterpret_cast<X *>(vextraParams);

  const auto length = shape::length(xShapeInfo);

  if (shape::isEmptyConst(xShapeInfo)) {
    z[0] = OpType::startingValue(x);
    return;
  }

  if (sd::ArrayOptions::arrayType(xShapeInfo) == sd::ArrayType::EMPTY) {
    if (sd::ArrayOptions::arrayType(zShapeInfo) == sd::ArrayType::EMPTY) return;
    const auto startingVal = OpType::startingValue(x);

    for (sd::LongType i = 0; i < length; i++) {
      z[i] = startingVal;
    }
    return;
  }

  auto startingValue = OpType::startingValue(x);
  int maxThreads = sd::math::sd_min<int>(64, sd::Environment::getInstance().maxThreads());
  X intermediate[64];

  PRAGMA_OMP_SIMD
  for (auto e = 0; e < maxThreads; e++) {
    intermediate[e] = startingValue;
  }

  sd::LongType xRank = shape::rank(xShapeInfo);
  sd::LongType* xShape = shape::shapeOf(xShapeInfo);
  sd::LongType* xStride = shape::stride(xShapeInfo);
  if(shape::isViewConst(xShapeInfo)) {
    auto func = PRAGMA_THREADS_FOR {
      for (auto i = start; i < stop; i++) {
        sd::LongType coords[SD_MAX_RANK];
        INDEX2COORDS(i, xRank, xShape, coords);
        sd::LongType indexOffset;
        COORDS2INDEX(xRank, xStride, coords, indexOffset);
        intermediate[thread_id] = OpType::update(intermediate[thread_id], OpType::op(x[indexOffset], extraParams), extraParams);
      }
    };
    maxThreads = samediff::Threads::parallel_for(func, 0, length, 1, maxThreads);
    PRAGMA_OMP_SIMD
    for (int e = 1; e < maxThreads; e++) {
      intermediate[0] = OpType::update(intermediate[0], intermediate[e], extraParams);
    }

    z[0] = OpType::postProcess(intermediate[0], length, extraParams);
  } else {
    auto func = PRAGMA_THREADS_FOR {
      for (auto i = start; i < stop; i++) {
        intermediate[thread_id] = OpType::update(intermediate[thread_id], OpType::op(x[i], extraParams), extraParams);
      }
    };
    maxThreads = samediff::Threads::parallel_for(func, 0, length, 1, maxThreads);
    PRAGMA_OMP_SIMD
    for (int e = 1; e < maxThreads; e++) {
      intermediate[0] = OpType::update(intermediate[0], intermediate[e], extraParams);
    }

    z[0] = OpType::postProcess(intermediate[0], length, extraParams);
  }

}

template <typename X>
template <typename OpType>
X SD_HOST ReduceSameFunction<X>::execScalar(const void *vx, const sd::LongType *xShapeInfo, void *vextraParams) {
  auto x = reinterpret_cast<const X *>(vx);
  auto extraParams = reinterpret_cast<X *>(vextraParams);

  const sd::LongType length = shape::length(xShapeInfo);

  if (shape::isEmptyConst(xShapeInfo)) {
    return OpType::startingValue(x);
  }

  auto startingValue = OpType::startingValue(x);
  sd::LongType xRank = shape::rank(xShapeInfo);
  sd::LongType* xShape = shape::shapeOf(xShapeInfo);
  sd::LongType* xStride = shape::stride(xShapeInfo);

  for (sd::LongType i = 0; i < length; i++) {
    sd::LongType coords[SD_MAX_RANK];
    INDEX2COORDS(i, xRank, xShape, coords);
    sd::LongType indexOffset;
    COORDS2INDEX(xRank, xStride, coords, indexOffset);
    startingValue = OpType::update(startingValue, OpType::op(x[indexOffset], extraParams), extraParams);
  }
  return OpType::postProcess(startingValue, length, extraParams);
}

template <typename X>
X ReduceSameFunction<X>::execScalar(const int opNum, const void *x, const sd::LongType *xShapeInfo, void *extraParams) {
  RETURNING_DISPATCH_BY_OPNUM_T(execScalar, PARAMS(x, xShapeInfo, extraParams), REDUCE_SAME_OPS);
}

template <typename X>
void ReduceSameFunction<X>::execScalar(const int opNum, const void *x, const sd::LongType *xShapeInfo,
                                       void *extraParams, void *z, const sd::LongType *zShapeInfo) {
  DISPATCH_BY_OPNUM_T(execScalar, PARAMS(x, xShapeInfo, extraParams, z, zShapeInfo), REDUCE_SAME_OPS);
}

template <typename X>
template <typename OpType>
void SD_HOST ReduceSameFunction<X>::exec(const void *x, const sd::LongType *xShapeInfo, void *extraParams, void *vz,
                                         const sd::LongType *zShapeInfo) {
  auto z = reinterpret_cast<X *>(vz);
  z[0] = execScalar<OpType>(x, xShapeInfo, extraParams);
}

template <typename X>
template <typename OpType>
void SD_HOST ReduceSameFunction<X>::exec(sd::memory::Workspace *workspace, const void *vx,
                                         const sd::LongType *xShapeInfo, void *vextraParams, void *vz,
                                         const sd::LongType *zShapeInfo, const sd::LongType *dims) {
  const X *x = reinterpret_cast<const X *>(vx);
  X *z = reinterpret_cast<X *>(vz);
  X *extraParams = reinterpret_cast<X *>(vextraParams);

  const sd::LongType xRank = shape::rank(xShapeInfo);
  const sd::LongType zRank = shape::rank(zShapeInfo);

  if (sd::ArrayOptions::arrayType(xShapeInfo) == sd::ArrayType::EMPTY) {
    const auto startingVal = OpType::startingValue(x);
    const auto zLen = shape::length(zShapeInfo);
    if (z != nullptr) {
      for (sd::LongType i = 0; i < zLen; i++) {
        z[i] = startingVal;
      }
    }
    return;
  }

  if (shape::length(zShapeInfo) == 1) {
    z[0] = execScalar<OpType>(x, xShapeInfo, extraParams);
    return;
  }

  if (OpType::requiresSpecialAccumulation) {
    OpType::execSpecial(x, xShapeInfo, extraParams, z, zShapeInfo, const_cast<sd::LongType *>(dims) + zRank,
                        xRank - zRank, nullptr, nullptr);
    return;
  }

#ifdef SD_LOOPS_INLINED
  sd::ReductionLoops<X, X, X>::template loopReduce<OpType>(workspace, x, xShapeInfo, z, zShapeInfo, dims, extraParams);
#else
  sd::ReductionSameLoops<X>::template innerloopReduce<OpType>(workspace, x, xShapeInfo, z, zShapeInfo, dims, extraParams);
#endif
}

template <typename X>
void ReduceSameFunction<X>::exec(int opNum, sd::memory::Workspace *workspace, const void *vx,
                                 const sd::LongType *xShapeInfo, void *vextraParams, void *vz,
                                 const sd::LongType *zShapeInfo, const sd::LongType *dims) {
  DISPATCH_BY_OPNUM_T(exec, PARAMS(workspace, vx, xShapeInfo, vextraParams, vz, zShapeInfo, dims), REDUCE_SAME_OPS);
}
}  // namespace reduce
}  // namespace functions
