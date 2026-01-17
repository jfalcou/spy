#include <spy/spy.hpp>

#include <iostream>

int main()
{
  // Comparisons
  if constexpr (spy::operating_system == spy::bsd_) std::cout << "This code runs on BSD.\n";
  else if constexpr (spy::operating_system == spy::linux_) std::cout << "This code runs on Linux.\n";
  else if constexpr (spy::operating_system == spy::windows_) std::cout << "This code runs on Windows.\n";

  // Direct test
  if constexpr (spy::bsd_) std::cout << "This code runs on BSD.\n";
  else if constexpr (spy::linux_) std::cout << "This code runs on Linux.\n";
  else if constexpr (spy::windows_) std::cout << "This code runs on Windows.\n";
}
