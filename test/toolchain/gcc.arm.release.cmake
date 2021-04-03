##==================================================================================================
##  SPY - C++ Informations Broker
##  Copyright : SPY Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================
set(CMAKE_SYSTEM_NAME Linux     )
set(CMAKE_SYSTEM_PROCESSOR arm  )

set(CMAKE_C_COMPILER    arm-linux-gnueabihf-gcc-10  )
set(CMAKE_CXX_COMPILER  arm-linux-gnueabihf-g++-10  )
set(CMAKE_BUILD_TYPE    Release                     )
set(CMAKE_CXX_FLAGS     "-Wno-psabi"                )

set(CMAKE_CROSSCOMPILING_CMD ../run_arm     )
