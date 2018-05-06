Operating System
================

**Required header** ``#include <spy/os.hpp>``

Provides objects and meta-functions to access current Operating System informations.

Objects
-------

.. _os-current_os:

current_os
**********

.. code-block:: c++

   namespace spy
   {
     constexpr inline auto current_os;
   }

A global object that gathers current OS' identification. The actual type
of ``spy::current_os`` is implementation-defined.

**See also:**

version_of, :ref:`os-is_os`

**Example:**

.. code-block:: c++

   #include <spy/os.hpp>
   #include <iostream>

   int main()
   {
      if constexpr(spy::current_os == spy::systems::windows_)
      {
        std::cout << "Running on Windows" << std::endl;
      }
   }

Types
-----

.. _os-systems:

systems
*********

.. code-block:: c++

   namespace spy
   {
      enum class systems  { undefined_  = - 1
                          , android_, bsd_, cygwin_, ios_, linux_, macos_, unix_, windows_
                          };
   }

An enumeration of all OS supported by SPY.

+-----------------+-------------------------------+
| Value           | Explanation                   |
+=================+===============================+
| ``undefined_``  | Unsupported operating system  |
+-----------------+-------------------------------+
| ``android_``    | Android identification        |
+-----------------+-------------------------------+
| ``bsd_``        | BSD identification            |
+-----------------+-------------------------------+
| ``cygwin_``     | Cygwin identification         |
+-----------------+-------------------------------+
| ``ios_``        | iOS identification            |
+-----------------+-------------------------------+
| ``linux_``      | Linux identification          |
+-----------------+-------------------------------+
| ``macos_``      | MacOS identification          |
+-----------------+-------------------------------+
| ``unix_``       | Unix identification           |
+-----------------+-------------------------------+
| ``windows_``    | Windows identification        |
+-----------------+-------------------------------+

.. _os-is_os:

is_os
***********

.. code-block:: c++

   namespace spy
   {
     template<systems TargetOS> struct is_os : std::bool_constant<unspecified>;
   }

Checks whether the os identified by the ``TargetOS`` value is similar
to :ref:`os-current_os`.

**Template parameters**

``TargetOS`` - the os identification to check. This value must be an enumerator listed by
:ref:`os-systems`

**Helper alias template**

.. code-block:: c++

   namespace spy
   {
      template<systems TargetOS>
      using is_os_t = typename is_os<TargetOS>::type;
   }

**Helper variable template**

.. code-block:: c++

   namespace spy
   {
      template<systems TargetOS>
      inline constexpr bool is_os_v = is_os<T>::value;
   }

**Example:**

.. code-block:: c++

   #include <spy/os.hpp>
   #include <iostream>

   int main()
   {
      std::cout << std::boolalpha << spy::is_os<spy::systems::ios_>::value  << "\n";
      std::cout << std::boolalpha << spy::is_os_v<spy::systems::windows_>      << "\n";
   }
