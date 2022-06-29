#include <float.h>
#include <limits.h>
#include "../testVector.h"

#ifndef EIGEN_MIPP_PLOGICAL_SHIFT_LEFT_TEST_H
#define EIGEN_MIPP_PLOGICAL_SHIFT_LEFT_TEST_H

#undef FUN2TEST
#define FUN2TEST plogical_shift_left

void plogical_shift_leftTests() {
  printTestTitle(FUN2TEST);

#ifdef __SSE__

  /* int = Packet4i (half) */
  beginTest("4 int tests");

  MIN2MAX_HALF_INT_VECTOR

  vectorHalfIntTemplateTest(3, FUN2TEST, (Packet4i)ihvmax);
  vectorHalfIntTemplateTest(3, FUN2TEST, (Packet4i)ihv36);
  vectorHalfIntTemplateTest(3, FUN2TEST, (Packet4i)ihv0);
  vectorHalfIntTemplateTest(3, FUN2TEST, (Packet4i)ihv_240);
  vectorHalfIntTemplateTest(3, FUN2TEST, (Packet4i)ihvmin);

  endTest();

#endif

#ifdef __AVX__

  /* int = Packet8i (full) */
  beginTest("8 int tests");

  MIN2MAX_FULL_INT_VECTOR

  vectorFullIntTemplateTest(3, FUN2TEST, (Packet8i)ivmax);
  vectorFullIntTemplateTest(3, FUN2TEST, (Packet8i)iv36);
  vectorFullIntTemplateTest(3, FUN2TEST, (Packet8i)iv0);
  vectorFullIntTemplateTest(3, FUN2TEST, (Packet8i)iv_240);
  vectorFullIntTemplateTest(3, FUN2TEST, (Packet8i)ivmin);

  endTest();

#endif

#ifdef __AVX2__
  /* long = Packet4l */
  beginTest("4 long tests");

  MIN2MAX_FULL_LONG_VECTOR

  vectorFullLongTemplateTest(3, FUN2TEST, (Packet4l)lvmax);
  vectorFullLongTemplateTest(3, FUN2TEST, (Packet4l)lv36);
  vectorFullLongTemplateTest(3, FUN2TEST, (Packet4l)lv0);
  vectorFullLongTemplateTest(3, FUN2TEST, (Packet4l)lv_240);
  vectorFullLongTemplateTest(3, FUN2TEST, (Packet4l)lvmin);

  endTest();

#endif

#ifdef __AVX512F__
#endif
}

addTest(FUN2TEST)

#endif  // EIGEN_MIPP_PLOGICAL_SHIFT_LEFT_TEST_H
