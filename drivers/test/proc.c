#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/proc_fs.h>
#define proc_name "pname"

struct proc_dir_entry *myproc;

int my_read(char *buffer,
	char **stat, off_t offset,
	int count, int *peof, void *data)
{
	int ret;
	ret = sprintf(buffer,"hello\n");
	return ret;
}

int proc_init()
{
	myproc = create_proc_entry(proc_name,0755,NULL);
	if(myproc == NULL) {
		remove_proc_entry(proc_name,NULL);
		printk(KERN_ALERT "error,can't create /proc/%s\n",proc_name);
		return -ENOMEM;
	}
	myproc->read_proc = my_read;
	//myproc->owner = THIS_MODULE;
	//myproc->size = 50;
	myproc->mode = S_IFREG | S_IRUGO;
	//myproc->uid = 0;
	//myproc->gid = 0;
	printk(KERN_ALERT "/proc/%s created1\n",proc_name);
	return 0;
}

void proc_exit()
{
	remove_proc_entry(proc_name,NULL);
	printk(KERN_ALERT "/proc/%s removed!\n",proc_name);
}

MODULE_ALIAS("PROC");
MODULE_LICENSE("GPL");

module_init(proc_init);
module_exit(proc_exit);
