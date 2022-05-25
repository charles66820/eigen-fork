// This file is part of Eigen, a lightweight C++ template library
// for linear algebra.
//
// Copyright (C) 2014 Benoit Steiner (benoit.steiner.goog@gmail.com)
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef EIGEN_PACKET_MATH_MIPP_H
#define EIGEN_PACKET_MATH_MIPP_H

#include "../../InternalHeaderCheck.h"

#undef min
#undef max
#include "../../../../../../MIPP/src/mipp.h"

namespace Eigen {

namespace internal {

#ifndef EIGEN_CACHEFRIENDLY_PRODUCT_THRESHOLD
#define EIGEN_CACHEFRIENDLY_PRODUCT_THRESHOLD 8
#endif

#if !defined(EIGEN_VECTORIZE_AVX) && !defined(EIGEN_ARCH_DEFAULT_NUMBER_OF_REGISTERS)
// 32 bits =>  8 registers
// 64 bits => 16 registers
#define EIGEN_ARCH_DEFAULT_NUMBER_OF_REGISTERS (2*sizeof(void*))
#endif

#ifdef EIGEN_VECTORIZE_FMA
#ifndef EIGEN_HAS_SINGLE_INSTRUCTION_MADD
#define EIGEN_HAS_SINGLE_INSTRUCTION_MADD
#endif
#endif

#if ((defined EIGEN_VECTORIZE_AVX) && (EIGEN_COMP_GNUC_STRICT || EIGEN_COMP_MINGW || EIGEN_COMP_LCC) && (__GXX_ABI_VERSION < 1004)) || EIGEN_OS_QNX
// With GCC's default ABI version, a __m128 or __m256 are the same types and therefore we cannot
// have overloads for both types without linking error.
// One solution is to increase ABI version using -fabi-version=4 (or greater).
// Otherwise, we workaround this inconvenience by wrapping 128bit types into the following helper
// structure:
typedef eigen_packet_wrapper<__m128>  Packet4f;
typedef eigen_packet_wrapper<__m128d> Packet2d;
#else
typedef __m128  Packet4f;
typedef __m128d Packet2d;
#endif

typedef eigen_packet_wrapper<__m128i, 0> Packet4i;
typedef eigen_packet_wrapper<__m128i, 1> Packet16b;

template<> struct is_arithmetic<__m128>  { enum { value = true }; };
template<> struct is_arithmetic<__m128i> { enum { value = true }; };
template<> struct is_arithmetic<__m128d> { enum { value = true }; };
template<> struct is_arithmetic<Packet4i>  { enum { value = true }; };
template<> struct is_arithmetic<Packet16b>  { enum { value = true }; };

template<int p, int q, int r, int s>
struct shuffle_mask{
 enum { mask = (s)<<6|(r)<<4|(q)<<2|(p) };
};

// TODO: change the implementation of all swizzle* ops from macro to template,
#define vec4f_swizzle1(v,p,q,r,s) \
  Packet4f(_mm_castsi128_ps(_mm_shuffle_epi32( _mm_castps_si128(v), (shuffle_mask<p,q,r,s>::mask))))

#define vec4i_swizzle1(v,p,q,r,s) \
  Packet4i(_mm_shuffle_epi32( v, (shuffle_mask<p,q,r,s>::mask)))

#define vec2d_swizzle1(v,p,q) \
  Packet2d(_mm_castsi128_pd(_mm_shuffle_epi32( _mm_castpd_si128(v), (shuffle_mask<2*p,2*p+1,2*q,2*q+1>::mask))))

#define vec4f_swizzle2(a,b,p,q,r,s) \
  Packet4f(_mm_shuffle_ps( (a), (b), (shuffle_mask<p,q,r,s>::mask)))

#define vec4i_swizzle2(a,b,p,q,r,s) \
  Packet4i(_mm_castps_si128( (_mm_shuffle_ps( _mm_castsi128_ps(a), _mm_castsi128_ps(b), (shuffle_mask<p,q,r,s>::mask)))))

EIGEN_STRONG_INLINE Packet4f vec4f_movelh(const Packet4f& a, const Packet4f& b)
{
  return Packet4f(_mm_movelh_ps(a,b));
}
EIGEN_STRONG_INLINE Packet4f vec4f_movehl(const Packet4f& a, const Packet4f& b)
{
  return Packet4f(_mm_movehl_ps(a,b));
}
EIGEN_STRONG_INLINE Packet4f vec4f_unpacklo(const Packet4f& a, const Packet4f& b)
{
  return Packet4f(_mm_unpacklo_ps(a,b));
}
EIGEN_STRONG_INLINE Packet4f vec4f_unpackhi(const Packet4f& a, const Packet4f& b)
{
  return Packet4f(_mm_unpackhi_ps(a,b));
}
#define vec4f_duplane(a,p) \
  vec4f_swizzle2(a,a,p,p,p,p)

#define vec2d_swizzle2(a,b,mask) \
  Packet2d(_mm_shuffle_pd(a,b,mask))

EIGEN_STRONG_INLINE Packet2d vec2d_unpacklo(const Packet2d& a, const Packet2d& b)
{
  return Packet2d(_mm_unpacklo_pd(a,b));
}
EIGEN_STRONG_INLINE Packet2d vec2d_unpackhi(const Packet2d& a, const Packet2d& b)
{
  return Packet2d(_mm_unpackhi_pd(a,b));
}
#define vec2d_duplane(a,p) \
  vec2d_swizzle2(a,a,(p<<1)|p)

#define EIGEN_DECLARE_CONST_Packet4f(NAME,X) \
  const Packet4f p4f_##NAME = pset1<Packet4f>(X)

#define EIGEN_DECLARE_CONST_Packet2d(NAME,X) \
  const Packet2d p2d_##NAME = pset1<Packet2d>(X)

#define EIGEN_DECLARE_CONST_Packet4f_FROM_INT(NAME,X) \
  const Packet4f p4f_##NAME = pset1frombits<Packet4f>(X)

#define EIGEN_DECLARE_CONST_Packet4i(NAME,X) \
  const Packet4i p4i_##NAME = pset1<Packet4i>(X)


// Use the packet_traits defined in AVX/PacketMath.h instead if we're going
// to leverage AVX instructions.
#ifndef EIGEN_VECTORIZE_AVX
template <>
struct packet_traits<float> : default_packet_traits {
  typedef Packet4f type;
  typedef Packet4f half;
  enum {
    Vectorizable = 1,
    AlignedOnScalar = 1,
    size = 4,
    HasHalfPacket = 0,

    HasCmp  = 1,
    HasDiv = 1,
    HasReciprocal = EIGEN_FAST_MATH,
    HasSin = EIGEN_FAST_MATH,
    HasCos = EIGEN_FAST_MATH,
    HasLog = 1,
    HasLog1p = 1,
    HasExpm1 = 1,
    HasNdtri = 1,
    HasExp = 1,
    HasBessel = 1,
    HasSqrt = 1,
    HasRsqrt = 1,
    HasTanh = EIGEN_FAST_MATH,
    HasErf = EIGEN_FAST_MATH,
    HasBlend = 1,
    HasCeil = 1,
    HasFloor = 1,
#ifdef EIGEN_VECTORIZE_SSE4_1
    HasRound = 1,
#endif
    HasRint = 1
  };
};
template <>
struct packet_traits<double> : default_packet_traits {
  typedef Packet2d type;
  typedef Packet2d half;
  enum {
    Vectorizable = 1,
    AlignedOnScalar = 1,
    size=2,
    HasHalfPacket = 0,

    HasCmp  = 1,
    HasDiv  = 1,
    HasLog  = 1,
    HasExp  = 1,
    HasSqrt = 1,
    HasRsqrt = 1,
    HasBlend = 1,
    HasFloor = 1,
    HasCeil = 1,
#ifdef EIGEN_VECTORIZE_SSE4_1
    HasRound = 1,
#endif
    HasRint = 1
  };
};
template<> struct packet_traits<int>    : default_packet_traits
{
  typedef Packet4i type;
  typedef Packet4i half;
  enum {
    Vectorizable = 1,
    AlignedOnScalar = 1,
    size=4,

    HasShift = 1,
    HasBlend = 1
  };
};
#endif
template<> struct packet_traits<bool> : default_packet_traits
{
  typedef Packet16b type;
  typedef Packet16b half;
  enum {
    Vectorizable = 1,
    AlignedOnScalar = 1,
    HasHalfPacket = 0,
    size=16,

    HasAdd       = 1,
    HasSub       = 1,
    HasShift     = 0,
    HasMul       = 1,
    HasNegate    = 1,
    HasAbs       = 0,
    HasAbs2      = 0,
    HasMin       = 0,
    HasMax       = 0,
    HasConj      = 0,
    HasSqrt      = 1
  };
};

#if !defined(EIGEN_VECTORIZE_AVX512) && !defined(EIGEN_ARCH_DEFAULT_NUMBER_OF_REGISTERS)
#define EIGEN_ARCH_DEFAULT_NUMBER_OF_REGISTERS 16
#endif

#ifdef EIGEN_VECTORIZE_FMA
#ifndef EIGEN_HAS_SINGLE_INSTRUCTION_MADD
#define EIGEN_HAS_SINGLE_INSTRUCTION_MADD
#endif
#endif

typedef __m256  Packet8f;
typedef eigen_packet_wrapper<__m256i, 0> Packet8i;
typedef __m256d Packet4d;
typedef eigen_packet_wrapper<__m128i, 2> Packet8h;
typedef eigen_packet_wrapper<__m128i, 3> Packet8bf;

#ifdef EIGEN_VECTORIZE_AVX2
// Start from 3 to be compatible with AVX512
typedef eigen_packet_wrapper<__m256i, 3> Packet4l;
#endif

template<> struct is_arithmetic<__m256>  { enum { value = true }; };
template<> struct is_arithmetic<__m256i> { enum { value = true }; };
template<> struct is_arithmetic<__m256d> { enum { value = true }; };
template<> struct is_arithmetic<Packet8i> { enum { value = true }; };
template<> struct is_arithmetic<Packet8h> { enum { value = true }; };
template<> struct is_arithmetic<Packet8bf> { enum { value = true }; };
#ifdef EIGEN_VECTORIZE_AVX2
template<> struct is_arithmetic<Packet4l> { enum { value = true }; };
#endif
/*
// Use the packet_traits defined in AVX512/PacketMath.h instead if we're going
// to leverage AVX512 instructions.
#ifndef EIGEN_VECTORIZE_AVX512
template<> struct packet_traits<float>  : default_packet_traits
{
  typedef Packet8f type;
  typedef Packet4f half;
  enum {
    Vectorizable = 1,
    AlignedOnScalar = 1,
    size = 8,
    HasHalfPacket = 1,

    HasCmp  = 1,
    HasDiv = 1,
    HasReciprocal = EIGEN_FAST_MATH,
    HasSin = EIGEN_FAST_MATH,
    HasCos = EIGEN_FAST_MATH,
    HasLog = 1,
    HasLog1p = 1,
    HasExpm1 = 1,
    HasExp = 1,
    HasNdtri = 1,
    HasBessel = 1,
    HasSqrt = 1,
    HasRsqrt = 1,
    HasTanh = EIGEN_FAST_MATH,
    HasErf = EIGEN_FAST_MATH,
    HasBlend = 1,
    HasRound = 1,
    HasFloor = 1,
    HasCeil = 1,
    HasRint = 1
  };
};
template<> struct packet_traits<double> : default_packet_traits
{
  typedef Packet4d type;
  typedef Packet2d half;
  enum {
    Vectorizable = 1,
    AlignedOnScalar = 1,
    size=4,
    HasHalfPacket = 1,

    HasCmp  = 1,
    HasDiv  = 1,
    HasLog  = 1,
    HasExp  = 1,
    HasSqrt = 1,
    HasRsqrt = 1,
    HasBlend = 1,
    HasRound = 1,
    HasFloor = 1,
    HasCeil = 1,
    HasRint = 1
  };
};

template <>
struct packet_traits<Eigen::half> : default_packet_traits {
  typedef Packet8h type;
  // There is no half-size packet for Packet8h.
  typedef Packet8h half;
  enum {
    Vectorizable = 1,
    AlignedOnScalar = 1,
    size = 8,
    HasHalfPacket = 0,

    HasCmp    = 1,
    HasAdd    = 1,
    HasSub    = 1,
    HasMul    = 1,
    HasDiv    = 1,
    HasSin    = EIGEN_FAST_MATH,
    HasCos    = EIGEN_FAST_MATH,
    HasNegate = 1,
    HasAbs    = 1,
    HasAbs2   = 0,
    HasMin    = 1,
    HasMax    = 1,
    HasConj   = 1,
    HasSetLinear = 0,
    HasLog    = 1,
    HasLog1p  = 1,
    HasExpm1  = 1,
    HasExp    = 1,
    HasSqrt   = 1,
    HasRsqrt  = 1,
    HasTanh   = EIGEN_FAST_MATH,
    HasErf    = EIGEN_FAST_MATH,
    HasBlend  = 0,
    HasRound  = 1,
    HasFloor  = 1,
    HasCeil   = 1,
    HasRint   = 1,
    HasBessel = 1,
    HasNdtri  = 1
  };
};

template <>
struct packet_traits<bfloat16> : default_packet_traits {
  typedef Packet8bf type;
  // There is no half-size packet for current Packet8bf.
  // TODO: support as SSE path.
  typedef Packet8bf half;
  enum {
    Vectorizable = 1,
    AlignedOnScalar = 1,
    size = 8,
    HasHalfPacket = 0,

    HasCmp = 1,
    HasAdd = 1,
    HasSub = 1,
    HasMul = 1,
    HasDiv = 1,
    HasSin = EIGEN_FAST_MATH,
    HasCos = EIGEN_FAST_MATH,
    HasNegate = 1,
    HasAbs    = 1,
    HasAbs2   = 0,
    HasMin    = 1,
    HasMax    = 1,
    HasConj   = 1,
    HasSetLinear = 0,
    HasLog = 1,
    HasLog1p  = 1,
    HasExpm1  = 1,
    HasExp = 1,
    HasSqrt = 1,
    HasRsqrt = 1,
    HasTanh = EIGEN_FAST_MATH,
    HasErf = EIGEN_FAST_MATH,
    HasBlend = 0,
    HasRound = 1,
    HasFloor = 1,
    HasCeil = 1,
    HasRint = 1,
    HasBessel = 1,
    HasNdtri  = 1
  };
};

template<> struct packet_traits<int> : default_packet_traits
{
  typedef Packet8i type;
  typedef Packet4i half;
  enum {
    Vectorizable = 1,
    AlignedOnScalar = 1,
    size=8
  };
};

#ifdef EIGEN_VECTORIZE_AVX2
template<> struct packet_traits<int64_t> : default_packet_traits
{
  typedef Packet4l type;
  // There is no half-size packet for current Packet4l.
  // TODO: support as SSE path.
  typedef Packet4l half;
  enum {
    Vectorizable = 1,
    AlignedOnScalar = 1,
    size=4,

    // requires AVX512
    HasShift     = 0,
  };
};
#endif

#endif
*/

#ifndef EIGEN_VECTORIZE_AVX
template<> struct scalar_div_cost<float,true> { enum { value = 7 }; };
template<> struct scalar_div_cost<double,true> { enum { value = 8 }; };
#else
template<> struct scalar_div_cost<float,true> { enum { value = 14 }; };
template<> struct scalar_div_cost<double,true> { enum { value = 16 }; };
#endif

template<> struct unpacket_traits<Packet4f> {
  typedef float     type;
  typedef Packet4f  half;
  typedef Packet4i  integer_packet;
  enum {size=4, alignment=Aligned16, vectorizable=true, masked_load_available=false, masked_store_available=false};
};
template<> struct unpacket_traits<Packet2d> {
  typedef double    type;
  typedef Packet2d  half;
  enum {size=2, alignment=Aligned16, vectorizable=true, masked_load_available=false, masked_store_available=false};
};
template<> struct unpacket_traits<Packet4i> {
  typedef int       type;
  typedef Packet4i  half;
  enum {size=4, alignment=Aligned16, vectorizable=true, masked_load_available=false, masked_store_available=false};
};
template<> struct unpacket_traits<Packet16b> {
  typedef bool       type;
  typedef Packet16b  half;
  enum {size=16, alignment=Aligned16, vectorizable=true, masked_load_available=false, masked_store_available=false};
};

template<> struct unpacket_traits<Packet8f> {
  typedef float     type;
  typedef Packet4f  half;
  typedef Packet8i  integer_packet;
  typedef uint8_t   mask_t;
  enum {size=8, alignment=Aligned32, vectorizable=true, masked_load_available=true, masked_store_available=true
#ifdef EIGEN_VECTORIZE_AVX512
    , masked_fpops_available=true
#endif
  };
};
template<> struct unpacket_traits<Packet4d> {
  typedef double type;
  typedef Packet2d half;
  enum {size=4, alignment=Aligned32, vectorizable=true, masked_load_available=false, masked_store_available=false};
};
template<> struct unpacket_traits<Packet8i> {
  typedef int    type;
  typedef Packet4i half;
  enum {size=8, alignment=Aligned32, vectorizable=true, masked_load_available=false, masked_store_available=false};
};
#ifdef EIGEN_VECTORIZE_AVX2
template<> struct unpacket_traits<Packet4l> {
  typedef int64_t    type;
  typedef Packet4l half;
  enum {size=4, alignment=Aligned32, vectorizable=true, masked_load_available=false, masked_store_available=false};
};
#endif
template<> struct unpacket_traits<Packet8bf> {
  typedef bfloat16 type;
  typedef Packet8bf half;
  enum {size=8, alignment=Aligned16, vectorizable=true, masked_load_available=false, masked_store_available=false};
};

// Helper function for bit packing snippet of low precision comparison.
// It packs the flags from 16x16 to 8x16.
EIGEN_STRONG_INLINE __m128i Pack16To8(Packet8f rf) {
  return _mm_packs_epi32(_mm256_extractf128_si256(_mm256_castps_si256(rf), 0),
                         _mm256_extractf128_si256(_mm256_castps_si256(rf), 1));
}

#ifdef EIGEN_VECTORIZE_AVX2
template <>
EIGEN_STRONG_INLINE Packet4l pset1<Packet4l>(const int64_t& from) {
  return _mm256_set1_epi64x(from);
}
template <>
EIGEN_STRONG_INLINE Packet4l pzero(const Packet4l& /*a*/) {
  return _mm256_setzero_si256();
}
template <>
EIGEN_STRONG_INLINE Packet4l peven_mask(const Packet4l& /*a*/) {
  return _mm256_set_epi64x(0ll, -1ll, 0ll, -1ll);
}
template <>
EIGEN_STRONG_INLINE Packet4l pload1<Packet4l>(const int64_t* from) {
  return _mm256_set1_epi64x(*from);
}
template <>
EIGEN_STRONG_INLINE Packet4l padd<Packet4l>(const Packet4l& a, const Packet4l& b) {
  return _mm256_add_epi64(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet4l plset<Packet4l>(const int64_t& a) {
  return padd(pset1<Packet4l>(a), Packet4l(_mm256_set_epi64x(3ll, 2ll, 1ll, 0ll)));
}
template <>
EIGEN_STRONG_INLINE Packet4l psub<Packet4l>(const Packet4l& a, const Packet4l& b) {
  return _mm256_sub_epi64(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet4l pnegate(const Packet4l& a) {
  return psub(pzero(a), a);
}
template <>
EIGEN_STRONG_INLINE Packet4l pconj(const Packet4l& a) {
  return a;
}
template <>
EIGEN_STRONG_INLINE Packet4l pcmp_le(const Packet4l& a, const Packet4l& b) {
  return _mm256_xor_si256(_mm256_cmpgt_epi64(a, b), _mm256_set1_epi32(-1));
}
template <>
EIGEN_STRONG_INLINE Packet4l pcmp_lt(const Packet4l& a, const Packet4l& b) {
  return _mm256_cmpgt_epi64(b, a);
}
template <>
EIGEN_STRONG_INLINE Packet4l pcmp_eq(const Packet4l& a, const Packet4l& b) {
  return _mm256_cmpeq_epi64(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet4l ptrue<Packet4l>(const Packet4l& a) {
  return _mm256_cmpeq_epi64(a, a);
}
template <>
EIGEN_STRONG_INLINE Packet4l pand<Packet4l>(const Packet4l& a, const Packet4l& b) {
  return _mm256_and_si256(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet4l por<Packet4l>(const Packet4l& a, const Packet4l& b) {
  return _mm256_or_si256(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet4l pxor<Packet4l>(const Packet4l& a, const Packet4l& b) {
  return _mm256_xor_si256(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet4l pandnot<Packet4l>(const Packet4l& a, const Packet4l& b) {
  return _mm256_andnot_si256(b, a);
}
template <int N>
EIGEN_STRONG_INLINE Packet4l plogical_shift_right(Packet4l a) {
  return _mm256_srli_epi64(a, N);
}
template <int N>
EIGEN_STRONG_INLINE Packet4l plogical_shift_left(Packet4l a) {
  return _mm256_slli_epi64(a, N);
}
template <>
EIGEN_STRONG_INLINE Packet4l pload<Packet4l>(const int64_t* from) {
  EIGEN_DEBUG_ALIGNED_LOAD return _mm256_load_si256(reinterpret_cast<const __m256i*>(from));
}
template <>
EIGEN_STRONG_INLINE Packet4l ploadu<Packet4l>(const int64_t* from) {
  EIGEN_DEBUG_UNALIGNED_LOAD return _mm256_loadu_si256(reinterpret_cast<const __m256i*>(from));
}
// Loads 2 int64_ts from memory a returns the packet {a0, a0, a1, a1}
template <>
EIGEN_STRONG_INLINE Packet4l ploaddup<Packet4l>(const int64_t* from) {
  const Packet4l a = _mm256_castsi128_si256(_mm_loadu_si128(reinterpret_cast<const __m128i*>(from)));
  return _mm256_permutevar8x32_epi32(a, _mm256_setr_epi32(0, 1, 0, 1, 2, 3, 2, 3));
}
template <>
EIGEN_STRONG_INLINE void pstore<int64_t>(int64_t* to, const Packet4l& from) {
  EIGEN_DEBUG_ALIGNED_STORE _mm256_storeu_si256(reinterpret_cast<__m256i*>(to), from);
}
template <>
EIGEN_STRONG_INLINE void pstoreu<int64_t>(int64_t* to, const Packet4l& from) {
  EIGEN_DEBUG_UNALIGNED_STORE _mm256_storeu_si256(reinterpret_cast<__m256i*>(to), from);
}
template <>
EIGEN_DEVICE_FUNC inline Packet4l pgather<int64_t, Packet4l>(const int64_t* from, Index stride) {
  return _mm256_set_epi64x(from[3 * stride], from[2 * stride], from[1 * stride], from[0 * stride]);
}
template <>
EIGEN_DEVICE_FUNC inline void pscatter<int64_t, Packet4l>(int64_t* to, const Packet4l& from, Index stride) {
  __m128i low = _mm256_extractf128_si256(from, 0);
  to[stride * 0] = _mm_extract_epi64(low, 0);
  to[stride * 1] = _mm_extract_epi64(low, 1);

  __m128i high = _mm256_extractf128_si256(from, 1);
  to[stride * 2] = _mm_extract_epi64(high, 0);
  to[stride * 3] = _mm_extract_epi64(high, 1);
}
template <>
EIGEN_STRONG_INLINE void pstore1<Packet4l>(int64_t* to, const int64_t& a) {
  Packet4l pa = pset1<Packet4l>(a);
  pstore(to, pa);
}
template <>
EIGEN_STRONG_INLINE int64_t pfirst<Packet4l>(const Packet4l& a) {
  return _mm_cvtsi128_si64(_mm256_castsi256_si128(a));
}
template <>
EIGEN_STRONG_INLINE int64_t predux<Packet4l>(const Packet4l& a) {
  __m128i r = _mm_add_epi64(_mm256_castsi256_si128(a), _mm256_extractf128_si256(a, 1));
  return _mm_extract_epi64(r, 0) + _mm_extract_epi64(r, 1);
}
#define MM256_SHUFFLE_EPI64(A, B, M) _mm256_shuffle_pd(_mm256_castsi256_pd(A), _mm256_castsi256_pd(B), M)
EIGEN_DEVICE_FUNC inline void ptranspose(PacketBlock<Packet4l, 4>& kernel) {
  __m256d T0 = MM256_SHUFFLE_EPI64(kernel.packet[0], kernel.packet[1], 15);
  __m256d T1 = MM256_SHUFFLE_EPI64(kernel.packet[0], kernel.packet[1], 0);
  __m256d T2 = MM256_SHUFFLE_EPI64(kernel.packet[2], kernel.packet[3], 15);
  __m256d T3 = MM256_SHUFFLE_EPI64(kernel.packet[2], kernel.packet[3], 0);

  kernel.packet[1] = _mm256_castpd_si256(_mm256_permute2f128_pd(T0, T2, 32));
  kernel.packet[3] = _mm256_castpd_si256(_mm256_permute2f128_pd(T0, T2, 49));
  kernel.packet[0] = _mm256_castpd_si256(_mm256_permute2f128_pd(T1, T3, 32));
  kernel.packet[2] = _mm256_castpd_si256(_mm256_permute2f128_pd(T1, T3, 49));
}
template <>
EIGEN_STRONG_INLINE Packet4l pmin<Packet4l>(const Packet4l& a, const Packet4l& b) {
  __m256i cmp = _mm256_cmpgt_epi64(a, b);
  __m256i a_min = _mm256_andnot_si256(cmp, a);
  __m256i b_min = _mm256_and_si256(cmp, b);
  return Packet4l(_mm256_or_si256(a_min, b_min));
}
template <>
EIGEN_STRONG_INLINE Packet4l pmax<Packet4l>(const Packet4l& a, const Packet4l& b) {
  __m256i cmp = _mm256_cmpgt_epi64(a, b);
  __m256i a_min = _mm256_and_si256(cmp, a);
  __m256i b_min = _mm256_andnot_si256(cmp, b);
  return Packet4l(_mm256_or_si256(a_min, b_min));
}
template <>
EIGEN_STRONG_INLINE Packet4l pabs<Packet4l>(const Packet4l& a) {
  Packet4l pz = pzero<Packet4l>(a);
  Packet4l cmp = _mm256_cmpgt_epi64(a, pz);
  return psub(cmp, pxor(a, cmp));
}
template <>
EIGEN_STRONG_INLINE Packet4l pmul<Packet4l>(const Packet4l& a, const Packet4l& b) {
  // 64-bit mul requires avx512, so do this with 32-bit multiplication
  __m256i upper32_a = _mm256_srli_epi64(a, 32);
  __m256i upper32_b = _mm256_srli_epi64(b, 32);

  // upper * lower
  __m256i mul1 = _mm256_mul_epu32(upper32_a, b);
  __m256i mul2 = _mm256_mul_epu32(upper32_b, a);
  // Gives us both upper*upper and lower*lower
  __m256i mul3 = _mm256_mul_epu32(a, b);

  __m256i high = _mm256_slli_epi64(_mm256_add_epi64(mul1, mul2), 32);
  return _mm256_add_epi64(high, mul3);
}
#endif

template<> EIGEN_STRONG_INLINE Packet4f pset1<Packet4f>(const float&  from) { return _mm_set_ps1(from); }
template<> EIGEN_STRONG_INLINE Packet2d pset1<Packet2d>(const double& from) { return _mm_set1_pd(from); }
template<> EIGEN_STRONG_INLINE Packet4i pset1<Packet4i>(const int&    from) { return _mm_set1_epi32(from); }
template<> EIGEN_STRONG_INLINE Packet16b pset1<Packet16b>(const bool&    from) { return _mm_set1_epi8(static_cast<char>(from)); }

template<> EIGEN_STRONG_INLINE Packet8f pset1<Packet8f>(const float&  from) { return _mm256_set1_ps(from); }
template<> EIGEN_STRONG_INLINE Packet4d pset1<Packet4d>(const double& from) { return _mm256_set1_pd(from); }
template<> EIGEN_STRONG_INLINE Packet8i pset1<Packet8i>(const int&    from) { return _mm256_set1_epi32(from); }

template<> EIGEN_STRONG_INLINE Packet4f pset1frombits<Packet4f>(unsigned int from) { return _mm_castsi128_ps(pset1<Packet4i>(from)); }
template<> EIGEN_STRONG_INLINE Packet2d pset1frombits<Packet2d>(uint64_t from) { return _mm_castsi128_pd(_mm_set1_epi64x(from)); }

template<> EIGEN_STRONG_INLINE Packet8f pset1frombits<Packet8f>(unsigned int from) { return _mm256_castsi256_ps(pset1<Packet8i>(from)); }
template<> EIGEN_STRONG_INLINE Packet4d pset1frombits<Packet4d>(uint64_t from) { return _mm256_castsi256_pd(_mm256_set1_epi64x(from)); }

template<> EIGEN_STRONG_INLINE Packet4f pzero(const Packet4f& /*a*/) { return _mm_setzero_ps(); }
template<> EIGEN_STRONG_INLINE Packet2d pzero(const Packet2d& /*a*/) { return _mm_setzero_pd(); }
template<> EIGEN_STRONG_INLINE Packet4i pzero(const Packet4i& /*a*/) { return _mm_setzero_si128(); }

template<> EIGEN_STRONG_INLINE Packet8f pzero(const Packet8f& /*a*/) { return _mm256_setzero_ps(); }
template<> EIGEN_STRONG_INLINE Packet4d pzero(const Packet4d& /*a*/) { return _mm256_setzero_pd(); }
template<> EIGEN_STRONG_INLINE Packet8i pzero(const Packet8i& /*a*/) { return _mm256_setzero_si256(); }

template<> EIGEN_STRONG_INLINE Packet4f peven_mask(const Packet4f& /*a*/) { return _mm_castsi128_ps(_mm_set_epi32(0, -1, 0, -1)); }
template<> EIGEN_STRONG_INLINE Packet4i peven_mask(const Packet4i& /*a*/) { return _mm_set_epi32(0, -1, 0, -1); }
template<> EIGEN_STRONG_INLINE Packet2d peven_mask(const Packet2d& /*a*/) { return _mm_castsi128_pd(_mm_set_epi32(0, 0, -1, -1)); }

template<> EIGEN_STRONG_INLINE Packet8f peven_mask(const Packet8f& /*a*/) { return _mm256_castsi256_ps(_mm256_set_epi32(0, -1, 0, -1, 0, -1, 0, -1)); }
template<> EIGEN_STRONG_INLINE Packet8i peven_mask(const Packet8i& /*a*/) { return _mm256_set_epi32(0, -1, 0, -1, 0, -1, 0, -1); }
template<> EIGEN_STRONG_INLINE Packet4d peven_mask(const Packet4d& /*a*/) { return _mm256_castsi256_pd(_mm256_set_epi32(0, 0, -1, -1, 0, 0, -1, -1)); }

// GCC generates a shufps instruction for _mm_set1_ps/_mm_load1_ps instead of the more efficient pshufd instruction.
// However, using inrinsics for pset1 makes gcc to generate crappy code in some cases (see bug 203)
// Using inline assembly is also not an option because then gcc fails to reorder properly the instructions.
// Therefore, we introduced the pload1 functions to be used in product kernels for which bug 203 does not apply.
// Also note that with AVX, we want it to generate a vbroadcastss.
#if EIGEN_COMP_GNUC_STRICT && (!defined __AVX__)
template<> EIGEN_STRONG_INLINE Packet4f pload1<Packet4f>(const float *from) {
  return vec4f_swizzle1(_mm_load_ss(from),0,0,0,0);
}
#endif

template<> EIGEN_STRONG_INLINE Packet8f pload1<Packet8f>(const float*  from) { return _mm256_broadcast_ss(from); }
template<> EIGEN_STRONG_INLINE Packet4d pload1<Packet4d>(const double* from) { return _mm256_broadcast_sd(from); }

template<> EIGEN_STRONG_INLINE Packet4f padd<Packet4f>(const Packet4f& a, const Packet4f& b) { return _mm_add_ps(a,b); }
template<> EIGEN_STRONG_INLINE Packet2d padd<Packet2d>(const Packet2d& a, const Packet2d& b) { return _mm_add_pd(a,b); }
template<> EIGEN_STRONG_INLINE Packet4i padd<Packet4i>(const Packet4i& a, const Packet4i& b) { return _mm_add_epi32(a,b); }

template<> EIGEN_STRONG_INLINE Packet16b padd<Packet16b>(const Packet16b& a, const Packet16b& b) { return _mm_or_si128(a,b); }

template<> EIGEN_STRONG_INLINE Packet8f padd<Packet8f>(const Packet8f& a, const Packet8f& b) { return _mm256_add_ps(a,b); }
#ifdef EIGEN_VECTORIZE_AVX512
template <>
EIGEN_STRONG_INLINE Packet8f padd<Packet8f>(const Packet8f& a, const Packet8f& b, uint8_t umask) {
  __mmask16 mask = static_cast<__mmask16>(umask & 0x00FF);
  return _mm512_castps512_ps256(_mm512_maskz_add_ps(
                                    mask,
                                    _mm512_castps256_ps512(a),
                                    _mm512_castps256_ps512(b)));
}
#endif
template<> EIGEN_STRONG_INLINE Packet4d padd<Packet4d>(const Packet4d& a, const Packet4d& b) { return _mm256_add_pd(a,b); }
template<> EIGEN_STRONG_INLINE Packet8i padd<Packet8i>(const Packet8i& a, const Packet8i& b) {
#ifdef EIGEN_VECTORIZE_AVX2
  return _mm256_add_epi32(a,b);
#else
  __m128i lo = _mm_add_epi32(_mm256_extractf128_si256(a, 0), _mm256_extractf128_si256(b, 0));
  __m128i hi = _mm_add_epi32(_mm256_extractf128_si256(a, 1), _mm256_extractf128_si256(b, 1));
  return _mm256_insertf128_si256(_mm256_castsi128_si256(lo), (hi), 1);
#endif
}

template<> EIGEN_STRONG_INLINE Packet4f plset<Packet4f>(const float& a) { return _mm_add_ps(pset1<Packet4f>(a), _mm_set_ps(3,2,1,0)); }
template<> EIGEN_STRONG_INLINE Packet2d plset<Packet2d>(const double& a) { return _mm_add_pd(pset1<Packet2d>(a),_mm_set_pd(1,0)); }
template<> EIGEN_STRONG_INLINE Packet4i plset<Packet4i>(const int& a) { return _mm_add_epi32(pset1<Packet4i>(a),_mm_set_epi32(3,2,1,0)); }

template<> EIGEN_STRONG_INLINE Packet8f plset<Packet8f>(const float& a) { return padd(pset1<Packet8f>(a), _mm256_set_ps(7.0,6.0,5.0,4.0,3.0,2.0,1.0,0.0)); }
template<> EIGEN_STRONG_INLINE Packet4d plset<Packet4d>(const double& a) { return padd(pset1<Packet4d>(a), _mm256_set_pd(3.0,2.0,1.0,0.0)); }
template<> EIGEN_STRONG_INLINE Packet8i plset<Packet8i>(const int& a) { return padd(pset1<Packet8i>(a), (Packet8i)_mm256_set_epi32(7,6,5,4,3,2,1,0)); }

template<> EIGEN_STRONG_INLINE Packet4f psub<Packet4f>(const Packet4f& a, const Packet4f& b) { return _mm_sub_ps(a,b); }
template<> EIGEN_STRONG_INLINE Packet2d psub<Packet2d>(const Packet2d& a, const Packet2d& b) { return _mm_sub_pd(a,b); }
template<> EIGEN_STRONG_INLINE Packet4i psub<Packet4i>(const Packet4i& a, const Packet4i& b) { return _mm_sub_epi32(a,b); }
template<> EIGEN_STRONG_INLINE Packet16b psub<Packet16b>(const Packet16b& a, const Packet16b& b) { return _mm_xor_si128(a,b); }

template<> EIGEN_STRONG_INLINE Packet8f psub<Packet8f>(const Packet8f& a, const Packet8f& b) { return _mm256_sub_ps(a,b); }
template<> EIGEN_STRONG_INLINE Packet4d psub<Packet4d>(const Packet4d& a, const Packet4d& b) { return _mm256_sub_pd(a,b); }
template<> EIGEN_STRONG_INLINE Packet8i psub<Packet8i>(const Packet8i& a, const Packet8i& b) {
#ifdef EIGEN_VECTORIZE_AVX2
  return _mm256_sub_epi32(a,b);
#else
  __m128i lo = _mm_sub_epi32(_mm256_extractf128_si256(a, 0), _mm256_extractf128_si256(b, 0));
  __m128i hi = _mm_sub_epi32(_mm256_extractf128_si256(a, 1), _mm256_extractf128_si256(b, 1));
  return _mm256_insertf128_si256(_mm256_castsi128_si256(lo), (hi), 1);
#endif
}
template<> EIGEN_STRONG_INLINE Packet4f pxor<Packet4f>(const Packet4f& a, const Packet4f& b);
template<> EIGEN_STRONG_INLINE Packet4f paddsub<Packet4f>(const Packet4f& a, const Packet4f& b)
{
#ifdef EIGEN_VECTORIZE_SSE3
  return _mm_addsub_ps(a,b);
#else
  const Packet4f mask = _mm_castsi128_ps(_mm_setr_epi32(0x80000000,0x0,0x80000000,0x0));
  return padd(a, pxor(mask, b));
#endif
}

template<> EIGEN_STRONG_INLINE Packet2d pxor<Packet2d>(const Packet2d& , const Packet2d& );
template<> EIGEN_STRONG_INLINE Packet2d paddsub<Packet2d>(const Packet2d& a, const Packet2d& b) 
{
#ifdef EIGEN_VECTORIZE_SSE3  
  return _mm_addsub_pd(a,b); 
#else
  const Packet2d mask = _mm_castsi128_pd(_mm_setr_epi32(0x0,0x80000000,0x0,0x0)); 
  return padd(a, pxor(mask, b));
#endif
}

template<> EIGEN_STRONG_INLINE Packet4f pnegate(const Packet4f& a)
{
  const Packet4f mask = _mm_castsi128_ps(_mm_setr_epi32(0x80000000,0x80000000,0x80000000,0x80000000));
  return _mm_xor_ps(a,mask);
}
template<> EIGEN_STRONG_INLINE Packet2d pnegate(const Packet2d& a)
{
  const Packet2d mask = _mm_castsi128_pd(_mm_setr_epi32(0x0,0x80000000,0x0,0x80000000));
  return _mm_xor_pd(a,mask);
}
template<> EIGEN_STRONG_INLINE Packet4i pnegate(const Packet4i& a)
{
  return psub(Packet4i(_mm_setr_epi32(0,0,0,0)), a);
}

template<> EIGEN_STRONG_INLINE Packet16b pnegate(const Packet16b& a)
{
  return psub(pset1<Packet16b>(false), a);
}

template<> EIGEN_STRONG_INLINE Packet4f pconj(const Packet4f& a) { return a; }
template<> EIGEN_STRONG_INLINE Packet2d pconj(const Packet2d& a) { return a; }
template<> EIGEN_STRONG_INLINE Packet4i pconj(const Packet4i& a) { return a; }

template<> EIGEN_STRONG_INLINE Packet4f pmul<Packet4f>(const Packet4f& a, const Packet4f& b) { return _mm_mul_ps(a,b); }
template<> EIGEN_STRONG_INLINE Packet2d pmul<Packet2d>(const Packet2d& a, const Packet2d& b) { return _mm_mul_pd(a,b); }
template<> EIGEN_STRONG_INLINE Packet4i pmul<Packet4i>(const Packet4i& a, const Packet4i& b)
{
#ifdef EIGEN_VECTORIZE_SSE4_1
  return _mm_mullo_epi32(a,b);
#else
  // this version is slightly faster than 4 scalar products
  return vec4i_swizzle1(
            vec4i_swizzle2(
              _mm_mul_epu32(a,b),
              _mm_mul_epu32(vec4i_swizzle1(a,1,0,3,2),
                            vec4i_swizzle1(b,1,0,3,2)),
              0,2,0,2),
            0,2,1,3);
#endif
}

template<> EIGEN_STRONG_INLINE Packet16b pmul<Packet16b>(const Packet16b& a, const Packet16b& b) { return _mm_and_si128(a,b); }

template<> EIGEN_STRONG_INLINE Packet4f pdiv<Packet4f>(const Packet4f& a, const Packet4f& b) { return _mm_div_ps(a,b); }
template<> EIGEN_STRONG_INLINE Packet2d pdiv<Packet2d>(const Packet2d& a, const Packet2d& b) { return _mm_div_pd(a,b); }

// for some weird raisons, it has to be overloaded for packet of integers
template<> EIGEN_STRONG_INLINE Packet4i pmadd(const Packet4i& a, const Packet4i& b, const Packet4i& c) { return padd(pmul(a,b), c); }
#ifdef EIGEN_VECTORIZE_FMA
template<> EIGEN_STRONG_INLINE Packet4f pmadd(const Packet4f& a, const Packet4f& b, const Packet4f& c) { return _mm_fmadd_ps(a,b,c); }
template<> EIGEN_STRONG_INLINE Packet2d pmadd(const Packet2d& a, const Packet2d& b, const Packet2d& c) { return _mm_fmadd_pd(a,b,c); }
template<> EIGEN_STRONG_INLINE Packet4f pmsub(const Packet4f& a, const Packet4f& b, const Packet4f& c) { return _mm_fmsub_ps(a,b,c); }
template<> EIGEN_STRONG_INLINE Packet2d pmsub(const Packet2d& a, const Packet2d& b, const Packet2d& c) { return _mm_fmsub_pd(a,b,c); }
template<> EIGEN_STRONG_INLINE Packet4f pnmadd(const Packet4f& a, const Packet4f& b, const Packet4f& c) { return _mm_fnmadd_ps(a,b,c); }
template<> EIGEN_STRONG_INLINE Packet2d pnmadd(const Packet2d& a, const Packet2d& b, const Packet2d& c) { return _mm_fnmadd_pd(a,b,c); }
template<> EIGEN_STRONG_INLINE Packet4f pnmsub(const Packet4f& a, const Packet4f& b, const Packet4f& c) { return _mm_fnmsub_ps(a,b,c); }
template<> EIGEN_STRONG_INLINE Packet2d pnmsub(const Packet2d& a, const Packet2d& b, const Packet2d& c) { return _mm_fnmsub_pd(a,b,c); }
#endif

#ifdef EIGEN_VECTORIZE_SSE4_1
template<> EIGEN_DEVICE_FUNC inline Packet4f pselect(const Packet4f& mask, const Packet4f& a, const Packet4f& b) {
  return _mm_blendv_ps(b,a,mask);
}

template<> EIGEN_DEVICE_FUNC inline Packet4i pselect(const Packet4i& mask, const Packet4i& a, const Packet4i& b) {
  return _mm_castps_si128(_mm_blendv_ps(_mm_castsi128_ps(b),_mm_castsi128_ps(a),_mm_castsi128_ps(mask)));
}

template<> EIGEN_DEVICE_FUNC inline Packet2d pselect(const Packet2d& mask, const Packet2d& a, const Packet2d& b) {  return _mm_blendv_pd(b,a,mask); }

template<> EIGEN_DEVICE_FUNC inline Packet16b pselect(const Packet16b& mask, const Packet16b& a, const Packet16b& b) {
  return _mm_blendv_epi8(b,a,mask);
}
#else
template<> EIGEN_DEVICE_FUNC inline Packet16b pselect(const Packet16b& mask, const Packet16b& a, const Packet16b& b) {
  Packet16b a_part = _mm_and_si128(mask, a);
  Packet16b b_part = _mm_andnot_si128(mask, b);
  return _mm_or_si128(a_part, b_part);
}
#endif

template<> EIGEN_STRONG_INLINE Packet4i ptrue<Packet4i>(const Packet4i& a) { return _mm_cmpeq_epi32(a, a); }
template<> EIGEN_STRONG_INLINE Packet16b ptrue<Packet16b>(const Packet16b& a) { return _mm_cmpeq_epi8(a, a); }
template<> EIGEN_STRONG_INLINE Packet4f
ptrue<Packet4f>(const Packet4f& a) {
  Packet4i b = _mm_castps_si128(a);
  return _mm_castsi128_ps(_mm_cmpeq_epi32(b, b));
}
template<> EIGEN_STRONG_INLINE Packet2d
ptrue<Packet2d>(const Packet2d& a) {
  Packet4i b = _mm_castpd_si128(a);
  return _mm_castsi128_pd(_mm_cmpeq_epi32(b, b));
}


template<> EIGEN_STRONG_INLINE Packet4f pand<Packet4f>(const Packet4f& a, const Packet4f& b) { return _mm_and_ps(a,b); }
template<> EIGEN_STRONG_INLINE Packet2d pand<Packet2d>(const Packet2d& a, const Packet2d& b) { return _mm_and_pd(a,b); }
template<> EIGEN_STRONG_INLINE Packet4i pand<Packet4i>(const Packet4i& a, const Packet4i& b) { return _mm_and_si128(a,b); }
template<> EIGEN_STRONG_INLINE Packet16b pand<Packet16b>(const Packet16b& a, const Packet16b& b) { return _mm_and_si128(a,b); }

template<> EIGEN_STRONG_INLINE Packet4f por<Packet4f>(const Packet4f& a, const Packet4f& b) { return _mm_or_ps(a,b); }
template<> EIGEN_STRONG_INLINE Packet2d por<Packet2d>(const Packet2d& a, const Packet2d& b) { return _mm_or_pd(a,b); }
template<> EIGEN_STRONG_INLINE Packet4i por<Packet4i>(const Packet4i& a, const Packet4i& b) { return _mm_or_si128(a,b); }
template<> EIGEN_STRONG_INLINE Packet16b por<Packet16b>(const Packet16b& a, const Packet16b& b) { return _mm_or_si128(a,b); }

template<> EIGEN_STRONG_INLINE Packet4f pxor<Packet4f>(const Packet4f& a, const Packet4f& b) { return _mm_xor_ps(a,b); }
template<> EIGEN_STRONG_INLINE Packet2d pxor<Packet2d>(const Packet2d& a, const Packet2d& b) { return _mm_xor_pd(a,b); }
template<> EIGEN_STRONG_INLINE Packet4i pxor<Packet4i>(const Packet4i& a, const Packet4i& b) { return _mm_xor_si128(a,b); }
template<> EIGEN_STRONG_INLINE Packet16b pxor<Packet16b>(const Packet16b& a, const Packet16b& b) { return _mm_xor_si128(a,b); }

template<> EIGEN_STRONG_INLINE Packet4f pandnot<Packet4f>(const Packet4f& a, const Packet4f& b) { return _mm_andnot_ps(b,a); }
template<> EIGEN_STRONG_INLINE Packet2d pandnot<Packet2d>(const Packet2d& a, const Packet2d& b) { return _mm_andnot_pd(b,a); }
template<> EIGEN_STRONG_INLINE Packet4i pandnot<Packet4i>(const Packet4i& a, const Packet4i& b) { return _mm_andnot_si128(b,a); }

template<> EIGEN_STRONG_INLINE Packet4f pcmp_le(const Packet4f& a, const Packet4f& b) { return _mm_cmple_ps(a,b); }
template<> EIGEN_STRONG_INLINE Packet4f pcmp_lt(const Packet4f& a, const Packet4f& b) { return _mm_cmplt_ps(a,b); }
template<> EIGEN_STRONG_INLINE Packet4f pcmp_lt_or_nan(const Packet4f& a, const Packet4f& b) { return _mm_cmpnge_ps(a,b); }
template<> EIGEN_STRONG_INLINE Packet4f pcmp_eq(const Packet4f& a, const Packet4f& b) { return _mm_cmpeq_ps(a,b); }

template<> EIGEN_STRONG_INLINE Packet2d pcmp_le(const Packet2d& a, const Packet2d& b) { return _mm_cmple_pd(a,b); }
template<> EIGEN_STRONG_INLINE Packet2d pcmp_lt(const Packet2d& a, const Packet2d& b) { return _mm_cmplt_pd(a,b); }
template<> EIGEN_STRONG_INLINE Packet2d pcmp_lt_or_nan(const Packet2d& a, const Packet2d& b) { return _mm_cmpnge_pd(a,b); }
template<> EIGEN_STRONG_INLINE Packet2d pcmp_eq(const Packet2d& a, const Packet2d& b) { return _mm_cmpeq_pd(a,b); }

template<> EIGEN_STRONG_INLINE Packet4i pcmp_lt(const Packet4i& a, const Packet4i& b) { return _mm_cmplt_epi32(a,b); }
template<> EIGEN_STRONG_INLINE Packet4i pcmp_eq(const Packet4i& a, const Packet4i& b) { return _mm_cmpeq_epi32(a,b); }
template<> EIGEN_STRONG_INLINE Packet16b pcmp_eq(const Packet16b& a, const Packet16b& b) { return _mm_cmpeq_epi8(a,b); }
template<> EIGEN_STRONG_INLINE Packet4i pcmp_le(const Packet4i& a, const Packet4i& b) { return por(pcmp_lt(a,b), pcmp_eq(a,b)); }

template<> EIGEN_STRONG_INLINE Packet4f pmin<Packet4f>(const Packet4f& a, const Packet4f& b) {
#if EIGEN_COMP_GNUC_STRICT && EIGEN_COMP_GNUC < 63
  // There appears to be a bug in GCC, by which the optimizer may
  // flip the argument order in calls to _mm_min_ps, so we have to
  // resort to inline ASM here. This is supposed to be fixed in gcc6.3,
  // see also: https://gcc.gnu.org/bugzilla/show_bug.cgi?id=72867
  #ifdef EIGEN_VECTORIZE_AVX
  Packet4f res;
  asm("vminps %[a], %[b], %[res]" : [res] "=x" (res) : [a] "x" (a), [b] "x" (b));
  #else
  Packet4f res = b;
  asm("minps %[a], %[res]" : [res] "+x" (res) : [a] "x" (a));
  #endif
  return res;
#else
  // Arguments are reversed to match NaN propagation behavior of std::min.
  return _mm_min_ps(b, a);
#endif
}
template<> EIGEN_STRONG_INLINE Packet2d pmin<Packet2d>(const Packet2d& a, const Packet2d& b) {
#if EIGEN_COMP_GNUC_STRICT && EIGEN_COMP_GNUC < 63
  // There appears to be a bug in GCC, by which the optimizer may
  // flip the argument order in calls to _mm_min_pd, so we have to
  // resort to inline ASM here. This is supposed to be fixed in gcc6.3,
  // see also: https://gcc.gnu.org/bugzilla/show_bug.cgi?id=72867
  #ifdef EIGEN_VECTORIZE_AVX
  Packet2d res;
  asm("vminpd %[a], %[b], %[res]" : [res] "=x" (res) : [a] "x" (a), [b] "x" (b));
  #else
  Packet2d res = b;
  asm("minpd %[a], %[res]" : [res] "+x" (res) : [a] "x" (a));
  #endif
  return res;
#else
  // Arguments are reversed to match NaN propagation behavior of std::min.
  return _mm_min_pd(b, a);
#endif
}
template<> EIGEN_STRONG_INLINE Packet4i pmin<Packet4i>(const Packet4i& a, const Packet4i& b)
{
#ifdef EIGEN_VECTORIZE_SSE4_1
  return _mm_min_epi32(a,b);
#else
  // after some bench, this version *is* faster than a scalar implementation
  Packet4i mask = _mm_cmplt_epi32(a,b);
  return _mm_or_si128(_mm_and_si128(mask,a),_mm_andnot_si128(mask,b));
#endif
}


template<> EIGEN_STRONG_INLINE Packet4f pmax<Packet4f>(const Packet4f& a, const Packet4f& b) {
#if EIGEN_COMP_GNUC_STRICT && EIGEN_COMP_GNUC < 63
  // There appears to be a bug in GCC, by which the optimizer may
  // flip the argument order in calls to _mm_max_ps, so we have to
  // resort to inline ASM here. This is supposed to be fixed in gcc6.3,
  // see also: https://gcc.gnu.org/bugzilla/show_bug.cgi?id=72867
  #ifdef EIGEN_VECTORIZE_AVX
  Packet4f res;
  asm("vmaxps %[a], %[b], %[res]" : [res] "=x" (res) : [a] "x" (a), [b] "x" (b));
  #else
  Packet4f res = b;
  asm("maxps %[a], %[res]" : [res] "+x" (res) : [a] "x" (a));
  #endif
  return res;
#else
  // Arguments are reversed to match NaN propagation behavior of std::max.
  return _mm_max_ps(b, a);
#endif
}
template<> EIGEN_STRONG_INLINE Packet2d pmax<Packet2d>(const Packet2d& a, const Packet2d& b) {
#if EIGEN_COMP_GNUC_STRICT && EIGEN_COMP_GNUC < 63
  // There appears to be a bug in GCC, by which the optimizer may
  // flip the argument order in calls to _mm_max_pd, so we have to
  // resort to inline ASM here. This is supposed to be fixed in gcc6.3,
  // see also: https://gcc.gnu.org/bugzilla/show_bug.cgi?id=72867
  #ifdef EIGEN_VECTORIZE_AVX
  Packet2d res;
  asm("vmaxpd %[a], %[b], %[res]" : [res] "=x" (res) : [a] "x" (a), [b] "x" (b));
  #else
  Packet2d res = b;
  asm("maxpd %[a], %[res]" : [res] "+x" (res) : [a] "x" (a));
  #endif
  return res;
#else
  // Arguments are reversed to match NaN propagation behavior of std::max.
  return _mm_max_pd(b, a);
#endif
}
template<> EIGEN_STRONG_INLINE Packet4i pmax<Packet4i>(const Packet4i& a, const Packet4i& b)
{
#ifdef EIGEN_VECTORIZE_SSE4_1
  return _mm_max_epi32(a,b);
#else
  // after some bench, this version *is* faster than a scalar implementation
  Packet4i mask = _mm_cmpgt_epi32(a,b);
  return _mm_or_si128(_mm_and_si128(mask,a),_mm_andnot_si128(mask,b));
#endif
}

template <typename Packet, typename Op>
EIGEN_STRONG_INLINE Packet pminmax_propagate_numbers(const Packet& a, const Packet& b, Op op) {
  // In this implementation, we take advantage of the fact that pmin/pmax for SSE
  // always return a if either a or b is NaN.
  Packet not_nan_mask_a = pcmp_eq(a, a);
  Packet m = op(a, b);
  return pselect<Packet>(not_nan_mask_a, m, b);
}

template <typename Packet, typename Op>
EIGEN_STRONG_INLINE Packet pminmax_propagate_nan(const Packet& a, const Packet& b, Op op) {
  // In this implementation, we take advantage of the fact that pmin/pmax for SSE
  // always return a if either a or b is NaN.
  Packet not_nan_mask_a = pcmp_eq(a, a);
  Packet m = op(b, a);
  return pselect<Packet>(not_nan_mask_a, m, a);
}

// Add specializations for min/max with prescribed NaN progation.
template<>
EIGEN_STRONG_INLINE Packet4f pmin<PropagateNumbers, Packet4f>(const Packet4f& a, const Packet4f& b) {
  return pminmax_propagate_numbers(a, b, pmin<Packet4f>);
}
template<>
EIGEN_STRONG_INLINE Packet2d pmin<PropagateNumbers, Packet2d>(const Packet2d& a, const Packet2d& b) {
  return pminmax_propagate_numbers(a, b, pmin<Packet2d>);
}
template<>
EIGEN_STRONG_INLINE Packet4f pmax<PropagateNumbers, Packet4f>(const Packet4f& a, const Packet4f& b) {
  return pminmax_propagate_numbers(a, b, pmax<Packet4f>);
}
template<>
EIGEN_STRONG_INLINE Packet2d pmax<PropagateNumbers, Packet2d>(const Packet2d& a, const Packet2d& b) {
  return pminmax_propagate_numbers(a, b, pmax<Packet2d>);
}
template<>
EIGEN_STRONG_INLINE Packet4f pmin<PropagateNaN, Packet4f>(const Packet4f& a, const Packet4f& b) {
  return pminmax_propagate_nan(a, b, pmin<Packet4f>);
}
template<>
EIGEN_STRONG_INLINE Packet2d pmin<PropagateNaN, Packet2d>(const Packet2d& a, const Packet2d& b) {
  return pminmax_propagate_nan(a, b, pmin<Packet2d>);
}
template<>
EIGEN_STRONG_INLINE Packet4f pmax<PropagateNaN, Packet4f>(const Packet4f& a, const Packet4f& b) {
  return pminmax_propagate_nan(a, b, pmax<Packet4f>);
}
template<>
EIGEN_STRONG_INLINE Packet2d pmax<PropagateNaN, Packet2d>(const Packet2d& a, const Packet2d& b) {
  return pminmax_propagate_nan(a, b, pmax<Packet2d>);
}

template<int N> EIGEN_STRONG_INLINE Packet4i parithmetic_shift_right(const Packet4i& a) { return _mm_srai_epi32(a,N); }
template<int N> EIGEN_STRONG_INLINE Packet4i plogical_shift_right   (const Packet4i& a) { return _mm_srli_epi32(a,N); }
template<int N> EIGEN_STRONG_INLINE Packet4i plogical_shift_left    (const Packet4i& a) { return _mm_slli_epi32(a,N); }

template<> EIGEN_STRONG_INLINE Packet4f pabs(const Packet4f& a)
{
  const Packet4f mask = _mm_castsi128_ps(_mm_setr_epi32(0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF));
  return _mm_and_ps(a,mask);
}
template<> EIGEN_STRONG_INLINE Packet2d pabs(const Packet2d& a)
{
  const Packet2d mask = _mm_castsi128_pd(_mm_setr_epi32(0xFFFFFFFF,0x7FFFFFFF,0xFFFFFFFF,0x7FFFFFFF));
  return _mm_and_pd(a,mask);
}
template<> EIGEN_STRONG_INLINE Packet4i pabs(const Packet4i& a)
{
  #ifdef EIGEN_VECTORIZE_SSSE3
  return _mm_abs_epi32(a);
  #else
  Packet4i aux = _mm_srai_epi32(a,31);
  return _mm_sub_epi32(_mm_xor_si128(a,aux),aux);
  #endif
}

#ifdef EIGEN_VECTORIZE_SSE4_1
template<> EIGEN_STRONG_INLINE Packet4f pround<Packet4f>(const Packet4f& a)
{
  // Unfortunately _mm_round_ps doesn't have a rounding mode to implement numext::round.
  const Packet4f mask = pset1frombits<Packet4f>(0x80000000u);
  const Packet4f prev0dot5 = pset1frombits<Packet4f>(0x3EFFFFFFu);
  return _mm_round_ps(padd(por(pand(a, mask), prev0dot5), a), _MM_FROUND_TO_ZERO);
}

template<> EIGEN_STRONG_INLINE Packet2d pround<Packet2d>(const Packet2d& a)
{
  const Packet2d mask = _mm_castsi128_pd(_mm_set_epi64x(0x8000000000000000ull, 0x8000000000000000ull));
  const Packet2d prev0dot5 = _mm_castsi128_pd(_mm_set_epi64x(0x3FDFFFFFFFFFFFFFull, 0x3FDFFFFFFFFFFFFFull));
  return _mm_round_pd(padd(por(pand(a, mask), prev0dot5), a), _MM_FROUND_TO_ZERO);
}

template<> EIGEN_STRONG_INLINE Packet4f print<Packet4f>(const Packet4f& a) { return _mm_round_ps(a, _MM_FROUND_CUR_DIRECTION); }
template<> EIGEN_STRONG_INLINE Packet2d print<Packet2d>(const Packet2d& a) { return _mm_round_pd(a, _MM_FROUND_CUR_DIRECTION); }

template<> EIGEN_STRONG_INLINE Packet4f pceil<Packet4f>(const Packet4f& a) { return _mm_ceil_ps(a); }
template<> EIGEN_STRONG_INLINE Packet2d pceil<Packet2d>(const Packet2d& a) { return _mm_ceil_pd(a); }

template<> EIGEN_STRONG_INLINE Packet4f pfloor<Packet4f>(const Packet4f& a) { return _mm_floor_ps(a); }
template<> EIGEN_STRONG_INLINE Packet2d pfloor<Packet2d>(const Packet2d& a) { return _mm_floor_pd(a); }
#else
template<> EIGEN_STRONG_INLINE Packet4f print(const Packet4f& a) {
  // Adds and subtracts signum(a) * 2^23 to force rounding.
  const Packet4f limit = pset1<Packet4f>(static_cast<float>(1<<23));
  const Packet4f abs_a = pabs(a);
  Packet4f r = padd(abs_a, limit);
  // Don't compile-away addition and subtraction.
  EIGEN_OPTIMIZATION_BARRIER(r);
  r = psub(r, limit);
  // If greater than limit, simply return a.  Otherwise, account for sign.
  r = pselect(pcmp_lt(abs_a, limit),
              pselect(pcmp_lt(a, pzero(a)), pnegate(r), r), a);
  return r;
}

template<> EIGEN_STRONG_INLINE Packet2d print(const Packet2d& a) {
  // Adds and subtracts signum(a) * 2^52 to force rounding.
  const Packet2d limit = pset1<Packet2d>(static_cast<double>(1ull<<52));
  const Packet2d abs_a = pabs(a);
  Packet2d r = padd(abs_a, limit);
  // Don't compile-away addition and subtraction.
  EIGEN_OPTIMIZATION_BARRIER(r);
  r = psub(r, limit);
  // If greater than limit, simply return a.  Otherwise, account for sign.
  r = pselect(pcmp_lt(abs_a, limit),
              pselect(pcmp_lt(a, pzero(a)), pnegate(r), r), a);
  return r;
}

template<> EIGEN_STRONG_INLINE Packet4f pfloor<Packet4f>(const Packet4f& a)
{
  const Packet4f cst_1 = pset1<Packet4f>(1.0f);
  Packet4f tmp  = print<Packet4f>(a);
  // If greater, subtract one.
  Packet4f mask = _mm_cmpgt_ps(tmp, a);
  mask = pand(mask, cst_1);
  return psub(tmp, mask);
}

template<> EIGEN_STRONG_INLINE Packet2d pfloor<Packet2d>(const Packet2d& a)
{
  const Packet2d cst_1 = pset1<Packet2d>(1.0);
  Packet2d tmp  = print<Packet2d>(a);
  // If greater, subtract one.
  Packet2d mask = _mm_cmpgt_pd(tmp, a);
  mask = pand(mask, cst_1);
  return psub(tmp, mask);
}

template<> EIGEN_STRONG_INLINE Packet4f pceil<Packet4f>(const Packet4f& a)
{
  const Packet4f cst_1 = pset1<Packet4f>(1.0f);
  Packet4f tmp  = print<Packet4f>(a);
  // If smaller, add one.
  Packet4f mask = _mm_cmplt_ps(tmp, a);
  mask = pand(mask, cst_1);
  return padd(tmp, mask);
}

template<> EIGEN_STRONG_INLINE Packet2d pceil<Packet2d>(const Packet2d& a)
{
  const Packet2d cst_1 = pset1<Packet2d>(1.0);
  Packet2d tmp  = print<Packet2d>(a);
  // If smaller, add one.
  Packet2d mask = _mm_cmplt_pd(tmp, a);
  mask = pand(mask, cst_1);
  return padd(tmp, mask);
}
#endif

template<> EIGEN_STRONG_INLINE Packet4f pload<Packet4f>(const float*   from) { EIGEN_DEBUG_ALIGNED_LOAD return _mm_load_ps(from); }
template<> EIGEN_STRONG_INLINE Packet2d pload<Packet2d>(const double*  from) { EIGEN_DEBUG_ALIGNED_LOAD return _mm_load_pd(from); }
template<> EIGEN_STRONG_INLINE Packet4i pload<Packet4i>(const int*     from) { EIGEN_DEBUG_ALIGNED_LOAD return _mm_load_si128(reinterpret_cast<const __m128i*>(from)); }
template<> EIGEN_STRONG_INLINE Packet16b pload<Packet16b>(const bool*     from) { EIGEN_DEBUG_ALIGNED_LOAD return  _mm_load_si128(reinterpret_cast<const __m128i*>(from)); }

#if EIGEN_COMP_MSVC
  template<> EIGEN_STRONG_INLINE Packet4f ploadu<Packet4f>(const float*  from) {
    EIGEN_DEBUG_UNALIGNED_LOAD
    return _mm_loadu_ps(from);
  }
#else
// NOTE: with the code below, MSVC's compiler crashes!

template<> EIGEN_STRONG_INLINE Packet4f ploadu<Packet4f>(const float* from)
{
  EIGEN_DEBUG_UNALIGNED_LOAD
  return _mm_loadu_ps(from);
}
#endif

template<> EIGEN_STRONG_INLINE Packet2d ploadu<Packet2d>(const double* from)
{
  EIGEN_DEBUG_UNALIGNED_LOAD
  return _mm_loadu_pd(from);
}
template<> EIGEN_STRONG_INLINE Packet4i ploadu<Packet4i>(const int* from)
{
  EIGEN_DEBUG_UNALIGNED_LOAD
  return _mm_loadu_si128(reinterpret_cast<const __m128i*>(from));
}
template<> EIGEN_STRONG_INLINE Packet16b ploadu<Packet16b>(const bool*     from) {
  EIGEN_DEBUG_UNALIGNED_LOAD
  return _mm_loadu_si128(reinterpret_cast<const __m128i*>(from));
}


template<> EIGEN_STRONG_INLINE Packet4f ploaddup<Packet4f>(const float*   from)
{
  return vec4f_swizzle1(_mm_castpd_ps(_mm_load_sd(reinterpret_cast<const double*>(from))), 0, 0, 1, 1);
}
template<> EIGEN_STRONG_INLINE Packet2d ploaddup<Packet2d>(const double*  from)
{ return pset1<Packet2d>(from[0]); }
template<> EIGEN_STRONG_INLINE Packet4i ploaddup<Packet4i>(const int*     from)
{
  Packet4i tmp;
  tmp = _mm_loadl_epi64(reinterpret_cast<const __m128i*>(from));
  return vec4i_swizzle1(tmp, 0, 0, 1, 1);
}

// Loads 8 bools from memory and returns the packet
// {b0, b0, b1, b1, b2, b2, b3, b3, b4, b4, b5, b5, b6, b6, b7, b7}
template<> EIGEN_STRONG_INLINE Packet16b ploaddup<Packet16b>(const bool*     from)
{
  __m128i tmp = _mm_castpd_si128(pload1<Packet2d>(reinterpret_cast<const double*>(from)));
  return  _mm_unpacklo_epi8(tmp, tmp);
}

// Loads 4 bools from memory and returns the packet
// {b0, b0  b0, b0, b1, b1, b1, b1, b2, b2, b2, b2, b3, b3, b3, b3}
template<> EIGEN_STRONG_INLINE Packet16b
ploadquad<Packet16b>(const bool* from) {
  __m128i tmp = _mm_castps_si128(pload1<Packet4f>(reinterpret_cast<const float*>(from)));
  tmp = _mm_unpacklo_epi8(tmp, tmp);
  return  _mm_unpacklo_epi16(tmp, tmp);
}

template<> EIGEN_STRONG_INLINE void pstore<float>(float*   to, const Packet4f& from) { EIGEN_DEBUG_ALIGNED_STORE _mm_store_ps(to, from); }
template<> EIGEN_STRONG_INLINE void pstore<double>(double* to, const Packet2d& from) { EIGEN_DEBUG_ALIGNED_STORE _mm_store_pd(to, from); }
template<> EIGEN_STRONG_INLINE void pstore<int>(int*       to, const Packet4i& from) { EIGEN_DEBUG_ALIGNED_STORE _mm_store_si128(reinterpret_cast<__m128i*>(to), from); }
template<> EIGEN_STRONG_INLINE void pstore<bool>(bool*     to, const Packet16b& from) { EIGEN_DEBUG_ALIGNED_STORE _mm_store_si128(reinterpret_cast<__m128i*>(to), from); }

template<> EIGEN_STRONG_INLINE void pstoreu<double>(double* to, const Packet2d& from) { EIGEN_DEBUG_UNALIGNED_STORE _mm_storeu_pd(to, from); }
template<> EIGEN_STRONG_INLINE void pstoreu<float>(float*   to, const Packet4f& from) { EIGEN_DEBUG_UNALIGNED_STORE _mm_storeu_ps(to, from); }
template<> EIGEN_STRONG_INLINE void pstoreu<int>(int*       to, const Packet4i& from) { EIGEN_DEBUG_UNALIGNED_STORE _mm_storeu_si128(reinterpret_cast<__m128i*>(to), from); }
template<> EIGEN_STRONG_INLINE void pstoreu<bool>(bool*     to, const Packet16b& from) { EIGEN_DEBUG_ALIGNED_STORE _mm_storeu_si128(reinterpret_cast<__m128i*>(to), from); }

template<> EIGEN_DEVICE_FUNC inline Packet4f pgather<float, Packet4f>(const float* from, Index stride)
{
 return _mm_set_ps(from[3*stride], from[2*stride], from[1*stride], from[0*stride]);
}
template<> EIGEN_DEVICE_FUNC inline Packet2d pgather<double, Packet2d>(const double* from, Index stride)
{
 return _mm_set_pd(from[1*stride], from[0*stride]);
}
template<> EIGEN_DEVICE_FUNC inline Packet4i pgather<int, Packet4i>(const int* from, Index stride)
{
 return _mm_set_epi32(from[3*stride], from[2*stride], from[1*stride], from[0*stride]);
}

template<> EIGEN_DEVICE_FUNC inline Packet16b pgather<bool, Packet16b>(const bool* from, Index stride)
{
  return _mm_set_epi8(from[15*stride], from[14*stride], from[13*stride], from[12*stride],
                      from[11*stride], from[10*stride], from[9*stride], from[8*stride],
                      from[7*stride], from[6*stride], from[5*stride], from[4*stride],
                      from[3*stride], from[2*stride], from[1*stride], from[0*stride]);
}

template<> EIGEN_DEVICE_FUNC inline void pscatter<float, Packet4f>(float* to, const Packet4f& from, Index stride)
{
  to[stride*0] = _mm_cvtss_f32(from);
  to[stride*1] = _mm_cvtss_f32(_mm_shuffle_ps(from, from, 1));
  to[stride*2] = _mm_cvtss_f32(_mm_shuffle_ps(from, from, 2));
  to[stride*3] = _mm_cvtss_f32(_mm_shuffle_ps(from, from, 3));
}
template<> EIGEN_DEVICE_FUNC inline void pscatter<double, Packet2d>(double* to, const Packet2d& from, Index stride)
{
  to[stride*0] = _mm_cvtsd_f64(from);
  to[stride*1] = _mm_cvtsd_f64(_mm_shuffle_pd(from, from, 1));
}
template<> EIGEN_DEVICE_FUNC inline void pscatter<int, Packet4i>(int* to, const Packet4i& from, Index stride)
{
  to[stride*0] = _mm_cvtsi128_si32(from);
  to[stride*1] = _mm_cvtsi128_si32(_mm_shuffle_epi32(from, 1));
  to[stride*2] = _mm_cvtsi128_si32(_mm_shuffle_epi32(from, 2));
  to[stride*3] = _mm_cvtsi128_si32(_mm_shuffle_epi32(from, 3));
}
template<> EIGEN_DEVICE_FUNC inline void pscatter<bool, Packet16b>(bool* to, const Packet16b& from, Index stride)
{
  to[4*stride*0] = _mm_cvtsi128_si32(from);
  to[4*stride*1] = _mm_cvtsi128_si32(_mm_shuffle_epi32(from, 1));
  to[4*stride*2] = _mm_cvtsi128_si32(_mm_shuffle_epi32(from, 2));
  to[4*stride*3] = _mm_cvtsi128_si32(_mm_shuffle_epi32(from, 3));
}


// some compilers might be tempted to perform multiple moves instead of using a vector path.
template<> EIGEN_STRONG_INLINE void pstore1<Packet4f>(float* to, const float& a)
{
  Packet4f pa = _mm_set_ss(a);
  pstore(to, Packet4f(vec4f_swizzle1(pa,0,0,0,0)));
}
// some compilers might be tempted to perform multiple moves instead of using a vector path.
template<> EIGEN_STRONG_INLINE void pstore1<Packet2d>(double* to, const double& a)
{
  Packet2d pa = _mm_set_sd(a);
  pstore(to, Packet2d(vec2d_swizzle1(pa,0,0)));
}

#if EIGEN_COMP_PGI && EIGEN_COMP_PGI < 1900
typedef const void * SsePrefetchPtrType;
#else
typedef const char * SsePrefetchPtrType;
#endif

#ifndef EIGEN_VECTORIZE_AVX
template<> EIGEN_STRONG_INLINE void prefetch<float>(const float*   addr) { _mm_prefetch((SsePrefetchPtrType)(addr), _MM_HINT_T0); }
template<> EIGEN_STRONG_INLINE void prefetch<double>(const double* addr) { _mm_prefetch((SsePrefetchPtrType)(addr), _MM_HINT_T0); }
template<> EIGEN_STRONG_INLINE void prefetch<int>(const int*       addr) { _mm_prefetch((SsePrefetchPtrType)(addr), _MM_HINT_T0); }
#endif

// #ifndef EIGEN_VECTORIZE_AVX512
// template<> EIGEN_STRONG_INLINE void prefetch<float>(const float*   addr) { _mm_prefetch((SsePrefetchPtrType)(addr), _MM_HINT_T0); }
// template<> EIGEN_STRONG_INLINE void prefetch<double>(const double* addr) { _mm_prefetch((SsePrefetchPtrType)(addr), _MM_HINT_T0); }
// template<> EIGEN_STRONG_INLINE void prefetch<int>(const int*       addr) { _mm_prefetch((SsePrefetchPtrType)(addr), _MM_HINT_T0); }
// #endif

#if EIGEN_COMP_MSVC_STRICT && EIGEN_OS_WIN64
// The temporary variable fixes an internal compilation error in vs <= 2008 and a wrong-result bug in vs 2010
// Direct of the struct members fixed bug #62.
template<> EIGEN_STRONG_INLINE float  pfirst<Packet4f>(const Packet4f& a) { return a.m128_f32[0]; }
template<> EIGEN_STRONG_INLINE double pfirst<Packet2d>(const Packet2d& a) { return a.m128d_f64[0]; }
template<> EIGEN_STRONG_INLINE int    pfirst<Packet4i>(const Packet4i& a) { int x = _mm_cvtsi128_si32(a); return x; }
#elif EIGEN_COMP_MSVC_STRICT
// The temporary variable fixes an internal compilation error in vs <= 2008 and a wrong-result bug in vs 2010
template<> EIGEN_STRONG_INLINE float  pfirst<Packet4f>(const Packet4f& a) { float x = _mm_cvtss_f32(a); return x; }
template<> EIGEN_STRONG_INLINE double pfirst<Packet2d>(const Packet2d& a) { double x = _mm_cvtsd_f64(a); return x; }
template<> EIGEN_STRONG_INLINE int    pfirst<Packet4i>(const Packet4i& a) { int x = _mm_cvtsi128_si32(a); return x; }
#else
template<> EIGEN_STRONG_INLINE float  pfirst<Packet4f>(const Packet4f& a) { return _mm_cvtss_f32(a); }
template<> EIGEN_STRONG_INLINE double pfirst<Packet2d>(const Packet2d& a) { return _mm_cvtsd_f64(a); }
template<> EIGEN_STRONG_INLINE int    pfirst<Packet4i>(const Packet4i& a) { return _mm_cvtsi128_si32(a); }
#endif
template<> EIGEN_STRONG_INLINE bool   pfirst<Packet16b>(const Packet16b& a) { int x = _mm_cvtsi128_si32(a); return static_cast<bool>(x & 1); }

template<> EIGEN_STRONG_INLINE Packet4f preverse(const Packet4f& a) { return _mm_shuffle_ps(a,a,0x1B); }
template<> EIGEN_STRONG_INLINE Packet2d preverse(const Packet2d& a) { return _mm_shuffle_pd(a,a,0x1); }
template<> EIGEN_STRONG_INLINE Packet4i preverse(const Packet4i& a) { return _mm_shuffle_epi32(a,0x1B); }
template<> EIGEN_STRONG_INLINE Packet16b preverse(const Packet16b& a) {
#ifdef EIGEN_VECTORIZE_SSSE3
  __m128i mask = _mm_set_epi8(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15);
  return _mm_shuffle_epi8(a, mask);
#else
  Packet16b tmp = _mm_shuffle_epi32(a, _MM_SHUFFLE(0, 1, 2, 3));
  tmp = _mm_shufflehi_epi16(_mm_shufflelo_epi16(tmp, _MM_SHUFFLE(2, 3, 0, 1)), _MM_SHUFFLE(2, 3, 0, 1));
  return _mm_or_si128(_mm_slli_epi16(tmp, 8), _mm_srli_epi16(tmp, 8));
#endif
}

template<> EIGEN_STRONG_INLINE Packet4f pfrexp<Packet4f>(const Packet4f& a, Packet4f& exponent) {
  return pfrexp_generic(a,exponent);
}

// Extract exponent without existence of Packet2l.
template<>
EIGEN_STRONG_INLINE  
Packet2d pfrexp_generic_get_biased_exponent(const Packet2d& a) {
  const Packet2d cst_exp_mask  = pset1frombits<Packet2d>(static_cast<uint64_t>(0x7ff0000000000000ull));
  __m128i a_expo = _mm_srli_epi64(_mm_castpd_si128(pand(a, cst_exp_mask)), 52);
  return _mm_cvtepi32_pd(vec4i_swizzle1(a_expo, 0, 2, 1, 3));
}

template<> EIGEN_STRONG_INLINE Packet2d pfrexp<Packet2d>(const Packet2d& a, Packet2d& exponent) {
  return pfrexp_generic(a, exponent);
}

template<> EIGEN_STRONG_INLINE Packet4f pldexp<Packet4f>(const Packet4f& a, const Packet4f& exponent) {
  return pldexp_generic(a,exponent);
}

// We specialize pldexp here, since the generic implementation uses Packet2l, which is not well
// supported by SSE, and has more range than is needed for exponents.
template<> EIGEN_STRONG_INLINE Packet2d pldexp<Packet2d>(const Packet2d& a, const Packet2d& exponent) {
  // Clamp exponent to [-2099, 2099]
  const Packet2d max_exponent = pset1<Packet2d>(2099.0);
  const Packet2d e = pmin(pmax(exponent, pnegate(max_exponent)), max_exponent);
  
  // Convert e to integer and swizzle to low-order bits.
  const Packet4i ei = vec4i_swizzle1(_mm_cvtpd_epi32(e), 0, 3, 1, 3);
  
  // Split 2^e into four factors and multiply:
  const Packet4i bias = _mm_set_epi32(0, 1023, 0, 1023);
  Packet4i b = parithmetic_shift_right<2>(ei);  // floor(e/4)
  Packet2d c = _mm_castsi128_pd(_mm_slli_epi64(padd(b, bias), 52));  // 2^b
  Packet2d out = pmul(pmul(pmul(a, c), c), c); // a * 2^(3b)
  b = psub(psub(psub(ei, b), b), b);  // e - 3b
  c = _mm_castsi128_pd(_mm_slli_epi64(padd(b, bias), 52));  // 2^(e - 3b)
  out = pmul(out, c);  // a * 2^e
  return out;
}

// with AVX, the default implementations based on pload1 are faster
#ifndef __AVX__
template<> EIGEN_STRONG_INLINE void
pbroadcast4<Packet4f>(const float *a,
                      Packet4f& a0, Packet4f& a1, Packet4f& a2, Packet4f& a3)
{
  a3 = pload<Packet4f>(a);
  a0 = vec4f_swizzle1(a3, 0,0,0,0);
  a1 = vec4f_swizzle1(a3, 1,1,1,1);
  a2 = vec4f_swizzle1(a3, 2,2,2,2);
  a3 = vec4f_swizzle1(a3, 3,3,3,3);
}
template<> EIGEN_STRONG_INLINE void
pbroadcast4<Packet2d>(const double *a,
                      Packet2d& a0, Packet2d& a1, Packet2d& a2, Packet2d& a3)
{
#ifdef EIGEN_VECTORIZE_SSE3
  a0 = _mm_loaddup_pd(a+0);
  a1 = _mm_loaddup_pd(a+1);
  a2 = _mm_loaddup_pd(a+2);
  a3 = _mm_loaddup_pd(a+3);
#else
  a1 = pload<Packet2d>(a);
  a0 = vec2d_swizzle1(a1, 0,0);
  a1 = vec2d_swizzle1(a1, 1,1);
  a3 = pload<Packet2d>(a+2);
  a2 = vec2d_swizzle1(a3, 0,0);
  a3 = vec2d_swizzle1(a3, 1,1);
#endif
}
#endif

EIGEN_STRONG_INLINE void punpackp(Packet4f* vecs)
{
  vecs[1] = _mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(vecs[0]), 0x55));
  vecs[2] = _mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(vecs[0]), 0xAA));
  vecs[3] = _mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(vecs[0]), 0xFF));
  vecs[0] = _mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(vecs[0]), 0x00));
}

template<> EIGEN_STRONG_INLINE float predux<Packet4f>(const Packet4f& a)
{
  // Disable SSE3 _mm_hadd_pd that is extremely slow on all existing Intel's architectures
  // (from Nehalem to Haswell)
// #ifdef EIGEN_VECTORIZE_SSE3
//   Packet4f tmp = _mm_add_ps(a, vec4f_swizzle1(a,2,3,2,3));
// #else
  Packet4f tmp = _mm_add_ps(a, _mm_movehl_ps(a,a));
  return pfirst<Packet4f>(_mm_add_ss(tmp, _mm_shuffle_ps(tmp,tmp, 1)));
// #endif
}

template<> EIGEN_STRONG_INLINE double predux<Packet2d>(const Packet2d& a)
{
  // Disable SSE3 _mm_hadd_pd that is extremely slow on all existing Intel's architectures
  // (from Nehalem to Haswell)
// #ifdef EIGEN_VECTORIZE_SSE3
//   return pfirst<Packet2d>(_mm_hadd_pd(a, a));
// #else
  return pfirst<Packet2d>(_mm_add_sd(a, _mm_unpackhi_pd(a,a)));
// #endif
}

#ifdef EIGEN_VECTORIZE_SSSE3
template<> EIGEN_STRONG_INLINE int predux<Packet4i>(const Packet4i& a)
{
  Packet4i tmp0 = _mm_hadd_epi32(a,a);
  return pfirst<Packet4i>(_mm_hadd_epi32(tmp0,tmp0));
}

#else
template<> EIGEN_STRONG_INLINE int predux<Packet4i>(const Packet4i& a)
{
  Packet4i tmp = _mm_add_epi32(a, _mm_unpackhi_epi64(a,a));
  return pfirst(tmp) + pfirst<Packet4i>(_mm_shuffle_epi32(tmp, 1));
}
#endif

template<> EIGEN_STRONG_INLINE bool predux<Packet16b>(const Packet16b& a) {
  Packet4i tmp = _mm_or_si128(a, _mm_unpackhi_epi64(a,a));
  return (pfirst(tmp) != 0) || (pfirst<Packet4i>(_mm_shuffle_epi32(tmp, 1)) != 0);
}

// Other reduction functions:


// mul
template<> EIGEN_STRONG_INLINE float predux_mul<Packet4f>(const Packet4f& a)
{
  Packet4f tmp = _mm_mul_ps(a, _mm_movehl_ps(a,a));
  return pfirst<Packet4f>(_mm_mul_ss(tmp, _mm_shuffle_ps(tmp,tmp, 1)));
}
template<> EIGEN_STRONG_INLINE double predux_mul<Packet2d>(const Packet2d& a)
{
  return pfirst<Packet2d>(_mm_mul_sd(a, _mm_unpackhi_pd(a,a)));
}
template<> EIGEN_STRONG_INLINE int predux_mul<Packet4i>(const Packet4i& a)
{
  // after some experiments, it is seems this is the fastest way to implement it
  // for GCC (eg., reusing pmul is very slow !)
  // TODO try to call _mm_mul_epu32 directly
  EIGEN_ALIGN16 int aux[4];
  pstore(aux, a);
  return  (aux[0] * aux[1]) * (aux[2] * aux[3]);
}

template<> EIGEN_STRONG_INLINE bool predux_mul<Packet16b>(const Packet16b& a) {
  Packet4i tmp = _mm_and_si128(a, _mm_unpackhi_epi64(a,a));
  return ((pfirst<Packet4i>(tmp) == 0x01010101) &&
          (pfirst<Packet4i>(_mm_shuffle_epi32(tmp, 1)) == 0x01010101));
}

// min
template<> EIGEN_STRONG_INLINE float predux_min<Packet4f>(const Packet4f& a)
{
  Packet4f tmp = _mm_min_ps(a, _mm_movehl_ps(a,a));
  return pfirst<Packet4f>(_mm_min_ss(tmp, _mm_shuffle_ps(tmp,tmp, 1)));
}
template<> EIGEN_STRONG_INLINE double predux_min<Packet2d>(const Packet2d& a)
{
  return pfirst<Packet2d>(_mm_min_sd(a, _mm_unpackhi_pd(a,a)));
}
template<> EIGEN_STRONG_INLINE int predux_min<Packet4i>(const Packet4i& a)
{
#ifdef EIGEN_VECTORIZE_SSE4_1
  Packet4i tmp = _mm_min_epi32(a, _mm_shuffle_epi32(a, _MM_SHUFFLE(0,0,3,2)));
  return pfirst<Packet4i>(_mm_min_epi32(tmp,_mm_shuffle_epi32(tmp, 1)));
#else
  // after some experiments, it is seems this is the fastest way to implement it
  // for GCC (eg., it does not like using std::min after the pstore !!)
  EIGEN_ALIGN16 int aux[4];
  pstore(aux, a);
  int aux0 = aux[0]<aux[1] ? aux[0] : aux[1];
  int aux2 = aux[2]<aux[3] ? aux[2] : aux[3];
  return aux0<aux2 ? aux0 : aux2;
#endif // EIGEN_VECTORIZE_SSE4_1
}

// max
template<> EIGEN_STRONG_INLINE float predux_max<Packet4f>(const Packet4f& a)
{
  Packet4f tmp = _mm_max_ps(a, _mm_movehl_ps(a,a));
  return pfirst<Packet4f>(_mm_max_ss(tmp, _mm_shuffle_ps(tmp,tmp, 1)));
}
template<> EIGEN_STRONG_INLINE double predux_max<Packet2d>(const Packet2d& a)
{
  return pfirst<Packet2d>(_mm_max_sd(a, _mm_unpackhi_pd(a,a)));
}
template<> EIGEN_STRONG_INLINE int predux_max<Packet4i>(const Packet4i& a)
{
#ifdef EIGEN_VECTORIZE_SSE4_1
  Packet4i tmp = _mm_max_epi32(a, _mm_shuffle_epi32(a, _MM_SHUFFLE(0,0,3,2)));
  return pfirst<Packet4i>(_mm_max_epi32(tmp,_mm_shuffle_epi32(tmp, 1)));
#else
  // after some experiments, it is seems this is the fastest way to implement it
  // for GCC (eg., it does not like using std::min after the pstore !!)
  EIGEN_ALIGN16 int aux[4];
  pstore(aux, a);
  int aux0 = aux[0]>aux[1] ? aux[0] : aux[1];
  int aux2 = aux[2]>aux[3] ? aux[2] : aux[3];
  return aux0>aux2 ? aux0 : aux2;
#endif // EIGEN_VECTORIZE_SSE4_1
}

template<> EIGEN_STRONG_INLINE Packet8f pnegate(const Packet8f& a)
{
  return _mm256_sub_ps(_mm256_set1_ps(0.0),a);
}
template<> EIGEN_STRONG_INLINE Packet4d pnegate(const Packet4d& a)
{
  return _mm256_sub_pd(_mm256_set1_pd(0.0),a);
}
template<> EIGEN_STRONG_INLINE Packet8i pnegate(const Packet8i& a)
{
  return psub(pzero(a), a);
}

template<> EIGEN_STRONG_INLINE Packet8f pconj(const Packet8f& a) { return a; }
template<> EIGEN_STRONG_INLINE Packet4d pconj(const Packet4d& a) { return a; }
template<> EIGEN_STRONG_INLINE Packet8i pconj(const Packet8i& a) { return a; }

template<> EIGEN_STRONG_INLINE Packet8f pmul<Packet8f>(const Packet8f& a, const Packet8f& b) { return _mm256_mul_ps(a,b); }
template<> EIGEN_STRONG_INLINE Packet4d pmul<Packet4d>(const Packet4d& a, const Packet4d& b) { return _mm256_mul_pd(a,b); }
template<> EIGEN_STRONG_INLINE Packet8i pmul<Packet8i>(const Packet8i& a, const Packet8i& b) {
#ifdef EIGEN_VECTORIZE_AVX2
  return _mm256_mullo_epi32(a,b);
#else
  const __m128i lo = _mm_mullo_epi32(_mm256_extractf128_si256(a, 0), _mm256_extractf128_si256(b, 0));
  const __m128i hi = _mm_mullo_epi32(_mm256_extractf128_si256(a, 1), _mm256_extractf128_si256(b, 1));
  return _mm256_insertf128_si256(_mm256_castsi128_si256(lo), (hi), 1);
#endif
}

template<> EIGEN_STRONG_INLINE Packet8f pdiv<Packet8f>(const Packet8f& a, const Packet8f& b) { return _mm256_div_ps(a,b); }
template<> EIGEN_STRONG_INLINE Packet4d pdiv<Packet4d>(const Packet4d& a, const Packet4d& b) { return _mm256_div_pd(a,b); }
template<> EIGEN_STRONG_INLINE Packet8i pdiv<Packet8i>(const Packet8i& /*a*/, const Packet8i& /*b*/)
{ eigen_assert(false && "packet integer division are not supported by AVX");
  return pset1<Packet8i>(0);
}

#ifdef EIGEN_VECTORIZE_FMA

template <>
EIGEN_STRONG_INLINE Packet8f pmadd(const Packet8f& a, const Packet8f& b, const Packet8f& c) {
  return _mm256_fmadd_ps(a, b, c);
}
template <>
EIGEN_STRONG_INLINE Packet4d pmadd(const Packet4d& a, const Packet4d& b, const Packet4d& c) {
  return _mm256_fmadd_pd(a, b, c);
}

template <>
EIGEN_STRONG_INLINE Packet8f pmsub(const Packet8f& a, const Packet8f& b, const Packet8f& c) {
  return _mm256_fmsub_ps(a, b, c);
}

template <>
EIGEN_STRONG_INLINE Packet4d pmsub(const Packet4d& a, const Packet4d& b, const Packet4d& c) {
  return _mm256_fmsub_pd(a, b, c);
}

template <>
EIGEN_STRONG_INLINE Packet8f pnmadd(const Packet8f& a, const Packet8f& b, const Packet8f& c) {
  return _mm256_fnmadd_ps(a, b, c);
}

template <>
EIGEN_STRONG_INLINE Packet4d pnmadd(const Packet4d& a, const Packet4d& b, const Packet4d& c) {
  return _mm256_fnmadd_pd(a, b, c);
}

template <>
EIGEN_STRONG_INLINE Packet8f pnmsub(const Packet8f& a, const Packet8f& b, const Packet8f& c) {
  return _mm256_fnmsub_ps(a, b, c);
}

template <>
EIGEN_STRONG_INLINE Packet4d pnmsub(const Packet4d& a, const Packet4d& b, const Packet4d& c) {
  return _mm256_fnmsub_pd(a, b, c);
}

#endif

template<> EIGEN_STRONG_INLINE Packet8f pcmp_le(const Packet8f& a, const Packet8f& b) { return _mm256_cmp_ps(a,b,_CMP_LE_OQ); }
template<> EIGEN_STRONG_INLINE Packet8f pcmp_lt(const Packet8f& a, const Packet8f& b) { return _mm256_cmp_ps(a,b,_CMP_LT_OQ); }
template<> EIGEN_STRONG_INLINE Packet8f pcmp_lt_or_nan(const Packet8f& a, const Packet8f& b) { return _mm256_cmp_ps(a, b, _CMP_NGE_UQ); }
template<> EIGEN_STRONG_INLINE Packet8f pcmp_eq(const Packet8f& a, const Packet8f& b) { return _mm256_cmp_ps(a,b,_CMP_EQ_OQ); }

template<> EIGEN_STRONG_INLINE Packet4d pcmp_le(const Packet4d& a, const Packet4d& b) { return _mm256_cmp_pd(a,b,_CMP_LE_OQ); }
template<> EIGEN_STRONG_INLINE Packet4d pcmp_lt(const Packet4d& a, const Packet4d& b) { return _mm256_cmp_pd(a,b,_CMP_LT_OQ); }
template<> EIGEN_STRONG_INLINE Packet4d pcmp_lt_or_nan(const Packet4d& a, const Packet4d& b) { return _mm256_cmp_pd(a, b, _CMP_NGE_UQ); }
template<> EIGEN_STRONG_INLINE Packet4d pcmp_eq(const Packet4d& a, const Packet4d& b) { return _mm256_cmp_pd(a,b,_CMP_EQ_OQ); }

template<> EIGEN_STRONG_INLINE Packet8i pcmp_le(const Packet8i& a, const Packet8i& b) {
#ifdef EIGEN_VECTORIZE_AVX2
  return _mm256_xor_si256(_mm256_cmpgt_epi32(a,b), _mm256_set1_epi32(-1));
#else
  __m128i lo = _mm_cmpgt_epi32(_mm256_extractf128_si256(a, 0), _mm256_extractf128_si256(b, 0));
  lo = _mm_xor_si128(lo, _mm_set1_epi32(-1));
  __m128i hi = _mm_cmpgt_epi32(_mm256_extractf128_si256(a, 1), _mm256_extractf128_si256(b, 1));
  hi = _mm_xor_si128(hi, _mm_set1_epi32(-1));
  return _mm256_insertf128_si256(_mm256_castsi128_si256(lo), (hi), 1);
#endif
}
template<> EIGEN_STRONG_INLINE Packet8i pcmp_lt(const Packet8i& a, const Packet8i& b) {
#ifdef EIGEN_VECTORIZE_AVX2
  return _mm256_cmpgt_epi32(b,a);
#else
  __m128i lo = _mm_cmpgt_epi32(_mm256_extractf128_si256(b, 0), _mm256_extractf128_si256(a, 0));
  __m128i hi = _mm_cmpgt_epi32(_mm256_extractf128_si256(b, 1), _mm256_extractf128_si256(a, 1));
  return _mm256_insertf128_si256(_mm256_castsi128_si256(lo), (hi), 1);
#endif
}
template<> EIGEN_STRONG_INLINE Packet8i pcmp_eq(const Packet8i& a, const Packet8i& b) {
#ifdef EIGEN_VECTORIZE_AVX2
  return _mm256_cmpeq_epi32(a,b);
#else
  __m128i lo = _mm_cmpeq_epi32(_mm256_extractf128_si256(a, 0), _mm256_extractf128_si256(b, 0));
  __m128i hi = _mm_cmpeq_epi32(_mm256_extractf128_si256(a, 1), _mm256_extractf128_si256(b, 1));
  return _mm256_insertf128_si256(_mm256_castsi128_si256(lo), (hi), 1);
#endif
}

template<> EIGEN_STRONG_INLINE Packet8f pmin<Packet8f>(const Packet8f& a, const Packet8f& b) {
#if EIGEN_COMP_GNUC && EIGEN_COMP_GNUC < 63
  // There appears to be a bug in GCC, by which the optimizer may flip
  // the argument order in calls to _mm_min_ps/_mm_max_ps, so we have to
  // resort to inline ASM here. This is supposed to be fixed in gcc6.3,
  // see also: https://gcc.gnu.org/bugzilla/show_bug.cgi?id=72867
  Packet8f res;
  asm("vminps %[a], %[b], %[res]" : [res] "=x" (res) : [a] "x" (a), [b] "x" (b));
  return res;
#else
  // Arguments are swapped to match NaN propagation behavior of std::min.
  return _mm256_min_ps(b,a);
#endif
}
template<> EIGEN_STRONG_INLINE Packet4d pmin<Packet4d>(const Packet4d& a, const Packet4d& b) {
#if EIGEN_COMP_GNUC && EIGEN_COMP_GNUC < 63
  // See pmin above
  Packet4d res;
  asm("vminpd %[a], %[b], %[res]" : [res] "=x" (res) : [a] "x" (a), [b] "x" (b));
  return res;
#else
  // Arguments are swapped to match NaN propagation behavior of std::min.
  return _mm256_min_pd(b,a);
#endif
}
template<> EIGEN_STRONG_INLINE Packet8i pmin<Packet8i>(const Packet8i& a, const Packet8i& b) {
#ifdef EIGEN_VECTORIZE_AVX2
  return _mm256_min_epi32(a, b);
#else
  __m128i lo = _mm_min_epi32(_mm256_extractf128_si256(a, 0), _mm256_extractf128_si256(b, 0));
  __m128i hi = _mm_min_epi32(_mm256_extractf128_si256(a, 1), _mm256_extractf128_si256(b, 1));
  return _mm256_insertf128_si256(_mm256_castsi128_si256(lo), (hi), 1);
#endif
}

template<> EIGEN_STRONG_INLINE Packet8f pmax<Packet8f>(const Packet8f& a, const Packet8f& b) {
#if EIGEN_COMP_GNUC && EIGEN_COMP_GNUC < 63
  // See pmin above
  Packet8f res;
  asm("vmaxps %[a], %[b], %[res]" : [res] "=x" (res) : [a] "x" (a), [b] "x" (b));
  return res;
#else
  // Arguments are swapped to match NaN propagation behavior of std::max.
  return _mm256_max_ps(b,a);
#endif
}
template<> EIGEN_STRONG_INLINE Packet4d pmax<Packet4d>(const Packet4d& a, const Packet4d& b) {
#if EIGEN_COMP_GNUC && EIGEN_COMP_GNUC < 63
  // See pmin above
  Packet4d res;
  asm("vmaxpd %[a], %[b], %[res]" : [res] "=x" (res) : [a] "x" (a), [b] "x" (b));
  return res;
#else
  // Arguments are swapped to match NaN propagation behavior of std::max.
  return _mm256_max_pd(b,a);
#endif
}
template<> EIGEN_STRONG_INLINE Packet8i pmax<Packet8i>(const Packet8i& a, const Packet8i& b) {
#ifdef EIGEN_VECTORIZE_AVX2
  return _mm256_max_epi32(a, b);
#else
  __m128i lo = _mm_max_epi32(_mm256_extractf128_si256(a, 0), _mm256_extractf128_si256(b, 0));
  __m128i hi = _mm_max_epi32(_mm256_extractf128_si256(a, 1), _mm256_extractf128_si256(b, 1));
  return _mm256_insertf128_si256(_mm256_castsi128_si256(lo), (hi), 1);
#endif
}

// Add specializations for min/max with prescribed NaN progation.
template<>
EIGEN_STRONG_INLINE Packet8f pmin<PropagateNumbers, Packet8f>(const Packet8f& a, const Packet8f& b) {
  return pminmax_propagate_numbers(a, b, pmin<Packet8f>);
}
template<>
EIGEN_STRONG_INLINE Packet4d pmin<PropagateNumbers, Packet4d>(const Packet4d& a, const Packet4d& b) {
  return pminmax_propagate_numbers(a, b, pmin<Packet4d>);
}
template<>
EIGEN_STRONG_INLINE Packet8f pmax<PropagateNumbers, Packet8f>(const Packet8f& a, const Packet8f& b) {
  return pminmax_propagate_numbers(a, b, pmax<Packet8f>);
}
template<>
EIGEN_STRONG_INLINE Packet4d pmax<PropagateNumbers, Packet4d>(const Packet4d& a, const Packet4d& b) {
  return pminmax_propagate_numbers(a, b, pmax<Packet4d>);
}
template<>
EIGEN_STRONG_INLINE Packet8f pmin<PropagateNaN, Packet8f>(const Packet8f& a, const Packet8f& b) {
  return pminmax_propagate_nan(a, b, pmin<Packet8f>);
}
template<>
EIGEN_STRONG_INLINE Packet4d pmin<PropagateNaN, Packet4d>(const Packet4d& a, const Packet4d& b) {
  return pminmax_propagate_nan(a, b, pmin<Packet4d>);
}
template<>
EIGEN_STRONG_INLINE Packet8f pmax<PropagateNaN, Packet8f>(const Packet8f& a, const Packet8f& b) {
  return pminmax_propagate_nan(a, b, pmax<Packet8f>);
}
template<>
EIGEN_STRONG_INLINE Packet4d pmax<PropagateNaN, Packet4d>(const Packet4d& a, const Packet4d& b) {
  return pminmax_propagate_nan(a, b, pmax<Packet4d>);
}

template<> EIGEN_STRONG_INLINE Packet8f print<Packet8f>(const Packet8f& a) { return _mm256_round_ps(a, _MM_FROUND_CUR_DIRECTION); }
template<> EIGEN_STRONG_INLINE Packet4d print<Packet4d>(const Packet4d& a) { return _mm256_round_pd(a, _MM_FROUND_CUR_DIRECTION); }

template<> EIGEN_STRONG_INLINE Packet8f pceil<Packet8f>(const Packet8f& a) { return _mm256_ceil_ps(a); }
template<> EIGEN_STRONG_INLINE Packet4d pceil<Packet4d>(const Packet4d& a) { return _mm256_ceil_pd(a); }

template<> EIGEN_STRONG_INLINE Packet8f pfloor<Packet8f>(const Packet8f& a) { return _mm256_floor_ps(a); }
template<> EIGEN_STRONG_INLINE Packet4d pfloor<Packet4d>(const Packet4d& a) { return _mm256_floor_pd(a); }


template<> EIGEN_STRONG_INLINE Packet8i ptrue<Packet8i>(const Packet8i& a) {
#ifdef EIGEN_VECTORIZE_AVX2
  // vpcmpeqd has lower latency than the more general vcmpps
  return _mm256_cmpeq_epi32(a,a);
#else
  const __m256 b = _mm256_castsi256_ps(a);
  return _mm256_castps_si256(_mm256_cmp_ps(b,b,_CMP_TRUE_UQ));
#endif
}

template<> EIGEN_STRONG_INLINE Packet8f ptrue<Packet8f>(const Packet8f& a) {
#ifdef EIGEN_VECTORIZE_AVX2
  // vpcmpeqd has lower latency than the more general vcmpps
  const __m256i b = _mm256_castps_si256(a);
  return _mm256_castsi256_ps(_mm256_cmpeq_epi32(b,b));
#else
  return _mm256_cmp_ps(a,a,_CMP_TRUE_UQ);
#endif
}

template<> EIGEN_STRONG_INLINE Packet4d ptrue<Packet4d>(const Packet4d& a) {
#ifdef EIGEN_VECTORIZE_AVX2
  // vpcmpeqq has lower latency than the more general vcmppd
  const __m256i b = _mm256_castpd_si256(a);
  return _mm256_castsi256_pd(_mm256_cmpeq_epi64(b,b));
#else
  return _mm256_cmp_pd(a,a,_CMP_TRUE_UQ);
#endif
}

template<> EIGEN_STRONG_INLINE Packet8f pand<Packet8f>(const Packet8f& a, const Packet8f& b) { return _mm256_and_ps(a,b); }
template<> EIGEN_STRONG_INLINE Packet4d pand<Packet4d>(const Packet4d& a, const Packet4d& b) { return _mm256_and_pd(a,b); }
template<> EIGEN_STRONG_INLINE Packet8i pand<Packet8i>(const Packet8i& a, const Packet8i& b) {
#ifdef EIGEN_VECTORIZE_AVX2
  return _mm256_and_si256(a,b);
#else
  return _mm256_castps_si256(_mm256_and_ps(_mm256_castsi256_ps(a),_mm256_castsi256_ps(b)));
#endif
}

template<> EIGEN_STRONG_INLINE Packet8f por<Packet8f>(const Packet8f& a, const Packet8f& b) { return _mm256_or_ps(a,b); }
template<> EIGEN_STRONG_INLINE Packet4d por<Packet4d>(const Packet4d& a, const Packet4d& b) { return _mm256_or_pd(a,b); }
template<> EIGEN_STRONG_INLINE Packet8i por<Packet8i>(const Packet8i& a, const Packet8i& b) {
#ifdef EIGEN_VECTORIZE_AVX2
  return _mm256_or_si256(a,b);
#else
  return _mm256_castps_si256(_mm256_or_ps(_mm256_castsi256_ps(a),_mm256_castsi256_ps(b)));
#endif
}

template<> EIGEN_STRONG_INLINE Packet8f pxor<Packet8f>(const Packet8f& a, const Packet8f& b) { return _mm256_xor_ps(a,b); }
template<> EIGEN_STRONG_INLINE Packet4d pxor<Packet4d>(const Packet4d& a, const Packet4d& b) { return _mm256_xor_pd(a,b); }
template<> EIGEN_STRONG_INLINE Packet8i pxor<Packet8i>(const Packet8i& a, const Packet8i& b) {
#ifdef EIGEN_VECTORIZE_AVX2
  return _mm256_xor_si256(a,b);
#else
  return _mm256_castps_si256(_mm256_xor_ps(_mm256_castsi256_ps(a),_mm256_castsi256_ps(b)));
#endif
}

template<> EIGEN_STRONG_INLINE Packet8f pandnot<Packet8f>(const Packet8f& a, const Packet8f& b) { return _mm256_andnot_ps(b,a); }
template<> EIGEN_STRONG_INLINE Packet4d pandnot<Packet4d>(const Packet4d& a, const Packet4d& b) { return _mm256_andnot_pd(b,a); }
template<> EIGEN_STRONG_INLINE Packet8i pandnot<Packet8i>(const Packet8i& a, const Packet8i& b) {
#ifdef EIGEN_VECTORIZE_AVX2
  return _mm256_andnot_si256(b,a);
#else
  return _mm256_castps_si256(_mm256_andnot_ps(_mm256_castsi256_ps(b),_mm256_castsi256_ps(a)));
#endif
}

template<> EIGEN_STRONG_INLINE Packet8f pround<Packet8f>(const Packet8f& a)
{
  const Packet8f mask = pset1frombits<Packet8f>(static_cast<numext::uint32_t>(0x80000000u));
  const Packet8f prev0dot5 = pset1frombits<Packet8f>(static_cast<numext::uint32_t>(0x3EFFFFFFu));
  return _mm256_round_ps(padd(por(pand(a, mask), prev0dot5), a), _MM_FROUND_TO_ZERO);
}
template<> EIGEN_STRONG_INLINE Packet4d pround<Packet4d>(const Packet4d& a)
{
  const Packet4d mask = pset1frombits<Packet4d>(static_cast<numext::uint64_t>(0x8000000000000000ull));
  const Packet4d prev0dot5 = pset1frombits<Packet4d>(static_cast<numext::uint64_t>(0x3FDFFFFFFFFFFFFFull));
  return _mm256_round_pd(padd(por(pand(a, mask), prev0dot5), a), _MM_FROUND_TO_ZERO);
}

template<> EIGEN_STRONG_INLINE Packet8f pselect<Packet8f>(const Packet8f& mask, const Packet8f& a, const Packet8f& b)
{ return _mm256_blendv_ps(b,a,mask); }
template<> EIGEN_STRONG_INLINE Packet4d pselect<Packet4d>(const Packet4d& mask, const Packet4d& a, const Packet4d& b)
{ return _mm256_blendv_pd(b,a,mask); }

template<int N> EIGEN_STRONG_INLINE Packet8i parithmetic_shift_right(Packet8i a) {
#ifdef EIGEN_VECTORIZE_AVX2
  return _mm256_srai_epi32(a, N);
#else
  __m128i lo = _mm_srai_epi32(_mm256_extractf128_si256(a, 0), N);
  __m128i hi = _mm_srai_epi32(_mm256_extractf128_si256(a, 1), N);
  return _mm256_insertf128_si256(_mm256_castsi128_si256(lo), (hi), 1);
#endif
}

template<int N> EIGEN_STRONG_INLINE Packet8i plogical_shift_right(Packet8i a) {
#ifdef EIGEN_VECTORIZE_AVX2
  return _mm256_srli_epi32(a, N);
#else
  __m128i lo = _mm_srli_epi32(_mm256_extractf128_si256(a, 0), N);
  __m128i hi = _mm_srli_epi32(_mm256_extractf128_si256(a, 1), N);
  return _mm256_insertf128_si256(_mm256_castsi128_si256(lo), (hi), 1);
#endif
}

template<int N> EIGEN_STRONG_INLINE Packet8i plogical_shift_left(Packet8i a) {
#ifdef EIGEN_VECTORIZE_AVX2
  return _mm256_slli_epi32(a, N);
#else
  __m128i lo = _mm_slli_epi32(_mm256_extractf128_si256(a, 0), N);
  __m128i hi = _mm_slli_epi32(_mm256_extractf128_si256(a, 1), N);
  return _mm256_insertf128_si256(_mm256_castsi128_si256(lo), (hi), 1);
#endif
}

template<> EIGEN_STRONG_INLINE Packet8f pload<Packet8f>(const float*   from) { EIGEN_DEBUG_ALIGNED_LOAD return _mm256_load_ps(from); }
template<> EIGEN_STRONG_INLINE Packet4d pload<Packet4d>(const double*  from) { EIGEN_DEBUG_ALIGNED_LOAD return _mm256_load_pd(from); }
template<> EIGEN_STRONG_INLINE Packet8i pload<Packet8i>(const int*     from) { EIGEN_DEBUG_ALIGNED_LOAD return _mm256_load_si256(reinterpret_cast<const __m256i*>(from)); }

template<> EIGEN_STRONG_INLINE Packet8f ploadu<Packet8f>(const float* from) { EIGEN_DEBUG_UNALIGNED_LOAD return _mm256_loadu_ps(from); }
template<> EIGEN_STRONG_INLINE Packet4d ploadu<Packet4d>(const double* from) { EIGEN_DEBUG_UNALIGNED_LOAD return _mm256_loadu_pd(from); }
template<> EIGEN_STRONG_INLINE Packet8i ploadu<Packet8i>(const int* from) { EIGEN_DEBUG_UNALIGNED_LOAD return _mm256_loadu_si256(reinterpret_cast<const __m256i*>(from)); }

template<> EIGEN_STRONG_INLINE Packet8f ploadu<Packet8f>(const float* from, uint8_t umask) {
#ifdef EIGEN_VECTORIZE_AVX512
  __mmask16 mask = static_cast<__mmask16>(umask & 0x00FF);
  EIGEN_DEBUG_UNALIGNED_LOAD return  _mm512_castps512_ps256(_mm512_maskz_loadu_ps(mask, from));
#else
  Packet8i mask = _mm256_set1_epi8(static_cast<char>(umask));
  const Packet8i bit_mask = _mm256_set_epi32(0xffffff7f, 0xffffffbf, 0xffffffdf, 0xffffffef, 0xfffffff7, 0xfffffffb, 0xfffffffd, 0xfffffffe);
  mask = por<Packet8i>(mask, bit_mask);
  mask = pcmp_eq<Packet8i>(mask, _mm256_set1_epi32(0xffffffff));
  EIGEN_DEBUG_UNALIGNED_LOAD return _mm256_maskload_ps(from, mask);
#endif
}

// Loads 4 floats from memory a returns the packet {a0, a0  a1, a1, a2, a2, a3, a3}
template<> EIGEN_STRONG_INLINE Packet8f ploaddup<Packet8f>(const float* from)
{
  // TODO try to find a way to avoid the need of a temporary register
//   Packet8f tmp  = _mm256_castps128_ps256(_mm_loadu_ps(from));
//   tmp = _mm256_insertf128_ps(tmp, _mm_movehl_ps(_mm256_castps256_ps128(tmp),_mm256_castps256_ps128(tmp)), 1);
//   return _mm256_unpacklo_ps(tmp,tmp);

  // _mm256_insertf128_ps is very slow on Haswell, thus:
  Packet8f tmp = _mm256_broadcast_ps((const __m128*)(const void*)from);
  // mimic an "inplace" permutation of the lower 128bits using a blend
  tmp = _mm256_blend_ps(tmp,_mm256_castps128_ps256(_mm_permute_ps( _mm256_castps256_ps128(tmp), _MM_SHUFFLE(1,0,1,0))), 15);
  // then we can perform a consistent permutation on the global register to get everything in shape:
  return  _mm256_permute_ps(tmp, _MM_SHUFFLE(3,3,2,2));
}
// Loads 2 doubles from memory a returns the packet {a0, a0, a1, a1}
template<> EIGEN_STRONG_INLINE Packet4d ploaddup<Packet4d>(const double* from)
{
  Packet4d tmp = _mm256_broadcast_pd((const __m128d*)(const void*)from);
  return  _mm256_permute_pd(tmp, 3<<2);
}
// Loads 4 integers from memory a returns the packet {a0, a0, a1, a1, a2, a2, a3, a3}
template<> EIGEN_STRONG_INLINE Packet8i ploaddup<Packet8i>(const int* from)
{
#ifdef EIGEN_VECTORIZE_AVX2
  const Packet8i a = _mm256_castsi128_si256(ploadu<Packet4i>(from));
  return _mm256_permutevar8x32_epi32(a, _mm256_setr_epi32(0, 0, 1, 1, 2, 2, 3, 3));
#else
  __m256 tmp = _mm256_broadcast_ps((const __m128*)(const void*)from);
  // mimic an "inplace" permutation of the lower 128bits using a blend
  tmp = _mm256_blend_ps(tmp,_mm256_castps128_ps256(_mm_permute_ps( _mm256_castps256_ps128(tmp), _MM_SHUFFLE(1,0,1,0))), 15);
  // then we can perform a consistent permutation on the global register to get everything in shape:
  return  _mm256_castps_si256(_mm256_permute_ps(tmp, _MM_SHUFFLE(3,3,2,2)));
#endif
}

// Loads 2 floats from memory a returns the packet {a0, a0  a0, a0, a1, a1, a1, a1}
template<> EIGEN_STRONG_INLINE Packet8f ploadquad<Packet8f>(const float* from)
{
  Packet8f tmp = _mm256_castps128_ps256(_mm_broadcast_ss(from));
  return _mm256_insertf128_ps(tmp, _mm_broadcast_ss(from+1), 1);
}
template<> EIGEN_STRONG_INLINE Packet8i ploadquad<Packet8i>(const int* from)
{
  return _mm256_insertf128_si256(_mm256_set1_epi32(*from), _mm_set1_epi32(*(from+1)), 1);
}

template<> EIGEN_STRONG_INLINE void pstore<float>(float*   to, const Packet8f& from) { EIGEN_DEBUG_ALIGNED_STORE _mm256_store_ps(to, from); }
template<> EIGEN_STRONG_INLINE void pstore<double>(double* to, const Packet4d& from) { EIGEN_DEBUG_ALIGNED_STORE _mm256_store_pd(to, from); }
template<> EIGEN_STRONG_INLINE void pstore<int>(int*       to, const Packet8i& from) { EIGEN_DEBUG_ALIGNED_STORE _mm256_storeu_si256(reinterpret_cast<__m256i*>(to), from); }

template<> EIGEN_STRONG_INLINE void pstoreu<float>(float*   to, const Packet8f& from) { EIGEN_DEBUG_UNALIGNED_STORE _mm256_storeu_ps(to, from); }
template<> EIGEN_STRONG_INLINE void pstoreu<double>(double* to, const Packet4d& from) { EIGEN_DEBUG_UNALIGNED_STORE _mm256_storeu_pd(to, from); }
template<> EIGEN_STRONG_INLINE void pstoreu<int>(int*       to, const Packet8i& from) { EIGEN_DEBUG_UNALIGNED_STORE _mm256_storeu_si256(reinterpret_cast<__m256i*>(to), from); }

template<> EIGEN_STRONG_INLINE void pstoreu<float>(float*   to, const Packet8f& from, uint8_t umask) {
#ifdef EIGEN_VECTORIZE_AVX512
  __mmask16 mask = static_cast<__mmask16>(umask & 0x00FF);
  EIGEN_DEBUG_UNALIGNED_STORE return _mm512_mask_storeu_ps(to, mask, _mm512_castps256_ps512(from));
#else
  Packet8i mask = _mm256_set1_epi8(static_cast<char>(umask));
  const Packet8i bit_mask = _mm256_set_epi32(0xffffff7f, 0xffffffbf, 0xffffffdf, 0xffffffef, 0xfffffff7, 0xfffffffb, 0xfffffffd, 0xfffffffe);
  mask = por<Packet8i>(mask, bit_mask);
  mask = pcmp_eq<Packet8i>(mask, _mm256_set1_epi32(0xffffffff));
  EIGEN_DEBUG_UNALIGNED_STORE return _mm256_maskstore_ps(to, mask, from);
#endif
}

// NOTE: leverage _mm256_i32gather_ps and _mm256_i32gather_pd if AVX2 instructions are available
// NOTE: for the record the following seems to be slower: return _mm256_i32gather_ps(from, _mm256_set1_epi32(stride), 4);
template<> EIGEN_DEVICE_FUNC inline Packet8f pgather<float, Packet8f>(const float* from, Index stride)
{
  return _mm256_set_ps(from[7*stride], from[6*stride], from[5*stride], from[4*stride],
                       from[3*stride], from[2*stride], from[1*stride], from[0*stride]);
}
template<> EIGEN_DEVICE_FUNC inline Packet4d pgather<double, Packet4d>(const double* from, Index stride)
{
  return _mm256_set_pd(from[3*stride], from[2*stride], from[1*stride], from[0*stride]);
}
template<> EIGEN_DEVICE_FUNC inline Packet8i pgather<int, Packet8i>(const int* from, Index stride)
{
  return _mm256_set_epi32(from[7*stride], from[6*stride], from[5*stride], from[4*stride],
                          from[3*stride], from[2*stride], from[1*stride], from[0*stride]);
}

template<> EIGEN_DEVICE_FUNC inline void pscatter<float, Packet8f>(float* to, const Packet8f& from, Index stride)
{
  __m128 low = _mm256_extractf128_ps(from, 0);
  to[stride*0] = _mm_cvtss_f32(low);
  to[stride*1] = _mm_cvtss_f32(_mm_shuffle_ps(low, low, 1));
  to[stride*2] = _mm_cvtss_f32(_mm_shuffle_ps(low, low, 2));
  to[stride*3] = _mm_cvtss_f32(_mm_shuffle_ps(low, low, 3));

  __m128 high = _mm256_extractf128_ps(from, 1);
  to[stride*4] = _mm_cvtss_f32(high);
  to[stride*5] = _mm_cvtss_f32(_mm_shuffle_ps(high, high, 1));
  to[stride*6] = _mm_cvtss_f32(_mm_shuffle_ps(high, high, 2));
  to[stride*7] = _mm_cvtss_f32(_mm_shuffle_ps(high, high, 3));
}
template<> EIGEN_DEVICE_FUNC inline void pscatter<double, Packet4d>(double* to, const Packet4d& from, Index stride)
{
  __m128d low = _mm256_extractf128_pd(from, 0);
  to[stride*0] = _mm_cvtsd_f64(low);
  to[stride*1] = _mm_cvtsd_f64(_mm_shuffle_pd(low, low, 1));
  __m128d high = _mm256_extractf128_pd(from, 1);
  to[stride*2] = _mm_cvtsd_f64(high);
  to[stride*3] = _mm_cvtsd_f64(_mm_shuffle_pd(high, high, 1));
}
template<> EIGEN_DEVICE_FUNC inline void pscatter<int, Packet8i>(int* to, const Packet8i& from, Index stride)
{
  __m128i low = _mm256_extractf128_si256(from, 0);
  to[stride*0] = _mm_extract_epi32(low, 0);
  to[stride*1] = _mm_extract_epi32(low, 1);
  to[stride*2] = _mm_extract_epi32(low, 2);
  to[stride*3] = _mm_extract_epi32(low, 3);

  __m128i high = _mm256_extractf128_si256(from, 1);
  to[stride*4] = _mm_extract_epi32(high, 0);
  to[stride*5] = _mm_extract_epi32(high, 1);
  to[stride*6] = _mm_extract_epi32(high, 2);
  to[stride*7] = _mm_extract_epi32(high, 3);
}

template<> EIGEN_STRONG_INLINE void pstore1<Packet8f>(float* to, const float& a)
{
  Packet8f pa = pset1<Packet8f>(a);
  pstore(to, pa);
}
template<> EIGEN_STRONG_INLINE void pstore1<Packet4d>(double* to, const double& a)
{
  Packet4d pa = pset1<Packet4d>(a);
  pstore(to, pa);
}
template<> EIGEN_STRONG_INLINE void pstore1<Packet8i>(int* to, const int& a)
{
  Packet8i pa = pset1<Packet8i>(a);
  pstore(to, pa);
}

template<> EIGEN_STRONG_INLINE float  pfirst<Packet8f>(const Packet8f& a) {
  return _mm_cvtss_f32(_mm256_castps256_ps128(a));
}
template<> EIGEN_STRONG_INLINE double pfirst<Packet4d>(const Packet4d& a) {
  return _mm_cvtsd_f64(_mm256_castpd256_pd128(a));
}
template<> EIGEN_STRONG_INLINE int    pfirst<Packet8i>(const Packet8i& a) {
  return _mm_cvtsi128_si32(_mm256_castsi256_si128(a));
}


template<> EIGEN_STRONG_INLINE Packet8f preverse(const Packet8f& a)
{
  __m256 tmp = _mm256_shuffle_ps(a,a,0x1b);
  return _mm256_permute2f128_ps(tmp, tmp, 1);
}
template<> EIGEN_STRONG_INLINE Packet4d preverse(const Packet4d& a)
{
   __m256d tmp = _mm256_shuffle_pd(a,a,5);
  return _mm256_permute2f128_pd(tmp, tmp, 1);
  #if 0
  // This version is unlikely to be faster as _mm256_shuffle_ps and _mm256_permute_pd
  // exhibit the same latency/throughput, but it is here for future reference/benchmarking...
  __m256d swap_halves = _mm256_permute2f128_pd(a,a,1);
    return _mm256_permute_pd(swap_halves,5);
  #endif
}
template<> EIGEN_STRONG_INLINE Packet8i preverse(const Packet8i& a)
{
  return _mm256_castps_si256(preverse(_mm256_castsi256_ps(a)));
}

#ifdef EIGEN_VECTORIZE_AVX2
template<> EIGEN_STRONG_INLINE Packet4l preverse(const Packet4l& a)
{
  return _mm256_castpd_si256(preverse(_mm256_castsi256_pd(a)));
}
#endif

// pabs should be ok
template<> EIGEN_STRONG_INLINE Packet8f pabs(const Packet8f& a)
{
  const Packet8f mask = _mm256_castsi256_ps(_mm256_setr_epi32(0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF));
  return _mm256_and_ps(a,mask);
}
template<> EIGEN_STRONG_INLINE Packet4d pabs(const Packet4d& a)
{
  const Packet4d mask = _mm256_castsi256_pd(_mm256_setr_epi32(0xFFFFFFFF,0x7FFFFFFF,0xFFFFFFFF,0x7FFFFFFF,0xFFFFFFFF,0x7FFFFFFF,0xFFFFFFFF,0x7FFFFFFF));
  return _mm256_and_pd(a,mask);
}
template<> EIGEN_STRONG_INLINE Packet8i pabs(const Packet8i& a)
{
#ifdef EIGEN_VECTORIZE_AVX2
  return _mm256_abs_epi32(a);
#else
  __m128i lo = _mm_abs_epi32(_mm256_extractf128_si256(a, 0));
  __m128i hi = _mm_abs_epi32(_mm256_extractf128_si256(a, 1));
  return _mm256_insertf128_si256(_mm256_castsi128_si256(lo), (hi), 1);
#endif
}

template<> EIGEN_STRONG_INLINE Packet8f pfrexp<Packet8f>(const Packet8f& a, Packet8f& exponent) {
  return pfrexp_generic(a,exponent);
}

// Extract exponent without existence of Packet4l.
template<>
EIGEN_STRONG_INLINE  
Packet4d pfrexp_generic_get_biased_exponent(const Packet4d& a) {
  const Packet4d cst_exp_mask  = pset1frombits<Packet4d>(static_cast<uint64_t>(0x7ff0000000000000ull));
  __m256i a_expo = _mm256_castpd_si256(pand(a, cst_exp_mask));
#ifdef EIGEN_VECTORIZE_AVX2
  a_expo = _mm256_srli_epi64(a_expo, 52);
  __m128i lo = _mm256_extractf128_si256(a_expo, 0);
  __m128i hi = _mm256_extractf128_si256(a_expo, 1);
#else
  __m128i lo = _mm256_extractf128_si256(a_expo, 0);
  __m128i hi = _mm256_extractf128_si256(a_expo, 1);
  lo = _mm_srli_epi64(lo, 52);
  hi = _mm_srli_epi64(hi, 52);
#endif
  Packet2d exponent_lo = _mm_cvtepi32_pd(vec4i_swizzle1(lo, 0, 2, 1, 3));
  Packet2d exponent_hi = _mm_cvtepi32_pd(vec4i_swizzle1(hi, 0, 2, 1, 3));
  Packet4d exponent = _mm256_insertf128_pd(_mm256_setzero_pd(), exponent_lo, 0);
  exponent = _mm256_insertf128_pd(exponent, exponent_hi, 1);
  return exponent;
}


template<> EIGEN_STRONG_INLINE Packet4d pfrexp<Packet4d>(const Packet4d& a, Packet4d& exponent) {
  return pfrexp_generic(a, exponent);
}

template<> EIGEN_STRONG_INLINE Packet8f pldexp<Packet8f>(const Packet8f& a, const Packet8f& exponent) {
  return pldexp_generic(a, exponent);
}

template<> EIGEN_STRONG_INLINE Packet4d pldexp<Packet4d>(const Packet4d& a, const Packet4d& exponent) {
  // Clamp exponent to [-2099, 2099]
  const Packet4d max_exponent = pset1<Packet4d>(2099.0);
  const Packet4i e = _mm256_cvtpd_epi32(pmin(pmax(exponent, pnegate(max_exponent)), max_exponent));
  
  // Split 2^e into four factors and multiply.
  const Packet4i bias = pset1<Packet4i>(1023);
  Packet4i b = parithmetic_shift_right<2>(e);  // floor(e/4)
  
  // 2^b
  Packet4i hi = vec4i_swizzle1(padd(b, bias), 0, 2, 1, 3);
  Packet4i lo = _mm_slli_epi64(hi, 52);
  hi = _mm_slli_epi64(_mm_srli_epi64(hi, 32), 52);
  Packet4d c = _mm256_castsi256_pd(_mm256_insertf128_si256(_mm256_castsi128_si256(lo), hi, 1));
  Packet4d out = pmul(pmul(pmul(a, c), c), c);  // a * 2^(3b)
  
  // 2^(e - 3b)
  b = psub(psub(psub(e, b), b), b);  // e - 3b
  hi = vec4i_swizzle1(padd(b, bias), 0, 2, 1, 3);
  lo = _mm_slli_epi64(hi, 52);
  hi = _mm_slli_epi64(_mm_srli_epi64(hi, 32), 52);
  c = _mm256_castsi256_pd(_mm256_insertf128_si256(_mm256_castsi128_si256(lo), hi, 1));
  out = pmul(out, c); // a * 2^e
  return out;
}

template<> EIGEN_STRONG_INLINE float predux<Packet8f>(const Packet8f& a)
{
  return predux(Packet4f(_mm_add_ps(_mm256_castps256_ps128(a),_mm256_extractf128_ps(a,1))));
}
template<> EIGEN_STRONG_INLINE double predux<Packet4d>(const Packet4d& a)
{
  return predux(Packet2d(_mm_add_pd(_mm256_castpd256_pd128(a),_mm256_extractf128_pd(a,1))));
}
template<> EIGEN_STRONG_INLINE int predux<Packet8i>(const Packet8i& a)
{
  return predux(Packet4i(_mm_add_epi32(_mm256_castsi256_si128(a),_mm256_extractf128_si256(a,1))));
}

template<> EIGEN_STRONG_INLINE Packet4f predux_half_dowto4<Packet8f>(const Packet8f& a)
{
  return _mm_add_ps(_mm256_castps256_ps128(a),_mm256_extractf128_ps(a,1));
}
template<> EIGEN_STRONG_INLINE Packet4i predux_half_dowto4<Packet8i>(const Packet8i& a)
{
  return _mm_add_epi32(_mm256_castsi256_si128(a),_mm256_extractf128_si256(a,1));
}

template<> EIGEN_STRONG_INLINE float predux_mul<Packet8f>(const Packet8f& a)
{
  Packet8f tmp;
  tmp = _mm256_mul_ps(a, _mm256_permute2f128_ps(a,a,1));
  tmp = _mm256_mul_ps(tmp, _mm256_shuffle_ps(tmp,tmp,_MM_SHUFFLE(1,0,3,2)));
  return pfirst(_mm256_mul_ps(tmp, _mm256_shuffle_ps(tmp,tmp,1)));
}
template<> EIGEN_STRONG_INLINE double predux_mul<Packet4d>(const Packet4d& a)
{
  Packet4d tmp;
  tmp = _mm256_mul_pd(a, _mm256_permute2f128_pd(a,a,1));
  return pfirst(_mm256_mul_pd(tmp, _mm256_shuffle_pd(tmp,tmp,1)));
}

template<> EIGEN_STRONG_INLINE float predux_min<Packet8f>(const Packet8f& a)
{
  Packet8f tmp = _mm256_min_ps(a, _mm256_permute2f128_ps(a,a,1));
  tmp = _mm256_min_ps(tmp, _mm256_shuffle_ps(tmp,tmp,_MM_SHUFFLE(1,0,3,2)));
  return pfirst(_mm256_min_ps(tmp, _mm256_shuffle_ps(tmp,tmp,1)));
}
template<> EIGEN_STRONG_INLINE double predux_min<Packet4d>(const Packet4d& a)
{
  Packet4d tmp = _mm256_min_pd(a, _mm256_permute2f128_pd(a,a,1));
  return pfirst(_mm256_min_pd(tmp, _mm256_shuffle_pd(tmp, tmp, 1)));
}

template<> EIGEN_STRONG_INLINE float predux_max<Packet8f>(const Packet8f& a)
{
  Packet8f tmp = _mm256_max_ps(a, _mm256_permute2f128_ps(a,a,1));
  tmp = _mm256_max_ps(tmp, _mm256_shuffle_ps(tmp,tmp,_MM_SHUFFLE(1,0,3,2)));
  return pfirst(_mm256_max_ps(tmp, _mm256_shuffle_ps(tmp,tmp,1)));
}

template<> EIGEN_STRONG_INLINE double predux_max<Packet4d>(const Packet4d& a)
{
  Packet4d tmp = _mm256_max_pd(a, _mm256_permute2f128_pd(a,a,1));
  return pfirst(_mm256_max_pd(tmp, _mm256_shuffle_pd(tmp, tmp, 1)));
}

// not needed yet
// template<> EIGEN_STRONG_INLINE bool predux_all(const Packet4f& x)
// {
//   return _mm_movemask_ps(x) == 0xF;
// }

template<> EIGEN_STRONG_INLINE bool predux_any(const Packet4f& x)
{
  return _mm_movemask_ps(x) != 0x0;
}

// not needed yet
// template<> EIGEN_STRONG_INLINE bool predux_all(const Packet8f& x)
// {
//   return _mm256_movemask_ps(x)==0xFF;
// }

template<> EIGEN_STRONG_INLINE bool predux_any(const Packet8f& x)
{
  return _mm256_movemask_ps(x)!=0;
}

EIGEN_DEVICE_FUNC inline void
ptranspose(PacketBlock<Packet4f,4>& kernel) {
  _MM_TRANSPOSE4_PS(kernel.packet[0], kernel.packet[1], kernel.packet[2], kernel.packet[3]);
}

EIGEN_DEVICE_FUNC inline void
ptranspose(PacketBlock<Packet2d,2>& kernel) {
  __m128d tmp = _mm_unpackhi_pd(kernel.packet[0], kernel.packet[1]);
  kernel.packet[0] = _mm_unpacklo_pd(kernel.packet[0], kernel.packet[1]);
  kernel.packet[1] = tmp;
}

EIGEN_DEVICE_FUNC inline void
ptranspose(PacketBlock<Packet4i,4>& kernel) {
  __m128i T0 = _mm_unpacklo_epi32(kernel.packet[0], kernel.packet[1]);
  __m128i T1 = _mm_unpacklo_epi32(kernel.packet[2], kernel.packet[3]);
  __m128i T2 = _mm_unpackhi_epi32(kernel.packet[0], kernel.packet[1]);
  __m128i T3 = _mm_unpackhi_epi32(kernel.packet[2], kernel.packet[3]);

  kernel.packet[0] = _mm_unpacklo_epi64(T0, T1);
  kernel.packet[1] = _mm_unpackhi_epi64(T0, T1);
  kernel.packet[2] = _mm_unpacklo_epi64(T2, T3);
  kernel.packet[3] = _mm_unpackhi_epi64(T2, T3);
}

EIGEN_DEVICE_FUNC inline void
ptranspose(PacketBlock<Packet16b,4>& kernel) {
  __m128i T0 =  _mm_unpacklo_epi8(kernel.packet[0], kernel.packet[1]);
  __m128i T1 =  _mm_unpackhi_epi8(kernel.packet[0], kernel.packet[1]);
  __m128i T2 =  _mm_unpacklo_epi8(kernel.packet[2], kernel.packet[3]);
  __m128i T3 =  _mm_unpackhi_epi8(kernel.packet[2], kernel.packet[3]);
  kernel.packet[0] = _mm_unpacklo_epi16(T0, T2);
  kernel.packet[1] = _mm_unpackhi_epi16(T0, T2);
  kernel.packet[2] = _mm_unpacklo_epi16(T1, T3);
  kernel.packet[3] = _mm_unpackhi_epi16(T1, T3);
}

EIGEN_DEVICE_FUNC inline void
ptranspose(PacketBlock<Packet16b,16>& kernel) {
  // If we number the elements in the input thus:
  // kernel.packet[ 0] = {00, 01, 02, 03, 04, 05, 06, 07, 08, 09, 0a, 0b, 0c, 0d, 0e, 0f}
  // kernel.packet[ 1] = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 1a, 1b, 1c, 1d, 1e, 1f}
  // ...
  // kernel.packet[15] = {f0, f1, f2, f3, f4, f5, f6, f7, f8, f9, fa, fb, fc, fd, fe, ff},
  //
  // the desired output is:
  // kernel.packet[ 0] = {00, 10, 20, 30, 40, 50, 60, 70, 80, 90, a0, b0, c0, d0, e0, f0}
  // kernel.packet[ 1] = {01, 11, 21, 31, 41, 51, 61, 71, 81, 91, a1, b1, c1, d1, e1, f1}
  // ...
  // kernel.packet[15] = {0f, 1f, 2f, 3f, 4f, 5f, 6f, 7f, 8f, 9f, af, bf, cf, df, ef, ff},
  __m128i t0 =  _mm_unpacklo_epi8(kernel.packet[0], kernel.packet[1]); // 00 10 01 11 02 12 03 13 04 14 05 15 06 16 07 17
  __m128i t1 =  _mm_unpackhi_epi8(kernel.packet[0], kernel.packet[1]); // 08 18 09 19 0a 1a 0b 1b 0c 1c 0d 1d 0e 1e 0f 1f
  __m128i t2 =  _mm_unpacklo_epi8(kernel.packet[2], kernel.packet[3]); // 20 30 21 31 22 32 ...                     27 37
  __m128i t3 =  _mm_unpackhi_epi8(kernel.packet[2], kernel.packet[3]); // 28 38 29 39 2a 3a ...                     2f 3f
  __m128i t4 =  _mm_unpacklo_epi8(kernel.packet[4], kernel.packet[5]); // 40 50 41 51 42 52                         47 57
  __m128i t5 =  _mm_unpackhi_epi8(kernel.packet[4], kernel.packet[5]); // 48 58 49 59 4a 5a
  __m128i t6 =  _mm_unpacklo_epi8(kernel.packet[6], kernel.packet[7]);
  __m128i t7 =  _mm_unpackhi_epi8(kernel.packet[6], kernel.packet[7]);
  __m128i t8 =  _mm_unpacklo_epi8(kernel.packet[8], kernel.packet[9]);
  __m128i t9 =  _mm_unpackhi_epi8(kernel.packet[8], kernel.packet[9]);
  __m128i ta =  _mm_unpacklo_epi8(kernel.packet[10], kernel.packet[11]);
  __m128i tb =  _mm_unpackhi_epi8(kernel.packet[10], kernel.packet[11]);
  __m128i tc =  _mm_unpacklo_epi8(kernel.packet[12], kernel.packet[13]);
  __m128i td =  _mm_unpackhi_epi8(kernel.packet[12], kernel.packet[13]);
  __m128i te =  _mm_unpacklo_epi8(kernel.packet[14], kernel.packet[15]);
  __m128i tf =  _mm_unpackhi_epi8(kernel.packet[14], kernel.packet[15]);

  __m128i s0 =  _mm_unpacklo_epi16(t0, t2); // 00 10 20 30 01 11 21 31 02 12 22 32 03 13 23 33
  __m128i s1 =  _mm_unpackhi_epi16(t0, t2); // 04 14 24 34
  __m128i s2 =  _mm_unpacklo_epi16(t1, t3); // 08 18 28 38 ...
  __m128i s3 =  _mm_unpackhi_epi16(t1, t3); // 0c 1c 2c 3c ...
  __m128i s4 =  _mm_unpacklo_epi16(t4, t6); // 40 50 60 70 41 51 61 71 42 52 62 72 43 53 63 73
  __m128i s5 =  _mm_unpackhi_epi16(t4, t6); // 44 54 64 74 ...
  __m128i s6 =  _mm_unpacklo_epi16(t5, t7);
  __m128i s7 =  _mm_unpackhi_epi16(t5, t7);
  __m128i s8 =  _mm_unpacklo_epi16(t8, ta);
  __m128i s9 =  _mm_unpackhi_epi16(t8, ta);
  __m128i sa =  _mm_unpacklo_epi16(t9, tb);
  __m128i sb =  _mm_unpackhi_epi16(t9, tb);
  __m128i sc =  _mm_unpacklo_epi16(tc, te);
  __m128i sd =  _mm_unpackhi_epi16(tc, te);
  __m128i se =  _mm_unpacklo_epi16(td, tf);
  __m128i sf =  _mm_unpackhi_epi16(td, tf);

  __m128i u0 =  _mm_unpacklo_epi32(s0, s4); // 00 10 20 30 40 50 60 70 01 11 21 31 41 51 61 71
  __m128i u1 =  _mm_unpackhi_epi32(s0, s4); // 02 12 22 32 42 52 62 72 03 13 23 33 43 53 63 73
  __m128i u2 =  _mm_unpacklo_epi32(s1, s5);
  __m128i u3 =  _mm_unpackhi_epi32(s1, s5);
  __m128i u4 =  _mm_unpacklo_epi32(s2, s6);
  __m128i u5 =  _mm_unpackhi_epi32(s2, s6);
  __m128i u6 =  _mm_unpacklo_epi32(s3, s7);
  __m128i u7 =  _mm_unpackhi_epi32(s3, s7);
  __m128i u8 =  _mm_unpacklo_epi32(s8, sc);
  __m128i u9 =  _mm_unpackhi_epi32(s8, sc);
  __m128i ua =  _mm_unpacklo_epi32(s9, sd);
  __m128i ub =  _mm_unpackhi_epi32(s9, sd);
  __m128i uc =  _mm_unpacklo_epi32(sa, se);
  __m128i ud =  _mm_unpackhi_epi32(sa, se);
  __m128i ue =  _mm_unpacklo_epi32(sb, sf);
  __m128i uf =  _mm_unpackhi_epi32(sb, sf);

  kernel.packet[0]  = _mm_unpacklo_epi64(u0, u8);
  kernel.packet[1]  = _mm_unpackhi_epi64(u0, u8);
  kernel.packet[2]  = _mm_unpacklo_epi64(u1, u9);
  kernel.packet[3]  = _mm_unpackhi_epi64(u1, u9);
  kernel.packet[4]  = _mm_unpacklo_epi64(u2, ua);
  kernel.packet[5]  = _mm_unpackhi_epi64(u2, ua);
  kernel.packet[6]  = _mm_unpacklo_epi64(u3, ub);
  kernel.packet[7]  = _mm_unpackhi_epi64(u3, ub);
  kernel.packet[8]  = _mm_unpacklo_epi64(u4, uc);
  kernel.packet[9]  = _mm_unpackhi_epi64(u4, uc);
  kernel.packet[10] = _mm_unpacklo_epi64(u5, ud);
  kernel.packet[11] = _mm_unpackhi_epi64(u5, ud);
  kernel.packet[12] = _mm_unpacklo_epi64(u6, ue);
  kernel.packet[13] = _mm_unpackhi_epi64(u6, ue);
  kernel.packet[14] = _mm_unpacklo_epi64(u7, uf);
  kernel.packet[15] = _mm_unpackhi_epi64(u7, uf);
}

EIGEN_DEVICE_FUNC inline void
ptranspose(PacketBlock<Packet8f,8>& kernel) {
  __m256 T0 = _mm256_unpacklo_ps(kernel.packet[0], kernel.packet[1]);
  __m256 T1 = _mm256_unpackhi_ps(kernel.packet[0], kernel.packet[1]);
  __m256 T2 = _mm256_unpacklo_ps(kernel.packet[2], kernel.packet[3]);
  __m256 T3 = _mm256_unpackhi_ps(kernel.packet[2], kernel.packet[3]);
  __m256 T4 = _mm256_unpacklo_ps(kernel.packet[4], kernel.packet[5]);
  __m256 T5 = _mm256_unpackhi_ps(kernel.packet[4], kernel.packet[5]);
  __m256 T6 = _mm256_unpacklo_ps(kernel.packet[6], kernel.packet[7]);
  __m256 T7 = _mm256_unpackhi_ps(kernel.packet[6], kernel.packet[7]);
  __m256 S0 = _mm256_shuffle_ps(T0,T2,_MM_SHUFFLE(1,0,1,0));
  __m256 S1 = _mm256_shuffle_ps(T0,T2,_MM_SHUFFLE(3,2,3,2));
  __m256 S2 = _mm256_shuffle_ps(T1,T3,_MM_SHUFFLE(1,0,1,0));
  __m256 S3 = _mm256_shuffle_ps(T1,T3,_MM_SHUFFLE(3,2,3,2));
  __m256 S4 = _mm256_shuffle_ps(T4,T6,_MM_SHUFFLE(1,0,1,0));
  __m256 S5 = _mm256_shuffle_ps(T4,T6,_MM_SHUFFLE(3,2,3,2));
  __m256 S6 = _mm256_shuffle_ps(T5,T7,_MM_SHUFFLE(1,0,1,0));
  __m256 S7 = _mm256_shuffle_ps(T5,T7,_MM_SHUFFLE(3,2,3,2));
  kernel.packet[0] = _mm256_permute2f128_ps(S0, S4, 0x20);
  kernel.packet[1] = _mm256_permute2f128_ps(S1, S5, 0x20);
  kernel.packet[2] = _mm256_permute2f128_ps(S2, S6, 0x20);
  kernel.packet[3] = _mm256_permute2f128_ps(S3, S7, 0x20);
  kernel.packet[4] = _mm256_permute2f128_ps(S0, S4, 0x31);
  kernel.packet[5] = _mm256_permute2f128_ps(S1, S5, 0x31);
  kernel.packet[6] = _mm256_permute2f128_ps(S2, S6, 0x31);
  kernel.packet[7] = _mm256_permute2f128_ps(S3, S7, 0x31);
}

EIGEN_DEVICE_FUNC inline void
ptranspose(PacketBlock<Packet8f,4>& kernel) {
  __m256 T0 = _mm256_unpacklo_ps(kernel.packet[0], kernel.packet[1]);
  __m256 T1 = _mm256_unpackhi_ps(kernel.packet[0], kernel.packet[1]);
  __m256 T2 = _mm256_unpacklo_ps(kernel.packet[2], kernel.packet[3]);
  __m256 T3 = _mm256_unpackhi_ps(kernel.packet[2], kernel.packet[3]);

  __m256 S0 = _mm256_shuffle_ps(T0,T2,_MM_SHUFFLE(1,0,1,0));
  __m256 S1 = _mm256_shuffle_ps(T0,T2,_MM_SHUFFLE(3,2,3,2));
  __m256 S2 = _mm256_shuffle_ps(T1,T3,_MM_SHUFFLE(1,0,1,0));
  __m256 S3 = _mm256_shuffle_ps(T1,T3,_MM_SHUFFLE(3,2,3,2));

  kernel.packet[0] = _mm256_permute2f128_ps(S0, S1, 0x20);
  kernel.packet[1] = _mm256_permute2f128_ps(S2, S3, 0x20);
  kernel.packet[2] = _mm256_permute2f128_ps(S0, S1, 0x31);
  kernel.packet[3] = _mm256_permute2f128_ps(S2, S3, 0x31);
}

#define MM256_SHUFFLE_EPI32(A, B, M) \
  _mm256_castps_si256(_mm256_shuffle_ps(_mm256_castsi256_ps(A), _mm256_castsi256_ps(B), M))

#ifndef EIGEN_VECTORIZE_AVX2
#define MM256_UNPACKLO_EPI32(A, B) \
  _mm256_castps_si256(_mm256_unpacklo_ps(_mm256_castsi256_ps(A), _mm256_castsi256_ps(B)))
#define MM256_UNPACKHI_EPI32(A, B) \
  _mm256_castps_si256(_mm256_unpackhi_ps(_mm256_castsi256_ps(A), _mm256_castsi256_ps(B)))
#else
#define MM256_UNPACKLO_EPI32(A, B) _mm256_unpacklo_epi32(A, B)
#define MM256_UNPACKHI_EPI32(A, B) _mm256_unpackhi_epi32(A, B)
#endif


EIGEN_DEVICE_FUNC inline void
ptranspose(PacketBlock<Packet8i,8>& kernel) {
  __m256i T0 = MM256_UNPACKLO_EPI32(kernel.packet[0], kernel.packet[1]);
  __m256i T1 = MM256_UNPACKHI_EPI32(kernel.packet[0], kernel.packet[1]);
  __m256i T2 = MM256_UNPACKLO_EPI32(kernel.packet[2], kernel.packet[3]);
  __m256i T3 = MM256_UNPACKHI_EPI32(kernel.packet[2], kernel.packet[3]);
  __m256i T4 = MM256_UNPACKLO_EPI32(kernel.packet[4], kernel.packet[5]);
  __m256i T5 = MM256_UNPACKHI_EPI32(kernel.packet[4], kernel.packet[5]);
  __m256i T6 = MM256_UNPACKLO_EPI32(kernel.packet[6], kernel.packet[7]);
  __m256i T7 = MM256_UNPACKHI_EPI32(kernel.packet[6], kernel.packet[7]);
  __m256i S0 = MM256_SHUFFLE_EPI32(T0,T2,_MM_SHUFFLE(1,0,1,0));
  __m256i S1 = MM256_SHUFFLE_EPI32(T0,T2,_MM_SHUFFLE(3,2,3,2));
  __m256i S2 = MM256_SHUFFLE_EPI32(T1,T3,_MM_SHUFFLE(1,0,1,0));
  __m256i S3 = MM256_SHUFFLE_EPI32(T1,T3,_MM_SHUFFLE(3,2,3,2));
  __m256i S4 = MM256_SHUFFLE_EPI32(T4,T6,_MM_SHUFFLE(1,0,1,0));
  __m256i S5 = MM256_SHUFFLE_EPI32(T4,T6,_MM_SHUFFLE(3,2,3,2));
  __m256i S6 = MM256_SHUFFLE_EPI32(T5,T7,_MM_SHUFFLE(1,0,1,0));
  __m256i S7 = MM256_SHUFFLE_EPI32(T5,T7,_MM_SHUFFLE(3,2,3,2));
  kernel.packet[0] = _mm256_permute2f128_si256(S0, S4, 0x20);
  kernel.packet[1] = _mm256_permute2f128_si256(S1, S5, 0x20);
  kernel.packet[2] = _mm256_permute2f128_si256(S2, S6, 0x20);
  kernel.packet[3] = _mm256_permute2f128_si256(S3, S7, 0x20);
  kernel.packet[4] = _mm256_permute2f128_si256(S0, S4, 0x31);
  kernel.packet[5] = _mm256_permute2f128_si256(S1, S5, 0x31);
  kernel.packet[6] = _mm256_permute2f128_si256(S2, S6, 0x31);
  kernel.packet[7] = _mm256_permute2f128_si256(S3, S7, 0x31);
}

EIGEN_DEVICE_FUNC inline void
ptranspose(PacketBlock<Packet8i,4>& kernel) {
  __m256i T0 = MM256_UNPACKLO_EPI32(kernel.packet[0], kernel.packet[1]);
  __m256i T1 = MM256_UNPACKHI_EPI32(kernel.packet[0], kernel.packet[1]);
  __m256i T2 = MM256_UNPACKLO_EPI32(kernel.packet[2], kernel.packet[3]);
  __m256i T3 = MM256_UNPACKHI_EPI32(kernel.packet[2], kernel.packet[3]);

  __m256i S0 = MM256_SHUFFLE_EPI32(T0,T2,_MM_SHUFFLE(1,0,1,0));
  __m256i S1 = MM256_SHUFFLE_EPI32(T0,T2,_MM_SHUFFLE(3,2,3,2));
  __m256i S2 = MM256_SHUFFLE_EPI32(T1,T3,_MM_SHUFFLE(1,0,1,0));
  __m256i S3 = MM256_SHUFFLE_EPI32(T1,T3,_MM_SHUFFLE(3,2,3,2));

  kernel.packet[0] = _mm256_permute2f128_si256(S0, S1, 0x20);
  kernel.packet[1] = _mm256_permute2f128_si256(S2, S3, 0x20);
  kernel.packet[2] = _mm256_permute2f128_si256(S0, S1, 0x31);
  kernel.packet[3] = _mm256_permute2f128_si256(S2, S3, 0x31);
}

EIGEN_DEVICE_FUNC inline void
ptranspose(PacketBlock<Packet4d,4>& kernel) {
  __m256d T0 = _mm256_shuffle_pd(kernel.packet[0], kernel.packet[1], 15);
  __m256d T1 = _mm256_shuffle_pd(kernel.packet[0], kernel.packet[1], 0);
  __m256d T2 = _mm256_shuffle_pd(kernel.packet[2], kernel.packet[3], 15);
  __m256d T3 = _mm256_shuffle_pd(kernel.packet[2], kernel.packet[3], 0);

  kernel.packet[1] = _mm256_permute2f128_pd(T0, T2, 32);
  kernel.packet[3] = _mm256_permute2f128_pd(T0, T2, 49);
  kernel.packet[0] = _mm256_permute2f128_pd(T1, T3, 32);
  kernel.packet[2] = _mm256_permute2f128_pd(T1, T3, 49);
}

template<> EIGEN_STRONG_INLINE Packet4i pblend(const Selector<4>& ifPacket, const Packet4i& thenPacket, const Packet4i& elsePacket) {
  const __m128i zero = _mm_setzero_si128();
  const __m128i select = _mm_set_epi32(ifPacket.select[3], ifPacket.select[2], ifPacket.select[1], ifPacket.select[0]);
  __m128i false_mask = _mm_cmpeq_epi32(select, zero);
#ifdef EIGEN_VECTORIZE_SSE4_1
  return _mm_blendv_epi8(thenPacket, elsePacket, false_mask);
#else
  return _mm_or_si128(_mm_andnot_si128(false_mask, thenPacket), _mm_and_si128(false_mask, elsePacket));
#endif
}
template<> EIGEN_STRONG_INLINE Packet4f pblend(const Selector<4>& ifPacket, const Packet4f& thenPacket, const Packet4f& elsePacket) {
  const __m128 zero = _mm_setzero_ps();
  const __m128 select = _mm_set_ps(ifPacket.select[3], ifPacket.select[2], ifPacket.select[1], ifPacket.select[0]);
  __m128 false_mask = _mm_cmpeq_ps(select, zero);
#ifdef EIGEN_VECTORIZE_SSE4_1
  return _mm_blendv_ps(thenPacket, elsePacket, false_mask);
#else
  return _mm_or_ps(_mm_andnot_ps(false_mask, thenPacket), _mm_and_ps(false_mask, elsePacket));
#endif
}
template<> EIGEN_STRONG_INLINE Packet2d pblend(const Selector<2>& ifPacket, const Packet2d& thenPacket, const Packet2d& elsePacket) {
  const __m128d zero = _mm_setzero_pd();
  const __m128d select = _mm_set_pd(ifPacket.select[1], ifPacket.select[0]);
  __m128d false_mask = _mm_cmpeq_pd(select, zero);
#ifdef EIGEN_VECTORIZE_SSE4_1
  return _mm_blendv_pd(thenPacket, elsePacket, false_mask);
#else
  return _mm_or_pd(_mm_andnot_pd(false_mask, thenPacket), _mm_and_pd(false_mask, elsePacket));
#endif
}

template<> EIGEN_STRONG_INLINE Packet8f pblend(const Selector<8>& ifPacket, const Packet8f& thenPacket, const Packet8f& elsePacket) {
  const __m256 zero = _mm256_setzero_ps();
  const __m256 select = _mm256_set_ps(ifPacket.select[7], ifPacket.select[6], ifPacket.select[5], ifPacket.select[4], ifPacket.select[3], ifPacket.select[2], ifPacket.select[1], ifPacket.select[0]);
  __m256 false_mask = _mm256_cmp_ps(select, zero, _CMP_EQ_UQ);
  return _mm256_blendv_ps(thenPacket, elsePacket, false_mask);
}
template<> EIGEN_STRONG_INLINE Packet4d pblend(const Selector<4>& ifPacket, const Packet4d& thenPacket, const Packet4d& elsePacket) {
  const __m256d zero = _mm256_setzero_pd();
  const __m256d select = _mm256_set_pd(ifPacket.select[3], ifPacket.select[2], ifPacket.select[1], ifPacket.select[0]);
  __m256d false_mask = _mm256_cmp_pd(select, zero, _CMP_EQ_UQ);
  return _mm256_blendv_pd(thenPacket, elsePacket, false_mask);
}

// Scalar path for pmadd with FMA to ensure consistency with vectorized path.
#ifdef EIGEN_VECTORIZE_FMA
template<> EIGEN_STRONG_INLINE float pmadd(const float& a, const float& b, const float& c) {
  return ::fmaf(a,b,c);
}
template<> EIGEN_STRONG_INLINE double pmadd(const double& a, const double& b, const double& c) {
  return ::fma(a,b,c);
}
template<> EIGEN_STRONG_INLINE float pmsub(const float& a, const float& b, const float& c) {
  return ::fmaf(a,b,-c);
}
template<> EIGEN_STRONG_INLINE double pmsub(const double& a, const double& b, const double& c) {
  return ::fma(a,b,-c);
}
template<> EIGEN_STRONG_INLINE float pnmadd(const float& a, const float& b, const float& c) {
  return ::fmaf(-a,b,c);
}
template<> EIGEN_STRONG_INLINE double pnmadd(const double& a, const double& b, const double& c) {
  return ::fma(-a,b,c);
}
template<> EIGEN_STRONG_INLINE float pnmsub(const float& a, const float& b, const float& c) {
  return ::fmaf(-a,b,-c);
}
template<> EIGEN_STRONG_INLINE double pnmsub(const double& a, const double& b, const double& c) {
  return ::fma(-a,b,-c);
}
#endif

// #ifdef EIGEN_VECTORIZE_SSE4_1
// Helpers for half->float and float->half conversions.
// Currently only used by the AVX code.
EIGEN_STRONG_INLINE __m128i half2floatsse(__m128i h) {
 __m128i input = _mm_cvtepu16_epi32(h);

  // Direct vectorization of half_to_float, C parts in the comments.
  __m128i shifted_exp = _mm_set1_epi32(0x7c00 << 13);
  // o.u = (h.x & 0x7fff) << 13; // exponent/mantissa bits
  __m128i ou = _mm_slli_epi32(_mm_and_si128(input, _mm_set1_epi32(0x7fff)), 13);
  // exp = shifted_exp & o.u;   // just the exponent
  __m128i exp = _mm_and_si128(ou, shifted_exp);
  // o.u += (127 - 15) << 23;
  ou = _mm_add_epi32(ou, _mm_set1_epi32((127 - 15) << 23));

  // Inf/NaN?
  __m128i naninf_mask = _mm_cmpeq_epi32(exp, shifted_exp);
  // Inf/NaN adjust
  __m128i naninf_adj =
      _mm_and_si128(_mm_set1_epi32((128 - 16) << 23), naninf_mask);
  // extra exp adjust for  Inf/NaN
  ou = _mm_add_epi32(ou, naninf_adj);

  // Zero/Denormal?
  __m128i zeroden_mask = _mm_cmpeq_epi32(exp, _mm_setzero_si128());
  __m128i zeroden_adj = _mm_and_si128(zeroden_mask, _mm_set1_epi32(1 << 23));
  // o.u += 1 << 23;
  ou = _mm_add_epi32(ou, zeroden_adj);
  // magic.u = 113 << 23
  __m128i magic = _mm_and_si128(zeroden_mask, _mm_set1_epi32(113 << 23));
  // o.f -= magic.f
  ou = _mm_castps_si128(
      _mm_sub_ps(_mm_castsi128_ps(ou), _mm_castsi128_ps(magic)));

  __m128i sign =
      _mm_slli_epi32(_mm_and_si128(input, _mm_set1_epi32(0x8000)), 16);
  // o.u |= (h.x & 0x8000) << 16;    // sign bit
  ou = _mm_or_si128(ou, sign);
  // return o.f;
  // We are actually returning uint version, to make
  // _mm256_insertf128_si256 work.
  return ou;
}

EIGEN_STRONG_INLINE __m128i float2half(__m128 f) {
  __m128i o = _mm_setzero_si128();

  // unsigned int sign_mask = 0x80000000u;
  __m128i sign = _mm_set1_epi32(0x80000000u);
  // unsigned int sign = f.u & sign_mask;
  sign = _mm_and_si128(sign, _mm_castps_si128(f));
  // f.u ^= sign;
  f = _mm_xor_ps(f, _mm_castsi128_ps(sign));

  __m128i fu = _mm_castps_si128(f);

  __m128i f16max = _mm_set1_epi32((127 + 16) << 23);
  __m128i f32infty = _mm_set1_epi32(255 << 23);
  // if (f.u >= f16max.u) // result is Inf or NaN (all exponent bits set)
  // there is no _mm_cmpge_epi32, so use lt and swap operands
  __m128i infnan_mask = _mm_cmplt_epi32(f16max, _mm_castps_si128(f));
  __m128i inf_mask = _mm_cmpgt_epi32(_mm_castps_si128(f), f32infty);
  __m128i nan_mask = _mm_andnot_si128(inf_mask, infnan_mask);
  __m128i inf_value = _mm_and_si128(inf_mask, _mm_set1_epi32(0x7e00));
  __m128i nan_value = _mm_and_si128(nan_mask, _mm_set1_epi32(0x7c00));
  // o.x = (f.u > f32infty.u) ? 0x7e00 : 0x7c00; // NaN->qNaN and Inf->Inf
  __m128i naninf_value = _mm_or_si128(inf_value, nan_value);

  __m128i denorm_magic = _mm_set1_epi32(((127 - 15) + (23 - 10) + 1) << 23);
  __m128i subnorm_mask =
      _mm_cmplt_epi32(_mm_castps_si128(f), _mm_set1_epi32(113 << 23));
  //  f.f += denorm_magic.f;
  f = _mm_add_ps(f, _mm_castsi128_ps(denorm_magic));
  // f.u - denorm_magic.u
  o = _mm_sub_epi32(_mm_castps_si128(f), denorm_magic);
  o = _mm_and_si128(o, subnorm_mask);
  // Correct result for inf/nan/zero/subnormal, 0 otherwise
  o = _mm_or_si128(o, naninf_value);

  __m128i mask = _mm_or_si128(infnan_mask, subnorm_mask);
  o = _mm_and_si128(o, mask);

  // mant_odd = (f.u >> 13) & 1;
  __m128i mand_odd = _mm_and_si128(_mm_srli_epi32(fu, 13), _mm_set1_epi32(0x1));
  // f.u += 0xc8000fffU;
  fu = _mm_add_epi32(fu, _mm_set1_epi32(0xc8000fffU));
  // f.u += mant_odd;
  fu = _mm_add_epi32(fu, mand_odd);
  fu = _mm_andnot_si128(mask, fu);
  // f.u >> 13
  fu = _mm_srli_epi32(fu, 13);
  o = _mm_or_si128(fu, o);

  // o.x |= static_cast<numext::uint16_t>(sign >> 16);
  o = _mm_or_si128(o, _mm_srli_epi32(sign, 16));

  // 16 bit values
  return _mm_and_si128(o, _mm_set1_epi32(0xffff));
}
// #endif

// Packet math for Eigen::half

template<> struct unpacket_traits<Packet8h> { typedef Eigen::half type; enum {size=8, alignment=Aligned16, vectorizable=true, masked_load_available=false, masked_store_available=false}; typedef Packet8h half; };

template<> EIGEN_STRONG_INLINE Packet8h pset1<Packet8h>(const Eigen::half& from) {
  return _mm_set1_epi16(numext::bit_cast<numext::uint16_t>(from));
}

template<> EIGEN_STRONG_INLINE Eigen::half pfirst<Packet8h>(const Packet8h& from) {
  return numext::bit_cast<Eigen::half>(static_cast<numext::uint16_t>(_mm_extract_epi16(from, 0)));
}

template<> EIGEN_STRONG_INLINE Packet8h pload<Packet8h>(const Eigen::half* from) {
  return _mm_load_si128(reinterpret_cast<const __m128i*>(from));
}

template<> EIGEN_STRONG_INLINE Packet8h ploadu<Packet8h>(const Eigen::half* from) {
  return _mm_loadu_si128(reinterpret_cast<const __m128i*>(from));
}

template<> EIGEN_STRONG_INLINE void pstore<Eigen::half>(Eigen::half* to, const Packet8h& from) {
  _mm_store_si128(reinterpret_cast<__m128i*>(to), from);
}

template<> EIGEN_STRONG_INLINE void pstoreu<Eigen::half>(Eigen::half* to, const Packet8h& from) {
  _mm_storeu_si128(reinterpret_cast<__m128i*>(to), from);
}

template<> EIGEN_STRONG_INLINE Packet8h
ploaddup<Packet8h>(const Eigen::half*  from) {
  const numext::uint16_t a = numext::bit_cast<numext::uint16_t>(from[0]);
  const numext::uint16_t b = numext::bit_cast<numext::uint16_t>(from[1]);
  const numext::uint16_t c = numext::bit_cast<numext::uint16_t>(from[2]);
  const numext::uint16_t d = numext::bit_cast<numext::uint16_t>(from[3]);
  return _mm_set_epi16(d, d, c, c, b, b, a, a);
}

template<> EIGEN_STRONG_INLINE Packet8h
ploadquad<Packet8h>(const Eigen::half* from) {
  const numext::uint16_t a = numext::bit_cast<numext::uint16_t>(from[0]);
  const numext::uint16_t b = numext::bit_cast<numext::uint16_t>(from[1]);
  return _mm_set_epi16(b, b, b, b, a, a, a, a);
}

template<> EIGEN_STRONG_INLINE Packet8h ptrue(const Packet8h& a) {
 return _mm_cmpeq_epi32(a, a);
}

template <>
EIGEN_STRONG_INLINE Packet8h pabs(const Packet8h& a) {
  const __m128i sign_mask = _mm_set1_epi16(static_cast<numext::uint16_t>(0x8000));
  return _mm_andnot_si128(sign_mask, a);
}

EIGEN_STRONG_INLINE Packet8f half2float(const Packet8h& a) {
#ifdef EIGEN_HAS_FP16_C
  return _mm256_cvtph_ps(a);
#else
  Eigen::internal::Packet8f pp = _mm256_castsi256_ps(_mm256_insertf128_si256(
      _mm256_castsi128_si256(half2floatsse(a)), half2floatsse(_mm_srli_si128(a, 8)), 1));
  return pp;
#endif
}

EIGEN_STRONG_INLINE Packet8h float2half(const Packet8f& a) {
#ifdef EIGEN_HAS_FP16_C
  return _mm256_cvtps_ph(a, _MM_FROUND_TO_NEAREST_INT|_MM_FROUND_NO_EXC);
#else
  __m128i lo = float2half(_mm256_extractf128_ps(a, 0));
  __m128i hi = float2half(_mm256_extractf128_ps(a, 1));
  return   _mm_packus_epi32(lo, hi);
#endif
}

template <>
EIGEN_STRONG_INLINE Packet8h pmin<Packet8h>(const Packet8h& a,
                                            const Packet8h& b) {
  return float2half(pmin<Packet8f>(half2float(a), half2float(b)));
}

template <>
EIGEN_STRONG_INLINE Packet8h pmax<Packet8h>(const Packet8h& a,
                                            const Packet8h& b) {
  return float2half(pmax<Packet8f>(half2float(a), half2float(b)));
}

template <>
EIGEN_STRONG_INLINE Packet8h plset<Packet8h>(const half& a) {
  return float2half(plset<Packet8f>(static_cast<float>(a)));
}

template<> EIGEN_STRONG_INLINE Packet8h por(const Packet8h& a,const Packet8h& b) {
  // in some cases Packet4i is a wrapper around __m128i, so we either need to
  // cast to Packet4i to directly call the intrinsics as below:
  return _mm_or_si128(a,b);
}
template<> EIGEN_STRONG_INLINE Packet8h pxor(const Packet8h& a,const Packet8h& b) {
  return _mm_xor_si128(a,b);
}
template<> EIGEN_STRONG_INLINE Packet8h pand(const Packet8h& a,const Packet8h& b) {
  return _mm_and_si128(a,b);
}
template<> EIGEN_STRONG_INLINE Packet8h pandnot(const Packet8h& a,const Packet8h& b) {
  return _mm_andnot_si128(b,a);
}

template<> EIGEN_STRONG_INLINE Packet8h pselect(const Packet8h& mask, const Packet8h& a, const Packet8h& b) {
  return _mm_blendv_epi8(b, a, mask);
}

template<> EIGEN_STRONG_INLINE Packet8h pround<Packet8h>(const Packet8h& a) {
  return float2half(pround<Packet8f>(half2float(a)));
}

template<> EIGEN_STRONG_INLINE Packet8h print<Packet8h>(const Packet8h& a) {
  return float2half(print<Packet8f>(half2float(a)));
}

template<> EIGEN_STRONG_INLINE Packet8h pceil<Packet8h>(const Packet8h& a) {
  return float2half(pceil<Packet8f>(half2float(a)));
}

template<> EIGEN_STRONG_INLINE Packet8h pfloor<Packet8h>(const Packet8h& a) {
  return float2half(pfloor<Packet8f>(half2float(a)));
}

template<> EIGEN_STRONG_INLINE Packet8h pcmp_eq(const Packet8h& a,const Packet8h& b) {
  return Pack16To8(pcmp_eq(half2float(a), half2float(b)));
}

template<> EIGEN_STRONG_INLINE Packet8h pcmp_le(const Packet8h& a,const Packet8h& b) {
  return Pack16To8(pcmp_le(half2float(a), half2float(b)));
}

template<> EIGEN_STRONG_INLINE Packet8h pcmp_lt(const Packet8h& a,const Packet8h& b) {
  return Pack16To8(pcmp_lt(half2float(a), half2float(b)));
}

template<> EIGEN_STRONG_INLINE Packet8h pcmp_lt_or_nan(const Packet8h& a,const Packet8h& b) {
  return Pack16To8(pcmp_lt_or_nan(half2float(a), half2float(b)));
}

template<> EIGEN_STRONG_INLINE Packet8h pconj(const Packet8h& a) { return a; }

template<> EIGEN_STRONG_INLINE Packet8h pnegate(const Packet8h& a) {
  Packet8h sign_mask = _mm_set1_epi16(static_cast<numext::uint16_t>(0x8000));
  return _mm_xor_si128(a, sign_mask);
}

template<> EIGEN_STRONG_INLINE Packet8h padd<Packet8h>(const Packet8h& a, const Packet8h& b) {
  Packet8f af = half2float(a);
  Packet8f bf = half2float(b);
  Packet8f rf = padd(af, bf);
  return float2half(rf);
}

template<> EIGEN_STRONG_INLINE Packet8h psub<Packet8h>(const Packet8h& a, const Packet8h& b) {
  Packet8f af = half2float(a);
  Packet8f bf = half2float(b);
  Packet8f rf = psub(af, bf);
  return float2half(rf);
}

template<> EIGEN_STRONG_INLINE Packet8h pmul<Packet8h>(const Packet8h& a, const Packet8h& b) {
  Packet8f af = half2float(a);
  Packet8f bf = half2float(b);
  Packet8f rf = pmul(af, bf);
  return float2half(rf);
}

template<> EIGEN_STRONG_INLINE Packet8h pdiv<Packet8h>(const Packet8h& a, const Packet8h& b) {
  Packet8f af = half2float(a);
  Packet8f bf = half2float(b);
  Packet8f rf = pdiv(af, bf);
  return float2half(rf);
}

template<> EIGEN_STRONG_INLINE Packet8h pgather<Eigen::half, Packet8h>(const Eigen::half* from, Index stride)
{
  const numext::uint16_t s0 = numext::bit_cast<numext::uint16_t>(from[0*stride]);
  const numext::uint16_t s1 = numext::bit_cast<numext::uint16_t>(from[1*stride]);
  const numext::uint16_t s2 = numext::bit_cast<numext::uint16_t>(from[2*stride]);
  const numext::uint16_t s3 = numext::bit_cast<numext::uint16_t>(from[3*stride]);
  const numext::uint16_t s4 = numext::bit_cast<numext::uint16_t>(from[4*stride]);
  const numext::uint16_t s5 = numext::bit_cast<numext::uint16_t>(from[5*stride]);
  const numext::uint16_t s6 = numext::bit_cast<numext::uint16_t>(from[6*stride]);
  const numext::uint16_t s7 = numext::bit_cast<numext::uint16_t>(from[7*stride]);
  return _mm_set_epi16(s7, s6, s5, s4, s3, s2, s1, s0);
}

template<> EIGEN_STRONG_INLINE void pscatter<Eigen::half, Packet8h>(Eigen::half* to, const Packet8h& from, Index stride)
{
  EIGEN_ALIGN32 Eigen::half aux[8];
  pstore(aux, from);
  to[stride*0] = aux[0];
  to[stride*1] = aux[1];
  to[stride*2] = aux[2];
  to[stride*3] = aux[3];
  to[stride*4] = aux[4];
  to[stride*5] = aux[5];
  to[stride*6] = aux[6];
  to[stride*7] = aux[7];
}

template<> EIGEN_STRONG_INLINE Eigen::half predux<Packet8h>(const Packet8h& a) {
  Packet8f af = half2float(a);
  float reduced = predux<Packet8f>(af);
  return Eigen::half(reduced);
}

template<> EIGEN_STRONG_INLINE Eigen::half predux_max<Packet8h>(const Packet8h& a) {
  Packet8f af = half2float(a);
  float reduced = predux_max<Packet8f>(af);
  return Eigen::half(reduced);
}

template<> EIGEN_STRONG_INLINE Eigen::half predux_min<Packet8h>(const Packet8h& a) {
  Packet8f af = half2float(a);
  float reduced = predux_min<Packet8f>(af);
  return Eigen::half(reduced);
}

template<> EIGEN_STRONG_INLINE Eigen::half predux_mul<Packet8h>(const Packet8h& a) {
  Packet8f af = half2float(a);
  float reduced = predux_mul<Packet8f>(af);
  return Eigen::half(reduced);
}

template<> EIGEN_STRONG_INLINE Packet8h preverse(const Packet8h& a)
{
  __m128i m = _mm_setr_epi8(14,15,12,13,10,11,8,9,6,7,4,5,2,3,0,1);
  return _mm_shuffle_epi8(a,m);
}

EIGEN_STRONG_INLINE void
ptranspose(PacketBlock<Packet8h,8>& kernel) {
  __m128i a = kernel.packet[0];
  __m128i b = kernel.packet[1];
  __m128i c = kernel.packet[2];
  __m128i d = kernel.packet[3];
  __m128i e = kernel.packet[4];
  __m128i f = kernel.packet[5];
  __m128i g = kernel.packet[6];
  __m128i h = kernel.packet[7];

  __m128i a03b03 = _mm_unpacklo_epi16(a, b);
  __m128i c03d03 = _mm_unpacklo_epi16(c, d);
  __m128i e03f03 = _mm_unpacklo_epi16(e, f);
  __m128i g03h03 = _mm_unpacklo_epi16(g, h);
  __m128i a47b47 = _mm_unpackhi_epi16(a, b);
  __m128i c47d47 = _mm_unpackhi_epi16(c, d);
  __m128i e47f47 = _mm_unpackhi_epi16(e, f);
  __m128i g47h47 = _mm_unpackhi_epi16(g, h);

  __m128i a01b01c01d01 = _mm_unpacklo_epi32(a03b03, c03d03);
  __m128i a23b23c23d23 = _mm_unpackhi_epi32(a03b03, c03d03);
  __m128i e01f01g01h01 = _mm_unpacklo_epi32(e03f03, g03h03);
  __m128i e23f23g23h23 = _mm_unpackhi_epi32(e03f03, g03h03);
  __m128i a45b45c45d45 = _mm_unpacklo_epi32(a47b47, c47d47);
  __m128i a67b67c67d67 = _mm_unpackhi_epi32(a47b47, c47d47);
  __m128i e45f45g45h45 = _mm_unpacklo_epi32(e47f47, g47h47);
  __m128i e67f67g67h67 = _mm_unpackhi_epi32(e47f47, g47h47);

  __m128i a0b0c0d0e0f0g0h0 = _mm_unpacklo_epi64(a01b01c01d01, e01f01g01h01);
  __m128i a1b1c1d1e1f1g1h1 = _mm_unpackhi_epi64(a01b01c01d01, e01f01g01h01);
  __m128i a2b2c2d2e2f2g2h2 = _mm_unpacklo_epi64(a23b23c23d23, e23f23g23h23);
  __m128i a3b3c3d3e3f3g3h3 = _mm_unpackhi_epi64(a23b23c23d23, e23f23g23h23);
  __m128i a4b4c4d4e4f4g4h4 = _mm_unpacklo_epi64(a45b45c45d45, e45f45g45h45);
  __m128i a5b5c5d5e5f5g5h5 = _mm_unpackhi_epi64(a45b45c45d45, e45f45g45h45);
  __m128i a6b6c6d6e6f6g6h6 = _mm_unpacklo_epi64(a67b67c67d67, e67f67g67h67);
  __m128i a7b7c7d7e7f7g7h7 = _mm_unpackhi_epi64(a67b67c67d67, e67f67g67h67);

  kernel.packet[0] = a0b0c0d0e0f0g0h0;
  kernel.packet[1] = a1b1c1d1e1f1g1h1;
  kernel.packet[2] = a2b2c2d2e2f2g2h2;
  kernel.packet[3] = a3b3c3d3e3f3g3h3;
  kernel.packet[4] = a4b4c4d4e4f4g4h4;
  kernel.packet[5] = a5b5c5d5e5f5g5h5;
  kernel.packet[6] = a6b6c6d6e6f6g6h6;
  kernel.packet[7] = a7b7c7d7e7f7g7h7;
}

EIGEN_STRONG_INLINE void
ptranspose(PacketBlock<Packet8h,4>& kernel) {
  EIGEN_ALIGN32 Eigen::half in[4][8];
  pstore<Eigen::half>(in[0], kernel.packet[0]);
  pstore<Eigen::half>(in[1], kernel.packet[1]);
  pstore<Eigen::half>(in[2], kernel.packet[2]);
  pstore<Eigen::half>(in[3], kernel.packet[3]);

  EIGEN_ALIGN32 Eigen::half out[4][8];

  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      out[i][j] = in[j][2*i];
    }
    for (int j = 0; j < 4; ++j) {
      out[i][j+4] = in[j][2*i+1];
    }
  }

  kernel.packet[0] = pload<Packet8h>(out[0]);
  kernel.packet[1] = pload<Packet8h>(out[1]);
  kernel.packet[2] = pload<Packet8h>(out[2]);
  kernel.packet[3] = pload<Packet8h>(out[3]);
}

// BFloat16 implementation.

EIGEN_STRONG_INLINE Packet8f Bf16ToF32(const Packet8bf& a) {
#ifdef EIGEN_VECTORIZE_AVX2
  __m256i extend = _mm256_cvtepu16_epi32(a);
  return _mm256_castsi256_ps(_mm256_slli_epi32(extend, 16));
#else
  __m128i lo = _mm_cvtepu16_epi32(a);
  __m128i hi = _mm_cvtepu16_epi32(_mm_srli_si128(a, 8));
  __m128i lo_shift = _mm_slli_epi32(lo, 16);
  __m128i hi_shift = _mm_slli_epi32(hi, 16);
  return _mm256_castsi256_ps(_mm256_insertf128_si256(_mm256_castsi128_si256(lo_shift), hi_shift, 1));
#endif
}

// Convert float to bfloat16 according to round-to-nearest-even/denormals algorithm.
EIGEN_STRONG_INLINE Packet8bf F32ToBf16(const Packet8f& a) {

  __m256i input = _mm256_castps_si256(a);

#ifdef EIGEN_VECTORIZE_AVX2
  // uint32_t lsb = (input >> 16);
  __m256i t = _mm256_srli_epi32(input, 16);
  // uint32_t lsb = lsb & 1;
  t = _mm256_and_si256(t, _mm256_set1_epi32(1));
  // uint32_t rounding_bias = 0x7fff + lsb;
  t = _mm256_add_epi32(t, _mm256_set1_epi32(0x7fff));
  // input += rounding_bias;
  t = _mm256_add_epi32(t, input);
  // input = input >> 16;
  t = _mm256_srli_epi32(t, 16);
  // Check NaN before converting back to bf16
  __m256 mask = _mm256_cmp_ps(a, a, _CMP_ORD_Q);
  __m256i nan = _mm256_set1_epi32(0x7fc0);
  t = _mm256_blendv_epi8(nan, t, _mm256_castps_si256(mask));
  // output = numext::bit_cast<uint16_t>(input);
  return _mm_packus_epi32(_mm256_extractf128_si256(t, 0),
                         _mm256_extractf128_si256(t, 1));
#else
  // uint32_t lsb = (input >> 16);
  __m128i lo = _mm_srli_epi32(_mm256_extractf128_si256(input, 0), 16);
  __m128i hi = _mm_srli_epi32(_mm256_extractf128_si256(input, 1), 16);
  // uint32_t lsb = lsb & 1;
  lo = _mm_and_si128(lo, _mm_set1_epi32(1));
  hi = _mm_and_si128(hi, _mm_set1_epi32(1));
  // uint32_t rounding_bias = 0x7fff + lsb;
  lo = _mm_add_epi32(lo, _mm_set1_epi32(0x7fff));
  hi = _mm_add_epi32(hi, _mm_set1_epi32(0x7fff));
  // input += rounding_bias;
  lo = _mm_add_epi32(lo, _mm256_extractf128_si256(input, 0));
  hi = _mm_add_epi32(hi, _mm256_extractf128_si256(input, 1));
  // input = input >> 16;
  lo = _mm_srli_epi32(lo, 16);
  hi = _mm_srli_epi32(hi, 16);
  // Check NaN before converting back to bf16
  __m256 mask = _mm256_cmp_ps(a, a, _CMP_ORD_Q);
  __m128i nan = _mm_set1_epi32(0x7fc0);
  lo = _mm_blendv_epi8(nan, lo, _mm_castps_si128(_mm256_castps256_ps128(mask)));
  hi = _mm_blendv_epi8(nan, hi, _mm_castps_si128(_mm256_extractf128_ps(mask, 1)));
  // output = numext::bit_cast<uint16_t>(input);
  return _mm_packus_epi32(lo, hi);
#endif
}

template<> EIGEN_STRONG_INLINE Packet8bf pset1<Packet8bf>(const bfloat16& from) {
  return _mm_set1_epi16(numext::bit_cast<numext::uint16_t>(from));
}

template<> EIGEN_STRONG_INLINE bfloat16 pfirst<Packet8bf>(const Packet8bf& from) {
  return numext::bit_cast<bfloat16>(static_cast<numext::uint16_t>(_mm_extract_epi16(from, 0)));
}

template<> EIGEN_STRONG_INLINE Packet8bf pload<Packet8bf>(const bfloat16* from) {
  return _mm_load_si128(reinterpret_cast<const __m128i*>(from));
}

template<> EIGEN_STRONG_INLINE Packet8bf ploadu<Packet8bf>(const bfloat16* from) {
  return _mm_loadu_si128(reinterpret_cast<const __m128i*>(from));
}

template<> EIGEN_STRONG_INLINE void pstore<bfloat16>(bfloat16* to, const Packet8bf& from) {
  _mm_store_si128(reinterpret_cast<__m128i*>(to), from);
}

template<> EIGEN_STRONG_INLINE void pstoreu<bfloat16>(bfloat16* to, const Packet8bf& from) {
  _mm_storeu_si128(reinterpret_cast<__m128i*>(to), from);
}

template<> EIGEN_STRONG_INLINE Packet8bf
ploaddup<Packet8bf>(const bfloat16* from) {
  const numext::uint16_t a = numext::bit_cast<numext::uint16_t>(from[0]);
  const numext::uint16_t b = numext::bit_cast<numext::uint16_t>(from[1]);
  const numext::uint16_t c = numext::bit_cast<numext::uint16_t>(from[2]);
  const numext::uint16_t d = numext::bit_cast<numext::uint16_t>(from[3]);
  return _mm_set_epi16(d, d, c, c, b, b, a, a);
}

template<> EIGEN_STRONG_INLINE Packet8bf
ploadquad<Packet8bf>(const bfloat16* from) {
  const numext::uint16_t a = numext::bit_cast<numext::uint16_t>(from[0]);
  const numext::uint16_t b = numext::bit_cast<numext::uint16_t>(from[1]);
  return _mm_set_epi16(b, b, b, b, a, a, a, a);
}

template<> EIGEN_STRONG_INLINE Packet8bf ptrue(const Packet8bf& a) {
 return _mm_cmpeq_epi32(a, a);
}

template <>
EIGEN_STRONG_INLINE Packet8bf pabs(const Packet8bf& a) {
  const __m128i sign_mask = _mm_set1_epi16(static_cast<numext::uint16_t>(0x8000));
  return _mm_andnot_si128(sign_mask, a);
}

template <>
EIGEN_STRONG_INLINE Packet8bf pmin<Packet8bf>(const Packet8bf& a,
                                                const Packet8bf& b) {
  return F32ToBf16(pmin<Packet8f>(Bf16ToF32(a), Bf16ToF32(b)));
}

template <>
EIGEN_STRONG_INLINE Packet8bf pmax<Packet8bf>(const Packet8bf& a,
                                                const Packet8bf& b) {
  return F32ToBf16(pmax<Packet8f>(Bf16ToF32(a), Bf16ToF32(b)));
}

template <>
EIGEN_STRONG_INLINE Packet8bf plset<Packet8bf>(const bfloat16& a) {
  return F32ToBf16(plset<Packet8f>(static_cast<float>(a)));
}

template<> EIGEN_STRONG_INLINE Packet8bf por(const Packet8bf& a,const Packet8bf& b) {
  return _mm_or_si128(a,b);
}
template<> EIGEN_STRONG_INLINE Packet8bf pxor(const Packet8bf& a,const Packet8bf& b) {
  return _mm_xor_si128(a,b);
}
template<> EIGEN_STRONG_INLINE Packet8bf pand(const Packet8bf& a,const Packet8bf& b) {
  return _mm_and_si128(a,b);
}
template<> EIGEN_STRONG_INLINE Packet8bf pandnot(const Packet8bf& a,const Packet8bf& b) {
  return _mm_andnot_si128(b,a);
}

template<> EIGEN_STRONG_INLINE Packet8bf pselect(const Packet8bf& mask, const Packet8bf& a, const Packet8bf& b) {
  return _mm_blendv_epi8(b, a, mask);
}

template<> EIGEN_STRONG_INLINE Packet8bf pround<Packet8bf>(const Packet8bf& a)
{
  return F32ToBf16(pround<Packet8f>(Bf16ToF32(a)));
}

template<> EIGEN_STRONG_INLINE Packet8bf print<Packet8bf>(const Packet8bf& a) {
  return F32ToBf16(print<Packet8f>(Bf16ToF32(a)));
}

template<> EIGEN_STRONG_INLINE Packet8bf pceil<Packet8bf>(const Packet8bf& a) {
  return F32ToBf16(pceil<Packet8f>(Bf16ToF32(a)));
}

template<> EIGEN_STRONG_INLINE Packet8bf pfloor<Packet8bf>(const Packet8bf& a) {
  return F32ToBf16(pfloor<Packet8f>(Bf16ToF32(a)));
}

template<> EIGEN_STRONG_INLINE Packet8bf pcmp_eq(const Packet8bf& a,const Packet8bf& b) {
  return Pack16To8(pcmp_eq(Bf16ToF32(a), Bf16ToF32(b)));
}

template<> EIGEN_STRONG_INLINE Packet8bf pcmp_le(const Packet8bf& a,const Packet8bf& b) {
  return Pack16To8(pcmp_le(Bf16ToF32(a), Bf16ToF32(b)));
}

template<> EIGEN_STRONG_INLINE Packet8bf pcmp_lt(const Packet8bf& a,const Packet8bf& b) {
  return Pack16To8(pcmp_lt(Bf16ToF32(a), Bf16ToF32(b)));
}

template<> EIGEN_STRONG_INLINE Packet8bf pcmp_lt_or_nan(const Packet8bf& a,const Packet8bf& b) {
  return Pack16To8(pcmp_lt_or_nan(Bf16ToF32(a), Bf16ToF32(b)));
}

template<> EIGEN_STRONG_INLINE Packet8bf pconj(const Packet8bf& a) { return a; }

template<> EIGEN_STRONG_INLINE Packet8bf pnegate(const Packet8bf& a) {
  Packet8bf sign_mask = _mm_set1_epi16(static_cast<numext::uint16_t>(0x8000));
  return _mm_xor_si128(a, sign_mask);
}

template<> EIGEN_STRONG_INLINE Packet8bf padd<Packet8bf>(const Packet8bf& a, const Packet8bf& b) {
  return F32ToBf16(padd<Packet8f>(Bf16ToF32(a), Bf16ToF32(b)));
}

template<> EIGEN_STRONG_INLINE Packet8bf psub<Packet8bf>(const Packet8bf& a, const Packet8bf& b) {
  return F32ToBf16(psub<Packet8f>(Bf16ToF32(a), Bf16ToF32(b)));
}

template<> EIGEN_STRONG_INLINE Packet8bf pmul<Packet8bf>(const Packet8bf& a, const Packet8bf& b) {
  return F32ToBf16(pmul<Packet8f>(Bf16ToF32(a), Bf16ToF32(b)));
}

template<> EIGEN_STRONG_INLINE Packet8bf pdiv<Packet8bf>(const Packet8bf& a, const Packet8bf& b) {
  return F32ToBf16(pdiv<Packet8f>(Bf16ToF32(a), Bf16ToF32(b)));
}


template<> EIGEN_STRONG_INLINE Packet8bf pgather<bfloat16, Packet8bf>(const bfloat16* from, Index stride)
{
  const numext::uint16_t s0 = numext::bit_cast<numext::uint16_t>(from[0*stride]);
  const numext::uint16_t s1 = numext::bit_cast<numext::uint16_t>(from[1*stride]);
  const numext::uint16_t s2 = numext::bit_cast<numext::uint16_t>(from[2*stride]);
  const numext::uint16_t s3 = numext::bit_cast<numext::uint16_t>(from[3*stride]);
  const numext::uint16_t s4 = numext::bit_cast<numext::uint16_t>(from[4*stride]);
  const numext::uint16_t s5 = numext::bit_cast<numext::uint16_t>(from[5*stride]);
  const numext::uint16_t s6 = numext::bit_cast<numext::uint16_t>(from[6*stride]);
  const numext::uint16_t s7 = numext::bit_cast<numext::uint16_t>(from[7*stride]);
  return _mm_set_epi16(s7, s6, s5, s4, s3, s2, s1, s0);
}

template<> EIGEN_STRONG_INLINE void pscatter<bfloat16, Packet8bf>(bfloat16* to, const Packet8bf& from, Index stride)
{
  EIGEN_ALIGN32 bfloat16 aux[8];
  pstore(aux, from);
  to[stride*0] = aux[0];
  to[stride*1] = aux[1];
  to[stride*2] = aux[2];
  to[stride*3] = aux[3];
  to[stride*4] = aux[4];
  to[stride*5] = aux[5];
  to[stride*6] = aux[6];
  to[stride*7] = aux[7];
}

template<> EIGEN_STRONG_INLINE bfloat16 predux<Packet8bf>(const Packet8bf& a) {
  return static_cast<bfloat16>(predux<Packet8f>(Bf16ToF32(a)));
}

template<> EIGEN_STRONG_INLINE bfloat16 predux_max<Packet8bf>(const Packet8bf& a) {
  return static_cast<bfloat16>(predux_max<Packet8f>(Bf16ToF32(a)));
}

template<> EIGEN_STRONG_INLINE bfloat16 predux_min<Packet8bf>(const Packet8bf& a) {
  return static_cast<bfloat16>(predux_min<Packet8f>(Bf16ToF32(a)));
}

template<> EIGEN_STRONG_INLINE bfloat16 predux_mul<Packet8bf>(const Packet8bf& a) {
  return static_cast<bfloat16>(predux_mul<Packet8f>(Bf16ToF32(a)));
}

template<> EIGEN_STRONG_INLINE Packet8bf preverse(const Packet8bf& a)
{
  __m128i m = _mm_setr_epi8(14,15,12,13,10,11,8,9,6,7,4,5,2,3,0,1);
  return _mm_shuffle_epi8(a,m);
}

EIGEN_STRONG_INLINE void
ptranspose(PacketBlock<Packet8bf,8>& kernel) {
  __m128i a = kernel.packet[0];
  __m128i b = kernel.packet[1];
  __m128i c = kernel.packet[2];
  __m128i d = kernel.packet[3];
  __m128i e = kernel.packet[4];
  __m128i f = kernel.packet[5];
  __m128i g = kernel.packet[6];
  __m128i h = kernel.packet[7];

  __m128i a03b03 = _mm_unpacklo_epi16(a, b);
  __m128i c03d03 = _mm_unpacklo_epi16(c, d);
  __m128i e03f03 = _mm_unpacklo_epi16(e, f);
  __m128i g03h03 = _mm_unpacklo_epi16(g, h);
  __m128i a47b47 = _mm_unpackhi_epi16(a, b);
  __m128i c47d47 = _mm_unpackhi_epi16(c, d);
  __m128i e47f47 = _mm_unpackhi_epi16(e, f);
  __m128i g47h47 = _mm_unpackhi_epi16(g, h);

  __m128i a01b01c01d01 = _mm_unpacklo_epi32(a03b03, c03d03);
  __m128i a23b23c23d23 = _mm_unpackhi_epi32(a03b03, c03d03);
  __m128i e01f01g01h01 = _mm_unpacklo_epi32(e03f03, g03h03);
  __m128i e23f23g23h23 = _mm_unpackhi_epi32(e03f03, g03h03);
  __m128i a45b45c45d45 = _mm_unpacklo_epi32(a47b47, c47d47);
  __m128i a67b67c67d67 = _mm_unpackhi_epi32(a47b47, c47d47);
  __m128i e45f45g45h45 = _mm_unpacklo_epi32(e47f47, g47h47);
  __m128i e67f67g67h67 = _mm_unpackhi_epi32(e47f47, g47h47);

  kernel.packet[0] = _mm_unpacklo_epi64(a01b01c01d01, e01f01g01h01);
  kernel.packet[1] = _mm_unpackhi_epi64(a01b01c01d01, e01f01g01h01);
  kernel.packet[2] = _mm_unpacklo_epi64(a23b23c23d23, e23f23g23h23);
  kernel.packet[3] = _mm_unpackhi_epi64(a23b23c23d23, e23f23g23h23);
  kernel.packet[4] = _mm_unpacklo_epi64(a45b45c45d45, e45f45g45h45);
  kernel.packet[5] = _mm_unpackhi_epi64(a45b45c45d45, e45f45g45h45);
  kernel.packet[6] = _mm_unpacklo_epi64(a67b67c67d67, e67f67g67h67);
  kernel.packet[7] = _mm_unpackhi_epi64(a67b67c67d67, e67f67g67h67);
}

EIGEN_STRONG_INLINE void
ptranspose(PacketBlock<Packet8bf,4>& kernel) {
  __m128i a = kernel.packet[0];
  __m128i b = kernel.packet[1];
  __m128i c = kernel.packet[2];
  __m128i d = kernel.packet[3];

  __m128i ab_03 = _mm_unpacklo_epi16(a, b);
  __m128i cd_03 = _mm_unpacklo_epi16(c, d);
  __m128i ab_47 = _mm_unpackhi_epi16(a, b);
  __m128i cd_47 = _mm_unpackhi_epi16(c, d);

  kernel.packet[0] = _mm_unpacklo_epi32(ab_03, cd_03);
  kernel.packet[1] = _mm_unpackhi_epi32(ab_03, cd_03);
  kernel.packet[2] = _mm_unpacklo_epi32(ab_47, cd_47);
  kernel.packet[3] = _mm_unpackhi_epi32(ab_47, cd_47);
}

} // end namespace internal

} // end namespace Eigen

#if EIGEN_COMP_PGI && EIGEN_COMP_PGI < 1900
// PGI++ does not define the following intrinsics in C++ mode.
static inline __m128  _mm_castpd_ps   (__m128d x) { return reinterpret_cast<__m128&>(x);  }
static inline __m128i _mm_castpd_si128(__m128d x) { return reinterpret_cast<__m128i&>(x); }
static inline __m128d _mm_castps_pd   (__m128  x) { return reinterpret_cast<__m128d&>(x); }
static inline __m128i _mm_castps_si128(__m128  x) { return reinterpret_cast<__m128i&>(x); }
static inline __m128  _mm_castsi128_ps(__m128i x) { return reinterpret_cast<__m128&>(x);  }
static inline __m128d _mm_castsi128_pd(__m128i x) { return reinterpret_cast<__m128d&>(x); }
#endif

#endif // EIGEN_PACKET_MATH_MIPP_H
