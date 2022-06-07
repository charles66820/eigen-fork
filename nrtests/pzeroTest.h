#include <float.h>
#include <limits.h>

#ifndef EIGEN_MIPP_PZERO_TEST_H
#define EIGEN_MIPP_PZERO_TEST_H

void pzeroTests() {
  /* long = Packet4l */
  std::cout << "pzero half long tests" << std::endl;
  Packet4l a;
  dynFullLongTest(pzero, a);

  /* float = Packet4f (half) */
  std::cout << "pzero half float tests" << std::endl;
  Packet4f bh;
  dynHalfFloatTest(pzero, bh);

  /* float = Packet8f (full) */
  std::cout << "pzero full float tests" << std::endl;
  Packet8f b;
  dynFullFloatTest(pzero, b);

  /* double = Packet2d (half) */
  std::cout << "pzero half double tests" << std::endl;
  Packet2d ch;
  dynHalfDoubleTest(pzero, ch);

  /* double = Packet4d (full) */
  std::cout << "pzero full double tests" << std::endl;
  Packet4d c;
  dynFullDoubleTest(pzero, c);

  /* int = Packet4i (half) */
  std::cout << "pzero half int tests" << std::endl;
  Packet4i dh;
  dynHalfIntTest(pzero, dh);

  /* int = Packet8i (full) */
  std::cout << "pzero full int tests" << std::endl;
  Packet8i d;
  dynFullIntTest(pzero, d);
}

#endif  // EIGEN_MIPP_PZERO_TEST_H
