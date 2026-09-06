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
#if __has_feature(address_sanitizer)
#define SPY_ADDRESS_SANITIZERS_ENABLED
#endif
#if __has_feature(thread_sanitizer)
#define SPY_THREAD_SANITIZERS_ENABLED
#endif
#endif

// g++/MSVC detection
#if !defined(SPY_ADDRESS_SANITIZERS_ENABLED)
#if defined(__SANITIZE_ADDRESS__)
#define SPY_ADDRESS_SANITIZERS_ENABLED
#endif
#endif

#if !defined(SPY_THREAD_SANITIZERS_ENABLED)
#if defined(__SANITIZE_THREAD__)
#define SPY_THREAD_SANITIZERS_ENABLED
#endif
#endif

namespace spy::supports
{
#if defined(SPY_ADDRESS_SANITIZERS_ENABLED)
  constexpr inline bool address_sanitizers_status = true;
#elif defined(SPY_DOXYGEN_INVOKED)
  //==================================================================================================
  //! @ingroup api
  //! @brief Address sanitizer status indicator.
  //!
  //! Evaluates to `true` when the current code is compiled with `-fsanitize=address`.
  //!
  //! @groupheader{Example}
  //! @godbolt{samples/sanitizers.cpp}
  //==================================================================================================
  constexpr inline bool address_sanitizers_status = _::implementation_defined {};
#else
  constexpr inline bool address_sanitizers_status = false;
#endif

#if defined(SPY_THREAD_SANITIZERS_ENABLED)
  constexpr inline bool thread_sanitizers_status = true;
#elif defined(SPY_DOXYGEN_INVOKED)
  //==================================================================================================
  //! @ingroup api
  //! @brief Thread sanitizer status indicator.
  //!
  //! Evaluates to `true` when the current code is compiled with `-fsanitize=thread`.
  //!
  //! @groupheader{Example}
  //! @godbolt{samples/sanitizers.cpp}
  //==================================================================================================
  constexpr inline bool thread_sanitizers_status = _::implementation_defined {};
#else
  constexpr inline bool thread_sanitizers_status = false;
#endif

  //==================================================================================================
  //! @ingroup api
  //! @brief Sanitizers status indicator.
  //!
  //! Evaluates to `true` when any of the sanitizers spy detects is enabled.
  //!
  //! @groupheader{Example}
  //! @godbolt{samples/sanitizers.cpp}
  //==================================================================================================
  constexpr inline bool sanitizers_status = address_sanitizers_status || thread_sanitizers_status;
}

#if defined(SPY_COMPILER_IS_CLANG) || defined(SPY_COMPILER_IS_GCC) ||                              \
    defined(SPY_COMPILER_IS_CLANGCL) || defined(SPY_COMPILER_IS_MINGW32) ||                        \
    defined(SPY_COMPILER_IS_MINGW64)
#define SPY_DISABLE_ADDRESS_SANITIZERS __attribute__((no_sanitize_address))
#define SPY_DISABLE_THREAD_SANITIZERS  __attribute__((no_sanitize_thread))
#elif defined(SPY_COMPILER_IS_MSVC)
#define SPY_DISABLE_ADDRESS_SANITIZERS __declspec(no_sanitize_address)
#define SPY_DISABLE_THREAD_SANITIZERS
#else
#define SPY_DISABLE_ADDRESS_SANITIZERS
#define SPY_DISABLE_THREAD_SANITIZERS
#endif

#define SPY_DISABLE_SANITIZERS SPY_DISABLE_ADDRESS_SANITIZERS SPY_DISABLE_THREAD_SANITIZERS
