//==================================================================================================
/*
  SPY - C++ Informations Broker
  Copyright : SPY Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

namespace spy::_
{
  enum class archs
  {
    undefined_ = -1,
    x86_ = 10,
    amd64_ = 11,
    ppc_ = 20,
    arm_ = 30,
    wasm_ = 40,
    riscv_ = 50
  };

  template<archs Arch> struct arch_info
  {
    static constexpr archs vendor = Arch;

    inline constexpr explicit operator bool() const noexcept;

    template<archs A2> constexpr bool operator==(arch_info<A2> const&) const noexcept { return A2 == vendor; }

    template<_::stream OS> friend auto& operator<<(OS& os, arch_info const&)
    {
      if (Arch == archs::x86_) return os << "X86";
      if (Arch == archs::amd64_) return os << "AMD64";
      if (Arch == archs::ppc_) return os << "PowerPC";
      if (Arch == archs::arm_) return os << "ARM";
      if (Arch == archs::wasm_) return os << "WebAssembly";
      if (Arch == archs::riscv_) return os << "RISC-V";

      return os << "Undefined Architecture";
    }
  };
}

namespace spy
{
#if defined(i386) || defined(__i386__) || defined(__i486__) || defined(__i586__) || defined(__i686__) ||               \
  defined(__i386) || defined(_M_IX86) || defined(_X86_) || defined(__THW_INTEL__) || defined(__I86__) ||               \
  defined(__INTEL__)
  using arch_type = _::arch_info<_::archs::x86_>;
#define SPY_ARCH_IS_X86
#elif defined(__x86_64) || defined(__x86_64__) || defined(__amd64__) || defined(__amd64) || defined(_M_X64)
#define SPY_ARCH_IS_AMD64
  using arch_type = _::arch_info<_::archs::amd64_>;
#elif defined(__powerpc) || defined(__powerpc__) || defined(__POWERPC__) || defined(__ppc__) || defined(_M_PPC) ||     \
  defined(_ARCH_PPC) || defined(__PPCGECKO__) || defined(__PPCBROADWAY__) || defined(_XENON)
  using arch_type = _::arch_info<_::archs::ppc_>;
#define SPY_ARCH_IS_PPC
#elif defined(__arm__) || defined(__arm64) || defined(__thumb__) || defined(__TARGET_ARCH_ARM) ||                      \
  defined(__TARGET_ARCH_THUMB) || defined(_M_ARM) || defined(__ARM_ARCH_ISA_A64)
  using arch_type = _::arch_info<_::archs::arm_>;
#define SPY_ARCH_IS_ARM
#elif defined(__wasm__)
  using arch_type = _::arch_info<_::archs::wasm_>;
#define SPY_ARCH_IS_WASM
#elif defined(__riscv)
  using arch_type = _::arch_info<_::archs::riscv_>;
#define SPY_ARCH_IS_RISCV
#else
#define SPY_ARCH_IS_UNKNOWN
  using arch_type = _::arch_info<_::archs::undefined_>;
#endif

  //================================================================================================
  //! @ingroup api
  //! @brief Architecture reporting value
  //!
  //! The `spy::architecture` object can be compared to any other architecture related value to verify
  //! if the code being compiled is compiled for a given CPU architecture.
  //!
  //! Additionally, any of the architecture related value are convertible to `bool`. They evaluates to `true` if they
  //! matches the correct architecture currently targeted.
  //!
  //! @groupheader{Supported Value}
  //!
  //! Name            | Architecture
  //! --------------- | -------------
  //! `spy::amd64`    | Intel X86-64 and similar architectures.
  //! `spy::arm`      | ARM.
  //! `spy::ppc`      | PowerPC.
  //! `spy::riscv`    | RISC-V.
  //! `spy::wasm`     | WASM pseudo-architecture.
  //! `spy::x86`      | Intel X86.
  //!
  //! @groupheader{Example}
  //! @godbolt{samples/architecture.cpp}
  //================================================================================================
  constexpr inline arch_type architecture;
}

namespace spy::_
{
  template<archs Arch> inline constexpr arch_info<Arch>::operator bool() const noexcept
  {
    return spy::architecture == *this;
  }
}

namespace spy
{
  //================================================================================================
  // Architecture detector stand-alone instances
  //================================================================================================
  constexpr inline auto x86_ = _::arch_info<_::archs::x86_>{};
  constexpr inline auto amd64_ = _::arch_info<_::archs::amd64_>{};
  constexpr inline auto ppc_ = _::arch_info<_::archs::ppc_>{};
  constexpr inline auto arm_ = _::arch_info<_::archs::arm_>{};
  constexpr inline auto wasm_ = _::arch_info<_::archs::wasm_>{};
  constexpr inline auto riscv_ = _::arch_info<_::archs::riscv_>{};
}
