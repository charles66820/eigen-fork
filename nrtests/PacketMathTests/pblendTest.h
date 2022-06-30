#include <float.h>
#include <limits.h>

#ifndef EIGEN_MIPP_PBLEND_TEST_H
#define EIGEN_MIPP_PBLEND_TEST_H

#undef FUN2TEST
#define FUN2TEST pblend

#define COMMA ,

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

  MIN2MAX_4_FLOAT_VECTOR_LOADED

  allTwoPermRep(vectorHalfFloatTemplateTest, FUN2TEST COMMA selector4, Packet4f, fhvmax, fhv36, fhv0, fhv_240, fhvmin);
  allTwoPermRep(vectorHalfFloatTemplateTest, FUN2TEST COMMA selector4_max, Packet4f, fhvmax, fhv36, fhv0, fhv_240,
                fhvmin);
  allTwoPermRep(vectorHalfFloatTemplateTest, FUN2TEST COMMA selector4_pos, Packet4f, fhvmax, fhv36, fhv0, fhv_240,
                fhvmin);
  allTwoPermRep(vectorHalfFloatTemplateTest, FUN2TEST COMMA selector4_zero, Packet4f, fhvmax, fhv36, fhv0, fhv_240,
                fhvmin);
  allTwoPermRep(vectorHalfFloatTemplateTest, FUN2TEST COMMA selector4_neg, Packet4f, fhvmax, fhv36, fhv0, fhv_240,
                fhvmin);
  allTwoPermRep(vectorHalfFloatTemplateTest, FUN2TEST COMMA selector4_min, Packet4f, fhvmax, fhv36, fhv0, fhv_240,
                fhvmin);

  endTest();

  /* double =  Packet2d (half) */
  beginTest("2 double tests");

  MIN2MAX_2_DOUBLE_VECTOR_LOADED

  allTwoPermRep(vectorHalfDoubleTemplateTest, FUN2TEST COMMA selector2, Packet2d, dhvmax, dhv36, dhv0, dhv_240, dhvmin);
  allTwoPermRep(vectorHalfDoubleTemplateTest, FUN2TEST COMMA selector2_max, Packet2d, dhvmax, dhv36, dhv0, dhv_240,
                dhvmin);
  allTwoPermRep(vectorHalfDoubleTemplateTest, FUN2TEST COMMA selector2_pos, Packet2d, dhvmax, dhv36, dhv0, dhv_240,
                dhvmin);
  allTwoPermRep(vectorHalfDoubleTemplateTest, FUN2TEST COMMA selector2_zero, Packet2d, dhvmax, dhv36, dhv0, dhv_240,
                dhvmin);
  allTwoPermRep(vectorHalfDoubleTemplateTest, FUN2TEST COMMA selector2_neg, Packet2d, dhvmax, dhv36, dhv0, dhv_240,
                dhvmin);
  allTwoPermRep(vectorHalfDoubleTemplateTest, FUN2TEST COMMA selector2_min, Packet2d, dhvmax, dhv36, dhv0, dhv_240,
                dhvmin);

  endTest();

  /* int = Packet4i (half) */
  beginTest("4 int tests");

  MIN2MAX_4_INT_VECTOR_LOADED

  allTwoPermRep(vectorHalfIntTemplateTest, FUN2TEST COMMA selector4, Packet4i, ihvmax, ihv36, ihv0, ihv_240, ihvmin);
  allTwoPermRep(vectorHalfIntTemplateTest, FUN2TEST COMMA selector4_max, Packet4i, ihvmax, ihv36, ihv0, ihv_240,
                ihvmin);
  allTwoPermRep(vectorHalfIntTemplateTest, FUN2TEST COMMA selector4_pos, Packet4i, ihvmax, ihv36, ihv0, ihv_240,
                ihvmin);
  allTwoPermRep(vectorHalfIntTemplateTest, FUN2TEST COMMA selector4_zero, Packet4i, ihvmax, ihv36, ihv0, ihv_240,
                ihvmin);
  allTwoPermRep(vectorHalfIntTemplateTest, FUN2TEST COMMA selector4_neg, Packet4i, ihvmax, ihv36, ihv0, ihv_240,
                ihvmin);
  allTwoPermRep(vectorHalfIntTemplateTest, FUN2TEST COMMA selector4_min, Packet4i, ihvmax, ihv36, ihv0, ihv_240,
                ihvmin);

  endTest();

  /* bool = Packet16b */
  beginTest("16 bool tests");

  MIN2MAX_16_BOOL_VECTOR_LOADED

  vectorHalfBoolTemplateTest(FUN2TEST COMMA selector16, Packet16b, bvtrue, bvtrue);
  vectorHalfBoolTemplateTest(FUN2TEST COMMA selector16, Packet16b, bvtrue, bvfalse);
  vectorHalfBoolTemplateTest(FUN2TEST COMMA selector16, Packet16b, bvfalse, bvtrue);
  vectorHalfBoolTemplateTest(FUN2TEST COMMA selector16, Packet16b, bvfalse, bvfalse);

  vectorHalfBoolTemplateTest(FUN2TEST COMMA selector16_max, Packet16b, bvtrue, bvtrue);
  vectorHalfBoolTemplateTest(FUN2TEST COMMA selector16_max, Packet16b, bvtrue, bvfalse);
  vectorHalfBoolTemplateTest(FUN2TEST COMMA selector16_max, Packet16b, bvfalse, bvtrue);
  vectorHalfBoolTemplateTest(FUN2TEST COMMA selector16_max, Packet16b, bvfalse, bvfalse);

  vectorHalfBoolTemplateTest(FUN2TEST COMMA selector16_pos, Packet16b, bvtrue, bvtrue);
  vectorHalfBoolTemplateTest(FUN2TEST COMMA selector16_pos, Packet16b, bvtrue, bvfalse);
  vectorHalfBoolTemplateTest(FUN2TEST COMMA selector16_pos, Packet16b, bvfalse, bvtrue);
  vectorHalfBoolTemplateTest(FUN2TEST COMMA selector16_pos, Packet16b, bvfalse, bvfalse);

  vectorHalfBoolTemplateTest(FUN2TEST COMMA selector16_zero, Packet16b, bvtrue, bvtrue);
  vectorHalfBoolTemplateTest(FUN2TEST COMMA selector16_zero, Packet16b, bvtrue, bvfalse);
  vectorHalfBoolTemplateTest(FUN2TEST COMMA selector16_zero, Packet16b, bvfalse, bvtrue);
  vectorHalfBoolTemplateTest(FUN2TEST COMMA selector16_zero, Packet16b, bvfalse, bvfalse);

  vectorHalfBoolTemplateTest(FUN2TEST COMMA selector16_neg, Packet16b, bvtrue, bvtrue);
  vectorHalfBoolTemplateTest(FUN2TEST COMMA selector16_neg, Packet16b, bvtrue, bvfalse);
  vectorHalfBoolTemplateTest(FUN2TEST COMMA selector16_neg, Packet16b, bvfalse, bvtrue);
  vectorHalfBoolTemplateTest(FUN2TEST COMMA selector16_neg, Packet16b, bvfalse, bvfalse);

  vectorHalfBoolTemplateTest(FUN2TEST COMMA selector16_min, Packet16b, bvtrue, bvtrue);
  vectorHalfBoolTemplateTest(FUN2TEST COMMA selector16_min, Packet16b, bvtrue, bvfalse);
  vectorHalfBoolTemplateTest(FUN2TEST COMMA selector16_min, Packet16b, bvfalse, bvtrue);
  vectorHalfBoolTemplateTest(FUN2TEST COMMA selector16_min, Packet16b, bvfalse, bvfalse);

  endTest();

#endif

#ifdef __AVX__
  /* float = Packet8f (full) */
  beginTest("8 float tests");

  MIN2MAX_8_FLOAT_VECTOR_LOADED

  allTwoPermRep(vectorFullFloatTemplateTest, FUN2TEST COMMA selector8, Packet8f, fvmax, fv36, fv0, fv_240, fvmin);
  allTwoPermRep(vectorFullFloatTemplateTest, FUN2TEST COMMA selector8_max, Packet8f, fvmax, fv36, fv0, fv_240, fvmin);
  allTwoPermRep(vectorFullFloatTemplateTest, FUN2TEST COMMA selector8_pos, Packet8f, fvmax, fv36, fv0, fv_240, fvmin);
  allTwoPermRep(vectorFullFloatTemplateTest, FUN2TEST COMMA selector8_zero, Packet8f, fvmax, fv36, fv0, fv_240, fvmin);
  allTwoPermRep(vectorFullFloatTemplateTest, FUN2TEST COMMA selector8_neg, Packet8f, fvmax, fv36, fv0, fv_240, fvmin);
  allTwoPermRep(vectorFullFloatTemplateTest, FUN2TEST COMMA selector8_min, Packet8f, fvmax, fv36, fv0, fv_240, fvmin);

  endTest();

  /* double = Packet4d (full) */
  beginTest("4 double tests");

  MIN2MAX_4_DOUBLE_VECTOR_LOADED

  allTwoPermRep(vectorFullDoubleTemplateTest, FUN2TEST COMMA selector4, Packet4d, dvmax, dv36, dv0, dv_240, dvmin);
  allTwoPermRep(vectorFullDoubleTemplateTest, FUN2TEST COMMA selector4_max, Packet4d, dvmax, dv36, dv0, dv_240, dvmin);
  allTwoPermRep(vectorFullDoubleTemplateTest, FUN2TEST COMMA selector4_pos, Packet4d, dvmax, dv36, dv0, dv_240, dvmin);
  allTwoPermRep(vectorFullDoubleTemplateTest, FUN2TEST COMMA selector4_zero, Packet4d, dvmax, dv36, dv0, dv_240, dvmin);
  allTwoPermRep(vectorFullDoubleTemplateTest, FUN2TEST COMMA selector4_neg, Packet4d, dvmax, dv36, dv0, dv_240, dvmin);
  allTwoPermRep(vectorFullDoubleTemplateTest, FUN2TEST COMMA selector4_min, Packet4d, dvmax, dv36, dv0, dv_240, dvmin);

  endTest();

  /* int = Packet8i (full) */
  beginTest("8 int tests");

  MIN2MAX_8_INT_VECTOR_LOADED

  allTwoPermRep(vectorFullIntTemplateTest, FUN2TEST COMMA selector8, Packet8i, ivmax, iv36, iv0, iv_240, ivmin);
  allTwoPermRep(vectorFullIntTemplateTest, FUN2TEST COMMA selector8_max, Packet8i, ivmax, iv36, iv0, iv_240, ivmin);
  allTwoPermRep(vectorFullIntTemplateTest, FUN2TEST COMMA selector8_pos, Packet8i, ivmax, iv36, iv0, iv_240, ivmin);
  allTwoPermRep(vectorFullIntTemplateTest, FUN2TEST COMMA selector8_zero, Packet8i, ivmax, iv36, iv0, iv_240, ivmin);
  allTwoPermRep(vectorFullIntTemplateTest, FUN2TEST COMMA selector8_neg, Packet8i, ivmax, iv36, iv0, iv_240, ivmin);
  allTwoPermRep(vectorFullIntTemplateTest, FUN2TEST COMMA selector8_min, Packet8i, ivmax, iv36, iv0, iv_240, ivmin);

  endTest();

  /* Eigen::half = Packet8h */
  beginTest("8 Eigen::half tests");

  MIN2MAX_8_HALF_VECTOR_LOADED

  allTwoPermRep(vectorHalfEigenHalfTemplateTest, FUN2TEST COMMA selector8, Packet8h, hvmax, hv36, hv0, hv_240, hvmin);
  allTwoPermRep(vectorHalfEigenHalfTemplateTest, FUN2TEST COMMA selector8_max, Packet8h, hvmax, hv36, hv0, hv_240,
                hvmin);
  allTwoPermRep(vectorHalfEigenHalfTemplateTest, FUN2TEST COMMA selector8_pos, Packet8h, hvmax, hv36, hv0, hv_240,
                hvmin);
  allTwoPermRep(vectorHalfEigenHalfTemplateTest, FUN2TEST COMMA selector8_zero, Packet8h, hvmax, hv36, hv0, hv_240,
                hvmin);
  allTwoPermRep(vectorHalfEigenHalfTemplateTest, FUN2TEST COMMA selector8_neg, Packet8h, hvmax, hv36, hv0, hv_240,
                hvmin);
  allTwoPermRep(vectorHalfEigenHalfTemplateTest, FUN2TEST COMMA selector8_min, Packet8h, hvmax, hv36, hv0, hv_240,
                hvmin);

  endTest();

  /* bfloat16 = Packet8bf */
  beginTest("8 bfloat16 tests");

  MIN2MAX_8_BFLOAT16_VECTOR_LOADED

  allTwoPermRep(vectorHalfBfloat16TemplateTest, FUN2TEST COMMA selector8, Packet8bf, bfvmax, bfv36, bfv0, bfv_240,
                bfvmin);
  allTwoPermRep(vectorHalfBfloat16TemplateTest, FUN2TEST COMMA selector8_max, Packet8bf, bfvmax, bfv36, bfv0, bfv_240,
                bfvmin);
  allTwoPermRep(vectorHalfBfloat16TemplateTest, FUN2TEST COMMA selector8_pos, Packet8bf, bfvmax, bfv36, bfv0, bfv_240,
                bfvmin);
  allTwoPermRep(vectorHalfBfloat16TemplateTest, FUN2TEST COMMA selector8_zero, Packet8bf, bfvmax, bfv36, bfv0, bfv_240,
                bfvmin);
  allTwoPermRep(vectorHalfBfloat16TemplateTest, FUN2TEST COMMA selector8_neg, Packet8bf, bfvmax, bfv36, bfv0, bfv_240,
                bfvmin);
  allTwoPermRep(vectorHalfBfloat16TemplateTest, FUN2TEST COMMA selector8_min, Packet8bf, bfvmax, bfv36, bfv0, bfv_240,
                bfvmin);

  endTest();

#endif

#ifdef __AVX2__
  /* long = Packet4l */
  beginTest("4 long tests");

  MIN2MAX_4_LONG_VECTOR_LOADED

  allTwoPermRep(vectorFullLongTemplateTest, FUN2TEST COMMA selector4, Packet4l, lvmax, lv36, lv0, lv_240, lvmin);
  allTwoPermRep(vectorFullLongTemplateTest, FUN2TEST COMMA selector4_max, Packet4l, lvmax, lv36, lv0, lv_240, lvmin);
  allTwoPermRep(vectorFullLongTemplateTest, FUN2TEST COMMA selector4_pos, Packet4l, lvmax, lv36, lv0, lv_240, lvmin);
  allTwoPermRep(vectorFullLongTemplateTest, FUN2TEST COMMA selector4_zero, Packet4l, lvmax, lv36, lv0, lv_240, lvmin);
  allTwoPermRep(vectorFullLongTemplateTest, FUN2TEST COMMA selector4_neg, Packet4l, lvmax, lv36, lv0, lv_240, lvmin);
  allTwoPermRep(vectorFullLongTemplateTest, FUN2TEST COMMA selector4_min, Packet4l, lvmax, lv36, lv0, lv_240, lvmin);

  endTest();

#endif

#ifdef __AVX512F__
#endif
}

addTest(FUN2TEST)

#endif  // EIGEN_MIPP_PBLEND_TEST_H
