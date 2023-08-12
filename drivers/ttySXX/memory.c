#include "memory.h"

extern struct mm_struct *get_task_mm(struct task_struct *task);

#if(LINUX_VERSION_CODE >= KERNEL_VERSION(5, 4, 61))
extern void mmput(struct mm_struct *); // 用于减少一次对应的任务引用mm_struct所对应的用户次数，如果用户数为0则收回该内存；

static inline phys_addr_t translate_linear_address(struct mm_struct* mm, uintptr_t va) {

    pgd_t *pgd;
    p4d_t *p4d;
    pmd_t *pmd;
    pte_t *pte;
    pud_t *pud;
	
    phys_addr_t page_addr;
    uintptr_t page_offset;
    
    pgd = pgd_offset(mm, va);
    if(pgd_none(*pgd) || pgd_bad(*pgd)) {
        return 0;
    }
    p4d = p4d_offset(pgd, va);
    if (p4d_none(*p4d) || p4d_bad(*p4d)) {
    	return 0;
    }
	pud = pud_offset(p4d,va);
	if(pud_none(*pud) || pud_bad(*pud)) {
        return 0;
    }
	pmd = pmd_offset(pud,va);
	if(pmd_none(*pmd)) {
        return 0;
    }
	pte = pte_offset_kernel(pmd,va);
	if(pte_none(*pte)) {
        return 0;
    }
	if(!pte_present(*pte)) {
        return 0;
    }
	//页物理地址
	page_addr = (phys_addr_t)(pte_pfn(*pte) << PAGE_SHIFT);
	//页内偏移
	page_offset = va & (PAGE_SIZE-1);
	
	return page_addr + page_offset;
}
#else
static inline phys_addr_t translate_linear_address(struct mm_struct* mm, uintptr_t va) {

    pgd_t *pgd;
    pmd_t *pmd;
    pte_t *pte;
    pud_t *pud;
	
    phys_addr_t page_addr;
    uintptr_t page_offset;
    
    pgd = pgd_offset(mm, va);
    if(pgd_none(*pgd) || pgd_bad(*pgd)) {
        return 0;
    }
	pud = pud_offset(pgd,va);
	if(pud_none(*pud) || pud_bad(*pud)) {
        return 0;
    }
	pmd = pmd_offset(pud,va);
	if(pmd_none(*pmd)) {
        return 0;
    }
	pte = pte_offset_kernel(pmd,va);
	if(pte_none(*pte)) {
        return 0;
    }
	if(!pte_present(*pte)) {
        return 0;
    }
	//页物理地址
	page_addr = (phys_addr_t)(pte_pfn(*pte) << PAGE_SHIFT);
	//页内偏移
	page_offset = va & (PAGE_SIZE-1);
	
	return page_addr + page_offset;
}
#endif

#ifdef USER_MODULE
static inline int __valid_phys_addr_range(phys_addr_t addr, size_t count) {
    return addr + count < __pa(phy_memory_size);
}

static inline bool read_physical_address(phys_addr_t pa, void* buffer, size_t size) {
    void* mapped;

    if (!pfn_valid(__phys_to_pfn(pa))) {
        return false;
    }
    if (!__valid_phys_addr_range(pa, size)) {
        return false;
    }
    mapped = ioremap_cache(pa, size);
    if (!mapped) {
        return false;
    }
    if(copy_to_user(buffer, mapped, size)) {
        iounmap(mapped);
        return false;
    }
    iounmap(mapped);
    return true;
}

static inline bool write_physical_address(phys_addr_t pa, void* buffer, size_t size) {
    void* mapped;

    if (!pfn_valid(__phys_to_pfn(pa))) {
        return false;
    }
    if (!__valid_phys_addr_range(pa, size)) {
        return false;
    }
    mapped = ioremap_cache(pa, size);
    if (!mapped) {
        return false;
    }
    if(copy_from_user(mapped, buffer, size)) {
        iounmap(mapped);
        return false;
    }
    iounmap(mapped);
    return true;
}
#else
static inline bool read_physical_address(phys_addr_t pa, void* buffer, size_t size) {
    void* mapped;

    if (!pfn_valid(__phys_to_pfn(pa))) {
        return false;
    }
    if (!valid_phys_addr_range(pa, size)) {
        return false;
    }
    mapped = ioremap_cache(pa, size);
    if (!mapped) {
        return false;
    }
    if(copy_to_user(buffer, mapped, size)) {
        iounmap(mapped);
        return false;
    }
    iounmap(mapped);
    return true;
}

static inline bool write_physical_address(phys_addr_t pa, void* buffer, size_t size) {
    void* mapped;

    if (!pfn_valid(__phys_to_pfn(pa))) {
        return false;
    }
    if (!valid_phys_addr_range(pa, size)) {
        return false;
    }
    mapped = ioremap_cache(pa, size);
    if (!mapped) {
        return false;
    }
    if(copy_from_user(mapped, buffer, size)) {
        iounmap(mapped);
        return false;
    }
    iounmap(mapped);
    return true;
}
#endif

bool read_process_memory(
    pid_t pid, 
    uintptr_t addr, 
    void* buffer, 
    size_t size) {
    
    struct task_struct* task;
    struct mm_struct* mm;
    struct pid* pid_struct;
    phys_addr_t pa;

    pid_struct = find_get_pid(pid);
    if (!pid_struct) {
        return false;
    }
	task = get_pid_task(pid_struct, PIDTYPE_PID);
	if (!task) {
        return false;
    }
	mm = get_task_mm(task);
    if (!mm) {
        return false;
    }
    pa = translate_linear_address(mm, addr);
    if (!pa) {
        return false;
    }
    mmput(mm);
    return read_physical_address(pa, buffer, size);
}

bool write_process_memory(
    pid_t pid, 
    uintptr_t addr, 
    void* buffer, 
    size_t size) {
    
    struct task_struct* task;
    struct mm_struct* mm;
    struct pid* pid_struct;
    phys_addr_t pa;

    pid_struct = find_get_pid(pid);
    if (!pid_struct) {
        return false;
    }
    task = get_pid_task(pid_struct, PIDTYPE_PID);
    if (!task) {
        return false;
    }
    mm = get_task_mm(task);
    if (!mm) {
        return false;
    }
    pa = translate_linear_address(mm, addr);
    if (!pa) {
        return false;
    }
    mmput(mm);
    return write_physical_address(pa,buffer,size);
}
