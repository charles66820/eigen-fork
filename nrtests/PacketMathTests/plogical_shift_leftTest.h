#include <float.h>
#include <limits.h>

#ifndef EIGEN_MIPP_PLOGICAL_SHIFT_LEFT_TEST_H
#define EIGEN_MIPP_PLOGICAL_SHIFT_LEFT_TEST_H

#undef FUN2TEST
#define FUN2TEST plogical_shift_left

void plogical_shift_leftTests() {
  printTestTitle(FUN2TEST);

#ifdef __SSE__

  /* int = Packet4i (half) */
  beginTest("4 int tests");

  MIN2MAX_4_INT_VECTOR_LOADED

  vectorHalfIntTemplateTest(FUN2TEST, 3, (Packet4i)ihvmax);
  vectorHalfIntTemplateTest(FUN2TEST, 3, (Packet4i)ihv36);
  vectorHalfIntTemplateTest(FUN2TEST, 3, (Packet4i)ihv0);
  vectorHalfIntTemplateTest(FUN2TEST, 3, (Packet4i)ihv_240);
  vectorHalfIntTemplateTest(FUN2TEST, 3, (Packet4i)ihvmin);

  endTest();

#endif

#ifdef __AVX__

  /* int = Packet8i (full) */
  beginTest("8 int tests");

  MIN2MAX_8_INT_VECTOR_LOADED

  vectorFullIntTemplateTest(FUN2TEST, 3, (Packet8i)ivmax);
  vectorFullIntTemplateTest(FUN2TEST, 3, (Packet8i)iv36);
  vectorFullIntTemplateTest(FUN2TEST, 3, (Packet8i)iv0);
  vectorFullIntTemplateTest(FUN2TEST, 3, (Packet8i)iv_240);
  vectorFullIntTemplateTest(FUN2TEST, 3, (Packet8i)ivmin);

  endTest();

#endif

#ifdef __AVX2__
  /* long = Packet4l */
  beginTest("4 long tests");

  MIN2MAX_4_LONG_VECTOR_LOADED

  vectorFullLongTemplateTest(FUN2TEST, 3, (Packet4l)lvmax);
  vectorFullLongTemplateTest(FUN2TEST, 3, (Packet4l)lv36);
  vectorFullLongTemplateTest(FUN2TEST, 3, (Packet4l)lv0);
  vectorFullLongTemplateTest(FUN2TEST, 3, (Packet4l)lv_240);
  vectorFullLongTemplateTest(FUN2TEST, 3, (Packet4l)lvmin);

  endTest();

#endif

#ifdef __AVX512F__
#endif
}

addTest(FUN2TEST)

#endif  // EIGEN_MIPP_PLOGICAL_SHIFT_LEFT_TEST_H
