#include <float.h>
#include <limits.h>

#ifndef EIGEN_MIPP_PREDUX_TEST_H
#define EIGEN_MIPP_PREDUX_TEST_H

#undef FUN2TEST
#define FUN2TEST predux

void preduxTests() {
  printTestTitle(FUN2TEST);

#ifdef __SSE__
  // Packet4f (128)
  beginTest("4 float tests");
  {
    MIN2MAX_FLOAT_VECTOR_LOADED(4);

    scalarSingleTypeTest(float, FUN2TEST, Packet4f, vmax);
    scalarSingleTypeTest(float, FUN2TEST, Packet4f, v36);
    scalarSingleTypeTest(float, FUN2TEST, Packet4f, v0);
    scalarSingleTypeTest(float, FUN2TEST, Packet4f, v_240);
    scalarSingleTypeTest(float, FUN2TEST, Packet4f, vmin);
  }
  endTest();

  // Packet2d (128)
  beginTest("2 double tests");
  {
    MIN2MAX_DOUBLE_VECTOR_LOADED(2);

    scalarSingleTypeTest(double, FUN2TEST, Packet2d, vmax);
    scalarSingleTypeTest(double, FUN2TEST, Packet2d, v36);
    scalarSingleTypeTest(double, FUN2TEST, Packet2d, v0);
    scalarSingleTypeTest(double, FUN2TEST, Packet2d, v_240);
    scalarSingleTypeTest(double, FUN2TEST, Packet2d, vmin);
  }
  endTest();

  // Packet4i (128)
  beginTest("4 int tests");
  {
    MIN2MAX_INT_VECTOR_LOADED(4);

    scalarSingleTypeTest(int, FUN2TEST, Packet4i, vmax);
    scalarSingleTypeTest(int, FUN2TEST, Packet4i, v36);
    scalarSingleTypeTest(int, FUN2TEST, Packet4i, v0);
    scalarSingleTypeTest(int, FUN2TEST, Packet4i, v_240);
    scalarSingleTypeTest(int, FUN2TEST, Packet4i, vmin);
  }
  endTest();

  // Packet16b (128)
  beginTest("16 bool tests");
  {
    MIN2MAX_BOOL_VECTOR_LOADED(16);

    scalarSingleTypeTest(bool, FUN2TEST, Packet16b, bvtrue);
    scalarSingleTypeTest(bool, FUN2TEST, Packet16b, bvfalse);
  }
  endTest();

#endif

#ifdef __AVX__
  // Packet8f (256)
  beginTest("8 float tests");
  {
    MIN2MAX_FLOAT_VECTOR_LOADED(8);

    scalarSingleTypeTest(float, FUN2TEST, Packet8f, vmax);
    scalarSingleTypeTest(float, FUN2TEST, Packet8f, v36);
    scalarSingleTypeTest(float, FUN2TEST, Packet8f, v0);
    scalarSingleTypeTest(float, FUN2TEST, Packet8f, v_240);
    scalarSingleTypeTest(float, FUN2TEST, Packet8f, vmin);
  }
  endTest();

  // Packet4d (256)
  beginTest("4 double tests");
  {
    MIN2MAX_DOUBLE_VECTOR_LOADED(4);

    scalarSingleTypeTest(double, FUN2TEST, Packet4d, vmax);
    scalarSingleTypeTest(double, FUN2TEST, Packet4d, v36);
    scalarSingleTypeTest(double, FUN2TEST, Packet4d, v0);
    scalarSingleTypeTest(double, FUN2TEST, Packet4d, v_240);
    scalarSingleTypeTest(double, FUN2TEST, Packet4d, vmin);
  }
  endTest();

  // Packet8i (256)
  beginTest("8 int tests");
  {
    MIN2MAX_INT_VECTOR_LOADED(8);

    scalarSingleTypeTest(int, FUN2TEST, Packet8i, vmax);
    scalarSingleTypeTest(int, FUN2TEST, Packet8i, v36);
    scalarSingleTypeTest(int, FUN2TEST, Packet8i, v0);
    scalarSingleTypeTest(int, FUN2TEST, Packet8i, v_240);
    scalarSingleTypeTest(int, FUN2TEST, Packet8i, vmin);
  }
  endTest();

  // Packet8h (128)
  beginTest("8 Eigen::half tests");
  {
    MIN2MAX_HALF_VECTOR_LOADED(8);

    scalarSingleTypeTest(Eigen::half, FUN2TEST, Packet8h, vmax);
    scalarSingleTypeTest(Eigen::half, FUN2TEST, Packet8h, v36);
    scalarSingleTypeTest(Eigen::half, FUN2TEST, Packet8h, v0);
    scalarSingleTypeTest(Eigen::half, FUN2TEST, Packet8h, vmin);
  }
  endTest();

  // Packet8bf (128) bfloat16
  beginTest("8 bfloat16 tests");
  {
    MIN2MAX_BFLOAT16_VECTOR_LOADED(8);

    scalarSingleTypeTest(bfloat16, FUN2TEST, Packet8bf, vmax);
    scalarSingleTypeTest(bfloat16, FUN2TEST, Packet8bf, v36);
    scalarSingleTypeTest(bfloat16, FUN2TEST, Packet8bf, v0);
    scalarSingleTypeTest(bfloat16, FUN2TEST, Packet8bf, v_240);
    scalarSingleTypeTest(bfloat16, FUN2TEST, Packet8bf, vmin);
  }
  endTest();

#endif

#ifdef __AVX2__
  // Packet4l (256)
  beginTest("4 long tests");
  {
    MIN2MAX_LONG_VECTOR_LOADED(4);

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

#endif  // EIGEN_MIPP_PREDUX_TEST_H
