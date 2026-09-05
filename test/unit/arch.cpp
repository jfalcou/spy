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
  std::cout << "Check that detected architecture is correct: " << std::endl;
  {
#if defined(i386) || defined(__i386__) || defined(__i486__) || defined(__i586__) ||                \
    defined(__i686__) || defined(__i386) || defined(_M_IX86) || defined(_X86_) ||                  \
    defined(__THW_INTEL__) || defined(__I86__) || defined(__INTEL__)
    SPY_ASSERT("the architecture is x86", spy::architecture == spy::x86_);
    SPY_ASSERT("the architecture is not amd64", !(spy::architecture == spy::amd64_));
    SPY_ASSERT("the architecture is not ppc", !(spy::architecture == spy::ppc_));
    SPY_ASSERT("the architecture is not arm", !(spy::architecture == spy::arm_));
    SPY_ASSERT("the architecture is not wasm", !(spy::architecture == spy::wasm_));
    SPY_ASSERT("the architecture is not riscv", !(spy::architecture == spy::riscv_));
#elif defined(__x86_64) || defined(__x86_64__) || defined(__amd64__) || defined(__amd64) ||        \
    defined(_M_X64)
    SPY_ASSERT("the architecture is not x86", !(spy::architecture == spy::x86_));
    SPY_ASSERT("the architecture is amd64", spy::architecture == spy::amd64_);
    SPY_ASSERT("the architecture is not ppc", !(spy::architecture == spy::ppc_));
    SPY_ASSERT("the architecture is not arm", !(spy::architecture == spy::arm_));
    SPY_ASSERT("the architecture is not wasm", !(spy::architecture == spy::wasm_));
    SPY_ASSERT("the architecture is not riscv", !(spy::architecture == spy::riscv_));
#elif defined(__powerpc) || defined(__powerpc__) || defined(__POWERPC__) || defined(__ppc__) ||    \
    defined(_M_PPC) || defined(_ARCH_PPC) || defined(__PPCGECKO__) || defined(__PPCBROADWAY__) ||  \
    defined(_XENON)
    SPY_ASSERT("the architecture is not x86", !(spy::architecture == spy::x86_));
    SPY_ASSERT("the architecture is not amd64", !(spy::architecture == spy::amd64_));
    SPY_ASSERT("the architecture is ppc", spy::architecture == spy::ppc_);
    SPY_ASSERT("the architecture is not arm", !(spy::architecture == spy::arm_));
    SPY_ASSERT("the architecture is not wasm", !(spy::architecture == spy::wasm_));
    SPY_ASSERT("the architecture is not riscv", !(spy::architecture == spy::riscv_));
#elif defined(__arm__) || defined(__arm64) || defined(__thumb__) || defined(__TARGET_ARCH_ARM) ||  \
    defined(__TARGET_ARCH_THUMB) || defined(_M_ARM) || defined(__ARM_ARCH_ISA_A64)
    SPY_ASSERT("the architecture is not x86", !(spy::architecture == spy::x86_));
    SPY_ASSERT("the architecture is not amd64", !(spy::architecture == spy::amd64_));
    SPY_ASSERT("the architecture is not ppc", !(spy::architecture == spy::ppc_));
    SPY_ASSERT("the architecture is arm", spy::architecture == spy::arm_);
    SPY_ASSERT("the architecture is not wasm", !(spy::architecture == spy::wasm_));
    SPY_ASSERT("the architecture is not riscv", !(spy::architecture == spy::riscv_));
#elif defined(__wasm__)
    SPY_ASSERT("the architecture is not x86", !(spy::architecture == spy::x86_));
    SPY_ASSERT("the architecture is not amd64", !(spy::architecture == spy::amd64_));
    SPY_ASSERT("the architecture is not ppc", !(spy::architecture == spy::ppc_));
    SPY_ASSERT("the architecture is not arm", !(spy::architecture == spy::arm_));
    SPY_ASSERT("the architecture is wasm", spy::architecture == spy::wasm_);
    SPY_ASSERT("the architecture is not riscv", !(spy::architecture == spy::riscv_));
#elif defined(__riscv)
    SPY_ASSERT("the architecture is not x86", !(spy::architecture == spy::x86_));
    SPY_ASSERT("the architecture is not amd64", !(spy::architecture == spy::amd64_));
    SPY_ASSERT("the architecture is not ppc", !(spy::architecture == spy::ppc_));
    SPY_ASSERT("the architecture is not arm", !(spy::architecture == spy::arm_));
    SPY_ASSERT("the architecture is not wasm", !(spy::architecture == spy::wasm_));
    SPY_ASSERT("the architecture is riscv", spy::architecture == spy::riscv_);
#else
    SPY_ASSERT("the architecture is not x86", !(spy::architecture == spy::x86_));
    SPY_ASSERT("the architecture is not amd64", !(spy::architecture == spy::amd64_));
    SPY_ASSERT("the architecture is not ppc", !(spy::architecture == spy::ppc_));
    SPY_ASSERT("the architecture is not arm", !(spy::architecture == spy::arm_));
    SPY_ASSERT("the architecture is not wasm", !(spy::architecture == spy::wasm_));
    SPY_ASSERT("the architecture is not riscv", !(spy::architecture == spy::riscv_));
#endif

    std::cout << "X86    status: " << std::boolalpha << (spy::architecture == spy::x86_)
              << std::endl;
    std::cout << "AMD64  status: " << std::boolalpha << (spy::architecture == spy::amd64_)
              << std::endl;
    std::cout << "PPC    status: " << std::boolalpha << (spy::architecture == spy::ppc_)
              << std::endl;
    std::cout << "ARM    status: " << std::boolalpha << (spy::architecture == spy::arm_)
              << std::endl;
    std::cout << "WASM   status: " << std::boolalpha << (spy::architecture == spy::wasm_)
              << std::endl;
    std::cout << "RISC-V status: " << std::boolalpha << (spy::architecture == spy::riscv_)
              << std::endl;
  }
}
