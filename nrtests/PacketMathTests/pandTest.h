#include <float.h>
#include <limits.h>

#ifndef EIGEN_MIPP_PAND_TEST_H
#define EIGEN_MIPP_PAND_TEST_H

#undef FUN2TEST
#define FUN2TEST pand

void pandTests() {
  printTestTitle(FUN2TEST);

#ifdef __SSE__
  // Packet4f (128)
  tests4FloatMin2MaxTwoArgsCombRep("4 float tests", FUN2TEST);

  // Packet2d (128)
  tests2DoubleMin2MaxTwoArgsCombRep("2 double tests", FUN2TEST);

  // Packet4i (128)
  tests4IntMin2MaxTwoArgsCombRep("4 int tests", FUN2TEST);

  // Packet16b (128)
  tests16BoolMin2MaxTwoArgsCombRep("16 bool tests", FUN2TEST);

#endif

#ifdef __AVX__
  // Packet8f (256)
  tests8FloatMin2MaxTwoArgsCombRep("8 float tests", FUN2TEST);

  // Packet4d (256)
  tests4DoubleMin2MaxTwoArgsCombRep("4 double tests", FUN2TEST);

  // Packet8i (256)
  tests8IntMin2MaxTwoArgsCombRep("8 int tests", FUN2TEST);

  // Packet8h (128)
  tests8HalfMin2MaxTwoArgsCombRep("8 Eigen::half tests", FUN2TEST);

  // Packet8bf (128) bfloat16
  tests8Bfloat16Min2MaxTwoArgsCombRep("8 bfloat16 tests", FUN2TEST);

#endif

#ifdef __AVX2__
  // Packet4l (256)
  tests4LongMin2MaxTwoArgsCombRep("4 long tests", FUN2TEST);

#endif

#ifdef __AVX512F__
#endif
}

addTest(FUN2TEST)

#endif  // EIGEN_MIPP_PAND_TEST_H
