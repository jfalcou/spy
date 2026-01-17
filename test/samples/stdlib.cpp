#include <spy/spy.hpp>

#include <iostream>

int main()
{
  // Comparisons
  if constexpr (spy::stdlib == spy::gnucpp_) std::cout << "This code is compiled with the GNU stdlib.\n";
  else if constexpr (spy::stdlib == spy::libcpp_) std::cout << "This code is compiled with the Clang stdlib.\n";

  // Direct test
  if constexpr (spy::gnucpp_) std::cout << "This code is compiled with the GNU stdlib.\n";
  else if constexpr (spy::libcpp_) std::cout << "This code is compiled with the Clang stdlib.\n";
}
