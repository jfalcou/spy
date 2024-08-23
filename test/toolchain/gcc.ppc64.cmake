##==================================================================================================
##  SPY - C++ Informations Broker
##  Copyright : SPY Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================
set(CMAKE_SYSTEM_NAME Linux         )
set(CMAKE_SYSTEM_PROCESSOR powerpc  )

set(CMAKE_C_COMPILER    powerpc64-linux-gnu-gcc-13 )
set(CMAKE_CXX_COMPILER  powerpc64-linux-gnu-g++-13 )
set(CMAKE_CXX_FLAGS     "-static"                  )

set(CMAKE_CROSSCOMPILING_CMD qemu-ppc64)
