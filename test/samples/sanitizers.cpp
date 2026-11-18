#include <iostream>
#include <spy/spy.hpp>

int main()
{
  std::cout << "Address sanitizers status: "
            << (spy::supports::address_sanitizers_status ? "true" : "false") << "\n";

  std::cout << "Threads sanitizers status: "
            << (spy::supports::thread_sanitizers_status ? "true" : "false") << "\n";

  std::cout << "Any sanitizers status: " << (spy::supports::sanitizers_status ? "true" : "false")
            << "\n";
}
