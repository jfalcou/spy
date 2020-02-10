## -------------------------------------------------------------------------------------------------
##  SPY - C++ Informations Broker
##  Copyright 2020 Joel FALCOU
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
## -------------------------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.2)

## -------------------------------------------------------------------------------------------------
## Setup project
## -------------------------------------------------------------------------------------------------
project(spy LANGUAGES CXX)
set(PROJECT_VERSION 0.0.2.0)
set(PROJECT_DOC_DIR   ${PROJECT_SOURCE_DIR}/doc)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake )

## -------------------------------------------------------------------------------------------------
## No in-source build
## -------------------------------------------------------------------------------------------------
if (${PROJECT_SOURCE_DIR} STREQUAL ${PROJECT_BINARY_DIR})
  message(FATAL_ERROR "[spy]: In-source build is not recommend")
endif()

## -------------------------------------------------------------------------------------------------
## Options
## -------------------------------------------------------------------------------------------------
option( SPY_BUILD_TEST  "Build tests for spy" ON )

## -------------------------------------------------------------------------------------------------
## Install target
## -------------------------------------------------------------------------------------------------
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/spy     DESTINATION spy )
install(FILES     ${PROJECT_SOURCE_DIR}/include/spy.hpp DESTINATION .   )

## -------------------------------------------------------------------------------------------------
## Standalone command
## -------------------------------------------------------------------------------------------------
add_custom_command(OUTPUT spy.hpp
  COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/script/embed.py"
          ${CMAKE_CURRENT_SOURCE_DIR}/include/spy/spy.hpp
          -I include
          -o ${CMAKE_CURRENT_SOURCE_DIR}/include/spy.hpp
          --include-match spy/*
          --guard-match .*_HPP_INLUDED

  WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
  COMMENT "Generating standalone headers"
  VERBATIM
)

add_custom_target(spy.standalone DEPENDS spy.hpp)

## -------------------------------------------------------------------------------------------------
## Test target
## -------------------------------------------------------------------------------------------------
if( SPY_BUILD_TEST )
  include(CTest)
  add_subdirectory(${PROJECT_SOURCE_DIR}/test/)
endif()
