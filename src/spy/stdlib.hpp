//==================================================================================================
/**
  SPY - C++ Informations Broker
  Copyright : SPY Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#pragma once

// Make sure the proper header is included to detect libstd
#include <cstddef>
#include <spy/detail.hpp>

namespace spy::detail
{
  enum class stdlib { undefined_  = - 1, libcpp_, gnucpp_ };

  template<stdlib Lib, int M, int N, int P> struct stdlib_info
  {
    static constexpr stdlib             vendor  = Lib;
    static constexpr version_id<M,N,P>  version = {};

    inline constexpr explicit operator bool() const noexcept;

    template<stdlib C2>
    constexpr bool operator==(stdlib_info<C2,-1,0,0> const&) const noexcept
    {
      return C2 == vendor;
    }

    SPY_VERSION_COMPARISONS_OPERATOR(stdlib,stdlib_info)
  };

  template<stdlib SLib, int M, int N, int P>
  std::ostream& operator<<(std::ostream& os, stdlib_info<SLib, M, N, P> const& p)
  {
    if(SLib == stdlib::libcpp_) return os << "libc++ Standard C++ Library " << p.version ;
    if(SLib == stdlib::gnucpp_) return os << "GNU Standard C++ Library" << p.version;

    return os << "Undefined Standard C++ Library";
  }

  template<int M, int N, int P> using libcpp_t = stdlib_info<stdlib::libcpp_,M,N,P>;
  template<int M, int N, int P> using gnucpp_t = stdlib_info<stdlib::gnucpp_,M,N,P>;
}

namespace spy
{
#if defined(_LIBCPP_VERSION)
  #define SPY_STDLIB_IS_LIBCPP
  using stdlib_type = detail::libcpp_t<(_LIBCPP_VERSION/1000)%10,0,_LIBCPP_VERSION%1000>;
#elif defined(__GLIBCXX__)
  #define SPY_STDLIB_IS_GLIBCXX
  #define SPY0 (__GLIBCXX__/100)
  using stdlib_type = detail::gnucpp_t<(SPY0/100)%10000, SPY0%100, __GLIBCXX__%100>;
  #undef SPY0
#else
  #define SPY_STDLIB_IS_UNKNOWN
  using stdlib_type = detail::stdlib_info<detail::stdlib::undefined_,-1,0,0>;
#endif

  //================================================================================================
  // STDLIB detection object
  //================================================================================================
  constexpr inline stdlib_type stdlib;
}

namespace spy::detail
{
  template<stdlib SLib, int M, int N, int P>
  inline constexpr stdlib_info<SLib,M,N,P>::operator bool() const noexcept
  {
    return *this == spy::stdlib;
  }
}

namespace spy
{
  //================================================================================================
  // STDLIBs detector stand-alone instances
  //================================================================================================
  constexpr inline auto  libcpp_  = detail::libcpp_t<-1,0,0>{};
  constexpr inline auto  gnucpp_  = detail::gnucpp_t<-1,0,0>{};
}

namespace spy::literal
{
  template<char ...c> constexpr auto operator"" _libcpp()
  {
    return detail::literal_wrap<detail::libcpp_t,c...>();
  }

  template<char ...c> constexpr auto operator"" _gnucpp()
  {
    return detail::literal_wrap<detail::gnucpp_t,c...>();
  }
}
