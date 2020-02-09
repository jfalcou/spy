//==================================================================================================
/*
  SPY - C++ Informations Broker
  Copyright 2020 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
 */
//==================================================================================================
#include <spy/spy.hpp>
#include <cassert>

int main()
{
  std::cout << "Check that detected architecture is correct: " << std::endl;
  {
#if defined(i386) || defined(__i386__) || defined(__i486__) || defined(__i586__) ||                \
    defined(__i686__) || defined(__i386) || defined(_M_IX86) || defined(_X86_) ||                  \
    defined(__THW_INTEL__) || defined(__I86__) || defined(__INTEL__)
    assert(  spy::architecture == spy::x86_   );
    assert( !spy::architecture == spy::amd64_ );
    assert( !spy::architecture == spy::ppc_   );
    assert( !spy::architecture == spy::arm_   );
#elif defined(__x86_64) || defined(__x86_64__) || defined(__amd64__) || defined(__amd64) || defined(_M_X64)
    assert( !spy::architecture == spy::x86_   );
    assert(  spy::architecture == spy::amd64_ );
    assert( !spy::architecture == spy::ppc_   );
    assert( !spy::architecture == spy::arm_   );
#elif defined(__powerpc) || defined(__powerpc__) || defined(__POWERPC__) || defined(__ppc__) ||     \
      defined(_M_PPC) || defined(_ARCH_PPC) || defined(__PPCGECKO__) || defined(__PPCBROADWAY__) || \
      defined(_XENON)
    assert( !spy::architecture == spy::x86_   );
    assert( !spy::architecture == spy::amd64_ );
    assert(  spy::architecture == spy::ppc_   );
    assert( !spy::architecture == spy::arm_   );
#elif defined(__arm__) || defined(__arm64) || defined(__thumb__) || defined(__TARGET_ARCH_ARM) ||   \
      defined(__TARGET_ARCH_THUMB) || defined(_M_ARM)
    assert( !spy::architecture == spy::x86_   );
    assert( !spy::architecture == spy::amd64_ );
    assert( !spy::architecture == spy::ppc_   );
    assert(  spy::architecture == spy::arm_   );
#else
    assert( !spy::architecture == spy::x86_   );
    assert( !spy::architecture == spy::amd64_ );
    assert( !spy::architecture == spy::ppc_   );
    assert( !spy::architecture == spy::arm_   );
#endif

    std::cout << "X86   status: " << std::boolalpha << (spy::architecture == spy::x86_  ) << std::endl;
    std::cout << "AMD64 status: " << std::boolalpha << (spy::architecture == spy::amd64_) << std::endl;
    std::cout << "PPC   status: " << std::boolalpha << (spy::architecture == spy::ppc_  ) << std::endl;
    std::cout << "ARM   status: " << std::boolalpha << (spy::architecture == spy::arm_  ) << std::endl;
  }
  std::cout << "Done." << std::endl;
}
