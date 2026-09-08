//==================================================================================================
/*
  SPY - C++ Informations Broker
  Copyright : SPY Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once
#if !defined(SPY_SIMD_DETECTED) && defined(__AVX512F__)
#define SPY_SIMD_IS_X86_AVX512
#define SPY_SIMD_DETECTED ::spy::_::simd_version::avx512_

#if defined(__AVX512BW__)
#define SPY_SIMD_IS_X86_AVX512_BW
#endif

#if defined(__AVX512CD__)
#define SPY_SIMD_IS_X86_AVX512_CD
#endif

#if defined(__AVX512DQ__)
#define SPY_SIMD_IS_X86_AVX512_DQ
#endif

#if defined(__AVX512ER__)
#define SPY_SIMD_IS_X86_AVX512_ER
#endif

#if defined(__AVX512IFMA__)
#define SPY_SIMD_IS_X86_AVX512_IFMA
#endif

#if defined(__AVX512PF__)
#define SPY_SIMD_IS_X86_AVX512_PF
#endif

#if defined(__AVX512VL__)
#define SPY_SIMD_IS_X86_AVX512_VL
#endif

#if defined(__AVX512VPOPCNTDQ__)
#define SPY_SIMD_IS_X86_AVX512_POPCNTDQ
#endif

#if defined(__AVX5124FMAPS__)
#define SPY_SIMD_IS_X86_AVX512_4FMAPS
#endif

#if defined(__AVX5124VNNIW__)
#define SPY_SIMD_IS_X86_AVX512_VNNIW
#endif

#if defined(__AVX512VBMI__)
#define SPY_SIMD_IS_X86_AVX512_VBMI
#endif

#if defined(__AVX512BF16__)
#define SPY_SIMD_IS_X86_AVX512_BF16
#endif

#if defined(__AVX512BITALG__)
#define SPY_SIMD_IS_X86_AVX512_BITALG
#endif

#if defined(__AVX512VBMI2__)
#define SPY_SIMD_IS_X86_AVX512_VBMI2
#endif

#if defined(__AVX512VNNI__)
#define SPY_SIMD_IS_X86_AVX512_VNNI
#endif

#if defined(__AVX512VP2INTERSECT__)
#define SPY_SIMD_IS_X86_AVX512_VP2INTERSECT
#endif

#endif

#if !defined(SPY_SIMD_DETECTED) && defined(__AVX2__)
#define SPY_SIMD_IS_X86_AVX2
#define SPY_SIMD_DETECTED ::spy::_::simd_version::avx2_
#endif

#if !defined(SPY_SIMD_DETECTED) && defined(__AVX__)
#define SPY_SIMD_IS_X86_AVX
#define SPY_SIMD_DETECTED ::spy::_::simd_version::avx_
#endif

#if !defined(SPY_SIMD_DETECTED) && defined(__SSE4_2__)
#define SPY_SIMD_IS_X86_SSE4_2
#define SPY_SIMD_DETECTED ::spy::_::simd_version::sse42_
#endif

#if !defined(SPY_SIMD_DETECTED) && defined(__SSE4_1__)
#define SPY_SIMD_IS_X86_SSE4_1
#define SPY_SIMD_DETECTED ::spy::_::simd_version::sse41_
#endif

#if !defined(SPY_SIMD_DETECTED) && defined(__SSSE3__)
#define SPY_SIMD_IS_X86_SSSE3
#define SPY_SIMD_DETECTED ::spy::_::simd_version::ssse3_
#endif

#if !defined(SPY_SIMD_DETECTED) && defined(__SSE3__)
#define SPY_SIMD_IS_X86_SSE3
#define SPY_SIMD_DETECTED ::spy::_::simd_version::sse3_
#endif

#if !defined(SPY_SIMD_DETECTED) &&                                                                 \
    (defined(__SSE2__) || defined(_M_X64) || (defined(_M_IX86_FP) && _M_IX86_FP >= 2))
#define SPY_SIMD_IS_X86_SSE2
#define SPY_SIMD_DETECTED ::spy::_::simd_version::sse2_
#endif

#if !defined(SPY_SIMD_DETECTED) && (defined(__SSE__) || defined(_M_IX86_FP))
#define SPY_SIMD_IS_X86_SSE
#define SPY_SIMD_DETECTED ::spy::_::simd_version::sse1_
#endif

#if defined(SPY_SIMD_DETECTED) && !defined(SPY_SIMD_VENDOR)
#define SPY_SIMD_IS_X86
#define SPY_SIMD_VENDOR ::spy::_::simd_isa::x86_
#endif

namespace spy::supports
{
  //================================================================================================
  // Supplemental ISA
  //================================================================================================
#if defined(__FMA__)
#define SPY_SIMD_SUPPORTS_FMA
  constexpr inline bool fma_ = true;
#elif defined(SPY_DOXYGEN_INVOKED)
  //================================================================================================
  //! @ingroup spy_isa_supplemental
  //! @brief Fused multiply-add availability indicator
  //!
  //! Evaluates to `true` when the FMA3 instructions of the AVX family are enabled.
  //!
  //! @groupheader{Example}
  //! @godbolt{samples/simd-additional.cpp}
  //================================================================================================
  constexpr inline bool fma_ = _::implementation_defined {};
#else
  constexpr inline bool fma_ = false;
#endif

#if defined(__FMA4__)
#define SPY_SIMD_SUPPORTS_FMA4
  constexpr inline bool fma4_ = true;
#elif defined(SPY_DOXYGEN_INVOKED)
  //================================================================================================
  //! @ingroup spy_isa_supplemental
  //! @brief FMA4 availability indicator
  //!
  //! Evaluates to `true` when the FMA4 instructions of AMD's AVX implementation are enabled.
  //!
  //! @groupheader{Example}
  //! @godbolt{samples/simd-additional.cpp}
  //================================================================================================
  constexpr inline bool fma4_ = _::implementation_defined {};
#else
  constexpr inline bool fma4_ = false;
#endif

#if defined(__XOP__)
#define SPY_SIMD_SUPPORTS_XOP
  constexpr inline bool xop_ = true;
#elif defined(SPY_DOXYGEN_INVOKED)
  //================================================================================================
  //! @ingroup spy_isa_supplemental
  //! @brief XOP availability indicator
  //!
  //! Evaluates to `true` when the XOP instructions of AMD's AVX implementation are enabled.
  //!
  //! @groupheader{Example}
  //! @godbolt{samples/simd-additional.cpp}
  //================================================================================================
  constexpr inline bool xop_ = _::implementation_defined {};
#else
  constexpr inline bool xop_ = false;
#endif

#if defined(__F16C__)
#define SPY_SIMD_SUPPORTS_F16C
  constexpr inline bool f16c_ = true;
#elif defined(SPY_DOXYGEN_INVOKED)
  //================================================================================================
  //! @ingroup spy_isa_supplemental
  //! @brief Half-precision conversion availability indicator
  //!
  //! Evaluates to `true` when the F16C instructions converting between half and single
  //! precision are enabled.
  //!
  //! @groupheader{Example}
  //! @godbolt{samples/simd-additional.cpp}
  //================================================================================================
  constexpr inline bool f16c_ = _::implementation_defined {};
#else
  constexpr inline bool f16c_ = false;
#endif

  namespace avx512
  {
#if defined(__AVX512BW__)
#define SPY_SIMD_IS_X86_AVX512_BW
    constexpr inline bool bw_ = true;
#elif defined(SPY_DOXYGEN_INVOKED)
    //==============================================================================================
    //! @ingroup spy_isa_supplemental
    //! @brief AVX-512 Byte and Word availability indicator
    //!
    //! Evaluates to `true` when the AVX-512 Byte and Word subset is enabled.
    //!
    //! @groupheader{Example}
    //! @godbolt{samples/simd-additional.cpp}
    //==============================================================================================
    constexpr inline bool bw_ = _::implementation_defined {};
#else
    constexpr inline bool bw_ = false;
#endif

#if defined(__AVX512CD__)
#define SPY_SIMD_IS_X86_AVX512_CD
    constexpr inline bool cd_ = true;
#elif defined(SPY_DOXYGEN_INVOKED)
    //==============================================================================================
    //! @ingroup spy_isa_supplemental
    //! @brief AVX-512 Conflict Detection availability indicator
    //!
    //! Evaluates to `true` when the AVX-512 Conflict Detection subset is enabled.
    //!
    //! @groupheader{Example}
    //! @godbolt{samples/simd-additional.cpp}
    //==============================================================================================
    constexpr inline bool cd_ = _::implementation_defined {};
#else
    constexpr inline bool cd_ = false;
#endif

#if defined(__AVX512DQ__)
#define SPY_SIMD_IS_X86_AVX512_DQ
    constexpr inline bool dq_ = true;
#elif defined(SPY_DOXYGEN_INVOKED)
    //==============================================================================================
    //! @ingroup spy_isa_supplemental
    //! @brief AVX-512 Doubleword and Quadword availability indicator
    //!
    //! Evaluates to `true` when the AVX-512 Doubleword and Quadword subset is enabled.
    //!
    //! @groupheader{Example}
    //! @godbolt{samples/simd-additional.cpp}
    //==============================================================================================
    constexpr inline bool dq_ = _::implementation_defined {};
#else
    constexpr inline bool dq_ = false;
#endif

#if defined(__AVX512ER__)
#define SPY_SIMD_IS_X86_AVX512_ER
    constexpr inline bool er_ = true;
#elif defined(SPY_DOXYGEN_INVOKED)
    //==============================================================================================
    //! @ingroup spy_isa_supplemental
    //! @brief AVX-512 Exponential and Reciprocal availability indicator
    //!
    //! Evaluates to `true` when the AVX-512 Exponential and Reciprocal subset is enabled.
    //!
    //! @groupheader{Example}
    //! @godbolt{samples/simd-additional.cpp}
    //==============================================================================================
    constexpr inline bool er_ = _::implementation_defined {};
#else
    constexpr inline bool er_ = false;
#endif

#if defined(__AVX512IFMA__)
#define SPY_SIMD_IS_X86_AVX512_IFMA
    constexpr inline bool ifma_ = true;
#elif defined(SPY_DOXYGEN_INVOKED)
    //==============================================================================================
    //! @ingroup spy_isa_supplemental
    //! @brief AVX-512 Integer Fused Multiply-Add availability indicator
    //!
    //! Evaluates to `true` when the AVX-512 Integer Fused Multiply-Add subset is enabled.
    //!
    //! @groupheader{Example}
    //! @godbolt{samples/simd-additional.cpp}
    //==============================================================================================
    constexpr inline bool ifma_ = _::implementation_defined {};
#else
    constexpr inline bool ifma_ = false;
#endif

#if defined(__AVX512PF__)
#define SPY_SIMD_IS_X86_AVX512_PF
    constexpr inline bool pf_ = true;
#elif defined(SPY_DOXYGEN_INVOKED)
    //==============================================================================================
    //! @ingroup spy_isa_supplemental
    //! @brief AVX-512 Prefetch availability indicator
    //!
    //! Evaluates to `true` when the AVX-512 Prefetch subset is enabled.
    //!
    //! @groupheader{Example}
    //! @godbolt{samples/simd-additional.cpp}
    //==============================================================================================
    constexpr inline bool pf_ = _::implementation_defined {};
#else
    constexpr inline bool pf_ = false;
#endif

#if defined(__AVX512VL__)
#define SPY_SIMD_IS_X86_AVX512_VL
    constexpr inline bool vl_ = true;
#elif defined(SPY_DOXYGEN_INVOKED)
    //==============================================================================================
    //! @ingroup spy_isa_supplemental
    //! @brief AVX-512 Vector Length availability indicator
    //!
    //! Evaluates to `true` when the AVX-512 Vector Length subset, which applies the AVX-512
    //! instructions to 128 and 256 bit registers, is enabled.
    //!
    //! @groupheader{Example}
    //! @godbolt{samples/simd-additional.cpp}
    //==============================================================================================
    constexpr inline bool vl_ = _::implementation_defined {};
#else
    constexpr inline bool vl_ = false;
#endif

#if defined(__AVX512VPOPCNTDQ__)
#define SPY_SIMD_IS_X86_AVX512_POPCNTDQ
    constexpr inline bool popcntdq_ = true;
#elif defined(SPY_DOXYGEN_INVOKED)
    //==============================================================================================
    //! @ingroup spy_isa_supplemental
    //! @brief AVX-512 population count availability indicator
    //!
    //! Evaluates to `true` when the AVX-512 population count subset for doubleword and quadword
    //! elements is enabled.
    //!
    //! @groupheader{Example}
    //! @godbolt{samples/simd-additional.cpp}
    //==============================================================================================
    constexpr inline bool popcntdq_ = _::implementation_defined {};
#else
    constexpr inline bool popcntdq_ = false;
#endif

#if defined(__AVX5124FMAPS__)
#define SPY_SIMD_IS_X86_AVX512_4FMAPS
    constexpr inline bool _4fmaps_ = true;
#elif defined(SPY_DOXYGEN_INVOKED)
    //==============================================================================================
    //! @ingroup spy_isa_supplemental
    //! @brief AVX-512 4FMAPS availability indicator
    //!
    //! Evaluates to `true` when the AVX-512 four-iteration packed single-precision fused
    //! multiply-add subset is enabled.
    //!
    //! @groupheader{Example}
    //! @godbolt{samples/simd-additional.cpp}
    //==============================================================================================
    constexpr inline bool _4fmaps_ = _::implementation_defined {};
#else
    constexpr inline bool _4fmaps_ = false;
#endif

#if defined(__AVX5124VNNIW__)
#define SPY_SIMD_IS_X86_AVX512_VNNIW
    constexpr inline bool vnniw_ = true;
#elif defined(SPY_DOXYGEN_INVOKED)
    //==============================================================================================
    //! @ingroup spy_isa_supplemental
    //! @brief AVX-512 4VNNIW availability indicator
    //!
    //! Evaluates to `true` when the AVX-512 four-iteration word neural network subset is enabled.
    //!
    //! @groupheader{Example}
    //! @godbolt{samples/simd-additional.cpp}
    //==============================================================================================
    constexpr inline bool vnniw_ = _::implementation_defined {};
#else
    constexpr inline bool vnniw_ = false;
#endif

#if defined(__AVX512VBMI__)
#define SPY_SIMD_IS_X86_AVX512_VBMI
    constexpr inline bool vbmi_ = true;
#elif defined(SPY_DOXYGEN_INVOKED)
    //==============================================================================================
    //! @ingroup spy_isa_supplemental
    //! @brief AVX-512 Vector Byte Manipulation availability indicator
    //!
    //! Evaluates to `true` when the AVX-512 Vector Byte Manipulation subset is enabled.
    //!
    //! @groupheader{Example}
    //! @godbolt{samples/simd-additional.cpp}
    //==============================================================================================
    constexpr inline bool vbmi_ = _::implementation_defined {};
#else
    constexpr inline bool vbmi_ = false;
#endif

#if defined(__AVX512BF16__)
#define SPY_SIMD_IS_X86_AVX512_BF16
    constexpr inline bool bf16_ = true;
#elif defined(SPY_DOXYGEN_INVOKED)
    //==============================================================================================
    //! @ingroup spy_isa_supplemental
    //! @brief AVX-512 bfloat16 availability indicator
    //!
    //! Evaluates to `true` when the AVX-512 bfloat16 subset is enabled.
    //!
    //! @groupheader{Example}
    //! @godbolt{samples/simd-additional.cpp}
    //==============================================================================================
    constexpr inline bool bf16_ = _::implementation_defined {};
#else
    constexpr inline bool bf16_ = false;
#endif

#if defined(__AVX512BITALG__)
#define SPY_SIMD_IS_X86_AVX512_BITALG
    constexpr inline bool bitalg_ = true;
#elif defined(SPY_DOXYGEN_INVOKED)
    //==============================================================================================
    //! @ingroup spy_isa_supplemental
    //! @brief AVX-512 Bit Algorithms availability indicator
    //!
    //! Evaluates to `true` when the AVX-512 Bit Algorithms subset is enabled.
    //!
    //! @groupheader{Example}
    //! @godbolt{samples/simd-additional.cpp}
    //==============================================================================================
    constexpr inline bool bitalg_ = _::implementation_defined {};
#else
    constexpr inline bool bitalg_ = false;
#endif

#if defined(__AVX512VBMI2__)
#define SPY_SIMD_IS_X86_AVX512_VBMI2
    constexpr inline bool vbmi2_ = true;
#elif defined(SPY_DOXYGEN_INVOKED)
    //==============================================================================================
    //! @ingroup spy_isa_supplemental
    //! @brief AVX-512 Vector Byte Manipulation 2 availability indicator
    //!
    //! Evaluates to `true` when the second AVX-512 Vector Byte Manipulation subset is enabled.
    //!
    //! @groupheader{Example}
    //! @godbolt{samples/simd-additional.cpp}
    //==============================================================================================
    constexpr inline bool vbmi2_ = _::implementation_defined {};
#else
    constexpr inline bool vbmi2_ = false;
#endif

#if defined(__AVX512VNNI__)
#define SPY_SIMD_IS_X86_AVX512_VNNI
    constexpr inline bool vnni_ = true;
#elif defined(SPY_DOXYGEN_INVOKED)
    //==============================================================================================
    //! @ingroup spy_isa_supplemental
    //! @brief AVX-512 Vector Neural Network availability indicator
    //!
    //! Evaluates to `true` when the AVX-512 Vector Neural Network subset is enabled.
    //!
    //! @groupheader{Example}
    //! @godbolt{samples/simd-additional.cpp}
    //==============================================================================================
    constexpr inline bool vnni_ = _::implementation_defined {};
#else
    constexpr inline bool vnni_ = false;
#endif

#if defined(__AVX512VP2INTERSECT__)
#define SPY_SIMD_IS_X86_AVX512_VP2INTERSECT
    constexpr inline bool vpintersect_ = true;
#elif defined(SPY_DOXYGEN_INVOKED)
    //==============================================================================================
    //! @ingroup spy_isa_supplemental
    //! @brief AVX-512 vector pair intersection availability indicator
    //!
    //! Evaluates to `true` when the AVX-512 vector pair intersection subset is enabled.
    //!
    //! @groupheader{Example}
    //! @godbolt{samples/simd-additional.cpp}
    //==============================================================================================
    constexpr inline bool vpintersect_ = _::implementation_defined {};
#else
    constexpr inline bool vpintersect_ = false;
#endif
  }

}
