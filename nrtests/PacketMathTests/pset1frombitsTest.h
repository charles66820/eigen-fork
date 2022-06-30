#include <float.h>
#include <limits.h>

#ifndef EIGEN_MIPP_PSET1FROMBITS_TEST_H
#define EIGEN_MIPP_PSET1FROMBITS_TEST_H

#undef FUN2TEST
#define FUN2TEST pset1frombits

void pset1frombitsTests() {
  printTestTitle(FUN2TEST);

#ifdef __SSE__
  /* float = Packet4f (half) */
  beginTest("4 float tests");

  min2MaxTests(vectorHalfFloatTemplateTest, FUN2TEST, Packet4f, (uint32_t)INT_MAX, (uint32_t)0x4212cccd,
               (uint32_t)0x00000000, (uint32_t)0xc370fae1, (uint32_t)INT_MIN);

  endTest();

  /* double =  Packet2d (half) */
  beginTest("2 double tests");

  min2MaxTests(vectorHalfDoubleTemplateTest, FUN2TEST, Packet2d, (uint64_t)LONG_MAX, (uint64_t)0x404259999999999a,
               (uint64_t)0x0000000000000000, (uint64_t)0xc06e1f5c28f5c28f, (uint64_t)LONG_MIN);

  endTest();

#endif

#ifdef __AVX__
  /* float = Packet8f (full) */
  beginTest("8 float tests");

  min2MaxTests(vectorFullFloatTemplateTest, FUN2TEST, Packet8f, (uint32_t)INT_MAX, (uint32_t)0x4212cccd,
               (uint32_t)0x00000000, (uint32_t)0xc370fae1, (uint32_t)INT_MIN);

  endTest();

  /* double = Packet4d (full) */
  beginTest("4 double tests");

  min2MaxTests(vectorFullDoubleTemplateTest, FUN2TEST, Packet4d, (uint64_t)LONG_MAX, (uint64_t)0x404259999999999a,
               (uint64_t)0x0000000000000000, (uint64_t)0xc06e1f5c28f5c28f, (uint64_t)LONG_MIN);

  endTest();

#endif

#ifdef __AVX2__
#endif

#ifdef __AVX512F__
#endif
}

addTest(FUN2TEST)

#endif  // EIGEN_MIPP_PSET1FROMBITS_TEST_H
