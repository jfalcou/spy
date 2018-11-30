//==================================================================================================
/*
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
 */
//==================================================================================================
#ifndef SPY_COMPILER_HPP_INLUDED
#define SPY_COMPILER_HPP_INLUDED

#include <iosfwd>
#include <spy/detail.hpp>

namespace spy { namespace detail
{
  enum class compilers { undefined_  = - 1, msvc_, intel_, clang_, gcc_ };

  template<compilers Compiler, int M, int N, int P> struct compilers_info
  {
    static constexpr compilers          vendor  = Compiler;
    static constexpr version_id<M,N,P>  version = {};

    inline constexpr operator bool() const noexcept;

    template<compilers C2>
    constexpr bool operator==(compilers_info<C2,-1,0,0> const& c2) const noexcept
    {
      return C2 == vendor;
    }

    SPY_VERSION_COMPARISONS_OPERATOR(compilers,compilers_info)
  };

  template<compilers C, int M, int N, int P>
  std::ostream& operator<<(std::ostream& os, compilers_info<C, M, N, P> const& c)
  {
    if(C == compilers::msvc_ ) return os << "Microsoft Visual Studio "  << c.version;
    if(C == compilers::intel_) return os << "Intel icpc "               << c.version;
    if(C == compilers::clang_) return os << "clang "                    << c.version;
    if(C == compilers::gcc_  ) return os << "g++ "                      << c.version;

    return os << "Undefined " << c.version;
  }

  template<int M, int N, int P> using msvc_t  = compilers_info<compilers::msvc_ ,M,N,P>;
  template<int M, int N, int P> using intel_t = compilers_info<compilers::intel_,M,N,P>;
  template<int M, int N, int P> using clang_t = compilers_info<compilers::clang_,M,N,P>;
  template<int M, int N, int P> using gcc_t   = compilers_info<compilers::gcc_  ,M,N,P>;
} }

namespace spy
{
  //================================================================================================
  // Compiler detection object type
  //================================================================================================
#if defined(_MSC_VER)
  using compiler_type = detail::msvc_t<_MSC_VER / 100, _MSC_VER % 100, _MSC_FULL_VER % 100000>;
#elif defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC) || defined(__ECC)
  #define SPY0 __INTEL_COMPILER
  using compiler_type = detail::intel_t<(SPY0 / 100) % 100,SPY0 % 100, __INTEL_COMPILER_UPDATE>;
  #undef SPY0
#elif defined(__clang__)
  using compiler_type = detail::clang_t<__clang_major__, __clang_minor__, __clang_patchlevel__>;
#elif defined(__GNUC__)
  using compiler_type = detail::gcc_t<__GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__>;
#else
  using compiler_type = detail::compilers_info<compilers::undefined_,-1,0,0>;
#endif

  //================================================================================================
  // Compiler detection object
  //================================================================================================
  constexpr inline compiler_type compiler;
}

namespace spy { namespace detail
{
  template<compilers C, int M, int N, int P>
  inline constexpr compilers_info<C,M,N,P>::operator bool() const noexcept
  {
    return *this == spy::compiler;
  }
} }

namespace spy
{
  //================================================================================================
  // Compilers detector stand-alone instances
  //================================================================================================
  constexpr inline auto  msvc_   = detail::msvc_t<-1,0,0>{};
  constexpr inline auto  intel_  = detail::intel_t<-1,0,0>{};
  constexpr inline auto  clang_  = detail::clang_t<-1,0,0>{};
  constexpr inline auto  gcc_    = detail::gcc_t<-1,0,0>{};
}

namespace spy { namespace literal
{
  template<char ...c> constexpr auto operator"" _msvc()
  {
    return detail::literal_wrap<detail::msvc_t,c...>();
  }

  template<char ...c> constexpr auto operator"" _intel()
  {
    return detail::literal_wrap<detail::intel_t,c...>();
  }

  template<char ...c> constexpr auto operator"" _clang()
  {
    return detail::literal_wrap<detail::clang_t,c...>();
  }

  template<char ...c> constexpr auto operator"" _gcc()
  {
    return detail::literal_wrap<detail::gcc_t,c...>();
  }
} }

#endif
