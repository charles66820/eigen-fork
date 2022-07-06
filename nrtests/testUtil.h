#ifndef EIGEN_MIPP_TEST_UTIL_H
#define EIGEN_MIPP_TEST_UTIL_H

#include <iostream>
#include <Eigen/Core>
#include "testCombinations.h"

using namespace Eigen::internal;
using namespace Eigen;

#ifndef VERBOSE
#define VERBOSE false
#endif  // VERBOSE

// Cast
#define MIPP_CAST (mipp::reg)

#ifdef __AVX512F__

#define INT_CAST_128_TO_MIPP_REG_T MIPP_CAST(__m512i) _mm512_castsi128_si512
#define INT_CAST_256_TO_MIPP_REG_T MIPP_CAST(__m512i) _mm512_castsi256_si512
#define INT_CAST_512_TO_MIPP_REG_T MIPP_CAST(__m512i)
#define FLOAT_CAST_128_TO_MIPP_REG_T MIPP_CAST _mm512_castps128_ps512
#define FLOAT_CAST_256_TO_MIPP_REG_T MIPP_CAST _mm512_castps256_ps512
#define FLOAT_CAST_512_TO_MIPP_REG_T MIPP_CAST
#define DOUBLE_CAST_128_TO_MIPP_REG_T MIPP_CAST(__m512d) _mm512_castpd128_pd512
#define DOUBLE_CAST_256_TO_MIPP_REG_T MIPP_CAST(__m512d) _mm512_castpd256_pd512
#define DOUBLE_CAST_512_TO_MIPP_REG_T MIPP_CAST(__m512d)

#elif defined(__AVX__)

#define INT_CAST_128_TO_MIPP_REG_T MIPP_CAST(__m256i) _mm256_castsi128_si256
#define INT_CAST_256_TO_MIPP_REG_T MIPP_CAST(__m256i)
#define FLOAT_CAST_128_TO_MIPP_REG_T MIPP_CAST _mm256_castps128_ps256
#define FLOAT_CAST_256_TO_MIPP_REG_T MIPP_CAST
#define DOUBLE_CAST_128_TO_MIPP_REG_T MIPP_CAST(__m256d) _mm256_castpd128_pd256
#define DOUBLE_CAST_256_TO_MIPP_REG_T MIPP_CAST(__m256d)

#elif defined(__SSE__)

#define INT_CAST_128_TO_MIPP_REG_T MIPP_CAST(__m128i)
#define FLOAT_CAST_128_TO_MIPP_REG_T MIPP_CAST
#define DOUBLE_CAST_128_TO_MIPP_REG_T MIPP_CAST(__m128d)

#endif

#define COMMA ,

#include "testString.h"

#define TO_STRING(s) #s
#if defined(DISABLE_PRINTING) && DISABLE_PRINTING == 1
#define printTestTitle(t)
#else
#define printTestTitle(t) std::cout << "================ " TO_STRING(t) " ================" << std::endl;
#endif

// Return test state
bool hasFailed = false;
bool hasFailedGlobal = false;
typedef void (*test_fun)();
static std::vector<test_fun> testFunctions;

#if defined(DISABLE_PRINTING) && DISABLE_PRINTING == 1
#define beginTest(str) \
  hasFailed = false

#define endTest() \
  hasFailedGlobal |= hasFailed;
#else
#define beginTest(str) \
  std::cout << str;    \
  hasFailed = false

#define endTest() \
  if (!hasFailed) std::cout << " done" << std::endl; \
  hasFailedGlobal |= hasFailed;
#endif

// auto run tests
int addTest2list(test_fun fun) {
  testFunctions.push_back(fun);
  return 0;
}

#define addTest_imp(name) static int name##res = addTest2list(name##Tests);
#define addTest(name) addTest_imp(name)

#define executeTest() \
  for (auto fun : testFunctions) fun();

// prints
bool printWhenDiff(bool isDiffer, std::string msg, std::string newVal, std::string oldVal) {
#if !defined(DISABLE_PRINTING) || DISABLE_PRINTING == 0
  if (!hasFailed && isDiffer) std::cout << " failed" << std::endl;

  if (isDiffer || VERBOSE)
    std::cout << "diff for " << msg << " : " << std::endl
              << "old " << oldVal << std::endl
              << "new " << newVal << std::endl
              << std::endl;
#endif
  return isDiffer;
}

// Macros for test that return vector
#define vectorSingleTypeTest(type, cast, name, eigenType, args...)                                                \
  {                                                                                                               \
    mipp::Reg<type> rVar = cast(name<eigenType>(args));                                                           \
    mipp::Reg<type> rVar_old = cast(name##_old<eigenType>(args));                                                 \
    hasFailed |= printWhenDiff(!mipp::testz(rVar != rVar_old), #name "<" #eigenType ">(" + to_string(args) + ")", \
                               to_string(rVar), to_string(rVar_old));                                             \
  }

// Macros for test that return vector
#define refSingleTypeGenericTest(type, name, eigenType, size, attr, args...)                                     \
  {                                                                                                              \
    type to[size] attr;                                                                                          \
    memset(to, 0, sizeof to);                                                                                    \
    type to_old[size] attr;                                                                                      \
    memset(to_old, 0, sizeof to_old);                                                                            \
                                                                                                                 \
    name<eigenType>(to, args);                                                                                   \
    name##_old<eigenType>(to_old, args);                                                                         \
    hasFailed |= printWhenDiff(!std::equal(to, to + size, to_old), #name "<" #type ">(" + to_string(args) + ")", \
                               to_stringTab(to, size), to_stringTab(to_old, size));                              \
  }

#define refSingleType(name, type, size, args...) \
  refSingleTypeGenericTest(type, name, type, size, __attribute__((aligned(32))), args)

#define uRefSingleType(name, type, size, args...) refSingleTypeGenericTest(type, name, type, size, , args)

// Macros for test that return scalar
#define scalarSingleTypeGenericTest(type, name, eigenType, args...)                                               \
  {                                                                                                               \
    type val = name<eigenType>(args);                                                                             \
    type val_old = name##_old<eigenType>(args);                                                                   \
    hasFailed |= printWhenDiff(val != val_old, #name "<" #eigenType ">(" + to_string(args) + ")", to_string(val), \
                               to_string(val_old));                                                               \
  }

#define scalarSingleTypeTest(type, name, eigenType, args...) scalarSingleTypeGenericTest(type, name, eigenType, args)

// Tests macro definition
#include "testDef.h"

#endif  // EIGEN_MIPP_TEST_UTIL_H