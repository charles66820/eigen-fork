#include <float.h>
#include <limits.h>

#ifndef EIGEN_MIPP_PSET1_TEST_H
#define EIGEN_MIPP_PSET1_TEST_H

#undef FUN2TEST
#define FUN2TEST pset1

void pset1Tests() {
  std::cout << printTestTitle(FUN2TEST) << std::endl;

#ifdef __SSE__
  /* float = Packet4f (half) */
  std::cout << "half float tests" << std::endl;
  dynHalfFloatTest(FUN2TEST, FLT_MAX);
  dynHalfFloatTest(FUN2TEST, 36.7f);
  dynHalfFloatTest(FUN2TEST, 0.0f);
  dynHalfFloatTest(FUN2TEST, -240.98f);
  dynHalfFloatTest(FUN2TEST, FLT_MIN);

  /* double =  Packet2d (half) */
  std::cout << "half double tests" << std::endl;
  dynHalfDoubleTest(FUN2TEST, DBL_MAX);
  dynHalfDoubleTest(FUN2TEST, 36.7d);
  dynHalfDoubleTest(FUN2TEST, 0.0d);
  dynHalfDoubleTest(FUN2TEST, -240.98d);
  dynHalfDoubleTest(FUN2TEST, DBL_MIN);

  /* int = Packet4i (half) */
  std::cout << "half int tests" << std::endl;
  dynHalfIntTest(FUN2TEST, INT_MAX);
  dynHalfIntTest(FUN2TEST, 36);
  dynHalfIntTest(FUN2TEST, 0);
  dynHalfIntTest(FUN2TEST, -240);
  dynHalfIntTest(FUN2TEST, INT_MIN);

  /* bool = Packet16b */
  std::cout << "bool tests" << std::endl;
  dynHalfBoolTest(FUN2TEST, true);
  dynHalfBoolTest(FUN2TEST, false);
  dynHalfBoolTest(FUN2TEST, CHAR_MAX);
  dynHalfBoolTest(FUN2TEST, CHAR_MIN);
#endif

#ifdef __AVX__
  /* float = Packet8f (full) */
  std::cout << "full float tests" << std::endl;
  dynFullFloatTest(FUN2TEST, FLT_MAX);
  dynFullFloatTest(FUN2TEST, 36.7f);
  dynFullFloatTest(FUN2TEST, 0.0f);
  dynFullFloatTest(FUN2TEST, -240.98f);
  dynFullFloatTest(FUN2TEST, FLT_MIN);

  /* double = Packet4d (full) */
  std::cout << "full double tests" << std::endl;
  dynFullDoubleTest(FUN2TEST, DBL_MAX);
  dynFullDoubleTest(FUN2TEST, 36.7d);
  dynFullDoubleTest(FUN2TEST, 0.0d);
  dynFullDoubleTest(FUN2TEST, -240.98d);
  dynFullDoubleTest(FUN2TEST, DBL_MIN);

  /* int = Packet8i (full) */
  std::cout << "full int tests" << std::endl;
  dynFullIntTest(FUN2TEST, INT_MAX);
  dynFullIntTest(FUN2TEST, 36);
  dynFullIntTest(FUN2TEST, 0);
  dynFullIntTest(FUN2TEST, -240);
  dynFullIntTest(FUN2TEST, INT_MIN);

  /* Eigen::half = Packet8h */
  std::cout << "Eigen::half tests" << std::endl;
  dynHalfEigenHalfTest(FUN2TEST, half(FLT_MAX));
  dynHalfEigenHalfTest(FUN2TEST, half(36.7f));
  dynHalfEigenHalfTest(FUN2TEST, half(0.0f));
  dynHalfEigenHalfTest(FUN2TEST, half(-240.98f));
  dynHalfEigenHalfTest(FUN2TEST, half(FLT_MIN));

  /* bfloat16 = Packet8bf */
  std::cout << "bfloat16 tests" << std::endl;
  dynHalfBfloat16Test(FUN2TEST, bfloat16(FLT_MAX));
  dynHalfBfloat16Test(FUN2TEST, bfloat16(36.7f));
  dynHalfBfloat16Test(FUN2TEST, bfloat16(0.0f));
  dynHalfBfloat16Test(FUN2TEST, bfloat16(-240.98f));
  dynHalfBfloat16Test(FUN2TEST, bfloat16(FLT_MIN));
#endif

#ifdef __AVX2__
  /* long = Packet4l */
  std::cout << "long tests" << std::endl;
  dynFullLongTest(FUN2TEST, LONG_MAX);
  dynFullLongTest(FUN2TEST, 36L);
  dynFullLongTest(FUN2TEST, 0L);
  dynFullLongTest(FUN2TEST, -240L);
  dynFullLongTest(FUN2TEST, LONG_MIN);
#endif

#ifdef __AVX512__
#endif
}

#endif  // EIGEN_MIPP_PSET1_TEST_H
