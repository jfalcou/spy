SPY
===

Detection and versioning of operating systems, compilers, architecture and other element are
traditionally done using preprocessor macros. Library like `Boost.Predef`_ provides a sanitized
interface on top of those but still live in a world where the preprocessor is king.

SPY is a C++17 library that gathers such informations and provides a ``constexpr``
compatible interface to access those information, thus making their exploitation safe within the
now widely accepted ``if constexpr`` language construct.

.. toctree::
   :caption: Introduction to SPY
   :maxdepth: 2

   howto
   tutorial

.. toctree::
   :caption: Reference Manual
   :maxdepth: 2

   compiler
   libc
   stdlib
   os


.. _`Boost.Predef`: https://www.boost.org/doc/libs/release/doc/html/predef.html
