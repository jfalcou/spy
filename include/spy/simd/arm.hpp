//==================================================================================================
/**
  SPY - C++ Informations Broker
  Copyright : SPY Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#if !defined(SPY_SIMD_DETECTED) && defined(__ARM_FEATURE_SVE)
// Flexible SVE has no SVE_BITS or SVE_BITS set at 0 and is set via -march=armv8-a+sve
# if !defined(__ARM_FEATURE_SVE_BITS) || (__ARM_FEATURE_SVE_BITS == 0)
#   define SPY_SIMD_IS_ARM_FLEXIBLE_SVE
#   define SPY_SIMD_DETECTED ::spy::detail::simd_version::sve_
// Fixed-size SVE has SVE_BITS set at expected size via -msve-vector-bits
# elif defined(__ARM_FEATURE_SVE_BITS)
#   if(__ARM_FEATURE_SVE_BITS == 128)
#     define SPY_SIMD_IS_ARM_FIXED_SVE
#     define SPY_SIMD_DETECTED ::spy::detail::simd_version::sve128_
namespace spy { inline constexpr auto sve_width = 128; }
#   elif(__ARM_FEATURE_SVE_BITS == 256)
#     define SPY_SIMD_IS_ARM_FIXED_SVE
#     define SPY_SIMD_DETECTED ::spy::detail::simd_version::sve256_
namespace spy { inline constexpr auto sve_width = 256; }
#   elif(__ARM_FEATURE_SVE_BITS == 512)
#     define SPY_SIMD_IS_ARM_FIXED_SVE
#     define SPY_SIMD_DETECTED ::spy::detail::simd_version::sve512_
namespace spy { inline constexpr auto sve_width = 512; }
#   elif(__ARM_FEATURE_SVE_BITS == 1024)
#     define SPY_SIMD_IS_ARM_FIXED_SVE
#     define SPY_SIMD_DETECTED ::spy::detail::simd_version::sve1024_
namespace spy { inline constexpr auto sve_width = 1024; }
#   endif
# endif
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


namespace spy
{
  inline constexpr auto not_available_ = 0;
  inline constexpr auto unsupported_   = -1;
}

#if defined(SPY_SIMD_DETECTED) && !defined(SPY_SIMD_IS_ARM_FIXED_SVE)
namespace spy
{
#if defined(SPY_SIMD_IS_ARM_FLEXIBLE_SVE)
  inline constexpr auto sve_width = not_available_;
#else
  inline constexpr auto sve_width = unsupported_;
#endif
}
#else
namespace spy
{
  inline constexpr auto sve_width = unsupported_;
}
#endif
