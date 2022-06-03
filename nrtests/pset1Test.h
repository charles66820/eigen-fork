#include <float.h>
#include <limits.h>

#ifndef EIGEN_MIPP_PSET1_TEST_H
#define EIGEN_MIPP_PSET1_TEST_H

void pset1Tests() {
  /* long = Packet4l */
  std::cout << "pset1 long tests" << std::endl;
  dymLongTest(pset1, LONG_MAX);
  dymLongTest(pset1, 36L);
  dymLongTest(pset1, 0L);
  dymLongTest(pset1, -240L);
  dymLongTest(pset1, LONG_MIN);

  /* float = half : Packet4f, full : Packet8f */
  std::cout << "pset1 float tests" << std::endl;
  dymFloatTest(pset1, FLT_MAX);
  dymFloatTest(pset1, 36.7f);
  dymFloatTest(pset1, 0.0f);
  dymFloatTest(pset1, -240.98f);
  dymFloatTest(pset1, FLT_MIN);
  /* double = half : Packet2d, full : Packet4d */
  std::cout << "pset1 double tests" << std::endl;
  dymDoubleTest(pset1, DBL_MAX);
  dymDoubleTest(pset1, 36.7d);
  dymDoubleTest(pset1, 0.0d);
  dymDoubleTest(pset1, -240.98d);
  dymDoubleTest(pset1, DBL_MIN);

  /* int = half : Packet4i, full : Packet8i */
  std::cout << "pset1 int tests" << std::endl;
  dymIntTest(pset1, INT_MAX);
  dymIntTest(pset1, 36);
  dymIntTest(pset1, 0);
  dymIntTest(pset1, -240);
  dymIntTest(pset1, INT_MIN);

  /* bool = Packet16b */
  std::cout << "pset1 bool tests" << std::endl;
  dymBoolTest(pset1, true);
  dymBoolTest(pset1, false);
  dymBoolTest(pset1, CHAR_MAX);
  dymBoolTest(pset1, CHAR_MIN);

  /* Eigen::half = Packet8h */
  std::cout << "pset1 Eigen::half tests" << std::endl;
  dymEigenHalfTest(pset1, half(FLT_MAX));
  dymEigenHalfTest(pset1, half(36.7f));
  dymEigenHalfTest(pset1, half(0.0f));
  dymEigenHalfTest(pset1, half(-240.98f));
  dymEigenHalfTest(pset1, half(FLT_MIN));

  /* bfloat16 = Packet8bf */
  std::cout << "pset1 bfloat16 tests" << std::endl;
  dymBfloat16Test(pset1, bfloat16(FLT_MAX));
  dymBfloat16Test(pset1, bfloat16(36.7f));
  dymBfloat16Test(pset1, bfloat16(0.0f));
  dymBfloat16Test(pset1, bfloat16(-240.98f));
  dymBfloat16Test(pset1, bfloat16(FLT_MIN));

}

#endif // EIGEN_MIPP_PSET1_TEST_H
