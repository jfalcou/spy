//==================================================================================================
/*
  SPY - C++ Informations Broker
  Copyright : SPY Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

// Make sure the proper header is included to detect GNU libc
#include <spy/detail.hpp>

#include <compare>
#include <cstddef>

namespace spy::_
{
  enum class libC
  {
    undefined_ = -1,
    cloudabi_,
    uc_,
    vms_,
    zos_,
    gnu_
  };

  template<libC Lib, int M, int N, int P> struct libc_info
  {
    static constexpr libC vendor = Lib;
    static constexpr version_id<M, N, P> version = {};

    inline constexpr explicit operator bool() const noexcept;

    template<libC C2> constexpr bool operator==(libc_info<C2, -1, 0, 0> const&) const noexcept { return C2 == vendor; }

    template<libC C2, int M2, int N2, int P2>
    constexpr bool operator==(libc_info<C2, M2, N2, P2> const& c2) const noexcept
    {
      return C2 == vendor && version == c2.version;
    }

    template<libC C2, int M2, int N2, int P2>
    constexpr auto operator<=>(libc_info<C2, M2, N2, P2> const& c2) const noexcept
    {
      if constexpr (vendor == C2) return version <=> c2.version;
      else return vendor <=> C2;
    }
  };

  template<_::stream OS, libC C, int M, int N, int P> auto& operator<<(OS& os, libc_info<C, M, N, P> const& c)
  {
    if (c.vendor == libC::cloudabi_) return os << "CloudABI Standard C Library " << c.version;
    if (c.vendor == libC::uc_) return os << "uClibc Standard C Library " << c.version;
    if (c.vendor == libC::vms_) return os << "VMS Standard C Library " << c.version;
    if (c.vendor == libC::zos_) return os << "z/OS Standard C Library " << c.version;
    if (c.vendor == libC::gnu_) return os << "GNU Standard C Library " << c.version;

    return os << "Undefined Standard C Library";
  }

  template<int M, int N, int P> using cloudabi_t = libc_info<libC::cloudabi_, M, N, P>;
  template<int M, int N, int P> using uc_t = libc_info<libC::uc_, M, N, P>;
  template<int M, int N, int P> using vms_t = libc_info<libC::vms_, M, N, P>;
  template<int M, int N, int P> using zos_t = libc_info<libC::zos_, M, N, P>;
  template<int M, int N, int P> using gnu_t = libc_info<libC::gnu_, M, N, P>;
}

namespace spy
{
  //================================================================================================
  // LIBC detection object type
  //================================================================================================
#if defined(__cloudlibc__)
#define SPY_LIBC_IS_CLOUDABI
  using libc_type = _::cloudabi_t<__cloudlibc_major__, __cloudlibc_minor__, 0>;
#elif defined(__GLIBC__)
#define SPY_LIBC_IS_GNU
  using libc_type = _::gnu_t<__GLIBC__, __GLIBC_MINOR__, 0>;
#elif defined(__GNU_LIBRARY__)
#define SPY_LIBC_IS_GNU
  using libc_type = _::gnu_t<__GNU_LIBRARY__, __GNU_LIBRARY_MINOR__, 0>;
#elif defined(__UCLIBC__)
#define SPY_LIBC_IS_UCLIBC
  using libc_type = _::uc_t<__UCLIBC_MAJOR__, __UCLIBC_MINOR__, __UCLIBC_SUBLEVEL__>;
#elif defined(__CRTL_VER)
#define SPY_LIBC_IS_VMS
#define SPY0 (__CRTL_VER / 100)
  using libc_type = _::vms_t<(SPY0 / 100000) % 100, (SPY0 / 1000) % 100, (SPY0) % 100>;
#undef SPY0
#elif defined(__LIBREL__)
#define SPY_LIBC_IS_ZOS
  using libc_type = _::zos_t < (__LIBREL__ & 0xF000000) >> 24, (__LIBREL__ & 0xFF0000) >> 16, (__LIBREL__ & 0xFFFF) > ;
#else
#define SPY_LIBC_IS_UNKNOWN
  using libc_type = _::libc_info<_::libC::undefined_, -1, 0, 0>;
#endif

  //================================================================================================
  //! @ingroup api
  //! @brief LIBC version reporting value
  //!
  //! The `spy::libc` object can be compared to any other libc related value to verify
  //! if the code being compiled with a specific version of the libc.
  //!
  //! Any libc related value can be checked for equality or ordering for a given version. The targeted
  //! version is then specified using a libc-dependent literal.
  //!
  //! Additionally, any of the libc related value are convertible to `bool`. They evaluates to `true` if they
  //! matches the correct libc currently used.
  //!
  //! @groupheader{Supported Value}
  //!
  //! Name              | Vendor
  //! ----------------- | -------------
  //! `spy::cloudabi_`  | CloudABI
  //! `spy::uc_`        | uClibc
  //! `spy::vms_`       | VMS
  //! `spy::zos_`       | zOS
  //! `spy::gnu_`       | GNU
  //!
  //! @groupheader{Example}
  //! @godbolt{samples/libc.cpp}
  //================================================================================================
  constexpr inline auto libc = libc_type{};
}

namespace spy::_
{
  template<libC C, int M, int N, int P> inline constexpr libc_info<C, M, N, P>::operator bool() const noexcept
  {
    return spy::libc == *this;
  }
}

namespace spy
{
  //================================================================================================
  // LIBCs detector stand-alone instances
  //================================================================================================
  constexpr inline auto cloudabi_ = _::cloudabi_t<-1, 0, 0>{};
  constexpr inline auto uc_ = _::uc_t<-1, 0, 0>{};
  constexpr inline auto vms_ = _::vms_t<-1, 0, 0>{};
  constexpr inline auto zos_ = _::zos_t<-1, 0, 0>{};
  constexpr inline auto gnu_ = _::gnu_t<-1, 0, 0>{};
}

namespace spy::literal
{
  //! @ingroup api
  //! @brief User-defined suffix for the CloudABI libc version definition
  template<char... c> constexpr auto operator""_cloud()
  {
    return _::literal_wrap<_::cloudabi_t, c...>();
  }

  //! @ingroup api
  //! @brief User-defined suffix for the uClibc version definition
  template<char... c> constexpr auto operator""_uc()
  {
    return _::literal_wrap<_::uc_t, c...>();
  }

  //! @ingroup api
  //! @brief User-defined suffix for the VMS libc version definition
  template<char... c> constexpr auto operator""_vms()
  {
    return _::literal_wrap<_::vms_t, c...>();
  }

  //! @ingroup api
  //! @brief User-defined suffix for the zOS libc version definition
  template<char... c> constexpr auto operator""_zos()
  {
    return _::literal_wrap<_::zos_t, c...>();
  }

  //! @ingroup api
  //! @brief User-defined suffix for the GNU libc version definition
  template<char... c> constexpr auto operator""_gnu()
  {
    return _::literal_wrap<_::gnu_t, c...>();
  }
}
