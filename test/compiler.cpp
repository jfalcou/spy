//==================================================================================================
/*
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
 */
//==================================================================================================

#include "test.hpp"
#include <spy/compiler.hpp>

CASE( "Check that detected compiler is correct" )
{
#if defined(_MSC_VER)
  EXPECT    ( spy::compiler == spy::msvc_   );
  EXPECT_NOT( spy::compiler == spy::intel_  );
  EXPECT_NOT( spy::compiler == spy::clang_  );
  EXPECT_NOT( spy::compiler == spy::gcc_    );
#elif defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC) || defined(__ECC)
  EXPECT_NOT( spy::compiler == spy::msvc_   );
  EXPECT    ( spy::compiler == spy::intel_  );
  EXPECT_NOT( spy::compiler == spy::clang_  );
  EXPECT_NOT( spy::compiler == spy::gcc_    );
#elif defined(__clang__)
  EXPECT_NOT( spy::compiler == spy::msvc_   );
  EXPECT_NOT( spy::compiler == spy::intel_  );
  EXPECT    ( spy::compiler == spy::clang_  );
  EXPECT_NOT( spy::compiler == spy::gcc_    );
#elif defined(__GNUC__)
  EXPECT_NOT( spy::compiler == spy::msvc_   );
  EXPECT_NOT( spy::compiler == spy::intel_  );
  EXPECT_NOT( spy::compiler == spy::clang_  );
  EXPECT    ( spy::compiler == spy::gcc_    );
#endif
}

CASE( "Check that detected compiler version is correct" )
{
  using namespace spy::literal;

#if defined(_MSC_VER)
  EXPECT    ( spy::compiler >= 19'5_msvc );
  EXPECT_NOT( spy::compiler >= 19_intel  );
  EXPECT_NOT( spy::compiler >= 3'9_clang );
  EXPECT_NOT( spy::compiler >= 7'2_gcc   );
#elif defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC) || defined(__ECC)
  EXPECT_NOT( spy::compiler >= 19'5_msvc );
  EXPECT    ( spy::compiler >= 19_intel  );
  EXPECT_NOT( spy::compiler >= 3'9_clang );
  EXPECT_NOT( spy::compiler >= 7'2_gcc   );
#elif defined(__clang__)
  EXPECT_NOT( spy::compiler >= 19'5_msvc );
  EXPECT_NOT( spy::compiler >= 19_intel  );
  EXPECT    ( spy::compiler >= 3'9_clang );
  EXPECT_NOT( spy::compiler >= 7'2_gcc   );
#elif defined(__GNUC__)
  EXPECT_NOT( spy::compiler >= 19'5_msvc );
  EXPECT_NOT( spy::compiler >= 19_intel  );
  EXPECT_NOT( spy::compiler >= 3'9_clang );
  EXPECT    ( spy::compiler >= 7'2_gcc   );
#endif
}

CASE( "Check that detected constexpr selection on exact compiler is correct" )
{
  using namespace spy::literal;

#if defined(_MSC_VER)
  auto const wrong_constexpr_behavior = 1'42'1337_msvc;
#elif defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC) || defined(__ECC)
  auto const wrong_constexpr_behavior = 1'42'1337_intel;
#elif defined(__clang__)
  auto const wrong_constexpr_behavior = 1'42'1337_clang;
#elif defined(__GNUC__)
  auto const wrong_constexpr_behavior = 1'42'1337_gcc;
#else
  auto const wrong_constexpr_behavior = false;
#endif

  if constexpr(spy::compiler)
    EXPECT_NOT( bool(wrong_constexpr_behavior) );
  else
    EXPECT    ( bool(wrong_constexpr_behavior) );
}
