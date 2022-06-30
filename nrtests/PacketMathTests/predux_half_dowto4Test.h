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
  {
    MIN2MAX_8_FLOAT_VECTOR_LOADED

    vectorHalfFloatTemplateTest(FUN2TEST, Packet8f, vmax);
    vectorHalfFloatTemplateTest(FUN2TEST, Packet8f, v36);
    vectorHalfFloatTemplateTest(FUN2TEST, Packet8f, v0);
    vectorHalfFloatTemplateTest(FUN2TEST, Packet8f, v_240);
    vectorHalfFloatTemplateTest(FUN2TEST, Packet8f, vmin);
  }
  endTest();

  /* int = Packet8i (full) -> Packet4i (half) */
  beginTest("full2half int tests");
  {
    MIN2MAX_8_INT_VECTOR_LOADED

    vectorHalfIntTemplateTest(FUN2TEST, Packet8i, vmax);
    vectorHalfIntTemplateTest(FUN2TEST, Packet8i, v36);
    vectorHalfIntTemplateTest(FUN2TEST, Packet8i, v0);
    vectorHalfIntTemplateTest(FUN2TEST, Packet8i, v_240);
    vectorHalfIntTemplateTest(FUN2TEST, Packet8i, vmin);
  }
  endTest();

#endif

#ifdef __AVX2__
#endif

#ifdef __AVX512F__
#endif
}

addTest(FUN2TEST)

#endif  // EIGEN_MIPP_PREDUX_HALF_DOWTO4_TEST_H
