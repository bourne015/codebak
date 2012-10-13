#include <linux/module.h>
#include <linux/init.h>

#include <linux/kernel.h>		/* printk() */
#include <linux/slab.h>			/* kmalloc() */
#include <linux/fs.h>			/* everything... */
#include <linux/errno.h>		/* error codes */
#include <linux/types.h>		/* size_t */
#include <linux/fcntl.h>		/* O_ACCMODE */

#include <asm/system.h>			/* cli(), *_flags */
#include <asm/uaccess.h>		/* copy_*_user */

#include <linux/ioctl.h>
#include <linux/device.h>


#include <linux/platform_device.h>
#include <linux/sysrq.h>
#include <linux/tty.h>
#include <linux/tty_flip.h>
#include <linux/serial_core.h>
#include <linux/serial.h>
#include <linux/delay.h>
#include <linux/clk.h>
#include <linux/console.h>
#include <linux/ioport.h>
#include <asm/io.h>
#include <asm/irq.h>
//#include <asm/hardware.h>
//#include <asm/plat-s3c/regs-serial.h>
//#include <asm/arch/regs-gpio.h>
//#include <match/map.h>
//#include <match/regs-gpio.h>
//#include <plat/gpio-cfg.h>



#include <linux/circ_buf.h>				/* 环形缓冲 */

#define DEV_NAME			"gprs_uart"	/* 设备名 */
#define GPRS_UART_MAJOR		0			/* 主设备号 */
#define GPRS_UART_MINOR		0			/* 次设备号 */
#define GPRS_UART_FIFO_SIZE	16			/* 串口FIFO的大小 */
#define DEBUG				KERN_WARNING
#define MAX_BUFFER_SIZE 128				/* 环形缓冲的大小 */
#define MAP_SIZE (0x100)
#define gprs_uart_circ_empty(circ)		((circ)->head == (circ)->tail)
#define gprs_uart_circ_full(circ)		((circ)->head == (circ)->tail + 1)

/* 串口中断号 */
#define TX_IRQ(port) ((port)->irq + 1)
#define RX_IRQ(port) ((port)->irq)

/* 允许串口接收字符的标志 */
#define tx_enabled(port) ((port)->unused[0])
/* 允许串口发送字符的标志 */
#define rx_enabled(port) ((port)->unused[1])

/* 获取寄存器地址 */
#define portaddr(port, reg) ((port)->membase + (reg))

/* read byte */
#define rd_regb(port, reg) (ioread8(portaddr(port, reg)))

/* read int */
#define rd_regl(port, reg) (ioread32(portaddr(port, reg)))

#define wr_regb(port, reg, val) \
	do { iowrite8(val, portaddr(port, reg)); } while(0)
#define wr_regl(port, reg, val) \
	do { iowrite32(val, portaddr(port, reg)); } while(0)

#include <plat/regs-serial.h>
#define S3C6410_PA_UART	       0x7f0050000
#define S3C6410_ULCON         0x00
#define S3C6410_UCON           0x04
#define S3C6410_UFCON          0x08
#define S3C6410_UMCON          0x0c
#define S3C6410_UTRSTAT        0x10
#define S3C6410_UERSTAT        0x14
#define S3C6410_UFSTAT         0x18      //fifo stat
#define S3C6410_UTXH           0x20
#define S3C6410_URXH           0x24      //reveive buffer
#define S3C6410_UBRDIV         0x28      //set the board rate
#define S3C6410_UINTP          0x30      //for intrrupt
#define S3C6410_UINTM          0x38      //intrrupt mask
#define ADDR_SIZE	       0x38

#define S3C6410_GPHCON		0x7F0080E0 


#define S3C6410_UFSTAT_RXFULL (1<<6)
#define S3C6410_UFSTAT_TXFULL (1<<14)
#define S3C6410_UFSTAT_TXSHIFT    (8)
#define S3C6410_UFSTAT_RXSHIFT    (0)
#define S3C6410_UFSTAT_TXMASK     (63<<8)
#define S3C6410_UFSTAT_RXMASK     (63)

#define S3C6410_UTRSTAT_TXE       (1<<2)
#define S3C6410_UTRSTAT_TXFE      (1<<1)
#define S3C6410_UTRSTAT_RXDR      (1<<0)

#define S3C6410_UERSTAT_OVERRUN   (1<<0)
#define S3C6410_UERSTAT_FRAME     (1<<2)
#define S3C6410_UERSTAT_BREAK     (1<<3)
#define S3C6410_UERSTAT_PARITY    (1<<1)

#define S3C6410_UERSTAT_ANY       (S3C2410_UERSTAT_OVERRUN | \
                                   S3C2410_UERSTAT_FRAME | \
                                   S3C2410_UERSTAT_BREAK)

unsigned long *S3C64XX_VA_UART;

int gprs_major = 0;
int gprs_minor = 0;

/* GPRS串口结构体 */
struct gprs_uart
{
	spinlock_t		lock;				/* 串口端口锁 */
	unsigned char	unused[2];
	resource_size_t	mapbase;			/* IO内存基地址 */
	unsigned char __iomem	*membase;	/* 重映射后的IO内存基地址 */
	unsigned int		irq;			/* 中断号 */
	unsigned int		uartclk;		/* 串口时钟 */
	unsigned int		fifosize;		/* FIFO缓冲大小 */	
	struct uart_icount	icount;			/* 计数器 */
};

/* GPRS驱动的device结构体 */
struct gprs_dev
{
	int		size;						/* 环形缓冲的大小 */
	const	char		*name;			/* 设备名 */
	struct	circ_buf	Rx_circ_buf;	/* 环形接收缓冲 */
	struct	circ_buf	Tx_circ_buf;	/* 环形发送缓冲 */		
	struct	gprs_uart	port;			/* 串口结构体 */
	struct	cdev		cdev;			/* 字符设备结构体 */
	struct	class_device *clsdev;    	/* class_device结构体 */	
};

static struct gprs_dev gprs_devices = {
	.name = DEV_NAME,
	.port = {
		.lock		= __SPIN_LOCK_UNLOCKED(gprs_uart_port.lock),
		.irq		= IRQ_S3CUART_RX2,
		.uartclk	= 0,
		.fifosize	= GPRS_UART_FIFO_SIZE,
	}
};

#define to_gprs_dev(x) container_of((x), struct gprs_dev, port)

/* 初始化环形缓存 */
static int gprs_init_buffer(struct gprs_dev *dev)
{
	int ret = 0;

	/* 环形接收缓存为NULL时,为环形接收缓存申请内存空间 */
	if (NULL == dev->Rx_circ_buf.buf)
	{
		dev->Rx_circ_buf.buf = kmalloc(MAX_BUFFER_SIZE * sizeof(char), GFP_KERNEL);
		if (NULL == dev->Rx_circ_buf.buf)
		{
			printk(KERN_ERR "%s :can not get kernel memory!\n", __FUNCTION__);
			ret = -ENOMEM;
			goto out;
		}
	}

	/* 环形发送缓存为NULL时,为环形发送缓存申请内存空间 */
	if (NULL == dev->Tx_circ_buf.buf)
	{
		dev->Tx_circ_buf.buf = kmalloc(MAX_BUFFER_SIZE * sizeof(char), GFP_KERNEL);
		if (NULL == dev->Tx_circ_buf.buf)
		{
			printk(KERN_ERR "%s :can not get kernel memory!\n", __FUNCTION__);
			if (NULL != dev->Rx_circ_buf.buf)
			{
				kfree(dev->Rx_circ_buf.buf);
				dev->Rx_circ_buf.buf = NULL;
			}	
			
			ret = -ENOMEM;
			goto out;
		}
	}

	/* 重置环形缓存 */
	dev->size = MAX_BUFFER_SIZE;
	dev->Rx_circ_buf.head = 0;
	dev->Rx_circ_buf.tail = 0;
	dev->Tx_circ_buf.head = 0;
	dev->Tx_circ_buf.tail = 0;	

out:
	return ret;
}

/* 释放缓存缓存 */
static void gprs_free_buffer(struct gprs_dev *dev)
{
	/* 释放环形接收缓存 */
	if (NULL != dev->Rx_circ_buf.buf)
	{
		kfree(dev->Rx_circ_buf.buf);
		dev->Rx_circ_buf.buf = NULL;
	}
	
	/* 释放环形发送缓存 */
	if (NULL != dev->Tx_circ_buf.buf)
	{
		kfree(dev->Tx_circ_buf.buf);
		dev->Tx_circ_buf.buf = NULL;
	}	
}

/* 初始化GPRS串口的IO内存 */
static int gprs_uart_init_iomem(struct gprs_uart *port)
{
	struct resource *res;
	const char *name = to_gprs_dev(port)->name;

	/* request_mem_region请求分配IO内存,从开始port->mapbase,大小MAP_SIZE
	 * port->mapbase保存当前串口的寄存器基地址(物理)
	 * uart2: 0x50008000
	 */
	res = request_mem_region(port->mapbase, MAP_SIZE, name);
	if (res == NULL)
	{
		printk(KERN_ERR"request_mem_region error: %p\n", res);
	}

	return res ? 0 : -EBUSY;
}

/* 释放GPRS串口的IO内存 */
static void gprs_uart_free_iomem(struct gprs_uart *port)
{
	/* 释放已分配IO内存 */
	release_mem_region(port->mapbase, MAP_SIZE);
}

/* 禁止GPRS串口发送数据 */
static void gprs_uart_stop_tx(struct gprs_uart *port)
{
	if (tx_enabled(port))			/* 若串口已启动发送 */
	{		
		disable_irq(TX_IRQ(port));	/* 禁止发送中断 */
		tx_enabled(port) = 0;		/* 设置串口为未启动发送 */
	}
}

/* 使能GPRS串口发送数据 */
static void gprs_uart_start_tx(struct gprs_uart *port)
{
	if (!tx_enabled(port))			/* 若串口未启动发送 */
	{
		enable_irq(TX_IRQ(port));	/* 使能发送中断 */
		tx_enabled(port) = 1;		/* 设置串口为已启动发送 */
	}	
}

/* 获取GPRS串口Rx FIFO中已存了多少字节数据 */
static int gprs_uart_rx_fifocnt(unsigned long ufstat)
{
	if (ufstat & S3C6410_UFSTAT_RXFULL)	/* 若Rx FIFO已满,返回FIFO的大小 */
		return GPRS_UART_FIFO_SIZE;

	/* 若FIFO未满,返回Rx FIFO已存了多少字节数据 */
	return (ufstat & S3C6410_UFSTAT_RXMASK) >> S3C6410_UFSTAT_RXSHIFT;
}

/* GPRS串口接收中断处理函数 */
static irqreturn_t gprs_uart_rx_chars(int irq, void *dev_id)
{
	struct gprs_uart *port	= dev_id;
	struct gprs_dev	 *dev	= to_gprs_dev(port);
	struct circ_buf *circ	= &dev->Rx_circ_buf;
	unsigned int ufcon, ch, ufstat, uerstat;
	int max_count = 64;	

	/* 循环接收数据,最多一次中断接收64字节数据 */
	while (max_count-- > 0)
	{
		ufcon	= rd_regl(port, S3C6410_UFCON);
		ufstat	= rd_regl(port, S3C6410_UFSTAT);

		/* 若Rx FIFO无数据了,跳出循环 */
		if (gprs_uart_rx_fifocnt(ufstat) == 0 ||
			gprs_uart_circ_full(circ))
			break;

		/* 读取Rx error状态寄存器 */
		uerstat = rd_regl(port, S3C6410_UERSTAT);
		/* 读取已接受到的数据 */
		ch = rd_regb(port, S3C6410_URXH);

		/* 递增接收字符计数器 */
		port->icount.rx++;

		/* 判断是否存在Rx error
		 * if (unlikely(uerstat & S3C6410_UERSTAT_ANY))等同于
		 * if (uerstat & S3C6410_UERSTAT_ANY)
		 * 只是unlikely表示uerstat & S3C6410_UERSTAT_ANY的值为假的可能性大一些
		 * 另外还有一个likely(value)表示value的值为真的可能性更大一些
		 */
		if (unlikely(uerstat & S3C6410_UERSTAT_ANY))
		{
			/* 若break错误,递增icount.brk计算器 */
			if (uerstat & S3C6410_UERSTAT_BREAK)
				port->icount.brk++;

			/* 若frame错误,递增icount.frame计算器 */
			if (uerstat & S3C6410_UERSTAT_FRAME)
				port->icount.frame++;
			/* 若overrun错误,递增icount.overrun计算器 */
			if (uerstat & S3C6410_UERSTAT_OVERRUN)
				port->icount.overrun++;

			continue;
		}

		/* 将接收到的字符插入到环形接收缓存中 */
		circ->tail = (circ->tail + 1) & (dev->size - 1);	
		*(circ->buf + circ->tail) = ch;
	}

	return IRQ_HANDLED;
}

/* GPRS串口发送中断处理函数 */
static irqreturn_t gprs_uart_tx_chars(int irq, void *dev_id)
{
	struct gprs_uart *port	= dev_id;
	struct gprs_dev	 *dev	= to_gprs_dev(port);
	struct circ_buf *circ	= &dev->Tx_circ_buf;
	int count = 256;


	/* 若环形发送缓冲为空,则停止发送并退出中断处理函数 */
	if (gprs_uart_circ_empty(circ))
	{
		gprs_uart_stop_tx(port);
		goto out;
	}

	/* 循环发送数据,最多一次中断发送256字节数据 */
	while (!gprs_uart_circ_empty(circ) && count-- > 0)
	{
		/* 若Tx FIFO已满,退出循环 */
		if (rd_regl(port, S3C6410_UFSTAT) & S3C6410_UFSTAT_TXFULL)
			break;

		/* 将要发送的数据写入Tx FIFO */
		wr_regb(port, S3C6410_UTXH, circ->buf[circ->head]);
		/* 移向循环发送缓冲中下一要发送的数据 */
		circ->head = (circ->head + 1) & (dev->size - 1);
		port->icount.tx++;
	}

	/* 如果环形发送缓冲为空，则停止发送 */
	if (gprs_uart_circ_empty(circ))
		gprs_uart_stop_tx(port);

out:
	return IRQ_HANDLED;
}

/* 初始化GPRS串口中断 */
static int gprs_uart_init_irq(struct gprs_uart *port)
{
//	unsigned long flags;
	int ret;
	const char *name = to_gprs_dev(port)->name;

	/* 设置串口为不可接收,也不可发送 */
	rx_enabled(port) = 0;
	tx_enabled(port) = 0;

//	spin_lock_irqsave(&port->lock, flags);

	/* 申请接收中断 */
	ret = request_irq(RX_IRQ(port), gprs_uart_rx_chars, 0, name, port);
	if (ret != 0)
	{
		printk(KERN_ERR "cannot get irq %d\n", RX_IRQ(port));
		return ret;
	}	

	/* 设置串口为允许接收 */
	rx_enabled(port) = 1;

	/* 申请发送中断 */
	ret = request_irq(TX_IRQ(port), gprs_uart_tx_chars, 0, name, port);
	if (ret)
	{
		printk(KERN_ERR "cannot get irq %d\n", TX_IRQ(port));
		rx_enabled(port) = 0;
		free_irq(RX_IRQ(port), port);
		goto out;
	}	
	
	/* 设置串口为允许发送 */
	tx_enabled(port) = 1;

out:
//	spin_unlock_irqrestore(&port->lock, flags);
	return ret;
}

/* 释放GPRS串口中断 */
static void gprs_uart_free_irq(struct gprs_uart *port)
{
	rx_enabled(port) = 0;				/* 设置串口为不允许接收	*/
	free_irq(RX_IRQ(port), port);		/* 释放接收中断	*/
	tx_enabled(port) = 0;				/* 设置串口为不允许发送	*/
	free_irq(TX_IRQ(port), port);		/* 释放发送中断	*/
}

/* 初始化GPRS串口 */
static int gprs_uart_init(struct gprs_uart *port)
{
	int ret;

	ret = gprs_uart_init_iomem(port);
	if (0 != ret)
		goto iomem_error;		

	ret = gprs_uart_init_irq(port);
	if (0 != ret)
		goto irq_error;	

	return 0;

irq_error:
	gprs_uart_free_iomem(port);
iomem_error:	
	return ret;
}

/* 关闭GPRS串口 */
static void gprs_uart_exit(struct gprs_uart *port)
{
	gprs_uart_free_irq(port);
	gprs_uart_free_iomem(port);
}

/* GPRS驱动的open函数 */
int gprs_open(struct inode *inode, struct file *filp)
{
	struct gprs_dev *dev;
	struct gprs_uart *port;	
	unsigned long flags;	
	int ret;

	dev = container_of(inode->i_cdev, struct gprs_dev, cdev);
	filp->private_data = dev; 
	port = &dev->port; 
	
	spin_lock_irqsave(&port->lock, flags);

	/* 初始化环形缓冲 */
	ret = gprs_init_buffer(dev);
	if (0 != ret)
		goto out;

	/* 初始化GPRS串口 */
	ret = gprs_uart_init(port);
	if (0 != ret)
	{
		gprs_free_buffer(dev);
		goto out;
	}

out:
	spin_unlock_irqrestore(&port->lock, flags);
	return ret;
}

/* GPRS驱动的write函数 */
ssize_t gprs_write(struct file *filp, const char __user *buf, size_t count,loff_t *f_pos)
{
	struct gprs_dev *dev;
	struct circ_buf *circ;
	struct gprs_uart *port;
	ssize_t ret = -EFAULT;
	unsigned long flags;
	int c, index = 0;

	dev = filp->private_data;
	if (!dev)
		return 0;

	port = &dev->port; 
	circ = &dev->Tx_circ_buf;
	if (!circ->buf)
		return 0;

	spin_lock_irqsave(&port->lock, flags);
	while (1)
	{
		/* 获取发送缓冲从tail到缓冲尾有多少可用空间 */
		c = CIRC_SPACE_TO_END(circ->head, circ->tail, dev->size);
		if (count < c)
			c = count;
		if (c <= 0)
			break;

		/* 将用户空间数据拷贝到环形发送缓冲中 */
		ret = copy_from_user(circ->buf+circ->tail, buf+index, c);
		if (0 != ret )
		{
			printk(KERN_ERR "%s: copy_to_user error!\n", __FUNCTION__);
			goto out;		
		}

		circ->tail = (circ->tail + c) & (dev->size - 1);
		count -= c;
		index += c;
	}

	ret = index;

	/* 若环形发送缓冲非空,则使能串口发送数据 */
	if (!gprs_uart_circ_empty(circ))
		gprs_uart_start_tx(port);

out:		
	spin_unlock_irqrestore(&port->lock, flags);
	return ret;	
}

/* GPRS驱动的read函数 */
ssize_t gprs_read(struct file *filp, char __user *buf, size_t count,loff_t *f_pos)
{
	struct gprs_dev *dev;
	ssize_t ret = -EFAULT;	
	struct circ_buf *circ;
	struct gprs_uart *port;
	unsigned long flags;
	int c, index = 0;


	dev = filp->private_data;
	if (!dev)
		return 0;

	port = &dev->port; 
	circ = &dev->Rx_circ_buf;
	if (!circ->buf)
		return 0;	

	spin_lock_irqsave(&port->lock, flags);
	while (1)
	{
		/* 获取接收缓存从head到缓冲尾存了多少数据 */
		c = CIRC_CNT_TO_END(circ->head, circ->tail, dev->size);
		if (count < c)
			c = count;
		if (c <= 0)
			break;

		/* 将环形接收缓冲中的数据拷贝到buf中 */
		ret = copy_to_user(buf+index, circ->buf+circ->head, c);
		if (0 > ret)
		{
			printk(KERN_ERR "%s: copy_to_user error!\n", __FUNCTION__);
			goto out;
		}
		
		circ->head = (circ->head + c) & (dev->size - 1);
		count -= c;
		index += c;
	}

	buf[index] = '\0';

	ret = index;
out:
	spin_unlock_irqrestore(&port->lock, flags);
	return ret;
}

/* GPRS驱动的release函数 */
int gprs_release(struct inode *inode, struct file *filp)
{
	struct gprs_dev *dev;
	struct gprs_uart *port;
	unsigned long flags;

	dev	= filp->private_data;
	port	= &dev->port;
	
	spin_lock_irqsave(&port->lock, flags);

	/* 关闭GPRS串口 */
	gprs_uart_exit(port);
	/* 释放环形缓冲 */	
	gprs_free_buffer(dev);

	spin_unlock_irqrestore(&port->lock, flags);

	return 0;
}

/* GPRS驱动的操作函数集 */
struct file_operations gprs_fops = {
	.owner	= THIS_MODULE,
	.read		= gprs_read,
	.write	= gprs_write,
	.open		= gprs_open,
	.release	= gprs_release,
};

/* 初始化GPRS串口端口 */
static int gprs_uart_init_port(struct gprs_uart *port)
{
	unsigned long flags;
	unsigned int gphcon, quot, baud=9600;

	/* 设置串口波特率时钟频率 */
	port->uartclk	= clk_get_rate(clk_get(NULL, "pclk"));
	quot = port->uartclk / baud / 16 - 1;

	/* 设置串口的寄存器基地址(物理): 0x50008000 */
	port->mapbase	= S3C6410_PA_UART;
	
	request_mem_region(S3C6410_PA_UART, ADDR_SIZE, "my_uart_addr");
	S3C64XX_VA_UART = ioremap(S3C6410_PA_UART, ADDR_SIZE);
	/* 设置当前串口的寄存器基地址(虚拟): 0xF5008000 */		
	port->membase	= S3C64XX_VA_UART;// + (S3C6410_PA_UART2 - S3C64XX_PA_UART);

	spin_lock_irqsave(&port->lock, flags);

//	wr_regl(port, S3C6410_UCON,  S3C6410_UCON_DEFAULT);
	wr_regl(port, S3C6410_UCON,  4);
//	wr_regl(port, S3C6410_ULCON, S3C6410_LCON_CS8 | S3C6410_LCON_PNONE);
	wr_regl(port, S3C6410_ULCON, 4);
//	wr_regl(port, S3C6410_UFCON, S3C6410_UFCON_FIFOMODE
//		| S3C6410_UFCON_RXTRIG8 | S3C6410_UFCON_RESETBOTH);
	wr_regl(port, S3C6410_UFCON, 4);
//	wr_regl(port, S3C6410_UBRDIV, quot);	
	wr_regl(port, S3C6410_UBRDIV, 4);	
printk(KERN_ALERT "tag 1\n\n");

	/* 将I/O port H的gph6和gph7设置为TXD2和RXD2 */
//output mode
/*        
	gphcon =readl(S3C6410_GPHCON);
        gphcon &= (~0xFFFF);
        gphcon |= 0x1111;
        writel(gphcon,S3C6410_GPHCON);
*/
/*	gphcon = readl(S3C6410_GPHCON);
printk(KERN_ALERT "tag 2\n\n");
	gphcon &= ~((0x5) << 12);
printk(KERN_ALERT "tag 3\n\n");
	writel(gphcon, S3C6410_GPHCON);
printk(KERN_ALERT "tag 4\n\n");
	
	spin_unlock_irqrestore(&port->lock, flags);
	
printk(KERN_ALERT "tag 5\n\n");
*/	
	return 0;
}

/* 平台驱动的probe函数 */
static int __init gprs_uart_probe(struct platform_device *dev)
{
	int ret;

	/* 初始化串口 */
	ret = gprs_uart_init_port(&gprs_devices.port);
	if (ret < 0)
	{
		printk(KERN_ERR"gprs_uart_probe: gprs_uart_init_port error: %d\n", ret);
		return ret;
	}

	/* 将串口uart_port结构体保存在platform_device->dev->driver_data中 */
	platform_set_drvdata(dev, &gprs_devices);

	return 0;
}

/* 平台驱动的remove函数 */
static int gprs_uart_remove(struct platform_device *dev)
{
	platform_set_drvdata(dev, NULL);

	return 0;
}

/* GPRS驱动的Platform driver结构体 */
static struct platform_driver gprs_plat_driver = {
	.probe   = gprs_uart_probe,
	.remove  = __exit_p(gprs_uart_remove),
	.driver  = {
		.owner	= THIS_MODULE,
		.name	= DEV_NAME,					/* 驱动名 */
	},
};

/* GPRS驱动的Platform device结构体 */
struct platform_device *gprs_plat_device; 

/* 初始化GPRS驱动的cdev结构体 */
static int init_gprs_dev(struct gprs_dev *dev)
{
	dev_t devno = MKDEV(gprs_major, gprs_minor);

	/* 初始化cdev */
	cdev_init(&dev->cdev, &gprs_fops);
	dev->cdev.owner = THIS_MODULE;
	dev->cdev.ops = &gprs_fops;

	/* 注册cdev */
	return cdev_add(&dev->cdev, devno, 1);
}

/* GPRS驱动的模块初始化函数 */
static int __init gprs_init_module(void)
{
	int ret;
	dev_t devno = 0;
	struct class *gprs_class;

	/* 若指定了主设备编号,则使用静态分配设备编号 */
	if (0 != gprs_major)
	{
		devno = MKDEV(gprs_major, gprs_minor);
		ret = register_chrdev_region(devno, 1, DEV_NAME);
	}
	else
	{/* 若未指定了主设备编号,则使用动态分配设备编号 */
		ret = alloc_chrdev_region(&devno, gprs_minor, 1, DEV_NAME);
		gprs_major = MAJOR(devno);
	}

	if (ret < 0)
	{
		printk(KERN_ERR "gprs_uart: can't get major %d\n", gprs_major);
		return ret;
	}	

	/* 注册GPRS驱动的platform device */
	gprs_plat_device = platform_device_register_simple(DEV_NAME, 0, NULL, 0);
	if (IS_ERR(gprs_plat_device)) 
	{
		ret = PTR_ERR(gprs_plat_device);
		printk(KERN_ERR "%s: can't register platform device %d\n", __FUNCTION__, ret);
		goto fail_reg_plat_dev;
	}

	/* 注册GPRS驱动的platform driver */
	ret = platform_driver_register(&gprs_plat_driver);
	if (0 != ret)
	{
		printk(KERN_ERR "%s: can't register platform driver %d\n", __FUNCTION__, ret);
		goto fail_reg_plat_drv;
	}

	/* 初始化GPRS驱动的cdev */
	ret = init_gprs_dev(&gprs_devices);
	if (0 != ret)
	{
		printk(KERN_ERR "Error %d adding gprs_dev", ret);
		goto fail_cdev_add;
	}

	/* 建立GPRS驱动的class */
	gprs_class = class_create(THIS_MODULE, DEV_NAME);
	if (IS_ERR(gprs_class))
	{
		ret = PTR_ERR(gprs_class);
		printk(KERN_ERR "%s: can't create class %d\n", __FUNCTION__, ret);
		goto fail_create_class;
	}

	/* 建立GPRS驱动的class device */
	gprs_devices.clsdev = device_create(gprs_class, NULL, devno, NULL, DEV_NAME);
	if (IS_ERR(gprs_devices.clsdev))
	{
		ret = PTR_ERR(gprs_devices.clsdev);
		printk(KERN_ERR "%s: can't create class_device %d\n", __FUNCTION__, ret);
		goto fail_create_class_device;
	}

	return 0; /* succeed */

fail_create_class_device:
	class_destroy(gprs_class);    
fail_create_class:
	cdev_del(&gprs_devices.cdev); 	
fail_cdev_add:
	platform_driver_unregister(&gprs_plat_driver);
fail_reg_plat_drv:
	platform_device_unregister(gprs_plat_device);
fail_reg_plat_dev:
	unregister_chrdev_region(devno, 1);
	return ret;
}

static void __exit gprs_exit_module(void)
{
	dev_t devno = MKDEV(gprs_major, gprs_minor);
	struct class *gprs_class = gprs_devices.clsdev;//->class; 	
	
	/* 注销GPRS驱动的platform driver */
	platform_driver_unregister(&gprs_plat_driver);
	/* 注销GPRS驱动的platform devices */
	platform_device_unregister(gprs_plat_device);

	/* 注销GPRS驱动的class device */
	device_destroy(gprs_class, devno);
	/* 注销GPRS驱动的class */	
	class_destroy(gprs_class);

	/* 删除GPRS驱动的cdev */
	cdev_del(&gprs_devices.cdev);

	/* 注销GPRS驱动的platform devices设备编号 */
	unregister_chrdev_region(devno, 1);
}

module_init(gprs_init_module);
module_exit(gprs_exit_module);

MODULE_AUTHOR("lingd");
MODULE_LICENSE("Dual BSD/GPL");
