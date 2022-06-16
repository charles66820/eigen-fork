#include <float.h>
#include <limits.h>
#include "testVector.h"

#ifndef EIGEN_MIPP_PLOAD_TEST_H
#define EIGEN_MIPP_PLOAD_TEST_H

#undef FUN2TEST
#define FUN2TEST pload

#define runTest(vec, type, test, value, delta) \
  {                                            \
    vec(type, v, value, delta);                \
    test(FUN2TEST, v);                         \
  }

void ploadTests() {
  std::cout << printTestTitle(FUN2TEST) << std::endl;

#ifdef __SSE__
  /* float = Packet4f (half) */
  beginTest("half float tests");

  runTest(vector4, float, dynHalfFloatTest, FLT_MAX, -0.1f);
  runTest(vector4, float, dynHalfFloatTest, 36.7f, 0.1f);
  runTest(vector4, float, dynHalfFloatTest, 0.0f, 0.1f);
  runTest(vector4, float, dynHalfFloatTest, -240.98f, 0.1f);
  runTest(vector4, float, dynHalfFloatTest, FLT_MIN, 0.1f);

  endTest();

  /* double =  Packet2d (half) */
  beginTest("half double tests");

  runTest(vector2, double, dynHalfDoubleTest, DBL_MAX, -0.1d);
  runTest(vector2, double, dynHalfDoubleTest, 36.7d, 0.1d);
  runTest(vector2, double, dynHalfDoubleTest, 0.0d, 0.1d);
  runTest(vector2, double, dynHalfDoubleTest, -240.98d, 0.1d);
  runTest(vector2, double, dynHalfDoubleTest, DBL_MIN, 0.1d);

  endTest();

  /* int = Packet4i (half) */
  beginTest("half int tests");

  runTest(vector4, int, dynHalfIntTest, INT_MAX, -1);
  runTest(vector4, int, dynHalfIntTest, 36, 1);
  runTest(vector4, int, dynHalfIntTest, 0, 1);
  runTest(vector4, int, dynHalfIntTest, -240, 1);
  runTest(vector4, int, dynHalfIntTest, INT_MIN, 1);

  endTest();

  /* bool = Packet16b */
  beginTest("bool tests");

  runTest(vector16, bool, dynHalfBoolTest, true, 0);
  runTest(vector16, bool, dynHalfBoolTest, false, 0);

  endTest();

#endif

#ifdef __AVX__
  /* float = Packet8f (full) */
  beginTest("full float tests");

  runTest(vector8, float, dynFullFloatTest, FLT_MAX, -0.1f);
  runTest(vector8, float, dynFullFloatTest, 36.7f, 0.1f);
  runTest(vector8, float, dynFullFloatTest, 0.0f, 0.1f);
  runTest(vector8, float, dynFullFloatTest, -240.98f, 0.1f);
  runTest(vector8, float, dynFullFloatTest, FLT_MIN, 0.1f);

  endTest();

  /* double = Packet4d (full) */
  beginTest("full double tests");

  runTest(vector4, double, dynFullDoubleTest, DBL_MAX, -0.1d);
  runTest(vector4, double, dynFullDoubleTest, 36.7d, 0.1d);
  runTest(vector4, double, dynFullDoubleTest, 0.0d, 0.1d);
  runTest(vector4, double, dynFullDoubleTest, -240.98d, 0.1d);
  runTest(vector4, double, dynFullDoubleTest, DBL_MIN, 0.1d);

  endTest();

  /* int = Packet8i (full) */
  beginTest("full int tests");

  runTest(vector8, int, dynFullIntTest, INT_MAX, -1);
  runTest(vector8, int, dynFullIntTest, 36, 1);
  runTest(vector8, int, dynFullIntTest, 0, 1);
  runTest(vector8, int, dynFullIntTest, -240, 1);
  runTest(vector8, int, dynFullIntTest, INT_MIN, 1);

  endTest();

  /* Eigen::half = Packet8h */
  beginTest("Eigen::half tests");

  runTest(vector8, Eigen::half, dynHalfEigenHalfTest, half(FLT_MAX), half(-0.1f));
  runTest(vector8, Eigen::half, dynHalfEigenHalfTest, half(36.7f), half(0.1f));
  runTest(vector8, Eigen::half, dynHalfEigenHalfTest, half(0.0f), half(0.1f));
  runTest(vector8, Eigen::half, dynHalfEigenHalfTest, half(-240.98f), half(0.1f));
  runTest(vector8, Eigen::half, dynHalfEigenHalfTest, half(FLT_MIN), half(0.1f));

  endTest();

  /* bfloat16 = Packet8bf */
  beginTest("bfloat16 tests");

  runTest(vector8, bfloat16, dynHalfBfloat16Test, bfloat16(FLT_MAX), bfloat16(-0.1f));
  runTest(vector8, bfloat16, dynHalfBfloat16Test, bfloat16(36.7f), bfloat16(0.1f));
  runTest(vector8, bfloat16, dynHalfBfloat16Test, bfloat16(0.0f), bfloat16(0.1f));
  runTest(vector8, bfloat16, dynHalfBfloat16Test, bfloat16(-240.98f), bfloat16(0.1f));
  runTest(vector8, bfloat16, dynHalfBfloat16Test, bfloat16(FLT_MIN), bfloat16(0.1f));

  endTest();

#endif

#ifdef __AVX2__
  /* long = Packet4l */
  beginTest("long tests");

  runTest(vector4, long, dynFullLongTest, LONG_MAX, -1L);
  runTest(vector4, long, dynFullLongTest, 36L, 1L);
  runTest(vector4, long, dynFullLongTest, 0L, 1L);
  runTest(vector4, long, dynFullLongTest, -240L, 1L);
  runTest(vector4, long, dynFullLongTest, LONG_MIN, 1L);
#endif

#ifdef __AVX512__
#endif
}

#endif  // EIGEN_MIPP_PLOAD_TEST_H
