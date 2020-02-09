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
  std::cout << "Check that detected libc is correct: " << std::flush;
  {
#if defined(__cloudlibc__)
    assert(  spy::libc == spy::cloudabi_ );
    assert( !spy::libc == spy::uc_       );
    assert( !spy::libc == spy::vms_      );
    assert( !spy::libc == spy::zos_      );
    assert( !spy::libc == spy::gnu_      );
#elif defined(__UCLIBC__)
    assert( !spy::libc == spy::cloudabi_ );
    assert(  spy::libc == spy::uc_       );
    assert( !spy::libc == spy::vms_      );
    assert( !spy::libc == spy::zos_      );
    assert( !spy::libc == spy::gnu_      );
#elif defined(__CRTL_VER)
    assert( !spy::libc == spy::cloudabi_ );
    assert( !spy::libc == spy::uc_       );
    assert(  spy::libc == spy::vms_      );
    assert( !spy::libc == spy::zos_      );
    assert( !spy::libc == spy::gnu_      );
#elif defined(__LIBREL__)
    assert( !spy::libc == spy::cloudabi_ );
    assert( !spy::libc == spy::uc_       );
    assert( !spy::libc == spy::vms_      );
    assert(  spy::libc == spy::zos_      );
    assert( !spy::libc == spy::gnu_      );
#elif defined(__GLIBC__) || defined(__GNU_LIBRARY__)
    assert( !spy::libc == spy::cloudabi_ );
    assert( !spy::libc == spy::uc_       );
    assert( !spy::libc == spy::vms_      );
    assert( !spy::libc == spy::zos_      );
    assert(  spy::libc == spy::gnu_      );
#else
    assert( !spy::libc == spy::cloudabi_ );
    assert( !spy::libc == spy::uc_       );
    assert( !spy::libc == spy::vms_      );
    assert( !spy::libc == spy::zos_      );
    assert( !spy::libc == spy::gnu_      );
#endif
  }
  std::cout << "Done." << std::endl;

  std::cout << "Check that detected constexpr selection on exact libc is correct: " << std::flush;
  {
    using namespace spy::literal;

#if defined(__cloudlibc__)
    auto const wrong_constexpr_behavior = 1'42'1337_cloud;
#elif defined(__UCLIBC__)
    auto const wrong_constexpr_behavior = 1'42'1337_uc;
#elif defined(__CRTL_VER)
    auto const wrong_constexpr_behavior = 1'42'1337_vms;
#elif defined(__LIBREL__)
    auto const wrong_constexpr_behavior = 1'42'1337_zos;
#elif defined(__GLIBC__) || defined(__GNU_LIBRARY__)
    auto const wrong_constexpr_behavior = 1'42'1337_gnu;
#else
    auto const wrong_constexpr_behavior = false;
#endif

    if constexpr(spy::libc)
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
