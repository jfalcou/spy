//==================================================================================================
/**
  SPY - C++ Informations Broker
  Copyright : SPY Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include <iostream>
#include <spy/spy.hpp>

#include "assert.hpp"

int main()
{
  std::cout << "== detected compiler is correct\n";
  {
#if defined(__NVCC__)
    SPY_ASSERT("the compiler is nvcc", spy::compiler == spy::nvcc_);
    SPY_ASSERT("the compiler is not msvc", !(spy::compiler == spy::msvc_));
    SPY_ASSERT("the compiler is not clang-cl", !(spy::compiler == spy::clangcl_));
    SPY_ASSERT("the compiler is not icc", !(spy::compiler == spy::intel_));
    SPY_ASSERT("the compiler is not dpc++", !(spy::compiler == spy::dpcpp_));
    SPY_ASSERT("the compiler is not clang", !(spy::compiler == spy::clang_));
    SPY_ASSERT("the compiler is not g++", !(spy::compiler == spy::gcc_));
    SPY_ASSERT("the compiler is not emscripten", !(spy::compiler == spy::emscripten_));
    SPY_ASSERT("the compiler is not mingw32", !(spy::compiler == spy::mingw32_));
    SPY_ASSERT("the compiler is not mingw64", !(spy::compiler == spy::mingw64_));
#elif defined(__MINGW32__) && !defined(__MINGW64__)
    SPY_ASSERT("the compiler is not nvcc", !(spy::compiler == spy::nvcc_));
    SPY_ASSERT("the compiler is not msvc", !(spy::compiler == spy::msvc_));
    SPY_ASSERT("the compiler is not clang-cl", !(spy::compiler == spy::clangcl_));
    SPY_ASSERT("the compiler is not icc", !(spy::compiler == spy::intel_));
    SPY_ASSERT("the compiler is not dpc++", !(spy::compiler == spy::dpcpp_));
    SPY_ASSERT("the compiler is not clang", !(spy::compiler == spy::clang_));
    SPY_ASSERT("the compiler is not g++", !(spy::compiler == spy::gcc_));
    SPY_ASSERT("the compiler is not emscripten", !(spy::compiler == spy::emscripten_));
    SPY_ASSERT("the compiler is mingw32", spy::compiler == spy::mingw32_);
    SPY_ASSERT("the compiler is not mingw64", !(spy::compiler == spy::mingw64_));
#elif defined(__MINGW32__) && defined(__MINGW64__)
    SPY_ASSERT("the compiler is not nvcc", !(spy::compiler == spy::nvcc_));
    SPY_ASSERT("the compiler is not msvc", !(spy::compiler == spy::msvc_));
    SPY_ASSERT("the compiler is not clang-cl", !(spy::compiler == spy::clangcl_));
    SPY_ASSERT("the compiler is not icc", !(spy::compiler == spy::intel_));
    SPY_ASSERT("the compiler is not dpc++", !(spy::compiler == spy::dpcpp_));
    SPY_ASSERT("the compiler is not clang", !(spy::compiler == spy::clang_));
    SPY_ASSERT("the compiler is not g++", !(spy::compiler == spy::gcc_));
    SPY_ASSERT("the compiler is not emscripten", !(spy::compiler == spy::emscripten_));
    SPY_ASSERT("the compiler is not mingw32", !(spy::compiler == spy::mingw32_));
    SPY_ASSERT("the compiler is mingw64", spy::compiler == spy::mingw64_);
#elif defined(_MSC_VER) && !defined(__clang__)
    SPY_ASSERT("the compiler is not nvcc", !(spy::compiler == spy::nvcc_));
    SPY_ASSERT("the compiler is msvc", spy::compiler == spy::msvc_);
    SPY_ASSERT("the compiler is not clang-cl", !(spy::compiler == spy::clangcl_));
    SPY_ASSERT("the compiler is not icc", !(spy::compiler == spy::intel_));
    SPY_ASSERT("the compiler is not dpc++", !(spy::compiler == spy::dpcpp_));
    SPY_ASSERT("the compiler is not clang", !(spy::compiler == spy::clang_));
    SPY_ASSERT("the compiler is not g++", !(spy::compiler == spy::gcc_));
    SPY_ASSERT("the compiler is not emscripten", !(spy::compiler == spy::emscripten_));
    SPY_ASSERT("the compiler is not mingw32", !(spy::compiler == spy::mingw32_));
    SPY_ASSERT("the compiler is not mingw64", !(spy::compiler == spy::mingw64_));
#elif defined(_MSC_VER) && defined(__clang__)
    SPY_ASSERT("the compiler is not nvcc", !(spy::compiler == spy::nvcc_));
    SPY_ASSERT("the compiler is not msvc", !(spy::compiler == spy::msvc_));
    SPY_ASSERT("the compiler is clang-cl", spy::compiler == spy::clangcl_);
    SPY_ASSERT("the compiler is not icc", !(spy::compiler == spy::intel_));
    SPY_ASSERT("the compiler is not dpc++", !(spy::compiler == spy::dpcpp_));
    SPY_ASSERT("the compiler is not clang", !(spy::compiler == spy::clang_));
    SPY_ASSERT("the compiler is not g++", !(spy::compiler == spy::gcc_));
    SPY_ASSERT("the compiler is not emscripten", !(spy::compiler == spy::emscripten_));
    SPY_ASSERT("the compiler is not mingw32", !(spy::compiler == spy::mingw32_));
    SPY_ASSERT("the compiler is not mingw64", !(spy::compiler == spy::mingw64_));
#elif defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC) || defined(__ECC)
    SPY_ASSERT("the compiler is not nvcc", !(spy::compiler == spy::nvcc_));
    SPY_ASSERT("the compiler is not msvc", !(spy::compiler == spy::msvc_));
    SPY_ASSERT("the compiler is not clang-cl", !(spy::compiler == spy::clangcl_));
    SPY_ASSERT("the compiler is icc", spy::compiler == spy::intel_);
    SPY_ASSERT("the compiler is not dpc++", !(spy::compiler == spy::dpcpp_));
    SPY_ASSERT("the compiler is not clang", !(spy::compiler == spy::clang_));
    SPY_ASSERT("the compiler is not g++", !(spy::compiler == spy::gcc_));
    SPY_ASSERT("the compiler is not emscripten", !(spy::compiler == spy::emscripten_));
    SPY_ASSERT("the compiler is not mingw32", !(spy::compiler == spy::mingw32_));
    SPY_ASSERT("the compiler is not mingw64", !(spy::compiler == spy::mingw64_));
#elif defined(__INTEL_LLVM_COMPILER)
    SPY_ASSERT("the compiler is not nvcc", !(spy::compiler == spy::nvcc_));
    SPY_ASSERT("the compiler is not msvc", !(spy::compiler == spy::msvc_));
    SPY_ASSERT("the compiler is not clang-cl", !(spy::compiler == spy::clangcl_));
    SPY_ASSERT("the compiler is not icc", !(spy::compiler == spy::intel_));
    SPY_ASSERT("the compiler is dpc++", spy::compiler == spy::dpcpp_);
    SPY_ASSERT("the compiler is not clang", !(spy::compiler == spy::clang_));
    SPY_ASSERT("the compiler is not g++", !(spy::compiler == spy::gcc_));
    SPY_ASSERT("the compiler is not emscripten", !(spy::compiler == spy::emscripten_));
    SPY_ASSERT("the compiler is not mingw32", !(spy::compiler == spy::mingw32_));
    SPY_ASSERT("the compiler is not mingw64", !(spy::compiler == spy::mingw64_));
#elif defined(__EMSCRIPTEN__)
    SPY_ASSERT("the compiler is not nvcc", !(spy::compiler == spy::nvcc_));
    SPY_ASSERT("the compiler is not msvc", !(spy::compiler == spy::msvc_));
    SPY_ASSERT("the compiler is not clang-cl", !(spy::compiler == spy::clangcl_));
    SPY_ASSERT("the compiler is not icc", !(spy::compiler == spy::intel_));
    SPY_ASSERT("the compiler is not dpc++", !(spy::compiler == spy::dpcpp_));
    SPY_ASSERT("the compiler is not clang", !(spy::compiler == spy::clang_));
    SPY_ASSERT("the compiler is not g++", !(spy::compiler == spy::gcc_));
    SPY_ASSERT("the compiler is emscripten", spy::compiler == spy::emscripten_);
#elif defined(__clang__)
    SPY_ASSERT("the compiler is not nvcc", !(spy::compiler == spy::nvcc_));
    SPY_ASSERT("the compiler is not msvc", !(spy::compiler == spy::msvc_));
    SPY_ASSERT("the compiler is not clang-cl", !(spy::compiler == spy::clangcl_));
    SPY_ASSERT("the compiler is not icc", !(spy::compiler == spy::intel_));
    SPY_ASSERT("the compiler is not dpc++", !(spy::compiler == spy::dpcpp_));
    SPY_ASSERT("the compiler is clang", spy::compiler == spy::clang_);
    SPY_ASSERT("the compiler is not g++", !(spy::compiler == spy::gcc_));
    SPY_ASSERT("the compiler is not emscripten", !(spy::compiler == spy::emscripten_));
    SPY_ASSERT("the compiler is not mingw32", !(spy::compiler == spy::mingw32_));
    SPY_ASSERT("the compiler is not mingw64", !(spy::compiler == spy::mingw64_));
#elif defined(__GNUC__)
    SPY_ASSERT("the compiler is not nvcc", !(spy::compiler == spy::nvcc_));
    SPY_ASSERT("the compiler is not msvc", !(spy::compiler == spy::msvc_));
    SPY_ASSERT("the compiler is not clang-cl", !(spy::compiler == spy::clangcl_));
    SPY_ASSERT("the compiler is not icc", !(spy::compiler == spy::intel_));
    SPY_ASSERT("the compiler is not dpc++", !(spy::compiler == spy::dpcpp_));
    SPY_ASSERT("the compiler is not clang", !(spy::compiler == spy::clang_));
    SPY_ASSERT("the compiler is g++", spy::compiler == spy::gcc_);
    SPY_ASSERT("the compiler is not emscripten", !(spy::compiler == spy::emscripten_));
    SPY_ASSERT("the compiler is not mingw32", !(spy::compiler == spy::mingw32_));
    SPY_ASSERT("the compiler is not mingw64", !(spy::compiler == spy::mingw64_));
#endif
  }
  std::cout << "Detected compiler: " << spy::compiler << std::endl;

  std::cout << "== detected compiler version is correct\n";
  {
    using namespace spy::literal;

#if defined(__NVCC__)
    SPY_ASSERT("the version is at least nvcc 6.0", spy::compiler >= 6'0_nvcc);
    SPY_ASSERT("the version is under msvc 19.5", !(spy::compiler >= 19'5_msvc));
    SPY_ASSERT("the version is under clang-cl 3.9", !(spy::compiler >= 3'9_clangcl));
    SPY_ASSERT("the version is under icc 19", !(spy::compiler >= 19_intel));
    SPY_ASSERT("the version is under dpc++ 2023.1", !(spy::compiler >= 2023'1_dpcpp));
    SPY_ASSERT("the version is under clang 3.9", !(spy::compiler >= 3'9_clang));
    SPY_ASSERT("the version is under g++ 7.2", !(spy::compiler >= 7'2_gcc));
    SPY_ASSERT("the version is under emscripten 3.1", !(spy::compiler >= 3'1_em));
    SPY_ASSERT("the version is under mingw32 7.2", !(spy::compiler >= 7'2_mingw32));
    SPY_ASSERT("the version is under mingw64 7.2", !(spy::compiler >= 7'2_mingw64));
#elif defined(_MSC_VER) && !defined(__clang__)
    SPY_ASSERT("the version is under nvcc 6.0", !(spy::compiler >= 6'0_nvcc));
    SPY_ASSERT("the version is at least msvc 19.5", spy::compiler >= 19'5_msvc);
    SPY_ASSERT("the version is under clang-cl 3.9", !(spy::compiler >= 3'9_clangcl));
    SPY_ASSERT("the version is under icc 19", !(spy::compiler >= 19_intel));
    SPY_ASSERT("the version is under dpc++ 2023.1", !(spy::compiler >= 2023'1_dpcpp));
    SPY_ASSERT("the version is under clang 3.9", !(spy::compiler >= 3'9_clang));
    SPY_ASSERT("the version is under g++ 7.2", !(spy::compiler >= 7'2_gcc));
    SPY_ASSERT("the version is under emscripten 3.1", !(spy::compiler >= 3'1_em));
    SPY_ASSERT("the version is under mingw32 7.2", !(spy::compiler >= 7'2_mingw32));
    SPY_ASSERT("the version is under mingw64 7.2", !(spy::compiler >= 7'2_mingw64));
#elif defined(_MSC_VER) && !defined(__clang__)
    SPY_ASSERT("the version is under nvcc 6.0", !(spy::compiler >= 6'0_nvcc));
    SPY_ASSERT("the version is under msvc 19.5", !(spy::compiler >= 19'5_msvc));
    SPY_ASSERT("the version is at least clang-cl 3.9", spy::compiler >= 3'9_clangcl);
    SPY_ASSERT("the version is under icc 19", !(spy::compiler >= 19_intel));
    SPY_ASSERT("the version is under dpc++ 2023.1", !(spy::compiler >= 2023'1_dpcpp));
    SPY_ASSERT("the version is under clang 3.9", !(spy::compiler >= 3'9_clang));
    SPY_ASSERT("the version is under g++ 7.2", !(spy::compiler >= 7'2_gcc));
    SPY_ASSERT("the version is under emscripten 3.1", !(spy::compiler >= 3'1_em));
    SPY_ASSERT("the version is under mingw32 7.2", !(spy::compiler >= 7'2_mingw32));
    SPY_ASSERT("the version is under mingw64 7.2", !(spy::compiler >= 7'2_mingw64));
#elif defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC) || defined(__ECC)
    SPY_ASSERT("the version is under nvcc 6.0", !(spy::compiler >= 6'0_nvcc));
    SPY_ASSERT("the version is under msvc 19.5", !(spy::compiler >= 19'5_msvc));
    SPY_ASSERT("the version is under clang-cl 3.9", !(spy::compiler >= 3'9_clangcl));
    SPY_ASSERT("the version is at least icc 19", spy::compiler >= 19_intel);
    SPY_ASSERT("the version is under dpc++ 2023.1", !(spy::compiler >= 2023'1_dpcpp));
    SPY_ASSERT("the version is under clang 3.9", !(spy::compiler >= 3'9_clang));
    SPY_ASSERT("the version is under g++ 7.2", !(spy::compiler >= 7'2_gcc));
    SPY_ASSERT("the version is under emscripten 3.1", !(spy::compiler >= 3'1_em));
    SPY_ASSERT("the version is under mingw32 7.2", !(spy::compiler >= 7'2_mingw32));
    SPY_ASSERT("the version is under mingw64 7.2", !(spy::compiler >= 7'2_mingw64));
#elif defined(__INTEL_LLVM_COMPILER)
    SPY_ASSERT("the version is under nvcc 6.0", !(spy::compiler >= 6'0_nvcc));
    SPY_ASSERT("the version is under msvc 19.5", !(spy::compiler >= 19'5_msvc));
    SPY_ASSERT("the version is under clang-cl 3.9", !(spy::compiler >= 3'9_clangcl));
    SPY_ASSERT("the version is under icc 19", !(spy::compiler >= 19_intel));
    SPY_ASSERT("the version is at least dpc++ 2023.1", spy::compiler >= 2023'1_dpcpp);
    SPY_ASSERT("the version is under clang 3.9", !(spy::compiler >= 3'9_clang));
    SPY_ASSERT("the version is under g++ 7.2", !(spy::compiler >= 7'2_gcc));
    SPY_ASSERT("the version is under emscripten 3.1", !(spy::compiler >= 3'1_em));
    SPY_ASSERT("the version is under mingw32 7.2", !(spy::compiler >= 7'2_mingw32));
    SPY_ASSERT("the version is under mingw64 7.2", !(spy::compiler >= 7'2_mingw64));
#elif defined(__EMSCRIPTEN__)
    SPY_ASSERT("the version is under nvcc 6.0", !(spy::compiler >= 6'0_nvcc));
    SPY_ASSERT("the version is under msvc 19.5", !(spy::compiler >= 19'5_msvc));
    SPY_ASSERT("the version is under clang-cl 3.9", !(spy::compiler >= 3'9_clangcl));
    SPY_ASSERT("the version is under icc 19", !(spy::compiler >= 19_intel));
    SPY_ASSERT("the version is under dpc++ 2023.1", !(spy::compiler >= 2023'1_dpcpp));
    SPY_ASSERT("the version is under clang 3.9", !(spy::compiler >= 3'9_clang));
    SPY_ASSERT("the version is under g++ 7.2", !(spy::compiler >= 7'2_gcc));
    SPY_ASSERT("the version is at least emscripten 3.1", spy::compiler >= 3'1_em);
#elif defined(__clang__) && !defined(_MSC_VER)
    SPY_ASSERT("the version is under nvcc 6.0", !(spy::compiler >= 6'0_nvcc));
    SPY_ASSERT("the version is under msvc 19.5", !(spy::compiler >= 19'5_msvc));
    SPY_ASSERT("the version is under clang-cl 3.9", !(spy::compiler >= 3'9_clangcl));
    SPY_ASSERT("the version is under icc 19", !(spy::compiler >= 19_intel));
    SPY_ASSERT("the version is under dpc++ 2023.1", !(spy::compiler >= 2023'1_dpcpp));
    SPY_ASSERT("the version is at least clang 3.9", spy::compiler >= 3'9_clang);
    SPY_ASSERT("the version is under g++ 7.2", !(spy::compiler >= 7'2_gcc));
    SPY_ASSERT("the version is under emscripten 3.1", !(spy::compiler >= 3'1_em));
    SPY_ASSERT("the version is under mingw32 7.2", !(spy::compiler >= 7'2_mingw32));
    SPY_ASSERT("the version is under mingw64 7.2", !(spy::compiler >= 7'2_mingw64));
#elif defined(__MINGW32__) && !defined(__MINGW64__)
    SPY_ASSERT("the version is under nvcc 6.0", !(spy::compiler >= 6'0_nvcc));
    SPY_ASSERT("the version is under msvc 19.5", !(spy::compiler >= 19'5_msvc));
    SPY_ASSERT("the version is under clang-cl 3.9", !(spy::compiler >= 3'9_clangcl));
    SPY_ASSERT("the version is under icc 19", !(spy::compiler >= 19_intel));
    SPY_ASSERT("the version is under dpc++ 2023.1", !(spy::compiler >= 2023'1_dpcpp));
    SPY_ASSERT("the version is under clang 3.9", !(spy::compiler >= 3'9_clang));
    SPY_ASSERT("the version is under emscripten 3.1", !(spy::compiler >= 3'1_em));
    SPY_ASSERT("the version is at least mingw32 7.2", spy::compiler >= 7'2_mingw32);
    SPY_ASSERT("the version is under mingw64 7.2", !(spy::compiler >= 7'2_mingw64));
#elif defined(__MINGW32__) && defined(__MINGW64__)
    SPY_ASSERT("the version is under nvcc 6.0", !(spy::compiler >= 6'0_nvcc));
    SPY_ASSERT("the version is under msvc 19.5", !(spy::compiler >= 19'5_msvc));
    SPY_ASSERT("the version is under clang-cl 3.9", !(spy::compiler >= 3'9_clangcl));
    SPY_ASSERT("the version is under icc 19", !(spy::compiler >= 19_intel));
    SPY_ASSERT("the version is under dpc++ 2023.1", !(spy::compiler >= 2023'1_dpcpp));
    SPY_ASSERT("the version is under clang 3.9", !(spy::compiler >= 3'9_clang));
    SPY_ASSERT("the version is under g++ 7.2", !(spy::compiler >= 7'2_gcc));
    SPY_ASSERT("the version is under emscripten 3.1", !(spy::compiler >= 3'1_em));
    SPY_ASSERT("the version is under mingw32 7.2", !(spy::compiler >= 7'2_mingw32));
    SPY_ASSERT("the version is at least mingw64 7.2", spy::compiler >= 7'2_mingw64);
#elif defined(__GNUC__)
    SPY_ASSERT("the version is under nvcc 6.0", !(spy::compiler >= 6'0_nvcc));
    SPY_ASSERT("the version is under msvc 19.5", !(spy::compiler >= 19'5_msvc));
    SPY_ASSERT("the version is under clang-cl 3.9", !(spy::compiler >= 3'9_clangcl));
    SPY_ASSERT("the version is under icc 19", !(spy::compiler >= 19_intel));
    SPY_ASSERT("the version is under dpc++ 2023.1", !(spy::compiler >= 2023'1_dpcpp));
    SPY_ASSERT("the version is under clang 3.9", !(spy::compiler >= 3'9_clang));
    SPY_ASSERT("the version is at least g++ 7.2", spy::compiler >= 7'2_gcc);
    SPY_ASSERT("the version is under emscripten 3.1", !(spy::compiler >= 3'1_em));
#endif
  }

  std::cout << "== detected constexpr selection on exact compiler is correct\n";
  {
    using namespace spy::literal;

#if defined(__NVCC__)
    [[maybe_unused]] auto constexpr wrong_constexpr_behavior = 1'42'1337_nvcc;
#elif defined(_MSC_VER) && !defined(__clang__)
    [[maybe_unused]] auto constexpr wrong_constexpr_behavior = 1'42'1337_msvc;
#elif defined(_MSC_VER) && defined(__clang__)
    [[maybe_unused]] auto constexpr wrong_constexpr_behavior = 1'42'1337_clangcl;
#elif defined(__INTEL_LLVM_COMPILER)
    [[maybe_unused]] auto constexpr wrong_constexpr_behavior = 1'42'1337_dpcpp;
#elif defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC) || defined(__ECC)
    [[maybe_unused]] auto constexpr wrong_constexpr_behavior = 1'42'1337_intel;
#elif defined(__EMSCRIPTEN___)
    [[maybe_unused]] auto constexpr wrong_constexpr_behavior = 1'42'1337_em;
#elif defined(__clang__)
    [[maybe_unused]] auto constexpr wrong_constexpr_behavior = 1'42'1337_clang;
#elif defined(__GNUC__)
    [[maybe_unused]] auto constexpr wrong_constexpr_behavior = 1'42'1337_gcc;
#else
    [[maybe_unused]] auto constexpr wrong_constexpr_behavior = false;
#endif

    if constexpr(spy::compiler)
    {
      SPY_ASSERT("a version that does not match is turned down", !bool(wrong_constexpr_behavior));
    }
    else
    {
      SPY_ASSERT("a version that does not match selects nothing", bool(wrong_constexpr_behavior));
    }
  }
}
