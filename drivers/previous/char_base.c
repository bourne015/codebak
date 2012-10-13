#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/types.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/slab.h>
#include<linux/sched.h>
#include<linux/mm.h>
#include<linux/ioctl.h>
#include<linux/errno.h>
#include<asm/io.h>
#include<asm/page.h>
#include<asm/system.h>
#include<asm/uaccess.h>
#include"char_def.h"

int mem_major = MEM_MAIN;
struct cdev cdev;

struct mem_dev
{
	char *data;
	unsigned long size;
};
struct mem_dev *mem_devp;

static int mem_open(struct inode *inode, struct file *filp)
{
	struct mem_dev *dev;
	int num = MINOR(inode->i_rdev);
	if (num > mem_num)
		return -ENOMEM;
	dev = &mem_devp[num];
	filp->private_data = dev;
	return 0;
}

int mem_release(struct inode *inode, struct file *filp)
{
	return 0;
}

static int mem_ioctl(struct file *filp, unsigned int cmd,
			unsigned long arg)
{
	int err = 0;
	int usrdata = 0;
	int kerdata;
	if (_IOC_TYPE(cmd) != MEM_IOC_MAGIC) return -ENOTTY;
	if (_IOC_NR(cmd) > MEM_IOC_MAXNR) return -ENOTTY;
	if (_IOC_DIR(cmd) & _IOC_READ)
		err=!access_ok(VERIFY_WRITE,(void __user *)arg,_IOC_SIZE(cmd));
	else if (_IOC_DIR(cmd) & _IOC_WRITE)
		err = !access_ok(VERIFT_READ,(void __user *)arg,_IOC_SIZE(cmd));
	if (err)
		return -EFAULT;	
	switch(cmd) {
		case MEM_IOCSTART:
			printk(KERN_ALERT "IOC START WORK!\n");
			break;
		case MEM_IOCSEND:
			__get_user(usrdata, (int *)arg);
			printk(KERN_ALERT "FROM USER:%d\n",usrdata);
			break;
		case MEM_IOCGET:
			kerdata = 54321;
			__put_user(kerdata, (int *)arg);
			printk(KERN_ALERT "TO USER:%d\n",kerdata);
			break;
		default:
			return -ENOTTY;
	}
	return 0;
}

static int mem_mmap(struct file *filp, struct vm_area_struct *vma)
{
	struct mem_dev *dev;
	dev = filp->private_data;
	if(remap_pfn_range(vma, vma->vm_start, vma->vm_pgoff,
		vma->vm_end - vma->vm_start,
		vma->vm_page_prot))
	return -EAGAIN;
	return 0;
}

struct file_operations mem_fops = {
	.owner = THIS_MODULE,
	.open = mem_open,
	.release = mem_release,
	.unlocked_ioctl = mem_ioctl,
	.mmap = mem_mmap,
};

static int init_char(void)
{
	int result;
	int i;
	dev_t dev;
	if(mem_major) {
		dev = MKDEV(mem_major, 0);
		result = register_chrdev_region(dev, mem_num, "memdev");
	} else {
		result = alloc_chrdev_region(&dev, 0, mem_num, "mem_dev");
		mem_major = MAJOR(dev);
	}
	if( result < 0) {
		printk(KERN_WARNING "CAN'T GET MAJOR %d\n",mem_major);
		return result;
	}
	cdev_init(&cdev, &mem_fops);
	cdev.owner = THIS_MODULE;
	cdev.ops = &mem_fops;
	cdev_add(&cdev, dev, mem_num);
	mem_devp = kmalloc(mem_num * sizeof(struct mem_dev), GFP_KERNEL);
	if (!mem_devp) {
		unregister_chrdev_region(dev, 1);
		return -ENOMEM;
	}
	for( i=0; i < mem_num; i++) {
		mem_devp[i].size = mem_size;
		mem_devp[i].data = kmalloc(mem_size, GFP_KERNEL);
		memset(mem_devp[i].data, 0, mem_size);
	}
	return result;
}
void exit_char(void)
{
	cdev_del(&cdev);
	kfree(mem_devp);
	unregister_chrdev_region(MKDEV(mem_major, 0), mem_num);
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("FANTAO");
MODULE_DESCRIPTION("BASE char dev for test");
module_init(init_char);
module_exit(exit_char);

