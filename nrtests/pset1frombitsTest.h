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

  dynHalfFloatTest(FUN2TEST, (uint32_t)INT_MAX);
  dynHalfFloatTest(FUN2TEST, (uint32_t)0x4212cccd);
  dynHalfFloatTest(FUN2TEST, (uint32_t)0x00000000);
  dynHalfFloatTest(FUN2TEST, (uint32_t)0xc370fae1);
  dynHalfFloatTest(FUN2TEST, (uint32_t)INT_MIN);

  endTest();

  /* double =  Packet2d (half) */
  beginTest("half double tests");

  dynHalfDoubleTest(FUN2TEST, (uint64_t)LONG_MAX);
  dynHalfDoubleTest(FUN2TEST, (uint64_t)0x404259999999999a);
  dynHalfDoubleTest(FUN2TEST, (uint64_t)0x0000000000000000);
  dynHalfDoubleTest(FUN2TEST, (uint64_t)0xc06e1f5c28f5c28f);
  dynHalfDoubleTest(FUN2TEST, (uint64_t)LONG_MIN);

  endTest();

#endif

#ifdef __AVX__
  /* float = Packet8f (full) */
  beginTest("full float tests");

  dynFullFloatTest(FUN2TEST, (uint32_t)INT_MAX);
  dynFullFloatTest(FUN2TEST, (uint32_t)0x4212cccd);
  dynFullFloatTest(FUN2TEST, (uint32_t)0x00000000);
  dynFullFloatTest(FUN2TEST, (uint32_t)0xc370fae1);
  dynFullFloatTest(FUN2TEST, (uint32_t)INT_MIN);

  endTest();

  /* double = Packet4d (full) */
  beginTest("full double tests");

  dynFullDoubleTest(FUN2TEST, (uint64_t)LONG_MAX);
  dynFullDoubleTest(FUN2TEST, (uint64_t)0x404259999999999a);
  dynFullDoubleTest(FUN2TEST, (uint64_t)0x0000000000000000);
  dynFullDoubleTest(FUN2TEST, (uint64_t)0xc06e1f5c28f5c28f);
  dynFullDoubleTest(FUN2TEST, (uint64_t)LONG_MIN);

  endTest();

#endif

#ifdef __AVX2__
#endif

#ifdef __AVX512__
#endif
}

#endif  // EIGEN_MIPP_PSET1FROMBITS_TEST_H
