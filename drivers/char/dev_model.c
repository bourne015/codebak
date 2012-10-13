#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/poll.h>
#include <linux/wait.h>
#include <asm/io.h>
#include <linux/interrupt.h>
#include <linux/sched.h>

#include <asm/irq.h>
#include <asm/uaccess.h>
#include <linux/irq.h>
#include <linux/miscdevice.h>
#include <linux/platform_device.h>
#include <mach/hardware.h>
#include <linux/errno.h>
#include <mach/regs-gpio.h>
#include <linux/delay.h>

MODULE_LICENSE("GPL"); 

/*MAGIC KEY*/
#define DEV_MAGIC 'k'

/*CMD*/
#define PRINT	_IO(DEV_MAGIC,1)
#define GETDATA	_IOR(DEV_MAGIC,2,int)
#define SETDATA	_IOW(DEV_MAGIC,3,int)

#define DEV_CMD_MAX	3

#define DEVICE_NAME "Yaoxing_Test"
static int dev_major=201;

module_param(dev_major,int,S_IRUGO);

struct cdev cdev;

#define ULCON0		(0x7F005000)
#define	UCON0		(0x7F005004)
#define UFCON0		(0x7F005008)
#define	UMCON0		(0x7F00500C)
#define	UTRSTAT0	(0x7F005010)
#define	UERSTAT0	(0x7F005014)
#define	UFSTAT0		(0x7F005018)
#define UMSTAT0		(0x7F00501C)
#define UTXH0		(0x7F005020)
#define URXH0		(0x7F005024)
#define UBRDIV0		(0x7F005028)
#define	UDIVSLOT0	(0x7F00502C)
#define UINTP0		(0x7F005030)
#define UINTSP0		(0x7F005034)
#define UINTM0		(0x7F005038)

#define	ULCON1		(0x7F005400)
#define	UCON1		(0x7F005404)
#define	UFCON1		(0x7F005408)
#define	UMCON1		(0x7F00540C)
#define UTRSTAT1	(0x7F005410)
#define UERSTAT1	(0x7F005414)
#define UFSTAT1		(0x7F005418)
#define	UMSTAT1		(0x7F00541C)
#define UTXH1		(0x7F005420)
#define	URXH1		(0x7F005424)
#define UBRDIV1		(0x7F005428)
#define UDIVSLOT1	(0x7F00542C)
#define	UINTP1		(0x7F005430)
#define	UINTSP1		(0x7F005434)
#define	UINTM1		(0x7F005438)

#define ULCON2		(0x7F005800)
#define UCON2		(0x7F005804)
#define UFCON2		(0x7F005808)
#define	UTRSTAT2	(0x7F005810)
#define	UERSTAT2	(0x7F005814)
#define	UFSTAT2		(0x7F005818)
#define	UTXH2		(0x7F005820)
#define	URXH2		(0x7F005824)
#define	UBRDIV2		(0x7F005828)
#define UDIVSLOT2	(0x7F00582C)
#define UINTP2		(0x7F005830)
#define	UINTSP2		(0x7F005834)
#define	UINTM2		(0x7F005838)

#define ULCON3		(0x7F005C00)
#define	UCON3		(0x7F005C04)
#define	UFCON3		(0x7F005C08)
#define	UTRSTAT3	(0x7F005C10)
#define	UERSTAT3	(0x7F005C14)
#define	UFSTAT3		(0x7F005C18)
#define	UTXH3		(0x7F005C20)
#define URXH3		(0x7F005C24)
#define UBRDIV3		(0x7F005C28)
#define UDIVSLOT3	(0x7F005C2C)
#define	UINTP3		(0x7F005C30)
#define	UINTSP3		(0x7F005C34)
#define	UINTM3		(0x7F005C38)
/*
#define	GPACON		(0x7F008000)
#define GPADAT		(0x7F008004)
#define	GPAPUD		(0x7F008008)
#define	GPACONSLP	(0x7F00800C)
#define	GPAPUDSLP	(0x7F008010)*/

#define	GPBCON		(0x7F008020)
#define GPBDAT		(0x7F008024)
#define	GPBPUD		(0x7F008028)
#define	GPBCONSLP	(0x7F00802C)
#define	GPBPUDSLP	(0x7F008030)


#define CLK_SRC		(0x7E00F01C)
#define	CLK_DIV1	(0x7E00F024)
#define PCLK_GATE	(0x7E00F034)
#define	SCLK_GATE	(0x7E00F038)

void *R_GPBCON,*R_GPBDAT,*R_GPBPUD,*R_GPBCONSLP,*R_GPBPUDSLP;
void *R_ULCON2,*R_UCON2,*R_UFCON2,*R_UTRSTAT2,*R_UERSTAT2,*R_UFSTAT2;
void *R_UTXH2,*R_URXH2,*R_UBRDIV2,*R_UDIVSLOT2,*R_UINTP2,*R_UINTSP2,*R_UINTM2;
//void *R_CLK_SRC,*R_CLK_DIV1,*R_PCLK_GATE,*R_SCLK_GATE;

//static irqreturn_t  Uart2_ReceiveByte(int irq,void *dev_id);
static void Uart2_Unmap(void);
static void Uart2_Remap(void);
static void Uart2_SendByte(char dat);
static void Uart2_ReceiveBytePoll(void);

int dev_ioctl(struct inode *inode,struct file *file,unsigned int cmd,unsigned long arg);
static void device_exit(void);
static int device_init(void);
static int dev_release(struct inode *inode,struct file *filp);
int dev_open(struct inode *inode,struct file *filp);

static int dev_release(struct inode *inode,struct file *filp);
static int err=0;

static struct file_operations dev_fops = {
	.owner	=	THIS_MODULE,
	//.read	=	dev_read,
	//.write=	dev_write,
	.unlocked_ioctl	=	dev_ioctl,
	.open	=	dev_open,
	.release=	dev_release,
};

int dev_open(struct inode *inode,struct file *filp)
{
	
//	filp->private_data=dev;
	printk(KERN_ALERT "dev_open OK!\n");
	return 0;
}

static int dev_release(struct inode *inode,struct file *filp)
{
	printk(KERN_ALERT "dev_release OK!\n");
	return 0;
}

struct class *Yaoxing_class=NULL;

static int device_init(void)
{
	Yaoxing_class=class_create(THIS_MODULE,"Yaoxing_device_driver");
	device_create(Yaoxing_class,NULL,MKDEV(dev_major,0),NULL,"Yaoxing_Test");
	return 0;
}

static void device_exit(void)
{
	device_destroy(Yaoxing_class,MKDEV(dev_major,0));
	class_destroy(Yaoxing_class);
	return;
}

int dev_ioctl(struct inode *inode,struct file *file,unsigned int cmd,unsigned long arg)
{
	return 0;
}

static void Uart2_Remap(void)
{
	if(!request_mem_region(0x7f005800,0x100,"Yaoxing_Uart2"))
	{
		printk(KERN_ALERT "Yaoxing_Uart2 request_mem_region -EBUSY\n");
	}
	else
	{
		printk(KERN_ALERT "Yaoxing_Uart2 request_mem_region PASS\n");
	}
	
/*	R_SCLK_GATE=ioremap(SCLK_GATE,4);
	R_CLK_SRC=ioremap(CLK_SRC,4);
	R_CLK_DIV1=ioremap(CLK_DIV1,4);
	R_PCLK_GATE=ioremap(PCLK_GATE,4);*/
	

	R_GPBCON=ioremap(GPBCON,4);
	R_GPBDAT=ioremap(GPBDAT,4);
	R_GPBPUD=ioremap(GPBPUD,4);
	R_GPBCONSLP=ioremap(GPBCONSLP,4);
	R_GPBPUDSLP=ioremap(GPBPUDSLP,4);

	R_ULCON2=ioremap(ULCON2,4);
	R_UCON2=ioremap(UCON2,4);
	R_UFCON2=ioremap(UFCON2,4);
	R_UTRSTAT2=ioremap(UTRSTAT2,4);
	
	R_UERSTAT2=ioremap(UERSTAT2,4);
	R_UFSTAT2=ioremap(UFSTAT2,4);
	R_UTXH2=ioremap(UTXH2,4);
	R_URXH2=ioremap(URXH2,4);
	
	R_UBRDIV2=ioremap(UBRDIV2,4);
	R_UDIVSLOT2=ioremap(UDIVSLOT2,4);
	R_UINTP2=ioremap(UINTP2,4);
	R_UINTSP2=ioremap(UINTSP2,4);
	R_UINTM2=ioremap(UINTM2,4);
}

static void Uart2_Unmap(void)
{
/*	iounmap(R_SCLK_GATE);
	iounmap(R_CLK_SRC);
	iounmap(R_CLK_DIV1);
	iounmap(R_PCLK_GATE);*/
	
	iounmap(R_GPBCON);
	iounmap(R_GPBDAT);
	iounmap(R_GPBPUD);
	iounmap(R_GPBCONSLP);
	iounmap(R_GPBPUDSLP);

	iounmap(R_ULCON2);
	iounmap(R_UCON2);
	iounmap(R_UFCON2);
	iounmap(R_UTRSTAT2);
	
	iounmap(R_UERSTAT2);
	iounmap(R_UFSTAT2);
	iounmap(R_UTXH2);
	iounmap(R_URXH2);
	
	iounmap(R_UBRDIV2);
	iounmap(R_UDIVSLOT2);
	iounmap(R_UINTP2);
	iounmap(R_UINTSP2);
	iounmap(R_UINTM2);
	
	release_mem_region(0x7f005800,0x100);
}

static irqreturn_t  Uart2_ReceiveByte()//int irq,void *dev_id)
{
	unsigned char tmp8;
	unsigned int tmp16;
	unsigned long tmp32;

	printk(KERN_ALERT "Uart2_ReceiveByte IRQ is asserted!\n");
	tmp32=ioread32(R_UTRSTAT2);
	tmp16=0xf;
	Uart2_SendByte(0x55);
	Uart2_SendByte(0xcc);
	while(tmp16--)
	{
		if((tmp32&0x1)==0x1)
		{
			tmp8=ioread8(R_URXH2);
			printk(KERN_ALERT "Uart2_ReceiveByte IRQ R_URXH2 data is received=%d !\n",tmp8);
			break;
		}
		else
		{
			tmp32=ioread32(R_UTRSTAT2);
			printk(KERN_ALERT "Uart2_ReceiveByte IRQ R_URXH2 wait for data!\n");	
			msleep(1);
		}	
	}	
	
	return IRQ_RETVAL(IRQ_HANDLED);	
	return 1;	
}

static void Uart2_ReceiveBytePoll(void)
{
	unsigned char tmp8;
	unsigned int tmp16;
	unsigned long tmp32;

	printk(KERN_ALERT "Uart2_ReceiveBytePoll is asserted!\n");
	tmp32=ioread32(R_UTRSTAT2);
	tmp16=0xf;
	while(tmp16--)
	{
		if((tmp32&0x1)==0x1)
		{
			tmp8=ioread8(R_URXH2);
			printk(KERN_ALERT "Uart2_ReceiveByte R_URXH2 data is received!\n");
			break;
		}
		else
		{
			tmp32=ioread32(R_UTRSTAT2);
			printk(KERN_ALERT "Uart2_ReceiveByte R_URXH2 wait for data!\n");	
			msleep(1);
		}	
	}	
	
	printk(KERN_ALERT "Uart2 = %d OK\n",tmp8);
}

static void Uart2_SendByte(char dat)
{
//	unsigned char tmp8;
//	unsigned int tmp16;
	unsigned long tmp32;

	printk(KERN_ALERT "Uart2_SendByte entred!\n");
	tmp32=ioread32(R_UTRSTAT2);
	while(!(tmp32&0x2))
	{
		tmp32=ioread32(R_UTRSTAT2);
		mdelay(1);			
	}
	iowrite8(dat,R_UTXH2);
	printk(KERN_ALERT "Uart2_SendByt: %c, good\n", dat);
}

static int __init Uart2_Init(void)
{
//	unsigned char tmp8;
//	unsigned int tmp16;
	unsigned long tmp32;

	printk(KERN_ALERT "Uart2_Init Entred!\n");
	device_init();
	Uart2_Remap();
	printk(KERN_ALERT "Uart2_Remap OK!\n");	

	printk(KERN_ALERT "Uart2_Init Start Setup Registers!\n");
	
	tmp32=ioread32(R_GPBCON);
	tmp32= (tmp32&(0xfffffff0))|(0x22);
	iowrite32(tmp32,R_GPBCON);
	
/*	tmp32=ioread32(R_GPAPUD);
	tmp32=0x00;
	iowrite32(tmp32,R_GPAPUD);
*/

	tmp32=0x03;
	iowrite32(tmp32,R_ULCON2);

	tmp32=((0<<10)|(1<<9)|(1<<8)|(0<<7)|(0<<6)|(0<<5)|(0<<4)|(1<<2)|(1<<0));
	iowrite32(tmp32,R_UCON2);

	tmp32=0;
	iowrite32(tmp32,R_UFCON2);
		
	tmp32=0x22;
	iowrite32(tmp32,R_UBRDIV2);

	tmp32=0xDFDD;
	iowrite32(tmp32,R_UDIVSLOT2);

	printk(KERN_ALERT "Uart2_Init Setup Registers OK!\n");
	printk(KERN_ALERT "Uart2_Init Setup IRQ!\n");
	err=request_irq(IRQ_S3CUART_RX2,Uart2_ReceiveByte,0,"Yaoxing_Uart2",0);/*IRQ_S3CUART_RX1 IRQF_DISABLED   IRQ_TYPE_EDGE_FALLING*/
	printk(KERN_ALERT "Uart2_Init Setup IRQ OK!\n");
	if(err==-EBUSY) 
	{
		printk(KERN_ALERT "Error=-EBUSY\n\n");	
		while(1); 
	}
	else if(err==-EINVAL)
	{
		printk(KERN_ALERT "Error=-INVAL\n\n");
		while(1);
	}

	printk(KERN_ALERT "Uart2_Init OK!\n");

	Uart2_SendByte('1');
	Uart2_ReceiveByte();
	
	Uart2_SendByte('2');
	Uart2_ReceiveByte();

	Uart2_SendByte(3);
	Uart2_ReceiveByte();

	Uart2_SendByte(4);
	Uart2_ReceiveByte();

	Uart2_SendByte(5);
	Uart2_ReceiveByte();

	return 0;
}


static void __exit Uart2_Exit(void)
{
	device_exit();
	disable_irq(IRQ_S3CUART_RX2);
	free_irq(IRQ_S3CUART_RX2,NULL);
	Uart2_Unmap();
	printk(KERN_ALERT "Uart2_Exit OK!\n");   	
}

module_init(Uart2_Init);
module_exit(Uart2_Exit);

MODULE_LICENSE("GPL");
