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

  MIN2MAX_4_FLOAT_VECTOR

  allTwoPermRep(vectorHalfFloatTest, FUN2TEST COMMA selector4, fhvmax, fhv36, fhv0, fhv_240, fhvmin);
  allTwoPermRep(vectorHalfFloatTest, FUN2TEST COMMA selector4_max, fhvmax, fhv36, fhv0, fhv_240, fhvmin);
  allTwoPermRep(vectorHalfFloatTest, FUN2TEST COMMA selector4_pos, fhvmax, fhv36, fhv0, fhv_240, fhvmin);
  allTwoPermRep(vectorHalfFloatTest, FUN2TEST COMMA selector4_zero, fhvmax, fhv36, fhv0, fhv_240, fhvmin);
  allTwoPermRep(vectorHalfFloatTest, FUN2TEST COMMA selector4_neg, fhvmax, fhv36, fhv0, fhv_240, fhvmin);
  allTwoPermRep(vectorHalfFloatTest, FUN2TEST COMMA selector4_min, fhvmax, fhv36, fhv0, fhv_240, fhvmin);

  endTest();

  /* double =  Packet2d (half) */
  beginTest("2 double tests");

  MIN2MAX_2_DOUBLE_VECTOR

  allTwoPermRep(vectorHalfDoubleTest, FUN2TEST COMMA selector2, dhvmax, dhv36, dhv0,
                dhv_240, dhvmin);
  allTwoPermRep(vectorHalfDoubleTest, FUN2TEST COMMA selector2_max, dhvmax, dhv36,
                dhv0, dhv_240, dhvmin);
  allTwoPermRep(vectorHalfDoubleTest, FUN2TEST COMMA selector2_pos, dhvmax, dhv36,
                dhv0, dhv_240, dhvmin);
  allTwoPermRep(vectorHalfDoubleTest, FUN2TEST COMMA selector2_zero, dhvmax, dhv36,
                dhv0, dhv_240, dhvmin);
  allTwoPermRep(vectorHalfDoubleTest, FUN2TEST COMMA selector2_neg, dhvmax, dhv36,
                dhv0, dhv_240, dhvmin);
  allTwoPermRep(vectorHalfDoubleTest, FUN2TEST COMMA selector2_min, dhvmax, dhv36,
                dhv0, dhv_240, dhvmin);

  endTest();

  /* int = Packet4i (half) */
  beginTest("4 int tests");

  MIN2MAX_4_INT_VECTOR

  allTwoPermRep(vectorHalfIntTest, FUN2TEST COMMA selector4, ihvmax, ihv36, ihv0,
                ihv_240, ihvmin);
  allTwoPermRep(vectorHalfIntTest, FUN2TEST COMMA selector4_max, ihvmax, ihv36, ihv0,
                ihv_240, ihvmin);
  allTwoPermRep(vectorHalfIntTest, FUN2TEST COMMA selector4_pos, ihvmax, ihv36, ihv0,
                ihv_240, ihvmin);
  allTwoPermRep(vectorHalfIntTest, FUN2TEST COMMA selector4_zero, ihvmax, ihv36, ihv0,
                ihv_240, ihvmin);
  allTwoPermRep(vectorHalfIntTest, FUN2TEST COMMA selector4_neg, ihvmax, ihv36, ihv0,
                ihv_240, ihvmin);
  allTwoPermRep(vectorHalfIntTest, FUN2TEST COMMA selector4_min, ihvmax, ihv36, ihv0,
                ihv_240, ihvmin);

  endTest();

  /* bool = Packet16b */
  beginTest("16 bool tests");

  MIN2MAX_16_BOOL_VECTOR

  vectorHalfBoolTest(FUN2TEST COMMA selector16, bvtrue, bvtrue);
  vectorHalfBoolTest(FUN2TEST COMMA selector16, bvtrue, bvfalse);
  vectorHalfBoolTest(FUN2TEST COMMA selector16, bvfalse, bvtrue);
  vectorHalfBoolTest(FUN2TEST COMMA selector16, bvfalse, bvfalse);

  vectorHalfBoolTest(FUN2TEST COMMA selector16_max, bvtrue, bvtrue);
  vectorHalfBoolTest(FUN2TEST COMMA selector16_max, bvtrue, bvfalse);
  vectorHalfBoolTest(FUN2TEST COMMA selector16_max, bvfalse, bvtrue);
  vectorHalfBoolTest(FUN2TEST COMMA selector16_max, bvfalse, bvfalse);

  vectorHalfBoolTest(FUN2TEST COMMA selector16_pos, bvtrue, bvtrue);
  vectorHalfBoolTest(FUN2TEST COMMA selector16_pos, bvtrue, bvfalse);
  vectorHalfBoolTest(FUN2TEST COMMA selector16_pos, bvfalse, bvtrue);
  vectorHalfBoolTest(FUN2TEST COMMA selector16_pos, bvfalse, bvfalse);

  vectorHalfBoolTest(FUN2TEST COMMA selector16_zero, bvtrue, bvtrue);
  vectorHalfBoolTest(FUN2TEST COMMA selector16_zero, bvtrue, bvfalse);
  vectorHalfBoolTest(FUN2TEST COMMA selector16_zero, bvfalse, bvtrue);
  vectorHalfBoolTest(FUN2TEST COMMA selector16_zero, bvfalse, bvfalse);

  vectorHalfBoolTest(FUN2TEST COMMA selector16_neg, bvtrue, bvtrue);
  vectorHalfBoolTest(FUN2TEST COMMA selector16_neg, bvtrue, bvfalse);
  vectorHalfBoolTest(FUN2TEST COMMA selector16_neg, bvfalse, bvtrue);
  vectorHalfBoolTest(FUN2TEST COMMA selector16_neg, bvfalse, bvfalse);

  vectorHalfBoolTest(FUN2TEST COMMA selector16_min, bvtrue, bvtrue);
  vectorHalfBoolTest(FUN2TEST COMMA selector16_min, bvtrue, bvfalse);
  vectorHalfBoolTest(FUN2TEST COMMA selector16_min, bvfalse, bvtrue);
  vectorHalfBoolTest(FUN2TEST COMMA selector16_min, bvfalse, bvfalse);

  endTest();

#endif

#ifdef __AVX__
  /* float = Packet8f (full) */
  beginTest("8 float tests");

  MIN2MAX_8_FLOAT_VECTOR

  allTwoPermRep(vectorFullFloatTest, FUN2TEST COMMA selector8, fvmax, fv36, fv0, fv_240, fvmin);
  allTwoPermRep(vectorFullFloatTest, FUN2TEST COMMA selector8_max, fvmax, fv36, fv0, fv_240, fvmin);
  allTwoPermRep(vectorFullFloatTest, FUN2TEST COMMA selector8_pos, fvmax, fv36, fv0, fv_240, fvmin);
  allTwoPermRep(vectorFullFloatTest, FUN2TEST COMMA selector8_zero, fvmax, fv36, fv0, fv_240, fvmin);
  allTwoPermRep(vectorFullFloatTest, FUN2TEST COMMA selector8_neg, fvmax, fv36, fv0, fv_240, fvmin);
  allTwoPermRep(vectorFullFloatTest, FUN2TEST COMMA selector8_min, fvmax, fv36, fv0, fv_240, fvmin);

  endTest();

  /* double = Packet4d (full) */
  beginTest("4 double tests");

  MIN2MAX_4_DOUBLE_VECTOR

  allTwoPermRep(vectorFullDoubleTest, FUN2TEST COMMA selector4, dvmax, dv36, dv0,
                dv_240, dvmin);
  allTwoPermRep(vectorFullDoubleTest, FUN2TEST COMMA selector4_max, dvmax, dv36,
                dv0, dv_240, dvmin);
  allTwoPermRep(vectorFullDoubleTest, FUN2TEST COMMA selector4_pos, dvmax, dv36,
                dv0, dv_240, dvmin);
  allTwoPermRep(vectorFullDoubleTest, FUN2TEST COMMA selector4_zero, dvmax, dv36,
                dv0, dv_240, dvmin);
  allTwoPermRep(vectorFullDoubleTest, FUN2TEST COMMA selector4_neg, dvmax, dv36,
                dv0, dv_240, dvmin);
  allTwoPermRep(vectorFullDoubleTest, FUN2TEST COMMA selector4_min, dvmax, dv36,
                dv0, dv_240, dvmin);

  endTest();

  /* int = Packet8i (full) */
  beginTest("8 int tests");

  MIN2MAX_8_INT_VECTOR

  allTwoPermRep(vectorFullIntTest, FUN2TEST COMMA selector8, ivmax, iv36, iv0,
                iv_240, ivmin);
  allTwoPermRep(vectorFullIntTest, FUN2TEST COMMA selector8_max, ivmax, iv36, iv0,
                iv_240, ivmin);
  allTwoPermRep(vectorFullIntTest, FUN2TEST COMMA selector8_pos, ivmax, iv36, iv0,
                iv_240, ivmin);
  allTwoPermRep(vectorFullIntTest, FUN2TEST COMMA selector8_zero, ivmax, iv36, iv0,
                iv_240, ivmin);
  allTwoPermRep(vectorFullIntTest, FUN2TEST COMMA selector8_neg, ivmax, iv36, iv0,
                iv_240, ivmin);
  allTwoPermRep(vectorFullIntTest, FUN2TEST COMMA selector8_min, ivmax, iv36, iv0,
                iv_240, ivmin);

  endTest();

  /* Eigen::half = Packet8h */
  beginTest("8 Eigen::half tests");

  MIN2MAX_8_HALF_VECTOR

  allTwoPermRep(vectorHalfEigenHalfTest, FUN2TEST COMMA selector8, hvmax, hv36, hv0,
                hv_240, hvmin);
  allTwoPermRep(vectorHalfEigenHalfTest, FUN2TEST COMMA selector8_max, hvmax, hv36,
                hv0, hv_240, hvmin);
  allTwoPermRep(vectorHalfEigenHalfTest, FUN2TEST COMMA selector8_pos, hvmax, hv36,
                hv0, hv_240, hvmin);
  allTwoPermRep(vectorHalfEigenHalfTest, FUN2TEST COMMA selector8_zero, hvmax, hv36,
                hv0, hv_240, hvmin);
  allTwoPermRep(vectorHalfEigenHalfTest, FUN2TEST COMMA selector8_neg, hvmax, hv36,
                hv0, hv_240, hvmin);
  allTwoPermRep(vectorHalfEigenHalfTest, FUN2TEST COMMA selector8_min, hvmax, hv36,
                hv0, hv_240, hvmin);

  endTest();

  /* bfloat16 = Packet8bf */
  beginTest("8 bfloat16 tests");

  MIN2MAX_8_BFLOAT16_VECTOR

  allTwoPermRep(vectorHalfBfloat16Test, FUN2TEST COMMA selector8, bfvmax, bfv36, bfv0,
                bfv_240, bfvmin);
  allTwoPermRep(vectorHalfBfloat16Test, FUN2TEST COMMA selector8_max, bfvmax, bfv36,
                bfv0, bfv_240, bfvmin);
  allTwoPermRep(vectorHalfBfloat16Test, FUN2TEST COMMA selector8_pos, bfvmax, bfv36,
                bfv0, bfv_240, bfvmin);
  allTwoPermRep(vectorHalfBfloat16Test, FUN2TEST COMMA selector8_zero, bfvmax, bfv36,
                bfv0, bfv_240, bfvmin);
  allTwoPermRep(vectorHalfBfloat16Test, FUN2TEST COMMA selector8_neg, bfvmax, bfv36,
                bfv0, bfv_240, bfvmin);
  allTwoPermRep(vectorHalfBfloat16Test, FUN2TEST COMMA selector8_min, bfvmax, bfv36,
                bfv0, bfv_240, bfvmin);

  endTest();

#endif

#ifdef __AVX2__
  /* long = Packet4l */
  beginTest("4 long tests");

  MIN2MAX_4_LONG_VECTOR

  allTwoPermRep(vectorFullLongTest, FUN2TEST COMMA selector4, lvmax, lv36, lv0,
                lv_240, lvmin);
  allTwoPermRep(vectorFullLongTest, FUN2TEST COMMA selector4_max, lvmax, lv36, lv0,
                lv_240, lvmin);
  allTwoPermRep(vectorFullLongTest, FUN2TEST COMMA selector4_pos, lvmax, lv36, lv0,
                lv_240, lvmin);
  allTwoPermRep(vectorFullLongTest, FUN2TEST COMMA selector4_zero, lvmax, lv36, lv0,
                lv_240, lvmin);
  allTwoPermRep(vectorFullLongTest, FUN2TEST COMMA selector4_neg, lvmax, lv36, lv0,
                lv_240, lvmin);
  allTwoPermRep(vectorFullLongTest, FUN2TEST COMMA selector4_min, lvmax, lv36, lv0,
                lv_240, lvmin);

  endTest();

#endif

#ifdef __AVX512F__
#endif
}

addTest(FUN2TEST)

#endif  // EIGEN_MIPP_PBLEND_TEST_H
