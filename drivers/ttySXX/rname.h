#ifndef RNAME_H
#define RNAME_H
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
#include <linux/random.h>

unsigned int get_random_area(unsigned int start, unsigned int end)
{
	unsigned int size, random;
	size_t ui_size = sizeof(unsigned int);
	unsigned int *seed = kmalloc(ui_size, GFP_KERNEL);
	get_random_bytes(seed, ui_size);
	size = end - start + 1;
	random = (*seed) % size + start;
	kfree(seed);
	return random;
}

void dispatch_name(char *name, unsigned int start, unsigned int end)
{ //ttyS%d
	char *s = kmalloc(sizeof(char) * 8, GFP_KERNEL);
	char hahaitRyc[8]={100, 90, 67, 199, 31, 84};
    unsigned char itRyc[6]={16, 46, 58, 148, 58, 48};
    int cDoTe;
    for(cDoTe=0; cDoTe<6; cDoTe++)
    {
        s[cDoTe] = hahaitRyc[cDoTe] ^ itRyc[cDoTe];
    }
    s[cDoTe++]=0;
    s[cDoTe]=0;
	snprintf(name, 8, s, get_random_area(start, end));
	kfree(s);
}


#endif