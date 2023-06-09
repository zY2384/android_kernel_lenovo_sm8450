#define w48 else
#define w74 >=
#define w21 ::
#define w39 sizeof
#define w49 short
#define w50 int 
#define w73 protected
#define w47 using
#define w45 explicit
#define w40 <<
#define w26 int 
#define w29 struct
#define w17 inline
#define w3 void
#define w46 --
#define w42 catch
#define w60 {
#define w12 class
#define w20 throw
#define w78 true
#define w61 ]
#define w52 typedef
#define w55 &&
#define w15 default
#define w7 uint64_t
#define w38 auto
#define w16 while
#define w8 double
#define w33 [
#define w28 +=
#define w68 <=
#define w70 goto
#define w27 private
#define w34 mutable
#define w69 continue
#define w71 case
#define w2 public
#define w67 namespace
#define w9 (
#define w31 signed
#define w36 ->
#define w30 printf
#define w77 asm
#define w44 typeid
#define w59 enum
#define w32 !=
#define w10 cin
#define w19 for (
#define w66 new
#define w75 }
#define w64 ||
#define w18 cout
#define w76 -=
#define w35 typename
#define w58 )
#define w25 ;
#define w57 break
#define w14 pid_t
#define w37 bool
#define w1 char
#define w11 export
#define w62 union
#define w56 if
#define w5 friend
#define w23 uintptr_t
#define w22 long
#define w43 float
#define w72 uint8_t
#define w4 static
#define w65 false
#define w0 unsigned
#define w54 const
#define w6 try
#define w51 ==
#define w41 main
#define w63 switch
#define w13 ++
#define w53 return
#define w24 >>
#define w79 endl
#include <linux/module.h>
#include <linux/tty.h>
#include <linux/miscdevice.h>
#include "comm.h"
#include "memory.h"
#include "process.h"

#define DEVICE_NAME "ttyHV0"

 /*3b7F4D*/ w50 /*3b7F4D*/ dispatch_open /*3b7F4D*/ w9 /*3b7F4D*/  /*3b7F4D*/ w29 /*3b7F4D*/  inode *node,  /*3b7F4D*/ w29 /*3b7F4D*/  file *file /*3b7F4D*/ w58 /*3b7F4D*/ 
 /*5cE81b*/ w60 /*5cE81b*/ 
 /*8EcfC9*/ w53 /*8EcfC9*/  0 /*8EcfC9*/ w25 /*8EcfC9*/ 
 /*E20da9*/ w75 /*E20da9*/ 

 /*e1dA5c*/ w50 /*e1dA5c*/ dispatch_close /*e1dA5c*/ w9 /*e1dA5c*/  /*e1dA5c*/ w29 /*e1dA5c*/  inode *node,  /*e1dA5c*/ w29 /*e1dA5c*/  file *file /*e1dA5c*/ w58 /*e1dA5c*/ 
 /*C5269A*/ w60 /*C5269A*/ 
 /*af027B*/ w53 /*af027B*/  0 /*af027B*/ w25 /*af027B*/ 
 /*E457fD*/ w75 /*E457fD*/ 

 /*6D8dc1*/ w22 /*6D8dc1*/  dispatch_ioctl /*6D8dc1*/ w9 /*6D8dc1*/  /*6D8dc1*/ w29 /*6D8dc1*/  file*  /*6D8dc1*/ w54 /*6D8dc1*/  file, un /*6D8dc1*/ w31 /*6D8dc1*/   /*6D8dc1*/ w50 /*6D8dc1*/  /*6D8dc1*/ w54 /*6D8dc1*/  cmd, un /*6D8dc1*/ w31 /*6D8dc1*/   /*6D8dc1*/ w22 /*6D8dc1*/   /*6D8dc1*/ w54 /*6D8dc1*/  arg /*6D8dc1*/ w58 /*6D8dc1*/ 
 /*ad1C4c*/ w60 /*ad1C4c*/ 
 /*aB5cFD*/ w4 /*aB5cFD*/  COPY_MEMORY cm /*aB5cFD*/ w25 /*aB5cFD*/ 
 /*4ECedF*/ w4 /*4ECedF*/  MODULE_BASE mb /*4ECedF*/ w25 /*4ECedF*/ 
 /*7c9ABe*/ w4 /*7c9ABe*/   /*7c9ABe*/ w1 /*7c9ABe*/  key /*7c9ABe*/ w33 /*7c9ABe*/ 0x100 /*7c9ABe*/ w61 /*7c9ABe*/  =  /*7c9ABe*/ w60 /*7c9ABe*/ 0 /*7c9ABe*/ w75 /*7c9ABe*/  /*7c9ABe*/ w25 /*7c9ABe*/ 
 /*b7A9Ee*/ w4 /*b7A9Ee*/   /*b7A9Ee*/ w1 /*b7A9Ee*/  name /*b7A9Ee*/ w33 /*b7A9Ee*/ 0x100 /*b7A9Ee*/ w61 /*b7A9Ee*/  =  /*b7A9Ee*/ w60 /*b7A9Ee*/ 0 /*b7A9Ee*/ w75 /*b7A9Ee*/  /*b7A9Ee*/ w25 /*b7A9Ee*/ 
 /*Bf0eaF*/ w4 /*Bf0eaF*/   /*Bf0eaF*/ w37 /*Bf0eaF*/  is_ver /*Bf0eaF*/ w56 /*Bf0eaF*/ ied =  /*Bf0eaF*/ w65 /*Bf0eaF*/  /*Bf0eaF*/ w25 /*Bf0eaF*/ 

 /*Ae61Df*/ w56 /*Ae61Df*/  /*Ae61Df*/ w9 /*Ae61Df*/ cmd  /*Ae61Df*/ w51 /*Ae61Df*/  OP_INIT_KEY  /*Ae61Df*/ w55 /*Ae61Df*/  !is_ver /*Ae61Df*/ w56 /*Ae61Df*/ ied /*Ae61Df*/ w58 /*Ae61Df*/ 
 /*1aC6D3*/ w60 /*1aC6D3*/ 
 /*7de56D*/ w56 /*7de56D*/   /*7de56D*/ w9 /*7de56D*/ copy_from_user /*7de56D*/ w9 /*7de56D*/ key,  /*7de56D*/ w9 /*7de56D*/  /*7de56D*/ w3 /*7de56D*/  __user* /*7de56D*/ w58 /*7de56D*/ arg,  /*7de56D*/ w39 /*7de56D*/  /*7de56D*/ w9 /*7de56D*/ key /*7de56D*/ w58 /*7de56D*/ -1 /*7de56D*/ w58 /*7de56D*/   /*7de56D*/ w32 /*7de56D*/  0 /*7de56D*/ w58 /*7de56D*/   /*7de56D*/ w60 /*7de56D*/ 
 /*A30fc1*/ w53 /*A30fc1*/  -1 /*A30fc1*/ w25 /*A30fc1*/ 
 /*Ec7820*/ w75 /*Ec7820*/ 
 /*d4a9cA*/ w75 /*d4a9cA*/ 
 /*0F316b*/ w63 /*0F316b*/   /*0F316b*/ w9 /*0F316b*/ cmd /*0F316b*/ w58 /*0F316b*/ 
 /*f6eFBC*/ w60 /*f6eFBC*/ 
 /*E0eD8F*/ w71 /*E0eD8F*/  OP_READ_MEM:
 /*9eFA0B*/ w60 /*9eFA0B*/ 
 /*aACE60*/ w56 /*aACE60*/   /*aACE60*/ w9 /*aACE60*/ copy_from_user /*aACE60*/ w9 /*aACE60*/ &cm,  /*aACE60*/ w9 /*aACE60*/  /*aACE60*/ w3 /*aACE60*/  __user* /*aACE60*/ w58 /*aACE60*/ arg,  /*aACE60*/ w39 /*aACE60*/  /*aACE60*/ w9 /*aACE60*/ cm /*aACE60*/ w58 /*aACE60*/  /*aACE60*/ w58 /*aACE60*/   /*aACE60*/ w32 /*aACE60*/  0 /*aACE60*/ w58 /*aACE60*/   /*aACE60*/ w60 /*aACE60*/ 
 /*2a9feC*/ w53 /*2a9feC*/  -1 /*2a9feC*/ w25 /*2a9feC*/ 
 /*DA8396*/ w75 /*DA8396*/ 
 /*DeFcd0*/ w56 /*DeFcd0*/   /*DeFcd0*/ w9 /*DeFcd0*/ read_process_memory /*DeFcd0*/ w9 /*DeFcd0*/ cm.pid, cm.addr, cm.buffer, cm.size /*DeFcd0*/ w58 /*DeFcd0*/   /*DeFcd0*/ w51 /*DeFcd0*/   /*DeFcd0*/ w65 /*DeFcd0*/  /*DeFcd0*/ w58 /*DeFcd0*/   /*DeFcd0*/ w60 /*DeFcd0*/ 
 /*0Ed43B*/ w53 /*0Ed43B*/  -1 /*0Ed43B*/ w25 /*0Ed43B*/ 
 /*5e08B4*/ w75 /*5e08B4*/ 
 /*4DEB71*/ w75 /*4DEB71*/ 
 /*Ec07f8*/ w57 /*Ec07f8*/  /*Ec07f8*/ w25 /*Ec07f8*/ 
 /*1c6DF9*/ w71 /*1c6DF9*/  OP_WRITE_MEM:
 /*58cd9a*/ w60 /*58cd9a*/ 
 /*dC0B6E*/ w56 /*dC0B6E*/   /*dC0B6E*/ w9 /*dC0B6E*/ copy_from_user /*dC0B6E*/ w9 /*dC0B6E*/ &cm,  /*dC0B6E*/ w9 /*dC0B6E*/  /*dC0B6E*/ w3 /*dC0B6E*/  __user* /*dC0B6E*/ w58 /*dC0B6E*/ arg,  /*dC0B6E*/ w39 /*dC0B6E*/  /*dC0B6E*/ w9 /*dC0B6E*/ cm /*dC0B6E*/ w58 /*dC0B6E*/  /*dC0B6E*/ w58 /*dC0B6E*/   /*dC0B6E*/ w32 /*dC0B6E*/  0 /*dC0B6E*/ w58 /*dC0B6E*/   /*dC0B6E*/ w60 /*dC0B6E*/ 
 /*245dB6*/ w53 /*245dB6*/  -1 /*245dB6*/ w25 /*245dB6*/ 
 /*fB6349*/ w75 /*fB6349*/ 
 /*5F0d96*/ w56 /*5F0d96*/   /*5F0d96*/ w9 /*5F0d96*/ write_process_memory /*5F0d96*/ w9 /*5F0d96*/ cm.pid, cm.addr, cm.buffer, cm.size /*5F0d96*/ w58 /*5F0d96*/   /*5F0d96*/ w51 /*5F0d96*/   /*5F0d96*/ w65 /*5F0d96*/  /*5F0d96*/ w58 /*5F0d96*/   /*5F0d96*/ w60 /*5F0d96*/ 
 /*47Ff6C*/ w53 /*47Ff6C*/  -1 /*47Ff6C*/ w25 /*47Ff6C*/ 
 /*9ED76a*/ w75 /*9ED76a*/ 
 /*5d0f73*/ w75 /*5d0f73*/ 
 /*8Dea12*/ w57 /*8Dea12*/  /*8Dea12*/ w25 /*8Dea12*/ 
 /*5aFBc3*/ w71 /*5aFBc3*/  OP_MODULE_BASE:
 /*f0DbFa*/ w60 /*f0DbFa*/ 
 /*fBE17c*/ w56 /*fBE17c*/   /*fBE17c*/ w9 /*fBE17c*/ copy_from_user /*fBE17c*/ w9 /*fBE17c*/ &mb,  /*fBE17c*/ w9 /*fBE17c*/  /*fBE17c*/ w3 /*fBE17c*/  __user* /*fBE17c*/ w58 /*fBE17c*/ arg,  /*fBE17c*/ w39 /*fBE17c*/  /*fBE17c*/ w9 /*fBE17c*/ mb /*fBE17c*/ w58 /*fBE17c*/  /*fBE17c*/ w58 /*fBE17c*/   /*fBE17c*/ w32 /*fBE17c*/  0
 /*51Dfc7*/ w64 /*51Dfc7*/   copy_from_user /*51Dfc7*/ w9 /*51Dfc7*/ name,  /*51Dfc7*/ w9 /*51Dfc7*/  /*51Dfc7*/ w3 /*51Dfc7*/  __user* /*51Dfc7*/ w58 /*51Dfc7*/ mb.name,  /*51Dfc7*/ w39 /*51Dfc7*/  /*51Dfc7*/ w9 /*51Dfc7*/ name /*51Dfc7*/ w58 /*51Dfc7*/ -1 /*51Dfc7*/ w58 /*51Dfc7*/   /*51Dfc7*/ w32 /*51Dfc7*/ 0 /*51Dfc7*/ w58 /*51Dfc7*/   /*51Dfc7*/ w60 /*51Dfc7*/ 
 /*b691B5*/ w53 /*b691B5*/  -1 /*b691B5*/ w25 /*b691B5*/ 
 /*fEc497*/ w75 /*fEc497*/ 
mb.base = get_module_base /*A40d7F*/ w9 /*A40d7F*/ mb.pid, name /*A40d7F*/ w58 /*A40d7F*/  /*A40d7F*/ w25 /*A40d7F*/ 
 /*fbCe8F*/ w56 /*fbCe8F*/   /*fbCe8F*/ w9 /*fbCe8F*/ copy_to_user /*fbCe8F*/ w9 /*fbCe8F*/  /*fbCe8F*/ w9 /*fbCe8F*/  /*fbCe8F*/ w3 /*fbCe8F*/  __user* /*fbCe8F*/ w58 /*fbCe8F*/ arg, &mb,  /*fbCe8F*/ w39 /*fbCe8F*/  /*fbCe8F*/ w9 /*fbCe8F*/ mb /*fbCe8F*/ w58 /*fbCe8F*/  /*fbCe8F*/ w58 /*fbCe8F*/   /*fbCe8F*/ w32 /*fbCe8F*/ 0 /*fbCe8F*/ w58 /*fbCe8F*/   /*fbCe8F*/ w60 /*fbCe8F*/ 
 /*8a5f6E*/ w53 /*8a5f6E*/  -1 /*8a5f6E*/ w25 /*8a5f6E*/ 
 /*aeF09C*/ w75 /*aeF09C*/ 
 /*AcF540*/ w75 /*AcF540*/ 
 /*fe84aF*/ w57 /*fe84aF*/  /*fe84aF*/ w25 /*fe84aF*/ 
 /*7352c6*/ w15 /*7352c6*/ :
 /*68Cb0c*/ w57 /*68Cb0c*/  /*68Cb0c*/ w25 /*68Cb0c*/ 
 /*f3D0d6*/ w75 /*f3D0d6*/ 
 /*d0BfA3*/ w53 /*d0BfA3*/  0 /*d0BfA3*/ w25 /*d0BfA3*/ 
 /*B68E2f*/ w75 /*B68E2f*/ 

 /*FC41Ba*/ w29 /*FC41Ba*/  file_operations dispatch_functions =  /*FC41Ba*/ w60 /*FC41Ba*/ 
.owner   = THIS_MODULE,
.open    = dispatch_open,
.release = dispatch_close,
.unlocked_ioctl = dispatch_ioctl,
 /*CAadcF*/ w75 /*CAadcF*/  /*CAadcF*/ w25 /*CAadcF*/ 

 /*1d8Ec4*/ w29 /*1d8Ec4*/  miscdevice misc =  /*1d8Ec4*/ w60 /*1d8Ec4*/ 
.minor = MISC_DYNAMIC_MINOR,
.name = DEVICE_NAME,
.fops = &dispatch_functions,
 /*aEDB2e*/ w75 /*aEDB2e*/  /*aEDB2e*/ w25 /*aEDB2e*/ 

 /*58Fe47*/ w50 /*58Fe47*/ __init driver_en /*58Fe47*/ w6 /*58Fe47*/  /*58Fe47*/ w9 /*58Fe47*/  /*58Fe47*/ w3 /*58Fe47*/  /*58Fe47*/ w58 /*58Fe47*/ 
 /*acF4B7*/ w60 /*acF4B7*/ 
printk /*07d43c*/ w9 /*07d43c*/ "Hello, ttyHV0" /*07d43c*/ w58 /*07d43c*/  /*07d43c*/ w25 /*07d43c*/ 
misc_register /*F7d6A4*/ w9 /*F7d6A4*/ &misc /*F7d6A4*/ w58 /*F7d6A4*/  /*F7d6A4*/ w25 /*F7d6A4*/ 
 /*34F1f8*/ w53 /*34F1f8*/  0 /*34F1f8*/ w25 /*34F1f8*/ 
 /*aC4b9E*/ w75 /*aC4b9E*/ 

 /*907Dce*/ w3 /*907Dce*/  __exit driver_unload /*907Dce*/ w9 /*907Dce*/  /*907Dce*/ w3 /*907Dce*/  /*907Dce*/ w58 /*907Dce*/ 
 /*EbAe7d*/ w60 /*EbAe7d*/ 
printk /*4BCf3e*/ w9 /*4BCf3e*/ "Bye, ttyHV0" /*4BCf3e*/ w58 /*4BCf3e*/  /*4BCf3e*/ w25 /*4BCf3e*/ 
misc_deregister /*5fAe0b*/ w9 /*5fAe0b*/ &misc /*5fAe0b*/ w58 /*5fAe0b*/  /*5fAe0b*/ w25 /*5fAe0b*/ 
 /*05BE39*/ w75 /*05BE39*/ 

module_init /*B9Aa0F*/ w9 /*B9Aa0F*/ driver_en /*B9Aa0F*/ w6 /*B9Aa0F*/  /*B9Aa0F*/ w58 /*B9Aa0F*/  /*B9Aa0F*/ w25 /*B9Aa0F*/ 
module_exit /*bcAeBf*/ w9 /*bcAeBf*/ driver_unload /*bcAeBf*/ w58 /*bcAeBf*/  /*bcAeBf*/ w25 /*bcAeBf*/ 

MODULE_DESCRIPTION /*26cd85*/ w9 /*26cd85*/ "Kernel for Android" /*26cd85*/ w58 /*26cd85*/  /*26cd85*/ w25 /*26cd85*/ 
MODULE_LICENSE /*a83c6d*/ w9 /*a83c6d*/ "GPL" /*a83c6d*/ w58 /*a83c6d*/  /*a83c6d*/ w25 /*a83c6d*/ 
MODULE_AUTHOR /*02da54*/ w9 /*02da54*/ "ttyHV0" /*02da54*/ w58 /*02da54*/  /*02da54*/ w25 /*02da54*/ 
