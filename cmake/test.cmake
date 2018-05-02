## -------------------------------------------------------------------------------------------------
##                              Copyright 2018 Joel FALCOU
##
##                   Distributed under the Boost Software License, Version 1.0.
##                        See accompanying file LICENSE.txt or copy at
##                            http://www.boost.org/LICENSE_1_0.txt
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
include_directories("${lest_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/test")

## Setup our tests
add_custom_target(tests)
add_custom_target(unit)
add_dependencies(tests unit)

add_subdirectory(${PROJECT_SOURCE_DIR}/test/)
