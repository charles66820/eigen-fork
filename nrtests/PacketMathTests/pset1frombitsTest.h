#include <float.h>
#include <limits.h>

#ifndef EIGEN_MIPP_PSET1FROMBITS_TEST_H
#define EIGEN_MIPP_PSET1FROMBITS_TEST_H

#undef FUN2TEST
#define FUN2TEST pset1frombits

void pset1frombitsTests() {
  std::cout << printTestTitle(FUN2TEST) << std::endl;

#ifdef __SSE__
  /* float = Packet4f (half) */
  beginTest("half float tests");

  vectorHalfFloatTest(FUN2TEST, (uint32_t)INT_MAX);
  vectorHalfFloatTest(FUN2TEST, (uint32_t)0x4212cccd);
  vectorHalfFloatTest(FUN2TEST, (uint32_t)0x00000000);
  vectorHalfFloatTest(FUN2TEST, (uint32_t)0xc370fae1);
  vectorHalfFloatTest(FUN2TEST, (uint32_t)INT_MIN);

  endTest();

  /* double =  Packet2d (half) */
  beginTest("half double tests");

  vectorHalfDoubleTest(FUN2TEST, (uint64_t)LONG_MAX);
  vectorHalfDoubleTest(FUN2TEST, (uint64_t)0x404259999999999a);
  vectorHalfDoubleTest(FUN2TEST, (uint64_t)0x0000000000000000);
  vectorHalfDoubleTest(FUN2TEST, (uint64_t)0xc06e1f5c28f5c28f);
  vectorHalfDoubleTest(FUN2TEST, (uint64_t)LONG_MIN);

  endTest();

#endif

#ifdef __AVX__
  /* float = Packet8f (full) */
  beginTest("full float tests");

  vectorFullFloatTest(FUN2TEST, (uint32_t)INT_MAX);
  vectorFullFloatTest(FUN2TEST, (uint32_t)0x4212cccd);
  vectorFullFloatTest(FUN2TEST, (uint32_t)0x00000000);
  vectorFullFloatTest(FUN2TEST, (uint32_t)0xc370fae1);
  vectorFullFloatTest(FUN2TEST, (uint32_t)INT_MIN);

  endTest();

  /* double = Packet4d (full) */
  beginTest("full double tests");

  vectorFullDoubleTest(FUN2TEST, (uint64_t)LONG_MAX);
  vectorFullDoubleTest(FUN2TEST, (uint64_t)0x404259999999999a);
  vectorFullDoubleTest(FUN2TEST, (uint64_t)0x0000000000000000);
  vectorFullDoubleTest(FUN2TEST, (uint64_t)0xc06e1f5c28f5c28f);
  vectorFullDoubleTest(FUN2TEST, (uint64_t)LONG_MIN);

  endTest();

#endif

#ifdef __AVX2__
#endif

#ifdef __AVX512__
#endif
}

#endif  // EIGEN_MIPP_PSET1FROMBITS_TEST_H
