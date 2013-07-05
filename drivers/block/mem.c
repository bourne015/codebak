#include <linux/module.h>
#include <linux/init.h>
//#include <linux/sched.h>
#include <linux/kernel.h>
#include <linux/slab.h>	
#include <linux/fs.h>		
#include <linux/errno.h>	
#include <linux/types.h>	
#include <linux/fcntl.h>	
//#include <linux/kdev_t.h>
#include <linux/vmalloc.h>
#include <linux/genhd.h>
#include <linux/blkdev.h>
//#include <linux/bio.h>

#define TEST

#define DEV_MAJOR        0
#define DEV_NAME        "blk_dev"
#define DEV_BYTES        (16*1024*102)

static int blk_major = DEV_MAJOR;

struct blk_dev {
	int size;
	u8 *data;
	short users;
	struct request_queue *blk_queue;
	struct gendisk *gd;
};

struct blk_dev *mydev = NULL;

static void
blk_tranfer(unsigned long mysector, unsigned long n_sector,
		char *buffer, int r_w)
{	

	unsigned long offset = mysector << 9;
	unsigned long nbytes = n_sector << 9;

#if defined TEST
	printk(KERN_ALERT "start to transfer\n");
	printk(KERN_ALERT "dev->size = %d\n", mydev->size);
#endif
	if ((offset + nbytes) > mydev->size) {
		printk(KERN_ALERT "size error\n");
		return;
	}

	if (r_w == WRITE)
		memcpy(mydev->data+offset, buffer, nbytes);
	else
		memcpy(buffer, mydev->data+offset, nbytes);
}

static void request_hand(struct request_queue *q)
{
        struct request *req;
	static int n = 0;

	req = blk_fetch_request(q);
	while ((req) != NULL) {
	
#if defined TEST
	printk(KERN_ALERT "now get the request %d\n", ++n);
#endif
//		struct blk_dev *dev = req->rq_disk->private_data;
		if (req->cmd_type != REQ_TYPE_FS) {
			printk(KERN_NOTICE "skip non-fs request\n");
			__blk_end_request_all(req, -1);
			continue;
		}

		blk_tranfer(blk_rq_pos(req), blk_rq_cur_sectors(req),
				req->buffer, rq_data_dir(req));
		if(!__blk_end_request_cur(req, 0))
			req = blk_fetch_request(q);
	}
#if defined TEST
	printk(KERN_ALERT "done\n\n");
#endif
	return;
}

struct block_device_operations blk_dev_fops = {
        .owner  = THIS_MODULE,
};

static int __init blk_init(void)
{
        int ret;

	blk_major = register_blkdev(DEV_MAJOR, DEV_NAME);
	if (blk_major <= 0) {
		printk(KERN_ALERT "failure to get major\n");
		unregister_blkdev(DEV_MAJOR, DEV_NAME);
		return -1;
	}

	mydev = kmalloc(sizeof(struct blk_dev), GFP_KERNEL);
	memset(mydev, 0, sizeof(struct blk_dev));
	mydev->size = DEV_BYTES;
	mydev->data = vmalloc(mydev->size);
	if (mydev->data == NULL) {
		printk(KERN_NOTICE "valloc failure\n");
		return -ENOMEM;
	}
#if defined TEST
	printk(KERN_ALERT "malloc and memset done\n");
#endif

        mydev->blk_queue = blk_init_queue(request_hand, NULL);
        if (!mydev->blk_queue) {
                ret = -ENOMEM;
                goto err_init_queue;
        }

        mydev->gd = alloc_disk(1);
        if (!mydev->gd) {
                ret = -ENOMEM;
                goto err_alloc_disk;
        }

        strcpy(mydev->gd->disk_name, DEV_NAME);
        mydev->gd->major = blk_major;
        mydev->gd->first_minor = 0;
        mydev->gd->fops = &blk_dev_fops;
        mydev->gd->queue = mydev->blk_queue;
        set_capacity(mydev->gd, DEV_BYTES >> 9);

        add_disk(mydev->gd);

#if defined TEST
	printk(KERN_ALERT "gd done\n");
#endif
        return 0;

err_alloc_disk:

        blk_cleanup_queue(mydev->blk_queue);

err_init_queue:

        return ret;

}

static void __exit blk_exit(void)
{
        del_gendisk(mydev->gd);
        put_disk(mydev->gd);
        blk_cleanup_queue(mydev->blk_queue);
	vfree(mydev->data);
	unregister_blkdev(blk_major, "DEV_NAME");
	kfree(mydev);
}

module_init(blk_init);
module_exit(blk_exit);
MODULE_LICENSE("GPL");
