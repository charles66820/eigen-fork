#include <float.h>
#include <limits.h>

#ifndef EIGEN_MIPP_PREDUX_HALF_DOWTO4_TEST_H
#define EIGEN_MIPP_PREDUX_HALF_DOWTO4_TEST_H

#undef FUN2TEST
#define FUN2TEST predux_half_dowto4

void predux_half_dowto4Tests() {
  printTestTitle(FUN2TEST);

#ifdef __SSE__
#endif

#ifdef __AVX__
  // Packet8f (256) -> Packet4f (128)
  beginTest("full2half float tests");
  {
    MIN2MAX_FLOAT_VECTOR_LOADED(8);

    vector128FloatTest(FUN2TEST, Packet8f, vmax);
    vector128FloatTest(FUN2TEST, Packet8f, v36);
    vector128FloatTest(FUN2TEST, Packet8f, v0);
    vector128FloatTest(FUN2TEST, Packet8f, v_240);
    vector128FloatTest(FUN2TEST, Packet8f, vmin);
  }
  endTest();

  // Packet8i (256) -> Packet4i (128)
  beginTest("full2half int tests");
  {
    MIN2MAX_INT_VECTOR_LOADED(8);

    vector128IntTest(FUN2TEST, Packet8i, vmax);
    vector128IntTest(FUN2TEST, Packet8i, v36);
    vector128IntTest(FUN2TEST, Packet8i, v0);
    vector128IntTest(FUN2TEST, Packet8i, v_240);
    vector128IntTest(FUN2TEST, Packet8i, vmin);
  }
  endTest();

#endif

#ifdef __AVX2__
#endif

#ifdef __AVX512F__
#endif
}

addTest(FUN2TEST)

#endif  // EIGEN_MIPP_PREDUX_HALF_DOWTO4_TEST_H
