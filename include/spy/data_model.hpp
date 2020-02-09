//==================================================================================================
/*
  SPY - C++ Informations Broker
  Copyright 2020 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
 */
//==================================================================================================
#ifndef SPY_DATA_MODEL_HPP_INLUDED
#define SPY_DATA_MODEL_HPP_INLUDED

#include <iosfwd>

namespace spy { namespace detail
{
  template<int SS, int SI, int SL, int SPTR>
  struct data_model_info
  {
    inline constexpr operator bool() const noexcept;

    template<int SS2, int SI2, int SL2, int SPTR2>
    constexpr bool operator==(data_model_info<SS2, SI2, SL2, SPTR2> const& c2) const noexcept
    {
      return (SS==SS2) && (SI == SI2) && (SL == SL2) && (SPTR == SPTR2);
    }
  };

  template<int SS, int SI, int SL, int SPTR>
  std::ostream& operator<<(std::ostream& os, data_model_info<SS, SI, SL, SPTR> const&)
  {
          if constexpr(SPTR == 4 && SI == 4) return os << "ILP32";
    else  if constexpr(SPTR == 4 && SI == 2) return os << "LP32";
    else  if constexpr(SPTR == 8 && SL == 8 && SI == 8 && SS == 8)  return os << "SILP64";
    else  if constexpr(SPTR == 8 && SS == 8 && SI == 8 && SS == 2)  return os << "ILP64";
    else  if constexpr(SPTR == 8 && SL == 4 && SI == 8 && SS == 2)  return os << "LLP64";
    else  if constexpr(SPTR == 8 && SL == 8 && SI == 4 && SS == 2)  return os << "LP64";
    else  return os << "Unknown data model";
  }
} }

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

namespace spy { namespace detail
{
  template<int SS, int SI, int SL, int SPTR>
  inline constexpr data_model_info<SS, SI, SL, SPTR>::operator bool() const noexcept
  {
    return *this == spy::data_model;
  }
} }

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

#endif
