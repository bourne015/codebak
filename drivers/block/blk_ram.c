#include <linux/module.h>
#include <linux/errno.h>
#include <linux/interrupt.h>
#include <linux/mm.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/timer.h>
#include <linux/genhd.h>
#include <linux/hdreg.h>
#include <linux/ioport.h>
#include <linux/init.h>
#include <linux/wait.h>
#include <linux/blkdev.h>
#include <linux/blkpg.h>
#include <linux/delay.h>
#include <linux/io.h>
#include <asm/system.h>
#include <asm/uaccess.h>
#include <asm/dma.h>

#define RAMBLK_SIZE (1024*1024)

static unsigned int major;
static unsigned char *ramblk_buf;
static DEFINE_SPINLOCK(ramblk_lock);
static struct gendisk *ramblk_disk;
static struct request_queue *ramblk_queue;

static const struct block_device_operations ramblk_fops = {
	.owner = THIS_MODULE,
};

static void do_ramblk(struct request_queue *q)
{
	struct request *req;
	
	while ((req = blk_fetch_request(q)) != NULL) {

//		unsigned long offset = req->__sector * 512;
		unsigned long offset = blk_rq_pos(req) << 9;
//		unsigned long len = req->__data_len;
		unsigned long len = blk_rq_cur_bytes(req);

		if (rq_data_dir(req) == READ) {
			printk(KERN_ALERT "read from block\n");
			memcpy(req->buffer, ramblk_buf+offset, len);
		}
		else {
			printk(KERN_ALERT "write to block\n");
			memcpy(ramblk_buf+offset, req->buffer, len);
		}		
		__blk_end_request_cur(req, 1);
	}

}

static __init int ramblock_init(void)
{
	major = register_blkdev(0, "ramblk");
	
	ramblk_disk = alloc_disk(5);
	ramblk_queue = blk_init_queue(do_ramblk, &ramblk_lock);
	ramblk_disk->major = major;
	ramblk_disk->first_minor = 0;
	ramblk_disk->fops = &ramblk_fops;
	sprintf(ramblk_disk->disk_name, "ramblk");
	set_capacity(ramblk_disk, RAMBLK_SIZE / 512);
	
	ramblk_buf = kzalloc(RAMBLK_SIZE, GFP_KERNEL);
	add_disk(ramblk_disk);

	return 0;
}

static __exit void ramblock_exit(void)
{
	unregister_blkdev(major, "ramblkd");
	del_gendisk(ramblk_disk);
	put_disk(ramblk_disk);
	blk_cleanup_queue(ramblk_queue);
	kfree(ramblk_buf);
}

module_init(ramblock_init);
module_exit(ramblock_exit);

MODULE_LICENSE("GPL");
