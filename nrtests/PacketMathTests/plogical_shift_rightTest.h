#include <float.h>
#include <limits.h>

#ifndef EIGEN_MIPP_PLOGICAL_SHIFT_RIGHT_TEST_H
#define EIGEN_MIPP_PLOGICAL_SHIFT_RIGHT_TEST_H

#undef FUN2TEST
#define FUN2TEST plogical_shift_right

void plogical_shift_rightTests() {
  printTestTitle(FUN2TEST);

#ifdef __SSE__

  // Packet4i (128)
  beginTest("4 int tests");
  {
    MIN2MAX_INT_VECTOR_LOADED(4);

    min2MaxTests(vector128IntTest, FUN2TEST, 3, vmax, v36, v0, v_240, vmin);
  }
  endTest();

#endif

#ifdef __AVX__

  // Packet8i (256)
  beginTest("8 int tests");
  {
    MIN2MAX_INT_VECTOR_LOADED(8);

    min2MaxTests(vector256IntTest, FUN2TEST, 3, vmax, v36, v0, v_240, vmin);
  }
  endTest();

#endif

#ifdef __AVX2__
  // Packet4l (256)
  beginTest("4 long tests");
  {
    MIN2MAX_LONG_VECTOR_LOADED(4);

    min2MaxTests(vector256LongTest, FUN2TEST, 3, vmax, v36, v0, v_240, vmin);
  }
  endTest();

#endif

#ifdef __AVX512F__
#endif
}

addTest(FUN2TEST)

#endif  // EIGEN_MIPP_PLOGICAL_SHIFT_RIGHT_TEST_H
