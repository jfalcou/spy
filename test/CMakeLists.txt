## -------------------------------------------------------------------------------------------------
## Copyright 2018-2020 Joel FALCOU
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
## -------------------------------------------------------------------------------------------------

if( MSVC )
  set( options /std:c++latest /W3 /EHsc )
else()
  set( options -std=c++17 -Wall)
endif()

add_executable( spy.arch      arch.cpp  )
add_executable( spy.compiler  compiler.cpp  )
add_executable( spy.libc      libc.cpp      )
add_executable( spy.stdlib    stdlib.cpp    )
add_executable( spy.os        os.cpp        )

target_compile_options( spy.arch      PUBLIC ${options} )
target_compile_options( spy.compiler  PUBLIC ${options} )
target_compile_options( spy.libc      PUBLIC ${options} )
target_compile_options( spy.stdlib    PUBLIC ${options} )
target_compile_options( spy.os        PUBLIC ${options} )

set_property( TARGET spy.arch     PROPERTY RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/unit" )
set_property( TARGET spy.compiler PROPERTY RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/unit" )
set_property( TARGET spy.libc     PROPERTY RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/unit" )
set_property( TARGET spy.stdlib   PROPERTY RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/unit" )
set_property( TARGET spy.os       PROPERTY RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/unit" )

target_include_directories( spy.arch     PRIVATE ${PROJECT_SOURCE_DIR}/include )
target_include_directories( spy.compiler PRIVATE ${PROJECT_SOURCE_DIR}/include )
target_include_directories( spy.libc     PRIVATE ${PROJECT_SOURCE_DIR}/include )
target_include_directories( spy.stdlib   PRIVATE ${PROJECT_SOURCE_DIR}/include )
target_include_directories( spy.os       PRIVATE ${PROJECT_SOURCE_DIR}/include )

if (CMAKE_CROSSCOMPILING_CMD)
    add_test( NAME spy.arch    WORKING_DIRECTORY "${PROJECT_BINARY_DIR}/unit"
              COMMAND ${CMAKE_CROSSCOMPILING_CMD} $<TARGET_FILE:spy.arch> --no-color --pass
            )
    add_test( NAME spy.compiler WORKING_DIRECTORY "${PROJECT_BINARY_DIR}/unit"
              COMMAND ${CMAKE_CROSSCOMPILING_CMD} $<TARGET_FILE:spy.compiler> --no-color --pass
            )
    add_test( NAME spy.libc     WORKING_DIRECTORY "${PROJECT_BINARY_DIR}/unit"
              COMMAND ${CMAKE_CROSSCOMPILING_CMD} $<TARGET_FILE:spy.libc> --no-color --pass
            )
    add_test( NAME spy.stdlib   WORKING_DIRECTORY "${PROJECT_BINARY_DIR}/unit"
              COMMAND ${CMAKE_CROSSCOMPILING_CMD} $<TARGET_FILE:spy.stdlib> --no-color --pass
            )
    add_test( NAME spy.os       WORKING_DIRECTORY "${PROJECT_BINARY_DIR}/unit"
              COMMAND ${CMAKE_CROSSCOMPILING_CMD} $<TARGET_FILE:spy.os> --no-color --pass
            )
  else()
    add_test( NAME spy.arch     COMMAND spy.arch      WORKING_DIRECTORY "${PROJECT_BINARY_DIR}/unit" )
    add_test( NAME spy.compiler COMMAND spy.compiler  WORKING_DIRECTORY "${PROJECT_BINARY_DIR}/unit" )
    add_test( NAME spy.libc     COMMAND spy.libc      WORKING_DIRECTORY "${PROJECT_BINARY_DIR}/unit" )
    add_test( NAME spy.stdlib   COMMAND spy.stdlib    WORKING_DIRECTORY "${PROJECT_BINARY_DIR}/unit" )
    add_test( NAME spy.os       COMMAND spy.os        WORKING_DIRECTORY "${PROJECT_BINARY_DIR}/unit" )
endif()

add_custom_target(unit)
add_custom_target(spy.unit)
add_dependencies(unit     spy.unit      )
add_dependencies(spy.unit spy.arch      )
add_dependencies(spy.unit spy.compiler  )
add_dependencies(spy.unit spy.libc      )
add_dependencies(spy.unit spy.stdlib    )
add_dependencies(spy.unit spy.os        )
