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

#define loadVector(vec, type, typeReg, name, cast, EigenType, value, delta, MIPP_reg) \
  vec(type, name##_tab, value, delta);                                                \
  mipp::MIPP_reg<typeReg> name = cast(pload<EigenType>(name##_tab));

#define loadVectorFull(vec, type, name, cast, full, value, delta) \
  loadVector(vec, type, type, name, cast, full, value, delta, Reg)
#define loadVectorHalf(vec, type, name, cast, half, value, delta) \
  loadVector(vec, type, type, name, cast, half, value, delta, Reg_2)
#define loadVectorFullRegType(vec, type, typeReg, name, cast, full, value, delta) \
  loadVector(vec, type, typeReg, name, cast, full, value, delta, Reg)
#define loadVectorHalfRegType(vec, type, typeReg, name, cast, half, value, delta) \
  loadVector(vec, type, typeReg, name, cast, half, value, delta, Reg_2)

// Preset loader

#define MIN2MAX_HALF_FLOAT_VECTOR                                      \
  loadVectorHalf(vector4, float, fhvmax, FLOAT_CAST_TO_MIPP_HALF, Packet4f, FLT_MAX, 0.0f);   \
  loadVectorHalf(vector4, float, fhv36, FLOAT_CAST_TO_MIPP_HALF, Packet4f, 36.7f, 0.0f);      \
  loadVectorHalf(vector4, float, fhv0, FLOAT_CAST_TO_MIPP_HALF, Packet4f, 0.0f, 0.0f);        \
  loadVectorHalf(vector4, float, fhv_240, FLOAT_CAST_TO_MIPP_HALF, Packet4f, -240.98f, 0.0f); \
  loadVectorHalf(vector4, float, fhvmin, FLOAT_CAST_TO_MIPP_HALF, Packet4f, FLT_MAX, 0.0f);

#define MIN2MAX_HALF_DOUBLE_VECTOR                                               \
  loadVectorHalf(vector2, double, dhvmax, DOUBLE_CAST_TO_MIPP_HALF, Packet2d, DBL_MAX, 0.0d);   \
  loadVectorHalf(vector2, double, dhv36, DOUBLE_CAST_TO_MIPP_HALF, Packet2d, 36.7d, 0.0d);      \
  loadVectorHalf(vector2, double, dhv0, DOUBLE_CAST_TO_MIPP_HALF, Packet2d, 0.0d, 0.0d);        \
  loadVectorHalf(vector2, double, dhv_240, DOUBLE_CAST_TO_MIPP_HALF, Packet2d, -240.98d, 0.0d); \
  loadVectorHalf(vector2, double, dhvmin, DOUBLE_CAST_TO_MIPP_HALF, Packet2d, DBL_MIN, 0.0d);

#define MIN2MAX_HALF_INT_VECTOR                                              \
  loadVectorHalf(vector4, int, ihvmax, INT_CAST_TO_MIPP_HALF, Packet4i, INT_MAX, 0); \
  loadVectorHalf(vector4, int, ihv36, INT_CAST_TO_MIPP_HALF, Packet4i, 36, 0);       \
  loadVectorHalf(vector4, int, ihv0, INT_CAST_TO_MIPP_HALF, Packet4i, 0, 0);         \
  loadVectorHalf(vector4, int, ihv_240, INT_CAST_TO_MIPP_HALF, Packet4i, -240, 0);   \
  loadVectorHalf(vector4, int, ihvmin, INT_CAST_TO_MIPP_HALF, Packet4i, INT_MIN, 0);

#define MIN2MAX_HALF_BOOL_VECTOR                                             \
  loadVectorHalf(vector16, bool, bvtrue, INT_CAST_TO_MIPP_HALF, Packet16b, true, 0); \
  loadVectorHalf(vector16, bool, bvfalse, INT_CAST_TO_MIPP_HALF, Packet16b, false, 0);

#define MIN2MAX_FULL_FLOAT_VECTOR                                     \
  loadVectorFull(vector8, float, fvmax, FLOAT_CAST_TO_MIPP_FULL, Packet8f, FLT_MAX, 0.0f);   \
  loadVectorFull(vector8, float, fv36, FLOAT_CAST_TO_MIPP_FULL, Packet8f, 36.7f, 0.0f);      \
  loadVectorFull(vector8, float, fv0, FLOAT_CAST_TO_MIPP_FULL, Packet8f, 0.0f, 0.0f);        \
  loadVectorFull(vector8, float, fv_240, FLOAT_CAST_TO_MIPP_FULL, Packet8f, -240.98f, 0.0f); \
  loadVectorFull(vector8, float, fvmin, FLOAT_CAST_TO_MIPP_FULL, Packet8f, FLT_MAX, 0.0f);

#define MIN2MAX_FULL_DOUBLE_VECTOR                                              \
  loadVectorFull(vector4, double, dvmax, DOUBLE_CAST_TO_MIPP_FULL, Packet4d, DBL_MAX, 0.0d);   \
  loadVectorFull(vector4, double, dv36, DOUBLE_CAST_TO_MIPP_FULL, Packet4d, 36.7d, 0.0d);      \
  loadVectorFull(vector4, double, dv0, DOUBLE_CAST_TO_MIPP_FULL, Packet4d, 0.0d, 0.0d);        \
  loadVectorFull(vector4, double, dv_240, DOUBLE_CAST_TO_MIPP_FULL, Packet4d, -240.98d, 0.0d); \
  loadVectorFull(vector4, double, dvmin, DOUBLE_CAST_TO_MIPP_FULL, Packet4d, DBL_MIN, 0.0d);

#define MIN2MAX_FULL_INT_VECTOR                                             \
  loadVectorFull(vector8, int, ivmax, INT_CAST_TO_MIPP_FULL, Packet8i, INT_MAX, 0); \
  loadVectorFull(vector8, int, iv36, INT_CAST_TO_MIPP_FULL, Packet8i, 36, 0);       \
  loadVectorFull(vector8, int, iv0, INT_CAST_TO_MIPP_FULL, Packet8i, 0, 0);         \
  loadVectorFull(vector8, int, iv_240, INT_CAST_TO_MIPP_FULL, Packet8i, -240, 0);   \
  loadVectorFull(vector8, int, ivmin, INT_CAST_TO_MIPP_FULL, Packet8i, INT_MIN, 0);

#define MIN2MAX_HALF_HALF_VECTOR                                                                                   \
  loadVectorHalfRegType(vector8, Eigen::half, short, hvmax, INT_CAST_TO_MIPP_HALF, Packet8h, half(FLT_MAX), half(0.0f));   \
  loadVectorHalfRegType(vector8, Eigen::half, short, hv36, INT_CAST_TO_MIPP_HALF, Packet8h, half(36.7f), half(0.0f));      \
  loadVectorHalfRegType(vector8, Eigen::half, short, hv0, INT_CAST_TO_MIPP_HALF, Packet8h, half(0.0f), half(0.0f));        \
  loadVectorHalfRegType(vector8, Eigen::half, short, hv_240, INT_CAST_TO_MIPP_HALF, Packet8h, half(-240.98f), half(0.0f)); \
  loadVectorHalfRegType(vector8, Eigen::half, short, hvmin, INT_CAST_TO_MIPP_HALF, Packet8h, half(FLT_MAX), half(0.0f));

#define MIN2MAX_HALF_BFLOAT16_VECTOR                                                                                 \
  loadVectorHalfRegType(vector8, bfloat16, short, bfvmax, INT_CAST_TO_MIPP_HALF, Packet8bf, bfloat16(FLT_MAX),               \
                        bfloat16(0.0f));                                                                             \
  loadVectorHalfRegType(vector8, bfloat16, short, bfv36, INT_CAST_TO_MIPP_HALF, Packet8bf, bfloat16(36.7f), bfloat16(0.0f)); \
  loadVectorHalfRegType(vector8, bfloat16, short, bfv0, INT_CAST_TO_MIPP_HALF, Packet8bf, bfloat16(0.0f), bfloat16(0.0f));   \
  loadVectorHalfRegType(vector8, bfloat16, short, bfv_240, INT_CAST_TO_MIPP_HALF, Packet8bf, bfloat16(-240.98f),             \
                        bfloat16(0.0f));                                                                             \
  loadVectorHalfRegType(vector8, bfloat16, short, bfvmin, INT_CAST_TO_MIPP_HALF, Packet8bf, bfloat16(FLT_MAX), bfloat16(0.0f));

#define MIN2MAX_FULL_LONG_VECTOR                                               \
  loadVectorFull(vector4, long, lvmax, INT_CAST_TO_MIPP_FULL, Packet4l, LONG_MAX, 0L); \
  loadVectorFull(vector4, long, lv36, INT_CAST_TO_MIPP_FULL, Packet4l, 36L, 0L);       \
  loadVectorFull(vector4, long, lv0, INT_CAST_TO_MIPP_FULL, Packet4l, 0L, 0L);         \
  loadVectorFull(vector4, long, lv_240, INT_CAST_TO_MIPP_FULL, Packet4l, -240L, 0L);   \
  loadVectorFull(vector4, long, lvmin, INT_CAST_TO_MIPP_FULL, Packet4l, LONG_MIN, 0L);

#endif  // EIGEN_MIPP_TEST_VECTOR_H