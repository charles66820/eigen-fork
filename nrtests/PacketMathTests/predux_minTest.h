#include <float.h>
#include <limits.h>


#ifndef EIGEN_MIPP_PREDUX_MIN_TEST_H
#define EIGEN_MIPP_PREDUX_MIN_TEST_H

#undef FUN2TEST
#define FUN2TEST predux_min

void predux_minTests() {
  printTestTitle(FUN2TEST);

#ifdef __SSE__
  /* float = Packet4f (half) */
  beginTest("4 float tests");

  MIN2MAX_4_FLOAT_VECTOR

  scalarSingleTypeTest(float, FUN2TEST, Packet4f, fhvmax);
  scalarSingleTypeTest(float, FUN2TEST, Packet4f, fhv36);
  scalarSingleTypeTest(float, FUN2TEST, Packet4f, fhv0);
  scalarSingleTypeTest(float, FUN2TEST, Packet4f, fhv_240);
  scalarSingleTypeTest(float, FUN2TEST, Packet4f, fhvmin);

  endTest();

  /* double =  Packet2d (half) */
  beginTest("2 double tests");

  MIN2MAX_2_DOUBLE_VECTOR

  scalarSingleTypeTest(double, FUN2TEST, Packet2d, dhvmax);
  scalarSingleTypeTest(double, FUN2TEST, Packet2d, dhv36);
  scalarSingleTypeTest(double, FUN2TEST, Packet2d, dhv0);
  scalarSingleTypeTest(double, FUN2TEST, Packet2d, dhv_240);
  scalarSingleTypeTest(double, FUN2TEST, Packet2d, dhvmin);

  endTest();

  /* int = Packet4i (half) */
  beginTest("4 int tests");

  MIN2MAX_4_INT_VECTOR

  scalarSingleTypeTest(int, FUN2TEST, Packet4i, ihvmax);
  scalarSingleTypeTest(int, FUN2TEST, Packet4i, ihv36);
  scalarSingleTypeTest(int, FUN2TEST, Packet4i, ihv0);
  scalarSingleTypeTest(int, FUN2TEST, Packet4i, ihv_240);
  scalarSingleTypeTest(int, FUN2TEST, Packet4i, ihvmin);

  endTest();

  /* bool = Packet16b */
  beginTest("16 bool tests");

  MIN2MAX_16_BOOL_VECTOR

  scalarSingleTypeTest(bool, FUN2TEST, Packet16b, bvtrue);
  scalarSingleTypeTest(bool, FUN2TEST, Packet16b, bvfalse);

  endTest();

#endif

#ifdef __AVX__
  /* float = Packet8f (full) */
  beginTest("8 float tests");

  MIN2MAX_8_FLOAT_VECTOR

  scalarSingleTypeTest(float, FUN2TEST, Packet8f, fvmax);
  scalarSingleTypeTest(float, FUN2TEST, Packet8f, fv36);
  scalarSingleTypeTest(float, FUN2TEST, Packet8f, fv0);
  scalarSingleTypeTest(float, FUN2TEST, Packet8f, fv_240);
  scalarSingleTypeTest(float, FUN2TEST, Packet8f, fvmin);

  endTest();

  /* double = Packet4d (full) */
  beginTest("4 double tests");

  MIN2MAX_4_DOUBLE_VECTOR

  scalarSingleTypeTest(double, FUN2TEST, Packet4d, dvmax);
  scalarSingleTypeTest(double, FUN2TEST, Packet4d, dv36);
  scalarSingleTypeTest(double, FUN2TEST, Packet4d, dv0);
  scalarSingleTypeTest(double, FUN2TEST, Packet4d, dv_240);
  scalarSingleTypeTest(double, FUN2TEST, Packet4d, dvmin);

  endTest();

  /* int = Packet8i (full) */
  beginTest("8 int tests");

  MIN2MAX_8_INT_VECTOR

  scalarSingleTypeTest(int, FUN2TEST, Packet8i, ivmax);
  scalarSingleTypeTest(int, FUN2TEST, Packet8i, iv36);
  scalarSingleTypeTest(int, FUN2TEST, Packet8i, iv0);
  scalarSingleTypeTest(int, FUN2TEST, Packet8i, iv_240);
  scalarSingleTypeTest(int, FUN2TEST, Packet8i, ivmin);

  endTest();

  /* Eigen::half = Packet8h */
  beginTest("8 Eigen::half tests");

  MIN2MAX_8_HALF_VECTOR

  scalarSingleTypeTest(Eigen::half, FUN2TEST, Packet8h, hvmax);
  scalarSingleTypeTest(Eigen::half, FUN2TEST, Packet8h, hv36);
  scalarSingleTypeTest(Eigen::half, FUN2TEST, Packet8h, hv0);
  scalarSingleTypeTest(Eigen::half, FUN2TEST, Packet8h, hvmin);

  endTest();

  /* bfloat16 = Packet8bf */
  beginTest("8 bfloat16 tests");

  MIN2MAX_8_BFLOAT16_VECTOR

  scalarSingleTypeTest(bfloat16, FUN2TEST, Packet8bf, bfvmax);
  scalarSingleTypeTest(bfloat16, FUN2TEST, Packet8bf, bfv36);
  scalarSingleTypeTest(bfloat16, FUN2TEST, Packet8bf, bfv0);
  scalarSingleTypeTest(bfloat16, FUN2TEST, Packet8bf, bfv_240);
  scalarSingleTypeTest(bfloat16, FUN2TEST, Packet8bf, bfvmin);

  endTest();

#endif

#ifdef __AVX2__
  /* long = Packet4l */
  beginTest("4 long tests");

  MIN2MAX_4_LONG_VECTOR

  scalarSingleTypeTest(long, FUN2TEST, Packet4l, lvmax);
  scalarSingleTypeTest(long, FUN2TEST, Packet4l, lv36);
  scalarSingleTypeTest(long, FUN2TEST, Packet4l, lv0);
  scalarSingleTypeTest(long, FUN2TEST, Packet4l, lv_240);
  scalarSingleTypeTest(long, FUN2TEST, Packet4l, lvmin);

  endTest();

#endif

#ifdef __AVX512F__
#endif
}

addTest(FUN2TEST)

#endif  // EIGEN_MIPP_PREDUX_MIN_TEST_H
