#include <float.h>
#include <limits.h>

#ifndef EIGEN_MIPP_PSCATTER_TEST_H
#define EIGEN_MIPP_PSCATTER_TEST_H

#undef FUN2TEST
#define FUN2TEST pscatter

#undef doTest

#define doTest(type, name, eigenType, size, stride, vecData...)                                          \
  {                                                                                                      \
    type vec[size] = {vecData};                                                                          \
    refSingleTypeGenericTest(type, name, type COMMA eigenType, size* size, __attribute__((aligned(32))), \
                             pload<eigenType>(vec), stride);                                             \
  }

void pscatterTests() {
  printTestTitle(FUN2TEST);

#ifdef __SSE__
  // Packet4f (128)
  beginTest("4 float tests");

  doTest(float, FUN2TEST, Packet4f, 4, 1, 6.0f, -3.2f, 28.9f, -64.89f);
  doTest(float, FUN2TEST, Packet4f, 4, 2, 6.0f, 28.9f, 36.0f, 32.02f);
  doTest(float, FUN2TEST, Packet4f, 4, 3, 6.0f, -64.89f, 32.02f, 66.40f);
  doTest(float, FUN2TEST, Packet4f, 4, 4, 6.0f, 36.0f, -27.58f, 9.32f);
  doTest(float, FUN2TEST, Packet4f, 4, 5, 6.0f, -8.0f, -4.6f, 36.37f);

  endTest();

  // Packet2d (128)
  beginTest("2 double tests");

  doTest(double, FUN2TEST, Packet2d, 2, 1, 6.0d, -3.2d);
  doTest(double, FUN2TEST, Packet2d, 2, 2, 6.0d, 36.0d);
  doTest(double, FUN2TEST, Packet2d, 2, 3, 6.0d, -8.0d);

  endTest();

  // Packet4i (128)
  beginTest("4 int tests");

  doTest(int, FUN2TEST, Packet4i, 4, 1, 6, -3, 28, -64);
  doTest(int, FUN2TEST, Packet4i, 4, 2, 6, 28, 36, 32);
  doTest(int, FUN2TEST, Packet4i, 4, 3, 6, -64, 32, 66);
  doTest(int, FUN2TEST, Packet4i, 4, 4, 6, 36, -27, 9);
  doTest(int, FUN2TEST, Packet4i, 4, 5, 6, -8, -4, 36);

  endTest();

  // Packet16b (128)
  beginTest("16 bool tests");

  doTest(bool, FUN2TEST, Packet16b, 16, 1, true, true, false, false, false, true, false, true, false, true, true, false,
         false, true, false, false);
  doTest(bool, FUN2TEST, Packet16b, 16, 2, true, true, false, false, false, true, false, true, false, true, true, false,
         false, true, false, false);
  doTest(bool, FUN2TEST, Packet16b, 16, 3, true, true, false, false, false, true, false, true, false, true, true, false,
         false, true, false, false);
  doTest(bool, FUN2TEST, Packet16b, 16, 4, true, true, false, false, false, true, false, true, false, true, true, false,
         false, true, false, false);
  doTest(bool, FUN2TEST, Packet16b, 16, 5, true, true, false, false, false, true, false, true, false, true, true, false,
         false, true, false, false);
  doTest(bool, FUN2TEST, Packet16b, 16, 6, true, true, false, false, false, true, false, true, false, true, true, false,
         false, true, false, false);
  doTest(bool, FUN2TEST, Packet16b, 16, 7, true, true, false, false, false, true, false, true, false, true, true, false,
         false, true, false, false);
  doTest(bool, FUN2TEST, Packet16b, 16, 8, true, true, false, false, false, true, false, true, false, true, true, false,
         false, true, false, false);
  doTest(bool, FUN2TEST, Packet16b, 16, 9, true, true, false, false, false, true, false, true, false, true, true, false,
         false, true, false, false);
  doTest(bool, FUN2TEST, Packet16b, 16, 10, true, true, false, false, false, true, false, true, false, true, true,
         false, false, true, false, false);
  doTest(bool, FUN2TEST, Packet16b, 16, 11, true, true, false, false, false, true, false, true, false, true, true,
         false, false, true, false, false);
  doTest(bool, FUN2TEST, Packet16b, 16, 12, true, true, false, false, false, true, false, true, false, true, true,
         false, false, true, false, false);
  doTest(bool, FUN2TEST, Packet16b, 16, 13, true, true, false, false, false, true, false, true, false, true, true,
         false, false, true, false, false);
  doTest(bool, FUN2TEST, Packet16b, 16, 14, true, true, false, false, false, true, false, true, false, true, true,
         false, false, true, false, false);
  doTest(bool, FUN2TEST, Packet16b, 16, 15, true, true, false, false, false, true, false, true, false, true, true,
         false, false, true, false, false);
  doTest(bool, FUN2TEST, Packet16b, 16, 16, true, true, false, false, false, true, false, true, false, true, true,
         false, false, true, false, false);
  doTest(bool, FUN2TEST, Packet16b, 16, 17, true, true, false, false, false, true, false, true, false, true, true,
         false, false, true, false, false);

  endTest();

#endif

#ifdef __AVX__
  // Packet8f (256)
  beginTest("8 float tests");

  doTest(float, FUN2TEST, Packet8f, 8, 1, 6.0f, -3.2f, 28.9f, -64.89f, 56.3f, 62.6f, -27.02f, 8.07f);
  doTest(float, FUN2TEST, Packet8f, 8, 2, 6.0f, 28.9f, 56.3f, -27.02f, 36.0f, 32.02f, 89.7f, 56.23f);
  doTest(float, FUN2TEST, Packet8f, 8, 3, 6.0f, -64.89f, -27.02f, -8.0f, 89.7f, 425.543f, -4.6f, 7.4f);
  doTest(float, FUN2TEST, Packet8f, 8, 4, 6.0f, 56.3f, 36.0f, 89.7f, -27.58f, 63.45f, 9.32f, -5.34f);
  doTest(float, FUN2TEST, Packet8f, 8, 5, 6.0f, 62.6f, 32.02f, 425.543f, 63.45f, -3.2f, 62.f, 678.3f);
  doTest(float, FUN2TEST, Packet8f, 8, 6, 6.0f, -27.02f, 89.7f, -4.6f, 9.32f, 62.f, -86.53f, 46.28f);
  doTest(float, FUN2TEST, Packet8f, 8, 7, 6.0f, 8.07f, 56.23f, 7.4f, -5.34f, 678.3f, 46.28f, 9.5f);
  doTest(float, FUN2TEST, Packet8f, 8, 8, 6.0f, 36.0f, -27.58f, 9.32f, 45.3f, -64.32f, -7.6f, 69.56f);
  doTest(float, FUN2TEST, Packet8f, 8, 9, 6.0f, -8.0f, -4.6f, 36.37f, -86.53f, 8.67f, 312.35f, 1.12f);

  endTest();

  // Packet4d (256)
  beginTest("4 double tests");

  doTest(double, FUN2TEST, Packet4d, 4, 1, 6.0d, -3.2d, 28.9d, -64.89d);
  doTest(double, FUN2TEST, Packet4d, 4, 2, 6.0d, 28.9d, 36.0d, 32.02d);
  doTest(double, FUN2TEST, Packet4d, 4, 3, 6.0d, -64.89d, 32.02d, 66.40d);
  doTest(double, FUN2TEST, Packet4d, 4, 4, 6.0d, 36.0d, -27.58d, 9.32d);
  doTest(double, FUN2TEST, Packet4d, 4, 5, 6.0d, -8.0d, -4.6d, 36.37d);

  endTest();

  // Packet8i (256)
  beginTest("8 int tests");

  doTest(int, FUN2TEST, Packet8i, 8, 1, 6, -3, 28, -64, 56, 62, -27, 8);
  doTest(int, FUN2TEST, Packet8i, 8, 2, 6, 28, 56, -27, 36, 32, 89, 56);
  doTest(int, FUN2TEST, Packet8i, 8, 3, 6, -64, -27, -8, 89, 425, -4, 7);
  doTest(int, FUN2TEST, Packet8i, 8, 4, 6, 56, 36, 89, -27, 63, 9, -5);
  doTest(int, FUN2TEST, Packet8i, 8, 5, 6, 62, 32, 425, 63, -3, 62, 678);
  doTest(int, FUN2TEST, Packet8i, 8, 6, 6, -27, 89, -4, 9, 62, -86, 46);
  doTest(int, FUN2TEST, Packet8i, 8, 7, 6, 8, 56, 7, -5, 678, 46, 9);
  doTest(int, FUN2TEST, Packet8i, 8, 8, 6, 36, -27, 9, 45, -64, -7, 69);
  doTest(int, FUN2TEST, Packet8i, 8, 9, 6, -8, -4, 36, -86, 8, 312, 1);

  endTest();

  // Packet8h (128)
  beginTest("8 Eigen::half tests");

  doTest(Eigen::half, FUN2TEST, Packet8h, 8, 1, half(6.0f), half(-3.2f), half(28.9f), half(-64.89f), half(56.3f),
         half(62.6f), half(-27.02f), half(8.07f));
  doTest(Eigen::half, FUN2TEST, Packet8h, 8, 2, half(6.0f), half(28.9f), half(56.3f), half(-27.02f), half(36.0f),
         half(32.02f), half(89.7f), half(56.23f));
  doTest(Eigen::half, FUN2TEST, Packet8h, 8, 3, half(6.0f), half(-64.89f), half(-27.02f), half(-8.0f), half(89.7f),
         half(425.543f), half(-4.6f), half(7.4f));
  doTest(Eigen::half, FUN2TEST, Packet8h, 8, 4, half(6.0f), half(56.3f), half(36.0f), half(89.7f), half(-27.58f),
         half(63.45f), half(9.32f), half(-5.34f));
  doTest(Eigen::half, FUN2TEST, Packet8h, 8, 5, half(6.0f), half(62.6f), half(32.02f), half(425.543f), half(63.45f),
         half(-3.2f), half(62.f), half(678.3f));
  doTest(Eigen::half, FUN2TEST, Packet8h, 8, 6, half(6.0f), half(-27.02f), half(89.7f), half(-4.6f), half(9.32f),
         half(62.f), half(-86.53f), half(46.28f));
  doTest(Eigen::half, FUN2TEST, Packet8h, 8, 7, half(6.0f), half(8.07f), half(56.23f), half(7.4f), half(-5.34f),
         half(678.3f), half(46.28f), half(9.5f));
  doTest(Eigen::half, FUN2TEST, Packet8h, 8, 8, half(6.0f), half(36.0f), half(-27.58f), half(9.32f), half(45.3f),
         half(-64.32f), half(-7.6f), half(69.56f));
  doTest(Eigen::half, FUN2TEST, Packet8h, 8, 9, half(6.0f), half(-8.0f), half(-4.6f), half(36.37f), half(-86.53f),
         half(8.67f), half(312.35f), half(1.12f));

  endTest();

  // Packet8bf (128) bfloat16
  beginTest("8 bfloat16 tests");

  doTest(bfloat16, FUN2TEST, Packet8bf, 8, 1, bfloat16(6.0f), bfloat16(-3.2f), bfloat16(28.9f), bfloat16(-64.89f),
         bfloat16(56.3f), bfloat16(62.6f), bfloat16(-27.02f), bfloat16(8.07f));
  doTest(bfloat16, FUN2TEST, Packet8bf, 8, 2, bfloat16(6.0f), bfloat16(28.9f), bfloat16(56.3f), bfloat16(-27.02f),
         bfloat16(36.0f), bfloat16(32.02f), bfloat16(89.7f), bfloat16(56.23f));
  doTest(bfloat16, FUN2TEST, Packet8bf, 8, 3, bfloat16(6.0f), bfloat16(-64.89f), bfloat16(-27.02f), bfloat16(-8.0f),
         bfloat16(89.7f), bfloat16(425.543f), bfloat16(-4.6f), bfloat16(7.4f));
  doTest(bfloat16, FUN2TEST, Packet8bf, 8, 4, bfloat16(6.0f), bfloat16(56.3f), bfloat16(36.0f), bfloat16(89.7f),
         bfloat16(-27.58f), bfloat16(63.45f), bfloat16(9.32f), bfloat16(-5.34f));
  doTest(bfloat16, FUN2TEST, Packet8bf, 8, 5, bfloat16(6.0f), bfloat16(62.6f), bfloat16(32.02f), bfloat16(425.543f),
         bfloat16(63.45f), bfloat16(-3.2f), bfloat16(62.f), bfloat16(678.3f));
  doTest(bfloat16, FUN2TEST, Packet8bf, 8, 6, bfloat16(6.0f), bfloat16(-27.02f), bfloat16(89.7f), bfloat16(-4.6f),
         bfloat16(9.32f), bfloat16(62.f), bfloat16(-86.53f), bfloat16(46.28f));
  doTest(bfloat16, FUN2TEST, Packet8bf, 8, 7, bfloat16(6.0f), bfloat16(8.07f), bfloat16(56.23f), bfloat16(7.4f),
         bfloat16(-5.34f), bfloat16(678.3f), bfloat16(46.28f), bfloat16(9.5f));
  doTest(bfloat16, FUN2TEST, Packet8bf, 8, 8, bfloat16(6.0f), bfloat16(36.0f), bfloat16(-27.58f), bfloat16(9.32f),
         bfloat16(45.3f), bfloat16(-64.32f), bfloat16(-7.6f), bfloat16(69.56f));
  doTest(bfloat16, FUN2TEST, Packet8bf, 8, 9, bfloat16(6.0f), bfloat16(-8.0f), bfloat16(-4.6f), bfloat16(36.37f),
         bfloat16(-86.53f), bfloat16(8.67f), bfloat16(312.35f), bfloat16(1.12f));

  endTest();

#endif

#ifdef __AVX2__
  // Packet4l (256)
  beginTest("4 long tests");

  doTest(long, FUN2TEST, Packet4l, 4, 1, 6L, -3L, 28L, -64L);
  doTest(long, FUN2TEST, Packet4l, 4, 2, 6L, 28L, 36L, 32L);
  doTest(long, FUN2TEST, Packet4l, 4, 3, 6L, -64L, 32L, 66L);
  doTest(long, FUN2TEST, Packet4l, 4, 4, 6L, 36L, -27L, 9L);
  doTest(long, FUN2TEST, Packet4l, 4, 5, 6L, -8L, -4L, 36L);

  endTest();

#endif

#ifdef __AVX512F__
#endif
}

addTest(FUN2TEST)

#endif  // EIGEN_MIPP_PSCATTER_TEST_H
