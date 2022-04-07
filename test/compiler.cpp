//==================================================================================================
/**
  SPY - C++ Informations Broker
  Copyright : SPY Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <spy/spy.hpp>
#include <iostream>
#include <cassert>

int main()
{
  std::cout << "Check that detected compiler is correct: " << std::flush;
  {
#if defined(_MSC_VER)
    assert(  spy::compiler == spy::msvc_      );
    assert( !(spy::compiler == spy::intel_    ));
    assert( !(spy::compiler == spy::clang_    ));
    assert( !(spy::compiler == spy::gcc_      ));
    assert( !(spy::compiler == spy::emscripten_));
#elif defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC) || defined(__ECC)
    assert( !(spy::compiler == spy::msvc_     ));
    assert(  spy::compiler == spy::intel_     );
    assert( !(spy::compiler == spy::clang_    ));
    assert( !(spy::compiler == spy::gcc_      ));
    assert( !(spy::compiler == spy::emscripten_));
#elif defined(__EMSCRIPTEN__)
    assert( !(spy::compiler == spy::msvc_     ));
    assert( !(spy::compiler == spy::intel_    ));
    assert( !(spy::compiler == spy::clang_    ));
    assert( !(spy::compiler == spy::gcc_      ));
    assert(  spy::compiler == spy::emscripten_);
#elif defined(__clang__)
    assert( !(spy::compiler == spy::msvc_     ));
    assert( !(spy::compiler == spy::intel_    ));
    assert(  spy::compiler == spy::clang_     );
    assert( !(spy::compiler == spy::gcc_      ));
    assert( !(spy::compiler == spy::emscripten_));
#elif defined(__GNUC__)
    assert( !(spy::compiler == spy::msvc_     ));
    assert( !(spy::compiler == spy::intel_    ));
    assert( !(spy::compiler == spy::clang_    ));
    assert(  spy::compiler == spy::gcc_       );
    assert( !(spy::compiler == spy::emscripten_));
#endif
  }
  std::cout << "Done." << std::endl;
  std::cout << "Detected compiler: " << spy::compiler << std::endl;

  std::cout << "Check that detected compiler version is correct: " << std::flush;
  {
    using namespace spy::literal;

#if defined(_MSC_VER)
    assert(  spy::compiler >= 19'5_msvc );
    assert( !(spy::compiler >= 19_intel ));
    assert( !(spy::compiler >= 3'9_clang));
    assert( !(spy::compiler >= 7'2_gcc  ));
    assert( !(spy::compiler >= 3'1_em   ));
#elif defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC) || defined(__ECC)
    assert( !(spy::compiler >= 19'5_msvc));
    assert(  spy::compiler >= 19_intel  );
    assert( !(spy::compiler >= 3'9_clang));
    assert( !(spy::compiler >= 7'2_gcc  ));
    assert( !(spy::compiler >= 3'1_em   ));
#elif defined(__EMSCRIPTEN___)
    assert( !(spy::compiler >= 19'5_msvc));
    assert( !(spy::compiler >= 19_intel ));
    assert( !(spy::compiler >= 3'9_clang));
    assert( !(spy::compiler >= 7'2_gcc  ));
    assert(  spy::compiler >= 3'1_em    );
#elif defined(__clang__)
    assert( !(spy::compiler >= 19'5_msvc));
    assert( !(spy::compiler >= 19_intel ));
    assert(  spy::compiler >= 3'9_clang );
    assert( !(spy::compiler >= 7'2_gcc  ));
    assert( !(spy::compiler >= 3'1_em   ));
#elif defined(__GNUC__)
    assert( !(spy::compiler >= 19'5_msvc));
    assert( !(spy::compiler >= 19_intel ));
    assert( !(spy::compiler >= 3'9_clang));
    assert(  spy::compiler >= 7'2_gcc   );
    assert( !(spy::compiler >= 3'1_em   ));
#endif
  }
  std::cout << "Done." << std::endl;

  std::cout << "Check that detected constexpr selection on exact compiler is correct: " << std::flush;
  {
    using namespace spy::literal;

#if defined(_MSC_VER)
    [[maybe_unused]] auto constexpr wrong_constexpr_behavior = 1'42'1337_msvc;
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
      assert( !bool(wrong_constexpr_behavior) );
    }
    else
    {
      assert( bool(wrong_constexpr_behavior) );
    }
  }
  std::cout << "Done." << std::endl;
}
