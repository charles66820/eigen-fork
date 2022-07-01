#include <float.h>
#include <limits.h>

#ifndef EIGEN_MIPP_PSTOREU_TEST_H
#define EIGEN_MIPP_PSTOREU_TEST_H

#undef FUN2TEST
#define FUN2TEST pstoreu

void pstoreuTests() {
  printTestTitle(FUN2TEST);

#ifdef __SSE__
  // Packet4f (128)
  beginTest("4 float tests");
  {
    MIN2MAX_FLOAT_VECTOR_LOADED(4);

    uRefSingleType(FUN2TEST, float, 4, vmax);
    uRefSingleType(FUN2TEST, float, 4, v36);
    uRefSingleType(FUN2TEST, float, 4, v0);
    uRefSingleType(FUN2TEST, float, 4, v_240);
    uRefSingleType(FUN2TEST, float, 4, vmin);
  }
  endTest();

  // Packet2d (128)
  beginTest("2 double tests");
  {
    MIN2MAX_DOUBLE_VECTOR_LOADED(2);

    uRefSingleType(FUN2TEST, double, 2, vmax);
    uRefSingleType(FUN2TEST, double, 2, v36);
    uRefSingleType(FUN2TEST, double, 2, v0);
    uRefSingleType(FUN2TEST, double, 2, v_240);
    uRefSingleType(FUN2TEST, double, 2, vmin);
  }
  endTest();

  // Packet4i (128)
  beginTest("4 int tests");
  {
    MIN2MAX_INT_VECTOR_LOADED(4);

    uRefSingleType(FUN2TEST, int, 4, vmax);
    uRefSingleType(FUN2TEST, int, 4, v36);
    uRefSingleType(FUN2TEST, int, 4, v0);
    uRefSingleType(FUN2TEST, int, 4, v_240);
    uRefSingleType(FUN2TEST, int, 4, vmin);
  }
  endTest();

  // Packet16b (128)
  beginTest("16 bool tests");
  {
    MIN2MAX_BOOL_VECTOR_LOADED(16);

    uRefSingleType(FUN2TEST, bool, 16, bvtrue);
    uRefSingleType(FUN2TEST, bool, 16, bvfalse);
  }
  endTest();

#endif

#ifdef __AVX__
  // Packet8f (256)
  beginTest("8 float tests");
  {
    MIN2MAX_FLOAT_VECTOR_LOADED(8);

    uRefSingleType(FUN2TEST, float, 8, vmax);
    uRefSingleType(FUN2TEST, float, 8, v36);
    uRefSingleType(FUN2TEST, float, 8, v0);
    uRefSingleType(FUN2TEST, float, 8, v_240);
    uRefSingleType(FUN2TEST, float, 8, vmin);
  }
  endTest();

  // Packet4d (256)
  beginTest("4 double tests");
  {
    MIN2MAX_DOUBLE_VECTOR_LOADED(4);

    uRefSingleType(FUN2TEST, double, 4, vmax);
    uRefSingleType(FUN2TEST, double, 4, v36);
    uRefSingleType(FUN2TEST, double, 4, v0);
    uRefSingleType(FUN2TEST, double, 4, v_240);
    uRefSingleType(FUN2TEST, double, 4, vmin);
  }
  endTest();

  // Packet8i (256)
  beginTest("8 int tests");
  {
    MIN2MAX_INT_VECTOR_LOADED(8);

    uRefSingleType(FUN2TEST, int, 8, vmax);
    uRefSingleType(FUN2TEST, int, 8, v36);
    uRefSingleType(FUN2TEST, int, 8, v0);
    uRefSingleType(FUN2TEST, int, 8, v_240);
    uRefSingleType(FUN2TEST, int, 8, vmin);
  }
  endTest();

  // Packet8h (128)
  beginTest("8 Eigen::half tests");
  {
    MIN2MAX_HALF_VECTOR_LOADED(8);

    uRefSingleType(FUN2TEST, Eigen::half, 8, vmax);
    uRefSingleType(FUN2TEST, Eigen::half, 8, v36);
    uRefSingleType(FUN2TEST, Eigen::half, 8, v0);
    uRefSingleType(FUN2TEST, Eigen::half, 8, v_240);
    uRefSingleType(FUN2TEST, Eigen::half, 8, vmin);
  }
  endTest();

  // Packet8bf (128) bfloat16
  beginTest("8 bfloat16 tests");
  {
    MIN2MAX_BFLOAT16_VECTOR_LOADED(8);

    uRefSingleType(FUN2TEST, bfloat16, 8, vmax);
    uRefSingleType(FUN2TEST, bfloat16, 8, v36);
    uRefSingleType(FUN2TEST, bfloat16, 8, v0);
    uRefSingleType(FUN2TEST, bfloat16, 8, v_240);
    uRefSingleType(FUN2TEST, bfloat16, 8, vmin);
  }
  endTest();

#endif

#ifdef __AVX2__
  // Packet4l (256)
  beginTest("4 long tests");
  {
    MIN2MAX_LONG_VECTOR_LOADED(4);

    uRefSingleType(FUN2TEST, long, 4, vmax);
    uRefSingleType(FUN2TEST, long, 4, v36);
    uRefSingleType(FUN2TEST, long, 4, v0);
    uRefSingleType(FUN2TEST, long, 4, v_240);
    uRefSingleType(FUN2TEST, long, 4, vmin);
  }
  endTest();

#endif

#ifdef __AVX512F__
#endif
}

addTest(FUN2TEST)

#endif  // EIGEN_MIPP_PSTOREU_TEST_H
