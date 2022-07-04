#include <float.h>
#include <limits.h>

#ifndef EIGEN_MIPP_PSTORE_TEST_H
#define EIGEN_MIPP_PSTORE_TEST_H

#undef FUN2TEST
#define FUN2TEST pstore

void pstoreTests() {
  printTestTitle(FUN2TEST);

#ifdef __SSE__
  // Packet4f (128)
  beginTest("4 float tests");
  {
    MIN2MAX_FLOAT_VECTOR_LOADED(4);

    min2MaxTests(refSingleType, FUN2TEST, float COMMA 4, vmax, v36, v0, v_240, vmin);
  }
  endTest();

  // Packet2d (128)
  beginTest("2 double tests");
  {
    MIN2MAX_DOUBLE_VECTOR_LOADED(2);

    min2MaxTests(refSingleType, FUN2TEST, double COMMA 2, vmax, v36, v0, v_240, vmin);
  }
  endTest();

  // Packet4i (128)
  beginTest("4 int tests");
  {
    MIN2MAX_INT_VECTOR_LOADED(4);

    min2MaxTests(refSingleType, FUN2TEST, int COMMA 4, vmax, v36, v0, v_240, vmin);
  }
  endTest();

  // Packet16b (128)
  beginTest("16 bool tests");
  {
    BOOL_VECTOR_LOADED(16);

    boolTests(refSingleType, FUN2TEST, bool COMMA 16, vtrue, vfalse);
  }
  endTest();

#endif

#ifdef __AVX__
  // Packet8f (256)
  beginTest("8 float tests");
  {
    MIN2MAX_FLOAT_VECTOR_LOADED(8);

    min2MaxTests(refSingleType, FUN2TEST, float COMMA 8, vmax, v36, v0, v_240, vmin);
  }
  endTest();

  // Packet4d (256)
  beginTest("4 double tests");
  {
    MIN2MAX_DOUBLE_VECTOR_LOADED(4);

    min2MaxTests(refSingleType, FUN2TEST, double COMMA 4, vmax, v36, v0, v_240, vmin);
  }
  endTest();

  // Packet8i (256)
  beginTest("8 int tests");
  {
    MIN2MAX_INT_VECTOR_LOADED(8);

    min2MaxTests(refSingleType, FUN2TEST, int COMMA 8, vmax, v36, v0, v_240, vmin);
  }
  endTest();

  // Packet8h (128)
  beginTest("8 Eigen::half tests");
  {
    MIN2MAX_HALF_VECTOR_LOADED(8);

    min2MaxTests(refSingleType, FUN2TEST, Eigen::half COMMA 8, vmax, v36, v0, v_240, vmin);
  }
  endTest();

  // Packet8bf (128) bfloat16
  beginTest("8 bfloat16 tests");
  {
    MIN2MAX_BFLOAT16_VECTOR_LOADED(8);

    min2MaxTests(refSingleType, FUN2TEST, bfloat16 COMMA 8, vmax, v36, v0, v_240, vmin);
  }
  endTest();

#endif

#ifdef __AVX2__
  // Packet4l (256)
  beginTest("4 long tests");
  {
    MIN2MAX_LONG_VECTOR_LOADED(4);

    min2MaxTests(refSingleType, FUN2TEST, long COMMA 4, vmax, v36, v0, v_240, vmin);
  }
  endTest();

#endif

#ifdef __AVX512F__
#endif
}

addTest(FUN2TEST)

#endif  // EIGEN_MIPP_PSTORE_TEST_H
