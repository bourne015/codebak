#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/slab.h>

char  *memory=NULL;

mem_get()
{
//	int size,flags;
	memory=(kmalloc(100,GFP_KERNEL));
	memset(memory,0,100);
	strcpy(memory,"hello,got the memory");
	printk("<0>BUF 1 : %s\n",memory);
}

mem_free()
{
	printk("<0>goodbye\n");
	free_page(memory);
}

module_init(mem_get);
module_exit(mem_free);





