#ifndef NETLINKS_H
#define NETLINKS_H
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/netlink.h>
#include <linux/skbuff.h>
#include <linux/vmalloc.h>
#include <linux/mm.h>
#include <linux/sched/mm.h>
#include <net/sock.h>

enum CMD
{
	CMD_INIT_KEY = 0x1004,
	CMD_READ_MEM = 0x2004,
	CMD_WRITE_MEM = 0x3004,
	CMD_MODULE_BASE = 0x4004,
};

struct Process
{
    int nlk; // nlk组
    int cmd; // 操作指令
    pid_t pid; // 目标进程PID
    pid_t spid; // 发送进程PID
    uintptr_t addr; // 虚拟地址，即需要读取的地址
    size_t size; // 数据长度
    char buffer[128]; // 写入数据，这里需要用1字节char[]表示void*，内存中只注重字节大小对齐不分类型，只要大小对齐即可
    char name[64]; // 模块名称
    int null; // 空数据
};

struct sock **nl_sk; // Netlink套接字
struct netlink_kernel_cfg *cfg = NULL; // Netlink结构信息
struct netlink_kernel_cfg cfg_size;
#endif
