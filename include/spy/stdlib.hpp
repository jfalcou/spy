//==================================================================================================
/*
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
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
  enum class stdlib { undefined_  = - 1, libcpp_, gcc_ };

  inline std::ostream& operator<<(std::ostream& os, stdlib const& c)
  {
    if(c == stdlib::libcpp_  ) return os << "libc++ Standard C++ Library";
    if(c == stdlib::gcc_     ) return os << "GNU Standard C++ Library";
    return os << "Undefined Standard C++ Library";
  }

  namespace detail
  {
    template<stdlib Vendor, int M, int N, int P> struct stdlib_info
    {
      static constexpr stdlib            vendor  = Vendor;
      static constexpr version_id<M,N,P>  version = {};

      inline constexpr operator stdlib() const { return vendor; }
    };

    template<stdlib Vendor, int M, int N, int P>
    constexpr bool operator==(stdlib_info<Vendor, M, N, P> const& d, stdlib const c)
    {
      return d.vendor == c;
    }

    template<stdlib Vendor, int M, int N, int P>
    std::ostream& operator<<(std::ostream& os, stdlib_info<Vendor, M, N, P> const& c)
    {
      return os << c.vendor << " " << c.version;
    }
  }

#if defined(_LIBCPP_VERSION)
  //================================================================================================
  // CloudABI
  //================================================================================================
  constexpr inline detail::stdlib_info< stdlib::libcpp_
                                    , (_LIBCPP_VERSION/1000)%10,0,_LIBCPP_VERSION%1000
                                    > current_stdlib;

#elif defined(__GLIBCXX__)
  //================================================================================================
  // GLIBS version 6 or later
  //================================================================================================
  constexpr inline detail::stdlib_info< stdlib::gcc_
                                      , (__GLIBCXX__/10000)%10000
                                      , (__GLIBCXX__/100)%100
                                      , __GLIBCXX__%100
                                      > current_stdlib;

#else
  //================================================================================================
  // Unsupported libstd
  //================================================================================================
  constexpr inline detail::stdlib_info<stdlib::undefined_,-1,0,0> current_stdlib;
#endif

  template<stdlib TargetLib>
  struct is_stdlib : std::integral_constant<bool, TargetLib == current_stdlib.vendor>
  {};

  template<stdlib TargetLib> using is_stdlib_t = typename is_stdlib<TargetLib>::type;
  template<stdlib TargetLib> constexpr inline bool  is_stdlib_v = is_stdlib<TargetLib>::value;
}

#endif
