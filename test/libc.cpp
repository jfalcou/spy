//==================================================================================================
/*
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
 */
//==================================================================================================

#include "test.hpp"
#include <spy/libc.hpp>

CASE( "Check that detected libc is correct" )
{
#if defined(__cloudlibc__)
  EXPECT    ( spy::libc == spy::cloudabi_ );
  EXPECT_NOT( spy::libc == spy::uc_       );
  EXPECT_NOT( spy::libc == spy::vms_      );
  EXPECT_NOT( spy::libc == spy::zos_      );
  EXPECT_NOT( spy::libc == spy::gnu_      );
#elif defined(__UCLIBC__)
  EXPECT_NOT( spy::libc == spy::cloudabi_ );
  EXPECT    ( spy::libc == spy::uc_       );
  EXPECT_NOT( spy::libc == spy::vms_      );
  EXPECT_NOT( spy::libc == spy::zos_      );
  EXPECT_NOT( spy::libc == spy::gnu_      );
#elif defined(__CRTL_VER)
  EXPECT_NOT( spy::libc == spy::cloudabi_ );
  EXPECT_NOT( spy::libc == spy::uc_       );
  EXPECT    ( spy::libc == spy::vms_      );
  EXPECT_NOT( spy::libc == spy::zos_      );
  EXPECT_NOT( spy::libc == spy::gnu_      );
#elif defined(__LIBREL__)
  EXPECT_NOT( spy::libc == spy::cloudabi_ );
  EXPECT_NOT( spy::libc == spy::uc_       );
  EXPECT_NOT( spy::libc == spy::vms_      );
  EXPECT    ( spy::libc == spy::zos_      );
  EXPECT_NOT( spy::libc == spy::gnu_      );
#elif defined(__GLIBC__) || defined(__GNU_LIBRARY__)
  EXPECT_NOT( spy::libc == spy::cloudabi_ );
  EXPECT_NOT( spy::libc == spy::uc_       );
  EXPECT_NOT( spy::libc == spy::vms_      );
  EXPECT_NOT( spy::libc == spy::zos_      );
  EXPECT    ( spy::libc == spy::gnu_      );
#else
  EXPECT_NOT( spy::libc == spy::cloudabi_ );
  EXPECT_NOT( spy::libc == spy::uc_       );
  EXPECT_NOT( spy::libc == spy::vms_      );
  EXPECT_NOT( spy::libc == spy::zos_      );
  EXPECT_NOT( spy::libc == spy::gnu_      );
#endif
}

CASE( "Check that detected constexpr selection on exact libc is correct" )
{
  using namespace spy::literal;

#if defined(__cloudlibc__)
  auto const wrong_constexpr_behavior = 1'42'1337_cloud;
#elif defined(__UCLIBC__)
  auto const wrong_constexpr_behavior = 1'42'1337_uc;
#elif defined(__CRTL_VER)
  auto const wrong_constexpr_behavior = 1'42'1337_vms;
#elif defined(__LIBREL__)
  auto const wrong_constexpr_behavior = 1'42'1337_zos;
#elif defined(__GLIBC__) || defined(__GNU_LIBRARY__)
  auto const wrong_constexpr_behavior = 1'42'1337_gnu;
#else
  auto const wrong_constexpr_behavior = false;
#endif

  if constexpr(spy::libc)
    EXPECT_NOT( bool(wrong_constexpr_behavior) );
  else
    EXPECT    ( bool(wrong_constexpr_behavior) );
}
