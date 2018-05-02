//==================================================================================================
/*
  Copyright 2018 Joel FALCOU

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
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
    EXPECT( spy::current_stdlib_                  == spy::stdlib_::libcpp_  );
    EXPECT( spy::version_of(spy::current_stdlib_) >= stdlib_version         );
  }
#elif defined(__GLIBCXX__)
  CASE( "Check that detected stdlib is GNU libstd" )
  {
    auto stdlib_version = spy::version< (__GLIBCXX__/10000)%10000
                                      , (__GLIBCXX__/100)%100
                                      , __GLIBCXX__%100
                                      >;
    EXPECT( spy::current_stdlib_                  == spy::stdlib_::gcc_ );
    EXPECT( spy::version_of(spy::current_stdlib_) >= stdlib_version     );
  }
#else
  CASE( "Check that detected stdlib is undefined" )
  {
    EXPECT( spy::current_stdlib_                  == spy::stdlib_::undefined_ );
    EXPECT( spy::version_of(spy::current_stdlib_) == spy::unspecified_version );
  }
#endif
};

int main( int argc, char** argv )
{
  return lest::run( specification, argc, argv );
}
