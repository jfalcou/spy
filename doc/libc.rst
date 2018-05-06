Standard C Library
==================

**Required header** ``#include <spy/libc.hpp>``

Provides objects and meta-functions to access current C standard library informations.

Objects
-------

.. _libc-current_libc:

current_libc
************

.. code-block:: c++

   namespace spy
   {
     constexpr inline auto current_libc;
   }

A global object that gathers current C stadnard library's identification and version number.

The actual type of ``spy::current_libc`` is an implementation detail that can be inserted into
standard output streams and compared directly to instance of :ref:`libc-libc`.

.. seealso:: :ref:`version-version_of`, :ref:`libc-is_libc`

**Example:**

.. code-block:: c++

   #include <spy/libc.hpp>
   #include <iostream>

   int main()
   {
      if constexpr(spy::current_libc == spy::libc::cloudabi_)
      {
        std::cout << spy::version_of(spy::current_libc) << std::endl;
      }
   }

Types
-----

.. _libc-libc:

libc
******

.. code-block:: c++

   namespace spy
   {
     enum class libc  { undefined_  = - 1, cloudabi_, uc_, vms_, zos_, gcc_ };
   }

An enumeration of all C Standard Library supported by SPY.

+-----------------+-----------------------------------------+
| Value           | Explanation                             |
+=================+=========================================+
| ``undefined_``  | Unsupported library identification      |
+-----------------+-----------------------------------------+
| ``cloudabi_``   | cloudABI library identification         |
+-----------------+-----------------------------------------+
| ``uc_``         | UClibc library identification           |
+-----------------+-----------------------------------------+
| ``vms_``        | VMS library identification              |
+-----------------+-----------------------------------------+
| ``zos_``        | Z/OS library identification             |
+-----------------+-----------------------------------------+
| ``gcc_``        | glibc  library identification           |
+-----------------+-----------------------------------------+

.. _libc-is_libc:

is_libc
***********

.. code-block:: c++

   namespace spy
   {
     template<libc TargetLib> struct is_libc : std::bool_constant<unspecified>;
   }

Checks whether the C Standard Library identified by the ``TargetLib`` value is similar
to :ref:`libc-current_libc`.

**Template parameters**

  - ``TargetLib``: the C Standard Library identification to check. This value must be an enumerator listed by :ref:`libc-libc`

**Helper alias template**

.. code-block:: c++

   namespace spy
   {
      template<libc TargetLib>
      using is_libc_t = typename is_libc<TargetLib>::type;
   }

**Helper variable template**

.. code-block:: c++

   namespace spy
   {
      template<libc TargetLib>
      inline constexpr bool is_libc_v = is_libc<T>::value;
   }

**Example:**

.. code-block:: c++

   #include <spy/libc.hpp>
   #include <iostream>

   int main()
   {
      std::cout << std::boolalpha << spy::is_libc<spy::libc::gcc_>::value  << "\n";
      std::cout << std::boolalpha << spy::is_libc_v<spy::libc::uc_>      << "\n";
   }
