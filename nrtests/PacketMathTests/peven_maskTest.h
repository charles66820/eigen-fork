#include <float.h>
#include <limits.h>

#ifndef EIGEN_MIPP_PEVEN_MASK_TEST_H
#define EIGEN_MIPP_PEVEN_MASK_TEST_H

#undef FUN2TEST
#define FUN2TEST peven_mask

void peven_maskTests() {
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
#endif
}

addTest(FUN2TEST)

#endif  // EIGEN_MIPP_PEVEN_MASK_TEST_H
