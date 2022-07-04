#include <float.h>
#include <limits.h>

#ifndef EIGEN_MIPP_PBLEND_TEST_H
#define EIGEN_MIPP_PBLEND_TEST_H

#undef FUN2TEST
#define FUN2TEST pblend

#define selectorNum(PacketSize)                        \
  internal::Selector<PacketSize> selector##PacketSize; \
  for (int i = 0; i < PacketSize; ++i) selector##PacketSize.select[i] = i;

#define selectorFixVal(PacketSize, val, name)                   \
  internal::Selector<PacketSize> selector##PacketSize##_##name; \
  for (int i = 0; i < PacketSize; ++i) selector##PacketSize##_##name.select[i] = val;

void pblendTests() {
  printTestTitle(FUN2TEST);

  selectorNum(2);
  selectorNum(4);
  selectorNum(8);
  selectorNum(16);

  selectorFixVal(2, INT_MAX, max);
  selectorFixVal(4, INT_MAX, max);
  selectorFixVal(8, INT_MAX, max);
  selectorFixVal(16, INT_MAX, max);

  selectorFixVal(2, 36, pos);
  selectorFixVal(4, 36, pos);
  selectorFixVal(8, 36, pos);
  selectorFixVal(16, 36, pos);

  selectorFixVal(2, 0, zero);
  selectorFixVal(4, 0, zero);
  selectorFixVal(8, 0, zero);
  selectorFixVal(16, 0, zero);

  selectorFixVal(2, -240, neg);
  selectorFixVal(4, -240, neg);
  selectorFixVal(8, -240, neg);
  selectorFixVal(16, -240, neg);

  selectorFixVal(2, INT_MIN, min);
  selectorFixVal(4, INT_MIN, min);
  selectorFixVal(8, INT_MIN, min);
  selectorFixVal(16, INT_MIN, min);

#ifdef __SSE__
  // Packet4f (128)
  beginTest("4 float tests");
  {
    MIN2MAX_FLOAT_VECTOR_LOADED(4);

    allTwoPermRep(vector128FloatTest, FUN2TEST, Packet4f COMMA selector4, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vector128FloatTest, FUN2TEST, Packet4f COMMA selector4_max, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vector128FloatTest, FUN2TEST, Packet4f COMMA selector4_pos, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vector128FloatTest, FUN2TEST, Packet4f COMMA selector4_zero, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vector128FloatTest, FUN2TEST, Packet4f COMMA selector4_neg, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vector128FloatTest, FUN2TEST, Packet4f COMMA selector4_min, vmax, v36, v0, v_240, vmin);
  }
  endTest();

  // Packet2d (128)
  beginTest("2 double tests");
  {
    MIN2MAX_DOUBLE_VECTOR_LOADED(2);

    allTwoPermRep(vector128DoubleTest, FUN2TEST, Packet2d COMMA selector2, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vector128DoubleTest, FUN2TEST, Packet2d COMMA selector2_max, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vector128DoubleTest, FUN2TEST, Packet2d COMMA selector2_pos, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vector128DoubleTest, FUN2TEST, Packet2d COMMA selector2_zero, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vector128DoubleTest, FUN2TEST, Packet2d COMMA selector2_neg, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vector128DoubleTest, FUN2TEST, Packet2d COMMA selector2_min, vmax, v36, v0, v_240, vmin);
  }
  endTest();

  // Packet4i (128)
  beginTest("4 int tests");
  {
    MIN2MAX_INT_VECTOR_LOADED(4);

    allTwoPermRep(vector128IntTest, FUN2TEST, Packet4i COMMA selector4, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vector128IntTest, FUN2TEST, Packet4i COMMA selector4_max, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vector128IntTest, FUN2TEST, Packet4i COMMA selector4_pos, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vector128IntTest, FUN2TEST, Packet4i COMMA selector4_zero, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vector128IntTest, FUN2TEST, Packet4i COMMA selector4_neg, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vector128IntTest, FUN2TEST, Packet4i COMMA selector4_min, vmax, v36, v0, v_240, vmin);
  }
  endTest();

  // Packet16b (128)
  beginTest("16 bool tests");
  {
    BOOL_VECTOR_LOADED(16);

    vector128BoolTest(FUN2TEST, Packet16b, selector16, vtrue, vtrue);
    vector128BoolTest(FUN2TEST, Packet16b, selector16, vtrue, vfalse);
    vector128BoolTest(FUN2TEST, Packet16b, selector16, vfalse, vtrue);
    vector128BoolTest(FUN2TEST, Packet16b, selector16, vfalse, vfalse);

    vector128BoolTest(FUN2TEST, Packet16b, selector16_max, vtrue, vtrue);
    vector128BoolTest(FUN2TEST, Packet16b, selector16_max, vtrue, vfalse);
    vector128BoolTest(FUN2TEST, Packet16b, selector16_max, vfalse, vtrue);
    vector128BoolTest(FUN2TEST, Packet16b, selector16_max, vfalse, vfalse);

    vector128BoolTest(FUN2TEST, Packet16b, selector16_pos, vtrue, vtrue);
    vector128BoolTest(FUN2TEST, Packet16b, selector16_pos, vtrue, vfalse);
    vector128BoolTest(FUN2TEST, Packet16b, selector16_pos, vfalse, vtrue);
    vector128BoolTest(FUN2TEST, Packet16b, selector16_pos, vfalse, vfalse);

    vector128BoolTest(FUN2TEST, Packet16b, selector16_zero, vtrue, vtrue);
    vector128BoolTest(FUN2TEST, Packet16b, selector16_zero, vtrue, vfalse);
    vector128BoolTest(FUN2TEST, Packet16b, selector16_zero, vfalse, vtrue);
    vector128BoolTest(FUN2TEST, Packet16b, selector16_zero, vfalse, vfalse);

    vector128BoolTest(FUN2TEST, Packet16b, selector16_neg, vtrue, vtrue);
    vector128BoolTest(FUN2TEST, Packet16b, selector16_neg, vtrue, vfalse);
    vector128BoolTest(FUN2TEST, Packet16b, selector16_neg, vfalse, vtrue);
    vector128BoolTest(FUN2TEST, Packet16b, selector16_neg, vfalse, vfalse);

    vector128BoolTest(FUN2TEST, Packet16b, selector16_min, vtrue, vtrue);
    vector128BoolTest(FUN2TEST, Packet16b, selector16_min, vtrue, vfalse);
    vector128BoolTest(FUN2TEST, Packet16b, selector16_min, vfalse, vtrue);
    vector128BoolTest(FUN2TEST, Packet16b, selector16_min, vfalse, vfalse);
  }
  endTest();

#endif

#ifdef __AVX__
  // Packet8f (256)
  beginTest("8 float tests");
  {
    MIN2MAX_FLOAT_VECTOR_LOADED(8);

    allTwoPermRep(vector256FloatTest, FUN2TEST, Packet8f COMMA selector8, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vector256FloatTest, FUN2TEST, Packet8f COMMA selector8_max, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vector256FloatTest, FUN2TEST, Packet8f COMMA selector8_pos, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vector256FloatTest, FUN2TEST, Packet8f COMMA selector8_zero, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vector256FloatTest, FUN2TEST, Packet8f COMMA selector8_neg, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vector256FloatTest, FUN2TEST, Packet8f COMMA selector8_min, vmax, v36, v0, v_240, vmin);
  }
  endTest();

  // Packet4d (256)
  beginTest("4 double tests");
  {
    MIN2MAX_DOUBLE_VECTOR_LOADED(4);

    allTwoPermRep(vector256DoubleTest, FUN2TEST, Packet4d COMMA selector4, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vector256DoubleTest, FUN2TEST, Packet4d COMMA selector4_max, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vector256DoubleTest, FUN2TEST, Packet4d COMMA selector4_pos, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vector256DoubleTest, FUN2TEST, Packet4d COMMA selector4_zero, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vector256DoubleTest, FUN2TEST, Packet4d COMMA selector4_neg, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vector256DoubleTest, FUN2TEST, Packet4d COMMA selector4_min, vmax, v36, v0, v_240, vmin);
  }
  endTest();

  // Packet8i (256)
  beginTest("8 int tests");
  {
    MIN2MAX_INT_VECTOR_LOADED(8);

    allTwoPermRep(vector256IntTest, FUN2TEST, Packet8i COMMA selector8, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vector256IntTest, FUN2TEST, Packet8i COMMA selector8_max, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vector256IntTest, FUN2TEST, Packet8i COMMA selector8_pos, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vector256IntTest, FUN2TEST, Packet8i COMMA selector8_zero, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vector256IntTest, FUN2TEST, Packet8i COMMA selector8_neg, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vector256IntTest, FUN2TEST, Packet8i COMMA selector8_min, vmax, v36, v0, v_240, vmin);
  }
  endTest();

  // Packet8h (128)
  beginTest("8 Eigen::half tests");
  {
    MIN2MAX_HALF_VECTOR_LOADED(8);

    allTwoPermRep(vector128EigenHalfTest, FUN2TEST, Packet8h COMMA selector8, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vector128EigenHalfTest, FUN2TEST, Packet8h COMMA selector8_max, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vector128EigenHalfTest, FUN2TEST, Packet8h COMMA selector8_pos, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vector128EigenHalfTest, FUN2TEST, Packet8h COMMA selector8_zero, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vector128EigenHalfTest, FUN2TEST, Packet8h COMMA selector8_neg, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vector128EigenHalfTest, FUN2TEST, Packet8h COMMA selector8_min, vmax, v36, v0, v_240, vmin);
  }
  endTest();

  // Packet8bf (128) bfloat16
  beginTest("8 bfloat16 tests");
  {
    MIN2MAX_BFLOAT16_VECTOR_LOADED(8);

    allTwoPermRep(vector128Bfloat16Test, FUN2TEST, Packet8bf COMMA selector8, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vector128Bfloat16Test, FUN2TEST, Packet8bf COMMA selector8_max, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vector128Bfloat16Test, FUN2TEST, Packet8bf COMMA selector8_pos, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vector128Bfloat16Test, FUN2TEST, Packet8bf COMMA selector8_zero, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vector128Bfloat16Test, FUN2TEST, Packet8bf COMMA selector8_neg, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vector128Bfloat16Test, FUN2TEST, Packet8bf COMMA selector8_min, vmax, v36, v0, v_240, vmin);
  }
  endTest();

#endif

#ifdef __AVX2__
  // Packet4l (256)
  beginTest("4 long tests");
  {
    MIN2MAX_LONG_VECTOR_LOADED(4);

    allTwoPermRep(vector256LongTest, FUN2TEST, Packet4l COMMA selector4, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vector256LongTest, FUN2TEST, Packet4l COMMA selector4_max, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vector256LongTest, FUN2TEST, Packet4l COMMA selector4_pos, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vector256LongTest, FUN2TEST, Packet4l COMMA selector4_zero, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vector256LongTest, FUN2TEST, Packet4l COMMA selector4_neg, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vector256LongTest, FUN2TEST, Packet4l COMMA selector4_min, vmax, v36, v0, v_240, vmin);
  }
  endTest();

#endif

#ifdef __AVX512F__
#endif
}

addTest(FUN2TEST)

#endif  // EIGEN_MIPP_PBLEND_TEST_H
