//==================================================================================================
/*
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
 */
//==================================================================================================
#ifndef TEST_HPP_INCLUDED
#define TEST_HPP_INCLUDED

#define lest_FEATURE_AUTO_REGISTER 1
#include <lest/lest.hpp>

static lest::tests specification;

int main( int argc, char** argv )
{
  return lest::run( specification, argc, argv );
}

#define CASE( name ) lest_CASE( specification, name )

#endif
