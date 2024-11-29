##======================================================================================================================
##  SPY - C++ Informations Broker
##  Copyright : SPY Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##======================================================================================================================

##======================================================================================================================
## Compiler options for Tests
##======================================================================================================================
add_library(spy_tests INTERFACE)

target_compile_features ( spy_tests INTERFACE  cxx_std_20 )

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  if(CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC")
    target_compile_options( spy_tests INTERFACE /W3 /EHsc )
  else()
    target_compile_options( spy_tests INTERFACE -Werror -Wall -Wextra -Wunused-variable -Wdocumentation)
  endif()
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_compile_options( spy_tests INTERFACE /W3 /EHsc /Zc:preprocessor)
else()
  target_compile_options( spy_tests INTERFACE -Werror -Wall -Wextra -Wunused-variable)
endif()

target_include_directories( spy_tests INTERFACE
                            ${PROJECT_SOURCE_DIR}/test
                            ${PROJECT_SOURCE_DIR}/include
                          )
