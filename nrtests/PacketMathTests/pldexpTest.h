#include <float.h>
#include <limits.h>
#include "../testVector.h"
#include "../testCombinations.h"

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
  beginTest("8 float tests");

  MIN2MAX_FULL_FLOAT_VECTOR

  allTwoPermRep(vectorFullFloatTest, FUN2TEST, fvmax.r, fv36.r, fv0.r, fv_240.r, fvmin.r);

  endTest();

  /* double = Packet4d (full) */
  beginTest("4 double tests");

  MIN2MAX_FULL_DOUBLE_VECTOR

  allTwoPermRep(vectorFullDoubleTest, FUN2TEST, (Packet4d)dvmax.r, (Packet4d)dv36.r, (Packet4d)dv0.r,
                (Packet4d)dv_240.r, (Packet4d)dvmin.r);

  endTest();

#endif

#ifdef __AVX2__
#endif

#ifdef __AVX512F__
#endif
}

addTest(FUN2TEST)

#endif  // EIGEN_MIPP_PLDEXP_TEST_H
