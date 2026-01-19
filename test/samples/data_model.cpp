#include <iostream>
#include <spy/spy.hpp>

int main()
{
  // Comparisons
  if constexpr(spy::data_model == spy::ilp32_)
    std::cout << "This code is compiled on a ILP32 system\n";
  else if constexpr(spy::data_model == spy::ilp64_)
    std::cout << "This code is compiled on a ILP64 system\n";
  else if constexpr(spy::data_model == spy::lp64_)
    std::cout << "This code is compiled on a LP64 system\n";

  // Direct test
  if constexpr(spy::ilp32_) std::cout << "This code is compiled on a ILP32 system\n";
  else if constexpr(spy::ilp64_) std::cout << "This code is compiled on a ILP64 system\n";
  else if constexpr(spy::lp64_) std::cout << "This code is compiled on a LP64 system\n";
}
