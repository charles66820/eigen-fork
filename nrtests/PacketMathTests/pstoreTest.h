#include <float.h>
#include <limits.h>
#include "../testVector.h"

#ifndef EIGEN_MIPP_PSTORE_TEST_H
#define EIGEN_MIPP_PSTORE_TEST_H

#undef FUN2TEST
#define FUN2TEST pstore

void pstoreTests() {
  printTestTitle(FUN2TEST);

#ifdef __SSE__
  /* float = Packet4f (half) */
  beginTest("4 float tests");

  MIN2MAX_HALF_FLOAT_VECTOR

  refSingleType(FUN2TEST, float, 4, (Packet4f)fhvmax);
  refSingleType(FUN2TEST, float, 4, (Packet4f)fhv36);
  refSingleType(FUN2TEST, float, 4, (Packet4f)fhv0);
  refSingleType(FUN2TEST, float, 4, (Packet4f)fhv_240);
  refSingleType(FUN2TEST, float, 4, (Packet4f)fhvmin);

  endTest();

  /* double =  Packet2d (half) */
  beginTest("2 double tests");

  MIN2MAX_HALF_DOUBLE_VECTOR

  refSingleType(FUN2TEST, double, 2, dhvmax);
  refSingleType(FUN2TEST, double, 2, dhv36);
  refSingleType(FUN2TEST, double, 2, dhv0);
  refSingleType(FUN2TEST, double, 2, dhv_240);
  refSingleType(FUN2TEST, double, 2, dhvmin);

  endTest();

  /* int = Packet4i (half) */
  beginTest("4 int tests");

  MIN2MAX_HALF_INT_VECTOR

  refSingleType(FUN2TEST, int, 4, (Packet4i)ihvmax);
  refSingleType(FUN2TEST, int, 4, (Packet4i)ihv36);
  refSingleType(FUN2TEST, int, 4, (Packet4i)ihv0);
  refSingleType(FUN2TEST, int, 4, (Packet4i)ihv_240);
  refSingleType(FUN2TEST, int, 4, (Packet4i)ihvmin);

  endTest();

  /* bool = Packet16b */
  beginTest("16 bool tests");

  MIN2MAX_HALF_BOOL_VECTOR

  refSingleType(FUN2TEST, bool, 16, (Packet16b)bvtrue);
  refSingleType(FUN2TEST, bool, 16, (Packet16b)bvfalse);

  endTest();

#endif

#ifdef __AVX__
  /* float = Packet8f (full) */
  beginTest("8 float tests");

  MIN2MAX_FULL_FLOAT_VECTOR

  refSingleType(FUN2TEST, float, 8, (Packet8f)fvmax);
  refSingleType(FUN2TEST, float, 8, (Packet8f)fv36);
  refSingleType(FUN2TEST, float, 8, (Packet8f)fv0);
  refSingleType(FUN2TEST, float, 8, (Packet8f)fv_240);
  refSingleType(FUN2TEST, float, 8, (Packet8f)fvmin);

  endTest();

  /* double = Packet4d (full) */
  beginTest("4 double tests");

  MIN2MAX_FULL_DOUBLE_VECTOR

  refSingleType(FUN2TEST, double, 4, dvmax);
  refSingleType(FUN2TEST, double, 4, dv36);
  refSingleType(FUN2TEST, double, 4, dv0);
  refSingleType(FUN2TEST, double, 4, dv_240);
  refSingleType(FUN2TEST, double, 4, dvmin);

  endTest();

  /* int = Packet8i (full) */
  beginTest("8 int tests");

  MIN2MAX_FULL_INT_VECTOR

  refSingleType(FUN2TEST, int, 8, (Packet8i)ivmax);
  refSingleType(FUN2TEST, int, 8, (Packet8i)iv36);
  refSingleType(FUN2TEST, int, 8, (Packet8i)iv0);
  refSingleType(FUN2TEST, int, 8, (Packet8i)iv_240);
  refSingleType(FUN2TEST, int, 8, (Packet8i)ivmin);

  endTest();

  /* Eigen::half = Packet8h */
  beginTest("8 Eigen::half tests");

  MIN2MAX_HALF_HALF_VECTOR

  refSingleType(FUN2TEST, Eigen::half, 8, (Packet8h)hvmax);
  refSingleType(FUN2TEST, Eigen::half, 8, (Packet8h)hv36);
  refSingleType(FUN2TEST, Eigen::half, 8, (Packet8h)hv0);
  refSingleType(FUN2TEST, Eigen::half, 8, (Packet8h)hv_240);
  refSingleType(FUN2TEST, Eigen::half, 8, (Packet8h)hvmin);

  endTest();

  /* bfloat16 = Packet8bf */
  beginTest("8 bfloat16 tests");

  MIN2MAX_HALF_BFLOAT16_VECTOR

  refSingleType(FUN2TEST, bfloat16, 8, (Packet8bf)bfvmax);
  refSingleType(FUN2TEST, bfloat16, 8, (Packet8bf)bfv36);
  refSingleType(FUN2TEST, bfloat16, 8, (Packet8bf)bfv0);
  refSingleType(FUN2TEST, bfloat16, 8, (Packet8bf)bfv_240);
  refSingleType(FUN2TEST, bfloat16, 8, (Packet8bf)bfvmin);

  endTest();

#endif

#ifdef __AVX2__
  /* long = Packet4l */
  beginTest("4 long tests");

  MIN2MAX_FULL_LONG_VECTOR

  refSingleType(FUN2TEST, long, 4, (Packet4l)lvmax);
  refSingleType(FUN2TEST, long, 4, (Packet4l)lv36);
  refSingleType(FUN2TEST, long, 4, (Packet4l)lv0);
  refSingleType(FUN2TEST, long, 4, (Packet4l)lv_240);
  refSingleType(FUN2TEST, long, 4, (Packet4l)lvmin);

  endTest();

#endif

#ifdef __AVX512F__
#endif
}

addTest(FUN2TEST)

#endif  // EIGEN_MIPP_PSTORE_TEST_H
