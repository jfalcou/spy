Change Log {#changelog}
==========

# Version 2.0.0 - Denise Bloch

## Changelog

- Features:
  - **[BREAKING CHANGE]** Move to C++20 to improve compile times.
  - Detect RISC-V and RISC-V SIMD instructions sets.
  - Update SIMD detection by upstreaming EVE recent changes.

- Bugs:
  - Fix #55 - Properly detect version for Clang CUDA.
  - Use <=> instead of macros for comparisons.
  - Fix streaming issues of SPY objects.

- Infrastructure:
  - Update CI to g++ 13 and clang 18.
  - Make doxygen generate a spy.tag in the doc files.
  - Added a proper clang format settings.

## Our SPY:

[Denise Bloch](https://en.wikipedia.org/wiki/Denise_Bloch)

# Version 1.1.0 - Julienne Aisner

## Changelog

- Features:
  - Split PPC VMX/VSX detection to take PPC ISA into account.
  - Separate ARM and ARM SVE tags and add SVE2 detectors.
  - Detect and supports sanitizers detection/disabling.
  - Implements SVE detection.
  - Add detections for ICPX and SYCL.
  - Add detections for NVIDIA CUDA usage.

- Bugs:
  - Fix int width for the LLP64 data model by @jmgorius
  - Add missing whitespace in stdlib output by @ahoarau

- Infrastructure:
  - Reorganize standalone header location & process.
  - Add Emscripten CI targets.
  - Now tests and supports Clang-CL.

## New Contributors
* @ahoarau made their first contribution in https://github.com/jfalcou/spy/pull/40
* @jmgorius made their first contribution in https://github.com/jfalcou/spy/pull/44

## Our SPY:

[Julienne Aisner](https://en.wikipedia.org/wiki/Julienne_Aisner)

# Version 1.0.0 - Alix d'Unienville

## Changelog
- **BREAKING CHANGES**
  - ARM Neon and ASIMD discrimination are in line with SSE-like extensions. `spy::asimd_` is now a descendant of `spy::neon_`. This leads to the removal of `spy::supports_aarch64`

- Bugs:
  - Fix #12 : Remove `<iostream>` from public headers

- Infrastructure:
   - Fix Circle CI uses a new Docker with more cross-compiler and setup

## Our SPY:

[Alix d'Unienville](https://en.wikipedia.org/wiki/Alix_d%27Unienville)

# Version 0.0.4 - Eileen Nearne

## Changelog
- Infrastructure:
  - Fix Circle CI use of compilers and proper dockers
  - More strict warnings handling in test
- Bugs:
  - No more ALL_CAPS template parameters (Issue #10)
  - Fix duplicate macros in AVX512 detection

## Our SPY:

[Eileen Nearne](https://en.wikipedia.org/wiki/Eileen_Nearne)

# Version 0.0.3 - Virginia Hall

## Changelog
- Infrastructure:
  - Fixed #5 - SPY now provide a Conan package recipe
  - Documentation now uses [Markdeep](https://casual-effects.com/markdeep/)
- Features
  - AVX512 detection and sub-ISA detection
  - SIMD ISA objects now provide member to access the actual ISA and version number
  - Added some macros to help to detect SPY successful detection. This is alas still required for some use cases.
  - Added detectors for POSIX

## Our SPY:

[Virginia Hall](https://en.wikipedia.org/wiki/Virginia_Hall)

# Version 0.0.2 - Blanche Charlet

## Changelog
 - Support for Continuous Integration
 - Fixed #2 - detecting compile-time support for SIMD instructions sets
 - Added detectors for data model (LP64, LP32, and all that jazz)
 - Added detectors for architecture brand

## Our SPY:

[Blanche Charlet](https://en.wikipedia.org/wiki/Blanche_Charlet)

# Version 0.0.1 - Peggy Knight

## First public release.

Support for:
 - OS vendor
 - Compilers version & vendor
 - libc version & vendor
 - stdlib version & vendor

## Our SPY:
[Peggy Knight](https://en.wikipedia.org/wiki/Peggy_Knight)
