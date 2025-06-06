//==================================================================================================
/*
  SPY - C++ Informations Broker
  Copyright : SPY Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <spy/detail.hpp>

#if defined __has_include
#if __has_include(<emscripten/version.h>)
#include <emscripten/version.h>
#endif
#endif

namespace spy::_
{
  enum class compilers
  {
    undefined_ = -1,
    msvc_,
    intel_,
    clang_,
    gcc_,
    emscripten_,
    dpcpp_,
    nvcc_
  };

  template<compilers Compiler, int M, int N, int P> struct compilers_info
  {
    static constexpr compilers vendor = Compiler;
    static constexpr version_id<M, N, P> version = {};

    inline constexpr explicit operator bool() const noexcept;

    template<compilers C2> constexpr bool operator==(compilers_info<C2, -1, 0, 0> const&) const noexcept
    {
      return C2 == vendor;
    }

    SPY_VERSION_COMPARISONS_OPERATOR(compilers, compilers_info)
  };

  template<_::stream OS, compilers C, int M, int N, int P> OS& operator<<(OS& os, compilers_info<C, M, N, P> const& c)
  {
    if (C == compilers::nvcc_) return os << "NVIDIA CUDA Compiler " << c.version;
    if (C == compilers::msvc_) return os << "Microsoft Visual Studio " << c.version;
    if (C == compilers::intel_) return os << "Intel(R) C++ Compiler " << c.version;
    if (C == compilers::dpcpp_) return os << "Intel(R) oneAPI DPC++/C++ Compiler " << c.version;
    if (C == compilers::clang_) return os << "clang " << c.version;
    if (C == compilers::gcc_) return os << "g++ " << c.version;
    if (C == compilers::emscripten_) return os << "Emscripten " << c.version;

    return os << "Undefined " << c.version;
  }

  template<int M, int N, int P> using msvc_t = compilers_info<compilers::msvc_, M, N, P>;
  template<int M, int N, int P> using intel_t = compilers_info<compilers::intel_, M, N, P>;
  template<int M, int N, int P> using dpcpp_t = compilers_info<compilers::dpcpp_, M, N, P>;
  template<int M, int N, int P> using nvcc_t = compilers_info<compilers::nvcc_, M, N, P>;
  template<int M, int N, int P> using clang_t = compilers_info<compilers::clang_, M, N, P>;
  template<int M, int N, int P> using gcc_t = compilers_info<compilers::gcc_, M, N, P>;
  template<int M, int N, int P> using emscripten_t = compilers_info<compilers::emscripten_, M, N, P>;
}

namespace spy
{
  //================================================================================================
  // Compiler detection object type
  //================================================================================================
#if defined(__NVCC__)
#define SPY_COMPILER_IS_NVCC
  using compiler_type = _::nvcc_t<__CUDACC_VER_MAJOR__, __CUDACC_VER_MINOR__, 0>;
#elif defined(_MSC_VER)
#define SPY_COMPILER_IS_MSVC
  using compiler_type = _::msvc_t<_MSC_VER / 100, _MSC_VER % 100, _MSC_FULL_VER % 100000>;
#elif defined(__INTEL_LLVM_COMPILER)
#define SPY_COMPILER_IS_INTEL_DPCPP
#define SPY0 __INTEL_LLVM_COMPILER
  using compiler_type = _::dpcpp_t<SPY0 / 10000, (SPY0 / 100) % 100, SPY0 % 100>;
#undef SPY0
#elif defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC) || defined(__ECC)
#define SPY_COMPILER_IS_INTEL
#define SPY0 __INTEL_COMPILER
  using compiler_type = _::intel_t<(SPY0 / 100) % 100, SPY0 % 100, __INTEL_COMPILER_UPDATE>;
#undef SPY0
#elif defined(__EMSCRIPTEN__)
#define SPY_COMPILER_IS_CLANG
  using compiler_type = _::emscripten_t<__EMSCRIPTEN_major__, __EMSCRIPTEN_minor__, __EMSCRIPTEN_tiny__>;
#undef SPY0
#elif defined(__clang__)
#define SPY_COMPILER_IS_CLANG
  using compiler_type = _::clang_t<__clang_major__, __clang_minor__, __clang_patchlevel__>;
#elif defined(__GNUC__)
#define SPY_COMPILER_IS_GCC
  using compiler_type = _::gcc_t<__GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__>;
#else
#define SPY_COMPILER_IS_UNKNOWN
  using compiler_type = _::compilers_info<compilers::undefined_, -1, 0, 0>;
#endif

  //================================================================================================
  //! @ingroup api
  //! @brief Compiler reporting value
  //!
  //! The `spy::compiler` object can be compared to any other compiler related value to verify
  //! if the code being compiled with a specific compiler.
  //!
  //! Any compiler related value can be checked for equality or ordering for a given version. The targeted
  //! version is then specified using a compiler-dependent literal.
  //!
  //! Additionally, any of the compiler related value are convertible to `bool`. They evaluates to `true` if they
  //! matches the correct compiler currently used.
  //!
  //! @groupheader{Supported Value}
  //!
  //! Name              | Compiler
  //! ----------------- | -------------
  //! `spy::clang`      | Clang
  //! `spy::dpcpp`      | Intel DPC++/ICPX
  //! `spy::emscripten` | Emscripten
  //! `spy::gcc`        | G++
  //! `spy::intel`      | Intel ICC
  //! `spy::msvc`       | Microsoft Visual Studio
  //! `spy::nvcc`       | NVIDIA NVCC
  //!
  //! @groupheader{Example}
  //! @godbolt{samples/compiler.cpp}
  //================================================================================================
  constexpr inline compiler_type compiler;
}

namespace spy::_
{
  template<compilers C, int M, int N, int P> inline constexpr compilers_info<C, M, N, P>::operator bool() const noexcept
  {
    return spy::compiler == *this;
  }
}

namespace spy
{
  //================================================================================================
  // Compilers detector stand-alone instances
  //================================================================================================
  constexpr inline auto nvcc_ = _::nvcc_t<-1, 0, 0>{};
  constexpr inline auto msvc_ = _::msvc_t<-1, 0, 0>{};
  constexpr inline auto intel_ = _::intel_t<-1, 0, 0>{};
  constexpr inline auto dpcpp_ = _::dpcpp_t<-1, 0, 0>{};
  constexpr inline auto clang_ = _::clang_t<-1, 0, 0>{};
  constexpr inline auto gcc_ = _::gcc_t<-1, 0, 0>{};
  constexpr inline auto emscripten_ = _::emscripten_t<-1, 0, 0>{};
}

namespace spy::literal
{
  //! @ingroup api
  //! @brief User-defined suffix for NVCC version definition
  template<char... c> constexpr auto operator""_nvcc()
  {
    return _::literal_wrap<_::nvcc_t, c...>();
  }

  //! @ingroup api
  //! @brief User-defined suffix for MSVC version definition
  template<char... c> constexpr auto operator""_msvc()
  {
    return _::literal_wrap<_::msvc_t, c...>();
  }

  //! @ingroup api
  //! @brief User-defined suffix for Intel ICC version definition
  template<char... c> constexpr auto operator""_intel()
  {
    return _::literal_wrap<_::intel_t, c...>();
  }

  //! @ingroup api
  //! @brief User-defined suffix for Intel DCP++/ICPX version definition
  template<char... c> constexpr auto operator""_dpcpp()
  {
    return _::literal_wrap<_::dpcpp_t, c...>();
  }

  //! @ingroup api
  //! @brief User-defined suffix for Clang version definition
  template<char... c> constexpr auto operator""_clang()
  {
    return _::literal_wrap<_::clang_t, c...>();
  }

  //! @ingroup api
  //! @brief User-defined suffix for G++ version definition
  template<char... c> constexpr auto operator""_gcc()
  {
    return _::literal_wrap<_::gcc_t, c...>();
  }

  //! @ingroup api
  //! @brief User-defined suffix for Emscripten version definition
  template<char... c> constexpr auto operator""_em()
  {
    return _::literal_wrap<_::emscripten_t, c...>();
  }
}
