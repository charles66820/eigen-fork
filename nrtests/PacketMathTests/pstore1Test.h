#include <float.h>
#include <limits.h>
#include "../testVector.h"

#ifndef EIGEN_MIPP_PSTORE1_TEST_H
#define EIGEN_MIPP_PSTORE1_TEST_H

#undef FUN2TEST
#define FUN2TEST pstore1

void pstore1Tests() {
  std::cout << printTestTitle(FUN2TEST) << std::endl;

#ifdef __SSE__
  /* float = Packet4f (half) */
  beginTest("4 float tests");

  refSingleType(FUN2TEST, float, 4, FLT_MAX);
  refSingleType(FUN2TEST, float, 4, 36.7f);
  refSingleType(FUN2TEST, float, 4, 0.0f);
  refSingleType(FUN2TEST, float, 4, -240.98f);
  refSingleType(FUN2TEST, float, 4, FLT_MAX);

  endTest();

  /* double =  Packet2d (half) */
  beginTest("2 double tests");

  refSingleType(FUN2TEST, double, 2, DBL_MAX);
  refSingleType(FUN2TEST, double, 2, 36.7d);
  refSingleType(FUN2TEST, double, 2, 0.0d);
  refSingleType(FUN2TEST, double, 2, -240.98d);
  refSingleType(FUN2TEST, double, 2, DBL_MIN);

  endTest();

  /* int = Packet4i (half) */
  beginTest("4 int tests");

  refSingleType(FUN2TEST, int, 4, INT_MAX);
  refSingleType(FUN2TEST, int, 4, 36);
  refSingleType(FUN2TEST, int, 4, 0);
  refSingleType(FUN2TEST, int, 4, -240);
  refSingleType(FUN2TEST, int, 4, INT_MIN);

  endTest();

  /* bool = Packet16b */
  beginTest("16 bool tests");

  refSingleType(FUN2TEST, bool, 16, true);
  refSingleType(FUN2TEST, bool, 16, false);

  endTest();

#endif

#ifdef __AVX__
  /* float = Packet8f (full) */
  beginTest("8 float tests");

  refSingleType(FUN2TEST, float, 8, FLT_MAX);
  refSingleType(FUN2TEST, float, 8, 36.7f);
  refSingleType(FUN2TEST, float, 8, 0.0f);
  refSingleType(FUN2TEST, float, 8, -240.98f);
  refSingleType(FUN2TEST, float, 8, FLT_MAX);

  endTest();

  /* double = Packet4d (full) */
  beginTest("4 double tests");

  refSingleType(FUN2TEST, double, 4, DBL_MAX);
  refSingleType(FUN2TEST, double, 4, 36.7d);
  refSingleType(FUN2TEST, double, 4, 0.0d);
  refSingleType(FUN2TEST, double, 4, -240.98d);
  refSingleType(FUN2TEST, double, 4, DBL_MIN);

  endTest();

  /* int = Packet8i (full) */
  beginTest("8 int tests");

  refSingleType(FUN2TEST, int, 8, INT_MAX);
  refSingleType(FUN2TEST, int, 8, 36);
  refSingleType(FUN2TEST, int, 8, 0);
  refSingleType(FUN2TEST, int, 8, -240);
  refSingleType(FUN2TEST, int, 8, INT_MIN);

  endTest();

  /* Eigen::half = Packet8h */
  beginTest("8 Eigen::half tests");

  refSingleType(FUN2TEST, Eigen::half, 8, half(FLT_MAX));
  refSingleType(FUN2TEST, Eigen::half, 8, half(36.7f));
  refSingleType(FUN2TEST, Eigen::half, 8, half(0.0f));
  refSingleType(FUN2TEST, Eigen::half, 8, half(-240.98f));
  refSingleType(FUN2TEST, Eigen::half, 8, half(FLT_MAX));

  endTest();

  /* bfloat16 = Packet8bf */
  beginTest("8 bfloat16 tests");

  refSingleType(FUN2TEST, bfloat16, 8, bfloat16(FLT_MAX));
  refSingleType(FUN2TEST, bfloat16, 8, bfloat16(36.7f));
  refSingleType(FUN2TEST, bfloat16, 8, bfloat16(0.0f));
  refSingleType(FUN2TEST, bfloat16, 8, bfloat16(-240.98f));
  refSingleType(FUN2TEST, bfloat16, 8, bfloat16(FLT_MAX));

  endTest();

#endif

#ifdef __AVX2__
  /* long = Packet4l */
  beginTest("4 long tests");

  refSingleType(FUN2TEST, long, 4, LONG_MAX);
  refSingleType(FUN2TEST, long, 4, 36L);
  refSingleType(FUN2TEST, long, 4, 0L);
  refSingleType(FUN2TEST, long, 4, -240L);
  refSingleType(FUN2TEST, long, 4, LONG_MIN);

  endTest();

#endif

#ifdef __AVX512F__
#endif
}

addTest(FUN2TEST)

#endif  // EIGEN_MIPP_PSTORE1_TEST_H
