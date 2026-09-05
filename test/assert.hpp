//======================================================================================================================
/**
  SPY - C++ Informations Broker
  Copyright : SPY Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//======================================================================================================================
#pragma once

#include <cstdlib>
#include <iostream>

namespace spy
{
  //====================================================================================================================
  // Everything spy reports is known at compile time, so the condition is a template argument: a
  // check that is not a constant expression does not compile, and the failing branch is chosen by
  // if constexpr rather than at run time.
  //
  // Unlike assert, this one holds under NDEBUG, which is what the Release half of the matrix
  // compiles with, and it is named check because assert is a macro of <cassert> that no header here
  // can be sure nobody pulled in.
  //====================================================================================================================
  template<bool Condition> void check(char const* message, char const* expression)
  {
    std::cout << message << ": ";

    if constexpr(Condition)
    {
      std::cout << "OK" << std::endl;
    }
    else
    {
      std::cout << "ERROR : " << expression << std::endl;
      std::abort();
    }
  }
}

// static_cast, because what spy reports is an object with an explicit operator bool, which a bool
// template argument does not convert on its own.
#define SPY_ASSERT(MESSAGE, ...) spy::check<static_cast<bool>(__VA_ARGS__)>(MESSAGE, #__VA_ARGS__)
