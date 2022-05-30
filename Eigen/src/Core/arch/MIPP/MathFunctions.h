// This file is part of Eigen, a lightweight C++ template library
// for linear algebra.
//
// Copyright (C) 2014 Pedro Gonnet (pedro.gonnet@gmail.com)
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef EIGEN_MATH_FUNCTIONS_MIPP_H
#define EIGEN_MATH_FUNCTIONS_MIPP_H

#include "../../InternalHeaderCheck.h"

namespace Eigen {

namespace internal {

template<> EIGEN_DEFINE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS
Packet4f plog<Packet4f>(const Packet4f& _x) {
  return plog_float(_x);
}

template <>
EIGEN_DEFINE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS Packet8f
plog<Packet8f>(const Packet8f& _x) {
  return plog_float(_x);
}

template<> EIGEN_DEFINE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS
Packet2d plog<Packet2d>(const Packet2d& _x) {
  return plog_double(_x);
}

template <>
EIGEN_DEFINE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS Packet4d
plog<Packet4d>(const Packet4d& _x) {
  return plog_double(_x);
}

template<> EIGEN_DEFINE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS
Packet4f plog2<Packet4f>(const Packet4f& _x) {
  return plog2_float(_x);
}

template <>
EIGEN_DEFINE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS Packet8f
plog2<Packet8f>(const Packet8f& _x) {
  return plog2_float(_x);
}

template<> EIGEN_DEFINE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS
Packet2d plog2<Packet2d>(const Packet2d& _x) {
  return plog2_double(_x);
}

template <>
EIGEN_DEFINE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS Packet4d
plog2<Packet4d>(const Packet4d& _x) {
  return plog2_double(_x);
}

template<> EIGEN_DEFINE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS
Packet4f plog1p<Packet4f>(const Packet4f& _x) {
  return generic_plog1p(_x);
}

template<> EIGEN_DEFINE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS
Packet8f plog1p<Packet8f>(const Packet8f& _x) {
  return generic_plog1p(_x);
}

template<> EIGEN_DEFINE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS
Packet4f pexpm1<Packet4f>(const Packet4f& _x) {
  return generic_expm1(_x);
}

template<> EIGEN_DEFINE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS
Packet8f pexpm1<Packet8f>(const Packet8f& _x) {
  return generic_expm1(_x);
}

template<> EIGEN_DEFINE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS
Packet4f pexp<Packet4f>(const Packet4f& _x)
{
  return pexp_float(_x);
}

// Exponential function. Works by writing "x = m*log(2) + r" where
// "m = floor(x/log(2)+1/2)" and "r" is the remainder. The result is then
// "exp(x) = 2^m*exp(r)" where exp(r) is in the range [-1,1).
template <>
EIGEN_DEFINE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS Packet8f
pexp<Packet8f>(const Packet8f& _x) {
  return pexp_float(_x);
}

template<> EIGEN_DEFINE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS
Packet2d pexp<Packet2d>(const Packet2d& x)
{
  return pexp_double(x);
}

// Exponential function for doubles.
template <>
EIGEN_DEFINE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS Packet4d
pexp<Packet4d>(const Packet4d& _x) {
  return pexp_double(_x);
}

template<> EIGEN_DEFINE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS
Packet4f psin<Packet4f>(const Packet4f& _x)
{
  return psin_float(_x);
}

template <>
EIGEN_DEFINE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS Packet8f
psin<Packet8f>(const Packet8f& _x) {
  return psin_float(_x);
}

template<> EIGEN_DEFINE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS
Packet4f pcos<Packet4f>(const Packet4f& _x)
{
  return pcos_float(_x);
}

template <>
EIGEN_DEFINE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS Packet8f
pcos<Packet8f>(const Packet8f& _x) {
  return pcos_float(_x);
}

// Notice that for newer processors, it is counterproductive to use Newton
// iteration for square root. In particular, Skylake and Zen2 processors
// have approximately doubled throughput of the _mm_sqrt_ps instruction
// compared to their predecessors.
template<>EIGEN_DEFINE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS
Packet4f psqrt<Packet4f>(const Packet4f& x) { return _mm_sqrt_ps(x); }
template <> EIGEN_DEFINE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS
Packet8f psqrt<Packet8f>(const Packet8f& _x) { return _mm256_sqrt_ps(_x); }
template<> EIGEN_DEFINE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS
Packet2d psqrt<Packet2d>(const Packet2d& x) { return _mm_sqrt_pd(x); }
template <> EIGEN_DEFINE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS
Packet4d psqrt<Packet4d>(const Packet4d& _x) { return _mm256_sqrt_pd(_x); }
template<> EIGEN_DEFINE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS
Packet16b psqrt<Packet16b>(const Packet16b& x) { return x; }

#if EIGEN_FAST_MATH
// Even on Skylake, using Newton iteration is a win for reciprocal square root.
template<> EIGEN_DEFINE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS EIGEN_UNUSED
Packet4f prsqrt<Packet4f>(const Packet4f& x) {
  return generic_rsqrt_newton_step<Packet4f, /*Steps=*/1>::run(x, _mm_rsqrt_ps(x));
}

template<> EIGEN_DEFINE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS
Packet8f prsqrt<Packet8f>(const Packet8f& a) {
  // _mm256_rsqrt_ps returns -inf for negative denormals.
  // _mm512_rsqrt**_ps returns -NaN for negative denormals.  We may want
  // consistency here.
  // const Packet8f rsqrt = pselect(pcmp_lt(a, pzero(a)),
  //                                pset1<Packet8f>(-NumTraits<float>::quiet_NaN()),
  //                                _mm256_rsqrt_ps(a));
  return generic_rsqrt_newton_step<Packet8f, /*Steps=*/1>::run(a, _mm256_rsqrt_ps(a));
}

#ifdef EIGEN_VECTORIZE_FMA
// Trying to speed up reciprocal using Newton-Raphson is counterproductive
// unless FMA is available. Without FMA pdiv(pset1<Packet>(Scalar(1),a)) is
// 30% faster.
template<> EIGEN_STRONG_INLINE Packet4f preciprocal<Packet4f>(const Packet4f& x) {
  return generic_reciprocal_newton_step<Packet4f, /*Steps=*/1>::run(x, _mm_rcp_ps(x));
}
template<> EIGEN_STRONG_INLINE Packet8f preciprocal<Packet8f>(const Packet8f& a) {
  return generic_reciprocal_newton_step<Packet8f, /*Steps=*/1>::run(a, _mm256_rcp_ps(a));
}
#endif

#endif

// Hyperbolic Tangent function.
template <>
EIGEN_DEFINE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS Packet4f
ptanh<Packet4f>(const Packet4f& x) {
  return internal::generic_fast_tanh_float(x);
}

template <>
EIGEN_DEFINE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS Packet8f
ptanh<Packet8f>(const Packet8f& _x) {
  return internal::generic_fast_tanh_float(_x);
}

F16_PACKET_FUNCTION(Packet8f, Packet8h, psin)
F16_PACKET_FUNCTION(Packet8f, Packet8h, pcos)
F16_PACKET_FUNCTION(Packet8f, Packet8h, plog)
F16_PACKET_FUNCTION(Packet8f, Packet8h, plog2)
F16_PACKET_FUNCTION(Packet8f, Packet8h, plog1p)
F16_PACKET_FUNCTION(Packet8f, Packet8h, pexpm1)
F16_PACKET_FUNCTION(Packet8f, Packet8h, pexp)
F16_PACKET_FUNCTION(Packet8f, Packet8h, ptanh)
F16_PACKET_FUNCTION(Packet8f, Packet8h, psqrt)
F16_PACKET_FUNCTION(Packet8f, Packet8h, prsqrt)
F16_PACKET_FUNCTION(Packet8f, Packet8h, preciprocal)

template <>
EIGEN_STRONG_INLINE Packet8h pfrexp(const Packet8h& a, Packet8h& exponent) {
  Packet8f fexponent;
  const Packet8h out = float2half(pfrexp<Packet8f>(half2float(a), fexponent));
  exponent = float2half(fexponent);
  return out;
}

template <>
EIGEN_STRONG_INLINE Packet8h pldexp(const Packet8h& a, const Packet8h& exponent) {
  return float2half(pldexp<Packet8f>(half2float(a), half2float(exponent)));
}

BF16_PACKET_FUNCTION(Packet8f, Packet8bf, psin)
BF16_PACKET_FUNCTION(Packet8f, Packet8bf, pcos)
BF16_PACKET_FUNCTION(Packet8f, Packet8bf, plog)
BF16_PACKET_FUNCTION(Packet8f, Packet8bf, plog2)
BF16_PACKET_FUNCTION(Packet8f, Packet8bf, plog1p)
BF16_PACKET_FUNCTION(Packet8f, Packet8bf, pexpm1)
BF16_PACKET_FUNCTION(Packet8f, Packet8bf, pexp)
BF16_PACKET_FUNCTION(Packet8f, Packet8bf, ptanh)
BF16_PACKET_FUNCTION(Packet8f, Packet8bf, psqrt)
BF16_PACKET_FUNCTION(Packet8f, Packet8bf, prsqrt)
BF16_PACKET_FUNCTION(Packet8f, Packet8bf, preciprocal)

template <>
EIGEN_STRONG_INLINE Packet8bf pfrexp(const Packet8bf& a, Packet8bf& exponent) {
  Packet8f fexponent;
  const Packet8bf out = F32ToBf16(pfrexp<Packet8f>(Bf16ToF32(a), fexponent));
  exponent = F32ToBf16(fexponent);
  return out;
}

template <>
EIGEN_STRONG_INLINE Packet8bf pldexp(const Packet8bf& a, const Packet8bf& exponent) {
  return F32ToBf16(pldexp<Packet8f>(Bf16ToF32(a), Bf16ToF32(exponent)));
}

} // end namespace internal

namespace numext {

template<>
EIGEN_DEVICE_FUNC EIGEN_ALWAYS_INLINE
float sqrt(const float &x)
{
  return internal::pfirst(internal::Packet4f(_mm_sqrt_ss(_mm_set_ss(x))));
}

template<>
EIGEN_DEVICE_FUNC EIGEN_ALWAYS_INLINE
double sqrt(const double &x)
{
#if EIGEN_COMP_GNUC_STRICT
  // This works around a GCC bug generating poor code for _mm_sqrt_pd
  // See https://gitlab.com/libeigen/eigen/commit/8dca9f97e38970
  return internal::pfirst(internal::Packet2d(__builtin_ia32_sqrtsd(_mm_set_sd(x))));
#else
  return internal::pfirst(internal::Packet2d(_mm_sqrt_pd(_mm_set_sd(x))));
#endif
}

} // end namespace numext

} // end namespace Eigen

#endif  // EIGEN_MATH_FUNCTIONS_MIPP_H
