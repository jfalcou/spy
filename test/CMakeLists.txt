## -------------------------------------------------------------------------------------------------
##                              Copyright 2018 Joel FALCOU
##
##                   Distributed under the Boost Software License, Version 1.0.
##                        See accompanying file LICENSE.txt or copy at
##                            http://www.boost.org/LICENSE_1_0.txt
## -------------------------------------------------------------------------------------------------

if( MSVC )
  set( options /std:c++latest -W3 -EHsc )
else()
  set( options -std=c++17 -Wall -Wno-missing-braces )
endif()

add_executable          ( spy.version   version.cpp   )
add_executable          ( spy.compiler  compiler.cpp  )

target_compile_options  ( spy.version   PUBLIC ${options} )
target_compile_options  ( spy.compiler  PUBLIC ${options} )

add_test                ( NAME spy.version
                          COMMAND spy.version
                          WORKING_DIRECTORY "${PROJECT_BINARY_DIR}/test"
                        )

add_test                ( NAME spy.compiler
                          COMMAND spy.compiler
                          WORKING_DIRECTORY "${PROJECT_BINARY_DIR}/test"
                        )
