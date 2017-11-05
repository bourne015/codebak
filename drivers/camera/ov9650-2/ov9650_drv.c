#include <linux/module.h>
#include <linux/errno.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/mm.h>
#include <linux/mutex.h>
//#include <linux/videodev2.h>
#include <linux/i2c.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/clk.h>
#include <linux/wait.h>
#include <linux/delay.h>
#include <linux/version.h>
#include <media/videobuf-vmalloc.h>
#include <media/v4l2-device.h>
#include <media/v4l2-ioctl.h>
#include <media/v4l2-common.h>
#include <asm/io.h>
#include <plat/clock.h>
#include <mach/irqs.h>

#define	CISRCFMT 		(0x00 >> 2)
#define	CIGCTRL    		(0x08 >> 2)
#define	CIWDOFST 		(0x04 >> 2)
#define	CIWDOFST2		(0x14 >> 2)

#define	CIPRYSA1   		(0x6c >> 2)
#define	CIPRYSA2   		(0x70 >> 2)
#define	CIPRYSA3   		(0x74 >> 2)
#define	CIPRYSA4   		(0x78 >> 2)
#define	CIPRTRGFMT		(0x9C >> 2)
#define	CIPRCTRL   		(0xA0 >> 2)
#define	CIPRSCPRERATIO 	(0xA4 >> 2)
#define	CIPRSCPREDST 	(0xA8 >> 2)
#define	CIPRSCCTRL 		(0xAC >> 2)
#define	CIPRTAREA 		(0xB0 >> 2)
#define	CIPRSTATUS 		(0xB8 >> 2)
#define	CIIMGCPT 		(0xC0 >> 2)
	
#define MAX_WIDTH 1920
#define MAX_HEIGHT 1200
#define OV9650_VERSION (2)
#define OV9650_MODULE_NAME "ov9650"
#define CHIP_DELAY 0xFF

#define frame_count 4

typedef struct s3c_fimc_i2c_value {
	const u8 subaddr;
	const u8 value;
} OV965X_t;

OV965X_t OV965X_init_reg[] =
{
	/* OV9650 intialization parameter table for VGA application */
	 
	{0x12, 0x40},// Camera Soft reset. Self cleared after reset.
	{CHIP_DELAY, 10},
	{0x11,0x81},{0x6a,0x3e},{0x3b,0x09},{0x13,0xe0},{0x01,0x80},{0x02,0x80},{0x00,0x00},{0x10,0x00},
	{0x13,0xe5},{0x39,0x43},{0x38,0x12},{0x37,0x91},{0x35,0x91},{0x0e,0xa0},{0x1e,0x04},{0xA8,0x80},
	{0x14,0x40},{0x04,0x00},{0x0c,0x04},{0x0d,0x80},{0x18,0xc6},{0x17,0x26},{0x32,0xad},{0x03,0x00},
	{0x1a,0x3d},{0x19,0x01},{0x3f,0xa6},{0x14,0x2e},{0x15,0x10},{0x41,0x02},{0x42,0x08},{0x1b,0x00},
	{0x16,0x06},{0x33,0xe2},{0x34,0xbf},{0x96,0x04},{0x3a,0x00},{0x8e,0x00},{0x3c,0x77},{0x8B,0x06},
	{0x94,0x88},{0x95,0x88},{0x40,0xc1},{0x29,0x3f},{0x0f,0x42},{0x3d,0x92},{0x69,0x40},{0x5C,0xb9},
	{0x5D,0x96},{0x5E,0x10},{0x59,0xc0},{0x5A,0xaf},{0x5B,0x55},{0x43,0xf0},{0x44,0x10},{0x45,0x68},	 
	{0x46,0x96},{0x47,0x60},{0x48,0x80},{0x5F,0xe0},{0x60,0x8c},{0x61,0x20},{0xa5,0xd9},{0xa4,0x74},	 
	{0x8d,0x02},{0x13,0xe7},{0x4f,0x3a},{0x50,0x3d},{0x51,0x03},{0x52,0x12},{0x53,0x26},{0x54,0x38},	 
	{0x55,0x40},{0x56,0x40},{0x57,0x40},{0x58,0x0d},{0x8C,0x23},{0x3E,0x02},{0xa9,0xb8},{0xaa,0x92},	 
	{0xab,0x0a},{0x8f,0xdf},{0x90,0x00},{0x91,0x00},{0x9f,0x00},{0xa0,0x00},{0x3A,0x01},{0x24,0x70},	 
	{0x25,0x64},{0x26,0xc3},{0x2a,0x00},{0x2b,0x00},{0x6c,0x40},{0x6d,0x30},{0x6e,0x4b},{0x6f,0x60},	 
	{0x70,0x70},{0x71,0x70},{0x72,0x70},{0x73,0x70},{0x74,0x60},{0x75,0x60},{0x76,0x50},{0x77,0x48},	 
	{0x78,0x3a},{0x79,0x2e},{0x7a,0x28},{0x7b,0x22},{0x7c,0x04},{0x7d,0x07},{0x7e,0x10},{0x7f,0x28},	 
	{0x80,0x36},{0x81,0x44},{0x82,0x52},{0x83,0x60},{0x84,0x6c},{0x85,0x78},{0x86,0x8c},{0x87,0x9e},	 
	{0x88,0xbb},{0x89,0xd2},{0x8a,0xe6},
};

static unsigned long *S3C_CAM;
static unsigned long *GPFCON;
static unsigned long *GPFDAT;
static unsigned long *GPFPUD;
static unsigned long *VIC0INTENCLEAR;

//static unsigned long buf_size;
static unsigned long bytesperline;
static unsigned int dst_width, dst_height;
static unsigned int src_width = 640, src_height = 480;

static struct ov9650_dev *dev;
static struct video_device *vfd;
static struct i2c_client *ov9650_i2c_client;

static volatile int cam_wq = 0;
static DECLARE_WAIT_QUEUE_HEAD(cam_wait_queue);

struct ov9650_scaler {
	u32		bypass;
	u32		hfactor;
	u32		vfactor;
	u32		pre_hratio;
	u32		pre_vratio;
	u32		pre_dst_width;
	u32		pre_dst_height;
	u32		scaleup_h;
	u32		scaleup_v;
	u32		main_hratio;
	u32		main_vratio;
	u32		real_width;
	u32		real_height;
	u32		line_length;
	u32		zoom_depth;

	u32		enabled;
	u32		copy_mode;
};
static struct ov9650_scaler *sc;

struct ov9650_fmt
{
	char *name;
	u32  fourcc;
	int depth;
};

static struct ov9650_fmt formats[] = {
		{
			.name = "PACKED_RGB_888",
			.fourcc = V4L2_PIX_FMT_RGB24,
			.depth  = 24,
		},
		{
			.name = "PACKED_RGB_565",
			.fourcc = V4L2_PIX_FMT_RGB565,
			.depth = 16,
		},
		{
			.name = "YUYV 4:2:2",
			.fourcc = V4L2_PIX_FMT_YUYV,
			.depth = 16,
		},
};

struct camif_buf
{
//	unsigned int order;
	unsigned long virt_base;
	unsigned long phy_base;
};

struct ov9650_dev {
	struct list_head       	ov9650_devlist;

	struct v4l2_device 	   	v4l2_dev;
	struct video_device      *vfd;

	struct ov9650_fmt       *fmt;
	unsigned int              	width;
	unsigned int 			height;
	unsigned long 		buf_size;

	struct camif_buf img_buf[frame_count];
	struct videobuf_queue  vb_vidq;


	spinlock_t         slock;
	struct mutex	   mutex;
};

static irqreturn_t ov9650_irq_codec(int irq, void *dev_id) 
{
	/*clear interrupt*/
	*(S3C_CAM + CIGCTRL) |= 1<<19;

	cam_wq = 1;
	printk(KERN_ALERT "irq : %s\n", __FUNCTION__);
	wake_up_interruptible(&cam_wait_queue);

	return IRQ_HANDLED;
}

static unsigned int current_frame = 0;
static irqreturn_t ov9650_irq_prev(int irq, void *dev_id) 
{

	/*clear interrupt*/
	*(S3C_CAM + CIGCTRL) |= 1<<18;
	*VIC0INTENCLEAR &= ~(1<<4);

	/*setting set current frame number*/
	current_frame = (((*(S3C_CAM + CIPRSTATUS))>>26) & 0x3);

	cam_wq = 1;
	wake_up_interruptible(&cam_wait_queue);

	return IRQ_HANDLED;
}
static int vidioc_querycap(struct file *file, void  *priv,
					struct v4l2_capability *cap)
{
	struct ov9650_dev *dev = video_drvdata(file);

	printk(KERN_ALERT "%s\n", __FUNCTION__);
	strcpy(cap->driver, "ov9650");
	strcpy(cap->card, "ov9650");
	strlcpy(cap->bus_info, dev->v4l2_dev.name, sizeof(cap->bus_info));
	cap->version = OV9650_VERSION;
	cap->capabilities = V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_STREAMING | \
			    V4L2_CAP_READWRITE;
	return 0;
}

static int vidioc_enum_fmt_vid_cap(struct file *file, void  *priv,
					struct v4l2_fmtdesc *f)
{
	struct ov9650_fmt *fmt;

	printk(KERN_ALERT "%s\n", __FUNCTION__);
	if (f->index >= ARRAY_SIZE(formats))
		return -EINVAL;

	fmt = &formats[f->index];

	strlcpy(f->description, fmt->name, sizeof(f->description));
	f->pixelformat = fmt->fourcc;
	return 0;
}

static int vidioc_g_fmt_vid_cap(struct file *file, void *priv,
					struct v4l2_format *f)
{
	struct ov9650_dev *dev = video_drvdata(file);

	printk(KERN_ALERT "%s\n", __FUNCTION__);
	f->fmt.pix.width        = dev->width;
	f->fmt.pix.height      	= dev->height;
	f->fmt.pix.field        = dev->vb_vidq.field;
	f->fmt.pix.pixelformat  = dev->fmt->fourcc;
	f->fmt.pix.bytesperline = (f->fmt.pix.width * 32) >> 3;
	f->fmt.pix.sizeimage 	= f->fmt.pix.height * f->fmt.pix.bytesperline;

	return 0;
}

static struct ov9650_fmt *get_format(struct v4l2_format *f)
{
	struct ov9650_fmt *fmt;
	unsigned int k;

	printk(KERN_ALERT "%s\n", __FUNCTION__);
	for (k = 0; k < ARRAY_SIZE(formats); k++) {
		fmt = &formats[k];
		if (fmt->fourcc == f->fmt.pix.pixelformat)
			break;
	}

	if (k == ARRAY_SIZE(formats))
		return NULL;
	
	return &formats[k];
}

static int vidioc_try_fmt_vid_cap(struct file *file, void *priv,
			struct v4l2_format *f)
{
//	struct ov9650_dev *dev = video_drvdata(file);
	struct ov9650_fmt *fmt;
//	enum v4l2_field field;

	printk(KERN_ALERT "%s\n", __FUNCTION__);
	fmt = get_format(f);
	if (!fmt) {
		printk(KERN_ALERT "Fourcc format (0x%08x) invalid.\n",
			f->fmt.pix.pixelformat);
		return -EINVAL;
	}

//	f->fmt.pix.field = field;
//	v4l_bound_align_image(&f->fmt.pix.width, 48, MAX_WIDTH, 2,
//			      &f->fmt.pix.height, 32, MAX_HEIGHT, 0, 0);
	f->fmt.pix.bytesperline =
		(f->fmt.pix.width * 32) >> 3;
	f->fmt.pix.sizeimage =
		f->fmt.pix.height * f->fmt.pix.bytesperline;

	bytesperline = f->fmt.pix.bytesperline;
		
	return 0;
}

static int vidioc_s_fmt_vid_cap(struct file *file, void *priv,
					struct v4l2_format *f)
{
	struct ov9650_dev *dev = video_drvdata(file);
	int ret = 0;

	printk(KERN_ALERT "%s\n", __FUNCTION__);
//	mutex_lock(&q->vb_lock);

	ret = vidioc_try_fmt_vid_cap(file, priv, f);

	dev->fmt = get_format(f);
	dev->width = f->fmt.pix.width;
	dev->height = f->fmt.pix.height;
	dev->vb_vidq.field = f->fmt.pix.field;
	f->fmt.pix.sizeimage = f->fmt.pix.height * f->fmt.pix.bytesperline;
		
	dst_width = f->fmt.pix.width;
	dst_height = f->fmt.pix.height;
	dev->buf_size = f->fmt.pix.sizeimage;

	//target img format of preview DMA: 640x480 with no ration
	*(S3C_CAM + CIPRTRGFMT) |= (0x3<<29) | (dst_width<<16) | (dst_height<<0);
	*(S3C_CAM + CIPRTRGFMT) &= ~(0x3<<14);

//	mutex_unlock(&q->vb_lock);
	return ret;
}

static int vidioc_reqbufs(struct file *file, void *priv,
			  struct v4l2_requestbuffers *p)
{
//	struct ov9650_dev *dev = video_drvdata(file);
	int i = 0;

	printk(KERN_ALERT "%s\n", __FUNCTION__);
	memset(dev->img_buf, 0, sizeof(dev->img_buf));
	for (i = 0; i < 4; i++) {
		dev->img_buf[i].virt_base = (unsigned long)kzalloc(dev->buf_size, GFP_DMA);
		
		if (dev->img_buf[i].virt_base == (unsigned long)NULL) {
			printk(KERN_ALERT "%s: failed mem err\n", __func__);
			goto mem_err;
		}
		dev->img_buf[i].phy_base = __virt_to_phys(dev->img_buf[i].virt_base);
	}
	*(S3C_CAM + CIPRYSA1) = dev->img_buf[0].phy_base;
	*(S3C_CAM + CIPRYSA2) = dev->img_buf[1].phy_base;
	*(S3C_CAM + CIPRYSA3) = dev->img_buf[2].phy_base;
	*(S3C_CAM + CIPRYSA4) = dev->img_buf[3].phy_base;

	return 0;

mem_err:
	for (;i >= 0; i--) {
		kfree((void *)dev->img_buf[i].virt_base);
		dev->img_buf[i].phy_base = (unsigned long)NULL;
	}
	return -ENOMEM;
}

static int vidioc_querybuf(struct file *file, void *priv, struct v4l2_buffer *p)
{
//	struct ov9650_dev *dev = video_drvdata(file);

//	return videobuf_querybuf(&dev->vb_vidq, p);
	printk(KERN_ALERT "%s\n", __FUNCTION__);
	return 0;
}

static int vidioc_qbuf(struct file *file, void *priv, struct v4l2_buffer *p)
{
//	struct ov9650_dev *dev = video_drvdata(file);

//	return videobuf_qbuf(&dev->vb_vidq, p);
	printk(KERN_ALERT "%s\n", __FUNCTION__);
	return 0;
}

static int vidioc_dqbuf(struct file *file, void *priv, struct v4l2_buffer *p)
{
//	struct ov9650_dev *dev = video_drvdata(file);

//	return videobuf_dqbuf(&dev->vb_vidq, p,
//				file->f_flags & O_NONBLOCK);
	printk(KERN_ALERT "%s\n", __FUNCTION__);
	return 0;
}

static void ov9650_get_burst(unsigned long width, unsigned long *mburst,
				unsigned long *rburst)
{
	unsigned int tmp;

//	tmp = (width / 4) & 0xf;
	tmp = (width/4)%16;
	switch (tmp) {
	case 0:
		*mburst = 16;
		*rburst = 16;
		break;

	case 4:
		*mburst = 16;
		*rburst = 4;
		break;

	case 8:
		*mburst = 16;
		*rburst = 8;
		break;

	default:
		tmp = (width / 4) % 8;

		if (tmp == 0) {
			*mburst = 8;
			*rburst = 8;
		} else if (tmp == 4) {
			*mburst = 8;
			*rburst = 4;
		} else {
			tmp = (width / 4) % 4;
			*mburst = 4;
			*rburst = (tmp) ? tmp : 4;
		}

		break;
	}
}

/*calculate scaler raion: width,height*/
static int ov9650_get_scaler_factor(u32 src, u32 tar, u32 *ratio, u32 *shift)
{
	if (src >= tar * 64) {
		return -EINVAL;
	} else if (src >= tar * 32) {
		*ratio = 32;
		*shift = 5;
	} else if (src >= tar * 16) {
		*ratio = 16;
		*shift = 4;
	} else if (src >= tar * 8) {
		*ratio = 8;
		*shift = 3;
	} else if (src >= tar * 4) {
		*ratio = 4;
		*shift = 2;
	} else if (src >= tar * 2) {
		*ratio = 2;
		*shift = 1;
	} else {
		*ratio = 1;
		*shift = 0;
	}

	return 0;
}

static int ov9650_set_scaler_info(void)
{
	int tx, ty, sx, sy;
	int ret;
	
	tx = dst_width;
	ty = dst_height;
	if (tx <= 0 || ty <= 0) {
		printk("invalid target size: %d x %d", tx, ty);
		return -EINVAL;
	}

	sx = src_width;
	sy = src_height;
	if (sx <= 0 || sy <= 0) {
		printk("invalid source size: %d x %d", sx, sy);
		return -EINVAL;
	}

	sc->real_width = sx;
	sc->real_height = sy;

	ret = ov9650_get_scaler_factor(sx, tx, &sc->pre_hratio, &sc->hfactor);
	if (ret)
		return ret;

	ret = ov9650_get_scaler_factor(sy, ty,  &sc->pre_vratio, &sc->vfactor);
	if (ret)
		return ret;

	sc->pre_dst_width = sx / sc->pre_hratio;
	sc->pre_dst_height = sy / sc->pre_vratio;

	sc->main_hratio = (sx << 8) / (tx << sc->hfactor);
	sc->main_vratio = (sy << 8) / (ty << sc->vfactor);

	sc->scaleup_h = (tx >= sx) ? 1 : 0;
	sc->scaleup_v = (ty >= sy) ? 1 : 0;

	return 0;
}

static void ov9650_set_scaler_pr(void)
{
	unsigned long shfactor;

	printk(KERN_ALERT "%s: before set scaler info\n", __FUNCTION__);
	sc = kmalloc(sizeof (struct ov9650_scaler), GFP_KERNEL);
	if (sc == NULL) {
		
		printk(KERN_ALERT "%s failed to malloc for sc\n", __FUNCTION__);
	}
	sc->bypass = 0;
	sc->scaleup_h = 1;
	sc->scaleup_v = 1;

	ov9650_set_scaler_info();

	shfactor = 10 - (sc->hfactor + sc->vfactor);
	*(S3C_CAM + CIPRSCPRERATIO) = (shfactor<<28) | (sc->pre_hratio<<16) | (sc->pre_vratio<<0);
	*(S3C_CAM + CIPRSCPREDST) 	= (sc->pre_dst_width<<16) | (sc->pre_dst_height<<0);
	*(S3C_CAM + CIPRSCCTRL )	|= (sc->bypass<<31) | (sc->scaleup_h<<30) | (sc->scaleup_v<<29) |
									(sc->main_hratio<<16) | (0x2<<11) | (sc->main_vratio<<0);

}

static int vidioc_streamon(struct file *file, void *priv, enum v4l2_buf_type i)
{
//	struct ov9650_dev *dev = video_drvdata(file);
	unsigned long yburst_m, yburst_r;

	printk(KERN_ALERT "%s\n", __FUNCTION__);
	*(S3C_CAM + CISRCFMT) |= (1<<31) | (src_width<<16) | (0x2<<14) | (src_height<<0);//CbYCrY
	*(S3C_CAM + CISRCFMT) &= ~(0x3<<14);// YCbYCr

	//clear preview overflow, enable window offset but set to 0
	*(S3C_CAM + CIWDOFST) |= (1<<31) | (1<<30) | (1<<27) | (0xf<<12);
	*(S3C_CAM + CIWDOFST) &= ~((0x7ff<<16) | (0x7ff));
	*(S3C_CAM + CIWDOFST2) &= ~((0x7ff<<16) | (0x7ff));

	/*testpattern, and inverse polarity*/
	*(S3C_CAM + CIGCTRL)  |= (1<<29);
	*(S3C_CAM + CIGCTRL) &= ~((0x1f<<24));
	
	ov9650_get_burst(bytesperline, &yburst_m, &yburst_r);
	
	*(S3C_CAM + CIPRCTRL) |= (yburst_m<<19) | (yburst_r<<14);

	ov9650_set_scaler_pr();

	*(S3C_CAM + CIPRTAREA) = dst_width * dst_height;
	*(S3C_CAM + CIIMGCPT)  = (1<<31) | (1<<29);
	*(S3C_CAM + CIPRSCCTRL) |= (1<<15);
	
	return 0;
}
static int vidioc_streamoff(struct file *file, void *priv, enum v4l2_buf_type i)
{
//	struct ov9650_dev *dev = video_drvdata(file);
	int ret = 0;

	printk(KERN_ALERT "%s\n", __FUNCTION__);
	*(S3C_CAM + CIPRSCCTRL) &= ~(1<<15);
	*(S3C_CAM + CIIMGCPT) &= ~((1<<31)|(1<<29));
	
	return ret;
}

static int ov9650_open(struct inode *inode, struct file *file)
{
	return 0;
}

static ssize_t ov9650_read(struct file *file, char __user *buf,
		    size_t nbytes, loff_t *ppos)
{
//	struct ov9650_dev *dev = video_drvdata(file);
	size_t end;

	end = min_t(size_t, dev->buf_size, nbytes);

	wait_event_interruptible(cam_wait_queue, cam_wq);

	printk(KERN_ALERT "[READ]  current_frame: %d\n", current_frame);
	if(copy_to_user(buf, (void *)(dev->img_buf[current_frame].virt_base), end))
		return -EFAULT;

	cam_wq = 0;

	return end;
}

static void ov9650_cfg_gpio(void)
{
	GPFCON	= ioremap (0x7f0080a0, 4);
	GPFDAT	= ioremap (0x7f0080a4, 4);
	GPFPUD	= ioremap (0x7f0080a8, 4);
	VIC0INTENCLEAR = ioremap(0x71200014, 4);
	
	S3C_CAM = ioremap(0x78000000, 1024);

	*GPFCON = 0x2aaaaaa;
	*GPFDAT = 0;
	*GPFPUD = 0x2aaaaaa;
}

/*camera interface software reset*/
static void ov9650_reset_camif(void)
{
	printk("[CAM]Reset camera1.\n");
	*(S3C_CAM + CISRCFMT)  |= (1<<31);
	mdelay(10);
	
	*(S3C_CAM + CIGCTRL) |= (1<<31) | (1<<20);
	mdelay(10);

	*(S3C_CAM + CIGCTRL) &= ~(1<<31);
	mdelay(10);
}

/*external camera processor input*/
void ov9650_select_cam(void)
{
	*(S3C_CAM + CIGCTRL) &= ~(0x3<<27);
}

/*enable camif clock and set camclock to 24MHz*/
static int ov9650_cfg_clk(void)
{
	struct clk *cam_clk, *cam_if;
	
	cam_if = clk_get(NULL, "fimc");
	cam_if->rate = 133000000;
	if ((!cam_if) || IS_ERR(cam_if)) {
		printk(KERN_ALERT "failed to get source clock of fimc\n");
		return -1;
	}
	clk_enable(cam_if);

	cam_clk = clk_get(NULL, "sclk_cam");
	if(!cam_clk || IS_ERR(cam_clk)) {
		printk(KERN_ALERT "failed to get CAM clock source\n");
		return -1;
	}
	clk_disable(cam_clk);

	clk_set_rate(cam_clk, 24000000);
	cam_clk->rate = 24000000;
	clk_enable(cam_clk);

	return 0;
}

/*external camera reset*/
static void ov9650_reset_sensor(void)
{
	printk(KERN_ALERT "%s: reset camera\n", __FUNCTION__);

	*(S3C_CAM + CIGCTRL) |= (1<<30);
	mdelay(200);
	*(S3C_CAM + CIGCTRL) &= ~(1<<30);
	mdelay(200);
}

static unsigned char s3c_cam_i2c_read(struct i2c_client *client, unsigned char subaddr)
{
	u8 buf[1];
	struct i2c_msg msg = {client->addr, 0, 1, buf};
	int ret;
	
	buf[0] = subaddr;

	ret = i2c_transfer(client->adapter, &msg, 1) == 1 ? 0 : -EIO;
	if (ret == -EIO) {
		printk(KERN_ALERT "i2c transfer error\n");
		return -EIO;
	}

	msg.flags = I2C_M_RD;
	ret = i2c_transfer(client->adapter, &msg, 1) == 1 ? 0 : -EIO;

	return buf[0];
}

static int s3c_cam_i2c_write(struct i2c_client *client, unsigned char subaddr,
										unsigned char val)
{
	u8 buf[2];
	struct i2c_msg msg = {client->addr, 0, 2, buf};

	buf[0] = subaddr;
	buf[1] = val;

	return i2c_transfer(client->adapter, &msg, 1) == 1 ? 0 : -EIO;
}


/*configure internal camera registers*/
static int ov9650_init_reg(void)
{
	int i, ret;
	unsigned int cam_id;
	unsigned int reg_size;
	
	cam_id = s3c_cam_i2c_read(ov9650_i2c_client, 0x0a)<<8;
	cam_id |= s3c_cam_i2c_read(ov9650_i2c_client, 0x0b);

	reg_size = sizeof (OV965X_init_reg)/sizeof (OV965X_init_reg[0]);
	for (i = 0; i < reg_size; i++) {
		ret = s3c_cam_i2c_write(ov9650_i2c_client, OV965X_init_reg[i].subaddr, OV965X_init_reg[i].value);
		mdelay(2);
	}

	printk(KERN_ALERT "Product ID: OV%0x\n", cam_id);

	return ret;
}

/*init everything about hardware stuff*/
static int ov9650_hw_setup(void)
{
	int ret;
	
	printk(KERN_ALERT "%s\n", __FUNCTION__);

	ov9650_cfg_gpio();

	ov9650_reset_camif();
	ov9650_select_cam();

	ret = ov9650_cfg_clk();
	if (ret != 0) {
		printk(KERN_ALERT "%s: failed to config clock\n", __FUNCTION__);
		return ret;
	}
	ov9650_reset_sensor();

	ret = ov9650_init_reg();
	if (ret != 0) {
		printk(KERN_ALERT "%s: failed to init reg\n", __FUNCTION__);
		return ret;
	}
	
	printk(KERN_ALERT "hw init done\n");
	return 0;
}

static const struct v4l2_file_operations ov9650_fops = {
	.owner	= THIS_MODULE,
	.open	= ov9650_open,
	.read	= ov9650_read,
//	.poll		= ov9650_poll,
//	.release	= ov9650_release,
	.unlocked_ioctl = video_ioctl2,
};

static const struct v4l2_ioctl_ops ov9650_ioctl = {
	.vidioc_querycap 			= vidioc_querycap,
	.vidioc_enum_fmt_vid_cap  	= vidioc_enum_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap     	= vidioc_g_fmt_vid_cap,
	.vidioc_try_fmt_vid_cap  	= vidioc_try_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap     	= vidioc_s_fmt_vid_cap,

	.vidioc_reqbufs       		= vidioc_reqbufs,
	.vidioc_querybuf     		= vidioc_querybuf,
	.vidioc_qbuf          			= vidioc_qbuf,
	.vidioc_dqbuf         		= vidioc_dqbuf,
	
	.vidioc_streamoff 			= vidioc_streamoff,
	.vidioc_streamon 			= vidioc_streamon,
};

void ov9650_device_release(struct video_device *vdev)
{
	int i;

	for (i = 0;i < 4; i++) {
		kfree((void *)dev->img_buf[i].virt_base);
		dev->img_buf[i].phy_base = (unsigned long)NULL;
	}
	kfree(vdev);
}

static struct video_device ov9650_tmp = {
	.name   		= "ov9650",
	.fops     		= &ov9650_fops,
	.ioctl_ops    	= &ov9650_ioctl,
	.release 		= ov9650_device_release,
};

static int ov9650_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	int ret;

//	memset(img_buf, 0, sizeof (img_buf));
	ov9650_i2c_client = client;
	printk(KERN_ALERT "i2c name : %s\n", client->name);

	ret = ov9650_hw_setup();
	if (ret < 0)
		printk("failed to setup hw\n");
	
	dev = kmalloc(sizeof (*dev), GFP_KERNEL);
	if (!dev) {
		printk(KERN_ALERT " mem alloc err, %s\n", __FUNCTION__);
		return -ENOMEM;
	}
	
	snprintf(dev->v4l2_dev.name, sizeof(dev->v4l2_dev.name),
			"%s", OV9650_MODULE_NAME);
	ret = v4l2_device_register(NULL, &dev->v4l2_dev);
	dev->fmt = &formats[0];
	dev->width = src_width;
	dev->height = src_height;	
	
	if (request_irq(IRQ_CAMIF_C, ov9650_irq_codec, IRQF_DISABLED , "CAM_C", NULL))
		printk("%s:request_irq failed\n", __func__);
	if (request_irq(IRQ_CAMIF_P, ov9650_irq_prev, IRQF_DISABLED , "CAM_P", NULL))
		printk("%s:request_irq failed\n", __func__);
	
	/*video device init, setup, and register*/
	vfd = video_device_alloc();
	if (!vfd)
		printk("%s, video alloc err\n", __FUNCTION__);
	*vfd = ov9650_tmp;
	vfd->v4l2_dev = &dev->v4l2_dev;
	ret = video_register_device(vfd, VFL_TYPE_GRABBER, -1);
	if (ret < 0)
		goto del_vdev;

	video_set_drvdata(vfd, dev);
	dev->vfd = vfd;

	return ret;
	
del_vdev:
	video_device_release(vfd);
	return ret;
}

static int ov9650_remove(struct i2c_client *client)
{
	printk(KERN_ALERT "%s\n", __FUNCTION__);

	iounmap(GPFCON);
	iounmap(GPFDAT);
	iounmap(GPFPUD);
	iounmap(S3C_CAM);
	iounmap(VIC0INTENCLEAR);

	free_irq(IRQ_CAMIF_C, NULL);
	free_irq(IRQ_CAMIF_P, NULL);

	video_unregister_device(vfd);
	v4l2_device_unregister(&dev->v4l2_dev);
	kfree(dev);

	return 0;
}

struct i2c_device_id  ov9650_id[] = {
	{"ov9650", 0},
	{}
};
	
static struct i2c_driver ov9650_driver = {
	.driver	= {
		.name	= "ov9650",
		.owner	= THIS_MODULE,
	},
	.probe		= ov9650_probe,
	.remove		= ov9650_remove,
	.id_table	= ov9650_id,
};

static int __init ov9650_drv_init(void)
{

	return i2c_add_driver(&ov9650_driver);
}

static void __exit ov9650_drv_exit(void)
{
	i2c_del_driver(&ov9650_driver);
}

module_init(ov9650_drv_init);
module_exit(ov9650_drv_exit);
MODULE_LICENSE("GPL");
