##======================================================================================================================
##  SPY - C++ Informations Broker
##  Copyright : SPY Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##======================================================================================================================
cmake_minimum_required(VERSION 3.22)
project(spy LANGUAGES CXX)

##======================================================================================================================
option( SPY_BUILD_TEST          "Build tests   for SPY"   ON  )
option( SPY_BUILD_DOCUMENTATION "Build Doxygen for SPY"   OFF )

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
copa_project_version(MAJOR 1 MINOR 1 PATCH 0)


##======================================================================================================================
## Summary Display
##======================================================================================================================
if(NOT SPY_QUIET)
  if(CMAKE_BUILD_TYPE)
    message(STATUS "[${PROJECT_NAME}] - Building in ${CMAKE_BUILD_TYPE} mode")
  endif()
  message(STATUS "[${PROJECT_NAME}] - Unit tests : ${SPY_BUILD_TEST} (via SPY_BUILD_TEST)")
  message(STATUS "[${PROJECT_NAME}] - Doxygen    : ${SPY_BUILD_DOCUMENTATION} (via SPY_BUILD_DOCUMENTATION)")
  set(QUIET_OPTION "")
else()
  set(QUIET_OPTION "QUIET")
endif()

##======================================================================================================================
## Install Process setup
##======================================================================================================================
copa_setup_install( LIBRARY spy
                    FEATURES cxx_std_17
                    DOC     ${PROJECT_SOURCE_DIR}/LICENSE.md
                    INCLUDE ${PROJECT_SOURCE_DIR}/include/spy
                  )

##======================================================================================================================
## Setup doxygen
##======================================================================================================================
if(SPY_BUILD_DOCUMENTATION)
  copa_setup_doxygen(${QUIET_OPTION} TARGET spy-doxygen DESTINATION "${PROJECT_BINARY_DIR}/doc")
endif()

##======================================================================================================================
## Standalone generation
##======================================================================================================================
copa_setup_standalone ( #QUIET
                        FILE spy.hpp SOURCE include  DESTINATION standalone
                        ROOT spy     TARGET spy-standalone
                      )

##======================================================================================================================
## Tests setup
##======================================================================================================================
if(SPY_BUILD_TEST)
  enable_testing()
  add_custom_target(spy-unit)
  add_subdirectory(test)
endif()
