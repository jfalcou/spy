##==================================================================================================
##  SPY - C++ Informations Broker
##  Copyright : SPY Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================
copa_setup_test_targets()
set(root "${CMAKE_SOURCE_DIR}/test")
copa_glob_unit(QUIET PATTERN "unit/*.cpp"     INTERFACE spy_tests)
copa_glob_unit(QUIET PATTERN "samples/*.cpp"  INTERFACE spy_tests)
