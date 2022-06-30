#include <float.h>
#include <limits.h>

#ifndef EIGEN_MIPP_PSTOREU_TEST_H
#define EIGEN_MIPP_PSTOREU_TEST_H

#undef FUN2TEST
#define FUN2TEST pstoreu

void pstoreuTests() {
  printTestTitle(FUN2TEST);

#ifdef __SSE__
  /* float = Packet4f (half) */
  beginTest("4 float tests");

  MIN2MAX_4_FLOAT_VECTOR_LOADED

  uRefSingleType(FUN2TEST, float, 4, (Packet4f)fhvmax);
  uRefSingleType(FUN2TEST, float, 4, (Packet4f)fhv36);
  uRefSingleType(FUN2TEST, float, 4, (Packet4f)fhv0);
  uRefSingleType(FUN2TEST, float, 4, (Packet4f)fhv_240);
  uRefSingleType(FUN2TEST, float, 4, (Packet4f)fhvmin);

  endTest();

  /* double =  Packet2d (half) */
  beginTest("2 double tests");

  MIN2MAX_2_DOUBLE_VECTOR_LOADED

  uRefSingleType(FUN2TEST, double, 2, dhvmax);
  uRefSingleType(FUN2TEST, double, 2, dhv36);
  uRefSingleType(FUN2TEST, double, 2, dhv0);
  uRefSingleType(FUN2TEST, double, 2, dhv_240);
  uRefSingleType(FUN2TEST, double, 2, dhvmin);

  endTest();

  /* int = Packet4i (half) */
  beginTest("4 int tests");

  MIN2MAX_4_INT_VECTOR_LOADED

  uRefSingleType(FUN2TEST, int, 4, (Packet4i)ihvmax);
  uRefSingleType(FUN2TEST, int, 4, (Packet4i)ihv36);
  uRefSingleType(FUN2TEST, int, 4, (Packet4i)ihv0);
  uRefSingleType(FUN2TEST, int, 4, (Packet4i)ihv_240);
  uRefSingleType(FUN2TEST, int, 4, (Packet4i)ihvmin);

  endTest();

  /* bool = Packet16b */
  beginTest("16 bool tests");

  MIN2MAX_16_BOOL_VECTOR_LOADED

  uRefSingleType(FUN2TEST, bool, 16, (Packet16b)bvtrue);
  uRefSingleType(FUN2TEST, bool, 16, (Packet16b)bvfalse);

  endTest();

#endif

#ifdef __AVX__
  /* float = Packet8f (full) */
  beginTest("8 float tests");

  MIN2MAX_8_FLOAT_VECTOR_LOADED

  uRefSingleType(FUN2TEST, float, 8, (Packet8f)fvmax);
  uRefSingleType(FUN2TEST, float, 8, (Packet8f)fv36);
  uRefSingleType(FUN2TEST, float, 8, (Packet8f)fv0);
  uRefSingleType(FUN2TEST, float, 8, (Packet8f)fv_240);
  uRefSingleType(FUN2TEST, float, 8, (Packet8f)fvmin);

  endTest();

  /* double = Packet4d (full) */
  beginTest("4 double tests");

  MIN2MAX_4_DOUBLE_VECTOR_LOADED

  uRefSingleType(FUN2TEST, double, 4, dvmax);
  uRefSingleType(FUN2TEST, double, 4, dv36);
  uRefSingleType(FUN2TEST, double, 4, dv0);
  uRefSingleType(FUN2TEST, double, 4, dv_240);
  uRefSingleType(FUN2TEST, double, 4, dvmin);

  endTest();

  /* int = Packet8i (full) */
  beginTest("8 int tests");

  MIN2MAX_8_INT_VECTOR_LOADED

  uRefSingleType(FUN2TEST, int, 8, (Packet8i)ivmax);
  uRefSingleType(FUN2TEST, int, 8, (Packet8i)iv36);
  uRefSingleType(FUN2TEST, int, 8, (Packet8i)iv0);
  uRefSingleType(FUN2TEST, int, 8, (Packet8i)iv_240);
  uRefSingleType(FUN2TEST, int, 8, (Packet8i)ivmin);

  endTest();

  /* Eigen::half = Packet8h */
  beginTest("8 Eigen::half tests");

  MIN2MAX_8_HALF_VECTOR_LOADED

  uRefSingleType(FUN2TEST, Eigen::half, 8, (Packet8h)hvmax);
  uRefSingleType(FUN2TEST, Eigen::half, 8, (Packet8h)hv36);
  uRefSingleType(FUN2TEST, Eigen::half, 8, (Packet8h)hv0);
  uRefSingleType(FUN2TEST, Eigen::half, 8, (Packet8h)hv_240);
  uRefSingleType(FUN2TEST, Eigen::half, 8, (Packet8h)hvmin);

  endTest();

  /* bfloat16 = Packet8bf */
  beginTest("8 bfloat16 tests");

  MIN2MAX_8_BFLOAT16_VECTOR_LOADED

  uRefSingleType(FUN2TEST, bfloat16, 8, (Packet8bf)bfvmax);
  uRefSingleType(FUN2TEST, bfloat16, 8, (Packet8bf)bfv36);
  uRefSingleType(FUN2TEST, bfloat16, 8, (Packet8bf)bfv0);
  uRefSingleType(FUN2TEST, bfloat16, 8, (Packet8bf)bfv_240);
  uRefSingleType(FUN2TEST, bfloat16, 8, (Packet8bf)bfvmin);

  endTest();

#endif

#ifdef __AVX2__
  /* long = Packet4l */
  beginTest("4 long tests");

  MIN2MAX_4_LONG_VECTOR_LOADED

  uRefSingleType(FUN2TEST, long, 4, (Packet4l)lvmax);
  uRefSingleType(FUN2TEST, long, 4, (Packet4l)lv36);
  uRefSingleType(FUN2TEST, long, 4, (Packet4l)lv0);
  uRefSingleType(FUN2TEST, long, 4, (Packet4l)lv_240);
  uRefSingleType(FUN2TEST, long, 4, (Packet4l)lvmin);

  endTest();

#endif

#ifdef __AVX512F__
#endif
}

addTest(FUN2TEST)

#endif  // EIGEN_MIPP_PSTOREU_TEST_H
