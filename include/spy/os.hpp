//==================================================================================================
/*
  SPY - C++ Informations Broker
  Copyright : SPY Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#if defined(__APPLE__) || defined(__APPLE_CC__) || defined(macintosh)
#include <AvailabilityMacros.h>
#endif

namespace spy::_
{
  enum class systems
  {
    undefined_ = -1,
    android_,
    bsd_,
    cygwin_,
    ios_,
    linux_,
    macos_,
    unix_,
    windows_
  };

  template<systems OpSys> struct os_info
  {
    static constexpr systems vendor = OpSys;

    inline constexpr explicit operator bool() const noexcept;

    template<systems C2> constexpr bool operator==(os_info<C2> const&) const noexcept { return C2 == vendor; }
  };

  template<_::stream OS, systems OpSys> OS& operator<<(OS& os, os_info<OpSys> const&)
  {
    if (OpSys == systems::android_) return os << "Android";
    if (OpSys == systems::bsd_) return os << "BSD";
    if (OpSys == systems::cygwin_) return os << "Cygwin";
    if (OpSys == systems::ios_) return os << "iOs";
    if (OpSys == systems::linux_) return os << "Linux";
    if (OpSys == systems::macos_) return os << "MacOs";
    if (OpSys == systems::unix_) return os << "UNIX";
    if (OpSys == systems::windows_) return os << "Windows";

    return os << "Undefined Operating System";
  }
}

namespace spy
{
#if defined(__ANDROID__)
#define SPY_OS_IS_ANDROID
  using os_type = _::os_info<_::systems::android_>;
#elif defined(BSD) || defined(_SYSTYPE_BSD)
#define SPY_OS_IS_BSD
  using os_type = _::os_info<_::systems::bsd_>;
#elif defined(__CYGWIN__)
#define SPY_OS_IS_CYGWIN
  using os_type = _::os_info<_::systems::cygwin_>;
#elif defined(__APPLE__) && defined(__MACH__) && defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__)
#define SPY_OS_IS_IOS
  using os_type = _::os_info<_::systems::ios_>;
#elif defined(linux) || defined(__linux)
#define SPY_OS_IS_LINUX
  using os_type = _::os_info<_::systems::linux_>;
#elif defined(macintosh) || defined(Macintosh) || (defined(__APPLE__) && defined(__MACH__))
#define SPY_OS_IS_MACOS
  using os_type = _::os_info<_::systems::macos_>;
#elif defined(unix) || defined(__unix) || defined(_XOPEN_SOURCE) || defined(_POSIX_SOURCE)
#define SPY_OS_IS_UNIX
  using os_type = _::os_info<_::systems::unix_>;
#elif defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__)
#define SPY_OS_IS_WINDOWS
  using os_type = _::os_info<_::systems::windows_>;
#else
#define SPY_OS_IS_UNKNOWN
  using os_type = _::os_info<_::systems::undefined_>;
#endif

  //================================================================================================
  //! @ingroup api
  //! @brief OS reporting value
  //!
  //! The `spy::operating_system` object can be compared to any other OS related value to verify
  //! if the code being compiled is compiled on a given Operating Systems.
  //!
  //! Additionally, any of the OS related value are convertible to `bool`. They evaluates to `true` if they
  //! matches the correct OS currently used.
  //!
  //! @groupheader{Supported Value}
  //!
  //! Name            | Operating System
  //! --------------- | -------------
  //! `spy::android_` | Android
  //! `spy::bsd`      | BSD
  //! `spy::cygwin_`  | CYGWIN
  //! `spy::ios_`     | iOS
  //! `spy::linux_`   | Linux
  //! `spy::macos_`   | MacOS
  //! `spy::unix_`    | UNIX
  //! `spy::windows_` | Windows
  //!
  //! @groupheader{Example}
  //! @godbolt{samples/os.cpp}
  //================================================================================================
  constexpr inline os_type operating_system;
}

namespace spy::_
{
  template<systems OS> inline constexpr os_info<OS>::operator bool() const noexcept
  {
    return spy::operating_system == *this;
  }
}

namespace spy
{
  constexpr inline auto android_ = _::os_info<_::systems::android_>{};
  constexpr inline auto bsd_ = _::os_info<_::systems::bsd_>{};
  constexpr inline auto cygwin_ = _::os_info<_::systems::cygwin_>{};
  constexpr inline auto ios_ = _::os_info<_::systems::ios_>{};
  constexpr inline auto linux_ = _::os_info<_::systems::linux_>{};
  constexpr inline auto macos_ = _::os_info<_::systems::macos_>{};
  constexpr inline auto unix_ = _::os_info<_::systems::unix_>{};
  constexpr inline auto windows_ = _::os_info<_::systems::windows_>{};
}

namespace spy::supports
{
#if defined(SPY_DOXYGEN_INVOKED)
  //================================================================================================
  //! @ingroup api
  //! @brief POSIX supports indicator.
  //!
  //! Evaluates to `true` if current OS supports POSIX system calls and functions.
  //!
  //! @groupheader{Example}
  //! @godbolt{samples/posix.cpp}
  //================================================================================================
  constexpr inline auto posix_ = **implementation specified * *;
#else
#if (MAC_OS_X_VERSION_MIN_REQUIRED >= 1090) || (_POSIX_C_SOURCE >= 200112L) || (_XOPEN_SOURCE >= 600)
#define SPY_SUPPORTS_POSIX
  constexpr inline auto posix_ = true;
#else
  constexpr inline auto posix_ = false;
#endif
#endif
}
