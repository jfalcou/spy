##==================================================================================================
##  SPY - C++ Informations Broker
##  Copyright 2020 Joel FALCOU
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================
#!/usr/bin/env bash

##==================================================================================================
## Prepare variant's folder
##==================================================================================================
mkdir -p build/$VARIANT
cd build/$VARIANT

##==================================================================================================
## CMAKE
##==================================================================================================
if [[ -v RUN_COMMAND ]]
then
  echo "Running tests with $RUN_COMMAND ..."
  cmake ../.. -G Ninja $CMAKE_OPTIONS -DCMAKE_CXX_COMPILER="$COMPILER" -DCMAKE_CXX_FLAGS="$OPTIONS" -DCMAKE_CROSSCOMPILING_CMD="$RUN_COMMAND"
else
  cmake ../.. -G Ninja $CMAKE_OPTIONS -DCMAKE_CXX_COMPILER="$COMPILER" -DCMAKE_CXX_FLAGS="$OPTIONS"
fi

##==================================================================================================
## PATH Infos
##==================================================================================================
if [[ -v EXTRA_PATH ]]
then
  echo "Updating path for $EXTRA_PATH/$EXTRA_NAME ..."
  LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$EXTRA_PATH
  export LD_LIBRARY_PATH
  ln -sf $EXTRA_PATH/$EXTRA_NAME /$EXTRA_LIB/$EXTRA_NAME
fi

##==================================================================================================
## Run every test up to SIMD
##==================================================================================================
ninja unit -j 8
ctest  -j 8
