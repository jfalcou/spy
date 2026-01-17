#include <spy/spy.hpp>

#include <iostream>

int main()
{
  std::cout << spy::simd_instruction_set << "\n";

  if constexpr (spy::simd_instruction_set == spy::avx_)
  {
    std::cout << "This code has been compiled with AVX instructions set.\n";
  }

  if constexpr (spy::simd_instruction_set >= spy::sse41_)
  {
    std::cout << "This code has been compiled with at least support for SSE 4.1\n";
  }

  if constexpr (spy::simd_instruction_set <= spy::sse2_)
  {
    std::cout << "This code has been compiled with support for SSE2 at most.\n";
  }

  std::cout << "This code can use " << spy::simd_instruction_set.width << " bits register.\n";
}
