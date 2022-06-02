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


#endif // EIGEN_PACKET_MATH_OLD_FUN_MIPP_H