# SPY - C++17 preprocessor-less informations gathering

## Purpose
Detection and versioning of operating systems, compilers, architecture and other element are
traditionally done using preprocessor macros. Library like
[Boost.Predef](https://www.boost.org/doc/libs/release/doc/html/predef.html) provides a sanitized
interface on top of those but still live in a world where the preprocessor is king.

SPY is a C++17 (and onward) library that gathers similar informations and provides a `constexpr`
compatible interface to access those information, thus making their exploitation safe within the
now widely accepted `if constexpr` language construct.

## Basic usage



## Support

g++ | clang | MSVC | Intel
----|-------|------|------
7   |3.9    |15.5.*|19.0

## Useful Links
