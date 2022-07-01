#include <float.h>
#include <limits.h>

#ifndef EIGEN_MIPP_PARITHMETIC_SHIFT_RIGHT_TEST_H
#define EIGEN_MIPP_PARITHMETIC_SHIFT_RIGHT_TEST_H

#undef FUN2TEST
#define FUN2TEST parithmetic_shift_right

void parithmetic_shift_rightTests() {
  printTestTitle(FUN2TEST);

#ifdef __SSE__

  /* int = Packet4i (half) */
  beginTest("4 int tests");
  {
    MIN2MAX_INT_VECTOR_LOADED(4);

    min2MaxTests(vectorHalfIntTest, FUN2TEST, 3, vmax, v36, v0, v_240, vmin);
  }
  endTest();

#endif

#ifdef __AVX__

  /* int = Packet8i (full) */
  beginTest("8 int tests");
  {
    MIN2MAX_INT_VECTOR_LOADED(8);

    min2MaxTests(vectorFullIntTest, FUN2TEST, 3, vmax, v36, v0, v_240, vmin);
  }
  endTest();

#endif

#ifdef __AVX2__
#endif

#ifdef __AVX512F__
#endif
}

addTest(FUN2TEST)

#endif  // EIGEN_MIPP_PARITHMETIC_SHIFT_RIGHT_TEST_H
