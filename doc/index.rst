SPY
===

Detection and versioning of operating systems, compilers, architecture and other element are
traditionally done using preprocessor macros. Library like `Boost.Predef`_ provides a sanitized
interface on top of those but still live in a world where the preprocessor is king.

SPY is a C++17 (and onward) library that gathers similar informations and provides a ``constexpr``
compatible interface to access those information, thus making their exploitation within ``constexpr``
context possible.

.. toctree::
   :caption: Reference Manual
   :maxdepth: 1

   howto
   version
   compiler
   os
   libc
   stdlib


.. _`Boost.Predef`: https://www.boost.org/doc/libs/release/doc/html/predef.html
