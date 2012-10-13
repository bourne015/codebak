#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <linux/errno.h>
#define SCULL_MAJOR 251
//#define SCULL_MINOR
#define dev_count 1
#define dev_name "tao"
#define dev_size 4096

int size = dev_size;
int dev_major = SCULL_MAJOR;
int dev_minor = 0;// = SCULL_MINOR;

struct mem_dev {
	char *data;
	unsigned long size;
	struct cdev cdev;
};
//struct cdev cdev;
struct mem_dev *mydev;

static int dev_open(struct inode *inode, struct file *filp)
/*{
	struct mem_dev *dev;
	int num = MINOR(inode->i_rdev);
	if (num > dev_count)
		return -ENODEV;
	dev = container_of(inode->i_cdev, struct mem_dev, cdev);
	filp->private_data = dev;
	printk(KERN_ALERT "ker:open succes\n");
	return 0;
}
*/
{
    struct mem_dev *dev;

    int num = MINOR(inode->i_rdev);

    if (num >= dev_count)
            return -ENODEV;
    dev = &mydev[num];

    filp->private_data = dev;

    return 0;
}

static int dev_release(struct inode *inode, struct file *filp)
{
	return 0;
}

static ssize_t dev_read(struct file *filp, char __user *buffer,
			size_t count, loff_t *offp)
{
	int ret = 0;
	unsigned long p = *offp;
	struct mem_dev *dev = filp->private_data;
	if (p > size) {
		printk(KERN_ALERT "can't read so much\n");
		return -1;
	} else if (count > size - p) {
		count = size - p;
	}
	
	if (copy_to_user(buffer, dev->data + p, count))
		return -EFAULT;
	else {
		*offp +=count;
		ret = count;
		printk(KERN_ALERT "read %d bytes from dev\n", count);
	}
	
	return 0;
}

static ssize_t dev_write(struct file *filp, const char __user *buffer,
			size_t count, loff_t *offp)
{
	int ret = 0;
	struct mem_dev *dev = filp->private_data;

	if (*offp > size) {
		printk(KERN_ALERT "space limit\n");
		ret = -ENOMEM;
		goto out;
		return 0;
	}
	if (count > size - *offp) {
		count = size - *offp;
	}

	if (copy_from_user(dev->data + *offp, buffer, count)) {
		ret = EFAULT;
		goto out;
		return -EFAULT;
	} else {
		*offp += count;
		ret = count;
		printk(KERN_ALERT "in kernel write:");//%s\n", dev->data);
		goto out;
	}
	out:
		return ret; 
}

static loff_t dev_llseek(struct file *filp, loff_t offset, int whence)
{
	loff_t new_p;
	switch (whence) {
		case 0:
			new_p = offset;
			break;
		case 1:
			new_p = filp->f_pos + offset;
			break;
		case 2:
			new_p = size - 1 + offset;
			break;
		default:
			return -EINVAL;
	}

	if ((new_p < 0) || (new_p > size))
		return -EINVAL;
	filp->f_pos = new_p;
	
	return new_p;
}

struct file_operations dev_fops = {
	.owner = THIS_MODULE,
	.llseek = dev_llseek,
	.open = dev_open,
	.read = dev_read,
	.write = dev_write,
	.release = dev_release,
};

static int __init char_init(struct mem_dev *dev, int index)
{
	dev_t devno;
	int result;
	int i;
//	struct cdev cdev;
/* alloc the device number */
	if (dev_major) {
		devno = MKDEV(dev_major, dev_minor);
		result = register_chrdev_region(devno, dev_count, dev_name);
	} else {
		result = alloc_chrdev_region(&devno, 0, dev_count, dev_name);
		dev_major = MAJOR(devno);
	}

	if (result < 0) {
		printk(KERN_WARNING "can't get major %d\n", dev_major);
		return result;
	}

/*register the device*/
	cdev_init(&dev->cdev, &dev_fops);
	dev->cdev.owner = THIS_MODULE;
	dev->cdev.ops = &dev_fops;
	cdev_add(&dev->cdev, MKDEV(dev_major, 0), dev_count);	
	
	mydev = kmalloc(dev_count * sizeof(struct mem_dev), GFP_KERNEL);
	if (!mydev) {
		printk(KERN_ALERT "can't malloc mydev\n");
		unregister_chrdev_region(MKDEV(dev_major, 0), dev_count);
		return -ENOMEM;
	}
	for (i = 0; i < dev_count; i++) {
		mydev[i].size = size;
		mydev[i].data = kmalloc(size, GFP_KERNEL);
		memset(mydev[i].data, 0, size);
	}
	
	return result;
}

static void __exit char_exit(struct mem_dev *dev)
{
	cdev_del(&dev->cdev);
	kfree(mydev);
	unregister_chrdev_region(MKDEV(dev_major, 0), dev_count);
}

MODULE_LICENSE("GPL");
module_init(char_init);
module_exit(char_exit);
