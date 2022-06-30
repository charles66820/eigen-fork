#ifndef EIGEN_MIPP_TEST_DEF_H
#define EIGEN_MIPP_TEST_DEF_H

// Tests macro definition
#define vectorFullLongTemplateTest(template, name, args...) \
  vectorSingleTypeFullTest(long, template, INT_CAST_TO_MIPP_FULL, name, args)

#define vectorHalfFloatTemplateTest(template, name, args...) \
  vectorSingleTypeHalfTest(float, template, FLOAT_CAST_TO_MIPP_HALF, name, args)
#define vectorHalfDoubleTemplateTest(template, name, args...) \
  vectorSingleTypeHalfTest(double, template, DOUBLE_CAST_TO_MIPP_HALF, name, args)
#define vectorHalfIntTemplateTest(template, name, args...) \
  vectorSingleTypeHalfTest(int, template, INT_CAST_TO_MIPP_HALF, name, args)

#define vectorFullFloatTemplateTest(template, name, args...) \
  vectorSingleTypeFullTest(float, template, FLOAT_CAST_TO_MIPP_FULL, name, args)
#define vectorFullDoubleTemplateTest(template, name, args...) \
  vectorSingleTypeFullTest(double, template, DOUBLE_CAST_TO_MIPP_FULL, name, args)
#define vectorFullIntTemplateTest(template, name, args...) \
  vectorSingleTypeFullTest(int, template, INT_CAST_TO_MIPP_FULL, name, args)

#define vectorHalfBoolTemplateTest(template, name, args...) \
  vectorSingleTypeHalfTest(int8_t, template, INT_CAST_TO_MIPP_HALF, name, args)
#define vectorHalfEigenHalfTemplateTest(template, name, args...) \
  vectorSingleTypeHalfTest(short, template, INT_CAST_TO_MIPP_HALF, name, args)
#define vectorHalfBfloat16TemplateTest(template, name, args...) \
  vectorSingleTypeHalfTest(short, template, INT_CAST_TO_MIPP_HALF, name, args)

#define vectorFullLongTest(name, args...) vectorFullLongTemplateTest(Packet4l, name, args)

#define vectorHalfFloatTest(name, args...) vectorHalfFloatTemplateTest(Packet4f, name, args)
#define vectorHalfDoubleTest(name, args...) vectorHalfDoubleTemplateTest(Packet2d, name, args)
#define vectorHalfIntTest(name, args...) vectorHalfIntTemplateTest(Packet4i, name, args)

#define vectorFullFloatTest(name, args...) vectorFullFloatTemplateTest(Packet8f, name, args)
#define vectorFullDoubleTest(name, args...) vectorFullDoubleTemplateTest(Packet4d, name, args)
#define vectorFullIntTest(name, args...) vectorFullIntTemplateTest(Packet8i, name, args)

#define vectorHalfBoolTest(name, args...) vectorHalfBoolTemplateTest(Packet16b, name, args)
#define vectorHalfEigenHalfTest(name, args...) vectorHalfEigenHalfTemplateTest(Packet8h, name, args)
#define vectorHalfBfloat16Test(name, args...) vectorHalfBfloat16TemplateTest(Packet8bf, name, args)

/* Packet4f with one arg */
#define tests4FloatMin2MaxOneArg(str, funName)                                      \
  beginTest(str);                                                                   \
                                                                                    \
  MIN2MAX_4_FLOAT_VECTOR_LOADED                                                     \
                                                                                    \
  min2MaxTests(vectorHalfFloatTest, funName, fhvmax, fhv36, fhv0, fhv_240, fhvmin); \
                                                                                    \
  endTest();

/* Packet2d with one arg */
#define tests2DoubleMin2MaxOneArg(str, funName)                                      \
  beginTest(str);                                                                    \
                                                                                     \
  MIN2MAX_2_DOUBLE_VECTOR_LOADED                                                     \
                                                                                     \
  min2MaxTests(vectorHalfDoubleTest, funName, dhvmax, dhv36, dhv0, dhv_240, dhvmin); \
                                                                                     \
  endTest();

/* Packet4i with one arg */
#define tests4IntMin2MaxOneArg(str, funName)                                      \
  beginTest(str);                                                                 \
                                                                                  \
  MIN2MAX_4_INT_VECTOR_LOADED                                                     \
                                                                                  \
  min2MaxTests(vectorHalfIntTest, funName, ihvmax, ihv36, ihv0, ihv_240, ihvmin); \
                                                                                  \
  endTest();

/* Packet16b with one arg */
#define tests16BoolMin2MaxOneArg(str, funName) \
  beginTest(str);                              \
                                               \
  MIN2MAX_16_BOOL_VECTOR_LOADED                \
                                               \
  vectorHalfBoolTest(funName, bvtrue);         \
  vectorHalfBoolTest(funName, bvfalse);        \
                                               \
  endTest();

/* Packet8f with one arg */
#define tests8FloatMin2MaxOneArg(str, funName)                                 \
  beginTest(str);                                                              \
                                                                               \
  MIN2MAX_8_FLOAT_VECTOR_LOADED                                                \
                                                                               \
  min2MaxTests(vectorFullFloatTest, funName, fvmax, fv36, fv0, fv_240, fvmin); \
                                                                               \
  endTest();

/* Packet4d with one arg */
#define tests4DoubleMin2MaxOneArg(str, funName)                                 \
  beginTest(str);                                                               \
                                                                                \
  MIN2MAX_4_DOUBLE_VECTOR_LOADED                                                \
                                                                                \
  min2MaxTests(vectorFullDoubleTest, funName, dvmax, dv36, dv0, dv_240, dvmin); \
                                                                                \
  endTest();

/* Packet8i with one arg */
#define tests8IntMin2MaxOneArg(str, funName)                                 \
  beginTest(str);                                                            \
                                                                             \
  MIN2MAX_8_INT_VECTOR_LOADED                                                \
                                                                             \
  min2MaxTests(vectorFullIntTest, funName, ivmax, iv36, iv0, iv_240, ivmin); \
                                                                             \
  endTest();

/* Packet8h with one arg */
#define tests8HalfMin2MaxOneArg(str, funName)                                      \
  beginTest(str);                                                                  \
                                                                                   \
  MIN2MAX_8_HALF_VECTOR_LOADED                                                     \
                                                                                   \
  min2MaxTests(vectorHalfEigenHalfTest, funName, hvmax, hv36, hv0, hv_240, hvmin); \
                                                                                   \
  endTest();

/* Packet8bf with one arg */
#define tests8Bfloat16Min2MaxOneArg(str, funName)                                      \
  beginTest(str);                                                                      \
                                                                                       \
  MIN2MAX_8_BFLOAT16_VECTOR_LOADED                                                     \
                                                                                       \
  min2MaxTests(vectorHalfBfloat16Test, funName, bfvmax, bfv36, bfv0, bfv_240, bfvmin); \
                                                                                       \
  endTest();

/* Packet4l with one arg */
#define tests4LongMin2MaxOneArg(str, funName)                                 \
  beginTest(str);                                                             \
                                                                              \
  MIN2MAX_4_LONG_VECTOR_LOADED                                                \
                                                                              \
  min2MaxTests(vectorFullLongTest, funName, lvmax, lv36, lv0, lv_240, lvmin); \
                                                                              \
  endTest();

/* Packet4f with two args and permutations with repetition */
#define tests4FloatMin2MaxTwoArgsPermRep(str, funName)                               \
  beginTest(str);                                                                    \
                                                                                     \
  MIN2MAX_4_FLOAT_VECTOR_LOADED                                                      \
                                                                                     \
  allTwoPermRep(vectorHalfFloatTest, funName, fhvmax, fhv36, fhv0, fhv_240, fhvmin); \
                                                                                     \
  endTest();

/* Packet2d with two args and permutations with repetition */
#define tests2DoubleMin2MaxTwoArgsPermRep(str, funName)                               \
  beginTest(str);                                                                     \
                                                                                      \
  MIN2MAX_2_DOUBLE_VECTOR_LOADED                                                      \
                                                                                      \
  allTwoPermRep(vectorHalfDoubleTest, funName, dhvmax, dhv36, dhv0, dhv_240, dhvmin); \
                                                                                      \
  endTest();

/* Packet4i with two args and permutations with repetition */
#define tests4IntMin2MaxTwoArgsPermRep(str, funName)                               \
  beginTest(str);                                                                  \
                                                                                   \
  MIN2MAX_4_INT_VECTOR_LOADED                                                      \
                                                                                   \
  allTwoPermRep(vectorHalfIntTest, funName, ihvmax, ihv36, ihv0, ihv_240, ihvmin); \
                                                                                   \
  endTest();

/* Packet16b with two args and permutations with repetition */
#define tests16BoolMin2MaxTwoArgsPermRep(str, funName)                                  \
  beginTest(str);                                                                       \
                                                                                        \
  MIN2MAX_8_BFLOAT16_VECTOR_LOADED                                                      \
                                                                                        \
  allTwoPermRep(vectorHalfBfloat16Test, funName, bfvmax, bfv36, bfv0, bfv_240, bfvmin); \
                                                                                        \
  endTest();

/* Packet8f with two args and permutations with repetition */
#define tests8FloatMin2MaxTwoArgsPermRep(str, funName)                          \
  beginTest(str);                                                               \
                                                                                \
  MIN2MAX_8_FLOAT_VECTOR_LOADED                                                 \
                                                                                \
  allTwoPermRep(vectorFullFloatTest, funName, fvmax, fv36, fv0, fv_240, fvmin); \
                                                                                \
  endTest();

/* Packet4d with two args and permutations with repetition */
#define tests4DoubleMin2MaxTwoArgsPermRep(str, funName)                          \
  beginTest(str);                                                                \
                                                                                 \
  MIN2MAX_4_DOUBLE_VECTOR_LOADED                                                 \
                                                                                 \
  allTwoPermRep(vectorFullDoubleTest, funName, dvmax, dv36, dv0, dv_240, dvmin); \
                                                                                 \
  endTest();

/* Packet8i with two args and permutations with repetition */
#define tests8IntMin2MaxTwoArgsPermRep(str, funName)                          \
  beginTest(str);                                                             \
                                                                              \
  MIN2MAX_8_INT_VECTOR_LOADED                                                 \
                                                                              \
  allTwoPermRep(vectorFullIntTest, funName, ivmax, iv36, iv0, iv_240, ivmin); \
                                                                              \
  endTest();

/* Packet8h with two args and permutations with repetition */
#define tests8HalfMin2MaxTwoArgsPermRep(str, funName)                               \
  beginTest(str);                                                                   \
                                                                                    \
  MIN2MAX_8_HALF_VECTOR_LOADED                                                      \
                                                                                    \
  allTwoPermRep(vectorHalfEigenHalfTest, funName, hvmax, hv36, hv0, hv_240, hvmin); \
                                                                                    \
  endTest();

/* Packet8bf with two args and permutations with repetition */
#define tests8Bfloat16Min2MaxTwoArgsPermRep(str, funName)                               \
  beginTest(str);                                                                       \
                                                                                        \
  MIN2MAX_8_BFLOAT16_VECTOR_LOADED                                                      \
                                                                                        \
  allTwoPermRep(vectorHalfBfloat16Test, funName, bfvmax, bfv36, bfv0, bfv_240, bfvmin); \
                                                                                        \
  endTest();

/* Packet4l with two args and permutations with repetition */
#define tests4LongMin2MaxTwoArgsPermRep(str, funName)                          \
  beginTest(str);                                                              \
                                                                               \
  MIN2MAX_4_LONG_VECTOR_LOADED                                                 \
                                                                               \
  allTwoPermRep(vectorFullLongTest, funName, lvmax, lv36, lv0, lv_240, lvmin); \
                                                                               \
  endTest();

/* Packet4f with two args and combinations with repetition */
#define tests4FloatMin2MaxTwoArgsCombRep(str, funName)                               \
  beginTest(str);                                                                    \
                                                                                     \
  MIN2MAX_4_FLOAT_VECTOR_LOADED                                                      \
                                                                                     \
  allTwoCombRep(vectorHalfFloatTest, funName, fhvmax, fhv36, fhv0, fhv_240, fhvmin); \
                                                                                     \
  endTest();

/* Packet2d with two args and combinations with repetition */
#define tests2DoubleMin2MaxTwoArgsCombRep(str, funName)                               \
  beginTest(str);                                                                     \
                                                                                      \
  MIN2MAX_2_DOUBLE_VECTOR_LOADED                                                      \
                                                                                      \
  allTwoCombRep(vectorHalfDoubleTest, funName, dhvmax, dhv36, dhv0, dhv_240, dhvmin); \
                                                                                      \
  endTest();

/* Packet4i with two args and combinations with repetition */
#define tests4IntMin2MaxTwoArgsCombRep(str, funName)                               \
  beginTest(str);                                                                  \
                                                                                   \
  MIN2MAX_4_INT_VECTOR_LOADED                                                      \
                                                                                   \
  allTwoCombRep(vectorHalfIntTest, funName, ihvmax, ihv36, ihv0, ihv_240, ihvmin); \
                                                                                   \
  endTest();

/* Packet16b with two args and combinations with repetition */
#define tests16BoolMin2MaxTwoArgsCombRep(str, funName) \
  beginTest(str);                                      \
                                                       \
  MIN2MAX_16_BOOL_VECTOR_LOADED                        \
                                                       \
  vectorHalfBoolTest(funName, bvtrue, bvtrue);         \
  vectorHalfBoolTest(funName, bvtrue, bvfalse);        \
  vectorHalfBoolTest(funName, bvfalse, bvtrue);        \
  vectorHalfBoolTest(funName, bvfalse, bvfalse);       \
                                                       \
  endTest();

/* Packet8f with two args and combinations with repetition */
#define tests8FloatMin2MaxTwoArgsCombRep(str, funName)                          \
  beginTest(str);                                                               \
                                                                                \
  MIN2MAX_8_FLOAT_VECTOR_LOADED                                                 \
                                                                                \
  allTwoCombRep(vectorFullFloatTest, funName, fvmax, fv36, fv0, fv_240, fvmin); \
                                                                                \
  endTest();

/* Packet4d with two args and combinations with repetition */
#define tests4DoubleMin2MaxTwoArgsCombRep(str, funName)                          \
  beginTest(str);                                                                \
                                                                                 \
  MIN2MAX_4_DOUBLE_VECTOR_LOADED                                                 \
                                                                                 \
  allTwoCombRep(vectorFullDoubleTest, funName, dvmax, dv36, dv0, dv_240, dvmin); \
                                                                                 \
  endTest();

/* Packet8i with two args and combinations with repetition */
#define tests8IntMin2MaxTwoArgsCombRep(str, funName)                          \
  beginTest(str);                                                             \
                                                                              \
  MIN2MAX_8_INT_VECTOR_LOADED                                                 \
                                                                              \
  allTwoCombRep(vectorFullIntTest, funName, ivmax, iv36, iv0, iv_240, ivmin); \
                                                                              \
  endTest();

/* Packet8h with two args and combinations with repetition */
#define tests8HalfMin2MaxTwoArgsCombRep(str, funName)                               \
  beginTest(str);                                                                   \
                                                                                    \
  MIN2MAX_8_HALF_VECTOR_LOADED                                                      \
                                                                                    \
  allTwoCombRep(vectorHalfEigenHalfTest, funName, hvmax, hv36, hv0, hv_240, hvmin); \
                                                                                    \
  endTest();

/* Packet8bf with two args and combinations with repetition */
#define tests8Bfloat16Min2MaxTwoArgsCombRep(str, funName)                               \
  beginTest(str);                                                                       \
                                                                                        \
  MIN2MAX_8_BFLOAT16_VECTOR_LOADED                                                      \
                                                                                        \
  allTwoCombRep(vectorHalfBfloat16Test, funName, bfvmax, bfv36, bfv0, bfv_240, bfvmin); \
                                                                                        \
  endTest();

/* Packet4l with two args and combinations with repetition */
#define tests4LongMin2MaxTwoArgsCombRep(str, funName)                          \
  beginTest(str);                                                              \
                                                                               \
  MIN2MAX_4_LONG_VECTOR_LOADED                                                 \
                                                                               \
  allTwoCombRep(vectorFullLongTest, funName, lvmax, lv36, lv0, lv_240, lvmin); \
                                                                               \
  endTest();

/* Packet4f with three args and permutations with repetition */
#define tests4FloatMin2MaxThreeArgsPermRep(str, funName)                               \
  beginTest(str);                                                                      \
                                                                                       \
  MIN2MAX_4_FLOAT_VECTOR_LOADED                                                        \
                                                                                       \
  allThreePermRep(vectorHalfFloatTest, funName, fhvmax, fhv36, fhv0, fhv_240, fhvmin); \
                                                                                       \
  endTest();

/* Packet2d with three args and permutations with repetition */
#define tests2DoubleMin2MaxThreeArgsPermRep(str, funName)                               \
  beginTest(str);                                                                       \
                                                                                        \
  MIN2MAX_2_DOUBLE_VECTOR_LOADED                                                        \
                                                                                        \
  allThreePermRep(vectorHalfDoubleTest, funName, dhvmax, dhv36, dhv0, dhv_240, dhvmin); \
                                                                                        \
  endTest();

/* Packet4i with three args and permutations with repetition */
#define tests4IntMin2MaxThreeArgsPermRep(str, funName)                               \
  beginTest(str);                                                                    \
                                                                                     \
  MIN2MAX_4_INT_VECTOR_LOADED                                                        \
                                                                                     \
  allThreePermRep(vectorHalfIntTest, funName, ihvmax, ihv36, ihv0, ihv_240, ihvmin); \
                                                                                     \
  endTest();

/* Packet16b with three args and permutations with repetition */
#define tests16BoolMin2MaxThreeArgsPermRep(str, funName)  \
  beginTest(str);                                         \
                                                          \
  MIN2MAX_16_BOOL_VECTOR_LOADED                           \
                                                          \
  vectorHalfBoolTest(funName, bvtrue, bvtrue, bvtrue);    \
  vectorHalfBoolTest(funName, bvtrue, bvtrue, bvfalse);   \
  vectorHalfBoolTest(funName, bvtrue, bvfalse, bvtrue);   \
  vectorHalfBoolTest(funName, bvtrue, bvfalse, bvfalse);  \
  vectorHalfBoolTest(funName, bvfalse, bvtrue, bvtrue);   \
  vectorHalfBoolTest(funName, bvfalse, bvtrue, bvfalse);  \
  vectorHalfBoolTest(funName, bvfalse, bvfalse, bvtrue);  \
  vectorHalfBoolTest(funName, bvfalse, bvfalse, bvfalse); \
                                                          \
  endTest();

/* Packet8f with three args and permutations with repetition */
#define tests8FloatMin2MaxThreeArgsPermRep(str, funName)                          \
  beginTest(str);                                                                 \
                                                                                  \
  MIN2MAX_8_FLOAT_VECTOR_LOADED                                                   \
                                                                                  \
  allThreePermRep(vectorFullFloatTest, funName, fvmax, fv36, fv0, fv_240, fvmin); \
                                                                                  \
  endTest();

/* Packet4d with three args and permutations with repetition */
#define tests4DoubleMin2MaxThreeArgsPermRep(str, funName)                          \
  beginTest(str);                                                                  \
                                                                                   \
  MIN2MAX_4_DOUBLE_VECTOR_LOADED                                                   \
                                                                                   \
  allThreePermRep(vectorFullDoubleTest, funName, dvmax, dv36, dv0, dv_240, dvmin); \
                                                                                   \
  endTest();

/* Packet8i with three args and permutations with repetition */
#define tests8IntMin2MaxThreeArgsPermRep(str, funName)                          \
  beginTest(str);                                                               \
                                                                                \
  MIN2MAX_8_INT_VECTOR_LOADED                                                   \
                                                                                \
  allThreePermRep(vectorFullIntTest, funName, ivmax, iv36, iv0, iv_240, ivmin); \
                                                                                \
  endTest();

/* Packet8h with three args and permutations with repetition */
#define tests8HalfMin2MaxThreeArgsPermRep(str, funName)                               \
  beginTest(str);                                                                     \
                                                                                      \
  MIN2MAX_8_HALF_VECTOR_LOADED                                                        \
                                                                                      \
  allThreePermRep(vectorHalfEigenHalfTest, funName, hvmax, hv36, hv0, hv_240, hvmin); \
                                                                                      \
  endTest();

/* Packet8bf with three args and permutations with repetition */
#define tests8Bfloat16Min2MaxThreeArgsPermRep(str, funName)                               \
  beginTest(str);                                                                         \
                                                                                          \
  MIN2MAX_8_BFLOAT16_VECTOR_LOADED                                                        \
                                                                                          \
  allThreePermRep(vectorHalfBfloat16Test, funName, bfvmax, bfv36, bfv0, bfv_240, bfvmin); \
                                                                                          \
  endTest();

/* Packet4l with three args and permutations with repetition */
#define tests4LongMin2MaxThreeArgsPermRep(str, funName)                          \
  beginTest(str);                                                                \
                                                                                 \
  MIN2MAX_4_LONG_VECTOR_LOADED                                                   \
                                                                                 \
  allThreePermRep(vectorFullLongTest, funName, lvmax, lv36, lv0, lv_240, lvmin); \
                                                                                 \
  endTest();

#endif  // EIGEN_MIPP_TEST_DEF_H