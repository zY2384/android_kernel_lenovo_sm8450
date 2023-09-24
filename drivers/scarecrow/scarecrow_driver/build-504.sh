#! /bin/bash

#clang环境变量
export PATH=$PATH:/root/android-kernel/prebuilts-master/clang/host/linux-x86/clang-r416183b/bin

#编译前清缓存
rm modules.order *.mod.o *.lto.o *.mod *.ko  *.o  Module.symvers .*.mod.o.cmd .*.ko.cmd .*.o.cmd *.o.cmd *.cmd .tmp_versions .thinlto-cache .Module.symvers.cmd .modules.order.cmd .*.mod.cmd -rf

#开始编模块 该命令只有两个变量 CROSS_COMPILE和-C , CROSS_COMPILE表示gcc目录，-C表示内核编译完成的目录
make CROSS_COMPILE=/root/aarch64-linux-android-4.9/bin/aarch64-linux-android- CLANG_TRIPLE=aarch64-linux-gnu- LLVM=1 LLVM_IAS=1 ARCH=arm64 -C /root/android-kernel-504/out M=$PWD

