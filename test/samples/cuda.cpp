#include <spy/spy.hpp>
#include <iostream>

int main()
{
  if constexpr( spy::supports::cuda )  std::cout << "Compiling with CUDA supports\n";
  else                                 std::cout << "No accelerator supports\n";
}
