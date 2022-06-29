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

#define MIN2MAX_HALF_FLOAT_VECTOR                                \
  loadVector(vector4, float, fhvmax, Packet4f, FLT_MAX, 0.0f);   \
  loadVector(vector4, float, fhv36, Packet4f, 36.7f, 0.0f);      \
  loadVector(vector4, float, fhv0, Packet4f, 0.0f, 0.0f);        \
  loadVector(vector4, float, fhv_240, Packet4f, -240.98f, 0.0f); \
  loadVector(vector4, float, fhvmin, Packet4f, FLT_MAX, 0.0f);

#define MIN2MAX_HALF_DOUBLE_VECTOR                                \
  loadVector(vector2, double, dhvmax, Packet2d, DBL_MAX, 0.0d);   \
  loadVector(vector2, double, dhv36, Packet2d, 36.7d, 0.0d);      \
  loadVector(vector2, double, dhv0, Packet2d, 0.0d, 0.0d);        \
  loadVector(vector2, double, dhv_240, Packet2d, -240.98d, 0.0d); \
  loadVector(vector2, double, dhvmin, Packet2d, DBL_MIN, 0.0d);

#define MIN2MAX_HALF_INT_VECTOR                           \
  loadVector(vector4, int, ihvmax, Packet4i, INT_MAX, 0); \
  loadVector(vector4, int, ihv36, Packet4i, 36, 0);       \
  loadVector(vector4, int, ihv0, Packet4i, 0, 0);         \
  loadVector(vector4, int, ihv_240, Packet4i, -240, 0);   \
  loadVector(vector4, int, ihvmin, Packet4i, INT_MIN, 0);

#define MIN2MAX_HALF_BOOL_VECTOR                          \
  loadVector(vector16, bool, bvtrue, Packet16b, true, 0); \
  loadVector(vector16, bool, bvfalse, Packet16b, false, 0);

#define MIN2MAX_FULL_FLOAT_VECTOR                               \
  loadVector(vector8, float, fvmax, Packet8f, FLT_MAX, 0.0f);   \
  loadVector(vector8, float, fv36, Packet8f, 36.7f, 0.0f);      \
  loadVector(vector8, float, fv0, Packet8f, 0.0f, 0.0f);        \
  loadVector(vector8, float, fv_240, Packet8f, -240.98f, 0.0f); \
  loadVector(vector8, float, fvmin, Packet8f, FLT_MAX, 0.0f);

#define MIN2MAX_FULL_DOUBLE_VECTOR                               \
  loadVector(vector4, double, dvmax, Packet4d, DBL_MAX, 0.0d);   \
  loadVector(vector4, double, dv36, Packet4d, 36.7d, 0.0d);      \
  loadVector(vector4, double, dv0, Packet4d, 0.0d, 0.0d);        \
  loadVector(vector4, double, dv_240, Packet4d, -240.98d, 0.0d); \
  loadVector(vector4, double, dvmin, Packet4d, DBL_MIN, 0.0d);

#define MIN2MAX_FULL_INT_VECTOR                          \
  loadVector(vector8, int, ivmax, Packet8i, INT_MAX, 0); \
  loadVector(vector8, int, iv36, Packet8i, 36, 0);       \
  loadVector(vector8, int, iv0, Packet8i, 0, 0);         \
  loadVector(vector8, int, iv_240, Packet8i, -240, 0);   \
  loadVector(vector8, int, ivmin, Packet8i, INT_MIN, 0);

#define MIN2MAX_HALF_HALF_VECTOR                                                  \
  loadVector(vector8, Eigen::half, hvmax, Packet8h, half(FLT_MAX), half(0.0f));   \
  loadVector(vector8, Eigen::half, hv36, Packet8h, half(36.7f), half(0.0f));      \
  loadVector(vector8, Eigen::half, hv0, Packet8h, half(0.0f), half(0.0f));        \
  loadVector(vector8, Eigen::half, hv_240, Packet8h, half(-240.98f), half(0.0f)); \
  loadVector(vector8, Eigen::half, hvmin, Packet8h, half(FLT_MAX), half(0.0f));

#define MIN2MAX_HALF_BFLOAT16_VECTOR                                                     \
  loadVector(vector8, bfloat16, bfvmax, Packet8bf, bfloat16(FLT_MAX), bfloat16(0.0f));   \
  loadVector(vector8, bfloat16, bfv36, Packet8bf, bfloat16(36.7f), bfloat16(0.0f));      \
  loadVector(vector8, bfloat16, bfv0, Packet8bf, bfloat16(0.0f), bfloat16(0.0f));        \
  loadVector(vector8, bfloat16, bfv_240, Packet8bf, bfloat16(-240.98f), bfloat16(0.0f)); \
  loadVector(vector8, bfloat16, bfvmin, Packet8bf, bfloat16(FLT_MAX), bfloat16(0.0f));

#define MIN2MAX_FULL_LONG_VECTOR                            \
  loadVector(vector4, long, lvmax, Packet4l, LONG_MAX, 0L); \
  loadVector(vector4, long, lv36, Packet4l, 36L, 0L);       \
  loadVector(vector4, long, lv0, Packet4l, 0L, 0L);         \
  loadVector(vector4, long, lv_240, Packet4l, -240L, 0L);   \
  loadVector(vector4, long, lvmin, Packet4l, LONG_MIN, 0L);

#endif  // EIGEN_MIPP_TEST_VECTOR_H