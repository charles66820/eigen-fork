#ifndef EIGEN_MIPP_TEST_UTIL_H
#define EIGEN_MIPP_TEST_UTIL_H

#include <iostream>
#include <Eigen/Core>

using namespace Eigen::internal;
using namespace Eigen;

#ifndef VERBOSE
#define VERBOSE false
#endif  // VERBOSE

template <typename T>
void printWhenDiff(std::string msg, T val, mipp::Reg<T> reg, mipp::Reg<T> reg_old) {
  if (!mipp::testz(reg != reg_old) || VERBOSE)
    std::cout << "diff for " << msg << " with " << val << " : " << std::endl
              << "old " << reg_old << std::endl
              << "new " << reg << std::endl
              << std::endl;
}

template <typename T>
void printWhenDiff(std::string msg, T val, mipp::Reg_2<T> reg, mipp::Reg_2<T> reg_old) {
  mipp::Reg<T> rf0 = 0.0;
  mipp::Reg_2<T> rf0_h = rf0.low();

  printWhenDiff(msg, val, mipp::combine(reg, rf0_h), mipp::combine(reg_old, rf0_h));
}

#endif  // EIGEN_MIPP_TEST_UTIL_H