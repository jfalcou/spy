##==================================================================================================
##  SPY - C++ Informations Broker
##  Copyright 2020-2021 Joel FALCOU
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================
set(CMAKE_SYSTEM_NAME Linux         )
set(CMAKE_SYSTEM_PROCESSOR powerpc  )

set(CMAKE_C_COMPILER    powerpc-linux-gnu-gcc-10  )
set(CMAKE_CXX_COMPILER  powerpc-linux-gnu-g++-10  )
set(CMAKE_BUILD_TYPE    Debug                     )
set(CMAKE_CXX_FLAGS     "-static"                 )

set(CMAKE_CROSSCOMPILING_CMD qemu-ppc)
