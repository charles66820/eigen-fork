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
#define dynFullLongTemplateTest(template, name, args...) dynOneTypeFullTest(long, template, INT_FULL_CAST, name, args)

#define dynHalfFloatTemplateTest(template, name, args...) dynOneTypeHalfTest(float, template, , name, args)
#define dynHalfDoubleTemplateTest(template, name, args...) dynOneTypeHalfTest(double, template, HALF_CAST, name, args)
#define dynHalfIntTemplateTest(template, name, args...) dynOneTypeHalfTest(int, template, INT_HALF_CAST, name, args)

#define dynFullFloatTemplateTest(template, name, args...) dynOneTypeFullTest(float, template, , name, args)
#define dynFullDoubleTemplateTest(template, name, args...) dynOneTypeFullTest(double, template, FULL_CAST, name, args)
#define dynFullIntTemplateTest(template, name, args...) dynOneTypeFullTest(int, template, INT_FULL_CAST, name, args)

#define dynHalfBoolTemplateTest(template, name, args...) dynOneTypeHalfTest(int8_t, template, INT_HALF_CAST, name, args)
#define dynHalfEigenHalfTemplateTest(template, name, args...) \
  dynOneTypeHalfTest(short, template, INT_HALF_CAST, name, args)
#define dynHalfBfloat16TemplateTest(template, name, args...) \
  dynOneTypeHalfTest(short, template, INT_HALF_CAST, name, args)

#define dynFullLongTest(name, args...) dynFullLongTemplateTest(Packet4l, name, args)

#define dynHalfFloatTest(name, args...) dynHalfFloatTemplateTest(Packet4f, name, args)
#define dynHalfDoubleTest(name, args...) dynHalfDoubleTemplateTest(Packet2d, name, args)
#define dynHalfIntTest(name, args...) dynHalfIntTemplateTest(Packet4i, name, args)

#define dynFullFloatTest(name, args...) dynFullFloatTemplateTest(Packet8f, name, args)
#define dynFullDoubleTest(name, args...) dynFullDoubleTemplateTest(Packet4d, name, args)
#define dynFullIntTest(name, args...) dynFullIntTemplateTest(Packet8i, name, args)

#define dynHalfBoolTest(name, args...) dynHalfBoolTemplateTest(Packet16b, name, args)
#define dynHalfEigenHalfTest(name, args...) dynHalfEigenHalfTemplateTest(Packet8h, name, args)
#define dynHalfBfloat16Test(name, args...) dynHalfBfloat16TemplateTest(Packet8bf, name, args)

// test and print for tab
template <typename T>
std::string toStringTab(T *tab, size_t size) {
  std::stringstream stream;
  stream << "[";

  for (size_t i = 0; i < size; i++) {
    if (i != 0) stream << ", ";
    stream << tab[i];
  }

  stream << "]";
  return stream.str();
}

template <typename T>
bool printWhenTabDiff(std::string msg, T tab[], T tab_old[], size_t size) {
  bool isDiffer = !std::equal(tab, tab + size, tab_old);

  if (!hasFailed && isDiffer) std::cout << " failed" << std::endl;

  if (isDiffer || VERBOSE)
    std::cout << "diff for " << msg << " : " << std::endl
              << "old " << toStringTab(tab_old, size) << std::endl
              << "new " << toStringTab(tab, size) << std::endl
              << std::endl;
  return isDiffer;
}

#define tabTypeSizeTest(name, type, size, args...)                                                \
  {                                                                                               \
    type to[size] __attribute__((aligned(32)));                                                   \
    memset(to, 0, sizeof to);                                                                     \
    type to_old[size] __attribute__((aligned(32)));                                               \
    memset(to_old, 0, sizeof to_old);                                                             \
                                                                                                  \
    name<type>(to, args);                                                                         \
    name##_old<type>(to_old, args);                                                               \
    hasFailed |= printWhenTabDiff(#name "<" #type ">(" + to_sting(args) + ")", to, to_old, size); \
  }
#define tabTypeTest(name, type, size, args...) tabTypeSizeTest(name, type, size, args)

#define tabuTypeSizeTest(name, type, size, args...)                                               \
  {                                                                                               \
    type to[size];                                                                                \
    memset(to, 0, sizeof to);                                                                     \
    type to_old[size];                                                                            \
    memset(to_old, 0, sizeof to_old);                                                             \
                                                                                                  \
    name<type>(to, args);                                                                         \
    name##_old<type>(to_old, args);                                                               \
    hasFailed |= printWhenTabDiff(#name "<" #type ">(" + to_sting(args) + ")", to, to_old, size); \
  }
#define tabuTypeTest(name, type, size, args...) tabuTypeSizeTest(name, type, size, args)

#endif  // EIGEN_MIPP_TEST_UTIL_H