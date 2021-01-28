//==================================================================================================
/*
  SPY - C++ Informations Broker
  Copyright 2020-2021 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
 */
//==================================================================================================
#include <spy/spy.hpp>
#include <iostream>
#include <cassert>

int main()
{
  std::cout << "Check that detected compiler is correct: " << std::flush;
  {
#if defined(_MSC_VER)
    assert(  spy::compiler == spy::msvc_   );
    assert( !spy::compiler == spy::intel_  );
    assert( !spy::compiler == spy::clang_  );
    assert( !spy::compiler == spy::gcc_    );
#elif defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC) || defined(__ECC)
    assert( !spy::compiler == spy::msvc_   );
    assert(  spy::compiler == spy::intel_  );
    assert( !spy::compiler == spy::clang_  );
    assert( !spy::compiler == spy::gcc_    );
#elif defined(__clang__)
    assert( !spy::compiler == spy::msvc_   );
    assert( !spy::compiler == spy::intel_  );
    assert(  spy::compiler == spy::clang_  );
    assert( !spy::compiler == spy::gcc_    );
#elif defined(__GNUC__)
    assert( !spy::compiler == spy::msvc_   );
    assert( !spy::compiler == spy::intel_  );
    assert( !spy::compiler == spy::clang_  );
    assert(  spy::compiler == spy::gcc_    );
#endif
  }
  std::cout << "Done." << std::endl;

  std::cout << "Check that detected compiler version is correct: " << std::flush;
  {
    using namespace spy::literal;

#if defined(_MSC_VER)
    assert(  spy::compiler >= 19'5_msvc );
    assert( !spy::compiler >= 19_intel  );
    assert( !spy::compiler >= 3'9_clang );
    assert( !spy::compiler >= 7'2_gcc   );
#elif defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC) || defined(__ECC)
    assert( !spy::compiler >= 19'5_msvc );
    assert(  spy::compiler >= 19_intel  );
    assert( !spy::compiler >= 3'9_clang );
    assert( !spy::compiler >= 7'2_gcc   );
#elif defined(__clang__)
    assert( !spy::compiler >= 19'5_msvc );
    assert( !spy::compiler >= 19_intel  );
    assert(  spy::compiler >= 3'9_clang );
    assert( !spy::compiler >= 7'2_gcc   );
#elif defined(__GNUC__)
    assert( !spy::compiler >= 19'5_msvc );
    assert( !spy::compiler >= 19_intel  );
    assert( !spy::compiler >= 3'9_clang );
    assert(  spy::compiler >= 7'2_gcc   );
#endif
  }
  std::cout << "Done." << std::endl;

  std::cout << "Check that detected constexpr selection on exact compiler is correct: " << std::flush;
  {
    using namespace spy::literal;

#if defined(_MSC_VER)
    auto const wrong_constexpr_behavior = 1'42'1337_msvc;
#elif defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC) || defined(__ECC)
    auto const wrong_constexpr_behavior = 1'42'1337_intel;
#elif defined(__clang__)
    auto const wrong_constexpr_behavior = 1'42'1337_clang;
#elif defined(__GNUC__)
    auto const wrong_constexpr_behavior = 1'42'1337_gcc;
#else
    auto const wrong_constexpr_behavior = false;
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
