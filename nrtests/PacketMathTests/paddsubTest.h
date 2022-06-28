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

  loadVectorHalf(vector4, float, fhvmax, , Packet4f, FLT_MAX, 0.0f);
  loadVectorHalf(vector4, float, fhv36, , Packet4f, 36.7f, 0.0f);
  loadVectorHalf(vector4, float, fhv0, , Packet4f, 0.0f, 0.0f);
  loadVectorHalf(vector4, float, fhv_240, , Packet4f, -240.98f, 0.0f);
  loadVectorHalf(vector4, float, fhvmin, , Packet4f, FLT_MAX, 0.0f);

  allTwoPermRep(vectorHalfFloatTest, FUN2TEST, fhvmax.r, fhv36.r, fhv0.r, fhv_240.r, fhvmin.r);

  endTest();

  /* double =  Packet2d (half) */
  beginTest("half double tests");

  loadVectorHalf(vector2, double, dhvmax, HALF_CAST, Packet2d, DBL_MAX, 0.0d);
  loadVectorHalf(vector2, double, dhv36, HALF_CAST, Packet2d, 36.7d, 0.0d);
  loadVectorHalf(vector2, double, dhv0, HALF_CAST, Packet2d, 0.0d, 0.0d);
  loadVectorHalf(vector2, double, dhv_240, HALF_CAST, Packet2d, -240.98d, 0.0d);
  loadVectorHalf(vector2, double, dhvmin, HALF_CAST, Packet2d, DBL_MIN, 0.0d);

  allTwoPermRep(vectorHalfDoubleTest, FUN2TEST, (Packet2d)dhvmax.r, (Packet2d)dhv36.r, (Packet2d)dhv0.r, (Packet2d)dhv_240.r, (Packet2d)dhvmin.r);

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
