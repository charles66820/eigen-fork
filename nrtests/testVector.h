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

#endif  // EIGEN_MIPP_TEST_VECTOR_H