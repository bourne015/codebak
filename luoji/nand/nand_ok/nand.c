

#define MEM_SYS_CFG     (*((volatile unsigned long *)0x7E00F120))
#define NFCONF          (*((volatile unsigned long *)0x70200000))
#define NFCONT          (*((volatile unsigned long *)0x70200004))
#define NFCMMD          (*((volatile unsigned long *)0x70200008))
#define NFADDR          (*((volatile unsigned long *)0x7020000C))
#define NFDATA          (*((volatile unsigned char *)0x70200010))
#define NFSTAT          (*((volatile unsigned long *)0x70200028))


void nand_select(void)
{
	NFCONT &= ~(1<<1);
}

void nand_deselect(void)
{
	NFCONT |= (1<<1);
}


void nand_cmd(unsigned char cmd)
{
	NFCMMD = cmd;
}

void nand_addr(unsigned char addr)
{
	NFADDR = addr;
}

unsigned char nand_get_data(void)
{
	return NFDATA;
}

void nand_send_data(unsigned char data)
{
	NFDATA = data;
}

void wait_ready(void)
{
	while ((NFSTAT & 0x1) == 0);
}

void nand_reset(void)
{
	/* ѡ�� */
	nand_select();
	
	/* ����0xff���� */
	nand_cmd(0xff);

	/* �ȴ����� */
	wait_ready();
	
	/* ȡ��ѡ�� */
	nand_deselect();
}


void nand_init(void)
{
	/* ��xm0csn2����nand flash cs0 Ƭѡ���� */
	MEM_SYS_CFG &= ~(1<<1);

	/* ����ʱ����� */
#define TACLS     0
#define TWRPH0    2
#define TWRPH1    1
	NFCONF &= ~((1<<30) | (7<<12) | (7<<8) | (7<<4));
	NFCONF |= ((TACLS<<12) | (TWRPH0<<8) | (TWRPH1<<4));

	/* ʹ��nand flash controller */
	NFCONT |= 1;
	NFCONT &= ~(1<<16); /* ɭֹsoft lock */

	nand_reset();
}


void nand_send_addr(unsigned int addr)
{
#if 1	
	unsigned int page   = addr / 4096;
	unsigned int colunm = addr & (4096 - 1);

	/* ��������ַ��ʾ��ҳ�����￪ʼ */
	nand_addr(colunm & 0xff);
	nand_addr((colunm >> 8) & 0xff);

	/* ����������ַ��ʾ��һҳ */
	nand_addr(page & 0xff);
	nand_addr((page >> 8) & 0xff);
	nand_addr((page >> 16) & 0xff);
#else
	nand_addr(addr & 0xff);         /* a0~a7 */
	nand_addr((addr >> 8) & 0x1f);   /* ����ĽǶ�: a8~a12 */

	nand_addr((addr >> 13) & 0xff); /* ����ĽǶ�: a13~a20 */
	nand_addr((addr >> 21) & 0xff); /* ����ĽǶ�: a21~a28 */
	nand_addr((addr >> 29) & 0x7); /* ����ĽǶ�: a29   ~ */
	
#endif
}


int nand_read(unsigned int nand_start, unsigned int ddr_start, unsigned int len)
{
	unsigned int addr = nand_start;
	int i = nand_start % 4096;
	int left = i;
	int count = 0;
	unsigned char *dest = (unsigned char *)ddr_start;
	unsigned char data = 0;
	
	/* ѡ��оƬ */
	nand_select();

	while (count < len)
	{
		/* ��������0x00 */
		nand_cmd(0x00);

		/* ������ַ */
		nand_send_addr(addr);

		/* ��������0x30 */
		nand_cmd(0x30);

		/* �ȴ����� */
		wait_ready();

		/* ������ */
		for (; i < (4096-left) && count < len; i++)
		{
			data = nand_get_data();
			if(addr<16384)
			{
			    if(i<(2048-left))
			    {
				dest[count++] = data;
			    }
			}
			else
			{
			    dest[count++] = data;
			}
			//dest[count++] = nand_get_data();
			addr++;			
		}

		i = 0;	
		left = i;	
	}

	/* ȡ��Ƭѡ */
	nand_deselect();
	return 0;
}

int nand_erase_block(unsigned long addr)
{
	int page = addr / 4096;
	
	nand_select();
	nand_cmd(0x60);
	
	nand_addr(page & 0xff);
	nand_addr((page >> 8) & 0xff);
	nand_addr((page >> 16) & 0xff);

	nand_cmd(0xd0);
	wait_ready();

	nand_deselect();
}


int nand_write(unsigned int nand_start, unsigned char * buf, unsigned int len)
{
	unsigned long count = 0;
	unsigned long addr  = nand_start;
	int i = nand_start % 4096;
	int left = i;
	
	nand_select();
	while (count < len)
	{
		nand_cmd(0x80);
		nand_send_addr(addr);
		for (; i < (4096-left) && count < len; i++)
		{
			if(addr<16384)
			{
			    if(i<(2048-left))
			    {
				nand_send_data(buf[count++]);
			    }
			}
			else
			{
			    nand_send_data(buf[count++]);
			}
			//nand_send_data(buf[count++]);
			addr++;
		}

		nand_cmd(0x10);
		wait_ready();
		i = 0;	
		left = i;	
	}

	nand_deselect();
	
}

int copy2ddr(unsigned int nand_start, unsigned int ddr_start, unsigned int len)
{
	int ret;
	
	/* ��ʼ��nand flash controller */
	nand_init();
	
	/* ��nand flash */
	ret = nand_read(nand_start, ddr_start, len);
	
	return ret;
}

