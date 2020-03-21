//==================================================================================================
/*
  SPY - C++ Informations Broker
  Copyright 2020 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
 */
//==================================================================================================
#ifndef SPY_SIMD_PPC_HPP_INLUDED
#define SPY_SIMD_PPC_HPP_INLUDED

#if !defined(SPY_SIMD_DETECTED) && defined(__VSX__)
#  define SPY_SIMD_IS_PPC_VSX
#  define SPY_SIMD_DETECTED ::spy::detail::simd_version::vsx_
#endif

#if !defined(SPY_SIMD_DETECTED) && (defined(__ALTIVEC__) || defined(__VEC__))
#  define SPY_SIMD_IS_PPC_VMX
#  define SPY_SIMD_DETECTED ::spy::detail::simd_version::vmx_
#endif

#if defined(SPY_SIMD_DETECTED) && !defined(SPY_SIMD_VENDOR)
#  define SPY_SIMD_IS_PPC
#  define SPY_SIMD_VENDOR ::spy::detail::simd_isa::ppc_
#endif

#endif
