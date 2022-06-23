#include <float.h>
#include <limits.h>
#include "../testVector.h"

#ifndef EIGEN_MIPP_PLDEXP_TEST_H
#define EIGEN_MIPP_PLDEXP_TEST_H

#undef FUN2TEST
#define FUN2TEST pldexp

void pldexpTests() {
  std::cout << printTestTitle(FUN2TEST) << std::endl;

#ifdef __SSE__
  /* float = Packet4f (half) */
  beginTest("half float tests");

  loadVectorHalf(vector4, float, fhvmax, , Packet4f, FLT_MAX, 0.0f);
  loadVectorHalf(vector4, float, fhv36, , Packet4f, 36.7f, 0.0f);
  loadVectorHalf(vector4, float, fhv0, , Packet4f, 0.0f, 0.0f);
  loadVectorHalf(vector4, float, fhv_240, , Packet4f, -240.98f, 0.0f);
  loadVectorHalf(vector4, float, fhvmin, , Packet4f, FLT_MAX, 0.0f);

  vectorHalfFloatTest(FUN2TEST, fhvmax.r, fhvmax.r);
  vectorHalfFloatTest(FUN2TEST, fhvmax.r, fhv36.r);
  vectorHalfFloatTest(FUN2TEST, fhvmax.r, fhv0.r);
  vectorHalfFloatTest(FUN2TEST, fhvmax.r, fhv_240.r);
  vectorHalfFloatTest(FUN2TEST, fhvmax.r, fhvmin.r);
  vectorHalfFloatTest(FUN2TEST, fhv36.r, fhv36.r);
  vectorHalfFloatTest(FUN2TEST, fhv36.r, fhv0.r);
  vectorHalfFloatTest(FUN2TEST, fhv36.r, fhv_240.r);
  vectorHalfFloatTest(FUN2TEST, fhv36.r, fhvmin.r);
  vectorHalfFloatTest(FUN2TEST, fhv0.r, fhv0.r);
  vectorHalfFloatTest(FUN2TEST, fhv0.r, fhv_240.r);
  vectorHalfFloatTest(FUN2TEST, fhv0.r, fhvmin.r);
  vectorHalfFloatTest(FUN2TEST, fhv_240.r, fhv_240.r);
  vectorHalfFloatTest(FUN2TEST, fhv_240.r, fhvmin.r);
  vectorHalfFloatTest(FUN2TEST, fhvmin.r, fhvmin.r);

  endTest();

  /* double =  Packet2d (half) */
  beginTest("half double tests");

  loadVectorHalf(vector2, double, dhvmax, HALF_CAST, Packet2d, DBL_MAX, 0.0d);
  loadVectorHalf(vector2, double, dhv36, HALF_CAST, Packet2d, 36.7d, 0.0d);
  loadVectorHalf(vector2, double, dhv0, HALF_CAST, Packet2d, 0.0d, 0.0d);
  loadVectorHalf(vector2, double, dhv_240, HALF_CAST, Packet2d, -240.98d, 0.0d);
  loadVectorHalf(vector2, double, dhvmin, HALF_CAST, Packet2d, DBL_MIN, 0.0d);

  vectorHalfDoubleTest(FUN2TEST, (Packet2d)dhvmax.r, (Packet2d)dhvmax.r);
  vectorHalfDoubleTest(FUN2TEST, (Packet2d)dhvmax.r, (Packet2d)dhv36.r);
  vectorHalfDoubleTest(FUN2TEST, (Packet2d)dhvmax.r, (Packet2d)dhv0.r);
  vectorHalfDoubleTest(FUN2TEST, (Packet2d)dhvmax.r, (Packet2d)dhv_240.r);
  vectorHalfDoubleTest(FUN2TEST, (Packet2d)dhvmax.r, (Packet2d)dhvmin.r);
  vectorHalfDoubleTest(FUN2TEST, (Packet2d)dhv36.r, (Packet2d)dhv36.r);
  vectorHalfDoubleTest(FUN2TEST, (Packet2d)dhv36.r, (Packet2d)dhv0.r);
  vectorHalfDoubleTest(FUN2TEST, (Packet2d)dhv36.r, (Packet2d)dhv_240.r);
  vectorHalfDoubleTest(FUN2TEST, (Packet2d)dhv36.r, (Packet2d)dhvmin.r);
  vectorHalfDoubleTest(FUN2TEST, (Packet2d)dhv0.r, (Packet2d)dhv0.r);
  vectorHalfDoubleTest(FUN2TEST, (Packet2d)dhv0.r, (Packet2d)dhv_240.r);
  vectorHalfDoubleTest(FUN2TEST, (Packet2d)dhv0.r, (Packet2d)dhvmin.r);
  vectorHalfDoubleTest(FUN2TEST, (Packet2d)dhv_240.r, (Packet2d)dhv_240.r);
  vectorHalfDoubleTest(FUN2TEST, (Packet2d)dhv_240.r, (Packet2d)dhvmin.r);
  vectorHalfDoubleTest(FUN2TEST, (Packet2d)dhvmin.r, (Packet2d)dhvmin.r);

  endTest();

#endif

#ifdef __AVX__
  /* float = Packet8f (full) */
  beginTest("full float tests");
  loadVectorFull(vector8, float, fvmax, , Packet8f, FLT_MAX, 0.0f);
  loadVectorFull(vector8, float, fv36, , Packet8f, 36.7f, 0.0f);
  loadVectorFull(vector8, float, fv0, , Packet8f, 0.0f, 0.0f);
  loadVectorFull(vector8, float, fv_240, , Packet8f, -240.98f, 0.0f);
  loadVectorFull(vector8, float, fvmin, , Packet8f, FLT_MAX, 0.0f);

  vectorFullFloatTest(FUN2TEST, fvmax.r, fvmax.r);
  vectorFullFloatTest(FUN2TEST, fvmax.r, fv36.r);
  vectorFullFloatTest(FUN2TEST, fvmax.r, fv0.r);
  vectorFullFloatTest(FUN2TEST, fvmax.r, fv_240.r);
  vectorFullFloatTest(FUN2TEST, fvmax.r, fvmin.r);
  vectorFullFloatTest(FUN2TEST, fv36.r, fv36.r);
  vectorFullFloatTest(FUN2TEST, fv36.r, fv0.r);
  vectorFullFloatTest(FUN2TEST, fv36.r, fv_240.r);
  vectorFullFloatTest(FUN2TEST, fv36.r, fvmin.r);
  vectorFullFloatTest(FUN2TEST, fv0.r, fv0.r);
  vectorFullFloatTest(FUN2TEST, fv0.r, fv_240.r);
  vectorFullFloatTest(FUN2TEST, fv0.r, fvmin.r);
  vectorFullFloatTest(FUN2TEST, fv_240.r, fv_240.r);
  vectorFullFloatTest(FUN2TEST, fv_240.r, fvmin.r);
  vectorFullFloatTest(FUN2TEST, fvmin.r, fvmin.r);

  endTest();

  /* double = Packet4d (full) */
  beginTest("full double tests");

  loadVectorFull(vector4, double, dvmax, FULL_CAST, Packet4d, DBL_MAX, 0.0d);
  loadVectorFull(vector4, double, dv36, FULL_CAST, Packet4d, 36.7d, 0.0d);
  loadVectorFull(vector4, double, dv0, FULL_CAST, Packet4d, 0.0d, 0.0d);
  loadVectorFull(vector4, double, dv_240, FULL_CAST, Packet4d, -240.98d, 0.0d);
  loadVectorFull(vector4, double, dvmin, FULL_CAST, Packet4d, DBL_MIN, 0.0d);

  vectorFullDoubleTest(FUN2TEST, (Packet4d)dvmax.r, (Packet4d)dvmax.r);
  vectorFullDoubleTest(FUN2TEST, (Packet4d)dvmax.r, (Packet4d)dv36.r);
  vectorFullDoubleTest(FUN2TEST, (Packet4d)dvmax.r, (Packet4d)dv0.r);
  vectorFullDoubleTest(FUN2TEST, (Packet4d)dvmax.r, (Packet4d)dv_240.r);
  vectorFullDoubleTest(FUN2TEST, (Packet4d)dvmax.r, (Packet4d)dvmin.r);
  vectorFullDoubleTest(FUN2TEST, (Packet4d)dv36.r, (Packet4d)dv36.r);
  vectorFullDoubleTest(FUN2TEST, (Packet4d)dv36.r, (Packet4d)dv0.r);
  vectorFullDoubleTest(FUN2TEST, (Packet4d)dv36.r, (Packet4d)dv_240.r);
  vectorFullDoubleTest(FUN2TEST, (Packet4d)dv36.r, (Packet4d)dvmin.r);
  vectorFullDoubleTest(FUN2TEST, (Packet4d)dv0.r, (Packet4d)dv0.r);
  vectorFullDoubleTest(FUN2TEST, (Packet4d)dv0.r, (Packet4d)dv_240.r);
  vectorFullDoubleTest(FUN2TEST, (Packet4d)dv0.r, (Packet4d)dvmin.r);
  vectorFullDoubleTest(FUN2TEST, (Packet4d)dv_240.r, (Packet4d)dv_240.r);
  vectorFullDoubleTest(FUN2TEST, (Packet4d)dv_240.r, (Packet4d)dvmin.r);
  vectorFullDoubleTest(FUN2TEST, (Packet4d)dvmin.r, (Packet4d)dvmin.r);

  endTest();

#endif

#ifdef __AVX2__
#endif

#ifdef __AVX512__
#endif
}

addTest(FUN2TEST)

#endif  // EIGEN_MIPP_PLDEXP_TEST_H
