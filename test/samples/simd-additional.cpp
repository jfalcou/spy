#include <iostream>
#include <spy/spy.hpp>

int main()
{
  if constexpr(spy::supports::fma_) std::cout << "This code has been compiled with FMA3 support.\n";
  else if constexpr(spy::supports::fma4_)
    std::cout << "This code has been compiled with FMA4 support.\n";
  else if constexpr(spy::supports::xop_)
    std::cout << "This code has been compiled with XOP support.\n";
  else if constexpr(spy::supports::avx512::cd_)
    std::cout << "This code has been compiled with AV512-CD support.\n";
}
