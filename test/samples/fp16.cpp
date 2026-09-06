#include <iostream>
#include <spy/spy.hpp>

int main()
{
  if constexpr(spy::supports::fp16::type)
  {
    std::cout << "_Float16 is available.\n";

    if constexpr(spy::supports::fp16::scalar_ops)
      std::cout << "Scalar half-precision arithmetic is available.\n";

    if constexpr(spy::supports::fp16::vector_ops)
      std::cout << "Vector half-precision arithmetic is available.\n";
    else if constexpr(spy::supports::fp16::vector_conversion)
      std::cout << "Packed half-precision conversions are available.\n";
  }
  else
  {
    std::cout << "_Float16 is not available.\n";
  }
}
