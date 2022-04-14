//==================================================================================================
/**
  SPY - C++ Informations Broker
  Copyright : SPY Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#if defined(__APPLE__) || defined(__APPLE_CC__) || defined(macintosh)
#  include <AvailabilityMacros.h>
#endif

namespace spy::detail
{
  enum class systems  { undefined_  = - 1
                      , android_, bsd_, cygwin_, ios_, linux_, macos_, unix_, windows_
                      };

  template<systems OpSys> struct os_info
  {
    static constexpr systems            vendor  = OpSys;

    inline constexpr explicit operator bool() const noexcept;

    template<systems C2>
    constexpr bool operator==(os_info<C2> const&) const noexcept
    {
      return C2 == vendor;
    }
  };

  template<systems OpSys>
  std::ostream& operator<<(std::ostream& os, os_info<OpSys> const&)
  {
    if(OpSys == systems::android_ ) return os << "Android";
    if(OpSys == systems::bsd_     ) return os << "BSD";
    if(OpSys == systems::cygwin_  ) return os << "Cygwin";
    if(OpSys == systems::ios_     ) return os << "iOs";
    if(OpSys == systems::linux_   ) return os << "Linux";
    if(OpSys == systems::macos_   ) return os << "MacOs";
    if(OpSys == systems::unix_    ) return os << "UNIX";
    if(OpSys == systems::windows_ ) return os << "Windows";

    return os << "Undefined Operating System";
  }
}

namespace spy
{
#if defined(__ANDROID__)
  #define SPY_OS_IS_ANDROID
  using os_type = detail::os_info<detail::systems::android_>;
#elif defined(BSD) || defined(_SYSTYPE_BSD)
  #define SPY_OS_IS_BSD
  using os_type = detail::os_info<detail::systems::bsd_>;
#elif defined(__CYGWIN__)
  #define SPY_OS_IS_CYGWIN
  using os_type = detail::os_info<detail::systems::cygwin_>;
#elif defined(__APPLE__) && defined(__MACH__) && defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__)
  #define SPY_OS_IS_IOS
  using os_type = detail::os_info<detail::systems::ios_>;
#elif defined(linux) || defined(__linux)
  #define SPY_OS_IS_LINUX
  using os_type = detail::os_info<detail::systems::linux_>;
#elif defined(macintosh) || defined(Macintosh) || (defined(__APPLE__) && defined(__MACH__))
  #define SPY_OS_IS_MACOS
  using os_type = detail::os_info<detail::systems::macos_>;
#elif defined(unix) || defined(__unix) || defined(_XOPEN_SOURCE) || defined(_POSIX_SOURCE)
  #define SPY_OS_IS_UNIX
  using os_type = detail::os_info<detail::systems::unix_>;
#elif defined(_WIN32) || defined(_WIN64) ||  defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__)
  #define SPY_OS_IS_WINDOWS
  using os_type = detail::os_info<detail::systems::windows_>;
#else
  #define SPY_OS_IS_UNKNOWN
  using os_type = detail::os_info<detail::systems::undefined_>;
#endif

  //================================================================================================
  // OS detection object
  //================================================================================================
  constexpr inline os_type operating_system;
}

namespace spy::detail
{
  template<systems OS>
  inline constexpr os_info<OS>::operator bool() const noexcept
  {
    return *this == spy::operating_system;
  }
}

namespace spy
{
  //================================================================================================
  // OS detector stand-alone instances
  //================================================================================================
  constexpr inline auto android_  = detail::os_info<detail::systems::android_>{};
  constexpr inline auto bsd_      = detail::os_info<detail::systems::bsd_>{};
  constexpr inline auto cygwin_   = detail::os_info<detail::systems::cygwin_>{};
  constexpr inline auto ios_      = detail::os_info<detail::systems::ios_>{};
  constexpr inline auto linux_    = detail::os_info<detail::systems::linux_>{};
  constexpr inline auto macos_    = detail::os_info<detail::systems::macos_>{};
  constexpr inline auto unix_     = detail::os_info<detail::systems::unix_>{};
  constexpr inline auto windows_  = detail::os_info<detail::systems::windows_>{};
}

namespace spy::supports
{
  //================================================================================================
  // POSIX supports detection
  //================================================================================================
#if(MAC_OS_X_VERSION_MIN_REQUIRED >= 1090) || (_POSIX_C_SOURCE >= 200112L) || (_XOPEN_SOURCE >= 600)
#define SPY_SUPPORTS_POSIX
  constexpr inline auto posix_ = true;
#else
  constexpr inline auto posix_ = false;
#endif
}
