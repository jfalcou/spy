//==================================================================================================
/*
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
 */
//==================================================================================================

#include "test.hpp"
#include <spy/os.hpp>

CASE( "Check that detected OS is correct" )
{
#if defined(__ANDROID__)
  EXPECT    ( spy::operating_system == spy::android_ );
  EXPECT_NOT( spy::operating_system == spy::bsd_     );
  EXPECT_NOT( spy::operating_system == spy::cygwin_  );
  EXPECT_NOT( spy::operating_system == spy::ios_     );
  EXPECT_NOT( spy::operating_system == spy::linux_   );
  EXPECT_NOT( spy::operating_system == spy::macos_   );
  EXPECT_NOT( spy::operating_system == spy::unix_    );
  EXPECT_NOT( spy::operating_system == spy::windows_ );
#elif defined(BSD) || defined(_SYSTYPE_BSD)
  EXPECT_NOT( spy::operating_system == spy::android_ );
  EXPECT    ( spy::operating_system == spy::bsd_     );
  EXPECT_NOT( spy::operating_system == spy::cygwin_  );
  EXPECT_NOT( spy::operating_system == spy::ios_     );
  EXPECT_NOT( spy::operating_system == spy::linux_   );
  EXPECT_NOT( spy::operating_system == spy::macos_   );
  EXPECT_NOT( spy::operating_system == spy::unix_    );
  EXPECT_NOT( spy::operating_system == spy::windows_ );
#elif defined(__CYGWIN__)
  EXPECT_NOT( spy::operating_system == spy::android_ );
  EXPECT_NOT( spy::operating_system == spy::bsd_     );
  EXPECT    ( spy::operating_system == spy::cygwin_  );
  EXPECT_NOT( spy::operating_system == spy::ios_     );
  EXPECT_NOT( spy::operating_system == spy::linux_   );
  EXPECT_NOT( spy::operating_system == spy::macos_   );
  EXPECT_NOT( spy::operating_system == spy::unix_    );
  EXPECT_NOT( spy::operating_system == spy::windows_ );
#elif defined(__APPLE__) && defined(__MACH__) && defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__)
  EXPECT_NOT( spy::operating_system == spy::android_ );
  EXPECT_NOT( spy::operating_system == spy::bsd_     );
  EXPECT_NOT( spy::operating_system == spy::cygwin_  );
  EXPECT    ( spy::operating_system == spy::ios_     );
  EXPECT_NOT( spy::operating_system == spy::linux_   );
  EXPECT_NOT( spy::operating_system == spy::macos_   );
  EXPECT_NOT( spy::operating_system == spy::unix_    );
  EXPECT_NOT( spy::operating_system == spy::windows_ );
#elif defined(linux) || defined(__linux)
  EXPECT_NOT( spy::operating_system == spy::android_ );
  EXPECT_NOT( spy::operating_system == spy::bsd_     );
  EXPECT_NOT( spy::operating_system == spy::cygwin_  );
  EXPECT_NOT( spy::operating_system == spy::ios_     );
  EXPECT    ( spy::operating_system == spy::linux_   );
  EXPECT_NOT( spy::operating_system == spy::macos_   );
  EXPECT_NOT( spy::operating_system == spy::unix_    );
  EXPECT_NOT( spy::operating_system == spy::windows_ );
#elif defined(macintosh) || defined(Macintosh) || (defined(__APPLE__) && defined(__MACH__))
  EXPECT_NOT( spy::operating_system == spy::android_ );
  EXPECT_NOT( spy::operating_system == spy::bsd_     );
  EXPECT_NOT( spy::operating_system == spy::cygwin_  );
  EXPECT_NOT( spy::operating_system == spy::ios_     );
  EXPECT_NOT( spy::operating_system == spy::linux_   );
  EXPECT    ( spy::operating_system == spy::macos_   );
  EXPECT_NOT( spy::operating_system == spy::unix_    );
  EXPECT_NOT( spy::operating_system == spy::windows_ );
#elif defined(unix) || defined(__unix) || defined(_XOPEN_SOURCE) || defined(_POSIX_SOURCE)
  EXPECT_NOT( spy::operating_system == spy::android_ );
  EXPECT_NOT( spy::operating_system == spy::bsd_     );
  EXPECT_NOT( spy::operating_system == spy::cygwin_  );
  EXPECT_NOT( spy::operating_system == spy::ios_     );
  EXPECT_NOT( spy::operating_system == spy::linux_   );
  EXPECT_NOT( spy::operating_system == spy::macos_   );
  EXPECT    ( spy::operating_system == spy::unix_    );
  EXPECT_NOT( spy::operating_system == spy::windows_ );
#elif defined(_WIN32) || defined(_WIN64) ||  defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__)
  EXPECT_NOT( spy::operating_system == spy::android_ );
  EXPECT_NOT( spy::operating_system == spy::bsd_     );
  EXPECT_NOT( spy::operating_system == spy::cygwin_  );
  EXPECT_NOT( spy::operating_system == spy::ios_     );
  EXPECT_NOT( spy::operating_system == spy::linux_   );
  EXPECT_NOT( spy::operating_system == spy::macos_   );
  EXPECT_NOT( spy::operating_system == spy::unix_    );
  EXPECT    ( spy::operating_system == spy::windows_ );
#endif
}
