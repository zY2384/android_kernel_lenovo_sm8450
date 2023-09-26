#! /bin/bash
#export PATH=$PATH:/root/android-kernel/prebuilts-master/clang/host/linux-x86/clang-r416183b/bin
export PATH=$PATH:/root/android-kernel-515/prebuilts/clang/host/linux-x86/clang-r450784e/bin

rm modules.order *.mod.o *.lto.o *.mod *.ko  *.o  Module.symvers .*.mod.o.cmd .*.ko.cmd .*.o.cmd *.o.cmd *.cmd .tmp_versions .thinlto-cache .Module.symvers.cmd .modules.order.cmd .*.mod.cmd built-in.a .built-in.a.cmd .scarecrow.usyms.cmd scarecrow.usyms -rf

make CROSS_COMPILE=/root/aarch64-linux-android-4.9/bin/aarch64-linux-android- CLANG_TRIPLE=aarch64-linux-gnu- LLVM=1 LLVM_IAS=1 ARCH=arm64 -C /root/android-kernel-515/out/android13-5.15/common M=$PWD

