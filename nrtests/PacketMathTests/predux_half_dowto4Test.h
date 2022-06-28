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

  MIN2MAX_FULL_FLOAT_VECTOR

  vectorHalfFloatTemplateTest(Packet8f, FUN2TEST, fvmax.r);
  vectorHalfFloatTemplateTest(Packet8f, FUN2TEST, fv36.r);
  vectorHalfFloatTemplateTest(Packet8f, FUN2TEST, fv0.r);
  vectorHalfFloatTemplateTest(Packet8f, FUN2TEST, fv_240.r);
  vectorHalfFloatTemplateTest(Packet8f, FUN2TEST, fvmin.r);

  endTest();

  /* int = Packet8i (full) -> Packet4i (half) */
  beginTest("full2half int tests");

  MIN2MAX_FULL_INT_VECTOR

  vectorHalfIntTemplateTest(Packet8i, FUN2TEST, (__m256i)ivmax.r);
  vectorHalfIntTemplateTest(Packet8i, FUN2TEST, (__m256i)iv36.r);
  vectorHalfIntTemplateTest(Packet8i, FUN2TEST, (__m256i)iv0.r);
  vectorHalfIntTemplateTest(Packet8i, FUN2TEST, (__m256i)iv_240.r);
  vectorHalfIntTemplateTest(Packet8i, FUN2TEST, (__m256i)ivmin.r);

  endTest();

#endif

#ifdef __AVX2__
#endif

#ifdef __AVX512F__
#endif
}

addTest(FUN2TEST)

#endif  // EIGEN_MIPP_PREDUX_HALF_DOWTO4_TEST_H
