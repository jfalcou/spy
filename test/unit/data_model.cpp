//==================================================================================================
/**
  SPY - C++ Informations Broker
  Copyright : SPY Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include <spy/spy.hpp>

#include <cassert>
#include <iostream>

int main()
{
  std::cout << "Check that detected data model is correct: " << std::endl;
  {
#if defined(__LP64__) || defined(_LP64)
    assert(!(spy::data_model == spy::ilp32_));
    assert(!(spy::data_model == spy::lp32_));
    assert(!(spy::data_model == spy::silp64_));
    assert(!(spy::data_model == spy::ilp64_));
    assert(!(spy::data_model == spy::llp64_));
    assert(spy::data_model == spy::lp64_);
#endif

#if defined(__ILP32__) || defined(_ILP32)
    assert(spy::data_model == spy::ilp32_);
    assert(!(spy::data_model == spy::lp32_));
    assert(!(spy::data_model == spy::silp64_));
    assert(!(spy::data_model == spy::ilp64_));
    assert(!(spy::data_model == spy::llp64_));
    assert(!(spy::data_model == spy::lp64_));
#endif

    std::cout << "ILP32  status: " << std::boolalpha << (spy::data_model == spy::ilp32_) << std::endl;
    std::cout << "LP32   status: " << std::boolalpha << (spy::data_model == spy::lp32_) << std::endl;
    std::cout << "SILP64 status: " << std::boolalpha << (spy::data_model == spy::silp64_) << std::endl;
    std::cout << "ILP64  status: " << std::boolalpha << (spy::data_model == spy::ilp64_) << std::endl;
    std::cout << "LLP64  status: " << std::boolalpha << (spy::data_model == spy::llp64_) << std::endl;
    std::cout << "LP64   status: " << std::boolalpha << (spy::data_model == spy::lp64_) << std::endl;
  }
  std::cout << "Done." << std::endl;
  std::cout << "Data model detected: " << spy::data_model << std::endl;
}
