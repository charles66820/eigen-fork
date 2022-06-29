#include <float.h>
#include <limits.h>


#ifndef EIGEN_MIPP_PROUND_TEST_H
#define EIGEN_MIPP_PROUND_TEST_H

#undef FUN2TEST
#define FUN2TEST pround

void proundTests() {
  printTestTitle(FUN2TEST);

#ifdef __SSE__
  /* float = Packet4f (half) */
  tests4FloatMin2MaxOneArg("4 float tests", FUN2TEST);

  /* double =  Packet2d (half) */
  tests2DoubleMin2MaxOneArg("2 double tests", FUN2TEST);

#endif

#ifdef __AVX__
  /* float = Packet8f (full) */
  tests8FloatMin2MaxOneArg("8 float tests", FUN2TEST);

  /* double = Packet4d (full) */
  tests4DoubleMin2MaxOneArg("4 double tests", FUN2TEST);

  /* Eigen::half = Packet8h */
  tests8HalfMin2MaxOneArg("8 Eigen::half tests", FUN2TEST);

  /* bfloat16 = Packet8bf */
  tests8Bfloat16Min2MaxOneArg("8 bfloat16 tests", FUN2TEST);

#endif

#ifdef __AVX2__
#endif

#ifdef __AVX512F__
#endif
}

addTest(FUN2TEST)

#endif  // EIGEN_MIPP_PROUND_TEST_H
