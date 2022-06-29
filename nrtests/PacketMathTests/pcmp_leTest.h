#include <float.h>
#include <limits.h>
#include "../testVector.h"
#include "../testCombinations.h"

#ifndef EIGEN_MIPP_PCMP_LE_TEST_H
#define EIGEN_MIPP_PCMP_LE_TEST_H

#undef FUN2TEST
#define FUN2TEST pcmp_le

void pcmp_leTests() {
  printTestTitle(FUN2TEST);

#ifdef __SSE__
  /* float = Packet4f (half) */
  tests4FloatMin2MaxTwoArgsPermRep("4 float tests", FUN2TEST);

  /* double =  Packet2d (half) */
  tests2DoubleMin2MaxTwoArgsPermRep("2 double tests", FUN2TEST);

  /* int = Packet4i (half) */
  beginTest("4 int tests");

  MIN2MAX_HALF_INT_VECTOR

  allTwoPermRep(vectorHalfIntTest, FUN2TEST, (__m128i)ihvmax.r, (__m128i)ihv36.r, (__m128i)ihv0.r, (__m128i)ihv_240.r,
                (__m128i)ihvmin.r);

  endTest();

#endif

#ifdef __AVX__
  /* float = Packet8f (full) */
  beginTest("8 float tests");

  MIN2MAX_FULL_FLOAT_VECTOR

  allTwoPermRep(vectorFullFloatTest, FUN2TEST, fvmax.r, fv36.r, fv0.r, fv_240.r, fvmin.r);

  endTest();

  /* double = Packet4d (full) */
  beginTest("4 double tests");

  MIN2MAX_FULL_DOUBLE_VECTOR

  allTwoPermRep(vectorFullDoubleTest, FUN2TEST, (Packet4d)dvmax.r, (Packet4d)dv36.r, (Packet4d)dv0.r,
                (Packet4d)dv_240.r, (Packet4d)dvmin.r);

  endTest();

  /* int = Packet8i (full) */
  beginTest("8 int tests");

  MIN2MAX_FULL_INT_VECTOR

  allTwoPermRep(vectorFullIntTest, FUN2TEST, (__m256i)ivmax.r, (__m256i)iv36.r, (__m256i)iv0.r, (__m256i)iv_240.r,
                (__m256i)ivmin.r);

  endTest();

  /* Eigen::half = Packet8h */
  beginTest("8 Eigen::half tests");

  MIN2MAX_HALF_HALF_VECTOR

  allTwoPermRep(vectorHalfEigenHalfTest, FUN2TEST, (__m128i)hvmax.r, (__m128i)hv36.r, (__m128i)hv0.r, (__m128i)hv_240.r,
                (__m128i)hvmin.r);

  endTest();

  /* bfloat16 = Packet8bf */
  beginTest("8 bfloat16 tests");

  MIN2MAX_HALF_BFLOAT16_VECTOR

  allTwoPermRep(vectorHalfBfloat16Test, FUN2TEST, (__m128i)bfvmax.r, (__m128i)bfv36.r, (__m128i)bfv0.r,
                (__m128i)bfv_240.r, (__m128i)bfvmin.r);
  endTest();

#endif

#ifdef __AVX2__
  /* long = Packet4l */
  beginTest("4 long tests");

  MIN2MAX_FULL_LONG_VECTOR

  allTwoPermRep(vectorFullLongTest, FUN2TEST, (__m256i)lvmax.r, (__m256i)lv36.r, (__m256i)lv0.r, (__m256i)lv_240.r,
                (__m256i)lvmin.r);

  endTest();

#endif

#ifdef __AVX512F__
#endif
}

addTest(FUN2TEST)

#endif  // EIGEN_MIPP_PCMP_LE_TEST_H
