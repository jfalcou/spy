//==================================================================================================
/**
  SPY - C++ Informations Broker
  Copyright : SPY Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <ostream>
#include <spy/simd/x86.hpp>
#include <spy/simd/arm.hpp>
#include <spy/simd/ppc.hpp>
#include <spy/simd/wasm.hpp>

namespace spy::detail
{
  enum class simd_isa { undefined_ = -1, x86_ = 1000, ppc_ = 2000, arm_ = 3000, wasm_ = 4000 };

  enum class simd_version { undefined_ = -1
                          , sse1_       = 1110, sse2_  = 1120, sse3_ = 1130, ssse3_ = 1131
                          , sse41_      = 1141, sse42_ = 1142
                          , avx_  = 1201, avx2_  = 1202
                          , avx512_     = 1300
                          , vmx_2_03_   = 2203, vmx_2_05_ = 2205, vmx_2_06_ = 2206
                          , vmx_2_07_   = 2207, vmx_3_00_ = 2300, vmx_3_01_ = 2301
                          , vsx_2_06_   = 3206, vsx_2_07_ = 3207, vsx_3_00_ = 3300, vsx_3_01_ = 3301
                          , neon_       = 4001, asimd_    = 4002, sve_      = 4003
                          , fixed_sve_  = 5000
                          , sve128_     = 5007, sve256_ = 5008, sve512_ = 5009, sve1024_  = 5010
                          , simd128_    = 6000
                          };

  template<simd_isa InsSetArch = simd_isa::undefined_, simd_version Version = simd_version::undefined_>
  struct simd_info
  {
    static constexpr auto           isa     = InsSetArch;
    static constexpr auto           version = Version;
    static constexpr std::ptrdiff_t width   = []()
    {
      if constexpr(   Version == simd_version::simd128_
                  ||  (Version >= simd_version::sse1_ && Version <= simd_version::sse42_)
                  ||  Version == simd_version::neon_ || Version == simd_version::asimd_
                  ||  Version == simd_version::sve128_
                  ||  (Version >= simd_version::vmx_2_03_ && Version <= simd_version::vsx_3_01_)
                  )   return 128;
      else if constexpr (   Version == simd_version::avx_
                        ||  Version == simd_version::avx2_
                        ||  Version == simd_version::sve256_
                        ) return 256;
      else  if constexpr  (   Version == simd_version::avx512_
                          ||  Version == simd_version::sve512_
                          ) return 512;
      else  if constexpr  ( Version == simd_version::sve1024_ ) return 1024;
      else return -1;
    }();

    friend std::ostream& operator<<(std::ostream& os, simd_info const&)
    {
            if constexpr ( Version == simd_version::simd128_  ) os << "WASM SIMD128";
      else  if constexpr ( Version == simd_version::sse1_     ) os << "X86 SSE";
      else  if constexpr ( Version == simd_version::sse2_     ) os << "X86 SSE2";
      else  if constexpr ( Version == simd_version::sse3_     ) os << "X86 SSE3";
      else  if constexpr ( Version == simd_version::ssse3_    ) os << "X86 SSSE3";
      else  if constexpr ( Version == simd_version::sse41_    ) os << "X86 SSE4.1";
      else  if constexpr ( Version == simd_version::sse42_    ) os << "X86 SSE4.2";
      else  if constexpr ( Version == simd_version::avx_      ) os << "X86 AVX";
      else  if constexpr ( Version == simd_version::avx2_     ) os << "X86 AVX2";
      else  if constexpr ( Version == simd_version::avx512_   ) os << "X86 AVX512";
      else  if constexpr ( Version >= simd_version::vmx_2_03_ && Version <= simd_version::vmx_3_01_)
      {
        constexpr auto v = static_cast<int>(Version);
        os << "PPC VMX with ISA v" << ((v-2000)/100.);
      }
      else  if constexpr ( Version >= simd_version::vsx_2_06_ && Version <= simd_version::vsx_3_01_)
      {
        constexpr auto v = static_cast<int>(Version);
        os << "PPC VSX with ISA v" << ((v-3000)/100.);
      }
      else  if constexpr ( Version == simd_version::neon_   ) os << "ARM NEON";
      else  if constexpr ( Version == simd_version::asimd_  ) os << "ARM ASIMD";
      else  if constexpr ( Version == simd_version::sve_    ) os << "ARM SVE (dyn. bits)";
      else  if constexpr ( Version == simd_version::sve128_ ) os << "ARM SVE ( 128 bits)";
      else  if constexpr ( Version == simd_version::sve256_ ) os << "ARM SVE ( 256 bits)";
      else  if constexpr ( Version == simd_version::sve512_ ) os << "ARM SVE ( 512 bits)";
      else  if constexpr ( Version == simd_version::sve1024_) os << "ARM SVE (1024 bits)";
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
  using wasm_simd_info = detail::simd_info<detail::simd_isa::wasm_,V>;

  constexpr inline auto wasm_simd_ = wasm_simd_info<>{};
  constexpr inline auto simd128_   = wasm_simd_info<detail::simd_version::simd128_>{};

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
  constexpr inline auto vmx_2_03_ = ppc_simd_info<detail::simd_version::vmx_2_03_>{};
  constexpr inline auto vmx_2_05_ = ppc_simd_info<detail::simd_version::vmx_2_05_>{};
  constexpr inline auto vmx_2_06_ = ppc_simd_info<detail::simd_version::vmx_2_06_>{};
  constexpr inline auto vmx_2_07_ = ppc_simd_info<detail::simd_version::vmx_2_07_>{};
  constexpr inline auto vmx_3_00_ = ppc_simd_info<detail::simd_version::vmx_3_00_>{};
  constexpr inline auto vmx_3_01_ = ppc_simd_info<detail::simd_version::vmx_3_01_>{};

  constexpr inline auto vsx_2_06_ = ppc_simd_info<detail::simd_version::vsx_2_06_>{};
  constexpr inline auto vsx_2_07_ = ppc_simd_info<detail::simd_version::vsx_2_07_>{};
  constexpr inline auto vsx_3_00_ = ppc_simd_info<detail::simd_version::vsx_3_00_>{};
  constexpr inline auto vsx_3_01_ = ppc_simd_info<detail::simd_version::vsx_3_01_>{};

  template<detail::simd_version V = detail::simd_version::undefined_>
  using arm_simd_info = detail::simd_info<detail::simd_isa::arm_,V>;

  constexpr inline auto arm_simd_   = arm_simd_info<>{};
  constexpr inline auto neon_       = arm_simd_info<detail::simd_version::neon_ >{};
  constexpr inline auto asimd_      = arm_simd_info<detail::simd_version::asimd_>{};
  constexpr inline auto sve_        = arm_simd_info<detail::simd_version::sve_>{};
  constexpr inline auto fixed_sve_  = arm_simd_info<detail::simd_version::fixed_sve_>{};
  constexpr inline auto sve128_     = arm_simd_info<detail::simd_version::sve128_>{};
  constexpr inline auto sve256_     = arm_simd_info<detail::simd_version::sve256_>{};
  constexpr inline auto sve512_     = arm_simd_info<detail::simd_version::sve512_>{};
  constexpr inline auto sve1024_    = arm_simd_info<detail::simd_version::sve1024_>{};
}
