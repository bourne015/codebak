#include<linux/ioctl.h>

/*gpio_m for the led*/
#define gpcon 0x7f008820
#define gpdat 0x7f008824
#define gppud 0x7f008828
/*gpio_n for the key*/
#define gpncon 0x7f008830
#define gpndat 0x7f008834
#define gpnpud 0x7f008838

//#define DEV_MINOR 0
#define MEM_IOC_MAGIC 'f'
#define MEM_IOC_MAXNR 2
#define MEM_IOCSTAT _IOR(MEM_IOC_MAGIC, 1, int)
//#define MEM_IOCSET0 _IO(MEM_IOC_MAGIC, 2)
//#define MEM_IOCSET1 _IO(MEM_IOC_MAGIC, 3)
#define MEM_IOCSET _IOW(MEM_IOC_MAGIC, 2, int)
#define gpio 0x7f008820
#define ioaddr addr
#define led_count 1
#define LED_MAJOR 252

#define KEY_MAJOR 252
#define key_name "mykey"
#define key_count 1

