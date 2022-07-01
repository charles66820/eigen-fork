#include <float.h>
#include <limits.h>

#ifndef EIGEN_MIPP_PLOAD1_TEST_H
#define EIGEN_MIPP_PLOAD1_TEST_H

#undef FUN2TEST
#define FUN2TEST pload1

void pload1Tests() {
  printTestTitle(FUN2TEST);

#ifdef __SSE__

#if EIGEN_COMP_GNUC_STRICT && (!defined __AVX__)
  // Packet4f (128)
  tests4FloatMin2MaxOneArg("4 float tests", FUN2TEST);

#endif

#endif

#ifdef __AVX__
  // Packet8f (256)
  tests8FloatMin2MaxOneArg("8 float tests", FUN2TEST);

  // Packet4d (256)
  tests4DoubleMin2MaxOneArg("4 double tests", FUN2TEST);

#endif

#ifdef __AVX2__
  // Packet4l (256)
  tests4LongMin2MaxOneArg("4 long tests", FUN2TEST);

#endif

#ifdef __AVX512F__
#endif
}

addTest(FUN2TEST)

#endif  // EIGEN_MIPP_PLOAD1_TEST_H
