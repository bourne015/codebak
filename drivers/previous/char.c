#include<linux/module.h>
#include<linux/init.h>
#include<linux/kernel.h>
#include<linux/cdev.h>
#include<linux/types.h>
#include<linux/fs.h>
#include<linux/kdev_t.h>
#include<linux/slab.h>
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

int mem_open(struct inode *inode, struct file *filp)
{
	struct mem_dev *dev;
	int num = MINOR(inode->i_rdev);
	if(num > mem_num) 
		return -ENODEV;
	dev = &mem_devp[num];
	filp->private_data = dev;
	return 0; 
}

int mem_release(struct inode *inode,struct file *filp)
{
	return 0;
}

static ssize_t mem_read(struct file *filp, char __user *buff, 
		size_t count, loff_t *offp)
{
	int ret = 0;
	struct mem_dev *dev = filp->private_data;
	if(*offp > mem_size) 
		return 0;
	if(count > mem_size - *offp)
		count = mem_size - *offp;
	if(copy_to_user(buff, dev->data + *offp, count)) 
		return -EFAULT;
	else {
		*offp += count; 
		ret = count;
		printk(KERN_ALERT "read %d bytes from %lld \n",count, *offp);
	}
	return ret;
}

static ssize_t mem_write(struct file *filp, const char __user *buff,
			size_t count, loff_t *offp)
{
	int ret = 0;
	struct mem_dev *dev = filp->private_data;
	if(*offp > mem_size)
		return 0;
	if(count > mem_size - *offp)
		count = mem_size - *offp;
	if(copy_from_user(dev->data + *offp, buff, count))
		return -EFAULT;
	else {
		*offp += count;
		ret = count;
		printk(KERN_ALERT "writed %d bytes to %lld \n",count,*offp);
	}
	return ret;
}

static loff_t mem_llseek(struct file *filp, loff_t offset, int whence)
{
	loff_t newp;
	switch(whence) {
		case 0:
			newp = offset;
			break;
		case 1:
			newp = filp->f_pos + offset;
			break;
		case 2:
			newp = mem_size - 1 + offset;
			break;
		default:
			return -EINVAL;
	}
	filp->f_pos = newp;
	return newp;
}
struct file_operations mem_fops = {
	.owner = THIS_MODULE,
	.llseek = mem_llseek,
	.read = mem_read,
	.write = mem_write,
	.open = mem_open,
	.release = mem_release,
};

int init_char(void)
{
	int i;
	int result;
	dev_t devo;
	if(mem_major) {
		devo = MKDEV(mem_major, 0);
		result = register_chrdev_region(devo, mem_num, "memdev");
	} else {
		result = alloc_chrdev_region(&devo, 0, mem_num, "memdev");
		mem_major = MAJOR(devo);
	}
	cdev_init(&cdev, &mem_fops);
	cdev.owner = THIS_MODULE;
	cdev.ops = &mem_fops;
	cdev_add(&cdev, MKDEV(mem_major, 0), mem_num);
	mem_devp = kmalloc(sizeof(struct mem_dev), GFP_KERNEL);
	if(!mem_devp) {
		printk(KERN_ALERT "erro,can't malloc\n");
		unregister_chrdev_region(devo, mem_num);
		return -ENOMEM;
	}
	for(i = 0; i < mem_num; i++) {
		mem_devp[i].size = mem_size;
		mem_devp[i].data =  kmalloc(mem_size, GFP_KERNEL);
		memset(mem_devp[i].data, 0, mem_size);
	}
	return result;
}

void exit_char(void)
{
	unregister_chrdev_region(MKDEV(mem_major,0), mem_num);
}
MODULE_LICENSE("GPL");
MODULE_AUTHOR("FANTAO");
MODULE_DESCRIPTION("CHAR DEVICE ONLY");
module_init(init_char);
module_exit(exit_char);
