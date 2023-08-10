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

extern size_t phy_memory_size; // 物理内存总大小

phys_addr_t translate_linear_address(struct mm_struct* mm, uintptr_t va);

bool read_physical_address(phys_addr_t pa, void* buffer, size_t size);

bool write_physical_address(phys_addr_t pa, void* buffer, size_t size);

bool read_process_memory(pid_t pid, uintptr_t addr, void* buffer, size_t size);

bool write_process_memory(pid_t pid, uintptr_t addr, void* buffer, size_t size);
