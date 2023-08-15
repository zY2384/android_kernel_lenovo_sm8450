#! /bin/bash
export PATH=$PATH:/root/android-kernel-510/prebuilts-master/clang/host/linux-x86/clang-r416183b/bin
# export PATH=$PATH:/root/android-kernel-510/prebuilts-master/clang/host/linux-x86/clang-r383902/bin/
make CROSS_COMPILE=/root/aarch64-linux-android-4.9/bin/aarch64-linux-android- CLANG_TRIPLE=aarch64-linux-gnu- LLVM=1 LLVM_IAS=1 ARCH=arm64 -C /root/android-kernel-510/out/android12-5.10/common M=$PWD

