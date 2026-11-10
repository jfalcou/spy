# Copacabana's own shape, for both cmake-format and cmake-lint.
#
# Written in python rather than yaml: cmakelang does not depend on pyyaml, so a yaml config cannot be read from the
# isolated environment pre-commit builds for it.

with section("parse"):
  # CPMAddPackage is not a CMake command, so the formatter has no signature for it and treats every token as a
  # standalone positional argument - one per line, keyword and value split apart. Declaring the signature is what
  # lets it keep a keyword next to the value it introduces.
  additional_commands = {
      "cpmaddpackage": {
          "pargs": {"nargs": "*"},
          "kwargs": {
              "NAME": 1,
              "VERSION": 1,
              "GIT_TAG": 1,
              "GIT_REPOSITORY": 1,
              "GITHUB_REPOSITORY": 1,
              "GITLAB_REPOSITORY": 1,
              "BITBUCKET_REPOSITORY": 1,
              "SOURCE_DIR": 1,
              "SOURCE_SUBDIR": 1,
              "DOWNLOAD_ONLY": 1,
              "DOWNLOAD_COMMAND": 1,
              "FIND_PACKAGE_ARGUMENTS": 1,
              "NO_CACHE": 1,
              "SYSTEM": 1,
              "GIT_SHALLOW": 1,
              "EXCLUDE_FROM_ALL": 1,
              "CUSTOM_CACHE_KEY": 1,
              "URL": 1,
              "URL_HASH": 1,
              "OPTIONS": "*",
              "PATCHES": "*",
          },
      }
  }
  additional_commands["cpmfindpackage"] = additional_commands["cpmaddpackage"]

  # Copacabana's own functions, so the formatter keeps a keyword next to the value it introduces rather than
  # putting every token on a line of its own. Read from their cmake_parse_arguments calls.

  additional_commands["cpmdeclarepackage"] = additional_commands["cpmaddpackage"]

  # Copacabana's own functions, so the formatter keeps a keyword next to the value it introduces rather than
  # putting every token on a line of its own. Read from their cmake_parse_arguments calls.
  additional_commands["copa_add_option"] = {"pargs": {"nargs": "*"}, "kwargs": {"LABEL": 1}}
  additional_commands["copa_glob_failure_unit"] = {"pargs": {"nargs": "*", "flags": ["QUIET"]}, "kwargs": {"RELATIVE": 1, "PATTERN": 1, "INTERFACE": 1}}
  additional_commands["copa_glob_unit"] = {"pargs": {"nargs": "*", "flags": ["QUIET", "IMPLICIT"]}, "kwargs": {"RELATIVE": 1, "PATTERN": 1, "INTERFACE": 1, "PCH": 1, "EXTENSION": 1, "DESTINATION": 1, "TARGET": 1, "DEPENDENCIES": "*", "EXTERNALS": "*", "PROPERTIES": "*"}}
  additional_commands["copa_make_failure_unit"] = {"pargs": {"nargs": "*", "flags": ["QUIET"]}, "kwargs": {"FILE": 1, "INTERFACE": 1, "ROOT": 1, "NAME": 1}}
  additional_commands["copa_make_single_unit"] = {"pargs": {"nargs": "*"}, "kwargs": {"NAME": 1, "INTERFACE": 1, "EXTENSION": 1, "ROOT": 1, "DESTINATION": 1, "PCH": 1, "TARGET": 1, "DEPENDENCIES": "*", "FILES": "*", "EXTERNALS": "*", "PROPERTIES": "*"}}
  additional_commands["copa_make_unit"] = {"pargs": {"nargs": "*", "flags": ["QUIET"]}, "kwargs": {"INTERFACE": 1, "EXTENSION": 1, "ROOT": 1, "DESTINATION": 1, "PCH": 1, "IMPLICIT": 1, "TARGET": 1, "DEPENDENCIES": "*", "FILES": "*", "EXTERNALS": "*", "PROPERTIES": "*"}}
  additional_commands["copa_project_version"] = {"pargs": {"nargs": "*", "flags": ["QUIET"]}, "kwargs": {"MAJOR": 1, "MINOR": 1, "PATCH": 1, "REPOSITORY": 1}}
  additional_commands["copa_sanitizer_flags"] = {"pargs": {"nargs": "*", "flags": ["ENABLE_ASAN", "ENABLE_UBSAN", "ENABLE_TSAN", "ENABLE_MSAN"]}}
  additional_commands["copa_setup_compile_cost"] = {"pargs": {"nargs": "*"}, "kwargs": {"PREFIX": 1, "DEPENDS": 1, "EXCLUDE": 1, "BASELINE": 1}}
  additional_commands["copa_setup_coverage"] = {"pargs": {"nargs": "*"}, "kwargs": {"PREFIX": 1, "FILTER": 1, "DEPENDS": 1}}
  additional_commands["copa_setup_cpack"] = {"pargs": {"nargs": "*", "flags": ["QUIET"]}, "kwargs": {"VENDOR": 1, "DESCRIPTION": 1, "LICENSE_FILE": 1, "MAINTAINER": 1, "DEB_DEPENDENCIES": "*", "RPM_DEPENDENCIES": "*"}}
  additional_commands["copa_setup_doxygen"] = {"pargs": {"nargs": "*", "flags": ["QUIET"]}, "kwargs": {"SOURCE": 1, "DESTINATION": 1, "TARGET": 1, "GODBOLT_COMPILER": 1, "GODBOLT_OPTIONS": 1, "COLOR_HUE": 1, "COLOR_SATURATION": 1, "COLOR_LIGHTNESS": 1, "COLOR_GAMMA": 1, "GODBOLT_LIBRARIES": "*", "TAGFILES": "*"}}
  additional_commands["copa_setup_install"] = {"pargs": {"nargs": "*"}, "kwargs": {"LIBRARY": 1, "NAMESPACE": 1, "COMPATIBILITY": 1, "CONFIG": 1, "DESTINATION": 1, "ARCH_INDEPENDENT": 1, "LIB": "*", "INCLUDE": "*", "DOC": "*", "FEATURES": "*"}}
  additional_commands["copa_setup_pch"] = {"pargs": {"nargs": "*", "flags": ["AUTONOMOUS"]}, "kwargs": {"TARGET": 1, "INTERFACES": "*", "HEADERS": "*", "PROPERTIES": "*"}}
  additional_commands["copa_setup_precommit_hooks"] = {"pargs": {"nargs": "*", "flags": ["QUIET"]}}
  additional_commands["copa_setup_sanitizers"] = {"pargs": {"nargs": "*", "flags": ["ENABLE_ASAN", "ENABLE_UBSAN", "ENABLE_TSAN", "ENABLE_MSAN"]}}
  additional_commands["copa_setup_standalone"] = {"pargs": {"nargs": "*", "flags": ["QUIET"]}, "kwargs": {"SOURCE": 1, "DESTINATION": 1, "FILE": 1, "ROOT": 1, "TARGET": 1, "OUTPUT": 1}}
  additional_commands["copa_setup_time_trace"] = {"pargs": {"nargs": "*"}, "kwargs": {"PREFIX": 1, "DEPENDS": 1, "SCAN": 1}}
  additional_commands["copa_show_options"] = {"pargs": {"nargs": "*", "flags": ["QUIET"]}}

  # Copacabana's own functions, so the formatter keeps a keyword next to the value it introduces rather than
  # putting every token on a line of its own. Read from their cmake_parse_arguments calls.

with section("format"):
  # The formatter lowercases every command it emits, which would rename the calls to COPA_SETUP_COVERAGE and friends
  # while leaving the function() declaring them untouched - an API documented in one case and invoked in another.
  # CPMAddPackage has the same problem, in CPM's spelling rather than ours.
  command_case = "unchanged"

  # Declaring the copa_* and CPM signatures makes cmake-format prefer one keyword per line, which turns
  # copa_project_version(MAJOR 0 MINOR 1 PATCH 0) into four. Three groups fit a line here at 120 columns.
  max_subgroups_hwrap = 3

  line_width = 120
  tab_size = 2

with section("markup"):
  # The formatter reflows a comment block into a paragraph, which would run the three lines of the licence header
  # into one and take SPDX-License-Identifier out of the first column, where the scanners look for it.
  enable_markup = False
  canonicalize_hashrulers = False

with section("lint"):
  # Commands are case-insensitive in CMake, so their case is a readability choice and nothing else. This project makes
  # it lowercase, everywhere and on both sides: what a function() declares, what a macro() declares, and what the call
  # writes. The macro pattern has to be stated because cmakelang defaults it to uppercase, splitting the two apart.
  function_pattern = "[a-z_][0-9a-z_]*"
  macro_pattern = "[a-z_][0-9a-z_]*"

  # A local here is uppercase like the directory-scope names around it. Variables, unlike commands, are case-sensitive,
  # so this one is about matching the surrounding code and not about style alone.
  local_var_pattern = "[A-Za-z_][0-9A-Za-z_]*"
  argument_var_pattern = "[A-Za-z_][0-9A-Za-z_]*"
