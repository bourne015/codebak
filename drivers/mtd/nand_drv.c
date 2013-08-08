#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/clk.h>
#include <linux/slab.h>

#include <linux/mtd/mtd.h>
#include <linux/mtd/nand.h>
#include <linux/mtd/nand_ecc.h>
#include <linux/mtd/partitions.h>

#include <asm/io.h>

#define S3C_NFDATA 0x10

static struct mtd_partition s3c_nand_partitions[] = {
	[0] = {
		.name = "bootloader",
		.size   = 0x100000,
		.offset = 0x0,
	},
	[1] = {
		.name  = "kernel",
		.size    = 0x500000,
		.offset  = MTDPART_OFS_APPEND,
	},
	[2] = {
		.name = "rootfs",
		.size   = 0x5000000,
		.offset = MTDPART_OFS_APPEND,
	},
};
/*
static struct s3c_platform_nand {
	int tacls;
	int twrph0;
	int twrph1;
};
*/
static struct s3c_nand_info {
	/* mtd info */
	struct nand_hw_control		controller;
	struct s3c_platform_nand	*platform;

	/* device info */
	struct device		*device;
	struct resource		*area;
	struct clk		*clk;
	void __iomem		*regs;
};

static struct s3c_nand_info s3c_nand;
static struct mtd_info *s3c_mtd = NULL;

/*
static void s3c_nand_hwcontrol(struct mtd_info *mtd, int dat, unsigned int ctrl)
{
	
}

static int s3c_nand_device_ready(struct mtd_info *mtd)
{
	return 0;
}
*/
static int s3c_nand_probe(struct platform_device *pdev)
{
	int size;
	int ret;
	struct resource *res;
	struct nand_chip *nand;
	
	s3c_nand.clk = clk_get(&pdev->dev, "nand");
	clk_enable(s3c_nand.clk);
	printk(KERN_ALERT "clk ok!\n");

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	size = res->end - res->end + 1;
	printk(KERN_ALERT "get resource ok!\n");

	s3c_nand.regs = request_mem_region(res->start, size, pdev->name);
	s3c_nand.device = &pdev->dev;
	s3c_nand.regs = ioremap(res->start, size);
	s3c_nand.platform = pdev->dev.platform_data;
	printk(KERN_ALERT "regs remap ok!\n");

	s3c_mtd = kmalloc(sizeof(struct nand_chip) + sizeof(struct mtd_info),
				GFP_KERNEL);
	if (s3c_mtd == NULL) {
		printk(KERN_ERR " failed to alloc mtd_info");
		return -ENOMEM;
	}

	printk(KERN_ALERT "alloc ok!\n");
	nand = (struct nand_chip *)(&s3c_mtd[1]);
	printk(KERN_ALERT "nand_chip ok!\n");
	memset(s3c_mtd, 0, sizeof(struct mtd_info));
	memset(nand, 0, sizeof(struct nand_chip));
	printk(KERN_ALERT "memset ok!\n");
	
	s3c_mtd->priv = nand;
	s3c_mtd->owner = THIS_MODULE;
	nand->IO_ADDR_R = (char *)(s3c_nand.regs + S3C_NFDATA);
	nand->IO_ADDR_W = (char *)(s3c_nand.regs + S3C_NFDATA);
	printk(KERN_ALERT "IO_ADDR_RW ok!\n");
//	nand->cmd_ctrl    = s3c_nand_hwcontrol;
//	nand->dev_ready  = s3c_nand_device_ready;	

	if (nand_scan(s3c_mtd, 1)) {
		printk(KERN_ALERT "nand error!\n");
		ret = -ENXIO;
		goto exit_error;
	}
	printk(KERN_ALERT "all ok!\n");
	
	/* Register the partitions */
	//add_mtd_partitions(s3c_mtd, s3c_nand_partitions, 3);

exit_error:
	return ret;
}

static int s3c_nand_release(struct platform_device *pdev)
{
	kfree(s3c_mtd);
	
	return 0;
}

struct platform_driver s3c_nand_driver = {
	.probe = s3c_nand_probe,
	.remove = s3c_nand_release,
	.driver = {
		.name = "ok6410-nand",
		.owner = THIS_MODULE,
	},
};

static int __init s3c_nand_init(void)
{
	return platform_driver_register(&s3c_nand_driver);
}

static void __exit s3c_nand_exit(void)
{
	platform_driver_unregister(&s3c_nand_driver);
}

module_init(s3c_nand_init);
module_exit(s3c_nand_exit);

MODULE_LICENSE("GPL");
