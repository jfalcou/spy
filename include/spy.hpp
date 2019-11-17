//==================================================================================================
/*
  Copyright 2018 Joel FALCOU
  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
 */
//==================================================================================================
#ifndef SPY_SPY_HPP_INLUDED
#define SPY_SPY_HPP_INLUDED
#include <iosfwd>
#include <iostream>
namespace spy { namespace detail
{
  template<char... c> constexpr int find(int i0)
  {
    int sz = sizeof...(c);
    char arr[] = {c...};
    while( i0<sz && arr[i0] != '\'' ) ++i0;
    return i0;
  }
  template<char... c> constexpr int parse(int i0, int i1)
  {
    char arr[] = {c...};
    int value = 0;
    while( i0<i1 && arr[i0] != '\'' ) value = value*10 + (arr[i0++] - 48);
    return value;
  }
  template<template<int,int,int> class Wrapper, char ...c> constexpr auto literal_wrap()
  {
    constexpr int b0 = 0     , e0 = find<c...>(0);
    constexpr int b1 = e0 + 1, e1 = find<c...>(b1);
    constexpr int b2 = e1+1  , e2 = sizeof...(c);
    return Wrapper<parse<c...>(b0,e0),parse<c...>(b1,e1),parse<c...>(b2,e2)>{};
  }
  template<int M, int N, int P> struct version_id
  {
    static constexpr int major = M;
    static constexpr int minor = N;
    static constexpr int patch = P;
  };
  template<int M = 1, int N = 0, int P = 0> constexpr inline version_id<M,N,P> version = {};
  using unspecified_version_t = version_id<-1,0,0>;
  constexpr inline unspecified_version_t unspecified_version = {};
  template<int M1, int N1, int P1, int M2, int N2, int P2>
  constexpr bool operator==(version_id<M1,N1,P1> const&, version_id<M2,N2,P2> const&) noexcept
  {
    return (M1==M2) && (N1==N2) && (P1==P2);
  }
  template<int M1, int N1, int P1, int M2, int N2, int P2>
  constexpr bool operator!=(version_id<M1,N1,P1> const& v1, version_id<M2,N2,P2> const& v2) noexcept
  {
    return !(v1==v2);
  }
  template<int M1, int N1, int P1, int M2, int N2, int P2>
  constexpr bool operator<(version_id<M1,N1,P1> const&, version_id<M2,N2,P2> const&) noexcept
  {
    if constexpr(M1 < M2) return true;
    if constexpr(M1 > M2) return false;
    if constexpr(N1 < N2) return true;
    if constexpr(N1 > N2) return false;
    return P1 < P2;
  }
  template<int M1, int N1, int P1, int M2, int N2, int P2>
  constexpr bool operator>(version_id<M1,N1,P1> const&, version_id<M2,N2,P2> const&) noexcept
  {
    if constexpr(M1 > M2) return true;
    if constexpr(M1 < M2) return false;
    if constexpr(N1 > N2) return true;
    if constexpr(N1 < N2) return false;
    return P1 > P2;
  }
  template<int M1, int N1, int P1, int M2, int N2, int P2>
  constexpr bool operator<=(version_id<M1,N1,P1> const& a, version_id<M2,N2,P2> const& b) noexcept
  {
    return !(a>b);
  }
  template<int M1, int N1, int P1, int M2, int N2, int P2>
  constexpr bool operator>=(version_id<M1,N1,P1> const& a, version_id<M2,N2,P2> const& b) noexcept
  {
    return !(a<b);
  }
  template<int M, int N, int P>
  std::ostream& operator<<(std::ostream& os, version_id<M,N,P> const&)
  {
    return os << "v" << M << "." << N << "." << P;
  }
  inline std::ostream& operator<<(std::ostream& os, unspecified_version_t const&)
  {
    return os << "(unspecified)";
  }
} }
#define SPY_VERSION_COMPARISONS_OPERATOR(ID,TYPE)                       \
template<ID C2,int M2, int N2, int P2>                                  \
constexpr bool operator==( TYPE<C2,M2,N2,P2> const& c2 ) const noexcept \
{                                                                       \
  return C2 == vendor && version == c2.version;                         \
}                                                                       \
                                                                        \
template<ID C2,int M2, int N2, int P2>                                  \
constexpr bool operator!=( TYPE<C2,M2,N2,P2> const& c2 ) const noexcept \
{                                                                       \
  return C2 == vendor && version != c2.version;                         \
}                                                                       \
                                                                        \
template<ID C2,int M2, int N2, int P2>                                  \
constexpr bool operator<( TYPE<C2,M2,N2,P2> const& c2 ) const noexcept  \
{                                                                       \
  return C2 == vendor && version < c2.version;                          \
}                                                                       \
                                                                        \
template<ID C2,int M2, int N2, int P2>                                  \
constexpr bool operator>( TYPE<C2,M2,N2,P2> const& c2 ) const noexcept  \
{                                                                       \
  return C2 == vendor && version > c2.version;                          \
}                                                                       \
                                                                        \
template<ID C2,int M2, int N2, int P2>                                  \
constexpr bool operator>=( TYPE<C2,M2,N2,P2> const& c2 ) const noexcept \
{                                                                       \
  return C2 == vendor && version >= c2.version;                         \
}                                                                       \
                                                                        \
template<ID C2,int M2, int N2, int P2>                                  \
constexpr bool operator<=( TYPE<C2,M2,N2,P2> const& c2 ) const noexcept \
{                                                                       \
  return C2 == vendor && version <= c2.version;                         \
}                                                                       \

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
#include <cstddef>
#include <iosfwd>
namespace spy { namespace detail
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
} }
namespace spy
{
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
  constexpr inline libc_type libc;
}
namespace spy { namespace detail
{
  template<libC C, int M, int N, int P>
  inline constexpr libc_info<C,M,N,P>::operator bool() const noexcept
  {
    return *this == spy::libc;
  }
} }
namespace spy
{
  constexpr inline auto  cloudabi_  = detail::cloudabi_t<-1,0,0>{};
  constexpr inline auto  uc_        = detail::uc_t<-1,0,0>{};
  constexpr inline auto  vms_       = detail::vms_t<-1,0,0>{};
  constexpr inline auto  zos_       = detail::zos_t<-1,0,0>{};
  constexpr inline auto  gnu_       = detail::gnu_t<-1,0,0>{};
}
namespace spy { namespace literal
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
} }
#include <cstddef>
#include <iosfwd>
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
#include <iosfwd>
namespace spy { namespace detail
{
  enum class systems  { undefined_  = - 1
                      , android_, bsd_, cygwin_, ios_, linux_, macos_, unix_, windows_
                      };
  template<systems OS> struct os_info
  {
    static constexpr systems            vendor  = OS;
    inline constexpr operator bool() const noexcept;
    template<systems C2>
    constexpr bool operator==(os_info<C2> const& c2) const noexcept
    {
      return C2 == vendor;
    }
  };
  template<systems OS>
  std::ostream& operator<<(std::ostream& os, os_info<OS> const&)
  {
    if(OS == systems::android_ ) return os << "Android";
    if(OS == systems::bsd_     ) return os << "BSD";
    if(OS == systems::cygwin_  ) return os << "Cygwin";
    if(OS == systems::ios_     ) return os << "iOS";
    if(OS == systems::linux_   ) return os << "Linux";
    if(OS == systems::macos_   ) return os << "MacOS";
    if(OS == systems::unix_    ) return os << "UNIX";
    if(OS == systems::windows_ ) return os << "Windows";
    return os << "Undefined Operating System";
  }
} }
namespace spy
{
#if defined(__ANDROID__)
  using os_type = detail::os_info<detail::systems::android_>;
#elif defined(BSD) || defined(_SYSTYPE_BSD)
  using os_type = detail::os_info<detail::systems::bsd_>;
#elif defined(__CYGWIN__)
  using os_type = detail::os_info<detail::systems::cygwin_>;
#elif defined(__APPLE__) && defined(__MACH__) && defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__)
  using os_type = detail::os_info<detail::systems::ios_>;
#elif defined(linux) || defined(__linux)
  using os_type = detail::os_info<detail::systems::linux_>;
#elif defined(macintosh) || defined(Macintosh) || (defined(__APPLE__) && defined(__MACH__))
  using os_type = detail::os_info<detail::systems::macos_>;
#elif defined(unix) || defined(__unix) || defined(_XOPEN_SOURCE) || defined(_POSIX_SOURCE)
  using os_type = detail::os_info<detail::systems::unix_>;
#elif defined(_WIN32) || defined(_WIN64) ||  defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__)
  using os_type = detail::os_info<detail::systems::windows_>;
#else
  using os_type = detail::os_info<detail::systems::undefined_>;
#endif
  constexpr inline os_type operating_system;
}
namespace spy { namespace detail
{
  template<systems OS>
  inline constexpr os_info<OS>::operator bool() const noexcept
  {
    return *this == spy::operating_system;
  }
} }
namespace spy
{
  constexpr inline auto android_  = detail::os_info<detail::systems::android_>{};
  constexpr inline auto bsd_      = detail::os_info<detail::systems::bsd_>{};
  constexpr inline auto cygwin_   = detail::os_info<detail::systems::cygwin_>{};
  constexpr inline auto ios_      = detail::os_info<detail::systems::ios_>{};
  constexpr inline auto linux_    = detail::os_info<detail::systems::linux_>{};
  constexpr inline auto macos_    = detail::os_info<detail::systems::macos_>{};
  constexpr inline auto unix_     = detail::os_info<detail::systems::unix_>{};
  constexpr inline auto windows_  = detail::os_info<detail::systems::windows_>{};
}
#endif
