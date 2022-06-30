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
  loadVector(vector4, float, fhvmax, Packet4f, FLT_MAX, 0.0f);   \
  loadVector(vector4, float, fhv36, Packet4f, 36.7f, 0.0f);      \
  loadVector(vector4, float, fhv0, Packet4f, 0.0f, 0.0f);        \
  loadVector(vector4, float, fhv_240, Packet4f, -240.98f, 0.0f); \
  loadVector(vector4, float, fhvmin, Packet4f, FLT_MAX, 0.0f);

#define MIN2MAX_2_DOUBLE_VECTOR_LOADED                            \
  loadVector(vector2, double, dhvmax, Packet2d, DBL_MAX, 0.0d);   \
  loadVector(vector2, double, dhv36, Packet2d, 36.7d, 0.0d);      \
  loadVector(vector2, double, dhv0, Packet2d, 0.0d, 0.0d);        \
  loadVector(vector2, double, dhv_240, Packet2d, -240.98d, 0.0d); \
  loadVector(vector2, double, dhvmin, Packet2d, DBL_MIN, 0.0d);

#define MIN2MAX_4_INT_VECTOR_LOADED                       \
  loadVector(vector4, int, ihvmax, Packet4i, INT_MAX, 0); \
  loadVector(vector4, int, ihv36, Packet4i, 36, 0);       \
  loadVector(vector4, int, ihv0, Packet4i, 0, 0);         \
  loadVector(vector4, int, ihv_240, Packet4i, -240, 0);   \
  loadVector(vector4, int, ihvmin, Packet4i, INT_MIN, 0);

#define MIN2MAX_16_BOOL_VECTOR_LOADED                     \
  loadVector(vector16, bool, bvtrue, Packet16b, true, 0); \
  loadVector(vector16, bool, bvfalse, Packet16b, false, 0);

#define MIN2MAX_8_FLOAT_VECTOR_LOADED                           \
  loadVector(vector8, float, fvmax, Packet8f, FLT_MAX, 0.0f);   \
  loadVector(vector8, float, fv36, Packet8f, 36.7f, 0.0f);      \
  loadVector(vector8, float, fv0, Packet8f, 0.0f, 0.0f);        \
  loadVector(vector8, float, fv_240, Packet8f, -240.98f, 0.0f); \
  loadVector(vector8, float, fvmin, Packet8f, FLT_MAX, 0.0f);

#define MIN2MAX_4_DOUBLE_VECTOR_LOADED                           \
  loadVector(vector4, double, dvmax, Packet4d, DBL_MAX, 0.0d);   \
  loadVector(vector4, double, dv36, Packet4d, 36.7d, 0.0d);      \
  loadVector(vector4, double, dv0, Packet4d, 0.0d, 0.0d);        \
  loadVector(vector4, double, dv_240, Packet4d, -240.98d, 0.0d); \
  loadVector(vector4, double, dvmin, Packet4d, DBL_MIN, 0.0d);

#define MIN2MAX_8_INT_VECTOR_LOADED                      \
  loadVector(vector8, int, ivmax, Packet8i, INT_MAX, 0); \
  loadVector(vector8, int, iv36, Packet8i, 36, 0);       \
  loadVector(vector8, int, iv0, Packet8i, 0, 0);         \
  loadVector(vector8, int, iv_240, Packet8i, -240, 0);   \
  loadVector(vector8, int, ivmin, Packet8i, INT_MIN, 0);

#define MIN2MAX_8_HALF_VECTOR_LOADED                                              \
  loadVector(vector8, Eigen::half, hvmax, Packet8h, half(FLT_MAX), half(0.0f));   \
  loadVector(vector8, Eigen::half, hv36, Packet8h, half(36.7f), half(0.0f));      \
  loadVector(vector8, Eigen::half, hv0, Packet8h, half(0.0f), half(0.0f));        \
  loadVector(vector8, Eigen::half, hv_240, Packet8h, half(-240.98f), half(0.0f)); \
  loadVector(vector8, Eigen::half, hvmin, Packet8h, half(FLT_MAX), half(0.0f));

#define MIN2MAX_8_BFLOAT16_VECTOR_LOADED                                                 \
  loadVector(vector8, bfloat16, bfvmax, Packet8bf, bfloat16(FLT_MAX), bfloat16(0.0f));   \
  loadVector(vector8, bfloat16, bfv36, Packet8bf, bfloat16(36.7f), bfloat16(0.0f));      \
  loadVector(vector8, bfloat16, bfv0, Packet8bf, bfloat16(0.0f), bfloat16(0.0f));        \
  loadVector(vector8, bfloat16, bfv_240, Packet8bf, bfloat16(-240.98f), bfloat16(0.0f)); \
  loadVector(vector8, bfloat16, bfvmin, Packet8bf, bfloat16(FLT_MAX), bfloat16(0.0f));

#define MIN2MAX_4_LONG_VECTOR_LOADED                        \
  loadVector(vector4, long, lvmax, Packet4l, LONG_MAX, 0L); \
  loadVector(vector4, long, lv36, Packet4l, 36L, 0L);       \
  loadVector(vector4, long, lv0, Packet4l, 0L, 0L);         \
  loadVector(vector4, long, lv_240, Packet4l, -240L, 0L);   \
  loadVector(vector4, long, lvmin, Packet4l, LONG_MIN, 0L);

// c

#define MIN2MAX_4_FLOAT_VECTOR             \
  vector4(float, fhvmax, FLT_MAX, -0.1f);  \
  vector4(float, fhv36, 36.7f, 0.1f);      \
  vector4(float, fhv0, 0.0f, 0.1f);        \
  vector4(float, fhv_240, -240.98f, 0.1f); \
  vector4(float, fhvmin, FLT_MIN, 0.1f);

#define MIN2MAX_2_DOUBLE_VECTOR            \
  vector2(double, dhvmax, DBL_MAX, -0.1d); \
  vector2(double, dhv36, 36.7d, 0.1d);     \
  vector2(double, dhv0, 0.0d, 0.1d);       \
  vector2(double, dhvmin, DBL_MIN, 0.1d);  \
  vector2(double, dhv_240, -240.98d, 0.1d);

#define MIN2MAX_4_INT_VECTOR         \
  vector4(int, ihvmax, INT_MAX, -1); \
  vector4(int, ihv36, 36, 1);        \
  vector4(int, ihv0, 0, 1);          \
  vector4(int, ihv_240, -240, 1);    \
  vector4(int, ihvmin, INT_MIN, 1);

#define MIN2MAX_16_BOOL_VECTOR     \
  vector16(bool, bvtrue, true, 0); \
  vector16(bool, bvfalse, false, 0);

#define MIN2MAX_8_FLOAT_VECTOR            \
  vector8(float, fvmax, FLT_MAX, -0.1f);  \
  vector8(float, fv36, 36.7f, 0.1f);      \
  vector8(float, fv0, 0.0f, 0.1f);        \
  vector8(float, fv_240, -240.98f, 0.1f); \
  vector8(float, fvmin, FLT_MIN, 0.1f);

#define MIN2MAX_4_DOUBLE_VECTOR           \
  vector4(double, dvmax, DBL_MAX, -0.1d); \
  vector4(double, dv36, 36.7d, 0.1d);     \
  vector4(double, dv0, 0.0d, 0.1d);       \
  vector4(double, dvmin, DBL_MIN, 0.1d);  \
  vector4(double, dv_240, -240.98d, 0.1d);

#define MIN2MAX_8_INT_VECTOR        \
  vector8(int, ivmax, INT_MAX, -1); \
  vector8(int, iv36, 36, 1);        \
  vector8(int, iv0, 0, 1);          \
  vector8(int, iv_240, -240, 1);    \
  vector8(int, ivmin, INT_MIN, 1);

#define MIN2MAX_8_HALF_VECTOR                               \
  vector8(Eigen::half, hvmax, half(FLT_MAX), half(-0.1f));  \
  vector8(Eigen::half, hv36, half(36.7f), half(0.1f));      \
  vector8(Eigen::half, hv0, half(0.0f), half(0.1f));        \
  vector8(Eigen::half, hv_240, half(-240.98f), half(0.1f)); \
  vector8(Eigen::half, hvmin, half(FLT_MIN), half(0.1f));

#define MIN2MAX_8_BFLOAT16_VECTOR                                 \
  vector8(bfloat16, bfvmax, bfloat16(FLT_MAX), bfloat16(-0.1f));  \
  vector8(bfloat16, bfv36, bfloat16(36.7f), bfloat16(0.1f));      \
  vector8(bfloat16, bfv0, bfloat16(0.0f), bfloat16(0.1f));        \
  vector8(bfloat16, bfv_240, bfloat16(-240.98f), bfloat16(0.1f)); \
  vector8(bfloat16, bfvmin, bfloat16(FLT_MIN), bfloat16(0.1f));

#define MIN2MAX_4_LONG_VECTOR          \
  vector4(long, lvmax, LONG_MAX, -1L); \
  vector4(long, lv36, 36L, 1L);        \
  vector4(long, lv0, 0L, 1L);          \
  vector4(long, lv_240, -240L, 1L);    \
  vector4(long, lvmin, LONG_MIN, 1L);

// c unaligned

#define MIN2MAX_4_FLOAT_VECTOR_U            \
  vector4u(float, fhvmax, FLT_MAX, -0.1f);  \
  vector4u(float, fhv36, 36.7f, 0.1f);      \
  vector4u(float, fhv0, 0.0f, 0.1f);        \
  vector4u(float, fhv_240, -240.98f, 0.1f); \
  vector4u(float, fhvmin, FLT_MIN, 0.1f);

#define MIN2MAX_2_DOUBLE_VECTOR_U           \
  vector2u(double, dhvmax, DBL_MAX, -0.1d); \
  vector2u(double, dhv36, 36.7d, 0.1d);     \
  vector2u(double, dhv0, 0.0d, 0.1d);       \
  vector2u(double, dhvmin, DBL_MIN, 0.1d);  \
  vector2u(double, dhv_240, -240.98d, 0.1d);

#define MIN2MAX_4_INT_VECTOR_U        \
  vector4u(int, ihvmax, INT_MAX, -1); \
  vector4u(int, ihv36, 36, 1);        \
  vector4u(int, ihv0, 0, 1);          \
  vector4u(int, ihv_240, -240, 1);    \
  vector4u(int, ihvmin, INT_MIN, 1);

#define MIN2MAX_16_BOOL_VECTOR_U    \
  vector16u(bool, bvtrue, true, 0); \
  vector16u(bool, bvfalse, false, 0);

#define MIN2MAX_8_FLOAT_VECTOR_U           \
  vector8u(float, fvmax, FLT_MAX, -0.1f);  \
  vector8u(float, fv36, 36.7f, 0.1f);      \
  vector8u(float, fv0, 0.0f, 0.1f);        \
  vector8u(float, fv_240, -240.98f, 0.1f); \
  vector8u(float, fvmin, FLT_MIN, 0.1f);

#define MIN2MAX_4_DOUBLE_VECTOR_U          \
  vector4u(double, dvmax, DBL_MAX, -0.1d); \
  vector4u(double, dv36, 36.7d, 0.1d);     \
  vector4u(double, dv0, 0.0d, 0.1d);       \
  vector4u(double, dvmin, DBL_MIN, 0.1d);  \
  vector4u(double, dv_240, -240.98d, 0.1d);

#define MIN2MAX_8_INT_VECTOR_U       \
  vector8u(int, ivmax, INT_MAX, -1); \
  vector8u(int, iv36, 36, 1);        \
  vector8u(int, iv0, 0, 1);          \
  vector8u(int, iv_240, -240, 1);    \
  vector8u(int, ivmin, INT_MIN, 1);

#define MIN2MAX_8_HALF_VECTOR_U                              \
  vector8u(Eigen::half, hvmax, half(FLT_MAX), half(-0.1f));  \
  vector8u(Eigen::half, hv36, half(36.7f), half(0.1f));      \
  vector8u(Eigen::half, hv0, half(0.0f), half(0.1f));        \
  vector8u(Eigen::half, hv_240, half(-240.98f), half(0.1f)); \
  vector8u(Eigen::half, hvmin, half(FLT_MIN), half(0.1f));

#define MIN2MAX_8_BFLOAT16_VECTOR_U                                \
  vector8u(bfloat16, bfvmax, bfloat16(FLT_MAX), bfloat16(-0.1f));  \
  vector8u(bfloat16, bfv36, bfloat16(36.7f), bfloat16(0.1f));      \
  vector8u(bfloat16, bfv0, bfloat16(0.0f), bfloat16(0.1f));        \
  vector8u(bfloat16, bfv_240, bfloat16(-240.98f), bfloat16(0.1f)); \
  vector8u(bfloat16, bfvmin, bfloat16(FLT_MIN), bfloat16(0.1f));

#define MIN2MAX_4_LONG_VECTOR_U         \
  vector4u(long, lvmax, LONG_MAX, -1L); \
  vector4u(long, lv36, 36L, 1L);        \
  vector4u(long, lv0, 0L, 1L);          \
  vector4u(long, lv_240, -240L, 1L);    \
  vector4u(long, lvmin, LONG_MIN, 1L);

#endif  // EIGEN_MIPP_TEST_VECTOR_H