#include <float.h>
#include <limits.h>

#ifndef EIGEN_MIPP_PLDEXP_TEST_H
#define EIGEN_MIPP_PLDEXP_TEST_H

#undef FUN2TEST
#define FUN2TEST pldexp

void pldexpTests() {
  printTestTitle(FUN2TEST);

#ifdef __SSE__
  /* float = Packet4f (half) */
  tests4FloatMin2MaxTwoArgsPermRep("4 float tests", FUN2TEST);

  /* double =  Packet2d (half) */
  tests2DoubleMin2MaxTwoArgsPermRep("2 double tests", FUN2TEST);

#endif

#ifdef __AVX__
  /* float = Packet8f (full) */
  tests8FloatMin2MaxTwoArgsPermRep("8 float tests", FUN2TEST);

  /* double = Packet4d (full) */
  tests4DoubleMin2MaxTwoArgsPermRep("4 double tests", FUN2TEST);

#endif

#ifdef __AVX2__
#endif

#ifdef __AVX512F__
#endif
}

addTest(FUN2TEST)

#endif  // EIGEN_MIPP_PLDEXP_TEST_H
