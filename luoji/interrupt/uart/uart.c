#define GPMCON	(*((volatile unsigned long *)0x7f008820))
#define GPMDAT	(*((volatile unsigned long *)0x7f008824))
#define GPACON	(*((volatile unsigned long *)0x7f008000))
#define GPADAT		(*((volatile unsigned long *)0x7f008004))

#define ULCON0		(*((volatile unsigned long *)0x7f005000))
#define UCON0		(*((volatile unsigned long *)0x7f005004))
#define UFCON0		(*((volatile unsigned long *)0x7f005008))
#define UMCON0		(*((volatile unsigned long *)0x7f00500c))
#define UBRDIV0		(*((volatile unsigned short *)0x7f005028))
#define UDIVSLOT0 	(*((volatile unsigned short *)0x7f00502C))
#define UFSTAT0		(*((volatile unsigned long *)0x7f005018))
#define URXH0		(*((volatile unsigned char *)0x7f005024))
#define UTXH0		(*((volatile unsigned char *)0x7f005020))

#define UINTP0		(*((volatile unsigned long *)0x7f005030))
#define UINTM0		(*((volatile unsigned long *)0x7f005038))
#define TX_BUF_LEN	2048

static unsigned char txbuf[2047] = "hello this is what i writed ,gone with the wind ,i'll always stay here by your side";
static unsigned int re = 0;
static unsigned int wr = 0;
	
int uart_init(void)
{
	/*set to uart mode*/
	GPACON &= ~0xff;
	GPACON |= 0x22;

	/*set the frame*/
	ULCON0 = 0x03;

	/*set to interrupt mode and PCLK*/
	UCON0 = 0x5 | (1 << 9);
	
	/*enable FIFO, trigger level 16B */
	UFCON0 = 0x7 | (1 << 6);
	
	/*don't use ACF*/
	UMCON0 = 0x0;
	
	/*boaud rate
	DIV_VAL = (PCLK / (bps * 16)) -1
		= (66500000 / (115200 * 16)) - 1
		= 35.08
	*/
	UBRDIV0 = 35;
	UDIVSLOT0 = 0X1;
}

static void uart_tx_int_enable(void)
{
	UINTM0 &= ~(1<<2);	
}

static void uart_tx_int_disable(void)
{
	UINTM0 |= (1<<2);	
}

static int isfull(void)
{
	if ((wr + 1) % TX_BUF_LEN == re)
		return 1;
	else 
		return 0;
}

static int isempty(void)
{
	return (wr == re);
}

static int getdata(unsigned char *pdata)
{
	if (isempty()) {
		return -1;
	} else {
		*pdata = txbuf[re];
		re = (re + 1) % TX_BUF_LEN;
		return 0;
	}
}

static int putData(unsigned char data)
{
	if (isfull())
		return -1;
	else {
		txbuf[wr] = data;
		wr = (wr + 1) % TX_BUF_LEN;
		return 0;
	}
}

void put_c(unsigned char c)
{
	putData(c);
	uart_tx_int_enable();
}

void do_uart_irq(void)
{
	int i, cnt;
	unsigned char c;
	
	if (UINTP0 & (1 << 2)) { //Transmit interrupt
		if (isempty()) {
			uart_tx_int_disable();
		} else {

			cnt = (UFSTAT0 >> 8) & 0x3f;
			cnt = 64 - cnt;

			for (i = 0; i < cnt; i++) {
				if (getdata(&c) == 0)
					UTXH0 = c;
				else
					break;
			}
		}
	} else if (UINTP0 & (1 << 0)) { //Receive interrupt
		cnt = (UFSTAT0 & 0x3f);
		cnt = 64 - cnt;

		for (i = 0; i < cnt; i++) {
			c = URXH0;
			put_c(c);
		}
	}
	UINTP0 = 0xf;
}
