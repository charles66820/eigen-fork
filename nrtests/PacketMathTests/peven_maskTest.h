#include <float.h>
#include <limits.h>

#ifndef EIGEN_MIPP_PEVEN_MASK_TEST_H
#define EIGEN_MIPP_PEVEN_MASK_TEST_H

#undef FUN2TEST
#define FUN2TEST peven_mask

void peven_maskTests() {
  std::cout << printTestTitle(FUN2TEST) << std::endl;

#ifdef __SSE__
  /* float = Packet4f (half) */
  beginTest("4 float tests");

  Packet4f bh;
  vectorHalfFloatTest(FUN2TEST, bh);

  endTest();

  /* double = Packet2d (half) */
  beginTest("2 double tests");

  Packet2d ch;
  vectorHalfDoubleTest(FUN2TEST, ch);

  endTest();

  /* int = Packet4i (half) */
  beginTest("4 int tests");

  Packet4i dh;
  vectorHalfIntTest(FUN2TEST, dh);

  endTest();

#endif

#ifdef __AVX__
  /* float = Packet8f (full) */
  beginTest("8 float tests");

  Packet8f b;
  vectorFullFloatTest(FUN2TEST, b);

  endTest();

  /* double = Packet4d (full) */
  beginTest("4 double tests");

  Packet4d c;
  vectorFullDoubleTest(FUN2TEST, c);

  endTest();

  /* int = Packet8i (full) */
  beginTest("8 int tests");

  Packet8i d;
  vectorFullIntTest(FUN2TEST, d);

  endTest();

#endif

#ifdef __AVX2__
  /* long = Packet4l */
  beginTest("4 long tests");

  Packet4l a;
  vectorFullLongTest(FUN2TEST, a);

  endTest();

#endif

#ifdef __AVX512F__
#endif
}

addTest(FUN2TEST)

#endif  // EIGEN_MIPP_PEVEN_MASK_TEST_H
