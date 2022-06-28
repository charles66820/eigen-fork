#include <float.h>
#include <limits.h>
#include "../testVector.h"

#ifndef EIGEN_MIPP_PFLOOR_TEST_H
#define EIGEN_MIPP_PFLOOR_TEST_H

#undef FUN2TEST
#define FUN2TEST pfloor

void pfloorTests() {
  std::cout << printTestTitle(FUN2TEST) << std::endl;

#ifdef __SSE__
  /* float = Packet4f (half) */
  beginTest("half float tests");

  MIN2MAX_HALF_FLOAT_VECTOR

  vectorHalfFloatTest(FUN2TEST, fhvmax.r);
  vectorHalfFloatTest(FUN2TEST, fhv36.r);
  vectorHalfFloatTest(FUN2TEST, fhv0.r);
  vectorHalfFloatTest(FUN2TEST, fhv_240.r);
  vectorHalfFloatTest(FUN2TEST, fhvmin.r);

  endTest();

  /* double =  Packet2d (half) */
  beginTest("half double tests");

  MIN2MAX_HALF_DOUBLE_VECTOR

  vectorHalfDoubleTest(FUN2TEST, (Packet2d)dhvmax.r);
  vectorHalfDoubleTest(FUN2TEST, (Packet2d)dhv36.r);
  vectorHalfDoubleTest(FUN2TEST, (Packet2d)dhv0.r);
  vectorHalfDoubleTest(FUN2TEST, (Packet2d)dhv_240.r);
  vectorHalfDoubleTest(FUN2TEST, (Packet2d)dhvmin.r);

  endTest();

#endif

#ifdef __AVX__
  /* float = Packet8f (full) */
  beginTest("full float tests");

  MIN2MAX_FULL_FLOAT_VECTOR

  vectorFullFloatTest(FUN2TEST, fvmax.r);
  vectorFullFloatTest(FUN2TEST, fv36.r);
  vectorFullFloatTest(FUN2TEST, fv0.r);
  vectorFullFloatTest(FUN2TEST, fv_240.r);
  vectorFullFloatTest(FUN2TEST, fvmin.r);

  endTest();

  /* double = Packet4d (full) */
  beginTest("full double tests");

  MIN2MAX_FULL_DOUBLE_VECTOR

  vectorFullDoubleTest(FUN2TEST, (Packet4d)dvmax.r);
  vectorFullDoubleTest(FUN2TEST, (Packet4d)dv36.r);
  vectorFullDoubleTest(FUN2TEST, (Packet4d)dv0.r);
  vectorFullDoubleTest(FUN2TEST, (Packet4d)dv_240.r);
  vectorFullDoubleTest(FUN2TEST, (Packet4d)dvmin.r);

  endTest();

  /* Eigen::half = Packet8h */
  beginTest("Eigen::half tests");

  MIN2MAX_HALF_HALF_VECTOR

  vectorHalfEigenHalfTest(FUN2TEST, (__m128i)hvmax.r);
  vectorHalfEigenHalfTest(FUN2TEST, (__m128i)hv36.r);
  vectorHalfEigenHalfTest(FUN2TEST, (__m128i)hv0.r);
  vectorHalfEigenHalfTest(FUN2TEST, (__m128i)hvmin.r);

  endTest();

  /* bfloat16 = Packet8bf */
  beginTest("bfloat16 tests");

  MIN2MAX_HALF_BFLOAT16_VECTOR

  vectorHalfBfloat16Test(FUN2TEST, (__m128i)bfvmax.r);
  vectorHalfBfloat16Test(FUN2TEST, (__m128i)bfv36.r);
  vectorHalfBfloat16Test(FUN2TEST, (__m128i)bfv0.r);
  vectorHalfBfloat16Test(FUN2TEST, (__m128i)bfv_240.r);
  vectorHalfBfloat16Test(FUN2TEST, (__m128i)bfvmin.r);

  endTest();

#endif

#ifdef __AVX2__
#endif

#ifdef __AVX512F__
#endif
}

addTest(FUN2TEST)

#endif  // EIGEN_MIPP_PFLOOR_TEST_H
