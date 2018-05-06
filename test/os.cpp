//==================================================================================================
/*
  Copyright 2018 Joel FALCOU

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */
//==================================================================================================

#include <lest/lest.hpp>
#include <spy/os.hpp>

using namespace lest;

const lest::test specification[] =
{
#if defined(__ANDROID__)
  CASE( "Check that detected OS is Android" )
  {
    EXPECT( spy::current_os_  == spy::systems::android_  );
  },
#elif defined(BSD) || defined(_SYSTYPE_BSD)
  CASE( "Check that detected OS is BSD" )
  {
    EXPECT( spy::current_os_  == spy::systems::bsd_ );
  },
#elif defined(__CYGWIN__)
  CASE( "Check that detected OS is Cygwin" )
  {
    EXPECT( spy::current_os_  == spy::systems::cygwin_ );
  },
#elif defined(__APPLE__) && defined(__MACH__) &&  defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__)
  CASE( "Check that detected OS is iOS" )
  {
    EXPECT( spy::current_os_  == spy::systems::ios_ );
  },
#elif defined(linux) || defined(__linux)
  CASE( "Check that detected OS is Linux" )
  {
    EXPECT( spy::current_os_  == spy::systems::linux_ );
  },
#elif defined(macintosh) || defined(Macintosh) || (defined(__APPLE__) && defined(__MACH__))
  CASE( "Check that detected OS is MacOS" )
  {
    EXPECT( spy::current_os_  == spy::systems::macos_ );
  },
#elif defined(unix) || defined(__unix) || defined(_XOPEN_SOURCE) || defined(_POSIX_SOURCE)
  CASE( "Check that detected OS is UNIX" )
  {
    EXPECT( spy::current_os_  == spy::systems::unix_ );
  },
#elif defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__)
  CASE( "Check that detected OS is Windows" )
  {
    EXPECT( spy::current_os_  == spy::systems::windows_ );
  },
#else
  CASE( "Check that detected OS is undefined" )
  {
    EXPECT( spy::current_os_  == spy::systems::undefined_ );
  },
#endif
  CASE( "Check that OS detection via traits is coherent" )
  {
    EXPECT( spy::is_os  <spy::current_os_>::value );
    EXPECT( spy::is_os_t<spy::current_os_>::value );
    EXPECT( spy::is_os_v<spy::current_os_>        );
  }
};

int main( int argc, char** argv )
{
  return lest::run( specification, argc, argv );
}
