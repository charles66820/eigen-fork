#include <float.h>
#include <limits.h>

#ifndef EIGEN_MIPP_PZERO_TEST_H
#define EIGEN_MIPP_PZERO_TEST_H

#undef FUN2TEST
#define FUN2TEST pzero

#define str(s) #s
#define xstr(s) str(s)

void pzeroTests() {
  std::cout << xstr(FUN2TEST) << " :" << std::endl;

  /* long = Packet4l */
  std::cout << "long tests" << std::endl;
  Packet4l a;
  dynFullLongTest(FUN2TEST, a);

  /* float = Packet4f (half) */
  std::cout << "half float tests" << std::endl;
  Packet4f bh;
  dynHalfFloatTest(FUN2TEST, bh);

  /* float = Packet8f (full) */
  std::cout << "full float tests" << std::endl;
  Packet8f b;
  dynFullFloatTest(FUN2TEST, b);

  /* double = Packet2d (half) */
  std::cout << "half double tests" << std::endl;
  Packet2d ch;
  dynHalfDoubleTest(FUN2TEST, ch);

  /* double = Packet4d (full) */
  std::cout << "full double tests" << std::endl;
  Packet4d c;
  dynFullDoubleTest(FUN2TEST, c);

  /* int = Packet4i (half) */
  std::cout << "half int tests" << std::endl;
  Packet4i dh;
  dynHalfIntTest(FUN2TEST, dh);

  /* int = Packet8i (full) */
  std::cout << "full int tests" << std::endl;
  Packet8i d;
  dynFullIntTest(FUN2TEST, d);
}

#endif  // EIGEN_MIPP_PZERO_TEST_H
