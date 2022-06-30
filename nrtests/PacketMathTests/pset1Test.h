#include <float.h>
#include <limits.h>

#ifndef EIGEN_MIPP_PSET1_TEST_H
#define EIGEN_MIPP_PSET1_TEST_H

#undef FUN2TEST
#define FUN2TEST pset1

void pset1Tests() {
  printTestTitle(FUN2TEST);

#ifdef __SSE__
  /* float = Packet4f (half) */
  beginTest("4 float tests");

  min2MaxTests(vectorHalfFloatTemplateTest, FUN2TEST, Packet4f, FLT_MAX, 36.7f, 0.0f, -240.98f, FLT_MIN);

  endTest();

  /* double =  Packet2d (half) */
  beginTest("2 double tests");

  min2MaxTests(vectorHalfDoubleTemplateTest, FUN2TEST, Packet2d, DBL_MAX, 36.7d, 0.0d, -240.98d, DBL_MIN);

  endTest();

  /* int = Packet4i (half) */
  beginTest("4 int tests");

  min2MaxTests(vectorHalfIntTemplateTest, FUN2TEST, Packet4i, INT_MAX, 36, 0, -240, INT_MIN);

  endTest();

  /* bool = Packet16b */
  beginTest("16 bool tests");

  vectorHalfBoolTemplateTest(FUN2TEST, Packet16b, true);
  vectorHalfBoolTemplateTest(FUN2TEST, Packet16b, false);
  vectorHalfBoolTemplateTest(FUN2TEST, Packet16b, CHAR_MAX);
  vectorHalfBoolTemplateTest(FUN2TEST, Packet16b, CHAR_MIN);

  endTest();

#endif

#ifdef __AVX__
  /* float = Packet8f (full) */
  beginTest("8 float tests");

  min2MaxTests(vectorFullFloatTemplateTest, FUN2TEST, Packet8f, FLT_MAX, 36.7f, 0.0f, -240.98f, FLT_MIN);

  endTest();

  /* double = Packet4d (full) */
  beginTest("4 double tests");

  min2MaxTests(vectorFullDoubleTemplateTest, FUN2TEST, Packet4d, DBL_MAX, 36.7d, 0.0d, -240.98d, DBL_MIN);

  endTest();

  /* int = Packet8i (full) */
  beginTest("8 int tests");

  min2MaxTests(vectorFullIntTemplateTest, FUN2TEST, Packet8i, INT_MAX, 36, 0, -240, INT_MIN);

  endTest();

  /* Eigen::half = Packet8h */
  beginTest("8 Eigen::half tests");

  min2MaxTests(vectorHalfEigenHalfTemplateTest, FUN2TEST, Packet8h, half(FLT_MAX), half(36.7f), half(0.0f),
               half(-240.98f), half(FLT_MIN));

  endTest();

  /* bfloat16 = Packet8bf */
  beginTest("8 bfloat16 tests");

  min2MaxTests(vectorHalfBfloat16TemplateTest, FUN2TEST, Packet8bf, bfloat16(FLT_MAX), bfloat16(36.7f), bfloat16(0.0f),
               bfloat16(-240.98f), bfloat16(FLT_MIN));

  endTest();

#endif

#ifdef __AVX2__
  /* long = Packet4l */
  beginTest("4 long tests");

  min2MaxTests(vectorFullLongTemplateTest, FUN2TEST, Packet4l, LONG_MAX, 36L, 0L, -240L, LONG_MIN);

  endTest();

#endif

#ifdef __AVX512F__
#endif
}

addTest(FUN2TEST)

#endif  // EIGEN_MIPP_PSET1_TEST_H
