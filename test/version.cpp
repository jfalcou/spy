//==================================================================================================
/*
  Copyright 2018 Joel FALCOU

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */
//==================================================================================================

#include <lest/lest.hpp>
#include <spy/version.hpp>

using namespace lest;

const lest::test specification[] =
{
  CASE( "Completely defined version object members behave normally" )
  {
    auto my_version = spy::version<1,2,3>;

    int major = my_version.major;
    int minor = my_version.minor;
    int patch = my_version.patch;

    EXPECT( major == 1 );
    EXPECT( minor == 2 );
    EXPECT( patch == 3 );
  },
  CASE( "Default patch level version object members behave normally" )
  {
    auto my_version  = spy::version<4,5>;

    int major = my_version.major;
    int minor = my_version.minor;
    int patch = my_version.patch;

    EXPECT( major == 4 );
    EXPECT( minor == 5 );
    EXPECT( patch == 0 );
  },
  CASE( "Fully default version object members behave normally" )
  {
    auto my_version  = spy::version<6>;

    int major = my_version.major;
    int minor = my_version.minor;
    int patch = my_version.patch;

    EXPECT( major == 6 );
    EXPECT( minor == 0 );
    EXPECT( patch == 0 );
  },
  CASE( "Versions objects compares for equality" )
  {
    auto version_1 = spy::version<6>;
    auto version_2 = spy::version<6,0,0>;
    auto version_3 = spy::version<6,0,1>;

    EXPECT( version_1 == version_2 );
    EXPECT_NOT( version_1 == version_3 );
  },
  CASE( "Versions objects compares for inequality" )
  {
    auto version_1  = spy::version<7>;
    auto version_2  = spy::version<7,0,0>;
    auto version_3a = spy::version<7,0,1>;
    auto version_3b = spy::version<7,2,0>;
    auto version_3c = spy::version<9,0,0>;

    EXPECT_NOT( version_1 != version_2 );
    EXPECT( version_1 != version_3a );
    EXPECT( version_1 != version_3b );
    EXPECT( version_1 != version_3c );
  },
  CASE( "Versions objects are ordered with <" )
  {
    auto version_1  = spy::version<5,3,4>;
    auto version_2  = spy::version<4,6,9>;
    auto version_3  = spy::version<3,2,1>;

    EXPECT( version_2 < version_1 );
    EXPECT( version_3 < version_1 );
    EXPECT( version_3 < version_2 );

    EXPECT_NOT( version_1 < version_2 );
    EXPECT_NOT( version_1 < version_3 );
    EXPECT_NOT( version_2 < version_3 );
  },
  CASE( "Versions objects are ordered with >" )
  {
    auto version_1  = spy::version<5,3,4>;
    auto version_2  = spy::version<4,6,9>;
    auto version_3  = spy::version<3,2,1>;

    EXPECT( version_1 > version_2 );
    EXPECT( version_1 > version_3 );
    EXPECT( version_2 > version_3 );

    EXPECT_NOT( version_2 > version_1 );
    EXPECT_NOT( version_3 > version_1 );
    EXPECT_NOT( version_3 > version_2 );
  },
  CASE( "Versions objects are ordered with >=" )
  {
    auto version_1  = spy::version<5,3,4>;
    auto version_2  = spy::version<4,6,9>;
    auto version_3  = spy::version<3,2,1>;

    EXPECT( version_1 >= version_1 );
    EXPECT( version_1 >= version_2 );
    EXPECT( version_1 >= version_3 );
    EXPECT( version_2 >= version_3 );
  },
  CASE( "Versions objects are ordered with <=" )
  {
    auto version_1  = spy::version<5,3,4>;
    auto version_2  = spy::version<4,6,9>;
    auto version_3  = spy::version<3,2,1>;

    EXPECT( version_1 <= version_1 );
    EXPECT( version_2 <= version_1 );
    EXPECT( version_3 <= version_1 );
    EXPECT( version_3 <= version_2 );
  }
};

int main( int argc, char** argv )
{
  return lest::run( specification, argc, argv );
}
