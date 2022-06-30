#include <float.h>
#include <limits.h>

#ifndef EIGEN_MIPP_PLOGICAL_SHIFT_LEFT_TEST_H
#define EIGEN_MIPP_PLOGICAL_SHIFT_LEFT_TEST_H

#undef FUN2TEST
#define FUN2TEST plogical_shift_left

void plogical_shift_leftTests() {
  printTestTitle(FUN2TEST);

#ifdef __SSE__

  /* int = Packet4i (half) */
  beginTest("4 int tests");
  {
    MIN2MAX_4_INT_VECTOR_LOADED

    min2MaxTests(vectorHalfIntTemplateTest, FUN2TEST, 3, vmax, v36, v0, v_240, vmin);
  }
  endTest();

#endif

#ifdef __AVX__

  /* int = Packet8i (full) */
  beginTest("8 int tests");
  {
    MIN2MAX_8_INT_VECTOR_LOADED

    min2MaxTests(vectorFullIntTemplateTest, FUN2TEST, 3, vmax, v36, v0, v_240, vmin);
  }
  endTest();

#endif

#ifdef __AVX2__
  /* long = Packet4l */
  beginTest("4 long tests");
  {
    MIN2MAX_4_LONG_VECTOR_LOADED

    min2MaxTests(vectorFullLongTemplateTest, FUN2TEST, 3, vmax, v36, v0, v_240, vmin);
  }
  endTest();

#endif

#ifdef __AVX512F__
#endif
}

addTest(FUN2TEST)

#endif  // EIGEN_MIPP_PLOGICAL_SHIFT_LEFT_TEST_H
