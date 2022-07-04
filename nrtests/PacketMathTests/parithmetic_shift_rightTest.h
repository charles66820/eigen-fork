#include <float.h>
#include <limits.h>

#ifndef EIGEN_MIPP_PARITHMETIC_SHIFT_RIGHT_TEST_H
#define EIGEN_MIPP_PARITHMETIC_SHIFT_RIGHT_TEST_H

#undef FUN2TEST
#define FUN2TEST parithmetic_shift_right

void parithmetic_shift_rightTests() {
  printTestTitle(FUN2TEST);

#ifdef __SSE__

  min2maxGenericTest("4 int tests", FUN2TEST, vector128IntTest, 3, min2MaxTests, MIN2MAX_INT_VECTOR_LOADED, 4);

#endif

#ifdef __AVX__

  // Packet8i (256)
  min2maxGenericTest("8 int tests", FUN2TEST, vector256IntTest, 3, min2MaxTests, MIN2MAX_INT_VECTOR_LOADED, 8);

#endif

#ifdef __AVX2__
#endif

#ifdef __AVX512F__
#endif
}

addTest(FUN2TEST)

#endif  // EIGEN_MIPP_PARITHMETIC_SHIFT_RIGHT_TEST_H
