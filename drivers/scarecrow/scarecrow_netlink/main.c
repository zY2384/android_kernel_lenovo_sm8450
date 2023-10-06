#include <linux/module.h>
#include <linux/sysinfo.h>
#include "memory.h"
#include "process.h"
#include "netlinks.h"

/*
    netlink内核读写
    注：编译内核模块，除了基本类型外都需要手动申请内存和释放内存。
*/

#ifdef USER_MODULE
size_t phy_memory_size; // 物理内存总大小
static bool init_phy_memory_size(void) // 计算物理内存函数
{
	struct sysinfo sysinfo_size;
	struct sysinfo *si;
	si = kmalloc(sizeof(sysinfo_size), GFP_KERNEL);
	si_meminfo(si);	
	uint64_t sav_total = 0;
	uint64_t  bitcount = 0;	
	uint64_t mem_unit = si->mem_unit;
	uint64_t mem_total = si->totalram;
	while (mem_unit > 1)
	{
		bitcount++;
		mem_unit >>= 1;
		sav_total = mem_total;
		mem_total <<= 1;
		if (mem_total < sav_total)
		{
			kfree(si);
			return false;
		}
	}
	si->totalram <<= bitcount;
	phy_memory_size = __pa(si->totalram);
	kfree(si);
	return true;
}
#else //如果不单编成模块的话，不需要计算物理内存，置空即可
static bool init_phy_memory_size(void)
{
    return true;
}
#endif

// 接收Netlink消息的回调函数 函数参数是内核写法规定写死的勿改
static void __nl_recv_msg(struct sk_buff *skb)
{
    #ifdef USER_DEBUG
    printk("kernel_netlink_rw: run netlink_function");
    #endif
    struct nlmsghdr *nlh = (struct nlmsghdr *)skb->data;
    struct Process *process = (struct Process *)nlmsg_data(nlh);
    struct sk_buff *skb_out = nlmsg_new(process->size, GFP_KERNEL);
    if (!skb_out) //判断sk_buff是否申请成功
    {
        #ifdef USER_DEBUG
        printk("kernel_netlink_rw: skb_out == nullptr");
        #endif
        return;
    }
    nlh = nlmsg_put(skb_out, 0, 0, NLMSG_DONE, process->size, 0);
    if (!nlh) //判断nlh是否赋值成功
    {
        #ifdef USER_DEBUG
        printk("kernel_netlink_rw: nlh == nullptr");
        #endif
        nlmsg_free(skb_out);
        return;
    }
    
    switch (process->cmd)
    {
        case CMD_INIT_KEY: //验证该netlink协议号是否我们的注册的读写
            {
                memcpy(nlmsg_data(nlh), &(process->cmd), process->size);
            }
            break;
        case CMD_READ_MEM: //读内存
            {
                if (!read_process_memory(process->pid, process->addr, process->buffer, process->size))
                {
                    memcpy(nlmsg_data(nlh), &(process->null), process->size);
                }else // 如果读取失败则回送0
                {
                    memcpy(nlmsg_data(nlh), &(process->buffer), process->size);
                }
            }
            break;
        case CMD_WRITE_MEM: //写内存
            {                
                if (!write_process_memory(process->pid, process->addr, process->buffer, process->size))
                {
                    memcpy(nlmsg_data(nlh), &(process->null), process->size);
                }else
                {
                    memcpy(nlmsg_data(nlh), &(process->size), process->size);
                }
            }
            break;
        case CMD_MODULE_BASE: //读模块
            {
                process->addr = get_module_base(process->pid, process->name);
                memcpy(nlmsg_data(nlh), &(process->addr), process->size);
            }
            break;
        default: //防止异常导致崩溃，回送0
            memcpy(nlmsg_data(nlh), &(process->null), process->size);
    }
    //回送数据，并释放内存
    nlmsg_unicast(nl_sk[process->nlk], skb_out, process->spid);
    #ifdef USER_DEBUG
    printk("kernel_netlink_rw: run ok");
    #endif
}


int __init driver_entry(void)
{
    if (init_phy_memory_size())
    {
        #ifdef USER_DEBUG
        printk("kernel_netlink_rw: load...");
        #endif
        struct netlink_kernel_cfg cfg_size;
        cfg = kmalloc(sizeof(cfg_size), GFP_KERNEL);
        nl_sk = kmalloc(3, GFP_KERNEL);
        #ifdef USER_DEBUG
        if (cfg)
        {
            printk("kernel_netlink_rw: cfg kmalloc ok");
        }else
        {
            printk("kernel_netlink_rw: cfg kmalloc err");
        }
        #endif
        cfg->input = __nl_recv_msg;
        int i;
        int j;
        for (j = 0; j < 3; j++) //注册三组读写以供多线程使用
        {
            for (i = 31; i > 0; i--)
            {
                nl_sk[j] = netlink_kernel_create(&init_net, i, cfg);
                if (nl_sk[j])
                    break;
            }
        }
        for (j = 0; j < 3; j++) //验证三组读写是否注册成功
        {
            if (nl_sk[j])
            {
                #ifdef USER_DEBUG
                printk("kernel_netlink_rw: netlink_kernel_create %d ok", j);
                #endif
            }else
            {
                #ifdef USER_DEBUG
                printk("kernel_netlink_rw: netlink_kernel_create %d err", j);
                #endif
                if (j == 2)
                {
                    j = 0;
                    break;
                }
            }
        }
        if (!j)
        {
            #ifdef USER_DEBUG
            printk("kernel_netlink_rw: option two netlink_kernel_create");
            #endif
            cfg_size.input = __nl_recv_msg;
            for (j = 0; j < 3; j++) //切换为由内核自行分配内存的方式进行 注册三组读写以供多线程使用
            {
                for (i = 31; i > 0; i--)
                {
                    nl_sk[j] = netlink_kernel_create(&init_net, i, &cfg_size);
                    if (nl_sk[j])
                        break;
                }
            }
            #ifdef USER_DEBUG
            if (nl_sk[0])
            {
                printk("kernel_netlink_rw: netlink_kernel_create ok");
            }else
            {
                printk("kernel_netlink_rw: netlink_kernel_create err");
            }
            #endif
        }
        
        printk("kernel_netlink_rw: load finished");
    }
	return 0;
}

void __exit driver_unload(void)
{
	if (phy_memory_size)
	{
        for (int j = 0; j < 3; j++)
        {
            if (nl_sk[j])
	            netlink_kernel_release(nl_sk[j]); //注销读写
        }
        kfree(cfg); //卸载模块需要手动释放内存，否则内存泄露
    }
    printk("kernel_netlink_rw: unload finished");
}


module_init(driver_entry); //初始化模块安装
module_exit(driver_unload); //卸载模块

MODULE_DESCRIPTION(" "); //必要，模块的描述，不推荐留信息
MODULE_LICENSE("GPL"); //必要，模块的协议
MODULE_AUTHOR(" "); //必要，模块作者，不推荐留ID，以防被特征
