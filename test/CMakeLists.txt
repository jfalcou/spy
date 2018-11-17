## -------------------------------------------------------------------------------------------------
## Copyright 2018 Joel FALCOU
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
## -------------------------------------------------------------------------------------------------

if( MSVC )
  set( options /std:c++latest /W3 /EHsc )
else()
  set( options -std=c++17 -Wall -Wno-missing-braces )
endif()

set ( test_includes -I${lest_SOURCE_DIR}/include
                    -I${PROJECT_SOURCE_DIR}/test
                    -I${PROJECT_SOURCE_DIR}/include
    )

add_executable( spy.compiler  compiler.cpp  )
add_executable( spy.libc      libc.cpp  )
add_executable( spy.stdlib    stdlib.cpp  )
add_executable( spy.os        os.cpp  )

target_compile_options  ( spy.compiler  PUBLIC ${options} ${test_includes})
target_compile_options  ( spy.libc      PUBLIC ${options} ${test_includes})
target_compile_options  ( spy.stdlib    PUBLIC ${options} ${test_includes})
target_compile_options  ( spy.os        PUBLIC ${options} ${test_includes})

add_test( NAME spy.compiler COMMAND spy.compiler WORKING_DIRECTORY "${PROJECT_BINARY_DIR}/test" )
add_test( NAME spy.libc     COMMAND spy.libc     WORKING_DIRECTORY "${PROJECT_BINARY_DIR}/test" )
add_test( NAME spy.stdlib   COMMAND spy.stdlib   WORKING_DIRECTORY "${PROJECT_BINARY_DIR}/test" )
add_test( NAME spy.os       COMMAND spy.os       WORKING_DIRECTORY "${PROJECT_BINARY_DIR}/test" )
