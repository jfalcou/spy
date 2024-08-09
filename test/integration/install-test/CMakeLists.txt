##======================================================================================================================
##  SPY - Compact C++20 Tuple Toolbox
##  Copyright : SPY Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##======================================================================================================================
cmake_minimum_required(VERSION 3.22)
project(spy-install-test LANGUAGES CXX)
enable_testing()

find_package(spy CONFIG REQUIRED)
add_executable(test_spy ../main.cpp)
target_link_libraries(test_spy PUBLIC spy::spy)
add_test(NAME test_spy COMMAND test_spy)
