//==================================================================================================
/**
  SPY - C++ Informations Broker
  Copyright : SPY Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include <iostream>
#include <spy/spy.hpp>

#include "assert.hpp"

int main()
{
  std::cout << "== detected stdlib is correct\n";
  {
#if defined(_LIBCPP_VERSION)
    {
      SPY_ASSERT("the standard library is libc++", spy::stdlib == spy::libcpp_);
      SPY_ASSERT("the standard library is not libstdc++", !(spy::stdlib == spy::gnucpp_));
    }
#elif defined(__GLIBCXX__)
    {
      SPY_ASSERT("the standard library is not libc++", !(spy::stdlib == spy::libcpp_));
      SPY_ASSERT("the standard library is libstdc++", spy::stdlib == spy::gnucpp_);
    }
#endif
  }
  std::cout << "Detected stdlib: " << spy::stdlib << std::endl;

  std::cout << "== detected constexpr selection on exact stdlib is correct\n";
  {
    using namespace spy::literal;

#if defined(_LIBCPP_VERSION)
    [[maybe_unused]] auto constexpr wrong_constexpr_behavior = 1'42'1337_libcpp;
#elif defined(__GLIBCXX__)
    [[maybe_unused]] auto constexpr wrong_constexpr_behavior = 1'42'1337_gnucpp;
#else
    [[maybe_unused]] auto constexpr wrong_constexpr_behavior = false;
#endif

    if constexpr(spy::stdlib)
    {
      SPY_ASSERT("a version that does not match is turned down", !bool(wrong_constexpr_behavior));
    }
    else
    {
      SPY_ASSERT("a version that does not match selects nothing", bool(wrong_constexpr_behavior));
    }
  }
}
