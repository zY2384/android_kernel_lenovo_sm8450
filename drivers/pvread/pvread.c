#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kallsyms.h> 
#include <linux/syscalls.h>
#include <asm/unistd.h>
#include <asm/ptrace.h> 

void (*update_mapping_prot)(phys_addr_t phys, unsigned long virt, phys_addr_t size, pgprot_t prot);

// .rodata segment 区间
unsigned long start_rodata;
unsigned long init_begin;

#define section_size init_begin - start_rodata

static unsigned long *__sys_call_table;

typedef long (*syscall_fn_t)(const struct pt_regs *regs);

#ifndef __NR_mkdirat
#define __NR_mkdirat 34
#endif

//用于保存原始的 mkdir 系统调用
static syscall_fn_t orig_mkdir;

//mkdir hook 函数
asmlinkage long mkdir_hook(const struct pt_regs *regs)
{
    pr_alert("hello mkdir sys_call\n");
    orig_mkdir(regs);
    return 0;
}

//修改指定内核地址范围的内存属性为只读
static inline void protect_memory(void)
{
	update_mapping_prot(__pa_symbol(start_rodata), (unsigned long)start_rodata,
			section_size, PAGE_KERNEL_RO);
}

//修改指定内核地址范围的内存属性为可读可写等
static inline void unprotect_memory(void)
{
	update_mapping_prot(__pa_symbol(start_rodata), (unsigned long)start_rodata,
			section_size, PAGE_KERNEL);
}
	
static int __init lkm_init(void)
{
    update_mapping_prot = (void *)kallsyms_lookup_name("update_mapping_prot");

	start_rodata = (unsigned long)kallsyms_lookup_name("__start_rodata");
	init_begin = (unsigned long)kallsyms_lookup_name("__init_begin");

    __sys_call_table = (unsigned long *)kallsyms_lookup_name("sys_call_table");
    if (!__sys_call_table)
		return -1;

    pr_alert("__sys_call_table = %lx\n", __sys_call_table);
    
    //保存原始的系统调用：mkdir
	orig_mkdir = (syscall_fn_t)__sys_call_table[__NR_mkdirat];

	//hook 系统调用表表项：sys_call_table[__NR_mkdirat]
    unprotect_memory();
    __sys_call_table[__NR_mkdirat] = (unsigned long)mkdir_hook;
    protect_memory();

    pr_alert("lkm_init\n");

	return 0;
}

static void __exit lkm_exit(void)
{
	//模块卸载时恢复原来的mkdir系统调用
	unprotect_memory();
    __sys_call_table[__NR_mkdirat] = (unsigned long)orig_mkdir;
    protect_memory();

    pr_alert("lkm_exit\n");
}

module_init(lkm_init);
module_exit(lkm_exit);

MODULE_LICENSE("GPL");
