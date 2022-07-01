#include <float.h>
#include <limits.h>

#ifndef EIGEN_MIPP_PMSUB_TEST_H
#define EIGEN_MIPP_PMSUB_TEST_H

#undef FUN2TEST
#define FUN2TEST pmsub

void pmsubTests() {
  printTestTitle(FUN2TEST);

#ifdef __SSE__
  // Packet4f (128)
  tests4FloatMin2MaxThreeArgsPermRep("4 float tests", FUN2TEST);

  // Packet2d (128)
  tests2DoubleMin2MaxThreeArgsPermRep("2 double tests", FUN2TEST);

  // Packet4i (128)
  tests4IntMin2MaxThreeArgsPermRep("4 int tests", FUN2TEST);

#endif

#ifdef __AVX__
  // Packet8f (256)
  tests8FloatMin2MaxThreeArgsPermRep("8 float tests", FUN2TEST);

  // Packet4d (256)
  tests4DoubleMin2MaxThreeArgsPermRep("4 double tests", FUN2TEST);

  // Packet8i (256)
  tests8IntMin2MaxThreeArgsPermRep("8 int tests", FUN2TEST);

  // Packet8h (128)
  tests8HalfMin2MaxThreeArgsPermRep("8 Eigen::half tests", FUN2TEST);

  // Packet8bf (128) bfloat16
  tests8Bfloat16Min2MaxThreeArgsPermRep("8 bfloat16 tests", FUN2TEST);

#endif

#ifdef __AVX2__
  // Packet4l (256)
  tests4LongMin2MaxThreeArgsPermRep("4 long tests", FUN2TEST);

#endif

#ifdef __AVX512F__
#endif
}

addTest(FUN2TEST)

#endif  // EIGEN_MIPP_PMSUB_TEST_H
