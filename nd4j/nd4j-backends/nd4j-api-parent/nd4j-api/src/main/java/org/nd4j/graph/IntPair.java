/*
 * ******************************************************************************
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


// automatically generated by the FlatBuffers compiler, do not modify

package org.nd4j.graph;

import com.google.flatbuffers.BaseVector;
import com.google.flatbuffers.BooleanVector;
import com.google.flatbuffers.ByteVector;
import com.google.flatbuffers.Constants;
import com.google.flatbuffers.DoubleVector;
import com.google.flatbuffers.FlatBufferBuilder;
import com.google.flatbuffers.FloatVector;
import com.google.flatbuffers.IntVector;
import com.google.flatbuffers.LongVector;
import com.google.flatbuffers.ShortVector;
import com.google.flatbuffers.StringVector;
import com.google.flatbuffers.Struct;
import com.google.flatbuffers.Table;
import com.google.flatbuffers.UnionVector;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;

@SuppressWarnings("unused")
public final class IntPair extends Table {
  public static void ValidateVersion() { Constants.FLATBUFFERS_25_2_10(); }
  public static IntPair getRootAsIntPair(ByteBuffer _bb) { return getRootAsIntPair(_bb, new IntPair()); }
  public static IntPair getRootAsIntPair(ByteBuffer _bb, IntPair obj) { _bb.order(ByteOrder.LITTLE_ENDIAN); return (obj.__assign(_bb.getInt(_bb.position()) + _bb.position(), _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __reset(_i, _bb); }
  public IntPair __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public int first() { int o = __offset(4); return o != 0 ? bb.getInt(o + bb_pos) : 0; }
  public int second() { int o = __offset(6); return o != 0 ? bb.getInt(o + bb_pos) : 0; }

  public static int createIntPair(FlatBufferBuilder builder,
      int first,
      int second) {
    builder.startTable(2);
    IntPair.addSecond(builder, second);
    IntPair.addFirst(builder, first);
    return IntPair.endIntPair(builder);
  }

  public static void startIntPair(FlatBufferBuilder builder) { builder.startTable(2); }
  public static void addFirst(FlatBufferBuilder builder, int first) { builder.addInt(0, first, 0); }
  public static void addSecond(FlatBufferBuilder builder, int second) { builder.addInt(1, second, 0); }
  public static int endIntPair(FlatBufferBuilder builder) {
    int o = builder.endTable();
    return o;
  }

  public static final class Vector extends BaseVector {
    public Vector __assign(int _vector, int _element_size, ByteBuffer _bb) { __reset(_vector, _element_size, _bb); return this; }

    public IntPair get(int j) { return get(new IntPair(), j); }
    public IntPair get(IntPair obj, int j) {  return obj.__assign(__indirect(__element(j), bb), bb); }
  }
}

