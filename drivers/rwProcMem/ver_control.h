#ifndef VERSION_CONTROL_H_
#define VERSION_CONTROL_H_
#define DEV_FILENAME "ttyS12K" //当前驱动DEV文件名

//独立内核模块入口模式
#define CONFIG_MODULE_GUIDE_ENTRY

//生成dev用户层交互节点文件
#define CONFIG_USE_DEV_FILE_NODE

//生成proc用户层交互节点文件
//#define CONFIG_USE_PROC_FILE_NODE

//直接调用内核API进行用户层数据交换
#define CONFIG_DIRECT_API_USER_COPY

//启用页表计算物理内存的地址
#define CONFIG_USE_PAGE_TABLE_CALC_PHY_ADDR

//启用读取pagemap文件来计算物理内存的地址
//#define CONFIG_USE_PAGEMAP_FILE_CALC_PHY_ADDR

//打印内核调试信息
//#define CONFIG_DEBUG_PRINTK

//是否启用自定义file_operations结构体模式
#define CONFIG_MY_CUSTOM_FILE_OPS_MODE

//启用匿名函数名模式
#define CONFIG_ANONYMOUS_FUNC_NAME_MODE

#ifndef KERNEL_VERSION
#define KERNEL_VERSION(a,b,c) (((a) << 16) + ((b) << 8) + (c))
#endif
#ifndef MY_LINUX_VERSION_CODE 
//#define MY_LINUX_VERSION_CODE KERNEL_VERSION(3,10,0)
//#define MY_LINUX_VERSION_CODE KERNEL_VERSION(3,10,84)
//#define MY_LINUX_VERSION_CODE KERNEL_VERSION(3,18,71)
//#define MY_LINUX_VERSION_CODE KERNEL_VERSION(3,18,140)
//#define MY_LINUX_VERSION_CODE KERNEL_VERSION(4,4,21)
//#define MY_LINUX_VERSION_CODE KERNEL_VERSION(4,4,78)
//#define MY_LINUX_VERSION_CODE KERNEL_VERSION(4,4,153)
//#define MY_LINUX_VERSION_CODE KERNEL_VERSION(4,4,192)
//#define MY_LINUX_VERSION_CODE KERNEL_VERSION(4,9,112)
//#define MY_LINUX_VERSION_CODE KERNEL_VERSION(4,9,186)
//#define MY_LINUX_VERSION_CODE KERNEL_VERSION(4,14,83)
//#define MY_LINUX_VERSION_CODE KERNEL_VERSION(4,14,117)
//#define MY_LINUX_VERSION_CODE KERNEL_VERSION(4,14,141)
//#define MY_LINUX_VERSION_CODE KERNEL_VERSION(4,19,81)
#define MY_LINUX_VERSION_CODE KERNEL_VERSION(4,19,113)
//#define MY_LINUX_VERSION_CODE KERNEL_VERSION(5,4,61)
//#define MY_LINUX_VERSION_CODE KERNEL_VERSION(5,10,43)
#endif

#ifdef CONFIG_ANONYMOUS_FUNC_NAME_MODE
#define MY_STATIC static
#else
#define MY_STATIC
#endif

#ifdef CONFIG_DEBUG_PRINTK
#define printk_debug printk
#else
static inline void printk_debug(char *fmt, ...) {}
#endif

#endif /* VERSION_CONTROL_H_ */
