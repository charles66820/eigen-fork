#ifndef EIGEN_PACKET_MATH_OLD_FUN_MIPP_H
#define EIGEN_PACKET_MATH_OLD_FUN_MIPP_H

// definition in `Eigen/src/Core/GenericPacketMath.h`

template<typename Packet> EIGEN_DEVICE_FUNC inline Packet
pset1_old(const typename unpacket_traits<Packet>::type& a);

template <> EIGEN_STRONG_INLINE Packet4l pset1_old<Packet4l>(const int64_t& from) {
  return _mm256_set1_epi64x(from);
}

template<> EIGEN_STRONG_INLINE Packet4f pset1_old<Packet4f>(const float&  from) { return _mm_set_ps1(from); }
template<> EIGEN_STRONG_INLINE Packet2d pset1_old<Packet2d>(const double& from) { return _mm_set1_pd(from); }
template<> EIGEN_STRONG_INLINE Packet4i pset1_old<Packet4i>(const int&    from) { return _mm_set1_epi32(from); }
template<> EIGEN_STRONG_INLINE Packet16b pset1_old<Packet16b>(const bool&    from) { return _mm_set1_epi8(static_cast<char>(from)); }

template<> EIGEN_STRONG_INLINE Packet8f pset1_old<Packet8f>(const float&  from) { return _mm256_set1_ps(from); }
template<> EIGEN_STRONG_INLINE Packet4d pset1_old<Packet4d>(const double& from) { return _mm256_set1_pd(from); }
template<> EIGEN_STRONG_INLINE Packet8i pset1_old<Packet8i>(const int&    from) { return _mm256_set1_epi32(from); }

template<> EIGEN_STRONG_INLINE Packet8h pset1_old<Packet8h>(const Eigen::half& from) {
  return _mm_set1_epi16(numext::bit_cast<numext::uint16_t>(from));
}

template<> EIGEN_STRONG_INLINE Packet8bf pset1_old<Packet8bf>(const bfloat16& from) {
  return _mm_set1_epi16(numext::bit_cast<numext::uint16_t>(from));
}

/** \internal \returns packet of zeros */
template<typename Packet> EIGEN_DEVICE_FUNC inline Packet
pzero_old(const Packet& a) {
  return pzero_impl<Packet>::run(a);
}

template <> EIGEN_STRONG_INLINE Packet4l pzero_old(const Packet4l& /*a*/) { return _mm256_setzero_si256(); }

template<> EIGEN_STRONG_INLINE Packet4f pzero_old(const Packet4f& /*a*/) { return _mm_setzero_ps(); }
template<> EIGEN_STRONG_INLINE Packet2d pzero_old(const Packet2d& /*a*/) { return _mm_setzero_pd(); }
template<> EIGEN_STRONG_INLINE Packet4i pzero_old(const Packet4i& /*a*/) { return _mm_setzero_si128(); }

template<> EIGEN_STRONG_INLINE Packet8f pzero_old(const Packet8f& /*a*/) { return _mm256_setzero_ps(); }
template<> EIGEN_STRONG_INLINE Packet4d pzero_old(const Packet4d& /*a*/) { return _mm256_setzero_pd(); }
template<> EIGEN_STRONG_INLINE Packet8i pzero_old(const Packet8i& /*a*/) { return _mm256_setzero_si256(); }

template<typename Packet> EIGEN_DEVICE_FUNC inline Packet
pload_old(const typename unpacket_traits<Packet>::type* from) { return *from; }

template <>
EIGEN_STRONG_INLINE Packet4l pload_old<Packet4l>(const int64_t* from) {
  EIGEN_DEBUG_ALIGNED_LOAD return _mm256_load_si256(reinterpret_cast<const __m256i*>(from));
}

template<> EIGEN_STRONG_INLINE Packet4f pload_old<Packet4f>(const float*   from) { EIGEN_DEBUG_ALIGNED_LOAD return _mm_load_ps(from); }
template<> EIGEN_STRONG_INLINE Packet2d pload_old<Packet2d>(const double*  from) { EIGEN_DEBUG_ALIGNED_LOAD return _mm_load_pd(from); }
template<> EIGEN_STRONG_INLINE Packet4i pload_old<Packet4i>(const int*     from) { EIGEN_DEBUG_ALIGNED_LOAD return _mm_load_si128(reinterpret_cast<const __m128i*>(from)); }
template<> EIGEN_STRONG_INLINE Packet16b pload_old<Packet16b>(const bool*     from) { EIGEN_DEBUG_ALIGNED_LOAD return  _mm_load_si128(reinterpret_cast<const __m128i*>(from)); }

template<> EIGEN_STRONG_INLINE Packet8f pload_old<Packet8f>(const float*   from) { EIGEN_DEBUG_ALIGNED_LOAD return _mm256_load_ps(from); }
template<> EIGEN_STRONG_INLINE Packet4d pload_old<Packet4d>(const double*  from) { EIGEN_DEBUG_ALIGNED_LOAD return _mm256_load_pd(from); }
template<> EIGEN_STRONG_INLINE Packet8i pload_old<Packet8i>(const int*     from) { EIGEN_DEBUG_ALIGNED_LOAD return _mm256_load_si256(reinterpret_cast<const __m256i*>(from)); }

template<> EIGEN_STRONG_INLINE Packet8h pload_old<Packet8h>(const Eigen::half* from) {
  return _mm_load_si128(reinterpret_cast<const __m128i*>(from));
}

template<> EIGEN_STRONG_INLINE Packet8bf pload_old<Packet8bf>(const bfloat16* from) {
  return _mm_load_si128(reinterpret_cast<const __m128i*>(from));
}

template<typename Packet> EIGEN_DEVICE_FUNC inline Packet
ploadu_old(const typename unpacket_traits<Packet>::type* from) { return *from; }

template <>
EIGEN_STRONG_INLINE Packet4f ploadu_old<Packet4f>(const float* from) {
  EIGEN_DEBUG_UNALIGNED_LOAD
  return _mm_loadu_ps(from);
}
template <>
EIGEN_STRONG_INLINE Packet2d ploadu_old<Packet2d>(const double* from) {
  EIGEN_DEBUG_UNALIGNED_LOAD
  return _mm_loadu_pd(from);
}
template <>
EIGEN_STRONG_INLINE Packet4i ploadu_old<Packet4i>(const int* from) {
  EIGEN_DEBUG_UNALIGNED_LOAD
  return _mm_loadu_si128(reinterpret_cast<const __m128i*>(from));
}
template <>
EIGEN_STRONG_INLINE Packet16b ploadu_old<Packet16b>(const bool* from) {
  EIGEN_DEBUG_UNALIGNED_LOAD
  return _mm_loadu_si128(reinterpret_cast<const __m128i*>(from));
}

template <>
EIGEN_STRONG_INLINE Packet8f ploadu_old<Packet8f>(const float* from) {
  EIGEN_DEBUG_UNALIGNED_LOAD return _mm256_loadu_ps(from);
}
template <>
EIGEN_STRONG_INLINE Packet4d ploadu_old<Packet4d>(const double* from) {
  EIGEN_DEBUG_UNALIGNED_LOAD return _mm256_loadu_pd(from);
}
template <>
EIGEN_STRONG_INLINE Packet8i ploadu_old<Packet8i>(const int* from) {
  EIGEN_DEBUG_UNALIGNED_LOAD return _mm256_loadu_si256(reinterpret_cast<const __m256i*>(from));
}

template <>
EIGEN_STRONG_INLINE Packet8h ploadu_old<Packet8h>(const Eigen::half* from) {
  return _mm_loadu_si128(reinterpret_cast<const __m128i*>(from));
}
template <>
EIGEN_STRONG_INLINE Packet8bf ploadu_old<Packet8bf>(const bfloat16* from) {
  return _mm_loadu_si128(reinterpret_cast<const __m128i*>(from));
}

template <>
EIGEN_STRONG_INLINE Packet4l ploadu_old<Packet4l>(const int64_t* from) {
  EIGEN_DEBUG_UNALIGNED_LOAD return _mm256_loadu_si256(reinterpret_cast<const __m256i*>(from));
}

template<typename Packet> EIGEN_DEVICE_FUNC inline Packet
padd_old(const Packet& a, const Packet& b) { return a+b; }
// Avoid compiler warning for boolean algebra.
template<> EIGEN_DEVICE_FUNC inline bool
padd_old(const bool& a, const bool& b) { return a || b; }

template <>
EIGEN_STRONG_INLINE Packet4f padd_old<Packet4f>(const Packet4f& a, const Packet4f& b) {
  return _mm_add_ps(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet2d padd_old<Packet2d>(const Packet2d& a, const Packet2d& b) {
  return _mm_add_pd(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet4i padd_old<Packet4i>(const Packet4i& a, const Packet4i& b) {
  return _mm_add_epi32(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet16b padd_old<Packet16b>(const Packet16b& a, const Packet16b& b) {
  return _mm_or_si128(a, b);
}

template <>
EIGEN_STRONG_INLINE Packet8f padd_old<Packet8f>(const Packet8f& a, const Packet8f& b) {
  return _mm256_add_ps(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet4d padd_old<Packet4d>(const Packet4d& a, const Packet4d& b) {
  return _mm256_add_pd(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet8i padd_old<Packet8i>(const Packet8i& a, const Packet8i& b) {
#ifdef EIGEN_VECTORIZE_AVX2
  return _mm256_add_epi32(a, b);
#else
  __m128i lo = _mm_add_epi32(_mm256_extractf128_si256(a, 0), _mm256_extractf128_si256(b, 0));
  __m128i hi = _mm_add_epi32(_mm256_extractf128_si256(a, 1), _mm256_extractf128_si256(b, 1));
  return _mm256_insertf128_si256(_mm256_castsi128_si256(lo), (hi), 1);
#endif
}

template <>
EIGEN_STRONG_INLINE Packet8h padd_old<Packet8h>(const Packet8h& a, const Packet8h& b) {
  Packet8f af = half2float(a);
  Packet8f bf = half2float(b);
  Packet8f rf = padd(af, bf);
  return float2half(rf);
}
template <>
EIGEN_STRONG_INLINE Packet8bf padd_old<Packet8bf>(const Packet8bf& a, const Packet8bf& b) {
  return F32ToBf16(padd<Packet8f>(Bf16ToF32(a), Bf16ToF32(b)));
}

template <>
EIGEN_STRONG_INLINE Packet4l padd_old<Packet4l>(const Packet4l& a, const Packet4l& b) {
  return _mm256_add_epi64(a, b);
}

template<typename Packet> EIGEN_DEVICE_FUNC inline Packet
psub_old(const Packet& a, const Packet& b) { return a-b; }

template <>
EIGEN_STRONG_INLINE Packet4f psub_old<Packet4f>(const Packet4f& a, const Packet4f& b) {
  return _mm_sub_ps(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet2d psub_old<Packet2d>(const Packet2d& a, const Packet2d& b) {
  return _mm_sub_pd(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet4i psub_old<Packet4i>(const Packet4i& a, const Packet4i& b) {
  return _mm_sub_epi32(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet16b psub_old<Packet16b>(const Packet16b& a, const Packet16b& b) {
  return _mm_xor_si128(a, b);
}

template <>
EIGEN_STRONG_INLINE Packet8f psub_old<Packet8f>(const Packet8f& a, const Packet8f& b) {
  return _mm256_sub_ps(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet4d psub_old<Packet4d>(const Packet4d& a, const Packet4d& b) {
  return _mm256_sub_pd(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet8i psub_old<Packet8i>(const Packet8i& a, const Packet8i& b) {
#ifdef EIGEN_VECTORIZE_AVX2
  return _mm256_sub_epi32(a, b);
#else
  __m128i lo = _mm_sub_epi32(_mm256_extractf128_si256(a, 0), _mm256_extractf128_si256(b, 0));
  __m128i hi = _mm_sub_epi32(_mm256_extractf128_si256(a, 1), _mm256_extractf128_si256(b, 1));
  return _mm256_insertf128_si256(_mm256_castsi128_si256(lo), (hi), 1);
#endif
}

template <>
EIGEN_STRONG_INLINE Packet8h psub_old<Packet8h>(const Packet8h& a, const Packet8h& b) {
  Packet8f af = half2float(a);
  Packet8f bf = half2float(b);
  Packet8f rf = psub_old(af, bf);
  return float2half(rf);
}

template <>
EIGEN_STRONG_INLINE Packet8bf psub_old<Packet8bf>(const Packet8bf& a, const Packet8bf& b) {
  return F32ToBf16(psub_old<Packet8f>(Bf16ToF32(a), Bf16ToF32(b)));
}

template <>
EIGEN_STRONG_INLINE Packet4l psub_old<Packet4l>(const Packet4l& a, const Packet4l& b) {
  return _mm256_sub_epi64(a, b);
}

template<typename Packet> EIGEN_DEVICE_FUNC inline Packet
pnegate_old(const Packet& a) { return -a; }

template<> EIGEN_DEVICE_FUNC inline bool
pnegate_old(const bool& a) { return !a; }

template <>
EIGEN_STRONG_INLINE Packet4f pnegate_old(const Packet4f& a) {
  const Packet4f mask = _mm_castsi128_ps(_mm_setr_epi32(0x80000000, 0x80000000, 0x80000000, 0x80000000));
  return _mm_xor_ps(a, mask);
}
template <>
EIGEN_STRONG_INLINE Packet2d pnegate_old(const Packet2d& a) {
  const Packet2d mask = _mm_castsi128_pd(_mm_setr_epi32(0x0, 0x80000000, 0x0, 0x80000000));
  return _mm_xor_pd(a, mask);
}
template <>
EIGEN_STRONG_INLINE Packet4i pnegate_old(const Packet4i& a) {
  return psub_old(Packet4i(_mm_setr_epi32(0, 0, 0, 0)), a);
}

template <>
EIGEN_STRONG_INLINE Packet16b pnegate_old(const Packet16b& a) {
  return psub_old(pset1_old<Packet16b>(false), a);
}

template <>
EIGEN_STRONG_INLINE Packet8f pnegate_old(const Packet8f& a) {
  return _mm256_sub_ps(_mm256_set1_ps(0.0), a);
}
template <>
EIGEN_STRONG_INLINE Packet4d pnegate_old(const Packet4d& a) {
  return _mm256_sub_pd(_mm256_set1_pd(0.0), a);
}

template <>
EIGEN_STRONG_INLINE Packet8i pnegate_old(const Packet8i& a) {
  return psub_old(pzero_old(a), a);
}

template <>
EIGEN_STRONG_INLINE Packet8h pnegate_old(const Packet8h& a) {
  Packet8h sign_mask = _mm_set1_epi16(static_cast<numext::uint16_t>(0x8000));
  return _mm_xor_si128(a, sign_mask);
}

template <>
EIGEN_STRONG_INLINE Packet8bf pnegate_old(const Packet8bf& a) {
  Packet8bf sign_mask = _mm_set1_epi16(static_cast<numext::uint16_t>(0x8000));
  return _mm_xor_si128(a, sign_mask);
}

template <>
EIGEN_STRONG_INLINE Packet4l pnegate_old(const Packet4l& a) {
  return psub_old(pzero_old(a), a);
}

template<typename Packet> EIGEN_DEVICE_FUNC inline Packet
pmul_old(const Packet& a, const Packet& b) { return a*b; }
// Avoid compiler warning for boolean algebra.
template<> EIGEN_DEVICE_FUNC inline bool
pmul_old(const bool& a, const bool& b) { return a && b; }

template <>
EIGEN_STRONG_INLINE Packet4f pmul_old<Packet4f>(const Packet4f& a, const Packet4f& b) {
  return _mm_mul_ps(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet2d pmul_old<Packet2d>(const Packet2d& a, const Packet2d& b) {
  return _mm_mul_pd(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet4i pmul_old<Packet4i>(const Packet4i& a, const Packet4i& b) {
#ifdef EIGEN_VECTORIZE_SSE4_1
  return _mm_mullo_epi32(a, b);
#else
  // this version is slightly faster than 4 scalar products
  return vec4i_swizzle1(
      vec4i_swizzle2(_mm_mul_epu32(a, b), _mm_mul_epu32(vec4i_swizzle1(a, 1, 0, 3, 2), vec4i_swizzle1(b, 1, 0, 3, 2)),
                     0, 2, 0, 2),
      0, 2, 1, 3);
#endif
}

template <>
EIGEN_STRONG_INLINE Packet16b pmul_old<Packet16b>(const Packet16b& a, const Packet16b& b) {
  return _mm_and_si128(a, b);
}

template <>
EIGEN_STRONG_INLINE Packet8f pmul_old<Packet8f>(const Packet8f& a, const Packet8f& b) {
  return _mm256_mul_ps(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet4d pmul_old<Packet4d>(const Packet4d& a, const Packet4d& b) {
  return _mm256_mul_pd(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet8i pmul_old<Packet8i>(const Packet8i& a, const Packet8i& b) {
#ifdef EIGEN_VECTORIZE_AVX2
  return _mm256_mullo_epi32(a, b);
#else
  const __m128i lo = _mm_mullo_epi32(_mm256_extractf128_si256(a, 0), _mm256_extractf128_si256(b, 0));
  const __m128i hi = _mm_mullo_epi32(_mm256_extractf128_si256(a, 1), _mm256_extractf128_si256(b, 1));
  return _mm256_insertf128_si256(_mm256_castsi128_si256(lo), (hi), 1);
#endif
}

template <>
EIGEN_STRONG_INLINE Packet8h pmul_old<Packet8h>(const Packet8h& a, const Packet8h& b) {
  Packet8f af = half2float(a);
  Packet8f bf = half2float(b);
  Packet8f rf = pmul_old(af, bf);
  return float2half(rf);
}

template <>
EIGEN_STRONG_INLINE Packet8bf pmul_old<Packet8bf>(const Packet8bf& a, const Packet8bf& b) {
  return F32ToBf16(pmul_old<Packet8f>(Bf16ToF32(a), Bf16ToF32(b)));
}

template <>
EIGEN_STRONG_INLINE Packet4l pmul_old<Packet4l>(const Packet4l& a, const Packet4l& b) {
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

template<typename Packet> EIGEN_DEVICE_FUNC inline Packet
pdiv_old(const Packet& a, const Packet& b) { return a/b; }

template <>
EIGEN_STRONG_INLINE Packet4f pdiv_old<Packet4f>(const Packet4f& a, const Packet4f& b) {
  return _mm_div_ps(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet2d pdiv_old<Packet2d>(const Packet2d& a, const Packet2d& b) {
  return _mm_div_pd(a, b);
}

template <>
EIGEN_STRONG_INLINE Packet8f pdiv_old<Packet8f>(const Packet8f& a, const Packet8f& b) {
  return _mm256_div_ps(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet4d pdiv_old<Packet4d>(const Packet4d& a, const Packet4d& b) {
  return _mm256_div_pd(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet8i pdiv_old<Packet8i>(const Packet8i& /*a*/, const Packet8i& /*b*/) {
  eigen_assert(false && "packet integer division are not supported by AVX");
  return pset1<Packet8i>(0);
}

template <>
EIGEN_STRONG_INLINE Packet8h pdiv_old<Packet8h>(const Packet8h& a, const Packet8h& b) {
  Packet8f af = half2float(a);
  Packet8f bf = half2float(b);
  Packet8f rf = pdiv_old(af, bf);
  return float2half(rf);
}

template <>
EIGEN_STRONG_INLINE Packet8bf pdiv_old<Packet8bf>(const Packet8bf& a, const Packet8bf& b) {
  return F32ToBf16(pdiv_old<Packet8f>(Bf16ToF32(a), Bf16ToF32(b)));
}

#endif // EIGEN_PACKET_MATH_OLD_FUN_MIPP_H