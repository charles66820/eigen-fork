#ifndef EIGEN_MIPP_TEST_STRING_H
#define EIGEN_MIPP_TEST_STRING_H

#if defined(DISABLE_VECTOR_PRINTING) && DISABLE_VECTOR_PRINTING == 1
#define to_string(...) toString()
#define to_stringTab(...) toString()
std::string toString() { return "?"; }
#else
// code inspered by
// https://stackoverflow.com/questions/22964799/how-to-print-a-variable-number-of-parameters-with-a-macro
#define to_string(...) toString(__VA_ARGS__)

#define printableToString(type)                 \
  template <>                                   \
  std::string toString<type>(const type arg1) { \
    std::stringstream stream;                   \
    stream << arg1;                             \
    return stream.str();                        \
  }

#define packetToString(eigenType, type, cast)             \
  template <>                                             \
  std::string toString<eigenType>(const eigenType arg1) { \
    return toString(mipp::Reg<type>(cast(arg1)));         \
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
printableToString(mipp::Reg<int8_t>);
printableToString(mipp::Reg<bool>);
printableToString(mipp::Reg<short>);
printableToString(mipp::Reg<int>);
printableToString(mipp::Reg<long>);
printableToString(mipp::Reg<float>);
printableToString(mipp::Reg<double>);

#ifdef __SSE__
packetToString(Eigen::internal::Packet4f, float, FLOAT_CAST_128_TO_MIPP_REG_T);
packetToString(Eigen::internal::Packet2d, double, DOUBLE_CAST_128_TO_MIPP_REG_T);
packetToString(Eigen::internal::Packet4i, int, INT_CAST_128_TO_MIPP_REG_T);
packetToString(Eigen::internal::Packet16b, int8_t, INT_CAST_128_TO_MIPP_REG_T);
#endif
#ifdef __AVX__
packetToString(Eigen::internal::Packet8f, float, FLOAT_CAST_256_TO_MIPP_REG_T);
packetToString(Eigen::internal::Packet4d, double, DOUBLE_CAST_256_TO_MIPP_REG_T);
packetToString(Eigen::internal::Packet8i, int, INT_CAST_256_TO_MIPP_REG_T);
packetToString(Eigen::internal::Packet8h, short, INT_CAST_128_TO_MIPP_REG_T);
packetToString(Eigen::internal::Packet8bf, short, INT_CAST_128_TO_MIPP_REG_T);
#endif
#ifdef __AVX2__
packetToString(Eigen::internal::Packet4l, long, INT_CAST_256_TO_MIPP_REG_T);
#endif

template <typename Arg1, typename... Args>
std::string toString(const Arg1 arg1, const Args... args) {
  return toString(arg1) + ", " + toString(args...);
}

#define to_stringTab(tab, size) toStringTab(tab, size)

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
#endif

#endif  // EIGEN_MIPP_TEST_STRING_H