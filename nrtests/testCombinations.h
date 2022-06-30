#ifndef EIGEN_MIPP_TEST_COMBINATIONS_H
#define EIGEN_MIPP_TEST_COMBINATIONS_H

#define min2MaxTests(test, name, template, max, pos, zero, neg, min) \
  test(name, template, max);                                         \
  test(name, template, pos);                                         \
  test(name, template, zero);                                        \
  test(name, template, neg);                                         \
  test(name, template, min);

#define min2MaxArgsTests(test, name, template, max, pos, zero, neg, min, args...) \
  test(name, template, max, args);                                                          \
  test(name, template, pos, args);                                                          \
  test(name, template, zero, args);                                                         \
  test(name, template, neg, args);                                                          \
  test(name, template, min, args);

// All two combinations with repetition
#define allTwoCombRep(test, name, template, max, pos, zero, neg, min) \
  test(name, template, max, max);                                               \
  test(name, template, max, pos);                                               \
  test(name, template, max, zero);                                              \
  test(name, template, max, neg);                                               \
  test(name, template, max, min);                                               \
  test(name, template, pos, pos);                                               \
  test(name, template, pos, zero);                                              \
  test(name, template, neg, pos);                                               \
  test(name, template, min, pos);                                               \
  test(name, template, zero, zero);                                             \
  test(name, template, neg, zero);                                              \
  test(name, template, min, zero);                                              \
  test(name, template, neg, neg);                                               \
  test(name, template, min, neg);                                               \
  test(name, template, min, min);

#define allTwoCombRepArgs(test, name, template, max, pos, zero, neg, min, args...) \
  test(name, template, max, max, args);                                                      \
  test(name, template, max, pos, args);                                                      \
  test(name, template, max, zero, args);                                                     \
  test(name, template, max, neg, args);                                                      \
  test(name, template, max, min, args);                                                      \
  test(name, template, pos, pos, args);                                                      \
  test(name, template, pos, zero, args);                                                     \
  test(name, template, neg, pos, args);                                                      \
  test(name, template, min, pos, args);                                                      \
  test(name, template, zero, zero, args);                                                    \
  test(name, template, neg, zero, args);                                                     \
  test(name, template, min, zero, args);                                                     \
  test(name, template, neg, neg, args);                                                      \
  test(name, template, min, neg, args);                                                      \
  test(name, template, min, min, args);

// All three combinations with repetition
#define allThreeCombRep(test, name, template, max, pos, zero, neg, min) \
  test(name, template, max, max, max);                                            \
  test(name, template, max, max, pos);                                            \
  test(name, template, max, max, zero);                                           \
  test(name, template, max, max, neg);                                            \
  test(name, template, max, max, min);                                            \
  test(name, template, max, pos, pos);                                            \
  test(name, template, max, pos, zero);                                           \
  test(name, template, max, neg, pos);                                            \
  test(name, template, max, min, pos);                                            \
  test(name, template, max, zero, zero);                                          \
  test(name, template, max, neg, zero);                                           \
  test(name, template, max, min, zero);                                           \
  test(name, template, max, neg, neg);                                            \
  test(name, template, max, min, neg);                                            \
  test(name, template, max, min, min);                                            \
  test(name, template, pos, pos, pos);                                            \
  test(name, template, pos, pos, zero);                                           \
  test(name, template, neg, pos, pos);                                            \
  test(name, template, min, pos, pos);                                            \
  test(name, template, pos, zero, zero);                                          \
  test(name, template, neg, pos, zero);                                           \
  test(name, template, min, pos, zero);                                           \
  test(name, template, neg, neg, pos);                                            \
  test(name, template, min, neg, pos);                                            \
  test(name, template, min, min, pos);                                            \
  test(name, template, zero, zero, zero);                                         \
  test(name, template, neg, zero, zero);                                          \
  test(name, template, min, zero, zero);                                          \
  test(name, template, neg, neg, zero);                                           \
  test(name, template, min, neg, zero);                                           \
  test(name, template, min, min, zero);                                           \
  test(name, template, neg, neg, neg);                                            \
  test(name, template, min, neg, neg);                                            \
  test(name, template, min, min, neg);                                            \
  test(name, template, min, min, min);

// All two permutations with repetition
#define allTwoPermRep(test, name, template, max, pos, zero, neg, min) \
  test(name, template, max, max);                                               \
  test(name, template, max, pos);                                               \
  test(name, template, max, zero);                                              \
  test(name, template, max, neg);                                               \
  test(name, template, max, min);                                               \
  test(name, template, pos, max);                                               \
  test(name, template, pos, pos);                                               \
  test(name, template, pos, zero);                                              \
  test(name, template, pos, neg);                                               \
  test(name, template, pos, min);                                               \
  test(name, template, zero, max);                                              \
  test(name, template, zero, pos);                                              \
  test(name, template, zero, zero);                                             \
  test(name, template, zero, neg);                                              \
  test(name, template, zero, min);                                              \
  test(name, template, neg, max);                                               \
  test(name, template, neg, pos);                                               \
  test(name, template, neg, zero);                                              \
  test(name, template, neg, neg);                                               \
  test(name, template, neg, min);                                               \
  test(name, template, min, max);                                               \
  test(name, template, min, pos);                                               \
  test(name, template, min, zero);                                              \
  test(name, template, min, neg);                                               \
  test(name, template, min, min);

// All three permutations with repetition
#define allThreePermRep(test, name, template, max, pos, zero, neg, min) \
  test(name, template, max, max, max);                                            \
  test(name, template, max, max, pos);                                            \
  test(name, template, max, max, zero);                                           \
  test(name, template, max, max, neg);                                            \
  test(name, template, max, max, min);                                            \
  test(name, template, max, pos, max);                                            \
  test(name, template, max, pos, pos);                                            \
  test(name, template, max, pos, zero);                                           \
  test(name, template, max, pos, neg);                                            \
  test(name, template, max, pos, min);                                            \
  test(name, template, max, zero, max);                                           \
  test(name, template, max, zero, pos);                                           \
  test(name, template, max, zero, zero);                                          \
  test(name, template, max, zero, neg);                                           \
  test(name, template, max, zero, min);                                           \
  test(name, template, max, neg, max);                                            \
  test(name, template, max, neg, pos);                                            \
  test(name, template, max, neg, zero);                                           \
  test(name, template, max, neg, neg);                                            \
  test(name, template, max, neg, min);                                            \
  test(name, template, max, min, max);                                            \
  test(name, template, max, min, pos);                                            \
  test(name, template, max, min, zero);                                           \
  test(name, template, max, min, neg);                                            \
  test(name, template, max, min, min);                                            \
  test(name, template, pos, max, max);                                            \
  test(name, template, pos, max, pos);                                            \
  test(name, template, pos, max, zero);                                           \
  test(name, template, pos, max, neg);                                            \
  test(name, template, pos, max, min);                                            \
  test(name, template, pos, pos, max);                                            \
  test(name, template, pos, pos, pos);                                            \
  test(name, template, pos, pos, zero);                                           \
  test(name, template, pos, pos, neg);                                            \
  test(name, template, pos, pos, min);                                            \
  test(name, template, pos, zero, max);                                           \
  test(name, template, pos, zero, pos);                                           \
  test(name, template, pos, zero, zero);                                          \
  test(name, template, pos, zero, neg);                                           \
  test(name, template, pos, zero, min);                                           \
  test(name, template, pos, neg, max);                                            \
  test(name, template, pos, neg, pos);                                            \
  test(name, template, pos, neg, zero);                                           \
  test(name, template, pos, neg, neg);                                            \
  test(name, template, pos, neg, min);                                            \
  test(name, template, pos, min, max);                                            \
  test(name, template, pos, min, pos);                                            \
  test(name, template, pos, min, zero);                                           \
  test(name, template, pos, min, neg);                                            \
  test(name, template, pos, min, min);                                            \
  test(name, template, zero, max, max);                                           \
  test(name, template, zero, max, pos);                                           \
  test(name, template, zero, max, zero);                                          \
  test(name, template, zero, max, neg);                                           \
  test(name, template, zero, max, min);                                           \
  test(name, template, zero, pos, max);                                           \
  test(name, template, zero, pos, pos);                                           \
  test(name, template, zero, pos, zero);                                          \
  test(name, template, zero, pos, neg);                                           \
  test(name, template, zero, pos, min);                                           \
  test(name, template, zero, zero, max);                                          \
  test(name, template, zero, zero, pos);                                          \
  test(name, template, zero, zero, zero);                                         \
  test(name, template, zero, zero, neg);                                          \
  test(name, template, zero, zero, min);                                          \
  test(name, template, zero, neg, max);                                           \
  test(name, template, zero, neg, pos);                                           \
  test(name, template, zero, neg, zero);                                          \
  test(name, template, zero, neg, neg);                                           \
  test(name, template, zero, neg, min);                                           \
  test(name, template, zero, min, max);                                           \
  test(name, template, zero, min, pos);                                           \
  test(name, template, zero, min, zero);                                          \
  test(name, template, zero, min, neg);                                           \
  test(name, template, zero, min, min);                                           \
  test(name, template, neg, max, max);                                            \
  test(name, template, neg, max, pos);                                            \
  test(name, template, neg, max, zero);                                           \
  test(name, template, neg, max, neg);                                            \
  test(name, template, neg, max, min);                                            \
  test(name, template, neg, pos, max);                                            \
  test(name, template, neg, pos, pos);                                            \
  test(name, template, neg, pos, zero);                                           \
  test(name, template, neg, pos, neg);                                            \
  test(name, template, neg, pos, min);                                            \
  test(name, template, neg, zero, max);                                           \
  test(name, template, neg, zero, pos);                                           \
  test(name, template, neg, zero, zero);                                          \
  test(name, template, neg, zero, neg);                                           \
  test(name, template, neg, zero, min);                                           \
  test(name, template, neg, neg, max);                                            \
  test(name, template, neg, neg, pos);                                            \
  test(name, template, neg, neg, zero);                                           \
  test(name, template, neg, neg, neg);                                            \
  test(name, template, neg, neg, min);                                            \
  test(name, template, neg, min, max);                                            \
  test(name, template, neg, min, pos);                                            \
  test(name, template, neg, min, zero);                                           \
  test(name, template, neg, min, neg);                                            \
  test(name, template, neg, min, min);                                            \
  test(name, template, min, max, max);                                            \
  test(name, template, min, max, pos);                                            \
  test(name, template, min, max, zero);                                           \
  test(name, template, min, max, neg);                                            \
  test(name, template, min, max, min);                                            \
  test(name, template, min, pos, max);                                            \
  test(name, template, min, pos, pos);                                            \
  test(name, template, min, pos, zero);                                           \
  test(name, template, min, pos, neg);                                            \
  test(name, template, min, pos, min);                                            \
  test(name, template, min, zero, max);                                           \
  test(name, template, min, zero, pos);                                           \
  test(name, template, min, zero, zero);                                          \
  test(name, template, min, zero, neg);                                           \
  test(name, template, min, zero, min);                                           \
  test(name, template, min, neg, max);                                            \
  test(name, template, min, neg, pos);                                            \
  test(name, template, min, neg, zero);                                           \
  test(name, template, min, neg, neg);                                            \
  test(name, template, min, neg, min);                                            \
  test(name, template, min, min, max);                                            \
  test(name, template, min, min, pos);                                            \
  test(name, template, min, min, zero);                                           \
  test(name, template, min, min, neg);                                            \
  test(name, template, min, min, min);

#endif  // EIGEN_MIPP_TEST_COMBINATIONS_H