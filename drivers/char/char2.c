#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/mm.h>
#include <linux/errno.h>
#include <linux/slab.h>
#include <linux/device.h>
#include <linux/semaphore.h>
#include <linux/sched.h>
#include <linux/poll.h>
#include <asm/io.h>
#include <asm/system.h>
#include <asm/uaccess.h>

#define MEM_SIZE	0x100
#define MEM_MAJOR	250

static int mem_major = MEM_MAJOR;

struct mem_dev {
	struct cdev cdev;
	unsigned char mem[MEM_SIZE];
	unsigned int current_len;
	struct semaphore sem;
	spinlock_t lock;
	wait_queue_head_t r_wait;
	wait_queue_head_t w_wait;
};

struct mem_dev *devp;
struct class *myclass;

static int mem_open(struct inode *inode, struct file *filp)
{
	struct mem_dev *dev;

	dev = container_of(inode->i_cdev, struct mem_dev, cdev);
	filp->private_data = dev;

	return 0;
}

static int mem_release(struct inode *inode, struct file *filp)
{
	return 0;
}

static ssize_t mem_read(struct file *filp, char __user *buf, 
			size_t size, loff_t *ppos)
{
	unsigned int count = size;
	int ret = 0;
	struct mem_dev *dev_buf = filp->private_data;

	DECLARE_WAITQUEUE(wait, current);
	
	down(&dev_buf->sem);
	add_wait_queue(&dev_buf->r_wait, &wait);

	while (dev_buf->current_len == 0) {
		if (filp->f_flags & O_NONBLOCK) {
			ret = -EAGAIN;
			goto out;
		}

		__set_current_state(TASK_INTERRUPTIBLE);
		up(&dev_buf->sem);

		schedule();
		if (signal_pending(current)) {
			ret = -ERESTARTSYS;
			goto out2;
		}
	
		down(&dev_buf->sem);
	}
	
	if (count > dev_buf->current_len)
		count = dev_buf->current_len;

	if (copy_to_user(buf, (dev_buf->mem), count)) {
		ret = -EFAULT;
		goto out;
	} else {
//		*ppos += count;
		memcpy(dev_buf->mem, dev_buf->mem + count,
				dev_buf->current_len - count);
		dev_buf->current_len -= count;
		ret = count;

//		printk(KERN_INFO "read %d bytes from %lu\n", count, p); 
		
		wake_up_interruptible(&dev_buf->w_wait);
	}
	
	out: up(&dev_buf->sem);
	out2: remove_wait_queue(&dev_buf->w_wait, &wait);
	set_current_state(TASK_RUNNING);

	return ret;
}

static ssize_t mem_write(struct file *filp, const char __user *buf, 
			size_t size, loff_t *ppos)
{
	unsigned int count = size;
	int ret = 0;
	struct mem_dev *dev_buf = filp->private_data;

	DECLARE_WAITQUEUE(wait, current);

	down(&dev_buf->sem);
	add_wait_queue(&dev_buf->w_wait, &wait);

	while (dev_buf->current_len == MEM_SIZE) {
		if (filp->f_flags & O_NONBLOCK) {
			ret = -EAGAIN;
			goto out;
		}
	
		__set_current_state(TASK_INTERRUPTIBLE);
		up(&dev_buf->sem);
		
		schedule();
		if (signal_pending(current)) {
			ret = -ERESTARTSYS;
			goto out2;
		}
		
		down(&dev_buf->sem);
	}

	if (count > MEM_SIZE - dev_buf->current_len)
		count = MEM_SIZE - dev_buf->current_len;

	if (copy_from_user(dev_buf->mem + dev_buf->current_len,
				buf, count)) {
			ret = -EFAULT;
			goto out;
	} else {
		dev_buf->current_len += count;

//		printk(KERN_INFO "written %d bytes from %u\n", count, p);

		wake_up_interruptible(&dev_buf->r_wait);
	
		ret = count;		
	}

	out: up(&dev_buf->sem);
	out2: remove_wait_queue(&dev_buf->w_wait, &wait);
	set_current_state(TASK_RUNNING);
	return ret;
}

static unsigned int 
my_mem_poll(struct file *filp, struct poll_table_struct *wait)
{
	unsigned int mask = 0;
	struct mem_dev *dev_buf = filp->private_data;

	down(&dev_buf->sem);

	poll_wait(filp, &dev_buf->r_wait, wait);
	poll_wait(filp, &dev_buf->w_wait, wait);

	if (dev_buf->current_len != 0)
		mask |= POLLIN | POLLRDNORM;
	if (dev_buf->current_len != MEM_SIZE)
		mask |= POLLOUT | POLLWRNORM;

	up(&dev_buf->sem);
	
	return mask;
}

static const struct file_operations mem_fops = {
	.owner = THIS_MODULE,
//	.llseek = mem_llseek,
	.open = mem_open,
	.read = mem_read,
	.write = mem_write,
//	.unlocked_ioctl = mem_ioctl,
	.poll = my_mem_poll,
	.release = mem_release,
};

void mem_setup(struct mem_dev *dev, int index)
{
	int err, devno = MKDEV(mem_major, index);

	cdev_init(&dev->cdev, &mem_fops);
	dev->cdev.owner = THIS_MODULE;
	err = cdev_add(&dev->cdev, devno, 1);
	if (err)
		printk(KERN_NOTICE "ERROR %d adding mem %d", err, index);
}

static int dev_init(void)
{
	int result;

	dev_t devno = MKDEV(mem_major, 0);

	if (mem_major)
		result = register_chrdev_region(devno, 1, "mem");
	else {
		result = alloc_chrdev_region(&devno, 0, 1, "mem");
		mem_major = MAJOR(devno);
	}
	if (result < 0)
		return result;

	devp = (struct mem_dev *)kmalloc(sizeof(struct mem_dev), GFP_KERNEL);
	if (!devp) {
		result = -ENOMEM;
		goto err1;
	}

	memset(devp, 0, sizeof(struct mem_dev));

	mem_setup(devp, 0);

	myclass = class_create(THIS_MODULE, "char_dev");
	device_create(myclass, NULL, devno, NULL, "tao");

	sema_init(&devp->sem, 1);
//	spin_lock_init(&devp->lock);

	init_waitqueue_head(&devp->r_wait);
	init_waitqueue_head(&devp->w_wait);
	
	return 0;
	err1: unregister_chrdev_region(devno, 1);
	return result;
}

static void __exit mem_exit(void)
{
	cdev_del(&devp->cdev);
	kfree(devp);
	device_destroy(myclass, MKDEV(mem_major, 0));
	class_destroy(myclass);
	unregister_chrdev_region(MKDEV(mem_major, 0), 1);
}

module_init(dev_init);
module_exit(mem_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("fantao");
