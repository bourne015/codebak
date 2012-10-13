#ifndef MEM_MAIN
#define MEM_MAIN 251
#endif

#define mem_num 2
#define mem_size 4096

#define MEM_IOC_MAGIC 'f'
#define MEM_IOCSTART _IO(MEM_IOC_MAGIC, 1)
#define MEM_IOCSEND _IOW(MEM_IOC_MAGIC,2, int)
#define MEM_IOCGET _IOR(MEM_IOC_MAGIC, 3, int)
#define MEM_IOC_MAXNR 3
