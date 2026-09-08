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
  //! @brief What spy reports, one group per detection axis
  //!
  //! @{
  //!   @defgroup spy_platform Target Platforms
  //!   @brief The system, the processor and the data model the code is compiled for
  //!
  //!   @defgroup spy_compiler Compilers
  //!   @brief The compiler processing the code, and the literals naming its versions
  //!
  //!   @defgroup spy_standards Language Standards
  //!   @brief The C++ standard in force, and the C and C++ standard library implementations
  //!
  //!   @defgroup spy_isa Instruction Sets
  //!   @brief The SIMD extensions the flags turn on, and what they can compute
  //!
  //!   @defgroup spy_accelerator Accelerators
  //!   @brief The accelerator programming models the code is compiled with
  //!
  //!   @defgroup spy_sanitizers Sanitizers
  //!   @brief The sanitizers the code is compiled with
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
