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
#if defined(SPY_SUPPORTS_FP16_TYPE)
  constexpr inline bool type = true;
#elif defined(SPY_DOXYGEN_INVOKED)
  //================================================================================================
  //! @ingroup spy_isa
  //! @brief Half-precision type availability indicator
  //!
  //! Evaluates to `true` when the `_Float16` type is provided by the compiler on the current
  //! platform. The three other indicators of this namespace are meaningful only when this one
  //! is `true`.
  //!
  //! @groupheader{Example}
  //! @godbolt{samples/fp16.cpp}
  //================================================================================================
  constexpr inline bool type = _::implementation_defined {};
#else
  constexpr inline bool type = false;
#endif

#if defined(SPY_SUPPORTS_FP16_SCALAR_OPS)
  constexpr inline bool scalar_ops = true;
#elif defined(SPY_DOXYGEN_INVOKED)
  //================================================================================================
  //! @ingroup spy_isa
  //! @brief Half-precision scalar arithmetic indicator
  //!
  //! Evaluates to `true` when the current architecture supports scalar operations on IEEE-754
  //! half-precision floating-point numbers.
  //!
  //! @groupheader{Example}
  //! @godbolt{samples/fp16.cpp}
  //================================================================================================
  constexpr inline bool scalar_ops = _::implementation_defined {};
#else
  constexpr inline bool scalar_ops = false;
#endif

#if defined(SPY_SUPPORTS_FP16_VECTOR_CONVERSION)
  constexpr inline bool vector_conversion = true;
#elif defined(SPY_DOXYGEN_INVOKED)
  //================================================================================================
  //! @ingroup spy_isa
  //! @brief Half-precision packed conversion indicator
  //!
  //! Evaluates to `true` when the current architecture supports packed conversion operations
  //! between IEEE-754 half-precision floating-point numbers and at least one other IEEE-754
  //! floating-point type. It is implied by @ref spy::supports::fp16::vector_ops.
  //!
  //! @groupheader{Example}
  //! @godbolt{samples/fp16.cpp}
  //================================================================================================
  constexpr inline bool vector_conversion = _::implementation_defined {};
#else
  constexpr inline bool vector_conversion = false;
#endif

#if defined(SPY_SUPPORTS_FP16_VECTOR_OPS)
  constexpr inline bool vector_ops = true;
#elif defined(SPY_DOXYGEN_INVOKED)
  //================================================================================================
  //! @ingroup spy_isa
  //! @brief Half-precision vector arithmetic indicator
  //!
  //! Evaluates to `true` when the current architecture supports vector operations on IEEE-754
  //! half-precision floating-point numbers.
  //!
  //! @groupheader{Example}
  //! @godbolt{samples/fp16.cpp}
  //================================================================================================
  constexpr inline bool vector_ops = _::implementation_defined {};
#else
  constexpr inline bool vector_ops = false;
#endif
}
