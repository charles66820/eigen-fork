// This file is part of Eigen, a lightweight C++ template library
// for linear algebra.
//
// Copyright (C) 2014 Benoit Steiner (benoit.steiner.goog@gmail.com)
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef EIGEN_COMPLEX_MIPP_H
#define EIGEN_COMPLEX_MIPP_H

#include "../../InternalHeaderCheck.h"

namespace Eigen {

namespace internal {

//---------- float ----------
struct Packet2cf
{
  EIGEN_STRONG_INLINE Packet2cf() {}
  EIGEN_STRONG_INLINE explicit Packet2cf(const __m128& a) : v(a) {}
  Packet4f v;
};

#ifdef EIGEN_VECTORIZE_AVX
struct Packet4cf
{
  EIGEN_STRONG_INLINE Packet4cf() {}
  EIGEN_STRONG_INLINE explicit Packet4cf(const __m256& a) : v(a) {}
  __m256  v;
};
#endif

#ifdef EIGEN_VECTORIZE_AVX512
struct Packet8cf
{
  EIGEN_STRONG_INLINE Packet8cf() {}
  EIGEN_STRONG_INLINE explicit Packet8cf(const __m512& a) : v(a) {}
  __m512  v;
};
#endif

// Use the packet_traits defined in AVX/PacketMath.h instead if we're going
// to leverage AVX instructions.
#ifdef EIGEN_VECTORIZE_AVX512

template<> struct packet_traits<std::complex<float> >  : default_packet_traits
{
  typedef Packet4cf type;
  typedef Packet2cf half;
  enum {
    Vectorizable = 1,
    AlignedOnScalar = 1,
    size = 4,
    HasHalfPacket = 1,

    HasAdd    = 1,
    HasSub    = 1,
    HasMul    = 1,
    HasDiv    = 1,
    HasNegate = 1,
    HasSqrt   = 1,
    HasAbs    = 0,
    HasAbs2   = 0,
    HasMin    = 0,
    HasMax    = 0,
    HasSetLinear = 0
  };
};

#elif defined(EIGEN_VECTORIZE_AVX)

template<> struct packet_traits<std::complex<float> >  : default_packet_traits
{
  typedef Packet4cf type;
  typedef Packet2cf half;
  enum {
    Vectorizable = 1,
    AlignedOnScalar = 1,
    size = 4,
    HasHalfPacket = 1,

    HasAdd    = 1,
    HasSub    = 1,
    HasMul    = 1,
    HasDiv    = 1,
    HasNegate = 1,
    HasSqrt   = 1,
    HasAbs    = 0,
    HasAbs2   = 0,
    HasMin    = 0,
    HasMax    = 0,
    HasSetLinear = 0
  };
};

#else

template<> struct packet_traits<std::complex<float> >  : default_packet_traits
{
  typedef Packet2cf type;
  typedef Packet2cf half;
  enum {
    Vectorizable = 1,
    AlignedOnScalar = 1,
    size = 2,
    HasHalfPacket = 0,

    HasAdd    = 1,
    HasSub    = 1,
    HasMul    = 1,
    HasDiv    = 1,
    HasNegate = 1,
    HasSqrt   = 1,
    HasAbs    = 0,
    HasAbs2   = 0,
    HasMin    = 0,
    HasMax    = 0,
    HasSetLinear = 0,
    HasBlend  = 1
  };
};
#endif

template<> struct unpacket_traits<Packet2cf> {
  typedef std::complex<float> type;
  typedef Packet2cf half;
  typedef Packet4f as_real;
  enum {
    size=2,
    alignment=Aligned16,
    vectorizable=true,
    masked_load_available=false,
    masked_store_available=false
  };
};

#ifdef EIGEN_VECTORIZE_AVX

template<> struct unpacket_traits<Packet4cf> {
  typedef std::complex<float> type;
  typedef Packet2cf half;
  typedef Packet8f as_real;
  enum {
    size=4,
    alignment=Aligned32,
    vectorizable=true,
    masked_load_available=false,
    masked_store_available=false
  };
};
#endif

#ifdef EIGEN_VECTORIZE_AVX512
template<> struct unpacket_traits<Packet8cf> {
  typedef std::complex<float> type;
  typedef Packet4cf half;
  typedef Packet16f as_real;
  enum {
    size = 8,
    alignment=unpacket_traits<Packet16f>::alignment,
    vectorizable=true,
    masked_load_available=false,
    masked_store_available=false
  };
};

#endif

template<> EIGEN_STRONG_INLINE Packet2cf padd<Packet2cf>(const Packet2cf& a, const Packet2cf& b) { return Packet2cf(_mm_add_ps(a.v,b.v)); }
template<> EIGEN_STRONG_INLINE Packet2cf psub<Packet2cf>(const Packet2cf& a, const Packet2cf& b) { return Packet2cf(_mm_sub_ps(a.v,b.v)); }

template<> EIGEN_STRONG_INLINE Packet2cf pnegate(const Packet2cf& a)
{
  const __m128 mask = _mm_castsi128_ps(_mm_setr_epi32(0x80000000,0x80000000,0x80000000,0x80000000));
  return Packet2cf(_mm_xor_ps(a.v,mask));
}
template<> EIGEN_STRONG_INLINE Packet2cf pconj(const Packet2cf& a)
{
  const __m128 mask = _mm_castsi128_ps(_mm_setr_epi32(0x00000000,0x80000000,0x00000000,0x80000000));
  return Packet2cf(_mm_xor_ps(a.v,mask));
}

template<> EIGEN_STRONG_INLINE Packet2cf pmul<Packet2cf>(const Packet2cf& a, const Packet2cf& b)
{
  #ifdef EIGEN_VECTORIZE_SSE3
  return Packet2cf(_mm_addsub_ps(_mm_mul_ps(_mm_moveldup_ps(a.v), b.v),
                                 _mm_mul_ps(_mm_movehdup_ps(a.v),
                                            vec4f_swizzle1(b.v, 1, 0, 3, 2))));
//   return Packet2cf(_mm_addsub_ps(_mm_mul_ps(vec4f_swizzle1(a.v, 0, 0, 2, 2), b.v),
//                                  _mm_mul_ps(vec4f_swizzle1(a.v, 1, 1, 3, 3),
//                                             vec4f_swizzle1(b.v, 1, 0, 3, 2))));
  #else
  const __m128 mask = _mm_castsi128_ps(_mm_setr_epi32(0x80000000,0x00000000,0x80000000,0x00000000));
  return Packet2cf(_mm_add_ps(_mm_mul_ps(vec4f_swizzle1(a.v, 0, 0, 2, 2), b.v),
                              _mm_xor_ps(_mm_mul_ps(vec4f_swizzle1(a.v, 1, 1, 3, 3),
                                                    vec4f_swizzle1(b.v, 1, 0, 3, 2)), mask)));
  #endif
}

template<> EIGEN_STRONG_INLINE Packet2cf ptrue  <Packet2cf>(const Packet2cf& a) { return Packet2cf(ptrue(Packet4f(a.v))); }
template<> EIGEN_STRONG_INLINE Packet2cf pand   <Packet2cf>(const Packet2cf& a, const Packet2cf& b) { return Packet2cf(_mm_and_ps(a.v,b.v)); }
template<> EIGEN_STRONG_INLINE Packet2cf por    <Packet2cf>(const Packet2cf& a, const Packet2cf& b) { return Packet2cf(_mm_or_ps(a.v,b.v)); }
template<> EIGEN_STRONG_INLINE Packet2cf pxor   <Packet2cf>(const Packet2cf& a, const Packet2cf& b) { return Packet2cf(_mm_xor_ps(a.v,b.v)); }
template<> EIGEN_STRONG_INLINE Packet2cf pandnot<Packet2cf>(const Packet2cf& a, const Packet2cf& b) { return Packet2cf(_mm_andnot_ps(b.v,a.v)); }

template<> EIGEN_STRONG_INLINE Packet2cf pload <Packet2cf>(const std::complex<float>* from) { EIGEN_DEBUG_ALIGNED_LOAD return Packet2cf(pload<Packet4f>(&numext::real_ref(*from))); }
template<> EIGEN_STRONG_INLINE Packet2cf ploadu<Packet2cf>(const std::complex<float>* from) { EIGEN_DEBUG_UNALIGNED_LOAD return Packet2cf(ploadu<Packet4f>(&numext::real_ref(*from))); }

template<> EIGEN_STRONG_INLINE Packet2cf pset1<Packet2cf>(const std::complex<float>&  from)
{
  const float re = std::real(from);
  const float im = std::imag(from);
  return Packet2cf(_mm_set_ps(im, re, im, re));
}

template<> EIGEN_STRONG_INLINE Packet2cf ploaddup<Packet2cf>(const std::complex<float>* from) { return pset1<Packet2cf>(*from); }

template<> EIGEN_STRONG_INLINE void pstore <std::complex<float> >(std::complex<float> *   to, const Packet2cf& from) { EIGEN_DEBUG_ALIGNED_STORE pstore(&numext::real_ref(*to), Packet4f(from.v)); }
template<> EIGEN_STRONG_INLINE void pstoreu<std::complex<float> >(std::complex<float> *   to, const Packet2cf& from) { EIGEN_DEBUG_UNALIGNED_STORE pstoreu(&numext::real_ref(*to), Packet4f(from.v)); }


template<> EIGEN_DEVICE_FUNC inline Packet2cf pgather<std::complex<float>, Packet2cf>(const std::complex<float>* from, Index stride)
{
  return Packet2cf(_mm_set_ps(std::imag(from[1*stride]), std::real(from[1*stride]),
                              std::imag(from[0*stride]), std::real(from[0*stride])));
}

template<> EIGEN_DEVICE_FUNC inline void pscatter<std::complex<float>, Packet2cf>(std::complex<float>* to, const Packet2cf& from, Index stride)
{
  to[stride*0] = std::complex<float>(_mm_cvtss_f32(_mm_shuffle_ps(from.v, from.v, 0)),
                                     _mm_cvtss_f32(_mm_shuffle_ps(from.v, from.v, 1)));
  to[stride*1] = std::complex<float>(_mm_cvtss_f32(_mm_shuffle_ps(from.v, from.v, 2)),
                                     _mm_cvtss_f32(_mm_shuffle_ps(from.v, from.v, 3)));
}

template<> EIGEN_STRONG_INLINE void prefetch<std::complex<float> >(const std::complex<float> *   addr) { _mm_prefetch((SsePrefetchPtrType)(addr), _MM_HINT_T0); }

template<> EIGEN_STRONG_INLINE std::complex<float>  pfirst<Packet2cf>(const Packet2cf& a)
{
  alignas(alignof(__m64)) std::complex<float> res;
  _mm_storel_pi((__m64*)&res, a.v);
  return res;
}

template<> EIGEN_STRONG_INLINE Packet2cf preverse(const Packet2cf& a) { return Packet2cf(_mm_castpd_ps(preverse(Packet2d(_mm_castps_pd(a.v))))); }

template<> EIGEN_STRONG_INLINE std::complex<float> predux<Packet2cf>(const Packet2cf& a)
{
  return pfirst(Packet2cf(_mm_add_ps(a.v, _mm_movehl_ps(a.v,a.v))));
}

template<> EIGEN_STRONG_INLINE std::complex<float> predux_mul<Packet2cf>(const Packet2cf& a)
{
  return pfirst(pmul(a, Packet2cf(_mm_movehl_ps(a.v,a.v))));
}

EIGEN_STRONG_INLINE Packet2cf pcplxflip/* <Packet2cf> */(const Packet2cf& x)
{
  return Packet2cf(vec4f_swizzle1(x.v, 1, 0, 3, 2));
}

EIGEN_MAKE_CONJ_HELPER_CPLX_REAL(Packet2cf,Packet4f)

template<> EIGEN_STRONG_INLINE Packet2cf pdiv<Packet2cf>(const Packet2cf& a, const Packet2cf& b)
{
  return pdiv_complex(a, b);
}

#ifdef EIGEN_VECTORIZE_AVX

template<> EIGEN_STRONG_INLINE Packet4cf padd<Packet4cf>(const Packet4cf& a, const Packet4cf& b) { return Packet4cf(_mm256_add_ps(a.v,b.v)); }
template<> EIGEN_STRONG_INLINE Packet4cf psub<Packet4cf>(const Packet4cf& a, const Packet4cf& b) { return Packet4cf(_mm256_sub_ps(a.v,b.v)); }
template<> EIGEN_STRONG_INLINE Packet4cf pnegate(const Packet4cf& a)
{
  return Packet4cf(pnegate(a.v));
}
template<> EIGEN_STRONG_INLINE Packet4cf pconj(const Packet4cf& a)
{
  const __m256 mask = _mm256_castsi256_ps(_mm256_setr_epi32(0x00000000,0x80000000,0x00000000,0x80000000,0x00000000,0x80000000,0x00000000,0x80000000));
  return Packet4cf(_mm256_xor_ps(a.v,mask));
}

template<> EIGEN_STRONG_INLINE Packet4cf pmul<Packet4cf>(const Packet4cf& a, const Packet4cf& b)
{
  __m256 tmp1 = _mm256_mul_ps(_mm256_moveldup_ps(a.v), b.v);
  __m256 tmp2 = _mm256_mul_ps(_mm256_movehdup_ps(a.v), _mm256_permute_ps(b.v, _MM_SHUFFLE(2,3,0,1)));
  __m256 result = _mm256_addsub_ps(tmp1, tmp2);
  return Packet4cf(result);
}

template <>
EIGEN_STRONG_INLINE Packet4cf pcmp_eq(const Packet4cf& a, const Packet4cf& b) {
  __m256 eq = _mm256_cmp_ps(a.v, b.v, _CMP_EQ_OQ);
  return Packet4cf(_mm256_and_ps(eq, _mm256_permute_ps(eq, 0xb1)));
}

template<> EIGEN_STRONG_INLINE Packet4cf ptrue<Packet4cf>(const Packet4cf& a) { return Packet4cf(ptrue(Packet8f(a.v))); }
template<> EIGEN_STRONG_INLINE Packet4cf pand   <Packet4cf>(const Packet4cf& a, const Packet4cf& b) { return Packet4cf(_mm256_and_ps(a.v,b.v)); }
template<> EIGEN_STRONG_INLINE Packet4cf por    <Packet4cf>(const Packet4cf& a, const Packet4cf& b) { return Packet4cf(_mm256_or_ps(a.v,b.v)); }
template<> EIGEN_STRONG_INLINE Packet4cf pxor   <Packet4cf>(const Packet4cf& a, const Packet4cf& b) { return Packet4cf(_mm256_xor_ps(a.v,b.v)); }
template<> EIGEN_STRONG_INLINE Packet4cf pandnot<Packet4cf>(const Packet4cf& a, const Packet4cf& b) { return Packet4cf(_mm256_andnot_ps(b.v,a.v)); }

template<> EIGEN_STRONG_INLINE Packet4cf pload <Packet4cf>(const std::complex<float>* from) { EIGEN_DEBUG_ALIGNED_LOAD return Packet4cf(pload<Packet8f>(&numext::real_ref(*from))); }
template<> EIGEN_STRONG_INLINE Packet4cf ploadu<Packet4cf>(const std::complex<float>* from) { EIGEN_DEBUG_UNALIGNED_LOAD return Packet4cf(ploadu<Packet8f>(&numext::real_ref(*from))); }


template<> EIGEN_STRONG_INLINE Packet4cf pset1<Packet4cf>(const std::complex<float>& from)
{
  const float re = std::real(from);
  const float im = std::imag(from);
  return Packet4cf(_mm256_set_ps(im, re, im, re, im, re, im, re));
}

template<> EIGEN_STRONG_INLINE Packet4cf ploaddup<Packet4cf>(const std::complex<float>* from)
{
  // FIXME The following might be optimized using _mm256_movedup_pd
  Packet2cf a = ploaddup<Packet2cf>(from);
  Packet2cf b = ploaddup<Packet2cf>(from+1);
  return  Packet4cf(_mm256_insertf128_ps(_mm256_castps128_ps256(a.v), b.v, 1));
}

template<> EIGEN_STRONG_INLINE void pstore <std::complex<float> >(std::complex<float>* to, const Packet4cf& from) { EIGEN_DEBUG_ALIGNED_STORE pstore(&numext::real_ref(*to), from.v); }
template<> EIGEN_STRONG_INLINE void pstoreu<std::complex<float> >(std::complex<float>* to, const Packet4cf& from) { EIGEN_DEBUG_UNALIGNED_STORE pstoreu(&numext::real_ref(*to), from.v); }

template<> EIGEN_DEVICE_FUNC inline Packet4cf pgather<std::complex<float>, Packet4cf>(const std::complex<float>* from, Index stride)
{
  return Packet4cf(_mm256_set_ps(std::imag(from[3*stride]), std::real(from[3*stride]),
                                 std::imag(from[2*stride]), std::real(from[2*stride]),
                                 std::imag(from[1*stride]), std::real(from[1*stride]),
                                 std::imag(from[0*stride]), std::real(from[0*stride])));
}

template<> EIGEN_DEVICE_FUNC inline void pscatter<std::complex<float>, Packet4cf>(std::complex<float>* to, const Packet4cf& from, Index stride)
{
  __m128 low = _mm256_extractf128_ps(from.v, 0);
  to[stride*0] = std::complex<float>(_mm_cvtss_f32(_mm_shuffle_ps(low, low, 0)),
                                     _mm_cvtss_f32(_mm_shuffle_ps(low, low, 1)));
  to[stride*1] = std::complex<float>(_mm_cvtss_f32(_mm_shuffle_ps(low, low, 2)),
                                     _mm_cvtss_f32(_mm_shuffle_ps(low, low, 3)));

  __m128 high = _mm256_extractf128_ps(from.v, 1);
  to[stride*2] = std::complex<float>(_mm_cvtss_f32(_mm_shuffle_ps(high, high, 0)),
                                     _mm_cvtss_f32(_mm_shuffle_ps(high, high, 1)));
  to[stride*3] = std::complex<float>(_mm_cvtss_f32(_mm_shuffle_ps(high, high, 2)),
                                     _mm_cvtss_f32(_mm_shuffle_ps(high, high, 3)));

}

template<> EIGEN_STRONG_INLINE std::complex<float>  pfirst<Packet4cf>(const Packet4cf& a)
{
  return pfirst(Packet2cf(_mm256_castps256_ps128(a.v)));
}

template<> EIGEN_STRONG_INLINE Packet4cf preverse(const Packet4cf& a) {
  __m128 low  = _mm256_extractf128_ps(a.v, 0);
  __m128 high = _mm256_extractf128_ps(a.v, 1);
  __m128d lowd  = _mm_castps_pd(low);
  __m128d highd = _mm_castps_pd(high);
  low  = _mm_castpd_ps(_mm_shuffle_pd(lowd,lowd,0x1));
  high = _mm_castpd_ps(_mm_shuffle_pd(highd,highd,0x1));
  __m256 result = _mm256_setzero_ps();
  result = _mm256_insertf128_ps(result, low, 1);
  result = _mm256_insertf128_ps(result, high, 0);
  return Packet4cf(result);
}

template<> EIGEN_STRONG_INLINE std::complex<float> predux<Packet4cf>(const Packet4cf& a)
{
  return predux(padd(Packet2cf(_mm256_extractf128_ps(a.v,0)),
                     Packet2cf(_mm256_extractf128_ps(a.v,1))));
}

template<> EIGEN_STRONG_INLINE std::complex<float> predux_mul<Packet4cf>(const Packet4cf& a)
{
  return predux_mul(pmul(Packet2cf(_mm256_extractf128_ps(a.v, 0)),
                         Packet2cf(_mm256_extractf128_ps(a.v, 1))));
}


EIGEN_MAKE_CONJ_HELPER_CPLX_REAL(Packet4cf,Packet8f)

template<> EIGEN_STRONG_INLINE Packet4cf pdiv<Packet4cf>(const Packet4cf& a, const Packet4cf& b)
{
  return pdiv_complex(a, b);
}

template<> EIGEN_STRONG_INLINE Packet4cf pcplxflip<Packet4cf>(const Packet4cf& x)
{
  return Packet4cf(_mm256_shuffle_ps(x.v, x.v, _MM_SHUFFLE(2, 3, 0 ,1)));
}

#endif

#ifdef EIGEN_VECTORIZE_AVX512

template<> EIGEN_STRONG_INLINE Packet8cf ptrue<Packet8cf>(const Packet8cf& a) { return Packet8cf(ptrue(Packet16f(a.v))); }
template<> EIGEN_STRONG_INLINE Packet8cf padd<Packet8cf>(const Packet8cf& a, const Packet8cf& b) { return Packet8cf(_mm512_add_ps(a.v,b.v)); }
template<> EIGEN_STRONG_INLINE Packet8cf psub<Packet8cf>(const Packet8cf& a, const Packet8cf& b) { return Packet8cf(_mm512_sub_ps(a.v,b.v)); }
template<> EIGEN_STRONG_INLINE Packet8cf pnegate(const Packet8cf& a)
{
  return Packet8cf(pnegate(a.v));
}
template<> EIGEN_STRONG_INLINE Packet8cf pconj(const Packet8cf& a)
{
  const __m512 mask = _mm512_castsi512_ps(_mm512_setr_epi32(
    0x00000000,0x80000000,0x00000000,0x80000000,0x00000000,0x80000000,0x00000000,0x80000000,
    0x00000000,0x80000000,0x00000000,0x80000000,0x00000000,0x80000000,0x00000000,0x80000000));
  return Packet8cf(pxor(a.v,mask));
}

template<> EIGEN_STRONG_INLINE Packet8cf pmul<Packet8cf>(const Packet8cf& a, const Packet8cf& b)
{
  __m512 tmp2 = _mm512_mul_ps(_mm512_movehdup_ps(a.v), _mm512_permute_ps(b.v, _MM_SHUFFLE(2,3,0,1)));
  return Packet8cf(_mm512_fmaddsub_ps(_mm512_moveldup_ps(a.v), b.v, tmp2));
}

template<> EIGEN_STRONG_INLINE Packet8cf pand   <Packet8cf>(const Packet8cf& a, const Packet8cf& b) { return Packet8cf(pand(a.v,b.v)); }
template<> EIGEN_STRONG_INLINE Packet8cf por    <Packet8cf>(const Packet8cf& a, const Packet8cf& b) { return Packet8cf(por(a.v,b.v)); }
template<> EIGEN_STRONG_INLINE Packet8cf pxor   <Packet8cf>(const Packet8cf& a, const Packet8cf& b) { return Packet8cf(pxor(a.v,b.v)); }
template<> EIGEN_STRONG_INLINE Packet8cf pandnot<Packet8cf>(const Packet8cf& a, const Packet8cf& b) { return Packet8cf(pandnot(a.v,b.v)); }

template <>
EIGEN_STRONG_INLINE Packet8cf pcmp_eq(const Packet8cf& a, const Packet8cf& b) {
  __m512 eq = pcmp_eq<Packet16f>(a.v, b.v);
  return Packet8cf(pand(eq, _mm512_permute_ps(eq, 0xB1)));
}

template<> EIGEN_STRONG_INLINE Packet8cf pload <Packet8cf>(const std::complex<float>* from) { EIGEN_DEBUG_ALIGNED_LOAD return Packet8cf(pload<Packet16f>(&numext::real_ref(*from))); }
template<> EIGEN_STRONG_INLINE Packet8cf ploadu<Packet8cf>(const std::complex<float>* from) { EIGEN_DEBUG_UNALIGNED_LOAD return Packet8cf(ploadu<Packet16f>(&numext::real_ref(*from))); }


template<> EIGEN_STRONG_INLINE Packet8cf pset1<Packet8cf>(const std::complex<float>& from)
{
  const float re = std::real(from);
  const float im = std::imag(from);
  return Packet8cf(_mm512_set_ps(im, re, im, re, im, re, im, re, im, re, im, re, im, re, im, re));
}

template<> EIGEN_STRONG_INLINE Packet8cf ploaddup<Packet8cf>(const std::complex<float>* from)
{
  return Packet8cf( _mm512_castpd_ps( ploaddup<Packet8d>((const double*)(const void*)from )) );
}
template<> EIGEN_STRONG_INLINE Packet8cf ploadquad<Packet8cf>(const std::complex<float>* from)
{
  return Packet8cf( _mm512_castpd_ps( ploadquad<Packet8d>((const double*)(const void*)from )) );
}

template<> EIGEN_STRONG_INLINE void pstore <std::complex<float> >(std::complex<float>* to, const Packet8cf& from) { EIGEN_DEBUG_ALIGNED_STORE pstore(&numext::real_ref(*to), from.v); }
template<> EIGEN_STRONG_INLINE void pstoreu<std::complex<float> >(std::complex<float>* to, const Packet8cf& from) { EIGEN_DEBUG_UNALIGNED_STORE pstoreu(&numext::real_ref(*to), from.v); }

template<> EIGEN_DEVICE_FUNC inline Packet8cf pgather<std::complex<float>, Packet8cf>(const std::complex<float>* from, Index stride)
{
  return Packet8cf(_mm512_castpd_ps(pgather<double,Packet8d>((const double*)(const void*)from, stride)));
}

template<> EIGEN_DEVICE_FUNC inline void pscatter<std::complex<float>, Packet8cf>(std::complex<float>* to, const Packet8cf& from, Index stride)
{
  pscatter((double*)(void*)to, _mm512_castps_pd(from.v), stride);
}

template<> EIGEN_STRONG_INLINE std::complex<float>  pfirst<Packet8cf>(const Packet8cf& a)
{
  return pfirst(Packet2cf(_mm512_castps512_ps128(a.v)));
}

template<> EIGEN_STRONG_INLINE Packet8cf preverse(const Packet8cf& a) {
  return Packet8cf(_mm512_castsi512_ps(
            _mm512_permutexvar_epi64( _mm512_set_epi32(0, 0, 0, 1, 0, 2, 0, 3, 0, 4, 0, 5, 0, 6, 0, 7),
                                      _mm512_castps_si512(a.v))));
}

template<> EIGEN_STRONG_INLINE std::complex<float> predux<Packet8cf>(const Packet8cf& a)
{
  return predux(padd(Packet4cf(extract256<0>(a.v)),
                     Packet4cf(extract256<1>(a.v))));
}

template<> EIGEN_STRONG_INLINE std::complex<float> predux_mul<Packet8cf>(const Packet8cf& a)
{
  return predux_mul(pmul(Packet4cf(extract256<0>(a.v)),
                         Packet4cf(extract256<1>(a.v))));
}

template <>
EIGEN_STRONG_INLINE Packet4cf predux_half_dowto4<Packet8cf>(const Packet8cf& a) {
  __m256 lane0 = extract256<0>(a.v);
  __m256 lane1 = extract256<1>(a.v);
  __m256 res = _mm256_add_ps(lane0, lane1);
  return Packet4cf(res);
}

EIGEN_MAKE_CONJ_HELPER_CPLX_REAL(Packet8cf,Packet16f)

template<> EIGEN_STRONG_INLINE Packet8cf pdiv<Packet8cf>(const Packet8cf& a, const Packet8cf& b)
{
  return pdiv_complex(a, b);
}

template<> EIGEN_STRONG_INLINE Packet8cf pcplxflip<Packet8cf>(const Packet8cf& x)
{
  return Packet8cf(_mm512_shuffle_ps(x.v, x.v, _MM_SHUFFLE(2, 3, 0 ,1)));
}

#endif

//---------- double ----------
struct Packet1cd
{
  EIGEN_STRONG_INLINE Packet1cd() {}
  EIGEN_STRONG_INLINE explicit Packet1cd(const __m128d& a) : v(a) {}
  Packet2d v;
};

#ifdef EIGEN_VECTORIZE_AVX
struct Packet2cd
{
  EIGEN_STRONG_INLINE Packet2cd() {}
  EIGEN_STRONG_INLINE explicit Packet2cd(const __m256d& a) : v(a) {}
  __m256d  v;
};
#endif

#ifdef EIGEN_VECTORIZE_AVX512
struct Packet4cd
{
  EIGEN_STRONG_INLINE Packet4cd() {}
  EIGEN_STRONG_INLINE explicit Packet4cd(const __m512d& a) : v(a) {}
  __m512d  v;
};
#endif

// Use the packet_traits defined in AVX/PacketMath.h instead if we're going
// to leverage AVX instructions.
#ifdef EIGEN_VECTORIZE_AVX512

template<> struct packet_traits<std::complex<double> >  : default_packet_traits
{
  typedef Packet4cd type;
  typedef Packet2cd half;
  enum {
    Vectorizable = 1,
    AlignedOnScalar = 0,
    size = 4,
    HasHalfPacket = 1,

    HasAdd    = 1,
    HasSub    = 1,
    HasMul    = 1,
    HasDiv    = 1,
    HasNegate = 1,
    HasSqrt   = 1,
    HasAbs    = 0,
    HasAbs2   = 0,
    HasMin    = 0,
    HasMax    = 0,
    HasSetLinear = 0
  };
};

#elif defined(EIGEN_VECTORIZE_AVX)

template<> struct packet_traits<std::complex<double> >  : default_packet_traits
{
  typedef Packet2cd type;
  typedef Packet1cd half;
  enum {
    Vectorizable = 1,
    AlignedOnScalar = 0,
    size = 2,
    HasHalfPacket = 1,

    HasAdd    = 1,
    HasSub    = 1,
    HasMul    = 1,
    HasDiv    = 1,
    HasNegate = 1,
    HasSqrt   = 1,
    HasAbs    = 0,
    HasAbs2   = 0,
    HasMin    = 0,
    HasMax    = 0,
    HasSetLinear = 0
  };
};

#else

template<> struct packet_traits<std::complex<double> >  : default_packet_traits
{
  typedef Packet1cd type;
  typedef Packet1cd half;
  enum {
    Vectorizable = 1,
    AlignedOnScalar = 0,
    size = 1,
    HasHalfPacket = 0,

    HasAdd    = 1,
    HasSub    = 1,
    HasMul    = 1,
    HasDiv    = 1,
    HasNegate = 1,
    HasSqrt   = 1,
    HasAbs    = 0,
    HasAbs2   = 0,
    HasMin    = 0,
    HasMax    = 0,
    HasSetLinear = 0
  };
};

#endif

template<> struct unpacket_traits<Packet1cd> {
  typedef std::complex<double> type;
  typedef Packet1cd half;
  typedef Packet2d as_real;
  enum {
    size=1,
    alignment=Aligned16,
    vectorizable=true,
    masked_load_available=false,
    masked_store_available=false
  };
};

#ifdef EIGEN_VECTORIZE_AVX
template<> struct unpacket_traits<Packet2cd> {
  typedef std::complex<double> type;
  typedef Packet1cd half;
  typedef Packet4d as_real;
  enum {
    size=2,
    alignment=Aligned32,
    vectorizable=true,
    masked_load_available=false,
    masked_store_available=false
  };
};
#endif

#ifdef EIGEN_VECTORIZE_AVX512
template<> struct unpacket_traits<Packet4cd> {
  typedef std::complex<double> type;
  typedef Packet2cd half;
  typedef Packet8d as_real;
  enum {
    size = 4,
    alignment = unpacket_traits<Packet8d>::alignment,
    vectorizable=true,
    masked_load_available=false,
    masked_store_available=false
  };
};
#endif

template<> EIGEN_STRONG_INLINE Packet1cd padd<Packet1cd>(const Packet1cd& a, const Packet1cd& b) { return Packet1cd(_mm_add_pd(a.v,b.v)); }
template<> EIGEN_STRONG_INLINE Packet1cd psub<Packet1cd>(const Packet1cd& a, const Packet1cd& b) { return Packet1cd(_mm_sub_pd(a.v,b.v)); }
template<> EIGEN_STRONG_INLINE Packet1cd pnegate(const Packet1cd& a) { return Packet1cd(pnegate(Packet2d(a.v))); }
template<> EIGEN_STRONG_INLINE Packet1cd pconj(const Packet1cd& a)
{
  const __m128d mask = _mm_castsi128_pd(_mm_set_epi32(0x80000000,0x0,0x0,0x0));
  return Packet1cd(_mm_xor_pd(a.v,mask));
}

template<> EIGEN_STRONG_INLINE Packet1cd pmul<Packet1cd>(const Packet1cd& a, const Packet1cd& b)
{
  #ifdef EIGEN_VECTORIZE_SSE3
  return Packet1cd(_mm_addsub_pd(_mm_mul_pd(_mm_movedup_pd(a.v), b.v),
                                 _mm_mul_pd(vec2d_swizzle1(a.v, 1, 1),
                                            vec2d_swizzle1(b.v, 1, 0))));
  #else
  const __m128d mask = _mm_castsi128_pd(_mm_set_epi32(0x0,0x0,0x80000000,0x0));
  return Packet1cd(_mm_add_pd(_mm_mul_pd(vec2d_swizzle1(a.v, 0, 0), b.v),
                              _mm_xor_pd(_mm_mul_pd(vec2d_swizzle1(a.v, 1, 1),
                                                    vec2d_swizzle1(b.v, 1, 0)), mask)));
  #endif
}

template<> EIGEN_STRONG_INLINE Packet1cd ptrue  <Packet1cd>(const Packet1cd& a) { return Packet1cd(ptrue(Packet2d(a.v))); }
template<> EIGEN_STRONG_INLINE Packet1cd pand   <Packet1cd>(const Packet1cd& a, const Packet1cd& b) { return Packet1cd(_mm_and_pd(a.v,b.v)); }
template<> EIGEN_STRONG_INLINE Packet1cd por    <Packet1cd>(const Packet1cd& a, const Packet1cd& b) { return Packet1cd(_mm_or_pd(a.v,b.v)); }
template<> EIGEN_STRONG_INLINE Packet1cd pxor   <Packet1cd>(const Packet1cd& a, const Packet1cd& b) { return Packet1cd(_mm_xor_pd(a.v,b.v)); }
template<> EIGEN_STRONG_INLINE Packet1cd pandnot<Packet1cd>(const Packet1cd& a, const Packet1cd& b) { return Packet1cd(_mm_andnot_pd(b.v,a.v)); }

// FIXME force unaligned load, this is a temporary fix
template<> EIGEN_STRONG_INLINE Packet1cd pload <Packet1cd>(const std::complex<double>* from)
{ EIGEN_DEBUG_ALIGNED_LOAD return Packet1cd(pload<Packet2d>((const double*)from)); }
template<> EIGEN_STRONG_INLINE Packet1cd ploadu<Packet1cd>(const std::complex<double>* from)
{ EIGEN_DEBUG_UNALIGNED_LOAD return Packet1cd(ploadu<Packet2d>((const double*)from)); }
template<> EIGEN_STRONG_INLINE Packet1cd pset1<Packet1cd>(const std::complex<double>&  from)
{ /* here we really have to use unaligned loads :( */ return ploadu<Packet1cd>(&from); }

template<> EIGEN_STRONG_INLINE Packet1cd ploaddup<Packet1cd>(const std::complex<double>* from) { return pset1<Packet1cd>(*from); }

// FIXME force unaligned store, this is a temporary fix
template<> EIGEN_STRONG_INLINE void pstore <std::complex<double> >(std::complex<double> *   to, const Packet1cd& from) { EIGEN_DEBUG_ALIGNED_STORE pstore((double*)to, Packet2d(from.v)); }
template<> EIGEN_STRONG_INLINE void pstoreu<std::complex<double> >(std::complex<double> *   to, const Packet1cd& from) { EIGEN_DEBUG_UNALIGNED_STORE pstoreu((double*)to, Packet2d(from.v)); }

template<> EIGEN_STRONG_INLINE void prefetch<std::complex<double> >(const std::complex<double> *   addr) { _mm_prefetch((SsePrefetchPtrType)(addr), _MM_HINT_T0); }

template<> EIGEN_STRONG_INLINE std::complex<double>  pfirst<Packet1cd>(const Packet1cd& a)
{
  EIGEN_ALIGN16 double res[2];
  _mm_store_pd(res, a.v);
  return std::complex<double>(res[0],res[1]);
}

template<> EIGEN_STRONG_INLINE Packet1cd preverse(const Packet1cd& a) { return a; }

template<> EIGEN_STRONG_INLINE std::complex<double> predux<Packet1cd>(const Packet1cd& a)
{
  return pfirst(a);
}

template<> EIGEN_STRONG_INLINE std::complex<double> predux_mul<Packet1cd>(const Packet1cd& a)
{
  return pfirst(a);
}

EIGEN_MAKE_CONJ_HELPER_CPLX_REAL(Packet1cd,Packet2d)

template<> EIGEN_STRONG_INLINE Packet1cd pdiv<Packet1cd>(const Packet1cd& a, const Packet1cd& b)
{
  return pdiv_complex(a, b);
}

EIGEN_STRONG_INLINE Packet1cd pcplxflip/* <Packet1cd> */(const Packet1cd& x)
{
  return Packet1cd(preverse(Packet2d(x.v)));
}

EIGEN_DEVICE_FUNC inline void
ptranspose(PacketBlock<Packet2cf,2>& kernel) {
  __m128d w1 = _mm_castps_pd(kernel.packet[0].v);
  __m128d w2 = _mm_castps_pd(kernel.packet[1].v);

  __m128 tmp = _mm_castpd_ps(_mm_unpackhi_pd(w1, w2));
  kernel.packet[0].v = _mm_castpd_ps(_mm_unpacklo_pd(w1, w2));
  kernel.packet[1].v = tmp;
}

template<> EIGEN_STRONG_INLINE Packet2cf pcmp_eq(const Packet2cf& a, const Packet2cf& b)
{
  __m128 eq = _mm_cmpeq_ps(a.v, b.v);
  return Packet2cf(pand<Packet4f>(eq, vec4f_swizzle1(eq, 1, 0, 3, 2)));
}

template<> EIGEN_STRONG_INLINE Packet1cd pcmp_eq(const Packet1cd& a, const Packet1cd& b)
{
  __m128d eq = _mm_cmpeq_pd(a.v, b.v);
  return Packet1cd(pand<Packet2d>(eq, vec2d_swizzle1(eq, 1, 0)));
}

template<>  EIGEN_STRONG_INLINE Packet2cf pblend(const Selector<2>& ifPacket, const Packet2cf& thenPacket, const Packet2cf& elsePacket) {
  __m128d result = pblend<Packet2d>(ifPacket, _mm_castps_pd(thenPacket.v), _mm_castps_pd(elsePacket.v));
  return Packet2cf(_mm_castpd_ps(result));
}

template<> EIGEN_STRONG_INLINE Packet1cd psqrt<Packet1cd>(const Packet1cd& a) {
  return psqrt_complex<Packet1cd>(a);
}

template<> EIGEN_STRONG_INLINE Packet2cf psqrt<Packet2cf>(const Packet2cf& a) {
  return psqrt_complex<Packet2cf>(a);
}

#ifdef EIGEN_VECTORIZE_AVX

template<> EIGEN_STRONG_INLINE Packet2cd padd<Packet2cd>(const Packet2cd& a, const Packet2cd& b) { return Packet2cd(_mm256_add_pd(a.v,b.v)); }
template<> EIGEN_STRONG_INLINE Packet2cd psub<Packet2cd>(const Packet2cd& a, const Packet2cd& b) { return Packet2cd(_mm256_sub_pd(a.v,b.v)); }
template<> EIGEN_STRONG_INLINE Packet2cd pnegate(const Packet2cd& a) { return Packet2cd(pnegate(a.v)); }
template<> EIGEN_STRONG_INLINE Packet2cd pconj(const Packet2cd& a)
{
  const __m256d mask = _mm256_castsi256_pd(_mm256_set_epi32(0x80000000,0x0,0x0,0x0,0x80000000,0x0,0x0,0x0));
  return Packet2cd(_mm256_xor_pd(a.v,mask));
}

template<> EIGEN_STRONG_INLINE Packet2cd pmul<Packet2cd>(const Packet2cd& a, const Packet2cd& b)
{
  __m256d tmp1 = _mm256_shuffle_pd(a.v,a.v,0x0);
  __m256d even = _mm256_mul_pd(tmp1, b.v);
  __m256d tmp2 = _mm256_shuffle_pd(a.v,a.v,0xF);
  __m256d tmp3 = _mm256_shuffle_pd(b.v,b.v,0x5);
  __m256d odd  = _mm256_mul_pd(tmp2, tmp3);
  return Packet2cd(_mm256_addsub_pd(even, odd));
}

template <>
EIGEN_STRONG_INLINE Packet2cd pcmp_eq(const Packet2cd& a, const Packet2cd& b) {
  __m256d eq = _mm256_cmp_pd(a.v, b.v, _CMP_EQ_OQ);
  return Packet2cd(pand(eq, _mm256_permute_pd(eq, 0x5)));
}

template<> EIGEN_STRONG_INLINE Packet2cd ptrue<Packet2cd>(const Packet2cd& a) { return Packet2cd(ptrue(Packet4d(a.v))); }
template<> EIGEN_STRONG_INLINE Packet2cd pand   <Packet2cd>(const Packet2cd& a, const Packet2cd& b) { return Packet2cd(_mm256_and_pd(a.v,b.v)); }
template<> EIGEN_STRONG_INLINE Packet2cd por    <Packet2cd>(const Packet2cd& a, const Packet2cd& b) { return Packet2cd(_mm256_or_pd(a.v,b.v)); }
template<> EIGEN_STRONG_INLINE Packet2cd pxor   <Packet2cd>(const Packet2cd& a, const Packet2cd& b) { return Packet2cd(_mm256_xor_pd(a.v,b.v)); }
template<> EIGEN_STRONG_INLINE Packet2cd pandnot<Packet2cd>(const Packet2cd& a, const Packet2cd& b) { return Packet2cd(_mm256_andnot_pd(b.v,a.v)); }

template<> EIGEN_STRONG_INLINE Packet2cd pload <Packet2cd>(const std::complex<double>* from)
{ EIGEN_DEBUG_ALIGNED_LOAD return Packet2cd(pload<Packet4d>((const double*)from)); }
template<> EIGEN_STRONG_INLINE Packet2cd ploadu<Packet2cd>(const std::complex<double>* from)
{ EIGEN_DEBUG_UNALIGNED_LOAD return Packet2cd(ploadu<Packet4d>((const double*)from)); }

template<> EIGEN_STRONG_INLINE Packet2cd pset1<Packet2cd>(const std::complex<double>& from)
{
  // in case casting to a __m128d* is really not safe, then we can still fallback to this version: (much slower though)
//   return Packet2cd(_mm256_loadu2_m128d((const double*)&from,(const double*)&from));
    return Packet2cd(_mm256_broadcast_pd((const __m128d*)(const void*)&from));
}

template<> EIGEN_STRONG_INLINE Packet2cd ploaddup<Packet2cd>(const std::complex<double>* from) { return pset1<Packet2cd>(*from); }

template<> EIGEN_STRONG_INLINE void pstore <std::complex<double> >(std::complex<double> *   to, const Packet2cd& from) { EIGEN_DEBUG_ALIGNED_STORE pstore((double*)to, from.v); }
template<> EIGEN_STRONG_INLINE void pstoreu<std::complex<double> >(std::complex<double> *   to, const Packet2cd& from) { EIGEN_DEBUG_UNALIGNED_STORE pstoreu((double*)to, from.v); }

template<> EIGEN_DEVICE_FUNC inline Packet2cd pgather<std::complex<double>, Packet2cd>(const std::complex<double>* from, Index stride)
{
  return Packet2cd(_mm256_set_pd(std::imag(from[1*stride]), std::real(from[1*stride]),
				 std::imag(from[0*stride]), std::real(from[0*stride])));
}

template<> EIGEN_DEVICE_FUNC inline void pscatter<std::complex<double>, Packet2cd>(std::complex<double>* to, const Packet2cd& from, Index stride)
{
  __m128d low = _mm256_extractf128_pd(from.v, 0);
  to[stride*0] = std::complex<double>(_mm_cvtsd_f64(low), _mm_cvtsd_f64(_mm_shuffle_pd(low, low, 1)));
  __m128d high = _mm256_extractf128_pd(from.v, 1);
  to[stride*1] = std::complex<double>(_mm_cvtsd_f64(high), _mm_cvtsd_f64(_mm_shuffle_pd(high, high, 1)));
}

template<> EIGEN_STRONG_INLINE std::complex<double> pfirst<Packet2cd>(const Packet2cd& a)
{
  __m128d low = _mm256_extractf128_pd(a.v, 0);
  EIGEN_ALIGN16 double res[2];
  _mm_store_pd(res, low);
  return std::complex<double>(res[0],res[1]);
}

template<> EIGEN_STRONG_INLINE Packet2cd preverse(const Packet2cd& a) {
  __m256d result = _mm256_permute2f128_pd(a.v, a.v, 1);
  return Packet2cd(result);
}

template<> EIGEN_STRONG_INLINE std::complex<double> predux<Packet2cd>(const Packet2cd& a)
{
  return predux(padd(Packet1cd(_mm256_extractf128_pd(a.v,0)),
                     Packet1cd(_mm256_extractf128_pd(a.v,1))));
}

template<> EIGEN_STRONG_INLINE std::complex<double> predux_mul<Packet2cd>(const Packet2cd& a)
{
  return predux(pmul(Packet1cd(_mm256_extractf128_pd(a.v,0)),
                     Packet1cd(_mm256_extractf128_pd(a.v,1))));
}

EIGEN_MAKE_CONJ_HELPER_CPLX_REAL(Packet2cd,Packet4d)

template<> EIGEN_STRONG_INLINE Packet2cd pdiv<Packet2cd>(const Packet2cd& a, const Packet2cd& b)
{
  return pdiv_complex(a, b);
}

template<> EIGEN_STRONG_INLINE Packet2cd pcplxflip<Packet2cd>(const Packet2cd& x)
{
  return Packet2cd(_mm256_shuffle_pd(x.v, x.v, 0x5));
}

EIGEN_DEVICE_FUNC inline void
ptranspose(PacketBlock<Packet4cf,4>& kernel) {
  __m256d P0 = _mm256_castps_pd(kernel.packet[0].v);
  __m256d P1 = _mm256_castps_pd(kernel.packet[1].v);
  __m256d P2 = _mm256_castps_pd(kernel.packet[2].v);
  __m256d P3 = _mm256_castps_pd(kernel.packet[3].v);

  __m256d T0 = _mm256_shuffle_pd(P0, P1, 15);
  __m256d T1 = _mm256_shuffle_pd(P0, P1, 0);
  __m256d T2 = _mm256_shuffle_pd(P2, P3, 15);
  __m256d T3 = _mm256_shuffle_pd(P2, P3, 0);

  kernel.packet[1].v = _mm256_castpd_ps(_mm256_permute2f128_pd(T0, T2, 32));
  kernel.packet[3].v = _mm256_castpd_ps(_mm256_permute2f128_pd(T0, T2, 49));
  kernel.packet[0].v = _mm256_castpd_ps(_mm256_permute2f128_pd(T1, T3, 32));
  kernel.packet[2].v = _mm256_castpd_ps(_mm256_permute2f128_pd(T1, T3, 49));
}

EIGEN_DEVICE_FUNC inline void
ptranspose(PacketBlock<Packet2cd,2>& kernel) {
  __m256d tmp = _mm256_permute2f128_pd(kernel.packet[0].v, kernel.packet[1].v, 0+(2<<4));
  kernel.packet[1].v = _mm256_permute2f128_pd(kernel.packet[0].v, kernel.packet[1].v, 1+(3<<4));
 kernel.packet[0].v = tmp;
}

template<> EIGEN_STRONG_INLINE Packet2cd psqrt<Packet2cd>(const Packet2cd& a) {
  return psqrt_complex<Packet2cd>(a);
}

template<> EIGEN_STRONG_INLINE Packet4cf psqrt<Packet4cf>(const Packet4cf& a) {
  return psqrt_complex<Packet4cf>(a);
}

#endif

#ifdef EIGEN_VECTORIZE_AVX512

template<> EIGEN_STRONG_INLINE Packet4cd padd<Packet4cd>(const Packet4cd& a, const Packet4cd& b) { return Packet4cd(_mm512_add_pd(a.v,b.v)); }
template<> EIGEN_STRONG_INLINE Packet4cd psub<Packet4cd>(const Packet4cd& a, const Packet4cd& b) { return Packet4cd(_mm512_sub_pd(a.v,b.v)); }
template<> EIGEN_STRONG_INLINE Packet4cd pnegate(const Packet4cd& a) { return Packet4cd(pnegate(a.v)); }
template<> EIGEN_STRONG_INLINE Packet4cd pconj(const Packet4cd& a)
{
  const __m512d mask = _mm512_castsi512_pd(
          _mm512_set_epi32(0x80000000,0x0,0x0,0x0,0x80000000,0x0,0x0,0x0,
                           0x80000000,0x0,0x0,0x0,0x80000000,0x0,0x0,0x0));
  return Packet4cd(pxor(a.v,mask));
}

template<> EIGEN_STRONG_INLINE Packet4cd pmul<Packet4cd>(const Packet4cd& a, const Packet4cd& b)
{
  __m512d tmp1 = _mm512_shuffle_pd(a.v,a.v,0x0);
  __m512d tmp2 = _mm512_shuffle_pd(a.v,a.v,0xFF);
  __m512d tmp3 = _mm512_shuffle_pd(b.v,b.v,0x55);
  __m512d odd  = _mm512_mul_pd(tmp2, tmp3);
  return Packet4cd(_mm512_fmaddsub_pd(tmp1, b.v, odd));
}

template<> EIGEN_STRONG_INLINE Packet4cd ptrue<Packet4cd>(const Packet4cd& a) { return Packet4cd(ptrue(Packet8d(a.v))); }
template<> EIGEN_STRONG_INLINE Packet4cd pand   <Packet4cd>(const Packet4cd& a, const Packet4cd& b) { return Packet4cd(pand(a.v,b.v)); }
template<> EIGEN_STRONG_INLINE Packet4cd por    <Packet4cd>(const Packet4cd& a, const Packet4cd& b) { return Packet4cd(por(a.v,b.v)); }
template<> EIGEN_STRONG_INLINE Packet4cd pxor   <Packet4cd>(const Packet4cd& a, const Packet4cd& b) { return Packet4cd(pxor(a.v,b.v)); }
template<> EIGEN_STRONG_INLINE Packet4cd pandnot<Packet4cd>(const Packet4cd& a, const Packet4cd& b) { return Packet4cd(pandnot(a.v,b.v)); }

template <>
EIGEN_STRONG_INLINE Packet4cd pcmp_eq(const Packet4cd& a, const Packet4cd& b) {
  __m512d eq = pcmp_eq<Packet8d>(a.v, b.v);
  return Packet4cd(pand(eq, _mm512_permute_pd(eq, 0x55)));
}

template<> EIGEN_STRONG_INLINE Packet4cd pload <Packet4cd>(const std::complex<double>* from)
{ EIGEN_DEBUG_ALIGNED_LOAD return Packet4cd(pload<Packet8d>((const double*)from)); }
template<> EIGEN_STRONG_INLINE Packet4cd ploadu<Packet4cd>(const std::complex<double>* from)
{ EIGEN_DEBUG_UNALIGNED_LOAD return Packet4cd(ploadu<Packet8d>((const double*)from)); }

template<> EIGEN_STRONG_INLINE Packet4cd pset1<Packet4cd>(const std::complex<double>& from)
{
  return Packet4cd(_mm512_castps_pd(_mm512_broadcast_f32x4( _mm_castpd_ps(pset1<Packet1cd>(from).v))));
}

template<> EIGEN_STRONG_INLINE Packet4cd ploaddup<Packet4cd>(const std::complex<double>* from) {
  return Packet4cd(_mm512_insertf64x4(
          _mm512_castpd256_pd512(ploaddup<Packet2cd>(from).v), ploaddup<Packet2cd>(from+1).v, 1));
}

template<> EIGEN_STRONG_INLINE void pstore <std::complex<double> >(std::complex<double> *   to, const Packet4cd& from) { EIGEN_DEBUG_ALIGNED_STORE pstore((double*)to, from.v); }
template<> EIGEN_STRONG_INLINE void pstoreu<std::complex<double> >(std::complex<double> *   to, const Packet4cd& from) { EIGEN_DEBUG_UNALIGNED_STORE pstoreu((double*)to, from.v); }

template<> EIGEN_DEVICE_FUNC inline Packet4cd pgather<std::complex<double>, Packet4cd>(const std::complex<double>* from, Index stride)
{
  return Packet4cd(_mm512_insertf64x4(_mm512_castpd256_pd512(
            _mm256_insertf128_pd(_mm256_castpd128_pd256(ploadu<Packet1cd>(from+0*stride).v), ploadu<Packet1cd>(from+1*stride).v,1)),
            _mm256_insertf128_pd(_mm256_castpd128_pd256(ploadu<Packet1cd>(from+2*stride).v), ploadu<Packet1cd>(from+3*stride).v,1), 1));
}

template<> EIGEN_DEVICE_FUNC inline void pscatter<std::complex<double>, Packet4cd>(std::complex<double>* to, const Packet4cd& from, Index stride)
{
  __m512i fromi = _mm512_castpd_si512(from.v);
  double* tod = (double*)(void*)to;
  _mm_storeu_pd(tod+0*stride, _mm_castsi128_pd(_mm512_extracti32x4_epi32(fromi,0)) );
  _mm_storeu_pd(tod+2*stride, _mm_castsi128_pd(_mm512_extracti32x4_epi32(fromi,1)) );
  _mm_storeu_pd(tod+4*stride, _mm_castsi128_pd(_mm512_extracti32x4_epi32(fromi,2)) );
  _mm_storeu_pd(tod+6*stride, _mm_castsi128_pd(_mm512_extracti32x4_epi32(fromi,3)) );
}

template<> EIGEN_STRONG_INLINE std::complex<double> pfirst<Packet4cd>(const Packet4cd& a)
{
  __m128d low = extract128<0>(a.v);
  EIGEN_ALIGN16 double res[2];
  _mm_store_pd(res, low);
  return std::complex<double>(res[0],res[1]);
}

template<> EIGEN_STRONG_INLINE Packet4cd preverse(const Packet4cd& a) {
  return Packet4cd(_mm512_shuffle_f64x2(a.v, a.v, (shuffle_mask<3,2,1,0>::mask)));
}

template<> EIGEN_STRONG_INLINE std::complex<double> predux<Packet4cd>(const Packet4cd& a)
{
  return predux(padd(Packet2cd(_mm512_extractf64x4_pd(a.v,0)),
                     Packet2cd(_mm512_extractf64x4_pd(a.v,1))));
}

template<> EIGEN_STRONG_INLINE std::complex<double> predux_mul<Packet4cd>(const Packet4cd& a)
{
  return predux_mul(pmul(Packet2cd(_mm512_extractf64x4_pd(a.v,0)),
                         Packet2cd(_mm512_extractf64x4_pd(a.v,1))));
}

EIGEN_MAKE_CONJ_HELPER_CPLX_REAL(Packet4cd,Packet8d)

template<> EIGEN_STRONG_INLINE Packet4cd pdiv<Packet4cd>(const Packet4cd& a, const Packet4cd& b)
{
  return pdiv_complex(a, b);
}

template<> EIGEN_STRONG_INLINE Packet4cd pcplxflip<Packet4cd>(const Packet4cd& x)
{
  return Packet4cd(_mm512_permute_pd(x.v,0x55));
}

EIGEN_DEVICE_FUNC inline void
ptranspose(PacketBlock<Packet8cf,4>& kernel) {
  PacketBlock<Packet8d,4> pb;
  
  pb.packet[0] = _mm512_castps_pd(kernel.packet[0].v);
  pb.packet[1] = _mm512_castps_pd(kernel.packet[1].v);
  pb.packet[2] = _mm512_castps_pd(kernel.packet[2].v);
  pb.packet[3] = _mm512_castps_pd(kernel.packet[3].v);
  ptranspose(pb);
  kernel.packet[0].v = _mm512_castpd_ps(pb.packet[0]);
  kernel.packet[1].v = _mm512_castpd_ps(pb.packet[1]);
  kernel.packet[2].v = _mm512_castpd_ps(pb.packet[2]);
  kernel.packet[3].v = _mm512_castpd_ps(pb.packet[3]);
}

EIGEN_DEVICE_FUNC inline void
ptranspose(PacketBlock<Packet8cf,8>& kernel) {
  PacketBlock<Packet8d,8> pb;
  
  pb.packet[0] = _mm512_castps_pd(kernel.packet[0].v);
  pb.packet[1] = _mm512_castps_pd(kernel.packet[1].v);
  pb.packet[2] = _mm512_castps_pd(kernel.packet[2].v);
  pb.packet[3] = _mm512_castps_pd(kernel.packet[3].v);
  pb.packet[4] = _mm512_castps_pd(kernel.packet[4].v);
  pb.packet[5] = _mm512_castps_pd(kernel.packet[5].v);
  pb.packet[6] = _mm512_castps_pd(kernel.packet[6].v);
  pb.packet[7] = _mm512_castps_pd(kernel.packet[7].v);
  ptranspose(pb);
  kernel.packet[0].v = _mm512_castpd_ps(pb.packet[0]);
  kernel.packet[1].v = _mm512_castpd_ps(pb.packet[1]);
  kernel.packet[2].v = _mm512_castpd_ps(pb.packet[2]);
  kernel.packet[3].v = _mm512_castpd_ps(pb.packet[3]);
  kernel.packet[4].v = _mm512_castpd_ps(pb.packet[4]);
  kernel.packet[5].v = _mm512_castpd_ps(pb.packet[5]);
  kernel.packet[6].v = _mm512_castpd_ps(pb.packet[6]);
  kernel.packet[7].v = _mm512_castpd_ps(pb.packet[7]);
}

EIGEN_DEVICE_FUNC inline void
ptranspose(PacketBlock<Packet4cd,4>& kernel) {
  __m512d T0 = _mm512_shuffle_f64x2(kernel.packet[0].v, kernel.packet[1].v, (shuffle_mask<0,1,0,1>::mask)); // [a0 a1 b0 b1]
  __m512d T1 = _mm512_shuffle_f64x2(kernel.packet[0].v, kernel.packet[1].v, (shuffle_mask<2,3,2,3>::mask)); // [a2 a3 b2 b3]
  __m512d T2 = _mm512_shuffle_f64x2(kernel.packet[2].v, kernel.packet[3].v, (shuffle_mask<0,1,0,1>::mask)); // [c0 c1 d0 d1]
  __m512d T3 = _mm512_shuffle_f64x2(kernel.packet[2].v, kernel.packet[3].v, (shuffle_mask<2,3,2,3>::mask)); // [c2 c3 d2 d3]

  kernel.packet[3] = Packet4cd(_mm512_shuffle_f64x2(T1, T3, (shuffle_mask<1,3,1,3>::mask))); // [a3 b3 c3 d3]
  kernel.packet[2] = Packet4cd(_mm512_shuffle_f64x2(T1, T3, (shuffle_mask<0,2,0,2>::mask))); // [a2 b2 c2 d2]
  kernel.packet[1] = Packet4cd(_mm512_shuffle_f64x2(T0, T2, (shuffle_mask<1,3,1,3>::mask))); // [a1 b1 c1 d1]
  kernel.packet[0] = Packet4cd(_mm512_shuffle_f64x2(T0, T2, (shuffle_mask<0,2,0,2>::mask))); // [a0 b0 c0 d0]
}

template<> EIGEN_STRONG_INLINE Packet4cd psqrt<Packet4cd>(const Packet4cd& a) {
  return psqrt_complex<Packet4cd>(a);
}

template<> EIGEN_STRONG_INLINE Packet8cf psqrt<Packet8cf>(const Packet8cf& a) {
  return psqrt_complex<Packet8cf>(a);
}

#endif

} // end namespace internal

} // end namespace Eigen

#endif // EIGEN_COMPLEX_MIPP_H
