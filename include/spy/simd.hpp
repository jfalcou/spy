//==================================================================================================
/*
  SPY - C++ Informations Broker
  Copyright 2020-2021 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
 */
//==================================================================================================
#ifndef SPY_SIMD_HPP_INCLUDED
#define SPY_SIMD_HPP_INCLUDED

#include <ostream>
#include <spy/simd/x86.hpp>
#include <spy/simd/arm.hpp>
#include <spy/simd/ppc.hpp>

namespace spy::detail
{
  enum class simd_isa { undefined_ = -1, x86_ = 1000, ppc_ = 2000, arm_ = 3000 };

  enum class simd_version { undefined_ = -1
                          , sse1_   = 1110, sse2_  = 1120, sse3_ = 1130, ssse3_ = 1131
                          , sse41_  = 1141, sse42_ = 1142, avx_  = 1201, avx2_  = 1202
                          , avx512_ = 1300
                          , vmx_    = 2001, vsx_   = 2002
                          , neon_   = 3001, asimd_ = 3002
                          };

  template<simd_isa InsSetArch = simd_isa::undefined_, simd_version Version = simd_version::undefined_>
  struct simd_info
  {
    static constexpr auto isa     = InsSetArch;
    static constexpr auto version = Version;

    friend std::ostream& operator<<(std::ostream& os, simd_info const&)
    {
            if constexpr ( Version == simd_version::sse1_   ) os << "X86 SSE";
      else  if constexpr ( Version == simd_version::sse2_   ) os << "X86 SSE2";
      else  if constexpr ( Version == simd_version::sse3_   ) os << "X86 SSE3";
      else  if constexpr ( Version == simd_version::ssse3_  ) os << "X86 SSSE3";
      else  if constexpr ( Version == simd_version::sse41_  ) os << "X86 SSE4.1";
      else  if constexpr ( Version == simd_version::sse42_  ) os << "X86 SSE4.2";
      else  if constexpr ( Version == simd_version::avx_    ) os << "X86 AVX";
      else  if constexpr ( Version == simd_version::avx2_   ) os << "X86 AVX2";
      else  if constexpr ( Version == simd_version::avx512_ ) os << "X86 AVX512";
      else  if constexpr ( Version == simd_version::vmx_    ) os << "PPC VMX";
      else  if constexpr ( Version == simd_version::vsx_    ) os << "PPC VSX";
      else  if constexpr ( Version == simd_version::neon_   ) os << "ARM NEON";
      else  if constexpr ( Version == simd_version::asimd_  ) os << "ARM ASIMD";
      else return os << "Undefined SIMD instructions set";

      if constexpr (spy::supports::fma_)     os << " (with FMA3 support)";
      if constexpr (spy::supports::fma4_)    os << " (with FMA4 support)";
      if constexpr (spy::supports::xop_)     os << " (with XOP support)";

      return os;
    }

    template<simd_isa OInsSetArch>
    constexpr bool operator==(simd_info<OInsSetArch> const&) const noexcept { return OInsSetArch == InsSetArch; }

    template<simd_isa OInsSetArch>
    constexpr bool operator!=(simd_info<OInsSetArch> const&) const noexcept { return OInsSetArch != InsSetArch; }

    template<simd_isa OInsSetArch, simd_version OVersion>
    constexpr bool operator==(simd_info<OInsSetArch,OVersion> const&) const noexcept
    {
      return (Version == OVersion) && (OInsSetArch == InsSetArch);
    }

    template<simd_isa OInsSetArch, simd_version OVersion>
    constexpr bool operator!=(simd_info<OInsSetArch,OVersion> const&) const noexcept
    {
      return (Version != OVersion) || (OInsSetArch != InsSetArch);
    }

    template<simd_isa OInsSetArch, simd_version OVersion>
    constexpr bool operator<(simd_info<OInsSetArch,OVersion> const&) const noexcept
    {
      return (Version < OVersion) && (OInsSetArch == InsSetArch);
    }

    template<simd_isa OInsSetArch, simd_version OVersion>
    constexpr bool operator>(simd_info<OInsSetArch,OVersion> const&) const noexcept
    {
      return (Version > OVersion) && (OInsSetArch == InsSetArch);
    }

    template<simd_isa OInsSetArch, simd_version OVersion>
    constexpr bool operator<=(simd_info<OInsSetArch,OVersion> const&) const noexcept
    {
      return (Version <= OVersion) && (OInsSetArch == InsSetArch);
    }

    template<simd_isa OInsSetArch, simd_version OVersion>
    constexpr bool operator>=(simd_info<OInsSetArch,OVersion> const&) const noexcept
    {
      return (Version >= OVersion) && (OInsSetArch == InsSetArch);
    }
  };
}

namespace spy
{
  //================================================================================================
  // Current SIMD instructions set
  //================================================================================================
  #if defined(SPY_SIMD_DETECTED)
  constexpr inline auto simd_instruction_set = detail::simd_info<SPY_SIMD_VENDOR,SPY_SIMD_DETECTED>{};
  #else
  constexpr inline auto simd_instruction_set = detail::simd_info<>{};
  #endif

  //================================================================================================
  // Available SIMD instructions set
  //================================================================================================
  constexpr inline auto undefined_simd_ = detail::simd_info<>{};

  template<detail::simd_version V = detail::simd_version::undefined_>
  using x86_simd_info = detail::simd_info<detail::simd_isa::x86_,V>;

  constexpr inline auto x86_simd_ = x86_simd_info<>{};
  constexpr inline auto sse1_     = x86_simd_info<detail::simd_version::sse1_   >{};
  constexpr inline auto sse2_     = x86_simd_info<detail::simd_version::sse2_   >{};
  constexpr inline auto sse3_     = x86_simd_info<detail::simd_version::sse3_   >{};
  constexpr inline auto ssse3_    = x86_simd_info<detail::simd_version::ssse3_  >{};
  constexpr inline auto sse41_    = x86_simd_info<detail::simd_version::sse41_  >{};
  constexpr inline auto sse42_    = x86_simd_info<detail::simd_version::sse42_  >{};
  constexpr inline auto avx_      = x86_simd_info<detail::simd_version::avx_    >{};
  constexpr inline auto avx2_     = x86_simd_info<detail::simd_version::avx2_   >{};
  constexpr inline auto avx512_   = x86_simd_info<detail::simd_version::avx512_ >{};

  template<detail::simd_version V = detail::simd_version::undefined_>
  using ppc_simd_info = detail::simd_info<detail::simd_isa::ppc_,V>;

  constexpr inline auto ppc_simd_ = ppc_simd_info<>{};
  constexpr inline auto vmx_      = ppc_simd_info<detail::simd_version::vmx_>{};
  constexpr inline auto vsx_      = ppc_simd_info<detail::simd_version::vsx_>{};

  template<detail::simd_version V = detail::simd_version::undefined_>
  using arm_simd_info = detail::simd_info<detail::simd_isa::arm_,V>;

  constexpr inline auto arm_simd_ = arm_simd_info<>{};
  constexpr inline auto neon_     = arm_simd_info<detail::simd_version::neon_ >{};
  constexpr inline auto asimd_    = arm_simd_info<detail::simd_version::asimd_>{};
}

#endif
