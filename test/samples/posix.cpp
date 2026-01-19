#include <iostream>
#include <spy/spy.hpp>

int main()
{
  if constexpr(spy::supports::posix_) { std::cout << "This is a POSIX platform.\n"; }
}
