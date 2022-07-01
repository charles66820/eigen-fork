#include <float.h>
#include <limits.h>

#ifndef EIGEN_MIPP_PZERO_TEST_H
#define EIGEN_MIPP_PZERO_TEST_H

#undef FUN2TEST
#define FUN2TEST pzero

void pzeroTests() {
  printTestTitle(FUN2TEST);

#ifdef __SSE__
  // Packet4f (128)
  beginTest("4 float tests");

  Packet4f bh;
  vector128FloatTest(FUN2TEST, Packet4f, bh);

  endTest();

  /* double = Packet2d (half) */
  beginTest("2 double tests");

  Packet2d ch;
  vector128DoubleTest(FUN2TEST, Packet2d, ch);

  endTest();

  // Packet4i (128)
  beginTest("4 int tests");

  Packet4i dh;
  vector128IntTest(FUN2TEST, Packet4i, dh);

  endTest();

#endif

#ifdef __AVX__
  // Packet8f (256)
  beginTest("8 float tests");

  Packet8f b;
  vector256FloatTest(FUN2TEST, Packet8f, b);

  endTest();

  // Packet4d (256)
  beginTest("4 double tests");

  Packet4d c;
  vector256DoubleTest(FUN2TEST, Packet4d, c);

  endTest();

  // Packet8i (256)
  beginTest("8 int tests");

  Packet8i d;
  vector256IntTest(FUN2TEST, Packet8i, d);

  endTest();

#endif

#ifdef __AVX2__
  // Packet4l (256)
  beginTest("4 long tests");

  Packet4l a;
  vector256LongTest(FUN2TEST, Packet4l, a);

  endTest();

#endif

#ifdef __AVX512F__
  // //Packet16f (512)
  // beginTest("16 float tests");

  // Packet16f fb;
  // vector512FloatTest(FUN2TEST, Packet16f, fb);

  // endTest();

  // //Packet8d (512)
  // beginTest("8 double tests");

  // Packet8d fd;
  // vector512DoubleTest(FUN2TEST, Packet8d, fd);

  // endTest();

  // /* int = Packet16i (512) */
  // beginTest("16 int tests");

  // Packet16i fi;
  // vector256IntTest(FUN2TEST, Packet16i, fi);

  // endTest();

#endif
}

addTest(FUN2TEST)

#endif  // EIGEN_MIPP_PZERO_TEST_H
