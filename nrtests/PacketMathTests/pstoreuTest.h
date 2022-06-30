#include <float.h>
#include <limits.h>

#ifndef EIGEN_MIPP_PSTOREU_TEST_H
#define EIGEN_MIPP_PSTOREU_TEST_H

#undef FUN2TEST
#define FUN2TEST pstoreu

void pstoreuTests() {
  printTestTitle(FUN2TEST);

#ifdef __SSE__
  /* float = Packet4f (half) */
  beginTest("4 float tests");
  {
    MIN2MAX_4_FLOAT_VECTOR_LOADED

    uRefSingleType(FUN2TEST, float, 4, vmax);
    uRefSingleType(FUN2TEST, float, 4, v36);
    uRefSingleType(FUN2TEST, float, 4, v0);
    uRefSingleType(FUN2TEST, float, 4, v_240);
    uRefSingleType(FUN2TEST, float, 4, vmin);
  }
  endTest();

  /* double =  Packet2d (half) */
  beginTest("2 double tests");
  {
    MIN2MAX_2_DOUBLE_VECTOR_LOADED

    uRefSingleType(FUN2TEST, double, 2, vmax);
    uRefSingleType(FUN2TEST, double, 2, v36);
    uRefSingleType(FUN2TEST, double, 2, v0);
    uRefSingleType(FUN2TEST, double, 2, v_240);
    uRefSingleType(FUN2TEST, double, 2, vmin);
  }
  endTest();

  /* int = Packet4i (half) */
  beginTest("4 int tests");
  {
    MIN2MAX_4_INT_VECTOR_LOADED

    uRefSingleType(FUN2TEST, int, 4, vmax);
    uRefSingleType(FUN2TEST, int, 4, v36);
    uRefSingleType(FUN2TEST, int, 4, v0);
    uRefSingleType(FUN2TEST, int, 4, v_240);
    uRefSingleType(FUN2TEST, int, 4, vmin);
  }
  endTest();

  /* bool = Packet16b */
  beginTest("16 bool tests");
  {
    MIN2MAX_16_BOOL_VECTOR_LOADED

    uRefSingleType(FUN2TEST, bool, 16, bvtrue);
    uRefSingleType(FUN2TEST, bool, 16, bvfalse);
  }
  endTest();

#endif

#ifdef __AVX__
  /* float = Packet8f (full) */
  beginTest("8 float tests");
  {
    MIN2MAX_8_FLOAT_VECTOR_LOADED

    uRefSingleType(FUN2TEST, float, 8, vmax);
    uRefSingleType(FUN2TEST, float, 8, v36);
    uRefSingleType(FUN2TEST, float, 8, v0);
    uRefSingleType(FUN2TEST, float, 8, v_240);
    uRefSingleType(FUN2TEST, float, 8, vmin);
  }
  endTest();

  /* double = Packet4d (full) */
  beginTest("4 double tests");
  {
    MIN2MAX_4_DOUBLE_VECTOR_LOADED

    uRefSingleType(FUN2TEST, double, 4, vmax);
    uRefSingleType(FUN2TEST, double, 4, v36);
    uRefSingleType(FUN2TEST, double, 4, v0);
    uRefSingleType(FUN2TEST, double, 4, v_240);
    uRefSingleType(FUN2TEST, double, 4, vmin);
  }
  endTest();

  /* int = Packet8i (full) */
  beginTest("8 int tests");
  {
    MIN2MAX_8_INT_VECTOR_LOADED

    uRefSingleType(FUN2TEST, int, 8, vmax);
    uRefSingleType(FUN2TEST, int, 8, v36);
    uRefSingleType(FUN2TEST, int, 8, v0);
    uRefSingleType(FUN2TEST, int, 8, v_240);
    uRefSingleType(FUN2TEST, int, 8, vmin);
  }
  endTest();

  /* Eigen::half = Packet8h */
  beginTest("8 Eigen::half tests");
  {
    MIN2MAX_8_HALF_VECTOR_LOADED

    uRefSingleType(FUN2TEST, Eigen::half, 8, vmax);
    uRefSingleType(FUN2TEST, Eigen::half, 8, v36);
    uRefSingleType(FUN2TEST, Eigen::half, 8, v0);
    uRefSingleType(FUN2TEST, Eigen::half, 8, v_240);
    uRefSingleType(FUN2TEST, Eigen::half, 8, vmin);
  }
  endTest();

  /* bfloat16 = Packet8bf */
  beginTest("8 bfloat16 tests");
  {
    MIN2MAX_8_BFLOAT16_VECTOR_LOADED

    uRefSingleType(FUN2TEST, bfloat16, 8, vmax);
    uRefSingleType(FUN2TEST, bfloat16, 8, v36);
    uRefSingleType(FUN2TEST, bfloat16, 8, v0);
    uRefSingleType(FUN2TEST, bfloat16, 8, v_240);
    uRefSingleType(FUN2TEST, bfloat16, 8, vmin);
  }
  endTest();

#endif

#ifdef __AVX2__
  /* long = Packet4l */
  beginTest("4 long tests");
  {
    MIN2MAX_4_LONG_VECTOR_LOADED

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
