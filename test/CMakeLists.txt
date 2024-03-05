##==================================================================================================
##  SPY - C++ Informations Broker
##  Copyright : SPY Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================

##==================================================================================================
# Unit test Configuration
##==================================================================================================
add_library(spy_test INTERFACE)
target_compile_features ( spy_test INTERFACE  cxx_std_17 )

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  if(CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC")
    target_compile_options( spy_test INTERFACE /W3 /EHsc )
  else()
    target_compile_options( spy_test INTERFACE -Werror -Wall -Wextra -Wunused-variable)
  endif()
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_compile_options( spy_test INTERFACE /W3 /EHsc )
else()
  target_compile_options( spy_test INTERFACE -Werror -Wall -Wextra -Wunused-variable)
endif()

##==================================================================================================
# Generate a test
##==================================================================================================
function(generate_test root file)
  string(REPLACE ".cpp" ".unit" base ${file})
  string(REPLACE "/"    "." base ${base})
  string(REPLACE "\\"   "." base ${base})
  set(test "${root}.${base}")

  add_executable( ${test}  "${file}")
  target_link_libraries(${test} PUBLIC spy_test)

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

  if(SPY_FORCE_STANDALONE)
    add_dependencies(${test} standalone)
  endif()

endfunction()

add_custom_target(unit)
add_custom_target(spy.unit)
add_dependencies(unit spy.unit)

##==================================================================================================
# All tests
##==================================================================================================
generate_test("spy" "accelerator.cpp")
generate_test("spy" "arch.cpp")
generate_test("spy" "compiler.cpp")
generate_test("spy" "data_model.cpp")
generate_test("spy" "libc.cpp")
generate_test("spy" "os.cpp")
generate_test("spy" "simd.cpp")
generate_test("spy" "stdlib.cpp")
