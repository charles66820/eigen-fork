#include <float.h>
#include <limits.h>
#include "../testVector.h"

#ifndef EIGEN_MIPP_PSTOREU_TEST_H
#define EIGEN_MIPP_PSTOREU_TEST_H

#undef FUN2TEST
#define FUN2TEST pstoreu

void pstoreuTests() {
  printTestTitle(FUN2TEST);

#ifdef __SSE__
  /* float = Packet4f (half) */
  beginTest("4 float tests");

  MIN2MAX_HALF_FLOAT_VECTOR

  uRefSingleType(FUN2TEST, float, 4, (Packet4f)fhvmax.r);
  uRefSingleType(FUN2TEST, float, 4, (Packet4f)fhv36.r);
  uRefSingleType(FUN2TEST, float, 4, (Packet4f)fhv0.r);
  uRefSingleType(FUN2TEST, float, 4, (Packet4f)fhv_240.r);
  uRefSingleType(FUN2TEST, float, 4, (Packet4f)fhvmin.r);

  endTest();

  /* double =  Packet2d (half) */
  beginTest("2 double tests");

  MIN2MAX_HALF_DOUBLE_VECTOR

  uRefSingleType(FUN2TEST, double, 2, (Packet2d)dhvmax.r);
  uRefSingleType(FUN2TEST, double, 2, (Packet2d)dhv36.r);
  uRefSingleType(FUN2TEST, double, 2, (Packet2d)dhv0.r);
  uRefSingleType(FUN2TEST, double, 2, (Packet2d)dhv_240.r);
  uRefSingleType(FUN2TEST, double, 2, (Packet2d)dhvmin.r);

  endTest();

  /* int = Packet4i (half) */
  beginTest("4 int tests");

  MIN2MAX_HALF_INT_VECTOR

  uRefSingleType(FUN2TEST, int, 4, (Packet4i)(__m128i)ihvmax.r);
  uRefSingleType(FUN2TEST, int, 4, (Packet4i)(__m128i)ihv36.r);
  uRefSingleType(FUN2TEST, int, 4, (Packet4i)(__m128i)ihv0.r);
  uRefSingleType(FUN2TEST, int, 4, (Packet4i)(__m128i)ihv_240.r);
  uRefSingleType(FUN2TEST, int, 4, (Packet4i)(__m128i)ihvmin.r);

  endTest();

  /* bool = Packet16b */
  beginTest("16 bool tests");

  MIN2MAX_HALF_BOOL_VECTOR

  uRefSingleType(FUN2TEST, bool, 16, (Packet16b)(__m128i)bvtrue.r);
  uRefSingleType(FUN2TEST, bool, 16, (Packet16b)(__m128i)bvfalse.r);

  endTest();

#endif

#ifdef __AVX__
  /* float = Packet8f (full) */
  beginTest("8 float tests");

  MIN2MAX_FULL_FLOAT_VECTOR

  uRefSingleType(FUN2TEST, float, 8, (Packet8f)fvmax.r);
  uRefSingleType(FUN2TEST, float, 8, (Packet8f)fv36.r);
  uRefSingleType(FUN2TEST, float, 8, (Packet8f)fv0.r);
  uRefSingleType(FUN2TEST, float, 8, (Packet8f)fv_240.r);
  uRefSingleType(FUN2TEST, float, 8, (Packet8f)fvmin.r);

  endTest();

  /* double = Packet4d (full) */
  beginTest("4 double tests");

  MIN2MAX_FULL_DOUBLE_VECTOR

  uRefSingleType(FUN2TEST, double, 4, (Packet4d)dvmax.r);
  uRefSingleType(FUN2TEST, double, 4, (Packet4d)dv36.r);
  uRefSingleType(FUN2TEST, double, 4, (Packet4d)dv0.r);
  uRefSingleType(FUN2TEST, double, 4, (Packet4d)dv_240.r);
  uRefSingleType(FUN2TEST, double, 4, (Packet4d)dvmin.r);

  endTest();

  /* int = Packet8i (full) */
  beginTest("8 int tests");

  MIN2MAX_FULL_INT_VECTOR

  uRefSingleType(FUN2TEST, int, 8, (Packet8i)(__m256i)ivmax.r);
  uRefSingleType(FUN2TEST, int, 8, (Packet8i)(__m256i)iv36.r);
  uRefSingleType(FUN2TEST, int, 8, (Packet8i)(__m256i)iv0.r);
  uRefSingleType(FUN2TEST, int, 8, (Packet8i)(__m256i)iv_240.r);
  uRefSingleType(FUN2TEST, int, 8, (Packet8i)(__m256i)ivmin.r);

  endTest();

  /* Eigen::half = Packet8h */
  beginTest("8 Eigen::half tests");

  MIN2MAX_HALF_HALF_VECTOR

  uRefSingleType(FUN2TEST, Eigen::half, 8, (Packet8h)(__m128i)hvmax.r);
  uRefSingleType(FUN2TEST, Eigen::half, 8, (Packet8h)(__m128i)hv36.r);
  uRefSingleType(FUN2TEST, Eigen::half, 8, (Packet8h)(__m128i)hv0.r);
  uRefSingleType(FUN2TEST, Eigen::half, 8, (Packet8h)(__m128i)hv_240.r);
  uRefSingleType(FUN2TEST, Eigen::half, 8, (Packet8h)(__m128i)hvmin.r);

  endTest();

  /* bfloat16 = Packet8bf */
  beginTest("8 bfloat16 tests");

  MIN2MAX_HALF_BFLOAT16_VECTOR

  uRefSingleType(FUN2TEST, bfloat16, 8, (Packet8bf)(__m128i)bfvmax.r);
  uRefSingleType(FUN2TEST, bfloat16, 8, (Packet8bf)(__m128i)bfv36.r);
  uRefSingleType(FUN2TEST, bfloat16, 8, (Packet8bf)(__m128i)bfv0.r);
  uRefSingleType(FUN2TEST, bfloat16, 8, (Packet8bf)(__m128i)bfv_240.r);
  uRefSingleType(FUN2TEST, bfloat16, 8, (Packet8bf)(__m128i)bfvmin.r);

  endTest();

#endif

#ifdef __AVX2__
  /* long = Packet4l */
  beginTest("4 long tests");

  MIN2MAX_FULL_LONG_VECTOR

  uRefSingleType(FUN2TEST, long, 4, (Packet4l)(__m256i)lvmax.r);
  uRefSingleType(FUN2TEST, long, 4, (Packet4l)(__m256i)lv36.r);
  uRefSingleType(FUN2TEST, long, 4, (Packet4l)(__m256i)lv0.r);
  uRefSingleType(FUN2TEST, long, 4, (Packet4l)(__m256i)lv_240.r);
  uRefSingleType(FUN2TEST, long, 4, (Packet4l)(__m256i)lvmin.r);

  endTest();

#endif

#ifdef __AVX512F__
#endif
}

addTest(FUN2TEST)

#endif  // EIGEN_MIPP_PSTOREU_TEST_H
