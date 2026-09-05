##==================================================================================================
##  SPY - C++ Informations Broker
##  Copyright : SPY Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================
## MINGW64_BIN is set by test/toolchain/setup_mingw64.sh, which the CI row sources before configuring.
if(DEFINED ENV{MINGW64_BIN})
  set(CMAKE_C_COMPILER    "$ENV{MINGW64_BIN}/gcc.exe" )
  set(CMAKE_CXX_COMPILER  "$ENV{MINGW64_BIN}/g++.exe" )
else()
  set(CMAKE_C_COMPILER    gcc )
  set(CMAKE_CXX_COMPILER  g++ )
endif()

## Linking statically keeps the test executables free of libstdc++ and libwinpthread, which live beside
## the compiler and would otherwise have to be on PATH for every step that runs a test.
set(CMAKE_EXE_LINKER_FLAGS_INIT "-static")
