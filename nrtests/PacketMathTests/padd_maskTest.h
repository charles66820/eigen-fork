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

  MIN2MAX_8_FLOAT_VECTOR_LOADED

  allTwoCombRepArgs(vectorFullFloatTest, FUN2TEST, (Packet8f)fvmax, (Packet8f)fv36, (Packet8f)fv0, (Packet8f)fv_240, (Packet8f)fvmin, (uint8_t)0x00);
  allTwoCombRepArgs(vectorFullFloatTest, FUN2TEST, (Packet8f)fvmax, (Packet8f)fv36, (Packet8f)fv0, (Packet8f)fv_240, (Packet8f)fvmin, (uint8_t)0xFF);
  allTwoCombRepArgs(vectorFullFloatTest, FUN2TEST, (Packet8f)fvmax, (Packet8f)fv36, (Packet8f)fv0, (Packet8f)fv_240, (Packet8f)fvmin, (uint8_t)0x0F);
  allTwoCombRepArgs(vectorFullFloatTest, FUN2TEST, (Packet8f)fvmax, (Packet8f)fv36, (Packet8f)fv0, (Packet8f)fv_240, (Packet8f)fvmin, (uint8_t)0xF0);
  allTwoCombRepArgs(vectorFullFloatTest, FUN2TEST, (Packet8f)fvmax, (Packet8f)fv36, (Packet8f)fv0, (Packet8f)fv_240, (Packet8f)fvmin, (uint8_t)0xaa);
  allTwoCombRepArgs(vectorFullFloatTest, FUN2TEST, (Packet8f)fvmax, (Packet8f)fv36, (Packet8f)fv0, (Packet8f)fv_240, (Packet8f)fvmin, (uint8_t)0x55);

  endTest();
#endif
}

addTest(padd2)

#endif  // EIGEN_MIPP_PADD_MASK_TEST_H
