#include <spy/spy.hpp>

#include <iostream>

int main()
{
  if constexpr (spy::supports::posix_) { std::cout << "This is a POSIX platform.\n"; }
}
