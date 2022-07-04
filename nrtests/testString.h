#ifndef EIGEN_MIPP_TEST_STRING_H
#define EIGEN_MIPP_TEST_STRING_H

// code inspered by
// https://stackoverflow.com/questions/22964799/how-to-print-a-variable-number-of-parameters-with-a-macro
#define to_sting(...) toString(__VA_ARGS__)

#define printableToString(type)           \
  template <>                             \
  std::string toString<type>(const type arg1) { \
    std::stringstream stream;             \
    stream << arg1;                       \
    return stream.str();                  \
  }

template <typename Arg1>
std::string toString(const Arg1 arg1) {
  return "?";
}

printableToString(int8_t);
printableToString(bool);
printableToString(short);
printableToString(int);
printableToString(long);
printableToString(float);
printableToString(double);
printableToString(Eigen::half);
printableToString(Eigen::bfloat16);
printableToString(mipp::Reg<bool>);
printableToString(mipp::Reg<int8_t>);
printableToString(mipp::Reg<int>);
printableToString(mipp::Reg<long>);
printableToString(mipp::Reg<float>);
printableToString(mipp::Reg<double>);

template <typename Arg1, typename... Args>
std::string toString(const Arg1 arg1, const Args... args) {
  return toString(arg1) + ", " + toString(args...);
}

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

#endif  // EIGEN_MIPP_TEST_STRING_H