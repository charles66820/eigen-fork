#ifndef EIGEN_MIPP_TEST_UTIL_H
#define EIGEN_MIPP_TEST_UTIL_H

#include <iostream>
#include <Eigen/Core>

using namespace Eigen::internal;
using namespace Eigen;

#ifndef VERBOSE
#define VERBOSE false
#endif  // VERBOSE

// prints
template <typename T>
void printWhenDiff(std::string msg, mipp::Reg<T> reg, mipp::Reg<T> reg_old) {
  if (!mipp::testz(reg != reg_old) || VERBOSE)
    std::cout << "diff for " << msg << " : " << std::endl
              << "old " << reg_old << std::endl
              << "new " << reg << std::endl
              << std::endl;
}

template <typename T>
void printWhenDiff(std::string msg, mipp::Reg_2<T> reg, mipp::Reg_2<T> reg_old) {
  mipp::Reg<T> rf0 = 0.0;
  mipp::Reg_2<T> rf0_h = rf0.low();

  printWhenDiff(msg, mipp::combine(reg, rf0_h), mipp::combine(reg_old, rf0_h));
}

// code inspered by
// https://stackoverflow.com/questions/22964799/how-to-print-a-variable-number-of-parameters-with-a-macro
#define to_sting(...) function(__VA_ARGS__)

template <typename Arg1>
std::string function(Arg1&& arg1) {
  std::stringstream stream;
  stream << arg1;
  return stream.str();
}

template <typename Arg1, typename... Args>
std::string function(Arg1&& arg1, Args&&... args) {
  std::stringstream stream;
  stream << arg1;
  return stream.str() + ", " + function(args...);
}

// Tests macro structure
#define dymOneTypeFullTest(type, full, fullCast, name, args...)                   \
  {                                                                               \
    mipp::Reg<type> rFull = fullCast name<full>(args);                            \
    mipp::Reg<type> rFull_old = fullCast name<full>(args);                        \
    printWhenDiff(#name "<" #full ">(" + to_sting(args) + ")", rFull, rFull_old); \
  }

#define dymOneTypeHalfTest(type, half, halfCast, name, args...)                   \
  {                                                                               \
    mipp::Reg_2<type> rHalf = halfCast name<half>(args);                          \
    mipp::Reg_2<type> rHalf_old = halfCast name<half>(args);                      \
    printWhenDiff(#name "<" #half ">(" + to_sting(args) + ")", rHalf, rHalf_old); \
  }

#define dymTwoTypeTest(type, half, halfCast, full, fullCast, name, args...)              \
  {                                                                                      \
    mipp::Reg_2<type> rHalf = halfCast name<half>(args);                                 \
    mipp::Reg_2<type> rHalf_old = halfCast name<half>(args);                             \
    printWhenDiff(#name "<" #half ">(" + to_sting(args) + ") (half)", rHalf, rHalf_old); \
                                                                                         \
    mipp::Reg<type> rFull = fullCast name<full>(args);                                   \
    mipp::Reg<type> rFull_old = fullCast name<full>(args);                               \
    printWhenDiff(#name "<" #full ">(" + to_sting(args) + ") (full)", rFull, rFull_old); \
  }

// Tests macro definition

#define dymLongTest(name, args...) dymOneTypeFullTest(long, Packet4l, (mipp::reg)(__m256i), name, args)

#define dymFloatTest(name, args...) dymTwoTypeTest(float, Packet4f, , Packet8f, , name, args)
#define dymDoubleTest(name, args...) dymTwoTypeTest(double, Packet2d, (mipp::reg_2), Packet4d, (mipp::reg), name, args)
#define dymIntTest(name, args...) \
  dymTwoTypeTest(int, Packet4i, (mipp::reg_2)(__m128i), Packet8i, (mipp::reg)(__m256i), name, args)

#define dymBoolTest(name, args...) dymOneTypeHalfTest(int, Packet16b, (mipp::reg_2)(__m128i), name, args)
#define dymEigenHalfTest(name, args...) dymOneTypeHalfTest(short, Packet8h, (mipp::reg_2)(__m128i), name, args)
#define dymBfloat16Test(name, args...) dymOneTypeHalfTest(short, Packet8bf, (mipp::reg_2)(__m128i), name, args)

#endif  // EIGEN_MIPP_TEST_UTIL_H