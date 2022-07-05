#include <float.h>
#include <limits.h>

#ifndef EIGEN_MIPP_PBROADCAST4_TEST_H
#define EIGEN_MIPP_PBROADCAST4_TEST_H

#undef FUN2TEST
#define FUN2TEST pbroadcast4

#define vector4Test_imp(type, cast, name, eigenType, tab)                                                         \
  {                                                                                                               \
    eigenType res1;                                                                                               \
    eigenType res2;                                                                                               \
    eigenType res3;                                                                                               \
    eigenType res4;                                                                                               \
    name<eigenType>(tab, res1, res2, res3, res4);                                                                 \
                                                                                                                  \
    eigenType res1_old;                                                                                           \
    eigenType res2_old;                                                                                           \
    eigenType res3_old;                                                                                           \
    eigenType res4_old;                                                                                           \
    name##_old<eigenType>(tab, res1_old, res2_old, res3_old, res4_old);                                           \
                                                                                                                  \
    mipp::Reg<type> res1M = cast(res1);                                                                           \
    mipp::Reg<type> res2M = cast(res2);                                                                           \
    mipp::Reg<type> res3M = cast(res3);                                                                           \
    mipp::Reg<type> res4M = cast(res4);                                                                           \
    mipp::Reg<type> res1M_old = cast(res1_old);                                                                   \
    mipp::Reg<type> res2M_old = cast(res2_old);                                                                   \
    mipp::Reg<type> res3M_old = cast(res3_old);                                                                   \
    mipp::Reg<type> res4M_old = cast(res4_old);                                                                   \
                                                                                                                  \
    hasFailed |=                                                                                                  \
        printWhenDiff((!mipp::testz(res1M != res1M_old) || !mipp::testz(res2M != res2M_old) ||                    \
                       !mipp::testz(res3M != res3M_old) || !mipp::testz(res4M != res4M_old)),                     \
                      #name "<" #eigenType ">(" + to_string(tab) + ", P*, P*, P*, P*)",                           \
                      to_string(res1M) + to_string(res2M) + to_string(res3M) + to_string(res4M),                  \
                      to_string(res1M_old) + to_string(res2M_old) + to_string(res3M_old) + to_string(res4M_old)); \
  }

#define vector4Test(type, cast, name, eigenType, tab) vector4Test_imp(type, cast, name, eigenType, tab)

void pbroadcast4Tests() {
  printTestTitle(FUN2TEST);

#ifdef __SSE__
  // Packet4f (128)
  beginTest("4 float tests");
  {
    float tabMax[4] = {FLT_MAX, FLT_MAX, FLT_MAX, FLT_MAX};
    float tab36[4] = {36.7f, 36.7f, 36.7f, 36.7f};
    float tab0[4] = {0.0f, 0.0f, 0.0f, 0.0f};
    float tab_240[4] = {-240.98f, -240.98f, -240.98f, -240.98f};
    float tabMin[4] = {FLT_MIN, FLT_MIN, FLT_MIN, FLT_MIN};

    vector4Test(float, FLOAT_CAST_128_TO_MIPP_REG_T, FUN2TEST, Packet4f, tabMax);
    vector4Test(float, FLOAT_CAST_128_TO_MIPP_REG_T, FUN2TEST, Packet4f, tab36);
    vector4Test(float, FLOAT_CAST_128_TO_MIPP_REG_T, FUN2TEST, Packet4f, tab0);
    vector4Test(float, FLOAT_CAST_128_TO_MIPP_REG_T, FUN2TEST, Packet4f, tab_240);
    vector4Test(float, FLOAT_CAST_128_TO_MIPP_REG_T, FUN2TEST, Packet4f, tabMin);
  }
  endTest();

  /* double = Packet2d (half) */
  beginTest("2 double tests");
  {
    double tabMax[4] = {DBL_MAX, DBL_MAX, DBL_MAX, DBL_MAX};
    double tab36[4] = {36.7d, 36.7d, 36.7d, 36.7d};
    double tab0[4] = {0.0d, 0.0d, 0.0d, 0.0d};
    double tab_240[4] = {-240.98d, -240.98d, -240.98d, -240.98d};
    double tabMin[4] = {DBL_MIN, DBL_MIN, DBL_MIN, DBL_MIN};

    vector4Test(double, DOUBLE_CAST_128_TO_MIPP_REG_T, FUN2TEST, Packet2d, tabMax);
    vector4Test(double, DOUBLE_CAST_128_TO_MIPP_REG_T, FUN2TEST, Packet2d, tab36);
    vector4Test(double, DOUBLE_CAST_128_TO_MIPP_REG_T, FUN2TEST, Packet2d, tab0);
    vector4Test(double, DOUBLE_CAST_128_TO_MIPP_REG_T, FUN2TEST, Packet2d, tab_240);
    vector4Test(double, DOUBLE_CAST_128_TO_MIPP_REG_T, FUN2TEST, Packet2d, tabMin);
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

#endif  // EIGEN_MIPP_PBROADCAST4_TEST_H
