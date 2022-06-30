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
  /* float = Packet4f (half) */
  tests4FloatMin2MaxOneArg("4 float tests", FUN2TEST);

#endif

#endif

#ifdef __AVX__
  /* float = Packet8f (full) */
  tests8FloatMin2MaxOneArg("8 float tests", FUN2TEST);

  /* double = Packet4d (full) */
  tests4DoubleMin2MaxOneArg("4 double tests", FUN2TEST);

#endif

#ifdef __AVX2__
  /* long = Packet4l */
  tests4LongMin2MaxOneArg("4 long tests", FUN2TEST);

#endif

#ifdef __AVX512F__
#endif
}

addTest(FUN2TEST)

#endif  // EIGEN_MIPP_PLOAD1_TEST_H
