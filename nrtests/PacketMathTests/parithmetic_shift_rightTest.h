#include <float.h>
#include <limits.h>

#ifndef EIGEN_MIPP_PARITHMETIC_SHIFT_RIGHT_TEST_H
#define EIGEN_MIPP_PARITHMETIC_SHIFT_RIGHT_TEST_H

#undef FUN2TEST
#define FUN2TEST parithmetic_shift_right

void parithmetic_shift_rightTests() {
  printTestTitle(FUN2TEST);

#ifdef __SSE__

  /* int = Packet4i (half) */
  beginTest("4 int tests");

  MIN2MAX_4_INT_VECTOR_LOADED

  vectorHalfIntTemplateTest(FUN2TEST, 3, ihvmax);
  vectorHalfIntTemplateTest(FUN2TEST, 3, ihv36);
  vectorHalfIntTemplateTest(FUN2TEST, 3, ihv0);
  vectorHalfIntTemplateTest(FUN2TEST, 3, ihv_240);
  vectorHalfIntTemplateTest(FUN2TEST, 3, ihvmin);

  endTest();

#endif

#ifdef __AVX__

  /* int = Packet8i (full) */
  beginTest("8 int tests");

  MIN2MAX_8_INT_VECTOR_LOADED

  vectorFullIntTemplateTest(FUN2TEST, 3, ivmax);
  vectorFullIntTemplateTest(FUN2TEST, 3, iv36);
  vectorFullIntTemplateTest(FUN2TEST, 3, iv0);
  vectorFullIntTemplateTest(FUN2TEST, 3, iv_240);
  vectorFullIntTemplateTest(FUN2TEST, 3, ivmin);

  endTest();

#endif

#ifdef __AVX2__
#endif

#ifdef __AVX512F__
#endif
}

addTest(FUN2TEST)

#endif  // EIGEN_MIPP_PARITHMETIC_SHIFT_RIGHT_TEST_H
