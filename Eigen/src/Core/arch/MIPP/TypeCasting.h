// This file is part of Eigen, a lightweight C++ template library
// for linear algebra.
//
// Copyright (C) 2015 Benoit Steiner <benoit.steiner.goog@gmail.com>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef EIGEN_TYPE_CASTING_MIPP_H
#define EIGEN_TYPE_CASTING_MIPP_H

#include "../../InternalHeaderCheck.h"

#undef min
#undef max
#include "../../../../../../MIPP/src/mipp.h"

namespace Eigen {

namespace internal {

#ifndef EIGEN_VECTORIZE_AVX
template <>
struct type_casting_traits<float, int> {
  enum {
    VectorizedCast = 1,
    SrcCoeffRatio = 1,
    TgtCoeffRatio = 1
  };
};

template <>
struct type_casting_traits<int, float> {
  enum {
    VectorizedCast = 1,
    SrcCoeffRatio = 1,
    TgtCoeffRatio = 1
  };
};

template <>
struct type_casting_traits<double, float> {
  enum {
    VectorizedCast = 1,
    SrcCoeffRatio = 2,
    TgtCoeffRatio = 1
  };
};

template <>
struct type_casting_traits<float, double> {
  enum {
    VectorizedCast = 1,
    SrcCoeffRatio = 1,
    TgtCoeffRatio = 2
  };
};
#else

// For now we use SSE to handle integers, so we can't use AVX instructions to cast
// from int to float
template <>
struct type_casting_traits<float, int> {
  enum {
    VectorizedCast = 0,
    SrcCoeffRatio = 1,
    TgtCoeffRatio = 1
  };
};

template <>
struct type_casting_traits<int, float> {
  enum {
    VectorizedCast = 0,
    SrcCoeffRatio = 1,
    TgtCoeffRatio = 1
  };
};
#endif


#ifndef EIGEN_VECTORIZE_AVX512

template <>
struct type_casting_traits<Eigen::half, float> {
  enum {
    VectorizedCast = 1,
    SrcCoeffRatio = 1,
    TgtCoeffRatio = 1
  };
};


template <>
struct type_casting_traits<float, Eigen::half> {
  enum {
    VectorizedCast = 1,
    SrcCoeffRatio = 1,
    TgtCoeffRatio = 1
  };
};

template <>
struct type_casting_traits<bfloat16, float> {
  enum {
    VectorizedCast = 1,
    SrcCoeffRatio = 1,
    TgtCoeffRatio = 1
  };
};

template <>
struct type_casting_traits<float, bfloat16> {
  enum {
    VectorizedCast = 1,
    SrcCoeffRatio = 1,
    TgtCoeffRatio = 1
  };
};

#endif  // EIGEN_VECTORIZE_AVX512

template<> EIGEN_STRONG_INLINE Packet4i pcast<Packet4f, Packet4i>(const Packet4f& a) {
  return _mm_cvttps_epi32(a);
}

template<> EIGEN_STRONG_INLINE Packet4f pcast<Packet4i, Packet4f>(const Packet4i& a) {
  return _mm_cvtepi32_ps(a);
}

template<> EIGEN_STRONG_INLINE Packet4f pcast<Packet2d, Packet4f>(const Packet2d& a, const Packet2d& b) {
  return _mm_shuffle_ps(_mm_cvtpd_ps(a), _mm_cvtpd_ps(b), (1 << 2) | (1 << 6));
}

template<> EIGEN_STRONG_INLINE Packet2d pcast<Packet4f, Packet2d>(const Packet4f& a) {
  // Simply discard the second half of the input
  return _mm_cvtps_pd(a);
}

template<> EIGEN_STRONG_INLINE Packet4i preinterpret<Packet4i,Packet4f>(const Packet4f& a) {
  return _mm_castps_si128(a);
}

template<> EIGEN_STRONG_INLINE Packet4f preinterpret<Packet4f,Packet4i>(const Packet4i& a) {
  return _mm_castsi128_ps(a);
}

template<> EIGEN_STRONG_INLINE Packet2d preinterpret<Packet2d,Packet4i>(const Packet4i& a) {
  return _mm_castsi128_pd(a);
}

template<> EIGEN_STRONG_INLINE Packet4i preinterpret<Packet4i,Packet2d>(const Packet2d& a) {
  return _mm_castpd_si128(a);
}

template<> EIGEN_STRONG_INLINE Packet8i pcast<Packet8f, Packet8i>(const Packet8f& a) {
  return _mm256_cvttps_epi32(a);
}

template<> EIGEN_STRONG_INLINE Packet8f pcast<Packet8i, Packet8f>(const Packet8i& a) {
  return _mm256_cvtepi32_ps(a);
}

template<> EIGEN_STRONG_INLINE Packet8i preinterpret<Packet8i,Packet8f>(const Packet8f& a) {
  return _mm256_castps_si256(a);
}

template<> EIGEN_STRONG_INLINE Packet8f preinterpret<Packet8f,Packet8i>(const Packet8i& a) {
  return _mm256_castsi256_ps(a);
}

template<> EIGEN_STRONG_INLINE Packet8f pcast<Packet8h, Packet8f>(const Packet8h& a) {
  return half2float(a);
}

template<> EIGEN_STRONG_INLINE Packet8f pcast<Packet8bf, Packet8f>(const Packet8bf& a) {
  return Bf16ToF32(a);
}

template<> EIGEN_STRONG_INLINE Packet8h pcast<Packet8f, Packet8h>(const Packet8f& a) {
  return float2half(a);
}

template<> EIGEN_STRONG_INLINE Packet8bf pcast<Packet8f, Packet8bf>(const Packet8f& a) {
  return F32ToBf16(a);
}

} // end namespace internal

} // end namespace Eigen

#endif // EIGEN_TYPE_CASTING_MIPP_H
