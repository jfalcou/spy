//==================================================================================================
/*
  Copyright 2018 Joel FALCOU

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */
//==================================================================================================
#ifndef SPY_VERSION_HPP_INLUDED
#define SPY_VERSION_HPP_INLUDED

#include <iosfwd>

namespace spy
{
  template<int M, int N = 0, int P = 0> struct version_
  {
    static constexpr int major = M;
    static constexpr int minor = N;
    static constexpr int patch = P;
  };

  template<int M, int N = 0, int P = 0>
  constexpr inline version_<M,N,P> version = {};

  template<int M1, int N1, int P1, int M2, int N2, int P2>
  constexpr bool operator==(version_<M1,N1,P1> const&, version_<M2,N2,P2> const&) noexcept
  {
    return (M1==M2) && (N1==N2) && (P1==P2);
  }

  template<int M1, int N1, int P1, int M2, int N2, int P2>
  constexpr bool operator!=(version_<M1,N1,P1> const& v1, version_<M2,N2,P2> const& v2) noexcept
  {
    return !(v1==v2);
  }

  template<int M1, int N1, int P1, int M2, int N2, int P2>
  constexpr bool operator<(version_<M1,N1,P1> const&, version_<M2,N2,P2> const&) noexcept
  {
    if constexpr(M1 < M2) return true;
    if constexpr(M1 > M2) return false;
    if constexpr(N1 < N2) return true;
    if constexpr(N1 > N2) return false;
    return P1 < P2;
  }

  template<int M1, int N1, int P1, int M2, int N2, int P2>
  constexpr bool operator>(version_<M1,N1,P1> const&, version_<M2,N2,P2> const&) noexcept
  {
    if constexpr(M1 > M2) return true;
    if constexpr(M1 < M2) return false;
    if constexpr(N1 > N2) return true;
    if constexpr(N1 < N2) return false;
    return P1 > P2;
  }

  template<int M1, int N1, int P1, int M2, int N2, int P2>
  constexpr bool operator<=(version_<M1,N1,P1> const& a, version_<M2,N2,P2> const& b) noexcept
  {
    return !(a>b);
  }

  template<int M1, int N1, int P1, int M2, int N2, int P2>
  constexpr bool operator>=(version_<M1,N1,P1> const& a, version_<M2,N2,P2> const& b) noexcept
  {
    return !(a<b);
  }

  template<int M, int N, int P>
  std::ostream& operator<<(std::ostream& os, version_<M,N,P> const&)
  {
    return os << "v" << M << "." << N << "." << P;
  }

  template<typename Descriptor> constexpr auto version_of(Descriptor const& d) noexcept
  {
    return d.version;
  }
}

#endif
