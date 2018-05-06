Version Encoding
================

**Required header** ``#include <spy/version.hpp>``

Provides objects and functions to represent and manipulate version numbers in ``constexpr``
contexts.

Objects
-------

.. _version-unspecified_version:

unspecified_version
*******************

.. code-block:: c++

   namespace spy
   {
     constexpr inline unspecified_version_t unspecified_version;
   }

A global object that represents an unspecified version number of type :ref:`version-unspecified_version_t`.

Types
-----

.. _version-version_id:

version_id
**********

.. code-block:: c++

   namespace spy
   {
      template<int M, int N, int P> struct version_id
      {
        static constexpr int major = M;
        static constexpr int minor = N;
        static constexpr int patch = P;
      };
   }

:ref:`version-version_id` is a wrapper for statically defined version number. It encapsulates comparable
and ordered version number defined by their major version number, minor version number and a patch level.

:ref:`version-version_id` is designed to follow the natural ordering of version number based on the
successive ordering of each component of the version number.

**Template parameters**
  - ``M``: integral constant representing a major version number
  - ``N``: integral constant representing a minor version number
  - ``P``: integral constant representing a patch level

**Helper variable template**

.. code-block:: c++

   template<int M = 1, int N = 0, int P = 0> constexpr inline version_id<M,N,P> version = {};

.. _version-unspecified_version_t:

unspecified_version_t
*********************

.. code-block:: c++

   using unspecified_version_t = version_id<-1,0,0>;

Predefined type representing an undefined version number.

Functions
---------

.. _version-operator_equal:

operator==
**********

.. code-block:: c++

   template<int M1, int N1, int P1, int M2, int N2, int P2>
   constexpr bool operator==(version_id<M1,N1,P1> const& v1, version_id<M2,N2,P2> const& v2) noexcept;

Checks if two instances of :ref:`version-version_id` represents the same version number.

**Parameters**
  - **v1**, **v2** :ref:`version-version_id` to compares

**Returns**
  - A boolean value that evaluates to ``true`` if **v1** and **v2** are the same version number and to ``false`` otherwise.

.. _version-operator_not_equal:

operator!=
**********

.. code-block:: c++

   template<int M1, int N1, int P1, int M2, int N2, int P2>
   constexpr bool operator!=(version_id<M1,N1,P1> const& v1, version_id<M2,N2,P2> const& v2) noexcept;

Checks if two instances of :ref:`version-version_id` represents different version numbers.

**Parameters**
  - **v1**, **v2** :ref:`version-version_id` to compares

**Returns**
  - A boolean value that evaluates to ``false`` if **v1** and **v2** are the same version number and to ``true`` otherwise.

.. _version-operator_less:

operator<
*********

.. code-block:: c++

   template<int M1, int N1, int P1, int M2, int N2, int P2>
   constexpr bool operator<(version_id<M1,N1,P1> const& v1, version_id<M2,N2,P2> const& v2) noexcept;

Checks if two instances of :ref:`version-version_id` follow a strict lexicographical order with
respect to the version number ordering relationship.

**Parameters**
  - **v1**, **v2** :ref:`version-version_id` instances to compares

**Returns**
  - A boolean value that evaluates to ``true`` if **v1** represents a lower version number than **v2** and to ``false`` otherwise.

.. _version-operator_less_equal:

operator<=
**********

.. code-block:: c++

   template<int M1, int N1, int P1, int M2, int N2, int P2>
   constexpr bool operator<=(version_id<M1,N1,P1> const& v1, version_id<M2,N2,P2> const& v2) noexcept;

Checks if two instances of :ref:`version-version_id` follow a relaxed lexicographical order with
respect to the version number ordering relationship.

**Parameters**
  - **v1**, **v2** :ref:`version-version_id` instances to compares

**Returns**
  - A boolean value that evaluates to ``true`` if **v1** represents a lesser or equal version number than **v2** and to ``false`` otherwise.

.. _version-operator_greater:

operator>
*********

.. code-block:: c++

   template<int M1, int N1, int P1, int M2, int N2, int P2>
   constexpr bool operator>(version_id<M1,N1,P1> const& v1, version_id<M2,N2,P2> const& v2) noexcept;

Checks if two instances of :ref:`version-version_id` follow a strict lexicographical reverse order
with respect to the version number ordering relationship.

**Parameters**
  - **v1**, **v2** :ref:`version-version_id` instances to compares

**Returns**
  - A boolean value that evaluates to ``true`` if **v1** represents a higher version number than **v2** and to ``false`` otherwise.

.. _version-operator_greater_equal:

operator>=
**********

.. code-block:: c++

   template<int M1, int N1, int P1, int M2, int N2, int P2>
   constexpr bool operator>=(version_id<M1,N1,P1> const& v1, version_id<M2,N2,P2> const& v2) noexcept;

Checks if two instances of :ref:`version-version_id` follow a relaxed lexicographical reverse order
with respect to the version number ordering relationship.

**Parameters**
  - **v1**, **v2** :ref:`version-version_id` instances to compares

**Returns**
  - A boolean value that evaluates to ``true`` if **v1** represents a greater or equal version number than **v2** and to ``false`` otherwise.

.. _version-operator_stream:

operator<<
**********

.. code-block:: c++

   template<int M, int N, int P>
   std::ostream& operator<<(std::ostream& os, version_id<M,N,P> const& v);

Inserts a textual representation of a given :ref:`version-version_id` instance into an standard
output stream.

**Parameters**
  - **os** a mutable ``std::ostream`` instance
  - **v** a :ref:`version-version_id` to inserts into ``os``

**Returns**
  - A reference to the modified ``std::ostream`` instance.

.. _version-version_of:

version_of
**********

.. code-block:: c++

  template<typename Descriptor>
  constexpr auto version_of(Descriptor const& d) noexcept;

Retrieve the :ref:`version-version_id` of a given versionned descriptor, i.e any
SPY objects containing a version member.

**Parameters**
  - **d** A reference to a SPY global informations object

**Returns**
  - A instance of the :ref:`version-version_id` representing the version number carried by d. Note that :ref:`version-version_of` does not participate to overload resolution if ``Descriptor`` contains no  such version member.
