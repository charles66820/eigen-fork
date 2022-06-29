#include <float.h>
#include <limits.h>


#ifndef EIGEN_MIPP_PLOADU_TEST_H
#define EIGEN_MIPP_PLOADU_TEST_H

#undef FUN2TEST
#define FUN2TEST ploadu

#define runTest(vec, type, test, value, delta) \
  {                                            \
    vec(type, v, value, delta);                \
    test(FUN2TEST, v);                         \
  }

void ploaduTests() {
  printTestTitle(FUN2TEST);

#ifdef __SSE__
  /* float = Packet4f (half) */
  beginTest("4 float tests");

  runTest(vector4u, float, vectorHalfFloatTest, FLT_MAX, -0.1f);
  runTest(vector4u, float, vectorHalfFloatTest, 36.7f, 0.1f);
  runTest(vector4u, float, vectorHalfFloatTest, 0.0f, 0.1f);
  runTest(vector4u, float, vectorHalfFloatTest, -240.98f, 0.1f);
  runTest(vector4u, float, vectorHalfFloatTest, FLT_MIN, 0.1f);

  endTest();

  /* double =  Packet2d (half) */
  beginTest("2 double tests");

  runTest(vector2u, double, vectorHalfDoubleTest, DBL_MAX, -0.1d);
  runTest(vector2u, double, vectorHalfDoubleTest, 36.7d, 0.1d);
  runTest(vector2u, double, vectorHalfDoubleTest, 0.0d, 0.1d);
  runTest(vector2u, double, vectorHalfDoubleTest, -240.98d, 0.1d);
  runTest(vector2u, double, vectorHalfDoubleTest, DBL_MIN, 0.1d);

  endTest();

  /* int = Packet4i (half) */
  beginTest("4 int tests");

  runTest(vector4u, int, vectorHalfIntTest, INT_MAX, -1);
  runTest(vector4u, int, vectorHalfIntTest, 36, 1);
  runTest(vector4u, int, vectorHalfIntTest, 0, 1);
  runTest(vector4u, int, vectorHalfIntTest, -240, 1);
  runTest(vector4u, int, vectorHalfIntTest, INT_MIN, 1);

  endTest();

  /* bool = Packet16b */
  beginTest("16 bool tests");

  runTest(vector16u, bool, vectorHalfBoolTest, true, 0);
  runTest(vector16u, bool, vectorHalfBoolTest, false, 0);

  endTest();

#endif

#ifdef __AVX__
  /* float = Packet8f (full) */
  beginTest("8 float tests");

  runTest(vector8u, float, vectorFullFloatTest, FLT_MAX, -0.1f);
  runTest(vector8u, float, vectorFullFloatTest, 36.7f, 0.1f);
  runTest(vector8u, float, vectorFullFloatTest, 0.0f, 0.1f);
  runTest(vector8u, float, vectorFullFloatTest, -240.98f, 0.1f);
  runTest(vector8u, float, vectorFullFloatTest, FLT_MIN, 0.1f);

  endTest();

  /* double = Packet4d (full) */
  beginTest("4 double tests");

  runTest(vector4u, double, vectorFullDoubleTest, DBL_MAX, -0.1d);
  runTest(vector4u, double, vectorFullDoubleTest, 36.7d, 0.1d);
  runTest(vector4u, double, vectorFullDoubleTest, 0.0d, 0.1d);
  runTest(vector4u, double, vectorFullDoubleTest, -240.98d, 0.1d);
  runTest(vector4u, double, vectorFullDoubleTest, DBL_MIN, 0.1d);

  endTest();

  /* int = Packet8i (full) */
  beginTest("8 int tests");

  runTest(vector8u, int, vectorFullIntTest, INT_MAX, -1);
  runTest(vector8u, int, vectorFullIntTest, 36, 1);
  runTest(vector8u, int, vectorFullIntTest, 0, 1);
  runTest(vector8u, int, vectorFullIntTest, -240, 1);
  runTest(vector8u, int, vectorFullIntTest, INT_MIN, 1);

  endTest();

  /* Eigen::half = Packet8h */
  beginTest("8 Eigen::half tests");

  runTest(vector8u, Eigen::half, vectorHalfEigenHalfTest, half(FLT_MAX), half(-0.1f));
  runTest(vector8u, Eigen::half, vectorHalfEigenHalfTest, half(36.7f), half(0.1f));
  runTest(vector8u, Eigen::half, vectorHalfEigenHalfTest, half(0.0f), half(0.1f));
  runTest(vector8u, Eigen::half, vectorHalfEigenHalfTest, half(-240.98f), half(0.1f));
  runTest(vector8u, Eigen::half, vectorHalfEigenHalfTest, half(FLT_MIN), half(0.1f));

  endTest();

  /* bfloat16 = Packet8bf */
  beginTest("8 bfloat16 tests");

  runTest(vector8u, bfloat16, vectorHalfBfloat16Test, bfloat16(FLT_MAX), bfloat16(-0.1f));
  runTest(vector8u, bfloat16, vectorHalfBfloat16Test, bfloat16(36.7f), bfloat16(0.1f));
  runTest(vector8u, bfloat16, vectorHalfBfloat16Test, bfloat16(0.0f), bfloat16(0.1f));
  runTest(vector8u, bfloat16, vectorHalfBfloat16Test, bfloat16(-240.98f), bfloat16(0.1f));
  runTest(vector8u, bfloat16, vectorHalfBfloat16Test, bfloat16(FLT_MIN), bfloat16(0.1f));

  endTest();

#endif

#ifdef __AVX2__
  /* long = Packet4l */
  beginTest("4 long tests");

  runTest(vector4u, long, vectorFullLongTest, LONG_MAX, -1L);
  runTest(vector4u, long, vectorFullLongTest, 36L, 1L);
  runTest(vector4u, long, vectorFullLongTest, 0L, 1L);
  runTest(vector4u, long, vectorFullLongTest, -240L, 1L);
  runTest(vector4u, long, vectorFullLongTest, LONG_MIN, 1L);

  endTest();

#endif

#ifdef __AVX512F__
#endif
}

addTest(FUN2TEST)

#endif  // EIGEN_MIPP_PLOADU_TEST_H
