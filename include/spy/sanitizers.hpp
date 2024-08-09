//==================================================================================================
/*
  SPY - C++ Informations Broker
  Copyright : SPY Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once
#include <spy/compiler.hpp>

// Clang detection
#if defined(__has_feature)
#  if __has_feature(address_sanitizer)
#     define SPY_ADDRESS_SANITIZERS_ENABLED
#  endif
#  if __has_feature(thread_sanitizer)
#     define SPY_THREAD_SANITIZERS_ENABLED
#  endif
#endif

// g++/MSVC detection
#if !defined(SPY_ADDRESS_SANITIZERS_ENABLED)
#  if defined(__SANITIZE_ADDRESS__)
#     define SPY_ADDRESS_SANITIZERS_ENABLED
#  endif
#endif

#if !defined(SPY_THREAD_SANITIZERS_ENABLED)
#  if defined(__SANITIZE_THREAD__)
#     define SPY_THREAD_SANITIZERS_ENABLED
#  endif
#endif

namespace spy::supports
{
#if defined(SPY_ADDRESS_SANITIZERS_ENABLED)
  constexpr bool address_sanitizers_status = true;
#elif defined(SPY_DOXYGEN_INVOKED)
  //==================================================================================================
  //! @ingroup api
  //! @brief Thread sanitizer status indicator.
  //!
  //! Indicate if current code is compile using `-fsanitize=address`.
  //!
  //! @groupheader{Example}
  //! @godbolt{samples/sanitizers.cpp}
  //==================================================================================================
  constexpr bool address_sanitizers_status = **implementation-specified**;
#else
  constexpr bool address_sanitizers_status = false;
#endif

#if defined(SPY_THREAD_SANITIZERS_ENABLED)
  constexpr bool thread_sanitizers_status = true;
#elif defined(SPY_DOXYGEN_INVOKED)
  //==================================================================================================
  //! @ingroup api
  //! @brief Thread sanitizer status indicator.
  //!
  //! Indicate if current code is compile using `-fsanitize=threads`.
  //!
  //! @groupheader{Example}
  //! @godbolt{samples/sanitizers.cpp}
  //==================================================================================================
  constexpr bool thread_sanitizers_status = **implementation-specified**;
#else
  constexpr bool thread_sanitizers_status = false;
#endif

  //==================================================================================================
  //! @ingroup api
  //! @brief Sanitizers status indicator.
  //!
  //! Aggregate the status of all detected sanitizers
  //!
  //! @groupheader{Example}
  //! @godbolt{samples/sanitizers.cpp}
  //==================================================================================================
  constexpr bool sanitizers_status = address_sanitizers_status || thread_sanitizers_status;
}

#if defined(SPY_COMPILER_IS_CLANG) || defined(SPY_COMPILER_IS_GCC)
#define SPY_DISABLE_ADDRESS_SANITIZERS  __attribute__((no_sanitize_address))
#define SPY_DISABLE_THREAD_SANITIZERS   __attribute__((no_sanitize_thread))
#elif defined(SPY_COMPILER_IS_MSVC)
#define SPY_DISABLE_ADDRESS_SANITIZERS  __declspec(no_sanitize_address)
#define SPY_DISABLE_THREAD_SANITIZERS
#else
#define SPY_DISABLE_ADDRESS_SANITIZERS
#define SPY_DISABLE_THREAD_SANITIZERS
#endif

#define SPY_DISABLE_SANITIZERS SPY_DISABLE_ADDRESS_SANITIZERS SPY_DISABLE_THREAD_SANITIZERS
