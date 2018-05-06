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
    EXPECT( spy::current_compiler                  == spy::compilers::msvc_  );
    EXPECT( spy::version_of(spy::current_compiler) >= compiler_version       );
  },
#elif defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC) || defined(__ECC)
  CASE( "Check that detected compiler is ICPC" )
  {
    auto compiler_version = spy::version<19>;
    EXPECT( spy::current_compiler                  == spy::compilers::intel_   );
    EXPECT( spy::version_of(spy::current_compiler) >= compiler_version         );
  },
#elif defined(__clang__)
  CASE( "Check that detected compiler is Clang" )
  {
    auto compiler_version = spy::version<3,9>;
    EXPECT( spy::current_compiler                  == spy::compilers::clang_ );
    EXPECT( spy::version_of(spy::current_compiler) >= compiler_version       );
  },
#elif defined(__GNUC__)
  CASE( "Check that detected compiler is GCC" )
  {
    auto compiler_version = spy::version<7>;
    EXPECT( spy::current_compiler                  == spy::compilers::gcc_ );
    EXPECT( spy::version_of(spy::current_compiler) >= compiler_version     );
  },
#else
  CASE( "Check that detected compiler is undefined" )
  {
    EXPECT( spy::current_compiler                  == spy::compilers::undefined_ );
    EXPECT( spy::version_of(spy::current_compiler) == spy::unspecified_version   );
  },
#endif
  CASE( "Check that compiler detection via traits is coherent" )
  {
    EXPECT( spy::is_compiler  <spy::current_compiler>::value );
    EXPECT( spy::is_compilerst<spy::current_compiler>::value );
    EXPECT( spy::is_compilersv<spy::current_compiler>        );
  }
};

int main( int argc, char** argv )
{
  return lest::run( specification, argc, argv );
}
