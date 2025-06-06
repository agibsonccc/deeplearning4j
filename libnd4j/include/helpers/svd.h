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
// Created by Yurii Shyrma on 03.01.2018
//

#ifndef LIBND4J_SVD_H
#define LIBND4J_SVD_H
#include <helpers/hhSequence.h>

#include "array/NDArray.h"

namespace sd {
namespace ops {
namespace helpers {

template <typename T>
class SVD {
 public:
  int _switchSize = 10;

  NDArray _m;
  NDArray _s;
  NDArray _u;
  NDArray _v;

  int _diagSize;

  bool _transp;
  bool _calcU;
  bool _calcV;
  bool _fullUV;

  /**
   *  constructor
   */
  SVD(NDArray& matrix, const int switchSize, const bool calcV, const bool calcU, const bool fullUV);

  SVD(NDArray& matrix, const int switchSize, const bool calcV, const bool calcU, const bool fullUV, const char t);

  void deflation1(int col1, int shift, int ind, int size);

  void deflation2(int col1U, int col1M, int row1W, int col1W, int ind1, int ind2, int size);

  void deflation(int col1, int col2, int ind, int row1W, int col1W, int shift);

  // FIXME: proper T support required here
  T secularEq(const T diff, NDArray& col0, NDArray& diag, NDArray permut, NDArray& diagShifted,
              const T shift);

  void calcSingVals(NDArray col0, NDArray& diag, NDArray& permut, NDArray& singVals, NDArray& shifts,
                    NDArray& mus);

  void perturb(NDArray col0, NDArray& diag, NDArray permut, NDArray& singVals,
               NDArray& shifts, NDArray& mus, NDArray& zhat);

  void calcSingVecs(NDArray zhat, NDArray& diag, NDArray perm, NDArray& singVals,
                    NDArray& shifts, NDArray& mus, NDArray& U, NDArray& V);

  void calcBlockSVD(int firstCol, int size, NDArray& U, NDArray& singVals, NDArray& V);

  void DivideAndConquer(int col1, int col2, int row1W, int col1W, int shift);

  void exchangeUV(HHsequence& hhU, HHsequence& hhV, NDArray& U, NDArray& V);

  void evalData(NDArray& matrix);

  SD_INLINE NDArray& getS();
  SD_INLINE NDArray& getU();
  SD_INLINE NDArray& getV();
};

//////////////////////////////////////////////////////////////////////////
template <typename T>
SD_INLINE NDArray& SVD<T>::getS() {
  return _s;
}

//////////////////////////////////////////////////////////////////////////
template <typename T>
SD_INLINE NDArray& SVD<T>::getU() {
  return _u;
}

//////////////////////////////////////////////////////////////////////////
template <typename T>
SD_INLINE NDArray& SVD<T>::getV() {
  return _v;
}

}  // namespace helpers
}  // namespace ops
}  // namespace sd

#endif  // LIBND4J_SVD_H
