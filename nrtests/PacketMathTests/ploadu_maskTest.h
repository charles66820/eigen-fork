#include <float.h>
#include <limits.h>

#ifndef EIGEN_MIPP_PLOADU_MASK_TEST_H
#define EIGEN_MIPP_PLOADU_MASK_TEST_H

#undef FUN2TEST
#define FUN2TEST ploadu

#define tests8FloatMin2MaxOneArgLoadedAndMask(str, funName)                                             \
  beginTest(str);                                                                                       \
  {                                                                                                     \
    MIN2MAX_FLOAT_VECTOR(vector8u);                                                                     \
                                                                                                        \
    min2MaxArgsTests(vector256FloatTest, funName, Packet8f, vmax, v36, v0, v_240, vmin, (uint8_t)0x00); \
    min2MaxArgsTests(vector256FloatTest, funName, Packet8f, vmax, v36, v0, v_240, vmin, (uint8_t)0xFF); \
    min2MaxArgsTests(vector256FloatTest, funName, Packet8f, vmax, v36, v0, v_240, vmin, (uint8_t)0x0F); \
    min2MaxArgsTests(vector256FloatTest, funName, Packet8f, vmax, v36, v0, v_240, vmin, (uint8_t)0xF0); \
    min2MaxArgsTests(vector256FloatTest, funName, Packet8f, vmax, v36, v0, v_240, vmin, (uint8_t)0xaa); \
    min2MaxArgsTests(vector256FloatTest, funName, Packet8f, vmax, v36, v0, v_240, vmin, (uint8_t)0x55); \
  }                                                                                                     \
  endTest();

void ploadu2Tests() {
  printTestTitle(ploadu + mask);

#ifdef __SSE__
#endif

#ifdef __AVX__
#endif

#ifdef __AVX2__
#endif

#ifdef __AVX512F__
  // Packet8f (256)
  tests8FloatMin2MaxOneArgLoadedAndMask("8 float tests", FUN2TEST);

#endif
}

addTest(ploadu2)

#endif  // EIGEN_MIPP_PLOADU_MASK_TEST_H
