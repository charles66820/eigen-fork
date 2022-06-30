#include <float.h>
#include <limits.h>

#ifndef EIGEN_MIPP_PREDUX_HALF_DOWTO4_TEST_H
#define EIGEN_MIPP_PREDUX_HALF_DOWTO4_TEST_H

#undef FUN2TEST
#define FUN2TEST predux_half_dowto4

void predux_half_dowto4Tests() {
  printTestTitle(FUN2TEST);

#ifdef __SSE__
#endif

#ifdef __AVX__
  /* float = Packet8f (full) -> Packet4f (half)*/
  beginTest("full2half float tests");

  MIN2MAX_8_FLOAT_VECTOR_LOADED

  vectorHalfFloatTemplateTest(Packet8f, FUN2TEST, fvmax);
  vectorHalfFloatTemplateTest(Packet8f, FUN2TEST, fv36);
  vectorHalfFloatTemplateTest(Packet8f, FUN2TEST, fv0);
  vectorHalfFloatTemplateTest(Packet8f, FUN2TEST, fv_240);
  vectorHalfFloatTemplateTest(Packet8f, FUN2TEST, fvmin);

  endTest();

  /* int = Packet8i (full) -> Packet4i (half) */
  beginTest("full2half int tests");

  MIN2MAX_8_INT_VECTOR_LOADED

  vectorHalfIntTemplateTest(Packet8i, FUN2TEST, ivmax);
  vectorHalfIntTemplateTest(Packet8i, FUN2TEST, iv36);
  vectorHalfIntTemplateTest(Packet8i, FUN2TEST, iv0);
  vectorHalfIntTemplateTest(Packet8i, FUN2TEST, iv_240);
  vectorHalfIntTemplateTest(Packet8i, FUN2TEST, ivmin);

  endTest();

#endif

#ifdef __AVX2__
#endif

#ifdef __AVX512F__
#endif
}

addTest(FUN2TEST)

#endif  // EIGEN_MIPP_PREDUX_HALF_DOWTO4_TEST_H
