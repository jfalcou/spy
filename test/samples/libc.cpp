#include <iostream>
#include <spy/spy.hpp>

int main()
{
  // Comparisons
  if constexpr(spy::libc == spy::gnu_) std::cout << "This code is compiled with the GNU libc.\n";
  else if constexpr(spy::libc == spy::zos_)
    std::cout << "This code is compiled with the zOS libc.\n";
  else if constexpr(spy::libc == spy::vms_)
    std::cout << "This code is compiled with the VMS libc.\n";

  // Direct test
  if constexpr(spy::gnu_) std::cout << "This code is compiled with the GNU libc.\n";
  else if constexpr(spy::zos_) std::cout << "This code is compiled with the zOS libc.\n";
  else if constexpr(spy::vms_) std::cout << "This code is compiled with the VMS libc.\n";
}
