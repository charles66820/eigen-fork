#include <float.h>
#include <limits.h>

#ifndef EIGEN_MIPP_PLOADDUP_TEST_H
#define EIGEN_MIPP_PLOADDUP_TEST_H

#undef FUN2TEST
#define FUN2TEST ploaddup

void ploaddupTests() {
  printTestTitle(FUN2TEST);

#ifdef __SSE__
  /* float = Packet4f (half) */
  tests4FloatMin2MaxOneArgUnaligned("4 float tests", FUN2TEST);

  /* double =  Packet2d (half) */
  tests2DoubleMin2MaxOneArgUnaligned("2 double tests", FUN2TEST);

  /* int = Packet4i (half) */
  tests4IntMin2MaxOneArgUnaligned("4 int tests", FUN2TEST);

  /* bool = Packet16b */
  tests16BoolMin2MaxOneArgUnaligned("16 bool tests", FUN2TEST);

#endif

#ifdef __AVX__
  /* float = Packet8f (full) */
  tests8FloatMin2MaxOneArgUnaligned("8 float tests", FUN2TEST);

  /* double = Packet4d (full) */
  tests4DoubleMin2MaxOneArgUnaligned("4 double tests", FUN2TEST);

  /* int = Packet8i (full) */
  tests8IntMin2MaxOneArgUnaligned("8 int tests", FUN2TEST);

  /* Eigen::half = Packet8h */
  tests8HalfMin2MaxOneArgUnaligned("8 Eigen::half tests", FUN2TEST);

  /* bfloat16 = Packet8bf */
  tests8Bfloat16Min2MaxOneArgUnaligned("8 bfloat16 tests", FUN2TEST);

#endif

#ifdef __AVX2__
  /* long = Packet4l */
  tests4LongMin2MaxOneArgUnaligned("4 long tests", FUN2TEST);

#endif

#ifdef __AVX512F__
#endif
}

addTest(FUN2TEST)

#endif  // EIGEN_MIPP_PLOADDUP_TEST_H
