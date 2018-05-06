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
  enum class systems  { undefined_  = - 1
                      , android_, bsd_, cygwin_, ios_, linux_, macos_, unix_, windows_
                      };

  inline std::ostream& operator<<(std::ostream& os, systems const& c)
  {
    if(c == systems::android_ ) return os << "Android";
    if(c == systems::bsd_     ) return os << "BSD";
    if(c == systems::cygwin_  ) return os << "Cygwin";
    if(c == systems::ios_     ) return os << "iOS";
    if(c == systems::linux_   ) return os << "Linux";
    if(c == systems::macos_   ) return os << "MacOS";
    if(c == systems::unix_    ) return os << "UNIX";
    if(c == systems::windows_ ) return os << "Windows";
    return os << "Undefined Operatign System";
  }

#if defined(__ANDROID__)
  //================================================================================================
  // Android
  //================================================================================================
  constexpr inline auto current_os_ = systems::android_;
#elif defined(BSD) || defined(_SYSTYPE_BSD)
  //================================================================================================
  // BSD
  //================================================================================================
  constexpr inline auto current_os_ = systems::bsd_;
#elif defined(__CYGWIN__)
  //================================================================================================
  // Cygwin
  //================================================================================================
  constexpr inline auto current_os_ = systems::cygwin_;
#elif     defined(__APPLE__) && defined(__MACH__) \
      &&  defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__)
  //================================================================================================
  // iOS
  //================================================================================================
  constexpr inline auto current_os_ = systems::ios_;
#elif defined(linux) || defined(__linux)
  //================================================================================================
  // Linux
  //================================================================================================
  constexpr inline auto current_os_ = systems::linux_;
#elif defined(macintosh) || defined(Macintosh) || (defined(__APPLE__) && defined(__MACH__))
  //================================================================================================
  // MacOS
  //================================================================================================
  constexpr inline auto current_os_ = systems::macos_;
#elif defined(unix) || defined(__unix) || defined(_XOPEN_SOURCE) || defined(_POSIX_SOURCE)
  //================================================================================================
  // UNIX
  //================================================================================================
  constexpr inline auto current_os_ = systems::unix_;
#elif   defined(_WIN32) || defined(_WIN64)  \
    ||  defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__)
  //================================================================================================
  // Windows
  //================================================================================================
  constexpr inline auto current_os_ = systems::windows_;
#else
  //================================================================================================
  // Unsupported OS
  //================================================================================================
  constexpr inline auto current_os_ = systems::undefined_;
#endif

  template<systems TargetOS>
  struct is_os : std::integral_constant<bool, TargetOS == current_os_>
  {};

  template<systems TargetOS> using is_os_t = typename is_os<TargetOS>::type;
  template<systems TargetOS> constexpr inline bool  is_os_v = is_os<TargetOS>::value;
}

#endif
