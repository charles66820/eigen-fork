#include <float.h>
#include <limits.h>
#include "../testVector.h"

#ifndef EIGEN_MIPP_PREDUX_MIN_TEST_H
#define EIGEN_MIPP_PREDUX_MIN_TEST_H

#undef FUN2TEST
#define FUN2TEST predux_min

void predux_minTests() {
  std::cout << printTestTitle(FUN2TEST) << std::endl;

#ifdef __SSE__
  /* float = Packet4f (half) */
  beginTest("half float tests");

  MIN2MAX_HALF_FLOAT_VECTOR

  scalarSingleTypeTest(float, FUN2TEST, Packet4f, fhvmax.r);
  scalarSingleTypeTest(float, FUN2TEST, Packet4f, fhv36.r);
  scalarSingleTypeTest(float, FUN2TEST, Packet4f, fhv0.r);
  scalarSingleTypeTest(float, FUN2TEST, Packet4f, fhv_240.r);
  scalarSingleTypeTest(float, FUN2TEST, Packet4f, fhvmin.r);

  endTest();

  /* double =  Packet2d (half) */
  beginTest("half double tests");

  MIN2MAX_HALF_DOUBLE_VECTOR

  scalarSingleTypeTest(double, FUN2TEST, Packet2d, (Packet2d)dhvmax.r);
  scalarSingleTypeTest(double, FUN2TEST, Packet2d, (Packet2d)dhv36.r);
  scalarSingleTypeTest(double, FUN2TEST, Packet2d, (Packet2d)dhv0.r);
  scalarSingleTypeTest(double, FUN2TEST, Packet2d, (Packet2d)dhv_240.r);
  scalarSingleTypeTest(double, FUN2TEST, Packet2d, (Packet2d)dhvmin.r);

  endTest();

  /* int = Packet4i (half) */
  beginTest("half int tests");

  MIN2MAX_HALF_INT_VECTOR

  scalarSingleTypeTest(int, FUN2TEST, Packet4i, (__m128i)ihvmax.r);
  scalarSingleTypeTest(int, FUN2TEST, Packet4i, (__m128i)ihv36.r);
  scalarSingleTypeTest(int, FUN2TEST, Packet4i, (__m128i)ihv0.r);
  scalarSingleTypeTest(int, FUN2TEST, Packet4i, (__m128i)ihv_240.r);
  scalarSingleTypeTest(int, FUN2TEST, Packet4i, (__m128i)ihvmin.r);

  endTest();

  /* bool = Packet16b */
  beginTest("bool tests");

  MIN2MAX_HALF_BOOL_VECTOR

  scalarSingleTypeTest(bool, FUN2TEST, Packet16b, (__m128i)bvtrue.r);
  scalarSingleTypeTest(bool, FUN2TEST, Packet16b, (__m128i)bvfalse.r);

  endTest();

#endif

#ifdef __AVX__
  /* float = Packet8f (full) */
  beginTest("full float tests");

  MIN2MAX_FULL_FLOAT_VECTOR

  scalarSingleTypeTest(float, FUN2TEST, Packet8f, fvmax.r);
  scalarSingleTypeTest(float, FUN2TEST, Packet8f, fv36.r);
  scalarSingleTypeTest(float, FUN2TEST, Packet8f, fv0.r);
  scalarSingleTypeTest(float, FUN2TEST, Packet8f, fv_240.r);
  scalarSingleTypeTest(float, FUN2TEST, Packet8f, fvmin.r);

  endTest();

  /* double = Packet4d (full) */
  beginTest("full double tests");

  MIN2MAX_FULL_DOUBLE_VECTOR

  scalarSingleTypeTest(double, FUN2TEST, Packet4d, (Packet4d)dvmax.r);
  scalarSingleTypeTest(double, FUN2TEST, Packet4d, (Packet4d)dv36.r);
  scalarSingleTypeTest(double, FUN2TEST, Packet4d, (Packet4d)dv0.r);
  scalarSingleTypeTest(double, FUN2TEST, Packet4d, (Packet4d)dv_240.r);
  scalarSingleTypeTest(double, FUN2TEST, Packet4d, (Packet4d)dvmin.r);

  endTest();

  /* int = Packet8i (full) */
  beginTest("full int tests");

  MIN2MAX_FULL_INT_VECTOR

  scalarSingleTypeTest(int, FUN2TEST, Packet8i, (__m256i)ivmax.r);
  scalarSingleTypeTest(int, FUN2TEST, Packet8i, (__m256i)iv36.r);
  scalarSingleTypeTest(int, FUN2TEST, Packet8i, (__m256i)iv0.r);
  scalarSingleTypeTest(int, FUN2TEST, Packet8i, (__m256i)iv_240.r);
  scalarSingleTypeTest(int, FUN2TEST, Packet8i, (__m256i)ivmin.r);

  endTest();

  /* Eigen::half = Packet8h */
  beginTest("Eigen::half tests");

  MIN2MAX_HALF_HALF_VECTOR

  scalarSingleTypeTest(Eigen::half, FUN2TEST, Packet8h, (__m128i)hvmax.r);
  scalarSingleTypeTest(Eigen::half, FUN2TEST, Packet8h, (__m128i)hv36.r);
  scalarSingleTypeTest(Eigen::half, FUN2TEST, Packet8h, (__m128i)hv0.r);
  scalarSingleTypeTest(Eigen::half, FUN2TEST, Packet8h, (__m128i)hvmin.r);

  endTest();

  /* bfloat16 = Packet8bf */
  beginTest("bfloat16 tests");

  MIN2MAX_HALF_BFLOAT16_VECTOR

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

  MIN2MAX_FULL_LONG_VECTOR

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

#endif  // EIGEN_MIPP_PREDUX_MIN_TEST_H
