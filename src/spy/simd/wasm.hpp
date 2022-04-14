//==================================================================================================
/**
  SPY - C++ Informations Broker
  Copyright : SPY Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#if !defined(SPY_SIMD_DETECTED) && defined(__wasm_simd128__)
#  define SPY_SIMD_DETECTED ::spy::detail::simd_version::simd128_
#endif

#if defined(SPY_SIMD_DETECTED) && !defined(SPY_SIMD_VENDOR)
#  define SPY_SIMD_IS_WASM
#  define SPY_SIMD_VENDOR ::spy::detail::simd_isa::wasm_
#endif
