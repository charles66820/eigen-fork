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
#define tests4FloatMin2MaxOneArgLoaded(str, funName)                                          \
  beginTest(str);                                                                             \
  {                                                                                           \
    MIN2MAX_FLOAT_VECTOR_LOADED(4);                                                           \
                                                                                              \
    min2MaxTests(vectorHalfFloatTemplateTest, funName, Packet4f, vmax, v36, v0, v_240, vmin); \
  }                                                                                           \
  endTest();

/* Packet2d with one arg of loaded vector */
#define tests2DoubleMin2MaxOneArgLoaded(str, funName)                                          \
  beginTest(str);                                                                              \
  {                                                                                            \
    MIN2MAX_DOUBLE_VECTOR_LOADED(2);                                                           \
                                                                                               \
    min2MaxTests(vectorHalfDoubleTemplateTest, funName, Packet2d, vmax, v36, v0, v_240, vmin); \
  }                                                                                            \
  endTest();

/* Packet4i with one arg of loaded vector */
#define tests4IntMin2MaxOneArgLoaded(str, funName)                                          \
  beginTest(str);                                                                           \
  {                                                                                         \
    MIN2MAX_INT_VECTOR_LOADED(4);                                                           \
                                                                                            \
    min2MaxTests(vectorHalfIntTemplateTest, funName, Packet4i, vmax, v36, v0, v_240, vmin); \
  }                                                                                         \
  endTest();

/* Packet16b with one arg of loaded vector */
#define tests16BoolMin2MaxOneArgLoaded(str, funName)         \
  beginTest(str);                                            \
  {                                                          \
    MIN2MAX_BOOL_VECTOR_LOADED(16);                          \
                                                             \
    vectorHalfBoolTemplateTest(funName, Packet16b, bvtrue);  \
    vectorHalfBoolTemplateTest(funName, Packet16b, bvfalse); \
  }                                                          \
  endTest();

/* Packet8f with one arg of loaded vector */
#define tests8FloatMin2MaxOneArgLoaded(str, funName)                                          \
  beginTest(str);                                                                             \
  {                                                                                           \
    MIN2MAX_FLOAT_VECTOR_LOADED(8);                                                           \
                                                                                              \
    min2MaxTests(vectorFullFloatTemplateTest, funName, Packet8f, vmax, v36, v0, v_240, vmin); \
  }                                                                                           \
  endTest();

/* Packet4d with one arg of loaded vector */
#define tests4DoubleMin2MaxOneArgLoaded(str, funName)                                          \
  beginTest(str);                                                                              \
  {                                                                                            \
    MIN2MAX_DOUBLE_VECTOR_LOADED(4);                                                           \
                                                                                               \
    min2MaxTests(vectorFullDoubleTemplateTest, funName, Packet4d, vmax, v36, v0, v_240, vmin); \
  }                                                                                            \
  endTest();

/* Packet8i with one arg of loaded vector */
#define tests8IntMin2MaxOneArgLoaded(str, funName)                                          \
  beginTest(str);                                                                           \
  {                                                                                         \
    MIN2MAX_INT_VECTOR_LOADED(8);                                                           \
                                                                                            \
    min2MaxTests(vectorFullIntTemplateTest, funName, Packet8i, vmax, v36, v0, v_240, vmin); \
  }                                                                                         \
  endTest();

/* Packet8h with one arg of loaded vector */
#define tests8HalfMin2MaxOneArgLoaded(str, funName)                                               \
  beginTest(str);                                                                                 \
  {                                                                                               \
    MIN2MAX_HALF_VECTOR_LOADED(8);                                                                \
                                                                                                  \
    min2MaxTests(vectorHalfEigenHalfTemplateTest, funName, Packet8h, vmax, v36, v0, v_240, vmin); \
  }                                                                                               \
  endTest();

/* Packet8bf with one arg of loaded vector */
#define tests8Bfloat16Min2MaxOneArgLoaded(str, funName)                                           \
  beginTest(str);                                                                                 \
  {                                                                                               \
    MIN2MAX_BFLOAT16_VECTOR_LOADED(8);                                                            \
                                                                                                  \
    min2MaxTests(vectorHalfBfloat16TemplateTest, funName, Packet8bf, vmax, v36, v0, v_240, vmin); \
  }                                                                                               \
  endTest();

/* Packet4l with one arg of loaded vector */
#define tests4LongMin2MaxOneArgLoaded(str, funName)                                          \
  beginTest(str);                                                                            \
  {                                                                                          \
    MIN2MAX_LONG_VECTOR_LOADED(4);                                                           \
                                                                                             \
    min2MaxTests(vectorFullLongTemplateTest, funName, Packet4l, vmax, v36, v0, v_240, vmin); \
  }                                                                                          \
  endTest();

/* Packet4f with two args and permutations with repetition */
#define tests4FloatMin2MaxTwoArgsPermRep(str, funName)                                         \
  beginTest(str);                                                                              \
  {                                                                                            \
    MIN2MAX_FLOAT_VECTOR_LOADED(4);                                                            \
                                                                                               \
    allTwoPermRep(vectorHalfFloatTemplateTest, funName, Packet4f, vmax, v36, v0, v_240, vmin); \
  }                                                                                            \
  endTest();

/* Packet2d with two args and permutations with repetition */
#define tests2DoubleMin2MaxTwoArgsPermRep(str, funName)                                         \
  beginTest(str);                                                                               \
  {                                                                                             \
    MIN2MAX_DOUBLE_VECTOR_LOADED(2);                                                            \
                                                                                                \
    allTwoPermRep(vectorHalfDoubleTemplateTest, funName, Packet2d, vmax, v36, v0, v_240, vmin); \
  }                                                                                             \
  endTest();

/* Packet4i with two args and permutations with repetition */
#define tests4IntMin2MaxTwoArgsPermRep(str, funName)                                         \
  beginTest(str);                                                                            \
  {                                                                                          \
    MIN2MAX_INT_VECTOR_LOADED(4);                                                            \
                                                                                             \
    allTwoPermRep(vectorHalfIntTemplateTest, funName, Packet4i, vmax, v36, v0, v_240, vmin); \
  }                                                                                          \
  endTest();

/* Packet16b with two args and permutations with repetition */
#define tests16BoolMin2MaxTwoArgsPermRep(str, funName)                 \
  beginTest(str);                                                      \
  {                                                                    \
    MIN2MAX_BOOL_VECTOR_LOADED(16);                                    \
                                                                       \
    vectorHalfBoolTemplateTest(FUN2TEST, Packet16b, bvtrue, bvtrue);   \
    vectorHalfBoolTemplateTest(FUN2TEST, Packet16b, bvtrue, bvfalse);  \
    vectorHalfBoolTemplateTest(FUN2TEST, Packet16b, bvfalse, bvtrue);  \
    vectorHalfBoolTemplateTest(FUN2TEST, Packet16b, bvfalse, bvfalse); \
  }                                                                    \
  endTest();

/* Packet8f with two args and permutations with repetition */
#define tests8FloatMin2MaxTwoArgsPermRep(str, funName)                                         \
  beginTest(str);                                                                              \
  {                                                                                            \
    MIN2MAX_FLOAT_VECTOR_LOADED(8);                                                            \
                                                                                               \
    allTwoPermRep(vectorFullFloatTemplateTest, funName, Packet8f, vmax, v36, v0, v_240, vmin); \
  }                                                                                            \
  endTest();

/* Packet4d with two args and permutations with repetition */
#define tests4DoubleMin2MaxTwoArgsPermRep(str, funName)                                         \
  beginTest(str);                                                                               \
  {                                                                                             \
    MIN2MAX_DOUBLE_VECTOR_LOADED(4);                                                            \
                                                                                                \
    allTwoPermRep(vectorFullDoubleTemplateTest, funName, Packet4d, vmax, v36, v0, v_240, vmin); \
  }                                                                                             \
  endTest();

/* Packet8i with two args and permutations with repetition */
#define tests8IntMin2MaxTwoArgsPermRep(str, funName)                                         \
  beginTest(str);                                                                            \
  {                                                                                          \
    MIN2MAX_INT_VECTOR_LOADED(8);                                                            \
                                                                                             \
    allTwoPermRep(vectorFullIntTemplateTest, funName, Packet8i, vmax, v36, v0, v_240, vmin); \
  }                                                                                          \
  endTest();

/* Packet8h with two args and permutations with repetition */
#define tests8HalfMin2MaxTwoArgsPermRep(str, funName)                                              \
  beginTest(str);                                                                                  \
  {                                                                                                \
    MIN2MAX_HALF_VECTOR_LOADED(8);                                                                 \
                                                                                                   \
    allTwoPermRep(vectorHalfEigenHalfTemplateTest, funName, Packet8h, vmax, v36, v0, v_240, vmin); \
  }                                                                                                \
  endTest();

/* Packet8bf with two args and permutations with repetition */
#define tests8Bfloat16Min2MaxTwoArgsPermRep(str, funName)                                          \
  beginTest(str);                                                                                  \
  {                                                                                                \
    MIN2MAX_BFLOAT16_VECTOR_LOADED(8);                                                             \
                                                                                                   \
    allTwoPermRep(vectorHalfBfloat16TemplateTest, funName, Packet8bf, vmax, v36, v0, v_240, vmin); \
  }                                                                                                \
  endTest();

/* Packet4l with two args and permutations with repetition */
#define tests4LongMin2MaxTwoArgsPermRep(str, funName)                                         \
  beginTest(str);                                                                             \
  {                                                                                           \
    MIN2MAX_LONG_VECTOR_LOADED(4);                                                            \
                                                                                              \
    allTwoPermRep(vectorFullLongTemplateTest, funName, Packet4l, vmax, v36, v0, v_240, vmin); \
  }                                                                                           \
  endTest();

/* Packet4f with two args and combinations with repetition */
#define tests4FloatMin2MaxTwoArgsCombRep(str, funName)                                         \
  beginTest(str);                                                                              \
  {                                                                                            \
    MIN2MAX_FLOAT_VECTOR_LOADED(4);                                                            \
                                                                                               \
    allTwoCombRep(vectorHalfFloatTemplateTest, funName, Packet4f, vmax, v36, v0, v_240, vmin); \
  }                                                                                            \
  endTest();

/* Packet2d with two args and combinations with repetition */
#define tests2DoubleMin2MaxTwoArgsCombRep(str, funName)                                         \
  beginTest(str);                                                                               \
  {                                                                                             \
    MIN2MAX_DOUBLE_VECTOR_LOADED(2);                                                            \
                                                                                                \
    allTwoCombRep(vectorHalfDoubleTemplateTest, funName, Packet2d, vmax, v36, v0, v_240, vmin); \
  }                                                                                             \
  endTest();

/* Packet4i with two args and combinations with repetition */
#define tests4IntMin2MaxTwoArgsCombRep(str, funName)                                         \
  beginTest(str);                                                                            \
  {                                                                                          \
    MIN2MAX_INT_VECTOR_LOADED(4);                                                            \
                                                                                             \
    allTwoCombRep(vectorHalfIntTemplateTest, funName, Packet4i, vmax, v36, v0, v_240, vmin); \
  }                                                                                          \
  endTest();

/* Packet16b with two args and combinations with repetition */
#define tests16BoolMin2MaxTwoArgsCombRep(str, funName)                \
  beginTest(str);                                                     \
  {                                                                   \
    MIN2MAX_BOOL_VECTOR_LOADED(16);                                   \
                                                                      \
    vectorHalfBoolTemplateTest(funName, Packet16b, bvtrue, bvtrue);   \
    vectorHalfBoolTemplateTest(funName, Packet16b, bvtrue, bvfalse);  \
    vectorHalfBoolTemplateTest(funName, Packet16b, bvfalse, bvtrue);  \
    vectorHalfBoolTemplateTest(funName, Packet16b, bvfalse, bvfalse); \
  }                                                                   \
  endTest();

/* Packet8f with two args and combinations with repetition */
#define tests8FloatMin2MaxTwoArgsCombRep(str, funName)                                         \
  beginTest(str);                                                                              \
  {                                                                                            \
    MIN2MAX_FLOAT_VECTOR_LOADED(8);                                                            \
                                                                                               \
    allTwoCombRep(vectorFullFloatTemplateTest, funName, Packet8f, vmax, v36, v0, v_240, vmin); \
  }                                                                                            \
  endTest();

/* Packet4d with two args and combinations with repetition */
#define tests4DoubleMin2MaxTwoArgsCombRep(str, funName)                                         \
  beginTest(str);                                                                               \
  {                                                                                             \
    MIN2MAX_DOUBLE_VECTOR_LOADED(4);                                                            \
                                                                                                \
    allTwoCombRep(vectorFullDoubleTemplateTest, funName, Packet4d, vmax, v36, v0, v_240, vmin); \
  }                                                                                             \
  endTest();

/* Packet8i with two args and combinations with repetition */
#define tests8IntMin2MaxTwoArgsCombRep(str, funName)                                         \
  beginTest(str);                                                                            \
  {                                                                                          \
    MIN2MAX_INT_VECTOR_LOADED(8);                                                            \
                                                                                             \
    allTwoCombRep(vectorFullIntTemplateTest, funName, Packet8i, vmax, v36, v0, v_240, vmin); \
  }                                                                                          \
  endTest();

/* Packet8h with two args and combinations with repetition */
#define tests8HalfMin2MaxTwoArgsCombRep(str, funName)                                              \
  beginTest(str);                                                                                  \
  {                                                                                                \
    MIN2MAX_HALF_VECTOR_LOADED(8);                                                                 \
                                                                                                   \
    allTwoCombRep(vectorHalfEigenHalfTemplateTest, funName, Packet8h, vmax, v36, v0, v_240, vmin); \
  }                                                                                                \
  endTest();

/* Packet8bf with two args and combinations with repetition */
#define tests8Bfloat16Min2MaxTwoArgsCombRep(str, funName)                                          \
  beginTest(str);                                                                                  \
  {                                                                                                \
    MIN2MAX_BFLOAT16_VECTOR_LOADED(8);                                                             \
                                                                                                   \
    allTwoCombRep(vectorHalfBfloat16TemplateTest, funName, Packet8bf, vmax, v36, v0, v_240, vmin); \
  }                                                                                                \
  endTest();

/* Packet4l with two args and combinations with repetition */
#define tests4LongMin2MaxTwoArgsCombRep(str, funName)                                         \
  beginTest(str);                                                                             \
  {                                                                                           \
    MIN2MAX_LONG_VECTOR_LOADED(4);                                                            \
                                                                                              \
    allTwoCombRep(vectorFullLongTemplateTest, funName, Packet4l, vmax, v36, v0, v_240, vmin); \
  }                                                                                           \
  endTest();

/* Packet4f with three args and permutations with repetition */
#define tests4FloatMin2MaxThreeArgsPermRep(str, funName)                                         \
  beginTest(str);                                                                                \
  {                                                                                              \
    MIN2MAX_FLOAT_VECTOR_LOADED(4);                                                              \
                                                                                                 \
    allThreePermRep(vectorHalfFloatTemplateTest, funName, Packet4f, vmax, v36, v0, v_240, vmin); \
  }                                                                                              \
  endTest();

/* Packet2d with three args and permutations with repetition */
#define tests2DoubleMin2MaxThreeArgsPermRep(str, funName)                                         \
  beginTest(str);                                                                                 \
  {                                                                                               \
    MIN2MAX_DOUBLE_VECTOR_LOADED(2);                                                              \
                                                                                                  \
    allThreePermRep(vectorHalfDoubleTemplateTest, funName, Packet2d, vmax, v36, v0, v_240, vmin); \
  }                                                                                               \
  endTest();

/* Packet4i with three args and permutations with repetition */
#define tests4IntMin2MaxThreeArgsPermRep(str, funName)                                         \
  beginTest(str);                                                                              \
  {                                                                                            \
    MIN2MAX_INT_VECTOR_LOADED(4);                                                              \
                                                                                               \
    allThreePermRep(vectorHalfIntTemplateTest, funName, Packet4i, vmax, v36, v0, v_240, vmin); \
  }                                                                                            \
  endTest();

/* Packet16b with three args and permutations with repetition */
#define tests16BoolMin2MaxThreeArgsPermRep(str, funName)                       \
  beginTest(str);                                                              \
  {                                                                            \
    MIN2MAX_BOOL_VECTOR_LOADED(16);                                            \
                                                                               \
    vectorHalfBoolTemplateTest(funName, Packet16b, bvtrue, bvtrue, bvtrue);    \
    vectorHalfBoolTemplateTest(funName, Packet16b, bvtrue, bvtrue, bvfalse);   \
    vectorHalfBoolTemplateTest(funName, Packet16b, bvtrue, bvfalse, bvtrue);   \
    vectorHalfBoolTemplateTest(funName, Packet16b, bvtrue, bvfalse, bvfalse);  \
    vectorHalfBoolTemplateTest(funName, Packet16b, bvfalse, bvtrue, bvtrue);   \
    vectorHalfBoolTemplateTest(funName, Packet16b, bvfalse, bvtrue, bvfalse);  \
    vectorHalfBoolTemplateTest(funName, Packet16b, bvfalse, bvfalse, bvtrue);  \
    vectorHalfBoolTemplateTest(funName, Packet16b, bvfalse, bvfalse, bvfalse); \
  }                                                                            \
  endTest();

/* Packet8f with three args and permutations with repetition */
#define tests8FloatMin2MaxThreeArgsPermRep(str, funName)                                         \
  beginTest(str);                                                                                \
  {                                                                                              \
    MIN2MAX_FLOAT_VECTOR_LOADED(8);                                                              \
                                                                                                 \
    allThreePermRep(vectorFullFloatTemplateTest, funName, Packet8f, vmax, v36, v0, v_240, vmin); \
  }                                                                                              \
  endTest();

/* Packet4d with three args and permutations with repetition */
#define tests4DoubleMin2MaxThreeArgsPermRep(str, funName)                                         \
  beginTest(str);                                                                                 \
  {                                                                                               \
    MIN2MAX_DOUBLE_VECTOR_LOADED(4);                                                              \
                                                                                                  \
    allThreePermRep(vectorFullDoubleTemplateTest, funName, Packet4d, vmax, v36, v0, v_240, vmin); \
  }                                                                                               \
  endTest();

/* Packet8i with three args and permutations with repetition */
#define tests8IntMin2MaxThreeArgsPermRep(str, funName)                                         \
  beginTest(str);                                                                              \
  {                                                                                            \
    MIN2MAX_INT_VECTOR_LOADED(8);                                                              \
                                                                                               \
    allThreePermRep(vectorFullIntTemplateTest, funName, Packet8i, vmax, v36, v0, v_240, vmin); \
  }                                                                                            \
  endTest();

/* Packet8h with three args and permutations with repetition */
#define tests8HalfMin2MaxThreeArgsPermRep(str, funName)                                              \
  beginTest(str);                                                                                    \
  {                                                                                                  \
    MIN2MAX_HALF_VECTOR_LOADED(8);                                                                   \
                                                                                                     \
    allThreePermRep(vectorHalfEigenHalfTemplateTest, funName, Packet8h, vmax, v36, v0, v_240, vmin); \
  }                                                                                                  \
  endTest();

/* Packet8bf with three args and permutations with repetition */
#define tests8Bfloat16Min2MaxThreeArgsPermRep(str, funName)                                          \
  beginTest(str);                                                                                    \
  {                                                                                                  \
    MIN2MAX_BFLOAT16_VECTOR_LOADED(8);                                                               \
                                                                                                     \
    allThreePermRep(vectorHalfBfloat16TemplateTest, funName, Packet8bf, vmax, v36, v0, v_240, vmin); \
  }                                                                                                  \
  endTest();

/* Packet4l with three args and permutations with repetition */
#define tests4LongMin2MaxThreeArgsPermRep(str, funName)                                         \
  beginTest(str);                                                                               \
  {                                                                                             \
    MIN2MAX_LONG_VECTOR_LOADED(4);                                                              \
                                                                                                \
    allThreePermRep(vectorFullLongTemplateTest, funName, Packet4l, vmax, v36, v0, v_240, vmin); \
  }                                                                                             \
  endTest();

/* Packet4f with one arg */
#define tests4FloatMin2MaxOneArg(str, funName)                                                \
  beginTest(str);                                                                             \
  {                                                                                           \
    MIN2MAX_FLOAT_VECTOR(vector4);                                                            \
                                                                                              \
    min2MaxTests(vectorHalfFloatTemplateTest, funName, Packet4f, vmax, v36, v0, v_240, vmin); \
  }                                                                                           \
  endTest();

/* Packet2d with one arg */
#define tests2DoubleMin2MaxOneArg(str, funName)                                                \
  beginTest(str);                                                                              \
  {                                                                                            \
    MIN2MAX_DOUBLE_VECTOR(vector2);                                                            \
                                                                                               \
    min2MaxTests(vectorHalfDoubleTemplateTest, funName, Packet2d, vmax, v36, v0, vmin, v_240); \
  }                                                                                            \
  endTest();

/* Packet4i with one arg */
#define tests4IntMin2MaxOneArg(str, funName)                                                \
  beginTest(str);                                                                           \
  {                                                                                         \
    MIN2MAX_INT_VECTOR(vector4);                                                            \
                                                                                            \
    min2MaxTests(vectorHalfIntTemplateTest, funName, Packet4i, vmax, v36, v0, v_240, vmin); \
  }                                                                                         \
  endTest();

/* Packet16b with one arg */
#define tests16BoolMin2MaxOneArg(str, funName)               \
  beginTest(str);                                            \
  {                                                          \
    MIN2MAX_BOOL_VECTOR(vector16);                           \
                                                             \
    vectorHalfBoolTemplateTest(funName, Packet16b, bvtrue);  \
    vectorHalfBoolTemplateTest(funName, Packet16b, bvfalse); \
  }                                                          \
  endTest();

/* Packet8f with one arg */
#define tests8FloatMin2MaxOneArg(str, funName)                                                \
  beginTest(str);                                                                             \
  {                                                                                           \
    MIN2MAX_FLOAT_VECTOR(vector8);                                                            \
                                                                                              \
    min2MaxTests(vectorFullFloatTemplateTest, funName, Packet8f, vmax, v36, v0, v_240, vmin); \
  }                                                                                           \
  endTest();

/* Packet4d with one arg */
#define tests4DoubleMin2MaxOneArg(str, funName)                                                \
  beginTest(str);                                                                              \
  {                                                                                            \
    MIN2MAX_DOUBLE_VECTOR(vector4);                                                            \
                                                                                               \
    min2MaxTests(vectorFullDoubleTemplateTest, funName, Packet4d, vmax, v36, v0, v_240, vmin); \
  }                                                                                            \
  endTest();

/* Packet8i with one arg */
#define tests8IntMin2MaxOneArg(str, funName)                                                \
  beginTest(str);                                                                           \
  {                                                                                         \
    MIN2MAX_INT_VECTOR(vector8);                                                            \
                                                                                            \
    min2MaxTests(vectorFullIntTemplateTest, funName, Packet8i, vmax, v36, v0, v_240, vmin); \
  }                                                                                         \
  endTest();

/* Packet8h with one arg */
#define tests8HalfMin2MaxOneArg(str, funName)                                                     \
  beginTest(str);                                                                                 \
  {                                                                                               \
    MIN2MAX_HALF_VECTOR(vector8);                                                                 \
                                                                                                  \
    min2MaxTests(vectorHalfEigenHalfTemplateTest, funName, Packet8h, vmax, v36, v0, v_240, vmin); \
  }                                                                                               \
  endTest();

/* Packet8bf with one arg */
#define tests8Bfloat16Min2MaxOneArg(str, funName)                                                 \
  beginTest(str);                                                                                 \
  {                                                                                               \
    MIN2MAX_BFLOAT16_VECTOR(vector8);                                                             \
                                                                                                  \
    min2MaxTests(vectorHalfBfloat16TemplateTest, funName, Packet8bf, vmax, v36, v0, v_240, vmin); \
  }                                                                                               \
  endTest();

/* Packet4l with one arg */
#define tests4LongMin2MaxOneArg(str, funName)                                                \
  beginTest(str);                                                                            \
  {                                                                                          \
    MIN2MAX_LONG_VECTOR(vector4);                                                            \
                                                                                             \
    min2MaxTests(vectorFullLongTemplateTest, funName, Packet4l, vmax, v36, v0, v_240, vmin); \
  }                                                                                          \
  endTest();

/* Packet4f with one arg unaligned */
#define tests4FloatMin2MaxOneArgUnaligned(str, funName)                                       \
  beginTest(str);                                                                             \
  {                                                                                           \
    MIN2MAX_FLOAT_VECTOR(vector4u);                                                           \
                                                                                              \
    min2MaxTests(vectorHalfFloatTemplateTest, funName, Packet4f, vmax, v36, v0, v_240, vmin); \
  }                                                                                           \
  endTest();

/* Packet2d with one arg unaligned */
#define tests2DoubleMin2MaxOneArgUnaligned(str, funName)                                       \
  beginTest(str);                                                                              \
  {                                                                                            \
    MIN2MAX_DOUBLE_VECTOR(vector2u);                                                           \
                                                                                               \
    min2MaxTests(vectorHalfDoubleTemplateTest, funName, Packet2d, vmax, v36, v0, vmin, v_240); \
  }                                                                                            \
  endTest();

/* Packet4i with one arg unaligned */
#define tests4IntMin2MaxOneArgUnaligned(str, funName)                                       \
  beginTest(str);                                                                           \
  {                                                                                         \
    MIN2MAX_INT_VECTOR(vector4u);                                                           \
                                                                                            \
    min2MaxTests(vectorHalfIntTemplateTest, funName, Packet4i, vmax, v36, v0, v_240, vmin); \
  }                                                                                         \
  endTest();

/* Packet16b with one arg unaligned */
#define tests16BoolMin2MaxOneArgUnaligned(str, funName)      \
  beginTest(str);                                            \
  {                                                          \
    MIN2MAX_BOOL_VECTOR(vector16u);                          \
                                                             \
    vectorHalfBoolTemplateTest(funName, Packet16b, bvtrue);  \
    vectorHalfBoolTemplateTest(funName, Packet16b, bvfalse); \
  }                                                          \
  endTest();

/* Packet8f with one arg unaligned */
#define tests8FloatMin2MaxOneArgUnaligned(str, funName)                                       \
  beginTest(str);                                                                             \
  {                                                                                           \
    MIN2MAX_FLOAT_VECTOR(vector8u);                                                           \
                                                                                              \
    min2MaxTests(vectorFullFloatTemplateTest, funName, Packet8f, vmax, v36, v0, v_240, vmin); \
  }                                                                                           \
  endTest();

/* Packet4d with one arg unaligned */
#define tests4DoubleMin2MaxOneArgUnaligned(str, funName)                                       \
  beginTest(str);                                                                              \
  {                                                                                            \
    MIN2MAX_DOUBLE_VECTOR(vector4u);                                                           \
                                                                                               \
    min2MaxTests(vectorFullDoubleTemplateTest, funName, Packet4d, vmax, v36, v0, v_240, vmin); \
  }                                                                                            \
  endTest();

/* Packet8i with one arg unaligned */
#define tests8IntMin2MaxOneArgUnaligned(str, funName)                                       \
  beginTest(str);                                                                           \
  {                                                                                         \
    MIN2MAX_INT_VECTOR(vector8u);                                                           \
                                                                                            \
    min2MaxTests(vectorFullIntTemplateTest, funName, Packet8i, vmax, v36, v0, v_240, vmin); \
  }                                                                                         \
  endTest();

/* Packet8h with one arg unaligned */
#define tests8HalfMin2MaxOneArgUnaligned(str, funName)                                            \
  beginTest(str);                                                                                 \
  {                                                                                               \
    MIN2MAX_HALF_VECTOR(vector8u);                                                                \
                                                                                                  \
    min2MaxTests(vectorHalfEigenHalfTemplateTest, funName, Packet8h, vmax, v36, v0, v_240, vmin); \
  }                                                                                               \
  endTest();

/* Packet8bf with one arg unaligned */
#define tests8Bfloat16Min2MaxOneArgUnaligned(str, funName)                                        \
  beginTest(str);                                                                                 \
  {                                                                                               \
    MIN2MAX_BFLOAT16_VECTOR(vector8u);                                                            \
                                                                                                  \
    min2MaxTests(vectorHalfBfloat16TemplateTest, funName, Packet8bf, vmax, v36, v0, v_240, vmin); \
  }                                                                                               \
  endTest();

/* Packet4l with one arg unaligned */
#define tests4LongMin2MaxOneArgUnaligned(str, funName)                                       \
  beginTest(str);                                                                            \
  {                                                                                          \
    MIN2MAX_LONG_VECTOR(vector4u);                                                           \
                                                                                             \
    min2MaxTests(vectorFullLongTemplateTest, funName, Packet4l, vmax, v36, v0, v_240, vmin); \
  }                                                                                          \
  endTest();

#endif  // EIGEN_MIPP_TEST_DEF_H