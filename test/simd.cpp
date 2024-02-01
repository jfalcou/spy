//==================================================================================================
/**
  SPY - C++ Informations Broker
  Copyright : SPY Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include <spy.hpp>
#include <iostream>
#include <cassert>

int main()
{
  std::cout << "Supported SIMD instructions set: " << spy::simd_instruction_set << std::endl;
  std::cout << "Supported SIMD instructions set: " << typeid(spy::simd_instruction_set).name() << std::endl;
  std::cout << "Check that X86 SIMD extension detection is correct: " << std::endl;
  {
    std::cout << "X86 SIMD status: " << std::boolalpha << (spy::simd_instruction_set == spy::x86_simd_) << std::endl;
    std::cout << "SSE1     status: " << std::boolalpha << (spy::simd_instruction_set >= spy::sse1_    ) << std::endl;
    std::cout << "SSE2     status: " << std::boolalpha << (spy::simd_instruction_set >= spy::sse2_    ) << std::endl;
    std::cout << "SSE3     status: " << std::boolalpha << (spy::simd_instruction_set >= spy::sse3_    ) << std::endl;
    std::cout << "SSE4.1   status: " << std::boolalpha << (spy::simd_instruction_set >= spy::sse41_   ) << std::endl;
    std::cout << "SSE4.2   status: " << std::boolalpha << (spy::simd_instruction_set >= spy::sse42_   ) << std::endl;
    std::cout << "AVX      status: " << std::boolalpha << (spy::simd_instruction_set >= spy::avx_     ) << std::endl;
    std::cout << "AVX2     status: " << std::boolalpha << (spy::simd_instruction_set >= spy::avx2_    ) << std::endl;
    std::cout << "FMA3    support: " << std::boolalpha << (spy::supports::fma_  ) << std::endl;
    std::cout << "FMA4    support: " << std::boolalpha << (spy::supports::fma4_ ) << std::endl;
    std::cout << "XOP     support: " << std::boolalpha << (spy::supports::xop_  ) << std::endl;
    std::cout << "AVX512   status: " << std::boolalpha << (spy::simd_instruction_set >= spy::avx512_  ) << std::endl;
    std::cout << "|-BW          support: " << std::boolalpha << (spy::supports::avx512::bw_ ) << std::endl;
    std::cout << "|-CD          support: " << std::boolalpha << (spy::supports::avx512::cd_ ) << std::endl;
    std::cout << "|-DQ          support: " << std::boolalpha << (spy::supports::avx512::dq_ ) << std::endl;
    std::cout << "|-ER          support: " << std::boolalpha << (spy::supports::avx512::er_ ) << std::endl;
    std::cout << "|-IFMA        support: " << std::boolalpha << (spy::supports::avx512::ifma_ ) << std::endl;
    std::cout << "|-PF          support: " << std::boolalpha << (spy::supports::avx512::pf_ ) << std::endl;
    std::cout << "|-VL          support: " << std::boolalpha << (spy::supports::avx512::vl_ ) << std::endl;
    std::cout << "|-POPCNTDQ    support: " << std::boolalpha << (spy::supports::avx512::popcntdq_ ) << std::endl;
    std::cout << "|-4FMAPS      support: " << std::boolalpha << (spy::supports::avx512::_4fmaps_ ) << std::endl;
    std::cout << "|-VNNIW       support: " << std::boolalpha << (spy::supports::avx512::vnniw_ ) << std::endl;
    std::cout << "|-VBMI        support: " << std::boolalpha << (spy::supports::avx512::vbmi_ ) << std::endl;
    std::cout << "|-BF16        support: " << std::boolalpha << (spy::supports::avx512::bf16_ ) << std::endl;
    std::cout << "|-BITALG      support: " << std::boolalpha << (spy::supports::avx512::bitalg_ ) << std::endl;
    std::cout << "|-VBMI2       support: " << std::boolalpha << (spy::supports::avx512::vbmi2_ ) << std::endl;
    std::cout << "|-VNNI        support: " << std::boolalpha << (spy::supports::avx512::vnni_ ) << std::endl;
    std::cout << "|-VPINTERSECT support: " << std::boolalpha << (spy::supports::avx512::vpintersect_ ) << std::endl;
  }
  std::cout << std::endl;

  std::cout << "Check that ARM SIMD extension detection is correct: " << std::endl;
  {
    std::cout << "ARM SIMD status: "  << std::boolalpha << (spy::simd_instruction_set == spy::arm_simd_ ) << std::endl;
    std::cout << "NEON     status: "  << std::boolalpha << (spy::simd_instruction_set >= spy::neon_ )     << std::endl;
    std::cout << "ASIMD    status: "  << std::boolalpha << (spy::simd_instruction_set >= spy::asimd_)     << std::endl;

    std::cout << "SVE      status: "  << std::boolalpha << (spy::simd_instruction_set == spy::sve_ )      << std::endl;
    std::cout << "SVE2     status: "  << std::boolalpha << (spy::simd_instruction_set == spy::sve2_)      << std::endl;
    if constexpr(spy::simd_instruction_set >= spy::sve_)
    {
      if constexpr(spy::simd_instruction_set.has_fixed_cardinal())
      {
        std::cout << "SVE uses fixed size: " << spy::simd_instruction_set.width << " bits" << std::endl;
      }
      else
      {
        std::cout << "SVE uses flexible size" << std::endl;
      }
    }
  }
  std::cout << std::endl;

  std::cout << "Check that PPC SIMD extension detection is correct: " << std::endl;
  {
    std::cout << "PPC SIMD status: "  << std::boolalpha << (spy::simd_instruction_set == spy::ppc_simd_ ) << std::endl;
    std::cout << "VMX (Any ISA)   status: " << std::boolalpha << (spy::simd_instruction_set >= spy::vmx_ ) << std::endl;
    std::cout << " |- ISA v2.03 support : " << std::boolalpha << (spy::simd_instruction_set >= spy::vmx_2_03_ ) << std::endl;
    std::cout << " |- ISA v2.05 support : " << std::boolalpha << (spy::simd_instruction_set >= spy::vmx_2_05_ ) << std::endl;
    std::cout << " |- ISA v2.06 support : " << std::boolalpha << (spy::simd_instruction_set >= spy::vmx_2_06_ ) << std::endl;
    std::cout << " |- ISA v2.07 support : " << std::boolalpha << (spy::simd_instruction_set >= spy::vmx_2_07_ ) << std::endl;
    std::cout << " |- ISA v3.00 support : " << std::boolalpha << (spy::simd_instruction_set >= spy::vmx_3_00_ ) << std::endl;
    std::cout << " |- ISA v3.01 support : " << std::boolalpha << (spy::simd_instruction_set >= spy::vmx_3_01_ ) << std::endl;
    std::cout << "VSX (Any ISA)   status: " << std::boolalpha << (spy::simd_instruction_set >= spy::vsx_ ) << std::endl;
    std::cout << " |- ISA v2.06 support : " << std::boolalpha << (spy::simd_instruction_set >= spy::vsx_2_06_ ) << std::endl;
    std::cout << " |- ISA v2.07 support : " << std::boolalpha << (spy::simd_instruction_set >= spy::vsx_2_07_ ) << std::endl;
    std::cout << " |- ISA v3.00 support : " << std::boolalpha << (spy::simd_instruction_set >= spy::vsx_3_00_ ) << std::endl;
    std::cout << " |- ISA v3.01 support : " << std::boolalpha << (spy::simd_instruction_set >= spy::vsx_3_01_ ) << std::endl;
  }
  std::cout << std::endl;

  std::cout << "Check that WASM SIMD extension detection is correct: " << std::endl;
  {
    std::cout << "WASM     status: " << std::boolalpha << (spy::simd_instruction_set == spy::wasm_simd_ ) << std::endl;
    std::cout << "SIMD128  status: " << std::boolalpha << (spy::simd_instruction_set >= spy::simd128_   ) << std::endl;
  }
  std::cout << std::endl;
}
