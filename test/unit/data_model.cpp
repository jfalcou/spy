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
  std::cout << "Check that detected data model is correct: " << std::endl;
  {
#if defined(__LP64__) || defined(_LP64)
    SPY_ASSERT("the data model is not ilp32", !(spy::data_model == spy::ilp32_));
    SPY_ASSERT("the data model is not lp32", !(spy::data_model == spy::lp32_));
    SPY_ASSERT("the data model is not silp64", !(spy::data_model == spy::silp64_));
    SPY_ASSERT("the data model is not ilp64", !(spy::data_model == spy::ilp64_));
    SPY_ASSERT("the data model is not llp64", !(spy::data_model == spy::llp64_));
    SPY_ASSERT("the data model is lp64", spy::data_model == spy::lp64_);
#endif

#if defined(__ILP32__) || defined(_ILP32)
    SPY_ASSERT("the data model is ilp32", spy::data_model == spy::ilp32_);
    SPY_ASSERT("the data model is not lp32", !(spy::data_model == spy::lp32_));
    SPY_ASSERT("the data model is not silp64", !(spy::data_model == spy::silp64_));
    SPY_ASSERT("the data model is not ilp64", !(spy::data_model == spy::ilp64_));
    SPY_ASSERT("the data model is not llp64", !(spy::data_model == spy::llp64_));
    SPY_ASSERT("the data model is not lp64", !(spy::data_model == spy::lp64_));
#endif

    std::cout << "ILP32  status: " << std::boolalpha << (spy::data_model == spy::ilp32_)
              << std::endl;
    std::cout << "LP32   status: " << std::boolalpha << (spy::data_model == spy::lp32_)
              << std::endl;
    std::cout << "SILP64 status: " << std::boolalpha << (spy::data_model == spy::silp64_)
              << std::endl;
    std::cout << "ILP64  status: " << std::boolalpha << (spy::data_model == spy::ilp64_)
              << std::endl;
    std::cout << "LLP64  status: " << std::boolalpha << (spy::data_model == spy::llp64_)
              << std::endl;
    std::cout << "LP64   status: " << std::boolalpha << (spy::data_model == spy::lp64_)
              << std::endl;
  }
  std::cout << "Data model detected: " << spy::data_model << std::endl;
}
