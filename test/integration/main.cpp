#include <iostream>
#include <spy/spy.hpp>

int main()
{
  std::cout << "OS                : " << spy::operating_system      << std::endl;
  std::cout << "CPU Architecture  : " << spy::architecture          << std::endl;
  std::cout << "SIMD Instructions : " << spy::simd_instruction_set  << std::endl;
  std::cout << "Compiler          : " << spy::compiler              << std::endl;
  std::cout << "libc version      : " << spy::libc                  << std::endl;
  std::cout << "libstd            : " << spy::stdlib                << std::endl;
}
