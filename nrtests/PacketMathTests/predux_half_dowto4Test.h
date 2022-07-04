#include <float.h>
#include <limits.h>

#ifndef EIGEN_MIPP_PREDUX_HALF_DOWTO4_TEST_H
#define EIGEN_MIPP_PREDUX_HALF_DOWTO4_TEST_H

#undef FUN2TEST
#define FUN2TEST predux_half_dowto4

void predux_half_dowto4Tests() {
  printTestTitle(FUN2TEST);

#ifdef __SSE__
#endif

#ifdef __AVX__
  // Packet8f (256) -> Packet4f (128)
  min2maxGenericTest("full2half float tests", FUN2TEST, vector128FloatTest, Packet8f, min2MaxTests, MIN2MAX_FLOAT_VECTOR_LOADED, 8)

  // Packet8i (256) -> Packet4i (128)
  min2maxGenericTest("full2half int tests", FUN2TEST, vector128IntTest, Packet8i, min2MaxTests, MIN2MAX_INT_VECTOR_LOADED, 8)

#endif

#ifdef __AVX2__
#endif

#ifdef __AVX512F__
#endif
}

addTest(FUN2TEST)

#endif  // EIGEN_MIPP_PREDUX_HALF_DOWTO4_TEST_H
