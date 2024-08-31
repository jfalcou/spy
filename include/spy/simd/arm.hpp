//==================================================================================================
/*
  SPY - C++ Informations Broker
  Copyright : SPY Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#if defined(__ARM_FEATURE_SVE2)
// Flexible SVE2 has no SVE_BITS or SVE_BITS set at 0 and is set via -march=armv8-a+sve
# if !defined(__ARM_FEATURE_SVE_BITS) || (__ARM_FEATURE_SVE_BITS == 0)
#   define SPY_SIMD_IS_ARM_FLEXIBLE_SVE2
#   define SPY_SIMD_DETECTED ::spy::detail::simd_version::sve2_
// Fixed-size SVE has SVE_BITS set at expected size via -msve-vector-bits
# elif defined(__ARM_FEATURE_SVE_BITS)
#   if(__ARM_FEATURE_SVE_BITS == 128)
#     define SPY_SIMD_IS_ARM_FIXED_SVE2
#     define SPY_SIMD_DETECTED ::spy::detail::simd_version::fixed_sve2_
#   elif(__ARM_FEATURE_SVE_BITS == 256)
#     define SPY_SIMD_IS_ARM_FIXED_SVE2
#     define SPY_SIMD_DETECTED ::spy::detail::simd_version::fixed_sve2_
#   elif(__ARM_FEATURE_SVE_BITS == 512)
#     define SPY_SIMD_IS_ARM_FIXED_SVE2
#     define SPY_SIMD_DETECTED ::spy::detail::simd_version::fixed_sve2_
#   elif(__ARM_FEATURE_SVE_BITS == 1024)
#     define SPY_SIMD_IS_ARM_FIXED_SVE2
#     define SPY_SIMD_DETECTED ::spy::detail::simd_version::fixed_sve2_
#   else
#   error "[SPY] - No support for non-power of 2 SVE-2 cardinals"
#   endif
# endif
#endif

#if !defined(SPY_SIMD_DETECTED) && defined(__ARM_FEATURE_SVE)
// Flexible SVE has no SVE_BITS or SVE_BITS set at 0 and is set via -march=armv8-a+sve
# if !defined(__ARM_FEATURE_SVE_BITS) || (__ARM_FEATURE_SVE_BITS == 0)
#   define SPY_SIMD_IS_ARM_FLEXIBLE_SVE
#   define SPY_SIMD_DETECTED ::spy::detail::simd_version::sve_
// Fixed-size SVE has SVE_BITS set at expected size via -msve-vector-bits
# elif defined(__ARM_FEATURE_SVE_BITS)
#   if(__ARM_FEATURE_SVE_BITS == 128)
#     define SPY_SIMD_IS_ARM_FIXED_SVE
#     define SPY_SIMD_DETECTED ::spy::detail::simd_version::fixed_sve_
#   elif(__ARM_FEATURE_SVE_BITS == 256)
#     define SPY_SIMD_IS_ARM_FIXED_SVE
#     define SPY_SIMD_DETECTED ::spy::detail::simd_version::fixed_sve_
#   elif(__ARM_FEATURE_SVE_BITS == 512)
#     define SPY_SIMD_IS_ARM_FIXED_SVE
#     define SPY_SIMD_DETECTED ::spy::detail::simd_version::fixed_sve_
#   elif(__ARM_FEATURE_SVE_BITS == 1024)
#     define SPY_SIMD_IS_ARM_FIXED_SVE
#     define SPY_SIMD_DETECTED ::spy::detail::simd_version::fixed_sve_
#   else
#   error "[SPY] - No support for non-power of 2 SVE cardinals"
#   endif
# endif
#endif

#if defined(__ARM_FEATURE_SVE2)
# define SPY_SIMD_IS_ARM_SVE2
# define SPY_SIMD_VENDOR ::spy::detail::simd_isa::arm_sve_
#elif defined(__ARM_FEATURE_SVE)
# define SPY_SIMD_IS_ARM_SVE
# define SPY_SIMD_VENDOR ::spy::detail::simd_isa::arm_sve_
#endif

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
