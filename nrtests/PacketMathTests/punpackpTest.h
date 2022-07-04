#include <float.h>
#include <limits.h>

#ifndef EIGEN_MIPP_PUNPACKP_TEST_H
#define EIGEN_MIPP_PUNPACKP_TEST_H

#undef FUN2TEST
#define FUN2TEST punpackp

#define vector4ptrTest_imp(type, cast, name, eigenType, args...)                                                   \
  {                                                                                                                \
    eigenType ptr;                                                                                                 \
                                                                                                                   \
    type tab[4] = {args};                                                                                          \
    eigenType p4[4];                                                                                               \
    p4[0] = pload<eigenType>(tab);                                                                                 \
    p4[1] = pzero<eigenType>(ptr);                                                                                 \
    p4[2] = pzero<eigenType>(ptr);                                                                                 \
    p4[3] = pzero<eigenType>(ptr);                                                                                 \
                                                                                                                   \
    type tab_old[4] = {args};                                                                                      \
    eigenType p4_old[4];                                                                                           \
    p4_old[0] = pload<eigenType>(tab_old);                                                                         \
    p4_old[1] = pzero<eigenType>(ptr);                                                                             \
    p4_old[2] = pzero<eigenType>(ptr);                                                                             \
    p4_old[3] = pzero<eigenType>(ptr);                                                                             \
                                                                                                                   \
    name(p4);                                                                                                      \
    name##_old(p4_old);                                                                                            \
                                                                                                                   \
    mipp::Reg<type> res1 = cast(p4[0]);                                                                            \
    mipp::Reg<type> res2 = cast(p4[1]);                                                                            \
    mipp::Reg<type> res3 = cast(p4[2]);                                                                            \
    mipp::Reg<type> res4 = cast(p4[3]);                                                                            \
    mipp::Reg<type> res1_old = cast(p4_old[0]);                                                                    \
    mipp::Reg<type> res2_old = cast(p4_old[1]);                                                                    \
    mipp::Reg<type> res3_old = cast(p4_old[2]);                                                                    \
    mipp::Reg<type> res4_old = cast(p4_old[3]);                                                                    \
                                                                                                                   \
    hasFailed |= printWhenDiff((!mipp::testz(res1 != res1_old) || !mipp::testz(res2 != res2_old) ||                \
                                !mipp::testz(res3 != res3_old) || !mipp::testz(res4 != res4_old)),                 \
                               #name "(" + to_sting(tab) + ")",                                                    \
                               to_sting(res1) + to_sting(res2) + to_sting(res3) + to_sting(res4),                  \
                               to_sting(res1_old) + to_sting(res2_old) + to_sting(res3_old) + to_sting(res4_old)); \
  }

#define vector4ptrTest(type, cast, name, eigenType, args...) vector4ptrTest_imp(type, cast, name, eigenType, args)

void punpackpTests() {
  printTestTitle(FUN2TEST);

#ifdef __SSE__
  // Packet4f (128)
  beginTest("4 float tests");
  {
    vector4ptrTest(float, FLOAT_CAST_128_TO_MIPP_REG_T, FUN2TEST, Packet4f, FLT_MAX, 36.7f, 0.0f, -240.98f);
    vector4ptrTest(float, FLOAT_CAST_128_TO_MIPP_REG_T, FUN2TEST, Packet4f, 36.7f, 0.0f, -240.98f, FLT_MIN);
  }
  endTest();

#endif

#ifdef __AVX__
#endif

#ifdef __AVX2__
#endif

#ifdef __AVX512F__
#endif
}

addTest(FUN2TEST)

#endif  // EIGEN_MIPP_PUNPACKP_TEST_H
