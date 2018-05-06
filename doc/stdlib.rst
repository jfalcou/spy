Standard C++ Library
====================

**Required header** ``#include <spy/stdlib.hpp>``

Provides objects and meta-functions to access current C++ standard library informations.

Objects
-------

.. _stdlib-current_stdlib:

current_stdlib
**************

.. code-block:: c++

   namespace spy
   {
     constexpr inline auto current_stdlib;
   }

A global object that gathers current C++ standard library's identification and version number.

The actual type of ``spy::current_stdlib`` is an implementation detail that can be inserted into
standard output streams and compared directly to instance of :ref:`stdlib-stdlib`.

.. seealso:: :ref:`stdlib-is_stdlib`

**Example:**

.. code-block:: c++

   #include <spy/stdlib.hpp>
   #include <iostream>

   int main()
   {
      if constexpr(spy::current_stdlib == spy::stdlib::libcpp_)
      {
        std::cout << spy::version_of(spy::current_stdlib) << std::endl;
      }
   }

Types
-----

.. _stdlib-stdlib:

stdlib
******

.. code-block:: c++

   namespace spy
   {
     enum class stdlib  { undefined_  = - 1, libcpp_, gcc_ };
   }

An enumeration of all C++ Standard Library supported by SPY.

+-----------------+-----------------------------------------+
| Value           | Explanation                             |
+=================+=========================================+
| ``undefined_``  | Unsupported library identification      |
+-----------------+-----------------------------------------+
| ``libcpp_``     | libc++ library identification           |
+-----------------+-----------------------------------------+
| ``gcc_``        | glibcxx library identification          |
+-----------------+-----------------------------------------+

.. _stdlib-is_stdlib:

is_stdlib
***********

.. code-block:: c++

   namespace spy
   {
     template<stdlib TargetLib> struct is_stdlib : std::bool_constant<unspecified>;
   }

Checks whether the C++ Standard Library identified by the ``TargetLib`` value is similar
to :ref:`stdlib-current_stdlib`.

**Template parameters**

  - ``TargetLib``: the C++ Standard Library identification to check. This value must be an enumerator listed by :ref:`stdlib-stdlib`

**Helper alias template**

.. code-block:: c++

   namespace spy
   {
      template<stdlib TargetLib>
      using is_stdlib_t = typename is_stdlib<TargetLib>::type;
   }

**Helper variable template**

.. code-block:: c++

   namespace spy
   {
      template<stdlib TargetLib>
      inline constexpr bool is_stdlib_v = is_stdlib<T>::value;
   }

**Example:**

.. code-block:: c++

   #include <spy/stdlib.hpp>
   #include <iostream>

   int main()
   {
      std::cout << std::boolalpha << spy::is_stdlib<spy::stdlib::gcc_>::value  << "\n";
      std::cout << std::boolalpha << spy::is_stdlib_v<spy::stdlib::libcpp_>      << "\n";
   }
