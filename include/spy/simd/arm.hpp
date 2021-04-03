//==================================================================================================
/*
  SPY - C++ Informations Broker
  Copyright 2020-2021 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
 */
//==================================================================================================
#pragma once

#if !defined(SPY_SIMD_DETECTED) && defined(__aarch64__)
#  define SPY_SIMD_IS_ARM_ASIMD
#  define SPY_SIMD_DETECTED ::spy::detail::simd_version::asimd_
#endif

#if !defined(SPY_SIMD_DETECTED) && ((defined(__ARM_NEON__) || defined(_M_ARM)) && (__ARM_ARCH == 7))
#  define SPY_SIMD_IS_ARM_NEON
#  define SPY_SIMD_DETECTED ::spy::detail::simd_version::neon_
#endif

#if defined(SPY_SIMD_DETECTED) && !defined(SPY_SIMD_VENDOR)
#  define SPY_SIMD_IS_ARM
#  define SPY_SIMD_VENDOR ::spy::detail::simd_isa::arm_
#endif
