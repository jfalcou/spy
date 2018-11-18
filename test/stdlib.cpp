//==================================================================================================
/*
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
 */
//==================================================================================================

#include <lest/lest.hpp>
#include <spy/stdlib.hpp>

using namespace lest;

const lest::test specification[] =
{
#if defined(_LIBCPP_VERSION)
  CASE( "Check that detected stdlib is libc++" )
  {
    auto stdlib_version = spy::version<(_LIBCPP_VERSION/1000)%10,0,_LIBCPP_VERSION%1000>;
    EXPECT( spy::current_stdlib                  == spy::stdlib::libcpp_  );
    EXPECT( spy::version_of(spy::current_stdlib) >= stdlib_version        );
  },
#elif defined(__GLIBCXX__)
  CASE( "Check that detected stdlib is GNU libstd" )
  {
    auto stdlib_version = spy::version< (__GLIBCXX__/10000)%10000
                                      , (__GLIBCXX__/100)%100
                                      , __GLIBCXX__%100
                                      >;
    EXPECT( spy::current_stdlib                  == spy::stdlib::gcc_ );
    EXPECT( spy::version_of(spy::current_stdlib) >= stdlib_version    );
  },
#else
  CASE( "Check that detected stdlib is undefined" )
  {
    EXPECT( spy::current_stdlib                  == spy::stdlib::undefined_  );
    EXPECT( spy::version_of(spy::current_stdlib) == spy::unspecified_version );
  },
#endif
  CASE( "Check that stdlib detection via traits is coherent" )
  {
    EXPECT( spy::is_stdlib  <spy::current_stdlib>::value );
    EXPECT( spy::is_stdlib_t<spy::current_stdlib>::value );
    EXPECT( spy::is_stdlib_v<spy::current_stdlib>        );
  }
};

int main( int argc, char** argv )
{
  return lest::run( specification, argc, argv );
}
