#include <float.h>
#include <limits.h>

#ifndef EIGEN_MIPP_PSET1_TEST_H
#define EIGEN_MIPP_PSET1_TEST_H

void pset1Tests() {
  /* long = Packet4l */
  std::cout << "pset1 long tests" << std::endl;
  dynFullLongTest(pset1, LONG_MAX);
  dynFullLongTest(pset1, 36L);
  dynFullLongTest(pset1, 0L);
  dynFullLongTest(pset1, -240L);
  dynFullLongTest(pset1, LONG_MIN);

  /* float = Packet4f (half) */
  std::cout << "pset1 half float tests" << std::endl;
  dynHalfFloatTest(pset1, FLT_MAX);
  dynHalfFloatTest(pset1, 36.7f);
  dynHalfFloatTest(pset1, 0.0f);
  dynHalfFloatTest(pset1, -240.98f);
  dynHalfFloatTest(pset1, FLT_MIN);

  /* float = Packet8f (full) */
  std::cout << "pset1 full float tests" << std::endl;
  dynFullFloatTest(pset1, FLT_MAX);
  dynFullFloatTest(pset1, 36.7f);
  dynFullFloatTest(pset1, 0.0f);
  dynFullFloatTest(pset1, -240.98f);
  dynFullFloatTest(pset1, FLT_MIN);

  /* double =  Packet2d (half) */
  std::cout << "pset1 half double tests" << std::endl;
  dynHalfDoubleTest(pset1, DBL_MAX);
  dynHalfDoubleTest(pset1, 36.7d);
  dynHalfDoubleTest(pset1, 0.0d);
  dynHalfDoubleTest(pset1, -240.98d);
  dynHalfDoubleTest(pset1, DBL_MIN);

  /* double = Packet4d (full) */
  std::cout << "pset1 full double tests" << std::endl;
  dynFullDoubleTest(pset1, DBL_MAX);
  dynFullDoubleTest(pset1, 36.7d);
  dynFullDoubleTest(pset1, 0.0d);
  dynFullDoubleTest(pset1, -240.98d);
  dynFullDoubleTest(pset1, DBL_MIN);

  /* int = Packet4i (half) */
  std::cout << "pset1 half int tests" << std::endl;
  dynHalfIntTest(pset1, INT_MAX);
  dynHalfIntTest(pset1, 36);
  dynHalfIntTest(pset1, 0);
  dynHalfIntTest(pset1, -240);
  dynHalfIntTest(pset1, INT_MIN);

  /* int = Packet8i (full) */
  std::cout << "pset1 full int tests" << std::endl;
  dynFullIntTest(pset1, INT_MAX);
  dynFullIntTest(pset1, 36);
  dynFullIntTest(pset1, 0);
  dynFullIntTest(pset1, -240);
  dynFullIntTest(pset1, INT_MIN);

  /* bool = Packet16b */
  std::cout << "pset1 bool tests" << std::endl;
  dynHalfBoolTest(pset1, true);
  dynHalfBoolTest(pset1, false);
  dynHalfBoolTest(pset1, CHAR_MAX);
  dynHalfBoolTest(pset1, CHAR_MIN);

  /* Eigen::half = Packet8h */
  std::cout << "pset1 Eigen::half tests" << std::endl;
  dynHalfEigenHalfTest(pset1, half(FLT_MAX));
  dynHalfEigenHalfTest(pset1, half(36.7f));
  dynHalfEigenHalfTest(pset1, half(0.0f));
  dynHalfEigenHalfTest(pset1, half(-240.98f));
  dynHalfEigenHalfTest(pset1, half(FLT_MIN));

  /* bfloat16 = Packet8bf */
  std::cout << "pset1 bfloat16 tests" << std::endl;
  dynHalfBfloat16Test(pset1, bfloat16(FLT_MAX));
  dynHalfBfloat16Test(pset1, bfloat16(36.7f));
  dynHalfBfloat16Test(pset1, bfloat16(0.0f));
  dynHalfBfloat16Test(pset1, bfloat16(-240.98f));
  dynHalfBfloat16Test(pset1, bfloat16(FLT_MIN));

}

#endif  // EIGEN_MIPP_PSET1_TEST_H
