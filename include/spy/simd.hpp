//==================================================================================================
/*
  SPY - C++ Informations Broker
  Copyright : SPY Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <ostream>
#include <spy/simd/x86.hpp>
#include <spy/simd/arm.hpp>
#include <spy/simd/ppc.hpp>
#include <spy/simd/wasm.hpp>
#include <spy/simd/riscv.hpp>

namespace spy::detail
{
  enum class simd_isa { undefined_  = -1
                      , x86_        = 1000
                      , ppc_        = 2000
                      , arm_        = 3000, arm_sve_ = 3500
                      , wasm_       = 4000
                      , riscv_      = 5000
                      };

  enum class simd_version { undefined_  = -1
                          , sse1_       = 1110, sse2_  = 1120, sse3_ = 1130, ssse3_ = 1131
                          , sse41_      = 1141, sse42_ = 1142
                          , avx_        = 1201, avx2_  = 1202
                          , avx512_     = 1300
                          , vmx_        = 2000
                          , vmx_2_03_   = 2203, vmx_2_05_ = 2205, vmx_2_06_ = 2206
                          , vmx_2_07_   = 2207, vmx_3_00_ = 2300, vmx_3_01_ = 2301
                          , vsx_        = 3000
                          , vsx_2_06_   = 3206, vsx_2_07_ = 3207, vsx_3_00_ = 3300, vsx_3_01_ = 3301
                          , neon_       = 4001, asimd_    = 4002
                          , sve_        = 5000, sve2_     = 5500
                          , simd128_    = 6000
                          , rvv_        = 7000
                          };

  template< simd_isa InsSetArch  = simd_isa::undefined_
          , simd_version Version = simd_version::undefined_
          >
  struct simd_info
  {
    static constexpr auto           isa     = InsSetArch;
    static constexpr auto           version = Version;

    static constexpr std::ptrdiff_t width   = []()
    {
      if constexpr(   Version == simd_version::simd128_
                  ||  (Version >= simd_version::sse1_ && Version <= simd_version::sse42_)
                  ||  Version == simd_version::neon_ || Version == simd_version::asimd_
                  ||  (Version >= simd_version::vmx_2_03_ && Version <= simd_version::vsx_3_01_)
                  )                                                                       return 128;
      else  if constexpr(Version == simd_version::avx_ || Version == simd_version::avx2_) return 256;
      else  if constexpr(Version == simd_version::avx512_     )                           return 512;
else if constexpr( Version == simd_version::rvv_ )
      {
#if defined(__riscv_v_fixed_vlen)
        return __riscv_v_fixed_vlen;
#else
        return -1;
#endif
      }
      else  if constexpr(Version == simd_version::sve_ || Version == simd_version::sve2_)
      {
#if defined(__ARM_FEATURE_SVE_BITS)
        return __ARM_FEATURE_SVE_BITS;
#else
        return -1;
#endif
      }

      else return -1;
    }();

    static constexpr bool has_fixed_cardinal() { return width != -1; }

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
      else  if constexpr ( Version == simd_version::neon_     ) os  << "ARM NEON";
      else  if constexpr ( Version == simd_version::asimd_    ) os  << "ARM ASIMD";
      else  if constexpr ( Version == simd_version::sve_ || Version == simd_version::sve2_ )
      {
        os  << "ARM SVE" << (Version == simd_version::sve2_ ? "2" : "") << "(";

        constexpr auto fc = has_fixed_cardinal();
        if constexpr(fc)  os << simd_info::width;
        else              os << "dyn.";

        os << " bits)";
      }
      else  if constexpr ( Version == simd_version::rvv_ )
      {
        os  << "RISC-V RVV(";

        constexpr auto fc = has_fixed_cardinal();
        if constexpr(fc)  os << simd_info::width;
        else              os << "dyn.";

        os << " bits)";
      }
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
  //! @ingroup api
  //! @brief SIMD extensions set  reporting value
  //!
  //! @groupheader{SIMD Instructions Sets}
  //! SIMD extensions set detection is made so that one can ask if the current SIMD extension is exactly,
  //! below or above a given reference instruction set. Detectable instructions sets depends on SIMD
  //! hardware vendor
  //!
  //! | Architecture      | Supported SIMD instructions sets                                                        |
  //! | ----------------- | --------------------------------------------------------------------------------------- |
  //! | **X86 SSE**       | `spy::sse1_`, `spy::sse2_`, `spy::sse3_`, `spy::ssse3_`, `spy::sse41_`, `spy::sse42_`   |
  //! | **X86 AVX**       | `spy::avx_`, `spy::avx2_`, `spy::avx512_`                                               |
  //! | **Power PC VMX**  | `spy::vmx_`, `spy::vmx_2_03_`, `spy::vmx_2_05_`, `spy::vmx_2_06_`, `spy::vmx_2_07_`, `spy::vmx_3_00_`, `spy::vmx_3_01_` |
  //! | **Power PC VSX**  | `spy::vsx_`, `spy::vsx_2_06_`, `spy::vsx_2_07_`, `spy::vsx_3_00_`, `spy::vsx_3_01_`     |
  //! | **ARM NEON**      | `spy::neon_`, `spy::asimd_`                                                             |
  //! | **ARM SVE**       | `spy::sve_`,`spy::sve128_`, `spy::sve256_`, `spy::sve512_`, `spy::sve1024_`             |
  //! | **WASM**          | `spy::simd128_`                                                                         |
  //! | **RISC-V**        | `spy::rvv_``                                                                            |
  //!
  //! Complete set of comparison operators is provided for those sets. Order of instructions sets
  //! are built so that if an instructions set supersedes another, it is considered greater than. For
  //! example, `spy::avx_` is greater than `spy::sse41_` as the former is a super-set of the later.
  //! Comparing SIMD descriptors across architecture is undefined behavior.
  //!
  //! Moreover, the `spy::simd_instruction_set` object exposes a constexpr `width` static field that
  //! contains the size in bits of the current SIMD instructions set registers.
  //!
  //! @subgroupheader{Example - SIMD Instructions Sets}
  //! @godbolt{samples/simd.cpp}
  //!
  //! @groupheader{SIMD Architectures}
  //!
  //! One can also simply asks if a given family of instructions set is available.
  //!
  //! | Architecture  | Generic indicator   |
  //! | ------------- | --------------------|
  //! | **X86**       | `spy::x86_simd_`    |
  //! | **Power PC**  | `spy::ppc_simd_`    |
  //! | **ARM**       | `spy::arm_simd_`    |
  //! | **WASM**      | `spy::wasm_simd_`   |
  //! | **RISC-V**    | `spy::riscv_simd_`  |
  //!
  //! @subgroupheader{Example - SIMD Architectures}
  //! @godbolt{samples/simd-arch.cpp}
  //!
  //! @groupheader{Supplemental Instructions sets}
  //!
  //! Some SIMD instructions set provides supplemental instructions on top of existing system.
  //! Those supplemental instruction set can be checked using the `spy::supports` namespace.
  //!
  //! | Architecture  | Supported SIMD instructions sets                                                    |
  //! | ------------- | ------------------------------------------------------------------------------------|
  //! | X86 AVX       | `xop_`, `fma_`, `fma4_`                                                             |
  //! | X86 AVX512    | `bw_`, `cd_`, `dq_`, `er_`, `ifma_`, `pf_`, `vl_`, `popcntdq_`                      |
  //! |               | `_4fmaps_`, `vnniw_`, `vbmi_`, `bf16_`,`bitalg_`, `vbmi2_`, `vnni_`, `vpintersect_` |
  //!
  //! @subgroupheader{Example - SIMD Architectures}
  //! @godbolt{samples/simd-additional.cpp}
  //!
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
  constexpr inline auto vmx_      = ppc_simd_info<detail::simd_version::vmx_>{};
  constexpr inline auto vmx_2_03_ = ppc_simd_info<detail::simd_version::vmx_2_03_>{};
  constexpr inline auto vmx_2_05_ = ppc_simd_info<detail::simd_version::vmx_2_05_>{};
  constexpr inline auto vmx_2_06_ = ppc_simd_info<detail::simd_version::vmx_2_06_>{};
  constexpr inline auto vmx_2_07_ = ppc_simd_info<detail::simd_version::vmx_2_07_>{};
  constexpr inline auto vmx_3_00_ = ppc_simd_info<detail::simd_version::vmx_3_00_>{};
  constexpr inline auto vmx_3_01_ = ppc_simd_info<detail::simd_version::vmx_3_01_>{};

  constexpr inline auto vsx_      = ppc_simd_info<detail::simd_version::vsx_>{};
  constexpr inline auto vsx_2_06_ = ppc_simd_info<detail::simd_version::vsx_2_06_>{};
  constexpr inline auto vsx_2_07_ = ppc_simd_info<detail::simd_version::vsx_2_07_>{};
  constexpr inline auto vsx_3_00_ = ppc_simd_info<detail::simd_version::vsx_3_00_>{};
  constexpr inline auto vsx_3_01_ = ppc_simd_info<detail::simd_version::vsx_3_01_>{};

  template<detail::simd_version V = detail::simd_version::undefined_>
  using arm_simd_info = detail::simd_info<detail::simd_isa::arm_,V>;

  template<detail::simd_version V = detail::simd_version::undefined_>
  using sve_simd_info = detail::simd_info<detail::simd_isa::arm_sve_,V>;

  constexpr inline auto arm_simd_   = arm_simd_info<>{};
  constexpr inline auto neon_       = arm_simd_info<detail::simd_version::neon_ >{};
  constexpr inline auto asimd_      = arm_simd_info<detail::simd_version::asimd_>{};
  constexpr inline auto sve_        = sve_simd_info<detail::simd_version::sve_>{};
  constexpr inline auto sve2_       = sve_simd_info<detail::simd_version::sve2_>{};

  template<detail::simd_version V= detail::simd_version::undefined_>
  using riscv_simd_info             =  detail::simd_info<detail::simd_isa::riscv_, V>;
  constexpr inline auto riscv_simd_ = riscv_simd_info<> {};
  constexpr inline auto rvv_        = riscv_simd_info<detail::simd_version::rvv_> {};
}
