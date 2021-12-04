##==================================================================================================
##  SPY - C++ Informations Broker
##  Copyright : SPY Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================
set(CMAKE_SYSTEM_NAME Linux         )
set(CMAKE_SYSTEM_PROCESSOR powerpc  )

set(CMAKE_C_COMPILER    powerpc64-linux-gnu-gcc-11 )
set(CMAKE_CXX_COMPILER  powerpc64-linux-gnu-g++-11 )
set(CMAKE_BUILD_TYPE    Release                    )
set(CMAKE_CXX_FLAGS     "-static"                  )

set(CMAKE_CROSSCOMPILING_CMD qemu-ppc64)
