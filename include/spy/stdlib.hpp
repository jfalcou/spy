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
#include <spy/detail.hpp>

namespace spy { namespace detail
{
  enum class stdlib { undefined_  = - 1, libcpp_, gnucpp_ };

  template<stdlib Lib, int M, int N, int P> struct stdlib_info
  {
    static constexpr stdlib             vendor  = Lib;
    static constexpr version_id<M,N,P>  version = {};

    inline constexpr operator bool() const noexcept;

    template<stdlib C2>
    constexpr bool operator==(stdlib_info<C2,-1,0,0> const& c2) const noexcept
    {
      return C2 == vendor;
    }

    SPY_VERSION_COMPARISONS_OPERATOR(stdlib,stdlib_info)
  };

  template<stdlib SLIB, int M, int N, int P>
  std::ostream& operator<<(std::ostream& os, stdlib_info<SLIB, M, N, P> const&)
  {
    if(SLIB == stdlib::libcpp_) return os << "libc++ Standard C++ Library";
    if(SLIB == stdlib::gnucpp_) return os << "GNU Standard C++ Library";

    return os << "Undefined Standard C++ Library";
  }

  template<int M, int N, int P> using libcpp_t        = stdlib_info<stdlib::libcpp_,M,N,P>;
  template<int M, int N, int P> using gnucpp_t        = stdlib_info<stdlib::gnucpp_,M,N,P>;
} }

namespace spy
{
#if defined(_LIBCPP_VERSION)
  using stdlib_type = detail::stdcpp_t<(_LIBCPP_VERSION/1000)%10,0,_LIBCPP_VERSION%1000,0>;
#elif defined(__GLIBCXX__)
  #define SPY0 (__GLIBCXX__/100)
  using stdlib_type = detail::gnucpp_t<(SPY0/100)%10000, SPY0%100, __GLIBCXX__%100>;
  #undef SPY0
#else
  using stdlib_type = detail::stdlib_info<detail::stdlib::undefined_,-1,0,0>;
#endif

  //================================================================================================
  // STDLIB detection object
  //================================================================================================
  constexpr inline stdlib_type stdlib;
}

namespace spy { namespace detail
{
  template<stdlib SLIB, int M, int N, int P>
  inline constexpr stdlib_info<SLIB,M,N,P>::operator bool() const noexcept
  {
    return *this == spy::stdlib;
  }
} }

namespace spy
{
  //================================================================================================
  // STDLIBs detector stand-alone instances
  //================================================================================================
  constexpr inline auto  libcpp_  = detail::libcpp_t<-1,0,0>{};
  constexpr inline auto  gnucpp_  = detail::gnucpp_t<-1,0,0>{};
}

namespace spy { namespace literal
{
  template<char ...c> constexpr auto operator"" _libcpp()
  {
    return detail::literal_wrap<detail::libcpp_t,c...>();
  }

  template<char ...c> constexpr auto operator"" _gnucpp()
  {
    return detail::literal_wrap<detail::gnucpp_t,c...>();
  }
} }

#endif
