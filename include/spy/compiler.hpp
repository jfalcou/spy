//==================================================================================================
/*
  Copyright 2018 Joel FALCOU

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */
//==================================================================================================
#ifndef SPY_COMPILER_HPP_INLUDED
#define SPY_COMPILER_HPP_INLUDED

#include <iosfwd>
#include <spy/version.hpp>

namespace spy
{
  enum class compilers { undefined_  = - 1, msvc_, intel_, clang_, gcc_ };

  inline std::ostream& operator<<(std::ostream& os, compilers const& c)
  {
    if(c == compilers::msvc_ ) return os << "Microsoft Visual Studio";
    if(c == compilers::intel_) return os << "Intel icpc";
    if(c == compilers::clang_) return os << "clang";
    if(c == compilers::gcc_  ) return os << "g++";
    return os << "Undefined";
  }

  namespace detail
  {
    template<compilers Compiler, int M, int N, int P> struct compilers_info
    {
      static constexpr compilers              vendor  = Compiler;
      static constexpr version_vendor<M,N,P>  version = {};

      inline constexpr operator compilers() const { return vendor; }
    };

    template<compilers Compiler, int M, int N, int P>
    constexpr bool operator==(compilers_info<Compiler, M, N, P> const& d, compilers const c)
    {
      return d.vendor == c;
    }

    template<compilers Compiler, int M, int N, int P>
    std::ostream& operator<<(std::ostream& os, compilers_info<Compiler, M, N, P> const& c)
    {
      return os << c.vendor << " " <<c.version;
    }
  }

#if defined(_MSC_VER)
  //================================================================================================
  // MSVC compilers
  //================================================================================================
  constexpr inline detail::compilers_info< compilers::msvc_, _MSC_VER/100
                                                          , _MSC_VER%100
                                                          , _MSC_FULL_VER % 100000
                                        > current_compiler;

#elif defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC) || defined(__ECC)
  //================================================================================================
  // Intel compilers
  //================================================================================================
  constexpr inline detail::compilers_info< compilers::intel_ , (__INTEL_COMPILER/100)%100
                                                            , __INTEL_COMPILER % 100
                                                            , __INTEL_COMPILER_UPDATE
                                        > current_compiler;

#elif defined(__clang__)
  //================================================================================================
  // Clang compilers
  //================================================================================================
  constexpr inline detail::compilers_info< compilers::clang_ , __clang_major__
                                                            , __clang_minor__
                                                            , __clang_patchlevel__
                                        > current_compiler;

#elif defined(__GNUC__)
  //================================================================================================
  // GCC compilers
  //================================================================================================
  constexpr inline detail::compilers_info< compilers::gcc_ , __GNUC__
                                                          , __GNUC_MINOR__
                                                          , __GNUC_PATCHLEVEL__
                                        > current_compiler;

#else
  //================================================================================================
  // Unsupported compilers
  //================================================================================================
  constexpr inline detail::compilers_info<compilers::undefined_,-1,0,0> current_compiler;

#endif

  template<compilers TargetCompiler>
  struct is_compiler : std::integral_constant<bool, TargetCompiler == current_compiler.vendor>
  {};

  template<compilers TargetCompiler>
  using is_compilerst = typename is_compiler<TargetCompiler>::type;

  template<compilers TargetCompiler>
  constexpr inline bool is_compilersv = is_compiler<TargetCompiler>::value;
}

#endif
