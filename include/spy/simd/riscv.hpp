//==================================================================================================
/*
  SPY - C++ Informations Broker
  Copyright : SPY Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#if defined(__riscv_vector)
// Flexible RISC-V Vector has no __riscv_v_fixed_vlen defined
# if !defined(__riscv_v_fixed_vlen)
#   define SPY_SIMD_IS_RISCV_FLEXIBLE_RVV
#   define SPY_SIMD_DETECTED  ::spy::detail::simd_version::rvv_
// Fixed-size RISC-V Vector has __riscv_v_fixed_vlen
#else
#  define SPY_SIMD_IS_RISCV_FIXED_RVV
#  define SPY_SIMD_DETECTED  ::spy::detail::simd_version::fixed_rvv_
#endif
#endif

#if defined(__riscv_vector)
# define SPY_SIMD_IS_RISCV_RVV
# define SPY_SIMD_VENDOR    ::spy::detail::simd_isa::riscv_
#endif
