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

  vectorHalfIntTemplateTest(3, FUN2TEST, (Packet4i)(__m128i)ihvmax.r);
  vectorHalfIntTemplateTest(3, FUN2TEST, (Packet4i)(__m128i)ihv36.r);
  vectorHalfIntTemplateTest(3, FUN2TEST, (Packet4i)(__m128i)ihv0.r);
  vectorHalfIntTemplateTest(3, FUN2TEST, (Packet4i)(__m128i)ihv_240.r);
  vectorHalfIntTemplateTest(3, FUN2TEST, (Packet4i)(__m128i)ihvmin.r);

  endTest();

#endif

#ifdef __AVX__

  /* int = Packet8i (full) */
  beginTest("8 int tests");

  MIN2MAX_FULL_INT_VECTOR

  vectorFullIntTemplateTest(3, FUN2TEST, (Packet8i)(__m256i)ivmax.r);
  vectorFullIntTemplateTest(3, FUN2TEST, (Packet8i)(__m256i)iv36.r);
  vectorFullIntTemplateTest(3, FUN2TEST, (Packet8i)(__m256i)iv0.r);
  vectorFullIntTemplateTest(3, FUN2TEST, (Packet8i)(__m256i)iv_240.r);
  vectorFullIntTemplateTest(3, FUN2TEST, (Packet8i)(__m256i)ivmin.r);

  endTest();

#endif

#ifdef __AVX2__
  /* long = Packet4l */
  beginTest("4 long tests");

  MIN2MAX_FULL_LONG_VECTOR

  vectorFullLongTemplateTest(3, FUN2TEST, (Packet4l)(__m256i)lvmax.r);
  vectorFullLongTemplateTest(3, FUN2TEST, (Packet4l)(__m256i)lv36.r);
  vectorFullLongTemplateTest(3, FUN2TEST, (Packet4l)(__m256i)lv0.r);
  vectorFullLongTemplateTest(3, FUN2TEST, (Packet4l)(__m256i)lv_240.r);
  vectorFullLongTemplateTest(3, FUN2TEST, (Packet4l)(__m256i)lvmin.r);

  endTest();

#endif

#ifdef __AVX512F__
#endif
}

addTest(FUN2TEST)

#endif  // EIGEN_MIPP_PLOGICAL_SHIFT_LEFT_TEST_H
