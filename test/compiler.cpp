//==================================================================================================
/*
  Copyright 2018 Joel FALCOU

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */
//==================================================================================================

#include <lest/lest.hpp>
#include <spy/compiler.hpp>

using namespace lest;

const lest::test specification[] =
{
#if defined(_MSC_VER)
  CASE( "Check that detected compiler is MSVC" )
  {
    auto compiler_version = spy::version<19,5>;
    EXPECT( spy::current_compiler_                  == spy::compiler_::msvc_  );
    EXPECT( spy::version_of(spy::current_compiler_) >= compiler_version       );
  }
#elif defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC) || defined(__ECC)
  CASE( "Check that detected compiler is ICPC" )
  {
    auto compiler_version = spy::version<19>;
    EXPECT( spy::current_compiler_                  == spy::compiler_::intel_   );
    EXPECT( spy::version_of(spy::current_compiler_) >= compiler_version         );
  }
#elif defined(__clang__)
  CASE( "Check that detected compiler is Clang" )
  {
    auto compiler_version = spy::version<3,9>;
    EXPECT( spy::current_compiler_                  == spy::compiler_::clang_ );
    EXPECT( spy::version_of(spy::current_compiler_) >= compiler_version       );
  }
#elif defined(__GNUC__)
  CASE( "Check that detected compiler is GCC" )
  {
    auto compiler_version = spy::version<7>;
    EXPECT( spy::current_compiler_                  == spy::compiler_::gcc_ );
    EXPECT( spy::version_of(spy::current_compiler_) >= compiler_version     );
  }
#else
  CASE( "Check that detected compiler is undefined" )
  {
    auto compiler_version = spy::version<0>;
    EXPECT( spy::current_compiler_                  == spy::compiler_::undefined_ );
    EXPECT( spy::version_of(spy::current_compiler_) >= compiler_version           );
  }
#endif
};

int main( int argc, char** argv )
{
  return lest::run( specification, argc, argv );
}
