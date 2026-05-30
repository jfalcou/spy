#include <spy/spy.hpp>

#include <iostream>

int main()
{
  std::cout << "This code compiled with " << spy::cpp_standard << ".\n";

  // Version checks
  using namespace spy::literal;
  if constexpr(spy::cpp_standard == 20_cpp) std::cout << "This code compiled with C++ 20.\n";
  if constexpr(spy::cpp_standard == 20) std::cout << "This code compiled with C++ 20.\n";
  if constexpr(spy::cpp_standard >= 17_cpp)
    std::cout << "This code compiled with C++ 17 or ulterior.\n";
  if constexpr(spy::cpp_standard >= 17)
    std::cout << "This code compiled with C++ 17 or ulterior.\n";
}
