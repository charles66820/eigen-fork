#include <float.h>
#include <limits.h>

#ifndef EIGEN_MIPP_PZERO_TEST_H
#define EIGEN_MIPP_PZERO_TEST_H

#undef FUN2TEST
#define FUN2TEST pzero

void pzeroTests() {
  printTestTitle(FUN2TEST);

#ifdef __SSE__
  /* float = Packet4f (half) */
  beginTest("4 float tests");

  Packet4f bh;
  vectorHalfFloatTest(FUN2TEST, Packet4f, bh);

  endTest();

  /* double = Packet2d (half) */
  beginTest("2 double tests");

  Packet2d ch;
  vectorHalfDoubleTest(FUN2TEST, Packet2d, ch);

  endTest();

  /* int = Packet4i (half) */
  beginTest("4 int tests");

  Packet4i dh;
  vectorHalfIntTest(FUN2TEST, Packet4i, dh);

  endTest();

#endif

#ifdef __AVX__
  /* float = Packet8f (full) */
  beginTest("8 float tests");

  Packet8f b;
  vectorFullFloatTest(FUN2TEST, Packet8f, b);

  endTest();

  /* double = Packet4d (full) */
  beginTest("4 double tests");

  Packet4d c;
  vectorFullDoubleTest(FUN2TEST, Packet4d, c);

  endTest();

  /* int = Packet8i (full) */
  beginTest("8 int tests");

  Packet8i d;
  vectorFullIntTest(FUN2TEST, Packet8i, d);

  endTest();

#endif

#ifdef __AVX2__
  /* long = Packet4l */
  beginTest("4 long tests");

  Packet4l a;
  vectorFullLongTest(FUN2TEST, Packet4l, a);

  endTest();

#endif

#ifdef __AVX512F__
  // /* float = Packet16f (full) */
  // beginTest("16 float tests");

  // Packet8f b;
  // vectorFullFloatTest(FUN2TEST, Packet8f, b);

  // endTest();

  // /* double = Packet8d (full) */
  // beginTest("8 double tests");

  // Packet4d c;
  // vectorFullDoubleTest(FUN2TEST, Packet4d, c);

  // endTest();

  // /* int = Packet16i (full) */
  // beginTest("16 int tests");

  // Packet8i d;
  // vectorFullIntTest(FUN2TEST, Packet8i, d);

  // endTest();

#endif
}

addTest(FUN2TEST)

#endif  // EIGEN_MIPP_PZERO_TEST_H
