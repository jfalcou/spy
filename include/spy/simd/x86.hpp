//==================================================================================================
/*
  SPY - C++ Informations Broker
  Copyright : SPY Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once
#if !defined(SPY_SIMD_DETECTED) && defined(__AVX512F__)
#  define SPY_SIMD_IS_X86_AVX512
#  define SPY_SIMD_DETECTED ::spy::detail::simd_version::avx512_

#if defined(__AVX512BW__)
#  define SPY_SIMD_IS_X86_AVX512_BW
#endif

#if defined(__AVX512CD__)
#  define SPY_SIMD_IS_X86_AVX512_CD
#endif

#if defined(__AVX512DQ__)
#  define SPY_SIMD_IS_X86_AVX512_DQ
#endif

#if defined(__AVX512ER__)
#  define SPY_SIMD_IS_X86_AVX512_ER
#endif

#if defined(__AVX512IFMA__)
#  define SPY_SIMD_IS_X86_AVX512_IFMA
#endif

#if defined(__AVX512PF__)
#  define SPY_SIMD_IS_X86_AVX512_PF
#endif

#if defined(__AVX512VL__)
#  define SPY_SIMD_IS_X86_AVX512_VL
#endif

#if defined(__AVX512VPOPCNTDQ__)
#  define SPY_SIMD_IS_X86_AVX512_POPCNTDQ
#endif

#if defined(__AVX5124FMAPS__)
#  define SPY_SIMD_IS_X86_AVX512_4FMAPS
#endif

#if defined(__AVX5124VNNIW__)
#  define SPY_SIMD_IS_X86_AVX512_VNNIW
#endif

#if defined(__AVX512VBMI__)
#  define SPY_SIMD_IS_X86_AVX512_VBMI
#endif

#if defined(__AVX512BF16__)
#  define SPY_SIMD_IS_X86_AVX512_BF16
#endif

#if defined(__AVX512BITALG__)
#  define SPY_SIMD_IS_X86_AVX512_BITALG
#endif

#if defined(__AVX512VBMI2__)
#  define SPY_SIMD_IS_X86_AVX512_VBMI2
#endif

#if defined(__AVX512VNNI__)
#  define SPY_SIMD_IS_X86_AVX512_VNNI
#endif

#if defined(__AVX512VP2INTERSECT__)
#  define SPY_SIMD_IS_X86_AVX512_VP2INTERSECT
#endif

#endif

#if !defined(SPY_SIMD_DETECTED) && defined(__AVX2__)
#  define SPY_SIMD_IS_X86_AVX2
#  define SPY_SIMD_DETECTED ::spy::detail::simd_version::avx2_
#endif

#if !defined(SPY_SIMD_DETECTED) && defined(__AVX__)
#  define SPY_SIMD_IS_X86_AVX
#  define SPY_SIMD_DETECTED ::spy::detail::simd_version::avx_
#endif

#if !defined(SPY_SIMD_DETECTED) && defined(__SSE4_2__)
#  define SPY_SIMD_IS_X86_SSE4_2
#  define SPY_SIMD_DETECTED ::spy::detail::simd_version::sse42_
#endif

#if !defined(SPY_SIMD_DETECTED) && defined(__SSE4_1__)
#  define SPY_SIMD_IS_X86_SSE4_1
#  define SPY_SIMD_DETECTED ::spy::detail::simd_version::sse41_
#endif

#if !defined(SPY_SIMD_DETECTED) && defined(__SSSE3__)
#  define SPY_SIMD_IS_X86_SSSE3
#  define SPY_SIMD_DETECTED ::spy::detail::simd_version::ssse3_
#endif

#if !defined(SPY_SIMD_DETECTED) && defined(__SSE3__)
#  define SPY_SIMD_IS_X86_SSE3
#  define SPY_SIMD_DETECTED ::spy::detail::simd_version::sse3_
#endif

#if !defined(SPY_SIMD_DETECTED) && (defined(__SSE2__) || defined(_M_X64) || (defined(_M_IX86_FP) && _M_IX86_FP >= 2))
#  define SPY_SIMD_IS_X86_SSE2
#  define SPY_SIMD_DETECTED ::spy::detail::simd_version::sse2_
#endif

#if !defined(SPY_SIMD_DETECTED) && (defined(__SSE__) || defined(_M_IX86_FP))
#  define SPY_SIMD_IS_X86_SSE
#  define SPY_SIMD_DETECTED ::spy::detail::simd_version::sse1_
#endif

#if defined(SPY_SIMD_DETECTED) && !defined(SPY_SIMD_VENDOR)
#  define SPY_SIMD_IS_X86
#  define SPY_SIMD_VENDOR ::spy::detail::simd_isa::x86_
#endif

namespace spy::supports
{
  //================================================================================================
  // Supplemental ISA
  //================================================================================================
#if defined(__FMA__)
#  define SPY_SIMD_SUPPORTS_FMA
  constexpr inline auto fma_ = true;
#else
  constexpr inline auto fma_ = false;
#endif

#if defined(__FMA4__)
#  define SPY_SIMD_SUPPORTS_FMA4
  constexpr inline auto fma4_ = true;
#else
  constexpr inline auto fma4_ = false;
#endif

#if defined(__XOP__)
#  define SPY_SIMD_SUPPORTS_XOP
  constexpr inline auto xop_ = true;
#else
  constexpr inline auto xop_ = false;
#endif

namespace avx512
{
#if defined(__AVX512BW__)
#  define SPY_SIMD_IS_X86_AVX512_BW
  constexpr inline auto bw_ = true;
#else
  constexpr inline auto bw_ = false;
#endif

#if defined(__AVX512CD__)
#  define SPY_SIMD_IS_X86_AVX512_CD
  constexpr inline auto cd_ = true;
#else
  constexpr inline auto cd_ = false;
#endif

#if defined(__AVX512DQ__)
#  define SPY_SIMD_IS_X86_AVX512_DQ
  constexpr inline auto dq_ = true;
#else
  constexpr inline auto dq_ = false;
#endif

#if defined(__AVX512ER__)
#  define SPY_SIMD_IS_X86_AVX512_ER
  constexpr inline auto er_ = true;
#else
  constexpr inline auto er_ = false;
#endif

#if defined(__AVX512IFMA__)
#  define SPY_SIMD_IS_X86_AVX512_IFMA
  constexpr inline auto ifma_ = true;
#else
  constexpr inline auto ifma_ = false;
#endif

#if defined(__AVX512PF__)
#  define SPY_SIMD_IS_X86_AVX512_PF
  constexpr inline auto pf_ = true;
#else
  constexpr inline auto pf_ = false;
#endif

#if defined(__AVX512VL__)
#  define SPY_SIMD_IS_X86_AVX512_VL
  constexpr inline auto vl_ = true;
#else
  constexpr inline auto vl_ = false;
#endif

#if defined(__AVX512VPOPCNTDQ__)
#  define SPY_SIMD_IS_X86_AVX512_POPCNTDQ
  constexpr inline auto popcntdq_ = true;
#else
  constexpr inline auto popcntdq_ = false;
#endif

#if defined(__AVX5124FMAPS__)
#  define SPY_SIMD_IS_X86_AVX512_4FMAPS
  constexpr inline auto _4fmaps_ = true;
#else
  constexpr inline auto _4fmaps_ = false;
#endif

#if defined(__AVX5124VNNIW__)
#  define SPY_SIMD_IS_X86_AVX512_VNNIW
  constexpr inline auto vnniw_ = true;
#else
  constexpr inline auto vnniw_ = false;
#endif

#if defined(__AVX512VBMI__)
#  define SPY_SIMD_IS_X86_AVX512_VBMI
  constexpr inline auto vbmi_ = true;
#else
  constexpr inline auto vbmi_ = false;
#endif

#if defined(__AVX512BF16__)
#  define SPY_SIMD_IS_X86_AVX512_BF16
  constexpr inline auto bf16_ = true;
#else
  constexpr inline auto bf16_ = false;
#endif

#if defined(__AVX512BITALG__)
#  define SPY_SIMD_IS_X86_AVX512_BITALG
  constexpr inline auto bitalg_ = true;
#else
  constexpr inline auto bitalg_ = false;
#endif

#if defined(__AVX512VBMI2__)
#  define SPY_SIMD_IS_X86_AVX512_VBMI2
  constexpr inline auto vbmi2_ = true;
#else
  constexpr inline auto vbmi2_ = false;
#endif

#if defined(__AVX512VNNI__)
#  define SPY_SIMD_IS_X86_AVX512_VNNI
  constexpr inline auto vnni_ = true;
#else
  constexpr inline auto vnni_ = false;
#endif

#if defined(__AVX512VP2INTERSECT__)
#  define SPY_SIMD_IS_X86_AVX512_VP2INTERSECT
  constexpr inline auto vpintersect_ = true;
#else
  constexpr inline auto vpintersect_ = false;
#endif
}

}
