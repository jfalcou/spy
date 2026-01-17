//==================================================================================================
/**
  SPY - C++ Informations Broker
  Copyright : SPY Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include <spy/spy.hpp>

#include <iostream>

int main(

)
{
  std::cout << "Check that specified accelerator is supported: " << std::endl;
  {
#if defined(SYCL_LANGUAGE_VERSION) && defined(__INTEL_LLVM_COMPILER)
    static_assert(spy::supports::sycl);
    std::cout << "Currently compiling with " << spy::supports::sycl << " enabled\n";
#else
    static_assert(!spy::supports::sycl);
    std::cout << "Currently compiling without SYCL enabled\n";
#endif
  }
  {
#if defined(__NVCC__) && defined(__CUDACC__)
    static_assert(spy::supports::cuda);
    std::cout << "Currently compiling with " << spy::supports::cuda << " enabled\n";
#else
    static_assert(!spy::supports::cuda);
    std::cout << "Currently compiling without CUDA enabled\n";
#endif
  }
  std::cout << "Done." << std::endl;
}
