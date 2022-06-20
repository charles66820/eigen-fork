#include <float.h>
#include <limits.h>
#include "testVector.h"

#ifndef EIGEN_MIPP_PLOAD1_TEST_H
#define EIGEN_MIPP_PLOAD1_TEST_H

#undef FUN2TEST
#define FUN2TEST pload1

#define runTest(vec, type, test, value, delta) \
  {                                            \
    vec(type, v, value, delta);                \
    test(FUN2TEST, v);                         \
  }

void pload1Tests() {
  std::cout << printTestTitle(FUN2TEST) << std::endl;

#ifdef __SSE__

#if EIGEN_COMP_GNUC_STRICT && (!defined __AVX__)
  /* float = Packet4f (half) */
  beginTest("half float tests");

  runTest(vector4, float, dynHalfFloatTest, FLT_MAX, -0.1f);
  runTest(vector4, float, dynHalfFloatTest, 36.7f, 0.1f);
  runTest(vector4, float, dynHalfFloatTest, 0.0f, 0.1f);
  runTest(vector4, float, dynHalfFloatTest, -240.98f, 0.1f);
  runTest(vector4, float, dynHalfFloatTest, FLT_MIN, 0.1f);

  endTest();

#endif

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

#endif

#ifdef __AVX2__
  /* long = Packet4l */
  beginTest("long tests");

  runTest(vector4, long, dynFullLongTest, LONG_MAX, -1L);
  runTest(vector4, long, dynFullLongTest, 36L, 1L);
  runTest(vector4, long, dynFullLongTest, 0L, 1L);
  runTest(vector4, long, dynFullLongTest, -240L, 1L);
  runTest(vector4, long, dynFullLongTest, LONG_MIN, 1L);

  endTest();

#endif

#ifdef __AVX512__
#endif
}

#endif  // EIGEN_MIPP_PLOAD1_TEST_H
