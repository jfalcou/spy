//==================================================================================================
/*
  Copyright 2018-2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
 */
//==================================================================================================
#ifndef SPY_OS_HPP_INLUDED
#define SPY_OS_HPP_INLUDED

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

  //================================================================================================
  // OS detection object
  //================================================================================================
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

#endif
