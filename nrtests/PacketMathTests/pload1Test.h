#include <float.h>
#include <limits.h>

#ifndef EIGEN_MIPP_PLOAD1_TEST_H
#define EIGEN_MIPP_PLOAD1_TEST_H

#undef FUN2TEST
#define FUN2TEST pload1

void pload1Tests() {
  printTestTitle(FUN2TEST);

#ifdef __SSE__

#if EIGEN_COMP_GNUC_STRICT && (!defined __AVX__)
  /* float = Packet4f (half) */
  beginTest("4 float tests");

  MIN2MAX_4_FLOAT_VECTOR

  min2MaxTests(vectorHalfFloatTest, FUN2TEST, fhvmax, fhv36, fhv0, fhv_240, fhvmin);

  endTest();

#endif

#endif

#ifdef __AVX__
  /* float = Packet8f (full) */
  beginTest("8 float tests");

  MIN2MAX_8_FLOAT_VECTOR

  min2MaxTests(vectorFullFloatTest, FUN2TEST, fvmax, fv36, fv0, fv_240, fvmin);

  endTest();

  /* double = Packet4d (full) */
  beginTest("4 double tests");

  MIN2MAX_4_DOUBLE_VECTOR

  min2MaxTests(vectorFullDoubleTest, FUN2TEST, dvmax, dv36, dv0, dv_240, dvmin);

  endTest();

#endif

#ifdef __AVX2__
  /* long = Packet4l */
  beginTest("4 long tests");

  MIN2MAX_4_LONG_VECTOR

  min2MaxTests(vectorFullLongTest, FUN2TEST, lvmax, lv36, lv0, lv_240, lvmin);

  endTest();

#endif

#ifdef __AVX512F__
#endif
}

addTest(FUN2TEST)

#endif  // EIGEN_MIPP_PLOAD1_TEST_H
