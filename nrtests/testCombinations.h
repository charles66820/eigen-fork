#ifndef EIGEN_MIPP_TEST_COMBINATIONS_H
#define EIGEN_MIPP_TEST_COMBINATIONS_H

// All two combinations with repetition
#define allTwoCombRep(test, name, max, pos, zero, neg, min) \
  test(name, max, max);                                     \
  test(name, max, pos);                                     \
  test(name, max, zero);                                    \
  test(name, max, neg);                                     \
  test(name, max, min);                                     \
  test(name, pos, pos);                                     \
  test(name, pos, zero);                                    \
  test(name, neg, pos);                                     \
  test(name, min, pos);                                     \
  test(name, zero, zero);                                   \
  test(name, neg, zero);                                    \
  test(name, min, zero);                                    \
  test(name, neg, neg);                                     \
  test(name, min, neg);                                     \
  test(name, min, min);

// All three combinations with repetition
#define allThreeCombRep(test, name, max, pos, zero, neg, min) \
  test(name, max, max, max);                                  \
  test(name, max, max, pos);                                  \
  test(name, max, max, zero);                                 \
  test(name, max, max, neg);                                  \
  test(name, max, max, min);                                  \
  test(name, max, pos, pos);                                  \
  test(name, max, pos, zero);                                 \
  test(name, max, neg, pos);                                  \
  test(name, max, min, pos);                                  \
  test(name, max, zero, zero);                                \
  test(name, max, neg, zero);                                 \
  test(name, max, min, zero);                                 \
  test(name, max, neg, neg);                                  \
  test(name, max, min, neg);                                  \
  test(name, max, min, min);                                  \
  test(name, pos, pos, pos);                                  \
  test(name, pos, pos, zero);                                 \
  test(name, neg, pos, pos);                                  \
  test(name, min, pos, pos);                                  \
  test(name, pos, zero, zero);                                \
  test(name, neg, pos, zero);                                 \
  test(name, min, pos, zero);                                 \
  test(name, neg, neg, pos);                                  \
  test(name, min, neg, pos);                                  \
  test(name, min, min, pos);                                  \
  test(name, zero, zero, zero);                               \
  test(name, neg, zero, zero);                                \
  test(name, min, zero, zero);                                \
  test(name, neg, neg, zero);                                 \
  test(name, min, neg, zero);                                 \
  test(name, min, min, zero);                                 \
  test(name, neg, neg, neg);                                  \
  test(name, min, neg, neg);                                  \
  test(name, min, min, neg);                                  \
  test(name, min, min, min);

// All two permutations with repetition
#define allTwoPermRep(test, name, max, pos, zero, neg, min) \
  test(name, max, max);                                     \
  test(name, max, pos);                                     \
  test(name, max, zero);                                    \
  test(name, max, neg);                                     \
  test(name, max, min);                                     \
  test(name, pos, max);                                     \
  test(name, pos, pos);                                     \
  test(name, pos, zero);                                    \
  test(name, pos, neg);                                     \
  test(name, pos, min);                                     \
  test(name, zero, max);                                    \
  test(name, zero, pos);                                    \
  test(name, zero, zero);                                   \
  test(name, zero, neg);                                    \
  test(name, zero, min);                                    \
  test(name, neg, max);                                     \
  test(name, neg, pos);                                     \
  test(name, neg, zero);                                    \
  test(name, neg, neg);                                     \
  test(name, neg, min);                                     \
  test(name, min, max);                                     \
  test(name, min, pos);                                     \
  test(name, min, zero);                                    \
  test(name, min, neg);                                     \
  test(name, min, min);

// All three permutations with repetition
#define allThreePermRep(test, name, max, pos, zero, neg, min) \
  test(name, max, max, max);                                  \
  test(name, max, max, pos);                                  \
  test(name, max, max, zero);                                 \
  test(name, max, max, neg);                                  \
  test(name, max, max, min);                                  \
  test(name, max, pos, max);                                  \
  test(name, max, pos, pos);                                  \
  test(name, max, pos, zero);                                 \
  test(name, max, pos, neg);                                  \
  test(name, max, pos, min);                                  \
  test(name, max, zero, max);                                 \
  test(name, max, zero, pos);                                 \
  test(name, max, zero, zero);                                \
  test(name, max, zero, neg);                                 \
  test(name, max, zero, min);                                 \
  test(name, max, neg, max);                                  \
  test(name, max, neg, pos);                                  \
  test(name, max, neg, zero);                                 \
  test(name, max, neg, neg);                                  \
  test(name, max, neg, min);                                  \
  test(name, max, min, max);                                  \
  test(name, max, min, pos);                                  \
  test(name, max, min, zero);                                 \
  test(name, max, min, neg);                                  \
  test(name, max, min, min);                                  \
  test(name, pos, max, max);                                  \
  test(name, pos, max, pos);                                  \
  test(name, pos, max, zero);                                 \
  test(name, pos, max, neg);                                  \
  test(name, pos, max, min);                                  \
  test(name, pos, pos, max);                                  \
  test(name, pos, pos, pos);                                  \
  test(name, pos, pos, zero);                                 \
  test(name, pos, pos, neg);                                  \
  test(name, pos, pos, min);                                  \
  test(name, pos, zero, max);                                 \
  test(name, pos, zero, pos);                                 \
  test(name, pos, zero, zero);                                \
  test(name, pos, zero, neg);                                 \
  test(name, pos, zero, min);                                 \
  test(name, pos, neg, max);                                  \
  test(name, pos, neg, pos);                                  \
  test(name, pos, neg, zero);                                 \
  test(name, pos, neg, neg);                                  \
  test(name, pos, neg, min);                                  \
  test(name, pos, min, max);                                  \
  test(name, pos, min, pos);                                  \
  test(name, pos, min, zero);                                 \
  test(name, pos, min, neg);                                  \
  test(name, pos, min, min);                                  \
  test(name, zero, max, max);                                 \
  test(name, zero, max, pos);                                 \
  test(name, zero, max, zero);                                \
  test(name, zero, max, neg);                                 \
  test(name, zero, max, min);                                 \
  test(name, zero, pos, max);                                 \
  test(name, zero, pos, pos);                                 \
  test(name, zero, pos, zero);                                \
  test(name, zero, pos, neg);                                 \
  test(name, zero, pos, min);                                 \
  test(name, zero, zero, max);                                \
  test(name, zero, zero, pos);                                \
  test(name, zero, zero, zero);                               \
  test(name, zero, zero, neg);                                \
  test(name, zero, zero, min);                                \
  test(name, zero, neg, max);                                 \
  test(name, zero, neg, pos);                                 \
  test(name, zero, neg, zero);                                \
  test(name, zero, neg, neg);                                 \
  test(name, zero, neg, min);                                 \
  test(name, zero, min, max);                                 \
  test(name, zero, min, pos);                                 \
  test(name, zero, min, zero);                                \
  test(name, zero, min, neg);                                 \
  test(name, zero, min, min);                                 \
  test(name, neg, max, max);                                  \
  test(name, neg, max, pos);                                  \
  test(name, neg, max, zero);                                 \
  test(name, neg, max, neg);                                  \
  test(name, neg, max, min);                                  \
  test(name, neg, pos, max);                                  \
  test(name, neg, pos, pos);                                  \
  test(name, neg, pos, zero);                                 \
  test(name, neg, pos, neg);                                  \
  test(name, neg, pos, min);                                  \
  test(name, neg, zero, max);                                 \
  test(name, neg, zero, pos);                                 \
  test(name, neg, zero, zero);                                \
  test(name, neg, zero, neg);                                 \
  test(name, neg, zero, min);                                 \
  test(name, neg, neg, max);                                  \
  test(name, neg, neg, pos);                                  \
  test(name, neg, neg, zero);                                 \
  test(name, neg, neg, neg);                                  \
  test(name, neg, neg, min);                                  \
  test(name, neg, min, max);                                  \
  test(name, neg, min, pos);                                  \
  test(name, neg, min, zero);                                 \
  test(name, neg, min, neg);                                  \
  test(name, neg, min, min);                                  \
  test(name, min, max, max);                                  \
  test(name, min, max, pos);                                  \
  test(name, min, max, zero);                                 \
  test(name, min, max, neg);                                  \
  test(name, min, max, min);                                  \
  test(name, min, pos, max);                                  \
  test(name, min, pos, pos);                                  \
  test(name, min, pos, zero);                                 \
  test(name, min, pos, neg);                                  \
  test(name, min, pos, min);                                  \
  test(name, min, zero, max);                                 \
  test(name, min, zero, pos);                                 \
  test(name, min, zero, zero);                                \
  test(name, min, zero, neg);                                 \
  test(name, min, zero, min);                                 \
  test(name, min, neg, max);                                  \
  test(name, min, neg, pos);                                  \
  test(name, min, neg, zero);                                 \
  test(name, min, neg, neg);                                  \
  test(name, min, neg, min);                                  \
  test(name, min, min, max);                                  \
  test(name, min, min, pos);                                  \
  test(name, min, min, zero);                                 \
  test(name, min, min, neg);                                  \
  test(name, min, min, min);

#endif  // EIGEN_MIPP_TEST_COMBINATIONS_H