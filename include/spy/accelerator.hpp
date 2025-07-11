//==================================================================================================
/*
  SPY - C++ Informations Broker
  Copyright : SPY Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

namespace spy::supports
{
  template<int M, int N, int P> struct sycl_t
  {
    explicit constexpr operator bool() const noexcept { return M > 0 && N > 0; }

    template<_::stream OS> friend auto& operator<<(OS& os, sycl_t)
    {
      os << "SYCL v" << M << '.' << N;
      if (P > 0) os << '.' << P;
      return os;
    }

    template<int M1, int N1, int P1> constexpr inline bool operator==(sycl_t<M1, N1, P1> const&) const noexcept
    {
      return M == M1 && N == N1 && P == P1;
    }
  };

  template<int M, int N, int P> struct cuda_t
  {
    explicit constexpr operator bool() const noexcept { return M > 0 && N > 0; }

    template<int M1, int N1, int P1> constexpr inline bool operator==(cuda_t<M1, N1, P1> const&) const noexcept
    {
      return M == M1 && N == N1 && P == P1;
    }

    template<_::stream OS> friend auto& operator<<(OS& os, cuda_t)
    {
#if defined(__NVCC__)
      os << "NVCC ";
#elif defined(__clang__)
      os << "Clang ";
#endif

      os << "CUDA v" << M << '.' << N;
      if (P > 0) os << '.' << P;
      return os;
    }
  };

#if defined(SYCL_LANGUAGE_VERSION) && defined(__INTEL_LLVM_COMPILER)
#define SPY_ACCELERATOR_SUPPORTS_SYCL
  constexpr inline auto sycl = sycl_t<SYCL_LANGUAGE_VERSION / 100, SYCL_LANGUAGE_VERSION % 100, 0>{};
#elif defined(SPY_DOXYGEN_INVOKED)
  //================================================================================================
  //! @ingroup api
  //! @brief SYCL usage indicator.
  //!
  //! Retrieves the information about wether or not current file is compiled with SYCL supports.
  //!
  //! @groupheader{Example}
  //! @godbolt{samples/sycl.cpp}
  //================================================================================================
  constexpr inline auto sycl = **implementation - defined * *;

#else
  constexpr inline auto sycl = sycl_t<-1, -1, -1>{};
#endif

#if defined(__CUDACC__)
#if defined(__CUDACC_VER_MAJOR__)
#define SPY_ACCELERATOR_SUPPORTS_CUDA
  constexpr inline auto cuda = cuda_t<__CUDACC_VER_MAJOR__, __CUDACC_VER_MINOR__, 0>{};
#elif defined(CUDA_VERSION)
#define SPY_ACCELERATOR_SUPPORTS_CUDA
  constexpr inline auto cuda = cuda_t<CUDA_VERSION / 1000, (CUDA_VERSION % 1000) / 10, CUDA_VERSION % 10>{};
#endif
#elif defined(SPY_DOXYGEN_INVOKED)
  //================================================================================================
  //! @ingroup api
  //! @brief CUDA usage indicator.
  //!
  //! Retrieves the information about wether or not current file is compiled using NVCC.
  //! Note that this indicator works in both  .cpp and .cu files.
  //!
  //! @groupheader{Example}
  //! @godbolt{samples/cuda.cpp}
  //================================================================================================
  constexpr inline auto cuda = **implementation - defined * *;
#else
  constexpr inline auto cuda = cuda_t<-1, -1, -1>{};
#endif
}
