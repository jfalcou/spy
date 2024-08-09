#include <spy/spy.hpp>
#include <iostream>

int main()
{
  if constexpr( spy::simd_instruction_set == spy::x86_simd_ )
  {
    std::cout << "This code has been compiled with some Intel SIMD instructions set.\n";
  }

  if constexpr( spy::simd_instruction_set == spy::arm_simd_ )
  {
    std::cout << "This code has been compiled with some ARM SIMD instructions set.\n";
  }

  if constexpr( spy::simd_instruction_set == spy::ppc_simd_ )
  {
    std::cout << "This code has been compiled with some Power PC SIMD instructions set.\n";
  }

  if constexpr( spy::simd_instruction_set == spy::wasm_simd_ )
  {
    std::cout << "This code has been compiled with WASM enabled.\n";
  }
}
