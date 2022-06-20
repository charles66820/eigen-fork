#include <float.h>
#include <limits.h>

#ifndef EIGEN_MIPP_PLSET_TEST_H
#define EIGEN_MIPP_PLSET_TEST_H

#undef FUN2TEST
#define FUN2TEST plset

void plsetTests() {
  std::cout << printTestTitle(FUN2TEST) << std::endl;

#ifdef __SSE__
  /* float = Packet4f (half) */
  beginTest("half float tests");

  dynHalfFloatTest(FUN2TEST, FLT_MAX);
  dynHalfFloatTest(FUN2TEST, 36.7f);
  dynHalfFloatTest(FUN2TEST, 0.0f);
  dynHalfFloatTest(FUN2TEST, -240.98f);
  dynHalfFloatTest(FUN2TEST, FLT_MIN);

  endTest();

  /* double =  Packet2d (half) */
  beginTest("half double tests");

  dynHalfDoubleTest(FUN2TEST, DBL_MAX);
  dynHalfDoubleTest(FUN2TEST, 36.7d);
  dynHalfDoubleTest(FUN2TEST, 0.0d);
  dynHalfDoubleTest(FUN2TEST, -240.98d);
  dynHalfDoubleTest(FUN2TEST, DBL_MIN);

  endTest();

  /* int = Packet4i (half) */
  beginTest("half int tests");

  dynHalfIntTest(FUN2TEST, INT_MAX);
  dynHalfIntTest(FUN2TEST, 36);
  dynHalfIntTest(FUN2TEST, 0);
  dynHalfIntTest(FUN2TEST, -240);
  dynHalfIntTest(FUN2TEST, INT_MIN);

  endTest();

#endif

#ifdef __AVX__
  /* float = Packet8f (full) */
  beginTest("full float tests");

  dynFullFloatTest(FUN2TEST, FLT_MAX);
  dynFullFloatTest(FUN2TEST, 36.7f);
  dynFullFloatTest(FUN2TEST, 0.0f);
  dynFullFloatTest(FUN2TEST, -240.98f);
  dynFullFloatTest(FUN2TEST, FLT_MIN);

  endTest();

  /* double = Packet4d (full) */
  beginTest("full double tests");

  dynFullDoubleTest(FUN2TEST, DBL_MAX);
  dynFullDoubleTest(FUN2TEST, 36.7d);
  dynFullDoubleTest(FUN2TEST, 0.0d);
  dynFullDoubleTest(FUN2TEST, -240.98d);
  dynFullDoubleTest(FUN2TEST, DBL_MIN);

  endTest();

  /* int = Packet8i (full) */
  beginTest("full int tests");

  dynFullIntTest(FUN2TEST, INT_MAX);
  dynFullIntTest(FUN2TEST, 36);
  dynFullIntTest(FUN2TEST, 0);
  dynFullIntTest(FUN2TEST, -240);
  dynFullIntTest(FUN2TEST, INT_MIN);

  endTest();

  /* Eigen::half = Packet8h */
  beginTest("Eigen::half tests");

  dynHalfEigenHalfTest(FUN2TEST, half(FLT_MAX));
  dynHalfEigenHalfTest(FUN2TEST, half(36.7f));
  dynHalfEigenHalfTest(FUN2TEST, half(0.0f));
  dynHalfEigenHalfTest(FUN2TEST, half(-240.98f));
  dynHalfEigenHalfTest(FUN2TEST, half(FLT_MIN));

  endTest();

  /* bfloat16 = Packet8bf */
  beginTest("bfloat16 tests");

  dynHalfBfloat16Test(FUN2TEST, bfloat16(FLT_MAX));
  dynHalfBfloat16Test(FUN2TEST, bfloat16(36.7f));
  dynHalfBfloat16Test(FUN2TEST, bfloat16(0.0f));
  dynHalfBfloat16Test(FUN2TEST, bfloat16(-240.98f));
  dynHalfBfloat16Test(FUN2TEST, bfloat16(FLT_MIN));

  endTest();

#endif

#ifdef __AVX2__
  /* long = Packet4l */
  beginTest("long tests");

  dynFullLongTest(FUN2TEST, LONG_MAX);
  dynFullLongTest(FUN2TEST, 36L);
  dynFullLongTest(FUN2TEST, 0L);
  dynFullLongTest(FUN2TEST, -240L);
  dynFullLongTest(FUN2TEST, LONG_MIN);

  endTest();

#endif

#ifdef __AVX512__
#endif
}

#endif  // EIGEN_MIPP_PLSET_TEST_H
