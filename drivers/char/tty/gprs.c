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



#include <linux/circ_buf.h>				/* ���λ��� */

#define DEV_NAME			"gprs_uart"	/* �豸�� */
#define GPRS_UART_MAJOR		0			/* ���豸�� */
#define GPRS_UART_MINOR		0			/* ���豸�� */
#define GPRS_UART_FIFO_SIZE	16			/* ����FIFO�Ĵ�С */
#define DEBUG				KERN_WARNING
#define MAX_BUFFER_SIZE 128				/* ���λ���Ĵ�С */
#define MAP_SIZE (0x100)
#define gprs_uart_circ_empty(circ)		((circ)->head == (circ)->tail)
#define gprs_uart_circ_full(circ)		((circ)->head == (circ)->tail + 1)

/* �����жϺ� */
#define TX_IRQ(port) ((port)->irq + 1)
#define RX_IRQ(port) ((port)->irq)

/* �����ڽ����ַ��ı�־ */
#define tx_enabled(port) ((port)->unused[0])
/* �����ڷ����ַ��ı�־ */
#define rx_enabled(port) ((port)->unused[1])

/* ��ȡ�Ĵ�����ַ */
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

/* GPRS���ڽṹ�� */
struct gprs_uart
{
	spinlock_t		lock;				/* ���ڶ˿��� */
	unsigned char	unused[2];
	resource_size_t	mapbase;			/* IO�ڴ����ַ */
	unsigned char __iomem	*membase;	/* ��ӳ����IO�ڴ����ַ */
	unsigned int		irq;			/* �жϺ� */
	unsigned int		uartclk;		/* ����ʱ�� */
	unsigned int		fifosize;		/* FIFO�����С */	
	struct uart_icount	icount;			/* ������ */
};

/* GPRS������device�ṹ�� */
struct gprs_dev
{
	int		size;						/* ���λ���Ĵ�С */
	const	char		*name;			/* �豸�� */
	struct	circ_buf	Rx_circ_buf;	/* ���ν��ջ��� */
	struct	circ_buf	Tx_circ_buf;	/* ���η��ͻ��� */		
	struct	gprs_uart	port;			/* ���ڽṹ�� */
	struct	cdev		cdev;			/* �ַ��豸�ṹ�� */
	struct	class_device *clsdev;    	/* class_device�ṹ�� */	
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

/* ��ʼ�����λ��� */
static int gprs_init_buffer(struct gprs_dev *dev)
{
	int ret = 0;

	/* ���ν��ջ���ΪNULLʱ,Ϊ���ν��ջ��������ڴ�ռ� */
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

	/* ���η��ͻ���ΪNULLʱ,Ϊ���η��ͻ��������ڴ�ռ� */
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

	/* ���û��λ��� */
	dev->size = MAX_BUFFER_SIZE;
	dev->Rx_circ_buf.head = 0;
	dev->Rx_circ_buf.tail = 0;
	dev->Tx_circ_buf.head = 0;
	dev->Tx_circ_buf.tail = 0;	

out:
	return ret;
}

/* �ͷŻ��滺�� */
static void gprs_free_buffer(struct gprs_dev *dev)
{
	/* �ͷŻ��ν��ջ��� */
	if (NULL != dev->Rx_circ_buf.buf)
	{
		kfree(dev->Rx_circ_buf.buf);
		dev->Rx_circ_buf.buf = NULL;
	}
	
	/* �ͷŻ��η��ͻ��� */
	if (NULL != dev->Tx_circ_buf.buf)
	{
		kfree(dev->Tx_circ_buf.buf);
		dev->Tx_circ_buf.buf = NULL;
	}	
}

/* ��ʼ��GPRS���ڵ�IO�ڴ� */
static int gprs_uart_init_iomem(struct gprs_uart *port)
{
	struct resource *res;
	const char *name = to_gprs_dev(port)->name;

	/* request_mem_region�������IO�ڴ�,�ӿ�ʼport->mapbase,��СMAP_SIZE
	 * port->mapbase���浱ǰ���ڵļĴ�������ַ(����)
	 * uart2: 0x50008000
	 */
	res = request_mem_region(port->mapbase, MAP_SIZE, name);
	if (res == NULL)
	{
		printk(KERN_ERR"request_mem_region error: %p\n", res);
	}

	return res ? 0 : -EBUSY;
}

/* �ͷ�GPRS���ڵ�IO�ڴ� */
static void gprs_uart_free_iomem(struct gprs_uart *port)
{
	/* �ͷ��ѷ���IO�ڴ� */
	release_mem_region(port->mapbase, MAP_SIZE);
}

/* ��ֹGPRS���ڷ������� */
static void gprs_uart_stop_tx(struct gprs_uart *port)
{
	if (tx_enabled(port))			/* ���������������� */
	{		
		disable_irq(TX_IRQ(port));	/* ��ֹ�����ж� */
		tx_enabled(port) = 0;		/* ���ô���Ϊδ�������� */
	}
}

/* ʹ��GPRS���ڷ������� */
static void gprs_uart_start_tx(struct gprs_uart *port)
{
	if (!tx_enabled(port))			/* ������δ�������� */
	{
		enable_irq(TX_IRQ(port));	/* ʹ�ܷ����ж� */
		tx_enabled(port) = 1;		/* ���ô���Ϊ���������� */
	}	
}

/* ��ȡGPRS����Rx FIFO���Ѵ��˶����ֽ����� */
static int gprs_uart_rx_fifocnt(unsigned long ufstat)
{
	if (ufstat & S3C6410_UFSTAT_RXFULL)	/* ��Rx FIFO����,����FIFO�Ĵ�С */
		return GPRS_UART_FIFO_SIZE;

	/* ��FIFOδ��,����Rx FIFO�Ѵ��˶����ֽ����� */
	return (ufstat & S3C6410_UFSTAT_RXMASK) >> S3C6410_UFSTAT_RXSHIFT;
}

/* GPRS���ڽ����жϴ����� */
static irqreturn_t gprs_uart_rx_chars(int irq, void *dev_id)
{
	struct gprs_uart *port	= dev_id;
	struct gprs_dev	 *dev	= to_gprs_dev(port);
	struct circ_buf *circ	= &dev->Rx_circ_buf;
	unsigned int ufcon, ch, ufstat, uerstat;
	int max_count = 64;	

	/* ѭ����������,���һ���жϽ���64�ֽ����� */
	while (max_count-- > 0)
	{
		ufcon	= rd_regl(port, S3C6410_UFCON);
		ufstat	= rd_regl(port, S3C6410_UFSTAT);

		/* ��Rx FIFO��������,����ѭ�� */
		if (gprs_uart_rx_fifocnt(ufstat) == 0 ||
			gprs_uart_circ_full(circ))
			break;

		/* ��ȡRx error״̬�Ĵ��� */
		uerstat = rd_regl(port, S3C6410_UERSTAT);
		/* ��ȡ�ѽ��ܵ������� */
		ch = rd_regb(port, S3C6410_URXH);

		/* ���������ַ������� */
		port->icount.rx++;

		/* �ж��Ƿ����Rx error
		 * if (unlikely(uerstat & S3C6410_UERSTAT_ANY))��ͬ��
		 * if (uerstat & S3C6410_UERSTAT_ANY)
		 * ֻ��unlikely��ʾuerstat & S3C6410_UERSTAT_ANY��ֵΪ�ٵĿ����Դ�һЩ
		 * ���⻹��һ��likely(value)��ʾvalue��ֵΪ��Ŀ����Ը���һЩ
		 */
		if (unlikely(uerstat & S3C6410_UERSTAT_ANY))
		{
			/* ��break����,����icount.brk������ */
			if (uerstat & S3C6410_UERSTAT_BREAK)
				port->icount.brk++;

			/* ��frame����,����icount.frame������ */
			if (uerstat & S3C6410_UERSTAT_FRAME)
				port->icount.frame++;
			/* ��overrun����,����icount.overrun������ */
			if (uerstat & S3C6410_UERSTAT_OVERRUN)
				port->icount.overrun++;

			continue;
		}

		/* �����յ����ַ����뵽���ν��ջ����� */
		circ->tail = (circ->tail + 1) & (dev->size - 1);	
		*(circ->buf + circ->tail) = ch;
	}

	return IRQ_HANDLED;
}

/* GPRS���ڷ����жϴ����� */
static irqreturn_t gprs_uart_tx_chars(int irq, void *dev_id)
{
	struct gprs_uart *port	= dev_id;
	struct gprs_dev	 *dev	= to_gprs_dev(port);
	struct circ_buf *circ	= &dev->Tx_circ_buf;
	int count = 256;


	/* �����η��ͻ���Ϊ��,��ֹͣ���Ͳ��˳��жϴ����� */
	if (gprs_uart_circ_empty(circ))
	{
		gprs_uart_stop_tx(port);
		goto out;
	}

	/* ѭ����������,���һ���жϷ���256�ֽ����� */
	while (!gprs_uart_circ_empty(circ) && count-- > 0)
	{
		/* ��Tx FIFO����,�˳�ѭ�� */
		if (rd_regl(port, S3C6410_UFSTAT) & S3C6410_UFSTAT_TXFULL)
			break;

		/* ��Ҫ���͵�����д��Tx FIFO */
		wr_regb(port, S3C6410_UTXH, circ->buf[circ->head]);
		/* ����ѭ�����ͻ�������һҪ���͵����� */
		circ->head = (circ->head + 1) & (dev->size - 1);
		port->icount.tx++;
	}

	/* ������η��ͻ���Ϊ�գ���ֹͣ���� */
	if (gprs_uart_circ_empty(circ))
		gprs_uart_stop_tx(port);

out:
	return IRQ_HANDLED;
}

/* ��ʼ��GPRS�����ж� */
static int gprs_uart_init_irq(struct gprs_uart *port)
{
//	unsigned long flags;
	int ret;
	const char *name = to_gprs_dev(port)->name;

	/* ���ô���Ϊ���ɽ���,Ҳ���ɷ��� */
	rx_enabled(port) = 0;
	tx_enabled(port) = 0;

//	spin_lock_irqsave(&port->lock, flags);

	/* ��������ж� */
	ret = request_irq(RX_IRQ(port), gprs_uart_rx_chars, 0, name, port);
	if (ret != 0)
	{
		printk(KERN_ERR "cannot get irq %d\n", RX_IRQ(port));
		return ret;
	}	

	/* ���ô���Ϊ������� */
	rx_enabled(port) = 1;

	/* ���뷢���ж� */
	ret = request_irq(TX_IRQ(port), gprs_uart_tx_chars, 0, name, port);
	if (ret)
	{
		printk(KERN_ERR "cannot get irq %d\n", TX_IRQ(port));
		rx_enabled(port) = 0;
		free_irq(RX_IRQ(port), port);
		goto out;
	}	
	
	/* ���ô���Ϊ������ */
	tx_enabled(port) = 1;

out:
//	spin_unlock_irqrestore(&port->lock, flags);
	return ret;
}

/* �ͷ�GPRS�����ж� */
static void gprs_uart_free_irq(struct gprs_uart *port)
{
	rx_enabled(port) = 0;				/* ���ô���Ϊ���������	*/
	free_irq(RX_IRQ(port), port);		/* �ͷŽ����ж�	*/
	tx_enabled(port) = 0;				/* ���ô���Ϊ��������	*/
	free_irq(TX_IRQ(port), port);		/* �ͷŷ����ж�	*/
}

/* ��ʼ��GPRS���� */
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

/* �ر�GPRS���� */
static void gprs_uart_exit(struct gprs_uart *port)
{
	gprs_uart_free_irq(port);
	gprs_uart_free_iomem(port);
}

/* GPRS������open���� */
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

	/* ��ʼ�����λ��� */
	ret = gprs_init_buffer(dev);
	if (0 != ret)
		goto out;

	/* ��ʼ��GPRS���� */
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

/* GPRS������write���� */
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
		/* ��ȡ���ͻ����tail������β�ж��ٿ��ÿռ� */
		c = CIRC_SPACE_TO_END(circ->head, circ->tail, dev->size);
		if (count < c)
			c = count;
		if (c <= 0)
			break;

		/* ���û��ռ����ݿ��������η��ͻ����� */
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

	/* �����η��ͻ���ǿ�,��ʹ�ܴ��ڷ������� */
	if (!gprs_uart_circ_empty(circ))
		gprs_uart_start_tx(port);

out:		
	spin_unlock_irqrestore(&port->lock, flags);
	return ret;	
}

/* GPRS������read���� */
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
		/* ��ȡ���ջ����head������β���˶������� */
		c = CIRC_CNT_TO_END(circ->head, circ->tail, dev->size);
		if (count < c)
			c = count;
		if (c <= 0)
			break;

		/* �����ν��ջ����е����ݿ�����buf�� */
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

/* GPRS������release���� */
int gprs_release(struct inode *inode, struct file *filp)
{
	struct gprs_dev *dev;
	struct gprs_uart *port;
	unsigned long flags;

	dev	= filp->private_data;
	port	= &dev->port;
	
	spin_lock_irqsave(&port->lock, flags);

	/* �ر�GPRS���� */
	gprs_uart_exit(port);
	/* �ͷŻ��λ��� */	
	gprs_free_buffer(dev);

	spin_unlock_irqrestore(&port->lock, flags);

	return 0;
}

/* GPRS�����Ĳ��������� */
struct file_operations gprs_fops = {
	.owner	= THIS_MODULE,
	.read		= gprs_read,
	.write	= gprs_write,
	.open		= gprs_open,
	.release	= gprs_release,
};

/* ��ʼ��GPRS���ڶ˿� */
static int gprs_uart_init_port(struct gprs_uart *port)
{
	unsigned long flags;
	unsigned int gphcon, quot, baud=9600;

	/* ���ô��ڲ�����ʱ��Ƶ�� */
	port->uartclk	= clk_get_rate(clk_get(NULL, "pclk"));
	quot = port->uartclk / baud / 16 - 1;

	/* ���ô��ڵļĴ�������ַ(����): 0x50008000 */
	port->mapbase	= S3C6410_PA_UART;
	
	request_mem_region(S3C6410_PA_UART, ADDR_SIZE, "my_uart_addr");
	S3C64XX_VA_UART = ioremap(S3C6410_PA_UART, ADDR_SIZE);
	/* ���õ�ǰ���ڵļĴ�������ַ(����): 0xF5008000 */		
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

	/* ��I/O port H��gph6��gph7����ΪTXD2��RXD2 */
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

/* ƽ̨������probe���� */
static int __init gprs_uart_probe(struct platform_device *dev)
{
	int ret;

	/* ��ʼ������ */
	ret = gprs_uart_init_port(&gprs_devices.port);
	if (ret < 0)
	{
		printk(KERN_ERR"gprs_uart_probe: gprs_uart_init_port error: %d\n", ret);
		return ret;
	}

	/* ������uart_port�ṹ�屣����platform_device->dev->driver_data�� */
	platform_set_drvdata(dev, &gprs_devices);

	return 0;
}

/* ƽ̨������remove���� */
static int gprs_uart_remove(struct platform_device *dev)
{
	platform_set_drvdata(dev, NULL);

	return 0;
}

/* GPRS������Platform driver�ṹ�� */
static struct platform_driver gprs_plat_driver = {
	.probe   = gprs_uart_probe,
	.remove  = __exit_p(gprs_uart_remove),
	.driver  = {
		.owner	= THIS_MODULE,
		.name	= DEV_NAME,					/* ������ */
	},
};

/* GPRS������Platform device�ṹ�� */
struct platform_device *gprs_plat_device; 

/* ��ʼ��GPRS������cdev�ṹ�� */
static int init_gprs_dev(struct gprs_dev *dev)
{
	dev_t devno = MKDEV(gprs_major, gprs_minor);

	/* ��ʼ��cdev */
	cdev_init(&dev->cdev, &gprs_fops);
	dev->cdev.owner = THIS_MODULE;
	dev->cdev.ops = &gprs_fops;

	/* ע��cdev */
	return cdev_add(&dev->cdev, devno, 1);
}

/* GPRS������ģ���ʼ������ */
static int __init gprs_init_module(void)
{
	int ret;
	dev_t devno = 0;
	struct class *gprs_class;

	/* ��ָ�������豸���,��ʹ�þ�̬�����豸��� */
	if (0 != gprs_major)
	{
		devno = MKDEV(gprs_major, gprs_minor);
		ret = register_chrdev_region(devno, 1, DEV_NAME);
	}
	else
	{/* ��δָ�������豸���,��ʹ�ö�̬�����豸��� */
		ret = alloc_chrdev_region(&devno, gprs_minor, 1, DEV_NAME);
		gprs_major = MAJOR(devno);
	}

	if (ret < 0)
	{
		printk(KERN_ERR "gprs_uart: can't get major %d\n", gprs_major);
		return ret;
	}	

	/* ע��GPRS������platform device */
	gprs_plat_device = platform_device_register_simple(DEV_NAME, 0, NULL, 0);
	if (IS_ERR(gprs_plat_device)) 
	{
		ret = PTR_ERR(gprs_plat_device);
		printk(KERN_ERR "%s: can't register platform device %d\n", __FUNCTION__, ret);
		goto fail_reg_plat_dev;
	}

	/* ע��GPRS������platform driver */
	ret = platform_driver_register(&gprs_plat_driver);
	if (0 != ret)
	{
		printk(KERN_ERR "%s: can't register platform driver %d\n", __FUNCTION__, ret);
		goto fail_reg_plat_drv;
	}

	/* ��ʼ��GPRS������cdev */
	ret = init_gprs_dev(&gprs_devices);
	if (0 != ret)
	{
		printk(KERN_ERR "Error %d adding gprs_dev", ret);
		goto fail_cdev_add;
	}

	/* ����GPRS������class */
	gprs_class = class_create(THIS_MODULE, DEV_NAME);
	if (IS_ERR(gprs_class))
	{
		ret = PTR_ERR(gprs_class);
		printk(KERN_ERR "%s: can't create class %d\n", __FUNCTION__, ret);
		goto fail_create_class;
	}

	/* ����GPRS������class device */
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
	
	/* ע��GPRS������platform driver */
	platform_driver_unregister(&gprs_plat_driver);
	/* ע��GPRS������platform devices */
	platform_device_unregister(gprs_plat_device);

	/* ע��GPRS������class device */
	device_destroy(gprs_class, devno);
	/* ע��GPRS������class */	
	class_destroy(gprs_class);

	/* ɾ��GPRS������cdev */
	cdev_del(&gprs_devices.cdev);

	/* ע��GPRS������platform devices�豸��� */
	unregister_chrdev_region(devno, 1);
}

module_init(gprs_init_module);
module_exit(gprs_exit_module);

MODULE_AUTHOR("lingd");
MODULE_LICENSE("Dual BSD/GPL");
