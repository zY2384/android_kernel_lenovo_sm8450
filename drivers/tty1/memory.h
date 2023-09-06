#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/tty.h>
#include <linux/io.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/version.h>

#include <asm/cpu.h>
#include <asm/io.h>
#include <asm/page.h>
#include <asm/pgtable.h>
#include "vapi.h"

#ifdef USER_MODULE
extern size_t phy_memory_size; // 物理内存总大小
#endif

bool read_process_memory(pid_t pid, uintptr_t addr, void* buffer, size_t size);

bool write_process_memory(pid_t pid, uintptr_t addr, void* buffer, size_t size);
