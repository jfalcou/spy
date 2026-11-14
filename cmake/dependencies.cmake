##======================================================================================================================
##  SPY - C++ Informations Broker
##  Copyright : SPY Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##======================================================================================================================

##======================================================================================================================
## Take the dependencies from the environment, without CPM
##======================================================================================================================
option(SPY_EXTERNAL_DEPENDENCIES "Take dependencies from the environment instead of fetching them" OFF)

if(SPY_EXTERNAL_DEPENDENCIES)
  if(NOT COPACABANA_SOURCE_DIR)
    message(FATAL_ERROR "[SPY] - SPY_EXTERNAL_DEPENDENCIES needs COPACABANA_SOURCE_DIR")
  endif()
  return()
endif()

##======================================================================================================================
## CPM is vendored: the download bootstrap reports nothing on a failure and leaves an empty file.
##======================================================================================================================
include(${CMAKE_CURRENT_LIST_DIR}/CPM.cmake)

##======================================================================================================================
## Retrieve dependencies
##======================================================================================================================
CPMAddPackage(NAME COPACABANA GITHUB_REPOSITORY jfalcou/copacabana GIT_TAG main)
