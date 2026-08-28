##======================================================================================================================
##  SPY - C++ Informations Broker
##  Copyright : SPY Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##======================================================================================================================

##======================================================================================================================
## CPM is vendored rather than fetched: file(DOWNLOAD) reports nothing on a failure, so a network
## hiccup leaves an empty file and CMake only complains later that CPMAddPackage does not exist.
##======================================================================================================================
include(${CMAKE_CURRENT_LIST_DIR}/CPM.cmake)

##======================================================================================================================
## Retrieve dependencies
##======================================================================================================================
CPMAddPackage(NAME COPACABANA GITHUB_REPOSITORY jfalcou/copacabana GIT_TAG v2)
