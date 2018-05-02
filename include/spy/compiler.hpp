//==================================================================================================
/*
  Copyright 2018 Joel FALCOU

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */
//==================================================================================================
#ifndef SPY_COMPILER_COMPILER_HPP_INLUDED
#define SPY_COMPILER_COMPILER_HPP_INLUDED

#include <iosfwd>
#include <spy/version.hpp>

namespace spy
{
  enum class compiler_ { undefined_  = - 1, msvc_, intel_, clang_, gcc_ };

  inline std::ostream& operator<<(std::ostream& os, compiler_ const& c)
  {
    if(c == compiler_::msvc_ ) return os << "Microsoft Visual Studio";
    if(c == compiler_::intel_) return os << "Intel icpc";
    if(c == compiler_::clang_) return os << "clang";
    if(c == compiler_::gcc_  ) return os << "g++";
    return os << "Undefined";
  }

  namespace detail
  {
    template<compiler_ Compiler, int M, int N, int P> struct compiler_info
    {
      static constexpr compiler_        id      = Compiler;
      static constexpr version_<M,N,P>  version = {};
    };

    template<compiler_ Compiler, int M, int N, int P>
    constexpr bool operator==(compiler_info<Compiler, M, N, P> const& d, compiler_ const c)
    {
      return d.id == c;
    }

    template<compiler_ Compiler, int M, int N, int P>
    std::ostream& operator<<(std::ostream& os, compiler_info<Compiler, M, N, P> const& c)
    {
      return os << c.id << " " <<c.version;
    }
  }

#if defined(_MSC_VER)
  //================================================================================================
  // MSVC compilers
  //================================================================================================
  constexpr inline detail::compiler_info< compiler_::msvc_, _MSC_VER/100
                                                          , _MSC_VER%100
                                                          , _MSC_FULL_VER % 100000
                                        > current_compiler_;

#elif defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC) || defined(__ECC)
  //================================================================================================
  // Intel compilers
  //================================================================================================
  constexpr inline detail::compiler_info< compiler_::intel_ , (__INTEL_COMPILER/100)%100
                                                            , __INTEL_COMPILER % 100
                                                            , __INTEL_COMPILER_UPDATE
                                        > current_compiler_;

#elif defined(__clang__)
  //================================================================================================
  // Clang compilers
  //================================================================================================
  constexpr inline detail::compiler_info< compiler_::clang_ , __clang_major__
                                                            , __clang_minor__
                                                            , __clang_patchlevel__
                                        > current_compiler_;

#elif defined(__GNUC__)
  //================================================================================================
  // GCC compilers
  //================================================================================================
  constexpr inline detail::compiler_info< compiler_::gcc_ , __GNUC__
                                                          , __GNUC_MINOR__
                                                          , __GNUC_PATCHLEVEL__
                                        > current_compiler_;

#else
  //================================================================================================
  // Unsupported compilers
  //================================================================================================
  constexpr inline detail::compiler_info<compiler_::undefined_,0,0,0> current_compiler_;

#endif
}

#endif
