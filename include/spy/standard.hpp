//==================================================================================================
/*
  SPY - C++ Informations Broker
  Copyright : SPY Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

// Make sure the proper header is included to detect GNU libc
#include <spy/detail.hpp>

#include <compare>
#include <cstddef>

namespace spy::_
{
  template<int Year> struct cpp_standard_t
  {
    static constexpr int                   year = Year;

    template<int OtherYear> constexpr auto operator<=>(cpp_standard_t<OtherYear>) const
    {
      return year <=> OtherYear;
    }

    template<int OtherYear> constexpr bool operator==(cpp_standard_t<OtherYear>) const
    {
      return year == OtherYear;
    }

    constexpr auto operator<=>(int other_year) const { return year <=> other_year; }

    constexpr bool operator==(int other_year) const { return year == other_year; }
  };

  template<_::stream OS, int Y> auto& operator<<(OS& os, cpp_standard_t<Y> const&)
  {
    if constexpr(Y != 0) return os << "C++" << Y;
    else return os << "Unknown C++ standard version";
  }
}

namespace spy
{
  //================================================================================================
  // C++ Standard detection object type
  //================================================================================================
#if defined(_MSVC_LANG)
#define SPY_RAW_CXX_STANDARD _MSVC_LANG
#else
#define SPY_RAW_CXX_STANDARD __cplusplus
#endif

#if SPY_RAW_CXX_STANDARD > 202302L
#define SPY_CXX_VERSION 26
#elif SPY_RAW_CXX_STANDARD >= 202302L
#define SPY_CXX_VERSION 23
#elif SPY_RAW_CXX_STANDARD >= 202002L
#define SPY_CXX_VERSION 20
#else
#define SPY_CXX_VERSION 0
#endif

  //================================================================================================
  //! @ingroup api
  //! @brief C++ standard version reporting value
  //!
  //! The `spy::current_standard` object can be compared to any other current_standard related value
  //! to verify if the code being compiled with a specific version of the C++ standard.
  //!
  //! @groupheader{Example}
  //! @godbolt{samples/standard.cpp}
  //================================================================================================
  inline constexpr _::cpp_standard_t<SPY_CXX_VERSION> cpp_standard {};
}

namespace spy::literal
{
  //! @ingroup api
  //! @brief User-defined suffix for C++ standard definition
  template<char... c>
    requires(sizeof...(c) == 2)
  constexpr auto operator""_cpp()
  {
    return _::cpp_standard_t<_::parse<c...>(0, 2)> {};
  }
}
