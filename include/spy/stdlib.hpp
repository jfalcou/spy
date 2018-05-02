//==================================================================================================
/*
  Copyright 2018 Joel FALCOU

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */
//==================================================================================================
#ifndef SPY_STDLIB_HPP_INLUDED
#define SPY_STDLIB_HPP_INLUDED

// Make sure the proper header is included to detect libstd
#include <cstddef>

#include <iosfwd>
#include <spy/version.hpp>

namespace spy
{
  enum class stdlib_  { undefined_  = - 1, libcpp_, gcc_ };

  inline std::ostream& operator<<(std::ostream& os, stdlib_ const& c)
  {
    if(c == stdlib_::libcpp_  ) return os << "libc++ Standard C++ Library";
    if(c == stdlib_::gcc_     ) return os << "GNU Standard C++ Library";
    return os << "Undefined Standard C++ Library";
  }

  namespace detail
  {
    template<stdlib_ Vendor, int M, int N, int P> struct stdlib_info
    {
      static constexpr stdlib_            vendor  = Vendor;
      static constexpr version_<M,N,P>  version = {};
    };

    template<stdlib_ Vendor, int M, int N, int P>
    constexpr bool operator==(stdlib_info<Vendor, M, N, P> const& d, stdlib_ const c)
    {
      return d.vendor == c;
    }

    template<stdlib_ Vendor, int M, int N, int P>
    std::ostream& operator<<(std::ostream& os, stdlib_info<Vendor, M, N, P> const& c)
    {
      return os << c.vendor << " " << c.version;
    }
  }

#if defined(_LIBCPP_VERSION)
  //================================================================================================
  // CloudABI
  //================================================================================================
  constexpr inline detail::stdlib_info< stdlib_::libcpp_
                                    , (_LIBCPP_VERSION/1000)%10,0,_LIBCPP_VERSION%1000
                                    > current_stdlib_;

#elif defined(__GLIBCXX__)
  //================================================================================================
  // GLIBS version 6 or later
  //================================================================================================
  constexpr inline detail::stdlib_info< stdlib_::gcc_
                                      , (__GLIBCXX__/10000)%10000
                                      , (__GLIBCXX__/100)%100
                                      , __GLIBCXX__%100
                                      > current_stdlib_;

#else
  //================================================================================================
  // Unsupported libstd
  //================================================================================================
  constexpr inline detail::stdlib_info<stdlib_::undefined_,-1,0,0> current_stdlib_;

#endif
}

#endif
