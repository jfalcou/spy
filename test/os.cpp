//==================================================================================================
/**
  SPY - C++ Informations Broker
  Copyright : SPY Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include <spy.hpp>
#include <iostream>
#include <cassert>

int main()
{
  std::cout << "Check that detected OS is correct: " << std::flush;
  {
#if defined(__ANDROID__)
    assert(  spy::operating_system == spy::android_ );
    assert( !(spy::operating_system == spy::bsd_   ));
    assert( !(spy::operating_system == spy::cygwin_));
    assert( !(spy::operating_system == spy::ios_   ));
    assert( !(spy::operating_system == spy::linux_ ));
    assert( !(spy::operating_system == spy::macos_ ));
    assert( !(spy::operating_system == spy::unix_  ));
    assert( !(spy::operating_system == spy::windows_));
#elif defined(BSD) || defined(_SYSTYPE_BSD)
    assert( !(spy::operating_system == spy::android_));
    assert(  spy::operating_system == spy::bsd_     );
    assert( !(spy::operating_system == spy::cygwin_));
    assert( !(spy::operating_system == spy::ios_   ));
    assert( !(spy::operating_system == spy::linux_ ));
    assert( !(spy::operating_system == spy::macos_ ));
    assert( !(spy::operating_system == spy::unix_  ));
    assert( !(spy::operating_system == spy::windows_));
#elif defined(__CYGWIN__)
    assert( !(spy::operating_system == spy::android_));
    assert( !(spy::operating_system == spy::bsd_   ));
    assert(  spy::operating_system == spy::cygwin_  );
    assert( !(spy::operating_system == spy::ios_   ));
    assert( !(spy::operating_system == spy::linux_ ));
    assert( !(spy::operating_system == spy::macos_ ));
    assert( !(spy::operating_system == spy::unix_  ));
    assert( !(spy::operating_system == spy::windows_));
#elif defined(__APPLE__) && defined(__MACH__) && defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__)
    assert( !(spy::operating_system == spy::android_));
    assert( !(spy::operating_system == spy::bsd_   ));
    assert( !(spy::operating_system == spy::cygwin_));
    assert(  spy::operating_system == spy::ios_     );
    assert( !(spy::operating_system == spy::linux_ ));
    assert( !(spy::operating_system == spy::macos_ ));
    assert( !(spy::operating_system == spy::unix_  ));
    assert( !(spy::operating_system == spy::windows_));
#elif defined(linux) || defined(__linux)
    assert( !(spy::operating_system == spy::android_));
    assert( !(spy::operating_system == spy::bsd_   ));
    assert( !(spy::operating_system == spy::cygwin_));
    assert( !(spy::operating_system == spy::ios_   ));
    assert(  spy::operating_system == spy::linux_   );
    assert( !(spy::operating_system == spy::macos_ ));
    assert( !(spy::operating_system == spy::unix_  ));
    assert( !(spy::operating_system == spy::windows_));
#elif defined(macintosh) || defined(Macintosh) || (defined(__APPLE__) && defined(__MACH__))
    assert( !(spy::operating_system == spy::android_));
    assert( !(spy::operating_system == spy::bsd_   ));
    assert( !(spy::operating_system == spy::cygwin_));
    assert( !(spy::operating_system == spy::ios_   ));
    assert( !(spy::operating_system == spy::linux_ ));
    assert(  spy::operating_system == spy::macos_   );
    assert( !(spy::operating_system == spy::unix_  ));
    assert( !(spy::operating_system == spy::windows_));
#elif defined(unix) || defined(__unix) || defined(_XOPEN_SOURCE) || defined(_POSIX_SOURCE)
    assert( !(spy::operating_system == spy::android_));
    assert( !(spy::operating_system == spy::bsd_   ));
    assert( !(spy::operating_system == spy::cygwin_));
    assert( !(spy::operating_system == spy::ios_   ));
    assert( !(spy::operating_system == spy::linux_ ));
    assert( !(spy::operating_system == spy::macos_ ));
    assert(  spy::operating_system == spy::unix_    );
    assert( !(spy::operating_system == spy::windows_));
#elif defined(_WIN32) || defined(_WIN64) ||  defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__)
    assert( !(spy::operating_system == spy::android_));
    assert( !(spy::operating_system == spy::bsd_   ));
    assert( !(spy::operating_system == spy::cygwin_));
    assert( !(spy::operating_system == spy::ios_   ));
    assert( !(spy::operating_system == spy::linux_ ));
    assert( !(spy::operating_system == spy::macos_ ));
    assert( !(spy::operating_system == spy::unix_  ));
    assert(  spy::operating_system == spy::windows_ );
#endif
  }
  std::cout << "Done." << std::endl;
  std::cout << "Detected OS: " << spy::operating_system << std::endl;
}
