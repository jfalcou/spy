##======================================================================================================================
##  SPY - C++ Informations Broker
##  Copyright : SPY Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##======================================================================================================================
cmake_minimum_required(VERSION 3.22)
project(spy LANGUAGES CXX)

if(DEFINED CMAKE_CUDA_COMPILER)
  enable_language(CUDA)
endif()

##======================================================================================================================
option( SPY_BUILD_TEST          "Build tests   for SPY"                                        ON  )
option( SPY_BUILD_DOCUMENTATION "Build Doxygen for SPY"                                        OFF )
option( SPY_ENABLE_SANITIZERS   "Build tests with AddressSanitizer + UndefinedBehaviorSanitizer" OFF )
option( SPY_ENABLE_COVERAGE     "Build tests with code coverage instrumentation"                 OFF )

##======================================================================================================================
include(${PROJECT_SOURCE_DIR}/cmake/dependencies.cmake)

if(SPY_BUILD_TEST)
  include(${PROJECT_SOURCE_DIR}/cmake/compiler.cmake)
endif()

##======================================================================================================================
## Project setup via copacabana
##======================================================================================================================
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake ${COPACABANA_SOURCE_DIR}/copacabana/cmake)
include(${COPACABANA_SOURCE_DIR}/copacabana/cmake/copacabana.cmake)
copa_project_version(MAJOR 2 MINOR 0 PATCH 0 REPOSITORY https://github.com/jfalcou/spy)

##======================================================================================================================
## Summary Display
##======================================================================================================================
if(NOT SPY_QUIET)
  if(CMAKE_BUILD_TYPE)
    message(STATUS "[${PROJECT_NAME}] - Building in ${CMAKE_BUILD_TYPE} mode")
  endif()
  message(STATUS "[${PROJECT_NAME}] - Unit tests : ${SPY_BUILD_TEST} (via SPY_BUILD_TEST)")
  message(STATUS "[${PROJECT_NAME}] - Doxygen    : ${SPY_BUILD_DOCUMENTATION} (via SPY_BUILD_DOCUMENTATION)")
  message(STATUS "[${PROJECT_NAME}] - Sanitizers : ${SPY_ENABLE_SANITIZERS} (via SPY_ENABLE_SANITIZERS)")
  message(STATUS "[${PROJECT_NAME}] - Coverage   : ${SPY_ENABLE_COVERAGE} (via SPY_ENABLE_COVERAGE)")
  set(QUIET_OPTION "")
else()
  set(QUIET_OPTION "QUIET")
endif()

##======================================================================================================================
## Pre-commit hooks setup targets
##======================================================================================================================
copa_setup_precommit_hooks(${QUIET_OPTION})

##======================================================================================================================
## Install Process setup
##======================================================================================================================
copa_setup_install( LIBRARY spy
                    FEATURES cxx_std_20
                    DOC     ${PROJECT_SOURCE_DIR}/LICENSE.md
                    INCLUDE ${PROJECT_SOURCE_DIR}/include/spy
                  )

##======================================================================================================================
## Setup doxygen
##======================================================================================================================
if(SPY_BUILD_DOCUMENTATION)
  copa_setup_doxygen(${QUIET_OPTION}
                     TARGET spy-doxygen
                     DESTINATION "${PROJECT_BINARY_DIR}/doc"
                     GODBOLT_LIBRARIES spy
                     GODBOLT_COMPILER clang1600
                     GODBOLT_OPTIONS "-O3 -std=c++20 -DNDEBUG"
                     COLOR_HUE 165
                     COLOR_SATURATION 95
                     COLOR_LIGHTNESS 30)
endif()

##======================================================================================================================
## Standalone generation
##======================================================================================================================
copa_setup_standalone ( QUIET
                        FILE spy.hpp SOURCE include ROOT spy TARGET spy-standalone
                        OUTPUT "${PROJECT_BINARY_DIR}"
                      )

##======================================================================================================================
## Tests setup
##======================================================================================================================
if(SPY_BUILD_TEST)
  if(SPY_ENABLE_SANITIZERS)
    copa_setup_sanitizers(spy_tests ENABLE_ASAN ENABLE_UBSAN)
  endif()

  enable_testing()
  add_custom_target(spy-unit)
  add_subdirectory(test)

  # After the test targets exist, so the coverage targets can depend on them
  if(SPY_ENABLE_COVERAGE)
    copa_setup_coverage(spy_tests)
  endif()
endif()
