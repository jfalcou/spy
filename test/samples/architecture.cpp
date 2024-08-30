#include <spy/spy.hpp>
#include <iostream>

int main()
{
  // Comparisons
  if      constexpr( spy::architecture == spy::x86_   ) std::cout << "This code is compiled for X86.\n";
  else if constexpr( spy::architecture == spy::amd64_ ) std::cout << "This code is compiled for X86-64.\n";
  else if constexpr( spy::architecture == spy::ppc_   ) std::cout << "This code is compiled for PowerPC.\n";
  else if constexpr( spy::architecture == spy::arm_   ) std::cout << "This code is compiled for ARM.\n";
  else if constexpr( spy::architecture == spy::riscv_ ) std::cout << "This code is compiled for RISC-V.\n";

  // Direct test
  if      constexpr( spy::x86_   ) std::cout << "This code is compiled for X86.\n";
  else if constexpr( spy::amd64_ ) std::cout << "This code is compiled for X86-64.\n";
  else if constexpr( spy::ppc_   ) std::cout << "This code is compiled for PowerPC.\n";
  else if constexpr( spy::arm_   ) std::cout << "This code is compiled for ARM.\n";
  else if constexpr( spy::riscv_ ) std::cout << "This code is compiled for RISC-V.\n";
}
