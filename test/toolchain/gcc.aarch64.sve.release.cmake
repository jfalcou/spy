##==================================================================================================
##  SPY - C++ Informations Broker
##  Copyright : SPY Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_C_COMPILER    aarch64-linux-gnu-gcc-11 )
set(CMAKE_CXX_COMPILER  aarch64-linux-gnu-g++-11 )
set(CMAKE_BUILD_TYPE    Release                  )
set(CMAKE_CXX_FLAGS     "-march=armv8-a+sve -msve-vector-bits=512" )

set(CMAKE_CROSSCOMPILING_CMD qemu-aarch64)
