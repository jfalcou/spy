## -------------------------------------------------------------------------------------------------
## Copyright 2018 Joel FALCOU
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
## -------------------------------------------------------------------------------------------------
include(download)

## Disable testing LEST
set(LEST_BUILD_TEST OFF CACHE INTERNAL    "OFF")
set(LEST_BUILD_EXAMPLE OFF CACHE INTERNAL "OFF")

download_project( PROJ                lest
                  GIT_REPOSITORY      https://github.com/martinmoene/lest
                  GIT_TAG             master
                  "UPDATE_DISCONNECTED 1"
                  QUIET
                )

add_subdirectory(${lest_SOURCE_DIR} ${lest_BINARY_DIR})

## Setup our tests
add_custom_target(tests)
add_custom_target(unit)
add_dependencies(tests unit)

add_subdirectory(${PROJECT_SOURCE_DIR}/test/)
