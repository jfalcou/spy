#include <iostream>
#include <spy/spy.hpp>

int main()
{
  std::cout << "Address sanitizers status: " << std::boolalpha
            << spy::supports::address_sanitizers_status << "\n";

  std::cout << "Threads sanitizers status: " << std::boolalpha
            << spy::supports::thread_sanitizers_status << "\n";

  std::cout << "Any sanitizers status: " << std::boolalpha << spy::supports::sanitizers_status
            << "\n";
}
