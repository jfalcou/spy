<img src="https://github.com/jfalcou/spy/raw/develop/logo.png" alt="SPY Library logo" data-canonical-src="https://github.com/jfalcou/spy/raw/develop/logo.png" align="left" width="20%" height="20%" />

# C++ Informations Broker

[![CircleCI](https://circleci.com/gh/jfalcou/spy.svg?style=svg&circle-token=91ebbf06adfe257ebdff3a5ed17ea512fe02771c)](https://circleci.com/gh/jfalcou/spy) [![Build status](https://ci.appveyor.com/api/projects/status/3us8906c0lvdl8ld/branch/develop?svg=true)](https://ci.appveyor.com/project/jfalcou/spy/branch/develop)
[![Licence](https://img.shields.io/github/license/jfalcou/ofw?style=plastic)](https://img.shields.io/github/license/jfalcou/ofw?style=plastic) 
[![Discord](https://img.shields.io/discord/692734675726237696?style=plastic)](https://discord.gg/a9qVaEMeXd8) 


# Purpose
Detection and versioning of operating systems, compilers, architecture and other element are
traditionally done using preprocessor macros. Library like
[Boost.Predef](https://www.boost.org/doc/libs/release/doc/html/predef.html) provides a sanitized
interface on top of those but still live in a world where the preprocessor is king.

SPY is a C++17 (and onward) library that gathers similar informations and provides a `constexpr`
compatible interface to access those information, thus making their exploitation within `constexpr`
context possible.

The complete [documentation can be found here](https://jfalcou.github.io/spy).

# Useful Links
- [Our CppCon 2019 Ligthning talk slides](https://docs.google.com/presentation/d/1nSBhU4pr5EWznni0MYsyDkMCr3O3q2XS-KQdz2_BRRI/edit?usp=sharing)
- [Our CppCon 2019 Ligthning talk video](https://www.youtube.com/watch?v=t406o2EhG-A)
- [Boost.Predef](https://www.boost.org/doc/libs/release/doc/html/predef.html)

# License
This library is licensed under the MIT License as specified in the LICENSE.md file.
If you use SPY in your project or product, feel free to send us an email so we can
advertise it here.

```
The MIT License (MIT)

Copyright (c) SPY Contributors & Maintainers

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
