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
#define tests4FloatMin2MaxOneArg(str, funName) \
  beginTest(str);                              \
                                               \
  MIN2MAX_HALF_FLOAT_VECTOR                    \
                                               \
  vectorHalfFloatTest(funName, fhvmax.r);      \
  vectorHalfFloatTest(funName, fhv36.r);       \
  vectorHalfFloatTest(funName, fhv0.r);        \
  vectorHalfFloatTest(funName, fhv_240.r);     \
  vectorHalfFloatTest(funName, fhvmin.r);      \
                                               \
  endTest();

/* Packet2d with one arg */
#define tests2DoubleMin2MaxOneArg(str, funName)       \
  beginTest(str);                                     \
                                                      \
  MIN2MAX_HALF_DOUBLE_VECTOR                          \
                                                      \
  vectorHalfDoubleTest(funName, (Packet2d)dhvmax.r);  \
  vectorHalfDoubleTest(funName, (Packet2d)dhv36.r);   \
  vectorHalfDoubleTest(funName, (Packet2d)dhv0.r);    \
  vectorHalfDoubleTest(funName, (Packet2d)dhv_240.r); \
  vectorHalfDoubleTest(funName, (Packet2d)dhvmin.r);  \
                                                      \
  endTest();

/* Packet4i with one arg */
#define tests4IntMin2MaxOneArg(str, funName)      \
  beginTest(str);                                 \
                                                  \
  MIN2MAX_HALF_INT_VECTOR                         \
                                                  \
  vectorHalfIntTest(funName, (__m128i)ihvmax.r);  \
  vectorHalfIntTest(funName, (__m128i)ihv36.r);   \
  vectorHalfIntTest(funName, (__m128i)ihv0.r);    \
  vectorHalfIntTest(funName, (__m128i)ihv_240.r); \
  vectorHalfIntTest(funName, (__m128i)ihvmin.r);  \
                                                  \
  endTest();

/* Packet16b with one arg */
#define tests16BoolMin2MaxOneArg(str, funName)     \
  beginTest(str);                                  \
                                                   \
  MIN2MAX_HALF_BOOL_VECTOR                         \
                                                   \
  vectorHalfBoolTest(funName, (__m128i)bvtrue.r);  \
  vectorHalfBoolTest(funName, (__m128i)bvfalse.r); \
                                                   \
  endTest();

/* Packet8f with one arg */
#define tests8FloatMin2MaxOneArg(str, funName) \
  beginTest(str);                              \
                                               \
  MIN2MAX_FULL_FLOAT_VECTOR                    \
                                               \
  vectorFullFloatTest(funName, fvmax.r);       \
  vectorFullFloatTest(funName, fv36.r);        \
  vectorFullFloatTest(funName, fv0.r);         \
  vectorFullFloatTest(funName, fv_240.r);      \
  vectorFullFloatTest(funName, fvmin.r);       \
                                               \
  endTest();

/* Packet4d with one arg */
#define tests4DoubleMin2MaxOneArg(str, funName)      \
  beginTest(str);                                    \
                                                     \
  MIN2MAX_FULL_DOUBLE_VECTOR                         \
                                                     \
  vectorFullDoubleTest(funName, (Packet4d)dvmax.r);  \
  vectorFullDoubleTest(funName, (Packet4d)dv36.r);   \
  vectorFullDoubleTest(funName, (Packet4d)dv0.r);    \
  vectorFullDoubleTest(funName, (Packet4d)dv_240.r); \
  vectorFullDoubleTest(funName, (Packet4d)dvmin.r);  \
                                                     \
  endTest();

/* Packet8i with one arg */
#define tests8IntMin2MaxOneArg(str, funName)     \
  beginTest(str);                                \
                                                 \
  MIN2MAX_FULL_INT_VECTOR                        \
                                                 \
  vectorFullIntTest(funName, (__m256i)ivmax.r);  \
  vectorFullIntTest(funName, (__m256i)iv36.r);   \
  vectorFullIntTest(funName, (__m256i)iv0.r);    \
  vectorFullIntTest(funName, (__m256i)iv_240.r); \
  vectorFullIntTest(funName, (__m256i)ivmin.r);  \
                                                 \
  endTest();

/* Packet8h with one arg */
#define tests8HalfMin2MaxOneArg(str, funName)         \
  beginTest(str);                                     \
                                                      \
  MIN2MAX_HALF_HALF_VECTOR                            \
                                                      \
  vectorHalfEigenHalfTest(funName, (__m128i)hvmax.r); \
  vectorHalfEigenHalfTest(funName, (__m128i)hv36.r);  \
  vectorHalfEigenHalfTest(funName, (__m128i)hv0.r);   \
  vectorHalfEigenHalfTest(funName, (__m128i)hvmin.r); \
                                                      \
  endTest();

/* Packet8bf with one arg */
#define tests8Bfloat16Min2MaxOneArg(str, funName)      \
  beginTest(str);                                      \
                                                       \
  MIN2MAX_HALF_BFLOAT16_VECTOR                         \
                                                       \
  vectorHalfBfloat16Test(funName, (__m128i)bfvmax.r);  \
  vectorHalfBfloat16Test(funName, (__m128i)bfv36.r);   \
  vectorHalfBfloat16Test(funName, (__m128i)bfv0.r);    \
  vectorHalfBfloat16Test(funName, (__m128i)bfv_240.r); \
  vectorHalfBfloat16Test(funName, (__m128i)bfvmin.r);  \
                                                       \
  endTest();

/* Packet4l with one arg */
#define tests4LongMin2MaxOneArg(str, funName)     \
  beginTest(str);                                 \
                                                  \
  MIN2MAX_FULL_LONG_VECTOR                        \
                                                  \
  vectorFullLongTest(funName, (__m256i)lvmax.r);  \
  vectorFullLongTest(funName, (__m256i)lv36.r);   \
  vectorFullLongTest(funName, (__m256i)lv0.r);    \
  vectorFullLongTest(funName, (__m256i)lv_240.r); \
  vectorFullLongTest(funName, (__m256i)lvmin.r);  \
                                                  \
  endTest();

/* Packet4f with two args and permutations with repetition */
#define tests4FloatMin2MaxTwoArgsPermRep(str, funName)                                         \
  beginTest(str);                                                                              \
                                                                                               \
  MIN2MAX_HALF_FLOAT_VECTOR                                                                    \
                                                                                               \
  allTwoPermRep(vectorHalfFloatTest, funName, fhvmax.r, fhv36.r, fhv0.r, fhv_240.r, fhvmin.r); \
                                                                                               \
  endTest();

/* Packet2d with two args and permutations with repetition */
#define tests2DoubleMin2MaxTwoArgsPermRep(str, funName)                                                 \
  beginTest(str);                                                                                       \
                                                                                                        \
  MIN2MAX_HALF_DOUBLE_VECTOR                                                                            \
                                                                                                        \
  allTwoPermRep(vectorHalfDoubleTest, funName, (Packet2d)dhvmax.r, (Packet2d)dhv36.r, (Packet2d)dhv0.r, \
                (Packet2d)dhv_240.r, (Packet2d)dhvmin.r);                                               \
                                                                                                        \
  endTest();

/* Packet4i with two args and permutations with repetition */
#define tests4IntMin2MaxTwoArgsPermRep(str, funName)                                                                  \
  beginTest(str);                                                                                                     \
                                                                                                                      \
  MIN2MAX_HALF_INT_VECTOR                                                                                             \
                                                                                                                      \
  allTwoPermRep(vectorHalfIntTest, funName, (__m128i)ihvmax.r, (__m128i)ihv36.r, (__m128i)ihv0.r, (__m128i)ihv_240.r, \
                (__m128i)ihvmin.r);                                                                                   \
                                                                                                                      \
  endTest();

/* Packet16b with two args and permutations with repetition */
#define tests16BoolMin2MaxTwoArgsPermRep(str, funName)                                                 \
  beginTest(str);                                                                                      \
                                                                                                       \
  MIN2MAX_HALF_BFLOAT16_VECTOR                                                                         \
                                                                                                       \
  allTwoPermRep(vectorHalfBfloat16Test, funName, (__m128i)bfvmax.r, (__m128i)bfv36.r, (__m128i)bfv0.r, \
                (__m128i)bfv_240.r, (__m128i)bfvmin.r);                                                \
                                                                                                       \
  endTest();

/* Packet8f with two args and permutations with repetition */
#define tests8FloatMin2MaxTwoArgsPermRep(str, funName)                                    \
  beginTest(str);                                                                         \
                                                                                          \
  MIN2MAX_FULL_FLOAT_VECTOR                                                               \
                                                                                          \
  allTwoPermRep(vectorFullFloatTest, funName, fvmax.r, fv36.r, fv0.r, fv_240.r, fvmin.r); \
                                                                                          \
  endTest();

/* Packet4d with two args and permutations with repetition */
#define tests4DoubleMin2MaxTwoArgsPermRep(str, funName)                                              \
  beginTest(str);                                                                                    \
                                                                                                     \
  MIN2MAX_FULL_DOUBLE_VECTOR                                                                         \
                                                                                                     \
  allTwoPermRep(vectorFullDoubleTest, funName, (Packet4d)dvmax.r, (Packet4d)dv36.r, (Packet4d)dv0.r, \
                (Packet4d)dv_240.r, (Packet4d)dvmin.r);                                              \
                                                                                                     \
  endTest();

/* Packet8i with two args and permutations with repetition */
#define tests8IntMin2MaxTwoArgsPermRep(str, funName)                                                              \
  beginTest(str);                                                                                                 \
                                                                                                                  \
  MIN2MAX_FULL_INT_VECTOR                                                                                         \
                                                                                                                  \
  allTwoPermRep(vectorFullIntTest, funName, (__m256i)ivmax.r, (__m256i)iv36.r, (__m256i)iv0.r, (__m256i)iv_240.r, \
                (__m256i)ivmin.r);                                                                                \
                                                                                                                  \
  endTest();

/* Packet8h with two args and permutations with repetition */
#define tests8HalfMin2MaxTwoArgsPermRep(str, funName)                                                \
  beginTest(str);                                                                                    \
                                                                                                     \
  MIN2MAX_HALF_HALF_VECTOR                                                                           \
                                                                                                     \
  allTwoPermRep(vectorHalfEigenHalfTest, funName, (__m128i)hvmax.r, (__m128i)hv36.r, (__m128i)hv0.r, \
                (__m128i)hv_240.r, (__m128i)hvmin.r);                                                \
                                                                                                     \
  endTest();

/* Packet8bf with two args and permutations with repetition */
#define tests8Bfloat16Min2MaxTwoArgsPermRep(str, funName)                                              \
  beginTest(str);                                                                                      \
                                                                                                       \
  MIN2MAX_HALF_BFLOAT16_VECTOR                                                                         \
                                                                                                       \
  allTwoPermRep(vectorHalfBfloat16Test, funName, (__m128i)bfvmax.r, (__m128i)bfv36.r, (__m128i)bfv0.r, \
                (__m128i)bfv_240.r, (__m128i)bfvmin.r);                                                \
                                                                                                       \
  endTest();

/* Packet4l with two args and permutations with repetition */
#define tests4LongMin2MaxTwoArgsPermRep(str, funName)                                                              \
  beginTest(str);                                                                                                  \
                                                                                                                   \
  MIN2MAX_FULL_LONG_VECTOR                                                                                         \
                                                                                                                   \
  allTwoPermRep(vectorFullLongTest, funName, (__m256i)lvmax.r, (__m256i)lv36.r, (__m256i)lv0.r, (__m256i)lv_240.r, \
                (__m256i)lvmin.r);                                                                                 \
                                                                                                                   \
  endTest();

/* Packet4f with two args and combinations with repetition */
#define tests4FloatMin2MaxTwoArgsCombRep(str, funName)                                         \
  beginTest(str);                                                                              \
                                                                                               \
  MIN2MAX_HALF_FLOAT_VECTOR                                                                    \
                                                                                               \
  allTwoCombRep(vectorHalfFloatTest, funName, fhvmax.r, fhv36.r, fhv0.r, fhv_240.r, fhvmin.r); \
                                                                                               \
  endTest();

/* Packet2d with two args and combinations with repetition */
#define tests2DoubleMin2MaxTwoArgsCombRep(str, funName)                                                 \
  beginTest(str);                                                                                       \
                                                                                                        \
  MIN2MAX_HALF_DOUBLE_VECTOR                                                                            \
                                                                                                        \
  allTwoCombRep(vectorHalfDoubleTest, funName, (Packet2d)dhvmax.r, (Packet2d)dhv36.r, (Packet2d)dhv0.r, \
                (Packet2d)dhv_240.r, (Packet2d)dhvmin.r);                                               \
                                                                                                        \
  endTest();

/* Packet4i with two args and combinations with repetition */
#define tests4IntMin2MaxTwoArgsCombRep(str, funName)                                                                  \
  beginTest(str);                                                                                                     \
                                                                                                                      \
  MIN2MAX_HALF_INT_VECTOR                                                                                             \
                                                                                                                      \
  allTwoCombRep(vectorHalfIntTest, funName, (__m128i)ihvmax.r, (__m128i)ihv36.r, (__m128i)ihv0.r, (__m128i)ihv_240.r, \
                (__m128i)ihvmin.r);                                                                                   \
                                                                                                                      \
  endTest();

/* Packet16b with two args and combinations with repetition */
#define tests16BoolMin2MaxTwoArgsCombRep(str, funName)                 \
  beginTest(str);                                                      \
                                                                       \
  MIN2MAX_HALF_BOOL_VECTOR                                             \
                                                                       \
  vectorHalfBoolTest(funName, (__m128i)bvtrue.r, (__m128i)bvtrue.r);   \
  vectorHalfBoolTest(funName, (__m128i)bvtrue.r, (__m128i)bvfalse.r);  \
  vectorHalfBoolTest(funName, (__m128i)bvfalse.r, (__m128i)bvtrue.r);  \
  vectorHalfBoolTest(funName, (__m128i)bvfalse.r, (__m128i)bvfalse.r); \
                                                                       \
  endTest();

/* Packet8f with two args and combinations with repetition */
#define tests8FloatMin2MaxTwoArgsCombRep(str, funName)                                    \
  beginTest(str);                                                                         \
                                                                                          \
  MIN2MAX_FULL_FLOAT_VECTOR                                                               \
                                                                                          \
  allTwoCombRep(vectorFullFloatTest, funName, fvmax.r, fv36.r, fv0.r, fv_240.r, fvmin.r); \
                                                                                          \
  endTest();

/* Packet4d with two args and combinations with repetition */
#define tests4DoubleMin2MaxTwoArgsCombRep(str, funName)                                              \
  beginTest(str);                                                                                    \
                                                                                                     \
  MIN2MAX_FULL_DOUBLE_VECTOR                                                                         \
                                                                                                     \
  allTwoCombRep(vectorFullDoubleTest, funName, (Packet4d)dvmax.r, (Packet4d)dv36.r, (Packet4d)dv0.r, \
                (Packet4d)dv_240.r, (Packet4d)dvmin.r);                                              \
                                                                                                     \
  endTest();

/* Packet8i with two args and combinations with repetition */
#define tests8IntMin2MaxTwoArgsCombRep(str, funName)                                                              \
  beginTest(str);                                                                                                 \
                                                                                                                  \
  MIN2MAX_FULL_INT_VECTOR                                                                                         \
                                                                                                                  \
  allTwoCombRep(vectorFullIntTest, funName, (__m256i)ivmax.r, (__m256i)iv36.r, (__m256i)iv0.r, (__m256i)iv_240.r, \
                (__m256i)ivmin.r);                                                                                \
                                                                                                                  \
  endTest();

/* Packet8h with two args and combinations with repetition */
#define tests8HalfMin2MaxTwoArgsCombRep(str, funName)                                                \
  beginTest(str);                                                                                    \
                                                                                                     \
  MIN2MAX_HALF_HALF_VECTOR                                                                           \
                                                                                                     \
  allTwoCombRep(vectorHalfEigenHalfTest, funName, (__m128i)hvmax.r, (__m128i)hv36.r, (__m128i)hv0.r, \
                (__m128i)hv_240.r, (__m128i)hvmin.r);                                                \
                                                                                                     \
  endTest();

/* Packet8bf with two args and combinations with repetition */
#define tests8Bfloat16Min2MaxTwoArgsCombRep(str, funName)                                              \
  beginTest(str);                                                                                      \
                                                                                                       \
  MIN2MAX_HALF_BFLOAT16_VECTOR                                                                         \
                                                                                                       \
  allTwoCombRep(vectorHalfBfloat16Test, funName, (__m128i)bfvmax.r, (__m128i)bfv36.r, (__m128i)bfv0.r, \
                (__m128i)bfv_240.r, (__m128i)bfvmin.r);                                                \
                                                                                                       \
  endTest();

/* Packet4l with two args and combinations with repetition */
#define tests4LongMin2MaxTwoArgsCombRep(str, funName)                                                              \
  beginTest(str);                                                                                                  \
                                                                                                                   \
  MIN2MAX_FULL_LONG_VECTOR                                                                                         \
                                                                                                                   \
  allTwoCombRep(vectorFullLongTest, funName, (__m256i)lvmax.r, (__m256i)lv36.r, (__m256i)lv0.r, (__m256i)lv_240.r, \
                (__m256i)lvmin.r);                                                                                 \
                                                                                                                   \
  endTest();

/* Packet4f with three args and permutations with repetition */
#define tests4FloatMin2MaxThreeArgsPermRep(str, funName)                                         \
  beginTest(str);                                                                                \
                                                                                                 \
  MIN2MAX_HALF_FLOAT_VECTOR                                                                      \
                                                                                                 \
  allThreePermRep(vectorHalfFloatTest, funName, fhvmax.r, fhv36.r, fhv0.r, fhv_240.r, fhvmin.r); \
                                                                                                 \
  endTest();

/* Packet2d with three args and permutations with repetition */
#define tests2DoubleMin2MaxThreeArgsPermRep(str, funName)                                                 \
  beginTest(str);                                                                                         \
                                                                                                          \
  MIN2MAX_HALF_DOUBLE_VECTOR                                                                              \
                                                                                                          \
  allThreePermRep(vectorHalfDoubleTest, funName, (Packet2d)dhvmax.r, (Packet2d)dhv36.r, (Packet2d)dhv0.r, \
                  (Packet2d)dhv_240.r, (Packet2d)dhvmin.r);                                               \
                                                                                                          \
  endTest();

/* Packet4i with three args and permutations with repetition */
#define tests4IntMin2MaxThreeArgsPermRep(str, funName)                                              \
  beginTest(str);                                                                                   \
                                                                                                    \
  MIN2MAX_HALF_INT_VECTOR                                                                           \
                                                                                                    \
  allThreePermRep(vectorHalfIntTest, funName, (__m128i)ihvmax.r, (__m128i)ihv36.r, (__m128i)ihv0.r, \
                  (__m128i)ihv_240.r, (__m128i)ihvmin.r);                                           \
                                                                                                    \
  endTest();

/* Packet16b with three args and permutations with repetition */
#define tests16BoolMin2MaxThreeArgsPermRep(str, funName)                                   \
  beginTest(str);                                                                          \
                                                                                           \
  MIN2MAX_HALF_BOOL_VECTOR                                                                 \
                                                                                           \
  vectorHalfBoolTest(funName, (__m128i)bvtrue.r, (__m128i)bvtrue.r, (__m128i)bvtrue.r);    \
  vectorHalfBoolTest(funName, (__m128i)bvtrue.r, (__m128i)bvtrue.r, (__m128i)bvfalse.r);   \
  vectorHalfBoolTest(funName, (__m128i)bvtrue.r, (__m128i)bvfalse.r, (__m128i)bvtrue.r);   \
  vectorHalfBoolTest(funName, (__m128i)bvtrue.r, (__m128i)bvfalse.r, (__m128i)bvfalse.r);  \
  vectorHalfBoolTest(funName, (__m128i)bvfalse.r, (__m128i)bvtrue.r, (__m128i)bvtrue.r);   \
  vectorHalfBoolTest(funName, (__m128i)bvfalse.r, (__m128i)bvtrue.r, (__m128i)bvfalse.r);  \
  vectorHalfBoolTest(funName, (__m128i)bvfalse.r, (__m128i)bvfalse.r, (__m128i)bvtrue.r);  \
  vectorHalfBoolTest(funName, (__m128i)bvfalse.r, (__m128i)bvfalse.r, (__m128i)bvfalse.r); \
                                                                                           \
  endTest();

/* Packet8f with three args and permutations with repetition */
#define tests8FloatMin2MaxThreeArgsPermRep(str, funName)                                    \
  beginTest(str);                                                                           \
                                                                                            \
  MIN2MAX_FULL_FLOAT_VECTOR                                                                 \
                                                                                            \
  allThreePermRep(vectorFullFloatTest, funName, fvmax.r, fv36.r, fv0.r, fv_240.r, fvmin.r); \
                                                                                            \
  endTest();

/* Packet4d with three args and permutations with repetition */
#define tests4DoubleMin2MaxThreeArgsPermRep(str, funName)                                              \
  beginTest(str);                                                                                      \
                                                                                                       \
  MIN2MAX_FULL_DOUBLE_VECTOR                                                                           \
                                                                                                       \
  allThreePermRep(vectorFullDoubleTest, funName, (Packet4d)dvmax.r, (Packet4d)dv36.r, (Packet4d)dv0.r, \
                  (Packet4d)dv_240.r, (Packet4d)dvmin.r);                                              \
                                                                                                       \
  endTest();

/* Packet8i with three args and permutations with repetition */
#define tests8IntMin2MaxThreeArgsPermRep(str, funName)                                                              \
  beginTest(str);                                                                                                   \
                                                                                                                    \
  MIN2MAX_FULL_INT_VECTOR                                                                                           \
                                                                                                                    \
  allThreePermRep(vectorFullIntTest, funName, (__m256i)ivmax.r, (__m256i)iv36.r, (__m256i)iv0.r, (__m256i)iv_240.r, \
                  (__m256i)ivmin.r);                                                                                \
                                                                                                                    \
  endTest();

/* Packet8h with three args and permutations with repetition */
#define tests8HalfMin2MaxThreeArgsPermRep(str, funName)                                                \
  beginTest(str);                                                                                      \
                                                                                                       \
  MIN2MAX_HALF_HALF_VECTOR                                                                             \
                                                                                                       \
  allThreePermRep(vectorHalfEigenHalfTest, funName, (__m128i)hvmax.r, (__m128i)hv36.r, (__m128i)hv0.r, \
                  (__m128i)hv_240.r, (__m128i)hvmin.r);                                                \
                                                                                                       \
  endTest();

/* Packet8bf with three args and permutations with repetition */
#define tests8Bfloat16Min2MaxThreeArgsPermRep(str, funName)                                              \
  beginTest(str);                                                                                        \
                                                                                                         \
  MIN2MAX_HALF_BFLOAT16_VECTOR                                                                           \
                                                                                                         \
  allThreePermRep(vectorHalfBfloat16Test, funName, (__m128i)bfvmax.r, (__m128i)bfv36.r, (__m128i)bfv0.r, \
                  (__m128i)bfv_240.r, (__m128i)bfvmin.r);                                                \
                                                                                                         \
  endTest();

/* Packet4l with three args and permutations with repetition */
#define tests4LongMin2MaxThreeArgsPermRep(str, funName)                                                              \
  beginTest(str);                                                                                                    \
                                                                                                                     \
  MIN2MAX_FULL_LONG_VECTOR                                                                                           \
                                                                                                                     \
  allThreePermRep(vectorFullLongTest, funName, (__m256i)lvmax.r, (__m256i)lv36.r, (__m256i)lv0.r, (__m256i)lv_240.r, \
                  (__m256i)lvmin.r);                                                                                 \
                                                                                                                     \
  endTest();

#endif  // EIGEN_MIPP_TEST_DEF_H