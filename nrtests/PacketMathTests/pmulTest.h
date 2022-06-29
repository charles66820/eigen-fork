#include <float.h>
#include <limits.h>
#include "../testVector.h"
#include "../testCombinations.h"

#ifndef EIGEN_MIPP_PMUL_TEST_H
#define EIGEN_MIPP_PMUL_TEST_H

#undef FUN2TEST
#define FUN2TEST pmul

void pmulTests() {
  std::cout << printTestTitle(FUN2TEST) << std::endl;

#ifdef __SSE__
  /* float = Packet4f (half) */
  beginTest("4 float tests");

  MIN2MAX_HALF_FLOAT_VECTOR

  allTwoCombRep(vectorHalfFloatTest, FUN2TEST, fhvmax.r, fhv36.r, fhv0.r, fhv_240.r, fhvmin.r);

  endTest();

  /* double =  Packet2d (half) */
  beginTest("2 double tests");

  MIN2MAX_HALF_DOUBLE_VECTOR

  allTwoCombRep(vectorHalfDoubleTest, FUN2TEST, (Packet2d)dhvmax.r, (Packet2d)dhv36.r, (Packet2d)dhv0.r,
                (Packet2d)dhv_240.r, (Packet2d)dhvmin.r);

  endTest();

  /* int = Packet4i (half) */
  beginTest("4 int tests");

  MIN2MAX_HALF_INT_VECTOR

  allTwoCombRep(vectorHalfIntTest, FUN2TEST, (__m128i)ihvmax.r, (__m128i)ihv36.r, (__m128i)ihv0.r, (__m128i)ihv_240.r,
                (__m128i)ihvmin.r);

  endTest();

  /* bool = Packet16b */
  beginTest("16 bool tests");

  MIN2MAX_HALF_BOOL_VECTOR

  vectorHalfBoolTest(FUN2TEST, (__m128i)bvtrue.r, (__m128i)bvtrue.r);
  vectorHalfBoolTest(FUN2TEST, (__m128i)bvtrue.r, (__m128i)bvfalse.r);
  vectorHalfBoolTest(FUN2TEST, (__m128i)bvfalse.r, (__m128i)bvtrue.r);
  vectorHalfBoolTest(FUN2TEST, (__m128i)bvfalse.r, (__m128i)bvfalse.r);

  endTest();

#endif

#ifdef __AVX__
  /* float = Packet8f (full) */
  beginTest("8 float tests");

  MIN2MAX_FULL_FLOAT_VECTOR

  allTwoCombRep(vectorFullFloatTest, FUN2TEST, fvmax.r, fv36.r, fv0.r, fv_240.r, fvmin.r);

  endTest();

  /* double = Packet4d (full) */
  beginTest("4 double tests");

  MIN2MAX_FULL_DOUBLE_VECTOR

  allTwoCombRep(vectorFullDoubleTest, FUN2TEST, (Packet4d)dvmax.r, (Packet4d)dv36.r, (Packet4d)dv0.r,
                (Packet4d)dv_240.r, (Packet4d)dvmin.r);

  endTest();

  /* int = Packet8i (full) */
  beginTest("8 int tests");

  MIN2MAX_FULL_INT_VECTOR

  allTwoCombRep(vectorFullIntTest, FUN2TEST, (__m256i)ivmax.r, (__m256i)iv36.r, (__m256i)iv0.r, (__m256i)iv_240.r,
                (__m256i)ivmin.r);

  endTest();

  /* Eigen::half = Packet8h */
  beginTest("8 Eigen::half tests");

  MIN2MAX_HALF_HALF_VECTOR

  allTwoCombRep(vectorHalfEigenHalfTest, FUN2TEST, (__m128i)hvmax.r, (__m128i)hv36.r, (__m128i)hv0.r, (__m128i)hv_240.r,
                (__m128i)hvmin.r);

  endTest();

  /* bfloat16 = Packet8bf */
  beginTest("8 bfloat16 tests");

  MIN2MAX_HALF_BFLOAT16_VECTOR

  allTwoCombRep(vectorHalfBfloat16Test, FUN2TEST, (__m128i)bfvmax.r, (__m128i)bfv36.r, (__m128i)bfv0.r,
                (__m128i)bfv_240.r, (__m128i)bfvmin.r);

  endTest();

#endif

#ifdef __AVX2__
  /* long = Packet4l */
  beginTest("4 long tests");

  MIN2MAX_FULL_LONG_VECTOR

  allTwoCombRep(vectorFullLongTest, FUN2TEST, (__m256i)lvmax.r, (__m256i)lv36.r, (__m256i)lv0.r, (__m256i)lv_240.r,
                (__m256i)lvmin.r);

  endTest();

#endif

#ifdef __AVX512F__
#endif
}

addTest(FUN2TEST)

#endif  // EIGEN_MIPP_PMUL_TEST_H
