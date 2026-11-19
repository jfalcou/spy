#include <array>
#include <iostream>
#include <spy/spy.hpp>

// Hot paths left out of the sanitizers
SPY_DISABLE_ADDRESS_SANITIZERS int first(int const* data) { return data[ 0 ]; }
SPY_DISABLE_THREAD_SANITIZERS int  second(int const* data) { return data[ 1 ]; }
SPY_DISABLE_SANITIZERS int         sum(int const* data)
{
  int total = 0;
  for(int i = 0; i < 4; ++i) total += data[ i ];
  return total;
}

int main()
{
  std::array<int, 4> values = {1, 2, 3, 4};
  int const*         data   = values.data();
  std::cout << first(data) + second(data) + sum(data) << "\n";
}
