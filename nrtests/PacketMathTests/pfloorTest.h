#include <float.h>
#include <limits.h>

#ifndef EIGEN_MIPP_PFLOOR_TEST_H
#define EIGEN_MIPP_PFLOOR_TEST_H

#undef FUN2TEST
#define FUN2TEST pfloor

void pfloorTests() {
  printTestTitle(FUN2TEST);

#ifdef __SSE__
  // Packet4f (128)
  tests4FloatMin2MaxOneArgLoaded("4 float tests", FUN2TEST);

  // Packet2d (128)
  tests2DoubleMin2MaxOneArgLoaded("2 double tests", FUN2TEST);

#endif

#ifdef __AVX__
  // Packet8f (256)
  tests8FloatMin2MaxOneArgLoaded("8 float tests", FUN2TEST);

  // Packet4d (256)
  tests4DoubleMin2MaxOneArgLoaded("4 double tests", FUN2TEST);

  // Packet8h (128)
  tests8HalfMin2MaxOneArgLoaded("8 Eigen::half tests", FUN2TEST);

  // Packet8bf (128) bfloat16
  tests8Bfloat16Min2MaxOneArgLoaded("8 bfloat16 tests", FUN2TEST);

#endif

#ifdef __AVX2__
#endif

#ifdef __AVX512F__
#endif
}

addTest(FUN2TEST)

#endif  // EIGEN_MIPP_PFLOOR_TEST_H
