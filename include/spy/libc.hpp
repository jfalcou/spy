//==================================================================================================
/*
  SPY - C++ Informations Broker
  Copyright 2020 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
 */
//==================================================================================================
#ifndef SPY_LIBC_HPP_INLUDED
#define SPY_LIBC_HPP_INLUDED

// Make sure the proper header is included to detect GNU libc
#include <cstddef>
#include <iosfwd>
#include <spy/detail.hpp>

namespace spy::detail
{
  enum class libC  { undefined_  = - 1, cloudabi_, uc_, vms_, zos_, gnu_ };

  template<libC Lib, int M, int N, int P> struct libc_info
  {
    static constexpr libC               vendor  = Lib;
    static constexpr version_id<M,N,P>  version = {};

    inline constexpr operator bool() const noexcept;

    template<libC C2>
    constexpr bool operator==(libc_info<C2,-1,0,0> const& c2) const noexcept
    {
      return C2 == vendor;
    }

    SPY_VERSION_COMPARISONS_OPERATOR(libC,libc_info)
  };

  template<libC C, int M, int N, int P>
  std::ostream& operator<<(std::ostream& os, libc_info<C, M, N, P> const& c)
  {
    if(c.vendor == libC::cloudabi_) return os << "CloudABI Standard C Library " << c.version;
    if(c.vendor == libC::uc_      ) return os << "uClibc Standard C Library "   << c.version;
    if(c.vendor == libC::vms_     ) return os << "VMS Standard C Library "      << c.version;
    if(c.vendor == libC::zos_     ) return os << "z/OS Standard C Library "    << c.version;
    if(c.vendor == libC::gnu_     ) return os << "GNU Standard C Library "     << c.version;

    return os << "Undefined Standard C Library";
  }

  template<int M, int N, int P> using cloudabi_t  = libc_info<libC::cloudabi_ ,M,N,P>;
  template<int M, int N, int P> using uc_t        = libc_info<libC::uc_ ,M,N,P>;
  template<int M, int N, int P> using vms_t       = libc_info<libC::vms_,M,N,P>;
  template<int M, int N, int P> using zos_t       = libc_info<libC::zos_,M,N,P>;
  template<int M, int N, int P> using gnu_t       = libc_info<libC::gnu_,M,N,P>;
}

namespace spy
{
  //================================================================================================
  // LIBC detection object type
  //================================================================================================
#if defined(__cloudlibc__)
  using libc_type = detail::cloudabi_t<__cloudlibc_major__,__cloudlibc_minor__,0>;
#elif defined(__GLIBC__)
  using libc_type = detail::gnu_t<__GLIBC__, __GLIBC_MINOR__, 0>;
#elif defined(__GNU_LIBRARY__)
  using libc_type = detail::gnu_t<__GNU_LIBRARY__, __GNU_LIBRARY_MINOR__, 0>;
#elif defined(__UCLIBC__)
  using libc_type = detail::uc_t<__UCLIBC_MAJOR__, __UCLIBC_MINOR__, __UCLIBC_SUBLEVEL__>;
#elif defined(__CRTL_VER)
  #define SPY0  (__CRTL_VER/100)
  using libc_type = detail::vms_t<(SPY0/100000)%100, (SPY0/1000)%100, (SPY0)%100>;
  #undef SPY0
#elif defined(__LIBREL__)
  using libc_type = detail::zos_t < (__LIBREL__&0xF000000)>>24
                                  , (__LIBREL__&0xFF0000)>>16
                                  , (__LIBREL__&0xFFFF)
                                  >;
#else
  using libc_type = detail::libc_info<detail::libC::undefined_,-1,0,0>;
#endif

  //================================================================================================
  // LIBC detection object
  //================================================================================================
  constexpr inline libc_type libc;
}

namespace spy::detail
{
  template<libC C, int M, int N, int P>
  inline constexpr libc_info<C,M,N,P>::operator bool() const noexcept
  {
    return *this == spy::libc;
  }
}

namespace spy
{
  //================================================================================================
  // LIBCs detector stand-alone instances
  //================================================================================================
  constexpr inline auto  cloudabi_  = detail::cloudabi_t<-1,0,0>{};
  constexpr inline auto  uc_        = detail::uc_t<-1,0,0>{};
  constexpr inline auto  vms_       = detail::vms_t<-1,0,0>{};
  constexpr inline auto  zos_       = detail::zos_t<-1,0,0>{};
  constexpr inline auto  gnu_       = detail::gnu_t<-1,0,0>{};
}

namespace spy::literal
{
  template<char ...c> constexpr auto operator"" _cloud()
  {
    return detail::literal_wrap<detail::cloudabi_t,c...>();
  }

  template<char ...c> constexpr auto operator"" _uc()
  {
    return detail::literal_wrap<detail::uc_t,c...>();
  }

  template<char ...c> constexpr auto operator"" _vms()
  {
    return detail::literal_wrap<detail::vms_t,c...>();
  }

  template<char ...c> constexpr auto operator"" _zos()
  {
    return detail::literal_wrap<detail::zos_t,c...>();
  }

  template<char ...c> constexpr auto operator"" _gnu()
  {
    return detail::literal_wrap<detail::gnu_t,c...>();
  }
}

#endif
