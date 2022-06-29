#include <float.h>
#include <limits.h>


#ifndef EIGEN_MIPP_PREDUX_ANY_TEST_H
#define EIGEN_MIPP_PREDUX_ANY_TEST_H

#undef FUN2TEST
#define FUN2TEST predux_any

void predux_anyTests() {
  printTestTitle(FUN2TEST);

#ifdef __SSE__
  /* float = Packet4f (half) */
  beginTest("4 float tests");

  MIN2MAX_4_FLOAT_VECTOR

  scalarSingleTypeTest(bool, FUN2TEST, Packet4f, fhvmax);
  scalarSingleTypeTest(bool, FUN2TEST, Packet4f, fhv36);
  scalarSingleTypeTest(bool, FUN2TEST, Packet4f, fhv0);
  scalarSingleTypeTest(bool, FUN2TEST, Packet4f, fhv_240);
  scalarSingleTypeTest(bool, FUN2TEST, Packet4f, fhvmin);

  endTest();

  /* double =  Packet2d (half) */
  beginTest("2 double tests");

  MIN2MAX_2_DOUBLE_VECTOR

  scalarSingleTypeTest(bool, FUN2TEST, Packet2d, dhvmax);
  scalarSingleTypeTest(bool, FUN2TEST, Packet2d, dhv36);
  scalarSingleTypeTest(bool, FUN2TEST, Packet2d, dhv0);
  scalarSingleTypeTest(bool, FUN2TEST, Packet2d, dhv_240);
  scalarSingleTypeTest(bool, FUN2TEST, Packet2d, dhvmin);

  endTest();

  /* int = Packet4i (half) */
  beginTest("4 int tests");

  MIN2MAX_4_INT_VECTOR

  scalarSingleTypeTest(bool, FUN2TEST, Packet4i, ihvmax);
  scalarSingleTypeTest(bool, FUN2TEST, Packet4i, ihv36);
  scalarSingleTypeTest(bool, FUN2TEST, Packet4i, ihv0);
  scalarSingleTypeTest(bool, FUN2TEST, Packet4i, ihv_240);
  scalarSingleTypeTest(bool, FUN2TEST, Packet4i, ihvmin);

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

  scalarSingleTypeTest(bool, FUN2TEST, Packet8f, fvmax);
  scalarSingleTypeTest(bool, FUN2TEST, Packet8f, fv36);
  scalarSingleTypeTest(bool, FUN2TEST, Packet8f, fv0);
  scalarSingleTypeTest(bool, FUN2TEST, Packet8f, fv_240);
  scalarSingleTypeTest(bool, FUN2TEST, Packet8f, fvmin);

  endTest();

  /* double = Packet4d (full) */
  beginTest("4 double tests");

  MIN2MAX_4_DOUBLE_VECTOR

  scalarSingleTypeTest(bool, FUN2TEST, Packet4d, dvmax);
  scalarSingleTypeTest(bool, FUN2TEST, Packet4d, dv36);
  scalarSingleTypeTest(bool, FUN2TEST, Packet4d, dv0);
  scalarSingleTypeTest(bool, FUN2TEST, Packet4d, dv_240);
  scalarSingleTypeTest(bool, FUN2TEST, Packet4d, dvmin);

  endTest();

  /* int = Packet8i (full) */
  beginTest("8 int tests");

  MIN2MAX_8_INT_VECTOR

  scalarSingleTypeTest(bool, FUN2TEST, Packet8i, ivmax);
  scalarSingleTypeTest(bool, FUN2TEST, Packet8i, iv36);
  scalarSingleTypeTest(bool, FUN2TEST, Packet8i, iv0);
  scalarSingleTypeTest(bool, FUN2TEST, Packet8i, iv_240);
  scalarSingleTypeTest(bool, FUN2TEST, Packet8i, ivmin);

  endTest();

  /* Eigen::half = Packet8h */
  beginTest("8 Eigen::half tests");

  MIN2MAX_8_HALF_VECTOR

  scalarSingleTypeTest(bool, FUN2TEST, Packet8h, hvmax);
  scalarSingleTypeTest(bool, FUN2TEST, Packet8h, hv36);
  scalarSingleTypeTest(bool, FUN2TEST, Packet8h, hv0);
  scalarSingleTypeTest(bool, FUN2TEST, Packet8h, hvmin);

  endTest();

  /* bfloat16 = Packet8bf */
  beginTest("8 bfloat16 tests");

  MIN2MAX_8_BFLOAT16_VECTOR

  scalarSingleTypeTest(bool, FUN2TEST, Packet8bf, bfvmax);
  scalarSingleTypeTest(bool, FUN2TEST, Packet8bf, bfv36);
  scalarSingleTypeTest(bool, FUN2TEST, Packet8bf, bfv0);
  scalarSingleTypeTest(bool, FUN2TEST, Packet8bf, bfv_240);
  scalarSingleTypeTest(bool, FUN2TEST, Packet8bf, bfvmin);

  endTest();

#endif

#ifdef __AVX2__
  /* long = Packet4l */
  beginTest("4 long tests");

  MIN2MAX_4_LONG_VECTOR

  scalarSingleTypeTest(bool, FUN2TEST, Packet4l, lvmax);
  scalarSingleTypeTest(bool, FUN2TEST, Packet4l, lv36);
  scalarSingleTypeTest(bool, FUN2TEST, Packet4l, lv0);
  scalarSingleTypeTest(bool, FUN2TEST, Packet4l, lv_240);
  scalarSingleTypeTest(bool, FUN2TEST, Packet4l, lvmin);

  endTest();

#endif

#ifdef __AVX512F__
#endif
}

addTest(FUN2TEST)

#endif  // EIGEN_MIPP_PREDUX_ANY_TEST_H
