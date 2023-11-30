#! /bin/bash
export PATH=$PATH:/root/android-kernel-601/prebuilts/clang/host/linux-x86/clang-r487747c/bin
# export PATH=$PATH:/root/android-kernel-510/prebuilts-master/clang/host/linux-x86/clang-r383902/bin/
rm modules.order *.mod.o *.lto.o *.mod *.ko  *.o  Module.symvers .*.mod.o.cmd .*.ko.cmd .*.o.cmd *.o.cmd *.cmd .tmp_versions .thinlto-cache .Module.symvers.cmd .modules.order.cmd .*.mod.cmd -rf

# make CROSS_COMPILE=/root/aarch64-linux-android-4.9/bin/aarch64-linux-android- CLANG_TRIPLE=aarch64-linux-gnu- LLVM=1 LLVM_IAS=1 ARCH=arm64 -C /root/android-kernel/out/android12-5.10/common M=$PWD
make CROSS_COMPILE=/root/aarch64-linux-android-4.9/bin/aarch64-linux-android- CLANG_TRIPLE=aarch64-linux-gnu- LLVM=1 LLVM_IAS=1 ARCH=arm64 -C /root/android-kernel-601/out/cache/last_build/common M=$PWD

