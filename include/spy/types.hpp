//==================================================================================================
/*
  SPY - C++ Informations Broker
  Copyright : SPY Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#if defined(SPY_ARCH_IS_ARM)
#if defined(__ARM_FP16_FORMAT_IEEE) && __ARM_FP16_FORMAT_IEEE == 1 &&                              \
    (!defined(__ARM_FP16_FORMAT_ALTERNATIVE) || __ARM_FP16_FORMAT_ALTERNATIVE == 0)
#define SPY_SUPPORTS_FP16_TYPE

#if defined(__ARM_FEATURE_FP16_SCALAR_ARITHMETIC)
#define SPY_SUPPORTS_FP16_SCALAR_OPS
#endif

#if defined(__ARM_FEATURE_FP16_VECTOR_ARITHMETIC)
#define SPY_SUPPORTS_FP16_VECTOR_OPS
#define SPY_SUPPORTS_FP16_VECTOR_CONVERSION
#elif defined(__aarch64__)
#define SPY_SUPPORTS_FP16_VECTOR_CONVERSION
#endif
#endif
#elif defined(SPY_ARCH_IS_X86)
#define SPY_SUPPORTS_FP16_TYPE
#elif defined(SPY_ARCH_IS_AMD64)
#define SPY_SUPPORTS_FP16_TYPE

#if defined(__AVX512FP16__)
#define SPY_SUPPORTS_FP16_SCALAR_OPS
#define SPY_SUPPORTS_FP16_VECTOR_OPS
#define SPY_SUPPORTS_FP16_VECTOR_CONVERSION
#elif defined(__F16C__)
#define SPY_SUPPORTS_FP16_VECTOR_CONVERSION
#endif
#elif defined(SPY_ARCH_IS_RISCV)
#define SPY_SUPPORTS_FP16_TYPE

#if defined(__riscv_zfh)
#define SPY_SUPPORTS_FP16_SCALAR_OPS
#endif

#if defined(__riscv_zvfh)
#define SPY_SUPPORTS_FP16_VECTOR_OPS
#define SPY_SUPPORTS_FP16_VECTOR_CONVERSION
#elif defined(__riscv_zvfhmin)
#define SPY_SUPPORTS_FP16_VECTOR_CONVERSION
#endif
#endif

namespace spy::supports::fp16
{
  //! Whether the _Float16 type is provided by the compiler on the current platform.
#ifdef SPY_SUPPORTS_FP16_TYPE
  static constexpr bool type = true;
#else
  static constexpr bool type = false;
#endif

  //! Whether the current architecture supports scalar operations on IEEE-754 half-precision
  //! floating-point numbers.
#ifdef SPY_SUPPORTS_FP16_SCALAR_OPS
  static constexpr bool scalar_ops = true;
#else
  static constexpr bool scalar_ops = false;
#endif

  //! Whether the current architecture supports packed conversion operations between IEEE-754
  //! half-precision floating-point numbers and at least one other IEEE-754 floating-point type.
#ifdef SPY_SUPPORTS_FP16_VECTOR_CONVERSION
  static constexpr bool vector_conversion = true;
#else
  static constexpr bool vector_conversion = false;
#endif

  //! Whether the current architecture supports vector operations on IEEE-754 half-precision
  //! floating-point numbers.
#ifdef SPY_SUPPORTS_FP16_VECTOR_OPS
  static constexpr bool vector_ops = true;
#else
  static constexpr bool vector_ops = false;
#endif
}
