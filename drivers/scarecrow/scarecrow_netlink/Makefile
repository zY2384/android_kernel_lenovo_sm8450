ccflags-y += -Wno-implicit-function-declaration -Wno-strict-prototypes -Wno-int-conversion -Wno-gcc-compat -Wno-declaration-after-statement -O3
MODULE_NAME := scarecrow
RESMAN_CORE_OBJS := main.o
RESMAN_GLUE_OBJS := memory.o process.o
$(MODULE_NAME)-objs:=$(RESMAN_CORE_OBJS) $(RESMAN_GLUE_OBJS)
obj-m := scarecrow.o
KER=/root/android-kernel/out/android12-5.10/common

all:
		@rm -rf *.ko
			@make -C $(KER) M=$(PWD) ARCH=arm64 SUBARCH=arm64 modules
				@rm -rf *.mod* *.sym* .*.cmd *.order *.o

clean:
		@rm -rf *.ko
			@rm -rf *.mod* *.sym* .*.cmd *.order *.o
