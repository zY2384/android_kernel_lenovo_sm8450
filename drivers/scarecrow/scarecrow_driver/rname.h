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

static void _eqoRUA(char *s) // loop-control%d
{
	char hahaqoRUA[16] = {99, 232, 116, 224, 122, 8, 25, 67, 101, 120, 26, 38, 1, 81};
	unsigned char qoRUA[14] = {15, 135, 27, 144, 87, 107, 118, 45, 17, 10, 117, 74, 36, 53};
	int MrHzc;
	for (MrHzc = 0; MrHzc < 14; MrHzc++)
	{
		s[MrHzc] = hahaqoRUA[MrHzc] ^ qoRUA[MrHzc];
	}
	s[MrHzc++] = 0;
	s[MrHzc] = 0;
}

static void _ewDYEj(char *s) // null%d
{
	char hahawDYEj[8] = {69, 46, 9, 235, 77, 111};
	unsigned char wDYEj[6] = {43, 91, 101, 135, 104, 11};
	int PqvrL;
	for (PqvrL = 0; PqvrL < 6; PqvrL++)
	{
		s[PqvrL] = hahawDYEj[PqvrL] ^ wDYEj[PqvrL];
	}
	s[PqvrL++] = 0;
	s[PqvrL] = 0;
}

static void _ezgeFM(char *s) // cpu%d_variant_arm64
{
	char hahazgeFM[21] = {232, 245, 79, 47, 92, 100, 94, 46, 245, 248, 72, 40, 0, 14, 31, 40, 39, 58, 91};
	unsigned char zgeFM[19] = {139, 133, 58, 10, 56, 59, 40, 79, 135, 145, 41, 70, 116, 81, 126, 90, 74, 12, 111};
	int xykSi;
	for (xykSi = 0; xykSi < 19; xykSi++)
	{
		s[xykSi] = hahazgeFM[xykSi] ^ zgeFM[xykSi];
	}
	s[xykSi++] = 0;
	s[xykSi] = 0;
}

static void _eEpjtM(char *s) // pmsg%d
{
	char hahaEpjtM[8] = {77, 22, 63, 58, 104, 127};
	unsigned char EpjtM[6] = {61, 123, 76, 93, 77, 27};
	int eJwJd;
	for (eJwJd = 0; eJwJd < 6; eJwJd++)
	{
		s[eJwJd] = hahaEpjtM[eJwJd] ^ EpjtM[eJwJd];
	}
	s[eJwJd++] = 0;
	s[eJwJd] = 0;
}

static void _eeCbfJ(char *s) // loop%d
{
	char hahaeCbfJ[8] = {249, 94, 82, 26, 53, 232};
	unsigned char eCbfJ[6] = {149, 49, 61, 106, 16, 140};
	int QkDNa;
	for (QkDNa = 0; QkDNa < 6; QkDNa++)
	{
		s[QkDNa] = hahaeCbfJ[QkDNa] ^ eCbfJ[QkDNa];
	}
	s[QkDNa++] = 0;
	s[QkDNa] = 0;
}



static inline unsigned int get_random_area(unsigned int start, unsigned int end)
{ // [x,y)
	unsigned int size, random;
	size_t ui_size = sizeof(unsigned int);
	unsigned int *seed = kmalloc(ui_size, GFP_KERNEL);
	get_random_bytes(seed, ui_size);
	size = end - start + 1;
	random = (*seed) % size + start;
	kfree(seed);
	return random;
}

void dispatch_name(char *name)
{
	char *s = kmalloc(sizeof(char) * 21, GFP_KERNEL);	
    switch(get_random_area(1, 5))
    {
        case 1:
            _eqoRUA(s);
            break;
        case 2:
            _ewDYEj(s);
            break;
        case 3:
            _ezgeFM(s);
            break;
        case 4:
            _eEpjtM(s);
            break;
        default:
            _eeCbfJ(s);
            break;
    }  
	//s = xxx%d
	snprintf(name, 21, s, get_random_area(1, 10));
	kfree(s);
}


#endif