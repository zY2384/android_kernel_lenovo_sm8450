#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/netlink.h>
#include <linux/skbuff.h>
#include <linux/vmalloc.h>
#include <linux/mm.h>
#include <linux/sched/mm.h>
#include <net/sock.h>

#define NETLINK_USER 31

struct process_info {
    pid_t pid; // 进程ID
    size_t virt_addr; // 虚拟地址
    size_t len; // 数据长度
};

struct sock *nl_sk = NULL; // Netlink套接字
struct netlink_kernel_cfg cfg; // Netlink内核配置
struct process_info *process_info_data; // 进程信息数据

// 将页表项转换为物理地址
static inline unsigned long pte_to_phys(unsigned long virt_addr, unsigned long pte_value) {
    return (virt_addr & ~PAGE_MASK) | (pte_value & PAGE_MASK);
}

// 根据进程ID获取进程的内存管理结构体
static inline struct mm_struct *get_mm_by_pid(pid_t nr)
{
    struct task_struct *task;

    task = pid_task(find_vpid(nr), PIDTYPE_PID);
    if (!task)
        return NULL;

    return get_task_mm(task);
}

// 获取虚拟地址所在页的物理地址
static size_t get_process_page_addr(struct mm_struct *mm, size_t virt_addr, pte_t **pte)
{
    pgd_t *pgd;
    p4d_t *p4d;
    pud_t *pud;
    pmd_t *pmd;

    pgd = pgd_offset(mm, virt_addr);
    if (pgd_none(*pgd))
        return 0;

    p4d = p4d_offset(pgd, virt_addr);
    if (p4d_none(*p4d))
        return 0;

    pud = pud_offset(p4d, virt_addr);
    if (pud_none(*pud))
        return 0;

    pmd = pmd_offset(pud, virt_addr);
    if (pmd_none(*pmd))
        return 0;

    *pte = pte_offset_kernel(pmd, virt_addr);
    if (pte_none(**pte))
        return 0;

    return pte_val(**pte);
}

// 接收Netlink消息的回调函数
static void nl_recv_msg(struct sk_buff *skb) {
    struct nlmsghdr *nlh;
    int pid;
    int send_pid;
    struct sk_buff *skb_out;
    int res;
    size_t virt_addr;
    unsigned long phys_addr;
    size_t page_addr;
    size_t len;
    void *kernel_addr;
    struct mm_struct *mm;
    pte_t *pte = NULL;
    char *buffer;

    pr_alert( "Entering: %s\n", __FUNCTION__);

    nlh = (struct nlmsghdr *)skb->data;

    send_pid = nlh->nlmsg_pid; // 发送方进程的PID

    // 解析虚拟地址和偏移量
    process_info_data = (struct process_info *)nlmsg_data(nlh);
    virt_addr = process_info_data->virt_addr;
    pid = process_info_data->pid;
    len = process_info_data->len;
    phys_addr = 0;

    pr_err( "v2p: send pid: %d,pid: %d\n",send_pid,pid);
    mm = get_mm_by_pid(pid);

    page_addr = get_process_page_addr(mm, virt_addr, &pte);

    // 如果获取到了进程的内存管理结构体和页表项，并且页表项存在且有效，则计算物理地址，并将数据复制到缓冲区中
    if (mm && pte && pte_present(*pte) && pfn_valid(pte_pfn(*pte))) {
        phys_addr = pte_to_phys(virt_addr, pte_val(*pte)) & 0x7fffffffffffffULL;
        kernel_addr = __va(phys_addr);
    }else{
        pr_err( "v2p: Failed to mm or pte\n");
        return;
    }

    buffer = kmalloc(len, GFP_KERNEL);
    memcpy(buffer, kernel_addr, len);

    skb_out = nlmsg_new(len, 0);
    if (!skb_out) {
        pr_err( "Failed to allocate new skb\n");
        return;
    }

    nlh = nlmsg_put(skb_out, 0, 0, NLMSG_DONE, len, 0);
    if (!nlh) {
        pr_err( "Failed to create netlink message header\n");
        nlmsg_free(skb_out);
        return;
    }

    memcpy(nlmsg_data(nlh), buffer, len);

    res = nlmsg_unicast(nl_sk, skb_out, send_pid);
    if (res < 0) {
        pr_alert( "Error while sending back to user\n");
    }
    kfree(buffer);
}

// 模块初始化函数
static int __init netlink_virt_to_phys_init(void) {
    pr_alert( "Loading netlink_virt_to_phys module...\n");

    cfg.input = nl_recv_msg;

    nl_sk = netlink_kernel_create(&init_net, NETLINK_USER, &cfg);
    if (!nl_sk) {
        pr_alert("Error creating socket.\n");
        return -10;
    }

    return 0;
}

// 模块卸载函数
static void __exit netlink_virt_to_phys_exit(void) {
    pr_alert( "Unloading netlink_virt_to_phys module...\n");

    netlink_kernel_release(nl_sk);
}

module_init(netlink_virt_to_phys_init);
module_exit(netlink_virt_to_phys_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("zY2384");