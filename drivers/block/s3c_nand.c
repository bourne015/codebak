#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/ioport.h>
#include <linux/err.h>

#include <linux/clk.h>
#include <linux/mtd/mtd.h>
#include <linux/mtd/nand.h>
#include <linux/mtd/nand_ecc.h>
#include <linux/mtd/partitions.h>

#include <asm/io.h>

struct s3c_nand_regs {
	unsigned long	NFCONF;
	unsigned long	NFCONT;
	unsigned long	NFCMMD;
	unsigned long	NFADDR;
	unsigned long	NFDATA;
	unsigned long	NFMECCD0;
	unsigned long	NFMECCD1;
	unsigned long	NFSECCD;
	unsigned long	NFSBLK;
	unsigned long	NFEBLK;
	unsigned long	NFSTAT;
	unsigned long	NFECCERR0;
	unsigned long	NFECCERR1;
	unsigned long	NFMECC0;
	unsigned long	NFMECC1;
	unsigned long	NFSECC;
	unsigned long	NFMLCBITPT;
	unsigned long	NF8ECCERR0;
	unsigned long	NF8ECCERR1;
	unsigned long	NF8ECCERR2;
	unsigned long	NFM8ECC0;
	unsigned long	NFM8ECC1;
	unsigned long	NFM8ECC2;
	unsigned long	NFM8ECC3;
	unsigned long	NFMLC8BITPT;
};

static struct nand_chip *nand;
static struct mtd_info *s3c_mtd = NULL;
static struct s3c_nand_regs *s3c_nand_regs;

static struct mtd_partition s3c_nand_parts[] = {
	[0] = {
        	.name   = "Bootloader",
        	.size   = 0x00040000,
		.offset	= 0,
	},

	[1] = {
        	.name   = "params",
        	.offset = MTDPART_OFS_APPEND,
        	.size   = 0x00020000,
	},

	[2] = {
        	.name   = "kernel",
        	.offset = MTDPART_OFS_APPEND,
        	.size   = 0x00200000,
	},

	[3] = {
        	.name   = "root",
        	.offset = MTDPART_OFS_APPEND,
        	.size   = MTDPART_SIZ_FULL,
	}
};

static void s3c_select_chip(struct mtd_info *mtd, int chipnr)
{
	if (chipnr == -1)
		s3c_nand_regs->NFCONT |= (1<<1); 
	else
		s3c_nand_regs->NFCONT &= ~(1<<1);
printk(KERN_ALERT "select done\n");
}

static void s3c_nand_hwcontrol(struct mtd_info *mtd, int dat, unsigned int ctrl)
{
	if (ctrl & NAND_CLE)
		s3c_nand_regs->NFCMMD	= dat;
	else
		s3c_nand_regs->NFADDR	= dat;
printk(KERN_ALERT "cmd done\n");
}

static int s3c_nand_device_ready(struct mtd_info *mtd)
{
printk(KERN_ALERT "ready\n");
	return (s3c_nand_regs->NFSTAT & 0x1);
}

static __init int s3c_nand_init(void)
{
	struct clk *clk;

	clk = clk_get(NULL, "nand");
	if (IS_ERR(clk)) {
		printk("failed to get clk\n");
		return -ENOMEM;
	}
	clk_enable(clk);
	
	s3c_mtd = kmalloc(sizeof(struct nand_chip) + sizeof(struct mtd_info),
			GFP_KERNEL);
	if (!s3c_mtd) {
		printk("Unable to allocate nand_chip dev structure.\n");
		return -ENOMEM;
	}
	memset((char *)s3c_mtd, 0, sizeof(struct nand_chip) +
			sizeof(struct mtd_info));
	nand = (struct nand_chip *)(&s3c_mtd[1]);
	
	s3c_nand_regs = ioremap(0x70200000, sizeof(s3c_nand_regs));

	nand->select_chip	= s3c_select_chip;
//	nand->IO_ADDR_R		= (char *)(s3c_nand_regs->NFDATA);
//	nand->IO_ADDR_W		= (char *)(s3c_nand_regs->NFDATA);
	nand->IO_ADDR_R		= &(s3c_nand_regs->NFDATA);
	nand->IO_ADDR_W		= &(s3c_nand_regs->NFDATA);
	nand->cmd_ctrl		= s3c_nand_hwcontrol;
	nand->dev_ready		= s3c_nand_device_ready;		
//	nand->options		= 0;	
	nand->ecc.mode		= NAND_ECC_SOFT_BCH;

#define TACLS    0
#define TWRPH0   2
#define TWRPH1   1
	s3c_nand_regs->NFCONF = (TACLS<<12) | (TWRPH0<<8) | (TWRPH1<<4);

	s3c_nand_regs->NFCONT = (1<<1) | (1<<0);
/*
	s3c_mtd	= kzalloc(sizeof(struct mtd_info), GFP_KERNEL);
	if (!s3c_mtd) {
		printk("Unable to allocate NAND MTD dev structure.\n");
		return -ENOMEM;
	}
	memset((char *) s3c_mtd, 0, sizeof(struct nand_chip));
*/

	s3c_mtd->owner	= THIS_MODULE;
	s3c_mtd->priv	= nand;
printk(KERN_ALERT "666\n");

	if (nand_scan(s3c_mtd, 1)) {
		printk(KERN_ALERT "nand_scan err\n");
		return -ENXIO;
	}
printk(KERN_ALERT "done\n");
	
//	add_mtd_partitions(s3c_mtd, s3c_nand_parts, 4);

	return 0;
}

static __exit void s3c_nand_exit(void)
{
//	nand_release(s3c_mtd);
	iounmap(s3c_nand_regs);
	kfree(s3c_mtd);
}

module_init(s3c_nand_init);
module_exit(s3c_nand_exit);

MODULE_LICENSE("GPL");
