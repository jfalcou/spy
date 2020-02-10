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
  std::cout << "Supported SIMD instructions set: " << spy::simd_instruction_set << std::endl;
  std::cout << "Check that X86 SIMD extension detection is correct: " << std::endl;
  {
    std::cout << "X86 SIMD status: " << std::boolalpha << (spy::simd_instruction_set == spy::x86_simd_ ) << std::endl;
    std::cout << "SSE1     status: " << std::boolalpha << (spy::simd_instruction_set >= spy::sse1_ ) << std::endl;
    std::cout << "SSE2     status: " << std::boolalpha << (spy::simd_instruction_set >= spy::sse2_ ) << std::endl;
    std::cout << "SSE3     status: " << std::boolalpha << (spy::simd_instruction_set >= spy::sse3_ ) << std::endl;
    std::cout << "SSE4.1   status: " << std::boolalpha << (spy::simd_instruction_set >= spy::sse41_) << std::endl;
    std::cout << "SSE4.2   status: " << std::boolalpha << (spy::simd_instruction_set >= spy::sse42_) << std::endl;
    std::cout << "AVX      status: " << std::boolalpha << (spy::simd_instruction_set >= spy::avx_  ) << std::endl;
    std::cout << "AVX2     status: " << std::boolalpha << (spy::simd_instruction_set >= spy::avx2_ ) << std::endl;
    std::cout << "FMA3    support: " << std::boolalpha << (spy::supports::fma_  ) << std::endl;
    std::cout << "FMA4    support: " << std::boolalpha << (spy::supports::fma4_ ) << std::endl;
    std::cout << "XOP     support: " << std::boolalpha << (spy::supports::xop_  ) << std::endl;
  }
  std::cout << std::endl;

  std::cout << "Check that ARM SIMD extension detection is correct: " << std::endl;
  {
    std::cout << "ARM SIMD status: "  << std::boolalpha << (spy::simd_instruction_set == spy::arm_simd_ ) << std::endl;
    std::cout << "NEON     status: "  << std::boolalpha << (spy::simd_instruction_set >= spy::neon_ ) << std::endl;
    std::cout << "AARCH64 support: "  << std::boolalpha << (spy::supports::aarch64_  ) << std::endl;
  }
  std::cout << std::endl;

  std::cout << "Check that PPC SIMD extension detection is correct: " << std::endl;
  {
    std::cout << "PPC SIMD status: "  << std::boolalpha << (spy::simd_instruction_set == spy::ppc_simd_ ) << std::endl;
    std::cout << "VMX      status: "  << std::boolalpha << (spy::simd_instruction_set >= spy::vmx_ ) << std::endl;
    std::cout << "VSX      status: "  << std::boolalpha << (spy::simd_instruction_set >= spy::vsx_ ) << std::endl;
  }
  std::cout << std::endl;
}
