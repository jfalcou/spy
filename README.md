<img src="https://github.com/jfalcou/spy/raw/develop/logo.png" alt="SPY Library logo" data-canonical-src="https://github.com/jfalcou/spy/raw/develop/logo.png" align="left" width="20%" height="20%" />

# C++ Informations Broker

* [Purpose](#purpose)
* [How to install](#how-to-install)
  + [Using CMake](#using-cmake)
  + [Manually](#manually)
  + [Sample usage](#sample-usage)
* [User manual](#user-manual)
  + [Supported detectors](#supported-detectors)
  + [Comparing vendors](#comparing-vendors)
  + [Comparing versions](#comparing-versions)
  + [Handling SIMD extensions](#handling-simd-extensions)
  + [Caveat](#caveat)
  + [Redistribuable include](redistribuable-include)
* [Useful Links](#useful-links)
* [License](#license)

[![CircleCI](https://circleci.com/gh/jfalcou/spy.svg?style=svg&circle-token=91ebbf06adfe257ebdff3a5ed17ea512fe02771c)](https://circleci.com/gh/jfalcou/spy) [![Build status](https://ci.appveyor.com/api/projects/status/3us8906c0lvdl8ld/branch/develop?svg=true)](https://ci.appveyor.com/project/jfalcou/spy/branch/develop)

## Purpose
Detection and versioning of operating systems, compilers, architecture and other element are
traditionally done using preprocessor macros. Library like
[Boost.Predef](https://www.boost.org/doc/libs/release/doc/html/predef.html) provides a sanitized
interface on top of those but still live in a world where the preprocessor is king.

SPY is a C++17 (and onward) library that gathers similar informations and provides a `constexpr`
compatible interface to access those information, thus making their exploitation within `constexpr`
context possible.

## How to install
### Using CMake
```
git clone https://github.com/jfalcou/spy.git
mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=path/to/install/folder
make install
```

### Manually
```
git clone https://github.com/jfalcou/spy.git
cp -r include/* path/to/install/folder
```

### Sample usage
SPY is usable by simply including the `spy.hpp` file as demonstrated here:

```c++
#include <spy/spy.hpp>
#include <iostream>

int main()
{
  std::cout << spy::os                    << std::endl;
  std::cout << spy::architecture          << std::endl;
  std::cout << spy::simd_instruction_set  << std::endl;
  std::cout << spy::compiler              << std::endl;
  std::cout << spy::libc                  << std::endl;
  std::cout << spy::stdlib                << std::endl;
}
```

Just compile this example using a C++17 compliant compiler.
Don't forget to add the path to the SPY library files to your favorite compiler's options.

## User manual
### Supported detectors
SPY can detect:

- Architecture family via the `spy::architecture` object.
- OS vendor via the `spy::os` object.
- Compiler vendor and version (in the M.N.P format) via the `spy::compiler` object.
- libc vendor and version (in the M.N.P format) via the `spy::libc` object.
- stdlib vendor and version (in the M.N.P format) via the `spy::stdlib` object.

The simplest usage of those objects is to pass them to an output stream to get
a readable display of their informations.

### Comparing vendors
Knowing is half the battle, we may want to compare the current compiler or OS to a given one
so you can branch off your code based on this informations. Here is the list of each detected
vendor for each SPY objects.

| Detector            | Supported vendor                                                               |
| ------------------- | ------------------------------------------------------------------------------ |
| `spy::architecture` | `x86_`, `amd64_`, `ppc_`, `arm_`                                               |
| `spy::os`           | `android_`, `bsd_`, `cygwin_`, `ios_`, `linux_`, `macos_`, `unix_`, `windows_` |
| `spy::compiler`     | `clang_`, `gcc_`, `intel_`, `msvc_`                                            |
| `spy::libc`         | `cloudabi_`, `gnu_` `uc_`, `vms_`, `zos_`                                      |
| `spy::stdlib`       | `gnucpp_`, `libcpp_`                                                           |

Here is a sample code comparing some detectors to a specific vendor:

```c++
#include <spy/spy.hpp>
#include <iostream>

void f()
{
  if constexpr( spy::os == spy::windows_ )
  {
    std::cout << "This code is Windows only.\n";
  }

  if constexpr( spy::compiler == spy::gcc_ )
  {
    std::cout << "This code has been compiled with g++.\n";
  }

  if constexpr( spy::compiler == spy::amd64_ )
  {
    std::cout << "This code has been compiled on AMD64 architecture.\n";
  }

  if constexpr( spy::stdlib == spy::libcpp_ )
  {
    std::cout << "This code uses libcpp as its standard library implementation.\n";
  }
}
```

### Comparing versions
Checking for a vendor is sometimes not enough, we need to check which version of a given
component is used. To do this, you can compare a detector to a given version value using
any comparison operators.

Versions are build using a custom literal suffix based on the vendor name (`_vendor`)
and a series of integral values separated by `'`.

| Detector        | Supported version suffixes                                                     |
| --------------- | ------------------------------------------------------------------------------ |
| `spy::compiler` | `_clang`, `_gcc`, `_intel`, `_msvc`                                            |
| `spy::libc`     | `_cloudabi`, `_gnu` `_uc`, `_vms`, `_zos`                                      |
| `spy::stdlib`   | `_gnucpp`, `_libcpp`                                                           |

The following code demonstrates such comparisons:

```c++
#include <spy/spy.hpp>
#include <iostream>

void f()
{
  using namespace spy::literal;

  if constexpr( spy::compiler == 7'2_gcc )
  {
    std::cout << "This code has been compiled with g++ 7.2 exactly.\n";
  }

  if constexpr( spy::compiler >= 8_clang )
  {
    std::cout << "This code has been compiled with clang++ 8 or above.\n";
  }

  if constexpr( spy::stdlib < 2'0'1_libcpp )
  {
    std::cout << "This code uses libcpp below v2.0.1.\n";
  }
}
```

### Handling SIMD extensions
SIMD extensions set detection is made so that one can ask if the current SIMD extension is exactly,
below or above a given reference instruction set. Detectable instructions sets depends on SIMD
hardware vendor

| Architecture  | Supported SIMD instructions sets                                         |
| ------------- | ------------------------------------------------------------------------ |
| X86           | `sse1_`, `sse2_`, `sse3_`, `ssse3_`, `sse41_`, `sse42_`, `avx_`, `avx2_` |
| Power PC      | `vmx_`, `vsx_`                                                           |
| ARM           | `neon_`                                                                  |

Complete set of comparison operators is provided for those sets. Order of instructions sets
are built so that if an instructions set supersedes another, it is considered greater than. For
example, `avx_` is greater than `sse41_` as the former is a super-set of the later.

```c++
#include <spy/spy.hpp>
#include <iostream>

void f()
{
  if constexpr( spy::simd_instruction_set == spy::avx_ )
  {
    std::cout << "This code has been compiled with AVX instructions set.\n";
  }

  if constexpr( spy::simd_instruction_set >= spy::sse41_ )
  {
    std::cout << "This code has been compiled with at least support for SSE 4.1\n";
  }

  if constexpr( spy::simd_instruction_set <= spy::sse2_ )
  {
    std::cout << "This code has been compiled with support for SSE2 at most.\n";
  }
}
```

One can also simply asks if a given family of instructions set is available.

```c++
#include <spy/spy.hpp>
#include <iostream>

void f()
{
  if constexpr( spy::simd_instruction_set == spy::x86_simd_ )
  {
    std::cout << "This code has been compiled with some Intel SIMD instructions set.\n";
  }

  if constexpr( spy::simd_instruction_set == spy::arm_simd_ )
  {
    std::cout << "This code has been compiled with some ARM SIMD instructions set.\n";
  }

  if constexpr( spy::simd_instruction_set == spy::ppc_simd_ )
  {
    std::cout << "This code has been compiled with some Power PC SIMD instructions set.\n";
  }
}
```

Some SIMD instructions set provides supplemental instructions on top of existing system. Those
supplemental instruction set can be checked using the `spy::supports` namespace.

```c++
#include <spy/spy.hpp>
#include <iostream>

void f()
{
  if constexpr( spy::supports::fma_ )
  {
    std::cout << "This code has been compiled with FMA3 support.\n";
  }

  if constexpr( spy::supports::fma4_ )
  {
    std::cout << "This code has been compiled with FMA4 support.\n";
  }

  if constexpr( spy::supports::xop_ )
  {
    std::cout << "This code has been compiled with XOP support.\n";
  }

  if constexpr( spy::supports::aarch64_ )
  {
    std::cout << "This code has been compiled with AARCH64 support.\n";
  }
}
```

### Caveat
The detection and comparisons of versions using SPY detectors are subject to some
caveats that stem from the way `if constexpr` behaves. As both branch of the `if constexpr`
are ODR_checked, all functions and type names must be defined even if not used. This means
that this can't compile whatsoever:

```c++
#include <spy/spy.hpp>

template<typename T>
auto f(T t)
{
  if constexpr( spy::clang )
  {
    return __builtin_bitreverse32(t);
  }
  else if constexpr( spy::gcc )
  {
    return __builtin_bswap32(t);
  }
}
```

Post C++20, we advice you to use concepts with template functions:

```c++
#include <spy/spy.hpp>

template<typename T>
auto f(T t) requires( spy::clang )
{
  return __builtin_bitreverse32(t);
}

template<typename T>
auto f(T t) requires( spy::gcc )
{
  return __builtin_bswap32(t);
}
```

### Redistribuable include
If you want to use SPY in your own project but want to keep a low imprint on your own source code,
one can copy the standalone `spy.hpp` file provided at the root of the include folder. This file
contains the whole SPY library ready to be used and shipped.

## Useful Links
- [Our CppCon 2019 Ligthning talk slides](https://docs.google.com/presentation/d/1nSBhU4pr5EWznni0MYsyDkMCr3O3q2XS-KQdz2_BRRI/edit?usp=sharing)
- [Our CppCon 2019 Ligthning talk video](https://www.youtube.com/watch?v=t406o2EhG-A)
- [Boost.Predef](https://www.boost.org/doc/libs/release/doc/html/predef.html)

## License
This library is licensed under the MIT License as specified in the LICENSE.md file.
If you use SPY in your project or product, feel free to send us an email so we can
advertise it here.

```
The MIT License (MIT)

Copyright (c) 2018-2020 Joel FALCOU

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

## Credits
- <small><i><a href='http://ecotrust-canada.github.io/markdown-toc/'>Table of contents generated with markdown-toc</a></i></small>

