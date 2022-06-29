#include <float.h>
#include <limits.h>
#include "../testVector.h"

#ifndef EIGEN_MIPP_PFREXP_GENERIC_GET_BIASED_EXPONENT_TEST_H
#define EIGEN_MIPP_PFREXP_GENERIC_GET_BIASED_EXPONENT_TEST_H

#undef FUN2TEST
#define FUN2TEST pfrexp_generic_get_biased_exponent

void pfrexp_generic_get_biased_exponentTests() {
  printTestTitle(FUN2TEST);

#ifdef __SSE__
  /* double =  Packet2d (half) */
  tests2DoubleMin2MaxOneArg("2 double tests", FUN2TEST);

#endif

#ifdef __AVX__
  /* double = Packet4d (full) */
  beginTest("4 double tests");

  MIN2MAX_FULL_DOUBLE_VECTOR
  vectorFullDoubleTest(FUN2TEST, (Packet4d)dvmax.r);
  vectorFullDoubleTest(FUN2TEST, (Packet4d)dv36.r);
  vectorFullDoubleTest(FUN2TEST, (Packet4d)dv0.r);
  vectorFullDoubleTest(FUN2TEST, (Packet4d)dv_240.r);
  vectorFullDoubleTest(FUN2TEST, (Packet4d)dvmin.r);

  endTest();

#endif

#ifdef __AVX2__
#endif

#ifdef __AVX512F__
#endif
}

addTest(FUN2TEST)

#endif  // EIGEN_MIPP_PFREXP_GENERIC_GET_BIASED_EXPONENT_TEST_H
