#include <float.h>
#include <limits.h>

#ifndef EIGEN_MIPP_PSET1_TEST_H
#define EIGEN_MIPP_PSET1_TEST_H

#undef FUN2TEST
#define FUN2TEST pset1

void pset1Tests() {
  std::cout << printTestTitle(FUN2TEST) << std::endl;

#ifdef __SSE__
  /* float = Packet4f (half) */
  beginTest("half float tests");

  vectorHalfFloatTest(FUN2TEST, FLT_MAX);
  vectorHalfFloatTest(FUN2TEST, 36.7f);
  vectorHalfFloatTest(FUN2TEST, 0.0f);
  vectorHalfFloatTest(FUN2TEST, -240.98f);
  vectorHalfFloatTest(FUN2TEST, FLT_MIN);

  endTest();

  /* double =  Packet2d (half) */
  beginTest("half double tests");

  vectorHalfDoubleTest(FUN2TEST, DBL_MAX);
  vectorHalfDoubleTest(FUN2TEST, 36.7d);
  vectorHalfDoubleTest(FUN2TEST, 0.0d);
  vectorHalfDoubleTest(FUN2TEST, -240.98d);
  vectorHalfDoubleTest(FUN2TEST, DBL_MIN);

  endTest();

  /* int = Packet4i (half) */
  beginTest("half int tests");

  vectorHalfIntTest(FUN2TEST, INT_MAX);
  vectorHalfIntTest(FUN2TEST, 36);
  vectorHalfIntTest(FUN2TEST, 0);
  vectorHalfIntTest(FUN2TEST, -240);
  vectorHalfIntTest(FUN2TEST, INT_MIN);

  endTest();

  /* bool = Packet16b */
  beginTest("bool tests");

  vectorHalfBoolTest(FUN2TEST, true);
  vectorHalfBoolTest(FUN2TEST, false);
  vectorHalfBoolTest(FUN2TEST, CHAR_MAX);
  vectorHalfBoolTest(FUN2TEST, CHAR_MIN);

  endTest();

#endif

#ifdef __AVX__
  /* float = Packet8f (full) */
  beginTest("full float tests");

  vectorFullFloatTest(FUN2TEST, FLT_MAX);
  vectorFullFloatTest(FUN2TEST, 36.7f);
  vectorFullFloatTest(FUN2TEST, 0.0f);
  vectorFullFloatTest(FUN2TEST, -240.98f);
  vectorFullFloatTest(FUN2TEST, FLT_MIN);

  endTest();

  /* double = Packet4d (full) */
  beginTest("full double tests");

  vectorFullDoubleTest(FUN2TEST, DBL_MAX);
  vectorFullDoubleTest(FUN2TEST, 36.7d);
  vectorFullDoubleTest(FUN2TEST, 0.0d);
  vectorFullDoubleTest(FUN2TEST, -240.98d);
  vectorFullDoubleTest(FUN2TEST, DBL_MIN);

  endTest();

  /* int = Packet8i (full) */
  beginTest("full int tests");

  vectorFullIntTest(FUN2TEST, INT_MAX);
  vectorFullIntTest(FUN2TEST, 36);
  vectorFullIntTest(FUN2TEST, 0);
  vectorFullIntTest(FUN2TEST, -240);
  vectorFullIntTest(FUN2TEST, INT_MIN);

  endTest();

  /* Eigen::half = Packet8h */
  beginTest("Eigen::half tests");

  vectorHalfEigenHalfTest(FUN2TEST, half(FLT_MAX));
  vectorHalfEigenHalfTest(FUN2TEST, half(36.7f));
  vectorHalfEigenHalfTest(FUN2TEST, half(0.0f));
  vectorHalfEigenHalfTest(FUN2TEST, half(-240.98f));
  vectorHalfEigenHalfTest(FUN2TEST, half(FLT_MIN));

  endTest();

  /* bfloat16 = Packet8bf */
  beginTest("bfloat16 tests");

  vectorHalfBfloat16Test(FUN2TEST, bfloat16(FLT_MAX));
  vectorHalfBfloat16Test(FUN2TEST, bfloat16(36.7f));
  vectorHalfBfloat16Test(FUN2TEST, bfloat16(0.0f));
  vectorHalfBfloat16Test(FUN2TEST, bfloat16(-240.98f));
  vectorHalfBfloat16Test(FUN2TEST, bfloat16(FLT_MIN));

  endTest();

#endif

#ifdef __AVX2__
  /* long = Packet4l */
  beginTest("long tests");

  vectorFullLongTest(FUN2TEST, LONG_MAX);
  vectorFullLongTest(FUN2TEST, 36L);
  vectorFullLongTest(FUN2TEST, 0L);
  vectorFullLongTest(FUN2TEST, -240L);
  vectorFullLongTest(FUN2TEST, LONG_MIN);

  endTest();

#endif

#ifdef __AVX512__
#endif
}

#endif  // EIGEN_MIPP_PSET1_TEST_H
