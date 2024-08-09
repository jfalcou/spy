##======================================================================================================================
##  SPY - Compact C++20 Tuple Toolbox
##  Copyright : SPY Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##======================================================================================================================
cmake_minimum_required(VERSION 3.18)
project(spy-cpm-test LANGUAGES CXX)
enable_testing()

message(STATUS "Testing CPM for branch ${GIT_BRANCH}")

# Setup CPM
include(cpm.cmake)

# Add dependencies
CPMAddPackage ( NAME spy
                GIT_REPOSITORY "https://github.com/jfalcou/spy.git"
                GIT_TAG "${GIT_BRANCH}"
                OPTIONS "SPY_BUILD_TEST OFF"
              )

# Use spy
add_executable(test_spy ../main.cpp)
target_link_libraries(test_spy PUBLIC spy::spy)
add_test(NAME test_spy COMMAND test_spy)
