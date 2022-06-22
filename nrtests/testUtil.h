#ifndef EIGEN_MIPP_TEST_UTIL_H
#define EIGEN_MIPP_TEST_UTIL_H

#include <iostream>
#include <Eigen/Core>
#include "testString.h"

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

#define beginTest(str) \
  std::cout << str;    \
  hasFailed = false

#define endTest() \
  if (!hasFailed) std::cout << " done" << std::endl;

// prints
bool printWhenDiff(bool isDiffer, std::string msg, std::string newVal, std::string oldVal) {
  if (!hasFailed && isDiffer) std::cout << " failed" << std::endl;

  if (isDiffer || VERBOSE)
    std::cout << "diff for " << msg << " : " << std::endl
              << "old " << oldVal << std::endl
              << "new " << newVal << std::endl
              << std::endl;
  return isDiffer;
}

template <typename T>
bool printWhenRegDiff(std::string msg, mipp::Reg<T> reg, mipp::Reg<T> reg_old) {
  return printWhenDiff(!mipp::testz(reg != reg_old), msg, to_sting(reg), to_sting(reg_old));
}

template <typename T>
bool printWhenRegDiff(std::string msg, mipp::Reg_2<T> reg, mipp::Reg_2<T> reg_old) {
  mipp::Reg<T> rf0 = 0.0;
  mipp::Reg_2<T> rf0_h = rf0.low();

  return printWhenRegDiff(msg, mipp::combine(reg, rf0_h), mipp::combine(reg_old, rf0_h));
}

template <typename T>
bool printWhenTabDiff(std::string msg, T tab[], T tab_old[], size_t size) {
  return printWhenDiff(!std::equal(tab, tab + size, tab_old), msg, toStringTab(tab, size), toStringTab(tab_old, size));
}

template <typename T>
bool printWhenScalarDiff(std::string msg, T scal, T scal_old) {
  return printWhenDiff(scal != scal_old, msg, to_sting(scal), to_sting(scal_old));
}

// Macros for test that return vector
#define vectorSingleTypeTest(MIPP_Reg, type, cast, eigenType, name, args...)                         \
  {                                                                                                  \
    mipp::MIPP_Reg<type> rVar = cast name<eigenType>(args);                                          \
    mipp::MIPP_Reg<type> rVar_old = cast name##_old<eigenType>(args);                                \
    hasFailed |= printWhenRegDiff(#name "<" #eigenType ">(" + to_sting(args) + ")", rVar, rVar_old); \
  }

#define vectorSingleTypeFullTest(type, full, fullCast, name, args...) \
  vectorSingleTypeTest(Reg, type, fullCast, full, name, args)

#define vectorSingleTypeHalfTest(type, half, halfCast, name, args...) \
  vectorSingleTypeTest(Reg_2, type, halfCast, half, name, args)

// Tests macro definition
#define vectorFullLongTemplateTest(template, name, args...) \
  vectorSingleTypeFullTest(long, template, INT_FULL_CAST, name, args)

#define vectorHalfFloatTemplateTest(template, name, args...) vectorSingleTypeHalfTest(float, template, , name, args)
#define vectorHalfDoubleTemplateTest(template, name, args...) \
  vectorSingleTypeHalfTest(double, template, HALF_CAST, name, args)
#define vectorHalfIntTemplateTest(template, name, args...) \
  vectorSingleTypeHalfTest(int, template, INT_HALF_CAST, name, args)

#define vectorFullFloatTemplateTest(template, name, args...) vectorSingleTypeFullTest(float, template, , name, args)
#define vectorFullDoubleTemplateTest(template, name, args...) \
  vectorSingleTypeFullTest(double, template, FULL_CAST, name, args)
#define vectorFullIntTemplateTest(template, name, args...) \
  vectorSingleTypeFullTest(int, template, INT_FULL_CAST, name, args)

#define vectorHalfBoolTemplateTest(template, name, args...) \
  vectorSingleTypeHalfTest(int8_t, template, INT_HALF_CAST, name, args)
#define vectorHalfEigenHalfTemplateTest(template, name, args...) \
  vectorSingleTypeHalfTest(short, template, INT_HALF_CAST, name, args)
#define vectorHalfBfloat16TemplateTest(template, name, args...) \
  vectorSingleTypeHalfTest(short, template, INT_HALF_CAST, name, args)

#define vectorFullLongTest(name, args...) vectorFullLongTemplateTest(Packet4l, name, args)

#define vectorHalfFloatTest(name, args...) vectorHalfFloatTemplateTest(Packet4f, name, args)
#define vectorHalfDoubleTest(name, args...) vectorHalfDoubleTemplateTest(Packet2d, name, args)
#define vectorHalfIntTest(name, args...) vectorHalfIntTemplateTest(Packet4i, name, args)

#define vectorFullFloatTest(name, args...) vectorFullFloatTemplateTest(Packet8f, name, args)
#define vectorFullDoubleTest(name, args...) vectorFullDoubleTemplateTest(Packet4d, name, args)
#define vectorFullIntTest(name, args...) vectorFullIntTemplateTest(Packet8i, name, args)

#define vectorHalfBoolTest(name, args...) vectorHalfBoolTemplateTest(Packet16b, name, args)
#define vectorHalfEigenHalfTest(name, args...) vectorHalfEigenHalfTemplateTest(Packet8h, name, args)
#define vectorHalfBfloat16Test(name, args...) vectorHalfBfloat16TemplateTest(Packet8bf, name, args)

// Macros for test that return vector
#define refSingleTypeGenericTest(name, type, size, attr, args...)                                 \
  {                                                                                               \
    type to[size] attr;                                                                           \
    memset(to, 0, sizeof to);                                                                     \
    type to_old[size] attr;                                                                       \
    memset(to_old, 0, sizeof to_old);                                                             \
                                                                                                  \
    name<type>(to, args);                                                                         \
    name##_old<type>(to_old, args);                                                               \
    hasFailed |= printWhenTabDiff(#name "<" #type ">(" + to_sting(args) + ")", to, to_old, size); \
  }

#define refSingleType(name, type, size, args...) \
  refSingleTypeGenericTest(name, type, size, __attribute__((aligned(32))), args)

#define uRefSingleType(name, type, size, args...) refSingleTypeGenericTest(name, type, size, , args)

// Macros for test that return scalar
#define scalarSingleTypeGenericTest(type, name, eigenType, args...)                                   \
  {                                                                                                   \
    type val = name<eigenType>(args);                                                                 \
    type val_old = name##_old<eigenType>(args);                                                       \
    hasFailed |= printWhenScalarDiff(#name "<" #eigenType ">(" + to_sting(args) + ")", val, val_old); \
  }

#define scalarSingleTypeTest(type, name, eigenType, args...) scalarSingleTypeGenericTest(type, name, eigenType, args)

#endif  // EIGEN_MIPP_TEST_UTIL_H