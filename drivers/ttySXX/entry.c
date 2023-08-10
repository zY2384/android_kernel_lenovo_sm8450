#include <linux/module.h>
#include <linux/tty.h>
#include <linux/miscdevice.h>
#include "comm.h"
#include "memory.h"
#include "process.h"
#include "rname.h"
#include <linux/sysinfo.h>

/*
    版本v1.0
    修复读写时内核崩溃
*/

#ifdef USER_MODULE
size_t phy_memory_size; // 物理内存总大小
static int init_phy_memory_size(void) {
	struct sysinfo sysinfo_size;
	struct sysinfo *si;
	si = kmalloc(sizeof(sysinfo_size), GFP_KERNEL);
	si_meminfo(si);	
	uint64_t sav_total = 0;
	uint64_t  bitcount = 0;	
	uint64_t mem_unit = si->mem_unit;
	uint64_t mem_total = si->totalram;
	while (mem_unit > 1) {
		bitcount++;
		mem_unit >>= 1;
		sav_total = mem_total;
		mem_total <<= 1;
		if (mem_total < sav_total) {
			kfree(si);
			return 0;
		}
	}
	si->totalram <<= bitcount;
	phy_memory_size = __pa(si->totalram);
	kfree(si);
	return 1;
}
#else
static int init_phy_memory_size(void) {
    return 1;
}
#endif

int dispatch_open(struct inode *node, struct file *file)
{
    return 0;
}

int dispatch_close(struct inode *node, struct file *file)
{
    return 0;
}

COPY_MEMORY *cm;
size_t cm_size;
MODULE_BASE *mb;
size_t mb_size;
char *module_name;
#define MODULE_SIZE 0x200

static void init_struct(void)
{
    COPY_MEMORY cms;
    MODULE_BASE mbs;
    cm_size = sizeof(cms);
    mb_size = sizeof(mbs);
    cm = kmalloc(cm_size, GFP_KERNEL);
    mb = kmalloc(mb_size, GFP_KERNEL);   
    module_name = kmalloc(MODULE_SIZE, GFP_KERNEL);   
}

static void exit_struct(void)
{
    kfree(cm);
    kfree(mb);
    kfree(module_name);
}

long __gcc_except_table_fini_array_preinit_array(struct file* const file, unsigned int const cmd, unsigned long const arg)
{    
    switch (cmd)
    {
        case OP_INIT_KEY:
            {
                return OP_INIT_KEY;
            }
            break;
        case OP_READ_MEM:
            {
                if (copy_from_user(cm, (void __user*)arg, cm_size) != 0) {
                    return -1;
                }
                if (read_process_memory(cm->pid, cm->addr, cm->buffer, cm->size) == false) {
                    return -1;
                }
            }
            break;
        case OP_WRITE_MEM:
            {
                if (copy_from_user(cm, (void __user*)arg, cm_size) != 0) {
                    return -1;
                }
                if (write_process_memory(cm->pid, cm->addr, cm->buffer, cm->size) == false) {
                    return -1;
                }
            }
            break;
        case OP_MODULE_BASE:
            {
                memset(module_name, 0, MODULE_SIZE);
                if (copy_from_user(mb, (void __user*)arg, mb_size) != 0 
                ||  copy_from_user(module_name, (void __user*)mb->name, MODULE_SIZE) !=0) {
                    return -1;
                }
                mb->base = get_module_base(mb->pid, module_name);
                if (copy_to_user((void __user*)arg, mb, mb_size) !=0) {
                    return -1;
                }
            }
            break;
        default:
            break;
    }
    return 0;
}

struct file_operations dispatch_functions = {
    .owner   = THIS_MODULE,
    .open    = dispatch_open,
    .release = dispatch_close,
    .unlocked_ioctl = __gcc_except_table_fini_array_preinit_array,
};
char DEVICE_NAME[8];
struct miscdevice misc = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = DEVICE_NAME,
	.fops = &dispatch_functions,
};

int __init driver_entry(void)
{
    if (init_phy_memory_size())
    {
        printk("Welcome to my kingdom");
    }
    init_struct();
    dispatch_name(DEVICE_NAME, 79, 99);
	misc_register(&misc);
	return 0;
}

void __exit driver_unload(void)
{
	misc_deregister(&misc);
	exit_struct();
}

module_init(driver_entry);
module_exit(driver_unload);

MODULE_DESCRIPTION("Kernel for Android");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Linux");
