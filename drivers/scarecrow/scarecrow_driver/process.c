#include "process.h"
/*
    版本v1.0
    修复内核崩溃
*/
#define ARC_PATH_MAX 0x200

extern struct mm_struct *get_task_mm(struct task_struct *task);

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 4, 61))
extern void mmput(struct mm_struct *);
#endif

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 1, 0))
uintptr_t get_module_base(pid_t pid, char *name)
{
    return 0;
}
#else
uintptr_t get_module_base(pid_t pid, char *name)
{
	struct pid *pid_struct;
	struct task_struct *task;
	struct mm_struct *mm;
	struct vm_area_struct *vma;

	pid_struct = find_get_pid(pid);
	if (!pid_struct)
	{
		return 0;
	}
	task = get_pid_task(pid_struct, PIDTYPE_PID);
	if (!task)
	{
		return 0;
	}
	mm = get_task_mm(task);
	if (!mm)
	{
		return 0;
	}
	mmput(mm);
	char *buf = kmalloc(ARC_PATH_MAX, GFP_KERNEL);
	for (vma = mm->mmap; vma; vma = vma->vm_next)
	{
		memset(buf, 0, ARC_PATH_MAX);
		if (vma->vm_file)
		{
			char *path_nm = file_path(vma->vm_file, buf, ARC_PATH_MAX);
			if (!strcmp(kbasename(path_nm), name))
			{
				kfree(buf);
				return vma->vm_start;
			}
		}
	}
	kfree(buf);
	return 0;
}
#endif