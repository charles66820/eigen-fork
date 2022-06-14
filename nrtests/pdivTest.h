#include <float.h>
#include <limits.h>
#include "testVector.h"

#ifndef EIGEN_MIPP_PDIV_TEST_H
#define EIGEN_MIPP_PDIV_TEST_H

#undef FUN2TEST
#define FUN2TEST pdiv

#define str(s) #s
#define xstr(s) str(s)

#define loadVector(vec, type, typeReg, name, cast, EigenType, value, delta, MIPP_reg) \
  vec(type, name##_tab, value, delta);                                                \
  mipp::MIPP_reg<typeReg> name = cast pload<EigenType>(name##_tab);

#define loadVectorFull(vec, type, name, cast, full, value, delta) \
  loadVector(vec, type, type, name, cast, full, value, delta, Reg)
#define loadVectorHalf(vec, type, name, cast, half, value, delta) \
  loadVector(vec, type, type, name, cast, half, value, delta, Reg_2)
#define loadVectorFullRegType(vec, type, typeReg, name, cast, full, value, delta) \
  loadVector(vec, type, typeReg, name, cast, full, value, delta, Reg)
#define loadVectorHalfRegType(vec, type, typeReg, name, cast, half, value, delta) \
  loadVector(vec, type, typeReg, name, cast, half, value, delta, Reg_2)

void pdivTests() {
  std::cout << xstr(FUN2TEST) << " :" << std::endl;

#ifdef __SSE__
  /* float = Packet4f (half) */
  std::cout << "half float tests" << std::endl;

  loadVectorHalf(vector4, float, fhvmax, , Packet4f, FLT_MAX, 0.0f);
  loadVectorHalf(vector4, float, fhv36, , Packet4f, 36.7f, 0.0f);
  loadVectorHalf(vector4, float, fhv0, , Packet4f, 0.0f, 0.0f);
  loadVectorHalf(vector4, float, fhv_240, , Packet4f, -240.98f, 0.0f);
  loadVectorHalf(vector4, float, fhvmin, , Packet4f, FLT_MAX, 0.0f);

  dynHalfFloatTest(FUN2TEST, fhvmax.r, fhvmax.r);
  dynHalfFloatTest(FUN2TEST, fhvmax.r, fhv36.r);
  dynHalfFloatTest(FUN2TEST, fhvmax.r, fhv0.r);
  dynHalfFloatTest(FUN2TEST, fhvmax.r, fhv_240.r);
  dynHalfFloatTest(FUN2TEST, fhvmax.r, fhvmin.r);
  dynHalfFloatTest(FUN2TEST, fhv36.r, fhv36.r);
  dynHalfFloatTest(FUN2TEST, fhv36.r, fhv0.r);
  dynHalfFloatTest(FUN2TEST, fhv36.r, fhv_240.r);
  dynHalfFloatTest(FUN2TEST, fhv36.r, fhvmin.r);
  dynHalfFloatTest(FUN2TEST, fhv0.r, fhv0.r);
  dynHalfFloatTest(FUN2TEST, fhv0.r, fhv_240.r);
  dynHalfFloatTest(FUN2TEST, fhv0.r, fhvmin.r);
  dynHalfFloatTest(FUN2TEST, fhv_240.r, fhv_240.r);
  dynHalfFloatTest(FUN2TEST, fhv_240.r, fhvmin.r);
  dynHalfFloatTest(FUN2TEST, fhvmin.r, fhvmin.r);

  /* double =  Packet2d (half) */
  std::cout << "half double tests" << std::endl;

  loadVectorHalf(vector2, double, dhvmax, HALF_CAST, Packet2d, DBL_MAX, 0.0d);
  loadVectorHalf(vector2, double, dhv36, HALF_CAST, Packet2d, 36.7d, 0.0d);
  loadVectorHalf(vector2, double, dhv0, HALF_CAST, Packet2d, 0.0d, 0.0d);
  loadVectorHalf(vector2, double, dhv_240, HALF_CAST, Packet2d, -240.98d, 0.0d);
  loadVectorHalf(vector2, double, dhvmin, HALF_CAST, Packet2d, DBL_MIN, 0.0d);

  dynHalfDoubleTest(FUN2TEST, (Packet2d)dhvmax.r, (Packet2d)dhvmax.r);
  dynHalfDoubleTest(FUN2TEST, (Packet2d)dhvmax.r, (Packet2d)dhv36.r);
  dynHalfDoubleTest(FUN2TEST, (Packet2d)dhvmax.r, (Packet2d)dhv0.r);
  dynHalfDoubleTest(FUN2TEST, (Packet2d)dhvmax.r, (Packet2d)dhv_240.r);
  dynHalfDoubleTest(FUN2TEST, (Packet2d)dhvmax.r, (Packet2d)dhvmin.r);
  dynHalfDoubleTest(FUN2TEST, (Packet2d)dhv36.r, (Packet2d)dhv36.r);
  dynHalfDoubleTest(FUN2TEST, (Packet2d)dhv36.r, (Packet2d)dhv0.r);
  dynHalfDoubleTest(FUN2TEST, (Packet2d)dhv36.r, (Packet2d)dhv_240.r);
  dynHalfDoubleTest(FUN2TEST, (Packet2d)dhv36.r, (Packet2d)dhvmin.r);
  dynHalfDoubleTest(FUN2TEST, (Packet2d)dhv0.r, (Packet2d)dhv0.r);
  dynHalfDoubleTest(FUN2TEST, (Packet2d)dhv0.r, (Packet2d)dhv_240.r);
  dynHalfDoubleTest(FUN2TEST, (Packet2d)dhv0.r, (Packet2d)dhvmin.r);
  dynHalfDoubleTest(FUN2TEST, (Packet2d)dhv_240.r, (Packet2d)dhv_240.r);
  dynHalfDoubleTest(FUN2TEST, (Packet2d)dhv_240.r, (Packet2d)dhvmin.r);
  dynHalfDoubleTest(FUN2TEST, (Packet2d)dhvmin.r, (Packet2d)dhvmin.r);

#endif

#ifdef __AVX__
  /* float = Packet8f (full) */
  std::cout << "full float tests" << std::endl;
  loadVectorFull(vector8, float, fvmax, , Packet8f, FLT_MAX, 0.0f);
  loadVectorFull(vector8, float, fv36, , Packet8f, 36.7f, 0.0f);
  loadVectorFull(vector8, float, fv0, , Packet8f, 0.0f, 0.0f);
  loadVectorFull(vector8, float, fv_240, , Packet8f, -240.98f, 0.0f);
  loadVectorFull(vector8, float, fvmin, , Packet8f, FLT_MAX, 0.0f);

  dynFullFloatTest(FUN2TEST, fvmax.r, fvmax.r);
  dynFullFloatTest(FUN2TEST, fvmax.r, fv36.r);
  dynFullFloatTest(FUN2TEST, fvmax.r, fv0.r);
  dynFullFloatTest(FUN2TEST, fvmax.r, fv_240.r);
  dynFullFloatTest(FUN2TEST, fvmax.r, fvmin.r);
  dynFullFloatTest(FUN2TEST, fv36.r, fv36.r);
  dynFullFloatTest(FUN2TEST, fv36.r, fv0.r);
  dynFullFloatTest(FUN2TEST, fv36.r, fv_240.r);
  dynFullFloatTest(FUN2TEST, fv36.r, fvmin.r);
  dynFullFloatTest(FUN2TEST, fv0.r, fv0.r);
  dynFullFloatTest(FUN2TEST, fv0.r, fv_240.r);
  dynFullFloatTest(FUN2TEST, fv0.r, fvmin.r);
  dynFullFloatTest(FUN2TEST, fv_240.r, fv_240.r);
  dynFullFloatTest(FUN2TEST, fv_240.r, fvmin.r);
  dynFullFloatTest(FUN2TEST, fvmin.r, fvmin.r);

  /* double = Packet4d (full) */
  std::cout << "full double tests" << std::endl;

  loadVectorFull(vector4, double, dvmax, FULL_CAST, Packet4d, DBL_MAX, 0.0d);
  loadVectorFull(vector4, double, dv36, FULL_CAST, Packet4d, 36.7d, 0.0d);
  loadVectorFull(vector4, double, dv0, FULL_CAST, Packet4d, 0.0d, 0.0d);
  loadVectorFull(vector4, double, dv_240, FULL_CAST, Packet4d, -240.98d, 0.0d);
  loadVectorFull(vector4, double, dvmin, FULL_CAST, Packet4d, DBL_MIN, 0.0d);

  dynFullDoubleTest(FUN2TEST, (Packet4d)dvmax.r, (Packet4d)dvmax.r);
  dynFullDoubleTest(FUN2TEST, (Packet4d)dvmax.r, (Packet4d)dv36.r);
  dynFullDoubleTest(FUN2TEST, (Packet4d)dvmax.r, (Packet4d)dv0.r);
  dynFullDoubleTest(FUN2TEST, (Packet4d)dvmax.r, (Packet4d)dv_240.r);
  dynFullDoubleTest(FUN2TEST, (Packet4d)dvmax.r, (Packet4d)dvmin.r);
  dynFullDoubleTest(FUN2TEST, (Packet4d)dv36.r, (Packet4d)dv36.r);
  dynFullDoubleTest(FUN2TEST, (Packet4d)dv36.r, (Packet4d)dv0.r);
  dynFullDoubleTest(FUN2TEST, (Packet4d)dv36.r, (Packet4d)dv_240.r);
  dynFullDoubleTest(FUN2TEST, (Packet4d)dv36.r, (Packet4d)dvmin.r);
  dynFullDoubleTest(FUN2TEST, (Packet4d)dv0.r, (Packet4d)dv0.r);
  dynFullDoubleTest(FUN2TEST, (Packet4d)dv0.r, (Packet4d)dv_240.r);
  dynFullDoubleTest(FUN2TEST, (Packet4d)dv0.r, (Packet4d)dvmin.r);
  dynFullDoubleTest(FUN2TEST, (Packet4d)dv_240.r, (Packet4d)dv_240.r);
  dynFullDoubleTest(FUN2TEST, (Packet4d)dv_240.r, (Packet4d)dvmin.r);
  dynFullDoubleTest(FUN2TEST, (Packet4d)dvmin.r, (Packet4d)dvmin.r);

  /* Eigen::half = Packet8h */
  std::cout << "Eigen::half tests" << std::endl;

  loadVectorHalfRegType(vector8, Eigen::half, short, hvmax, INT_HALF_CAST, Packet8h, half(FLT_MAX), half(0.0f));
  loadVectorHalfRegType(vector8, Eigen::half, short, hv36, INT_HALF_CAST, Packet8h, half(36.7f), half(0.0f));
  loadVectorHalfRegType(vector8, Eigen::half, short, hv0, INT_HALF_CAST, Packet8h, half(0.0f), half(0.0f));
  loadVectorHalfRegType(vector8, Eigen::half, short, hv_240, INT_HALF_CAST, Packet8h, half(-240.98f), half(0.0f));
  loadVectorHalfRegType(vector8, Eigen::half, short, hvmin, INT_HALF_CAST, Packet8h, half(FLT_MAX), half(0.0f));

  dynHalfEigenHalfTest(FUN2TEST, (__m128i)hvmax.r, (__m128i)hvmax.r);
  dynHalfEigenHalfTest(FUN2TEST, (__m128i)hvmax.r, (__m128i)hv36.r);
  dynHalfEigenHalfTest(FUN2TEST, (__m128i)hvmax.r, (__m128i)hv0.r);
  dynHalfEigenHalfTest(FUN2TEST, (__m128i)hvmax.r, (__m128i)hv_240.r);
  dynHalfEigenHalfTest(FUN2TEST, (__m128i)hvmax.r, (__m128i)hvmin.r);
  dynHalfEigenHalfTest(FUN2TEST, (__m128i)hv36.r, (__m128i)hv36.r);
  dynHalfEigenHalfTest(FUN2TEST, (__m128i)hv36.r, (__m128i)hv0.r);
  dynHalfEigenHalfTest(FUN2TEST, (__m128i)hv36.r, (__m128i)hv_240.r);
  dynHalfEigenHalfTest(FUN2TEST, (__m128i)hv36.r, (__m128i)hvmin.r);
  dynHalfEigenHalfTest(FUN2TEST, (__m128i)hv0.r, (__m128i)hv0.r);
  dynHalfEigenHalfTest(FUN2TEST, (__m128i)hv0.r, (__m128i)hv_240.r);
  dynHalfEigenHalfTest(FUN2TEST, (__m128i)hv0.r, (__m128i)hvmin.r);
  dynHalfEigenHalfTest(FUN2TEST, (__m128i)hv_240.r, (__m128i)hv_240.r);
  dynHalfEigenHalfTest(FUN2TEST, (__m128i)hv_240.r, (__m128i)hvmin.r);
  dynHalfEigenHalfTest(FUN2TEST, (__m128i)hvmin.r, (__m128i)hvmin.r);

  /* bfloat16 = Packet8bf */
  std::cout << "bfloat16 tests" << std::endl;

  loadVectorHalfRegType(vector8, bfloat16, short, bfvmax, INT_HALF_CAST, Packet8bf, bfloat16(FLT_MAX), bfloat16(0.0f));
  loadVectorHalfRegType(vector8, bfloat16, short, bfv36, INT_HALF_CAST, Packet8bf, bfloat16(36.7f), bfloat16(0.0f));
  loadVectorHalfRegType(vector8, bfloat16, short, bfv0, INT_HALF_CAST, Packet8bf, bfloat16(0.0f), bfloat16(0.0f));
  loadVectorHalfRegType(vector8, bfloat16, short, bfv_240, INT_HALF_CAST, Packet8bf, bfloat16(-240.98f),
                        bfloat16(0.0f));
  loadVectorHalfRegType(vector8, bfloat16, short, bfvmin, INT_HALF_CAST, Packet8bf, bfloat16(FLT_MAX), bfloat16(0.0f));

  dynHalfBfloat16Test(FUN2TEST, (__m128i)bfvmax.r, (__m128i)bfvmax.r);
  dynHalfBfloat16Test(FUN2TEST, (__m128i)bfvmax.r, (__m128i)bfv36.r);
  dynHalfBfloat16Test(FUN2TEST, (__m128i)bfvmax.r, (__m128i)bfv0.r);
  dynHalfBfloat16Test(FUN2TEST, (__m128i)bfvmax.r, (__m128i)bfv_240.r);
  dynHalfBfloat16Test(FUN2TEST, (__m128i)bfvmax.r, (__m128i)bfvmin.r);
  dynHalfBfloat16Test(FUN2TEST, (__m128i)bfv36.r, (__m128i)bfv36.r);
  dynHalfBfloat16Test(FUN2TEST, (__m128i)bfv36.r, (__m128i)bfv0.r);
  dynHalfBfloat16Test(FUN2TEST, (__m128i)bfv36.r, (__m128i)bfv_240.r);
  dynHalfBfloat16Test(FUN2TEST, (__m128i)bfv36.r, (__m128i)bfvmin.r);
  dynHalfBfloat16Test(FUN2TEST, (__m128i)bfv0.r, (__m128i)bfv0.r);
  dynHalfBfloat16Test(FUN2TEST, (__m128i)bfv0.r, (__m128i)bfv_240.r);
  dynHalfBfloat16Test(FUN2TEST, (__m128i)bfv0.r, (__m128i)bfvmin.r);
  dynHalfBfloat16Test(FUN2TEST, (__m128i)bfv_240.r, (__m128i)bfv_240.r);
  dynHalfBfloat16Test(FUN2TEST, (__m128i)bfv_240.r, (__m128i)bfvmin.r);
  dynHalfBfloat16Test(FUN2TEST, (__m128i)bfvmin.r, (__m128i)bfvmin.r);
#endif

#ifdef __AVX512__
#endif
}

#endif  // EIGEN_MIPP_PDIV_TEST_H
