#include <float.h>
#include <limits.h>
#include "../testVector.h"

#ifndef EIGEN_MIPP_PREDUX_HALF_DOWTO4_TEST_H
#define EIGEN_MIPP_PREDUX_HALF_DOWTO4_TEST_H

#undef FUN2TEST
#define FUN2TEST predux_half_dowto4

void predux_half_dowto4Tests() {
  std::cout << printTestTitle(FUN2TEST) << std::endl;

#ifdef __SSE__
#endif

#ifdef __AVX__
  /* float = Packet8f (full) -> Packet4f (half)*/
  beginTest("full2half float tests");
  loadVectorFull(vector8, float, fvmax, , Packet8f, FLT_MAX, 0.0f);
  loadVectorFull(vector8, float, fv36, , Packet8f, 36.7f, 0.0f);
  loadVectorFull(vector8, float, fv0, , Packet8f, 0.0f, 0.0f);
  loadVectorFull(vector8, float, fv_240, , Packet8f, -240.98f, 0.0f);
  loadVectorFull(vector8, float, fvmin, , Packet8f, FLT_MAX, 0.0f);

  vectorHalfFloatTemplateTest(Packet8f, FUN2TEST, fvmax.r);
  vectorHalfFloatTemplateTest(Packet8f, FUN2TEST, fv36.r);
  vectorHalfFloatTemplateTest(Packet8f, FUN2TEST, fv0.r);
  vectorHalfFloatTemplateTest(Packet8f, FUN2TEST, fv_240.r);
  vectorHalfFloatTemplateTest(Packet8f, FUN2TEST, fvmin.r);

  endTest();

  /* int = Packet8i (full) -> Packet4i (half) */
  beginTest("full2half int tests");

  loadVectorFull(vector8, int, ivmax, INT_FULL_CAST, Packet8i, INT_MAX, 0);
  loadVectorFull(vector8, int, iv36, INT_FULL_CAST, Packet8i, 36, 0);
  loadVectorFull(vector8, int, iv0, INT_FULL_CAST, Packet8i, 0, 0);
  loadVectorFull(vector8, int, iv_240, INT_FULL_CAST, Packet8i, -240, 0);
  loadVectorFull(vector8, int, ivmin, INT_FULL_CAST, Packet8i, INT_MIN, 0);

  vectorHalfIntTemplateTest(Packet8i, FUN2TEST, (__m256i)ivmax.r);
  vectorHalfIntTemplateTest(Packet8i, FUN2TEST, (__m256i)iv36.r);
  vectorHalfIntTemplateTest(Packet8i, FUN2TEST, (__m256i)iv0.r);
  vectorHalfIntTemplateTest(Packet8i, FUN2TEST, (__m256i)iv_240.r);
  vectorHalfIntTemplateTest(Packet8i, FUN2TEST, (__m256i)ivmin.r);

  endTest();

#endif

#ifdef __AVX2__
#endif

#ifdef __AVX512__
#endif
}

addTest(FUN2TEST)

#endif  // EIGEN_MIPP_PREDUX_HALF_DOWTO4_TEST_H
