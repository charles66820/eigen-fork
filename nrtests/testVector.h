#ifndef EIGEN_MIPP_TEST_VECTOR_H
#define EIGEN_MIPP_TEST_VECTOR_H

#define vector2(type, name, value, delta) type name[] __attribute__((aligned(32))) = {value, value + delta};
#define vector4(type, name, value, delta) \
  type name[]                             \
      __attribute__((aligned(32))) = {value, value + delta, value + delta + delta, value + delta + delta + delta};
#define vector8(type, name, value, delta)                                                            \
  type name[] __attribute__((aligned(32))) = {value,                                                 \
                                              value + delta,                                         \
                                              value + delta + delta,                                 \
                                              value + delta + delta + delta,                         \
                                              value + delta + delta + delta + delta,                 \
                                              value + delta + delta + delta + delta + delta,         \
                                              value + delta + delta + delta + delta + delta + delta, \
                                              value + delta + delta + delta + delta + delta + delta + delta};
#define vector16(type, name, value, delta)                                                                            \
  type name[] __attribute__((aligned(32))) = {                                                                        \
      value,                                                                                                          \
      value + delta,                                                                                                  \
      value + delta + delta,                                                                                          \
      value + delta + delta + delta,                                                                                  \
      value + delta + delta + delta + delta,                                                                          \
      value + delta + delta + delta + delta + delta,                                                                  \
      value + delta + delta + delta + delta + delta + delta,                                                          \
      value + delta + delta + delta + delta + delta + delta + delta,                                                  \
      value + delta + delta + delta + delta + delta + delta + delta + delta,                                          \
      value + delta + delta + delta + delta + delta + delta + delta + delta + delta,                                  \
      value + delta + delta + delta + delta + delta + delta + delta + delta + delta + delta,                          \
      value + delta + delta + delta + delta + delta + delta + delta + delta + delta + delta + delta,                  \
      value + delta + delta + delta + delta + delta + delta + delta + delta + delta + delta + delta + delta,          \
      value + delta + delta + delta + delta + delta + delta + delta + delta + delta + delta + delta + delta + delta,  \
      value + delta + delta + delta + delta + delta + delta + delta + delta + delta + delta + delta + delta + delta + \
          delta,                                                                                                      \
      value + delta + delta + delta + delta + delta + delta + delta + delta + delta + delta + delta + delta + delta + \
          delta + delta};

#define vector2u(type, name, value, delta) type name[] = {value, value + delta};
#define vector4u(type, name, value, delta) \
  type name[] = {value, value + delta, value + delta + delta, value + delta + delta + delta};
#define vector8u(type, name, value, delta)                              \
  type name[] = {value,                                                 \
                 value + delta,                                         \
                 value + delta + delta,                                 \
                 value + delta + delta + delta,                         \
                 value + delta + delta + delta + delta,                 \
                 value + delta + delta + delta + delta + delta,         \
                 value + delta + delta + delta + delta + delta + delta, \
                 value + delta + delta + delta + delta + delta + delta + delta};
#define vector16u(type, name, value, delta)                                                                           \
  type name[] = {                                                                                                     \
      value,                                                                                                          \
      value + delta,                                                                                                  \
      value + delta + delta,                                                                                          \
      value + delta + delta + delta,                                                                                  \
      value + delta + delta + delta + delta,                                                                          \
      value + delta + delta + delta + delta + delta,                                                                  \
      value + delta + delta + delta + delta + delta + delta,                                                          \
      value + delta + delta + delta + delta + delta + delta + delta,                                                  \
      value + delta + delta + delta + delta + delta + delta + delta + delta,                                          \
      value + delta + delta + delta + delta + delta + delta + delta + delta + delta,                                  \
      value + delta + delta + delta + delta + delta + delta + delta + delta + delta + delta,                          \
      value + delta + delta + delta + delta + delta + delta + delta + delta + delta + delta + delta,                  \
      value + delta + delta + delta + delta + delta + delta + delta + delta + delta + delta + delta + delta,          \
      value + delta + delta + delta + delta + delta + delta + delta + delta + delta + delta + delta + delta + delta,  \
      value + delta + delta + delta + delta + delta + delta + delta + delta + delta + delta + delta + delta + delta + \
          delta,                                                                                                      \
      value + delta + delta + delta + delta + delta + delta + delta + delta + delta + delta + delta + delta + delta + \
          delta + delta};

// Loader

#define loadVector(vec, type, name, EigenType, value, delta) \
  vec(type, name##_tab, value, delta);                       \
  EigenType name = pload<EigenType>(name##_tab);

// Preset loader

#define MIN2MAX_FLOAT_VECTOR_LOADED(size)                                  \
  loadVector(vector##size, float, vmax, Packet##size##f, FLT_MAX, 0.0f);   \
  loadVector(vector##size, float, v36, Packet##size##f, 36.7f, 0.0f);      \
  loadVector(vector##size, float, v0, Packet##size##f, 0.0f, 0.0f);        \
  loadVector(vector##size, float, v_240, Packet##size##f, -240.98f, 0.0f); \
  loadVector(vector##size, float, vmin, Packet##size##f, FLT_MIN, 0.0f);

#define MIN2MAX_DOUBLE_VECTOR_LOADED(size)                                  \
  loadVector(vector##size, double, vmax, Packet##size##d, DBL_MAX, 0.0d);   \
  loadVector(vector##size, double, v36, Packet##size##d, 36.7d, 0.0d);      \
  loadVector(vector##size, double, v0, Packet##size##d, 0.0d, 0.0d);        \
  loadVector(vector##size, double, v_240, Packet##size##d, -240.98d, 0.0d); \
  loadVector(vector##size, double, vmin, Packet##size##d, DBL_MIN, 0.0d);

#define MIN2MAX_INT_VECTOR_LOADED(size)                             \
  loadVector(vector##size, int, vmax, Packet##size##i, INT_MAX, 0); \
  loadVector(vector##size, int, v36, Packet##size##i, 36, 0);       \
  loadVector(vector##size, int, v0, Packet##size##i, 0, 0);         \
  loadVector(vector##size, int, v_240, Packet##size##i, -240, 0);   \
  loadVector(vector##size, int, vmin, Packet##size##i, INT_MIN, 0);

#define BOOL_VECTOR_LOADED(size)                                   \
  loadVector(vector##size, bool, vtrue, Packet##size##b, true, 0); \
  loadVector(vector##size, bool, vfalse, Packet##size##b, false, 0);

#define MIN2MAX_HALF_VECTOR_LOADED(size)                                                     \
  loadVector(vector##size, Eigen::half, vmax, Packet##size##h, half(FLT_MAX), half(0.0f));   \
  loadVector(vector##size, Eigen::half, v36, Packet##size##h, half(36.7f), half(0.0f));      \
  loadVector(vector##size, Eigen::half, v0, Packet##size##h, half(0.0f), half(0.0f));        \
  loadVector(vector##size, Eigen::half, v_240, Packet##size##h, half(-240.98f), half(0.0f)); \
  loadVector(vector##size, Eigen::half, vmin, Packet##size##h, half(FLT_MIN), half(0.0f));

#define MIN2MAX_BFLOAT16_VECTOR_LOADED(size)                                                       \
  loadVector(vector##size, bfloat16, vmax, Packet##size##bf, bfloat16(FLT_MAX), bfloat16(0.0f));   \
  loadVector(vector##size, bfloat16, v36, Packet##size##bf, bfloat16(36.7f), bfloat16(0.0f));      \
  loadVector(vector##size, bfloat16, v0, Packet##size##bf, bfloat16(0.0f), bfloat16(0.0f));        \
  loadVector(vector##size, bfloat16, v_240, Packet##size##bf, bfloat16(-240.98f), bfloat16(0.0f)); \
  loadVector(vector##size, bfloat16, vmin, Packet##size##bf, bfloat16(FLT_MIN), bfloat16(0.0f));

#define MIN2MAX_LONG_VECTOR_LOADED(size)                               \
  loadVector(vector##size, long, vmax, Packet##size##l, LONG_MAX, 0L); \
  loadVector(vector##size, long, v36, Packet##size##l, 36L, 0L);       \
  loadVector(vector##size, long, v0, Packet##size##l, 0L, 0L);         \
  loadVector(vector##size, long, v_240, Packet##size##l, -240L, 0L);   \
  loadVector(vector##size, long, vmin, Packet##size##l, LONG_MIN, 0L);

// Preset

#define MIN2MAX_FLOAT_VECTOR(vec)    \
  vec(float, vmax, FLT_MAX, -0.1f);  \
  vec(float, v36, 36.7f, 0.1f);      \
  vec(float, v0, 0.0f, 0.1f);        \
  vec(float, v_240, -240.98f, 0.1f); \
  vec(float, vmin, FLT_MIN, 0.1f);

#define MIN2MAX_DOUBLE_VECTOR(vec)   \
  vec(double, vmax, DBL_MAX, -0.1d); \
  vec(double, v36, 36.7d, 0.1d);     \
  vec(double, v0, 0.0d, 0.1d);       \
  vec(double, vmin, DBL_MIN, 0.1d);  \
  vec(double, v_240, -240.98d, 0.1d);

#define MIN2MAX_INT_VECTOR(vec) \
  vec(int, vmax, INT_MAX, -1);  \
  vec(int, v36, 36, 1);         \
  vec(int, v0, 0, 1);           \
  vec(int, v_240, -240, 1);     \
  vec(int, vmin, INT_MIN, 1);

#define BOOL_VECTOR(vec)     \
  vec(bool, vtrue, true, 0); \
  vec(bool, vfalse, false, 0);

#define MIN2MAX_FLOAT_VECTOR(vec)    \
  vec(float, vmax, FLT_MAX, -0.1f);  \
  vec(float, v36, 36.7f, 0.1f);      \
  vec(float, v0, 0.0f, 0.1f);        \
  vec(float, v_240, -240.98f, 0.1f); \
  vec(float, vmin, FLT_MIN, 0.1f);

#define MIN2MAX_DOUBLE_VECTOR(vec)   \
  vec(double, vmax, DBL_MAX, -0.1d); \
  vec(double, v36, 36.7d, 0.1d);     \
  vec(double, v0, 0.0d, 0.1d);       \
  vec(double, vmin, DBL_MIN, 0.1d);  \
  vec(double, v_240, -240.98d, 0.1d);

#define MIN2MAX_INT_VECTOR(vec) \
  vec(int, vmax, INT_MAX, -1);  \
  vec(int, v36, 36, 1);         \
  vec(int, v0, 0, 1);           \
  vec(int, v_240, -240, 1);     \
  vec(int, vmin, INT_MIN, 1);

#define MIN2MAX_HALF_VECTOR(vec)                       \
  vec(Eigen::half, vmax, half(FLT_MAX), half(-0.1f));  \
  vec(Eigen::half, v36, half(36.7f), half(0.1f));      \
  vec(Eigen::half, v0, half(0.0f), half(0.1f));        \
  vec(Eigen::half, v_240, half(-240.98f), half(0.1f)); \
  vec(Eigen::half, vmin, half(FLT_MIN), half(0.1f));

#define MIN2MAX_BFLOAT16_VECTOR(vec)                        \
  vec(bfloat16, vmax, bfloat16(FLT_MAX), bfloat16(-0.1f));  \
  vec(bfloat16, v36, bfloat16(36.7f), bfloat16(0.1f));      \
  vec(bfloat16, v0, bfloat16(0.0f), bfloat16(0.1f));        \
  vec(bfloat16, v_240, bfloat16(-240.98f), bfloat16(0.1f)); \
  vec(bfloat16, vmin, bfloat16(FLT_MIN), bfloat16(0.1f));

#define MIN2MAX_LONG_VECTOR(vec)  \
  vec(long, vmax, LONG_MAX, -1L); \
  vec(long, v36, 36L, 1L);        \
  vec(long, v0, 0L, 1L);          \
  vec(long, v_240, -240L, 1L);    \
  vec(long, vmin, LONG_MIN, 1L);

#endif  // EIGEN_MIPP_TEST_VECTOR_H