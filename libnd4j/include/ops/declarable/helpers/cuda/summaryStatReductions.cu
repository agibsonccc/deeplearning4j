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
// @author AbdelRauf (rauf@konduit.ai)
//
#include <helpers/ConstantTadHelper.h>
#include <legacy/NativeOpExecutioner.h>
#include <ops/declarable/helpers/reductions.h>
#include <system/op_enums.h>


namespace sd {
namespace ops {
namespace helpers {

//////////////////////////////////////////////////////////////////////////
void variance(NDArray& input, NDArray& output, const std::vector<LongType>& dimensions, bool biasCorrected) {
  // informs and prepares (syncs) specialBuffer of which NDArrays will be used as read, write.
  NDArray::prepareSpecialUse({&output}, {&input});
  if (output.isScalar()) {
    NativeOpExecutioner::execSummaryStatsScalar(LaunchContext::defaultContext(), variance::SummaryStatsVariance,
                                                input.buffer(), input.shapeInfo(), input.specialBuffer(),
                                                input.specialShapeInfo(), nullptr, output.buffer(), output.shapeInfo(),
                                                output.specialBuffer(), output.specialShapeInfo(), biasCorrected);
  } else {
    auto tadPack = ConstantTadHelper::getInstance().tadForDimensions(input.shapeInfo(), const_cast<sd::LongType *>(dimensions.data()),dimensions.size());

    NativeOpExecutioner::execSummaryStats(
        LaunchContext::defaultContext(), variance::SummaryStatsVariance, input.buffer(), input.shapeInfo(),
        input.specialBuffer(), input.specialShapeInfo(), nullptr, output.buffer(), output.shapeInfo(),
        output.specialBuffer(), output.specialShapeInfo(), (LongType*)nullptr, dimensions.size(), tadPack->specialShapeInfo(),
        tadPack->specialOffsets(), biasCorrected);
  }
  // inform that we are done with those specialBuffers. it matches arrays used in the prepareSpecialUse
  NDArray::registerSpecialUse({&output}, {&input});
}

//////////////////////////////////////////////////////////////////////////
void standardDeviation(NDArray& input, NDArray& output, const std::vector<LongType>& dimensions, bool biasCorrected) {
  // informs and prepares (syncs) of which NDArrays will be used as read, write
  NDArray::prepareSpecialUse({&output}, {&input});
  if (output.isScalar()) {
    NativeOpExecutioner::execSummaryStatsScalar(
        LaunchContext::defaultContext(), variance::SummaryStatsStandardDeviation, input.buffer(), input.shapeInfo(),
        input.specialBuffer(), input.specialShapeInfo(), nullptr, output.buffer(), output.shapeInfo(),
        output.specialBuffer(), output.specialShapeInfo(), biasCorrected);
  } else {
    auto tadPack = ConstantTadHelper::getInstance().tadForDimensions(input.shapeInfo(), const_cast<sd::LongType *>(dimensions.data()),dimensions.size());

    NativeOpExecutioner::execSummaryStats(
        LaunchContext::defaultContext(), variance::SummaryStatsStandardDeviation, input.buffer(), input.shapeInfo(),
        input.specialBuffer(), input.specialShapeInfo(), nullptr, output.buffer(), output.shapeInfo(),
        output.specialBuffer(), output.specialShapeInfo(), (LongType*)nullptr, dimensions.size(), tadPack->specialShapeInfo(),
        tadPack->specialOffsets(), biasCorrected);
  }
  // inform that we are done with those specialBuffers. it matches arrays used in the prepareSpecialUse
  NDArray::registerSpecialUse({&output}, {&input});
}

}  // namespace helpers
}  // namespace ops
}  // namespace sd
