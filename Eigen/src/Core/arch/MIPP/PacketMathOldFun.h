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

#endif // EIGEN_PACKET_MATH_OLD_FUN_MIPP_H