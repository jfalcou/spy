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
    int sz = sizeof...(c);
    char arr[] = {c...};
    while (i0 < sz && arr[i0] != '\'') ++i0;
    return i0;
  }

  template<char... c> constexpr int parse(int i0, int i1)
  {
    char arr[] = {c...};
    int value = 0;
    while (i0 < i1 && arr[i0] != '\'') value = value * 10 + (arr[i0++] - 48);
    return value;
  }

  template<template<int, int, int> class Wrapper, char... c> constexpr auto literal_wrap()
  {
    constexpr int b0 = 0, e0 = find<c...>(0);
    constexpr int b1 = e0 + 1, e1 = find<c...>(b1);
    constexpr int b2 = e1 + 1, e2 = sizeof...(c);

    return Wrapper<parse<c...>(b0, e0), parse<c...>(b1, e1), parse<c...>(b2, e2)>{};
  }

  template<int M, int N, int P> struct version_id
  {
    static constexpr int major = M;
    static constexpr int minor = N;
    static constexpr int patch = P;
  };

  template<int M1, int N1, int P1, int M2, int N2, int P2>
  constexpr bool operator==(version_id<M1, N1, P1>, version_id<M2, N2, P2>) noexcept
  {
    return (M1 == M2) && (N1 == N2) && (P1 == P2);
  }

  template<int M1, int N1, int P1, int M2, int N2, int P2>
  constexpr std::strong_ordering operator<=>(version_id<M1, N1, P1>, version_id<M2, N2, P2>) noexcept
  {
    if constexpr (constexpr auto cmp = M1 <=> M2; cmp != 0) return cmp;
    else if constexpr (constexpr auto cmp = N1 <=> N2; cmp != 0) return cmp;
    else return P1 <=> P2;
  }

  template<int M = 1, int N = 0, int P = 0> constexpr inline version_id<M, N, P> version = {};

  using unspecified_version_t = version_id<-1, 0, 0>;
  constexpr inline unspecified_version_t unspecified_version = {};

  template<_::stream OS, int M, int N, int P> OS& operator<<(OS& os, version_id<M, N, P> const&)
  {
    return os << "v" << M << "." << N << "." << P;
  }

  template<_::stream OS> OS& operator<<(OS& os, unspecified_version_t const&)
  {
    return os << "(unspecified)";
  }
}
