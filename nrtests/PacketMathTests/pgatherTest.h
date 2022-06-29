#include <float.h>
#include <limits.h>


#ifndef EIGEN_MIPP_PGATHER_TEST_H
#define EIGEN_MIPP_PGATHER_TEST_H

#undef FUN2TEST
#define FUN2TEST pgather

#define mvTest(MIPP_Reg, typeMipp, cast, type, eigenType, name, args...)                             \
  {                                                                                                  \
    mipp::MIPP_Reg<typeMipp> rVar = cast(name<type, eigenType>(args));                                \
    mipp::MIPP_Reg<typeMipp> rVar_old = cast(name##_old<type, eigenType>(args));                      \
    hasFailed |= printWhenRegDiff(#name "<" #eigenType ">(" + to_sting(args) + ")", rVar, rVar_old); \
  }

#define mvTestUnarg(MIPP_Reg, typeMipp, cast, type, eigenType, name, args...) \
  mvTest(MIPP_Reg, typeMipp, cast, type, eigenType, name, args)
#define doTest(MIPP_Reg, typeMipp, cast, type, eigenType, args...) \
  mvTestUnarg(MIPP_Reg, typeMipp, cast, type, eigenType, FUN2TEST, args)

void pgatherTests() {
  printTestTitle(FUN2TEST);

#ifdef __SSE__
  /* float = Packet4f (half) */
  beginTest("4 float tests");

  float fv4x4[4 * 4] = {
      // 4f matrix
      6.0f,    -3.2f,  28.9f,  -64.89f,  // row1
      36.0f,   -8.0f,  32.02f, 1.2f,     // row2
      -27.58f, 66.40f, -4.6f,  24.18f,   // row3
      9.32f,   -3.2f,  8.6f,   36.37f    // row4
  };

  for (size_t i = 1; i <= 4 + 1; i++) {
    doTest(Reg_2, float, FLOAT_CAST_TO_MIPP_HALF, float, Packet4f, (const float*)&fv4x4, i);
  }

  endTest();

  /* double =  Packet2d (half) */
  beginTest("2 double tests");

  double dv2x2[2 * 2] = {
      // 2d matrix
      6.0d, -3.2d,  // row1
      36.0d, -8.0d  // row2
  };

  for (size_t i = 1; i <= 2 + 1; i++) {
    doTest(Reg_2, double, DOUBLE_CAST_TO_MIPP_HALF, double, Packet2d, (const double*)&dv2x2, i);
  }

  endTest();

  /* int = Packet4i (half) */
  beginTest("4 int tests");

  int iv4x4[4 * 4] = {
      // 4i matrix
      6,   -3, 28, -64,  // row1
      36,  -8, 32, 1,    // row2
      -27, 66, -4, 24,   // row3
      9,   -3, 8,  36    // row4
  };

  for (size_t i = 1; i <= 4 + 1; i++) {
    doTest(Reg_2, int, INT_CAST_TO_MIPP_HALF, int, Packet4i, (const int*)&iv4x4, i);
  }

  endTest();

  /* bool = Packet16b */
  beginTest("16 bool tests");

  bool bv16x16[16 * 16] = {
      // 16b matrix
      true,  true,  false, false, false, true,  false, true,  false, true,  true,  false, false, true,  false,
      false,  // row1
      true,  true,  true,  true,  false, false, true,  false, false, true,  true,  false, true,  false, true,
      false,  // row2
      false, false, false, true,  false, true,  false, true,  true,  false, true,  true,  false, true,  false,
      false,  // row3
      true,  true,  false, false, false, false, false, true,  false, false, false, false, true,  true,  false,
      false,  // row4
      true,  true,  false, false, false, true,  false, true,  false, true,  true,  false, false, true,  true,
      false,  // row5
      false, true,  false, false, false, false, true,  true,  true,  true,  true,  true,  false, false, false,
      false,  // row6
      true,  true,  false, true,  false, true,  true,  false, true,  false, false, false, true,  false, true,
      true,  // row7
      false, true,  false, false, false, true,  true,  true,  true,  true,  false, true,  false, true,  false,
      false,  // row8
      true,  true,  false, false, true,  true,  true,  true,  true,  true,  true,  false, false, true,  false,
      false,  // row9
      true,  false, false, true,  true,  true,  false, false, true,  true,  true,  false, false, true,  false,
      false,  // row10
      false, true,  true,  true,  true,  false, true,  true,  false, false, false, false, true,  true,  true,
      false,  // row11
      false, true,  false, false, false, false, false, false, true,  false, true,  true,  true,  false, false,
      false,  // row12
      true,  true,  false, false, false, true,  false, false, false, true,  true,  false, false, true,  false,
      false,  // row13
      false, false, false, false, true,  true,  false, true,  false, true,  true,  false, false, false, false,
      false,  // row14
      true,  true,  false, true,  false, true,  false, true,  true,  false, true,  true,  false, true,  true,
      false,  // row15
      true,  true,  false, true,  false, false, false, true,  false, true,  false, false, false, true,  false,
      true  // row16
  };

  for (size_t i = 1; i <= 16 + 1; i++) {
    doTest(Reg_2, int8_t, INT_CAST_TO_MIPP_HALF, bool, Packet16b, (const bool*)&bv16x16, i);
  }

  endTest();

#endif

#ifdef __AVX__
  /* float = Packet8f (full) */
  beginTest("8 float tests");

  float fv8x8[8 * 8] = {
      // 8f matrix
      6.0f,    -3.2f,  28.9f,   -64.89f,  56.3f,   62.6f,    -27.02f, 8.07f,     // row1
      36.0f,   -8.0f,  32.02f,  1.2f,     89.7f,   -103.04f, 56.23f,  425.543f,  // row2
      -27.58f, 66.40f, -4.6f,   24.18f,   63.45f,  7.4f,     -35.43f, -9.87f,    // row3
      9.32f,   -3.2f,  8.6f,    36.37f,   -5.34f,  65.67f,   62.f,    43.98f,    // row4
      45.3f,   67.85f, 97.5f,   678.3f,   -86.53f, 53.12f,   -82.15f, 49.8f,     // row5
      -64.32f, -66.4f, 46.28f,  675.265f, -86.7f,  8.67f,    -94.3f,  -24.57f,   // row6
      -7.6f,   9.5f,   -67.2f,  -65.26f,  654.7f,  -31.25f,  312.35f, 98.2f,     // row7
      69.56f,  8.97f,  -65.72f, 554.1f,   25.4f,   32.13f,   -55.64f, 1.12f      // row8
  };

  for (size_t i = 1; i <= 8 + 1; i++) {
    doTest(Reg, float, FLOAT_CAST_TO_MIPP_FULL, float, Packet8f, (const float*)&fv8x8, i);
  }

  endTest();

  /* double = Packet4d (full) */
  beginTest("4 double tests");

  double dv4x4[4 * 4] = {
      // 4d matrix
      6.0d,    -3.2d,  28.9d,  -64.89d,  // row1
      36.0d,   -8.0d,  32.02d, 1.2d,     // row2
      -27.58d, 66.40d, -4.6d,  24.18d,   // row3
      9.32d,   -3.2d,  8.6d,   36.37d    // row4
  };

  for (size_t i = 1; i <= 4 + 1; i++) {
    doTest(Reg, double, DOUBLE_CAST_TO_MIPP_FULL, double, Packet4d, (const double*)&dv4x4, i);
  }

  endTest();

  /* int = Packet8i (full) */
  beginTest("8 int tests");

  int iv8x8[8 * 8] = {
      // 8i matrix
      6,   -3,  28,  -64, 56,  62,   -27, 8,    // row1
      36,  -8,  32,  1,   89,  -103, 56,  425,  // row2
      -27, 66,  -4,  24,  63,  7,    -35, -9,   // row3
      9,   -3,  8,   36,  -5,  65,   62,  43,   // row4
      45,  67,  97,  678, -86, 53,   -82, 49,   // row5
      -64, -66, 46,  675, -86, 8,    -94, -24,  // row6
      -7,  9,   -67, -65, 654, -31,  312, 98,   // row7
      69,  8,   -65, 554, 25,  32,   -55, 1     // row8
  };

  for (size_t i = 1; i <= 8 + 1; i++) {
    doTest(Reg, int, INT_CAST_TO_MIPP_FULL, int, Packet8i, (const int*)&iv8x8, i);
  }

  endTest();

  /* Eigen::half = Packet8h */
  beginTest("8 Eigen::half tests");

  Eigen::half hv8x8[8 * 8] = {
      // 8h matrix
      half(6.0f),    half(-3.2f),    half(28.9f),   half(-64.89f),
      half(56.3f),   half(62.6f),    half(-27.02f), half(8.07f),  // row1
      half(36.0f),   half(-8.0f),    half(32.02f),  half(1.2f),
      half(89.7f),   half(-103.04f), half(56.23f),  half(425.543f),  // row2
      half(-27.58f), half(66.40f),   half(-4.6f),   half(24.18f),
      half(63.45f),  half(7.4f),     half(-35.43f), half(-9.87f),  // row3
      half(9.32f),   half(-3.2f),    half(8.6f),    half(36.37f),
      half(-5.34f),  half(65.67f),   half(62.f),    half(43.98f),  // row4
      half(45.3f),   half(67.85f),   half(97.5f),   half(678.3f),
      half(-86.53f), half(53.12f),   half(-82.15f), half(49.8f),  // row5
      half(-64.32f), half(-66.4f),   half(46.28f),  half(675.265f),
      half(-86.7f),  half(8.67f),    half(-94.3f),  half(-24.57f),  // row6
      half(-7.6f),   half(9.5f),     half(-67.2f),  half(-65.26f),
      half(654.7f),  half(-31.25f),  half(312.35f), half(98.2f),  // row7
      half(69.56f),  half(8.97f),    half(-65.72f), half(554.1f),
      half(25.4f),   half(32.13f),   half(-55.64f), half(1.12f)  // row8
  };

  for (size_t i = 1; i <= 8 + 1; i++) {
    doTest(Reg_2, short, INT_CAST_TO_MIPP_HALF, Eigen::half, Packet8h, (const Eigen::half*)&hv8x8, i);
  }

  endTest();

  /* bfloat16 = Packet8bf */
  beginTest("8 bfloat16 tests");

  bfloat16 bfv8x8[8 * 8] = {
      // 8bf matrix
      bfloat16(6.0f),    bfloat16(-3.2f),    bfloat16(28.9f),   bfloat16(-64.89f),
      bfloat16(56.3f),   bfloat16(62.6f),    bfloat16(-27.02f), bfloat16(8.07f),  // row1
      bfloat16(36.0f),   bfloat16(-8.0f),    bfloat16(32.02f),  bfloat16(1.2f),
      bfloat16(89.7f),   bfloat16(-103.04f), bfloat16(56.23f),  bfloat16(425.543f),  // row2
      bfloat16(-27.58f), bfloat16(66.40f),   bfloat16(-4.6f),   bfloat16(24.18f),
      bfloat16(63.45f),  bfloat16(7.4f),     bfloat16(-35.43f), bfloat16(-9.87f),  // row3
      bfloat16(9.32f),   bfloat16(-3.2f),    bfloat16(8.6f),    bfloat16(36.37f),
      bfloat16(-5.34f),  bfloat16(65.67f),   bfloat16(62.f),    bfloat16(43.98f),  // row4
      bfloat16(45.3f),   bfloat16(67.85f),   bfloat16(97.5f),   bfloat16(678.3f),
      bfloat16(-86.53f), bfloat16(53.12f),   bfloat16(-82.15f), bfloat16(49.8f),  // row5
      bfloat16(-64.32f), bfloat16(-66.4f),   bfloat16(46.28f),  bfloat16(675.265f),
      bfloat16(-86.7f),  bfloat16(8.67f),    bfloat16(-94.3f),  bfloat16(-24.57f),  // row6
      bfloat16(-7.6f),   bfloat16(9.5f),     bfloat16(-67.2f),  bfloat16(-65.26f),
      bfloat16(654.7f),  bfloat16(-31.25f),  bfloat16(312.35f), bfloat16(98.2f),  // row7
      bfloat16(69.56f),  bfloat16(8.97f),    bfloat16(-65.72f), bfloat16(554.1f),
      bfloat16(25.4f),   bfloat16(32.13f),   bfloat16(-55.64f), bfloat16(1.12f)  // row8
  };

  for (size_t i = 1; i <= 8 + 1; i++) {
    doTest(Reg_2, short, INT_CAST_TO_MIPP_HALF, bfloat16, Packet8bf, (const bfloat16*)&bfv8x8, i);
  }

  endTest();

#endif

#ifdef __AVX2__
  /* long = Packet4l */
  beginTest("4 long tests");

  long lv4x4[4 * 4] = {
      // 4i matrix
      6L,   -3L, 28L, -64L,  // row1
      36L,  -8L, 32L, 1L,    // row2
      -27L, 66L, -4L, 24L,   // row3
      9L,   -3L, 8L,  36L    // row4
  };

  for (size_t i = 1; i <= 4 + 1; i++) {
    doTest(Reg, long, INT_CAST_TO_MIPP_FULL, long, Packet4l, (const long*)&lv4x4, i);
  }

  endTest();

#endif

#ifdef __AVX512F__
#endif
}

addTest(FUN2TEST)

#endif  // EIGEN_MIPP_PGATHER_TEST_H
