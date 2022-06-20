#ifndef EIGEN_PACKET_MATH_OLD_FUN_MIPP_H
#define EIGEN_PACKET_MATH_OLD_FUN_MIPP_H

// definition in `Eigen/src/Core/GenericPacketMath.h`

#if 1 // definition

#ifndef SYCL_DEVICE_ONLY
#define EIGEN_BINARY_OP_NAN_PROPAGATION(Type, Func) Func
#else
#define EIGEN_BINARY_OP_NAN_PROPAGATION(Type, Func) \
[](const Type& a, const Type& b) { \
        return Func(a, b);}
#endif

// definition in `Eigen/src/Core/GenericPacketMath.h`
/** \internal \returns static_cast<TgtType>(a) (coeff-wise) */
template <typename SrcPacket, typename TgtPacket>
EIGEN_DEVICE_FUNC inline TgtPacket
pcast_old(const SrcPacket& a) {
  return static_cast<TgtPacket>(a);
}
template <typename SrcPacket, typename TgtPacket>
EIGEN_DEVICE_FUNC inline TgtPacket
pcast_old(const SrcPacket& a, const SrcPacket& /*b*/) {
  return static_cast<TgtPacket>(a);
}
template <typename SrcPacket, typename TgtPacket>
EIGEN_DEVICE_FUNC inline TgtPacket
pcast_old(const SrcPacket& a, const SrcPacket& /*b*/, const SrcPacket& /*c*/, const SrcPacket& /*d*/) {
  return static_cast<TgtPacket>(a);
}
template <typename SrcPacket, typename TgtPacket>
EIGEN_DEVICE_FUNC inline TgtPacket
pcast_old(const SrcPacket& a, const SrcPacket& /*b*/, const SrcPacket& /*c*/, const SrcPacket& /*d*/,
      const SrcPacket& /*e*/, const SrcPacket& /*f*/, const SrcPacket& /*g*/, const SrcPacket& /*h*/) {
  return static_cast<TgtPacket>(a);
}

/** \internal \returns reinterpret_cast<Target>(a) */
template <typename Target, typename Packet>
EIGEN_DEVICE_FUNC inline Target
preinterpret_old(const Packet& a); /* { return reinterpret_cast<const Target&>(a); } */

/** \internal \returns a + b (coeff-wise) */
template<typename Packet> EIGEN_DEVICE_FUNC inline Packet
padd_old(const Packet& a, const Packet& b) { return a+b; }
// Avoid compiler warning for boolean algebra.
template<> EIGEN_DEVICE_FUNC inline bool
padd_old(const bool& a, const bool& b) { return a || b; }

/** \internal \returns a packet version of \a *from, (un-aligned masked add)
 * There is no generic implementation. We only have implementations for specialized
 * cases. Generic case should not be called.
 */
template<typename Packet> EIGEN_DEVICE_FUNC inline
std::enable_if_t<unpacket_traits<Packet>::masked_fpops_available, Packet>
padd_old(const Packet& a, const Packet& b, typename unpacket_traits<Packet>::mask_t umask);


/** \internal \returns a - b (coeff-wise) */
template<typename Packet> EIGEN_DEVICE_FUNC inline Packet
psub_old(const Packet& a, const Packet& b) { return a-b; }

/** \internal \returns -a (coeff-wise) */
template<typename Packet> EIGEN_DEVICE_FUNC inline Packet
pnegate_old(const Packet& a) { return -a; }

template<> EIGEN_DEVICE_FUNC inline bool
pnegate_old(const bool& a) { return !a; }

/** \internal \returns conj(a) (coeff-wise) */
template<typename Packet> EIGEN_DEVICE_FUNC inline Packet
pconj_old(const Packet& a) { return numext::conj(a); }

/** \internal \returns a * b (coeff-wise) */
template<typename Packet> EIGEN_DEVICE_FUNC inline Packet
pmul_old(const Packet& a, const Packet& b) { return a*b; }
// Avoid compiler warning for boolean algebra.
template<> EIGEN_DEVICE_FUNC inline bool
pmul_old(const bool& a, const bool& b) { return a && b; }

/** \internal \returns a / b (coeff-wise) */
template<typename Packet> EIGEN_DEVICE_FUNC inline Packet
pdiv_old(const Packet& a, const Packet& b) { return a/b; }

/** \internal \returns one bits. */
template<typename Packet> EIGEN_DEVICE_FUNC inline Packet
ptrue_old(const Packet& a) {
  return ptrue_impl<Packet>::run(a);
}
/** \internal \returns packet of zeros */
template<typename Packet> EIGEN_DEVICE_FUNC inline Packet
pzero_old(const Packet& a) {
  return pzero_impl<Packet>::run(a);
}

/** \internal \returns a <= b as a bit mask */
template<typename Packet> EIGEN_DEVICE_FUNC inline Packet
pcmp_le_old(const Packet& a, const Packet& b)  { return a<=b ? ptrue_old(a) : pzero_old(a); }

/** \internal \returns a < b as a bit mask */
template<typename Packet> EIGEN_DEVICE_FUNC inline Packet
pcmp_lt_old(const Packet& a, const Packet& b)  { return a<b ? ptrue_old(a) : pzero_old(a); }

/** \internal \returns a == b as a bit mask */
template<typename Packet> EIGEN_DEVICE_FUNC inline Packet
pcmp_eq_old(const Packet& a, const Packet& b) { return a==b ? ptrue_old(a) : pzero_old(a); }

/** \internal \returns a < b or a==NaN or b==NaN as a bit mask */
template<typename Packet> EIGEN_DEVICE_FUNC inline Packet
pcmp_lt_or_nan_old(const Packet& a, const Packet& b) { return a>=b ? pzero_old(a) : ptrue_old(a); }

/** \internal \returns the bitwise and of \a a and \a b */
template<typename Packet> EIGEN_DEVICE_FUNC inline Packet
pand_old(const Packet& a, const Packet& b) {
  return bitwise_helper<Packet>::bitwise_and(a, b);
}

/** \internal \returns the bitwise or of \a a and \a b */
template<typename Packet> EIGEN_DEVICE_FUNC inline Packet
por_old(const Packet& a, const Packet& b) {
  return bitwise_helper<Packet>::bitwise_or(a, b);
}

/** \internal \returns the bitwise xor of \a a and \a b */
template<typename Packet> EIGEN_DEVICE_FUNC inline Packet
pxor_old(const Packet& a, const Packet& b) {
  return bitwise_helper<Packet>::bitwise_xor(a, b);
}

/** \internal \returns the bitwise not of \a a */
template<typename Packet> EIGEN_DEVICE_FUNC inline Packet
pnot_old(const Packet& a) {
  return bitwise_helper<Packet>::bitwise_not(a);
}

/** \internal \returns the bitwise and of \a a and not \a b */
template<typename Packet> EIGEN_DEVICE_FUNC inline Packet
pandnot_old(const Packet& a, const Packet& b) { return pand_old(a, pnot_old(b)); }

/** \internal \returns \a or \b for each field in packet according to \mask */
template<typename Packet> EIGEN_DEVICE_FUNC inline Packet
pselect_old(const Packet& mask, const Packet& a, const Packet& b) {
  return pselect_impl<Packet>::run(mask, a, b);
}

template<> EIGEN_DEVICE_FUNC inline bool pselect_old<bool>(
    const bool& cond, const bool& a, const bool& b) {
  return cond ? a : b;
}

/** \internal \returns the min of \a a and \a b  (coeff-wise).
    If \a a or \b b is NaN, the return value is implementation defined. */
template<typename Packet> EIGEN_DEVICE_FUNC inline Packet
pmin_old(const Packet& a, const Packet& b) { return numext::mini(a,b); }

/** \internal \returns the min of \a a and \a b  (coeff-wise).
    NaNPropagation determines the NaN propagation semantics. */
template <int NaNPropagation, typename Packet>
EIGEN_DEVICE_FUNC inline Packet pmin_old(const Packet& a, const Packet& b) {
  return pminmax_impl<NaNPropagation>::run(a, b, EIGEN_BINARY_OP_NAN_PROPAGATION(Packet, (pmin_old<Packet>)));
}

/** \internal \returns the max of \a a and \a b  (coeff-wise)
    If \a a or \b b is NaN, the return value is implementation defined. */
template<typename Packet> EIGEN_DEVICE_FUNC inline Packet
pmax_old(const Packet& a, const Packet& b) { return numext::maxi(a, b); }

/** \internal \returns the max of \a a and \a b  (coeff-wise).
    NaNPropagation determines the NaN propagation semantics. */
template <int NaNPropagation, typename Packet>
EIGEN_DEVICE_FUNC inline Packet pmax_old(const Packet& a, const Packet& b) {
  return pminmax_impl<NaNPropagation>::run(a, b, EIGEN_BINARY_OP_NAN_PROPAGATION(Packet,(pmax_old<Packet>)));
}

/** \internal \returns the absolute value of \a a */
template<typename Packet> EIGEN_DEVICE_FUNC inline Packet
pabs_old(const Packet& a) { return numext::abs(a); }
template<> EIGEN_DEVICE_FUNC inline unsigned int
pabs_old(const unsigned int& a) { return a; }
template<> EIGEN_DEVICE_FUNC inline unsigned long
pabs_old(const unsigned long& a) { return a; }
template<> EIGEN_DEVICE_FUNC inline unsigned long long
pabs_old(const unsigned long long& a) { return a; }

/** \internal \returns the addsub value of \a a,b */
template<typename Packet> EIGEN_DEVICE_FUNC inline Packet
paddsub_old(const Packet& a, const Packet& b) {
  return pselect_old(peven_mask_old(a), padd_old(a, b), psub_old(a, b));
 }

/** \internal \returns the phase angle of \a a */
template<typename Packet> EIGEN_DEVICE_FUNC inline Packet
parg_old(const Packet& a) { using numext::arg; return arg(a); }


/** \internal \returns \a a logically shifted by N bits to the right */
template<int N> EIGEN_DEVICE_FUNC inline int
parithmetic_shift_right_old(const int& a) { return a >> N; }
template<int N> EIGEN_DEVICE_FUNC inline long int
parithmetic_shift_right_old(const long int& a) { return a >> N; }

/** \internal \returns \a a arithmetically shifted by N bits to the right */
template<int N> EIGEN_DEVICE_FUNC inline int
plogical_shift_right_old(const int& a) { return static_cast<int>(static_cast<unsigned int>(a) >> N); }
template<int N> EIGEN_DEVICE_FUNC inline long int
plogical_shift_right_old(const long int& a) { return static_cast<long>(static_cast<unsigned long>(a) >> N); }

/** \internal \returns \a a shifted by N bits to the left */
template<int N> EIGEN_DEVICE_FUNC inline int
plogical_shift_left_old(const int& a) { return a << N; }
template<int N> EIGEN_DEVICE_FUNC inline long int
plogical_shift_left_old(const long int& a) { return a << N; }

/** \internal \returns the significant and exponent of the underlying floating point numbers
  * See https://en.cppreference.com/w/cpp/numeric/math/frexp
  */
template <typename Packet>
EIGEN_DEVICE_FUNC inline Packet pfrexp_old(const Packet& a, Packet& exponent) {
  int exp;
  EIGEN_USING_STD(frexp);
  Packet result = static_cast<Packet>(frexp(a, &exp));
  exponent = static_cast<Packet>(exp);
  return result;
}

/** \internal \returns a * 2^((int)exponent)
  * See https://en.cppreference.com/w/cpp/numeric/math/ldexp
  */
template<typename Packet> EIGEN_DEVICE_FUNC inline Packet
pldexp_old(const Packet &a, const Packet &exponent) {
  EIGEN_USING_STD(ldexp)
  return static_cast<Packet>(ldexp(a, static_cast<int>(exponent)));
}

/** \internal \returns the min of \a a and \a b  (coeff-wise) */
template<typename Packet> EIGEN_DEVICE_FUNC inline Packet
pabsdiff_old(const Packet& a, const Packet& b) { return pselect_old(pcmp_lt_old(a, b), psub_old(b, a), psub_old(a, b)); }

/** \internal \returns a packet version of \a *from, from must be 16 bytes aligned */
template<typename Packet> EIGEN_DEVICE_FUNC inline Packet
pload_old(const typename unpacket_traits<Packet>::type* from) { return *from; }

/** \internal \returns a packet version of \a *from, (un-aligned load) */
template<typename Packet> EIGEN_DEVICE_FUNC inline Packet
ploadu_old(const typename unpacket_traits<Packet>::type* from) { return *from; }

/** \internal \returns a packet version of \a *from, (un-aligned masked load)
 * There is no generic implementation. We only have implementations for specialized
 * cases. Generic case should not be called.
 */
template<typename Packet> EIGEN_DEVICE_FUNC inline
std::enable_if_t<unpacket_traits<Packet>::masked_load_available, Packet>
ploadu_old(const typename unpacket_traits<Packet>::type* from, typename unpacket_traits<Packet>::mask_t umask);

/** \internal \returns a packet with constant coefficients \a a, e.g.: (a,a,a,a) */
template<typename Packet> EIGEN_DEVICE_FUNC inline Packet
pset1_old(const typename unpacket_traits<Packet>::type& a) { return a; }

/** \internal \returns a packet with constant coefficients set from bits */
template<typename Packet,typename BitsType> EIGEN_DEVICE_FUNC inline Packet
pset1frombits_old(BitsType a);

/** \internal \returns a packet with constant coefficients \a a[0], e.g.: (a[0],a[0],a[0],a[0]) */
template<typename Packet> EIGEN_DEVICE_FUNC inline Packet
pload1_old(const typename unpacket_traits<Packet>::type  *a) { return pset1_old<Packet>(*a); }

/** \internal \returns a packet with elements of \a *from duplicated.
  * For instance, for a packet of 8 elements, 4 scalars will be read from \a *from and
  * duplicated to form: {from[0],from[0],from[1],from[1],from[2],from[2],from[3],from[3]}
  * Currently, this function is only used for scalar * complex products.
  */
template<typename Packet> EIGEN_DEVICE_FUNC EIGEN_STRONG_INLINE Packet
ploaddup_old(const typename unpacket_traits<Packet>::type* from) { return *from; }

/** \internal \returns a packet with elements of \a *from quadrupled.
  * For instance, for a packet of 8 elements, 2 scalars will be read from \a *from and
  * replicated to form: {from[0],from[0],from[0],from[0],from[1],from[1],from[1],from[1]}
  * Currently, this function is only used in matrix products.
  * For packet-size smaller or equal to 4, this function is equivalent to pload1_old
  */
template<typename Packet> EIGEN_DEVICE_FUNC inline Packet
ploadquad_old(const typename unpacket_traits<Packet>::type* from)
{ return pload1_old<Packet>(from); }

/** \internal equivalent to
  * \code
  * a0 = pload1_old(a+0);
  * a1 = pload1_old(a+1);
  * a2 = pload1_old(a+2);
  * a3 = pload1_old(a+3);
  * \endcode
  * \sa pset1_old, pload1_old, ploaddup_old, pbroadcast2_old
  */
template<typename Packet> EIGEN_DEVICE_FUNC
inline void pbroadcast4_old(const typename unpacket_traits<Packet>::type *a,
                        Packet& a0, Packet& a1, Packet& a2, Packet& a3)
{
  a0 = pload1_old<Packet>(a+0);
  a1 = pload1_old<Packet>(a+1);
  a2 = pload1_old<Packet>(a+2);
  a3 = pload1_old<Packet>(a+3);
}

/** \internal equivalent to
  * \code
  * a0 = pload1_old(a+0);
  * a1 = pload1_old(a+1);
  * \endcode
  * \sa pset1_old, pload1_old, ploaddup_old, pbroadcast4_old
  */
template<typename Packet> EIGEN_DEVICE_FUNC
inline void pbroadcast2_old(const typename unpacket_traits<Packet>::type *a,
                        Packet& a0, Packet& a1)
{
  a0 = pload1_old<Packet>(a+0);
  a1 = pload1_old<Packet>(a+1);
}

/** \internal \brief Returns a packet with coefficients (a,a+1,...,a+packet_size-1). */
template<typename Packet> EIGEN_DEVICE_FUNC EIGEN_STRONG_INLINE Packet
plset_old(const typename unpacket_traits<Packet>::type& a) { return a; }

/** \internal \returns a packet with constant coefficients \a a, e.g.: (x, 0, x, 0),
     where x is the value of all 1-bits. */
template<typename Packet> EIGEN_DEVICE_FUNC inline Packet
peven_mask_old(const Packet& /*a*/) {
  typedef typename unpacket_traits<Packet>::type Scalar;
  const size_t n = unpacket_traits<Packet>::size;
  EIGEN_ALIGN_TO_BOUNDARY(sizeof(Packet)) Scalar elements[n];
  for(size_t i = 0; i < n; ++i) {
    memset(elements+i, ((i & 1) == 0 ? 0xff : 0), sizeof(Scalar));
  }
  return ploadu_old<Packet>(elements);
}


/** \internal copy the packet \a from to \a *to, \a to must be 16 bytes aligned */
template<typename Scalar, typename Packet> EIGEN_DEVICE_FUNC inline void pstore_old(Scalar* to, const Packet& from)
{ (*to) = from; }

/** \internal copy the packet \a from to \a *to, (un-aligned store) */
template<typename Scalar, typename Packet> EIGEN_DEVICE_FUNC inline void pstoreu_old(Scalar* to, const Packet& from)
{  (*to) = from; }

/** \internal copy the packet \a from to \a *to, (un-aligned store with a mask)
 * There is no generic implementation. We only have implementations for specialized
 * cases. Generic case should not be called.
 */
template<typename Scalar, typename Packet>
EIGEN_DEVICE_FUNC inline
std::enable_if_t<unpacket_traits<Packet>::masked_store_available, void>
pstoreu_old(Scalar* to, const Packet& from, typename unpacket_traits<Packet>::mask_t umask);

template<typename Scalar, typename Packet> EIGEN_DEVICE_FUNC inline Packet pgather_old(const Scalar* from, Index /*stride*/)
{ return ploadu_old<Packet>(from); }

template<typename Scalar, typename Packet> EIGEN_DEVICE_FUNC inline void pscatter_old(Scalar* to, const Packet& from, Index /*stride*/)
{ pstore_old(to, from); }

/** \internal tries to do cache prefetching of \a addr */
template<typename Scalar> EIGEN_DEVICE_FUNC inline void prefetch_old(const Scalar* addr)
{
#if defined(EIGEN_HIP_DEVICE_COMPILE)
  // do nothing
#elif defined(EIGEN_CUDA_ARCH)
#if defined(__LP64__) || EIGEN_OS_WIN64
  // 64-bit pointer operand constraint for inlined asm
  asm(" prefetch.L1 [ %1 ];" : "=l"(addr) : "l"(addr));
#else
  // 32-bit pointer operand constraint for inlined asm
  asm(" prefetch.L1 [ %1 ];" : "=r"(addr) : "r"(addr));
#endif
#elif (!EIGEN_COMP_MSVC) && (EIGEN_COMP_GNUC || EIGEN_COMP_CLANG || EIGEN_COMP_ICC)
  __builtin_prefetch(addr);
#endif
}

/** \internal \returns the reversed elements of \a a*/
template<typename Packet> EIGEN_DEVICE_FUNC inline Packet preverse_old(const Packet& a)
{ return a; }

/** \internal \returns \a a with real and imaginary part flipped (for complex type only) */
template<typename Packet> EIGEN_DEVICE_FUNC inline Packet pcplxflip_old(const Packet& a)
{
  return Packet(numext::imag(a),numext::real(a));
}

/**************************
* Special math functions
***************************/

/** \internal \returns the sine of \a a (coeff-wise) */
template<typename Packet> EIGEN_DECLARE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS
Packet psin_old(const Packet& a) { EIGEN_USING_STD(sin); return sin(a); }

/** \internal \returns the cosine of \a a (coeff-wise) */
template<typename Packet> EIGEN_DECLARE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS
Packet pcos_old(const Packet& a) { EIGEN_USING_STD(cos); return cos(a); }

/** \internal \returns the tan of \a a (coeff-wise) */
template<typename Packet> EIGEN_DECLARE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS
Packet ptan_old(const Packet& a) { EIGEN_USING_STD(tan); return tan(a); }

/** \internal \returns the arc sine of \a a (coeff-wise) */
template<typename Packet> EIGEN_DECLARE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS
Packet pasin_old(const Packet& a) { EIGEN_USING_STD(asin); return asin(a); }

/** \internal \returns the arc cosine of \a a (coeff-wise) */
template<typename Packet> EIGEN_DECLARE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS
Packet pacos_old(const Packet& a) { EIGEN_USING_STD(acos); return acos(a); }

/** \internal \returns the arc tangent of \a a (coeff-wise) */
template<typename Packet> EIGEN_DECLARE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS
Packet patan_old(const Packet& a) { EIGEN_USING_STD(atan); return atan(a); }

/** \internal \returns the hyperbolic sine of \a a (coeff-wise) */
template<typename Packet> EIGEN_DECLARE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS
Packet psinh_old(const Packet& a) { EIGEN_USING_STD(sinh); return sinh(a); }

/** \internal \returns the hyperbolic cosine of \a a (coeff-wise) */
template<typename Packet> EIGEN_DECLARE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS
Packet pcosh_old(const Packet& a) { EIGEN_USING_STD(cosh); return cosh(a); }

/** \internal \returns the hyperbolic tan of \a a (coeff-wise) */
template<typename Packet> EIGEN_DECLARE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS
Packet ptanh_old(const Packet& a) { EIGEN_USING_STD(tanh); return tanh(a); }

/** \internal \returns the exp of \a a (coeff-wise) */
template<typename Packet> EIGEN_DECLARE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS
Packet pexp_old(const Packet& a) { EIGEN_USING_STD(exp); return exp(a); }

/** \internal \returns the expm1 of \a a (coeff-wise) */
template<typename Packet> EIGEN_DECLARE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS
Packet pexpm1_old(const Packet& a) { return numext::expm1(a); }

/** \internal \returns the log of \a a (coeff-wise) */
template<typename Packet> EIGEN_DECLARE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS
Packet plog_old(const Packet& a) { EIGEN_USING_STD(log); return log(a); }

/** \internal \returns the log1p of \a a (coeff-wise) */
template<typename Packet> EIGEN_DECLARE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS
Packet plog1p_old(const Packet& a) { return numext::log1p(a); }

/** \internal \returns the log10 of \a a (coeff-wise) */
template<typename Packet> EIGEN_DECLARE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS
Packet plog10_old(const Packet& a) { EIGEN_USING_STD(log10); return log10(a); }

/** \internal \returns the log10 of \a a (coeff-wise) */
template<typename Packet> EIGEN_DECLARE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS
Packet plog2_old(const Packet& a) {
  typedef typename internal::unpacket_traits<Packet>::type Scalar;
  return pmul_old(pset1_old<Packet>(Scalar(EIGEN_LOG2E)), plog_old(a));
}

/** \internal \returns the square-root of \a a (coeff-wise) */
template<typename Packet> EIGEN_DECLARE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS
Packet psqrt_old(const Packet& a) { return numext::sqrt(a); }

/** \internal \returns the rounded value of \a a (coeff-wise) */
template<typename Packet> EIGEN_DECLARE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS
Packet pround_old(const Packet& a) { using numext::round; return round(a); }

/** \internal \returns the floor of \a a (coeff-wise) */
template<typename Packet> EIGEN_DECLARE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS
Packet pfloor_old(const Packet& a) { using numext::floor; return floor(a); }

/** \internal \returns the rounded value of \a a (coeff-wise) with current
 * rounding mode */
template<typename Packet> EIGEN_DECLARE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS
Packet print_old(const Packet& a) { using numext::rint; return rint(a); }

/** \internal \returns the ceil of \a a (coeff-wise) */
template<typename Packet> EIGEN_DECLARE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS
Packet pceil_old(const Packet& a) { using numext::ceil; return ceil(a); }

/** \internal \returns the first element of a packet */
template<typename Packet>
EIGEN_DEVICE_FUNC inline typename unpacket_traits<Packet>::type
pfirst_old(const Packet& a)
{ return a; }

/** \internal \returns the sum of the elements of upper and lower half of \a a if \a a is larger than 4.
  * For a packet {a0, a1, a2, a3, a4, a5, a6, a7}, it returns a half packet {a0+a4, a1+a5, a2+a6, a3+a7}
  * For packet-size smaller or equal to 4, this boils down to a noop.
  */
template<typename Packet>
EIGEN_DEVICE_FUNC inline std::conditional_t<(unpacket_traits<Packet>::size%8)==0,typename unpacket_traits<Packet>::half,Packet>
predux_half_dowto4_old(const Packet& a)
{ return a; }

// Slow generic implementation of Packet reduction.
template <typename Packet, typename Op>
EIGEN_DEVICE_FUNC inline typename unpacket_traits<Packet>::type
predux_helper_old(const Packet& a, Op op) {
  typedef typename unpacket_traits<Packet>::type Scalar;
  const size_t n = unpacket_traits<Packet>::size;
  EIGEN_ALIGN_TO_BOUNDARY(sizeof(Packet)) Scalar elements[n];
  pstoreu_old<Scalar>(elements, a);
  for(size_t k = n / 2; k > 0; k /= 2)  {
    for(size_t i = 0; i < k; ++i) {
      elements[i] = op(elements[i], elements[i + k]);
    }
  }
  return elements[0];
}

/** \internal \returns the sum of the elements of \a a*/
template<typename Packet>
EIGEN_DEVICE_FUNC inline typename unpacket_traits<Packet>::type
predux_old(const Packet& a)
{
  return a;
}

/** \internal \returns the product of the elements of \a a */
template <typename Packet>
EIGEN_DEVICE_FUNC inline typename unpacket_traits<Packet>::type predux_mul_old(
    const Packet& a) {
  typedef typename unpacket_traits<Packet>::type Scalar;
  return predux_helper_old(a, EIGEN_BINARY_OP_NAN_PROPAGATION(Scalar, (pmul_old<Scalar>)));
}

/** \internal \returns the min of the elements of \a a */
template <typename Packet>
EIGEN_DEVICE_FUNC inline typename unpacket_traits<Packet>::type predux_min_old(
    const Packet &a) {
  typedef typename unpacket_traits<Packet>::type Scalar;
  return predux_helper_old(a, EIGEN_BINARY_OP_NAN_PROPAGATION(Scalar, (pmin_old<PropagateFast, Scalar>)));
}

template <int NaNPropagation, typename Packet>
EIGEN_DEVICE_FUNC inline typename unpacket_traits<Packet>::type predux_min_old(
    const Packet& a) {
  typedef typename unpacket_traits<Packet>::type Scalar;
  return predux_helper_old(a, EIGEN_BINARY_OP_NAN_PROPAGATION(Scalar, (pmin_old<NaNPropagation, Scalar>)));
}

/** \internal \returns the min of the elements of \a a */
template <typename Packet>
EIGEN_DEVICE_FUNC inline typename unpacket_traits<Packet>::type predux_max_old(
    const Packet &a) {
  typedef typename unpacket_traits<Packet>::type Scalar;
  return predux_helper_old(a, EIGEN_BINARY_OP_NAN_PROPAGATION(Scalar, (pmax_old<PropagateFast, Scalar>)));
}

template <int NaNPropagation, typename Packet>
EIGEN_DEVICE_FUNC inline typename unpacket_traits<Packet>::type predux_max_old(
    const Packet& a) {
  typedef typename unpacket_traits<Packet>::type Scalar;
  return predux_helper_old(a, EIGEN_BINARY_OP_NAN_PROPAGATION(Scalar, (pmax_old<NaNPropagation, Scalar>)));
}

/** \internal \returns true if all coeffs of \a a means "true"
  * It is supposed to be called on values returned by pcmp_*.
  */
// not needed yet
// template<typename Packet> EIGEN_DEVICE_FUNC inline bool predux_all_old(const Packet& a)
// { return bool(a); }

/** \internal \returns true if any coeffs of \a a means "true"
  * It is supposed to be called on values returned by pcmp_*.
  */
template<typename Packet> EIGEN_DEVICE_FUNC inline bool predux_any_old(const Packet& a)
{
  // Dirty but generic implementation where "true" is assumed to be non 0 and all the sames.
  // It is expected that "true" is either:
  //  - Scalar(1)
  //  - bits full of ones (NaN for floats),
  //  - or first bit equals to 1 (1 for ints, smallest denormal for floats).
  // For all these cases, taking the sum is just fine, and this boils down to a no-op for scalars.
  typedef typename unpacket_traits<Packet>::type Scalar;
  return numext::not_equal_strict(predux_old(a), Scalar(0));
}

/***************************************************************************
* The following functions might not have to be overwritten for vectorized types
***************************************************************************/

// FMA instructions.
/** \internal \returns a * b + c (coeff-wise) */
template <typename Packet>
EIGEN_DEVICE_FUNC inline Packet pmadd_old(const Packet& a, const Packet& b,
                                      const Packet& c) {
  return padd_old(pmul_old(a, b), c);
}

/** \internal \returns a * b - c (coeff-wise) */
template <typename Packet>
EIGEN_DEVICE_FUNC inline Packet pmsub_old(const Packet& a, const Packet& b,
                                      const Packet& c) {
  return psub_old(pmul_old(a, b), c);
}

/** \internal \returns -(a * b) + c (coeff-wise) */
template <typename Packet>
EIGEN_DEVICE_FUNC inline Packet pnmadd_old(const Packet& a, const Packet& b,
                                       const Packet& c) {
  return padd_old(pnegate_old(pmul_old(a, b)), c);
}

/** \internal \returns -(a * b) - c (coeff-wise) */
template <typename Packet>
EIGEN_DEVICE_FUNC inline Packet pnmsub_old(const Packet& a, const Packet& b,
                                       const Packet& c) {
  return psub_old(pnegate_old(pmul_old(a, b)), c);
}

/** \internal copy a packet with constant coefficient \a a (e.g., [a,a,a,a]) to \a *to. \a to must be 16 bytes aligned */
// NOTE: this function must really be templated on the packet type (think about different packet types for the same scalar type)
template<typename Packet>
inline void pstore1_old(typename unpacket_traits<Packet>::type* to, const typename unpacket_traits<Packet>::type& a)
{
  pstore_old(to, pset1_old<Packet>(a));
}

/** \internal \returns a packet version of \a *from.
  * The pointer \a from must be aligned on a \a Alignment bytes boundary. */
template<typename Packet, int Alignment>
EIGEN_DEVICE_FUNC EIGEN_ALWAYS_INLINE Packet ploadt_old(const typename unpacket_traits<Packet>::type* from)
{
  if(Alignment >= unpacket_traits<Packet>::alignment)
    return pload_old<Packet>(from);
  else
    return ploadu_old<Packet>(from);
}

/** \internal copy the packet \a from to \a *to.
  * The pointer \a from must be aligned on a \a Alignment bytes boundary. */
template<typename Scalar, typename Packet, int Alignment>
EIGEN_DEVICE_FUNC EIGEN_ALWAYS_INLINE void pstoret_old(Scalar* to, const Packet& from)
{
  if(Alignment >= unpacket_traits<Packet>::alignment)
    pstore_old(to, from);
  else
    pstoreu_old(to, from);
}

/** \internal \returns a packet version of \a *from.
  * Unlike ploadt_old, ploadt_ro_old takes advantage of the read-only memory path on the
  * hardware if available to speedup the loading of data that won't be modified
  * by the current computation.
  */
template<typename Packet, int LoadMode>
EIGEN_DEVICE_FUNC EIGEN_ALWAYS_INLINE Packet ploadt_ro_old(const typename unpacket_traits<Packet>::type* from)
{
  return ploadt_old<Packet, LoadMode>(from);
}

/***************************************************************************
* Fast complex products (GCC generates a function call which is very slow)
***************************************************************************/

// Eigen+CUDA does not support complexes.
#if !defined(EIGEN_GPUCC)

template<> inline std::complex<float> pmul_old(const std::complex<float>& a, const std::complex<float>& b)
{ return std::complex<float>(a.real()*b.real() - a.imag()*b.imag(), a.imag()*b.real() + a.real()*b.imag()); }

template<> inline std::complex<double> pmul_old(const std::complex<double>& a, const std::complex<double>& b)
{ return std::complex<double>(a.real()*b.real() - a.imag()*b.imag(), a.imag()*b.real() + a.real()*b.imag()); }

#endif

template<typename Packet> EIGEN_DEVICE_FUNC inline void
ptranspose_old(PacketBlock<Packet,1>& /*kernel*/) {
  // Nothing to do in the scalar case, i.e. a 1x1 matrix.
}

template<typename Packet> EIGEN_DEVICE_FUNC inline Packet
pblend_old(const Selector<unpacket_traits<Packet>::size>& ifPacket, const Packet& thenPacket, const Packet& elsePacket) {
  return ifPacket.select[0] ? thenPacket : elsePacket;
}

/** \internal \returns 1 / a (coeff-wise) */
template <typename Packet>
EIGEN_DEVICE_FUNC inline Packet preciprocal_old(const Packet& a) {
  using Scalar = typename unpacket_traits<Packet>::type;
  return pdiv_old(pset1_old<Packet>(Scalar(1)), a);
}

/** \internal \returns the reciprocal square-root of \a a (coeff-wise) */
template<typename Packet> EIGEN_DECLARE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS
Packet prsqrt_old(const Packet& a) {
  return preciprocal_old<Packet>(psqrt_old(a));
}

template<typename Packet> EIGEN_STRONG_INLINE EIGEN_DEVICE_FUNC
Packet pfrexp_generic_get_biased_exponent_old(const Packet& a) {
  typedef typename unpacket_traits<Packet>::type Scalar;
  typedef typename unpacket_traits<Packet>::integer_packet PacketI;
  static constexpr int mantissa_bits = numext::numeric_limits<Scalar>::digits - 1;
  return pcast_old<PacketI, Packet>(plogical_shift_right_old<mantissa_bits>(preinterpret_old<PacketI>(pabs_old(a))));
}

#endif

#ifdef EIGEN_VECTORIZE_SSE

template <>
EIGEN_STRONG_INLINE Packet4f pset1_old<Packet4f>(const float& from) {
  return _mm_set_ps1(from);
}
template <>
EIGEN_STRONG_INLINE Packet2d pset1_old<Packet2d>(const double& from) {
  return _mm_set1_pd(from);
}
template <>
EIGEN_STRONG_INLINE Packet4i pset1_old<Packet4i>(const int& from) {
  return _mm_set1_epi32(from);
}
template <>
EIGEN_STRONG_INLINE Packet16b pset1_old<Packet16b>(const bool& from) {
  return _mm_set1_epi8(static_cast<char>(from));
}

template <>
EIGEN_STRONG_INLINE Packet4f pset1frombits_old<Packet4f>(unsigned int from) {
  return _mm_castsi128_ps(pset1_old<Packet4i>(from));
}
template <>
EIGEN_STRONG_INLINE Packet2d pset1frombits_old<Packet2d>(uint64_t from) {
  return _mm_castsi128_pd(_mm_set1_epi64x(from));
}

template <>
EIGEN_STRONG_INLINE Packet4f peven_mask_old(const Packet4f& /*a*/) {
  return _mm_castsi128_ps(_mm_set_epi32(0, -1, 0, -1));
}
template <>
EIGEN_STRONG_INLINE Packet4i peven_mask_old(const Packet4i& /*a*/) {
  return _mm_set_epi32(0, -1, 0, -1);
}
template <>
EIGEN_STRONG_INLINE Packet2d peven_mask_old(const Packet2d& /*a*/) {
  return _mm_castsi128_pd(_mm_set_epi32(0, 0, -1, -1));
}

template <>
EIGEN_STRONG_INLINE Packet4f pzero_old(const Packet4f& /*a*/) {
  return _mm_setzero_ps();
}
template <>
EIGEN_STRONG_INLINE Packet2d pzero_old(const Packet2d& /*a*/) {
  return _mm_setzero_pd();
}
template <>
EIGEN_STRONG_INLINE Packet4i pzero_old(const Packet4i& /*a*/) {
  return _mm_setzero_si128();
}

// GCC generates a shufps instruction for _mm_set1_ps/_mm_load1_ps instead of the more efficient pshufd instruction.
// However, using inrinsics for pset1_old makes gcc to generate crappy code in some cases (see bug 203)
// Using inline assembly is also not an option because then gcc fails to reorder properly the instructions.
// Therefore, we introduced the pload1_old functions to be used in product kernels for which bug 203 does not apply.
// Also note that with AVX, we want it to generate a vbroadcastss.
#if EIGEN_COMP_GNUC_STRICT && (!defined __AVX__)
template <>
EIGEN_STRONG_INLINE Packet4f pload1_old<Packet4f>(const float* from) {
  return vec4f_swizzle1(_mm_load_ss(from), 0, 0, 0, 0);
}
#endif

template <>
EIGEN_STRONG_INLINE Packet4f plset_old<Packet4f>(const float& a) {
  return _mm_add_ps(pset1_old<Packet4f>(a), _mm_set_ps(3, 2, 1, 0));
}
template <>
EIGEN_STRONG_INLINE Packet2d plset_old<Packet2d>(const double& a) {
  return _mm_add_pd(pset1_old<Packet2d>(a), _mm_set_pd(1, 0));
}
template <>
EIGEN_STRONG_INLINE Packet4i plset_old<Packet4i>(const int& a) {
  return _mm_add_epi32(pset1_old<Packet4i>(a), _mm_set_epi32(3, 2, 1, 0));
}

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
EIGEN_STRONG_INLINE Packet4f pxor_old<Packet4f>(const Packet4f& a, const Packet4f& b);
template <>
EIGEN_STRONG_INLINE Packet4f paddsub_old<Packet4f>(const Packet4f& a, const Packet4f& b) {
#ifdef EIGEN_VECTORIZE_SSE3
  return _mm_addsub_ps(a, b);
#else
  const Packet4f mask = _mm_castsi128_ps(_mm_setr_epi32(0x80000000, 0x0, 0x80000000, 0x0));
  return padd_old(a, pxor_old(mask, b));
#endif
}

template <>
EIGEN_STRONG_INLINE Packet2d pxor_old<Packet2d>(const Packet2d&, const Packet2d&);
template <>
EIGEN_STRONG_INLINE Packet2d paddsub_old<Packet2d>(const Packet2d& a, const Packet2d& b) {
#ifdef EIGEN_VECTORIZE_SSE3
  return _mm_addsub_pd(a, b);
#else
  const Packet2d mask = _mm_castsi128_pd(_mm_setr_epi32(0x0, 0x80000000, 0x0, 0x0));
  return padd_old(a, pxor_old(mask, b));
#endif
}

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
EIGEN_STRONG_INLINE Packet4f pconj_old(const Packet4f& a) {
  return a;
}
template <>
EIGEN_STRONG_INLINE Packet2d pconj_old(const Packet2d& a) {
  return a;
}
template <>
EIGEN_STRONG_INLINE Packet4i pconj_old(const Packet4i& a) {
  return a;
}

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
EIGEN_STRONG_INLINE Packet4f pdiv_old<Packet4f>(const Packet4f& a, const Packet4f& b) {
  return _mm_div_ps(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet2d pdiv_old<Packet2d>(const Packet2d& a, const Packet2d& b) {
  return _mm_div_pd(a, b);
}

// for some weird raisons, it has to be overloaded for packet of integers
template <>
EIGEN_STRONG_INLINE Packet4i pmadd_old(const Packet4i& a, const Packet4i& b, const Packet4i& c) {
  return padd_old(pmul_old(a, b), c);
}
#ifdef EIGEN_VECTORIZE_FMA
template <>
EIGEN_STRONG_INLINE Packet4f pmadd_old(const Packet4f& a, const Packet4f& b, const Packet4f& c) {
  return _mm_fmadd_ps(a, b, c);
}
template <>
EIGEN_STRONG_INLINE Packet2d pmadd_old(const Packet2d& a, const Packet2d& b, const Packet2d& c) {
  return _mm_fmadd_pd(a, b, c);
}
template <>
EIGEN_STRONG_INLINE Packet4f pmsub_old(const Packet4f& a, const Packet4f& b, const Packet4f& c) {
  return _mm_fmsub_ps(a, b, c);
}
template <>
EIGEN_STRONG_INLINE Packet2d pmsub_old(const Packet2d& a, const Packet2d& b, const Packet2d& c) {
  return _mm_fmsub_pd(a, b, c);
}
template <>
EIGEN_STRONG_INLINE Packet4f pnmadd_old(const Packet4f& a, const Packet4f& b, const Packet4f& c) {
  return _mm_fnmadd_ps(a, b, c);
}
template <>
EIGEN_STRONG_INLINE Packet2d pnmadd_old(const Packet2d& a, const Packet2d& b, const Packet2d& c) {
  return _mm_fnmadd_pd(a, b, c);
}
template <>
EIGEN_STRONG_INLINE Packet4f pnmsub_old(const Packet4f& a, const Packet4f& b, const Packet4f& c) {
  return _mm_fnmsub_ps(a, b, c);
}
template <>
EIGEN_STRONG_INLINE Packet2d pnmsub_old(const Packet2d& a, const Packet2d& b, const Packet2d& c) {
  return _mm_fnmsub_pd(a, b, c);
}
#endif

#ifdef EIGEN_VECTORIZE_SSE4_1
template <>
EIGEN_DEVICE_FUNC inline Packet4f pselect_old(const Packet4f& mask, const Packet4f& a, const Packet4f& b) {
  return _mm_blendv_ps(b, a, mask);
}

template <>
EIGEN_DEVICE_FUNC inline Packet4i pselect_old(const Packet4i& mask, const Packet4i& a, const Packet4i& b) {
  return _mm_castps_si128(_mm_blendv_ps(_mm_castsi128_ps(b), _mm_castsi128_ps(a), _mm_castsi128_ps(mask)));
}

template <>
EIGEN_DEVICE_FUNC inline Packet2d pselect_old(const Packet2d& mask, const Packet2d& a, const Packet2d& b) {
  return _mm_blendv_pd(b, a, mask);
}

template <>
EIGEN_DEVICE_FUNC inline Packet16b pselect_old(const Packet16b& mask, const Packet16b& a, const Packet16b& b) {
  return _mm_blendv_epi8(b, a, mask);
}
#else
template <>
EIGEN_DEVICE_FUNC inline Packet16b pselect_old(const Packet16b& mask, const Packet16b& a, const Packet16b& b) {
  Packet16b a_part = _mm_and_si128(mask, a);
  Packet16b b_part = _mm_andnot_si128(mask, b);
  return _mm_or_si128(a_part, b_part);
}
#endif

template <>
EIGEN_STRONG_INLINE Packet4i ptrue_old<Packet4i>(const Packet4i& a) {
  return _mm_cmpeq_epi32(a, a);
}
template <>
EIGEN_STRONG_INLINE Packet16b ptrue_old<Packet16b>(const Packet16b& a) {
  return _mm_cmpeq_epi8(a, a);
}
template <>
EIGEN_STRONG_INLINE Packet4f ptrue_old<Packet4f>(const Packet4f& a) {
  Packet4i b = _mm_castps_si128(a);
  return _mm_castsi128_ps(_mm_cmpeq_epi32(b, b));
}
template <>
EIGEN_STRONG_INLINE Packet2d ptrue_old<Packet2d>(const Packet2d& a) {
  Packet4i b = _mm_castpd_si128(a);
  return _mm_castsi128_pd(_mm_cmpeq_epi32(b, b));
}

template <>
EIGEN_STRONG_INLINE Packet4f pand_old<Packet4f>(const Packet4f& a, const Packet4f& b) {
  return _mm_and_ps(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet2d pand_old<Packet2d>(const Packet2d& a, const Packet2d& b) {
  return _mm_and_pd(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet4i pand_old<Packet4i>(const Packet4i& a, const Packet4i& b) {
  return _mm_and_si128(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet16b pand_old<Packet16b>(const Packet16b& a, const Packet16b& b) {
  return _mm_and_si128(a, b);
}

template <>
EIGEN_STRONG_INLINE Packet4f por_old<Packet4f>(const Packet4f& a, const Packet4f& b) {
  return _mm_or_ps(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet2d por_old<Packet2d>(const Packet2d& a, const Packet2d& b) {
  return _mm_or_pd(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet4i por_old<Packet4i>(const Packet4i& a, const Packet4i& b) {
  return _mm_or_si128(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet16b por_old<Packet16b>(const Packet16b& a, const Packet16b& b) {
  return _mm_or_si128(a, b);
}

template <>
EIGEN_STRONG_INLINE Packet4f pxor_old<Packet4f>(const Packet4f& a, const Packet4f& b) {
  return _mm_xor_ps(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet2d pxor_old<Packet2d>(const Packet2d& a, const Packet2d& b) {
  return _mm_xor_pd(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet4i pxor_old<Packet4i>(const Packet4i& a, const Packet4i& b) {
  return _mm_xor_si128(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet16b pxor_old<Packet16b>(const Packet16b& a, const Packet16b& b) {
  return _mm_xor_si128(a, b);
}

template <>
EIGEN_STRONG_INLINE Packet4f pandnot_old<Packet4f>(const Packet4f& a, const Packet4f& b) {
  return _mm_andnot_ps(b, a);
}
template <>
EIGEN_STRONG_INLINE Packet2d pandnot_old<Packet2d>(const Packet2d& a, const Packet2d& b) {
  return _mm_andnot_pd(b, a);
}
template <>
EIGEN_STRONG_INLINE Packet4i pandnot_old<Packet4i>(const Packet4i& a, const Packet4i& b) {
  return _mm_andnot_si128(b, a);
}

template <>
EIGEN_STRONG_INLINE Packet4f pcmp_le_old(const Packet4f& a, const Packet4f& b) {
  return _mm_cmple_ps(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet4f pcmp_lt_old(const Packet4f& a, const Packet4f& b) {
  return _mm_cmplt_ps(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet4f pcmp_lt_or_nan_old(const Packet4f& a, const Packet4f& b) {
  return _mm_cmpnge_ps(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet4f pcmp_eq_old(const Packet4f& a, const Packet4f& b) {
  return _mm_cmpeq_ps(a, b);
}

template <>
EIGEN_STRONG_INLINE Packet2d pcmp_le_old(const Packet2d& a, const Packet2d& b) {
  return _mm_cmple_pd(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet2d pcmp_lt_old(const Packet2d& a, const Packet2d& b) {
  return _mm_cmplt_pd(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet2d pcmp_lt_or_nan_old(const Packet2d& a, const Packet2d& b) {
  return _mm_cmpnge_pd(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet2d pcmp_eq_old(const Packet2d& a, const Packet2d& b) {
  return _mm_cmpeq_pd(a, b);
}

template <>
EIGEN_STRONG_INLINE Packet4i pcmp_lt_old(const Packet4i& a, const Packet4i& b) {
  return _mm_cmplt_epi32(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet4i pcmp_eq_old(const Packet4i& a, const Packet4i& b) {
  return _mm_cmpeq_epi32(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet16b pcmp_eq_old(const Packet16b& a, const Packet16b& b) {
  return _mm_cmpeq_epi8(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet4i pcmp_le_old(const Packet4i& a, const Packet4i& b) {
  return por_old(pcmp_lt_old(a, b), pcmp_eq_old(a, b));
}

template <>
EIGEN_STRONG_INLINE Packet4f pmin_old<Packet4f>(const Packet4f& a, const Packet4f& b) {
#if EIGEN_COMP_GNUC_STRICT && EIGEN_COMP_GNUC < 63
// There appears to be a bug in GCC, by which the optimizer may
// flip the argument order in calls to _mm_min_ps, so we have to
// resort to inline ASM here. This is supposed to be fixed in gcc6.3,
// see also: https://gcc.gnu.org/bugzilla/show_bug.cgi?id=72867
#ifdef EIGEN_VECTORIZE_AVX
  Packet4f res;
  asm("vminps %[a], %[b], %[res]" : [res] "=x"(res) : [a] "x"(a), [b] "x"(b));
#else
  Packet4f res = b;
  asm("minps %[a], %[res]" : [res] "+x"(res) : [a] "x"(a));
#endif
  return res;
#else
  // Arguments are reversed to match NaN propagation behavior of std::min.
  return _mm_min_ps(b, a);
#endif
}
template <>
EIGEN_STRONG_INLINE Packet2d pmin_old<Packet2d>(const Packet2d& a, const Packet2d& b) {
#if EIGEN_COMP_GNUC_STRICT && EIGEN_COMP_GNUC < 63
// There appears to be a bug in GCC, by which the optimizer may
// flip the argument order in calls to _mm_min_pd, so we have to
// resort to inline ASM here. This is supposed to be fixed in gcc6.3,
// see also: https://gcc.gnu.org/bugzilla/show_bug.cgi?id=72867
#ifdef EIGEN_VECTORIZE_AVX
  Packet2d res;
  asm("vminpd %[a], %[b], %[res]" : [res] "=x"(res) : [a] "x"(a), [b] "x"(b));
#else
  Packet2d res = b;
  asm("minpd %[a], %[res]" : [res] "+x"(res) : [a] "x"(a));
#endif
  return res;
#else
  // Arguments are reversed to match NaN propagation behavior of std::min.
  return _mm_min_pd(b, a);
#endif
}
template <>
EIGEN_STRONG_INLINE Packet4i pmin_old<Packet4i>(const Packet4i& a, const Packet4i& b) {
#ifdef EIGEN_VECTORIZE_SSE4_1
  return _mm_min_epi32(a, b);
#else
  // after some bench, this version *is* faster than a scalar implementation
  Packet4i mask = _mm_cmplt_epi32(a, b);
  return _mm_or_si128(_mm_and_si128(mask, a), _mm_andnot_si128(mask, b));
#endif
}

template <>
EIGEN_STRONG_INLINE Packet4f pmax_old<Packet4f>(const Packet4f& a, const Packet4f& b) {
#if EIGEN_COMP_GNUC_STRICT && EIGEN_COMP_GNUC < 63
// There appears to be a bug in GCC, by which the optimizer may
// flip the argument order in calls to _mm_max_ps, so we have to
// resort to inline ASM here. This is supposed to be fixed in gcc6.3,
// see also: https://gcc.gnu.org/bugzilla/show_bug.cgi?id=72867
#ifdef EIGEN_VECTORIZE_AVX
  Packet4f res;
  asm("vmaxps %[a], %[b], %[res]" : [res] "=x"(res) : [a] "x"(a), [b] "x"(b));
#else
  Packet4f res = b;
  asm("maxps %[a], %[res]" : [res] "+x"(res) : [a] "x"(a));
#endif
  return res;
#else
  // Arguments are reversed to match NaN propagation behavior of std::max.
  return _mm_max_ps(b, a);
#endif
}
template <>
EIGEN_STRONG_INLINE Packet2d pmax_old<Packet2d>(const Packet2d& a, const Packet2d& b) {
#if EIGEN_COMP_GNUC_STRICT && EIGEN_COMP_GNUC < 63
// There appears to be a bug in GCC, by which the optimizer may
// flip the argument order in calls to _mm_max_pd, so we have to
// resort to inline ASM here. This is supposed to be fixed in gcc6.3,
// see also: https://gcc.gnu.org/bugzilla/show_bug.cgi?id=72867
#ifdef EIGEN_VECTORIZE_AVX
  Packet2d res;
  asm("vmaxpd %[a], %[b], %[res]" : [res] "=x"(res) : [a] "x"(a), [b] "x"(b));
#else
  Packet2d res = b;
  asm("maxpd %[a], %[res]" : [res] "+x"(res) : [a] "x"(a));
#endif
  return res;
#else
  // Arguments are reversed to match NaN propagation behavior of std::max.
  return _mm_max_pd(b, a);
#endif
}
template <>
EIGEN_STRONG_INLINE Packet4i pmax_old<Packet4i>(const Packet4i& a, const Packet4i& b) {
#ifdef EIGEN_VECTORIZE_SSE4_1
  return _mm_max_epi32(a, b);
#else
  // after some bench, this version *is* faster than a scalar implementation
  Packet4i mask = _mm_cmpgt_epi32(a, b);
  return _mm_or_si128(_mm_and_si128(mask, a), _mm_andnot_si128(mask, b));
#endif
}

template <typename Packet, typename Op>
EIGEN_STRONG_INLINE Packet pminmax_propagate_numbers_old(const Packet& a, const Packet& b, Op op) {
  // In this implementation, we take advantage of the fact that pmin_old/pmax_old for SSE
  // always return a if either a or b is NaN.
  Packet not_nan_mask_a = pcmp_eq_old(a, a);
  Packet m = op(a, b);
  return pselect_old<Packet>(not_nan_mask_a, m, b);
}

template <typename Packet, typename Op>
EIGEN_STRONG_INLINE Packet pminmax_propagate_nan_old(const Packet& a, const Packet& b, Op op) {
  // In this implementation, we take advantage of the fact that pmin_old/pmax_old for SSE
  // always return a if either a or b is NaN.
  Packet not_nan_mask_a = pcmp_eq_old(a, a);
  Packet m = op(b, a);
  return pselect_old<Packet>(not_nan_mask_a, m, a);
}

// Add specializations for min/max with prescribed NaN progation.
template <>
EIGEN_STRONG_INLINE Packet4f pmin_old<PropagateNumbers, Packet4f>(const Packet4f& a, const Packet4f& b) {
  return pminmax_propagate_numbers_old(a, b, pmin_old<Packet4f>);
}
template <>
EIGEN_STRONG_INLINE Packet2d pmin_old<PropagateNumbers, Packet2d>(const Packet2d& a, const Packet2d& b) {
  return pminmax_propagate_numbers_old(a, b, pmin_old<Packet2d>);
}
template <>
EIGEN_STRONG_INLINE Packet4f pmax_old<PropagateNumbers, Packet4f>(const Packet4f& a, const Packet4f& b) {
  return pminmax_propagate_numbers_old(a, b, pmax_old<Packet4f>);
}
template <>
EIGEN_STRONG_INLINE Packet2d pmax_old<PropagateNumbers, Packet2d>(const Packet2d& a, const Packet2d& b) {
  return pminmax_propagate_numbers_old(a, b, pmax_old<Packet2d>);
}
template <>
EIGEN_STRONG_INLINE Packet4f pmin_old<PropagateNaN, Packet4f>(const Packet4f& a, const Packet4f& b) {
  return pminmax_propagate_nan_old(a, b, pmin_old<Packet4f>);
}
template <>
EIGEN_STRONG_INLINE Packet2d pmin_old<PropagateNaN, Packet2d>(const Packet2d& a, const Packet2d& b) {
  return pminmax_propagate_nan_old(a, b, pmin_old<Packet2d>);
}
template <>
EIGEN_STRONG_INLINE Packet4f pmax_old<PropagateNaN, Packet4f>(const Packet4f& a, const Packet4f& b) {
  return pminmax_propagate_nan_old(a, b, pmax_old<Packet4f>);
}
template <>
EIGEN_STRONG_INLINE Packet2d pmax_old<PropagateNaN, Packet2d>(const Packet2d& a, const Packet2d& b) {
  return pminmax_propagate_nan_old(a, b, pmax_old<Packet2d>);
}

template <int N>
EIGEN_STRONG_INLINE Packet4i parithmetic_shift_right_old(const Packet4i& a) {
  return _mm_srai_epi32(a, N);
}
template <int N>
EIGEN_STRONG_INLINE Packet4i plogical_shift_right_old(const Packet4i& a) {
  return _mm_srli_epi32(a, N);
}
template <int N>
EIGEN_STRONG_INLINE Packet4i plogical_shift_left_old(const Packet4i& a) {
  return _mm_slli_epi32(a, N);
}

template <>
EIGEN_STRONG_INLINE Packet4f pabs_old(const Packet4f& a) {
  const Packet4f mask = _mm_castsi128_ps(_mm_setr_epi32(0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF));
  return _mm_and_ps(a, mask);
}
template <>
EIGEN_STRONG_INLINE Packet2d pabs_old(const Packet2d& a) {
  const Packet2d mask = _mm_castsi128_pd(_mm_setr_epi32(0xFFFFFFFF, 0x7FFFFFFF, 0xFFFFFFFF, 0x7FFFFFFF));
  return _mm_and_pd(a, mask);
}
template <>
EIGEN_STRONG_INLINE Packet4i pabs_old(const Packet4i& a) {
#ifdef EIGEN_VECTORIZE_SSSE3
  return _mm_abs_epi32(a);
#else
  Packet4i aux = _mm_srai_epi32(a, 31);
  return _mm_sub_epi32(_mm_xor_si128(a, aux), aux);
#endif
}

#ifdef EIGEN_VECTORIZE_SSE4_1
template <>
EIGEN_STRONG_INLINE Packet4f pround_old<Packet4f>(const Packet4f& a) {
  // Unfortunately _mm_round_ps doesn't have a rounding mode to implement numext::round.
  const Packet4f mask = pset1frombits_old<Packet4f>(0x80000000u);
  const Packet4f prev0dot5 = pset1frombits_old<Packet4f>(0x3EFFFFFFu);
  return _mm_round_ps(padd_old(por_old(pand_old(a, mask), prev0dot5), a), _MM_FROUND_TO_ZERO);
}

template <>
EIGEN_STRONG_INLINE Packet2d pround_old<Packet2d>(const Packet2d& a) {
  const Packet2d mask = _mm_castsi128_pd(_mm_set_epi64x(0x8000000000000000ull, 0x8000000000000000ull));
  const Packet2d prev0dot5 = _mm_castsi128_pd(_mm_set_epi64x(0x3FDFFFFFFFFFFFFFull, 0x3FDFFFFFFFFFFFFFull));
  return _mm_round_pd(padd_old(por_old(pand_old(a, mask), prev0dot5), a), _MM_FROUND_TO_ZERO);
}

template <>
EIGEN_STRONG_INLINE Packet4f print_old<Packet4f>(const Packet4f& a) {
  return _mm_round_ps(a, _MM_FROUND_CUR_DIRECTION);
}
template <>
EIGEN_STRONG_INLINE Packet2d print_old<Packet2d>(const Packet2d& a) {
  return _mm_round_pd(a, _MM_FROUND_CUR_DIRECTION);
}

template <>
EIGEN_STRONG_INLINE Packet4f pceil_old<Packet4f>(const Packet4f& a) {
  return _mm_ceil_ps(a);
}
template <>
EIGEN_STRONG_INLINE Packet2d pceil_old<Packet2d>(const Packet2d& a) {
  return _mm_ceil_pd(a);
}

template <>
EIGEN_STRONG_INLINE Packet4f pfloor_old<Packet4f>(const Packet4f& a) {
  return _mm_floor_ps(a);
}
template <>
EIGEN_STRONG_INLINE Packet2d pfloor_old<Packet2d>(const Packet2d& a) {
  return _mm_floor_pd(a);
}
#else
template <>
EIGEN_STRONG_INLINE Packet4f print_old(const Packet4f& a) {
  // Adds and subtracts signum(a) * 2^23 to force rounding.
  const Packet4f limit = pset1_old<Packet4f>(static_cast<float>(1 << 23));
  const Packet4f abs_a = pabs_old(a);
  Packet4f r = padd_old(abs_a, limit);
  // Don't compile-away addition and subtraction.
  EIGEN_OPTIMIZATION_BARRIER(r);
  r = psub_old(r, limit);
  // If greater than limit, simply return a.  Otherwise, account for sign.
  r = pselect_old(pcmp_lt_old(abs_a, limit), pselect_old(pcmp_lt_old(a, pzero_old(a)), pnegate_old(r), r), a);
  return r;
}

template <>
EIGEN_STRONG_INLINE Packet2d print_old(const Packet2d& a) {
  // Adds and subtracts signum(a) * 2^52 to force rounding.
  const Packet2d limit = pset1_old<Packet2d>(static_cast<double>(1ull << 52));
  const Packet2d abs_a = pabs_old(a);
  Packet2d r = padd_old(abs_a, limit);
  // Don't compile-away addition and subtraction.
  EIGEN_OPTIMIZATION_BARRIER(r);
  r = psub_old(r, limit);
  // If greater than limit, simply return a.  Otherwise, account for sign.
  r = pselect_old(pcmp_lt_old(abs_a, limit), pselect_old(pcmp_lt_old(a, pzero_old(a)), pnegate_old(r), r), a);
  return r;
}

template <>
EIGEN_STRONG_INLINE Packet4f pfloor_old<Packet4f>(const Packet4f& a) {
  const Packet4f cst_1 = pset1_old<Packet4f>(1.0f);
  Packet4f tmp = print_old<Packet4f>(a);
  // If greater, subtract one.
  Packet4f mask = _mm_cmpgt_ps(tmp, a);
  mask = pand_old(mask, cst_1);
  return psub_old(tmp, mask);
}

template <>
EIGEN_STRONG_INLINE Packet2d pfloor_old<Packet2d>(const Packet2d& a) {
  const Packet2d cst_1 = pset1_old<Packet2d>(1.0);
  Packet2d tmp = print_old<Packet2d>(a);
  // If greater, subtract one.
  Packet2d mask = _mm_cmpgt_pd(tmp, a);
  mask = pand_old(mask, cst_1);
  return psub_old(tmp, mask);
}

template <>
EIGEN_STRONG_INLINE Packet4f pceil_old<Packet4f>(const Packet4f& a) {
  const Packet4f cst_1 = pset1_old<Packet4f>(1.0f);
  Packet4f tmp = print_old<Packet4f>(a);
  // If smaller, add one.
  Packet4f mask = _mm_cmplt_ps(tmp, a);
  mask = pand_old(mask, cst_1);
  return padd_old(tmp, mask);
}

template <>
EIGEN_STRONG_INLINE Packet2d pceil_old<Packet2d>(const Packet2d& a) {
  const Packet2d cst_1 = pset1_old<Packet2d>(1.0);
  Packet2d tmp = print_old<Packet2d>(a);
  // If smaller, add one.
  Packet2d mask = _mm_cmplt_pd(tmp, a);
  mask = pand_old(mask, cst_1);
  return padd_old(tmp, mask);
}
#endif

template <>
EIGEN_STRONG_INLINE Packet4f pload_old<Packet4f>(const float* from) {
  EIGEN_DEBUG_ALIGNED_LOAD return _mm_load_ps(from);
}
template <>
EIGEN_STRONG_INLINE Packet2d pload_old<Packet2d>(const double* from) {
  EIGEN_DEBUG_ALIGNED_LOAD return _mm_load_pd(from);
}
template <>
EIGEN_STRONG_INLINE Packet4i pload_old<Packet4i>(const int* from) {
  EIGEN_DEBUG_ALIGNED_LOAD return _mm_load_si128(reinterpret_cast<const __m128i*>(from));
}
template <>
EIGEN_STRONG_INLINE Packet16b pload_old<Packet16b>(const bool* from) {
  EIGEN_DEBUG_ALIGNED_LOAD return  _mm_load_si128(reinterpret_cast<const __m128i*>(from));
}

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
EIGEN_STRONG_INLINE Packet4f ploaddup_old<Packet4f>(const float* from) {
  return vec4f_swizzle1(_mm_castpd_ps(_mm_load_sd(reinterpret_cast<const double*>(from))), 0, 0, 1, 1);
}
template <>
EIGEN_STRONG_INLINE Packet2d ploaddup_old<Packet2d>(const double* from) {
  return pset1_old<Packet2d>(from[0]);
}
template <>
EIGEN_STRONG_INLINE Packet4i ploaddup_old<Packet4i>(const int* from) {
  Packet4i tmp;
  tmp = _mm_loadl_epi64(reinterpret_cast<const __m128i*>(from));
  return vec4i_swizzle1(tmp, 0, 0, 1, 1);
}

// Loads 8 bools from memory and returns the packet
// {b0, b0, b1, b1, b2, b2, b3, b3, b4, b4, b5, b5, b6, b6, b7, b7}
template <>
EIGEN_STRONG_INLINE Packet16b ploaddup_old<Packet16b>(const bool* from) {
  __m128i tmp = _mm_castpd_si128(pload1_old<Packet2d>(reinterpret_cast<const double*>(from)));
  return _mm_unpacklo_epi8(tmp, tmp);
}

// Loads 4 bools from memory and returns the packet
// {b0, b0  b0, b0, b1, b1, b1, b1, b2, b2, b2, b2, b3, b3, b3, b3}
template <>
EIGEN_STRONG_INLINE Packet16b ploadquad_old<Packet16b>(const bool* from) {
  __m128i tmp = _mm_castps_si128(pload1_old<Packet4f>(reinterpret_cast<const float*>(from)));
  tmp = _mm_unpacklo_epi8(tmp, tmp);
  return _mm_unpacklo_epi16(tmp, tmp);
}

template <>
EIGEN_STRONG_INLINE void pstore_old<float>(float* to, const Packet4f& from) {
  EIGEN_DEBUG_ALIGNED_STORE _mm_store_ps(to, from);
}
template <>
EIGEN_STRONG_INLINE void pstore_old<double>(double* to, const Packet2d& from) {
  EIGEN_DEBUG_ALIGNED_STORE _mm_store_pd(to, from);
}
template <>
EIGEN_STRONG_INLINE void pstore_old<int>(int* to, const Packet4i& from) {
  EIGEN_DEBUG_ALIGNED_STORE _mm_store_si128(reinterpret_cast<__m128i*>(to), from);
}
template <>
EIGEN_STRONG_INLINE void pstore_old<bool>(bool* to, const Packet16b& from) {
  EIGEN_DEBUG_ALIGNED_STORE _mm_store_si128(reinterpret_cast<__m128i*>(to), from);
}

template <>
EIGEN_STRONG_INLINE void pstoreu_old<double>(double* to, const Packet2d& from) {
  EIGEN_DEBUG_UNALIGNED_STORE _mm_storeu_pd(to, from);
}
template <>
EIGEN_STRONG_INLINE void pstoreu_old<float>(float* to, const Packet4f& from) {
  EIGEN_DEBUG_UNALIGNED_STORE _mm_storeu_ps(to, from);
}
template <>
EIGEN_STRONG_INLINE void pstoreu_old<int>(int* to, const Packet4i& from) {
  EIGEN_DEBUG_UNALIGNED_STORE _mm_storeu_si128(reinterpret_cast<__m128i*>(to), from);
}
template <>
EIGEN_STRONG_INLINE void pstoreu_old<bool>(bool* to, const Packet16b& from) {
  EIGEN_DEBUG_ALIGNED_STORE _mm_storeu_si128(reinterpret_cast<__m128i*>(to), from);
}

template <>
EIGEN_DEVICE_FUNC inline Packet4f pgather_old<float, Packet4f>(const float* from, Index stride) {
  return _mm_set_ps(from[3 * stride], from[2 * stride], from[1 * stride], from[0 * stride]);
}
template <>
EIGEN_DEVICE_FUNC inline Packet2d pgather_old<double, Packet2d>(const double* from, Index stride) {
  return _mm_set_pd(from[1 * stride], from[0 * stride]);
}
template <>
EIGEN_DEVICE_FUNC inline Packet4i pgather_old<int, Packet4i>(const int* from, Index stride) {
  return _mm_set_epi32(from[3 * stride], from[2 * stride], from[1 * stride], from[0 * stride]);
}

template <>
EIGEN_DEVICE_FUNC inline Packet16b pgather_old<bool, Packet16b>(const bool* from, Index stride) {
  return _mm_set_epi8(from[15 * stride], from[14 * stride], from[13 * stride], from[12 * stride], from[11 * stride],
                      from[10 * stride], from[9 * stride], from[8 * stride], from[7 * stride], from[6 * stride],
                      from[5 * stride], from[4 * stride], from[3 * stride], from[2 * stride], from[1 * stride],
                      from[0 * stride]);
}

template <>
EIGEN_DEVICE_FUNC inline void pscatter_old<float, Packet4f>(float* to, const Packet4f& from, Index stride) {
  to[stride * 0] = _mm_cvtss_f32(from);
  to[stride * 1] = _mm_cvtss_f32(_mm_shuffle_ps(from, from, 1));
  to[stride * 2] = _mm_cvtss_f32(_mm_shuffle_ps(from, from, 2));
  to[stride * 3] = _mm_cvtss_f32(_mm_shuffle_ps(from, from, 3));
}
template <>
EIGEN_DEVICE_FUNC inline void pscatter_old<double, Packet2d>(double* to, const Packet2d& from, Index stride) {
  to[stride * 0] = _mm_cvtsd_f64(from);
  to[stride * 1] = _mm_cvtsd_f64(_mm_shuffle_pd(from, from, 1));
}
template <>
EIGEN_DEVICE_FUNC inline void pscatter_old<int, Packet4i>(int* to, const Packet4i& from, Index stride) {
  to[stride * 0] = _mm_cvtsi128_si32(from);
  to[stride * 1] = _mm_cvtsi128_si32(_mm_shuffle_epi32(from, 1));
  to[stride * 2] = _mm_cvtsi128_si32(_mm_shuffle_epi32(from, 2));
  to[stride * 3] = _mm_cvtsi128_si32(_mm_shuffle_epi32(from, 3));
}
template <>
EIGEN_DEVICE_FUNC inline void pscatter_old<bool, Packet16b>(bool* to, const Packet16b& from, Index stride) {
  to[4 * stride * 0] = _mm_cvtsi128_si32(from);
  to[4 * stride * 1] = _mm_cvtsi128_si32(_mm_shuffle_epi32(from, 1));
  to[4 * stride * 2] = _mm_cvtsi128_si32(_mm_shuffle_epi32(from, 2));
  to[4 * stride * 3] = _mm_cvtsi128_si32(_mm_shuffle_epi32(from, 3));
}

// some compilers might be tempted to perform multiple moves instead of using a vector path.
template <>
EIGEN_STRONG_INLINE void pstore1_old<Packet4f>(float* to, const float& a) {
  Packet4f pa = _mm_set_ss(a);
  pstore_old(to, Packet4f(vec4f_swizzle1(pa, 0, 0, 0, 0)));
}
// some compilers might be tempted to perform multiple moves instead of using a vector path.
template <>
EIGEN_STRONG_INLINE void pstore1_old<Packet2d>(double* to, const double& a) {
  Packet2d pa = _mm_set_sd(a);
  pstore_old(to, Packet2d(vec2d_swizzle1(pa, 0, 0)));
}

#ifndef EIGEN_VECTORIZE_AVX
template <>
EIGEN_STRONG_INLINE void prefetch_old<float>(const float* addr) {
  _mm_prefetch((SsePrefetchPtrType)(addr), _MM_HINT_T0);
}
template <>
EIGEN_STRONG_INLINE void prefetch_old<double>(const double* addr) {
  _mm_prefetch((SsePrefetchPtrType)(addr), _MM_HINT_T0);
}
template <>
EIGEN_STRONG_INLINE void prefetch_old<int>(const int* addr) {
  _mm_prefetch((SsePrefetchPtrType)(addr), _MM_HINT_T0);
}
#endif

#if EIGEN_COMP_MSVC_STRICT && EIGEN_OS_WIN64
// The temporary variable fixes an internal compilation error in vs <= 2008 and a wrong-result bug in vs 2010
// Direct of the struct members fixed bug #62.
template <>
EIGEN_STRONG_INLINE float pfirst_old<Packet4f>(const Packet4f& a) {
  return a.m128_f32[0];
}
template <>
EIGEN_STRONG_INLINE double pfirst_old<Packet2d>(const Packet2d& a) {
  return a.m128d_f64[0];
}
template <>
EIGEN_STRONG_INLINE int pfirst_old<Packet4i>(const Packet4i& a) {
  int x = _mm_cvtsi128_si32(a);
  return x;
}
#elif EIGEN_COMP_MSVC_STRICT
// The temporary variable fixes an internal compilation error in vs <= 2008 and a wrong-result bug in vs 2010
template <>
EIGEN_STRONG_INLINE float pfirst_old<Packet4f>(const Packet4f& a) {
  float x = _mm_cvtss_f32(a);
  return x;
}
template <>
EIGEN_STRONG_INLINE double pfirst_old<Packet2d>(const Packet2d& a) {
  double x = _mm_cvtsd_f64(a);
  return x;
}
template <>
EIGEN_STRONG_INLINE int pfirst_old<Packet4i>(const Packet4i& a) {
  int x = _mm_cvtsi128_si32(a);
  return x;
}
#else
template <>
EIGEN_STRONG_INLINE float pfirst_old<Packet4f>(const Packet4f& a) {
  return _mm_cvtss_f32(a);
}
template <>
EIGEN_STRONG_INLINE double pfirst_old<Packet2d>(const Packet2d& a) {
  return _mm_cvtsd_f64(a);
}
template <>
EIGEN_STRONG_INLINE int pfirst_old<Packet4i>(const Packet4i& a) {
  return _mm_cvtsi128_si32(a);
}
#endif
template <>
EIGEN_STRONG_INLINE bool pfirst_old<Packet16b>(const Packet16b& a) {
  int x = _mm_cvtsi128_si32(a);
  return static_cast<bool>(x & 1);
}

template <>
EIGEN_STRONG_INLINE Packet4f preverse_old(const Packet4f& a) {
  return _mm_shuffle_ps(a, a, 0x1B);
}
template <>
EIGEN_STRONG_INLINE Packet2d preverse_old(const Packet2d& a) {
  return _mm_shuffle_pd(a, a, 0x1);
}
template <>
EIGEN_STRONG_INLINE Packet4i preverse_old(const Packet4i& a) {
  return _mm_shuffle_epi32(a, 0x1B);
}
template <>
EIGEN_STRONG_INLINE Packet16b preverse_old(const Packet16b& a) {
#ifdef EIGEN_VECTORIZE_SSSE3
  __m128i mask = _mm_set_epi8(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15);
  return _mm_shuffle_epi8(a, mask);
#else
  Packet16b tmp = _mm_shuffle_epi32(a, _MM_SHUFFLE(0, 1, 2, 3));
  tmp = _mm_shufflehi_epi16(_mm_shufflelo_epi16(tmp, _MM_SHUFFLE(2, 3, 0, 1)), _MM_SHUFFLE(2, 3, 0, 1));
  return _mm_or_si128(_mm_slli_epi16(tmp, 8), _mm_srli_epi16(tmp, 8));
#endif
}

template <>
EIGEN_STRONG_INLINE Packet4f pfrexp_old<Packet4f>(const Packet4f& a, Packet4f& exponent) {
  return pfrexp_generic(a, exponent);
}

// Extract exponent without existence of Packet2l.
template <>
EIGEN_STRONG_INLINE Packet2d pfrexp_generic_get_biased_exponent_old(const Packet2d& a) {
  const Packet2d cst_exp_mask = pset1frombits_old<Packet2d>(static_cast<uint64_t>(0x7ff0000000000000ull));
  __m128i a_expo = _mm_srli_epi64(_mm_castpd_si128(pand_old(a, cst_exp_mask)), 52);
  return _mm_cvtepi32_pd(vec4i_swizzle1(a_expo, 0, 2, 1, 3));
}

template <>
EIGEN_STRONG_INLINE Packet2d pfrexp_old<Packet2d>(const Packet2d& a, Packet2d& exponent) {
  return pfrexp_generic(a, exponent);
}

template <>
EIGEN_STRONG_INLINE Packet4f pldexp_old<Packet4f>(const Packet4f& a, const Packet4f& exponent) {
  return pldexp_generic(a, exponent);
}

// We specialize pldexp_old here, since the generic implementation uses Packet2l, which is not well
// supported by SSE, and has more range than is needed for exponents.
template <>
EIGEN_STRONG_INLINE Packet2d pldexp_old<Packet2d>(const Packet2d& a, const Packet2d& exponent) {
  // Clamp exponent to [-2099, 2099]
  const Packet2d max_exponent = pset1_old<Packet2d>(2099.0);
  const Packet2d e = pmin_old(pmax_old(exponent, pnegate_old(max_exponent)), max_exponent);

  // Convert e to integer and swizzle to low-order bits.
  const Packet4i ei = vec4i_swizzle1(_mm_cvtpd_epi32(e), 0, 3, 1, 3);

  // Split 2^e into four factors and multiply:
  const Packet4i bias = _mm_set_epi32(0, 1023, 0, 1023);
  Packet4i b = parithmetic_shift_right_old<2>(ei);                       // floor(e/4)
  Packet2d c = _mm_castsi128_pd(_mm_slli_epi64(padd_old(b, bias), 52));  // 2^b
  Packet2d out = pmul_old(pmul_old(pmul_old(a, c), c), c);                       // a * 2^(3b)
  b = psub_old(psub_old(psub_old(ei, b), b), b);                                 // e - 3b
  c = _mm_castsi128_pd(_mm_slli_epi64(padd_old(b, bias), 52));           // 2^(e - 3b)
  out = pmul_old(out, c);                                                // a * 2^e
  return out;
}

// with AVX, the default implementations based on pload1_old are faster
#ifndef __AVX__
template <>
EIGEN_STRONG_INLINE void pbroadcast4_old<Packet4f>(const float* a, Packet4f& a0, Packet4f& a1, Packet4f& a2, Packet4f& a3) {
  a3 = pload_old<Packet4f>(a);
  a0 = vec4f_swizzle1(a3, 0, 0, 0, 0);
  a1 = vec4f_swizzle1(a3, 1, 1, 1, 1);
  a2 = vec4f_swizzle1(a3, 2, 2, 2, 2);
  a3 = vec4f_swizzle1(a3, 3, 3, 3, 3);
}
template <>
EIGEN_STRONG_INLINE void pbroadcast4_old<Packet2d>(const double* a, Packet2d& a0, Packet2d& a1, Packet2d& a2,
                                               Packet2d& a3) {
#ifdef EIGEN_VECTORIZE_SSE3
  a0 = _mm_loaddup_pd(a + 0);
  a1 = _mm_loaddup_pd(a + 1);
  a2 = _mm_loaddup_pd(a + 2);
  a3 = _mm_loaddup_pd(a + 3);
#else
  a1 = pload_old<Packet2d>(a);
  a0 = vec2d_swizzle1(a1, 0, 0);
  a1 = vec2d_swizzle1(a1, 1, 1);
  a3 = pload_old<Packet2d>(a + 2);
  a2 = vec2d_swizzle1(a3, 0, 0);
  a3 = vec2d_swizzle1(a3, 1, 1);
#endif
}
#endif

EIGEN_STRONG_INLINE void punpackp_old(Packet4f* vecs) {
  vecs[1] = _mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(vecs[0]), 0x55));
  vecs[2] = _mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(vecs[0]), 0xAA));
  vecs[3] = _mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(vecs[0]), 0xFF));
  vecs[0] = _mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(vecs[0]), 0x00));
}

template <>
EIGEN_STRONG_INLINE float predux_old<Packet4f>(const Packet4f& a) {
  // Disable SSE3 _mm_hadd_pd that is extremely slow on all existing Intel's architectures
  // (from Nehalem to Haswell)
  // #ifdef EIGEN_VECTORIZE_SSE3
  //   Packet4f tmp = _mm_add_ps(a, vec4f_swizzle1(a,2,3,2,3));
  //   return pfirst_old<Packet4f>(_mm_hadd_ps(tmp, tmp));
  // #else
  Packet4f tmp = _mm_add_ps(a, _mm_movehl_ps(a, a));
  return pfirst_old<Packet4f>(_mm_add_ss(tmp, _mm_shuffle_ps(tmp, tmp, 1)));
  // #endif
}

template <>
EIGEN_STRONG_INLINE double predux_old<Packet2d>(const Packet2d& a) {
  // Disable SSE3 _mm_hadd_pd that is extremely slow on all existing Intel's architectures
  // (from Nehalem to Haswell)
  // #ifdef EIGEN_VECTORIZE_SSE3
  //   return pfirst_old<Packet2d>(_mm_hadd_pd(a, a));
  // #else
  return pfirst_old<Packet2d>(_mm_add_sd(a, _mm_unpackhi_pd(a, a)));
  // #endif
}

#ifdef EIGEN_VECTORIZE_SSSE3
template <>
EIGEN_STRONG_INLINE int predux_old<Packet4i>(const Packet4i& a) {
  Packet4i tmp0 = _mm_hadd_epi32(a, a);
  return pfirst_old<Packet4i>(_mm_hadd_epi32(tmp0, tmp0));
}

#else
template <>
EIGEN_STRONG_INLINE int predux_old<Packet4i>(const Packet4i& a) {
  Packet4i tmp = _mm_add_epi32(a, _mm_unpackhi_epi64(a, a));
  return pfirst_old(tmp) + pfirst_old<Packet4i>(_mm_shuffle_epi32(tmp, 1));
}
#endif

template <>
EIGEN_STRONG_INLINE bool predux_old<Packet16b>(const Packet16b& a) {
  Packet4i tmp = _mm_or_si128(a, _mm_unpackhi_epi64(a, a));
  return (pfirst_old(tmp) != 0) || (pfirst_old<Packet4i>(_mm_shuffle_epi32(tmp, 1)) != 0);
}

// Other reduction functions:

// mul
template <>
EIGEN_STRONG_INLINE float predux_mul_old<Packet4f>(const Packet4f& a) {
  Packet4f tmp = _mm_mul_ps(a, _mm_movehl_ps(a, a));
  return pfirst_old<Packet4f>(_mm_mul_ss(tmp, _mm_shuffle_ps(tmp, tmp, 1)));
}
template <>
EIGEN_STRONG_INLINE double predux_mul_old<Packet2d>(const Packet2d& a) {
  return pfirst_old<Packet2d>(_mm_mul_sd(a, _mm_unpackhi_pd(a, a)));
}
template <>
EIGEN_STRONG_INLINE int predux_mul_old<Packet4i>(const Packet4i& a) {
  // after some experiments, it is seems this is the fastest way to implement it
  // for GCC (eg., reusing pmul_old is very slow !)
  // TODO try to call _mm_mul_epu32 directly
  EIGEN_ALIGN16 int aux[4];
  pstore_old(aux, a);
  return (aux[0] * aux[1]) * (aux[2] * aux[3]);
}

template <>
EIGEN_STRONG_INLINE bool predux_mul_old<Packet16b>(const Packet16b& a) {
  Packet4i tmp = _mm_and_si128(a, _mm_unpackhi_epi64(a, a));
  return ((pfirst_old<Packet4i>(tmp) == 0x01010101) && (pfirst_old<Packet4i>(_mm_shuffle_epi32(tmp, 1)) == 0x01010101));
}

// min
template <>
EIGEN_STRONG_INLINE float predux_min_old<Packet4f>(const Packet4f& a) {
  Packet4f tmp = _mm_min_ps(a, _mm_movehl_ps(a, a));
  return pfirst_old<Packet4f>(_mm_min_ss(tmp, _mm_shuffle_ps(tmp, tmp, 1)));
}
template <>
EIGEN_STRONG_INLINE double predux_min_old<Packet2d>(const Packet2d& a) {
  return pfirst_old<Packet2d>(_mm_min_sd(a, _mm_unpackhi_pd(a, a)));
}
template <>
EIGEN_STRONG_INLINE int predux_min_old<Packet4i>(const Packet4i& a) {
#ifdef EIGEN_VECTORIZE_SSE4_1
  Packet4i tmp = _mm_min_epi32(a, _mm_shuffle_epi32(a, _MM_SHUFFLE(0, 0, 3, 2)));
  return pfirst_old<Packet4i>(_mm_min_epi32(tmp, _mm_shuffle_epi32(tmp, 1)));
#else
  // after some experiments, it is seems this is the fastest way to implement it
  // for GCC (eg., it does not like using std::min after the pstore_old !!)
  EIGEN_ALIGN16 int aux[4];
  pstore_old(aux, a);
  int aux0 = aux[0] < aux[1] ? aux[0] : aux[1];
  int aux2 = aux[2] < aux[3] ? aux[2] : aux[3];
  return aux0 < aux2 ? aux0 : aux2;
#endif  // EIGEN_VECTORIZE_SSE4_1
}

// max
template <>
EIGEN_STRONG_INLINE float predux_max_old<Packet4f>(const Packet4f& a) {
  Packet4f tmp = _mm_max_ps(a, _mm_movehl_ps(a, a));
  return pfirst_old<Packet4f>(_mm_max_ss(tmp, _mm_shuffle_ps(tmp, tmp, 1)));
}
template <>
EIGEN_STRONG_INLINE double predux_max_old<Packet2d>(const Packet2d& a) {
  return pfirst_old<Packet2d>(_mm_max_sd(a, _mm_unpackhi_pd(a, a)));
}
template <>
EIGEN_STRONG_INLINE int predux_max_old<Packet4i>(const Packet4i& a) {
#ifdef EIGEN_VECTORIZE_SSE4_1
  Packet4i tmp = _mm_max_epi32(a, _mm_shuffle_epi32(a, _MM_SHUFFLE(0, 0, 3, 2)));
  return pfirst_old<Packet4i>(_mm_max_epi32(tmp, _mm_shuffle_epi32(tmp, 1)));
#else
  // after some experiments, it is seems this is the fastest way to implement it
  // for GCC (eg., it does not like using std::min after the pstore_old !!)
  EIGEN_ALIGN16 int aux[4];
  pstore_old(aux, a);
  int aux0 = aux[0] > aux[1] ? aux[0] : aux[1];
  int aux2 = aux[2] > aux[3] ? aux[2] : aux[3];
  return aux0 > aux2 ? aux0 : aux2;
#endif  // EIGEN_VECTORIZE_SSE4_1
}

// not needed yet
// template<> EIGEN_STRONG_INLINE bool predux_all_old(const Packet4f& x)
// {
//   return _mm_movemask_ps(x) == 0xF;
// }

template <>
EIGEN_STRONG_INLINE bool predux_any_old(const Packet4f& x) {
  return _mm_movemask_ps(x) != 0x0;
}

EIGEN_DEVICE_FUNC inline void ptranspose_old(PacketBlock<Packet4f, 4>& kernel) {
  _MM_TRANSPOSE4_PS(kernel.packet[0], kernel.packet[1], kernel.packet[2], kernel.packet[3]);
}

EIGEN_DEVICE_FUNC inline void ptranspose_old(PacketBlock<Packet2d, 2>& kernel) {
  __m128d tmp = _mm_unpackhi_pd(kernel.packet[0], kernel.packet[1]);
  kernel.packet[0] = _mm_unpacklo_pd(kernel.packet[0], kernel.packet[1]);
  kernel.packet[1] = tmp;
}

EIGEN_DEVICE_FUNC inline void ptranspose_old(PacketBlock<Packet4i, 4>& kernel) {
  __m128i T0 = _mm_unpacklo_epi32(kernel.packet[0], kernel.packet[1]);
  __m128i T1 = _mm_unpacklo_epi32(kernel.packet[2], kernel.packet[3]);
  __m128i T2 = _mm_unpackhi_epi32(kernel.packet[0], kernel.packet[1]);
  __m128i T3 = _mm_unpackhi_epi32(kernel.packet[2], kernel.packet[3]);

  kernel.packet[0] = _mm_unpacklo_epi64(T0, T1);
  kernel.packet[1] = _mm_unpackhi_epi64(T0, T1);
  kernel.packet[2] = _mm_unpacklo_epi64(T2, T3);
  kernel.packet[3] = _mm_unpackhi_epi64(T2, T3);
}

EIGEN_DEVICE_FUNC inline void ptranspose_old(PacketBlock<Packet16b, 4>& kernel) {
  __m128i T0 = _mm_unpacklo_epi8(kernel.packet[0], kernel.packet[1]);
  __m128i T1 = _mm_unpackhi_epi8(kernel.packet[0], kernel.packet[1]);
  __m128i T2 = _mm_unpacklo_epi8(kernel.packet[2], kernel.packet[3]);
  __m128i T3 = _mm_unpackhi_epi8(kernel.packet[2], kernel.packet[3]);
  kernel.packet[0] = _mm_unpacklo_epi16(T0, T2);
  kernel.packet[1] = _mm_unpackhi_epi16(T0, T2);
  kernel.packet[2] = _mm_unpacklo_epi16(T1, T3);
  kernel.packet[3] = _mm_unpackhi_epi16(T1, T3);
}

EIGEN_DEVICE_FUNC inline void ptranspose_old(PacketBlock<Packet16b, 16>& kernel) {
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
  __m128i t0 =
      _mm_unpacklo_epi8(kernel.packet[0], kernel.packet[1]);  // 00 10 01 11 02 12 03 13 04 14 05 15 06 16 07 17
  __m128i t1 =
      _mm_unpackhi_epi8(kernel.packet[0], kernel.packet[1]);  // 08 18 09 19 0a 1a 0b 1b 0c 1c 0d 1d 0e 1e 0f 1f
  __m128i t2 =
      _mm_unpacklo_epi8(kernel.packet[2], kernel.packet[3]);  // 20 30 21 31 22 32 ...                     27 37
  __m128i t3 =
      _mm_unpackhi_epi8(kernel.packet[2], kernel.packet[3]);  // 28 38 29 39 2a 3a ...                     2f 3f
  __m128i t4 =
      _mm_unpacklo_epi8(kernel.packet[4], kernel.packet[5]);  // 40 50 41 51 42 52                         47 57
  __m128i t5 = _mm_unpackhi_epi8(kernel.packet[4], kernel.packet[5]);  // 48 58 49 59 4a 5a
  __m128i t6 = _mm_unpacklo_epi8(kernel.packet[6], kernel.packet[7]);
  __m128i t7 = _mm_unpackhi_epi8(kernel.packet[6], kernel.packet[7]);
  __m128i t8 = _mm_unpacklo_epi8(kernel.packet[8], kernel.packet[9]);
  __m128i t9 = _mm_unpackhi_epi8(kernel.packet[8], kernel.packet[9]);
  __m128i ta = _mm_unpacklo_epi8(kernel.packet[10], kernel.packet[11]);
  __m128i tb = _mm_unpackhi_epi8(kernel.packet[10], kernel.packet[11]);
  __m128i tc = _mm_unpacklo_epi8(kernel.packet[12], kernel.packet[13]);
  __m128i td = _mm_unpackhi_epi8(kernel.packet[12], kernel.packet[13]);
  __m128i te = _mm_unpacklo_epi8(kernel.packet[14], kernel.packet[15]);
  __m128i tf = _mm_unpackhi_epi8(kernel.packet[14], kernel.packet[15]);

  __m128i s0 = _mm_unpacklo_epi16(t0, t2);  // 00 10 20 30 01 11 21 31 02 12 22 32 03 13 23 33
  __m128i s1 = _mm_unpackhi_epi16(t0, t2);  // 04 14 24 34
  __m128i s2 = _mm_unpacklo_epi16(t1, t3);  // 08 18 28 38 ...
  __m128i s3 = _mm_unpackhi_epi16(t1, t3);  // 0c 1c 2c 3c ...
  __m128i s4 = _mm_unpacklo_epi16(t4, t6);  // 40 50 60 70 41 51 61 71 42 52 62 72 43 53 63 73
  __m128i s5 = _mm_unpackhi_epi16(t4, t6);  // 44 54 64 74 ...
  __m128i s6 = _mm_unpacklo_epi16(t5, t7);
  __m128i s7 = _mm_unpackhi_epi16(t5, t7);
  __m128i s8 = _mm_unpacklo_epi16(t8, ta);
  __m128i s9 = _mm_unpackhi_epi16(t8, ta);
  __m128i sa = _mm_unpacklo_epi16(t9, tb);
  __m128i sb = _mm_unpackhi_epi16(t9, tb);
  __m128i sc = _mm_unpacklo_epi16(tc, te);
  __m128i sd = _mm_unpackhi_epi16(tc, te);
  __m128i se = _mm_unpacklo_epi16(td, tf);
  __m128i sf = _mm_unpackhi_epi16(td, tf);

  __m128i u0 = _mm_unpacklo_epi32(s0, s4);  // 00 10 20 30 40 50 60 70 01 11 21 31 41 51 61 71
  __m128i u1 = _mm_unpackhi_epi32(s0, s4);  // 02 12 22 32 42 52 62 72 03 13 23 33 43 53 63 73
  __m128i u2 = _mm_unpacklo_epi32(s1, s5);
  __m128i u3 = _mm_unpackhi_epi32(s1, s5);
  __m128i u4 = _mm_unpacklo_epi32(s2, s6);
  __m128i u5 = _mm_unpackhi_epi32(s2, s6);
  __m128i u6 = _mm_unpacklo_epi32(s3, s7);
  __m128i u7 = _mm_unpackhi_epi32(s3, s7);
  __m128i u8 = _mm_unpacklo_epi32(s8, sc);
  __m128i u9 = _mm_unpackhi_epi32(s8, sc);
  __m128i ua = _mm_unpacklo_epi32(s9, sd);
  __m128i ub = _mm_unpackhi_epi32(s9, sd);
  __m128i uc = _mm_unpacklo_epi32(sa, se);
  __m128i ud = _mm_unpackhi_epi32(sa, se);
  __m128i ue = _mm_unpacklo_epi32(sb, sf);
  __m128i uf = _mm_unpackhi_epi32(sb, sf);

  kernel.packet[0] = _mm_unpacklo_epi64(u0, u8);
  kernel.packet[1] = _mm_unpackhi_epi64(u0, u8);
  kernel.packet[2] = _mm_unpacklo_epi64(u1, u9);
  kernel.packet[3] = _mm_unpackhi_epi64(u1, u9);
  kernel.packet[4] = _mm_unpacklo_epi64(u2, ua);
  kernel.packet[5] = _mm_unpackhi_epi64(u2, ua);
  kernel.packet[6] = _mm_unpacklo_epi64(u3, ub);
  kernel.packet[7] = _mm_unpackhi_epi64(u3, ub);
  kernel.packet[8] = _mm_unpacklo_epi64(u4, uc);
  kernel.packet[9] = _mm_unpackhi_epi64(u4, uc);
  kernel.packet[10] = _mm_unpacklo_epi64(u5, ud);
  kernel.packet[11] = _mm_unpackhi_epi64(u5, ud);
  kernel.packet[12] = _mm_unpacklo_epi64(u6, ue);
  kernel.packet[13] = _mm_unpackhi_epi64(u6, ue);
  kernel.packet[14] = _mm_unpacklo_epi64(u7, uf);
  kernel.packet[15] = _mm_unpackhi_epi64(u7, uf);
}

template <>
EIGEN_STRONG_INLINE Packet4i pblend_old(const Selector<4>& ifPacket, const Packet4i& thenPacket,
                                    const Packet4i& elsePacket) {
  const __m128i zero = _mm_setzero_si128();
  const __m128i select = _mm_set_epi32(ifPacket.select[3], ifPacket.select[2], ifPacket.select[1], ifPacket.select[0]);
  __m128i false_mask = _mm_cmpeq_epi32(select, zero);
#ifdef EIGEN_VECTORIZE_SSE4_1
  return _mm_blendv_epi8(thenPacket, elsePacket, false_mask);
#else
  return _mm_or_si128(_mm_andnot_si128(false_mask, thenPacket), _mm_and_si128(false_mask, elsePacket));
#endif
}
template <>
EIGEN_STRONG_INLINE Packet4f pblend_old(const Selector<4>& ifPacket, const Packet4f& thenPacket,
                                    const Packet4f& elsePacket) {
  const __m128 zero = _mm_setzero_ps();
  const __m128 select = _mm_set_ps(ifPacket.select[3], ifPacket.select[2], ifPacket.select[1], ifPacket.select[0]);
  __m128 false_mask = _mm_cmpeq_ps(select, zero);
#ifdef EIGEN_VECTORIZE_SSE4_1
  return _mm_blendv_ps(thenPacket, elsePacket, false_mask);
#else
  return _mm_or_ps(_mm_andnot_ps(false_mask, thenPacket), _mm_and_ps(false_mask, elsePacket));
#endif
}
template <>
EIGEN_STRONG_INLINE Packet2d pblend_old(const Selector<2>& ifPacket, const Packet2d& thenPacket,
                                    const Packet2d& elsePacket) {
  const __m128d zero = _mm_setzero_pd();
  const __m128d select = _mm_set_pd(ifPacket.select[1], ifPacket.select[0]);
  __m128d false_mask = _mm_cmpeq_pd(select, zero);
#ifdef EIGEN_VECTORIZE_SSE4_1
  return _mm_blendv_pd(thenPacket, elsePacket, false_mask);
#else
  return _mm_or_pd(_mm_andnot_pd(false_mask, thenPacket), _mm_and_pd(false_mask, elsePacket));
#endif
}

// Scalar path for pmadd_old with FMA to ensure consistency with vectorized path.
#ifdef EIGEN_VECTORIZE_FMA
template <>
EIGEN_STRONG_INLINE float pmadd_old(const float& a, const float& b, const float& c) {
  return ::fmaf(a, b, c);
}
template <>
EIGEN_STRONG_INLINE double pmadd_old(const double& a, const double& b, const double& c) {
  return ::fma(a, b, c);
}
template <>
EIGEN_STRONG_INLINE float pmsub_old(const float& a, const float& b, const float& c) {
  return ::fmaf(a, b, -c);
}
template <>
EIGEN_STRONG_INLINE double pmsub_old(const double& a, const double& b, const double& c) {
  return ::fma(a, b, -c);
}
template <>
EIGEN_STRONG_INLINE float pnmadd_old(const float& a, const float& b, const float& c) {
  return ::fmaf(-a, b, c);
}
template <>
EIGEN_STRONG_INLINE double pnmadd_old(const double& a, const double& b, const double& c) {
  return ::fma(-a, b, c);
}
template <>
EIGEN_STRONG_INLINE float pnmsub_old(const float& a, const float& b, const float& c) {
  return ::fmaf(-a, b, -c);
}
template <>
EIGEN_STRONG_INLINE double pnmsub_old(const double& a, const double& b, const double& c) {
  return ::fma(-a, b, -c);
}
#endif

#ifdef EIGEN_VECTORIZE_SSE4_1
// Helpers for half->float and float->half conversions.
// Currently only used by the AVX code.
EIGEN_STRONG_INLINE __m128i half2floatsse_old(__m128i h) {
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
  __m128i naninf_adj = _mm_and_si128(_mm_set1_epi32((128 - 16) << 23), naninf_mask);
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
  ou = _mm_castps_si128(_mm_sub_ps(_mm_castsi128_ps(ou), _mm_castsi128_ps(magic)));

  __m128i sign = _mm_slli_epi32(_mm_and_si128(input, _mm_set1_epi32(0x8000)), 16);
  // o.u |= (h.x & 0x8000) << 16;    // sign bit
  ou = _mm_or_si128(ou, sign);
  // return o.f;
  // We are actually returning uint version, to make
  // _mm256_insertf128_si256 work.
  return ou;
}

EIGEN_STRONG_INLINE __m128i float2half_old(__m128 f) {
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
  __m128i subnorm_mask = _mm_cmplt_epi32(_mm_castps_si128(f), _mm_set1_epi32(113 << 23));
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
#endif

#endif

#ifdef EIGEN_VECTORIZE_AVX

template <>
EIGEN_STRONG_INLINE Packet8f pset1_old<Packet8f>(const float& from) {
  return _mm256_set1_ps(from);
}
template <>
EIGEN_STRONG_INLINE Packet4d pset1_old<Packet4d>(const double& from) {
  return _mm256_set1_pd(from);
}
template <>
EIGEN_STRONG_INLINE Packet8i pset1_old<Packet8i>(const int& from) {
  return _mm256_set1_epi32(from);
}

template <>
EIGEN_STRONG_INLINE Packet8f pset1frombits_old<Packet8f>(unsigned int from) {
  return _mm256_castsi256_ps(pset1_old<Packet8i>(from));
}
template <>
EIGEN_STRONG_INLINE Packet4d pset1frombits_old<Packet4d>(uint64_t from) {
  return _mm256_castsi256_pd(_mm256_set1_epi64x(from));
}

template <>
EIGEN_STRONG_INLINE Packet8f pzero_old(const Packet8f& /*a*/) {
  return _mm256_setzero_ps();
}
template <>
EIGEN_STRONG_INLINE Packet4d pzero_old(const Packet4d& /*a*/) {
  return _mm256_setzero_pd();
}
template <>
EIGEN_STRONG_INLINE Packet8i pzero_old(const Packet8i& /*a*/) {
  return _mm256_setzero_si256();
}

template <>
EIGEN_STRONG_INLINE Packet8f peven_mask_old(const Packet8f& /*a*/) {
  return _mm256_castsi256_ps(_mm256_set_epi32(0, -1, 0, -1, 0, -1, 0, -1));
}
template <>
EIGEN_STRONG_INLINE Packet8i peven_mask_old(const Packet8i& /*a*/) {
  return _mm256_set_epi32(0, -1, 0, -1, 0, -1, 0, -1);
}
template <>
EIGEN_STRONG_INLINE Packet4d peven_mask_old(const Packet4d& /*a*/) {
  return _mm256_castsi256_pd(_mm256_set_epi32(0, 0, -1, -1, 0, 0, -1, -1));
}

template <>
EIGEN_STRONG_INLINE Packet8f pload1_old<Packet8f>(const float* from) {
  return _mm256_broadcast_ss(from);
}
template <>
EIGEN_STRONG_INLINE Packet4d pload1_old<Packet4d>(const double* from) {
  return _mm256_broadcast_sd(from);
}

template <>
EIGEN_STRONG_INLINE Packet8f padd_old<Packet8f>(const Packet8f& a, const Packet8f& b) {
  return _mm256_add_ps(a, b);
}
#ifdef EIGEN_VECTORIZE_AVX512
template <>
EIGEN_STRONG_INLINE Packet8f padd_old<Packet8f>(const Packet8f& a, const Packet8f& b, uint8_t umask) {
  __mmask16 mask = static_cast<__mmask16>(umask & 0x00FF);
  return _mm512_castps512_ps256(_mm512_maskz_add_ps(mask, _mm512_castps256_ps512(a), _mm512_castps256_ps512(b)));
}
#endif
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
EIGEN_STRONG_INLINE Packet8f plset_old<Packet8f>(const float& a) {
  return padd_old(pset1_old<Packet8f>(a), _mm256_set_ps(7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0, 0.0));
}
template <>
EIGEN_STRONG_INLINE Packet4d plset_old<Packet4d>(const double& a) {
  return padd_old(pset1_old<Packet4d>(a), _mm256_set_pd(3.0, 2.0, 1.0, 0.0));
}
template <>
EIGEN_STRONG_INLINE Packet8i plset_old<Packet8i>(const int& a) {
  return padd_old(pset1_old<Packet8i>(a), (Packet8i)_mm256_set_epi32(7, 6, 5, 4, 3, 2, 1, 0));
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
EIGEN_STRONG_INLINE Packet8f pconj_old(const Packet8f& a) {
  return a;
}
template <>
EIGEN_STRONG_INLINE Packet4d pconj_old(const Packet4d& a) {
  return a;
}
template <>
EIGEN_STRONG_INLINE Packet8i pconj_old(const Packet8i& a) {
  return a;
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
  return pset1_old<Packet8i>(0);
}

#ifdef EIGEN_VECTORIZE_FMA

template <>
EIGEN_STRONG_INLINE Packet8f pmadd_old(const Packet8f& a, const Packet8f& b, const Packet8f& c) {
  return _mm256_fmadd_ps(a, b, c);
}
template <>
EIGEN_STRONG_INLINE Packet4d pmadd_old(const Packet4d& a, const Packet4d& b, const Packet4d& c) {
  return _mm256_fmadd_pd(a, b, c);
}

template <>
EIGEN_STRONG_INLINE Packet8f pmsub_old(const Packet8f& a, const Packet8f& b, const Packet8f& c) {
  return _mm256_fmsub_ps(a, b, c);
}

template <>
EIGEN_STRONG_INLINE Packet4d pmsub_old(const Packet4d& a, const Packet4d& b, const Packet4d& c) {
  return _mm256_fmsub_pd(a, b, c);
}

template <>
EIGEN_STRONG_INLINE Packet8f pnmadd_old(const Packet8f& a, const Packet8f& b, const Packet8f& c) {
  return _mm256_fnmadd_ps(a, b, c);
}

template <>
EIGEN_STRONG_INLINE Packet4d pnmadd_old(const Packet4d& a, const Packet4d& b, const Packet4d& c) {
  return _mm256_fnmadd_pd(a, b, c);
}

template <>
EIGEN_STRONG_INLINE Packet8f pnmsub_old(const Packet8f& a, const Packet8f& b, const Packet8f& c) {
  return _mm256_fnmsub_ps(a, b, c);
}

template <>
EIGEN_STRONG_INLINE Packet4d pnmsub_old(const Packet4d& a, const Packet4d& b, const Packet4d& c) {
  return _mm256_fnmsub_pd(a, b, c);
}

#endif

template <>
EIGEN_STRONG_INLINE Packet8f pcmp_le_old(const Packet8f& a, const Packet8f& b) {
  return _mm256_cmp_ps(a, b, _CMP_LE_OQ);
}
template <>
EIGEN_STRONG_INLINE Packet8f pcmp_lt_old(const Packet8f& a, const Packet8f& b) {
  return _mm256_cmp_ps(a, b, _CMP_LT_OQ);
}
template <>
EIGEN_STRONG_INLINE Packet8f pcmp_lt_or_nan_old(const Packet8f& a, const Packet8f& b) {
  return _mm256_cmp_ps(a, b, _CMP_NGE_UQ);
}
template <>
EIGEN_STRONG_INLINE Packet8f pcmp_eq_old(const Packet8f& a, const Packet8f& b) {
  return _mm256_cmp_ps(a, b, _CMP_EQ_OQ);
}

template <>
EIGEN_STRONG_INLINE Packet4d pcmp_le_old(const Packet4d& a, const Packet4d& b) {
  return _mm256_cmp_pd(a, b, _CMP_LE_OQ);
}
template <>
EIGEN_STRONG_INLINE Packet4d pcmp_lt_old(const Packet4d& a, const Packet4d& b) {
  return _mm256_cmp_pd(a, b, _CMP_LT_OQ);
}
template <>
EIGEN_STRONG_INLINE Packet4d pcmp_lt_or_nan_old(const Packet4d& a, const Packet4d& b) {
  return _mm256_cmp_pd(a, b, _CMP_NGE_UQ);
}
template <>
EIGEN_STRONG_INLINE Packet4d pcmp_eq_old(const Packet4d& a, const Packet4d& b) {
  return _mm256_cmp_pd(a, b, _CMP_EQ_OQ);
}

template <>
EIGEN_STRONG_INLINE Packet8i pcmp_le_old(const Packet8i& a, const Packet8i& b) {
#ifdef EIGEN_VECTORIZE_AVX2
  return _mm256_xor_si256(_mm256_cmpgt_epi32(a, b), _mm256_set1_epi32(-1));
#else
  __m128i lo = _mm_cmpgt_epi32(_mm256_extractf128_si256(a, 0), _mm256_extractf128_si256(b, 0));
  lo = _mm_xor_si128(lo, _mm_set1_epi32(-1));
  __m128i hi = _mm_cmpgt_epi32(_mm256_extractf128_si256(a, 1), _mm256_extractf128_si256(b, 1));
  hi = _mm_xor_si128(hi, _mm_set1_epi32(-1));
  return _mm256_insertf128_si256(_mm256_castsi128_si256(lo), (hi), 1);
#endif
}
template <>
EIGEN_STRONG_INLINE Packet8i pcmp_lt_old(const Packet8i& a, const Packet8i& b) {
#ifdef EIGEN_VECTORIZE_AVX2
  return _mm256_cmpgt_epi32(b, a);
#else
  __m128i lo = _mm_cmpgt_epi32(_mm256_extractf128_si256(b, 0), _mm256_extractf128_si256(a, 0));
  __m128i hi = _mm_cmpgt_epi32(_mm256_extractf128_si256(b, 1), _mm256_extractf128_si256(a, 1));
  return _mm256_insertf128_si256(_mm256_castsi128_si256(lo), (hi), 1);
#endif
}
template <>
EIGEN_STRONG_INLINE Packet8i pcmp_eq_old(const Packet8i& a, const Packet8i& b) {
#ifdef EIGEN_VECTORIZE_AVX2
  return _mm256_cmpeq_epi32(a, b);
#else
  __m128i lo = _mm_cmpeq_epi32(_mm256_extractf128_si256(a, 0), _mm256_extractf128_si256(b, 0));
  __m128i hi = _mm_cmpeq_epi32(_mm256_extractf128_si256(a, 1), _mm256_extractf128_si256(b, 1));
  return _mm256_insertf128_si256(_mm256_castsi128_si256(lo), (hi), 1);
#endif
}

template <>
EIGEN_STRONG_INLINE Packet8f pmin_old<Packet8f>(const Packet8f& a, const Packet8f& b) {
#if EIGEN_COMP_GNUC && EIGEN_COMP_GNUC < 63
  // There appears to be a bug in GCC, by which the optimizer may flip
  // the argument order in calls to _mm_min_ps/_mm_max_ps, so we have to
  // resort to inline ASM here. This is supposed to be fixed in gcc6.3,
  // see also: https://gcc.gnu.org/bugzilla/show_bug.cgi?id=72867
  Packet8f res;
  asm("vminps %[a], %[b], %[res]" : [res] "=x"(res) : [a] "x"(a), [b] "x"(b));
  return res;
#else
  // Arguments are swapped to match NaN propagation behavior of std::min.
  return _mm256_min_ps(b, a);
#endif
}
template <>
EIGEN_STRONG_INLINE Packet4d pmin_old<Packet4d>(const Packet4d& a, const Packet4d& b) {
#if EIGEN_COMP_GNUC && EIGEN_COMP_GNUC < 63
  // See pmin_old above
  Packet4d res;
  asm("vminpd %[a], %[b], %[res]" : [res] "=x"(res) : [a] "x"(a), [b] "x"(b));
  return res;
#else
  // Arguments are swapped to match NaN propagation behavior of std::min.
  return _mm256_min_pd(b, a);
#endif
}
template <>
EIGEN_STRONG_INLINE Packet8i pmin_old<Packet8i>(const Packet8i& a, const Packet8i& b) {
#ifdef EIGEN_VECTORIZE_AVX2
  return _mm256_min_epi32(a, b);
#else
  __m128i lo = _mm_min_epi32(_mm256_extractf128_si256(a, 0), _mm256_extractf128_si256(b, 0));
  __m128i hi = _mm_min_epi32(_mm256_extractf128_si256(a, 1), _mm256_extractf128_si256(b, 1));
  return _mm256_insertf128_si256(_mm256_castsi128_si256(lo), (hi), 1);
#endif
}

template <>
EIGEN_STRONG_INLINE Packet8f pmax_old<Packet8f>(const Packet8f& a, const Packet8f& b) {
#if EIGEN_COMP_GNUC && EIGEN_COMP_GNUC < 63
  // See pmin_old above
  Packet8f res;
  asm("vmaxps %[a], %[b], %[res]" : [res] "=x"(res) : [a] "x"(a), [b] "x"(b));
  return res;
#else
  // Arguments are swapped to match NaN propagation behavior of std::max.
  return _mm256_max_ps(b, a);
#endif
}
template <>
EIGEN_STRONG_INLINE Packet4d pmax_old<Packet4d>(const Packet4d& a, const Packet4d& b) {
#if EIGEN_COMP_GNUC && EIGEN_COMP_GNUC < 63
  // See pmin_old above
  Packet4d res;
  asm("vmaxpd %[a], %[b], %[res]" : [res] "=x"(res) : [a] "x"(a), [b] "x"(b));
  return res;
#else
  // Arguments are swapped to match NaN propagation behavior of std::max.
  return _mm256_max_pd(b, a);
#endif
}
template <>
EIGEN_STRONG_INLINE Packet8i pmax_old<Packet8i>(const Packet8i& a, const Packet8i& b) {
#ifdef EIGEN_VECTORIZE_AVX2
  return _mm256_max_epi32(a, b);
#else
  __m128i lo = _mm_max_epi32(_mm256_extractf128_si256(a, 0), _mm256_extractf128_si256(b, 0));
  __m128i hi = _mm_max_epi32(_mm256_extractf128_si256(a, 1), _mm256_extractf128_si256(b, 1));
  return _mm256_insertf128_si256(_mm256_castsi128_si256(lo), (hi), 1);
#endif
}

// Add specializations for min/max with prescribed NaN progation.
template <>
EIGEN_STRONG_INLINE Packet8f pmin_old<PropagateNumbers, Packet8f>(const Packet8f& a, const Packet8f& b) {
  return pminmax_propagate_numbers_old(a, b, pmin_old<Packet8f>);
}
template <>
EIGEN_STRONG_INLINE Packet4d pmin_old<PropagateNumbers, Packet4d>(const Packet4d& a, const Packet4d& b) {
  return pminmax_propagate_numbers_old(a, b, pmin_old<Packet4d>);
}
template <>
EIGEN_STRONG_INLINE Packet8f pmax_old<PropagateNumbers, Packet8f>(const Packet8f& a, const Packet8f& b) {
  return pminmax_propagate_numbers_old(a, b, pmax_old<Packet8f>);
}
template <>
EIGEN_STRONG_INLINE Packet4d pmax_old<PropagateNumbers, Packet4d>(const Packet4d& a, const Packet4d& b) {
  return pminmax_propagate_numbers_old(a, b, pmax_old<Packet4d>);
}
template <>
EIGEN_STRONG_INLINE Packet8f pmin_old<PropagateNaN, Packet8f>(const Packet8f& a, const Packet8f& b) {
  return pminmax_propagate_nan_old(a, b, pmin_old<Packet8f>);
}
template <>
EIGEN_STRONG_INLINE Packet4d pmin_old<PropagateNaN, Packet4d>(const Packet4d& a, const Packet4d& b) {
  return pminmax_propagate_nan_old(a, b, pmin_old<Packet4d>);
}
template <>
EIGEN_STRONG_INLINE Packet8f pmax_old<PropagateNaN, Packet8f>(const Packet8f& a, const Packet8f& b) {
  return pminmax_propagate_nan_old(a, b, pmax_old<Packet8f>);
}
template <>
EIGEN_STRONG_INLINE Packet4d pmax_old<PropagateNaN, Packet4d>(const Packet4d& a, const Packet4d& b) {
  return pminmax_propagate_nan_old(a, b, pmax_old<Packet4d>);
}

template <>
EIGEN_STRONG_INLINE Packet8f print_old<Packet8f>(const Packet8f& a) {
  return _mm256_round_ps(a, _MM_FROUND_CUR_DIRECTION);
}
template <>
EIGEN_STRONG_INLINE Packet4d print_old<Packet4d>(const Packet4d& a) {
  return _mm256_round_pd(a, _MM_FROUND_CUR_DIRECTION);
}

template <>
EIGEN_STRONG_INLINE Packet8f pceil_old<Packet8f>(const Packet8f& a) {
  return _mm256_ceil_ps(a);
}
template <>
EIGEN_STRONG_INLINE Packet4d pceil_old<Packet4d>(const Packet4d& a) {
  return _mm256_ceil_pd(a);
}

template <>
EIGEN_STRONG_INLINE Packet8f pfloor_old<Packet8f>(const Packet8f& a) {
  return _mm256_floor_ps(a);
}
template <>
EIGEN_STRONG_INLINE Packet4d pfloor_old<Packet4d>(const Packet4d& a) {
  return _mm256_floor_pd(a);
}

template <>
EIGEN_STRONG_INLINE Packet8i ptrue_old<Packet8i>(const Packet8i& a) {
#ifdef EIGEN_VECTORIZE_AVX2
  // vpcmpeqd has lower latency than the more general vcmpps
  return _mm256_cmpeq_epi32(a, a);
#else
  const __m256 b = _mm256_castsi256_ps(a);
  return _mm256_castps_si256(_mm256_cmp_ps(b, b, _CMP_TRUE_UQ));
#endif
}

template <>
EIGEN_STRONG_INLINE Packet8f ptrue_old<Packet8f>(const Packet8f& a) {
#ifdef EIGEN_VECTORIZE_AVX2
  // vpcmpeqd has lower latency than the more general vcmpps
  const __m256i b = _mm256_castps_si256(a);
  return _mm256_castsi256_ps(_mm256_cmpeq_epi32(b, b));
#else
  return _mm256_cmp_ps(a, a, _CMP_TRUE_UQ);
#endif
}

template <>
EIGEN_STRONG_INLINE Packet4d ptrue_old<Packet4d>(const Packet4d& a) {
#ifdef EIGEN_VECTORIZE_AVX2
  // vpcmpeqq has lower latency than the more general vcmppd
  const __m256i b = _mm256_castpd_si256(a);
  return _mm256_castsi256_pd(_mm256_cmpeq_epi64(b, b));
#else
  return _mm256_cmp_pd(a, a, _CMP_TRUE_UQ);
#endif
}

template <>
EIGEN_STRONG_INLINE Packet8f pand_old<Packet8f>(const Packet8f& a, const Packet8f& b) {
  return _mm256_and_ps(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet4d pand_old<Packet4d>(const Packet4d& a, const Packet4d& b) {
  return _mm256_and_pd(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet8i pand_old<Packet8i>(const Packet8i& a, const Packet8i& b) {
#ifdef EIGEN_VECTORIZE_AVX2
  return _mm256_and_si256(a, b);
#else
  return _mm256_castps_si256(_mm256_and_ps(_mm256_castsi256_ps(a), _mm256_castsi256_ps(b)));
#endif
}

template <>
EIGEN_STRONG_INLINE Packet8f por_old<Packet8f>(const Packet8f& a, const Packet8f& b) {
  return _mm256_or_ps(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet4d por_old<Packet4d>(const Packet4d& a, const Packet4d& b) {
  return _mm256_or_pd(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet8i por_old<Packet8i>(const Packet8i& a, const Packet8i& b) {
#ifdef EIGEN_VECTORIZE_AVX2
  return _mm256_or_si256(a, b);
#else
  return _mm256_castps_si256(_mm256_or_ps(_mm256_castsi256_ps(a), _mm256_castsi256_ps(b)));
#endif
}

template <>
EIGEN_STRONG_INLINE Packet8f pxor_old<Packet8f>(const Packet8f& a, const Packet8f& b) {
  return _mm256_xor_ps(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet4d pxor_old<Packet4d>(const Packet4d& a, const Packet4d& b) {
  return _mm256_xor_pd(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet8i pxor_old<Packet8i>(const Packet8i& a, const Packet8i& b) {
#ifdef EIGEN_VECTORIZE_AVX2
  return _mm256_xor_si256(a, b);
#else
  return _mm256_castps_si256(_mm256_xor_ps(_mm256_castsi256_ps(a), _mm256_castsi256_ps(b)));
#endif
}

template <>
EIGEN_STRONG_INLINE Packet8f pandnot_old<Packet8f>(const Packet8f& a, const Packet8f& b) {
  return _mm256_andnot_ps(b, a);
}
template <>
EIGEN_STRONG_INLINE Packet4d pandnot_old<Packet4d>(const Packet4d& a, const Packet4d& b) {
  return _mm256_andnot_pd(b, a);
}
template <>
EIGEN_STRONG_INLINE Packet8i pandnot_old<Packet8i>(const Packet8i& a, const Packet8i& b) {
#ifdef EIGEN_VECTORIZE_AVX2
  return _mm256_andnot_si256(b, a);
#else
  return _mm256_castps_si256(_mm256_andnot_ps(_mm256_castsi256_ps(b), _mm256_castsi256_ps(a)));
#endif
}

template <>
EIGEN_STRONG_INLINE Packet8f pround_old<Packet8f>(const Packet8f& a) {
  const Packet8f mask = pset1frombits_old<Packet8f>(static_cast<numext::uint32_t>(0x80000000u));
  const Packet8f prev0dot5 = pset1frombits_old<Packet8f>(static_cast<numext::uint32_t>(0x3EFFFFFFu));
  return _mm256_round_ps(padd_old(por_old(pand_old(a, mask), prev0dot5), a), _MM_FROUND_TO_ZERO);
}
template <>
EIGEN_STRONG_INLINE Packet4d pround_old<Packet4d>(const Packet4d& a) {
  const Packet4d mask = pset1frombits_old<Packet4d>(static_cast<numext::uint64_t>(0x8000000000000000ull));
  const Packet4d prev0dot5 = pset1frombits_old<Packet4d>(static_cast<numext::uint64_t>(0x3FDFFFFFFFFFFFFFull));
  return _mm256_round_pd(padd_old(por_old(pand_old(a, mask), prev0dot5), a), _MM_FROUND_TO_ZERO);
}

template <>
EIGEN_STRONG_INLINE Packet8f pselect_old<Packet8f>(const Packet8f& mask, const Packet8f& a, const Packet8f& b) {
  return _mm256_blendv_ps(b, a, mask);
}
template <>
EIGEN_STRONG_INLINE Packet4d pselect_old<Packet4d>(const Packet4d& mask, const Packet4d& a, const Packet4d& b) {
  return _mm256_blendv_pd(b, a, mask);
}

template <int N>
EIGEN_STRONG_INLINE Packet8i parithmetic_shift_right_old(Packet8i a) {
#ifdef EIGEN_VECTORIZE_AVX2
  return _mm256_srai_epi32(a, N);
#else
  __m128i lo = _mm_srai_epi32(_mm256_extractf128_si256(a, 0), N);
  __m128i hi = _mm_srai_epi32(_mm256_extractf128_si256(a, 1), N);
  return _mm256_insertf128_si256(_mm256_castsi128_si256(lo), (hi), 1);
#endif
}

template <int N>
EIGEN_STRONG_INLINE Packet8i plogical_shift_right_old(Packet8i a) {
#ifdef EIGEN_VECTORIZE_AVX2
  return _mm256_srli_epi32(a, N);
#else
  __m128i lo = _mm_srli_epi32(_mm256_extractf128_si256(a, 0), N);
  __m128i hi = _mm_srli_epi32(_mm256_extractf128_si256(a, 1), N);
  return _mm256_insertf128_si256(_mm256_castsi128_si256(lo), (hi), 1);
#endif
}

template <int N>
EIGEN_STRONG_INLINE Packet8i plogical_shift_left_old(Packet8i a) {
#ifdef EIGEN_VECTORIZE_AVX2
  return _mm256_slli_epi32(a, N);
#else
  __m128i lo = _mm_slli_epi32(_mm256_extractf128_si256(a, 0), N);
  __m128i hi = _mm_slli_epi32(_mm256_extractf128_si256(a, 1), N);
  return _mm256_insertf128_si256(_mm256_castsi128_si256(lo), (hi), 1);
#endif
}

template <>
EIGEN_STRONG_INLINE Packet8f pload_old<Packet8f>(const float* from) {
  EIGEN_DEBUG_ALIGNED_LOAD return _mm256_load_ps(from);
}
template <>
EIGEN_STRONG_INLINE Packet4d pload_old<Packet4d>(const double* from) {
  EIGEN_DEBUG_ALIGNED_LOAD return _mm256_load_pd(from);
}
template <>
EIGEN_STRONG_INLINE Packet8i pload_old<Packet8i>(const int* from) {
  EIGEN_DEBUG_ALIGNED_LOAD return _mm256_load_si256(reinterpret_cast<const __m256i*>(from));
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
EIGEN_STRONG_INLINE Packet8f ploadu_old<Packet8f>(const float* from, uint8_t umask) {
#ifdef EIGEN_VECTORIZE_AVX512
  __mmask16 mask = static_cast<__mmask16>(umask & 0x00FF);
  EIGEN_DEBUG_UNALIGNED_LOAD return _mm512_castps512_ps256(_mm512_maskz_loadu_ps(mask, from));
#else
  Packet8i mask = _mm256_set1_epi8(static_cast<char>(umask));
  const Packet8i bit_mask =
      _mm256_set_epi32(0xffffff7f, 0xffffffbf, 0xffffffdf, 0xffffffef, 0xfffffff7, 0xfffffffb, 0xfffffffd, 0xfffffffe);
  mask = por_old<Packet8i>(mask, bit_mask);
  mask = pcmp_eq_old<Packet8i>(mask, _mm256_set1_epi32(0xffffffff));
  EIGEN_DEBUG_UNALIGNED_LOAD return _mm256_maskload_ps(from, mask);
#endif
}

// Loads 4 floats from memory a returns the packet {a0, a0  a1, a1, a2, a2, a3, a3}
template <>
EIGEN_STRONG_INLINE Packet8f ploaddup_old<Packet8f>(const float* from) {
  // TODO try to find a way to avoid the need of a temporary register
  //   Packet8f tmp  = _mm256_castps128_ps256(_mm_loadu_ps(from));
  //   tmp = _mm256_insertf128_ps(tmp, _mm_movehl_ps(_mm256_castps256_ps128(tmp),_mm256_castps256_ps128(tmp)), 1);
  //   return _mm256_unpacklo_ps(tmp,tmp);

  // _mm256_insertf128_ps is very slow on Haswell, thus:
  Packet8f tmp = _mm256_broadcast_ps((const __m128*)(const void*)from);
  // mimic an "inplace" permutation of the lower 128bits using a blend
  tmp = _mm256_blend_ps(
      tmp, _mm256_castps128_ps256(_mm_permute_ps(_mm256_castps256_ps128(tmp), _MM_SHUFFLE(1, 0, 1, 0))), 15);
  // then we can perform a consistent permutation on the global register to get everything in shape:
  return _mm256_permute_ps(tmp, _MM_SHUFFLE(3, 3, 2, 2));
}
// Loads 2 doubles from memory a returns the packet {a0, a0, a1, a1}
template <>
EIGEN_STRONG_INLINE Packet4d ploaddup_old<Packet4d>(const double* from) {
  Packet4d tmp = _mm256_broadcast_pd((const __m128d*)(const void*)from);
  return _mm256_permute_pd(tmp, 3 << 2);
}
// Loads 4 integers from memory a returns the packet {a0, a0, a1, a1, a2, a2, a3, a3}
template <>
EIGEN_STRONG_INLINE Packet8i ploaddup_old<Packet8i>(const int* from) {
#ifdef EIGEN_VECTORIZE_AVX2
  const Packet8i a = _mm256_castsi128_si256(ploadu_old<Packet4i>(from));
  return _mm256_permutevar8x32_epi32(a, _mm256_setr_epi32(0, 0, 1, 1, 2, 2, 3, 3));
#else
  __m256 tmp = _mm256_broadcast_ps((const __m128*)(const void*)from);
  // mimic an "inplace" permutation of the lower 128bits using a blend
  tmp = _mm256_blend_ps(
      tmp, _mm256_castps128_ps256(_mm_permute_ps(_mm256_castps256_ps128(tmp), _MM_SHUFFLE(1, 0, 1, 0))), 15);
  // then we can perform a consistent permutation on the global register to get everything in shape:
  return _mm256_castps_si256(_mm256_permute_ps(tmp, _MM_SHUFFLE(3, 3, 2, 2)));
#endif
}

// Loads 2 floats from memory a returns the packet {a0, a0  a0, a0, a1, a1, a1, a1}
template <>
EIGEN_STRONG_INLINE Packet8f ploadquad_old<Packet8f>(const float* from) {
  Packet8f tmp = _mm256_castps128_ps256(_mm_broadcast_ss(from));
  return _mm256_insertf128_ps(tmp, _mm_broadcast_ss(from + 1), 1);
}
template <>
EIGEN_STRONG_INLINE Packet8i ploadquad_old<Packet8i>(const int* from) {
  return _mm256_insertf128_si256(_mm256_set1_epi32(*from), _mm_set1_epi32(*(from + 1)), 1);
}

template <>
EIGEN_STRONG_INLINE void pstore_old<float>(float* to, const Packet8f& from) {
  EIGEN_DEBUG_ALIGNED_STORE _mm256_store_ps(to, from);
}
template <>
EIGEN_STRONG_INLINE void pstore_old<double>(double* to, const Packet4d& from) {
  EIGEN_DEBUG_ALIGNED_STORE _mm256_store_pd(to, from);
}
template <>
EIGEN_STRONG_INLINE void pstore_old<int>(int* to, const Packet8i& from) {
  EIGEN_DEBUG_ALIGNED_STORE _mm256_storeu_si256(reinterpret_cast<__m256i*>(to), from);
}

template <>
EIGEN_STRONG_INLINE void pstoreu_old<float>(float* to, const Packet8f& from) {
  EIGEN_DEBUG_UNALIGNED_STORE _mm256_storeu_ps(to, from);
}
template <>
EIGEN_STRONG_INLINE void pstoreu_old<double>(double* to, const Packet4d& from) {
  EIGEN_DEBUG_UNALIGNED_STORE _mm256_storeu_pd(to, from);
}
template <>
EIGEN_STRONG_INLINE void pstoreu_old<int>(int* to, const Packet8i& from) {
  EIGEN_DEBUG_UNALIGNED_STORE _mm256_storeu_si256(reinterpret_cast<__m256i*>(to), from);
}

template <>
EIGEN_STRONG_INLINE void pstoreu_old<float>(float* to, const Packet8f& from, uint8_t umask) {
#ifdef EIGEN_VECTORIZE_AVX512
  __mmask16 mask = static_cast<__mmask16>(umask & 0x00FF);
  EIGEN_DEBUG_UNALIGNED_STORE return _mm512_mask_storeu_ps(to, mask, _mm512_castps256_ps512(from));
#else
  Packet8i mask = _mm256_set1_epi8(static_cast<char>(umask));
  const Packet8i bit_mask =
      _mm256_set_epi32(0xffffff7f, 0xffffffbf, 0xffffffdf, 0xffffffef, 0xfffffff7, 0xfffffffb, 0xfffffffd, 0xfffffffe);
  mask = por_old<Packet8i>(mask, bit_mask);
  mask = pcmp_eq_old<Packet8i>(mask, _mm256_set1_epi32(0xffffffff));
  EIGEN_DEBUG_UNALIGNED_STORE return _mm256_maskstore_ps(to, mask, from);
#endif
}

// NOTE: leverage _mm256_i32gather_ps and _mm256_i32gather_pd if AVX2 instructions are available
// NOTE: for the record the following seems to be slower: return _mm256_i32gather_ps(from, _mm256_set1_epi32(stride),
// 4);
template <>
EIGEN_DEVICE_FUNC inline Packet8f pgather_old<float, Packet8f>(const float* from, Index stride) {
  return _mm256_set_ps(from[7 * stride], from[6 * stride], from[5 * stride], from[4 * stride], from[3 * stride],
                       from[2 * stride], from[1 * stride], from[0 * stride]);
}
template <>
EIGEN_DEVICE_FUNC inline Packet4d pgather_old<double, Packet4d>(const double* from, Index stride) {
  return _mm256_set_pd(from[3 * stride], from[2 * stride], from[1 * stride], from[0 * stride]);
}
template <>
EIGEN_DEVICE_FUNC inline Packet8i pgather_old<int, Packet8i>(const int* from, Index stride) {
  return _mm256_set_epi32(from[7 * stride], from[6 * stride], from[5 * stride], from[4 * stride], from[3 * stride],
                          from[2 * stride], from[1 * stride], from[0 * stride]);
}

template <>
EIGEN_DEVICE_FUNC inline void pscatter_old<float, Packet8f>(float* to, const Packet8f& from, Index stride) {
  __m128 low = _mm256_extractf128_ps(from, 0);
  to[stride * 0] = _mm_cvtss_f32(low);
  to[stride * 1] = _mm_cvtss_f32(_mm_shuffle_ps(low, low, 1));
  to[stride * 2] = _mm_cvtss_f32(_mm_shuffle_ps(low, low, 2));
  to[stride * 3] = _mm_cvtss_f32(_mm_shuffle_ps(low, low, 3));

  __m128 high = _mm256_extractf128_ps(from, 1);
  to[stride * 4] = _mm_cvtss_f32(high);
  to[stride * 5] = _mm_cvtss_f32(_mm_shuffle_ps(high, high, 1));
  to[stride * 6] = _mm_cvtss_f32(_mm_shuffle_ps(high, high, 2));
  to[stride * 7] = _mm_cvtss_f32(_mm_shuffle_ps(high, high, 3));
}
template <>
EIGEN_DEVICE_FUNC inline void pscatter_old<double, Packet4d>(double* to, const Packet4d& from, Index stride) {
  __m128d low = _mm256_extractf128_pd(from, 0);
  to[stride * 0] = _mm_cvtsd_f64(low);
  to[stride * 1] = _mm_cvtsd_f64(_mm_shuffle_pd(low, low, 1));
  __m128d high = _mm256_extractf128_pd(from, 1);
  to[stride * 2] = _mm_cvtsd_f64(high);
  to[stride * 3] = _mm_cvtsd_f64(_mm_shuffle_pd(high, high, 1));
}
template <>
EIGEN_DEVICE_FUNC inline void pscatter_old<int, Packet8i>(int* to, const Packet8i& from, Index stride) {
  __m128i low = _mm256_extractf128_si256(from, 0);
  to[stride * 0] = _mm_extract_epi32(low, 0);
  to[stride * 1] = _mm_extract_epi32(low, 1);
  to[stride * 2] = _mm_extract_epi32(low, 2);
  to[stride * 3] = _mm_extract_epi32(low, 3);

  __m128i high = _mm256_extractf128_si256(from, 1);
  to[stride * 4] = _mm_extract_epi32(high, 0);
  to[stride * 5] = _mm_extract_epi32(high, 1);
  to[stride * 6] = _mm_extract_epi32(high, 2);
  to[stride * 7] = _mm_extract_epi32(high, 3);
}

template <>
EIGEN_STRONG_INLINE void pstore1_old<Packet8f>(float* to, const float& a) {
  Packet8f pa = pset1_old<Packet8f>(a);
  pstore_old(to, pa);
}
template <>
EIGEN_STRONG_INLINE void pstore1_old<Packet4d>(double* to, const double& a) {
  Packet4d pa = pset1_old<Packet4d>(a);
  pstore_old(to, pa);
}
template <>
EIGEN_STRONG_INLINE void pstore1_old<Packet8i>(int* to, const int& a) {
  Packet8i pa = pset1_old<Packet8i>(a);
  pstore_old(to, pa);
}

#ifndef EIGEN_VECTORIZE_AVX512
template <>
EIGEN_STRONG_INLINE void prefetch_old<float>(const float* addr) {
  _mm_prefetch((SsePrefetchPtrType)(addr), _MM_HINT_T0);
}
template <>
EIGEN_STRONG_INLINE void prefetch_old<double>(const double* addr) {
  _mm_prefetch((SsePrefetchPtrType)(addr), _MM_HINT_T0);
}
template <>
EIGEN_STRONG_INLINE void prefetch_old<int>(const int* addr) {
  _mm_prefetch((SsePrefetchPtrType)(addr), _MM_HINT_T0);
}
#endif

template <>
EIGEN_STRONG_INLINE float pfirst_old<Packet8f>(const Packet8f& a) {
  return _mm_cvtss_f32(_mm256_castps256_ps128(a));
}
template <>
EIGEN_STRONG_INLINE double pfirst_old<Packet4d>(const Packet4d& a) {
  return _mm_cvtsd_f64(_mm256_castpd256_pd128(a));
}
template <>
EIGEN_STRONG_INLINE int pfirst_old<Packet8i>(const Packet8i& a) {
  return _mm_cvtsi128_si32(_mm256_castsi256_si128(a));
}

template <>
EIGEN_STRONG_INLINE Packet8f preverse_old(const Packet8f& a) {
  __m256 tmp = _mm256_shuffle_ps(a, a, 0x1b);
  return _mm256_permute2f128_ps(tmp, tmp, 1);
}
template <>
EIGEN_STRONG_INLINE Packet4d preverse_old(const Packet4d& a) {
  __m256d tmp = _mm256_shuffle_pd(a, a, 5);
  return _mm256_permute2f128_pd(tmp, tmp, 1);
#if 0
  // This version is unlikely to be faster as _mm256_shuffle_ps and _mm256_permute_pd
  // exhibit the same latency/throughput, but it is here for future reference/benchmarking...
  __m256d swap_halves = _mm256_permute2f128_pd(a,a,1);
    return _mm256_permute_pd(swap_halves,5);
#endif
}
template <>
EIGEN_STRONG_INLINE Packet8i preverse_old(const Packet8i& a) {
  return _mm256_castps_si256(preverse_old(_mm256_castsi256_ps(a)));
}

// pabs_old should be ok
template <>
EIGEN_STRONG_INLINE Packet8f pabs_old(const Packet8f& a) {
  const Packet8f mask = _mm256_castsi256_ps(_mm256_setr_epi32(0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF,
                                                              0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF));
  return _mm256_and_ps(a, mask);
}
template <>
EIGEN_STRONG_INLINE Packet4d pabs_old(const Packet4d& a) {
  const Packet4d mask = _mm256_castsi256_pd(_mm256_setr_epi32(0xFFFFFFFF, 0x7FFFFFFF, 0xFFFFFFFF, 0x7FFFFFFF,
                                                              0xFFFFFFFF, 0x7FFFFFFF, 0xFFFFFFFF, 0x7FFFFFFF));
  return _mm256_and_pd(a, mask);
}
template <>
EIGEN_STRONG_INLINE Packet8i pabs_old(const Packet8i& a) {
#ifdef EIGEN_VECTORIZE_AVX2
  return _mm256_abs_epi32(a);
#else
  __m128i lo = _mm_abs_epi32(_mm256_extractf128_si256(a, 0));
  __m128i hi = _mm_abs_epi32(_mm256_extractf128_si256(a, 1));
  return _mm256_insertf128_si256(_mm256_castsi128_si256(lo), (hi), 1);
#endif
}

template <>
EIGEN_STRONG_INLINE Packet8f pfrexp_old<Packet8f>(const Packet8f& a, Packet8f& exponent) {
  return pfrexp_generic(a, exponent);
}

// Extract exponent without existence of Packet4l.
template <>
EIGEN_STRONG_INLINE Packet4d pfrexp_generic_get_biased_exponent_old(const Packet4d& a) {
  const Packet4d cst_exp_mask = pset1frombits_old<Packet4d>(static_cast<uint64_t>(0x7ff0000000000000ull));
  __m256i a_expo = _mm256_castpd_si256(pand_old(a, cst_exp_mask));
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

template <>
EIGEN_STRONG_INLINE Packet4d pfrexp_old<Packet4d>(const Packet4d& a, Packet4d& exponent) {
  return pfrexp_generic(a, exponent);
}

template <>
EIGEN_STRONG_INLINE Packet8f pldexp_old<Packet8f>(const Packet8f& a, const Packet8f& exponent) {
  return pldexp_generic(a, exponent);
}

template <>
EIGEN_STRONG_INLINE Packet4d pldexp_old<Packet4d>(const Packet4d& a, const Packet4d& exponent) {
  // Clamp exponent to [-2099, 2099]
  const Packet4d max_exponent = pset1_old<Packet4d>(2099.0);
  const Packet4i e = _mm256_cvtpd_epi32(pmin_old(pmax_old(exponent, pnegate_old(max_exponent)), max_exponent));

  // Split 2^e into four factors and multiply.
  const Packet4i bias = pset1_old<Packet4i>(1023);
  Packet4i b = parithmetic_shift_right_old<2>(e);  // floor(e/4)

  // 2^b
  Packet4i hi = vec4i_swizzle1(padd_old(b, bias), 0, 2, 1, 3);
  Packet4i lo = _mm_slli_epi64(hi, 52);
  hi = _mm_slli_epi64(_mm_srli_epi64(hi, 32), 52);
  Packet4d c = _mm256_castsi256_pd(_mm256_insertf128_si256(_mm256_castsi128_si256(lo), hi, 1));
  Packet4d out = pmul_old(pmul_old(pmul_old(a, c), c), c);  // a * 2^(3b)

  // 2^(e - 3b)
  b = psub_old(psub_old(psub_old(e, b), b), b);  // e - 3b
  hi = vec4i_swizzle1(padd_old(b, bias), 0, 2, 1, 3);
  lo = _mm_slli_epi64(hi, 52);
  hi = _mm_slli_epi64(_mm_srli_epi64(hi, 32), 52);
  c = _mm256_castsi256_pd(_mm256_insertf128_si256(_mm256_castsi128_si256(lo), hi, 1));
  out = pmul_old(out, c);  // a * 2^e
  return out;
}

template <>
EIGEN_STRONG_INLINE float predux_old<Packet8f>(const Packet8f& a) {
  return predux_old(Packet4f(_mm_add_ps(_mm256_castps256_ps128(a), _mm256_extractf128_ps(a, 1))));
}
template <>
EIGEN_STRONG_INLINE double predux_old<Packet4d>(const Packet4d& a) {
  return predux_old(Packet2d(_mm_add_pd(_mm256_castpd256_pd128(a), _mm256_extractf128_pd(a, 1))));
}
template <>
EIGEN_STRONG_INLINE int predux_old<Packet8i>(const Packet8i& a) {
  return predux_old(Packet4i(_mm_add_epi32(_mm256_castsi256_si128(a), _mm256_extractf128_si256(a, 1))));
}

template <>
EIGEN_STRONG_INLINE Packet4f predux_half_dowto4_old<Packet8f>(const Packet8f& a) {
  return _mm_add_ps(_mm256_castps256_ps128(a), _mm256_extractf128_ps(a, 1));
}
template <>
EIGEN_STRONG_INLINE Packet4i predux_half_dowto4_old<Packet8i>(const Packet8i& a) {
  return _mm_add_epi32(_mm256_castsi256_si128(a), _mm256_extractf128_si256(a, 1));
}

template <>
EIGEN_STRONG_INLINE float predux_mul_old<Packet8f>(const Packet8f& a) {
  Packet8f tmp;
  tmp = _mm256_mul_ps(a, _mm256_permute2f128_ps(a, a, 1));
  tmp = _mm256_mul_ps(tmp, _mm256_shuffle_ps(tmp, tmp, _MM_SHUFFLE(1, 0, 3, 2)));
  return pfirst_old(_mm256_mul_ps(tmp, _mm256_shuffle_ps(tmp, tmp, 1)));
}
template <>
EIGEN_STRONG_INLINE double predux_mul_old<Packet4d>(const Packet4d& a) {
  Packet4d tmp;
  tmp = _mm256_mul_pd(a, _mm256_permute2f128_pd(a, a, 1));
  return pfirst_old(_mm256_mul_pd(tmp, _mm256_shuffle_pd(tmp, tmp, 1)));
}

template <>
EIGEN_STRONG_INLINE float predux_min_old<Packet8f>(const Packet8f& a) {
  Packet8f tmp = _mm256_min_ps(a, _mm256_permute2f128_ps(a, a, 1));
  tmp = _mm256_min_ps(tmp, _mm256_shuffle_ps(tmp, tmp, _MM_SHUFFLE(1, 0, 3, 2)));
  return pfirst_old(_mm256_min_ps(tmp, _mm256_shuffle_ps(tmp, tmp, 1)));
}
template <>
EIGEN_STRONG_INLINE double predux_min_old<Packet4d>(const Packet4d& a) {
  Packet4d tmp = _mm256_min_pd(a, _mm256_permute2f128_pd(a, a, 1));
  return pfirst_old(_mm256_min_pd(tmp, _mm256_shuffle_pd(tmp, tmp, 1)));
}

template <>
EIGEN_STRONG_INLINE float predux_max_old<Packet8f>(const Packet8f& a) {
  Packet8f tmp = _mm256_max_ps(a, _mm256_permute2f128_ps(a, a, 1));
  tmp = _mm256_max_ps(tmp, _mm256_shuffle_ps(tmp, tmp, _MM_SHUFFLE(1, 0, 3, 2)));
  return pfirst_old(_mm256_max_ps(tmp, _mm256_shuffle_ps(tmp, tmp, 1)));
}

template <>
EIGEN_STRONG_INLINE double predux_max_old<Packet4d>(const Packet4d& a) {
  Packet4d tmp = _mm256_max_pd(a, _mm256_permute2f128_pd(a, a, 1));
  return pfirst_old(_mm256_max_pd(tmp, _mm256_shuffle_pd(tmp, tmp, 1)));
}

// not needed yet
// template<> EIGEN_STRONG_INLINE bool predux_all_old(const Packet8f& x)
// {
//   return _mm256_movemask_ps(x)==0xFF;
// }

template <>
EIGEN_STRONG_INLINE bool predux_any_old(const Packet8f& x) {
  return _mm256_movemask_ps(x) != 0;
}

EIGEN_DEVICE_FUNC inline void ptranspose_old(PacketBlock<Packet8f, 8>& kernel) {
  __m256 T0 = _mm256_unpacklo_ps(kernel.packet[0], kernel.packet[1]);
  __m256 T1 = _mm256_unpackhi_ps(kernel.packet[0], kernel.packet[1]);
  __m256 T2 = _mm256_unpacklo_ps(kernel.packet[2], kernel.packet[3]);
  __m256 T3 = _mm256_unpackhi_ps(kernel.packet[2], kernel.packet[3]);
  __m256 T4 = _mm256_unpacklo_ps(kernel.packet[4], kernel.packet[5]);
  __m256 T5 = _mm256_unpackhi_ps(kernel.packet[4], kernel.packet[5]);
  __m256 T6 = _mm256_unpacklo_ps(kernel.packet[6], kernel.packet[7]);
  __m256 T7 = _mm256_unpackhi_ps(kernel.packet[6], kernel.packet[7]);
  __m256 S0 = _mm256_shuffle_ps(T0, T2, _MM_SHUFFLE(1, 0, 1, 0));
  __m256 S1 = _mm256_shuffle_ps(T0, T2, _MM_SHUFFLE(3, 2, 3, 2));
  __m256 S2 = _mm256_shuffle_ps(T1, T3, _MM_SHUFFLE(1, 0, 1, 0));
  __m256 S3 = _mm256_shuffle_ps(T1, T3, _MM_SHUFFLE(3, 2, 3, 2));
  __m256 S4 = _mm256_shuffle_ps(T4, T6, _MM_SHUFFLE(1, 0, 1, 0));
  __m256 S5 = _mm256_shuffle_ps(T4, T6, _MM_SHUFFLE(3, 2, 3, 2));
  __m256 S6 = _mm256_shuffle_ps(T5, T7, _MM_SHUFFLE(1, 0, 1, 0));
  __m256 S7 = _mm256_shuffle_ps(T5, T7, _MM_SHUFFLE(3, 2, 3, 2));
  kernel.packet[0] = _mm256_permute2f128_ps(S0, S4, 0x20);
  kernel.packet[1] = _mm256_permute2f128_ps(S1, S5, 0x20);
  kernel.packet[2] = _mm256_permute2f128_ps(S2, S6, 0x20);
  kernel.packet[3] = _mm256_permute2f128_ps(S3, S7, 0x20);
  kernel.packet[4] = _mm256_permute2f128_ps(S0, S4, 0x31);
  kernel.packet[5] = _mm256_permute2f128_ps(S1, S5, 0x31);
  kernel.packet[6] = _mm256_permute2f128_ps(S2, S6, 0x31);
  kernel.packet[7] = _mm256_permute2f128_ps(S3, S7, 0x31);
}

EIGEN_DEVICE_FUNC inline void ptranspose_old(PacketBlock<Packet8f, 4>& kernel) {
  __m256 T0 = _mm256_unpacklo_ps(kernel.packet[0], kernel.packet[1]);
  __m256 T1 = _mm256_unpackhi_ps(kernel.packet[0], kernel.packet[1]);
  __m256 T2 = _mm256_unpacklo_ps(kernel.packet[2], kernel.packet[3]);
  __m256 T3 = _mm256_unpackhi_ps(kernel.packet[2], kernel.packet[3]);

  __m256 S0 = _mm256_shuffle_ps(T0, T2, _MM_SHUFFLE(1, 0, 1, 0));
  __m256 S1 = _mm256_shuffle_ps(T0, T2, _MM_SHUFFLE(3, 2, 3, 2));
  __m256 S2 = _mm256_shuffle_ps(T1, T3, _MM_SHUFFLE(1, 0, 1, 0));
  __m256 S3 = _mm256_shuffle_ps(T1, T3, _MM_SHUFFLE(3, 2, 3, 2));

  kernel.packet[0] = _mm256_permute2f128_ps(S0, S1, 0x20);
  kernel.packet[1] = _mm256_permute2f128_ps(S2, S3, 0x20);
  kernel.packet[2] = _mm256_permute2f128_ps(S0, S1, 0x31);
  kernel.packet[3] = _mm256_permute2f128_ps(S2, S3, 0x31);
}

EIGEN_DEVICE_FUNC inline void ptranspose_old(PacketBlock<Packet8i, 8>& kernel) {
  __m256i T0 = MM256_UNPACKLO_EPI32(kernel.packet[0], kernel.packet[1]);
  __m256i T1 = MM256_UNPACKHI_EPI32(kernel.packet[0], kernel.packet[1]);
  __m256i T2 = MM256_UNPACKLO_EPI32(kernel.packet[2], kernel.packet[3]);
  __m256i T3 = MM256_UNPACKHI_EPI32(kernel.packet[2], kernel.packet[3]);
  __m256i T4 = MM256_UNPACKLO_EPI32(kernel.packet[4], kernel.packet[5]);
  __m256i T5 = MM256_UNPACKHI_EPI32(kernel.packet[4], kernel.packet[5]);
  __m256i T6 = MM256_UNPACKLO_EPI32(kernel.packet[6], kernel.packet[7]);
  __m256i T7 = MM256_UNPACKHI_EPI32(kernel.packet[6], kernel.packet[7]);
  __m256i S0 = MM256_SHUFFLE_EPI32(T0, T2, _MM_SHUFFLE(1, 0, 1, 0));
  __m256i S1 = MM256_SHUFFLE_EPI32(T0, T2, _MM_SHUFFLE(3, 2, 3, 2));
  __m256i S2 = MM256_SHUFFLE_EPI32(T1, T3, _MM_SHUFFLE(1, 0, 1, 0));
  __m256i S3 = MM256_SHUFFLE_EPI32(T1, T3, _MM_SHUFFLE(3, 2, 3, 2));
  __m256i S4 = MM256_SHUFFLE_EPI32(T4, T6, _MM_SHUFFLE(1, 0, 1, 0));
  __m256i S5 = MM256_SHUFFLE_EPI32(T4, T6, _MM_SHUFFLE(3, 2, 3, 2));
  __m256i S6 = MM256_SHUFFLE_EPI32(T5, T7, _MM_SHUFFLE(1, 0, 1, 0));
  __m256i S7 = MM256_SHUFFLE_EPI32(T5, T7, _MM_SHUFFLE(3, 2, 3, 2));
  kernel.packet[0] = _mm256_permute2f128_si256(S0, S4, 0x20);
  kernel.packet[1] = _mm256_permute2f128_si256(S1, S5, 0x20);
  kernel.packet[2] = _mm256_permute2f128_si256(S2, S6, 0x20);
  kernel.packet[3] = _mm256_permute2f128_si256(S3, S7, 0x20);
  kernel.packet[4] = _mm256_permute2f128_si256(S0, S4, 0x31);
  kernel.packet[5] = _mm256_permute2f128_si256(S1, S5, 0x31);
  kernel.packet[6] = _mm256_permute2f128_si256(S2, S6, 0x31);
  kernel.packet[7] = _mm256_permute2f128_si256(S3, S7, 0x31);
}

EIGEN_DEVICE_FUNC inline void ptranspose_old(PacketBlock<Packet8i, 4>& kernel) {
  __m256i T0 = MM256_UNPACKLO_EPI32(kernel.packet[0], kernel.packet[1]);
  __m256i T1 = MM256_UNPACKHI_EPI32(kernel.packet[0], kernel.packet[1]);
  __m256i T2 = MM256_UNPACKLO_EPI32(kernel.packet[2], kernel.packet[3]);
  __m256i T3 = MM256_UNPACKHI_EPI32(kernel.packet[2], kernel.packet[3]);

  __m256i S0 = MM256_SHUFFLE_EPI32(T0, T2, _MM_SHUFFLE(1, 0, 1, 0));
  __m256i S1 = MM256_SHUFFLE_EPI32(T0, T2, _MM_SHUFFLE(3, 2, 3, 2));
  __m256i S2 = MM256_SHUFFLE_EPI32(T1, T3, _MM_SHUFFLE(1, 0, 1, 0));
  __m256i S3 = MM256_SHUFFLE_EPI32(T1, T3, _MM_SHUFFLE(3, 2, 3, 2));

  kernel.packet[0] = _mm256_permute2f128_si256(S0, S1, 0x20);
  kernel.packet[1] = _mm256_permute2f128_si256(S2, S3, 0x20);
  kernel.packet[2] = _mm256_permute2f128_si256(S0, S1, 0x31);
  kernel.packet[3] = _mm256_permute2f128_si256(S2, S3, 0x31);
}

EIGEN_DEVICE_FUNC inline void ptranspose_old(PacketBlock<Packet4d, 4>& kernel) {
  __m256d T0 = _mm256_shuffle_pd(kernel.packet[0], kernel.packet[1], 15);
  __m256d T1 = _mm256_shuffle_pd(kernel.packet[0], kernel.packet[1], 0);
  __m256d T2 = _mm256_shuffle_pd(kernel.packet[2], kernel.packet[3], 15);
  __m256d T3 = _mm256_shuffle_pd(kernel.packet[2], kernel.packet[3], 0);

  kernel.packet[1] = _mm256_permute2f128_pd(T0, T2, 32);
  kernel.packet[3] = _mm256_permute2f128_pd(T0, T2, 49);
  kernel.packet[0] = _mm256_permute2f128_pd(T1, T3, 32);
  kernel.packet[2] = _mm256_permute2f128_pd(T1, T3, 49);
}

template <>
EIGEN_STRONG_INLINE Packet8f pblend_old(const Selector<8>& ifPacket, const Packet8f& thenPacket,
                                    const Packet8f& elsePacket) {
  const __m256 zero = _mm256_setzero_ps();
  const __m256 select = _mm256_set_ps(ifPacket.select[7], ifPacket.select[6], ifPacket.select[5], ifPacket.select[4],
                                      ifPacket.select[3], ifPacket.select[2], ifPacket.select[1], ifPacket.select[0]);
  __m256 false_mask = _mm256_cmp_ps(select, zero, _CMP_EQ_UQ);
  return _mm256_blendv_ps(thenPacket, elsePacket, false_mask);
}
template <>
EIGEN_STRONG_INLINE Packet4d pblend_old(const Selector<4>& ifPacket, const Packet4d& thenPacket,
                                    const Packet4d& elsePacket) {
  const __m256d zero = _mm256_setzero_pd();
  const __m256d select = _mm256_set_pd(ifPacket.select[3], ifPacket.select[2], ifPacket.select[1], ifPacket.select[0]);
  __m256d false_mask = _mm256_cmp_pd(select, zero, _CMP_EQ_UQ);
  return _mm256_blendv_pd(thenPacket, elsePacket, false_mask);
}

// Packet math for Eigen::half

template <>
EIGEN_STRONG_INLINE Packet8h pset1_old<Packet8h>(const Eigen::half& from) {
  return _mm_set1_epi16(numext::bit_cast<numext::uint16_t>(from));
}

template <>
EIGEN_STRONG_INLINE Eigen::half pfirst_old<Packet8h>(const Packet8h& from) {
  return numext::bit_cast<Eigen::half>(static_cast<numext::uint16_t>(_mm_extract_epi16(from, 0)));
}

template <>
EIGEN_STRONG_INLINE Packet8h pload_old<Packet8h>(const Eigen::half* from) {
  return _mm_load_si128(reinterpret_cast<const __m128i*>(from));
}

template <>
EIGEN_STRONG_INLINE Packet8h ploadu_old<Packet8h>(const Eigen::half* from) {
  return _mm_loadu_si128(reinterpret_cast<const __m128i*>(from));
}

template <>
EIGEN_STRONG_INLINE void pstore_old<Eigen::half>(Eigen::half* to, const Packet8h& from) {
  _mm_store_si128(reinterpret_cast<__m128i*>(to), from);
}

template <>
EIGEN_STRONG_INLINE void pstoreu_old<Eigen::half>(Eigen::half* to, const Packet8h& from) {
  _mm_storeu_si128(reinterpret_cast<__m128i*>(to), from);
}

template <>
EIGEN_STRONG_INLINE Packet8h ploaddup_old<Packet8h>(const Eigen::half* from) {
  const numext::uint16_t a = numext::bit_cast<numext::uint16_t>(from[0]);
  const numext::uint16_t b = numext::bit_cast<numext::uint16_t>(from[1]);
  const numext::uint16_t c = numext::bit_cast<numext::uint16_t>(from[2]);
  const numext::uint16_t d = numext::bit_cast<numext::uint16_t>(from[3]);
  return _mm_set_epi16(d, d, c, c, b, b, a, a);
}

template <>
EIGEN_STRONG_INLINE Packet8h ploadquad_old<Packet8h>(const Eigen::half* from) {
  const numext::uint16_t a = numext::bit_cast<numext::uint16_t>(from[0]);
  const numext::uint16_t b = numext::bit_cast<numext::uint16_t>(from[1]);
  return _mm_set_epi16(b, b, b, b, a, a, a, a);
}

template <>
EIGEN_STRONG_INLINE Packet8h ptrue_old(const Packet8h& a) {
  return _mm_cmpeq_epi32(a, a);
}

template <>
EIGEN_STRONG_INLINE Packet8h pabs_old(const Packet8h& a) {
  const __m128i sign_mask = _mm_set1_epi16(static_cast<numext::uint16_t>(0x8000));
  return _mm_andnot_si128(sign_mask, a);
}

// Helper function for bit packing snippet of low precision comparison.
// It packs the flags from 16x16 to 8x16.
EIGEN_STRONG_INLINE __m128i Pack16To8_old(Packet8f rf) {
  return _mm_packs_epi32(_mm256_extractf128_si256(_mm256_castps_si256(rf), 0),
                         _mm256_extractf128_si256(_mm256_castps_si256(rf), 1));
}

EIGEN_STRONG_INLINE Packet8f half2float_old(const Packet8h& a) {
#ifdef EIGEN_HAS_FP16_C
  return _mm256_cvtph_ps(a);
#else
  Eigen::internal::Packet8f pp = _mm256_castsi256_ps(
      _mm256_insertf128_si256(_mm256_castsi128_si256(half2floatsse_old(a)), half2floatsse_old(_mm_srli_si128(a, 8)), 1));
  return pp;
#endif
}

EIGEN_STRONG_INLINE Packet8h float2half_old(const Packet8f& a) {
#ifdef EIGEN_HAS_FP16_C
  return _mm256_cvtps_ph(a, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC);
#else
  __m128i lo = float2half_old(_mm256_extractf128_ps(a, 0));
  __m128i hi = float2half_old(_mm256_extractf128_ps(a, 1));
  return _mm_packus_epi32(lo, hi);
#endif
}

template <>
EIGEN_STRONG_INLINE Packet8h pmin_old<Packet8h>(const Packet8h& a, const Packet8h& b) {
  return float2half_old(pmin_old<Packet8f>(half2float_old(a), half2float_old(b)));
}

template <>
EIGEN_STRONG_INLINE Packet8h pmax_old<Packet8h>(const Packet8h& a, const Packet8h& b) {
  return float2half_old(pmax_old<Packet8f>(half2float_old(a), half2float_old(b)));
}

template <>
EIGEN_STRONG_INLINE Packet8h plset_old<Packet8h>(const half& a) {
  return float2half_old(plset_old<Packet8f>(static_cast<float>(a)));
}

template <>
EIGEN_STRONG_INLINE Packet8h por_old(const Packet8h& a, const Packet8h& b) {
  // in some cases Packet4i is a wrapper around __m128i, so we either need to
  // cast to Packet4i to directly call the intrinsics as below:
  return _mm_or_si128(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet8h pxor_old(const Packet8h& a, const Packet8h& b) {
  return _mm_xor_si128(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet8h pand_old(const Packet8h& a, const Packet8h& b) {
  return _mm_and_si128(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet8h pandnot_old(const Packet8h& a, const Packet8h& b) {
  return _mm_andnot_si128(b, a);
}

template <>
EIGEN_STRONG_INLINE Packet8h pselect_old(const Packet8h& mask, const Packet8h& a, const Packet8h& b) {
  return _mm_blendv_epi8(b, a, mask);
}

template <>
EIGEN_STRONG_INLINE Packet8h pround_old<Packet8h>(const Packet8h& a) {
  return float2half_old(pround_old<Packet8f>(half2float_old(a)));
}

template <>
EIGEN_STRONG_INLINE Packet8h print_old<Packet8h>(const Packet8h& a) {
  return float2half_old(print_old<Packet8f>(half2float_old(a)));
}

template <>
EIGEN_STRONG_INLINE Packet8h pceil_old<Packet8h>(const Packet8h& a) {
  return float2half_old(pceil_old<Packet8f>(half2float_old(a)));
}

template <>
EIGEN_STRONG_INLINE Packet8h pfloor_old<Packet8h>(const Packet8h& a) {
  return float2half_old(pfloor_old<Packet8f>(half2float_old(a)));
}

template <>
EIGEN_STRONG_INLINE Packet8h pcmp_eq_old(const Packet8h& a, const Packet8h& b) {
  return Pack16To8_old(pcmp_eq_old(half2float_old(a), half2float_old(b)));
}

template <>
EIGEN_STRONG_INLINE Packet8h pcmp_le_old(const Packet8h& a, const Packet8h& b) {
  return Pack16To8_old(pcmp_le_old(half2float_old(a), half2float_old(b)));
}

template <>
EIGEN_STRONG_INLINE Packet8h pcmp_lt_old(const Packet8h& a, const Packet8h& b) {
  return Pack16To8_old(pcmp_lt_old(half2float_old(a), half2float_old(b)));
}

template <>
EIGEN_STRONG_INLINE Packet8h pcmp_lt_or_nan_old(const Packet8h& a, const Packet8h& b) {
  return Pack16To8_old(pcmp_lt_or_nan_old(half2float_old(a), half2float_old(b)));
}

template <>
EIGEN_STRONG_INLINE Packet8h pconj_old(const Packet8h& a) {
  return a;
}

template <>
EIGEN_STRONG_INLINE Packet8h pnegate_old(const Packet8h& a) {
  Packet8h sign_mask = _mm_set1_epi16(static_cast<numext::uint16_t>(0x8000));
  return _mm_xor_si128(a, sign_mask);
}

template <>
EIGEN_STRONG_INLINE Packet8h padd_old<Packet8h>(const Packet8h& a, const Packet8h& b) {
  Packet8f af = half2float_old(a);
  Packet8f bf = half2float_old(b);
  Packet8f rf = padd_old(af, bf);
  return float2half_old(rf);
}

template <>
EIGEN_STRONG_INLINE Packet8h psub_old<Packet8h>(const Packet8h& a, const Packet8h& b) {
  Packet8f af = half2float_old(a);
  Packet8f bf = half2float_old(b);
  Packet8f rf = psub_old(af, bf);
  return float2half_old(rf);
}

template <>
EIGEN_STRONG_INLINE Packet8h pmul_old<Packet8h>(const Packet8h& a, const Packet8h& b) {
  Packet8f af = half2float_old(a);
  Packet8f bf = half2float_old(b);
  Packet8f rf = pmul_old(af, bf);
  return float2half_old(rf);
}

template <>
EIGEN_STRONG_INLINE Packet8h pdiv_old<Packet8h>(const Packet8h& a, const Packet8h& b) {
  Packet8f af = half2float_old(a);
  Packet8f bf = half2float_old(b);
  Packet8f rf = pdiv_old(af, bf);
  return float2half_old(rf);
}

template <>
EIGEN_STRONG_INLINE Packet8h pgather_old<Eigen::half, Packet8h>(const Eigen::half* from, Index stride) {
  const numext::uint16_t s0 = numext::bit_cast<numext::uint16_t>(from[0 * stride]);
  const numext::uint16_t s1 = numext::bit_cast<numext::uint16_t>(from[1 * stride]);
  const numext::uint16_t s2 = numext::bit_cast<numext::uint16_t>(from[2 * stride]);
  const numext::uint16_t s3 = numext::bit_cast<numext::uint16_t>(from[3 * stride]);
  const numext::uint16_t s4 = numext::bit_cast<numext::uint16_t>(from[4 * stride]);
  const numext::uint16_t s5 = numext::bit_cast<numext::uint16_t>(from[5 * stride]);
  const numext::uint16_t s6 = numext::bit_cast<numext::uint16_t>(from[6 * stride]);
  const numext::uint16_t s7 = numext::bit_cast<numext::uint16_t>(from[7 * stride]);
  return _mm_set_epi16(s7, s6, s5, s4, s3, s2, s1, s0);
}

template <>
EIGEN_STRONG_INLINE void pscatter_old<Eigen::half, Packet8h>(Eigen::half* to, const Packet8h& from, Index stride) {
  EIGEN_ALIGN32 Eigen::half aux[8];
  pstore_old(aux, from);
  to[stride * 0] = aux[0];
  to[stride * 1] = aux[1];
  to[stride * 2] = aux[2];
  to[stride * 3] = aux[3];
  to[stride * 4] = aux[4];
  to[stride * 5] = aux[5];
  to[stride * 6] = aux[6];
  to[stride * 7] = aux[7];
}

template <>
EIGEN_STRONG_INLINE Eigen::half predux_old<Packet8h>(const Packet8h& a) {
  Packet8f af = half2float_old(a);
  float reduced = predux_old<Packet8f>(af);
  return Eigen::half(reduced);
}

template <>
EIGEN_STRONG_INLINE Eigen::half predux_max_old<Packet8h>(const Packet8h& a) {
  Packet8f af = half2float_old(a);
  float reduced = predux_max_old<Packet8f>(af);
  return Eigen::half(reduced);
}

template <>
EIGEN_STRONG_INLINE Eigen::half predux_min_old<Packet8h>(const Packet8h& a) {
  Packet8f af = half2float_old(a);
  float reduced = predux_min_old<Packet8f>(af);
  return Eigen::half(reduced);
}

template <>
EIGEN_STRONG_INLINE Eigen::half predux_mul_old<Packet8h>(const Packet8h& a) {
  Packet8f af = half2float_old(a);
  float reduced = predux_mul_old<Packet8f>(af);
  return Eigen::half(reduced);
}

template <>
EIGEN_STRONG_INLINE Packet8h preverse_old(const Packet8h& a) {
  __m128i m = _mm_setr_epi8(14, 15, 12, 13, 10, 11, 8, 9, 6, 7, 4, 5, 2, 3, 0, 1);
  return _mm_shuffle_epi8(a, m);
}

EIGEN_STRONG_INLINE void ptranspose_old(PacketBlock<Packet8h, 8>& kernel) {
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

EIGEN_STRONG_INLINE void ptranspose_old(PacketBlock<Packet8h, 4>& kernel) {
  EIGEN_ALIGN32 Eigen::half in[4][8];
  pstore_old<Eigen::half>(in[0], kernel.packet[0]);
  pstore_old<Eigen::half>(in[1], kernel.packet[1]);
  pstore_old<Eigen::half>(in[2], kernel.packet[2]);
  pstore_old<Eigen::half>(in[3], kernel.packet[3]);

  EIGEN_ALIGN32 Eigen::half out[4][8];

  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      out[i][j] = in[j][2 * i];
    }
    for (int j = 0; j < 4; ++j) {
      out[i][j + 4] = in[j][2 * i + 1];
    }
  }

  kernel.packet[0] = pload_old<Packet8h>(out[0]);
  kernel.packet[1] = pload_old<Packet8h>(out[1]);
  kernel.packet[2] = pload_old<Packet8h>(out[2]);
  kernel.packet[3] = pload_old<Packet8h>(out[3]);
}

// BFloat16 implementation.

EIGEN_STRONG_INLINE Packet8f Bf16ToF32_old(const Packet8bf& a) {
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
EIGEN_STRONG_INLINE Packet8bf F32ToBf16_old(const Packet8f& a) {
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
  return _mm_packus_epi32(_mm256_extractf128_si256(t, 0), _mm256_extractf128_si256(t, 1));
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

template <>
EIGEN_STRONG_INLINE Packet8bf pset1_old<Packet8bf>(const bfloat16& from) {
  return _mm_set1_epi16(numext::bit_cast<numext::uint16_t>(from));
}

template <>
EIGEN_STRONG_INLINE bfloat16 pfirst_old<Packet8bf>(const Packet8bf& from) {
  return numext::bit_cast<bfloat16>(static_cast<numext::uint16_t>(_mm_extract_epi16(from, 0)));
}

template <>
EIGEN_STRONG_INLINE Packet8bf pload_old<Packet8bf>(const bfloat16* from) {
  return _mm_load_si128(reinterpret_cast<const __m128i*>(from));
}

template <>
EIGEN_STRONG_INLINE Packet8bf ploadu_old<Packet8bf>(const bfloat16* from) {
  return _mm_loadu_si128(reinterpret_cast<const __m128i*>(from));
}

template <>
EIGEN_STRONG_INLINE void pstore_old<bfloat16>(bfloat16* to, const Packet8bf& from) {
  _mm_store_si128(reinterpret_cast<__m128i*>(to), from);
}

template <>
EIGEN_STRONG_INLINE void pstoreu_old<bfloat16>(bfloat16* to, const Packet8bf& from) {
  _mm_storeu_si128(reinterpret_cast<__m128i*>(to), from);
}

template <>
EIGEN_STRONG_INLINE Packet8bf ploaddup_old<Packet8bf>(const bfloat16* from) {
  const numext::uint16_t a = numext::bit_cast<numext::uint16_t>(from[0]);
  const numext::uint16_t b = numext::bit_cast<numext::uint16_t>(from[1]);
  const numext::uint16_t c = numext::bit_cast<numext::uint16_t>(from[2]);
  const numext::uint16_t d = numext::bit_cast<numext::uint16_t>(from[3]);
  return _mm_set_epi16(d, d, c, c, b, b, a, a);
}

template <>
EIGEN_STRONG_INLINE Packet8bf ploadquad_old<Packet8bf>(const bfloat16* from) {
  const numext::uint16_t a = numext::bit_cast<numext::uint16_t>(from[0]);
  const numext::uint16_t b = numext::bit_cast<numext::uint16_t>(from[1]);
  return _mm_set_epi16(b, b, b, b, a, a, a, a);
}

template <>
EIGEN_STRONG_INLINE Packet8bf ptrue_old(const Packet8bf& a) {
  return _mm_cmpeq_epi32(a, a);
}

template <>
EIGEN_STRONG_INLINE Packet8bf pabs_old(const Packet8bf& a) {
  const __m128i sign_mask = _mm_set1_epi16(static_cast<numext::uint16_t>(0x8000));
  return _mm_andnot_si128(sign_mask, a);
}

template <>
EIGEN_STRONG_INLINE Packet8bf pmin_old<Packet8bf>(const Packet8bf& a, const Packet8bf& b) {
  return F32ToBf16_old(pmin_old<Packet8f>(Bf16ToF32_old(a), Bf16ToF32_old(b)));
}

template <>
EIGEN_STRONG_INLINE Packet8bf pmax_old<Packet8bf>(const Packet8bf& a, const Packet8bf& b) {
  return F32ToBf16_old(pmax_old<Packet8f>(Bf16ToF32_old(a), Bf16ToF32_old(b)));
}

template <>
EIGEN_STRONG_INLINE Packet8bf plset_old<Packet8bf>(const bfloat16& a) {
  return F32ToBf16_old(plset_old<Packet8f>(static_cast<float>(a)));
}

template <>
EIGEN_STRONG_INLINE Packet8bf por_old(const Packet8bf& a, const Packet8bf& b) {
  return _mm_or_si128(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet8bf pxor_old(const Packet8bf& a, const Packet8bf& b) {
  return _mm_xor_si128(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet8bf pand_old(const Packet8bf& a, const Packet8bf& b) {
  return _mm_and_si128(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet8bf pandnot_old(const Packet8bf& a, const Packet8bf& b) {
  return _mm_andnot_si128(b, a);
}

template <>
EIGEN_STRONG_INLINE Packet8bf pselect_old(const Packet8bf& mask, const Packet8bf& a, const Packet8bf& b) {
  return _mm_blendv_epi8(b, a, mask);
}

template <>
EIGEN_STRONG_INLINE Packet8bf pround_old<Packet8bf>(const Packet8bf& a) {
  return F32ToBf16_old(pround_old<Packet8f>(Bf16ToF32_old(a)));
}

template <>
EIGEN_STRONG_INLINE Packet8bf print_old<Packet8bf>(const Packet8bf& a) {
  return F32ToBf16_old(print_old<Packet8f>(Bf16ToF32_old(a)));
}

template <>
EIGEN_STRONG_INLINE Packet8bf pceil_old<Packet8bf>(const Packet8bf& a) {
  return F32ToBf16_old(pceil_old<Packet8f>(Bf16ToF32_old(a)));
}

template <>
EIGEN_STRONG_INLINE Packet8bf pfloor_old<Packet8bf>(const Packet8bf& a) {
  return F32ToBf16_old(pfloor_old<Packet8f>(Bf16ToF32_old(a)));
}

template <>
EIGEN_STRONG_INLINE Packet8bf pcmp_eq_old(const Packet8bf& a, const Packet8bf& b) {
  return Pack16To8_old(pcmp_eq_old(Bf16ToF32_old(a), Bf16ToF32_old(b)));
}

template <>
EIGEN_STRONG_INLINE Packet8bf pcmp_le_old(const Packet8bf& a, const Packet8bf& b) {
  return Pack16To8_old(pcmp_le_old(Bf16ToF32_old(a), Bf16ToF32_old(b)));
}

template <>
EIGEN_STRONG_INLINE Packet8bf pcmp_lt_old(const Packet8bf& a, const Packet8bf& b) {
  return Pack16To8_old(pcmp_lt_old(Bf16ToF32_old(a), Bf16ToF32_old(b)));
}

template <>
EIGEN_STRONG_INLINE Packet8bf pcmp_lt_or_nan_old(const Packet8bf& a, const Packet8bf& b) {
  return Pack16To8_old(pcmp_lt_or_nan_old(Bf16ToF32_old(a), Bf16ToF32_old(b)));
}

template <>
EIGEN_STRONG_INLINE Packet8bf pconj_old(const Packet8bf& a) {
  return a;
}

template <>
EIGEN_STRONG_INLINE Packet8bf pnegate_old(const Packet8bf& a) {
  Packet8bf sign_mask = _mm_set1_epi16(static_cast<numext::uint16_t>(0x8000));
  return _mm_xor_si128(a, sign_mask);
}

template <>
EIGEN_STRONG_INLINE Packet8bf padd_old<Packet8bf>(const Packet8bf& a, const Packet8bf& b) {
  return F32ToBf16_old(padd_old<Packet8f>(Bf16ToF32_old(a), Bf16ToF32_old(b)));
}

template <>
EIGEN_STRONG_INLINE Packet8bf psub_old<Packet8bf>(const Packet8bf& a, const Packet8bf& b) {
  return F32ToBf16_old(psub_old<Packet8f>(Bf16ToF32_old(a), Bf16ToF32_old(b)));
}

template <>
EIGEN_STRONG_INLINE Packet8bf pmul_old<Packet8bf>(const Packet8bf& a, const Packet8bf& b) {
  return F32ToBf16_old(pmul_old<Packet8f>(Bf16ToF32_old(a), Bf16ToF32_old(b)));
}

template <>
EIGEN_STRONG_INLINE Packet8bf pdiv_old<Packet8bf>(const Packet8bf& a, const Packet8bf& b) {
  return F32ToBf16_old(pdiv_old<Packet8f>(Bf16ToF32_old(a), Bf16ToF32_old(b)));
}

template <>
EIGEN_STRONG_INLINE Packet8bf pgather_old<bfloat16, Packet8bf>(const bfloat16* from, Index stride) {
  const numext::uint16_t s0 = numext::bit_cast<numext::uint16_t>(from[0 * stride]);
  const numext::uint16_t s1 = numext::bit_cast<numext::uint16_t>(from[1 * stride]);
  const numext::uint16_t s2 = numext::bit_cast<numext::uint16_t>(from[2 * stride]);
  const numext::uint16_t s3 = numext::bit_cast<numext::uint16_t>(from[3 * stride]);
  const numext::uint16_t s4 = numext::bit_cast<numext::uint16_t>(from[4 * stride]);
  const numext::uint16_t s5 = numext::bit_cast<numext::uint16_t>(from[5 * stride]);
  const numext::uint16_t s6 = numext::bit_cast<numext::uint16_t>(from[6 * stride]);
  const numext::uint16_t s7 = numext::bit_cast<numext::uint16_t>(from[7 * stride]);
  return _mm_set_epi16(s7, s6, s5, s4, s3, s2, s1, s0);
}

template <>
EIGEN_STRONG_INLINE void pscatter_old<bfloat16, Packet8bf>(bfloat16* to, const Packet8bf& from, Index stride) {
  EIGEN_ALIGN32 bfloat16 aux[8];
  pstore_old(aux, from);
  to[stride * 0] = aux[0];
  to[stride * 1] = aux[1];
  to[stride * 2] = aux[2];
  to[stride * 3] = aux[3];
  to[stride * 4] = aux[4];
  to[stride * 5] = aux[5];
  to[stride * 6] = aux[6];
  to[stride * 7] = aux[7];
}

template <>
EIGEN_STRONG_INLINE bfloat16 predux_old<Packet8bf>(const Packet8bf& a) {
  return static_cast<bfloat16>(predux_old<Packet8f>(Bf16ToF32_old(a)));
}

template <>
EIGEN_STRONG_INLINE bfloat16 predux_max_old<Packet8bf>(const Packet8bf& a) {
  return static_cast<bfloat16>(predux_max_old<Packet8f>(Bf16ToF32_old(a)));
}

template <>
EIGEN_STRONG_INLINE bfloat16 predux_min_old<Packet8bf>(const Packet8bf& a) {
  return static_cast<bfloat16>(predux_min_old<Packet8f>(Bf16ToF32_old(a)));
}

template <>
EIGEN_STRONG_INLINE bfloat16 predux_mul_old<Packet8bf>(const Packet8bf& a) {
  return static_cast<bfloat16>(predux_mul_old<Packet8f>(Bf16ToF32_old(a)));
}

template <>
EIGEN_STRONG_INLINE Packet8bf preverse_old(const Packet8bf& a) {
  __m128i m = _mm_setr_epi8(14, 15, 12, 13, 10, 11, 8, 9, 6, 7, 4, 5, 2, 3, 0, 1);
  return _mm_shuffle_epi8(a, m);
}

EIGEN_STRONG_INLINE void ptranspose_old(PacketBlock<Packet8bf, 8>& kernel) {
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

EIGEN_STRONG_INLINE void ptranspose_old(PacketBlock<Packet8bf, 4>& kernel) {
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

#endif

#ifdef EIGEN_VECTORIZE_AVX2
template <>
EIGEN_STRONG_INLINE Packet4l pset1_old<Packet4l>(const int64_t& from) {
  return _mm256_set1_epi64x(from);
}
template <>
EIGEN_STRONG_INLINE Packet4l pzero_old(const Packet4l& /*a*/) {
  return _mm256_setzero_si256();
}
template <>
EIGEN_STRONG_INLINE Packet4l peven_mask_old(const Packet4l& /*a*/) {
  return _mm256_set_epi64x(0ll, -1ll, 0ll, -1ll);
}
template <>
EIGEN_STRONG_INLINE Packet4l pload1_old<Packet4l>(const int64_t* from) {
  return _mm256_set1_epi64x(*from);
}
template <>
EIGEN_STRONG_INLINE Packet4l padd_old<Packet4l>(const Packet4l& a, const Packet4l& b) {
  return _mm256_add_epi64(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet4l plset_old<Packet4l>(const int64_t& a) {
  return padd_old(pset1_old<Packet4l>(a), Packet4l(_mm256_set_epi64x(3ll, 2ll, 1ll, 0ll)));
}
template <>
EIGEN_STRONG_INLINE Packet4l psub_old<Packet4l>(const Packet4l& a, const Packet4l& b) {
  return _mm256_sub_epi64(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet4l pnegate_old(const Packet4l& a) {
  return psub_old(pzero_old(a), a);
}
template <>
EIGEN_STRONG_INLINE Packet4l pconj_old(const Packet4l& a) {
  return a;
}
template <>
EIGEN_STRONG_INLINE Packet4l pcmp_le_old(const Packet4l& a, const Packet4l& b) {
  return _mm256_xor_si256(_mm256_cmpgt_epi64(a, b), _mm256_set1_epi32(-1));
}
template <>
EIGEN_STRONG_INLINE Packet4l pcmp_lt_old(const Packet4l& a, const Packet4l& b) {
  return _mm256_cmpgt_epi64(b, a);
}
template <>
EIGEN_STRONG_INLINE Packet4l pcmp_eq_old(const Packet4l& a, const Packet4l& b) {
  return _mm256_cmpeq_epi64(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet4l ptrue_old<Packet4l>(const Packet4l& a) {
  return _mm256_cmpeq_epi64(a, a);
}
template <>
EIGEN_STRONG_INLINE Packet4l pand_old<Packet4l>(const Packet4l& a, const Packet4l& b) {
  return _mm256_and_si256(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet4l por_old<Packet4l>(const Packet4l& a, const Packet4l& b) {
  return _mm256_or_si256(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet4l pxor_old<Packet4l>(const Packet4l& a, const Packet4l& b) {
  return _mm256_xor_si256(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet4l pandnot_old<Packet4l>(const Packet4l& a, const Packet4l& b) {
  return _mm256_andnot_si256(b, a);
}
template <int N>
EIGEN_STRONG_INLINE Packet4l plogical_shift_right_old(Packet4l a) {
  return _mm256_srli_epi64(a, N);
}
template <int N>
EIGEN_STRONG_INLINE Packet4l plogical_shift_left_old(Packet4l a) {
  return _mm256_slli_epi64(a, N);
}
template <>
EIGEN_STRONG_INLINE Packet4l pload_old<Packet4l>(const int64_t* from) {
  EIGEN_DEBUG_ALIGNED_LOAD return _mm256_load_si256(reinterpret_cast<const __m256i*>(from));
}
template <>
EIGEN_STRONG_INLINE Packet4l ploadu_old<Packet4l>(const int64_t* from) {
  EIGEN_DEBUG_UNALIGNED_LOAD return _mm256_loadu_si256(reinterpret_cast<const __m256i*>(from));
}
// Loads 2 int64_ts from memory a returns the packet {a0, a0, a1, a1}
template <>
EIGEN_STRONG_INLINE Packet4l ploaddup_old<Packet4l>(const int64_t* from) {
  const Packet4l a = _mm256_castsi128_si256(_mm_loadu_si128(reinterpret_cast<const __m128i*>(from)));
  return _mm256_permutevar8x32_epi32(a, _mm256_setr_epi32(0, 1, 0, 1, 2, 3, 2, 3));
}
template <>
EIGEN_STRONG_INLINE void pstore_old<int64_t>(int64_t* to, const Packet4l& from) {
  EIGEN_DEBUG_ALIGNED_STORE _mm256_storeu_si256(reinterpret_cast<__m256i*>(to), from);
}
template <>
EIGEN_STRONG_INLINE void pstoreu_old<int64_t>(int64_t* to, const Packet4l& from) {
  EIGEN_DEBUG_UNALIGNED_STORE _mm256_storeu_si256(reinterpret_cast<__m256i*>(to), from);
}
template <>
EIGEN_DEVICE_FUNC inline Packet4l pgather_old<int64_t, Packet4l>(const int64_t* from, Index stride) {
  return _mm256_set_epi64x(from[3 * stride], from[2 * stride], from[1 * stride], from[0 * stride]);
}
template <>
EIGEN_DEVICE_FUNC inline void pscatter_old<int64_t, Packet4l>(int64_t* to, const Packet4l& from, Index stride) {
  __m128i low = _mm256_extractf128_si256(from, 0);
  to[stride * 0] = _mm_extract_epi64(low, 0);
  to[stride * 1] = _mm_extract_epi64(low, 1);

  __m128i high = _mm256_extractf128_si256(from, 1);
  to[stride * 2] = _mm_extract_epi64(high, 0);
  to[stride * 3] = _mm_extract_epi64(high, 1);
}
template <>
EIGEN_STRONG_INLINE void pstore1_old<Packet4l>(int64_t* to, const int64_t& a) {
  Packet4l pa = pset1_old<Packet4l>(a);
  pstore_old(to, pa);
}
template <>
EIGEN_STRONG_INLINE int64_t pfirst_old<Packet4l>(const Packet4l& a) {
  return _mm_cvtsi128_si64(_mm256_castsi256_si128(a));
}
template <>
EIGEN_STRONG_INLINE Packet4l preverse_old(const Packet4l& a) {
  return _mm256_castpd_si256(preverse_old(_mm256_castsi256_pd(a)));
}
template <>
EIGEN_STRONG_INLINE int64_t predux_old<Packet4l>(const Packet4l& a) {
  __m128i r = _mm_add_epi64(_mm256_castsi256_si128(a), _mm256_extractf128_si256(a, 1));
  return _mm_extract_epi64(r, 0) + _mm_extract_epi64(r, 1);
}
#define MM256_SHUFFLE_EPI64(A, B, M) _mm256_shuffle_pd(_mm256_castsi256_pd(A), _mm256_castsi256_pd(B), M)
EIGEN_DEVICE_FUNC inline void ptranspose_old(PacketBlock<Packet4l, 4>& kernel) {
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
EIGEN_STRONG_INLINE Packet4l pmin_old<Packet4l>(const Packet4l& a, const Packet4l& b) {
  __m256i cmp = _mm256_cmpgt_epi64(a, b);
  __m256i a_min = _mm256_andnot_si256(cmp, a);
  __m256i b_min = _mm256_and_si256(cmp, b);
  return Packet4l(_mm256_or_si256(a_min, b_min));
}
template <>
EIGEN_STRONG_INLINE Packet4l pmax_old<Packet4l>(const Packet4l& a, const Packet4l& b) {
  __m256i cmp = _mm256_cmpgt_epi64(a, b);
  __m256i a_min = _mm256_and_si256(cmp, a);
  __m256i b_min = _mm256_andnot_si256(cmp, b);
  return Packet4l(_mm256_or_si256(a_min, b_min));
}
template <>
EIGEN_STRONG_INLINE Packet4l pabs_old<Packet4l>(const Packet4l& a) {
  Packet4l pz = pzero_old<Packet4l>(a);
  Packet4l cmp = _mm256_cmpgt_epi64(a, pz);
  return psub_old(cmp, pxor_old(a, cmp));
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
#endif

#ifdef EIGEN_VECTORIZE_AVX512

template <>
EIGEN_STRONG_INLINE Packet16f pset1_old<Packet16f>(const float& from) {
  return _mm512_set1_ps(from);
}
template <>
EIGEN_STRONG_INLINE Packet8d pset1_old<Packet8d>(const double& from) {
  return _mm512_set1_pd(from);
}
template <>
EIGEN_STRONG_INLINE Packet16i pset1_old<Packet16i>(const int& from) {
  return _mm512_set1_epi32(from);
}

template <>
EIGEN_STRONG_INLINE Packet16f pset1frombits_old<Packet16f>(unsigned int from) {
  return _mm512_castsi512_ps(_mm512_set1_epi32(from));
}

template <>
EIGEN_STRONG_INLINE Packet8d pset1frombits_old<Packet8d>(const numext::uint64_t from) {
  return _mm512_castsi512_pd(_mm512_set1_epi64(from));
}

template <>
EIGEN_STRONG_INLINE Packet16f pzero_old(const Packet16f& /*a*/) {
  return _mm512_setzero_ps();
}
template <>
EIGEN_STRONG_INLINE Packet8d pzero_old(const Packet8d& /*a*/) {
  return _mm512_setzero_pd();
}
template <>
EIGEN_STRONG_INLINE Packet16i pzero_old(const Packet16i& /*a*/) {
  return _mm512_setzero_si512();
}

template <>
EIGEN_STRONG_INLINE Packet16f peven_mask_old(const Packet16f& /*a*/) {
  return _mm512_castsi512_ps(_mm512_set_epi32(0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1));
}
template <>
EIGEN_STRONG_INLINE Packet16i peven_mask_old(const Packet16i& /*a*/) {
  return _mm512_set_epi32(0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1);
}
template <>
EIGEN_STRONG_INLINE Packet8d peven_mask_old(const Packet8d& /*a*/) {
  return _mm512_castsi512_pd(_mm512_set_epi32(0, 0, -1, -1, 0, 0, -1, -1, 0, 0, -1, -1, 0, 0, -1, -1));
}

template <>
EIGEN_STRONG_INLINE Packet16f pload1_old<Packet16f>(const float* from) {
#if (EIGEN_COMP_GNUC != 0) || (EIGEN_COMP_CLANG != 0)
  // Inline asm here helps reduce some register spilling in TRSM kernels.
  // See note in unrolls::gemm::microKernel in TrsmKernel.h
  Packet16f ret;
  __asm__("vbroadcastss %[mem], %[dst]" : [dst] "=v"(ret) : [mem] "m"(*from));
  return ret;
#else
  return _mm512_broadcastss_ps(_mm_load_ps1(from));
#endif
}
template <>
EIGEN_STRONG_INLINE Packet8d pload1_old<Packet8d>(const double* from) {
#if (EIGEN_COMP_GNUC != 0) || (EIGEN_COMP_CLANG != 0)
  Packet8d ret;
  __asm__("vbroadcastsd %[mem], %[dst]" : [dst] "=v"(ret) : [mem] "m"(*from));
  return ret;
#else
  return _mm512_set1_pd(*from);
#endif
}

template <>
EIGEN_STRONG_INLINE Packet16f plset_old<Packet16f>(const float& a) {
  return _mm512_add_ps(_mm512_set1_ps(a), _mm512_set_ps(15.0f, 14.0f, 13.0f, 12.0f, 11.0f, 10.0f, 9.0f, 8.0f, 7.0f,
                                                        6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f, 0.0f));
}
template <>
EIGEN_STRONG_INLINE Packet8d plset_old<Packet8d>(const double& a) {
  return _mm512_add_pd(_mm512_set1_pd(a), _mm512_set_pd(7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0, 0.0));
}
template <>
EIGEN_STRONG_INLINE Packet16i plset_old<Packet16i>(const int& a) {
  return _mm512_add_epi32(_mm512_set1_epi32(a), _mm512_set_epi32(15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0));
}

template <>
EIGEN_STRONG_INLINE Packet16f padd_old<Packet16f>(const Packet16f& a, const Packet16f& b) {
  return _mm512_add_ps(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet8d padd_old<Packet8d>(const Packet8d& a, const Packet8d& b) {
  return _mm512_add_pd(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet16i padd_old<Packet16i>(const Packet16i& a, const Packet16i& b) {
  return _mm512_add_epi32(a, b);
}

template <>
EIGEN_STRONG_INLINE Packet16f padd_old<Packet16f>(const Packet16f& a, const Packet16f& b, uint16_t umask) {
  __mmask16 mask = static_cast<__mmask16>(umask);
  return _mm512_maskz_add_ps(mask, a, b);
}
template <>
EIGEN_STRONG_INLINE Packet8d padd_old<Packet8d>(const Packet8d& a, const Packet8d& b, uint8_t umask) {
  __mmask8 mask = static_cast<__mmask8>(umask);
  return _mm512_maskz_add_pd(mask, a, b);
}

template <>
EIGEN_STRONG_INLINE Packet16f psub_old<Packet16f>(const Packet16f& a, const Packet16f& b) {
  return _mm512_sub_ps(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet8d psub_old<Packet8d>(const Packet8d& a, const Packet8d& b) {
  return _mm512_sub_pd(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet16i psub_old<Packet16i>(const Packet16i& a, const Packet16i& b) {
  return _mm512_sub_epi32(a, b);
}

template <>
EIGEN_STRONG_INLINE Packet16f pnegate_old(const Packet16f& a) {
  return _mm512_sub_ps(_mm512_set1_ps(0.0), a);
}
template <>
EIGEN_STRONG_INLINE Packet8d pnegate_old(const Packet8d& a) {
  return _mm512_sub_pd(_mm512_set1_pd(0.0), a);
}
template <>
EIGEN_STRONG_INLINE Packet16i pnegate_old(const Packet16i& a) {
  return _mm512_sub_epi32(_mm512_set1_epi32(0), a);
}

template <>
EIGEN_STRONG_INLINE Packet16f pconj_old(const Packet16f& a) {
  return a;
}
template <>
EIGEN_STRONG_INLINE Packet8d pconj_old(const Packet8d& a) {
  return a;
}
template <>
EIGEN_STRONG_INLINE Packet16i pconj_old(const Packet16i& a) {
  return a;
}

template <>
EIGEN_STRONG_INLINE Packet16f pmul_old<Packet16f>(const Packet16f& a, const Packet16f& b) {
  return _mm512_mul_ps(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet8d pmul_old<Packet8d>(const Packet8d& a, const Packet8d& b) {
  return _mm512_mul_pd(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet16i pmul_old<Packet16i>(const Packet16i& a, const Packet16i& b) {
  return _mm512_mullo_epi32(a, b);
}

template <>
EIGEN_STRONG_INLINE Packet16f pdiv_old<Packet16f>(const Packet16f& a, const Packet16f& b) {
  return _mm512_div_ps(a, b);
}
template <>
EIGEN_STRONG_INLINE Packet8d pdiv_old<Packet8d>(const Packet8d& a, const Packet8d& b) {
  return _mm512_div_pd(a, b);
}

#ifdef EIGEN_VECTORIZE_FMA
template <>
EIGEN_STRONG_INLINE Packet16f pmadd_old(const Packet16f& a, const Packet16f& b, const Packet16f& c) {
  return _mm512_fmadd_ps(a, b, c);
}
template <>
EIGEN_STRONG_INLINE Packet8d pmadd_old(const Packet8d& a, const Packet8d& b, const Packet8d& c) {
  return _mm512_fmadd_pd(a, b, c);
}

template <>
EIGEN_STRONG_INLINE Packet16f pmsub_old(const Packet16f& a, const Packet16f& b, const Packet16f& c) {
  return _mm512_fmsub_ps(a, b, c);
}
template <>
EIGEN_STRONG_INLINE Packet8d pmsub_old(const Packet8d& a, const Packet8d& b, const Packet8d& c) {
  return _mm512_fmsub_pd(a, b, c);
}

template <>
EIGEN_STRONG_INLINE Packet16f pnmadd_old(const Packet16f& a, const Packet16f& b, const Packet16f& c) {
  return _mm512_fnmadd_ps(a, b, c);
}
template <>
EIGEN_STRONG_INLINE Packet8d pnmadd_old(const Packet8d& a, const Packet8d& b, const Packet8d& c) {
  return _mm512_fnmadd_pd(a, b, c);
}

template <>
EIGEN_STRONG_INLINE Packet16f pnmsub_old(const Packet16f& a, const Packet16f& b, const Packet16f& c) {
  return _mm512_fnmsub_ps(a, b, c);
}
template <>
EIGEN_STRONG_INLINE Packet8d pnmsub_old(const Packet8d& a, const Packet8d& b, const Packet8d& c) {
  return _mm512_fnmsub_pd(a, b, c);
}
#endif

template <>
EIGEN_DEVICE_FUNC inline Packet16f pselect_old(const Packet16f& mask, const Packet16f& a, const Packet16f& b) {
  __mmask16 mask16 = _mm512_cmp_epi32_mask(_mm512_castps_si512(mask), _mm512_setzero_epi32(), _MM_CMPINT_EQ);
  return _mm512_mask_blend_ps(mask16, a, b);
}

template <>
EIGEN_DEVICE_FUNC inline Packet8d pselect_old(const Packet8d& mask, const Packet8d& a, const Packet8d& b) {
  __mmask8 mask8 = _mm512_cmp_epi64_mask(_mm512_castpd_si512(mask), _mm512_setzero_epi32(), _MM_CMPINT_EQ);
  return _mm512_mask_blend_pd(mask8, a, b);
}

template <>
EIGEN_STRONG_INLINE Packet16f pmin_old<Packet16f>(const Packet16f& a, const Packet16f& b) {
  // Arguments are reversed to match NaN propagation behavior of std::min.
  return _mm512_min_ps(b, a);
}
template <>
EIGEN_STRONG_INLINE Packet8d pmin_old<Packet8d>(const Packet8d& a, const Packet8d& b) {
  // Arguments are reversed to match NaN propagation behavior of std::min.
  return _mm512_min_pd(b, a);
}
template <>
EIGEN_STRONG_INLINE Packet16i pmin_old<Packet16i>(const Packet16i& a, const Packet16i& b) {
  return _mm512_min_epi32(b, a);
}

template <>
EIGEN_STRONG_INLINE Packet16f pmax_old<Packet16f>(const Packet16f& a, const Packet16f& b) {
  // Arguments are reversed to match NaN propagation behavior of std::max.
  return _mm512_max_ps(b, a);
}
template <>
EIGEN_STRONG_INLINE Packet8d pmax_old<Packet8d>(const Packet8d& a, const Packet8d& b) {
  // Arguments are reversed to match NaN propagation behavior of std::max.
  return _mm512_max_pd(b, a);
}
template <>
EIGEN_STRONG_INLINE Packet16i pmax_old<Packet16i>(const Packet16i& a, const Packet16i& b) {
  return _mm512_max_epi32(b, a);
}

// Add specializations for min/max with prescribed NaN progation.
template <>
EIGEN_STRONG_INLINE Packet16f pmin_old<PropagateNumbers, Packet16f>(const Packet16f& a, const Packet16f& b) {
  return pminmax_propagate_numbers_old(a, b, pmin_old<Packet16f>);
}
template <>
EIGEN_STRONG_INLINE Packet8d pmin_old<PropagateNumbers, Packet8d>(const Packet8d& a, const Packet8d& b) {
  return pminmax_propagate_numbers_old(a, b, pmin_old<Packet8d>);
}
template <>
EIGEN_STRONG_INLINE Packet16f pmax_old<PropagateNumbers, Packet16f>(const Packet16f& a, const Packet16f& b) {
  return pminmax_propagate_numbers_old(a, b, pmax_old<Packet16f>);
}
template <>
EIGEN_STRONG_INLINE Packet8d pmax_old<PropagateNumbers, Packet8d>(const Packet8d& a, const Packet8d& b) {
  return pminmax_propagate_numbers_old(a, b, pmax_old<Packet8d>);
}
template <>
EIGEN_STRONG_INLINE Packet16f pmin_old<PropagateNaN, Packet16f>(const Packet16f& a, const Packet16f& b) {
  return pminmax_propagate_nan_old(a, b, pmin_old<Packet16f>);
}
template <>
EIGEN_STRONG_INLINE Packet8d pmin_old<PropagateNaN, Packet8d>(const Packet8d& a, const Packet8d& b) {
  return pminmax_propagate_nan_old(a, b, pmin_old<Packet8d>);
}
template <>
EIGEN_STRONG_INLINE Packet16f pmax_old<PropagateNaN, Packet16f>(const Packet16f& a, const Packet16f& b) {
  return pminmax_propagate_nan_old(a, b, pmax_old<Packet16f>);
}
template <>
EIGEN_STRONG_INLINE Packet8d pmax_old<PropagateNaN, Packet8d>(const Packet8d& a, const Packet8d& b) {
  return pminmax_propagate_nan_old(a, b, pmax_old<Packet8d>);
}

#ifdef EIGEN_VECTORIZE_AVX512DQ
template <int I_>
EIGEN_STRONG_INLINE Packet8f extract256_old(Packet16f x) {
  return _mm512_extractf32x8_ps(x, I_);
}
template <int I_>
EIGEN_STRONG_INLINE Packet2d extract128_old(Packet8d x) {
  return _mm512_extractf64x2_pd(x, I_);
}
EIGEN_STRONG_INLINE Packet16f cat256_old(Packet8f a, Packet8f b) {
  return _mm512_insertf32x8(_mm512_castps256_ps512(a), b, 1);
}
#else
// AVX512F does not define _mm512_extractf32x8_ps to extract _m256 from _m512
template <int I_>
EIGEN_STRONG_INLINE Packet8f extract256_old(Packet16f x) {
  return _mm256_castsi256_ps(_mm512_extracti64x4_epi64(_mm512_castps_si512(x), I_));
}

// AVX512F does not define _mm512_extractf64x2_pd to extract _m128 from _m512
template <int I_>
EIGEN_STRONG_INLINE Packet2d extract128_old(Packet8d x) {
  return _mm_castsi128_pd(_mm512_extracti32x4_epi32(_mm512_castpd_si512(x), I_));
}

EIGEN_STRONG_INLINE Packet16f cat256_old(Packet8f a, Packet8f b) {
  return _mm512_castsi512_ps(
      _mm512_inserti64x4(_mm512_castsi256_si512(_mm256_castps_si256(a)), _mm256_castps_si256(b), 1));
}
#endif

// Helper function for bit packing snippet of low precision comparison.
// It packs the flags from 32x16 to 16x16.
EIGEN_STRONG_INLINE __m256i Pack32To16(Packet16f rf) {
  // Split data into small pieces and handle with AVX instructions
  // to guarantee internal order of vector.
  // Operation:
  //   dst[15:0]    := Saturate16(rf[31:0])
  //   dst[31:16]   := Saturate16(rf[63:32])
  //   ...
  //   dst[255:240] := Saturate16(rf[255:224])
  __m256i lo = _mm256_castps_si256(extract256_old<0>(rf));
  __m256i hi = _mm256_castps_si256(extract256_old<1>(rf));
  __m128i result_lo = _mm_packs_epi32(_mm256_extractf128_si256(lo, 0), _mm256_extractf128_si256(lo, 1));
  __m128i result_hi = _mm_packs_epi32(_mm256_extractf128_si256(hi, 0), _mm256_extractf128_si256(hi, 1));
  return _mm256_insertf128_si256(_mm256_castsi128_si256(result_lo), result_hi, 1);
}

template <>
EIGEN_STRONG_INLINE Packet16f pcmp_eq_old(const Packet16f& a, const Packet16f& b) {
  __mmask16 mask = _mm512_cmp_ps_mask(a, b, _CMP_EQ_OQ);
  return _mm512_castsi512_ps(_mm512_mask_set1_epi32(_mm512_set1_epi32(0), mask, 0xffffffffu));
}
template <>
EIGEN_STRONG_INLINE Packet16f pcmp_le_old(const Packet16f& a, const Packet16f& b) {
  __mmask16 mask = _mm512_cmp_ps_mask(a, b, _CMP_LE_OQ);
  return _mm512_castsi512_ps(_mm512_mask_set1_epi32(_mm512_set1_epi32(0), mask, 0xffffffffu));
}

template <>
EIGEN_STRONG_INLINE Packet16f pcmp_lt_old(const Packet16f& a, const Packet16f& b) {
  __mmask16 mask = _mm512_cmp_ps_mask(a, b, _CMP_LT_OQ);
  return _mm512_castsi512_ps(_mm512_mask_set1_epi32(_mm512_set1_epi32(0), mask, 0xffffffffu));
}

template <>
EIGEN_STRONG_INLINE Packet16f pcmp_lt_or_nan_old(const Packet16f& a, const Packet16f& b) {
  __mmask16 mask = _mm512_cmp_ps_mask(a, b, _CMP_NGE_UQ);
  return _mm512_castsi512_ps(_mm512_mask_set1_epi32(_mm512_set1_epi32(0), mask, 0xffffffffu));
}

template <>
EIGEN_STRONG_INLINE Packet16i pcmp_eq_old(const Packet16i& a, const Packet16i& b) {
  __mmask16 mask = _mm512_cmp_epi32_mask(a, b, _MM_CMPINT_EQ);
  return _mm512_mask_set1_epi32(_mm512_set1_epi32(0), mask, 0xffffffffu);
}
template <>
EIGEN_STRONG_INLINE Packet16i pcmp_le_old(const Packet16i& a, const Packet16i& b) {
  __mmask16 mask = _mm512_cmp_epi32_mask(a, b, _MM_CMPINT_LE);
  return _mm512_mask_set1_epi32(_mm512_set1_epi32(0), mask, 0xffffffffu);
}
template <>
EIGEN_STRONG_INLINE Packet16i pcmp_lt_old(const Packet16i& a, const Packet16i& b) {
  __mmask16 mask = _mm512_cmp_epi32_mask(a, b, _MM_CMPINT_LT);
  return _mm512_mask_set1_epi32(_mm512_set1_epi32(0), mask, 0xffffffffu);
}

template <>
EIGEN_STRONG_INLINE Packet8d pcmp_eq_old(const Packet8d& a, const Packet8d& b) {
  __mmask8 mask = _mm512_cmp_pd_mask(a, b, _CMP_EQ_OQ);
  return _mm512_castsi512_pd(_mm512_mask_set1_epi64(_mm512_set1_epi64(0), mask, 0xffffffffffffffffu));
}
template <>
EIGEN_STRONG_INLINE Packet8d pcmp_le_old(const Packet8d& a, const Packet8d& b) {
  __mmask8 mask = _mm512_cmp_pd_mask(a, b, _CMP_LE_OQ);
  return _mm512_castsi512_pd(_mm512_mask_set1_epi64(_mm512_set1_epi64(0), mask, 0xffffffffffffffffu));
}
template <>
EIGEN_STRONG_INLINE Packet8d pcmp_lt_old(const Packet8d& a, const Packet8d& b) {
  __mmask8 mask = _mm512_cmp_pd_mask(a, b, _CMP_LT_OQ);
  return _mm512_castsi512_pd(_mm512_mask_set1_epi64(_mm512_set1_epi64(0), mask, 0xffffffffffffffffu));
}
template <>
EIGEN_STRONG_INLINE Packet8d pcmp_lt_or_nan_old(const Packet8d& a, const Packet8d& b) {
  __mmask8 mask = _mm512_cmp_pd_mask(a, b, _CMP_NGE_UQ);
  return _mm512_castsi512_pd(_mm512_mask_set1_epi64(_mm512_set1_epi64(0), mask, 0xffffffffffffffffu));
}

template <>
EIGEN_STRONG_INLINE Packet16f print_old<Packet16f>(const Packet16f& a) {
  return _mm512_roundscale_ps(a, _MM_FROUND_CUR_DIRECTION);
}
template <>
EIGEN_STRONG_INLINE Packet8d print_old<Packet8d>(const Packet8d& a) {
  return _mm512_roundscale_pd(a, _MM_FROUND_CUR_DIRECTION);
}

template <>
EIGEN_STRONG_INLINE Packet16f pceil_old<Packet16f>(const Packet16f& a) {
  return _mm512_roundscale_ps(a, _MM_FROUND_TO_POS_INF);
}
template <>
EIGEN_STRONG_INLINE Packet8d pceil_old<Packet8d>(const Packet8d& a) {
  return _mm512_roundscale_pd(a, _MM_FROUND_TO_POS_INF);
}

template <>
EIGEN_STRONG_INLINE Packet16f pfloor_old<Packet16f>(const Packet16f& a) {
  return _mm512_roundscale_ps(a, _MM_FROUND_TO_NEG_INF);
}
template <>
EIGEN_STRONG_INLINE Packet8d pfloor_old<Packet8d>(const Packet8d& a) {
  return _mm512_roundscale_pd(a, _MM_FROUND_TO_NEG_INF);
}

template <>
EIGEN_STRONG_INLINE Packet16i ptrue_old<Packet16i>(const Packet16i& /*a*/) {
  return _mm512_set1_epi32(0xffffffffu);
}

template <>
EIGEN_STRONG_INLINE Packet16f ptrue_old<Packet16f>(const Packet16f& a) {
  return _mm512_castsi512_ps(ptrue_old<Packet16i>(_mm512_castps_si512(a)));
}

template <>
EIGEN_STRONG_INLINE Packet8d ptrue_old<Packet8d>(const Packet8d& a) {
  return _mm512_castsi512_pd(ptrue_old<Packet16i>(_mm512_castpd_si512(a)));
}

template <>
EIGEN_STRONG_INLINE Packet16i pand_old<Packet16i>(const Packet16i& a, const Packet16i& b) {
  return _mm512_and_si512(a, b);
}

template <>
EIGEN_STRONG_INLINE Packet16f pand_old<Packet16f>(const Packet16f& a, const Packet16f& b) {
#ifdef EIGEN_VECTORIZE_AVX512DQ
  return _mm512_and_ps(a, b);
#else
  return _mm512_castsi512_ps(pand_old(_mm512_castps_si512(a), _mm512_castps_si512(b)));
#endif
}
template <>
EIGEN_STRONG_INLINE Packet8d pand_old<Packet8d>(const Packet8d& a, const Packet8d& b) {
#ifdef EIGEN_VECTORIZE_AVX512DQ
  return _mm512_and_pd(a, b);
#else
  Packet8d res = _mm512_undefined_pd();
  Packet4d lane0_a = _mm512_extractf64x4_pd(a, 0);
  Packet4d lane0_b = _mm512_extractf64x4_pd(b, 0);
  res = _mm512_insertf64x4(res, _mm256_and_pd(lane0_a, lane0_b), 0);

  Packet4d lane1_a = _mm512_extractf64x4_pd(a, 1);
  Packet4d lane1_b = _mm512_extractf64x4_pd(b, 1);
  return _mm512_insertf64x4(res, _mm256_and_pd(lane1_a, lane1_b), 1);
#endif
}

template <>
EIGEN_STRONG_INLINE Packet16i por_old<Packet16i>(const Packet16i& a, const Packet16i& b) {
  return _mm512_or_si512(a, b);
}

template <>
EIGEN_STRONG_INLINE Packet16f por_old<Packet16f>(const Packet16f& a, const Packet16f& b) {
#ifdef EIGEN_VECTORIZE_AVX512DQ
  return _mm512_or_ps(a, b);
#else
  return _mm512_castsi512_ps(por_old(_mm512_castps_si512(a), _mm512_castps_si512(b)));
#endif
}

template <>
EIGEN_STRONG_INLINE Packet8d por_old<Packet8d>(const Packet8d& a, const Packet8d& b) {
#ifdef EIGEN_VECTORIZE_AVX512DQ
  return _mm512_or_pd(a, b);
#else
  return _mm512_castsi512_pd(por_old(_mm512_castpd_si512(a), _mm512_castpd_si512(b)));
#endif
}

template <>
EIGEN_STRONG_INLINE Packet16i pxor_old<Packet16i>(const Packet16i& a, const Packet16i& b) {
  return _mm512_xor_si512(a, b);
}

template <>
EIGEN_STRONG_INLINE Packet16f pxor_old<Packet16f>(const Packet16f& a, const Packet16f& b) {
#ifdef EIGEN_VECTORIZE_AVX512DQ
  return _mm512_xor_ps(a, b);
#else
  return _mm512_castsi512_ps(pxor_old(_mm512_castps_si512(a), _mm512_castps_si512(b)));
#endif
}

template <>
EIGEN_STRONG_INLINE Packet8d pxor_old<Packet8d>(const Packet8d& a, const Packet8d& b) {
#ifdef EIGEN_VECTORIZE_AVX512DQ
  return _mm512_xor_pd(a, b);
#else
  return _mm512_castsi512_pd(pxor_old(_mm512_castpd_si512(a), _mm512_castpd_si512(b)));
#endif
}

template <>
EIGEN_STRONG_INLINE Packet16i pandnot_old<Packet16i>(const Packet16i& a, const Packet16i& b) {
  return _mm512_andnot_si512(b, a);
}

template <>
EIGEN_STRONG_INLINE Packet16f pandnot_old<Packet16f>(const Packet16f& a, const Packet16f& b) {
#ifdef EIGEN_VECTORIZE_AVX512DQ
  return _mm512_andnot_ps(b, a);
#else
  return _mm512_castsi512_ps(pandnot_old(_mm512_castps_si512(a), _mm512_castps_si512(b)));
#endif
}
template <>
EIGEN_STRONG_INLINE Packet8d pandnot_old<Packet8d>(const Packet8d& a, const Packet8d& b) {
#ifdef EIGEN_VECTORIZE_AVX512DQ
  return _mm512_andnot_pd(b, a);
#else
  return _mm512_castsi512_pd(pandnot_old(_mm512_castpd_si512(a), _mm512_castpd_si512(b)));
#endif
}

template <>
EIGEN_STRONG_INLINE Packet16f pround_old<Packet16f>(const Packet16f& a) {
  // Work-around for default std::round rounding mode.
  const Packet16f mask = pset1frombits_old<Packet16f>(static_cast<numext::uint32_t>(0x80000000u));
  const Packet16f prev0dot5 = pset1frombits_old<Packet16f>(static_cast<numext::uint32_t>(0x3EFFFFFFu));
  return _mm512_roundscale_ps(padd_old(por_old(pand_old(a, mask), prev0dot5), a), _MM_FROUND_TO_ZERO);
}
template <>
EIGEN_STRONG_INLINE Packet8d pround_old<Packet8d>(const Packet8d& a) {
  // Work-around for default std::round rounding mode.
  const Packet8d mask = pset1frombits_old<Packet8d>(static_cast<numext::uint64_t>(0x8000000000000000ull));
  const Packet8d prev0dot5 = pset1frombits_old<Packet8d>(static_cast<numext::uint64_t>(0x3FDFFFFFFFFFFFFFull));
  return _mm512_roundscale_pd(padd_old(por_old(pand_old(a, mask), prev0dot5), a), _MM_FROUND_TO_ZERO);
}

template <int N>
EIGEN_STRONG_INLINE Packet16i parithmetic_shift_right_old(Packet16i a) {
  return _mm512_srai_epi32(a, N);
}

template <int N>
EIGEN_STRONG_INLINE Packet16i plogical_shift_right_old(Packet16i a) {
  return _mm512_srli_epi32(a, N);
}

template <int N>
EIGEN_STRONG_INLINE Packet16i plogical_shift_left_old(Packet16i a) {
  return _mm512_slli_epi32(a, N);
}

template <>
EIGEN_STRONG_INLINE Packet16f pload_old<Packet16f>(const float* from) {
  EIGEN_DEBUG_ALIGNED_LOAD return _mm512_load_ps(from);
}
template <>
EIGEN_STRONG_INLINE Packet8d pload_old<Packet8d>(const double* from) {
  EIGEN_DEBUG_ALIGNED_LOAD return _mm512_load_pd(from);
}
template <>
EIGEN_STRONG_INLINE Packet16i pload_old<Packet16i>(const int* from) {
  EIGEN_DEBUG_ALIGNED_LOAD return _mm512_load_si512(reinterpret_cast<const __m512i*>(from));
}

template <>
EIGEN_STRONG_INLINE Packet16f ploadu_old<Packet16f>(const float* from) {
  EIGEN_DEBUG_UNALIGNED_LOAD return _mm512_loadu_ps(from);
}
template <>
EIGEN_STRONG_INLINE Packet8d ploadu_old<Packet8d>(const double* from) {
  EIGEN_DEBUG_UNALIGNED_LOAD return _mm512_loadu_pd(from);
}
template <>
EIGEN_STRONG_INLINE Packet16i ploadu_old<Packet16i>(const int* from) {
  EIGEN_DEBUG_UNALIGNED_LOAD return _mm512_loadu_si512(reinterpret_cast<const __m512i*>(from));
}

template <>
EIGEN_STRONG_INLINE Packet16f ploadu_old<Packet16f>(const float* from, uint16_t umask) {
  __mmask16 mask = static_cast<__mmask16>(umask);
  EIGEN_DEBUG_UNALIGNED_LOAD return _mm512_maskz_loadu_ps(mask, from);
}
template <>
EIGEN_STRONG_INLINE Packet8d ploadu_old<Packet8d>(const double* from, uint8_t umask) {
  __mmask8 mask = static_cast<__mmask8>(umask);
  EIGEN_DEBUG_UNALIGNED_LOAD return _mm512_maskz_loadu_pd(mask, from);
}

// Loads 8 floats from memory a returns the packet
// {a0, a0  a1, a1, a2, a2, a3, a3, a4, a4, a5, a5, a6, a6, a7, a7}
template <>
EIGEN_STRONG_INLINE Packet16f ploaddup_old<Packet16f>(const float* from) {
  // an unaligned load is required here as there is no requirement
  // on the alignment of input pointer 'from'
  __m256i low_half = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(from));
  __m512 even_elements = _mm512_castsi512_ps(_mm512_cvtepu32_epi64(low_half));
  __m512 pairs = _mm512_permute_ps(even_elements, _MM_SHUFFLE(2, 2, 0, 0));
  return pairs;
}

#ifdef EIGEN_VECTORIZE_AVX512DQ
// FIXME: this does not look optimal, better load a Packet4d and shuffle...
// Loads 4 doubles from memory a returns the packet {a0, a0  a1, a1, a2, a2, a3,
// a3}
template <>
EIGEN_STRONG_INLINE Packet8d ploaddup_old<Packet8d>(const double* from) {
  __m512d x = _mm512_setzero_pd();
  x = _mm512_insertf64x2(x, _mm_loaddup_pd(&from[0]), 0);
  x = _mm512_insertf64x2(x, _mm_loaddup_pd(&from[1]), 1);
  x = _mm512_insertf64x2(x, _mm_loaddup_pd(&from[2]), 2);
  x = _mm512_insertf64x2(x, _mm_loaddup_pd(&from[3]), 3);
  return x;
}
#else
template <>
EIGEN_STRONG_INLINE Packet8d ploaddup_old<Packet8d>(const double* from) {
  __m512d x = _mm512_setzero_pd();
  x = _mm512_mask_broadcastsd_pd(x, 0x3 << 0, _mm_load_sd(from + 0));
  x = _mm512_mask_broadcastsd_pd(x, 0x3 << 2, _mm_load_sd(from + 1));
  x = _mm512_mask_broadcastsd_pd(x, 0x3 << 4, _mm_load_sd(from + 2));
  x = _mm512_mask_broadcastsd_pd(x, 0x3 << 6, _mm_load_sd(from + 3));
  return x;
}
#endif

// Loads 8 integers from memory and returns the packet
// {a0, a0  a1, a1, a2, a2, a3, a3, a4, a4, a5, a5, a6, a6, a7, a7}
template <>
EIGEN_STRONG_INLINE Packet16i ploaddup_old<Packet16i>(const int* from) {
  __m256i low_half = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(from));
  __m512 even_elements = _mm512_castsi512_ps(_mm512_cvtepu32_epi64(low_half));
  __m512 pairs = _mm512_permute_ps(even_elements, _MM_SHUFFLE(2, 2, 0, 0));
  return _mm512_castps_si512(pairs);
}

// Loads 4 floats from memory a returns the packet
// {a0, a0  a0, a0, a1, a1, a1, a1, a2, a2, a2, a2, a3, a3, a3, a3}
template <>
EIGEN_STRONG_INLINE Packet16f ploadquad_old<Packet16f>(const float* from) {
  Packet16f tmp = _mm512_castps128_ps512(ploadu_old<Packet4f>(from));
  const Packet16i scatter_mask = _mm512_set_epi32(3, 3, 3, 3, 2, 2, 2, 2, 1, 1, 1, 1, 0, 0, 0, 0);
  return _mm512_permutexvar_ps(scatter_mask, tmp);
}

// Loads 2 doubles from memory a returns the packet
// {a0, a0  a0, a0, a1, a1, a1, a1}
template <>
EIGEN_STRONG_INLINE Packet8d ploadquad_old<Packet8d>(const double* from) {
  __m256d lane0 = _mm256_set1_pd(*from);
  __m256d lane1 = _mm256_set1_pd(*(from + 1));
  __m512d tmp = _mm512_undefined_pd();
  tmp = _mm512_insertf64x4(tmp, lane0, 0);
  return _mm512_insertf64x4(tmp, lane1, 1);
}

// Loads 4 integers from memory and returns the packet
// {a0, a0  a0, a0, a1, a1, a1, a1, a2, a2, a2, a2, a3, a3, a3, a3}
template <>
EIGEN_STRONG_INLINE Packet16i ploadquad_old<Packet16i>(const int* from) {
  Packet16i tmp = _mm512_castsi128_si512(ploadu_old<Packet4i>(from));
  const Packet16i scatter_mask = _mm512_set_epi32(3, 3, 3, 3, 2, 2, 2, 2, 1, 1, 1, 1, 0, 0, 0, 0);
  return _mm512_permutexvar_epi32(scatter_mask, tmp);
}

template <>
EIGEN_STRONG_INLINE void pstore_old<float>(float* to, const Packet16f& from) {
  EIGEN_DEBUG_ALIGNED_STORE _mm512_store_ps(to, from);
}
template <>
EIGEN_STRONG_INLINE void pstore_old<double>(double* to, const Packet8d& from) {
  EIGEN_DEBUG_ALIGNED_STORE _mm512_store_pd(to, from);
}
template <>
EIGEN_STRONG_INLINE void pstore_old<int>(int* to, const Packet16i& from) {
  EIGEN_DEBUG_ALIGNED_STORE _mm512_storeu_si512(reinterpret_cast<__m512i*>(to), from);
}

template <>
EIGEN_STRONG_INLINE void pstoreu_old<float>(float* to, const Packet16f& from) {
  EIGEN_DEBUG_UNALIGNED_STORE _mm512_storeu_ps(to, from);
}
template <>
EIGEN_STRONG_INLINE void pstoreu_old<double>(double* to, const Packet8d& from) {
  EIGEN_DEBUG_UNALIGNED_STORE _mm512_storeu_pd(to, from);
}
template <>
EIGEN_STRONG_INLINE void pstoreu_old<int>(int* to, const Packet16i& from) {
  EIGEN_DEBUG_UNALIGNED_STORE _mm512_storeu_si512(reinterpret_cast<__m512i*>(to), from);
}
template <>
EIGEN_STRONG_INLINE void pstoreu_old<float>(float* to, const Packet16f& from, uint16_t umask) {
  __mmask16 mask = static_cast<__mmask16>(umask);
  EIGEN_DEBUG_UNALIGNED_STORE return _mm512_mask_storeu_ps(to, mask, from);
}
template <>
EIGEN_STRONG_INLINE void pstoreu_old<double>(double* to, const Packet8d& from, uint8_t umask) {
  __mmask8 mask = static_cast<__mmask8>(umask);
  EIGEN_DEBUG_UNALIGNED_STORE return _mm512_mask_storeu_pd(to, mask, from);
}

template <>
EIGEN_DEVICE_FUNC inline Packet16f pgather_old<float, Packet16f>(const float* from, Index stride) {
  Packet16i stride_vector = _mm512_set1_epi32(convert_index<int>(stride));
  Packet16i stride_multiplier = _mm512_set_epi32(15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0);
  Packet16i indices = _mm512_mullo_epi32(stride_vector, stride_multiplier);

  return _mm512_i32gather_ps(indices, from, 4);
}
template <>
EIGEN_DEVICE_FUNC inline Packet8d pgather_old<double, Packet8d>(const double* from, Index stride) {
  Packet8i stride_vector = _mm256_set1_epi32(convert_index<int>(stride));
  Packet8i stride_multiplier = _mm256_set_epi32(7, 6, 5, 4, 3, 2, 1, 0);
  Packet8i indices = _mm256_mullo_epi32(stride_vector, stride_multiplier);

  return _mm512_i32gather_pd(indices, from, 8);
}
template <>
EIGEN_DEVICE_FUNC inline Packet16i pgather_old<int, Packet16i>(const int* from, Index stride) {
  Packet16i stride_vector = _mm512_set1_epi32(convert_index<int>(stride));
  Packet16i stride_multiplier = _mm512_set_epi32(15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0);
  Packet16i indices = _mm512_mullo_epi32(stride_vector, stride_multiplier);
  return _mm512_i32gather_epi32(indices, from, 4);
}

template <>
EIGEN_DEVICE_FUNC inline void pscatter_old<float, Packet16f>(float* to, const Packet16f& from, Index stride) {
  Packet16i stride_vector = _mm512_set1_epi32(convert_index<int>(stride));
  Packet16i stride_multiplier = _mm512_set_epi32(15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0);
  Packet16i indices = _mm512_mullo_epi32(stride_vector, stride_multiplier);
  _mm512_i32scatter_ps(to, indices, from, 4);
}
template <>
EIGEN_DEVICE_FUNC inline void pscatter_old<double, Packet8d>(double* to, const Packet8d& from, Index stride) {
  Packet8i stride_vector = _mm256_set1_epi32(convert_index<int>(stride));
  Packet8i stride_multiplier = _mm256_set_epi32(7, 6, 5, 4, 3, 2, 1, 0);
  Packet8i indices = _mm256_mullo_epi32(stride_vector, stride_multiplier);
  _mm512_i32scatter_pd(to, indices, from, 8);
}
template <>
EIGEN_DEVICE_FUNC inline void pscatter_old<int, Packet16i>(int* to, const Packet16i& from, Index stride) {
  Packet16i stride_vector = _mm512_set1_epi32(convert_index<int>(stride));
  Packet16i stride_multiplier = _mm512_set_epi32(15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0);
  Packet16i indices = _mm512_mullo_epi32(stride_vector, stride_multiplier);
  _mm512_i32scatter_epi32(to, indices, from, 4);
}

template <>
EIGEN_STRONG_INLINE void pstore1_old<Packet16f>(float* to, const float& a) {
  Packet16f pa = pset1_old<Packet16f>(a);
  pstore_old(to, pa);
}
template <>
EIGEN_STRONG_INLINE void pstore1_old<Packet8d>(double* to, const double& a) {
  Packet8d pa = pset1_old<Packet8d>(a);
  pstore_old(to, pa);
}
template <>
EIGEN_STRONG_INLINE void pstore1_old<Packet16i>(int* to, const int& a) {
  Packet16i pa = pset1_old<Packet16i>(a);
  pstore_old(to, pa);
}

template <>
EIGEN_STRONG_INLINE void prefetch_old<float>(const float* addr) {
  _mm_prefetch((SsePrefetchPtrType)(addr), _MM_HINT_T0);
}
template <>
EIGEN_STRONG_INLINE void prefetch_old<double>(const double* addr) {
  _mm_prefetch((SsePrefetchPtrType)(addr), _MM_HINT_T0);
}
template <>
EIGEN_STRONG_INLINE void prefetch_old<int>(const int* addr) {
  _mm_prefetch((SsePrefetchPtrType)(addr), _MM_HINT_T0);
}

template <>
EIGEN_STRONG_INLINE float pfirst_old<Packet16f>(const Packet16f& a) {
  return _mm_cvtss_f32(_mm512_extractf32x4_ps(a, 0));
}
template <>
EIGEN_STRONG_INLINE double pfirst_old<Packet8d>(const Packet8d& a) {
  return _mm_cvtsd_f64(_mm256_extractf128_pd(_mm512_extractf64x4_pd(a, 0), 0));
}
template <>
EIGEN_STRONG_INLINE int pfirst_old<Packet16i>(const Packet16i& a) {
  return _mm_extract_epi32(_mm512_extracti32x4_epi32(a, 0), 0);
}

template <>
EIGEN_STRONG_INLINE Packet16f preverse_old(const Packet16f& a) {
  return _mm512_permutexvar_ps(_mm512_set_epi32(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15), a);
}

template <>
EIGEN_STRONG_INLINE Packet8d preverse_old(const Packet8d& a) {
  return _mm512_permutexvar_pd(_mm512_set_epi32(0, 0, 0, 1, 0, 2, 0, 3, 0, 4, 0, 5, 0, 6, 0, 7), a);
}

template <>
EIGEN_STRONG_INLINE Packet16i preverse_old(const Packet16i& a) {
  return _mm512_permutexvar_epi32(_mm512_set_epi32(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15), a);
}

template <>
EIGEN_STRONG_INLINE Packet16f pabs_old(const Packet16f& a) {
  // _mm512_abs_ps intrinsic not found, so hack around it
  return _mm512_castsi512_ps(_mm512_and_si512(_mm512_castps_si512(a), _mm512_set1_epi32(0x7fffffff)));
}
template <>
EIGEN_STRONG_INLINE Packet8d pabs_old(const Packet8d& a) {
  // _mm512_abs_ps intrinsic not found, so hack around it
  return _mm512_castsi512_pd(_mm512_and_si512(_mm512_castpd_si512(a), _mm512_set1_epi64(0x7fffffffffffffff)));
}
template <>
EIGEN_STRONG_INLINE Packet16i pabs_old(const Packet16i& a) {
  return _mm512_abs_epi32(a);
}

template <>
EIGEN_STRONG_INLINE Packet16f pfrexp_old<Packet16f>(const Packet16f& a, Packet16f& exponent) {
  return pfrexp_generic(a, exponent);
}

// Extract exponent without existence of Packet8l.
template <>
EIGEN_STRONG_INLINE Packet8d pfrexp_generic_get_biased_exponent_old(const Packet8d& a) {
  const Packet8d cst_exp_mask = pset1frombits_old<Packet8d>(static_cast<uint64_t>(0x7ff0000000000000ull));
#ifdef EIGEN_VECTORIZE_AVX512DQ
  return _mm512_cvtepi64_pd(_mm512_srli_epi64(_mm512_castpd_si512(pand_old(a, cst_exp_mask)), 52));
#else
  return _mm512_cvtepi32_pd(_mm512_cvtepi64_epi32(_mm512_srli_epi64(_mm512_castpd_si512(pand_old(a, cst_exp_mask)), 52)));
#endif
}

template <>
EIGEN_STRONG_INLINE Packet8d pfrexp_old<Packet8d>(const Packet8d& a, Packet8d& exponent) {
  return pfrexp_generic(a, exponent);
}

template <>
EIGEN_STRONG_INLINE Packet16f pldexp_old<Packet16f>(const Packet16f& a, const Packet16f& exponent) {
  return pldexp_generic(a, exponent);
}

template <>
EIGEN_STRONG_INLINE Packet8d pldexp_old<Packet8d>(const Packet8d& a, const Packet8d& exponent) {
  // Clamp exponent to [-2099, 2099]
  const Packet8d max_exponent = pset1_old<Packet8d>(2099.0);
  const Packet8i e = _mm512_cvtpd_epi32(pmin_old(pmax_old(exponent, pnegate_old(max_exponent)), max_exponent));

  // Split 2^e into four factors and multiply.
  const Packet8i bias = pset1_old<Packet8i>(1023);
  Packet8i b = parithmetic_shift_right_old<2>(e);  // floor(e/4)

  // 2^b
  const Packet8i permute_idx = _mm256_setr_epi32(0, 4, 1, 5, 2, 6, 3, 7);
  Packet8i hi = _mm256_permutevar8x32_epi32(padd_old(b, bias), permute_idx);
  Packet8i lo = _mm256_slli_epi64(hi, 52);
  hi = _mm256_slli_epi64(_mm256_srli_epi64(hi, 32), 52);
  Packet8d c = _mm512_castsi512_pd(_mm512_inserti64x4(_mm512_castsi256_si512(lo), hi, 1));
  Packet8d out = pmul_old(pmul_old(pmul_old(a, c), c), c);  // a * 2^(3b)

  // 2^(e - 3b)
  b = psub_old(psub_old(psub_old(e, b), b), b);  // e - 3b
  hi = _mm256_permutevar8x32_epi32(padd_old(b, bias), permute_idx);
  lo = _mm256_slli_epi64(hi, 52);
  hi = _mm256_slli_epi64(_mm256_srli_epi64(hi, 32), 52);
  c = _mm512_castsi512_pd(_mm512_inserti64x4(_mm512_castsi256_si512(lo), hi, 1));
  out = pmul_old(out, c);  // a * 2^e
  return out;
}

#ifdef EIGEN_VECTORIZE_AVX512DQ

template <>
EIGEN_STRONG_INLINE float predux_old<Packet16f>(const Packet16f& a) {
#ifdef EIGEN_VECTORIZE_AVX512DQ
  __m256 lane0 = _mm512_extractf32x8_ps(a, 0);
  __m256 lane1 = _mm512_extractf32x8_ps(a, 1);
  Packet8f x = _mm256_add_ps(lane0, lane1);
  return predux_old<Packet8f>(x);
#else
  __m128 lane0 = _mm512_extractf32x4_ps(a, 0);
  __m128 lane1 = _mm512_extractf32x4_ps(a, 1);
  __m128 lane2 = _mm512_extractf32x4_ps(a, 2);
  __m128 lane3 = _mm512_extractf32x4_ps(a, 3);
  __m128 sum = _mm_add_ps(_mm_add_ps(lane0, lane1), _mm_add_ps(lane2, lane3));
  sum = _mm_hadd_ps(sum, sum);
  sum = _mm_hadd_ps(sum, _mm_permute_ps(sum, 1));
  return _mm_cvtss_f32(sum);
#endif
}
template <>
EIGEN_STRONG_INLINE double predux_old<Packet8d>(const Packet8d& a) {
  __m256d lane0 = _mm512_extractf64x4_pd(a, 0);
  __m256d lane1 = _mm512_extractf64x4_pd(a, 1);
  __m256d sum = _mm256_add_pd(lane0, lane1);
  __m256d tmp0 = _mm256_hadd_pd(sum, _mm256_permute2f128_pd(sum, sum, 1));
  return _mm_cvtsd_f64(_mm256_castpd256_pd128(_mm256_hadd_pd(tmp0, tmp0)));
}
template <>
EIGEN_STRONG_INLINE int predux_old<Packet16i>(const Packet16i& a) {
#ifdef EIGEN_VECTORIZE_AVX512DQ
  __m256i lane0 = _mm512_extracti32x8_epi32(a, 0);
  __m256i lane1 = _mm512_extracti32x8_epi32(a, 1);
  Packet8i x = _mm256_add_epi32(lane0, lane1);
  return predux_old<Packet8i>(x);
#else
  __m128i lane0 = _mm512_extracti32x4_epi32(a, 0);
  __m128i lane1 = _mm512_extracti32x4_epi32(a, 1);
  __m128i lane2 = _mm512_extracti32x4_epi32(a, 2);
  __m128i lane3 = _mm512_extracti32x4_epi32(a, 3);
  __m128i sum = _mm_add_epi32(_mm_add_epi32(lane0, lane1), _mm_add_epi32(lane2, lane3));
  sum = _mm_hadd_epi32(sum, sum);
  sum = _mm_hadd_epi32(sum, _mm_castps_si128(_mm_permute_ps(_mm_castsi128_ps(sum), 1)));
  return _mm_cvtsi128_si32(sum);
#endif
}

template <>
EIGEN_STRONG_INLINE Packet8f predux_half_dowto4_old<Packet16f>(const Packet16f& a) {
#ifdef EIGEN_VECTORIZE_AVX512DQ
  __m256 lane0 = _mm512_extractf32x8_ps(a, 0);
  __m256 lane1 = _mm512_extractf32x8_ps(a, 1);
  return _mm256_add_ps(lane0, lane1);
#else
  __m128 lane0 = _mm512_extractf32x4_ps(a, 0);
  __m128 lane1 = _mm512_extractf32x4_ps(a, 1);
  __m128 lane2 = _mm512_extractf32x4_ps(a, 2);
  __m128 lane3 = _mm512_extractf32x4_ps(a, 3);
  __m128 sum0 = _mm_add_ps(lane0, lane2);
  __m128 sum1 = _mm_add_ps(lane1, lane3);
  return _mm256_insertf128_ps(_mm256_castps128_ps256(sum0), sum1, 1);
#endif
}
template <>
EIGEN_STRONG_INLINE Packet4d predux_half_dowto4_old<Packet8d>(const Packet8d& a) {
  __m256d lane0 = _mm512_extractf64x4_pd(a, 0);
  __m256d lane1 = _mm512_extractf64x4_pd(a, 1);
  return _mm256_add_pd(lane0, lane1);
}
template <>
EIGEN_STRONG_INLINE Packet8i predux_half_dowto4_old<Packet16i>(const Packet16i& a) {
#ifdef EIGEN_VECTORIZE_AVX512DQ
  __m256i lane0 = _mm512_extracti32x8_epi32(a, 0);
  __m256i lane1 = _mm512_extracti32x8_epi32(a, 1);
  return _mm256_add_epi32(lane0, lane1);
#else
  __m128i lane0 = _mm512_extracti32x4_epi32(a, 0);
  __m128i lane1 = _mm512_extracti32x4_epi32(a, 1);
  __m128i lane2 = _mm512_extracti32x4_epi32(a, 2);
  __m128i lane3 = _mm512_extracti32x4_epi32(a, 3);
  __m128i sum0 = _mm_add_epi32(lane0, lane2);
  __m128i sum1 = _mm_add_epi32(lane1, lane3);
  return _mm256_inserti128_si256(_mm256_castsi128_si256(sum0), sum1, 1);
#endif
}

template <>
EIGEN_STRONG_INLINE float predux_mul_old<Packet16f>(const Packet16f& a) {
//#ifdef EIGEN_VECTORIZE_AVX512DQ
#if 0
  Packet8f lane0 = _mm512_extractf32x8_ps(a, 0);
  Packet8f lane1 = _mm512_extractf32x8_ps(a, 1);
  Packet8f res = pmul_old(lane0, lane1);
  res = pmul_old(res, _mm256_permute2f128_ps(res, res, 1));
  res = pmul_old(res, _mm_permute_ps(res, _MM_SHUFFLE(0, 0, 3, 2)));
  return pfirst_old(pmul_old(res, _mm_permute_ps(res, _MM_SHUFFLE(0, 0, 0, 1))));
#else
  __m128 lane0 = _mm512_extractf32x4_ps(a, 0);
  __m128 lane1 = _mm512_extractf32x4_ps(a, 1);
  __m128 lane2 = _mm512_extractf32x4_ps(a, 2);
  __m128 lane3 = _mm512_extractf32x4_ps(a, 3);
  __m128 res = pmul_old(pmul_old(lane0, lane1), pmul_old(lane2, lane3));
  res = pmul_old(res, _mm_permute_ps(res, _MM_SHUFFLE(0, 0, 3, 2)));
  return pfirst_old(pmul_old(res, _mm_permute_ps(res, _MM_SHUFFLE(0, 0, 0, 1))));
#endif
}
template <>
EIGEN_STRONG_INLINE double predux_mul_old<Packet8d>(const Packet8d& a) {
  __m256d lane0 = _mm512_extractf64x4_pd(a, 0);
  __m256d lane1 = _mm512_extractf64x4_pd(a, 1);
  __m256d res = pmul_old(lane0, lane1);
  res = pmul_old(res, _mm256_permute2f128_pd(res, res, 1));
  return pfirst_old(pmul_old(res, _mm256_shuffle_pd(res, res, 1)));
}

template <>
EIGEN_STRONG_INLINE float predux_min_old<Packet16f>(const Packet16f& a) {
  __m128 lane0 = _mm512_extractf32x4_ps(a, 0);
  __m128 lane1 = _mm512_extractf32x4_ps(a, 1);
  __m128 lane2 = _mm512_extractf32x4_ps(a, 2);
  __m128 lane3 = _mm512_extractf32x4_ps(a, 3);
  __m128 res = _mm_min_ps(_mm_min_ps(lane0, lane1), _mm_min_ps(lane2, lane3));
  res = _mm_min_ps(res, _mm_permute_ps(res, _MM_SHUFFLE(0, 0, 3, 2)));
  return pfirst_old(_mm_min_ps(res, _mm_permute_ps(res, _MM_SHUFFLE(0, 0, 0, 1))));
}
template <>
EIGEN_STRONG_INLINE double predux_min_old<Packet8d>(const Packet8d& a) {
  __m256d lane0 = _mm512_extractf64x4_pd(a, 0);
  __m256d lane1 = _mm512_extractf64x4_pd(a, 1);
  __m256d res = _mm256_min_pd(lane0, lane1);
  res = _mm256_min_pd(res, _mm256_permute2f128_pd(res, res, 1));
  return pfirst_old(_mm256_min_pd(res, _mm256_shuffle_pd(res, res, 1)));
}

template <>
EIGEN_STRONG_INLINE float predux_max_old<Packet16f>(const Packet16f& a) {
  __m128 lane0 = _mm512_extractf32x4_ps(a, 0);
  __m128 lane1 = _mm512_extractf32x4_ps(a, 1);
  __m128 lane2 = _mm512_extractf32x4_ps(a, 2);
  __m128 lane3 = _mm512_extractf32x4_ps(a, 3);
  __m128 res = _mm_max_ps(_mm_max_ps(lane0, lane1), _mm_max_ps(lane2, lane3));
  res = _mm_max_ps(res, _mm_permute_ps(res, _MM_SHUFFLE(0, 0, 3, 2)));
  return pfirst_old(_mm_max_ps(res, _mm_permute_ps(res, _MM_SHUFFLE(0, 0, 0, 1))));
}

template <>
EIGEN_STRONG_INLINE double predux_max_old<Packet8d>(const Packet8d& a) {
  __m256d lane0 = _mm512_extractf64x4_pd(a, 0);
  __m256d lane1 = _mm512_extractf64x4_pd(a, 1);
  __m256d res = _mm256_max_pd(lane0, lane1);
  res = _mm256_max_pd(res, _mm256_permute2f128_pd(res, res, 1));
  return pfirst_old(_mm256_max_pd(res, _mm256_shuffle_pd(res, res, 1)));
}

template <>
EIGEN_STRONG_INLINE bool predux_any_old(const Packet16f& x) {
  Packet16i xi = _mm512_castps_si512(x);
  __mmask16 tmp = _mm512_test_epi32_mask(xi, xi);
  return !_mm512_kortestz(tmp, tmp);
}

#define PACK_OUTPUT(OUTPUT, INPUT, INDEX, STRIDE) \
  EIGEN_INSERT_8f_INTO_16f(OUTPUT[INDEX], INPUT[INDEX], INPUT[INDEX + STRIDE]);

EIGEN_DEVICE_FUNC inline void ptranspose_old(PacketBlock<Packet16f, 16>& kernel) {
  __m512 T0 = _mm512_unpacklo_ps(kernel.packet[0], kernel.packet[1]);
  __m512 T1 = _mm512_unpackhi_ps(kernel.packet[0], kernel.packet[1]);
  __m512 T2 = _mm512_unpacklo_ps(kernel.packet[2], kernel.packet[3]);
  __m512 T3 = _mm512_unpackhi_ps(kernel.packet[2], kernel.packet[3]);
  __m512 T4 = _mm512_unpacklo_ps(kernel.packet[4], kernel.packet[5]);
  __m512 T5 = _mm512_unpackhi_ps(kernel.packet[4], kernel.packet[5]);
  __m512 T6 = _mm512_unpacklo_ps(kernel.packet[6], kernel.packet[7]);
  __m512 T7 = _mm512_unpackhi_ps(kernel.packet[6], kernel.packet[7]);
  __m512 T8 = _mm512_unpacklo_ps(kernel.packet[8], kernel.packet[9]);
  __m512 T9 = _mm512_unpackhi_ps(kernel.packet[8], kernel.packet[9]);
  __m512 T10 = _mm512_unpacklo_ps(kernel.packet[10], kernel.packet[11]);
  __m512 T11 = _mm512_unpackhi_ps(kernel.packet[10], kernel.packet[11]);
  __m512 T12 = _mm512_unpacklo_ps(kernel.packet[12], kernel.packet[13]);
  __m512 T13 = _mm512_unpackhi_ps(kernel.packet[12], kernel.packet[13]);
  __m512 T14 = _mm512_unpacklo_ps(kernel.packet[14], kernel.packet[15]);
  __m512 T15 = _mm512_unpackhi_ps(kernel.packet[14], kernel.packet[15]);
  __m512 S0 = _mm512_shuffle_ps(T0, T2, _MM_SHUFFLE(1, 0, 1, 0));
  __m512 S1 = _mm512_shuffle_ps(T0, T2, _MM_SHUFFLE(3, 2, 3, 2));
  __m512 S2 = _mm512_shuffle_ps(T1, T3, _MM_SHUFFLE(1, 0, 1, 0));
  __m512 S3 = _mm512_shuffle_ps(T1, T3, _MM_SHUFFLE(3, 2, 3, 2));
  __m512 S4 = _mm512_shuffle_ps(T4, T6, _MM_SHUFFLE(1, 0, 1, 0));
  __m512 S5 = _mm512_shuffle_ps(T4, T6, _MM_SHUFFLE(3, 2, 3, 2));
  __m512 S6 = _mm512_shuffle_ps(T5, T7, _MM_SHUFFLE(1, 0, 1, 0));
  __m512 S7 = _mm512_shuffle_ps(T5, T7, _MM_SHUFFLE(3, 2, 3, 2));
  __m512 S8 = _mm512_shuffle_ps(T8, T10, _MM_SHUFFLE(1, 0, 1, 0));
  __m512 S9 = _mm512_shuffle_ps(T8, T10, _MM_SHUFFLE(3, 2, 3, 2));
  __m512 S10 = _mm512_shuffle_ps(T9, T11, _MM_SHUFFLE(1, 0, 1, 0));
  __m512 S11 = _mm512_shuffle_ps(T9, T11, _MM_SHUFFLE(3, 2, 3, 2));
  __m512 S12 = _mm512_shuffle_ps(T12, T14, _MM_SHUFFLE(1, 0, 1, 0));
  __m512 S13 = _mm512_shuffle_ps(T12, T14, _MM_SHUFFLE(3, 2, 3, 2));
  __m512 S14 = _mm512_shuffle_ps(T13, T15, _MM_SHUFFLE(1, 0, 1, 0));
  __m512 S15 = _mm512_shuffle_ps(T13, T15, _MM_SHUFFLE(3, 2, 3, 2));

  EIGEN_EXTRACT_8f_FROM_16f(S0, S0);
  EIGEN_EXTRACT_8f_FROM_16f(S1, S1);
  EIGEN_EXTRACT_8f_FROM_16f(S2, S2);
  EIGEN_EXTRACT_8f_FROM_16f(S3, S3);
  EIGEN_EXTRACT_8f_FROM_16f(S4, S4);
  EIGEN_EXTRACT_8f_FROM_16f(S5, S5);
  EIGEN_EXTRACT_8f_FROM_16f(S6, S6);
  EIGEN_EXTRACT_8f_FROM_16f(S7, S7);
  EIGEN_EXTRACT_8f_FROM_16f(S8, S8);
  EIGEN_EXTRACT_8f_FROM_16f(S9, S9);
  EIGEN_EXTRACT_8f_FROM_16f(S10, S10);
  EIGEN_EXTRACT_8f_FROM_16f(S11, S11);
  EIGEN_EXTRACT_8f_FROM_16f(S12, S12);
  EIGEN_EXTRACT_8f_FROM_16f(S13, S13);
  EIGEN_EXTRACT_8f_FROM_16f(S14, S14);
  EIGEN_EXTRACT_8f_FROM_16f(S15, S15);

  PacketBlock<Packet8f, 32> tmp;

  tmp.packet[0] = _mm256_permute2f128_ps(S0_0, S4_0, 0x20);
  tmp.packet[1] = _mm256_permute2f128_ps(S1_0, S5_0, 0x20);
  tmp.packet[2] = _mm256_permute2f128_ps(S2_0, S6_0, 0x20);
  tmp.packet[3] = _mm256_permute2f128_ps(S3_0, S7_0, 0x20);
  tmp.packet[4] = _mm256_permute2f128_ps(S0_0, S4_0, 0x31);
  tmp.packet[5] = _mm256_permute2f128_ps(S1_0, S5_0, 0x31);
  tmp.packet[6] = _mm256_permute2f128_ps(S2_0, S6_0, 0x31);
  tmp.packet[7] = _mm256_permute2f128_ps(S3_0, S7_0, 0x31);

  tmp.packet[8] = _mm256_permute2f128_ps(S0_1, S4_1, 0x20);
  tmp.packet[9] = _mm256_permute2f128_ps(S1_1, S5_1, 0x20);
  tmp.packet[10] = _mm256_permute2f128_ps(S2_1, S6_1, 0x20);
  tmp.packet[11] = _mm256_permute2f128_ps(S3_1, S7_1, 0x20);
  tmp.packet[12] = _mm256_permute2f128_ps(S0_1, S4_1, 0x31);
  tmp.packet[13] = _mm256_permute2f128_ps(S1_1, S5_1, 0x31);
  tmp.packet[14] = _mm256_permute2f128_ps(S2_1, S6_1, 0x31);
  tmp.packet[15] = _mm256_permute2f128_ps(S3_1, S7_1, 0x31);

  // Second set of _m256 outputs
  tmp.packet[16] = _mm256_permute2f128_ps(S8_0, S12_0, 0x20);
  tmp.packet[17] = _mm256_permute2f128_ps(S9_0, S13_0, 0x20);
  tmp.packet[18] = _mm256_permute2f128_ps(S10_0, S14_0, 0x20);
  tmp.packet[19] = _mm256_permute2f128_ps(S11_0, S15_0, 0x20);
  tmp.packet[20] = _mm256_permute2f128_ps(S8_0, S12_0, 0x31);
  tmp.packet[21] = _mm256_permute2f128_ps(S9_0, S13_0, 0x31);
  tmp.packet[22] = _mm256_permute2f128_ps(S10_0, S14_0, 0x31);
  tmp.packet[23] = _mm256_permute2f128_ps(S11_0, S15_0, 0x31);

  tmp.packet[24] = _mm256_permute2f128_ps(S8_1, S12_1, 0x20);
  tmp.packet[25] = _mm256_permute2f128_ps(S9_1, S13_1, 0x20);
  tmp.packet[26] = _mm256_permute2f128_ps(S10_1, S14_1, 0x20);
  tmp.packet[27] = _mm256_permute2f128_ps(S11_1, S15_1, 0x20);
  tmp.packet[28] = _mm256_permute2f128_ps(S8_1, S12_1, 0x31);
  tmp.packet[29] = _mm256_permute2f128_ps(S9_1, S13_1, 0x31);
  tmp.packet[30] = _mm256_permute2f128_ps(S10_1, S14_1, 0x31);
  tmp.packet[31] = _mm256_permute2f128_ps(S11_1, S15_1, 0x31);

  // Pack them into the output
  PACK_OUTPUT(kernel.packet, tmp.packet, 0, 16);
  PACK_OUTPUT(kernel.packet, tmp.packet, 1, 16);
  PACK_OUTPUT(kernel.packet, tmp.packet, 2, 16);
  PACK_OUTPUT(kernel.packet, tmp.packet, 3, 16);

  PACK_OUTPUT(kernel.packet, tmp.packet, 4, 16);
  PACK_OUTPUT(kernel.packet, tmp.packet, 5, 16);
  PACK_OUTPUT(kernel.packet, tmp.packet, 6, 16);
  PACK_OUTPUT(kernel.packet, tmp.packet, 7, 16);

  PACK_OUTPUT(kernel.packet, tmp.packet, 8, 16);
  PACK_OUTPUT(kernel.packet, tmp.packet, 9, 16);
  PACK_OUTPUT(kernel.packet, tmp.packet, 10, 16);
  PACK_OUTPUT(kernel.packet, tmp.packet, 11, 16);

  PACK_OUTPUT(kernel.packet, tmp.packet, 12, 16);
  PACK_OUTPUT(kernel.packet, tmp.packet, 13, 16);
  PACK_OUTPUT(kernel.packet, tmp.packet, 14, 16);
  PACK_OUTPUT(kernel.packet, tmp.packet, 15, 16);
}
#define PACK_OUTPUT_2(OUTPUT, INPUT, INDEX, STRIDE) \
  EIGEN_INSERT_8f_INTO_16f(OUTPUT[INDEX], INPUT[2 * INDEX], INPUT[2 * INDEX + STRIDE]);

EIGEN_DEVICE_FUNC inline void ptranspose_old(PacketBlock<Packet16f, 8>& kernel) {
  __m512 T0 = _mm512_unpacklo_ps(kernel.packet[0], kernel.packet[1]);
  __m512 T1 = _mm512_unpackhi_ps(kernel.packet[0], kernel.packet[1]);
  __m512 T2 = _mm512_unpacklo_ps(kernel.packet[2], kernel.packet[3]);
  __m512 T3 = _mm512_unpackhi_ps(kernel.packet[2], kernel.packet[3]);
  __m512 T4 = _mm512_unpacklo_ps(kernel.packet[4], kernel.packet[5]);
  __m512 T5 = _mm512_unpackhi_ps(kernel.packet[4], kernel.packet[5]);
  __m512 T6 = _mm512_unpacklo_ps(kernel.packet[6], kernel.packet[7]);
  __m512 T7 = _mm512_unpackhi_ps(kernel.packet[6], kernel.packet[7]);

  kernel.packet[0] = _mm512_castpd_ps(_mm512_unpacklo_pd(_mm512_castps_pd(T0), _mm512_castps_pd(T2)));
  kernel.packet[1] = _mm512_castpd_ps(_mm512_unpackhi_pd(_mm512_castps_pd(T0), _mm512_castps_pd(T2)));
  kernel.packet[2] = _mm512_castpd_ps(_mm512_unpacklo_pd(_mm512_castps_pd(T1), _mm512_castps_pd(T3)));
  kernel.packet[3] = _mm512_castpd_ps(_mm512_unpackhi_pd(_mm512_castps_pd(T1), _mm512_castps_pd(T3)));
  kernel.packet[4] = _mm512_castpd_ps(_mm512_unpacklo_pd(_mm512_castps_pd(T4), _mm512_castps_pd(T6)));
  kernel.packet[5] = _mm512_castpd_ps(_mm512_unpackhi_pd(_mm512_castps_pd(T4), _mm512_castps_pd(T6)));
  kernel.packet[6] = _mm512_castpd_ps(_mm512_unpacklo_pd(_mm512_castps_pd(T5), _mm512_castps_pd(T7)));
  kernel.packet[7] = _mm512_castpd_ps(_mm512_unpackhi_pd(_mm512_castps_pd(T5), _mm512_castps_pd(T7)));

  T0 = _mm512_castpd_ps(_mm512_permutex_pd(_mm512_castps_pd(kernel.packet[4]), 0x4E));
  T0 = _mm512_mask_blend_ps(0xF0F0, kernel.packet[0], T0);
  T4 = _mm512_castpd_ps(_mm512_permutex_pd(_mm512_castps_pd(kernel.packet[0]), 0x4E));
  T4 = _mm512_mask_blend_ps(0xF0F0, T4, kernel.packet[4]);
  T1 = _mm512_castpd_ps(_mm512_permutex_pd(_mm512_castps_pd(kernel.packet[5]), 0x4E));
  T1 = _mm512_mask_blend_ps(0xF0F0, kernel.packet[1], T1);
  T5 = _mm512_castpd_ps(_mm512_permutex_pd(_mm512_castps_pd(kernel.packet[1]), 0x4E));
  T5 = _mm512_mask_blend_ps(0xF0F0, T5, kernel.packet[5]);
  T2 = _mm512_castpd_ps(_mm512_permutex_pd(_mm512_castps_pd(kernel.packet[6]), 0x4E));
  T2 = _mm512_mask_blend_ps(0xF0F0, kernel.packet[2], T2);
  T6 = _mm512_castpd_ps(_mm512_permutex_pd(_mm512_castps_pd(kernel.packet[2]), 0x4E));
  T6 = _mm512_mask_blend_ps(0xF0F0, T6, kernel.packet[6]);
  T3 = _mm512_castpd_ps(_mm512_permutex_pd(_mm512_castps_pd(kernel.packet[7]), 0x4E));
  T3 = _mm512_mask_blend_ps(0xF0F0, kernel.packet[3], T3);
  T7 = _mm512_castpd_ps(_mm512_permutex_pd(_mm512_castps_pd(kernel.packet[3]), 0x4E));
  T7 = _mm512_mask_blend_ps(0xF0F0, T7, kernel.packet[7]);

  kernel.packet[0] = T0;
  kernel.packet[1] = T1;
  kernel.packet[2] = T2;
  kernel.packet[3] = T3;
  kernel.packet[4] = T4;
  kernel.packet[5] = T5;
  kernel.packet[6] = T6;
  kernel.packet[7] = T7;
}

EIGEN_DEVICE_FUNC inline void ptranspose_old(PacketBlock<Packet16f, 4>& kernel) {
  __m512 T0 = _mm512_unpacklo_ps(kernel.packet[0], kernel.packet[1]);
  __m512 T1 = _mm512_unpackhi_ps(kernel.packet[0], kernel.packet[1]);
  __m512 T2 = _mm512_unpacklo_ps(kernel.packet[2], kernel.packet[3]);
  __m512 T3 = _mm512_unpackhi_ps(kernel.packet[2], kernel.packet[3]);

  __m512 S0 = _mm512_shuffle_ps(T0, T2, _MM_SHUFFLE(1, 0, 1, 0));
  __m512 S1 = _mm512_shuffle_ps(T0, T2, _MM_SHUFFLE(3, 2, 3, 2));
  __m512 S2 = _mm512_shuffle_ps(T1, T3, _MM_SHUFFLE(1, 0, 1, 0));
  __m512 S3 = _mm512_shuffle_ps(T1, T3, _MM_SHUFFLE(3, 2, 3, 2));

  EIGEN_EXTRACT_8f_FROM_16f(S0, S0);
  EIGEN_EXTRACT_8f_FROM_16f(S1, S1);
  EIGEN_EXTRACT_8f_FROM_16f(S2, S2);
  EIGEN_EXTRACT_8f_FROM_16f(S3, S3);

  PacketBlock<Packet8f, 8> tmp;

  tmp.packet[0] = _mm256_permute2f128_ps(S0_0, S1_0, 0x20);
  tmp.packet[1] = _mm256_permute2f128_ps(S2_0, S3_0, 0x20);
  tmp.packet[2] = _mm256_permute2f128_ps(S0_0, S1_0, 0x31);
  tmp.packet[3] = _mm256_permute2f128_ps(S2_0, S3_0, 0x31);

  tmp.packet[4] = _mm256_permute2f128_ps(S0_1, S1_1, 0x20);
  tmp.packet[5] = _mm256_permute2f128_ps(S2_1, S3_1, 0x20);
  tmp.packet[6] = _mm256_permute2f128_ps(S0_1, S1_1, 0x31);
  tmp.packet[7] = _mm256_permute2f128_ps(S2_1, S3_1, 0x31);

  PACK_OUTPUT_2(kernel.packet, tmp.packet, 0, 1);
  PACK_OUTPUT_2(kernel.packet, tmp.packet, 1, 1);
  PACK_OUTPUT_2(kernel.packet, tmp.packet, 2, 1);
  PACK_OUTPUT_2(kernel.packet, tmp.packet, 3, 1);
}

#define PACK_OUTPUT_SQ_D(OUTPUT, INPUT, INDEX, STRIDE)                \
  OUTPUT[INDEX] = _mm512_insertf64x4(OUTPUT[INDEX], INPUT[INDEX], 0); \
  OUTPUT[INDEX] = _mm512_insertf64x4(OUTPUT[INDEX], INPUT[INDEX + STRIDE], 1);

#define PACK_OUTPUT_D(OUTPUT, INPUT, INDEX, STRIDE)                         \
  OUTPUT[INDEX] = _mm512_insertf64x4(OUTPUT[INDEX], INPUT[(2 * INDEX)], 0); \
  OUTPUT[INDEX] = _mm512_insertf64x4(OUTPUT[INDEX], INPUT[(2 * INDEX) + STRIDE], 1);

EIGEN_DEVICE_FUNC inline void ptranspose_old(PacketBlock<Packet8d, 4>& kernel) {
  __m512d T0 = _mm512_shuffle_pd(kernel.packet[0], kernel.packet[1], 0);
  __m512d T1 = _mm512_shuffle_pd(kernel.packet[0], kernel.packet[1], 0xff);
  __m512d T2 = _mm512_shuffle_pd(kernel.packet[2], kernel.packet[3], 0);
  __m512d T3 = _mm512_shuffle_pd(kernel.packet[2], kernel.packet[3], 0xff);

  PacketBlock<Packet4d, 8> tmp;

  tmp.packet[0] = _mm256_permute2f128_pd(_mm512_extractf64x4_pd(T0, 0), _mm512_extractf64x4_pd(T2, 0), 0x20);
  tmp.packet[1] = _mm256_permute2f128_pd(_mm512_extractf64x4_pd(T1, 0), _mm512_extractf64x4_pd(T3, 0), 0x20);
  tmp.packet[2] = _mm256_permute2f128_pd(_mm512_extractf64x4_pd(T0, 0), _mm512_extractf64x4_pd(T2, 0), 0x31);
  tmp.packet[3] = _mm256_permute2f128_pd(_mm512_extractf64x4_pd(T1, 0), _mm512_extractf64x4_pd(T3, 0), 0x31);

  tmp.packet[4] = _mm256_permute2f128_pd(_mm512_extractf64x4_pd(T0, 1), _mm512_extractf64x4_pd(T2, 1), 0x20);
  tmp.packet[5] = _mm256_permute2f128_pd(_mm512_extractf64x4_pd(T1, 1), _mm512_extractf64x4_pd(T3, 1), 0x20);
  tmp.packet[6] = _mm256_permute2f128_pd(_mm512_extractf64x4_pd(T0, 1), _mm512_extractf64x4_pd(T2, 1), 0x31);
  tmp.packet[7] = _mm256_permute2f128_pd(_mm512_extractf64x4_pd(T1, 1), _mm512_extractf64x4_pd(T3, 1), 0x31);

  PACK_OUTPUT_D(kernel.packet, tmp.packet, 0, 1);
  PACK_OUTPUT_D(kernel.packet, tmp.packet, 1, 1);
  PACK_OUTPUT_D(kernel.packet, tmp.packet, 2, 1);
  PACK_OUTPUT_D(kernel.packet, tmp.packet, 3, 1);
}

EIGEN_DEVICE_FUNC inline void ptranspose_old(PacketBlock<Packet8d, 8>& kernel) {
  __m512d T0 = _mm512_unpacklo_pd(kernel.packet[0], kernel.packet[1]);
  __m512d T1 = _mm512_unpackhi_pd(kernel.packet[0], kernel.packet[1]);
  __m512d T2 = _mm512_unpacklo_pd(kernel.packet[2], kernel.packet[3]);
  __m512d T3 = _mm512_unpackhi_pd(kernel.packet[2], kernel.packet[3]);
  __m512d T4 = _mm512_unpacklo_pd(kernel.packet[4], kernel.packet[5]);
  __m512d T5 = _mm512_unpackhi_pd(kernel.packet[4], kernel.packet[5]);
  __m512d T6 = _mm512_unpacklo_pd(kernel.packet[6], kernel.packet[7]);
  __m512d T7 = _mm512_unpackhi_pd(kernel.packet[6], kernel.packet[7]);

  kernel.packet[0] = _mm512_permutex_pd(T2, 0x4E);
  kernel.packet[0] = _mm512_mask_blend_pd(0xCC, T0, kernel.packet[0]);
  kernel.packet[2] = _mm512_permutex_pd(T0, 0x4E);
  kernel.packet[2] = _mm512_mask_blend_pd(0xCC, kernel.packet[2], T2);
  kernel.packet[1] = _mm512_permutex_pd(T3, 0x4E);
  kernel.packet[1] = _mm512_mask_blend_pd(0xCC, T1, kernel.packet[1]);
  kernel.packet[3] = _mm512_permutex_pd(T1, 0x4E);
  kernel.packet[3] = _mm512_mask_blend_pd(0xCC, kernel.packet[3], T3);
  kernel.packet[4] = _mm512_permutex_pd(T6, 0x4E);
  kernel.packet[4] = _mm512_mask_blend_pd(0xCC, T4, kernel.packet[4]);
  kernel.packet[6] = _mm512_permutex_pd(T4, 0x4E);
  kernel.packet[6] = _mm512_mask_blend_pd(0xCC, kernel.packet[6], T6);
  kernel.packet[5] = _mm512_permutex_pd(T7, 0x4E);
  kernel.packet[5] = _mm512_mask_blend_pd(0xCC, T5, kernel.packet[5]);
  kernel.packet[7] = _mm512_permutex_pd(T5, 0x4E);
  kernel.packet[7] = _mm512_mask_blend_pd(0xCC, kernel.packet[7], T7);

  T0 = _mm512_shuffle_f64x2(kernel.packet[4], kernel.packet[4], 0x4E);
  T0 = _mm512_mask_blend_pd(0xF0, kernel.packet[0], T0);
  T4 = _mm512_shuffle_f64x2(kernel.packet[0], kernel.packet[0], 0x4E);
  T4 = _mm512_mask_blend_pd(0xF0, T4, kernel.packet[4]);
  T1 = _mm512_shuffle_f64x2(kernel.packet[5], kernel.packet[5], 0x4E);
  T1 = _mm512_mask_blend_pd(0xF0, kernel.packet[1], T1);
  T5 = _mm512_shuffle_f64x2(kernel.packet[1], kernel.packet[1], 0x4E);
  T5 = _mm512_mask_blend_pd(0xF0, T5, kernel.packet[5]);
  T2 = _mm512_shuffle_f64x2(kernel.packet[6], kernel.packet[6], 0x4E);
  T2 = _mm512_mask_blend_pd(0xF0, kernel.packet[2], T2);
  T6 = _mm512_shuffle_f64x2(kernel.packet[2], kernel.packet[2], 0x4E);
  T6 = _mm512_mask_blend_pd(0xF0, T6, kernel.packet[6]);
  T3 = _mm512_shuffle_f64x2(kernel.packet[7], kernel.packet[7], 0x4E);
  T3 = _mm512_mask_blend_pd(0xF0, kernel.packet[3], T3);
  T7 = _mm512_shuffle_f64x2(kernel.packet[3], kernel.packet[3], 0x4E);
  T7 = _mm512_mask_blend_pd(0xF0, T7, kernel.packet[7]);

  kernel.packet[0] = T0;
  kernel.packet[1] = T1;
  kernel.packet[2] = T2;
  kernel.packet[3] = T3;
  kernel.packet[4] = T4;
  kernel.packet[5] = T5;
  kernel.packet[6] = T6;
  kernel.packet[7] = T7;
}

EIGEN_DEVICE_FUNC inline void ptranspose_old(PacketBlock<Packet16i, 16>& kernel) {
  __m512i T0 = _mm512_unpacklo_epi32(kernel.packet[0], kernel.packet[1]);
  __m512i T1 = _mm512_unpackhi_epi32(kernel.packet[0], kernel.packet[1]);
  __m512i T2 = _mm512_unpacklo_epi32(kernel.packet[2], kernel.packet[3]);
  __m512i T3 = _mm512_unpackhi_epi32(kernel.packet[2], kernel.packet[3]);
  __m512i T4 = _mm512_unpacklo_epi32(kernel.packet[4], kernel.packet[5]);
  __m512i T5 = _mm512_unpackhi_epi32(kernel.packet[4], kernel.packet[5]);
  __m512i T6 = _mm512_unpacklo_epi32(kernel.packet[6], kernel.packet[7]);
  __m512i T7 = _mm512_unpackhi_epi32(kernel.packet[6], kernel.packet[7]);
  __m512i T8 = _mm512_unpacklo_epi32(kernel.packet[8], kernel.packet[9]);
  __m512i T9 = _mm512_unpackhi_epi32(kernel.packet[8], kernel.packet[9]);
  __m512i T10 = _mm512_unpacklo_epi32(kernel.packet[10], kernel.packet[11]);
  __m512i T11 = _mm512_unpackhi_epi32(kernel.packet[10], kernel.packet[11]);
  __m512i T12 = _mm512_unpacklo_epi32(kernel.packet[12], kernel.packet[13]);
  __m512i T13 = _mm512_unpackhi_epi32(kernel.packet[12], kernel.packet[13]);
  __m512i T14 = _mm512_unpacklo_epi32(kernel.packet[14], kernel.packet[15]);
  __m512i T15 = _mm512_unpackhi_epi32(kernel.packet[14], kernel.packet[15]);
  __m512i S0 = SHUFFLE_EPI32(T0, T2, _MM_SHUFFLE(1, 0, 1, 0));
  __m512i S1 = SHUFFLE_EPI32(T0, T2, _MM_SHUFFLE(3, 2, 3, 2));
  __m512i S2 = SHUFFLE_EPI32(T1, T3, _MM_SHUFFLE(1, 0, 1, 0));
  __m512i S3 = SHUFFLE_EPI32(T1, T3, _MM_SHUFFLE(3, 2, 3, 2));
  __m512i S4 = SHUFFLE_EPI32(T4, T6, _MM_SHUFFLE(1, 0, 1, 0));
  __m512i S5 = SHUFFLE_EPI32(T4, T6, _MM_SHUFFLE(3, 2, 3, 2));
  __m512i S6 = SHUFFLE_EPI32(T5, T7, _MM_SHUFFLE(1, 0, 1, 0));
  __m512i S7 = SHUFFLE_EPI32(T5, T7, _MM_SHUFFLE(3, 2, 3, 2));
  __m512i S8 = SHUFFLE_EPI32(T8, T10, _MM_SHUFFLE(1, 0, 1, 0));
  __m512i S9 = SHUFFLE_EPI32(T8, T10, _MM_SHUFFLE(3, 2, 3, 2));
  __m512i S10 = SHUFFLE_EPI32(T9, T11, _MM_SHUFFLE(1, 0, 1, 0));
  __m512i S11 = SHUFFLE_EPI32(T9, T11, _MM_SHUFFLE(3, 2, 3, 2));
  __m512i S12 = SHUFFLE_EPI32(T12, T14, _MM_SHUFFLE(1, 0, 1, 0));
  __m512i S13 = SHUFFLE_EPI32(T12, T14, _MM_SHUFFLE(3, 2, 3, 2));
  __m512i S14 = SHUFFLE_EPI32(T13, T15, _MM_SHUFFLE(1, 0, 1, 0));
  __m512i S15 = SHUFFLE_EPI32(T13, T15, _MM_SHUFFLE(3, 2, 3, 2));

  EIGEN_EXTRACT_8i_FROM_16i(S0, S0);
  EIGEN_EXTRACT_8i_FROM_16i(S1, S1);
  EIGEN_EXTRACT_8i_FROM_16i(S2, S2);
  EIGEN_EXTRACT_8i_FROM_16i(S3, S3);
  EIGEN_EXTRACT_8i_FROM_16i(S4, S4);
  EIGEN_EXTRACT_8i_FROM_16i(S5, S5);
  EIGEN_EXTRACT_8i_FROM_16i(S6, S6);
  EIGEN_EXTRACT_8i_FROM_16i(S7, S7);
  EIGEN_EXTRACT_8i_FROM_16i(S8, S8);
  EIGEN_EXTRACT_8i_FROM_16i(S9, S9);
  EIGEN_EXTRACT_8i_FROM_16i(S10, S10);
  EIGEN_EXTRACT_8i_FROM_16i(S11, S11);
  EIGEN_EXTRACT_8i_FROM_16i(S12, S12);
  EIGEN_EXTRACT_8i_FROM_16i(S13, S13);
  EIGEN_EXTRACT_8i_FROM_16i(S14, S14);
  EIGEN_EXTRACT_8i_FROM_16i(S15, S15);

  PacketBlock<Packet8i, 32> tmp;

  tmp.packet[0] = _mm256_permute2f128_si256(S0_0, S4_0, 0x20);
  tmp.packet[1] = _mm256_permute2f128_si256(S1_0, S5_0, 0x20);
  tmp.packet[2] = _mm256_permute2f128_si256(S2_0, S6_0, 0x20);
  tmp.packet[3] = _mm256_permute2f128_si256(S3_0, S7_0, 0x20);
  tmp.packet[4] = _mm256_permute2f128_si256(S0_0, S4_0, 0x31);
  tmp.packet[5] = _mm256_permute2f128_si256(S1_0, S5_0, 0x31);
  tmp.packet[6] = _mm256_permute2f128_si256(S2_0, S6_0, 0x31);
  tmp.packet[7] = _mm256_permute2f128_si256(S3_0, S7_0, 0x31);

  tmp.packet[8] = _mm256_permute2f128_si256(S0_1, S4_1, 0x20);
  tmp.packet[9] = _mm256_permute2f128_si256(S1_1, S5_1, 0x20);
  tmp.packet[10] = _mm256_permute2f128_si256(S2_1, S6_1, 0x20);
  tmp.packet[11] = _mm256_permute2f128_si256(S3_1, S7_1, 0x20);
  tmp.packet[12] = _mm256_permute2f128_si256(S0_1, S4_1, 0x31);
  tmp.packet[13] = _mm256_permute2f128_si256(S1_1, S5_1, 0x31);
  tmp.packet[14] = _mm256_permute2f128_si256(S2_1, S6_1, 0x31);
  tmp.packet[15] = _mm256_permute2f128_si256(S3_1, S7_1, 0x31);

  // Second set of _m256 outputs
  tmp.packet[16] = _mm256_permute2f128_si256(S8_0, S12_0, 0x20);
  tmp.packet[17] = _mm256_permute2f128_si256(S9_0, S13_0, 0x20);
  tmp.packet[18] = _mm256_permute2f128_si256(S10_0, S14_0, 0x20);
  tmp.packet[19] = _mm256_permute2f128_si256(S11_0, S15_0, 0x20);
  tmp.packet[20] = _mm256_permute2f128_si256(S8_0, S12_0, 0x31);
  tmp.packet[21] = _mm256_permute2f128_si256(S9_0, S13_0, 0x31);
  tmp.packet[22] = _mm256_permute2f128_si256(S10_0, S14_0, 0x31);
  tmp.packet[23] = _mm256_permute2f128_si256(S11_0, S15_0, 0x31);

  tmp.packet[24] = _mm256_permute2f128_si256(S8_1, S12_1, 0x20);
  tmp.packet[25] = _mm256_permute2f128_si256(S9_1, S13_1, 0x20);
  tmp.packet[26] = _mm256_permute2f128_si256(S10_1, S14_1, 0x20);
  tmp.packet[27] = _mm256_permute2f128_si256(S11_1, S15_1, 0x20);
  tmp.packet[28] = _mm256_permute2f128_si256(S8_1, S12_1, 0x31);
  tmp.packet[29] = _mm256_permute2f128_si256(S9_1, S13_1, 0x31);
  tmp.packet[30] = _mm256_permute2f128_si256(S10_1, S14_1, 0x31);
  tmp.packet[31] = _mm256_permute2f128_si256(S11_1, S15_1, 0x31);

  // Pack them into the output
  PACK_OUTPUT_I32(kernel.packet, tmp.packet, 0, 16);
  PACK_OUTPUT_I32(kernel.packet, tmp.packet, 1, 16);
  PACK_OUTPUT_I32(kernel.packet, tmp.packet, 2, 16);
  PACK_OUTPUT_I32(kernel.packet, tmp.packet, 3, 16);

  PACK_OUTPUT_I32(kernel.packet, tmp.packet, 4, 16);
  PACK_OUTPUT_I32(kernel.packet, tmp.packet, 5, 16);
  PACK_OUTPUT_I32(kernel.packet, tmp.packet, 6, 16);
  PACK_OUTPUT_I32(kernel.packet, tmp.packet, 7, 16);

  PACK_OUTPUT_I32(kernel.packet, tmp.packet, 8, 16);
  PACK_OUTPUT_I32(kernel.packet, tmp.packet, 9, 16);
  PACK_OUTPUT_I32(kernel.packet, tmp.packet, 10, 16);
  PACK_OUTPUT_I32(kernel.packet, tmp.packet, 11, 16);

  PACK_OUTPUT_I32(kernel.packet, tmp.packet, 12, 16);
  PACK_OUTPUT_I32(kernel.packet, tmp.packet, 13, 16);
  PACK_OUTPUT_I32(kernel.packet, tmp.packet, 14, 16);
  PACK_OUTPUT_I32(kernel.packet, tmp.packet, 15, 16);
}

EIGEN_DEVICE_FUNC inline void ptranspose_old(PacketBlock<Packet16i, 4>& kernel) {
  __m512i T0 = _mm512_unpacklo_epi32(kernel.packet[0], kernel.packet[1]);
  __m512i T1 = _mm512_unpackhi_epi32(kernel.packet[0], kernel.packet[1]);
  __m512i T2 = _mm512_unpacklo_epi32(kernel.packet[2], kernel.packet[3]);
  __m512i T3 = _mm512_unpackhi_epi32(kernel.packet[2], kernel.packet[3]);

  __m512i S0 = SHUFFLE_EPI32(T0, T2, _MM_SHUFFLE(1, 0, 1, 0));
  __m512i S1 = SHUFFLE_EPI32(T0, T2, _MM_SHUFFLE(3, 2, 3, 2));
  __m512i S2 = SHUFFLE_EPI32(T1, T3, _MM_SHUFFLE(1, 0, 1, 0));
  __m512i S3 = SHUFFLE_EPI32(T1, T3, _MM_SHUFFLE(3, 2, 3, 2));

  EIGEN_EXTRACT_8i_FROM_16i(S0, S0);
  EIGEN_EXTRACT_8i_FROM_16i(S1, S1);
  EIGEN_EXTRACT_8i_FROM_16i(S2, S2);
  EIGEN_EXTRACT_8i_FROM_16i(S3, S3);

  PacketBlock<Packet8i, 8> tmp;

  tmp.packet[0] = _mm256_permute2f128_si256(S0_0, S1_0, 0x20);
  tmp.packet[1] = _mm256_permute2f128_si256(S2_0, S3_0, 0x20);
  tmp.packet[2] = _mm256_permute2f128_si256(S0_0, S1_0, 0x31);
  tmp.packet[3] = _mm256_permute2f128_si256(S2_0, S3_0, 0x31);

  tmp.packet[4] = _mm256_permute2f128_si256(S0_1, S1_1, 0x20);
  tmp.packet[5] = _mm256_permute2f128_si256(S2_1, S3_1, 0x20);
  tmp.packet[6] = _mm256_permute2f128_si256(S0_1, S1_1, 0x31);
  tmp.packet[7] = _mm256_permute2f128_si256(S2_1, S3_1, 0x31);

  PACK_OUTPUT_I32_2(kernel.packet, tmp.packet, 0, 1);
  PACK_OUTPUT_I32_2(kernel.packet, tmp.packet, 1, 1);
  PACK_OUTPUT_I32_2(kernel.packet, tmp.packet, 2, 1);
  PACK_OUTPUT_I32_2(kernel.packet, tmp.packet, 3, 1);
}

template <>
EIGEN_STRONG_INLINE Packet16f pblend_old(const Selector<16>& /*ifPacket*/, const Packet16f& /*thenPacket*/,
                                     const Packet16f& /*elsePacket*/) {
  assert(false && "To be implemented");
  return Packet16f();
}
template <>
EIGEN_STRONG_INLINE Packet8d pblend_old(const Selector<8>& ifPacket, const Packet8d& thenPacket,
                                    const Packet8d& elsePacket) {
  __mmask8 m = (ifPacket.select[0]) | (ifPacket.select[1] << 1) | (ifPacket.select[2] << 2) |
               (ifPacket.select[3] << 3) | (ifPacket.select[4] << 4) | (ifPacket.select[5] << 5) |
               (ifPacket.select[6] << 6) | (ifPacket.select[7] << 7);
  return _mm512_mask_blend_pd(m, elsePacket, thenPacket);
}

// Packet math for Eigen::half
template <>
EIGEN_STRONG_INLINE Packet16h pset1_old<Packet16h>(const Eigen::half& from) {
  return _mm256_set1_epi16(from.x);
}

template <>
EIGEN_STRONG_INLINE Eigen::half pfirst_old<Packet16h>(const Packet16h& from) {
  return half_impl::raw_uint16_to_half(static_cast<unsigned short>(_mm256_extract_epi16(from, 0)));
}

template <>
EIGEN_STRONG_INLINE Packet16h pload_old<Packet16h>(const Eigen::half* from) {
  return _mm256_load_si256(reinterpret_cast<const __m256i*>(from));
}

template <>
EIGEN_STRONG_INLINE Packet16h ploadu_old<Packet16h>(const Eigen::half* from) {
  return _mm256_loadu_si256(reinterpret_cast<const __m256i*>(from));
}

template <>
EIGEN_STRONG_INLINE void pstore_old<half>(Eigen::half* to, const Packet16h& from) {
  // (void*) -> workaround clang warning:
  // cast from 'Eigen::half *' to '__m256i *' increases required alignment from 2 to 32
  _mm256_store_si256((__m256i*)(void*)to, from);
}

template <>
EIGEN_STRONG_INLINE void pstoreu_old<half>(Eigen::half* to, const Packet16h& from) {
  // (void*) -> workaround clang warning:
  // cast from 'Eigen::half *' to '__m256i *' increases required alignment from 2 to 32
  _mm256_storeu_si256((__m256i*)(void*)to, from);
}

template <>
EIGEN_STRONG_INLINE Packet16h ploaddup_old<Packet16h>(const Eigen::half* from) {
  unsigned short a = from[0].x;
  unsigned short b = from[1].x;
  unsigned short c = from[2].x;
  unsigned short d = from[3].x;
  unsigned short e = from[4].x;
  unsigned short f = from[5].x;
  unsigned short g = from[6].x;
  unsigned short h = from[7].x;
  return _mm256_set_epi16(h, h, g, g, f, f, e, e, d, d, c, c, b, b, a, a);
}

template <>
EIGEN_STRONG_INLINE Packet16h ploadquad_old(const Eigen::half* from) {
  unsigned short a = from[0].x;
  unsigned short b = from[1].x;
  unsigned short c = from[2].x;
  unsigned short d = from[3].x;
  return _mm256_set_epi16(d, d, d, d, c, c, c, c, b, b, b, b, a, a, a, a);
}

EIGEN_STRONG_INLINE Packet16f half2float_old(const Packet16h& a) {
#ifdef EIGEN_HAS_FP16_C
  return _mm512_cvtph_ps(a);
#else
  EIGEN_ALIGN64 half aux[16];
  pstore_old(aux, a);
  float f0(aux[0]);
  float f1(aux[1]);
  float f2(aux[2]);
  float f3(aux[3]);
  float f4(aux[4]);
  float f5(aux[5]);
  float f6(aux[6]);
  float f7(aux[7]);
  float f8(aux[8]);
  float f9(aux[9]);
  float fa(aux[10]);
  float fb(aux[11]);
  float fc(aux[12]);
  float fd(aux[13]);
  float fe(aux[14]);
  float ff(aux[15]);

  return _mm512_set_ps(ff, fe, fd, fc, fb, fa, f9, f8, f7, f6, f5, f4, f3, f2, f1, f0);
#endif
}

EIGEN_STRONG_INLINE Packet16h float2half_old(const Packet16f& a) {
#ifdef EIGEN_HAS_FP16_C
  return _mm512_cvtps_ph(a, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC);
#else
  EIGEN_ALIGN64 float aux[16];
  pstore_old(aux, a);
  half h0(aux[0]);
  half h1(aux[1]);
  half h2(aux[2]);
  half h3(aux[3]);
  half h4(aux[4]);
  half h5(aux[5]);
  half h6(aux[6]);
  half h7(aux[7]);
  half h8(aux[8]);
  half h9(aux[9]);
  half ha(aux[10]);
  half hb(aux[11]);
  half hc(aux[12]);
  half hd(aux[13]);
  half he(aux[14]);
  half hf(aux[15]);

  return _mm256_set_epi16(hf.x, he.x, hd.x, hc.x, hb.x, ha.x, h9.x, h8.x, h7.x, h6.x, h5.x, h4.x, h3.x, h2.x, h1.x,
                          h0.x);
#endif
}

template <>
EIGEN_STRONG_INLINE Packet16h ptrue_old(const Packet16h& a) {
  return Packet16h(ptrue_old(Packet8i(a)));
}

template <>
EIGEN_STRONG_INLINE Packet16h pabs_old(const Packet16h& a) {
  const __m256i sign_mask = _mm256_set1_epi16(static_cast<numext::uint16_t>(0x8000));
  return _mm256_andnot_si256(sign_mask, a);
}

template <>
EIGEN_STRONG_INLINE Packet16h pmin_old<Packet16h>(const Packet16h& a, const Packet16h& b) {
  return float2half_old(pmin_old<Packet16f>(half2float_old(a), half2float_old(b)));
}

template <>
EIGEN_STRONG_INLINE Packet16h pmax_old<Packet16h>(const Packet16h& a, const Packet16h& b) {
  return float2half_old(pmax_old<Packet16f>(half2float_old(a), half2float_old(b)));
}

template <>
EIGEN_STRONG_INLINE Packet16h plset_old<Packet16h>(const half& a) {
  return float2half_old(plset_old<Packet16f>(static_cast<float>(a)));
}

template <>
EIGEN_STRONG_INLINE Packet16h por_old(const Packet16h& a, const Packet16h& b) {
  // in some cases Packet8i is a wrapper around __m256i, so we need to
  // cast to Packet8i to call the correct overload.
  return Packet16h(por_old(Packet8i(a), Packet8i(b)));
}
template <>
EIGEN_STRONG_INLINE Packet16h pxor_old(const Packet16h& a, const Packet16h& b) {
  return Packet16h(pxor_old(Packet8i(a), Packet8i(b)));
}
template <>
EIGEN_STRONG_INLINE Packet16h pand_old(const Packet16h& a, const Packet16h& b) {
  return Packet16h(pand_old(Packet8i(a), Packet8i(b)));
}
template <>
EIGEN_STRONG_INLINE Packet16h pandnot_old(const Packet16h& a, const Packet16h& b) {
  return Packet16h(pandnot_old(Packet8i(a), Packet8i(b)));
}

template <>
EIGEN_STRONG_INLINE Packet16h pselect_old(const Packet16h& mask, const Packet16h& a, const Packet16h& b) {
  return _mm256_blendv_epi8(b, a, mask);
}

template <>
EIGEN_STRONG_INLINE Packet16h pround_old<Packet16h>(const Packet16h& a) {
  return float2half_old(pround_old<Packet16f>(half2float_old(a)));
}

template <>
EIGEN_STRONG_INLINE Packet16h print_old<Packet16h>(const Packet16h& a) {
  return float2half_old(print_old<Packet16f>(half2float_old(a)));
}

template <>
EIGEN_STRONG_INLINE Packet16h pceil_old<Packet16h>(const Packet16h& a) {
  return float2half_old(pceil_old<Packet16f>(half2float_old(a)));
}

template <>
EIGEN_STRONG_INLINE Packet16h pfloor_old<Packet16h>(const Packet16h& a) {
  return float2half_old(pfloor_old<Packet16f>(half2float_old(a)));
}

template <>
EIGEN_STRONG_INLINE Packet16h pcmp_eq_old(const Packet16h& a, const Packet16h& b) {
  Packet16f af = half2float_old(a);
  Packet16f bf = half2float_old(b);
  return Pack32To16(pcmp_eq_old(af, bf));
}

template <>
EIGEN_STRONG_INLINE Packet16h pcmp_le_old(const Packet16h& a, const Packet16h& b) {
  return Pack32To16(pcmp_le_old(half2float_old(a), half2float_old(b)));
}

template <>
EIGEN_STRONG_INLINE Packet16h pcmp_lt_old(const Packet16h& a, const Packet16h& b) {
  return Pack32To16(pcmp_lt_old(half2float_old(a), half2float_old(b)));
}

template <>
EIGEN_STRONG_INLINE Packet16h pcmp_lt_or_nan_old(const Packet16h& a, const Packet16h& b) {
  return Pack32To16(pcmp_lt_or_nan_old(half2float_old(a), half2float_old(b)));
}

template <>
EIGEN_STRONG_INLINE Packet16h pconj_old(const Packet16h& a) {
  return a;
}

template <>
EIGEN_STRONG_INLINE Packet16h pnegate_old(const Packet16h& a) {
  Packet16h sign_mask = _mm256_set1_epi16(static_cast<unsigned short>(0x8000));
  return _mm256_xor_si256(a, sign_mask);
}

template <>
EIGEN_STRONG_INLINE Packet16h padd_old<Packet16h>(const Packet16h& a, const Packet16h& b) {
  Packet16f af = half2float_old(a);
  Packet16f bf = half2float_old(b);
  Packet16f rf = padd_old(af, bf);
  return float2half_old(rf);
}

template <>
EIGEN_STRONG_INLINE Packet16h psub_old<Packet16h>(const Packet16h& a, const Packet16h& b) {
  Packet16f af = half2float_old(a);
  Packet16f bf = half2float_old(b);
  Packet16f rf = psub_old(af, bf);
  return float2half_old(rf);
}

template <>
EIGEN_STRONG_INLINE Packet16h pmul_old<Packet16h>(const Packet16h& a, const Packet16h& b) {
  Packet16f af = half2float_old(a);
  Packet16f bf = half2float_old(b);
  Packet16f rf = pmul_old(af, bf);
  return float2half_old(rf);
}

template <>
EIGEN_STRONG_INLINE Packet16h pdiv_old<Packet16h>(const Packet16h& a, const Packet16h& b) {
  Packet16f af = half2float_old(a);
  Packet16f bf = half2float_old(b);
  Packet16f rf = pdiv_old(af, bf);
  return float2half_old(rf);
}

template <>
EIGEN_STRONG_INLINE half predux_old<Packet16h>(const Packet16h& from) {
  Packet16f from_float = half2float_old(from);
  return half(predux_old(from_float));
}

template <>
EIGEN_STRONG_INLINE Packet8h predux_half_dowto4_old<Packet16h>(const Packet16h& a) {
  Packet8h lane0 = _mm256_extractf128_si256(a, 0);
  Packet8h lane1 = _mm256_extractf128_si256(a, 1);
  return padd_old<Packet8h>(lane0, lane1);
}

template <>
EIGEN_STRONG_INLINE Eigen::half predux_max_old<Packet16h>(const Packet16h& a) {
  Packet16f af = half2float_old(a);
  float reduced = predux_max_old<Packet16f>(af);
  return Eigen::half(reduced);
}

template <>
EIGEN_STRONG_INLINE Eigen::half predux_min_old<Packet16h>(const Packet16h& a) {
  Packet16f af = half2float_old(a);
  float reduced = predux_min_old<Packet16f>(af);
  return Eigen::half(reduced);
}

template <>
EIGEN_STRONG_INLINE half predux_mul_old<Packet16h>(const Packet16h& from) {
  Packet16f from_float = half2float_old(from);
  return half(predux_mul_old(from_float));
}

template <>
EIGEN_STRONG_INLINE Packet16h preverse_old(const Packet16h& a) {
  __m128i m = _mm_setr_epi8(14, 15, 12, 13, 10, 11, 8, 9, 6, 7, 4, 5, 2, 3, 0, 1);
  return _mm256_insertf128_si256(_mm256_castsi128_si256(_mm_shuffle_epi8(_mm256_extractf128_si256(a, 1), m)),
                                 _mm_shuffle_epi8(_mm256_extractf128_si256(a, 0), m), 1);
}

template <>
EIGEN_STRONG_INLINE Packet16h pgather_old<Eigen::half, Packet16h>(const Eigen::half* from, Index stride) {
  return _mm256_set_epi16(from[15 * stride].x, from[14 * stride].x, from[13 * stride].x, from[12 * stride].x,
                          from[11 * stride].x, from[10 * stride].x, from[9 * stride].x, from[8 * stride].x,
                          from[7 * stride].x, from[6 * stride].x, from[5 * stride].x, from[4 * stride].x,
                          from[3 * stride].x, from[2 * stride].x, from[1 * stride].x, from[0 * stride].x);
}

template <>
EIGEN_STRONG_INLINE void pscatter_old<half, Packet16h>(half* to, const Packet16h& from, Index stride) {
  EIGEN_ALIGN64 half aux[16];
  pstore_old(aux, from);
  to[stride * 0] = aux[0];
  to[stride * 1] = aux[1];
  to[stride * 2] = aux[2];
  to[stride * 3] = aux[3];
  to[stride * 4] = aux[4];
  to[stride * 5] = aux[5];
  to[stride * 6] = aux[6];
  to[stride * 7] = aux[7];
  to[stride * 8] = aux[8];
  to[stride * 9] = aux[9];
  to[stride * 10] = aux[10];
  to[stride * 11] = aux[11];
  to[stride * 12] = aux[12];
  to[stride * 13] = aux[13];
  to[stride * 14] = aux[14];
  to[stride * 15] = aux[15];
}

EIGEN_STRONG_INLINE void ptranspose_old(PacketBlock<Packet16h, 16>& kernel) {
  __m256i a = kernel.packet[0];
  __m256i b = kernel.packet[1];
  __m256i c = kernel.packet[2];
  __m256i d = kernel.packet[3];
  __m256i e = kernel.packet[4];
  __m256i f = kernel.packet[5];
  __m256i g = kernel.packet[6];
  __m256i h = kernel.packet[7];
  __m256i i = kernel.packet[8];
  __m256i j = kernel.packet[9];
  __m256i k = kernel.packet[10];
  __m256i l = kernel.packet[11];
  __m256i m = kernel.packet[12];
  __m256i n = kernel.packet[13];
  __m256i o = kernel.packet[14];
  __m256i p = kernel.packet[15];

  __m256i ab_07 = _mm256_unpacklo_epi16(a, b);
  __m256i cd_07 = _mm256_unpacklo_epi16(c, d);
  __m256i ef_07 = _mm256_unpacklo_epi16(e, f);
  __m256i gh_07 = _mm256_unpacklo_epi16(g, h);
  __m256i ij_07 = _mm256_unpacklo_epi16(i, j);
  __m256i kl_07 = _mm256_unpacklo_epi16(k, l);
  __m256i mn_07 = _mm256_unpacklo_epi16(m, n);
  __m256i op_07 = _mm256_unpacklo_epi16(o, p);

  __m256i ab_8f = _mm256_unpackhi_epi16(a, b);
  __m256i cd_8f = _mm256_unpackhi_epi16(c, d);
  __m256i ef_8f = _mm256_unpackhi_epi16(e, f);
  __m256i gh_8f = _mm256_unpackhi_epi16(g, h);
  __m256i ij_8f = _mm256_unpackhi_epi16(i, j);
  __m256i kl_8f = _mm256_unpackhi_epi16(k, l);
  __m256i mn_8f = _mm256_unpackhi_epi16(m, n);
  __m256i op_8f = _mm256_unpackhi_epi16(o, p);

  __m256i abcd_03 = _mm256_unpacklo_epi32(ab_07, cd_07);
  __m256i abcd_47 = _mm256_unpackhi_epi32(ab_07, cd_07);
  __m256i efgh_03 = _mm256_unpacklo_epi32(ef_07, gh_07);
  __m256i efgh_47 = _mm256_unpackhi_epi32(ef_07, gh_07);
  __m256i ijkl_03 = _mm256_unpacklo_epi32(ij_07, kl_07);
  __m256i ijkl_47 = _mm256_unpackhi_epi32(ij_07, kl_07);
  __m256i mnop_03 = _mm256_unpacklo_epi32(mn_07, op_07);
  __m256i mnop_47 = _mm256_unpackhi_epi32(mn_07, op_07);

  __m256i abcd_8b = _mm256_unpacklo_epi32(ab_8f, cd_8f);
  __m256i abcd_cf = _mm256_unpackhi_epi32(ab_8f, cd_8f);
  __m256i efgh_8b = _mm256_unpacklo_epi32(ef_8f, gh_8f);
  __m256i efgh_cf = _mm256_unpackhi_epi32(ef_8f, gh_8f);
  __m256i ijkl_8b = _mm256_unpacklo_epi32(ij_8f, kl_8f);
  __m256i ijkl_cf = _mm256_unpackhi_epi32(ij_8f, kl_8f);
  __m256i mnop_8b = _mm256_unpacklo_epi32(mn_8f, op_8f);
  __m256i mnop_cf = _mm256_unpackhi_epi32(mn_8f, op_8f);

  __m256i abcdefgh_01 = _mm256_unpacklo_epi64(abcd_03, efgh_03);
  __m256i abcdefgh_23 = _mm256_unpackhi_epi64(abcd_03, efgh_03);
  __m256i ijklmnop_01 = _mm256_unpacklo_epi64(ijkl_03, mnop_03);
  __m256i ijklmnop_23 = _mm256_unpackhi_epi64(ijkl_03, mnop_03);
  __m256i abcdefgh_45 = _mm256_unpacklo_epi64(abcd_47, efgh_47);
  __m256i abcdefgh_67 = _mm256_unpackhi_epi64(abcd_47, efgh_47);
  __m256i ijklmnop_45 = _mm256_unpacklo_epi64(ijkl_47, mnop_47);
  __m256i ijklmnop_67 = _mm256_unpackhi_epi64(ijkl_47, mnop_47);
  __m256i abcdefgh_89 = _mm256_unpacklo_epi64(abcd_8b, efgh_8b);
  __m256i abcdefgh_ab = _mm256_unpackhi_epi64(abcd_8b, efgh_8b);
  __m256i ijklmnop_89 = _mm256_unpacklo_epi64(ijkl_8b, mnop_8b);
  __m256i ijklmnop_ab = _mm256_unpackhi_epi64(ijkl_8b, mnop_8b);
  __m256i abcdefgh_cd = _mm256_unpacklo_epi64(abcd_cf, efgh_cf);
  __m256i abcdefgh_ef = _mm256_unpackhi_epi64(abcd_cf, efgh_cf);
  __m256i ijklmnop_cd = _mm256_unpacklo_epi64(ijkl_cf, mnop_cf);
  __m256i ijklmnop_ef = _mm256_unpackhi_epi64(ijkl_cf, mnop_cf);

  // NOTE: no unpacklo/hi instr in this case, so using permute instr.
  __m256i a_p_0 = _mm256_permute2x128_si256(abcdefgh_01, ijklmnop_01, 0x20);
  __m256i a_p_1 = _mm256_permute2x128_si256(abcdefgh_23, ijklmnop_23, 0x20);
  __m256i a_p_2 = _mm256_permute2x128_si256(abcdefgh_45, ijklmnop_45, 0x20);
  __m256i a_p_3 = _mm256_permute2x128_si256(abcdefgh_67, ijklmnop_67, 0x20);
  __m256i a_p_4 = _mm256_permute2x128_si256(abcdefgh_89, ijklmnop_89, 0x20);
  __m256i a_p_5 = _mm256_permute2x128_si256(abcdefgh_ab, ijklmnop_ab, 0x20);
  __m256i a_p_6 = _mm256_permute2x128_si256(abcdefgh_cd, ijklmnop_cd, 0x20);
  __m256i a_p_7 = _mm256_permute2x128_si256(abcdefgh_ef, ijklmnop_ef, 0x20);
  __m256i a_p_8 = _mm256_permute2x128_si256(abcdefgh_01, ijklmnop_01, 0x31);
  __m256i a_p_9 = _mm256_permute2x128_si256(abcdefgh_23, ijklmnop_23, 0x31);
  __m256i a_p_a = _mm256_permute2x128_si256(abcdefgh_45, ijklmnop_45, 0x31);
  __m256i a_p_b = _mm256_permute2x128_si256(abcdefgh_67, ijklmnop_67, 0x31);
  __m256i a_p_c = _mm256_permute2x128_si256(abcdefgh_89, ijklmnop_89, 0x31);
  __m256i a_p_d = _mm256_permute2x128_si256(abcdefgh_ab, ijklmnop_ab, 0x31);
  __m256i a_p_e = _mm256_permute2x128_si256(abcdefgh_cd, ijklmnop_cd, 0x31);
  __m256i a_p_f = _mm256_permute2x128_si256(abcdefgh_ef, ijklmnop_ef, 0x31);

  kernel.packet[0] = a_p_0;
  kernel.packet[1] = a_p_1;
  kernel.packet[2] = a_p_2;
  kernel.packet[3] = a_p_3;
  kernel.packet[4] = a_p_4;
  kernel.packet[5] = a_p_5;
  kernel.packet[6] = a_p_6;
  kernel.packet[7] = a_p_7;
  kernel.packet[8] = a_p_8;
  kernel.packet[9] = a_p_9;
  kernel.packet[10] = a_p_a;
  kernel.packet[11] = a_p_b;
  kernel.packet[12] = a_p_c;
  kernel.packet[13] = a_p_d;
  kernel.packet[14] = a_p_e;
  kernel.packet[15] = a_p_f;
}

EIGEN_STRONG_INLINE void ptranspose_old(PacketBlock<Packet16h, 8>& kernel) {
  EIGEN_ALIGN64 half in[8][16];
  pstore_old<half>(in[0], kernel.packet[0]);
  pstore_old<half>(in[1], kernel.packet[1]);
  pstore_old<half>(in[2], kernel.packet[2]);
  pstore_old<half>(in[3], kernel.packet[3]);
  pstore_old<half>(in[4], kernel.packet[4]);
  pstore_old<half>(in[5], kernel.packet[5]);
  pstore_old<half>(in[6], kernel.packet[6]);
  pstore_old<half>(in[7], kernel.packet[7]);

  EIGEN_ALIGN64 half out[8][16];

  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      out[i][j] = in[j][2 * i];
    }
    for (int j = 0; j < 8; ++j) {
      out[i][j + 8] = in[j][2 * i + 1];
    }
  }

  kernel.packet[0] = pload_old<Packet16h>(out[0]);
  kernel.packet[1] = pload_old<Packet16h>(out[1]);
  kernel.packet[2] = pload_old<Packet16h>(out[2]);
  kernel.packet[3] = pload_old<Packet16h>(out[3]);
  kernel.packet[4] = pload_old<Packet16h>(out[4]);
  kernel.packet[5] = pload_old<Packet16h>(out[5]);
  kernel.packet[6] = pload_old<Packet16h>(out[6]);
  kernel.packet[7] = pload_old<Packet16h>(out[7]);
}

EIGEN_STRONG_INLINE void ptranspose_old(PacketBlock<Packet16h, 4>& kernel) {
  EIGEN_ALIGN64 half in[4][16];
  pstore_old<half>(in[0], kernel.packet[0]);
  pstore_old<half>(in[1], kernel.packet[1]);
  pstore_old<half>(in[2], kernel.packet[2]);
  pstore_old<half>(in[3], kernel.packet[3]);

  EIGEN_ALIGN64 half out[4][16];

  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      out[i][j] = in[j][4 * i];
    }
    for (int j = 0; j < 4; ++j) {
      out[i][j + 4] = in[j][4 * i + 1];
    }
    for (int j = 0; j < 4; ++j) {
      out[i][j + 8] = in[j][4 * i + 2];
    }
    for (int j = 0; j < 4; ++j) {
      out[i][j + 12] = in[j][4 * i + 3];
    }
  }

  kernel.packet[0] = pload_old<Packet16h>(out[0]);
  kernel.packet[1] = pload_old<Packet16h>(out[1]);
  kernel.packet[2] = pload_old<Packet16h>(out[2]);
  kernel.packet[3] = pload_old<Packet16h>(out[3]);
}

template <>
EIGEN_STRONG_INLINE Packet16bf pset1_old<Packet16bf>(const bfloat16& from) {
  return _mm256_set1_epi16(from.value);
}

template <>
EIGEN_STRONG_INLINE bfloat16 pfirst_old<Packet16bf>(const Packet16bf& from) {
  bfloat16 t;
  t.value = static_cast<unsigned short>(_mm256_extract_epi16(from, 0));
  return t;
}

template <>
EIGEN_STRONG_INLINE Packet16bf pload_old<Packet16bf>(const bfloat16* from) {
  return _mm256_load_si256(reinterpret_cast<const __m256i*>(from));
}

template <>
EIGEN_STRONG_INLINE Packet16bf ploadu_old<Packet16bf>(const bfloat16* from) {
  return _mm256_loadu_si256(reinterpret_cast<const __m256i*>(from));
}

template <>
EIGEN_STRONG_INLINE void pstore_old<bfloat16>(bfloat16* to, const Packet16bf& from) {
  _mm256_store_si256(reinterpret_cast<__m256i*>(to), from);
}

template <>
EIGEN_STRONG_INLINE void pstoreu_old<bfloat16>(bfloat16* to, const Packet16bf& from) {
  _mm256_storeu_si256(reinterpret_cast<__m256i*>(to), from);
}

template <>
EIGEN_STRONG_INLINE Packet16bf ploaddup_old<Packet16bf>(const bfloat16* from) {
  unsigned short a = from[0].value;
  unsigned short b = from[1].value;
  unsigned short c = from[2].value;
  unsigned short d = from[3].value;
  unsigned short e = from[4].value;
  unsigned short f = from[5].value;
  unsigned short g = from[6].value;
  unsigned short h = from[7].value;
  return _mm256_set_epi16(h, h, g, g, f, f, e, e, d, d, c, c, b, b, a, a);
}

template <>
EIGEN_STRONG_INLINE Packet16bf ploadquad_old(const bfloat16* from) {
  unsigned short a = from[0].value;
  unsigned short b = from[1].value;
  unsigned short c = from[2].value;
  unsigned short d = from[3].value;
  return _mm256_set_epi16(d, d, d, d, c, c, c, c, b, b, b, b, a, a, a, a);
}

EIGEN_STRONG_INLINE Packet16f Bf16ToF32_old(const Packet16bf& a) {
  return _mm512_castsi512_ps(_mm512_slli_epi32(_mm512_cvtepu16_epi32(a), 16));
}

// Convert float to bfloat16 according to round-to-nearest-even/denormals algorithm.
EIGEN_STRONG_INLINE Packet16bf F32ToBf16_old(const Packet16f& a) {
  Packet16bf r;

#if defined(EIGEN_VECTORIZE_AVX512BF16) && EIGEN_GNUC_AT_LEAST(10, 1)
  // Since GCC 10.1 supports avx512bf16 and C style explicit cast
  // (C++ static_cast is not supported yet), do conversion via intrinsic
  // and register path for performance.
  r = (__m256i)(_mm512_cvtneps_pbh(a));

#else
  __m512i t;
  __m512i input = _mm512_castps_si512(a);
  __m512i nan = _mm512_set1_epi32(0x7fc0);

  // uint32_t lsb = (input >> 16) & 1;
  t = _mm512_and_si512(_mm512_srli_epi32(input, 16), _mm512_set1_epi32(1));
  // uint32_t rounding_bias = 0x7fff + lsb;
  t = _mm512_add_epi32(t, _mm512_set1_epi32(0x7fff));
  // input += rounding_bias;
  t = _mm512_add_epi32(t, input);
  // input = input >> 16;
  t = _mm512_srli_epi32(t, 16);

  // Check NaN before converting back to bf16
  __mmask16 mask = _mm512_cmp_ps_mask(a, a, _CMP_ORD_Q);

  t = _mm512_mask_blend_epi32(mask, nan, t);
  // output.value = static_cast<uint16_t>(input);
  r = _mm512_cvtepi32_epi16(t);
#endif  // EIGEN_VECTORIZE_AVX512BF16

  return r;
}

template <>
EIGEN_STRONG_INLINE Packet16bf ptrue_old(const Packet16bf& a) {
  return Packet16bf(ptrue_old<Packet8i>(Packet8i(a)));
}

template <>
EIGEN_STRONG_INLINE Packet16bf por_old(const Packet16bf& a, const Packet16bf& b) {
  return Packet16bf(por_old<Packet8i>(Packet8i(a), Packet8i(b)));
}

template <>
EIGEN_STRONG_INLINE Packet16bf pxor_old(const Packet16bf& a, const Packet16bf& b) {
  return Packet16bf(pxor_old<Packet8i>(Packet8i(a), Packet8i(b)));
}

template <>
EIGEN_STRONG_INLINE Packet16bf pand_old(const Packet16bf& a, const Packet16bf& b) {
  return Packet16bf(pand_old<Packet8i>(Packet8i(a), Packet8i(b)));
}

template <>
EIGEN_STRONG_INLINE Packet16bf pandnot_old(const Packet16bf& a, const Packet16bf& b) {
  return Packet16bf(pandnot_old<Packet8i>(Packet8i(a), Packet8i(b)));
}

template <>
EIGEN_STRONG_INLINE Packet16bf pselect_old(const Packet16bf& mask, const Packet16bf& a, const Packet16bf& b) {
  // Input mask is expected to be all 0/1, handle it with 8-bit
  // intrinsic for performance.
  return _mm256_blendv_epi8(b, a, mask);
}

template <>
EIGEN_STRONG_INLINE Packet16bf pround_old<Packet16bf>(const Packet16bf& a) {
  return F32ToBf16_old(pround_old<Packet16f>(Bf16ToF32_old(a)));
}

template <>
EIGEN_STRONG_INLINE Packet16bf print_old<Packet16bf>(const Packet16bf& a) {
  return F32ToBf16_old(print_old<Packet16f>(Bf16ToF32_old(a)));
}

template <>
EIGEN_STRONG_INLINE Packet16bf pceil_old<Packet16bf>(const Packet16bf& a) {
  return F32ToBf16_old(pceil_old<Packet16f>(Bf16ToF32_old(a)));
}

template <>
EIGEN_STRONG_INLINE Packet16bf pfloor_old<Packet16bf>(const Packet16bf& a) {
  return F32ToBf16_old(pfloor_old<Packet16f>(Bf16ToF32_old(a)));
}

template <>
EIGEN_STRONG_INLINE Packet16bf pcmp_eq_old(const Packet16bf& a, const Packet16bf& b) {
  return Pack32To16(pcmp_eq_old(Bf16ToF32_old(a), Bf16ToF32_old(b)));
}

template <>
EIGEN_STRONG_INLINE Packet16bf pcmp_le_old(const Packet16bf& a, const Packet16bf& b) {
  return Pack32To16(pcmp_le_old(Bf16ToF32_old(a), Bf16ToF32_old(b)));
}

template <>
EIGEN_STRONG_INLINE Packet16bf pcmp_lt_old(const Packet16bf& a, const Packet16bf& b) {
  return Pack32To16(pcmp_lt_old(Bf16ToF32_old(a), Bf16ToF32_old(b)));
}

template <>
EIGEN_STRONG_INLINE Packet16bf pcmp_lt_or_nan_old(const Packet16bf& a, const Packet16bf& b) {
  return Pack32To16(pcmp_lt_or_nan_old(Bf16ToF32_old(a), Bf16ToF32_old(b)));
}

template <>
EIGEN_STRONG_INLINE Packet16bf pnegate_old(const Packet16bf& a) {
  Packet16bf sign_mask = _mm256_set1_epi16(static_cast<unsigned short>(0x8000));
  return _mm256_xor_si256(a, sign_mask);
}

template <>
EIGEN_STRONG_INLINE Packet16bf pconj_old(const Packet16bf& a) {
  return a;
}

template <>
EIGEN_STRONG_INLINE Packet16bf pabs_old(const Packet16bf& a) {
  const __m256i sign_mask = _mm256_set1_epi16(static_cast<numext::uint16_t>(0x8000));
  return _mm256_andnot_si256(sign_mask, a);
}

template <>
EIGEN_STRONG_INLINE Packet16bf padd_old<Packet16bf>(const Packet16bf& a, const Packet16bf& b) {
  return F32ToBf16_old(padd_old<Packet16f>(Bf16ToF32_old(a), Bf16ToF32_old(b)));
}

template <>
EIGEN_STRONG_INLINE Packet16bf psub_old<Packet16bf>(const Packet16bf& a, const Packet16bf& b) {
  return F32ToBf16_old(psub_old<Packet16f>(Bf16ToF32_old(a), Bf16ToF32_old(b)));
}

template <>
EIGEN_STRONG_INLINE Packet16bf pmul_old<Packet16bf>(const Packet16bf& a, const Packet16bf& b) {
  return F32ToBf16_old(pmul_old<Packet16f>(Bf16ToF32_old(a), Bf16ToF32_old(b)));
}

template <>
EIGEN_STRONG_INLINE Packet16bf pdiv_old<Packet16bf>(const Packet16bf& a, const Packet16bf& b) {
  return F32ToBf16_old(pdiv_old<Packet16f>(Bf16ToF32_old(a), Bf16ToF32_old(b)));
}

template <>
EIGEN_STRONG_INLINE Packet16bf pmin_old<Packet16bf>(const Packet16bf& a, const Packet16bf& b) {
  return F32ToBf16_old(pmin_old<Packet16f>(Bf16ToF32_old(a), Bf16ToF32_old(b)));
}

template <>
EIGEN_STRONG_INLINE Packet16bf pmax_old<Packet16bf>(const Packet16bf& a, const Packet16bf& b) {
  return F32ToBf16_old(pmax_old<Packet16f>(Bf16ToF32_old(a), Bf16ToF32_old(b)));
}

template <>
EIGEN_STRONG_INLINE Packet16bf plset_old<Packet16bf>(const bfloat16& a) {
  return F32ToBf16_old(plset_old<Packet16f>(static_cast<float>(a)));
}

template <>
EIGEN_STRONG_INLINE Packet8bf predux_half_dowto4_old<Packet16bf>(const Packet16bf& a) {
  Packet8bf lane0 = _mm256_extractf128_si256(a, 0);
  Packet8bf lane1 = _mm256_extractf128_si256(a, 1);
  return padd_old<Packet8bf>(lane0, lane1);
}

template <>
EIGEN_STRONG_INLINE bfloat16 predux_old<Packet16bf>(const Packet16bf& p) {
  return static_cast<bfloat16>(predux_old<Packet16f>(Bf16ToF32_old(p)));
}

template <>
EIGEN_STRONG_INLINE bfloat16 predux_mul_old<Packet16bf>(const Packet16bf& from) {
  return static_cast<bfloat16>(predux_mul_old<Packet16f>(Bf16ToF32_old(from)));
}

template <>
EIGEN_STRONG_INLINE bfloat16 predux_min_old<Packet16bf>(const Packet16bf& from) {
  return static_cast<bfloat16>(predux_min_old<Packet16f>(Bf16ToF32_old(from)));
}

template <>
EIGEN_STRONG_INLINE bfloat16 predux_max_old<Packet16bf>(const Packet16bf& from) {
  return static_cast<bfloat16>(predux_max_old<Packet16f>(Bf16ToF32_old(from)));
}

template <>
EIGEN_STRONG_INLINE Packet16bf preverse_old(const Packet16bf& a) {
  __m256i m = _mm256_setr_epi8(14, 15, 12, 13, 10, 11, 8, 9, 6, 7, 4, 5, 2, 3, 0, 1, 14, 15, 12, 13, 10, 11, 8, 9, 6, 7,
                               4, 5, 2, 3, 0, 1);

  Packet16bf res;
  // Swap hi and lo first because shuffle is in 128-bit lanes.
  res = _mm256_permute2x128_si256(a, a, 1);
  // Shuffle 8-bit values in src within 2*128-bit lanes.
  return _mm256_shuffle_epi8(res, m);
}

template <>
EIGEN_STRONG_INLINE Packet16bf pgather_old<bfloat16, Packet16bf>(const bfloat16* from, Index stride) {
  return _mm256_set_epi16(
      from[15 * stride].value, from[14 * stride].value, from[13 * stride].value, from[12 * stride].value,
      from[11 * stride].value, from[10 * stride].value, from[9 * stride].value, from[8 * stride].value,
      from[7 * stride].value, from[6 * stride].value, from[5 * stride].value, from[4 * stride].value,
      from[3 * stride].value, from[2 * stride].value, from[1 * stride].value, from[0 * stride].value);
}

template <>
EIGEN_STRONG_INLINE void pscatter_old<bfloat16, Packet16bf>(bfloat16* to, const Packet16bf& from, Index stride) {
  EIGEN_ALIGN64 bfloat16 aux[16];
  pstore_old(aux, from);
  to[stride * 0] = aux[0];
  to[stride * 1] = aux[1];
  to[stride * 2] = aux[2];
  to[stride * 3] = aux[3];
  to[stride * 4] = aux[4];
  to[stride * 5] = aux[5];
  to[stride * 6] = aux[6];
  to[stride * 7] = aux[7];
  to[stride * 8] = aux[8];
  to[stride * 9] = aux[9];
  to[stride * 10] = aux[10];
  to[stride * 11] = aux[11];
  to[stride * 12] = aux[12];
  to[stride * 13] = aux[13];
  to[stride * 14] = aux[14];
  to[stride * 15] = aux[15];
}

EIGEN_STRONG_INLINE void ptranspose_old(PacketBlock<Packet16bf, 16>& kernel) {
  __m256i a = kernel.packet[0];
  __m256i b = kernel.packet[1];
  __m256i c = kernel.packet[2];
  __m256i d = kernel.packet[3];
  __m256i e = kernel.packet[4];
  __m256i f = kernel.packet[5];
  __m256i g = kernel.packet[6];
  __m256i h = kernel.packet[7];
  __m256i i = kernel.packet[8];
  __m256i j = kernel.packet[9];
  __m256i k = kernel.packet[10];
  __m256i l = kernel.packet[11];
  __m256i m = kernel.packet[12];
  __m256i n = kernel.packet[13];
  __m256i o = kernel.packet[14];
  __m256i p = kernel.packet[15];

  __m256i ab_07 = _mm256_unpacklo_epi16(a, b);
  __m256i cd_07 = _mm256_unpacklo_epi16(c, d);
  __m256i ef_07 = _mm256_unpacklo_epi16(e, f);
  __m256i gh_07 = _mm256_unpacklo_epi16(g, h);
  __m256i ij_07 = _mm256_unpacklo_epi16(i, j);
  __m256i kl_07 = _mm256_unpacklo_epi16(k, l);
  __m256i mn_07 = _mm256_unpacklo_epi16(m, n);
  __m256i op_07 = _mm256_unpacklo_epi16(o, p);

  __m256i ab_8f = _mm256_unpackhi_epi16(a, b);
  __m256i cd_8f = _mm256_unpackhi_epi16(c, d);
  __m256i ef_8f = _mm256_unpackhi_epi16(e, f);
  __m256i gh_8f = _mm256_unpackhi_epi16(g, h);
  __m256i ij_8f = _mm256_unpackhi_epi16(i, j);
  __m256i kl_8f = _mm256_unpackhi_epi16(k, l);
  __m256i mn_8f = _mm256_unpackhi_epi16(m, n);
  __m256i op_8f = _mm256_unpackhi_epi16(o, p);

  __m256i abcd_03 = _mm256_unpacklo_epi32(ab_07, cd_07);
  __m256i abcd_47 = _mm256_unpackhi_epi32(ab_07, cd_07);
  __m256i efgh_03 = _mm256_unpacklo_epi32(ef_07, gh_07);
  __m256i efgh_47 = _mm256_unpackhi_epi32(ef_07, gh_07);
  __m256i ijkl_03 = _mm256_unpacklo_epi32(ij_07, kl_07);
  __m256i ijkl_47 = _mm256_unpackhi_epi32(ij_07, kl_07);
  __m256i mnop_03 = _mm256_unpacklo_epi32(mn_07, op_07);
  __m256i mnop_47 = _mm256_unpackhi_epi32(mn_07, op_07);

  __m256i abcd_8b = _mm256_unpacklo_epi32(ab_8f, cd_8f);
  __m256i abcd_cf = _mm256_unpackhi_epi32(ab_8f, cd_8f);
  __m256i efgh_8b = _mm256_unpacklo_epi32(ef_8f, gh_8f);
  __m256i efgh_cf = _mm256_unpackhi_epi32(ef_8f, gh_8f);
  __m256i ijkl_8b = _mm256_unpacklo_epi32(ij_8f, kl_8f);
  __m256i ijkl_cf = _mm256_unpackhi_epi32(ij_8f, kl_8f);
  __m256i mnop_8b = _mm256_unpacklo_epi32(mn_8f, op_8f);
  __m256i mnop_cf = _mm256_unpackhi_epi32(mn_8f, op_8f);

  __m256i abcdefgh_01 = _mm256_unpacklo_epi64(abcd_03, efgh_03);
  __m256i abcdefgh_23 = _mm256_unpackhi_epi64(abcd_03, efgh_03);
  __m256i ijklmnop_01 = _mm256_unpacklo_epi64(ijkl_03, mnop_03);
  __m256i ijklmnop_23 = _mm256_unpackhi_epi64(ijkl_03, mnop_03);
  __m256i abcdefgh_45 = _mm256_unpacklo_epi64(abcd_47, efgh_47);
  __m256i abcdefgh_67 = _mm256_unpackhi_epi64(abcd_47, efgh_47);
  __m256i ijklmnop_45 = _mm256_unpacklo_epi64(ijkl_47, mnop_47);
  __m256i ijklmnop_67 = _mm256_unpackhi_epi64(ijkl_47, mnop_47);
  __m256i abcdefgh_89 = _mm256_unpacklo_epi64(abcd_8b, efgh_8b);
  __m256i abcdefgh_ab = _mm256_unpackhi_epi64(abcd_8b, efgh_8b);
  __m256i ijklmnop_89 = _mm256_unpacklo_epi64(ijkl_8b, mnop_8b);
  __m256i ijklmnop_ab = _mm256_unpackhi_epi64(ijkl_8b, mnop_8b);
  __m256i abcdefgh_cd = _mm256_unpacklo_epi64(abcd_cf, efgh_cf);
  __m256i abcdefgh_ef = _mm256_unpackhi_epi64(abcd_cf, efgh_cf);
  __m256i ijklmnop_cd = _mm256_unpacklo_epi64(ijkl_cf, mnop_cf);
  __m256i ijklmnop_ef = _mm256_unpackhi_epi64(ijkl_cf, mnop_cf);

  // NOTE: no unpacklo/hi instr in this case, so using permute instr.
  kernel.packet[0] = _mm256_permute2x128_si256(abcdefgh_01, ijklmnop_01, 0x20);
  kernel.packet[1] = _mm256_permute2x128_si256(abcdefgh_23, ijklmnop_23, 0x20);
  kernel.packet[2] = _mm256_permute2x128_si256(abcdefgh_45, ijklmnop_45, 0x20);
  kernel.packet[3] = _mm256_permute2x128_si256(abcdefgh_67, ijklmnop_67, 0x20);
  kernel.packet[4] = _mm256_permute2x128_si256(abcdefgh_89, ijklmnop_89, 0x20);
  kernel.packet[5] = _mm256_permute2x128_si256(abcdefgh_ab, ijklmnop_ab, 0x20);
  kernel.packet[6] = _mm256_permute2x128_si256(abcdefgh_cd, ijklmnop_cd, 0x20);
  kernel.packet[7] = _mm256_permute2x128_si256(abcdefgh_ef, ijklmnop_ef, 0x20);
  kernel.packet[8] = _mm256_permute2x128_si256(abcdefgh_01, ijklmnop_01, 0x31);
  kernel.packet[9] = _mm256_permute2x128_si256(abcdefgh_23, ijklmnop_23, 0x31);
  kernel.packet[10] = _mm256_permute2x128_si256(abcdefgh_45, ijklmnop_45, 0x31);
  kernel.packet[11] = _mm256_permute2x128_si256(abcdefgh_67, ijklmnop_67, 0x31);
  kernel.packet[12] = _mm256_permute2x128_si256(abcdefgh_89, ijklmnop_89, 0x31);
  kernel.packet[13] = _mm256_permute2x128_si256(abcdefgh_ab, ijklmnop_ab, 0x31);
  kernel.packet[14] = _mm256_permute2x128_si256(abcdefgh_cd, ijklmnop_cd, 0x31);
  kernel.packet[15] = _mm256_permute2x128_si256(abcdefgh_ef, ijklmnop_ef, 0x31);
}

EIGEN_STRONG_INLINE void ptranspose_old(PacketBlock<Packet16bf, 4>& kernel) {
  __m256i a = kernel.packet[0];
  __m256i b = kernel.packet[1];
  __m256i c = kernel.packet[2];
  __m256i d = kernel.packet[3];

  __m256i ab_07 = _mm256_unpacklo_epi16(a, b);
  __m256i cd_07 = _mm256_unpacklo_epi16(c, d);
  __m256i ab_8f = _mm256_unpackhi_epi16(a, b);
  __m256i cd_8f = _mm256_unpackhi_epi16(c, d);

  __m256i abcd_03 = _mm256_unpacklo_epi32(ab_07, cd_07);
  __m256i abcd_47 = _mm256_unpackhi_epi32(ab_07, cd_07);
  __m256i abcd_8b = _mm256_unpacklo_epi32(ab_8f, cd_8f);
  __m256i abcd_cf = _mm256_unpackhi_epi32(ab_8f, cd_8f);

  // NOTE: no unpacklo/hi instr in this case, so using permute instr.
  kernel.packet[0] = _mm256_permute2x128_si256(abcd_03, abcd_47, 0x20);
  kernel.packet[1] = _mm256_permute2x128_si256(abcd_8b, abcd_cf, 0x20);
  kernel.packet[2] = _mm256_permute2x128_si256(abcd_03, abcd_47, 0x31);
  kernel.packet[3] = _mm256_permute2x128_si256(abcd_8b, abcd_cf, 0x31);
}

#endif

#endif

#undef EIGEN_BINARY_OP_NAN_PROPAGATION

#endif // EIGEN_PACKET_MATH_OLD_FUN_MIPP_H