//======================================================================================================================
/*
  SPY - C++ Informations Broker
  Copyright : SPY Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#ifndef SPY_SPY_HPP_INCLUDED
#define SPY_SPY_HPP_INCLUDED

//======================================================================================================================
//! @namespace spy
//! @brief Main SPY namespace
//======================================================================================================================
namespace spy
{
  //====================================================================================================================
  //! @defgroup api Main API
  //! @brief Everything spy reports about the target, the toolchain and the flags it was given
  //!
  //! Every axis spy detects is a `constexpr` object living in namespace `spy`, so a question the
  //! preprocessor used to answer becomes a value any `constexpr` context can read. The six groups
  //! below sort those values by the question they answer.
  //!
  //! A value is read in three ways, shown here on the compiler:
  //!
  //! @code{.cpp}
  //! // compared to a named value
  //! if constexpr(spy::compiler == spy::gcc_) { }
  //!
  //! // or the named value itself, which converts to bool
  //! if constexpr(spy::gcc_) { }
  //!
  //! // and any of them prints
  //! std::cout << spy::compiler;
  //! @endcode
  //!
  //! Versions are named by a user-defined literal per vendor, gathered in `spy::literal`, and the
  //! ordering operators compare against them:
  //!
  //! @code{.cpp}
  //! using namespace spy::literal;
  //! if constexpr(spy::compiler >= 15'0_clang) { } // clang 15 or later
  //! @endcode
  //!
  //! Two different vendors compare as `std::partial_ordering::unordered` rather than as `false`, so
  //! `spy::gcc_ < spy::clang_` has no answer instead of a wrong one.
  //!
  //! Capabilities that are not an axis of their own live in `spy::supports`, each a plain
  //! `constexpr inline bool`.
  //!
  //! @{
  //!   @defgroup spy_platform Target Platforms
  //!   @brief The system, the processor and the data model the code is compiled for
  //!
  //!   Where the code will run. `spy::operating_system` names the system and
  //!   `spy::supports::posix_` says whether it offers a POSIX interface, `spy::architecture` names
  //!   the processor family, and `spy::data_model` gives the sizes the ABI hands the fundamental
  //!   types, which the system and the architecture decide together.
  //!
  //!   @defgroup spy_compiler Compilers
  //!   @brief The compiler processing the code, and the literals naming its versions
  //!
  //!   `spy::compiler` reports the toolchain as itself: a compiler that imitates another still
  //!   answers with its own name. The literals gathered here name a version to compare it against.
  //!
  //!   @defgroup spy_standards Language Standards
  //!   @brief The C++ standard in force, and the C and C++ standard library implementations
  //!
  //!   What the code is allowed to say and what it can call: the standard the compiler was told to
  //!   follow, and the two library implementations behind the headers it includes.
  //!
  //!   @defgroup spy_isa Instruction Sets
  //!   @brief The SIMD extensions the flags turn on, and what they can compute
  //!
  //!   `spy::simd_instruction_set` names the extension the flags enabled and the width of its
  //!   registers, and the `spy::supports::fp16` indicators say what that unit does with
  //!   half-precision, which the same architecture macros decide.
  //!   @{
  //!     @defgroup spy_isa_supplemental Supplemental Instruction Sets
  //!     @brief The instructions some extensions add on top of an existing set
  //!
  //!     One indicator per supplemental set, `true` when the flags turned it on. The AVX family
  //!     adds FMA3, FMA4, XOP and F16C, and the AVX-512 subsets live in their own namespace.
  //!   @}
  //!
  //!   @defgroup spy_accelerator Accelerators
  //!   @brief The accelerator programming models the code is compiled with
  //!
  //!   These report how the current translation unit is being compiled, not what the machine
  //!   holds: they are true when the compiler was asked for CUDA or for SYCL, whatever device is
  //!   present.
  //!
  //!   @defgroup spy_sanitizers Sanitizers
  //!   @brief The sanitizers the code is compiled with
  //!
  //!   Whether the binary carries the instrumentation of the address or the thread sanitizer, so
  //!   that code which the instrumentation would slow down or trip can step aside at compile time.
  //! @}
  //====================================================================================================================

  //====================================================================================================================
  //! @namespace supports
  //! @brief Support detection SPY namespace
  //====================================================================================================================
  namespace supports
  {
  }

  //====================================================================================================================
  //! @namespace literal
  //! @brief SPY User-defined literal namespace
  //====================================================================================================================
  namespace literal
  {
  }
}

#if defined(_MSC_VER)
#if _MSVC_LANG < 202002L
#error "SPY C++ version error"
#include "SPY requires C++20 or higher. Use /std:c++20 or higher to enable C++20 features."
#endif
#else
#if __cplusplus < 202002L
#error "SPY C++ version error"
#include "SPY requires C++20 or higher. Use -std=c++20 or higher to enable C++20 features."
#endif
#endif

#include <spy/detail.hpp>

#include <spy/accelerator.hpp>
#include <spy/arch.hpp>
#include <spy/compiler.hpp>
#include <spy/data_model.hpp>
#include <spy/libc.hpp>
#include <spy/os.hpp>
#include <spy/sanitizers.hpp>
#include <spy/simd.hpp>
#include <spy/standard.hpp>
#include <spy/stdlib.hpp>
#include <spy/types.hpp>

#endif
