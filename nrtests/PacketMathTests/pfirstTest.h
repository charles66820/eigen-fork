#include <float.h>
#include <limits.h>

#ifndef EIGEN_MIPP_PFIRST_TEST_H
#define EIGEN_MIPP_PFIRST_TEST_H

#undef FUN2TEST
#define FUN2TEST pfirst

void pfirstTests() {
  printTestTitle(FUN2TEST);

#ifdef __SSE__
  /* float = Packet4f (half) */
  beginTest("4 float tests");
  {
    MIN2MAX_4_FLOAT_VECTOR_LOADED

    scalarSingleTypeTest(float, FUN2TEST, Packet4f, vmax);
    scalarSingleTypeTest(float, FUN2TEST, Packet4f, v36);
    scalarSingleTypeTest(float, FUN2TEST, Packet4f, v0);
    scalarSingleTypeTest(float, FUN2TEST, Packet4f, v_240);
    scalarSingleTypeTest(float, FUN2TEST, Packet4f, vmin);
  }
  endTest();

  /* double =  Packet2d (half) */
  beginTest("2 double tests");
  {
    MIN2MAX_2_DOUBLE_VECTOR_LOADED

    scalarSingleTypeTest(double, FUN2TEST, Packet2d, vmax);
    scalarSingleTypeTest(double, FUN2TEST, Packet2d, v36);
    scalarSingleTypeTest(double, FUN2TEST, Packet2d, v0);
    scalarSingleTypeTest(double, FUN2TEST, Packet2d, v_240);
    scalarSingleTypeTest(double, FUN2TEST, Packet2d, vmin);
  }
  endTest();

  /* int = Packet4i (half) */
  beginTest("4 int tests");
  {
    MIN2MAX_4_INT_VECTOR_LOADED

    scalarSingleTypeTest(int, FUN2TEST, Packet4i, vmax);
    scalarSingleTypeTest(int, FUN2TEST, Packet4i, v36);
    scalarSingleTypeTest(int, FUN2TEST, Packet4i, v0);
    scalarSingleTypeTest(int, FUN2TEST, Packet4i, v_240);
    scalarSingleTypeTest(int, FUN2TEST, Packet4i, vmin);
  }
  endTest();

  /* bool = Packet16b */
  beginTest("16 bool tests");
  {
    MIN2MAX_16_BOOL_VECTOR_LOADED

    scalarSingleTypeTest(bool, FUN2TEST, Packet16b, bvtrue);
    scalarSingleTypeTest(bool, FUN2TEST, Packet16b, bvfalse);
  }
  endTest();

#endif

#ifdef __AVX__
  /* float = Packet8f (full) */
  beginTest("8 float tests");
  {
    MIN2MAX_8_FLOAT_VECTOR_LOADED

    scalarSingleTypeTest(float, FUN2TEST, Packet8f, vmax);
    scalarSingleTypeTest(float, FUN2TEST, Packet8f, v36);
    scalarSingleTypeTest(float, FUN2TEST, Packet8f, v0);
    scalarSingleTypeTest(float, FUN2TEST, Packet8f, v_240);
    scalarSingleTypeTest(float, FUN2TEST, Packet8f, vmin);
  }
  endTest();

  /* double = Packet4d (full) */
  beginTest("4 double tests");
  {
    MIN2MAX_4_DOUBLE_VECTOR_LOADED

    scalarSingleTypeTest(double, FUN2TEST, Packet4d, vmax);
    scalarSingleTypeTest(double, FUN2TEST, Packet4d, v36);
    scalarSingleTypeTest(double, FUN2TEST, Packet4d, v0);
    scalarSingleTypeTest(double, FUN2TEST, Packet4d, v_240);
    scalarSingleTypeTest(double, FUN2TEST, Packet4d, vmin);
  }
  endTest();

  /* int = Packet8i (full) */
  beginTest("8 int tests");
  {
    MIN2MAX_8_INT_VECTOR_LOADED

    scalarSingleTypeTest(int, FUN2TEST, Packet8i, vmax);
    scalarSingleTypeTest(int, FUN2TEST, Packet8i, v36);
    scalarSingleTypeTest(int, FUN2TEST, Packet8i, v0);
    scalarSingleTypeTest(int, FUN2TEST, Packet8i, v_240);
    scalarSingleTypeTest(int, FUN2TEST, Packet8i, vmin);
  }
  endTest();

  /* Eigen::half = Packet8h */
  beginTest("8 Eigen::half tests");
  {
    MIN2MAX_8_HALF_VECTOR_LOADED

    scalarSingleTypeTest(Eigen::half, FUN2TEST, Packet8h, vmax);
    scalarSingleTypeTest(Eigen::half, FUN2TEST, Packet8h, v36);
    scalarSingleTypeTest(Eigen::half, FUN2TEST, Packet8h, v0);
    scalarSingleTypeTest(Eigen::half, FUN2TEST, Packet8h, vmin);
  }
  endTest();

  /* bfloat16 = Packet8bf */
  beginTest("8 bfloat16 tests");
  {
    MIN2MAX_8_BFLOAT16_VECTOR_LOADED

    scalarSingleTypeTest(bfloat16, FUN2TEST, Packet8bf, vmax);
    scalarSingleTypeTest(bfloat16, FUN2TEST, Packet8bf, v36);
    scalarSingleTypeTest(bfloat16, FUN2TEST, Packet8bf, v0);
    scalarSingleTypeTest(bfloat16, FUN2TEST, Packet8bf, v_240);
    scalarSingleTypeTest(bfloat16, FUN2TEST, Packet8bf, vmin);
  }
  endTest();

#endif

#ifdef __AVX2__
  /* long = Packet4l */
  beginTest("4 long tests");
  {
    MIN2MAX_4_LONG_VECTOR_LOADED

    scalarSingleTypeTest(long, FUN2TEST, Packet4l, vmax);
    scalarSingleTypeTest(long, FUN2TEST, Packet4l, v36);
    scalarSingleTypeTest(long, FUN2TEST, Packet4l, v0);
    scalarSingleTypeTest(long, FUN2TEST, Packet4l, v_240);
    scalarSingleTypeTest(long, FUN2TEST, Packet4l, vmin);
  }
  endTest();

#endif

#ifdef __AVX512F__
#endif
}

addTest(FUN2TEST)

#endif  // EIGEN_MIPP_PFIRST_TEST_H
