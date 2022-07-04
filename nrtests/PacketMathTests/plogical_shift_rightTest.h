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
  min2maxGenericTest("4 int tests", FUN2TEST, vector128IntTest, 3, min2MaxTests, MIN2MAX_INT_VECTOR_LOADED, 4);

#endif

#ifdef __AVX__

  // Packet8i (256)
  min2maxGenericTest("8 int tests", FUN2TEST, vector256IntTest, 3, min2MaxTests, MIN2MAX_INT_VECTOR_LOADED, 8);

#endif

#ifdef __AVX2__
  // Packet4l (256)
  min2maxGenericTest("4 long tests", FUN2TEST, vector256LongTest, 3, min2MaxTests, MIN2MAX_LONG_VECTOR_LOADED, 4);

#endif

#ifdef __AVX512F__
#endif
}

addTest(FUN2TEST)

#endif  // EIGEN_MIPP_PLOGICAL_SHIFT_RIGHT_TEST_H
