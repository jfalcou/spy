//==================================================================================================
/*
  Copyright 2018 Joel FALCOU

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */
//==================================================================================================

#include <lest/lest.hpp>
#include <spy/libc.hpp>

using namespace lest;

const lest::test specification[] =
{
#if defined(__cloudlibc__)
  CASE( "Check that detected libc is CloudABI" )
  {
    auto libc_version = spy::version<__cloudlibc_major__,__cloudlibc_minor__>;
    EXPECT( spy::current_libc_                  == spy::libc_::cloudabi_  );
    EXPECT( spy::version_of(spy::current_libc_) >= libc_version       );
  }
#elif defined(__GLIBC__)
  CASE( "Check that detected libc is glibc" )
  {
    auto libc_version = spy::version<__GLIBC__, __GLIBC_MINOR__>;
    EXPECT( spy::current_libc_                  == spy::libc_::gcc_ );
    EXPECT( spy::version_of(spy::current_libc_) >= libc_version     );
  }
#elif defined(__GNU_LIBRARY__)
  CASE( "Check that detected libc is GNU libc" )
  {
    auto libc_version = spy::version<__GNU_LIBRARY__,__GNU_LIBRARY_MINOR__>;
    EXPECT( spy::current_libc_                  == spy::libc_::gcc_ );
    EXPECT( spy::version_of(spy::current_libc_) >= libc_version     );
  }
#elif defined(__UCLIBC__)
  CASE( "Check that detected libc is UC libc" )
  {
    auto libc_version = spy::version<__UCLIBC_MAJOR__, __UCLIBC_MINOR__, __UCLIBC_SUBLEVEL__>;
    EXPECT( spy::current_libc_                  == spy::libc_::uc_  );
    EXPECT( spy::version_of(spy::current_libc_) >= libc_version     );
  }
#elif defined(__CRTL_VER)
  CASE( "Check that detected libc is VMS libc" )
  {
    auto libc_version = spy::version< (__CRTL_VER/10000000)%100
                                    , (__CRTL_VER/100000)%100
                                    , (__CRTL_VER/100)%100
                                    >;
    EXPECT( spy::current_libc_                  == spy::libc_::vms_ );
    EXPECT( spy::version_of(spy::current_libc_) >= libc_version     );
  }
#elif defined(__LIBREL__)
  CASE( "Check that detected libc is z/OS libc" )
  {
    auto libc_version = spy::version< (__LIBREL__&0xF000000)>>24
                                    , (__LIBREL__&0xFF0000)>>16
                                    , (__LIBREL__&0xFFFF)
                                    >;
    EXPECT( spy::current_libc_                  == spy::libc_::zos_ );
    EXPECT( spy::version_of(spy::current_libc_) >= libc_version     );
  }
#else
  CASE( "Check that detected libc is undefined" )
  {
    EXPECT( spy::current_libc_                  == spy::libc_::undefined_ );
    EXPECT( spy::version_of(spy::current_libc_) == spy::unspecified_version   );
  }
#endif
};

int main( int argc, char** argv )
{
  return lest::run( specification, argc, argv );
}
