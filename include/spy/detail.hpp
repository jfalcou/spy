//==================================================================================================
/*
  SPY - C++ Informations Broker
  Copyright 2020 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
 */
//==================================================================================================
#ifndef SPY_DETAIL_HPP_INLUDED
#define SPY_DETAIL_HPP_INLUDED

#include <iostream>

namespace spy { namespace detail
{
  template<char... c> constexpr int find(int i0)
  {
    int sz = sizeof...(c);
    char arr[] = {c...};
    while( i0<sz && arr[i0] != '\'' ) ++i0;
    return i0;
  }

  template<char... c> constexpr int parse(int i0, int i1)
  {
    char arr[] = {c...};
    int value = 0;
    while( i0<i1 && arr[i0] != '\'' ) value = value*10 + (arr[i0++] - 48);
    return value;
  }

  template<template<int,int,int> class Wrapper, char ...c> constexpr auto literal_wrap()
  {
    constexpr int b0 = 0     , e0 = find<c...>(0);
    constexpr int b1 = e0 + 1, e1 = find<c...>(b1);
    constexpr int b2 = e1+1  , e2 = sizeof...(c);

    return Wrapper<parse<c...>(b0,e0),parse<c...>(b1,e1),parse<c...>(b2,e2)>{};
  }

  template<int M, int N, int P> struct version_id
  {
    static constexpr int major = M;
    static constexpr int minor = N;
    static constexpr int patch = P;
  };

  template<int M = 1, int N = 0, int P = 0> constexpr inline version_id<M,N,P> version = {};

  using unspecified_version_t = version_id<-1,0,0>;
  constexpr inline unspecified_version_t unspecified_version = {};

  template<int M1, int N1, int P1, int M2, int N2, int P2>
  constexpr bool operator==(version_id<M1,N1,P1> const&, version_id<M2,N2,P2> const&) noexcept
  {
    return (M1==M2) && (N1==N2) && (P1==P2);
  }

  template<int M1, int N1, int P1, int M2, int N2, int P2>
  constexpr bool operator!=(version_id<M1,N1,P1> const& v1, version_id<M2,N2,P2> const& v2) noexcept
  {
    return !(v1==v2);
  }

  template<int M1, int N1, int P1, int M2, int N2, int P2>
  constexpr bool operator<(version_id<M1,N1,P1> const&, version_id<M2,N2,P2> const&) noexcept
  {
    if constexpr(M1 < M2) return true;
    if constexpr(M1 > M2) return false;
    if constexpr(N1 < N2) return true;
    if constexpr(N1 > N2) return false;
    return P1 < P2;
  }

  template<int M1, int N1, int P1, int M2, int N2, int P2>
  constexpr bool operator>(version_id<M1,N1,P1> const&, version_id<M2,N2,P2> const&) noexcept
  {
    if constexpr(M1 > M2) return true;
    if constexpr(M1 < M2) return false;
    if constexpr(N1 > N2) return true;
    if constexpr(N1 < N2) return false;
    return P1 > P2;
  }

  template<int M1, int N1, int P1, int M2, int N2, int P2>
  constexpr bool operator<=(version_id<M1,N1,P1> const& a, version_id<M2,N2,P2> const& b) noexcept
  {
    return !(a>b);
  }

  template<int M1, int N1, int P1, int M2, int N2, int P2>
  constexpr bool operator>=(version_id<M1,N1,P1> const& a, version_id<M2,N2,P2> const& b) noexcept
  {
    return !(a<b);
  }

  template<int M, int N, int P>
  std::ostream& operator<<(std::ostream& os, version_id<M,N,P> const&)
  {
    return os << "v" << M << "." << N << "." << P;
  }

  inline std::ostream& operator<<(std::ostream& os, unspecified_version_t const&)
  {
    return os << "(unspecified)";
  }
} }

#define SPY_VERSION_COMPARISONS_OPERATOR(ID,TYPE)                       \
template<ID C2,int M2, int N2, int P2>                                  \
constexpr bool operator==( TYPE<C2,M2,N2,P2> const& c2 ) const noexcept \
{                                                                       \
  return C2 == vendor && version == c2.version;                         \
}                                                                       \
                                                                        \
template<ID C2,int M2, int N2, int P2>                                  \
constexpr bool operator!=( TYPE<C2,M2,N2,P2> const& c2 ) const noexcept \
{                                                                       \
  return C2 == vendor && version != c2.version;                         \
}                                                                       \
                                                                        \
template<ID C2,int M2, int N2, int P2>                                  \
constexpr bool operator<( TYPE<C2,M2,N2,P2> const& c2 ) const noexcept  \
{                                                                       \
  return C2 == vendor && version < c2.version;                          \
}                                                                       \
                                                                        \
template<ID C2,int M2, int N2, int P2>                                  \
constexpr bool operator>( TYPE<C2,M2,N2,P2> const& c2 ) const noexcept  \
{                                                                       \
  return C2 == vendor && version > c2.version;                          \
}                                                                       \
                                                                        \
template<ID C2,int M2, int N2, int P2>                                  \
constexpr bool operator>=( TYPE<C2,M2,N2,P2> const& c2 ) const noexcept \
{                                                                       \
  return C2 == vendor && version >= c2.version;                         \
}                                                                       \
                                                                        \
template<ID C2,int M2, int N2, int P2>                                  \
constexpr bool operator<=( TYPE<C2,M2,N2,P2> const& c2 ) const noexcept \
{                                                                       \
  return C2 == vendor && version <= c2.version;                         \
}                                                                       \
/***/

#endif
