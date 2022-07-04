#include <float.h>
#include <limits.h>

#ifndef EIGEN_MIPP_PSET1_TEST_H
#define EIGEN_MIPP_PSET1_TEST_H

#undef FUN2TEST
#define FUN2TEST pset1

void pset1Tests() {
  printTestTitle(FUN2TEST);

#ifdef __SSE__
  // Packet4f (128)
  beginTest("4 float tests");

  min2MaxTests(vector128FloatTest, FUN2TEST, Packet4f, FLT_MAX, 36.7f, 0.0f, -240.98f, FLT_MIN);

  endTest();

  // Packet2d (128)
  beginTest("2 double tests");

  min2MaxTests(vector128DoubleTest, FUN2TEST, Packet2d, DBL_MAX, 36.7d, 0.0d, -240.98d, DBL_MIN);

  endTest();

  // Packet4i (128)
  beginTest("4 int tests");

  min2MaxTests(vector128IntTest, FUN2TEST, Packet4i, INT_MAX, 36, 0, -240, INT_MIN);

  endTest();

  // Packet16b (128)
  beginTest("16 bool tests");

  boolTests(vector128BoolTest, FUN2TEST, Packet16b, true, false);
  vector128BoolTest(FUN2TEST, Packet16b, CHAR_MAX);
  vector128BoolTest(FUN2TEST, Packet16b, CHAR_MIN);

  endTest();

#endif

#ifdef __AVX__
  // Packet8f (256)
  beginTest("8 float tests");

  min2MaxTests(vector256FloatTest, FUN2TEST, Packet8f, FLT_MAX, 36.7f, 0.0f, -240.98f, FLT_MIN);

  endTest();

  // Packet4d (256)
  beginTest("4 double tests");

  min2MaxTests(vector256DoubleTest, FUN2TEST, Packet4d, DBL_MAX, 36.7d, 0.0d, -240.98d, DBL_MIN);

  endTest();

  // Packet8i (256)
  beginTest("8 int tests");

  min2MaxTests(vector256IntTest, FUN2TEST, Packet8i, INT_MAX, 36, 0, -240, INT_MIN);

  endTest();

  // Packet8h (128)
  beginTest("8 Eigen::half tests");

  min2MaxTests(vector128EigenHalfTest, FUN2TEST, Packet8h, half(FLT_MAX), half(36.7f), half(0.0f),
               half(-240.98f), half(FLT_MIN));

  endTest();

  // Packet8bf (128) bfloat16
  beginTest("8 bfloat16 tests");

  min2MaxTests(vector128Bfloat16Test, FUN2TEST, Packet8bf, bfloat16(FLT_MAX), bfloat16(36.7f), bfloat16(0.0f),
               bfloat16(-240.98f), bfloat16(FLT_MIN));

  endTest();

#endif

#ifdef __AVX2__
  // Packet4l (256)
  beginTest("4 long tests");

  min2MaxTests(vector256LongTest, FUN2TEST, Packet4l, LONG_MAX, 36L, 0L, -240L, LONG_MIN);

  endTest();

#endif

#ifdef __AVX512F__
#endif
}

addTest(FUN2TEST)

#endif  // EIGEN_MIPP_PSET1_TEST_H
