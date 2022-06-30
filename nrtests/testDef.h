#ifndef EIGEN_MIPP_TEST_DEF_H
#define EIGEN_MIPP_TEST_DEF_H

// Tests macro definition
#define vectorFullLongTemplateTest(name, template, args...) \
  vectorSingleTypeFullTest(long, template, INT_CAST_TO_MIPP_FULL, name, args)

#define vectorHalfFloatTemplateTest(name, template, args...) \
  vectorSingleTypeHalfTest(float, template, FLOAT_CAST_TO_MIPP_HALF, name, args)
#define vectorHalfDoubleTemplateTest(name, template, args...) \
  vectorSingleTypeHalfTest(double, template, DOUBLE_CAST_TO_MIPP_HALF, name, args)
#define vectorHalfIntTemplateTest(name, template, args...) \
  vectorSingleTypeHalfTest(int, template, INT_CAST_TO_MIPP_HALF, name, args)

#define vectorFullFloatTemplateTest(name, template, args...) \
  vectorSingleTypeFullTest(float, template, FLOAT_CAST_TO_MIPP_FULL, name, args)
#define vectorFullDoubleTemplateTest(name, template, args...) \
  vectorSingleTypeFullTest(double, template, DOUBLE_CAST_TO_MIPP_FULL, name, args)
#define vectorFullIntTemplateTest(name, template, args...) \
  vectorSingleTypeFullTest(int, template, INT_CAST_TO_MIPP_FULL, name, args)

#define vectorHalfBoolTemplateTest(name, template, args...) \
  vectorSingleTypeHalfTest(int8_t, template, INT_CAST_TO_MIPP_HALF, name, args)
#define vectorHalfEigenHalfTemplateTest(name, template, args...) \
  vectorSingleTypeHalfTest(short, template, INT_CAST_TO_MIPP_HALF, name, args)
#define vectorHalfBfloat16TemplateTest(name, template, args...) \
  vectorSingleTypeHalfTest(short, template, INT_CAST_TO_MIPP_HALF, name, args)

/* Packet4f with one arg of loaded vector */
#define tests4FloatMin2MaxOneArgLoaded(str, funName)                                                  \
  beginTest(str);                                                                                     \
                                                                                                      \
  MIN2MAX_4_FLOAT_VECTOR_LOADED                                                                       \
                                                                                                      \
  min2MaxTests(vectorHalfFloatTemplateTest, funName, Packet4f, fhvmax, fhv36, fhv0, fhv_240, fhvmin); \
                                                                                                      \
  endTest();

/* Packet2d with one arg of loaded vector */
#define tests2DoubleMin2MaxOneArgLoaded(str, funName)                                                  \
  beginTest(str);                                                                                      \
                                                                                                       \
  MIN2MAX_2_DOUBLE_VECTOR_LOADED                                                                       \
                                                                                                       \
  min2MaxTests(vectorHalfDoubleTemplateTest, funName, Packet2d, dhvmax, dhv36, dhv0, dhv_240, dhvmin); \
                                                                                                       \
  endTest();

/* Packet4i with one arg of loaded vector */
#define tests4IntMin2MaxOneArgLoaded(str, funName)                                                  \
  beginTest(str);                                                                                   \
                                                                                                    \
  MIN2MAX_4_INT_VECTOR_LOADED                                                                       \
                                                                                                    \
  min2MaxTests(vectorHalfIntTemplateTest, funName, Packet4i, ihvmax, ihv36, ihv0, ihv_240, ihvmin); \
                                                                                                    \
  endTest();

/* Packet16b with one arg of loaded vector */
#define tests16BoolMin2MaxOneArgLoaded(str, funName)       \
  beginTest(str);                                          \
                                                           \
  MIN2MAX_16_BOOL_VECTOR_LOADED                            \
                                                           \
  vectorHalfBoolTemplateTest(funName, Packet16b, bvtrue);  \
  vectorHalfBoolTemplateTest(funName, Packet16b, bvfalse); \
                                                           \
  endTest();

/* Packet8f with one arg of loaded vector */
#define tests8FloatMin2MaxOneArgLoaded(str, funName)                                             \
  beginTest(str);                                                                                \
                                                                                                 \
  MIN2MAX_8_FLOAT_VECTOR_LOADED                                                                  \
                                                                                                 \
  min2MaxTests(vectorFullFloatTemplateTest, funName, Packet8f, fvmax, fv36, fv0, fv_240, fvmin); \
                                                                                                 \
  endTest();

/* Packet4d with one arg of loaded vector */
#define tests4DoubleMin2MaxOneArgLoaded(str, funName)                                             \
  beginTest(str);                                                                                 \
                                                                                                  \
  MIN2MAX_4_DOUBLE_VECTOR_LOADED                                                                  \
                                                                                                  \
  min2MaxTests(vectorFullDoubleTemplateTest, funName, Packet4d, dvmax, dv36, dv0, dv_240, dvmin); \
                                                                                                  \
  endTest();

/* Packet8i with one arg of loaded vector */
#define tests8IntMin2MaxOneArgLoaded(str, funName)                                             \
  beginTest(str);                                                                              \
                                                                                               \
  MIN2MAX_8_INT_VECTOR_LOADED                                                                  \
                                                                                               \
  min2MaxTests(vectorFullIntTemplateTest, funName, Packet8i, ivmax, iv36, iv0, iv_240, ivmin); \
                                                                                               \
  endTest();

/* Packet8h with one arg of loaded vector */
#define tests8HalfMin2MaxOneArgLoaded(str, funName)                                                  \
  beginTest(str);                                                                                    \
                                                                                                     \
  MIN2MAX_8_HALF_VECTOR_LOADED                                                                       \
                                                                                                     \
  min2MaxTests(vectorHalfEigenHalfTemplateTest, funName, Packet8h, hvmax, hv36, hv0, hv_240, hvmin); \
                                                                                                     \
  endTest();

/* Packet8bf with one arg of loaded vector */
#define tests8Bfloat16Min2MaxOneArgLoaded(str, funName)                                                   \
  beginTest(str);                                                                                         \
                                                                                                          \
  MIN2MAX_8_BFLOAT16_VECTOR_LOADED                                                                        \
                                                                                                          \
  min2MaxTests(vectorHalfBfloat16TemplateTest, funName, Packet8bf, bfvmax, bfv36, bfv0, bfv_240, bfvmin); \
                                                                                                          \
  endTest();

/* Packet4l with one arg of loaded vector */
#define tests4LongMin2MaxOneArgLoaded(str, funName)                                             \
  beginTest(str);                                                                               \
                                                                                                \
  MIN2MAX_4_LONG_VECTOR_LOADED                                                                  \
                                                                                                \
  min2MaxTests(vectorFullLongTemplateTest, funName, Packet4l, lvmax, lv36, lv0, lv_240, lvmin); \
                                                                                                \
  endTest();

/* Packet4f with two args and permutations with repetition */
#define tests4FloatMin2MaxTwoArgsPermRep(str, funName)                                                 \
  beginTest(str);                                                                                      \
                                                                                                       \
  MIN2MAX_4_FLOAT_VECTOR_LOADED                                                                        \
                                                                                                       \
  allTwoPermRep(vectorHalfFloatTemplateTest, funName, Packet4f, fhvmax, fhv36, fhv0, fhv_240, fhvmin); \
                                                                                                       \
  endTest();

/* Packet2d with two args and permutations with repetition */
#define tests2DoubleMin2MaxTwoArgsPermRep(str, funName)                                                 \
  beginTest(str);                                                                                       \
                                                                                                        \
  MIN2MAX_2_DOUBLE_VECTOR_LOADED                                                                        \
                                                                                                        \
  allTwoPermRep(vectorHalfDoubleTemplateTest, funName, Packet2d, dhvmax, dhv36, dhv0, dhv_240, dhvmin); \
                                                                                                        \
  endTest();

/* Packet4i with two args and permutations with repetition */
#define tests4IntMin2MaxTwoArgsPermRep(str, funName)                                                 \
  beginTest(str);                                                                                    \
                                                                                                     \
  MIN2MAX_4_INT_VECTOR_LOADED                                                                        \
                                                                                                     \
  allTwoPermRep(vectorHalfIntTemplateTest, funName, Packet4i, ihvmax, ihv36, ihv0, ihv_240, ihvmin); \
                                                                                                     \
  endTest();

/* Packet16b with two args and permutations with repetition */
#define tests16BoolMin2MaxTwoArgsPermRep(str, funName)               \
  beginTest(str);                                                    \
                                                                     \
  MIN2MAX_16_BOOL_VECTOR_LOADED                                      \
                                                                     \
  vectorHalfBoolTemplateTest(FUN2TEST, Packet16b, bvtrue, bvtrue);   \
  vectorHalfBoolTemplateTest(FUN2TEST, Packet16b, bvtrue, bvfalse);  \
  vectorHalfBoolTemplateTest(FUN2TEST, Packet16b, bvfalse, bvtrue);  \
  vectorHalfBoolTemplateTest(FUN2TEST, Packet16b, bvfalse, bvfalse); \
                                                                     \
  endTest();

/* Packet8f with two args and permutations with repetition */
#define tests8FloatMin2MaxTwoArgsPermRep(str, funName)                                            \
  beginTest(str);                                                                                 \
                                                                                                  \
  MIN2MAX_8_FLOAT_VECTOR_LOADED                                                                   \
                                                                                                  \
  allTwoPermRep(vectorFullFloatTemplateTest, funName, Packet8f, fvmax, fv36, fv0, fv_240, fvmin); \
                                                                                                  \
  endTest();

/* Packet4d with two args and permutations with repetition */
#define tests4DoubleMin2MaxTwoArgsPermRep(str, funName)                                            \
  beginTest(str);                                                                                  \
                                                                                                   \
  MIN2MAX_4_DOUBLE_VECTOR_LOADED                                                                   \
                                                                                                   \
  allTwoPermRep(vectorFullDoubleTemplateTest, funName, Packet4d, dvmax, dv36, dv0, dv_240, dvmin); \
                                                                                                   \
  endTest();

/* Packet8i with two args and permutations with repetition */
#define tests8IntMin2MaxTwoArgsPermRep(str, funName)                                            \
  beginTest(str);                                                                               \
                                                                                                \
  MIN2MAX_8_INT_VECTOR_LOADED                                                                   \
                                                                                                \
  allTwoPermRep(vectorFullIntTemplateTest, funName, Packet8i, ivmax, iv36, iv0, iv_240, ivmin); \
                                                                                                \
  endTest();

/* Packet8h with two args and permutations with repetition */
#define tests8HalfMin2MaxTwoArgsPermRep(str, funName)                                                 \
  beginTest(str);                                                                                     \
                                                                                                      \
  MIN2MAX_8_HALF_VECTOR_LOADED                                                                        \
                                                                                                      \
  allTwoPermRep(vectorHalfEigenHalfTemplateTest, funName, Packet8h, hvmax, hv36, hv0, hv_240, hvmin); \
                                                                                                      \
  endTest();

/* Packet8bf with two args and permutations with repetition */
#define tests8Bfloat16Min2MaxTwoArgsPermRep(str, funName)                                                  \
  beginTest(str);                                                                                          \
                                                                                                           \
  MIN2MAX_8_BFLOAT16_VECTOR_LOADED                                                                         \
                                                                                                           \
  allTwoPermRep(vectorHalfBfloat16TemplateTest, funName, Packet8bf, bfvmax, bfv36, bfv0, bfv_240, bfvmin); \
                                                                                                           \
  endTest();

/* Packet4l with two args and permutations with repetition */
#define tests4LongMin2MaxTwoArgsPermRep(str, funName)                                            \
  beginTest(str);                                                                                \
                                                                                                 \
  MIN2MAX_4_LONG_VECTOR_LOADED                                                                   \
                                                                                                 \
  allTwoPermRep(vectorFullLongTemplateTest, funName, Packet4l, lvmax, lv36, lv0, lv_240, lvmin); \
                                                                                                 \
  endTest();

/* Packet4f with two args and combinations with repetition */
#define tests4FloatMin2MaxTwoArgsCombRep(str, funName)                                                 \
  beginTest(str);                                                                                      \
                                                                                                       \
  MIN2MAX_4_FLOAT_VECTOR_LOADED                                                                        \
                                                                                                       \
  allTwoCombRep(vectorHalfFloatTemplateTest, funName, Packet4f, fhvmax, fhv36, fhv0, fhv_240, fhvmin); \
                                                                                                       \
  endTest();

/* Packet2d with two args and combinations with repetition */
#define tests2DoubleMin2MaxTwoArgsCombRep(str, funName)                                                 \
  beginTest(str);                                                                                       \
                                                                                                        \
  MIN2MAX_2_DOUBLE_VECTOR_LOADED                                                                        \
                                                                                                        \
  allTwoCombRep(vectorHalfDoubleTemplateTest, funName, Packet2d, dhvmax, dhv36, dhv0, dhv_240, dhvmin); \
                                                                                                        \
  endTest();

/* Packet4i with two args and combinations with repetition */
#define tests4IntMin2MaxTwoArgsCombRep(str, funName)                                                 \
  beginTest(str);                                                                                    \
                                                                                                     \
  MIN2MAX_4_INT_VECTOR_LOADED                                                                        \
                                                                                                     \
  allTwoCombRep(vectorHalfIntTemplateTest, funName, Packet4i, ihvmax, ihv36, ihv0, ihv_240, ihvmin); \
                                                                                                     \
  endTest();

/* Packet16b with two args and combinations with repetition */
#define tests16BoolMin2MaxTwoArgsCombRep(str, funName)              \
  beginTest(str);                                                   \
                                                                    \
  MIN2MAX_16_BOOL_VECTOR_LOADED                                     \
                                                                    \
  vectorHalfBoolTemplateTest(funName, Packet16b, bvtrue, bvtrue);   \
  vectorHalfBoolTemplateTest(funName, Packet16b, bvtrue, bvfalse);  \
  vectorHalfBoolTemplateTest(funName, Packet16b, bvfalse, bvtrue);  \
  vectorHalfBoolTemplateTest(funName, Packet16b, bvfalse, bvfalse); \
                                                                    \
  endTest();

/* Packet8f with two args and combinations with repetition */
#define tests8FloatMin2MaxTwoArgsCombRep(str, funName)                                            \
  beginTest(str);                                                                                 \
                                                                                                  \
  MIN2MAX_8_FLOAT_VECTOR_LOADED                                                                   \
                                                                                                  \
  allTwoCombRep(vectorFullFloatTemplateTest, funName, Packet8f, fvmax, fv36, fv0, fv_240, fvmin); \
                                                                                                  \
  endTest();

/* Packet4d with two args and combinations with repetition */
#define tests4DoubleMin2MaxTwoArgsCombRep(str, funName)                                            \
  beginTest(str);                                                                                  \
                                                                                                   \
  MIN2MAX_4_DOUBLE_VECTOR_LOADED                                                                   \
                                                                                                   \
  allTwoCombRep(vectorFullDoubleTemplateTest, funName, Packet4d, dvmax, dv36, dv0, dv_240, dvmin); \
                                                                                                   \
  endTest();

/* Packet8i with two args and combinations with repetition */
#define tests8IntMin2MaxTwoArgsCombRep(str, funName)                                            \
  beginTest(str);                                                                               \
                                                                                                \
  MIN2MAX_8_INT_VECTOR_LOADED                                                                   \
                                                                                                \
  allTwoCombRep(vectorFullIntTemplateTest, funName, Packet8i, ivmax, iv36, iv0, iv_240, ivmin); \
                                                                                                \
  endTest();

/* Packet8h with two args and combinations with repetition */
#define tests8HalfMin2MaxTwoArgsCombRep(str, funName)                                                 \
  beginTest(str);                                                                                     \
                                                                                                      \
  MIN2MAX_8_HALF_VECTOR_LOADED                                                                        \
                                                                                                      \
  allTwoCombRep(vectorHalfEigenHalfTemplateTest, funName, Packet8h, hvmax, hv36, hv0, hv_240, hvmin); \
                                                                                                      \
  endTest();

/* Packet8bf with two args and combinations with repetition */
#define tests8Bfloat16Min2MaxTwoArgsCombRep(str, funName)                                                  \
  beginTest(str);                                                                                          \
                                                                                                           \
  MIN2MAX_8_BFLOAT16_VECTOR_LOADED                                                                         \
                                                                                                           \
  allTwoCombRep(vectorHalfBfloat16TemplateTest, funName, Packet8bf, bfvmax, bfv36, bfv0, bfv_240, bfvmin); \
                                                                                                           \
  endTest();

/* Packet4l with two args and combinations with repetition */
#define tests4LongMin2MaxTwoArgsCombRep(str, funName)                                            \
  beginTest(str);                                                                                \
                                                                                                 \
  MIN2MAX_4_LONG_VECTOR_LOADED                                                                   \
                                                                                                 \
  allTwoCombRep(vectorFullLongTemplateTest, funName, Packet4l, lvmax, lv36, lv0, lv_240, lvmin); \
                                                                                                 \
  endTest();

/* Packet4f with three args and permutations with repetition */
#define tests4FloatMin2MaxThreeArgsPermRep(str, funName)                                                 \
  beginTest(str);                                                                                        \
                                                                                                         \
  MIN2MAX_4_FLOAT_VECTOR_LOADED                                                                          \
                                                                                                         \
  allThreePermRep(vectorHalfFloatTemplateTest, funName, Packet4f, fhvmax, fhv36, fhv0, fhv_240, fhvmin); \
                                                                                                         \
  endTest();

/* Packet2d with three args and permutations with repetition */
#define tests2DoubleMin2MaxThreeArgsPermRep(str, funName)                                                 \
  beginTest(str);                                                                                         \
                                                                                                          \
  MIN2MAX_2_DOUBLE_VECTOR_LOADED                                                                          \
                                                                                                          \
  allThreePermRep(vectorHalfDoubleTemplateTest, funName, Packet2d, dhvmax, dhv36, dhv0, dhv_240, dhvmin); \
                                                                                                          \
  endTest();

/* Packet4i with three args and permutations with repetition */
#define tests4IntMin2MaxThreeArgsPermRep(str, funName)                                                 \
  beginTest(str);                                                                                      \
                                                                                                       \
  MIN2MAX_4_INT_VECTOR_LOADED                                                                          \
                                                                                                       \
  allThreePermRep(vectorHalfIntTemplateTest, funName, Packet4i, ihvmax, ihv36, ihv0, ihv_240, ihvmin); \
                                                                                                       \
  endTest();

/* Packet16b with three args and permutations with repetition */
#define tests16BoolMin2MaxThreeArgsPermRep(str, funName)                     \
  beginTest(str);                                                            \
                                                                             \
  MIN2MAX_16_BOOL_VECTOR_LOADED                                              \
                                                                             \
  vectorHalfBoolTemplateTest(funName, Packet16b, bvtrue, bvtrue, bvtrue);    \
  vectorHalfBoolTemplateTest(funName, Packet16b, bvtrue, bvtrue, bvfalse);   \
  vectorHalfBoolTemplateTest(funName, Packet16b, bvtrue, bvfalse, bvtrue);   \
  vectorHalfBoolTemplateTest(funName, Packet16b, bvtrue, bvfalse, bvfalse);  \
  vectorHalfBoolTemplateTest(funName, Packet16b, bvfalse, bvtrue, bvtrue);   \
  vectorHalfBoolTemplateTest(funName, Packet16b, bvfalse, bvtrue, bvfalse);  \
  vectorHalfBoolTemplateTest(funName, Packet16b, bvfalse, bvfalse, bvtrue);  \
  vectorHalfBoolTemplateTest(funName, Packet16b, bvfalse, bvfalse, bvfalse); \
                                                                             \
  endTest();

/* Packet8f with three args and permutations with repetition */
#define tests8FloatMin2MaxThreeArgsPermRep(str, funName)                                            \
  beginTest(str);                                                                                   \
                                                                                                    \
  MIN2MAX_8_FLOAT_VECTOR_LOADED                                                                     \
                                                                                                    \
  allThreePermRep(vectorFullFloatTemplateTest, funName, Packet8f, fvmax, fv36, fv0, fv_240, fvmin); \
                                                                                                    \
  endTest();

/* Packet4d with three args and permutations with repetition */
#define tests4DoubleMin2MaxThreeArgsPermRep(str, funName)                                            \
  beginTest(str);                                                                                    \
                                                                                                     \
  MIN2MAX_4_DOUBLE_VECTOR_LOADED                                                                     \
                                                                                                     \
  allThreePermRep(vectorFullDoubleTemplateTest, funName, Packet4d, dvmax, dv36, dv0, dv_240, dvmin); \
                                                                                                     \
  endTest();

/* Packet8i with three args and permutations with repetition */
#define tests8IntMin2MaxThreeArgsPermRep(str, funName)                                            \
  beginTest(str);                                                                                 \
                                                                                                  \
  MIN2MAX_8_INT_VECTOR_LOADED                                                                     \
                                                                                                  \
  allThreePermRep(vectorFullIntTemplateTest, funName, Packet8i, ivmax, iv36, iv0, iv_240, ivmin); \
                                                                                                  \
  endTest();

/* Packet8h with three args and permutations with repetition */
#define tests8HalfMin2MaxThreeArgsPermRep(str, funName)                                                 \
  beginTest(str);                                                                                       \
                                                                                                        \
  MIN2MAX_8_HALF_VECTOR_LOADED                                                                          \
                                                                                                        \
  allThreePermRep(vectorHalfEigenHalfTemplateTest, funName, Packet8h, hvmax, hv36, hv0, hv_240, hvmin); \
                                                                                                        \
  endTest();

/* Packet8bf with three args and permutations with repetition */
#define tests8Bfloat16Min2MaxThreeArgsPermRep(str, funName)                                                  \
  beginTest(str);                                                                                            \
                                                                                                             \
  MIN2MAX_8_BFLOAT16_VECTOR_LOADED                                                                           \
                                                                                                             \
  allThreePermRep(vectorHalfBfloat16TemplateTest, funName, Packet8bf, bfvmax, bfv36, bfv0, bfv_240, bfvmin); \
                                                                                                             \
  endTest();

/* Packet4l with three args and permutations with repetition */
#define tests4LongMin2MaxThreeArgsPermRep(str, funName)                                            \
  beginTest(str);                                                                                  \
                                                                                                   \
  MIN2MAX_4_LONG_VECTOR_LOADED                                                                     \
                                                                                                   \
  allThreePermRep(vectorFullLongTemplateTest, funName, Packet4l, lvmax, lv36, lv0, lv_240, lvmin); \
                                                                                                   \
  endTest();

/* Packet4f with one arg */
#define tests4FloatMin2MaxOneArg(str, funName)                                                        \
  beginTest(str);                                                                                     \
                                                                                                      \
  MIN2MAX_4_FLOAT_VECTOR                                                                              \
                                                                                                      \
  min2MaxTests(vectorHalfFloatTemplateTest, funName, Packet4f, fhvmax, fhv36, fhv0, fhv_240, fhvmin); \
                                                                                                      \
  endTest();

/* Packet2d with one arg */
#define tests2DoubleMin2MaxOneArg(str, funName)                                                        \
  beginTest(str);                                                                                      \
                                                                                                       \
  MIN2MAX_2_DOUBLE_VECTOR                                                                              \
                                                                                                       \
  min2MaxTests(vectorHalfDoubleTemplateTest, funName, Packet2d, dhvmax, dhv36, dhv0, dhvmin, dhv_240); \
                                                                                                       \
  endTest();

/* Packet4i with one arg */
#define tests4IntMin2MaxOneArg(str, funName)                                                        \
  beginTest(str);                                                                                   \
                                                                                                    \
  MIN2MAX_4_INT_VECTOR                                                                              \
                                                                                                    \
  min2MaxTests(vectorHalfIntTemplateTest, funName, Packet4i, ihvmax, ihv36, ihv0, ihv_240, ihvmin); \
                                                                                                    \
  endTest();

/* Packet16b with one arg */
#define tests16BoolMin2MaxOneArg(str, funName)             \
  beginTest(str);                                          \
                                                           \
  MIN2MAX_16_BOOL_VECTOR                                   \
                                                           \
  vectorHalfBoolTemplateTest(funName, Packet16b, bvtrue);  \
  vectorHalfBoolTemplateTest(funName, Packet16b, bvfalse); \
                                                           \
  endTest();

/* Packet8f with one arg */
#define tests8FloatMin2MaxOneArg(str, funName)                                                   \
  beginTest(str);                                                                                \
                                                                                                 \
  MIN2MAX_8_FLOAT_VECTOR                                                                         \
                                                                                                 \
  min2MaxTests(vectorFullFloatTemplateTest, funName, Packet8f, fvmax, fv36, fv0, fv_240, fvmin); \
                                                                                                 \
  endTest();

/* Packet4d with one arg */
#define tests4DoubleMin2MaxOneArg(str, funName)                                                   \
  beginTest(str);                                                                                 \
                                                                                                  \
  MIN2MAX_4_DOUBLE_VECTOR                                                                         \
                                                                                                  \
  min2MaxTests(vectorFullDoubleTemplateTest, funName, Packet4d, dvmax, dv36, dv0, dv_240, dvmin); \
                                                                                                  \
  endTest();

/* Packet8i with one arg */
#define tests8IntMin2MaxOneArg(str, funName)                                                   \
  beginTest(str);                                                                              \
                                                                                               \
  MIN2MAX_8_INT_VECTOR                                                                         \
                                                                                               \
  min2MaxTests(vectorFullIntTemplateTest, funName, Packet8i, ivmax, iv36, iv0, iv_240, ivmin); \
                                                                                               \
  endTest();

/* Packet8h with one arg */
#define tests8HalfMin2MaxOneArg(str, funName)                                                        \
  beginTest(str);                                                                                    \
                                                                                                     \
  MIN2MAX_8_HALF_VECTOR                                                                              \
                                                                                                     \
  min2MaxTests(vectorHalfEigenHalfTemplateTest, funName, Packet8h, hvmax, hv36, hv0, hv_240, hvmin); \
                                                                                                     \
  endTest();

/* Packet8bf with one arg */
#define tests8Bfloat16Min2MaxOneArg(str, funName)                                                         \
  beginTest(str);                                                                                         \
                                                                                                          \
  MIN2MAX_8_BFLOAT16_VECTOR                                                                               \
                                                                                                          \
  min2MaxTests(vectorHalfBfloat16TemplateTest, funName, Packet8bf, bfvmax, bfv36, bfv0, bfv_240, bfvmin); \
                                                                                                          \
  endTest();

/* Packet4l with one arg */
#define tests4LongMin2MaxOneArg(str, funName)                                                   \
  beginTest(str);                                                                               \
                                                                                                \
  MIN2MAX_4_LONG_VECTOR                                                                         \
                                                                                                \
  min2MaxTests(vectorFullLongTemplateTest, funName, Packet4l, lvmax, lv36, lv0, lv_240, lvmin); \
                                                                                                \
  endTest();

/* Packet4f with one arg unaligned */
#define tests4FloatMin2MaxOneArgUnaligned(str, funName)                                               \
  beginTest(str);                                                                                     \
                                                                                                      \
  MIN2MAX_4_FLOAT_VECTOR_U                                                                            \
                                                                                                      \
  min2MaxTests(vectorHalfFloatTemplateTest, funName, Packet4f, fhvmax, fhv36, fhv0, fhv_240, fhvmin); \
                                                                                                      \
  endTest();

/* Packet2d with one arg unaligned */
#define tests2DoubleMin2MaxOneArgUnaligned(str, funName)                                               \
  beginTest(str);                                                                                      \
                                                                                                       \
  MIN2MAX_2_DOUBLE_VECTOR_U                                                                            \
                                                                                                       \
  min2MaxTests(vectorHalfDoubleTemplateTest, funName, Packet2d, dhvmax, dhv36, dhv0, dhvmin, dhv_240); \
                                                                                                       \
  endTest();

/* Packet4i with one arg unaligned */
#define tests4IntMin2MaxOneArgUnaligned(str, funName)                                               \
  beginTest(str);                                                                                   \
                                                                                                    \
  MIN2MAX_4_INT_VECTOR_U                                                                            \
                                                                                                    \
  min2MaxTests(vectorHalfIntTemplateTest, funName, Packet4i, ihvmax, ihv36, ihv0, ihv_240, ihvmin); \
                                                                                                    \
  endTest();

/* Packet16b with one arg unaligned */
#define tests16BoolMin2MaxOneArgUnaligned(str, funName)    \
  beginTest(str);                                          \
                                                           \
  MIN2MAX_16_BOOL_VECTOR_U                                 \
                                                           \
  vectorHalfBoolTemplateTest(funName, Packet16b, bvtrue);  \
  vectorHalfBoolTemplateTest(funName, Packet16b, bvfalse); \
                                                           \
  endTest();

/* Packet8f with one arg unaligned */
#define tests8FloatMin2MaxOneArgUnaligned(str, funName)                                          \
  beginTest(str);                                                                                \
                                                                                                 \
  MIN2MAX_8_FLOAT_VECTOR_U                                                                       \
                                                                                                 \
  min2MaxTests(vectorFullFloatTemplateTest, funName, Packet8f, fvmax, fv36, fv0, fv_240, fvmin); \
                                                                                                 \
  endTest();

/* Packet4d with one arg unaligned */
#define tests4DoubleMin2MaxOneArgUnaligned(str, funName)                                          \
  beginTest(str);                                                                                 \
                                                                                                  \
  MIN2MAX_4_DOUBLE_VECTOR_U                                                                       \
                                                                                                  \
  min2MaxTests(vectorFullDoubleTemplateTest, funName, Packet4d, dvmax, dv36, dv0, dv_240, dvmin); \
                                                                                                  \
  endTest();

/* Packet8i with one arg unaligned */
#define tests8IntMin2MaxOneArgUnaligned(str, funName)                                          \
  beginTest(str);                                                                              \
                                                                                               \
  MIN2MAX_8_INT_VECTOR_U                                                                       \
                                                                                               \
  min2MaxTests(vectorFullIntTemplateTest, funName, Packet8i, ivmax, iv36, iv0, iv_240, ivmin); \
                                                                                               \
  endTest();

/* Packet8h with one arg unaligned */
#define tests8HalfMin2MaxOneArgUnaligned(str, funName)                                               \
  beginTest(str);                                                                                    \
                                                                                                     \
  MIN2MAX_8_HALF_VECTOR_U                                                                            \
                                                                                                     \
  min2MaxTests(vectorHalfEigenHalfTemplateTest, funName, Packet8h, hvmax, hv36, hv0, hv_240, hvmin); \
                                                                                                     \
  endTest();

/* Packet8bf with one arg unaligned */
#define tests8Bfloat16Min2MaxOneArgUnaligned(str, funName)                                                \
  beginTest(str);                                                                                         \
                                                                                                          \
  MIN2MAX_8_BFLOAT16_VECTOR_U                                                                             \
                                                                                                          \
  min2MaxTests(vectorHalfBfloat16TemplateTest, funName, Packet8bf, bfvmax, bfv36, bfv0, bfv_240, bfvmin); \
                                                                                                          \
  endTest();

/* Packet4l with one arg unaligned */
#define tests4LongMin2MaxOneArgUnaligned(str, funName)                                          \
  beginTest(str);                                                                               \
                                                                                                \
  MIN2MAX_4_LONG_VECTOR_U                                                                       \
                                                                                                \
  min2MaxTests(vectorFullLongTemplateTest, funName, Packet4l, lvmax, lv36, lv0, lv_240, lvmin); \
                                                                                                \
  endTest();

#endif  // EIGEN_MIPP_TEST_DEF_H