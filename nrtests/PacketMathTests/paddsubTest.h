#include <float.h>
#include <limits.h>

#ifndef EIGEN_MIPP_PADDSUB_TEST_H
#define EIGEN_MIPP_PADDSUB_TEST_H

#undef FUN2TEST
#define FUN2TEST paddsub

void paddsubTests() {
  printTestTitle(FUN2TEST);

#ifdef __SSE__
  /* float = Packet4f (half) */
  tests4FloatMin2MaxTwoArgsPermRep("4 float tests", FUN2TEST);

  /* double =  Packet2d (half) */
  tests2DoubleMin2MaxTwoArgsPermRep("2 double tests", FUN2TEST);

#endif

#ifdef __AVX__
#endif

#ifdef __AVX2__
#endif

#ifdef __AVX512F__
#endif
}

addTest(FUN2TEST)

#endif  // EIGEN_MIPP_PADDSUB_TEST_H
