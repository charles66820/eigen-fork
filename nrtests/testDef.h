#ifndef EIGEN_MIPP_TEST_DEF_H
#define EIGEN_MIPP_TEST_DEF_H

// Tests macro definition
#define vectorFullLongTest(name, template, args...) \
  vectorSingleTypeTest(long, INT_CAST_TO_MIPP_FULL, name, template, args)

#define vectorHalfFloatTest(name, template, args...) \
  vectorSingleTypeTest(float, FLOAT_CAST_TO_MIPP_HALF, name, template, args)
#define vectorHalfDoubleTest(name, template, args...) \
  vectorSingleTypeTest(double, DOUBLE_CAST_TO_MIPP_HALF, name, template, args)
#define vectorHalfIntTest(name, template, args...) \
  vectorSingleTypeTest(int, INT_CAST_TO_MIPP_HALF, name, template, args)

#define vectorFullFloatTest(name, template, args...) \
  vectorSingleTypeTest(float, FLOAT_CAST_TO_MIPP_FULL, name, template, args)
#define vectorFullDoubleTest(name, template, args...) \
  vectorSingleTypeTest(double, DOUBLE_CAST_TO_MIPP_FULL, name, template, args)
#define vectorFullIntTest(name, template, args...) \
  vectorSingleTypeTest(int, INT_CAST_TO_MIPP_FULL, name, template, args)

#define vectorHalfBoolTest(name, template, args...) \
  vectorSingleTypeTest(int8_t, INT_CAST_TO_MIPP_HALF, name, template, args)
#define vectorHalfEigenHalfTest(name, template, args...) \
  vectorSingleTypeTest(short, INT_CAST_TO_MIPP_HALF, name, template, args)
#define vectorHalfBfloat16Test(name, template, args...) \
  vectorSingleTypeTest(short, INT_CAST_TO_MIPP_HALF, name, template, args)

/* Packet4f with one arg of loaded vector */
#define tests4FloatMin2MaxOneArgLoaded(str, funName)                                  \
  beginTest(str);                                                                     \
  {                                                                                   \
    MIN2MAX_FLOAT_VECTOR_LOADED(4);                                                   \
                                                                                      \
    min2MaxTests(vectorHalfFloatTest, funName, Packet4f, vmax, v36, v0, v_240, vmin); \
  }                                                                                   \
  endTest();

/* Packet2d with one arg of loaded vector */
#define tests2DoubleMin2MaxOneArgLoaded(str, funName)                                  \
  beginTest(str);                                                                      \
  {                                                                                    \
    MIN2MAX_DOUBLE_VECTOR_LOADED(2);                                                   \
                                                                                       \
    min2MaxTests(vectorHalfDoubleTest, funName, Packet2d, vmax, v36, v0, v_240, vmin); \
  }                                                                                    \
  endTest();

/* Packet4i with one arg of loaded vector */
#define tests4IntMin2MaxOneArgLoaded(str, funName)                                  \
  beginTest(str);                                                                   \
  {                                                                                 \
    MIN2MAX_INT_VECTOR_LOADED(4);                                                   \
                                                                                    \
    min2MaxTests(vectorHalfIntTest, funName, Packet4i, vmax, v36, v0, v_240, vmin); \
  }                                                                                 \
  endTest();

/* Packet16b with one arg of loaded vector */
#define tests16BoolMin2MaxOneArgLoaded(str, funName) \
  beginTest(str);                                    \
  {                                                  \
    MIN2MAX_BOOL_VECTOR_LOADED(16);                  \
                                                     \
    vectorHalfBoolTest(funName, Packet16b, bvtrue);  \
    vectorHalfBoolTest(funName, Packet16b, bvfalse); \
  }                                                  \
  endTest();

/* Packet8f with one arg of loaded vector */
#define tests8FloatMin2MaxOneArgLoaded(str, funName)                                  \
  beginTest(str);                                                                     \
  {                                                                                   \
    MIN2MAX_FLOAT_VECTOR_LOADED(8);                                                   \
                                                                                      \
    min2MaxTests(vectorFullFloatTest, funName, Packet8f, vmax, v36, v0, v_240, vmin); \
  }                                                                                   \
  endTest();

/* Packet4d with one arg of loaded vector */
#define tests4DoubleMin2MaxOneArgLoaded(str, funName)                                  \
  beginTest(str);                                                                      \
  {                                                                                    \
    MIN2MAX_DOUBLE_VECTOR_LOADED(4);                                                   \
                                                                                       \
    min2MaxTests(vectorFullDoubleTest, funName, Packet4d, vmax, v36, v0, v_240, vmin); \
  }                                                                                    \
  endTest();

/* Packet8i with one arg of loaded vector */
#define tests8IntMin2MaxOneArgLoaded(str, funName)                                  \
  beginTest(str);                                                                   \
  {                                                                                 \
    MIN2MAX_INT_VECTOR_LOADED(8);                                                   \
                                                                                    \
    min2MaxTests(vectorFullIntTest, funName, Packet8i, vmax, v36, v0, v_240, vmin); \
  }                                                                                 \
  endTest();

/* Packet8h with one arg of loaded vector */
#define tests8HalfMin2MaxOneArgLoaded(str, funName)                                       \
  beginTest(str);                                                                         \
  {                                                                                       \
    MIN2MAX_HALF_VECTOR_LOADED(8);                                                        \
                                                                                          \
    min2MaxTests(vectorHalfEigenHalfTest, funName, Packet8h, vmax, v36, v0, v_240, vmin); \
  }                                                                                       \
  endTest();

/* Packet8bf with one arg of loaded vector */
#define tests8Bfloat16Min2MaxOneArgLoaded(str, funName)                                   \
  beginTest(str);                                                                         \
  {                                                                                       \
    MIN2MAX_BFLOAT16_VECTOR_LOADED(8);                                                    \
                                                                                          \
    min2MaxTests(vectorHalfBfloat16Test, funName, Packet8bf, vmax, v36, v0, v_240, vmin); \
  }                                                                                       \
  endTest();

/* Packet4l with one arg of loaded vector */
#define tests4LongMin2MaxOneArgLoaded(str, funName)                                  \
  beginTest(str);                                                                    \
  {                                                                                  \
    MIN2MAX_LONG_VECTOR_LOADED(4);                                                   \
                                                                                     \
    min2MaxTests(vectorFullLongTest, funName, Packet4l, vmax, v36, v0, v_240, vmin); \
  }                                                                                  \
  endTest();

/* Packet4f with two args and permutations with repetition */
#define tests4FloatMin2MaxTwoArgsPermRep(str, funName)                                 \
  beginTest(str);                                                                      \
  {                                                                                    \
    MIN2MAX_FLOAT_VECTOR_LOADED(4);                                                    \
                                                                                       \
    allTwoPermRep(vectorHalfFloatTest, funName, Packet4f, vmax, v36, v0, v_240, vmin); \
  }                                                                                    \
  endTest();

/* Packet2d with two args and permutations with repetition */
#define tests2DoubleMin2MaxTwoArgsPermRep(str, funName)                                 \
  beginTest(str);                                                                       \
  {                                                                                     \
    MIN2MAX_DOUBLE_VECTOR_LOADED(2);                                                    \
                                                                                        \
    allTwoPermRep(vectorHalfDoubleTest, funName, Packet2d, vmax, v36, v0, v_240, vmin); \
  }                                                                                     \
  endTest();

/* Packet4i with two args and permutations with repetition */
#define tests4IntMin2MaxTwoArgsPermRep(str, funName)                                 \
  beginTest(str);                                                                    \
  {                                                                                  \
    MIN2MAX_INT_VECTOR_LOADED(4);                                                    \
                                                                                     \
    allTwoPermRep(vectorHalfIntTest, funName, Packet4i, vmax, v36, v0, v_240, vmin); \
  }                                                                                  \
  endTest();

/* Packet16b with two args and permutations with repetition */
#define tests16BoolMin2MaxTwoArgsPermRep(str, funName)         \
  beginTest(str);                                              \
  {                                                            \
    MIN2MAX_BOOL_VECTOR_LOADED(16);                            \
                                                               \
    vectorHalfBoolTest(FUN2TEST, Packet16b, bvtrue, bvtrue);   \
    vectorHalfBoolTest(FUN2TEST, Packet16b, bvtrue, bvfalse);  \
    vectorHalfBoolTest(FUN2TEST, Packet16b, bvfalse, bvtrue);  \
    vectorHalfBoolTest(FUN2TEST, Packet16b, bvfalse, bvfalse); \
  }                                                            \
  endTest();

/* Packet8f with two args and permutations with repetition */
#define tests8FloatMin2MaxTwoArgsPermRep(str, funName)                                 \
  beginTest(str);                                                                      \
  {                                                                                    \
    MIN2MAX_FLOAT_VECTOR_LOADED(8);                                                    \
                                                                                       \
    allTwoPermRep(vectorFullFloatTest, funName, Packet8f, vmax, v36, v0, v_240, vmin); \
  }                                                                                    \
  endTest();

/* Packet4d with two args and permutations with repetition */
#define tests4DoubleMin2MaxTwoArgsPermRep(str, funName)                                 \
  beginTest(str);                                                                       \
  {                                                                                     \
    MIN2MAX_DOUBLE_VECTOR_LOADED(4);                                                    \
                                                                                        \
    allTwoPermRep(vectorFullDoubleTest, funName, Packet4d, vmax, v36, v0, v_240, vmin); \
  }                                                                                     \
  endTest();

/* Packet8i with two args and permutations with repetition */
#define tests8IntMin2MaxTwoArgsPermRep(str, funName)                                 \
  beginTest(str);                                                                    \
  {                                                                                  \
    MIN2MAX_INT_VECTOR_LOADED(8);                                                    \
                                                                                     \
    allTwoPermRep(vectorFullIntTest, funName, Packet8i, vmax, v36, v0, v_240, vmin); \
  }                                                                                  \
  endTest();

/* Packet8h with two args and permutations with repetition */
#define tests8HalfMin2MaxTwoArgsPermRep(str, funName)                                      \
  beginTest(str);                                                                          \
  {                                                                                        \
    MIN2MAX_HALF_VECTOR_LOADED(8);                                                         \
                                                                                           \
    allTwoPermRep(vectorHalfEigenHalfTest, funName, Packet8h, vmax, v36, v0, v_240, vmin); \
  }                                                                                        \
  endTest();

/* Packet8bf with two args and permutations with repetition */
#define tests8Bfloat16Min2MaxTwoArgsPermRep(str, funName)                                  \
  beginTest(str);                                                                          \
  {                                                                                        \
    MIN2MAX_BFLOAT16_VECTOR_LOADED(8);                                                     \
                                                                                           \
    allTwoPermRep(vectorHalfBfloat16Test, funName, Packet8bf, vmax, v36, v0, v_240, vmin); \
  }                                                                                        \
  endTest();

/* Packet4l with two args and permutations with repetition */
#define tests4LongMin2MaxTwoArgsPermRep(str, funName)                                 \
  beginTest(str);                                                                     \
  {                                                                                   \
    MIN2MAX_LONG_VECTOR_LOADED(4);                                                    \
                                                                                      \
    allTwoPermRep(vectorFullLongTest, funName, Packet4l, vmax, v36, v0, v_240, vmin); \
  }                                                                                   \
  endTest();

/* Packet4f with two args and combinations with repetition */
#define tests4FloatMin2MaxTwoArgsCombRep(str, funName)                                 \
  beginTest(str);                                                                      \
  {                                                                                    \
    MIN2MAX_FLOAT_VECTOR_LOADED(4);                                                    \
                                                                                       \
    allTwoCombRep(vectorHalfFloatTest, funName, Packet4f, vmax, v36, v0, v_240, vmin); \
  }                                                                                    \
  endTest();

/* Packet2d with two args and combinations with repetition */
#define tests2DoubleMin2MaxTwoArgsCombRep(str, funName)                                 \
  beginTest(str);                                                                       \
  {                                                                                     \
    MIN2MAX_DOUBLE_VECTOR_LOADED(2);                                                    \
                                                                                        \
    allTwoCombRep(vectorHalfDoubleTest, funName, Packet2d, vmax, v36, v0, v_240, vmin); \
  }                                                                                     \
  endTest();

/* Packet4i with two args and combinations with repetition */
#define tests4IntMin2MaxTwoArgsCombRep(str, funName)                                 \
  beginTest(str);                                                                    \
  {                                                                                  \
    MIN2MAX_INT_VECTOR_LOADED(4);                                                    \
                                                                                     \
    allTwoCombRep(vectorHalfIntTest, funName, Packet4i, vmax, v36, v0, v_240, vmin); \
  }                                                                                  \
  endTest();

/* Packet16b with two args and combinations with repetition */
#define tests16BoolMin2MaxTwoArgsCombRep(str, funName)        \
  beginTest(str);                                             \
  {                                                           \
    MIN2MAX_BOOL_VECTOR_LOADED(16);                           \
                                                              \
    vectorHalfBoolTest(funName, Packet16b, bvtrue, bvtrue);   \
    vectorHalfBoolTest(funName, Packet16b, bvtrue, bvfalse);  \
    vectorHalfBoolTest(funName, Packet16b, bvfalse, bvtrue);  \
    vectorHalfBoolTest(funName, Packet16b, bvfalse, bvfalse); \
  }                                                           \
  endTest();

/* Packet8f with two args and combinations with repetition */
#define tests8FloatMin2MaxTwoArgsCombRep(str, funName)                                 \
  beginTest(str);                                                                      \
  {                                                                                    \
    MIN2MAX_FLOAT_VECTOR_LOADED(8);                                                    \
                                                                                       \
    allTwoCombRep(vectorFullFloatTest, funName, Packet8f, vmax, v36, v0, v_240, vmin); \
  }                                                                                    \
  endTest();

/* Packet4d with two args and combinations with repetition */
#define tests4DoubleMin2MaxTwoArgsCombRep(str, funName)                                 \
  beginTest(str);                                                                       \
  {                                                                                     \
    MIN2MAX_DOUBLE_VECTOR_LOADED(4);                                                    \
                                                                                        \
    allTwoCombRep(vectorFullDoubleTest, funName, Packet4d, vmax, v36, v0, v_240, vmin); \
  }                                                                                     \
  endTest();

/* Packet8i with two args and combinations with repetition */
#define tests8IntMin2MaxTwoArgsCombRep(str, funName)                                 \
  beginTest(str);                                                                    \
  {                                                                                  \
    MIN2MAX_INT_VECTOR_LOADED(8);                                                    \
                                                                                     \
    allTwoCombRep(vectorFullIntTest, funName, Packet8i, vmax, v36, v0, v_240, vmin); \
  }                                                                                  \
  endTest();

/* Packet8h with two args and combinations with repetition */
#define tests8HalfMin2MaxTwoArgsCombRep(str, funName)                                      \
  beginTest(str);                                                                          \
  {                                                                                        \
    MIN2MAX_HALF_VECTOR_LOADED(8);                                                         \
                                                                                           \
    allTwoCombRep(vectorHalfEigenHalfTest, funName, Packet8h, vmax, v36, v0, v_240, vmin); \
  }                                                                                        \
  endTest();

/* Packet8bf with two args and combinations with repetition */
#define tests8Bfloat16Min2MaxTwoArgsCombRep(str, funName)                                  \
  beginTest(str);                                                                          \
  {                                                                                        \
    MIN2MAX_BFLOAT16_VECTOR_LOADED(8);                                                     \
                                                                                           \
    allTwoCombRep(vectorHalfBfloat16Test, funName, Packet8bf, vmax, v36, v0, v_240, vmin); \
  }                                                                                        \
  endTest();

/* Packet4l with two args and combinations with repetition */
#define tests4LongMin2MaxTwoArgsCombRep(str, funName)                                 \
  beginTest(str);                                                                     \
  {                                                                                   \
    MIN2MAX_LONG_VECTOR_LOADED(4);                                                    \
                                                                                      \
    allTwoCombRep(vectorFullLongTest, funName, Packet4l, vmax, v36, v0, v_240, vmin); \
  }                                                                                   \
  endTest();

/* Packet4f with three args and permutations with repetition */
#define tests4FloatMin2MaxThreeArgsPermRep(str, funName)                                 \
  beginTest(str);                                                                        \
  {                                                                                      \
    MIN2MAX_FLOAT_VECTOR_LOADED(4);                                                      \
                                                                                         \
    allThreePermRep(vectorHalfFloatTest, funName, Packet4f, vmax, v36, v0, v_240, vmin); \
  }                                                                                      \
  endTest();

/* Packet2d with three args and permutations with repetition */
#define tests2DoubleMin2MaxThreeArgsPermRep(str, funName)                                 \
  beginTest(str);                                                                         \
  {                                                                                       \
    MIN2MAX_DOUBLE_VECTOR_LOADED(2);                                                      \
                                                                                          \
    allThreePermRep(vectorHalfDoubleTest, funName, Packet2d, vmax, v36, v0, v_240, vmin); \
  }                                                                                       \
  endTest();

/* Packet4i with three args and permutations with repetition */
#define tests4IntMin2MaxThreeArgsPermRep(str, funName)                                 \
  beginTest(str);                                                                      \
  {                                                                                    \
    MIN2MAX_INT_VECTOR_LOADED(4);                                                      \
                                                                                       \
    allThreePermRep(vectorHalfIntTest, funName, Packet4i, vmax, v36, v0, v_240, vmin); \
  }                                                                                    \
  endTest();

/* Packet16b with three args and permutations with repetition */
#define tests16BoolMin2MaxThreeArgsPermRep(str, funName)               \
  beginTest(str);                                                      \
  {                                                                    \
    MIN2MAX_BOOL_VECTOR_LOADED(16);                                    \
                                                                       \
    vectorHalfBoolTest(funName, Packet16b, bvtrue, bvtrue, bvtrue);    \
    vectorHalfBoolTest(funName, Packet16b, bvtrue, bvtrue, bvfalse);   \
    vectorHalfBoolTest(funName, Packet16b, bvtrue, bvfalse, bvtrue);   \
    vectorHalfBoolTest(funName, Packet16b, bvtrue, bvfalse, bvfalse);  \
    vectorHalfBoolTest(funName, Packet16b, bvfalse, bvtrue, bvtrue);   \
    vectorHalfBoolTest(funName, Packet16b, bvfalse, bvtrue, bvfalse);  \
    vectorHalfBoolTest(funName, Packet16b, bvfalse, bvfalse, bvtrue);  \
    vectorHalfBoolTest(funName, Packet16b, bvfalse, bvfalse, bvfalse); \
  }                                                                    \
  endTest();

/* Packet8f with three args and permutations with repetition */
#define tests8FloatMin2MaxThreeArgsPermRep(str, funName)                                 \
  beginTest(str);                                                                        \
  {                                                                                      \
    MIN2MAX_FLOAT_VECTOR_LOADED(8);                                                      \
                                                                                         \
    allThreePermRep(vectorFullFloatTest, funName, Packet8f, vmax, v36, v0, v_240, vmin); \
  }                                                                                      \
  endTest();

/* Packet4d with three args and permutations with repetition */
#define tests4DoubleMin2MaxThreeArgsPermRep(str, funName)                                 \
  beginTest(str);                                                                         \
  {                                                                                       \
    MIN2MAX_DOUBLE_VECTOR_LOADED(4);                                                      \
                                                                                          \
    allThreePermRep(vectorFullDoubleTest, funName, Packet4d, vmax, v36, v0, v_240, vmin); \
  }                                                                                       \
  endTest();

/* Packet8i with three args and permutations with repetition */
#define tests8IntMin2MaxThreeArgsPermRep(str, funName)                                 \
  beginTest(str);                                                                      \
  {                                                                                    \
    MIN2MAX_INT_VECTOR_LOADED(8);                                                      \
                                                                                       \
    allThreePermRep(vectorFullIntTest, funName, Packet8i, vmax, v36, v0, v_240, vmin); \
  }                                                                                    \
  endTest();

/* Packet8h with three args and permutations with repetition */
#define tests8HalfMin2MaxThreeArgsPermRep(str, funName)                                      \
  beginTest(str);                                                                            \
  {                                                                                          \
    MIN2MAX_HALF_VECTOR_LOADED(8);                                                           \
                                                                                             \
    allThreePermRep(vectorHalfEigenHalfTest, funName, Packet8h, vmax, v36, v0, v_240, vmin); \
  }                                                                                          \
  endTest();

/* Packet8bf with three args and permutations with repetition */
#define tests8Bfloat16Min2MaxThreeArgsPermRep(str, funName)                                  \
  beginTest(str);                                                                            \
  {                                                                                          \
    MIN2MAX_BFLOAT16_VECTOR_LOADED(8);                                                       \
                                                                                             \
    allThreePermRep(vectorHalfBfloat16Test, funName, Packet8bf, vmax, v36, v0, v_240, vmin); \
  }                                                                                          \
  endTest();

/* Packet4l with three args and permutations with repetition */
#define tests4LongMin2MaxThreeArgsPermRep(str, funName)                                 \
  beginTest(str);                                                                       \
  {                                                                                     \
    MIN2MAX_LONG_VECTOR_LOADED(4);                                                      \
                                                                                        \
    allThreePermRep(vectorFullLongTest, funName, Packet4l, vmax, v36, v0, v_240, vmin); \
  }                                                                                     \
  endTest();

/* Packet4f with one arg */
#define tests4FloatMin2MaxOneArg(str, funName)                                        \
  beginTest(str);                                                                     \
  {                                                                                   \
    MIN2MAX_FLOAT_VECTOR(vector4);                                                    \
                                                                                      \
    min2MaxTests(vectorHalfFloatTest, funName, Packet4f, vmax, v36, v0, v_240, vmin); \
  }                                                                                   \
  endTest();

/* Packet2d with one arg */
#define tests2DoubleMin2MaxOneArg(str, funName)                                        \
  beginTest(str);                                                                      \
  {                                                                                    \
    MIN2MAX_DOUBLE_VECTOR(vector2);                                                    \
                                                                                       \
    min2MaxTests(vectorHalfDoubleTest, funName, Packet2d, vmax, v36, v0, vmin, v_240); \
  }                                                                                    \
  endTest();

/* Packet4i with one arg */
#define tests4IntMin2MaxOneArg(str, funName)                                        \
  beginTest(str);                                                                   \
  {                                                                                 \
    MIN2MAX_INT_VECTOR(vector4);                                                    \
                                                                                    \
    min2MaxTests(vectorHalfIntTest, funName, Packet4i, vmax, v36, v0, v_240, vmin); \
  }                                                                                 \
  endTest();

/* Packet16b with one arg */
#define tests16BoolMin2MaxOneArg(str, funName)       \
  beginTest(str);                                    \
  {                                                  \
    MIN2MAX_BOOL_VECTOR(vector16);                   \
                                                     \
    vectorHalfBoolTest(funName, Packet16b, bvtrue);  \
    vectorHalfBoolTest(funName, Packet16b, bvfalse); \
  }                                                  \
  endTest();

/* Packet8f with one arg */
#define tests8FloatMin2MaxOneArg(str, funName)                                        \
  beginTest(str);                                                                     \
  {                                                                                   \
    MIN2MAX_FLOAT_VECTOR(vector8);                                                    \
                                                                                      \
    min2MaxTests(vectorFullFloatTest, funName, Packet8f, vmax, v36, v0, v_240, vmin); \
  }                                                                                   \
  endTest();

/* Packet4d with one arg */
#define tests4DoubleMin2MaxOneArg(str, funName)                                        \
  beginTest(str);                                                                      \
  {                                                                                    \
    MIN2MAX_DOUBLE_VECTOR(vector4);                                                    \
                                                                                       \
    min2MaxTests(vectorFullDoubleTest, funName, Packet4d, vmax, v36, v0, v_240, vmin); \
  }                                                                                    \
  endTest();

/* Packet8i with one arg */
#define tests8IntMin2MaxOneArg(str, funName)                                        \
  beginTest(str);                                                                   \
  {                                                                                 \
    MIN2MAX_INT_VECTOR(vector8);                                                    \
                                                                                    \
    min2MaxTests(vectorFullIntTest, funName, Packet8i, vmax, v36, v0, v_240, vmin); \
  }                                                                                 \
  endTest();

/* Packet8h with one arg */
#define tests8HalfMin2MaxOneArg(str, funName)                                             \
  beginTest(str);                                                                         \
  {                                                                                       \
    MIN2MAX_HALF_VECTOR(vector8);                                                         \
                                                                                          \
    min2MaxTests(vectorHalfEigenHalfTest, funName, Packet8h, vmax, v36, v0, v_240, vmin); \
  }                                                                                       \
  endTest();

/* Packet8bf with one arg */
#define tests8Bfloat16Min2MaxOneArg(str, funName)                                         \
  beginTest(str);                                                                         \
  {                                                                                       \
    MIN2MAX_BFLOAT16_VECTOR(vector8);                                                     \
                                                                                          \
    min2MaxTests(vectorHalfBfloat16Test, funName, Packet8bf, vmax, v36, v0, v_240, vmin); \
  }                                                                                       \
  endTest();

/* Packet4l with one arg */
#define tests4LongMin2MaxOneArg(str, funName)                                        \
  beginTest(str);                                                                    \
  {                                                                                  \
    MIN2MAX_LONG_VECTOR(vector4);                                                    \
                                                                                     \
    min2MaxTests(vectorFullLongTest, funName, Packet4l, vmax, v36, v0, v_240, vmin); \
  }                                                                                  \
  endTest();

/* Packet4f with one arg unaligned */
#define tests4FloatMin2MaxOneArgUnaligned(str, funName)                               \
  beginTest(str);                                                                     \
  {                                                                                   \
    MIN2MAX_FLOAT_VECTOR(vector4u);                                                   \
                                                                                      \
    min2MaxTests(vectorHalfFloatTest, funName, Packet4f, vmax, v36, v0, v_240, vmin); \
  }                                                                                   \
  endTest();

/* Packet2d with one arg unaligned */
#define tests2DoubleMin2MaxOneArgUnaligned(str, funName)                               \
  beginTest(str);                                                                      \
  {                                                                                    \
    MIN2MAX_DOUBLE_VECTOR(vector2u);                                                   \
                                                                                       \
    min2MaxTests(vectorHalfDoubleTest, funName, Packet2d, vmax, v36, v0, vmin, v_240); \
  }                                                                                    \
  endTest();

/* Packet4i with one arg unaligned */
#define tests4IntMin2MaxOneArgUnaligned(str, funName)                               \
  beginTest(str);                                                                   \
  {                                                                                 \
    MIN2MAX_INT_VECTOR(vector4u);                                                   \
                                                                                    \
    min2MaxTests(vectorHalfIntTest, funName, Packet4i, vmax, v36, v0, v_240, vmin); \
  }                                                                                 \
  endTest();

/* Packet16b with one arg unaligned */
#define tests16BoolMin2MaxOneArgUnaligned(str, funName) \
  beginTest(str);                                       \
  {                                                     \
    MIN2MAX_BOOL_VECTOR(vector16u);                     \
                                                        \
    vectorHalfBoolTest(funName, Packet16b, bvtrue);     \
    vectorHalfBoolTest(funName, Packet16b, bvfalse);    \
  }                                                     \
  endTest();

/* Packet8f with one arg unaligned */
#define tests8FloatMin2MaxOneArgUnaligned(str, funName)                               \
  beginTest(str);                                                                     \
  {                                                                                   \
    MIN2MAX_FLOAT_VECTOR(vector8u);                                                   \
                                                                                      \
    min2MaxTests(vectorFullFloatTest, funName, Packet8f, vmax, v36, v0, v_240, vmin); \
  }                                                                                   \
  endTest();

/* Packet4d with one arg unaligned */
#define tests4DoubleMin2MaxOneArgUnaligned(str, funName)                               \
  beginTest(str);                                                                      \
  {                                                                                    \
    MIN2MAX_DOUBLE_VECTOR(vector4u);                                                   \
                                                                                       \
    min2MaxTests(vectorFullDoubleTest, funName, Packet4d, vmax, v36, v0, v_240, vmin); \
  }                                                                                    \
  endTest();

/* Packet8i with one arg unaligned */
#define tests8IntMin2MaxOneArgUnaligned(str, funName)                               \
  beginTest(str);                                                                   \
  {                                                                                 \
    MIN2MAX_INT_VECTOR(vector8u);                                                   \
                                                                                    \
    min2MaxTests(vectorFullIntTest, funName, Packet8i, vmax, v36, v0, v_240, vmin); \
  }                                                                                 \
  endTest();

/* Packet8h with one arg unaligned */
#define tests8HalfMin2MaxOneArgUnaligned(str, funName)                                    \
  beginTest(str);                                                                         \
  {                                                                                       \
    MIN2MAX_HALF_VECTOR(vector8u);                                                        \
                                                                                          \
    min2MaxTests(vectorHalfEigenHalfTest, funName, Packet8h, vmax, v36, v0, v_240, vmin); \
  }                                                                                       \
  endTest();

/* Packet8bf with one arg unaligned */
#define tests8Bfloat16Min2MaxOneArgUnaligned(str, funName)                                \
  beginTest(str);                                                                         \
  {                                                                                       \
    MIN2MAX_BFLOAT16_VECTOR(vector8u);                                                    \
                                                                                          \
    min2MaxTests(vectorHalfBfloat16Test, funName, Packet8bf, vmax, v36, v0, v_240, vmin); \
  }                                                                                       \
  endTest();

/* Packet4l with one arg unaligned */
#define tests4LongMin2MaxOneArgUnaligned(str, funName)                               \
  beginTest(str);                                                                    \
  {                                                                                  \
    MIN2MAX_LONG_VECTOR(vector4u);                                                   \
                                                                                     \
    min2MaxTests(vectorFullLongTest, funName, Packet4l, vmax, v36, v0, v_240, vmin); \
  }                                                                                  \
  endTest();

#endif  // EIGEN_MIPP_TEST_DEF_H