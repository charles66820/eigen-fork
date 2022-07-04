#include <float.h>
#include <limits.h>

#ifndef EIGEN_MIPP_PSTOREU_MASK_TEST_H
#define EIGEN_MIPP_PSTOREU_MASK_TEST_H

#undef FUN2TEST
#define FUN2TEST pstoreu

void pstoreu2Tests() {
  printTestTitle(pstoreu + mask);

#ifdef __SSE__
#endif

#ifdef __AVX__
#endif

#ifdef __AVX2__
#endif

#ifdef __AVX512F__
  // Packet8f (256)
  beginTest("8 float tests");
  {
    MIN2MAX_FLOAT_VECTOR_LOADED(8);

    min2MaxArgsTests(uRefSingleType, FUN2TEST, float COMMA 8, vmax, v36, v0, v_240, vmin, (uint8_t)0x00);
    min2MaxArgsTests(uRefSingleType, FUN2TEST, float COMMA 8, vmax, v36, v0, v_240, vmin, (uint8_t)0xFF);
    min2MaxArgsTests(uRefSingleType, FUN2TEST, float COMMA 8, vmax, v36, v0, v_240, vmin, (uint8_t)0x0F);
    min2MaxArgsTests(uRefSingleType, FUN2TEST, float COMMA 8, vmax, v36, v0, v_240, vmin, (uint8_t)0xF0);
    min2MaxArgsTests(uRefSingleType, FUN2TEST, float COMMA 8, vmax, v36, v0, v_240, vmin, (uint8_t)0xaa);
    min2MaxArgsTests(uRefSingleType, FUN2TEST, float COMMA 8, vmax, v36, v0, v_240, vmin, (uint8_t)0x55);
  }
  endTest();

#endif
}

addTest(pstoreu2)

#endif  // EIGEN_MIPP_PSTOREU_MASK_TEST_H
