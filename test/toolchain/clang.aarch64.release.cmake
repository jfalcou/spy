##==================================================================================================
##  SPY - C++ Informations Broker
##  Copyright 2020-2021 Joel FALCOU
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================
set(CMAKE_SYSTEM_NAME Linux   )
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_SYSROOT       /usr/aarch64-linux-gnu)
set(CMAKE_C_COMPILER    clang-10              )
set(CMAKE_CXX_COMPILER  clang++-10            )
set(CMAKE_BUILD_TYPE    Release               )

set(CMAKE_CXX_FLAGS         "--target=aarch64-pc-linux-gnu -I/usr/aarch64-linux-gnu/include/c++/10/aarch64-linux-gnu" )
set(CMAKE_EXE_LINKER_FLAGS  "-fuse-ld=lld")
set(CMAKE_CROSSCOMPILING_CMD qemu-aarch64)
