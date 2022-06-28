#include <float.h>
#include <limits.h>
#include "../testVector.h"
#include "../testCombinations.h"

#ifndef EIGEN_MIPP_PADD_MASK_TEST_H
#define EIGEN_MIPP_PADD_MASK_TEST_H

#undef FUN2TEST
#define FUN2TEST padd

void padd2Tests() {
  std::cout << printTestTitle(padd + mask) << std::endl;

#ifdef __SSE__
#endif

#ifdef __AVX__
#endif

#ifdef __AVX2__
#endif

#ifdef __AVX512F__
  /* float = Packet8f (full) */
  beginTest("full float tests");
  loadVectorFull(vector8, float, fvmax, , Packet8f, FLT_MAX, 0.0f);
  loadVectorFull(vector8, float, fv36, , Packet8f, 36.7f, 0.0f);
  loadVectorFull(vector8, float, fv0, , Packet8f, 0.0f, 0.0f);
  loadVectorFull(vector8, float, fv_240, , Packet8f, -240.98f, 0.0f);
  loadVectorFull(vector8, float, fvmin, , Packet8f, FLT_MAX, 0.0f);

  allTwoCombRepArgs(vectorFullFloatTest, FUN2TEST, (Packet8f)fvmax.r, (Packet8f)fv36.r, (Packet8f)fv0.r, (Packet8f)fv_240.r, (Packet8f)fvmin.r, (uint8_t)0x00);

  endTest();
#endif
}

addTest(padd2)

#endif  // EIGEN_MIPP_PADD_MASK_TEST_H
