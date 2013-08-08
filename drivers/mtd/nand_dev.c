#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/platform_device.h>

#include <linux/mtd/mtd.h>
#include <linux/mtd/nand.h>
#include <linux/mtd/nand_ecc.h>
#include <linux/mtd/partitions.h>

#include <asm/io.h>

#define S3C_NAND_BA 0x70200000
#define S3C_NFDATA 0x10

struct s3c_nand_regs {
        unsigned long   NFCONF;
        unsigned long   NFCONT;
        unsigned long   NFCMMD;
        unsigned long   NFADDR;
        unsigned long   NFDATA;
        unsigned long   NFMECCD0;
        unsigned long   NFMECCD1;
        unsigned long   NFSECCD;
        unsigned long   NFSBLK;
        unsigned long   NFEBLK;
        unsigned long   NFSTAT;
        unsigned long   NFECCERR0;
        unsigned long   NFECCERR1;
        unsigned long   NFMECC0;
        unsigned long   NFMECC1;
        unsigned long   NFSECC;
        unsigned long   NFMLCBITPT;
        unsigned long   NF8ECCERR0;
        unsigned long   NF8ECCERR1;
        unsigned long   NF8ECCERR2;
        unsigned long   NFM8ECC0;
        unsigned long   NFM8ECC1;
        unsigned long   NFM8ECC2;
        unsigned long   NFM8ECC3;
        unsigned long   NFMLC8BITPT;
};

static struct resource s3c_nand_resource[] = {
	[0] = {
		.start = S3C_NAND_BA, 
		.end =  S3C_NAND_BA + sizeof(struct s3c_nand_regs) -1,
		.flags = IORESOURCE_MEM,
	},
};

static struct platform_device s3c_nand_dev = {
	.name = "ok6410-nand",
	.id = -1,
	.num_resources = ARRAY_SIZE(s3c_nand_resource),
	.resource = s3c_nand_resource,
};

static int  __init s3c_nand_dev_init(void)
{
	return platform_device_register(&s3c_nand_dev);
}

static void __exit s3c_nand_dev_exit(void)
{
	platform_device_unregister(&s3c_nand_dev);
}

module_init(s3c_nand_dev_init);
module_exit(s3c_nand_dev_exit);

MODULE_LICENSE("GPL");
