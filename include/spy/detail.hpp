//==================================================================================================
/*
  SPY - C++ Informations Broker
  Copyright : SPY Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <compare>

namespace spy::_
{
  template<typename T>
  concept stream = requires(T& os, char c) {
    { os.copyfmt(os) };
    { os.flush() };
    { os.put(c) };
  };

  template<char... c> constexpr int find(int i0)
  {
    int  sz    = sizeof...(c);
    char arr[] = {c...}; // NOSONAR - <array> is outside the two standard headers spy includes
    while(i0 < sz && arr[ i0 ] != '\'') ++i0;
    return i0;
  }

  template<char... c> constexpr int parse(int i0, int i1)
  {
    char arr[] = {c...}; // NOSONAR - <array> is outside the two standard headers spy includes
    int  value = 0;
    while(i0 < i1 && arr[ i0 ] != '\'') value = value * 10 + (arr[ i0++ ] - 48);
    return value;
  }

  template<template<int, int, int> class Wrapper, char... c> constexpr auto literal_wrap()
  {
    constexpr int b0 = 0;
    constexpr int e0 = find<c...>(0);
    constexpr int b1 = e0 + 1;
    constexpr int e1 = find<c...>(b1);
    constexpr int b2 = e1 + 1;
    constexpr int e2 = sizeof...(c);

    return Wrapper<parse<c...>(b0, e0), parse<c...>(b1, e1), parse<c...>(b2, e2)> {};
  }

  template<int M, int N, int P> struct version_id
  {
    static constexpr int major = M;
    static constexpr int minor = N;
    static constexpr int patch = P;

    template<int M2, int N2, int P2>
    friend constexpr bool operator==(version_id, version_id<M2, N2, P2>) noexcept
    {
      return (M == M2) && (N == N2) && (P == P2);
    }

    template<int M2, int N2, int P2>
    friend constexpr std::strong_ordering operator<=>(version_id, version_id<M2, N2, P2>) noexcept
    {
      if constexpr(constexpr auto cmp0 = M <=> M2; cmp0 != 0) return cmp0;
      else if constexpr(constexpr auto cmp1 = N <=> N2; cmp1 != 0) return cmp1;
      else return P <=> P2;
    }

    template<_::stream OS> friend auto& operator<<(OS& os, version_id const&)
    {
      if constexpr(M == -1 && N == 0 && P == 0) return os << "(unspecified)";
      else return os << "v" << M << "." << N << "." << P;
    }
  };

  using unspecified_version_t                                = version_id<-1, 0, 0>;
  constexpr inline unspecified_version_t unspecified_version = {};
}
