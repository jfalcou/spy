#include <spy/spy.hpp>
#include <iostream>

int main()
{
  // Comparisons
  if      constexpr( spy::compiler == spy::gcc_     ) std::cout << "This code compiled with g++.\n";
  else if constexpr( spy::compiler == spy::clang_   ) std::cout << "This code compiled with clang.\n";
  else if constexpr( spy::compiler == spy::dpcpp_ ) std::cout << "This code compiled with ICPX.\n";

  // Direct test
  if      constexpr( spy::gcc_   ) std::cout << "This code compiled with g++.\n";
  else if constexpr( spy::clang_ ) std::cout << "This code compiled with clang.\n";
  else if constexpr( spy::dpcpp_ ) std::cout << "This code compiled with ICPX.\n";

  //Version checks
  using namespace spy;
  if constexpr( spy::compiler == 16'0_clang ) std::cout << "This code compiled with clang 16.\n";
  if constexpr( spy::compiler >= 15'0_clang ) std::cout << "This code compiled with clang 15 or ulterior.\n";
}
