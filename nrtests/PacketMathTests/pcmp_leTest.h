#include <float.h>
#include <limits.h>
#include "../testVector.h"
#include "../testCombinations.h"

#ifndef EIGEN_MIPP_PCMP_LE_TEST_H
#define EIGEN_MIPP_PCMP_LE_TEST_H

#undef FUN2TEST
#define FUN2TEST pcmp_le

void pcmp_leTests() {
  printTestTitle(FUN2TEST);

#ifdef __SSE__
  /* float = Packet4f (half) */
  tests4FloatMin2MaxTwoArgsPermRep("4 float tests", FUN2TEST);

  /* double =  Packet2d (half) */
  tests2DoubleMin2MaxTwoArgsPermRep("2 double tests", FUN2TEST);

  /* int = Packet4i (half) */
  tests4IntMin2MaxTwoArgsPermRep("4 int tests", FUN2TEST);

#endif

#ifdef __AVX__
  /* float = Packet8f (full) */
  tests8FloatMin2MaxTwoArgsPermRep("8 float tests", FUN2TEST);

  /* double = Packet4d (full) */
  tests4DoubleMin2MaxTwoArgsPermRep("4 double tests", FUN2TEST);

  /* int = Packet8i (full) */
  tests8IntMin2MaxTwoArgsPermRep("8 int tests", FUN2TEST);

  /* Eigen::half = Packet8h */
  tests8HalfMin2MaxTwoArgsPermRep("8 Eigen::half tests", FUN2TEST);

  /* bfloat16 = Packet8bf */
  tests8Bfloat16Min2MaxTwoArgsPermRep("8 bfloat16 tests", FUN2TEST);

#endif

#ifdef __AVX2__
  /* long = Packet4l */
  tests4LongMin2MaxTwoArgsPermRep("4 long tests", FUN2TEST);

#endif

#ifdef __AVX512F__
#endif
}

addTest(FUN2TEST)

#endif  // EIGEN_MIPP_PCMP_LE_TEST_H
