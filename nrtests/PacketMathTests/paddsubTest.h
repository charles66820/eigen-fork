#include <float.h>
#include <limits.h>
#include "../testVector.h"
#include "../testCombinations.h"

#ifndef EIGEN_MIPP_PADDSUB_TEST_H
#define EIGEN_MIPP_PADDSUB_TEST_H

#undef FUN2TEST
#define FUN2TEST paddsub

void paddsubTests() {
  std::cout << printTestTitle(FUN2TEST) << std::endl;

#ifdef __SSE__
  /* float = Packet4f (half) */
  beginTest("half float tests");

  MIN2MAX_HALF_FLOAT_VECTOR

  allTwoPermRep(vectorHalfFloatTest, FUN2TEST, fhvmax.r, fhv36.r, fhv0.r, fhv_240.r, fhvmin.r);

  endTest();

  /* double =  Packet2d (half) */
  beginTest("half double tests");

  MIN2MAX_HALF_DOUBLE_VECTOR

  allTwoPermRep(vectorHalfDoubleTest, FUN2TEST, (Packet2d)dhvmax.r, (Packet2d)dhv36.r, (Packet2d)dhv0.r,
                (Packet2d)dhv_240.r, (Packet2d)dhvmin.r);

  endTest();

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
