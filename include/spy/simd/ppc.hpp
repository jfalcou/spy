//==================================================================================================
/*
  SPY - C++ Informations Broker
  Copyright : SPY Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#if !defined(SPY_SIMD_DETECTED) && defined(__VSX__)
# define SPY_SIMD_IS_PPC_VSX
#  if defined(_ARCH_PWR10)
#    define SPY_SIMD_IS_PPC_VSX_3_01
#    define SPY_SIMD_DETECTED ::spy::detail::simd_version::vsx_3_01_
#  elif defined(_ARCH_PWR9)
#    define SPY_SIMD_IS_PPC_VSX_3_00
#    define SPY_SIMD_DETECTED ::spy::detail::simd_version::vsx_3_00_
#  elif defined(_ARCH_PWR8)
#    define SPY_SIMD_IS_PPC_VSX_2_07
#    define SPY_SIMD_DETECTED ::spy::detail::simd_version::vsx_2_07_
#  elif defined(_ARCH_PWR7)
#    define SPY_SIMD_IS_PPC_VSX_2_06
#    define SPY_SIMD_DETECTED ::spy::detail::simd_version::vsx_2_06_
#  endif
#endif

#if !defined(SPY_SIMD_DETECTED) && (defined(__ALTIVEC__) || defined(__VEC__))
#  define SPY_SIMD_IS_PPC_VMX
#  if defined(_ARCH_PWR10)
#    define SPY_SIMD_IS_PPC_VMX_3_01
#    define SPY_SIMD_DETECTED ::spy::detail::simd_version::vmx_3_01_
#  elif defined(_ARCH_PWR9)
#    define SPY_SIMD_IS_PPC_VMX_3_00
#    define SPY_SIMD_DETECTED ::spy::detail::simd_version::vmx_3_00_
#  elif defined(_ARCH_PWR8)
#    define SPY_SIMD_IS_PPC_VMX_2_07
#    define SPY_SIMD_DETECTED ::spy::detail::simd_version::vmx_2_07_
#  elif defined(_ARCH_PWR7)
#    define SPY_SIMD_IS_PPC_VMX_2_06
#    define SPY_SIMD_DETECTED ::spy::detail::simd_version::vmx_2_06_
#  elif defined(_ARCH_PWR6)
#    define SPY_SIMD_IS_PPC_VMX_2_05
#    define SPY_SIMD_DETECTED ::spy::detail::simd_version::vmx_2_05_
#  elif defined(_ARCH_PWR5)
#    define SPY_SIMD_IS_PPC_VMX_2_03
#    define SPY_SIMD_DETECTED ::spy::detail::simd_version::vmx_2_03_
#  endif
#  define SPY_SIMD_DETECTED ::spy::detail::simd_version::vmx_
#endif

#if defined(SPY_SIMD_DETECTED) && !defined(SPY_SIMD_VENDOR)
#  define SPY_SIMD_IS_PPC
#  define SPY_SIMD_VENDOR ::spy::detail::simd_isa::ppc_
#endif
