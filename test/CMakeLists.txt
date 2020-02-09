## -------------------------------------------------------------------------------------------------
## Copyright 2018-2020 Joel FALCOU
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
## -------------------------------------------------------------------------------------------------

if( MSVC )
  set( options /std:c++latest /W3 /EHsc )
else()
  set( options -std=c++17 -Wall)
endif()

function(generate_test root file)
  string(REPLACE ".cpp" ".unit" base ${file})
  string(REPLACE "/"    "." base ${base})
  string(REPLACE "\\"   "." base ${base})
  set(test "${root}.${base}")

  add_executable( ${test}  "${file}")
  target_compile_options  ( ${test} PUBLIC ${options} )

  set_property( TARGET ${test}
                PROPERTY RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/unit"
              )

  if (CMAKE_CROSSCOMPILING_CMD)
    add_test( NAME ${test}
              WORKING_DIRECTORY "${PROJECT_BINARY_DIR}/unit"
              COMMAND ${CMAKE_CROSSCOMPILING_CMD} $<TARGET_FILE:${test}> --no-color --pass
            )
  else()
    add_test( NAME ${test}
              WORKING_DIRECTORY "${PROJECT_BINARY_DIR}/unit"
              COMMAND $<TARGET_FILE:${test}> --no-color --pass
            )
  endif()

  set_target_properties ( ${test} PROPERTIES
                          EXCLUDE_FROM_DEFAULT_BUILD TRUE
                          EXCLUDE_FROM_ALL TRUE
                          ${MAKE_UNIT_TARGET_PROPERTIES}
                        )

  target_include_directories( ${test}
                              PRIVATE
                                ${PROJECT_SOURCE_DIR}/test
                                ${PROJECT_SOURCE_DIR}/include
                            )

  add_dependencies(unit ${test})
endfunction()

add_custom_target(unit)
add_custom_target(spy.unit)
add_dependencies(unit spy.unit)

generate_test("spy" "arch.cpp")
generate_test("spy" "compiler.cpp")
generate_test("spy" "data_model.cpp")
generate_test("spy" "libc.cpp")
generate_test("spy" "os.cpp")
generate_test("spy" "stdlib.cpp")

