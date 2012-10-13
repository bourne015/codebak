#include<linux/ioctl.h>

#define gpcon 0x7f008820
#define gpdat 0x7f008824
#define gppud 0x7f008828

#define DEV_MINOR 0

#define MEM_IOC_MAGIC 'f'
#define MEM_IOC_MAXNR 2
#define MEM_IOCSTAT _IOR(MEM_IOC_MAGIC, 1, int)
//#define MEM_IOCSET0 _IO(MEM_IOC_MAGIC, 2)
//#define MEM_IOCSET1 _IO(MEM_IOC_MAGIC, 3)
#define MEM_IOCSET _IOW(MEM_IOC_MAGIC, 2, int)
