#include <iostream>
#include <spy/spy.hpp>

// Hot paths left out of the sanitizers
SPY_DISABLE_ADDRESS_SANITIZERS int first(int const* data) { return data[ 0 ]; }
SPY_DISABLE_THREAD_SANITIZERS int  second(int const* data) { return data[ 1 ]; }
SPY_DISABLE_SANITIZERS int         sum(int const* data, int size)
{
  int total = 0;
  for(int i = 0; i < size; ++i) total += data[ i ];
  return total;
}

int main()
{
  int data[ 4 ] = {1, 2, 3, 4};
  std::cout << first(data) + second(data) + sum(data, 4) << "\n";
}
