//==================================================================================================
/*
  Copyright 2018 Joel FALCOU

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */
//==================================================================================================
#ifndef SPY_LIBC_HPP_INLUDED
#define SPY_LIBC_HPP_INLUDED

// Make sure the proper header is included to detect GNU libc
#include <cstddef>

#include <iosfwd>
#include <spy/version.hpp>

namespace spy
{
  enum class libc_  { undefined_  = - 1, cloudabi_, uc_, vms_, zos_, gcc_ };

  inline std::ostream& operator<<(std::ostream& os, libc_ const& c)
  {
    if(c == libc_::cloudabi_) return os << "CloudABI Standard C Library";
    if(c == libc_::uc_      ) return os << "uClibc Standard C Library";
    if(c == libc_::vms_     ) return os << "VMS Standard C Library";
    if(c == libc_::zos_     ) return os << "z/OS Standard C Library";
    if(c == libc_::gcc_     ) return os << "GNU Standard C Library";
    return os << "Undefined Standard C Library";
  }

  namespace detail
  {
    template<libc_ Vendor, int M, int N, int P> struct libc_info
    {
      static constexpr libc_            vendor  = Vendor;
      static constexpr version_<M,N,P>  version = {};
    };

    template<libc_ Vendor, int M, int N, int P>
    constexpr bool operator==(libc_info<Vendor, M, N, P> const& d, libc_ const c)
    {
      return d.vendor == c;
    }

    template<libc_ Vendor, int M, int N, int P>
    std::ostream& operator<<(std::ostream& os, libc_info<Vendor, M, N, P> const& c)
    {
      return os << c.vendor << " " << c.version;
    }
  }

#if defined(__cloudlibc__)
  //================================================================================================
  // CloudABI
  //================================================================================================
  constexpr inline detail::libc_info< libc_::cloudabi_
                                    , __cloudlibc_major__,__cloudlibc_minor__,0
                                    > current_libc_;

#elif defined(__GLIBC__)
  //================================================================================================
  // GLIBC version 5 or earlier
  //================================================================================================
  constexpr inline detail::libc_info< libc_::gcc_
                                    , __GLIBC__, __GLIBC_MINOR__, 0
                                    > current_libc_;

#elif defined(__GNU_LIBRARY__)
  //================================================================================================
  // GLIBS version 6 or later
  //================================================================================================
  constexpr inline detail::libc_info< libc_::gcc_
                                    , __GNU_LIBRARY__, __GNU_LIBRARY_MINOR__, 0
                                    > current_libc_;

#elif defined(__UCLIBC__)
  //================================================================================================
  // UCliBC
  //================================================================================================
  constexpr inline detail::libc_info< libc_::uc_
                                    , __UCLIBC_MAJOR__, __UCLIBC_MINOR__, __UCLIBC_SUBLEVEL__
                                    > current_libc_;

#elif defined(__CRTL_VER)
  //================================================================================================
  // VMS
  //================================================================================================
  constexpr inline detail::libc_info< libc_::vms_
                                    , (__CRTL_VER/10000000)%100
                                    , (__CRTL_VER/100000)%100
                                    , (__CRTL_VER/100)%100
                                    > current_libc_;

#elif defined(__LIBREL__)
  //================================================================================================
  // Z/OS
  //================================================================================================
  constexpr inline detail::libc_info< libc_::zos_
                                    , (__LIBREL__&0xF000000)>>24
                                    , (__LIBREL__&0xFF0000)>>16
                                    , (__LIBREL__&0xFFFF)
                                    > current_libc_;

#else
  //================================================================================================
  // Unsupported libc
  //================================================================================================
  constexpr inline detail::libc_info<libc_::undefined_,-1,0,0> current_libc_;

#endif
}

#endif
