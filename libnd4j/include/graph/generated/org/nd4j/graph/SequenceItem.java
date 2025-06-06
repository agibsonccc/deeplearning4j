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
public final class SequenceItem extends Table {
  public static void ValidateVersion() { Constants.FLATBUFFERS_25_2_10(); }
  public static SequenceItem getRootAsSequenceItem(ByteBuffer _bb) { return getRootAsSequenceItem(_bb, new SequenceItem()); }
  public static SequenceItem getRootAsSequenceItem(ByteBuffer _bb, SequenceItem obj) { _bb.order(ByteOrder.LITTLE_ENDIAN); return (obj.__assign(_bb.getInt(_bb.position()) + _bb.position(), _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __reset(_i, _bb); }
  public SequenceItem __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public String name() { int o = __offset(4); return o != 0 ? __string(o + bb_pos) : null; }
  public ByteBuffer nameAsByteBuffer() { return __vector_as_bytebuffer(4, 1); }
  public ByteBuffer nameInByteBuffer(ByteBuffer _bb) { return __vector_in_bytebuffer(_bb, 4, 1); }
  public org.nd4j.graph.FlatArray associatedVariable(int j) { return associatedVariable(new org.nd4j.graph.FlatArray(), j); }
  public org.nd4j.graph.FlatArray associatedVariable(org.nd4j.graph.FlatArray obj, int j) { int o = __offset(6); return o != 0 ? obj.__assign(__indirect(__vector(o) + j * 4), bb) : null; }
  public int associatedVariableLength() { int o = __offset(6); return o != 0 ? __vector_len(o) : 0; }
  public org.nd4j.graph.FlatArray.Vector associatedVariableVector() { return associatedVariableVector(new org.nd4j.graph.FlatArray.Vector()); }
  public org.nd4j.graph.FlatArray.Vector associatedVariableVector(org.nd4j.graph.FlatArray.Vector obj) { int o = __offset(6); return o != 0 ? obj.__assign(__vector(o), 4, bb) : null; }

  public static int createSequenceItem(FlatBufferBuilder builder,
      int nameOffset,
      int associatedVariableOffset) {
    builder.startTable(2);
    SequenceItem.addAssociatedVariable(builder, associatedVariableOffset);
    SequenceItem.addName(builder, nameOffset);
    return SequenceItem.endSequenceItem(builder);
  }

  public static void startSequenceItem(FlatBufferBuilder builder) { builder.startTable(2); }
  public static void addName(FlatBufferBuilder builder, int nameOffset) { builder.addOffset(0, nameOffset, 0); }
  public static void addAssociatedVariable(FlatBufferBuilder builder, int associatedVariableOffset) { builder.addOffset(1, associatedVariableOffset, 0); }
  public static int createAssociatedVariableVector(FlatBufferBuilder builder, int[] data) { builder.startVector(4, data.length, 4); for (int i = data.length - 1; i >= 0; i--) builder.addOffset(data[i]); return builder.endVector(); }
  public static void startAssociatedVariableVector(FlatBufferBuilder builder, int numElems) { builder.startVector(4, numElems, 4); }
  public static int endSequenceItem(FlatBufferBuilder builder) {
    int o = builder.endTable();
    return o;
  }

  public static final class Vector extends BaseVector {
    public Vector __assign(int _vector, int _element_size, ByteBuffer _bb) { __reset(_vector, _element_size, _bb); return this; }

    public SequenceItem get(int j) { return get(new SequenceItem(), j); }
    public SequenceItem get(SequenceItem obj, int j) {  return obj.__assign(__indirect(__element(j), bb), bb); }
  }
}

