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
  std::cout << "== specified accelerator is supported\n";
  {
#if defined(SYCL_LANGUAGE_VERSION) && defined(__INTEL_LLVM_COMPILER)
    SPY_ASSERT("sycl is reported", spy::supports::sycl);
    std::cout << "Compiled with " << spy::supports::sycl << "\n";
#else
    SPY_ASSERT("sycl is not reported", !spy::supports::sycl);
#endif
  }
  {
#if defined(__NVCC__) && defined(__CUDACC__)
    SPY_ASSERT("cuda is reported", spy::supports::cuda);
    std::cout << "Compiled with " << spy::supports::cuda << "\n";
#else
    SPY_ASSERT("cuda is not reported", !spy::supports::cuda);
#endif
  }
}
