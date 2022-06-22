#include <float.h>
#include <limits.h>
#include "testVector.h"

#ifndef EIGEN_MIPP_PARITHMETIC_SHIFT_RIGHT_TEST_H
#define EIGEN_MIPP_PARITHMETIC_SHIFT_RIGHT_TEST_H

#undef FUN2TEST
#define FUN2TEST parithmetic_shift_right

void parithmetic_shift_rightTests() {
  std::cout << printTestTitle(FUN2TEST) << std::endl;

#ifdef __SSE__

  /* int = Packet4i (half) */
  beginTest("half int tests");

  loadVectorHalf(vector4, int, ihvmax, INT_HALF_CAST, Packet4i, INT_MAX, 0);
  loadVectorHalf(vector4, int, ihv36, INT_HALF_CAST, Packet4i, 36, 0);
  loadVectorHalf(vector4, int, ihv0, INT_HALF_CAST, Packet4i, 0, 0);
  loadVectorHalf(vector4, int, ihv_240, INT_HALF_CAST, Packet4i, -240, 0);
  loadVectorHalf(vector4, int, ihvmin, INT_HALF_CAST, Packet4i, INT_MIN, 0);

  dynHalfIntTemplateTest(3, FUN2TEST, (__m128i)ihvmax.r);
  dynHalfIntTemplateTest(3, FUN2TEST, (__m128i)ihv36.r);
  dynHalfIntTemplateTest(3, FUN2TEST, (__m128i)ihv0.r);
  dynHalfIntTemplateTest(3, FUN2TEST, (__m128i)ihv_240.r);
  dynHalfIntTemplateTest(3, FUN2TEST, (__m128i)ihvmin.r);

  endTest();

#endif

#ifdef __AVX__

  /* int = Packet8i (full) */
  beginTest("full int tests");

  loadVectorFull(vector8, int, ivmax, INT_FULL_CAST, Packet8i, INT_MAX, 0);
  loadVectorFull(vector8, int, iv36, INT_FULL_CAST, Packet8i, 36, 0);
  loadVectorFull(vector8, int, iv0, INT_FULL_CAST, Packet8i, 0, 0);
  loadVectorFull(vector8, int, iv_240, INT_FULL_CAST, Packet8i, -240, 0);
  loadVectorFull(vector8, int, ivmin, INT_FULL_CAST, Packet8i, INT_MIN, 0);

  dynFullIntTemplateTest(3, FUN2TEST, (__m256i)ivmax.r);
  dynFullIntTemplateTest(3, FUN2TEST, (__m256i)iv36.r);
  dynFullIntTemplateTest(3, FUN2TEST, (__m256i)iv0.r);
  dynFullIntTemplateTest(3, FUN2TEST, (__m256i)iv_240.r);
  dynFullIntTemplateTest(3, FUN2TEST, (__m256i)ivmin.r);

  endTest();

#endif

#ifdef __AVX2__
  /* long = Packet4l */
  beginTest("long tests");

  loadVectorFull(vector4, long, lvmax, INT_FULL_CAST, Packet4l, LONG_MAX, 0L);
  loadVectorFull(vector4, long, lv36, INT_FULL_CAST, Packet4l, 36L, 0L);
  loadVectorFull(vector4, long, lv0, INT_FULL_CAST, Packet4l, 0L, 0L);
  loadVectorFull(vector4, long, lv_240, INT_FULL_CAST, Packet4l, -240L, 0L);
  loadVectorFull(vector4, long, lvmin, INT_FULL_CAST, Packet4l, LONG_MIN, 0L);

  dynFullLongTemplateTest(3, FUN2TEST, (__m256i)lvmax.r);
  dynFullLongTemplateTest(3, FUN2TEST, (__m256i)lv36.r);
  dynFullLongTemplateTest(3, FUN2TEST, (__m256i)lv0.r);
  dynFullLongTemplateTest(3, FUN2TEST, (__m256i)lv_240.r);
  dynFullLongTemplateTest(3, FUN2TEST, (__m256i)lvmin.r);

  endTest();

#endif

#ifdef __AVX512__
#endif
}

#endif  // EIGEN_MIPP_PARITHMETIC_SHIFT_RIGHT_TEST_H
