Compilers
=========

**Required header** ``#include <spy/compiler.hpp>``

Provides objects and meta-functions to access current compiler informations.

Objects
-------

.. _compiler-current_compiler:

current_compiler
****************

.. code-block:: c++

   namespace spy
   {
     constexpr inline auto current_compiler;
   }

A global object that gathers current compiler's identification and version number.

The actual type of ``spy::current_compiler`` is an implementation detail that can be inserted into
standard output streams and compared directly to instance of :ref:`compiler-compilers`.

.. seealso:: :ref:`version-version_of`, :ref:`compiler-is_compiler`

**Example:**

.. code-block:: c++

   #include <spy/compiler.hpp>
   #include <iostream>

   int main()
   {
      if constexpr(spy::current_compiler == spy::compilers::gcc_)
      {
        std::cout << spy::version_of(spy::current_compiler) << std::endl;
      }
   }

Types
-----

.. _compiler-compilers:

compilers
*********

.. code-block:: c++

   namespace spy
   {
     enum class compilers { undefined_  = - 1, msvc_, intel_, clang_, gcc_ };
   }

An enumeration of all compilers supported by SPY.

+-----------------+-----------------------------------------+
| Value           | Explanation                             |
+=================+=========================================+
| ``undefined_``  | Unsupported compiler identification     |
+-----------------+-----------------------------------------+
| ``msvc_``       | Microsoft Visual Studio identification  |
+-----------------+-----------------------------------------+
| ``intel_``      | Intel compiler identification           |
+-----------------+-----------------------------------------+
| ``clang_``      | Clang compiler identification           |
+-----------------+-----------------------------------------+
| ``gcc_``        | g++ compiler identification             |
+-----------------+-----------------------------------------+

.. _compiler-is_compiler:

is_compiler
***********

.. code-block:: c++

   namespace spy
   {
     template<compilers TargetCompiler> struct is_compiler : std::bool_constant<unspecified>;
   }

Checks whether the compiler identified by the ``TargetCompiler`` value is similar
to :ref:`compiler-current_compiler`.

**Template parameters**

  - ``TargetCompiler``: the compiler identification to check. This value must be an enumerator listed by :ref:`compiler-compilers`

**Helper alias template**

.. code-block:: c++

   namespace spy
   {
      template<compilers TargetCompiler>
      using is_compiler_t = typename is_compiler<TargetCompiler>::type;
   }

**Helper variable template**

.. code-block:: c++

   namespace spy
   {
      template<compilers TargetCompiler>
      inline constexpr bool is_compiler_v = is_compiler<T>::value;
   }

**Example:**

.. code-block:: c++

   #include <spy/compiler.hpp>
   #include <iostream>

   int main()
   {
      std::cout << std::boolalpha << spy::is_compiler<spy::compilers::gcc_>::value  << "\n";
      std::cout << std::boolalpha << spy::is_compiler_v<spy::compilers::msvc_>      << "\n";
   }
