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

#include <spy/detail.hpp>

#include <spy/accelerator.hpp>
#include <spy/arch.hpp>
#include <spy/compiler.hpp>
#include <spy/data_model.hpp>
#include <spy/libc.hpp>
#include <spy/os.hpp>
#include <spy/sanitizers.hpp>
#include <spy/simd.hpp>
#include <spy/stdlib.hpp>

#endif
