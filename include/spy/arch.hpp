//==================================================================================================
/*
  Copyright 2020 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
 */
//==================================================================================================
#ifndef SPY_ARCH_HPP_INLUDED
#define SPY_ARCH_HPP_INLUDED

#include <iostream>

namespace spy { namespace detail
{
  enum class archs  { undefined_  = -1
                    , x86_ = 10, amd64_ = 11
                    , ppc_ = 20, arm_ = 30
                    };

  template<archs ARCH> struct arch_info
  {
    static constexpr archs  vendor  = ARCH;

    inline constexpr operator bool() const noexcept;

    template<archs A2>
    constexpr bool operator==(arch_info<A2> const& c2) const noexcept
    {
      return A2 == vendor;
    }
  };

  template<archs ARCH>
  std::ostream& operator<<(std::ostream& os, arch_info<ARCH> const&)
  {
    if(ARCH == archs::x86_  ) return os << "X86";
    if(ARCH == archs::amd64_) return os << "AMD64";
    if(ARCH == archs::ppc_  ) return os << "PowerPC";
    if(ARCH == archs::arm_  ) return os << "ARM";

    return os << "Undefined Architecture";
  }
} }

namespace spy
{
#if defined(i386) || defined(__i386__) || defined(__i486__) || defined(__i586__) ||                \
    defined(__i686__) || defined(__i386) || defined(_M_IX86) || defined(_X86_) ||                  \
    defined(__THW_INTEL__) || defined(__I86__) || defined(__INTEL__)
  using arch_type = detail::arch_info<detail::archs::x86_>;
#elif defined(__x86_64) || defined(__x86_64__) || defined(__amd64__) || defined(__amd64) || defined(_M_X64)
  using arch_type = detail::arch_info<detail::archs::amd64_>;
#elif defined(__powerpc) || defined(__powerpc__) || defined(__POWERPC__) || defined(__ppc__) ||     \
      defined(_M_PPC) || defined(_ARCH_PPC) || defined(__PPCGECKO__) || defined(__PPCBROADWAY__) || \
      defined(_XENON)
  using arch_type = detail::arch_info<detail::archs::ppc_>;
#elif defined(__arm__) || defined(__arm64) || defined(__thumb__) || defined(__TARGET_ARCH_ARM) ||   \
      defined(__TARGET_ARCH_THUMB) || defined(_M_ARM)
  using arch_type = detail::arch_info<detail::archs::arm_>;
#else
  using arch_type = detail::arch_info<detail::archs::undefined_>;
#endif

  //================================================================================================
  // Architecture detection object
  //================================================================================================
  constexpr inline arch_type architecture;
}

namespace spy { namespace detail
{
  template<archs ARCH>
  inline constexpr arch_info<ARCH>::operator bool() const noexcept
  {
    return *this == spy::architecture;
  }
} }

namespace spy
{
  //================================================================================================
  // Architecture detector stand-alone instances
  //================================================================================================
  constexpr inline auto x86_    = detail::arch_info<detail::archs::x86_>{};
  constexpr inline auto amd64_  = detail::arch_info<detail::archs::amd64_>{};
  constexpr inline auto ppc_    = detail::arch_info<detail::archs::ppc_>{};
  constexpr inline auto arm_    = detail::arch_info<detail::archs::arm_>{};
}

#endif
