#include <float.h>
#include <limits.h>
#include "../testVector.h"

#ifndef EIGEN_MIPP_PREDUX_MAX_TEST_H
#define EIGEN_MIPP_PREDUX_MAX_TEST_H

#undef FUN2TEST
#define FUN2TEST predux_max

void predux_maxTests() {
  std::cout << printTestTitle(FUN2TEST) << std::endl;

#ifdef __SSE__
  /* float = Packet4f (half) */
  beginTest("half float tests");

  loadVectorHalf(vector4, float, fhvmax, , Packet4f, FLT_MAX, 0.0f);
  loadVectorHalf(vector4, float, fhv36, , Packet4f, 36.7f, 0.0f);
  loadVectorHalf(vector4, float, fhv0, , Packet4f, 0.0f, 0.0f);
  loadVectorHalf(vector4, float, fhv_240, , Packet4f, -240.98f, 0.0f);
  loadVectorHalf(vector4, float, fhvmin, , Packet4f, FLT_MAX, 0.0f);

  scalarSingleTypeTest(float, FUN2TEST, Packet4f, fhvmax.r)
  scalarSingleTypeTest(float, FUN2TEST, Packet4f, fhv36.r);
  scalarSingleTypeTest(float, FUN2TEST, Packet4f, fhv0.r);
  scalarSingleTypeTest(float, FUN2TEST, Packet4f, fhv_240.r);
  scalarSingleTypeTest(float, FUN2TEST, Packet4f, fhvmin.r);

  endTest();

  /* double =  Packet2d (half) */
  beginTest("half double tests");

  loadVectorHalf(vector2, double, dhvmax, HALF_CAST, Packet2d, DBL_MAX, 0.0d);
  loadVectorHalf(vector2, double, dhv36, HALF_CAST, Packet2d, 36.7d, 0.0d);
  loadVectorHalf(vector2, double, dhv0, HALF_CAST, Packet2d, 0.0d, 0.0d);
  loadVectorHalf(vector2, double, dhv_240, HALF_CAST, Packet2d, -240.98d, 0.0d);
  loadVectorHalf(vector2, double, dhvmin, HALF_CAST, Packet2d, DBL_MIN, 0.0d);

  scalarSingleTypeTest(double, FUN2TEST, Packet2d, (Packet2d)dhvmax.r);
  scalarSingleTypeTest(double, FUN2TEST, Packet2d, (Packet2d)dhv36.r);
  scalarSingleTypeTest(double, FUN2TEST, Packet2d, (Packet2d)dhv0.r);
  scalarSingleTypeTest(double, FUN2TEST, Packet2d, (Packet2d)dhv_240.r);
  scalarSingleTypeTest(double, FUN2TEST, Packet2d, (Packet2d)dhvmin.r);

  endTest();

  /* int = Packet4i (half) */
  beginTest("half int tests");

  loadVectorHalf(vector4, int, ihvmax, INT_HALF_CAST, Packet4i, INT_MAX, 0);
  loadVectorHalf(vector4, int, ihv36, INT_HALF_CAST, Packet4i, 36, 0);
  loadVectorHalf(vector4, int, ihv0, INT_HALF_CAST, Packet4i, 0, 0);
  loadVectorHalf(vector4, int, ihv_240, INT_HALF_CAST, Packet4i, -240, 0);
  loadVectorHalf(vector4, int, ihvmin, INT_HALF_CAST, Packet4i, INT_MIN, 0);

  scalarSingleTypeTest(int, FUN2TEST, Packet4i, (__m128i)ihvmax.r);
  scalarSingleTypeTest(int, FUN2TEST, Packet4i, (__m128i)ihv36.r);
  scalarSingleTypeTest(int, FUN2TEST, Packet4i, (__m128i)ihv0.r);
  scalarSingleTypeTest(int, FUN2TEST, Packet4i, (__m128i)ihv_240.r);
  scalarSingleTypeTest(int, FUN2TEST, Packet4i, (__m128i)ihvmin.r);

  endTest();

  /* bool = Packet16b */
  beginTest("bool tests");

  loadVectorHalf(vector16, bool, bvtrue, INT_HALF_CAST, Packet16b, true, 0);
  loadVectorHalf(vector16, bool, bvfalse, INT_HALF_CAST, Packet16b, false, 0);

  scalarSingleTypeTest(bool, FUN2TEST, Packet16b, (__m128i)bvtrue.r);
  scalarSingleTypeTest(bool, FUN2TEST, Packet16b, (__m128i)bvfalse.r);

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

  scalarSingleTypeTest(float, FUN2TEST, Packet8f, fvmax.r);
  scalarSingleTypeTest(float, FUN2TEST, Packet8f, fv36.r);
  scalarSingleTypeTest(float, FUN2TEST, Packet8f, fv0.r);
  scalarSingleTypeTest(float, FUN2TEST, Packet8f, fv_240.r);
  scalarSingleTypeTest(float, FUN2TEST, Packet8f, fvmin.r);

  endTest();

  /* double = Packet4d (full) */
  beginTest("full double tests");

  loadVectorFull(vector4, double, dvmax, FULL_CAST, Packet4d, DBL_MAX, 0.0d);
  loadVectorFull(vector4, double, dv36, FULL_CAST, Packet4d, 36.7d, 0.0d);
  loadVectorFull(vector4, double, dv0, FULL_CAST, Packet4d, 0.0d, 0.0d);
  loadVectorFull(vector4, double, dv_240, FULL_CAST, Packet4d, -240.98d, 0.0d);
  loadVectorFull(vector4, double, dvmin, FULL_CAST, Packet4d, DBL_MIN, 0.0d);

  scalarSingleTypeTest(double, FUN2TEST, Packet4d, (Packet4d)dvmax.r);
  scalarSingleTypeTest(double, FUN2TEST, Packet4d, (Packet4d)dv36.r);
  scalarSingleTypeTest(double, FUN2TEST, Packet4d, (Packet4d)dv0.r);
  scalarSingleTypeTest(double, FUN2TEST, Packet4d, (Packet4d)dv_240.r);
  scalarSingleTypeTest(double, FUN2TEST, Packet4d, (Packet4d)dvmin.r);

  endTest();

  /* int = Packet8i (full) */
  beginTest("full int tests");

  loadVectorFull(vector8, int, ivmax, INT_FULL_CAST, Packet8i, INT_MAX, 0);
  loadVectorFull(vector8, int, iv36, INT_FULL_CAST, Packet8i, 36, 0);
  loadVectorFull(vector8, int, iv0, INT_FULL_CAST, Packet8i, 0, 0);
  loadVectorFull(vector8, int, iv_240, INT_FULL_CAST, Packet8i, -240, 0);
  loadVectorFull(vector8, int, ivmin, INT_FULL_CAST, Packet8i, INT_MIN, 0);

  scalarSingleTypeTest(int, FUN2TEST, Packet8i, (__m256i)ivmax.r);
  scalarSingleTypeTest(int, FUN2TEST, Packet8i, (__m256i)iv36.r);
  scalarSingleTypeTest(int, FUN2TEST, Packet8i, (__m256i)iv0.r);
  scalarSingleTypeTest(int, FUN2TEST, Packet8i, (__m256i)iv_240.r);
  scalarSingleTypeTest(int, FUN2TEST, Packet8i, (__m256i)ivmin.r);

  endTest();

  /* Eigen::half = Packet8h */
  beginTest("Eigen::half tests");

  loadVectorHalfRegType(vector8, Eigen::half, short, hvmax, INT_HALF_CAST, Packet8h, half(FLT_MAX), half(0.0f));
  loadVectorHalfRegType(vector8, Eigen::half, short, hv36, INT_HALF_CAST, Packet8h, half(36.7f), half(0.0f));
  loadVectorHalfRegType(vector8, Eigen::half, short, hv0, INT_HALF_CAST, Packet8h, half(0.0f), half(0.0f));
  loadVectorHalfRegType(vector8, Eigen::half, short, hv_240, INT_HALF_CAST, Packet8h, half(-240.98f), half(0.0f));
  loadVectorHalfRegType(vector8, Eigen::half, short, hvmin, INT_HALF_CAST, Packet8h, half(FLT_MAX), half(0.0f));

  scalarSingleTypeTest(Eigen::half, FUN2TEST, Packet8h, (__m128i)hvmax.r);
  scalarSingleTypeTest(Eigen::half, FUN2TEST, Packet8h, (__m128i)hv36.r);
  scalarSingleTypeTest(Eigen::half, FUN2TEST, Packet8h, (__m128i)hv0.r);
  scalarSingleTypeTest(Eigen::half, FUN2TEST, Packet8h, (__m128i)hvmin.r);

  endTest();

  /* bfloat16 = Packet8bf */
  beginTest("bfloat16 tests");

  loadVectorHalfRegType(vector8, bfloat16, short, bfvmax, INT_HALF_CAST, Packet8bf, bfloat16(FLT_MAX), bfloat16(0.0f));
  loadVectorHalfRegType(vector8, bfloat16, short, bfv36, INT_HALF_CAST, Packet8bf, bfloat16(36.7f), bfloat16(0.0f));
  loadVectorHalfRegType(vector8, bfloat16, short, bfv0, INT_HALF_CAST, Packet8bf, bfloat16(0.0f), bfloat16(0.0f));
  loadVectorHalfRegType(vector8, bfloat16, short, bfv_240, INT_HALF_CAST, Packet8bf, bfloat16(-240.98f),
                        bfloat16(0.0f));
  loadVectorHalfRegType(vector8, bfloat16, short, bfvmin, INT_HALF_CAST, Packet8bf, bfloat16(FLT_MAX), bfloat16(0.0f));

  scalarSingleTypeTest(bfloat16, FUN2TEST, Packet8bf, (__m128i)bfvmax.r);
  scalarSingleTypeTest(bfloat16, FUN2TEST, Packet8bf, (__m128i)bfv36.r);
  scalarSingleTypeTest(bfloat16, FUN2TEST, Packet8bf, (__m128i)bfv0.r);
  scalarSingleTypeTest(bfloat16, FUN2TEST, Packet8bf, (__m128i)bfv_240.r);
  scalarSingleTypeTest(bfloat16, FUN2TEST, Packet8bf, (__m128i)bfvmin.r);

  endTest();

#endif

#ifdef __AVX2__
  /* long = Packet4l */
  beginTest("long tests");

  loadVectorFull(vector4, long, lvmax, INT_FULL_CAST, Packet4l, LONG_MAX, 0L);
  loadVectorFull(vector4, long, lv36, INT_FULL_CAST, Packet4l, 36L, 0L);
  loadVectorFull(vector4, long, lv0, INT_FULL_CAST, Packet4l, 0L, 0L);
  loadVectorFull(vector4, long, lv_240, INT_FULL_CAST, Packet4l, -240L, 0L);
  loadVectorFull(vector4, long, lvmin, INT_FULL_CAST, Packet4l, LONG_MIN, 0L);

  scalarSingleTypeTest(long, FUN2TEST, Packet4l, (__m256i)lvmax.r);
  scalarSingleTypeTest(long, FUN2TEST, Packet4l, (__m256i)lv36.r);
  scalarSingleTypeTest(long, FUN2TEST, Packet4l, (__m256i)lv0.r);
  scalarSingleTypeTest(long, FUN2TEST, Packet4l, (__m256i)lv_240.r);
  scalarSingleTypeTest(long, FUN2TEST, Packet4l, (__m256i)lvmin.r);

  endTest();

#endif

#ifdef __AVX512F__
#endif
}

addTest(FUN2TEST)

#endif  // EIGEN_MIPP_PREDUX_MAX_TEST_H
