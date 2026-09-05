//==================================================================================================
/**
  SPY - C++ Informations Broker
  Copyright : SPY Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include <iostream>
#include <spy/spy.hpp>

#include "assert.hpp"

int main()
{
  std::cout << "== detected OS is correct\n";
  {
#if defined(__ANDROID__)
    SPY_ASSERT("the system is android", spy::operating_system == spy::android_);
    SPY_ASSERT("the system is not bsd", !(spy::operating_system == spy::bsd_));
    SPY_ASSERT("the system is not cygwin", !(spy::operating_system == spy::cygwin_));
    SPY_ASSERT("the system is not ios", !(spy::operating_system == spy::ios_));
    SPY_ASSERT("the system is not linux", !(spy::operating_system == spy::linux_));
    SPY_ASSERT("the system is not macos", !(spy::operating_system == spy::macos_));
    SPY_ASSERT("the system is not unix", !(spy::operating_system == spy::unix_));
    SPY_ASSERT("the system is not windows", !(spy::operating_system == spy::windows_));
#elif defined(BSD) || defined(_SYSTYPE_BSD)
    SPY_ASSERT("the system is not android", !(spy::operating_system == spy::android_));
    SPY_ASSERT("the system is bsd", spy::operating_system == spy::bsd_);
    SPY_ASSERT("the system is not cygwin", !(spy::operating_system == spy::cygwin_));
    SPY_ASSERT("the system is not ios", !(spy::operating_system == spy::ios_));
    SPY_ASSERT("the system is not linux", !(spy::operating_system == spy::linux_));
    SPY_ASSERT("the system is not macos", !(spy::operating_system == spy::macos_));
    SPY_ASSERT("the system is not unix", !(spy::operating_system == spy::unix_));
    SPY_ASSERT("the system is not windows", !(spy::operating_system == spy::windows_));
#elif defined(__CYGWIN__)
    SPY_ASSERT("the system is not android", !(spy::operating_system == spy::android_));
    SPY_ASSERT("the system is not bsd", !(spy::operating_system == spy::bsd_));
    SPY_ASSERT("the system is cygwin", spy::operating_system == spy::cygwin_);
    SPY_ASSERT("the system is not ios", !(spy::operating_system == spy::ios_));
    SPY_ASSERT("the system is not linux", !(spy::operating_system == spy::linux_));
    SPY_ASSERT("the system is not macos", !(spy::operating_system == spy::macos_));
    SPY_ASSERT("the system is not unix", !(spy::operating_system == spy::unix_));
    SPY_ASSERT("the system is not windows", !(spy::operating_system == spy::windows_));
#elif defined(__APPLE__) && defined(__MACH__) &&                                                   \
    defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__)
    SPY_ASSERT("the system is not android", !(spy::operating_system == spy::android_));
    SPY_ASSERT("the system is not bsd", !(spy::operating_system == spy::bsd_));
    SPY_ASSERT("the system is not cygwin", !(spy::operating_system == spy::cygwin_));
    SPY_ASSERT("the system is ios", spy::operating_system == spy::ios_);
    SPY_ASSERT("the system is not linux", !(spy::operating_system == spy::linux_));
    SPY_ASSERT("the system is not macos", !(spy::operating_system == spy::macos_));
    SPY_ASSERT("the system is not unix", !(spy::operating_system == spy::unix_));
    SPY_ASSERT("the system is not windows", !(spy::operating_system == spy::windows_));
#elif defined(linux) || defined(__linux)
    SPY_ASSERT("the system is not android", !(spy::operating_system == spy::android_));
    SPY_ASSERT("the system is not bsd", !(spy::operating_system == spy::bsd_));
    SPY_ASSERT("the system is not cygwin", !(spy::operating_system == spy::cygwin_));
    SPY_ASSERT("the system is not ios", !(spy::operating_system == spy::ios_));
    SPY_ASSERT("the system is linux", spy::operating_system == spy::linux_);
    SPY_ASSERT("the system is not macos", !(spy::operating_system == spy::macos_));
    SPY_ASSERT("the system is not unix", !(spy::operating_system == spy::unix_));
    SPY_ASSERT("the system is not windows", !(spy::operating_system == spy::windows_));
#elif defined(macintosh) || defined(Macintosh) || (defined(__APPLE__) && defined(__MACH__))
    SPY_ASSERT("the system is not android", !(spy::operating_system == spy::android_));
    SPY_ASSERT("the system is not bsd", !(spy::operating_system == spy::bsd_));
    SPY_ASSERT("the system is not cygwin", !(spy::operating_system == spy::cygwin_));
    SPY_ASSERT("the system is not ios", !(spy::operating_system == spy::ios_));
    SPY_ASSERT("the system is not linux", !(spy::operating_system == spy::linux_));
    SPY_ASSERT("the system is macos", spy::operating_system == spy::macos_);
    SPY_ASSERT("the system is not unix", !(spy::operating_system == spy::unix_));
    SPY_ASSERT("the system is not windows", !(spy::operating_system == spy::windows_));
#elif defined(unix) || defined(__unix) || defined(_XOPEN_SOURCE) || defined(_POSIX_SOURCE)
    SPY_ASSERT("the system is not android", !(spy::operating_system == spy::android_));
    SPY_ASSERT("the system is not bsd", !(spy::operating_system == spy::bsd_));
    SPY_ASSERT("the system is not cygwin", !(spy::operating_system == spy::cygwin_));
    SPY_ASSERT("the system is not ios", !(spy::operating_system == spy::ios_));
    SPY_ASSERT("the system is not linux", !(spy::operating_system == spy::linux_));
    SPY_ASSERT("the system is not macos", !(spy::operating_system == spy::macos_));
    SPY_ASSERT("the system is unix", spy::operating_system == spy::unix_);
    SPY_ASSERT("the system is not windows", !(spy::operating_system == spy::windows_));
#elif defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__TOS_WIN__) ||          \
    defined(__WINDOWS__)
    SPY_ASSERT("the system is not android", !(spy::operating_system == spy::android_));
    SPY_ASSERT("the system is not bsd", !(spy::operating_system == spy::bsd_));
    SPY_ASSERT("the system is not cygwin", !(spy::operating_system == spy::cygwin_));
    SPY_ASSERT("the system is not ios", !(spy::operating_system == spy::ios_));
    SPY_ASSERT("the system is not linux", !(spy::operating_system == spy::linux_));
    SPY_ASSERT("the system is not macos", !(spy::operating_system == spy::macos_));
    SPY_ASSERT("the system is not unix", !(spy::operating_system == spy::unix_));
    SPY_ASSERT("the system is windows", spy::operating_system == spy::windows_);
#endif
  }
  std::cout << "Detected OS: " << spy::operating_system << std::endl;
}
