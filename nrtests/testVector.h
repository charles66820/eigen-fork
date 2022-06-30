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

#define MIN2MAX_4_FLOAT_VECTOR_LOADED                            \
  loadVector(vector4, float, vmax, Packet4f, FLT_MAX, 0.0f);   \
  loadVector(vector4, float, v36, Packet4f, 36.7f, 0.0f);      \
  loadVector(vector4, float, v0, Packet4f, 0.0f, 0.0f);        \
  loadVector(vector4, float, v_240, Packet4f, -240.98f, 0.0f); \
  loadVector(vector4, float, vmin, Packet4f, FLT_MAX, 0.0f);

#define MIN2MAX_2_DOUBLE_VECTOR_LOADED                            \
  loadVector(vector2, double, vmax, Packet2d, DBL_MAX, 0.0d);   \
  loadVector(vector2, double, v36, Packet2d, 36.7d, 0.0d);      \
  loadVector(vector2, double, v0, Packet2d, 0.0d, 0.0d);        \
  loadVector(vector2, double, v_240, Packet2d, -240.98d, 0.0d); \
  loadVector(vector2, double, vmin, Packet2d, DBL_MIN, 0.0d);

#define MIN2MAX_4_INT_VECTOR_LOADED                       \
  loadVector(vector4, int, vmax, Packet4i, INT_MAX, 0); \
  loadVector(vector4, int, v36, Packet4i, 36, 0);       \
  loadVector(vector4, int, v0, Packet4i, 0, 0);         \
  loadVector(vector4, int, v_240, Packet4i, -240, 0);   \
  loadVector(vector4, int, vmin, Packet4i, INT_MIN, 0);

#define MIN2MAX_16_BOOL_VECTOR_LOADED                     \
  loadVector(vector16, bool, bvtrue, Packet16b, true, 0); \
  loadVector(vector16, bool, bvfalse, Packet16b, false, 0);

#define MIN2MAX_8_FLOAT_VECTOR_LOADED                           \
  loadVector(vector8, float, vmax, Packet8f, FLT_MAX, 0.0f);   \
  loadVector(vector8, float, v36, Packet8f, 36.7f, 0.0f);      \
  loadVector(vector8, float, v0, Packet8f, 0.0f, 0.0f);        \
  loadVector(vector8, float, v_240, Packet8f, -240.98f, 0.0f); \
  loadVector(vector8, float, vmin, Packet8f, FLT_MAX, 0.0f);

#define MIN2MAX_4_DOUBLE_VECTOR_LOADED                           \
  loadVector(vector4, double, vmax, Packet4d, DBL_MAX, 0.0d);   \
  loadVector(vector4, double, v36, Packet4d, 36.7d, 0.0d);      \
  loadVector(vector4, double, v0, Packet4d, 0.0d, 0.0d);        \
  loadVector(vector4, double, v_240, Packet4d, -240.98d, 0.0d); \
  loadVector(vector4, double, vmin, Packet4d, DBL_MIN, 0.0d);

#define MIN2MAX_8_INT_VECTOR_LOADED                      \
  loadVector(vector8, int, vmax, Packet8i, INT_MAX, 0); \
  loadVector(vector8, int, v36, Packet8i, 36, 0);       \
  loadVector(vector8, int, v0, Packet8i, 0, 0);         \
  loadVector(vector8, int, v_240, Packet8i, -240, 0);   \
  loadVector(vector8, int, vmin, Packet8i, INT_MIN, 0);

#define MIN2MAX_8_HALF_VECTOR_LOADED                                              \
  loadVector(vector8, Eigen::half, vmax, Packet8h, half(FLT_MAX), half(0.0f));   \
  loadVector(vector8, Eigen::half, v36, Packet8h, half(36.7f), half(0.0f));      \
  loadVector(vector8, Eigen::half, v0, Packet8h, half(0.0f), half(0.0f));        \
  loadVector(vector8, Eigen::half, v_240, Packet8h, half(-240.98f), half(0.0f)); \
  loadVector(vector8, Eigen::half, vmin, Packet8h, half(FLT_MAX), half(0.0f));

#define MIN2MAX_8_BFLOAT16_VECTOR_LOADED                                                 \
  loadVector(vector8, bfloat16, vmax, Packet8bf, bfloat16(FLT_MAX), bfloat16(0.0f));   \
  loadVector(vector8, bfloat16, v36, Packet8bf, bfloat16(36.7f), bfloat16(0.0f));      \
  loadVector(vector8, bfloat16, v0, Packet8bf, bfloat16(0.0f), bfloat16(0.0f));        \
  loadVector(vector8, bfloat16, v_240, Packet8bf, bfloat16(-240.98f), bfloat16(0.0f)); \
  loadVector(vector8, bfloat16, vmin, Packet8bf, bfloat16(FLT_MAX), bfloat16(0.0f));

#define MIN2MAX_4_LONG_VECTOR_LOADED                        \
  loadVector(vector4, long, vmax, Packet4l, LONG_MAX, 0L); \
  loadVector(vector4, long, v36, Packet4l, 36L, 0L);       \
  loadVector(vector4, long, v0, Packet4l, 0L, 0L);         \
  loadVector(vector4, long, v_240, Packet4l, -240L, 0L);   \
  loadVector(vector4, long, vmin, Packet4l, LONG_MIN, 0L);

// c

#define MIN2MAX_4_FLOAT_VECTOR             \
  vector4(float, vmax, FLT_MAX, -0.1f);  \
  vector4(float, v36, 36.7f, 0.1f);      \
  vector4(float, v0, 0.0f, 0.1f);        \
  vector4(float, v_240, -240.98f, 0.1f); \
  vector4(float, vmin, FLT_MIN, 0.1f);

#define MIN2MAX_2_DOUBLE_VECTOR            \
  vector2(double, vmax, DBL_MAX, -0.1d); \
  vector2(double, v36, 36.7d, 0.1d);     \
  vector2(double, v0, 0.0d, 0.1d);       \
  vector2(double, vmin, DBL_MIN, 0.1d);  \
  vector2(double, v_240, -240.98d, 0.1d);

#define MIN2MAX_4_INT_VECTOR         \
  vector4(int, vmax, INT_MAX, -1); \
  vector4(int, v36, 36, 1);        \
  vector4(int, v0, 0, 1);          \
  vector4(int, v_240, -240, 1);    \
  vector4(int, vmin, INT_MIN, 1);

#define MIN2MAX_16_BOOL_VECTOR     \
  vector16(bool, bvtrue, true, 0); \
  vector16(bool, bvfalse, false, 0);

#define MIN2MAX_8_FLOAT_VECTOR            \
  vector8(float, vmax, FLT_MAX, -0.1f);  \
  vector8(float, v36, 36.7f, 0.1f);      \
  vector8(float, v0, 0.0f, 0.1f);        \
  vector8(float, v_240, -240.98f, 0.1f); \
  vector8(float, vmin, FLT_MIN, 0.1f);

#define MIN2MAX_4_DOUBLE_VECTOR           \
  vector4(double, vmax, DBL_MAX, -0.1d); \
  vector4(double, v36, 36.7d, 0.1d);     \
  vector4(double, v0, 0.0d, 0.1d);       \
  vector4(double, vmin, DBL_MIN, 0.1d);  \
  vector4(double, v_240, -240.98d, 0.1d);

#define MIN2MAX_8_INT_VECTOR        \
  vector8(int, vmax, INT_MAX, -1); \
  vector8(int, v36, 36, 1);        \
  vector8(int, v0, 0, 1);          \
  vector8(int, v_240, -240, 1);    \
  vector8(int, vmin, INT_MIN, 1);

#define MIN2MAX_8_HALF_VECTOR                               \
  vector8(Eigen::half, vmax, half(FLT_MAX), half(-0.1f));  \
  vector8(Eigen::half, v36, half(36.7f), half(0.1f));      \
  vector8(Eigen::half, v0, half(0.0f), half(0.1f));        \
  vector8(Eigen::half, v_240, half(-240.98f), half(0.1f)); \
  vector8(Eigen::half, vmin, half(FLT_MIN), half(0.1f));

#define MIN2MAX_8_BFLOAT16_VECTOR                                 \
  vector8(bfloat16, vmax, bfloat16(FLT_MAX), bfloat16(-0.1f));  \
  vector8(bfloat16, v36, bfloat16(36.7f), bfloat16(0.1f));      \
  vector8(bfloat16, v0, bfloat16(0.0f), bfloat16(0.1f));        \
  vector8(bfloat16, v_240, bfloat16(-240.98f), bfloat16(0.1f)); \
  vector8(bfloat16, vmin, bfloat16(FLT_MIN), bfloat16(0.1f));

#define MIN2MAX_4_LONG_VECTOR          \
  vector4(long, vmax, LONG_MAX, -1L); \
  vector4(long, v36, 36L, 1L);        \
  vector4(long, v0, 0L, 1L);          \
  vector4(long, v_240, -240L, 1L);    \
  vector4(long, vmin, LONG_MIN, 1L);

// c unaligned

#define MIN2MAX_4_FLOAT_VECTOR_U            \
  vector4u(float, vmax, FLT_MAX, -0.1f);  \
  vector4u(float, v36, 36.7f, 0.1f);      \
  vector4u(float, v0, 0.0f, 0.1f);        \
  vector4u(float, v_240, -240.98f, 0.1f); \
  vector4u(float, vmin, FLT_MIN, 0.1f);

#define MIN2MAX_2_DOUBLE_VECTOR_U           \
  vector2u(double, vmax, DBL_MAX, -0.1d); \
  vector2u(double, v36, 36.7d, 0.1d);     \
  vector2u(double, v0, 0.0d, 0.1d);       \
  vector2u(double, vmin, DBL_MIN, 0.1d);  \
  vector2u(double, v_240, -240.98d, 0.1d);

#define MIN2MAX_4_INT_VECTOR_U        \
  vector4u(int, vmax, INT_MAX, -1); \
  vector4u(int, v36, 36, 1);        \
  vector4u(int, v0, 0, 1);          \
  vector4u(int, v_240, -240, 1);    \
  vector4u(int, vmin, INT_MIN, 1);

#define MIN2MAX_16_BOOL_VECTOR_U    \
  vector16u(bool, bvtrue, true, 0); \
  vector16u(bool, bvfalse, false, 0);

#define MIN2MAX_8_FLOAT_VECTOR_U           \
  vector8u(float, vmax, FLT_MAX, -0.1f);  \
  vector8u(float, v36, 36.7f, 0.1f);      \
  vector8u(float, v0, 0.0f, 0.1f);        \
  vector8u(float, v_240, -240.98f, 0.1f); \
  vector8u(float, vmin, FLT_MIN, 0.1f);

#define MIN2MAX_4_DOUBLE_VECTOR_U          \
  vector4u(double, vmax, DBL_MAX, -0.1d); \
  vector4u(double, v36, 36.7d, 0.1d);     \
  vector4u(double, v0, 0.0d, 0.1d);       \
  vector4u(double, vmin, DBL_MIN, 0.1d);  \
  vector4u(double, v_240, -240.98d, 0.1d);

#define MIN2MAX_8_INT_VECTOR_U       \
  vector8u(int, vmax, INT_MAX, -1); \
  vector8u(int, v36, 36, 1);        \
  vector8u(int, v0, 0, 1);          \
  vector8u(int, v_240, -240, 1);    \
  vector8u(int, vmin, INT_MIN, 1);

#define MIN2MAX_8_HALF_VECTOR_U                              \
  vector8u(Eigen::half, vmax, half(FLT_MAX), half(-0.1f));  \
  vector8u(Eigen::half, v36, half(36.7f), half(0.1f));      \
  vector8u(Eigen::half, v0, half(0.0f), half(0.1f));        \
  vector8u(Eigen::half, v_240, half(-240.98f), half(0.1f)); \
  vector8u(Eigen::half, vmin, half(FLT_MIN), half(0.1f));

#define MIN2MAX_8_BFLOAT16_VECTOR_U                                \
  vector8u(bfloat16, vmax, bfloat16(FLT_MAX), bfloat16(-0.1f));  \
  vector8u(bfloat16, v36, bfloat16(36.7f), bfloat16(0.1f));      \
  vector8u(bfloat16, v0, bfloat16(0.0f), bfloat16(0.1f));        \
  vector8u(bfloat16, v_240, bfloat16(-240.98f), bfloat16(0.1f)); \
  vector8u(bfloat16, vmin, bfloat16(FLT_MIN), bfloat16(0.1f));

#define MIN2MAX_4_LONG_VECTOR_U         \
  vector4u(long, vmax, LONG_MAX, -1L); \
  vector4u(long, v36, 36L, 1L);        \
  vector4u(long, v0, 0L, 1L);          \
  vector4u(long, v_240, -240L, 1L);    \
  vector4u(long, vmin, LONG_MIN, 1L);

#endif  // EIGEN_MIPP_TEST_VECTOR_H