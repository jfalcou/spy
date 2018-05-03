//==================================================================================================
/*
  Copyright 2018 Joel FALCOU

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */
//==================================================================================================
#ifndef SPY_OS_HPP_INLUDED
#define SPY_OS_HPP_INLUDED

#include <iosfwd>
#include <spy/version.hpp>

namespace spy
{
  enum class os_  { undefined_  = - 1
                  , android_, bsd_, cygwin_, ios_, linux_, macos_, unix_, windows_
                  };

  inline std::ostream& operator<<(std::ostream& os, os_ const& c)
  {
    if(c == os_::android_ ) return os << "Android";
    if(c == os_::bsd_     ) return os << "BSD";
    if(c == os_::cygwin_  ) return os << "Cygwin";
    if(c == os_::ios_     ) return os << "iOS";
    if(c == os_::linux_   ) return os << "Linux";
    if(c == os_::macos_   ) return os << "MacOS";
    if(c == os_::unix_    ) return os << "UNIX";
    if(c == os_::windows_ ) return os << "Windows";
    return os << "Undefined Operatign System";
  }

#if defined(__ANDROID__)
  //================================================================================================
  // Android
  //================================================================================================
  constexpr inline auto current_os_ = os_::android_;
#elif defined(BSD) || defined(_SYSTYPE_BSD)
  //================================================================================================
  // BSD
  //================================================================================================
  constexpr inline auto current_os_ = os_::bsd_;
#elif defined(__CYGWIN__)
  //================================================================================================
  // Cygwin
  //================================================================================================
  constexpr inline auto current_os_ = os_::cygwin_;
#elif     defined(__APPLE__) && defined(__MACH__) \
      &&  defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__)
  //================================================================================================
  // iOS
  //================================================================================================
  constexpr inline auto current_os_ = os_::ios_;
#elif defined(linux) || defined(__linux)
  //================================================================================================
  // Linux
  //================================================================================================
  constexpr inline auto current_os_ = os_::linux_;
#elif defined(macintosh) || defined(Macintosh) || (defined(__APPLE__) && defined(__MACH__))
  //================================================================================================
  // MacOS
  //================================================================================================
  constexpr inline auto current_os_ = os_::macos_;
#elif defined(unix) || defined(__unix) || defined(_XOPEN_SOURCE) || defined(_POSIX_SOURCE)
  //================================================================================================
  // UNIX
  //================================================================================================
  constexpr inline auto current_os_ = os_::unix_;
#elif   defined(_WIN32) || defined(_WIN64)  \
    ||  defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__)
  //================================================================================================
  // Windows
  //================================================================================================
  constexpr inline auto current_os_ = os_::windows_;
#else
  //================================================================================================
  // Unsupported OS
  //================================================================================================
  constexpr inline auto current_os_ = os_::undefined_;
#endif
}

#endif
