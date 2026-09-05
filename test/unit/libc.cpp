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
  std::cout << "== detected libc is correct\n";
  {
#if defined(__cloudlibc__)
    SPY_ASSERT("the libc is cloudabi", spy::libc == spy::cloudabi_);
    SPY_ASSERT("the libc is not uClibc", !(spy::libc == spy::uc_));
    SPY_ASSERT("the libc is not vms", !(spy::libc == spy::vms_));
    SPY_ASSERT("the libc is not z/OS", !(spy::libc == spy::zos_));
    SPY_ASSERT("the libc is not glibc", !(spy::libc == spy::gnu_));
#elif defined(__UCLIBC__)
    SPY_ASSERT("the libc is not cloudabi", !(spy::libc == spy::cloudabi_));
    SPY_ASSERT("the libc is uClibc", spy::libc == spy::uc_);
    SPY_ASSERT("the libc is not vms", !(spy::libc == spy::vms_));
    SPY_ASSERT("the libc is not z/OS", !(spy::libc == spy::zos_));
    SPY_ASSERT("the libc is not glibc", !(spy::libc == spy::gnu_));
#elif defined(__CRTL_VER)
    SPY_ASSERT("the libc is not cloudabi", !(spy::libc == spy::cloudabi_));
    SPY_ASSERT("the libc is not uClibc", !(spy::libc == spy::uc_));
    SPY_ASSERT("the libc is vms", spy::libc == spy::vms_);
    SPY_ASSERT("the libc is not z/OS", !(spy::libc == spy::zos_));
    SPY_ASSERT("the libc is not glibc", !(spy::libc == spy::gnu_));
#elif defined(__LIBREL__)
    SPY_ASSERT("the libc is not cloudabi", !(spy::libc == spy::cloudabi_));
    SPY_ASSERT("the libc is not uClibc", !(spy::libc == spy::uc_));
    SPY_ASSERT("the libc is not vms", !(spy::libc == spy::vms_));
    SPY_ASSERT("the libc is z/OS", spy::libc == spy::zos_);
    SPY_ASSERT("the libc is not glibc", !(spy::libc == spy::gnu_));
#elif defined(__GLIBC__) || defined(__GNU_LIBRARY__)
    SPY_ASSERT("the libc is not cloudabi", !(spy::libc == spy::cloudabi_));
    SPY_ASSERT("the libc is not uClibc", !(spy::libc == spy::uc_));
    SPY_ASSERT("the libc is not vms", !(spy::libc == spy::vms_));
    SPY_ASSERT("the libc is not z/OS", !(spy::libc == spy::zos_));
    SPY_ASSERT("the libc is glibc", spy::libc == spy::gnu_);
#else
    SPY_ASSERT("the libc is not cloudabi", !(spy::libc == spy::cloudabi_));
    SPY_ASSERT("the libc is not uClibc", !(spy::libc == spy::uc_));
    SPY_ASSERT("the libc is not vms", !(spy::libc == spy::vms_));
    SPY_ASSERT("the libc is not z/OS", !(spy::libc == spy::zos_));
    SPY_ASSERT("the libc is not glibc", !(spy::libc == spy::gnu_));
#endif
  }
  std::cout << "Detected libc: " << spy::libc << std::endl;

  std::cout << "== detected constexpr selection on exact libc is correct\n";
  {
    using namespace spy::literal;

#if defined(__cloudlibc__)
    [[maybe_unused]] auto constexpr wrong_constexpr_behavior = 1'42'1337_cloud;
#elif defined(__UCLIBC__)
    [[maybe_unused]] auto constexpr wrong_constexpr_behavior = 1'42'1337_uc;
#elif defined(__CRTL_VER)
    [[maybe_unused]] auto constexpr wrong_constexpr_behavior = 1'42'1337_vms;
#elif defined(__LIBREL__)
    [[maybe_unused]] auto constexpr wrong_constexpr_behavior = 1'42'1337_zos;
#elif defined(__GLIBC__) || defined(__GNU_LIBRARY__)
    [[maybe_unused]] auto constexpr wrong_constexpr_behavior = 1'42'1337_gnu;
#else
    [[maybe_unused]] auto constexpr wrong_constexpr_behavior = false;
#endif

    if constexpr(spy::libc)
    {
      SPY_ASSERT("a version that does not match is turned down", !bool(wrong_constexpr_behavior));
    }
    else
    {
      SPY_ASSERT("a version that does not match selects nothing", bool(wrong_constexpr_behavior));
    }
  }
}
