#ifndef EIGEN_MIPP_TEST_DEF_H
#define EIGEN_MIPP_TEST_DEF_H

// Tests macro definition
#define vector256LongTest(name, template, args...) \
  vectorSingleTypeTest(long, INT_CAST_256_TO_MIPP_REG_T, name, template, args)

#define vector128FloatTest(name, template, args...) \
  vectorSingleTypeTest(float, FLOAT_CAST_128_TO_MIPP_REG_T, name, template, args)
#define vector128DoubleTest(name, template, args...) \
  vectorSingleTypeTest(double, DOUBLE_CAST_128_TO_MIPP_REG_T, name, template, args)
#define vector128IntTest(name, template, args...) \
  vectorSingleTypeTest(int, INT_CAST_128_TO_MIPP_REG_T, name, template, args)

#define vector256FloatTest(name, template, args...) \
  vectorSingleTypeTest(float, FLOAT_CAST_256_TO_MIPP_REG_T, name, template, args)
#define vector256DoubleTest(name, template, args...) \
  vectorSingleTypeTest(double, DOUBLE_CAST_256_TO_MIPP_REG_T, name, template, args)
#define vector256IntTest(name, template, args...) \
  vectorSingleTypeTest(int, INT_CAST_256_TO_MIPP_REG_T, name, template, args)

#define vector128BoolTest(name, template, args...) \
  vectorSingleTypeTest(int8_t, INT_CAST_128_TO_MIPP_REG_T, name, template, args)
#define vector128EigenHalfTest(name, template, args...) \
  vectorSingleTypeTest(short, INT_CAST_128_TO_MIPP_REG_T, name, template, args)
#define vector128Bfloat16Test(name, template, args...) \
  vectorSingleTypeTest(short, INT_CAST_128_TO_MIPP_REG_T, name, template, args)

#define genericTest(str, funName, testFun, packet, exec, vec, vecArg, args...) \
  beginTest(str);                                                              \
  {                                                                            \
    vec(vecArg);                                                               \
                                                                               \
    exec(testFun, funName, packet, args);                                      \
  }                                                                            \
  endTest();

#define min2maxGenericTest(str, funName, testFun, packet, exec, vec, vecArg) \
  genericTest(str, funName, testFun, packet, exec, vec, vecArg, vmax, v36, v0, v_240, vmin)

#define boolGenericTest(str, funName, testFun, packet, exec, vec, vecArg) \
  genericTest(str, funName, testFun, packet, exec, vec, vecArg, vtrue, vfalse)

/* Packet4f with one arg of loaded vector */
#define tests4FloatMin2MaxOneArgLoaded(str, funName) \
  min2maxGenericTest(str, funName, vector128FloatTest, Packet4f, min2MaxTests, MIN2MAX_FLOAT_VECTOR_LOADED, 4)

/* Packet2d with one arg of loaded vector */
#define tests2DoubleMin2MaxOneArgLoaded(str, funName) \
  min2maxGenericTest(str, funName, vector128DoubleTest, Packet2d, min2MaxTests, MIN2MAX_DOUBLE_VECTOR_LOADED, 2)

/* Packet4i with one arg of loaded vector */
#define tests4IntMin2MaxOneArgLoaded(str, funName) \
  min2maxGenericTest(str, funName, vector128IntTest, Packet4i, min2MaxTests, MIN2MAX_INT_VECTOR_LOADED, 4)

/* Packet16b with one arg of loaded vector */
#define tests16BoolMin2MaxOneArgLoaded(str, funName) \
  boolGenericTest(str, funName, vector128BoolTest, Packet16b, boolTests, BOOL_VECTOR_LOADED, 16)

/* Packet8f with one arg of loaded vector */
#define tests8FloatMin2MaxOneArgLoaded(str, funName) \
  min2maxGenericTest(str, funName, vector256FloatTest, Packet8f, min2MaxTests, MIN2MAX_FLOAT_VECTOR_LOADED, 8)

/* Packet4d with one arg of loaded vector */
#define tests4DoubleMin2MaxOneArgLoaded(str, funName) \
  min2maxGenericTest(str, funName, vector256DoubleTest, Packet4d, min2MaxTests, MIN2MAX_DOUBLE_VECTOR_LOADED, 4)

/* Packet8i with one arg of loaded vector */
#define tests8IntMin2MaxOneArgLoaded(str, funName) \
  min2maxGenericTest(str, funName, vector256IntTest, Packet8i, min2MaxTests, MIN2MAX_INT_VECTOR_LOADED, 8)

/* Packet8h with one arg of loaded vector */
#define tests8HalfMin2MaxOneArgLoaded(str, funName) \
  min2maxGenericTest(str, funName, vector128EigenHalfTest, Packet8h, min2MaxTests, MIN2MAX_HALF_VECTOR_LOADED, 8)

/* Packet8bf with one arg of loaded vector */
#define tests8Bfloat16Min2MaxOneArgLoaded(str, funName) \
  min2maxGenericTest(str, funName, vector128Bfloat16Test, Packet8bf, min2MaxTests, MIN2MAX_BFLOAT16_VECTOR_LOADED, 8)

/* Packet4l with one arg of loaded vector */
#define tests4LongMin2MaxOneArgLoaded(str, funName) \
  min2maxGenericTest(str, funName, vector256LongTest, Packet4l, min2MaxTests, MIN2MAX_LONG_VECTOR_LOADED, 4)

/* Packet4f with two args and permutations with repetition */
#define tests4FloatMin2MaxTwoArgsPermRep(str, funName) \
  min2maxGenericTest(str, funName, vector128FloatTest, Packet4f, allTwoPermRep, MIN2MAX_FLOAT_VECTOR_LOADED, 4)

/* Packet2d with two args and permutations with repetition */
#define tests2DoubleMin2MaxTwoArgsPermRep(str, funName) \
  min2maxGenericTest(str, funName, vector128DoubleTest, Packet2d, allTwoPermRep, MIN2MAX_DOUBLE_VECTOR_LOADED, 2)

/* Packet4i with two args and permutations with repetition */
#define tests4IntMin2MaxTwoArgsPermRep(str, funName) \
  min2maxGenericTest(str, funName, vector128IntTest, Packet4i, allTwoPermRep, MIN2MAX_INT_VECTOR_LOADED, 4)

/* Packet8f with two args and permutations with repetition */
#define tests8FloatMin2MaxTwoArgsPermRep(str, funName) \
  min2maxGenericTest(str, funName, vector256FloatTest, Packet8f, allTwoPermRep, MIN2MAX_FLOAT_VECTOR_LOADED, 8)

/* Packet4d with two args and permutations with repetition */
#define tests4DoubleMin2MaxTwoArgsPermRep(str, funName) \
  min2maxGenericTest(str, funName, vector256DoubleTest, Packet4d, allTwoPermRep, MIN2MAX_DOUBLE_VECTOR_LOADED, 4)

/* Packet8i with two args and permutations with repetition */
#define tests8IntMin2MaxTwoArgsPermRep(str, funName) \
  min2maxGenericTest(str, funName, vector256IntTest, Packet8i, allTwoPermRep, MIN2MAX_INT_VECTOR_LOADED, 8)

/* Packet8h with two args and permutations with repetition */
#define tests8HalfMin2MaxTwoArgsPermRep(str, funName) \
  min2maxGenericTest(str, funName, vector128EigenHalfTest, Packet8h, allTwoPermRep, MIN2MAX_HALF_VECTOR_LOADED, 8)

/* Packet8bf with two args and permutations with repetition */
#define tests8Bfloat16Min2MaxTwoArgsPermRep(str, funName) \
  min2maxGenericTest(str, funName, vector128Bfloat16Test, Packet8bf, allTwoPermRep, MIN2MAX_BFLOAT16_VECTOR_LOADED, 8)

/* Packet4l with two args and permutations with repetition */
#define tests4LongMin2MaxTwoArgsPermRep(str, funName) \
  min2maxGenericTest(str, funName, vector256LongTest, Packet4l, allTwoPermRep, MIN2MAX_LONG_VECTOR_LOADED, 4)

/* Packet4f with two args and combinations with repetition */
#define tests4FloatMin2MaxTwoArgsCombRep(str, funName) \
  min2maxGenericTest(str, funName, vector128FloatTest, Packet4f, allTwoCombRep, MIN2MAX_FLOAT_VECTOR_LOADED, 4)

/* Packet2d with two args and combinations with repetition */
#define tests2DoubleMin2MaxTwoArgsCombRep(str, funName) \
  min2maxGenericTest(str, funName, vector128DoubleTest, Packet2d, allTwoCombRep, MIN2MAX_DOUBLE_VECTOR_LOADED, 2)

/* Packet4i with two args and combinations with repetition */
#define tests4IntMin2MaxTwoArgsCombRep(str, funName) \
  min2maxGenericTest(str, funName, vector128IntTest, Packet4i, allTwoCombRep, MIN2MAX_INT_VECTOR_LOADED, 4)

/* Packet16b with two args and combinations with repetition */
#define tests16BoolMin2MaxTwoArgsCombRep(str, funName) \
  boolGenericTest(str, funName, vector128BoolTest, Packet16b, allTwoBoolTests, BOOL_VECTOR_LOADED, 16)

/* Packet8f with two args and combinations with repetition */
#define tests8FloatMin2MaxTwoArgsCombRep(str, funName) \
  min2maxGenericTest(str, funName, vector256FloatTest, Packet8f, allTwoCombRep, MIN2MAX_FLOAT_VECTOR_LOADED, 8)

/* Packet4d with two args and combinations with repetition */
#define tests4DoubleMin2MaxTwoArgsCombRep(str, funName) \
  min2maxGenericTest(str, funName, vector256DoubleTest, Packet4d, allTwoCombRep, MIN2MAX_DOUBLE_VECTOR_LOADED, 4)

/* Packet8i with two args and combinations with repetition */
#define tests8IntMin2MaxTwoArgsCombRep(str, funName) \
  min2maxGenericTest(str, funName, vector256IntTest, Packet8i, allTwoCombRep, MIN2MAX_INT_VECTOR_LOADED, 8)

/* Packet8h with two args and combinations with repetition */
#define tests8HalfMin2MaxTwoArgsCombRep(str, funName) \
  min2maxGenericTest(str, funName, vector128EigenHalfTest, Packet8h, allTwoCombRep, MIN2MAX_HALF_VECTOR_LOADED, 8)

/* Packet8bf with two args and combinations with repetition */
#define tests8Bfloat16Min2MaxTwoArgsCombRep(str, funName) \
  min2maxGenericTest(str, funName, vector128Bfloat16Test, Packet8bf, allTwoCombRep, MIN2MAX_BFLOAT16_VECTOR_LOADED, 8)

/* Packet4l with two args and combinations with repetition */
#define tests4LongMin2MaxTwoArgsCombRep(str, funName) \
  min2maxGenericTest(str, funName, vector256LongTest, Packet4l, allTwoCombRep, MIN2MAX_LONG_VECTOR_LOADED, 4)

/* Packet4f with three args and permutations with repetition */
#define tests4FloatMin2MaxThreeArgsPermRep(str, funName) \
  min2maxGenericTest(str, funName, vector128FloatTest, Packet4f, allThreePermRep, MIN2MAX_FLOAT_VECTOR_LOADED, 4)

/* Packet2d with three args and permutations with repetition */
#define tests2DoubleMin2MaxThreeArgsPermRep(str, funName) \
  min2maxGenericTest(str, funName, vector128DoubleTest, Packet2d, allThreePermRep, MIN2MAX_DOUBLE_VECTOR_LOADED, 2)

/* Packet4i with three args and permutations with repetition */
#define tests4IntMin2MaxThreeArgsPermRep(str, funName) \
  min2maxGenericTest(str, funName, vector128IntTest, Packet4i, allThreePermRep, MIN2MAX_INT_VECTOR_LOADED, 4)

/* Packet16b with three args and permutations with repetition */
#define tests16BoolMin2MaxThreeArgsPermRep(str, funName) \
  boolGenericTest(str, funName, vector128BoolTest, Packet16b, allThreeBoolTests, BOOL_VECTOR_LOADED, 16)

/* Packet8f with three args and permutations with repetition */
#define tests8FloatMin2MaxThreeArgsPermRep(str, funName) \
  min2maxGenericTest(str, funName, vector256FloatTest, Packet8f, allThreePermRep, MIN2MAX_FLOAT_VECTOR_LOADED, 8)

/* Packet4d with three args and permutations with repetition */
#define tests4DoubleMin2MaxThreeArgsPermRep(str, funName) \
  min2maxGenericTest(str, funName, vector256DoubleTest, Packet4d, allThreePermRep, MIN2MAX_DOUBLE_VECTOR_LOADED, 4)

/* Packet8i with three args and permutations with repetition */
#define tests8IntMin2MaxThreeArgsPermRep(str, funName) \
  min2maxGenericTest(str, funName, vector256IntTest, Packet8i, allThreePermRep, MIN2MAX_INT_VECTOR_LOADED, 8)

/* Packet8h with three args and permutations with repetition */
#define tests8HalfMin2MaxThreeArgsPermRep(str, funName) \
  min2maxGenericTest(str, funName, vector128EigenHalfTest, Packet8h, allThreePermRep, MIN2MAX_HALF_VECTOR_LOADED, 8)

/* Packet8bf with three args and permutations with repetition */
#define tests8Bfloat16Min2MaxThreeArgsPermRep(str, funName) \
  min2maxGenericTest(str, funName, vector128Bfloat16Test, Packet8bf, allThreePermRep, MIN2MAX_BFLOAT16_VECTOR_LOADED, 8)

/* Packet4l with three args and permutations with repetition */
#define tests4LongMin2MaxThreeArgsPermRep(str, funName) \
  min2maxGenericTest(str, funName, vector256LongTest, Packet4l, allThreePermRep, MIN2MAX_LONG_VECTOR_LOADED, 4)

/* Packet4f with one arg */
#define tests4FloatMin2MaxOneArg(str, funName) \
  min2maxGenericTest(str, funName, vector128FloatTest, Packet4f, min2MaxTests, MIN2MAX_FLOAT_VECTOR, vector4)

/* Packet2d with one arg */
#define tests2DoubleMin2MaxOneArg(str, funName) \
  min2maxGenericTest(str, funName, vector128DoubleTest, Packet2d, min2MaxTests, MIN2MAX_DOUBLE_VECTOR, vector2)

/* Packet4i with one arg */
#define tests4IntMin2MaxOneArg(str, funName) \
  min2maxGenericTest(str, funName, vector128IntTest, Packet4i, min2MaxTests, MIN2MAX_INT_VECTOR, vector4)

/* Packet16b with one arg */
#define tests16BoolMin2MaxOneArg(str, funName) \
  boolGenericTest(str, funName, vector128BoolTest, Packet16b, boolTests, BOOL_VECTOR, vector16)

/* Packet8f with one arg */
#define tests8FloatMin2MaxOneArg(str, funName) \
  min2maxGenericTest(str, funName, vector256FloatTest, Packet8f, min2MaxTests, MIN2MAX_FLOAT_VECTOR, vector8)

/* Packet4d with one arg */
#define tests4DoubleMin2MaxOneArg(str, funName) \
  min2maxGenericTest(str, funName, vector256DoubleTest, Packet4d, min2MaxTests, MIN2MAX_DOUBLE_VECTOR, vector4)

/* Packet8i with one arg */
#define tests8IntMin2MaxOneArg(str, funName) \
  min2maxGenericTest(str, funName, vector256IntTest, Packet8i, min2MaxTests, MIN2MAX_INT_VECTOR, vector8)

/* Packet8h with one arg */
#define tests8HalfMin2MaxOneArg(str, funName) \
  min2maxGenericTest(str, funName, vector128EigenHalfTest, Packet8h, min2MaxTests, MIN2MAX_HALF_VECTOR, vector8)

/* Packet8bf with one arg */
#define tests8Bfloat16Min2MaxOneArg(str, funName) \
  min2maxGenericTest(str, funName, vector128Bfloat16Test, Packet8bf, min2MaxTests, MIN2MAX_BFLOAT16_VECTOR, vector8)

/* Packet4l with one arg */
#define tests4LongMin2MaxOneArg(str, funName) \
  min2maxGenericTest(str, funName, vector256LongTest, Packet4l, min2MaxTests, MIN2MAX_LONG_VECTOR, vector4)

/* Packet4f with one arg unaligned */
#define tests4FloatMin2MaxOneArgUnaligned(str, funName) \
  min2maxGenericTest(str, funName, vector128FloatTest, Packet4f, min2MaxTests, MIN2MAX_FLOAT_VECTOR, vector4u)

/* Packet2d with one arg unaligned */
#define tests2DoubleMin2MaxOneArgUnaligned(str, funName) \
  min2maxGenericTest(str, funName, vector128DoubleTest, Packet2d, min2MaxTests, MIN2MAX_DOUBLE_VECTOR, vector2u)

/* Packet4i with one arg unaligned */
#define tests4IntMin2MaxOneArgUnaligned(str, funName) \
  min2maxGenericTest(str, funName, vector128IntTest, Packet4i, min2MaxTests, MIN2MAX_INT_VECTOR, vector4u)

/* Packet16b with one arg unaligned */
#define tests16BoolMin2MaxOneArgUnaligned(str, funName) \
  boolGenericTest(str, funName, vector128BoolTest, Packet16b, boolTests, BOOL_VECTOR, vector16u)

/* Packet8f with one arg unaligned */
#define tests8FloatMin2MaxOneArgUnaligned(str, funName) \
  min2maxGenericTest(str, funName, vector256FloatTest, Packet8f, min2MaxTests, MIN2MAX_FLOAT_VECTOR, vector8u)

/* Packet4d with one arg unaligned */
#define tests4DoubleMin2MaxOneArgUnaligned(str, funName) \
  min2maxGenericTest(str, funName, vector256DoubleTest, Packet4d, min2MaxTests, MIN2MAX_DOUBLE_VECTOR, vector4u)

/* Packet8i with one arg unaligned */
#define tests8IntMin2MaxOneArgUnaligned(str, funName) \
  min2maxGenericTest(str, funName, vector256IntTest, Packet8i, min2MaxTests, MIN2MAX_INT_VECTOR, vector8u)

/* Packet8h with one arg unaligned */
#define tests8HalfMin2MaxOneArgUnaligned(str, funName) \
  min2maxGenericTest(str, funName, vector128EigenHalfTest, Packet8h, min2MaxTests, MIN2MAX_HALF_VECTOR, vector8u)

/* Packet8bf with one arg unaligned */
#define tests8Bfloat16Min2MaxOneArgUnaligned(str, funName) \
  min2maxGenericTest(str, funName, vector128Bfloat16Test, Packet8bf, min2MaxTests, MIN2MAX_BFLOAT16_VECTOR, vector8u)

/* Packet4l with one arg unaligned */
#define tests4LongMin2MaxOneArgUnaligned(str, funName) \
  min2maxGenericTest(str, funName, vector256LongTest, Packet4l, min2MaxTests, MIN2MAX_LONG_VECTOR, vector4u)

#endif  // EIGEN_MIPP_TEST_DEF_H