//==================================================================================================
/*
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
 */
//==================================================================================================

#include "test.hpp"
#include <spy/stdlib.hpp>

CASE( "Check that detected stdlib is correct" )
{
#if defined(_LIBCPP_VERSION)
  EXPECT    ( spy::stdlib == spy::libcpp_ );
  EXPECT_NOT( spy::stdlib == spy::gnucpp_ );
#elif defined(__GLIBCXX__)
  EXPECT_NOT( spy::stdlib == spy::libcpp_ );
  EXPECT    ( spy::stdlib == spy::gnucpp_ );
#endif
}

CASE( "Check that detected constexpr selection on exact stdlib is correct" )
{
  using namespace spy::literal;

#if defined(_LIBCPP_VERSION)
  auto const wrong_constexpr_behavior = 1'42'1337_libcpp;
#elif defined(__GLIBCXX__)
  auto const wrong_constexpr_behavior = 1'42'1337_gnucpp;
#else
  auto const wrong_constexpr_behavior = false;
#endif

  if constexpr(spy::stdlib)
    EXPECT_NOT( bool(wrong_constexpr_behavior) );
  else
    EXPECT    ( bool(wrong_constexpr_behavior) );
}
