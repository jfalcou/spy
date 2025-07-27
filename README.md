<img src="https://github.com/jfalcou/spy/raw/main/logo.png" alt="SPY Library logo" data-canonical-src="https://github.com/jfalcou/spy/raw/main/logo.png" align="left" width="20%" height="20%" />

# C++ Informations Broker

[![Licence](https://img.shields.io/github/license/jfalcou/spy?style=plastic)](https://img.shields.io/github/license/jfalcou/spy?style=plastic)
[![Discord](https://img.shields.io/discord/692734675726237696?style=plastic)](https://discord.gg/a9qVaEMeXd8)


# Purpose
Detection and versioning of operating systems, compilers, architecture and other elements are
traditionally done using preprocessor macros. Library like
[Boost.Predef](https://www.boost.org/doc/libs/release/doc/html/predef.html) provides a sanitized
interface on top of those, but still lives in a world where the preprocessor is king.

SPY is a C++20 (and onward) library that gathers similar information and provides a `constexpr`
compatible interface to access that information, thus making their exploitation within `constexpr`
context possible.

The complete [documentation can be found here](https://jfalcou.github.io/spy).

# Useful Links
- [Our CppCon 2019 Ligthning talk slides](https://docs.google.com/presentation/d/1nSBhU4pr5EWznni0MYsyDkMCr3O3q2XS-KQdz2_BRRI/edit?usp=sharing)
- [Our CppCon 2019 Ligthning talk video](https://www.youtube.com/watch?v=t406o2EhG-A)
- [Boost.Predef](https://www.boost.org/doc/libs/release/doc/html/predef.html)
