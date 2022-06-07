#include <float.h>
#include <limits.h>

#ifndef EIGEN_MIPP_PZERO_TEST_H
#define EIGEN_MIPP_PZERO_TEST_H

void pzeroLongTest() {
  Packet4l a;
  mipp::Reg<long> rFull = (mipp::reg)(__m256i)pzero<Packet4l>(a);
  mipp::Reg<long> rFull_old = (mipp::reg)(__m256i)pzero_old<Packet4l>(a);
  printWhenDiff("pzero<Packet4l>", rFull, rFull_old);
}

void pzeroFloatTest() {
  Packet4f ah;
  mipp::Reg_2<float> rHalf = pzero<Packet4f>(ah);
  mipp::Reg_2<float> rHalf_old = pzero_old<Packet4f>(ah);
  printWhenDiff("pzero<Packet4f> (half)", rHalf, rHalf_old);

  Packet8f a;
  mipp::Reg<float> rFull = pzero<Packet8f>(a);
  mipp::Reg<float> rFull_old = pzero_old<Packet8f>(a);
  printWhenDiff("pzero<Packet8f> (full)", rFull, rFull_old);
}

void pzeroDoubleTest() {
  Packet2d ah;
  mipp::Reg_2<double> rHalf = (mipp::reg_2)pzero<Packet2d>(ah);
  mipp::Reg_2<double> rHalf_old = (mipp::reg_2)pzero_old<Packet2d>(ah);
  printWhenDiff("pzero<Packet2d> (half)", rHalf, rHalf_old);

  Packet4d a;
  mipp::Reg<double> rFull = (mipp::reg)pzero<Packet4d>(a);
  mipp::Reg<double> rFull_old = (mipp::reg)pzero_old<Packet4d>(a);
  printWhenDiff("pzero<Packet4d> (full)", rFull, rFull_old);
}

void pzeroIntTest() {
  Packet4i ah;
  mipp::Reg_2<int> rHalf = (mipp::reg_2)(__m128i)pzero<Packet4i>(ah);
  mipp::Reg_2<int> rHalf_old = (mipp::reg_2)(__m128i)pzero_old<Packet4i>(ah);
  printWhenDiff("pzero<Packet4i> (half)", rHalf, rHalf_old);

  Packet8i a;
  mipp::Reg<int> rFull = (mipp::reg)(__m256i)pzero<Packet8i>(a);
  mipp::Reg<int> rFull_old = (mipp::reg)(__m256i)pzero_old<Packet8i>(a);
  printWhenDiff("pzero<Packet8i> (full)", rFull, rFull_old);
}

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
