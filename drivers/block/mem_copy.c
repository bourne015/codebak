//from network
#include <linux/kernel.h>
#include <linux/fcntl.h>
#include <linux/init.h>
#include <linux/genhd.h>
#include <linux/fs.h>
#include <linux/blkdev.h>
#include <linux/types.h>
#include <linux/module.h>

/*全局数组，表示本设备*/
unsigned char array_data[16*1024*102];

/*全局变量，表示本设备*/
struct gendisk *my_gendisk;
int major_num = -1;

/*全局变量，本设备关联的请求队列*/
struct request_queue *my_request_queue = NULL;
/*全局变量，内核访问请求队列的自旋锁*/
static DEFINE_SPINLOCK (lock);

struct block_device_operations my_operations=
{
        .owner                = THIS_MODULE,
};

static void sbd_transfer(sector_t sector,unsigned long nsect, char *buffer, int write) 
{
        unsigned long offset = sector<<9;
        unsigned long nbytes = nsect<<9;

        if ((offset + nbytes) > 16*1024*1024) {
                printk (KERN_NOTICE "sbd: Beyond-end write (%ld %ld)\n", offset, nbytes);
                return;
        }
        if (write)
                memcpy(array_data + offset, buffer, nbytes);
        else
                memcpy(buffer, array_data + offset, nbytes);
}

static void 
my_process_on_request_queue(struct request_queue *q)
{

        struct request *req;

        req = blk_fetch_request(q);
        while (req != NULL) 
        {
                if (req == NULL || (req->cmd_type != REQ_TYPE_FS)) 
                {
                        printk (KERN_NOTICE "Skip non-CMD request\n");
                        __blk_end_request_all(req, -EIO);
                        continue;
                }
                sbd_transfer(blk_rq_pos(req), blk_rq_cur_sectors(req),req->buffer, rq_data_dir(req));
                if ( ! __blk_end_request_cur(req, 0) ) {
                        req = blk_fetch_request(q);
                }
        }
}


static int __init
my_init(void)
{        
        
        
        /*1、为代表本设备的结构体申请内存
             这里的参数是本磁盘使用的次设备号的数目，一经申请，这个数字就不可更改        
        */
        my_gendisk = alloc_disk (1);/*linux/genhd.h*/
        if (NULL == my_gendisk)
        {
                printk(KERN_NOTICE"alloc gendisk failure\n");
                return -ENOMEM;
        }
        /*2、为这个结构体成员变量复制,必须的赋值有5个*/
        /*申请"主"设备号,这个名字是出现在：估计是设备号数据库那里的名字 /proc/devices下显示的（下面还有一个名字）事实证明的确如此“251 blocksimple”*/        

        major_num = register_blkdev (0,"blocksimple");/*linux/fs.h*/
        if (major_num<=0)
        {
                printk(KERN_WARNING"no major number\n");
                /*申请主设备号失败的时候，驱动程序就无法正常加载，要释放已经申请的资源，目前资源只有gendisk*/
                goto major_alloc_error;
                
        }
        /*3、我们提到过，每个块设备关联了一个请求队列，我们这里申请一个,需要注意的是：
        1）每个请求队列都对应一个”请求队列处理函数“，这个是设备相关的                
        2）每次分配一个请求队列的时候，必须提供一个自旋锁来控制对请求队列的访问,我们先不考虑并发访问
        */
        //spin_lock_init (&lock);

        my_request_queue = blk_init_queue (my_process_on_request_queue,&lock);

        if (NULL == my_request_queue)
        {
                printk("request queue error");
                goto requeue_alloc_error;        
        
        }
        /*4、使用前面申请的资源为gendisk赋值*/
        strcpy(my_gendisk->disk_name ,"BlockSimple");/*本设备的名称，这个名称是出现在“/dev/”目录下的 */
        my_gendisk->major = major_num;
        my_gendisk->first_minor = 0;
        my_gendisk->queue = my_request_queue;
        my_gendisk->fops = &my_operations;
        /*设置块设备的大小，以扇区为单位，因为内核总是认为扇区大小是512B，所以用函数设定*/
        set_capacity (my_gendisk,16*1024*2);

        
        /*5、注册gendisk*/
        add_disk (my_gendisk);
        return 0;




requeue_alloc_error:
        /*释放主设备号，和gendisk*/
        unregister_blkdev(major_num, "blocksimple");
major_alloc_error:
        /*释放gendisk*/
        del_gendisk(my_gendisk);
        return -ENOMEM;

}


static void __exit
my_exit(void)
{
        blk_cleanup_queue (my_request_queue);
        
        unregister_blkdev(major_num, "blocksimple");

        del_gendisk(my_gendisk);
        put_disk (my_gendisk);
}


module_init (my_init);
module_exit (my_exit);
