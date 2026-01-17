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
copa_project_version(MAJOR 2 MINOR 0 PATCH 0)

##======================================================================================================================
## Pre-commit hooks setup targets
##======================================================================================================================
if(EXISTS "${CMAKE_SOURCE_DIR}/.git")
  find_program(PRE_COMMIT_CMD NAMES pre-commit)

  if(PRE_COMMIT_CMD)
    add_custom_target ( setup-hooks
                        COMMAND ${PRE_COMMIT_CMD} install
                        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                        COMMENT "Installing pre-commit git hooks to ${CMAKE_SOURCE_DIR}/.git/hooks"
                        VERBATIM
                      )
  endif()

  if(EXISTS "${CMAKE_SOURCE_DIR}/.git/hooks/pre-commit")
    set(PRE_COMMIT_HOOKS_INSTALLED TRUE)
  else()
    set(PRE_COMMIT_HOOKS_INSTALLED FALSE)
  endif()

  if(NOT PRE_COMMIT_CMD OR NOT PRE_COMMIT_HOOKS_INSTALLED)
    message(STATUS "")
    message(STATUS "==================================================================")
    message(STATUS "             ATTENTION: DEVELOPMENT ENVIRONMENT SETUP             ")
    message(STATUS "==================================================================")

    if(NOT PRE_COMMIT_CMD)
      message(STATUS "  1. 'pre-commit' tool is NOT found on your system.")
      message(STATUS "     Please install it: 'pip install pre-commit' or 'brew install pre-commit'")
    else()
      message(STATUS "  1. 'pre-commit' tool is found.")
    endif()

    if(NOT PRE_COMMIT_HOOKS_INSTALLED)
      message(STATUS "  2. Git hooks are NOT active for this repo.")
      message(STATUS "     Run this command to fix it:")
      message(STATUS "     --------------------------------------------------")
      message(STATUS "     cmake --build . --target setup-hooks")
      message(STATUS "     --------------------------------------------------")
    endif()

    message(STATUS "==================================================================")
    message(STATUS "")
  endif()

endif()

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
copa_setup_standalone ( QUIET
                        FILE spy.hpp SOURCE include ROOT spy TARGET spy-standalone
                        OUTPUT "${PROJECT_BINARY_DIR}"
                      )

##======================================================================================================================
## Tests setup
##======================================================================================================================
if(SPY_BUILD_TEST)
  enable_testing()
  add_custom_target(spy-unit)
  add_subdirectory(test)
endif()
