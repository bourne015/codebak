#include<linux/init.h>
#include<linux/module.h>

MODULE_LICENSE("CPL");
MODULE_DESCRIPTION("hello");
static int hello_init(void)
{
	printk(KERN_WARNING "hello,world\n");
	return 0;
}

static void hello_exit(void)
{
	printk(KERN_ALERT "goodbye!\n");
}

module_init(hello_init);
module_exit(hello_exit);
