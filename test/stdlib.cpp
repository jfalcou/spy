//==================================================================================================
/*
  SPY - C++ Informations Broker
  Copyright 2020 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
 */
//==================================================================================================
#include <spy/spy.hpp>
#include <cassert>

int main()
{
  std::cout << "Check that detected stdlib is correct: " << std::flush;
  {
#if defined(_LIBCPP_VERSION)
  {
    assert(  spy::stdlib == spy::libcpp_ );
    assert( !spy::stdlib == spy::gnucpp_ );
  }
#elif defined(__GLIBCXX__)
  {
    assert( !spy::stdlib == spy::libcpp_ );
    assert(  spy::stdlib == spy::gnucpp_ );
  }
#endif
  }
  std::cout << "Done." << std::endl;

  std::cout << "Check that detected constexpr selection on exact stdlib is correct: " << std::flush;
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
    {
      assert( !bool(wrong_constexpr_behavior) );
    }
    else
    {
      assert( bool(wrong_constexpr_behavior) );
    }
  }
  std::cout << "Done." << std::endl;
}
