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

  MIN2MAX_4_INT_VECTOR

  vectorHalfIntTemplateTest(3, FUN2TEST, ihvmax);
  vectorHalfIntTemplateTest(3, FUN2TEST, ihv36);
  vectorHalfIntTemplateTest(3, FUN2TEST, ihv0);
  vectorHalfIntTemplateTest(3, FUN2TEST, ihv_240);
  vectorHalfIntTemplateTest(3, FUN2TEST, ihvmin);

  endTest();

#endif

#ifdef __AVX__

  /* int = Packet8i (full) */
  beginTest("8 int tests");

  MIN2MAX_8_INT_VECTOR

  vectorFullIntTemplateTest(3, FUN2TEST, ivmax);
  vectorFullIntTemplateTest(3, FUN2TEST, iv36);
  vectorFullIntTemplateTest(3, FUN2TEST, iv0);
  vectorFullIntTemplateTest(3, FUN2TEST, iv_240);
  vectorFullIntTemplateTest(3, FUN2TEST, ivmin);

  endTest();

#endif

#ifdef __AVX2__
#endif

#ifdef __AVX512F__
#endif
}

addTest(FUN2TEST)

#endif  // EIGEN_MIPP_PARITHMETIC_SHIFT_RIGHT_TEST_H
