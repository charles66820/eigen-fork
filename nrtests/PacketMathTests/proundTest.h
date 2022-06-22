#include <float.h>
#include <limits.h>
#include "../testVector.h"

#ifndef EIGEN_MIPP_PROUND_TEST_H
#define EIGEN_MIPP_PROUND_TEST_H

#undef FUN2TEST
#define FUN2TEST pround

void proundTests() {
  std::cout << printTestTitle(FUN2TEST) << std::endl;

#ifdef __SSE__
  /* float = Packet4f (half) */
  beginTest("half float tests");

  loadVectorHalf(vector4, float, fhvmax, , Packet4f, FLT_MAX, 0.0f);
  loadVectorHalf(vector4, float, fhv36, , Packet4f, 36.7f, 0.0f);
  loadVectorHalf(vector4, float, fhv0, , Packet4f, 0.0f, 0.0f);
  loadVectorHalf(vector4, float, fhv_240, , Packet4f, -240.98f, 0.0f);
  loadVectorHalf(vector4, float, fhvmin, , Packet4f, FLT_MAX, 0.0f);

  vectorHalfFloatTest(FUN2TEST, fhvmax.r);
  vectorHalfFloatTest(FUN2TEST, fhv36.r);
  vectorHalfFloatTest(FUN2TEST, fhv0.r);
  vectorHalfFloatTest(FUN2TEST, fhv_240.r);
  vectorHalfFloatTest(FUN2TEST, fhvmin.r);

  endTest();

  /* double =  Packet2d (half) */
  beginTest("half double tests");

  loadVectorHalf(vector2, double, dhvmax, HALF_CAST, Packet2d, DBL_MAX, 0.0d);
  loadVectorHalf(vector2, double, dhv36, HALF_CAST, Packet2d, 36.7d, 0.0d);
  loadVectorHalf(vector2, double, dhv0, HALF_CAST, Packet2d, 0.0d, 0.0d);
  loadVectorHalf(vector2, double, dhv_240, HALF_CAST, Packet2d, -240.98d, 0.0d);
  loadVectorHalf(vector2, double, dhvmin, HALF_CAST, Packet2d, DBL_MIN, 0.0d);

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
  loadVectorFull(vector8, float, fvmax, , Packet8f, FLT_MAX, 0.0f);
  loadVectorFull(vector8, float, fv36, , Packet8f, 36.7f, 0.0f);
  loadVectorFull(vector8, float, fv0, , Packet8f, 0.0f, 0.0f);
  loadVectorFull(vector8, float, fv_240, , Packet8f, -240.98f, 0.0f);
  loadVectorFull(vector8, float, fvmin, , Packet8f, FLT_MAX, 0.0f);

  vectorFullFloatTest(FUN2TEST, fvmax.r);
  vectorFullFloatTest(FUN2TEST, fv36.r);
  vectorFullFloatTest(FUN2TEST, fv0.r);
  vectorFullFloatTest(FUN2TEST, fv_240.r);
  vectorFullFloatTest(FUN2TEST, fvmin.r);

  endTest();

  /* double = Packet4d (full) */
  beginTest("full double tests");

  loadVectorFull(vector4, double, dvmax, FULL_CAST, Packet4d, DBL_MAX, 0.0d);
  loadVectorFull(vector4, double, dv36, FULL_CAST, Packet4d, 36.7d, 0.0d);
  loadVectorFull(vector4, double, dv0, FULL_CAST, Packet4d, 0.0d, 0.0d);
  loadVectorFull(vector4, double, dv_240, FULL_CAST, Packet4d, -240.98d, 0.0d);
  loadVectorFull(vector4, double, dvmin, FULL_CAST, Packet4d, DBL_MIN, 0.0d);

  vectorFullDoubleTest(FUN2TEST, (Packet4d)dvmax.r);
  vectorFullDoubleTest(FUN2TEST, (Packet4d)dv36.r);
  vectorFullDoubleTest(FUN2TEST, (Packet4d)dv0.r);
  vectorFullDoubleTest(FUN2TEST, (Packet4d)dv_240.r);
  vectorFullDoubleTest(FUN2TEST, (Packet4d)dvmin.r);

  endTest();

  /* Eigen::half = Packet8h */
  beginTest("Eigen::half tests");

  loadVectorHalfRegType(vector8, Eigen::half, short, hvmax, INT_HALF_CAST, Packet8h, half(FLT_MAX), half(0.0f));
  loadVectorHalfRegType(vector8, Eigen::half, short, hv36, INT_HALF_CAST, Packet8h, half(36.7f), half(0.0f));
  loadVectorHalfRegType(vector8, Eigen::half, short, hv0, INT_HALF_CAST, Packet8h, half(0.0f), half(0.0f));
  loadVectorHalfRegType(vector8, Eigen::half, short, hv_240, INT_HALF_CAST, Packet8h, half(-240.98f), half(0.0f));
  loadVectorHalfRegType(vector8, Eigen::half, short, hvmin, INT_HALF_CAST, Packet8h, half(FLT_MAX), half(0.0f));

  vectorHalfEigenHalfTest(FUN2TEST, (__m128i)hvmax.r);
  vectorHalfEigenHalfTest(FUN2TEST, (__m128i)hv36.r);
  vectorHalfEigenHalfTest(FUN2TEST, (__m128i)hv0.r);
  vectorHalfEigenHalfTest(FUN2TEST, (__m128i)hvmin.r);

  endTest();

  /* bfloat16 = Packet8bf */
  beginTest("bfloat16 tests");

  loadVectorHalfRegType(vector8, bfloat16, short, bfvmax, INT_HALF_CAST, Packet8bf, bfloat16(FLT_MAX), bfloat16(0.0f));
  loadVectorHalfRegType(vector8, bfloat16, short, bfv36, INT_HALF_CAST, Packet8bf, bfloat16(36.7f), bfloat16(0.0f));
  loadVectorHalfRegType(vector8, bfloat16, short, bfv0, INT_HALF_CAST, Packet8bf, bfloat16(0.0f), bfloat16(0.0f));
  loadVectorHalfRegType(vector8, bfloat16, short, bfv_240, INT_HALF_CAST, Packet8bf, bfloat16(-240.98f),
                        bfloat16(0.0f));
  loadVectorHalfRegType(vector8, bfloat16, short, bfvmin, INT_HALF_CAST, Packet8bf, bfloat16(FLT_MAX), bfloat16(0.0f));

  vectorHalfBfloat16Test(FUN2TEST, (__m128i)bfvmax.r);
  vectorHalfBfloat16Test(FUN2TEST, (__m128i)bfv36.r);
  vectorHalfBfloat16Test(FUN2TEST, (__m128i)bfv0.r);
  vectorHalfBfloat16Test(FUN2TEST, (__m128i)bfv_240.r);
  vectorHalfBfloat16Test(FUN2TEST, (__m128i)bfvmin.r);

  endTest();

#endif

#ifdef __AVX2__
#endif

#ifdef __AVX512__
#endif
}

#endif  // EIGEN_MIPP_PROUND_TEST_H