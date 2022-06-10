#include <float.h>
#include <limits.h>

#ifndef EIGEN_MIPP_PLOAD_TEST_H
#define EIGEN_MIPP_PLOAD_TEST_H

#undef FUN2TEST
#define FUN2TEST pload

#define str(s) #s
#define xstr(s) str(s)

#define vector2(type, name, value, delta) type name[] __attribute__((aligned(32))) = {value, value + delta};
#define vector4(type, name, value, delta) \
  type name[]                             \
      __attribute__((aligned(32))) = {value, value + delta, value + delta + delta, value + delta + delta + delta};
#define vector8(type, name, value, delta)                                                            \
  type name[] __attribute__((aligned(32))) = {value,                                                 \
                                              value + delta,                                         \
                                              value + delta + delta,                                 \
                                              value + delta + delta + delta,                         \
                                              value + delta + delta + delta + delta,                 \
                                              value + delta + delta + delta + delta + delta,         \
                                              value + delta + delta + delta + delta + delta + delta, \
                                              value + delta + delta + delta + delta + delta + delta + delta};
#define vector16(type, name, value, delta)                                                                            \
  type name[] __attribute__((aligned(32))) = {                                                                        \
      value,                                                                                                          \
      value + delta,                                                                                                  \
      value + delta + delta,                                                                                          \
      value + delta + delta + delta,                                                                                  \
      value + delta + delta + delta + delta,                                                                          \
      value + delta + delta + delta + delta + delta,                                                                  \
      value + delta + delta + delta + delta + delta + delta,                                                          \
      value + delta + delta + delta + delta + delta + delta + delta,                                                  \
      value + delta + delta + delta + delta + delta + delta + delta + delta,                                          \
      value + delta + delta + delta + delta + delta + delta + delta + delta + delta,                                  \
      value + delta + delta + delta + delta + delta + delta + delta + delta + delta + delta,                          \
      value + delta + delta + delta + delta + delta + delta + delta + delta + delta + delta + delta,                  \
      value + delta + delta + delta + delta + delta + delta + delta + delta + delta + delta + delta + delta,          \
      value + delta + delta + delta + delta + delta + delta + delta + delta + delta + delta + delta + delta + delta,  \
      value + delta + delta + delta + delta + delta + delta + delta + delta + delta + delta + delta + delta + delta + \
          delta,                                                                                                      \
      value + delta + delta + delta + delta + delta + delta + delta + delta + delta + delta + delta + delta + delta + \
          delta + delta};

#define runTest(vec, type, test, value, delta) \
  {                                            \
    vec(type, v, value, delta);                \
    test(FUN2TEST, v);                         \
  }

void ploadTests() {
  std::cout << xstr(FUN2TEST) << " :" << std::endl;

#ifdef __SSE__
  /* float = Packet4f (half) */
  std::cout << "half float tests" << std::endl;
  runTest(vector4, float, dynHalfFloatTest, FLT_MAX, -0.1f);
  runTest(vector4, float, dynHalfFloatTest, 36.7f, 0.1f);
  runTest(vector4, float, dynHalfFloatTest, 0.0f, 0.1f);
  runTest(vector4, float, dynHalfFloatTest, -240.98f, 0.1f);
  runTest(vector4, float, dynHalfFloatTest, FLT_MIN, 0.1f);

  /* double =  Packet2d (half) */
  std::cout << "half double tests" << std::endl;
  runTest(vector2, double, dynHalfDoubleTest, DBL_MAX, -0.1d);
  runTest(vector2, double, dynHalfDoubleTest, 36.7d, 0.1d);
  runTest(vector2, double, dynHalfDoubleTest, 0.0d, 0.1d);
  runTest(vector2, double, dynHalfDoubleTest, -240.98d, 0.1d);
  runTest(vector2, double, dynHalfDoubleTest, DBL_MIN, 0.1d);

  /* int = Packet4i (half) */
  std::cout << "half int tests" << std::endl;
  runTest(vector4, int, dynHalfIntTest, INT_MAX, -1);
  runTest(vector4, int, dynHalfIntTest, 36, 1);
  runTest(vector4, int, dynHalfIntTest, 0, 1);
  runTest(vector4, int, dynHalfIntTest, -240, 1);
  runTest(vector4, int, dynHalfIntTest, INT_MIN, 1);

  /* bool = Packet16b */
  std::cout << "bool tests" << std::endl;
  runTest(vector16, bool, dynHalfBoolTest, true, 0);
  runTest(vector16, bool, dynHalfBoolTest, false, 0);
#endif

#ifdef __AVX__
  /* float = Packet8f (full) */
  std::cout << "full float tests" << std::endl;
  runTest(vector8, float, dynFullFloatTest, FLT_MAX, -0.1f);
  runTest(vector8, float, dynFullFloatTest, 36.7f, 0.1f);
  runTest(vector8, float, dynFullFloatTest, 0.0f, 0.1f);
  runTest(vector8, float, dynFullFloatTest, -240.98f, 0.1f);
  runTest(vector8, float, dynFullFloatTest, FLT_MIN, 0.1f);

  /* double = Packet4d (full) */
  std::cout << "full double tests" << std::endl;
  runTest(vector4, double, dynFullDoubleTest, DBL_MAX, -0.1d);
  runTest(vector4, double, dynFullDoubleTest, 36.7d, 0.1d);
  runTest(vector4, double, dynFullDoubleTest, 0.0d, 0.1d);
  runTest(vector4, double, dynFullDoubleTest, -240.98d, 0.1d);
  runTest(vector4, double, dynFullDoubleTest, DBL_MIN, 0.1d);

  /* int = Packet8i (full) */
  std::cout << "full int tests" << std::endl;
  runTest(vector8, int, dynFullIntTest, INT_MAX, -1);
  runTest(vector8, int, dynFullIntTest, 36, 1);
  runTest(vector8, int, dynFullIntTest, 0, 1);
  runTest(vector8, int, dynFullIntTest, -240, 1);
  runTest(vector8, int, dynFullIntTest, INT_MIN, 1);

  /* Eigen::half = Packet8h */
  std::cout << "Eigen::half tests" << std::endl;
  runTest(vector8, Eigen::half, dynHalfEigenHalfTest, half(FLT_MAX), half(-0.1f));
  runTest(vector8, Eigen::half, dynHalfEigenHalfTest, half(36.7f), half(0.1f));
  runTest(vector8, Eigen::half, dynHalfEigenHalfTest, half(0.0f), half(0.1f));
  runTest(vector8, Eigen::half, dynHalfEigenHalfTest, half(-240.98f), half(0.1f));
  runTest(vector8, Eigen::half, dynHalfEigenHalfTest, half(FLT_MIN), half(0.1f));

  /* bfloat16 = Packet8bf */
  std::cout << "bfloat16 tests" << std::endl;
  runTest(vector8, bfloat16, dynHalfBfloat16Test, bfloat16(FLT_MAX), bfloat16(-0.1f));
  runTest(vector8, bfloat16, dynHalfBfloat16Test, bfloat16(36.7f), bfloat16(0.1f));
  runTest(vector8, bfloat16, dynHalfBfloat16Test, bfloat16(0.0f), bfloat16(0.1f));
  runTest(vector8, bfloat16, dynHalfBfloat16Test, bfloat16(-240.98f), bfloat16(0.1f));
  runTest(vector8, bfloat16, dynHalfBfloat16Test, bfloat16(FLT_MIN), bfloat16(0.1f));
#endif

#ifdef __AVX2__
  /* long = Packet4l */
  std::cout << "long tests" << std::endl;
  runTest(vector4, long, dynFullLongTest, LONG_MAX, -1L);
  runTest(vector4, long, dynFullLongTest, 36L, 1L);
  runTest(vector4, long, dynFullLongTest, 0L, 1L);
  runTest(vector4, long, dynFullLongTest, -240L, 1L);
  runTest(vector4, long, dynFullLongTest, LONG_MIN, 1L);
#endif

#ifdef __AVX512__
#endif
}

#endif  // EIGEN_MIPP_PLOAD_TEST_H
