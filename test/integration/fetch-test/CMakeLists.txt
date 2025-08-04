##======================================================================================================================
##  SPY - C++ Informations Broker
##  Copyright : SPY Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##======================================================================================================================
cmake_minimum_required(VERSION 3.22)
project(spy-fetch-test LANGUAGES CXX)
enable_testing()

message(STATUS "Testing FetchContent for branch ${GIT_BRANCH}")

# Enable FetchContent
include(FetchContent)

# Retrieve SPY from relative git directory
FetchContent_Declare(spy
  GIT_REPOSITORY "https://github.com/jfalcou/spy.git"
  GIT_TAG ${GIT_BRANCH}
)

# make available
FetchContent_MakeAvailable(spy)

add_executable(test_spy ../main.cpp)
target_link_libraries(test_spy PUBLIC spy::spy)
add_test(NAME test_spy COMMAND test_spy)
