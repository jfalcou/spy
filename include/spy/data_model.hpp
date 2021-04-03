//==================================================================================================
/**
  SPY - C++ Informations Broker
  Copyright : SPY Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

namespace spy::detail
{
  template<int Short, int Integer, int Long, int Pointer>
  struct data_model_info
  {
    inline constexpr operator bool() const noexcept;

    template<int Short2, int Integer2, int Long2, int Pointer2>
    constexpr bool operator==(data_model_info<Short2, Integer2, Long2, Pointer2> const& ) const noexcept
    {
      return (Short==Short2) && (Integer == Integer2) && (Long == Long2) && (Pointer == Pointer2);
    }
  };

  template<int Short, int Integer, int Long, int Pointer>
  std::ostream& operator<<(std::ostream& os, data_model_info<Short, Integer, Long, Pointer> const&)
  {
          if constexpr(Pointer == 4 && Integer == 4) return os << "ILP32";
    else  if constexpr(Pointer == 4 && Integer == 2) return os << "LP32";
    else  if constexpr(Pointer == 8 && Long == 8 && Integer == 8 && Short == 8)  return os << "IntegerLP64";
    else  if constexpr(Pointer == 8 && Short == 8 && Integer == 8 && Short == 2)  return os << "ILP64";
    else  if constexpr(Pointer == 8 && Long == 4 && Integer == 8 && Short == 2)  return os << "LLP64";
    else  if constexpr(Pointer == 8 && Long == 8 && Integer == 4 && Short == 2)  return os << "LP64";
    else  return os << "Unknown data model";
  }
}

namespace spy
{
  using data_model_type = detail::data_model_info < sizeof(short), sizeof(int)
                                                  , sizeof(long), sizeof(void*)
                                                  >;

  //================================================================================================
  // Data model detection object
  //================================================================================================
  constexpr inline data_model_type data_model;
}

namespace spy::detail
{
  template<int Short, int Integer, int Long, int Pointer>
  inline constexpr data_model_info<Short, Integer, Long, Pointer>::operator bool() const noexcept
  {
    return *this == spy::data_model;
  }
}

namespace spy
{
  //================================================================================================
  // Data model detector stand-alone instances
  //================================================================================================
  constexpr inline auto ilp32_  = detail::data_model_info<2,4,sizeof(long),4>{};
  constexpr inline auto lp32_   = detail::data_model_info<2,2,sizeof(long),4>{};
  constexpr inline auto silp64_ = detail::data_model_info<8,8,8,8>{};
  constexpr inline auto ilp64_  = detail::data_model_info<2,8,8,8>{};
  constexpr inline auto llp64_  = detail::data_model_info<2,8,4,8>{};
  constexpr inline auto lp64_   = detail::data_model_info<2,4,8,8>{};
}
