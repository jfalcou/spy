##==================================================================================================
##  SPY - C++ Informations Broker
##  Copyright : SPY Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================
set(CMAKE_SYSTEM_NAME Linux     )
set(CMAKE_SYSTEM_PROCESSOR arm  )

set(CMAKE_SYSROOT       /usr/arm-linux-gnueabihf/ )
set(CMAKE_C_COMPILER    clang                     )
set(CMAKE_CXX_COMPILER  clang++                   )
set(CMAKE_BUILD_TYPE    Debug                     )

set(CMAKE_CXX_FLAGS         "--target=armv7a-linux-gnueabihf -I/usr/arm-linux-gnueabihf/include/c++/10/arm-linux-gnueabihf" )
set(CMAKE_EXE_LINKER_FLAGS  "-fuse-ld=lld"  )
set(CMAKE_CROSSCOMPILING_CMD ../run_arm     )
