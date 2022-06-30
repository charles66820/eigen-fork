#include <float.h>
#include <limits.h>

#ifndef EIGEN_MIPP_PLOADU_TEST_H
#define EIGEN_MIPP_PLOADU_TEST_H

#undef FUN2TEST
#define FUN2TEST ploadu

void ploaduTests() {
  printTestTitle(FUN2TEST);

#ifdef __SSE__
  /* float = Packet4f (half) */
  beginTest("4 float tests");

  MIN2MAX_4_FLOAT_VECTOR_U

  min2MaxTests(vectorHalfFloatTest, FUN2TEST, fhvmax, fhv36, fhv0, fhv_240, fhvmin);

  endTest();

  /* double =  Packet2d (half) */
  beginTest("2 double tests");

  MIN2MAX_2_DOUBLE_VECTOR_U

  min2MaxTests(vectorHalfDoubleTest, FUN2TEST, dhvmax, dhv36, dhv0, dhvmin, dhv_240);

  endTest();

  /* int = Packet4i (half) */
  beginTest("4 int tests");

  MIN2MAX_4_INT_VECTOR_U

  min2MaxTests(vectorHalfIntTest, FUN2TEST, ihvmax, ihv36, ihv0, ihv_240, ihvmin);

  endTest();

  /* bool = Packet16b */
  beginTest("16 bool tests");

  MIN2MAX_16_BOOL_VECTOR_U

  vectorHalfBoolTest(FUN2TEST, bvtrue);
  vectorHalfBoolTest(FUN2TEST, bvfalse);

  endTest();

#endif

#ifdef __AVX__
  /* float = Packet8f (full) */
  beginTest("8 float tests");

  MIN2MAX_8_FLOAT_VECTOR_U

  min2MaxTests(vectorFullFloatTest, FUN2TEST, fvmax, fv36, fv0, fv_240, fvmin);

  endTest();

  /* double = Packet4d (full) */
  beginTest("4 double tests");

  MIN2MAX_4_DOUBLE_VECTOR_U

  min2MaxTests(vectorFullDoubleTest, FUN2TEST, dvmax, dv36, dv0, dv_240, dvmin);

  endTest();

  /* int = Packet8i (full) */
  beginTest("8 int tests");

  MIN2MAX_8_INT_VECTOR_U

  min2MaxTests(vectorFullIntTest, FUN2TEST, ivmax, iv36, iv0, iv_240, ivmin);

  endTest();

  /* Eigen::half = Packet8h */
  beginTest("8 Eigen::half tests");

  MIN2MAX_8_HALF_VECTOR_U

  min2MaxTests(vectorHalfEigenHalfTest, FUN2TEST, hvmax, hv36, hv0, hv_240, hvmin);

  endTest();

  /* bfloat16 = Packet8bf */
  beginTest("8 bfloat16 tests");

  MIN2MAX_8_BFLOAT16_VECTOR_U

  min2MaxTests(vectorHalfBfloat16Test, FUN2TEST, bfvmax, bfv36, bfv0, bfv_240, bfvmin);

  endTest();

#endif

#ifdef __AVX2__
  /* long = Packet4l */
  beginTest("4 long tests");

  MIN2MAX_4_LONG_VECTOR_U

  min2MaxTests(vectorFullLongTest, FUN2TEST, lvmax, lv36, lv0, lv_240, lvmin);

  endTest();

#endif

#ifdef __AVX512F__
#endif
}

addTest(FUN2TEST)

#endif  // EIGEN_MIPP_PLOADU_TEST_H
