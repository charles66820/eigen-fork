#include <float.h>
#include <limits.h>

#ifndef EIGEN_MIPP_PSET1_TEST_H
#define EIGEN_MIPP_PSET1_TEST_H

void pset1LongTest(long val) {
  mipp::Reg<long> rFull = (mipp::reg)(__m256i) pset1<Packet4l>(val);
  mipp::Reg<long> rFull_old = (mipp::reg)(__m256i)pset1_old<Packet4l>(val);
  printWhenDiff("pset1<Packet4l>", val, rFull, rFull_old);
}

void pset1FloatTest(float val) {
  mipp::Reg_2<float> rHalf = pset1<Packet4f>(val);
  mipp::Reg_2<float> rHalf_old = pset1_old<Packet4f>(val);
  printWhenDiff("pset1<Packet4f> (half)", val, rHalf, rHalf_old);

  mipp::Reg<float> rFull = pset1<Packet8f>(val);
  mipp::Reg<float> rFull_old = pset1_old<Packet8f>(val);
  printWhenDiff("pset1<Packet8f> (full)", val, rFull, rFull_old);
}

void pset1DoubleTest(double val) {
  mipp::Reg_2<double> rHalf = (mipp::reg_2)pset1<Packet2d>(val);
  mipp::Reg_2<double> rHalf_old = (mipp::reg_2)pset1_old<Packet2d>(val);
  printWhenDiff("pset1<Packet2d> (half)", val, rHalf, rHalf_old);

  mipp::Reg<double> rFull = (mipp::reg)pset1<Packet4d>(val);
  mipp::Reg<double> rFull_old = (mipp::reg)pset1_old<Packet4d>(val);
  printWhenDiff("pset1<Packet4d> (full)", val, rFull, rFull_old);
}

void pset1IntTest(int val) {
  mipp::Reg_2<int> rHalf = (mipp::reg_2)(__m128i)pset1<Packet4i>(val);
  mipp::Reg_2<int> rHalf_old = (mipp::reg_2)(__m128i)pset1_old<Packet4i>(val);
  printWhenDiff("pset1<Packet4i> (half)", val, rHalf, rHalf_old);

  mipp::Reg<int> rFull = (mipp::reg)(__m256i)pset1<Packet8i>(val);
  mipp::Reg<int> rFull_old = (mipp::reg)(__m256i)pset1_old<Packet8i>(val);
  printWhenDiff("pset1<Packet8i> (full)", val, rFull, rFull_old);
}

void pset1BoolTest(int val) {
  mipp::Reg_2<int> rFull = (mipp::reg_2)(__m128i)pset1<Packet16b>(val);
  mipp::Reg_2<int> rFull_old = (mipp::reg_2)(__m128i)pset1_old<Packet16b>(val);
  printWhenDiff("pset1<Packet16b>", val, rFull, rFull_old);
}

void pset1EigenHalfTest(Eigen::half val) {
  mipp::Reg_2<short> rFull = (mipp::reg_2)(__m128i)pset1<Packet8h>(val);
  mipp::Reg_2<short> rFull_old = (mipp::reg_2)(__m128i)pset1_old<Packet8h>(val);
  printWhenDiff("pset1<Packet8h>", (short)val, rFull, rFull_old);
}

void pset1Bfloat16Test(bfloat16 val) {
  mipp::Reg_2<short> rFull = (mipp::reg_2)(__m128i)pset1<Packet8bf>(val);
  mipp::Reg_2<short> rFull_old = (mipp::reg_2)(__m128i)pset1_old<Packet8bf>(val);
  printWhenDiff("pset1<Packet8bf>", (short)val, rFull, rFull_old);
}

void pset1Tests() {
  /* long = Packet4l */
  std::cout << "pset1 long tests" << std::endl;
  pset1LongTest(LONG_MAX);
  pset1LongTest(36.7L);
  pset1LongTest(0.0L);
  pset1LongTest(-240.98L);
  pset1LongTest(LONG_MIN);

  /* float = half : Packet4f, full : Packet8f */
  std::cout << "pset1 float tests" << std::endl;
  pset1FloatTest(FLT_MAX);
  pset1FloatTest(36.7f);
  pset1FloatTest(0.0f);
  pset1FloatTest(-240.98f);
  pset1FloatTest(FLT_MIN);

  /* double = half : Packet2d, full : Packet4d */
  std::cout << "pset1 double tests" << std::endl;
  pset1DoubleTest(DBL_MAX);
  pset1DoubleTest(36.7d);
  pset1DoubleTest(0.0d);
  pset1DoubleTest(-240.98d);
  pset1DoubleTest(DBL_MIN);

  /* int = half : Packet4i, full : Packet8i */
  std::cout << "pset1 int tests" << std::endl;
  pset1IntTest(INT_MAX);
  pset1IntTest(36);
  pset1IntTest(0);
  pset1IntTest(-240);
  pset1IntTest(INT_MIN);

  /* bool = Packet16b */
  std::cout << "pset1 bool tests" << std::endl;
  pset1BoolTest(true);
  pset1BoolTest(false);
  pset1BoolTest(CHAR_MAX);
  pset1BoolTest(CHAR_MIN);

  /* Eigen::half = Packet8h */
  std::cout << "pset1 Eigen::half tests" << std::endl;
  pset1EigenHalfTest(half(FLT_MAX));
  pset1EigenHalfTest(half(36.7f));
  pset1EigenHalfTest(half(0.0f));
  pset1EigenHalfTest(half(-240.98f));
  pset1EigenHalfTest(half(FLT_MIN));

  /* bfloat16 = Packet8bf */
  std::cout << "pset1 bfloat16 tests" << std::endl;
  bfloat16 valbf16[8] = { bfloat16(0), bfloat16(1), bfloat16(2), bfloat16(3),
                          bfloat16(4), bfloat16(5), bfloat16(6), bfloat16(7) };
  pset1Bfloat16Test(*valbf16);

#endif // EIGEN_MIPP_PSET1_TEST_H
