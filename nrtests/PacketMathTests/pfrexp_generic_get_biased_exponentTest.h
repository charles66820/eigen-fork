#include <float.h>
#include <limits.h>
#include "../testVector.h"

#ifndef EIGEN_MIPP_PFREXP_GENERIC_GET_BIASED_EXPONENT_TEST_H
#define EIGEN_MIPP_PFREXP_GENERIC_GET_BIASED_EXPONENT_TEST_H

#undef FUN2TEST
#define FUN2TEST pfrexp_generic_get_biased_exponent

void pfrexp_generic_get_biased_exponentTests() {
  std::cout << printTestTitle(FUN2TEST) << std::endl;

#ifdef __SSE__
  /* double =  Packet2d (half) */
  beginTest("half double tests");

  loadVectorHalf(vector2, double, dhvmax, HALF_CAST, Packet2d, DBL_MAX, 0.0d);
  loadVectorHalf(vector2, double, dhv36, HALF_CAST, Packet2d, 36.7d, 0.0d);
  loadVectorHalf(vector2, double, dhv0, HALF_CAST, Packet2d, 0.0d, 0.0d);
  loadVectorHalf(vector2, double, dhv_240, HALF_CAST, Packet2d, -240.98d, 0.0d);
  loadVectorHalf(vector2, double, dhvmin, HALF_CAST, Packet2d, DBL_MIN, 0.0d);

  vectorHalfDoubleTest(FUN2TEST, (Packet2d)dhvmax.r);
  vectorHalfDoubleTest(FUN2TEST, (Packet2d)dhv36.r);
  vectorHalfDoubleTest(FUN2TEST, (Packet2d)dhv0.r);
  vectorHalfDoubleTest(FUN2TEST, (Packet2d)dhv_240.r);
  vectorHalfDoubleTest(FUN2TEST, (Packet2d)dhvmin.r);

  endTest();

#endif

#ifdef __AVX__
  /* double = Packet4d (full) */
  beginTest("full double tests");

  loadVectorFull(vector4, double, dvmax, FULL_CAST, Packet4d, DBL_MAX, 0.0d);
  loadVectorFull(vector4, double, dv36, FULL_CAST, Packet4d, 36.7d, 0.0d);
  loadVectorFull(vector4, double, dv0, FULL_CAST, Packet4d, 0.0d, 0.0d);
  loadVectorFull(vector4, double, dv_240, FULL_CAST, Packet4d, -240.98d, 0.0d);
  loadVectorFull(vector4, double, dvmin, FULL_CAST, Packet4d, DBL_MIN, 0.0d);

  vectorFullDoubleTest(FUN2TEST, (Packet4d)dvmax.r);
  vectorFullDoubleTest(FUN2TEST, (Packet4d)dv36.r);
  vectorFullDoubleTest(FUN2TEST, (Packet4d)dv0.r);
  vectorFullDoubleTest(FUN2TEST, (Packet4d)dv_240.r);
  vectorFullDoubleTest(FUN2TEST, (Packet4d)dvmin.r);

  endTest();

#endif

#ifdef __AVX2__
#endif

#ifdef __AVX512__
#endif
}

addTest(FUN2TEST)

#endif  // EIGEN_MIPP_PFREXP_GENERIC_GET_BIASED_EXPONENT_TEST_H
