#include <float.h>
#include <limits.h>

#ifndef EIGEN_MIPP_PTRANSPOSE_TEST_H
#define EIGEN_MIPP_PTRANSPOSE_TEST_H

#undef FUN2TEST
#define FUN2TEST ptranspose

#define vectorMatTest_imp(type, cast, name, eigenType, N, tab)                                                \
  {                                                                                                           \
    try {                                                                                                     \
      MAT(eigenType, N, matC, tab);                                                                           \
      MAT(eigenType, N, matC_old, tab);                                                                       \
                                                                                                              \
      std::stringstream matStr;                                                                               \
      matStr << std::endl;                                                                                    \
      for (size_t i = 0; i < N; i++) {                                                                        \
        matStr << mipp::Reg<type>(cast(matC.packet[i])) << std::endl;                                         \
      }                                                                                                       \
                                                                                                              \
      name(matC);                                                                                             \
      name##_old(matC_old);                                                                                   \
                                                                                                              \
      std::stringstream matRStr;                                                                              \
      std::stringstream matRStr_old;                                                                          \
      matRStr << std::endl;                                                                                   \
      matRStr_old << std::endl;                                                                               \
                                                                                                              \
      bool isEqual = false;                                                                                   \
      for (size_t i = 0; i < N; i++) {                                                                        \
        mipp::Reg<type> rMatR = cast(matC.packet[i]);                                                         \
        mipp::Reg<type> rMatR_old = cast(matC_old.packet[i]);                                                 \
                                                                                                              \
        matRStr << rMatR << std::endl;                                                                        \
        matRStr_old << rMatR_old << std::endl;                                                                \
                                                                                                              \
        isEqual |= !bitwiseEq(rMatR, rMatR_old);                                                              \
      }                                                                                                       \
                                                                                                              \
      hasFailed |= printWhenDiff(!isEqual, #name "(" + matStr.str() + ")", matRStr.str(), matRStr_old.str()); \
    } catch (const std::exception& e) {                                                                       \
      std::cerr << e.what() << std::endl;                                                                     \
      std::cout << " failed" << std::endl;                                                                    \
    }                                                                                                         \
  }

#define vectorMatTest(type, cast, name, eigenType, args...) vectorMatTest_imp(type, cast, name, eigenType, args)

#define MAT(eigenType, N, name, tab) \
  PacketBlock<eigenType, N> name;    \
  for (size_t i = 0; i < N; i++) name.packet[i] = pload<eigenType>(tab + i * unpacket_traits<eigenType>::size);

void ptransposeTests() {
  printTestTitle(FUN2TEST);

#ifdef __SSE__
  // Packet4f (128)
  beginTest("4 float 4⨉4 mat tests");
  {
    float tab1[4 * 4] = {14.02f, 38.8f,  42.14f, 3.33f,   //
                         6.3f,   54.25f, 62.6f,  92.04f,  //
                         99.0f,  78.7f,  89.3f,  56.32f,  //
                         5.5f,   8.42f,  94.0f,  46.9f};

    vectorMatTest(float, FLOAT_CAST_128_TO_MIPP_REG_T, FUN2TEST, Packet4f, 4, tab1);
  }
  endTest();

  // Packet2d (128)
  beginTest("2 double 2⨉2 mat tests");
  {
    double tab1[2 * 2] = {14.02d, 38.8d,  //
                          6.3d, 54.25d};

    vectorMatTest(double, DOUBLE_CAST_128_TO_MIPP_REG_T, FUN2TEST, Packet2d, 2, tab1);
  }
  endTest();

  // Packet4i (128)
  beginTest("4 int 4⨉4 mat tests");
  {
    int tab1[4 * 4] = {14, 38, 42, 3,   //
                       6,  54, 62, 92,  //
                       99, 78, 89, 56,  //
                       5,  8,  94, 46};

    vectorMatTest(int, INT_CAST_128_TO_MIPP_REG_T, FUN2TEST, Packet4i, 4, tab1);
  }
  endTest();

  // Packet16b (128)
  beginTest("16 bool 4⨉16 mat tests");
  {
    bool tab1[4 * 16] = {true,  false, false, false, false, false, false, false,
                         false, false, false, false, false, false, false, false,  //
                         true,  false, false, false, false, false, false, false,
                         false, false, false, false, false, false, false, false,  //
                         false, false, false, false, false, false, false, false,
                         false, false, false, false, false, false, false, false,  //
                         false, false, false, false, false, false, false, false,
                         false, false, false, false, false, false, false, false};

    vectorMatTest(int8_t, INT_CAST_128_TO_MIPP_REG_T, FUN2TEST, Packet16b, 4, tab1);
  }
  endTest();

  beginTest("16 bool 16⨉16 mat tests");
  {
    bool tab1[16 * 16] = {true,  true,  false, true,  false, false, false, false,
                          false, false, false, false, false, false, false, true,  //
                          false, true,  true,  true,  false, false, false, false,
                          false, false, false, false, false, false, false, false,  //
                          false, false, false, false, false, false, false, false,
                          false, false, false, false, false, false, false, false,  //
                          false, true,  true,  true,  false, false, false, false,
                          false, false, false, false, false, false, false, false,  //
                          false, false, false, false, false, false, false, false,
                          false, false, false, false, false, false, false, false,  //
                          false, false, false, false, false, false, false, false,
                          false, false, false, false, false, false, false, false,  //
                          false, false, false, false, false, false, false, false,
                          false, false, false, false, false, false, false, false,  //
                          false, false, false, false, false, false, false, false,
                          false, false, false, false, false, false, false, false,  //
                          false, false, false, false, false, false, false, false,
                          false, false, false, false, false, false, false, false,  //
                          false, false, false, false, false, false, false, false,
                          false, false, false, false, false, false, false, false,  //
                          false, false, false, false, false, false, false, false,
                          false, false, false, false, false, false, false, false,  //
                          false, false, false, false, false, false, false, false,
                          false, false, false, false, false, false, false, false,  //
                          false, false, false, false, false, false, false, false,
                          false, false, false, false, false, false, false, false,  //
                          false, false, false, false, false, false, false, false,
                          false, false, false, false, false, false, false, true,  //
                          false, false, false, false, false, false, false, false,
                          false, false, false, false, false, false, false, false,  //
                          false, false, false, false, false, false, false, false,
                          false, false, false, false, false, false, true,  false};

    vectorMatTest(int8_t, INT_CAST_128_TO_MIPP_REG_T, FUN2TEST, Packet16b, 16, tab1);
  }
  endTest();

#endif

#ifdef __AVX__
  // Packet8f (256)
  beginTest("8 float 8⨉8 mat tests");
  {
    float tab1[8 * 8] = {14.02f, 38.8f,  42.14f, 3.33f,  0.0f, 0.0f, 0.0f, 2.0f,  //
                         6.3f,   54.25f, 62.6f,  92.04f, 0.0f, 0.0f, 0.0f, 0.0f,  //
                         99.0f,  78.7f,  89.3f,  56.32f, 0.0f, 0.0f, 0.0f, 0.0f,  //
                         5.5f,   8.42f,  94.0f,  46.9f,  0.0f, 0.0f, 0.0f, 0.0f,  //
                         0.0f,   0.0f,   0.0f,   0.0f,   0.0f, 0.0f, 0.0f, 0.0f,  //
                         0.0f,   0.0f,   0.0f,   0.0f,   0.0f, 0.0f, 0.0f, 8.0f,  //
                         0.0f,   0.0f,   0.0f,   0.0f,   0.0f, 0.0f, 0.0f, 0.0f,  //
                         6.0f,   0.0f,   0.0f,   0.0f,   0.0f, 0.0f, 1.0f, 0.0f};

    vectorMatTest(float, FLOAT_CAST_256_TO_MIPP_REG_T, FUN2TEST, Packet8f, 8, tab1);
  }
  endTest();

  beginTest("8 float 4⨉8 mat tests");
  {
    float tab1[4 * 8] = {14.02f, 38.8f,  42.14f, 3.33f,  0.0f, 0.0f, 0.0f, 2.0f,  //
                         6.3f,   54.25f, 62.6f,  92.04f, 0.0f, 0.0f, 0.0f, 0.0f,  //
                         99.0f,  78.7f,  89.3f,  56.32f, 0.0f, 0.0f, 0.0f, 0.0f,  //
                         5.5f,   8.42f,  94.0f,  46.9f,  0.0f, 0.0f, 0.0f, 0.0f};

    vectorMatTest(float, FLOAT_CAST_256_TO_MIPP_REG_T, FUN2TEST, Packet8f, 4, tab1);
  }
  endTest();

  // Packet4d (256)
  beginTest("4 double 4⨉4 mat tests");
  {
    double tab1[4 * 4] = {14.02d, 38.8d,  42.14d, 3.33d,   //
                          6.3d,   54.25d, 62.6d,  92.04d,  //
                          99.0d,  78.7d,  89.3d,  56.32d,  //
                          5.5d,   8.42d,  94.0d,  46.9d};

    vectorMatTest(double, DOUBLE_CAST_256_TO_MIPP_REG_T, FUN2TEST, Packet4d, 4, tab1);
  }
  endTest();

  // Packet8i (256)
  beginTest("8 int 8⨉8 mat tests");
  {
    int tab1[8 * 8] = {14, 38, 42, 3,  0, 0, 0, 2,  //
                       6,  54, 62, 92, 0, 0, 0, 0,  //
                       99, 78, 89, 56, 0, 0, 0, 0,  //
                       5,  8,  94, 46, 0, 0, 0, 0,  //
                       0,  0,  0,  0,  0, 0, 0, 0,  //
                       0,  0,  0,  0,  0, 0, 0, 8,  //
                       0,  0,  0,  0,  0, 0, 0, 0,  //
                       6,  0,  0,  0,  0, 0, 1, 0};

    vectorMatTest(int, INT_CAST_256_TO_MIPP_REG_T, FUN2TEST, Packet8i, 8, tab1);
  }
  endTest();

  beginTest("8 int 4⨉8 mat tests");
  {
    int tab1[4 * 8] = {14, 38, 42, 3,  0, 0, 0, 2,  //
                       6,  54, 62, 92, 0, 0, 0, 0,  //
                       99, 78, 89, 56, 0, 0, 0, 0,  //
                       5,  8,  94, 46, 0, 0, 0, 0};

    vectorMatTest(int, INT_CAST_256_TO_MIPP_REG_T, FUN2TEST, Packet8i, 4, tab1);
  }
  endTest();

  // Packet8h (128)
  beginTest("8 Eigen::half 8⨉8 mat tests");
  {
    Eigen::half tab1[8 * 8] = {
        half(14.02f), half(38.8f),  half(42.14f), half(3.33f),  half(0.0f), half(0.0f), half(0.0f), half(2.0f),  //
        half(6.3f),   half(54.25f), half(62.6f),  half(92.04f), half(0.0f), half(0.0f), half(0.0f), half(0.0f),  //
        half(99.0f),  half(78.7f),  half(89.3f),  half(56.32f), half(0.0f), half(0.0f), half(0.0f), half(0.0f),  //
        half(5.5f),   half(8.42f),  half(94.0f),  half(46.9f),  half(0.0f), half(0.0f), half(0.0f), half(0.0f),  //
        half(0.0f),   half(0.0f),   half(0.0f),   half(0.0f),   half(0.0f), half(0.0f), half(0.0f), half(0.0f),  //
        half(0.0f),   half(0.0f),   half(0.0f),   half(0.0f),   half(0.0f), half(0.0f), half(0.0f), half(8.0f),  //
        half(0.0f),   half(0.0f),   half(0.0f),   half(0.0f),   half(0.0f), half(0.0f), half(0.0f), half(0.0f),  //
        half(6.0f),   half(0.0f),   half(0.0f),   half(0.0f),   half(0.0f), half(0.0f), half(1.0f), half(0.0f)   //
    };

    vectorMatTest(short, INT_CAST_128_TO_MIPP_REG_T, FUN2TEST, Packet8h, 8, tab1);
  }
  endTest();

  beginTest("8 Eigen::half 4⨉8 mat tests");
  {
    Eigen::half tab1[4 * 8] = {
        half(14.02f), half(38.8f),  half(42.14f), half(3.33f),  half(0.0f), half(0.0f), half(0.0f), half(2.0f),  //
        half(6.3f),   half(54.25f), half(62.6f),  half(92.04f), half(0.0f), half(0.0f), half(0.0f), half(0.0f),  //
        half(99.0f),  half(78.7f),  half(89.3f),  half(56.32f), half(0.0f), half(0.0f), half(0.0f), half(0.0f),  //
        half(5.5f),   half(8.42f),  half(94.0f),  half(46.9f),  half(0.0f), half(0.0f), half(0.0f), half(0.0f)   //
    };

    vectorMatTest(short, INT_CAST_128_TO_MIPP_REG_T, FUN2TEST, Packet8h, 4, tab1);
  }
  endTest();

  // Packet8bf (128)
  beginTest("8 bfloat16 8⨉8 mat tests");
  {
    bfloat16 tab1[8 * 8] = {
        bfloat16(14.02f), bfloat16(38.8f),  bfloat16(42.14f), bfloat16(3.33f),
        bfloat16(0.0f),   bfloat16(0.0f),   bfloat16(0.0f),   bfloat16(2.0f),  //
        bfloat16(6.3f),   bfloat16(54.25f), bfloat16(62.6f),  bfloat16(92.04f),
        bfloat16(0.0f),   bfloat16(0.0f),   bfloat16(0.0f),   bfloat16(0.0f),  //
        bfloat16(99.0f),  bfloat16(78.7f),  bfloat16(89.3f),  bfloat16(56.32f),
        bfloat16(0.0f),   bfloat16(0.0f),   bfloat16(0.0f),   bfloat16(0.0f),  //
        bfloat16(5.5f),   bfloat16(8.42f),  bfloat16(94.0f),  bfloat16(46.9f),
        bfloat16(0.0f),   bfloat16(0.0f),   bfloat16(0.0f),   bfloat16(0.0f),  //
        bfloat16(0.0f),   bfloat16(0.0f),   bfloat16(0.0f),   bfloat16(0.0f),
        bfloat16(0.0f),   bfloat16(0.0f),   bfloat16(0.0f),   bfloat16(0.0f),  //
        bfloat16(0.0f),   bfloat16(0.0f),   bfloat16(0.0f),   bfloat16(0.0f),
        bfloat16(0.0f),   bfloat16(0.0f),   bfloat16(0.0f),   bfloat16(8.0f),  //
        bfloat16(0.0f),   bfloat16(0.0f),   bfloat16(0.0f),   bfloat16(0.0f),
        bfloat16(0.0f),   bfloat16(0.0f),   bfloat16(0.0f),   bfloat16(0.0f),  //
        bfloat16(6.0f),   bfloat16(0.0f),   bfloat16(0.0f),   bfloat16(0.0f),
        bfloat16(0.0f),   bfloat16(0.0f),   bfloat16(1.0f),   bfloat16(0.0f)  //
    };

    vectorMatTest(short, INT_CAST_128_TO_MIPP_REG_T, FUN2TEST, Packet8bf, 8, tab1);
  }
  endTest();

  beginTest("8 bfloat16 4⨉8 mat tests");
  {
    bfloat16 tab1[4 * 8] = {
        bfloat16(14.02f), bfloat16(38.8f),  bfloat16(42.14f), bfloat16(3.33f),
        bfloat16(0.0f),   bfloat16(0.0f),   bfloat16(0.0f),   bfloat16(2.0f),  //
        bfloat16(6.3f),   bfloat16(54.25f), bfloat16(62.6f),  bfloat16(92.04f),
        bfloat16(0.0f),   bfloat16(0.0f),   bfloat16(0.0f),   bfloat16(0.0f),  //
        bfloat16(99.0f),  bfloat16(78.7f),  bfloat16(89.3f),  bfloat16(56.32f),
        bfloat16(0.0f),   bfloat16(0.0f),   bfloat16(0.0f),   bfloat16(0.0f),  //
        bfloat16(5.5f),   bfloat16(8.42f),  bfloat16(94.0f),  bfloat16(46.9f),
        bfloat16(0.0f),   bfloat16(0.0f),   bfloat16(0.0f),   bfloat16(0.0f)  //
    };

    vectorMatTest(short, INT_CAST_128_TO_MIPP_REG_T, FUN2TEST, Packet8bf, 4, tab1);
  }
  endTest();

#endif

#ifdef __AVX2__
  // Packet4l (256)
  beginTest("4 long 4⨉4 mat tests");
  {
    long tab1[4 * 4] = {14, 38, 42, 3,   //
                        6,  54, 62, 92,  //
                        99, 78, 89, 56,  //
                        5,  8,  94, 46};

    vectorMatTest(long, INT_CAST_256_TO_MIPP_REG_T, FUN2TEST, Packet4l, 4, tab1);
  }
  endTest();
#endif

#ifdef __AVX512F__
#endif
}

addTest(FUN2TEST)

#endif  // EIGEN_MIPP_PTRANSPOSE_TEST_H
