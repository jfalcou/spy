##==================================================================================================
##  SPY - C++ Informations Broker
##  Copyright : SPY Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================
set(CMAKE_SYSTEM_PROCESSOR arm  )

set(CMAKE_C_COMPILER    /opt/homebrew/opt/llvm@15/bin/clang   )
set(CMAKE_CXX_COMPILER  /opt/homebrew/opt/llvm@15/bin/clang++ )

set(CMAKE_CXX_FLAGS     " -DEVE_NO_FORCEINLINE ${EVE_OPTIONS}" )