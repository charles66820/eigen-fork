#ifndef EIGEN_MIPP_TEST_UTIL_H
#define EIGEN_MIPP_TEST_UTIL_H

#include <iostream>
#include <Eigen/Core>

using namespace Eigen::internal;
using namespace Eigen;

#ifndef VERBOSE
#define VERBOSE false
#endif  // VERBOSE

#define HALF_CAST (mipp::reg_2)
#define FULL_CAST (mipp::reg)
#define INT_HALF_CAST HALF_CAST(__m128i)
#define INT_FULL_CAST FULL_CAST(__m256i)

#define TO_STRING(s) #s
#define printTestTitle(t) "================ " TO_STRING(t) " ================"

// Return test state
bool hasFailed = false;

void resetFail() { hasFailed = false; }

#define beginTest(str) \
  std::cout << str;    \
  resetFail();

#define endTest() \
  if (!hasFailed) std::cout << " done" << std::endl;

// prints
template <typename T>
bool printWhenDiff(std::string msg, mipp::Reg<T> reg, mipp::Reg<T> reg_old) {
  bool isDiffer = !mipp::testz(reg != reg_old);

  if (!hasFailed && isDiffer) std::cout << " failed" << std::endl;

  if (isDiffer || VERBOSE)
    std::cout << "diff for " << msg << " : " << std::endl
              << "old " << reg_old << std::endl
              << "new " << reg << std::endl
              << std::endl;
  return isDiffer;
}

template <typename T>
bool printWhenDiff(std::string msg, mipp::Reg_2<T> reg, mipp::Reg_2<T> reg_old) {
  mipp::Reg<T> rf0 = 0.0;
  mipp::Reg_2<T> rf0_h = rf0.low();

  return printWhenDiff(msg, mipp::combine(reg, rf0_h), mipp::combine(reg_old, rf0_h));
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
#define dynOneTypeTest(MIPP_Reg, type, cast, eigenType, name, args...)                            \
  {                                                                                               \
    mipp::MIPP_Reg<type> rVar = cast name<eigenType>(args);                                       \
    mipp::MIPP_Reg<type> rVar_old = cast name##_old<eigenType>(args);                             \
    hasFailed |= printWhenDiff(#name "<" #eigenType ">(" + to_sting(args) + ")", rVar, rVar_old); \
  }

#define dynOneTypeFullTest(type, full, fullCast, name, args...) dynOneTypeTest(Reg, type, fullCast, full, name, args)

#define dynOneTypeHalfTest(type, half, halfCast, name, args...) dynOneTypeTest(Reg_2, type, halfCast, half, name, args)

// Tests macro definition
#define dynFullLongTest(name, args...) dynOneTypeFullTest(long, Packet4l, INT_FULL_CAST, name, args)

#define dynHalfFloatTest(name, args...) dynOneTypeHalfTest(float, Packet4f, , name, args)
#define dynHalfDoubleTest(name, args...) dynOneTypeHalfTest(double, Packet2d, HALF_CAST, name, args)
#define dynHalfIntTest(name, args...) dynOneTypeHalfTest(int, Packet4i, INT_HALF_CAST, name, args)

#define dynFullFloatTest(name, args...) dynOneTypeFullTest(float, Packet8f, , name, args)
#define dynFullDoubleTest(name, args...) dynOneTypeFullTest(double, Packet4d, FULL_CAST, name, args)
#define dynFullIntTest(name, args...) dynOneTypeFullTest(int, Packet8i, INT_FULL_CAST, name, args)

#define dynHalfBoolTest(name, args...) dynOneTypeHalfTest(int, Packet16b, INT_HALF_CAST, name, args)
#define dynHalfEigenHalfTest(name, args...) dynOneTypeHalfTest(short, Packet8h, INT_HALF_CAST, name, args)
#define dynHalfBfloat16Test(name, args...) dynOneTypeHalfTest(short, Packet8bf, INT_HALF_CAST, name, args)

#endif  // EIGEN_MIPP_TEST_UTIL_H