<img src="https://github.com/jfalcou/spy/raw/main/logo.png" alt="SPY Library logo" data-canonical-src="https://github.com/jfalcou/spy/raw/main/logo.png" align="left" width="20%" height="20%" />

# SPY: C++ Information Broker

[![Licence](https://img.shields.io/github/license/jfalcou/spy?style=plastic)](https://img.shields.io/github/license/jfalcou/spy?style=plastic)
[![Discord](https://img.shields.io/discord/692734675726237696?style=plastic)](https://discord.gg/a9qVaEMeXd8)
[![CI Status](https://github.com/jfalcou/spy/actions/workflows/unit.yml/badge.svg)](https://github.com/jfalcou/spy/actions/workflows/unit.yml)

<br clear="left"/>

## Purpose

Detection and versioning of operating systems, compilers, architecture, and SIMD extensions are traditionally done using messy preprocessor macros.

**SPY** is a C++20 library that gathers this information and provides a `constexpr` compatible interface. This replaces `#ifdef` spaghetti with clean, compile-time control flow.

## Quick Start

SPY turns compile-time detection into simple boolean checks:

```cpp
#include <spy/spy.hpp>
#include <iostream>

int main()
{
  // Check Compiler
  if constexpr( spy::compiler == spy::clang_ )
  {
    std::cout << "Optimizing with Clang version " << spy::compiler.version << "\n";
  }

  // Check Architecture
  if constexpr( spy::architecture == spy::amd64_ )
  {
    std::cout << "Running on x86-64\n";
  }

  // Check SIMD capabilities (hierarchical)
  if constexpr( spy::simd_instruction_set >= spy::avx2_ )
  {
    std::cout << "AVX2 or better is available\n";
  }
}
```

## Supported Features

SPY detects and versions a wide range of environments:

| Category | Supported Detection |
| --- | --- |
| **Compilers** | GCC, Clang, MSVC, Intel (Classic & OneAPI), NVCC, Emscripten |
| **Architectures** | x86, AMD64, ARM (incl. AArch64), PowerPC, RISC-V, WebAssembly |
| **SIMD** | SSE1-4.2, AVX, AVX2, AVX512, Neon, ASIMD, SVE, SVE2, VMX, VSX, RVV, SIMD128 |
| **OS** | Windows, Linux, macOS, Android, iOS, BSD, Emscripten, CUDA |

## Integration

### 1. Single Header (Easiest)

You can grab the standalone single-header file from the `standalone` branch.

```bash
wget https://github.com/jfalcou/spy/raw/standalone/spy.hpp
```

### 2. CMake FetchContent

SPY has no dependencies, making it easy to fetch compile-time:

```cmake
include(FetchContent)
FetchContent_Declare(
  spy
  GIT_REPOSITORY [https://github.com/jfalcou/spy.git](https://github.com/jfalcou/spy.git)
  GIT_TAG        v2.0.0 # Replace with latest tag
)
FetchContent_MakeAvailable(spy)

target_link_libraries(your_target PRIVATE spy::spy)
```

### 3. CPM (Package Manager)

```cmake
CPMAddPackage(
  NAME spy
  GITHUB_REPOSITORY jfalcou/spy
  GIT_TAG v2.0.0
)
target_link_libraries(your_target PRIVATE spy::spy)
```

## Documentation

The complete [API documentation can be found here](https://jfalcou.github.io/spy).

## Useful Links
- [Our CppCon 2019 Ligthning talk slides](https://docs.google.com/presentation/d/1nSBhU4pr5EWznni0MYsyDkMCr3O3q2XS-KQdz2_BRRI/edit?usp=sharing)
- [Our CppCon 2019 Ligthning talk video](https://www.youtube.com/watch?v=t406o2EhG-A)

## License

This project is licensed under the [Boost Software License 1.0](LICENSE.md).
