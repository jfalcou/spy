//==================================================================================================
/*
  SPY - C++ Informations Broker
  Copyright 2020 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
 */
//==================================================================================================
#ifndef SPY_SIMD_ARM_HPP_INCLUDED
#define SPY_SIMD_ARM_HPP_INCLUDED

#if !defined(SPY_SIMD_DETECTED) && (defined(__ARM_NEON__) || defined(_M_ARM) || defined(__aarch64__))
#  define SPY_SIMD_IS_ARM_NEON
#  define SPY_SIMD_DETECTED ::spy::detail::simd_version::neon_
#endif

#if defined(SPY_SIMD_DETECTED) && !defined(SPY_SIMD_VENDOR)
#  define SPY_SIMD_IS_ARM
#  define SPY_SIMD_VENDOR ::spy::detail::simd_isa::arm_
#endif

namespace spy::supports
{
  //================================================================================================
  // Supplemental ISA
  //================================================================================================
#if defined(__aarch64__)
#  define SPY_SIMD_SUPPORTS_AARCH64
  constexpr inline auto aarch64_ = true;
#else
  constexpr inline auto aarch64_ = false;
#endif

}

#endif
