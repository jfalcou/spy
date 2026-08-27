##==================================================================================================
##  SPY - C++ Informations Broker
##  Copyright : SPY Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================
#!/bin/sh

# qemu 10 accepts v=true on the rv64 model and does nothing with it - the first vector
# instruction traps. Only max exposes RVV, and the extensions this target does not have are
# switched back off so the emulated hardware still matches -march=rv64gcv.
qemu-riscv64 --cpu max,vlen=128,zfh=false,zvfh=false $@
