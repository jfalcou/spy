//==================================================================================================
/*
  SPY - C++ Informations Broker
  Copyright 2020 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
 */
//==================================================================================================
#ifndef SPY_SIMD_X86_HPP_INLUDED
#define SPY_SIMD_X86_HPP_INLUDED

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
}

#endif
