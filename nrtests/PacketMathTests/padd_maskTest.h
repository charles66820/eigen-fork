#include <float.h>
#include <limits.h>

#ifndef EIGEN_MIPP_PADD_MASK_TEST_H
#define EIGEN_MIPP_PADD_MASK_TEST_H

#undef FUN2TEST
#define FUN2TEST padd

void padd2Tests() {
  printTestTitle(padd + mask);

#ifdef __SSE__
#endif

#ifdef __AVX__
#endif

#ifdef __AVX2__
#endif

#ifdef __AVX512F__
  /* float = Packet8f (full) */
  beginTest("8 float tests");
  {
    MIN2MAX_FLOAT_VECTOR_LOADED(8);

    allTwoCombRepArgs(vectorFullFloatTemplateTest, FUN2TEST, Packet8f, vmax, v36, v0, v_240, vmin, (uint8_t)0x00);
    allTwoCombRepArgs(vectorFullFloatTemplateTest, FUN2TEST, Packet8f, vmax, v36, v0, v_240, vmin, (uint8_t)0xFF);
    allTwoCombRepArgs(vectorFullFloatTemplateTest, FUN2TEST, Packet8f, vmax, v36, v0, v_240, vmin, (uint8_t)0x0F);
    allTwoCombRepArgs(vectorFullFloatTemplateTest, FUN2TEST, Packet8f, vmax, v36, v0, v_240, vmin, (uint8_t)0xF0);
    allTwoCombRepArgs(vectorFullFloatTemplateTest, FUN2TEST, Packet8f, vmax, v36, v0, v_240, vmin, (uint8_t)0xaa);
    allTwoCombRepArgs(vectorFullFloatTemplateTest, FUN2TEST, Packet8f, vmax, v36, v0, v_240, vmin, (uint8_t)0x55);
  }
  endTest();

#endif
}

addTest(padd2)

#endif  // EIGEN_MIPP_PADD_MASK_TEST_H
