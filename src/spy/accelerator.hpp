//==================================================================================================
/**
  SPY - C++ Informations Broker
  Copyright : SPY Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#pragma once
#include <ostream>

namespace spy::supports
{
  template<int M, int N, int P> struct  sycl_t
  {
    explicit constexpr operator bool() const noexcept { return M>0 && N>0; }

    friend std::ostream& operator<<(std::ostream& os, sycl_t)
    {
      os << "SYCL v" << M << '.' << N;
      if(P>0) os << '.' << P;
      return os;
    }
  };

  template<int M0, int N0, int P0, int M1, int N1, int P1>
  constexpr inline bool operator==(sycl_t<M0,N0,P0> const&, sycl_t<M1,N1,P1> const&) noexcept
  {
    return M0==M1 && N0==N1 && P0==P1;
  }

  template<int M0, int N0, int P0, int M1, int N1, int P1>
  constexpr inline bool operator!=(sycl_t<M0,N0,P0> const& a, sycl_t<M1,N1,P1> const& b) noexcept
  {
    return !(a==b);
  }

#if defined(SYCL_LANGUAGE_VERSION) && defined (__INTEL_LLVM_COMPILER)
#  define SPY_ACCELERATOR_SUPPORTS_SYCL
  constexpr inline auto  sycl  = sycl_t<SYCL_LANGUAGE_VERSION/100, SYCL_LANGUAGE_VERSION%100, 0>{};
#else
  constexpr inline auto  sycl  = sycl_t<-1,-1,-1>{};
#endif
}
