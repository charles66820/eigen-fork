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
#define to_sting(...) toString(__VA_ARGS__)

template <typename Arg1>
std::string toString(Arg1 arg1) {
  return "?";
}

#define printableToString(type)           \
  template <>                             \
  std::string toString<type>(type arg1) { \
    std::stringstream stream;             \
    stream << arg1;                       \
    return stream.str();                  \
  }

printableToString(bool);
printableToString(short);
printableToString(int);
printableToString(long);
printableToString(float);
printableToString(double);
printableToString(Eigen::half);
printableToString(bfloat16);

template <typename Arg1, typename... Args>
std::string toString(Arg1 arg1, Args... args) {
  return toString(arg1) + ", " + toString(args...);
}

// Tests macro structure
#define dynOneTypeFullTest(type, full, fullCast, name, args...)                   \
  {                                                                               \
    mipp::Reg<type> rFull = fullCast name<full>(args);                            \
    mipp::Reg<type> rFull_old = fullCast name<full>(args);                        \
    printWhenDiff(#name "<" #full ">(" + to_sting(args) + ")", rFull, rFull_old); \
  }

#define dynOneTypeHalfTest(type, half, halfCast, name, args...)                   \
  {                                                                               \
    mipp::Reg_2<type> rHalf = halfCast name<half>(args);                          \
    mipp::Reg_2<type> rHalf_old = halfCast name<half>(args);                      \
    printWhenDiff(#name "<" #half ">(" + to_sting(args) + ")", rHalf, rHalf_old); \
  }

// Tests macro definition
#define dynFullLongTest(name, args...) dynOneTypeFullTest(long, Packet4l, (mipp::reg)(__m256i), name, args)

#define dynHalfFloatTest(name, args...) dynOneTypeHalfTest(float, Packet4f, , name, args)
#define dynHalfDoubleTest(name, args...) dynOneTypeHalfTest(double, Packet2d, (mipp::reg_2), name, args)
#define dynHalfIntTest(name, args...) dynOneTypeHalfTest(int, Packet4i, (mipp::reg_2)(__m128i), name, args)

#define dynFullFloatTest(name, args...) dynOneTypeFullTest(float, Packet8f, , name, args)
#define dynFullDoubleTest(name, args...) dynOneTypeFullTest(double, Packet4d, (mipp::reg), name, args)
#define dynFullIntTest(name, args...) dynOneTypeFullTest(int, Packet8i, (mipp::reg)(__m256i), name, args)

#define dynHalfBoolTest(name, args...) dynOneTypeHalfTest(int, Packet16b, (mipp::reg_2)(__m128i), name, args)
#define dynHalfEigenHalfTest(name, args...) dynOneTypeHalfTest(short, Packet8h, (mipp::reg_2)(__m128i), name, args)
#define dynHalfBfloat16Test(name, args...) dynOneTypeHalfTest(short, Packet8bf, (mipp::reg_2)(__m128i), name, args)

#endif  // EIGEN_MIPP_TEST_UTIL_H