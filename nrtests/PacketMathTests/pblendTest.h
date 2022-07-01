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
  /* float = Packet4f (half) */
  beginTest("4 float tests");
  {
    MIN2MAX_FLOAT_VECTOR_LOADED(4);

    allTwoPermRep(vectorHalfFloatTemplateTest, FUN2TEST, Packet4f COMMA selector4, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vectorHalfFloatTemplateTest, FUN2TEST, Packet4f COMMA selector4_max, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vectorHalfFloatTemplateTest, FUN2TEST, Packet4f COMMA selector4_pos, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vectorHalfFloatTemplateTest, FUN2TEST, Packet4f COMMA selector4_zero, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vectorHalfFloatTemplateTest, FUN2TEST, Packet4f COMMA selector4_neg, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vectorHalfFloatTemplateTest, FUN2TEST, Packet4f COMMA selector4_min, vmax, v36, v0, v_240, vmin);
  }
  endTest();

  /* double =  Packet2d (half) */
  beginTest("2 double tests");
  {
    MIN2MAX_DOUBLE_VECTOR_LOADED(2);

    allTwoPermRep(vectorHalfDoubleTemplateTest, FUN2TEST, Packet2d COMMA selector2, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vectorHalfDoubleTemplateTest, FUN2TEST, Packet2d COMMA selector2_max, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vectorHalfDoubleTemplateTest, FUN2TEST, Packet2d COMMA selector2_pos, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vectorHalfDoubleTemplateTest, FUN2TEST, Packet2d COMMA selector2_zero, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vectorHalfDoubleTemplateTest, FUN2TEST, Packet2d COMMA selector2_neg, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vectorHalfDoubleTemplateTest, FUN2TEST, Packet2d COMMA selector2_min, vmax, v36, v0, v_240, vmin);
  }
  endTest();

  /* int = Packet4i (half) */
  beginTest("4 int tests");
  {
    MIN2MAX_INT_VECTOR_LOADED(4);

    allTwoPermRep(vectorHalfIntTemplateTest, FUN2TEST, Packet4i COMMA selector4, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vectorHalfIntTemplateTest, FUN2TEST, Packet4i COMMA selector4_max, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vectorHalfIntTemplateTest, FUN2TEST, Packet4i COMMA selector4_pos, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vectorHalfIntTemplateTest, FUN2TEST, Packet4i COMMA selector4_zero, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vectorHalfIntTemplateTest, FUN2TEST, Packet4i COMMA selector4_neg, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vectorHalfIntTemplateTest, FUN2TEST, Packet4i COMMA selector4_min, vmax, v36, v0, v_240, vmin);
  }
  endTest();

  /* bool = Packet16b */
  beginTest("16 bool tests");
  {
    MIN2MAX_BOOL_VECTOR_LOADED(16);

    vectorHalfBoolTemplateTest(FUN2TEST, Packet16b, selector16, bvtrue, bvtrue);
    vectorHalfBoolTemplateTest(FUN2TEST, Packet16b, selector16, bvtrue, bvfalse);
    vectorHalfBoolTemplateTest(FUN2TEST, Packet16b, selector16, bvfalse, bvtrue);
    vectorHalfBoolTemplateTest(FUN2TEST, Packet16b, selector16, bvfalse, bvfalse);

    vectorHalfBoolTemplateTest(FUN2TEST, Packet16b, selector16_max, bvtrue, bvtrue);
    vectorHalfBoolTemplateTest(FUN2TEST, Packet16b, selector16_max, bvtrue, bvfalse);
    vectorHalfBoolTemplateTest(FUN2TEST, Packet16b, selector16_max, bvfalse, bvtrue);
    vectorHalfBoolTemplateTest(FUN2TEST, Packet16b, selector16_max, bvfalse, bvfalse);

    vectorHalfBoolTemplateTest(FUN2TEST, Packet16b, selector16_pos, bvtrue, bvtrue);
    vectorHalfBoolTemplateTest(FUN2TEST, Packet16b, selector16_pos, bvtrue, bvfalse);
    vectorHalfBoolTemplateTest(FUN2TEST, Packet16b, selector16_pos, bvfalse, bvtrue);
    vectorHalfBoolTemplateTest(FUN2TEST, Packet16b, selector16_pos, bvfalse, bvfalse);

    vectorHalfBoolTemplateTest(FUN2TEST, Packet16b, selector16_zero, bvtrue, bvtrue);
    vectorHalfBoolTemplateTest(FUN2TEST, Packet16b, selector16_zero, bvtrue, bvfalse);
    vectorHalfBoolTemplateTest(FUN2TEST, Packet16b, selector16_zero, bvfalse, bvtrue);
    vectorHalfBoolTemplateTest(FUN2TEST, Packet16b, selector16_zero, bvfalse, bvfalse);

    vectorHalfBoolTemplateTest(FUN2TEST, Packet16b, selector16_neg, bvtrue, bvtrue);
    vectorHalfBoolTemplateTest(FUN2TEST, Packet16b, selector16_neg, bvtrue, bvfalse);
    vectorHalfBoolTemplateTest(FUN2TEST, Packet16b, selector16_neg, bvfalse, bvtrue);
    vectorHalfBoolTemplateTest(FUN2TEST, Packet16b, selector16_neg, bvfalse, bvfalse);

    vectorHalfBoolTemplateTest(FUN2TEST, Packet16b, selector16_min, bvtrue, bvtrue);
    vectorHalfBoolTemplateTest(FUN2TEST, Packet16b, selector16_min, bvtrue, bvfalse);
    vectorHalfBoolTemplateTest(FUN2TEST, Packet16b, selector16_min, bvfalse, bvtrue);
    vectorHalfBoolTemplateTest(FUN2TEST, Packet16b, selector16_min, bvfalse, bvfalse);
  }
  endTest();

#endif

#ifdef __AVX__
  /* float = Packet8f (full) */
  beginTest("8 float tests");
  {
    MIN2MAX_FLOAT_VECTOR_LOADED(8);

    allTwoPermRep(vectorFullFloatTemplateTest, FUN2TEST, Packet8f COMMA selector8, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vectorFullFloatTemplateTest, FUN2TEST, Packet8f COMMA selector8_max, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vectorFullFloatTemplateTest, FUN2TEST, Packet8f COMMA selector8_pos, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vectorFullFloatTemplateTest, FUN2TEST, Packet8f COMMA selector8_zero, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vectorFullFloatTemplateTest, FUN2TEST, Packet8f COMMA selector8_neg, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vectorFullFloatTemplateTest, FUN2TEST, Packet8f COMMA selector8_min, vmax, v36, v0, v_240, vmin);
  }
  endTest();

  /* double = Packet4d (full) */
  beginTest("4 double tests");
  {
    MIN2MAX_DOUBLE_VECTOR_LOADED(4);

    allTwoPermRep(vectorFullDoubleTemplateTest, FUN2TEST, Packet4d COMMA selector4, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vectorFullDoubleTemplateTest, FUN2TEST, Packet4d COMMA selector4_max, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vectorFullDoubleTemplateTest, FUN2TEST, Packet4d COMMA selector4_pos, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vectorFullDoubleTemplateTest, FUN2TEST, Packet4d COMMA selector4_zero, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vectorFullDoubleTemplateTest, FUN2TEST, Packet4d COMMA selector4_neg, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vectorFullDoubleTemplateTest, FUN2TEST, Packet4d COMMA selector4_min, vmax, v36, v0, v_240, vmin);
  }
  endTest();

  /* int = Packet8i (full) */
  beginTest("8 int tests");
  {
    MIN2MAX_INT_VECTOR_LOADED(8);

    allTwoPermRep(vectorFullIntTemplateTest, FUN2TEST, Packet8i COMMA selector8, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vectorFullIntTemplateTest, FUN2TEST, Packet8i COMMA selector8_max, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vectorFullIntTemplateTest, FUN2TEST, Packet8i COMMA selector8_pos, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vectorFullIntTemplateTest, FUN2TEST, Packet8i COMMA selector8_zero, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vectorFullIntTemplateTest, FUN2TEST, Packet8i COMMA selector8_neg, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vectorFullIntTemplateTest, FUN2TEST, Packet8i COMMA selector8_min, vmax, v36, v0, v_240, vmin);
  }
  endTest();

  /* Eigen::half = Packet8h */
  beginTest("8 Eigen::half tests");
  {
    MIN2MAX_HALF_VECTOR_LOADED(8);

    allTwoPermRep(vectorHalfEigenHalfTemplateTest, FUN2TEST, Packet8h COMMA selector8, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vectorHalfEigenHalfTemplateTest, FUN2TEST, Packet8h COMMA selector8_max, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vectorHalfEigenHalfTemplateTest, FUN2TEST, Packet8h COMMA selector8_pos, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vectorHalfEigenHalfTemplateTest, FUN2TEST, Packet8h COMMA selector8_zero, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vectorHalfEigenHalfTemplateTest, FUN2TEST, Packet8h COMMA selector8_neg, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vectorHalfEigenHalfTemplateTest, FUN2TEST, Packet8h COMMA selector8_min, vmax, v36, v0, v_240, vmin);
  }
  endTest();

  /* bfloat16 = Packet8bf */
  beginTest("8 bfloat16 tests");
  {
    MIN2MAX_BFLOAT16_VECTOR_LOADED(8);

    allTwoPermRep(vectorHalfBfloat16TemplateTest, FUN2TEST, Packet8bf COMMA selector8, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vectorHalfBfloat16TemplateTest, FUN2TEST, Packet8bf COMMA selector8_max, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vectorHalfBfloat16TemplateTest, FUN2TEST, Packet8bf COMMA selector8_pos, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vectorHalfBfloat16TemplateTest, FUN2TEST, Packet8bf COMMA selector8_zero, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vectorHalfBfloat16TemplateTest, FUN2TEST, Packet8bf COMMA selector8_neg, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vectorHalfBfloat16TemplateTest, FUN2TEST, Packet8bf COMMA selector8_min, vmax, v36, v0, v_240, vmin);
  }
  endTest();

#endif

#ifdef __AVX2__
  /* long = Packet4l */
  beginTest("4 long tests");
  {
    MIN2MAX_LONG_VECTOR_LOADED(4);

    allTwoPermRep(vectorFullLongTemplateTest, FUN2TEST, Packet4l COMMA selector4, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vectorFullLongTemplateTest, FUN2TEST, Packet4l COMMA selector4_max, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vectorFullLongTemplateTest, FUN2TEST, Packet4l COMMA selector4_pos, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vectorFullLongTemplateTest, FUN2TEST, Packet4l COMMA selector4_zero, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vectorFullLongTemplateTest, FUN2TEST, Packet4l COMMA selector4_neg, vmax, v36, v0, v_240, vmin);
    allTwoPermRep(vectorFullLongTemplateTest, FUN2TEST, Packet4l COMMA selector4_min, vmax, v36, v0, v_240, vmin);
  }
  endTest();

#endif

#ifdef __AVX512F__
#endif
}

addTest(FUN2TEST)

#endif  // EIGEN_MIPP_PBLEND_TEST_H
