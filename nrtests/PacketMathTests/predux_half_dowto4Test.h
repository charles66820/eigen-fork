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

  vectorHalfFloatTemplateTest(FUN2TEST, Packet8f, fvmax);
  vectorHalfFloatTemplateTest(FUN2TEST, Packet8f, fv36);
  vectorHalfFloatTemplateTest(FUN2TEST, Packet8f, fv0);
  vectorHalfFloatTemplateTest(FUN2TEST, Packet8f, fv_240);
  vectorHalfFloatTemplateTest(FUN2TEST, Packet8f, fvmin);

  endTest();

  /* int = Packet8i (full) -> Packet4i (half) */
  beginTest("full2half int tests");

  MIN2MAX_8_INT_VECTOR_LOADED

  vectorHalfIntTemplateTest(FUN2TEST, Packet8i, ivmax);
  vectorHalfIntTemplateTest(FUN2TEST, Packet8i, iv36);
  vectorHalfIntTemplateTest(FUN2TEST, Packet8i, iv0);
  vectorHalfIntTemplateTest(FUN2TEST, Packet8i, iv_240);
  vectorHalfIntTemplateTest(FUN2TEST, Packet8i, ivmin);

  endTest();

#endif

#ifdef __AVX2__
#endif

#ifdef __AVX512F__
#endif
}

addTest(FUN2TEST)

#endif  // EIGEN_MIPP_PREDUX_HALF_DOWTO4_TEST_H
