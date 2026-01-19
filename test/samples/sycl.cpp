#include <iostream>
#include <spy/spy.hpp>

int main()
{
  if constexpr(spy::supports::sycl) std::cout << "Compiling with SYCL supports.\n";
  else std::cout << "No accelerator supports\n";
}
