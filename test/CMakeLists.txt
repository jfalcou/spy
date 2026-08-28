##==================================================================================================
##  SPY - C++ Informations Broker
##  Copyright : SPY Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================
copa_setup_test_targets()
set(root "${CMAKE_SOURCE_DIR}/test")
copa_glob_unit(QUIET PATTERN "unit/*.cpp"     INTERFACE spy_tests)
copa_glob_unit(QUIET PATTERN "samples/*.cpp"  INTERFACE spy_tests)

##======================================================================================================================
## accelerator.cpp and accelerator.cu are the same test compiled twice: as plain C++ spy must
## report no CUDA, as CUDA it must report some. Only the second needs a CUDA compiler to exist.
##======================================================================================================================
if(CMAKE_CUDA_COMPILER)
  copa_make_single_unit( INTERFACE spy_tests
                         FILES     unit/accelerator.cu
                         ROOT      ${root}
                         NAME      unit.accelerator.device.cu
                       )
endif()
