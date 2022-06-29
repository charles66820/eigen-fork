#include <float.h>
#include <limits.h>
#include "../testVector.h"
#include "../testCombinations.h"

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

  MIN2MAX_HALF_FLOAT_VECTOR

  allTwoPermRep(vectorHalfFloatTest, FUN2TEST COMMA selector4, fhvmax.r, fhv36.r, fhv0.r, fhv_240.r, fhvmin.r);
  allTwoPermRep(vectorHalfFloatTest, FUN2TEST COMMA selector4_max, fhvmax.r, fhv36.r, fhv0.r, fhv_240.r, fhvmin.r);
  allTwoPermRep(vectorHalfFloatTest, FUN2TEST COMMA selector4_pos, fhvmax.r, fhv36.r, fhv0.r, fhv_240.r, fhvmin.r);
  allTwoPermRep(vectorHalfFloatTest, FUN2TEST COMMA selector4_zero, fhvmax.r, fhv36.r, fhv0.r, fhv_240.r, fhvmin.r);
  allTwoPermRep(vectorHalfFloatTest, FUN2TEST COMMA selector4_neg, fhvmax.r, fhv36.r, fhv0.r, fhv_240.r, fhvmin.r);
  allTwoPermRep(vectorHalfFloatTest, FUN2TEST COMMA selector4_min, fhvmax.r, fhv36.r, fhv0.r, fhv_240.r, fhvmin.r);

  endTest();

  /* double =  Packet2d (half) */
  beginTest("2 double tests");

  MIN2MAX_HALF_DOUBLE_VECTOR

  allTwoPermRep(vectorHalfDoubleTest, FUN2TEST COMMA selector2, (Packet2d)dhvmax.r, (Packet2d)dhv36.r, (Packet2d)dhv0.r,
                (Packet2d)dhv_240.r, (Packet2d)dhvmin.r);
  allTwoPermRep(vectorHalfDoubleTest, FUN2TEST COMMA selector2_max, (Packet2d)dhvmax.r, (Packet2d)dhv36.r,
                (Packet2d)dhv0.r, (Packet2d)dhv_240.r, (Packet2d)dhvmin.r);
  allTwoPermRep(vectorHalfDoubleTest, FUN2TEST COMMA selector2_pos, (Packet2d)dhvmax.r, (Packet2d)dhv36.r,
                (Packet2d)dhv0.r, (Packet2d)dhv_240.r, (Packet2d)dhvmin.r);
  allTwoPermRep(vectorHalfDoubleTest, FUN2TEST COMMA selector2_zero, (Packet2d)dhvmax.r, (Packet2d)dhv36.r,
                (Packet2d)dhv0.r, (Packet2d)dhv_240.r, (Packet2d)dhvmin.r);
  allTwoPermRep(vectorHalfDoubleTest, FUN2TEST COMMA selector2_neg, (Packet2d)dhvmax.r, (Packet2d)dhv36.r,
                (Packet2d)dhv0.r, (Packet2d)dhv_240.r, (Packet2d)dhvmin.r);
  allTwoPermRep(vectorHalfDoubleTest, FUN2TEST COMMA selector2_min, (Packet2d)dhvmax.r, (Packet2d)dhv36.r,
                (Packet2d)dhv0.r, (Packet2d)dhv_240.r, (Packet2d)dhvmin.r);

  endTest();

  /* int = Packet4i (half) */
  beginTest("4 int tests");

  MIN2MAX_HALF_INT_VECTOR

  allTwoPermRep(vectorHalfIntTest, FUN2TEST COMMA selector4, (__m128i)ihvmax.r, (__m128i)ihv36.r, (__m128i)ihv0.r,
                (__m128i)ihv_240.r, (__m128i)ihvmin.r);
  allTwoPermRep(vectorHalfIntTest, FUN2TEST COMMA selector4_max, (__m128i)ihvmax.r, (__m128i)ihv36.r, (__m128i)ihv0.r,
                (__m128i)ihv_240.r, (__m128i)ihvmin.r);
  allTwoPermRep(vectorHalfIntTest, FUN2TEST COMMA selector4_pos, (__m128i)ihvmax.r, (__m128i)ihv36.r, (__m128i)ihv0.r,
                (__m128i)ihv_240.r, (__m128i)ihvmin.r);
  allTwoPermRep(vectorHalfIntTest, FUN2TEST COMMA selector4_zero, (__m128i)ihvmax.r, (__m128i)ihv36.r, (__m128i)ihv0.r,
                (__m128i)ihv_240.r, (__m128i)ihvmin.r);
  allTwoPermRep(vectorHalfIntTest, FUN2TEST COMMA selector4_neg, (__m128i)ihvmax.r, (__m128i)ihv36.r, (__m128i)ihv0.r,
                (__m128i)ihv_240.r, (__m128i)ihvmin.r);
  allTwoPermRep(vectorHalfIntTest, FUN2TEST COMMA selector4_min, (__m128i)ihvmax.r, (__m128i)ihv36.r, (__m128i)ihv0.r,
                (__m128i)ihv_240.r, (__m128i)ihvmin.r);

  endTest();

  /* bool = Packet16b */
  beginTest("16 bool tests");

  MIN2MAX_HALF_BOOL_VECTOR

  vectorHalfBoolTest(FUN2TEST COMMA selector16, (__m128i)bvtrue.r, (__m128i)bvtrue.r);
  vectorHalfBoolTest(FUN2TEST COMMA selector16, (__m128i)bvtrue.r, (__m128i)bvfalse.r);
  vectorHalfBoolTest(FUN2TEST COMMA selector16, (__m128i)bvfalse.r, (__m128i)bvtrue.r);
  vectorHalfBoolTest(FUN2TEST COMMA selector16, (__m128i)bvfalse.r, (__m128i)bvfalse.r);

  vectorHalfBoolTest(FUN2TEST COMMA selector16_max, (__m128i)bvtrue.r, (__m128i)bvtrue.r);
  vectorHalfBoolTest(FUN2TEST COMMA selector16_max, (__m128i)bvtrue.r, (__m128i)bvfalse.r);
  vectorHalfBoolTest(FUN2TEST COMMA selector16_max, (__m128i)bvfalse.r, (__m128i)bvtrue.r);
  vectorHalfBoolTest(FUN2TEST COMMA selector16_max, (__m128i)bvfalse.r, (__m128i)bvfalse.r);

  vectorHalfBoolTest(FUN2TEST COMMA selector16_pos, (__m128i)bvtrue.r, (__m128i)bvtrue.r);
  vectorHalfBoolTest(FUN2TEST COMMA selector16_pos, (__m128i)bvtrue.r, (__m128i)bvfalse.r);
  vectorHalfBoolTest(FUN2TEST COMMA selector16_pos, (__m128i)bvfalse.r, (__m128i)bvtrue.r);
  vectorHalfBoolTest(FUN2TEST COMMA selector16_pos, (__m128i)bvfalse.r, (__m128i)bvfalse.r);

  vectorHalfBoolTest(FUN2TEST COMMA selector16_zero, (__m128i)bvtrue.r, (__m128i)bvtrue.r);
  vectorHalfBoolTest(FUN2TEST COMMA selector16_zero, (__m128i)bvtrue.r, (__m128i)bvfalse.r);
  vectorHalfBoolTest(FUN2TEST COMMA selector16_zero, (__m128i)bvfalse.r, (__m128i)bvtrue.r);
  vectorHalfBoolTest(FUN2TEST COMMA selector16_zero, (__m128i)bvfalse.r, (__m128i)bvfalse.r);

  vectorHalfBoolTest(FUN2TEST COMMA selector16_neg, (__m128i)bvtrue.r, (__m128i)bvtrue.r);
  vectorHalfBoolTest(FUN2TEST COMMA selector16_neg, (__m128i)bvtrue.r, (__m128i)bvfalse.r);
  vectorHalfBoolTest(FUN2TEST COMMA selector16_neg, (__m128i)bvfalse.r, (__m128i)bvtrue.r);
  vectorHalfBoolTest(FUN2TEST COMMA selector16_neg, (__m128i)bvfalse.r, (__m128i)bvfalse.r);

  vectorHalfBoolTest(FUN2TEST COMMA selector16_min, (__m128i)bvtrue.r, (__m128i)bvtrue.r);
  vectorHalfBoolTest(FUN2TEST COMMA selector16_min, (__m128i)bvtrue.r, (__m128i)bvfalse.r);
  vectorHalfBoolTest(FUN2TEST COMMA selector16_min, (__m128i)bvfalse.r, (__m128i)bvtrue.r);
  vectorHalfBoolTest(FUN2TEST COMMA selector16_min, (__m128i)bvfalse.r, (__m128i)bvfalse.r);

  endTest();

#endif

#ifdef __AVX__
  /* float = Packet8f (full) */
  beginTest("8 float tests");

  MIN2MAX_FULL_FLOAT_VECTOR

  allTwoPermRep(vectorFullFloatTest, FUN2TEST COMMA selector8, fvmax.r, fv36.r, fv0.r, fv_240.r, fvmin.r);
  allTwoPermRep(vectorFullFloatTest, FUN2TEST COMMA selector8_max, fvmax.r, fv36.r, fv0.r, fv_240.r, fvmin.r);
  allTwoPermRep(vectorFullFloatTest, FUN2TEST COMMA selector8_pos, fvmax.r, fv36.r, fv0.r, fv_240.r, fvmin.r);
  allTwoPermRep(vectorFullFloatTest, FUN2TEST COMMA selector8_zero, fvmax.r, fv36.r, fv0.r, fv_240.r, fvmin.r);
  allTwoPermRep(vectorFullFloatTest, FUN2TEST COMMA selector8_neg, fvmax.r, fv36.r, fv0.r, fv_240.r, fvmin.r);
  allTwoPermRep(vectorFullFloatTest, FUN2TEST COMMA selector8_min, fvmax.r, fv36.r, fv0.r, fv_240.r, fvmin.r);

  endTest();

  /* double = Packet4d (full) */
  beginTest("4 double tests");

  MIN2MAX_FULL_DOUBLE_VECTOR

  allTwoPermRep(vectorFullDoubleTest, FUN2TEST COMMA selector4, (Packet4d)dvmax.r, (Packet4d)dv36.r, (Packet4d)dv0.r,
                (Packet4d)dv_240.r, (Packet4d)dvmin.r);
  allTwoPermRep(vectorFullDoubleTest, FUN2TEST COMMA selector4_max, (Packet4d)dvmax.r, (Packet4d)dv36.r,
                (Packet4d)dv0.r, (Packet4d)dv_240.r, (Packet4d)dvmin.r);
  allTwoPermRep(vectorFullDoubleTest, FUN2TEST COMMA selector4_pos, (Packet4d)dvmax.r, (Packet4d)dv36.r,
                (Packet4d)dv0.r, (Packet4d)dv_240.r, (Packet4d)dvmin.r);
  allTwoPermRep(vectorFullDoubleTest, FUN2TEST COMMA selector4_zero, (Packet4d)dvmax.r, (Packet4d)dv36.r,
                (Packet4d)dv0.r, (Packet4d)dv_240.r, (Packet4d)dvmin.r);
  allTwoPermRep(vectorFullDoubleTest, FUN2TEST COMMA selector4_neg, (Packet4d)dvmax.r, (Packet4d)dv36.r,
                (Packet4d)dv0.r, (Packet4d)dv_240.r, (Packet4d)dvmin.r);
  allTwoPermRep(vectorFullDoubleTest, FUN2TEST COMMA selector4_min, (Packet4d)dvmax.r, (Packet4d)dv36.r,
                (Packet4d)dv0.r, (Packet4d)dv_240.r, (Packet4d)dvmin.r);

  endTest();

  /* int = Packet8i (full) */
  beginTest("8 int tests");

  MIN2MAX_FULL_INT_VECTOR

  allTwoPermRep(vectorFullIntTest, FUN2TEST COMMA selector8, (__m256i)ivmax.r, (__m256i)iv36.r, (__m256i)iv0.r,
                (__m256i)iv_240.r, (__m256i)ivmin.r);
  allTwoPermRep(vectorFullIntTest, FUN2TEST COMMA selector8_max, (__m256i)ivmax.r, (__m256i)iv36.r, (__m256i)iv0.r,
                (__m256i)iv_240.r, (__m256i)ivmin.r);
  allTwoPermRep(vectorFullIntTest, FUN2TEST COMMA selector8_pos, (__m256i)ivmax.r, (__m256i)iv36.r, (__m256i)iv0.r,
                (__m256i)iv_240.r, (__m256i)ivmin.r);
  allTwoPermRep(vectorFullIntTest, FUN2TEST COMMA selector8_zero, (__m256i)ivmax.r, (__m256i)iv36.r, (__m256i)iv0.r,
                (__m256i)iv_240.r, (__m256i)ivmin.r);
  allTwoPermRep(vectorFullIntTest, FUN2TEST COMMA selector8_neg, (__m256i)ivmax.r, (__m256i)iv36.r, (__m256i)iv0.r,
                (__m256i)iv_240.r, (__m256i)ivmin.r);
  allTwoPermRep(vectorFullIntTest, FUN2TEST COMMA selector8_min, (__m256i)ivmax.r, (__m256i)iv36.r, (__m256i)iv0.r,
                (__m256i)iv_240.r, (__m256i)ivmin.r);

  endTest();

  /* Eigen::half = Packet8h */
  beginTest("8 Eigen::half tests");

  MIN2MAX_HALF_HALF_VECTOR

  allTwoPermRep(vectorHalfEigenHalfTest, FUN2TEST COMMA selector8, (__m128i)hvmax.r, (__m128i)hv36.r, (__m128i)hv0.r,
                (__m128i)hv_240.r, (__m128i)hvmin.r);
  allTwoPermRep(vectorHalfEigenHalfTest, FUN2TEST COMMA selector8_max, (__m128i)hvmax.r, (__m128i)hv36.r,
                (__m128i)hv0.r, (__m128i)hv_240.r, (__m128i)hvmin.r);
  allTwoPermRep(vectorHalfEigenHalfTest, FUN2TEST COMMA selector8_pos, (__m128i)hvmax.r, (__m128i)hv36.r,
                (__m128i)hv0.r, (__m128i)hv_240.r, (__m128i)hvmin.r);
  allTwoPermRep(vectorHalfEigenHalfTest, FUN2TEST COMMA selector8_zero, (__m128i)hvmax.r, (__m128i)hv36.r,
                (__m128i)hv0.r, (__m128i)hv_240.r, (__m128i)hvmin.r);
  allTwoPermRep(vectorHalfEigenHalfTest, FUN2TEST COMMA selector8_neg, (__m128i)hvmax.r, (__m128i)hv36.r,
                (__m128i)hv0.r, (__m128i)hv_240.r, (__m128i)hvmin.r);
  allTwoPermRep(vectorHalfEigenHalfTest, FUN2TEST COMMA selector8_min, (__m128i)hvmax.r, (__m128i)hv36.r,
                (__m128i)hv0.r, (__m128i)hv_240.r, (__m128i)hvmin.r);

  endTest();

  /* bfloat16 = Packet8bf */
  beginTest("8 bfloat16 tests");

  MIN2MAX_HALF_BFLOAT16_VECTOR

  allTwoPermRep(vectorHalfBfloat16Test, FUN2TEST COMMA selector8, (__m128i)bfvmax.r, (__m128i)bfv36.r, (__m128i)bfv0.r,
                (__m128i)bfv_240.r, (__m128i)bfvmin.r);
  allTwoPermRep(vectorHalfBfloat16Test, FUN2TEST COMMA selector8_max, (__m128i)bfvmax.r, (__m128i)bfv36.r,
                (__m128i)bfv0.r, (__m128i)bfv_240.r, (__m128i)bfvmin.r);
  allTwoPermRep(vectorHalfBfloat16Test, FUN2TEST COMMA selector8_pos, (__m128i)bfvmax.r, (__m128i)bfv36.r,
                (__m128i)bfv0.r, (__m128i)bfv_240.r, (__m128i)bfvmin.r);
  allTwoPermRep(vectorHalfBfloat16Test, FUN2TEST COMMA selector8_zero, (__m128i)bfvmax.r, (__m128i)bfv36.r,
                (__m128i)bfv0.r, (__m128i)bfv_240.r, (__m128i)bfvmin.r);
  allTwoPermRep(vectorHalfBfloat16Test, FUN2TEST COMMA selector8_neg, (__m128i)bfvmax.r, (__m128i)bfv36.r,
                (__m128i)bfv0.r, (__m128i)bfv_240.r, (__m128i)bfvmin.r);
  allTwoPermRep(vectorHalfBfloat16Test, FUN2TEST COMMA selector8_min, (__m128i)bfvmax.r, (__m128i)bfv36.r,
                (__m128i)bfv0.r, (__m128i)bfv_240.r, (__m128i)bfvmin.r);

  endTest();

#endif

#ifdef __AVX2__
  /* long = Packet4l */
  beginTest("4 long tests");

  MIN2MAX_FULL_LONG_VECTOR

  allTwoPermRep(vectorFullLongTest, FUN2TEST COMMA selector4, (__m256i)lvmax.r, (__m256i)lv36.r, (__m256i)lv0.r,
                (__m256i)lv_240.r, (__m256i)lvmin.r);
  allTwoPermRep(vectorFullLongTest, FUN2TEST COMMA selector4_max, (__m256i)lvmax.r, (__m256i)lv36.r, (__m256i)lv0.r,
                (__m256i)lv_240.r, (__m256i)lvmin.r);
  allTwoPermRep(vectorFullLongTest, FUN2TEST COMMA selector4_pos, (__m256i)lvmax.r, (__m256i)lv36.r, (__m256i)lv0.r,
                (__m256i)lv_240.r, (__m256i)lvmin.r);
  allTwoPermRep(vectorFullLongTest, FUN2TEST COMMA selector4_zero, (__m256i)lvmax.r, (__m256i)lv36.r, (__m256i)lv0.r,
                (__m256i)lv_240.r, (__m256i)lvmin.r);
  allTwoPermRep(vectorFullLongTest, FUN2TEST COMMA selector4_neg, (__m256i)lvmax.r, (__m256i)lv36.r, (__m256i)lv0.r,
                (__m256i)lv_240.r, (__m256i)lvmin.r);
  allTwoPermRep(vectorFullLongTest, FUN2TEST COMMA selector4_min, (__m256i)lvmax.r, (__m256i)lv36.r, (__m256i)lv0.r,
                (__m256i)lv_240.r, (__m256i)lvmin.r);

  endTest();

#endif

#ifdef __AVX512F__
#endif
}

addTest(FUN2TEST)

#endif  // EIGEN_MIPP_PBLEND_TEST_H
