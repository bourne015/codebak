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

int uart_init(void)
{
	/*set to uart mode*/
	GPACON &= ~0xff;
	GPACON |= 0x22;

	/*set the frame*/
	ULCON0 = 0x03;

	/*set to interrupt mode and PCLK*/
	UCON0 = 0x805;
	
	/*enable FIFO*/
	UFCON0 = 0x01;
	
	/*don't use ACF*/
	UMCON0 = 0x01;
	
	/*boaud rate
	DIV_VAL = (PCLK / (bps * 16)) -1
		= (66500000 / (115200 * 16)) - 1
		= 35.08
	*/
	UBRDIV0 = 35;
	UDIVSLOT0 = 0X1;
}

char getchar(void)
{
	while ((UFSTAT0 & 0x7f) == 0);
	
	return URXH0;
}

void put_char(char c)
{
	while (UFSTAT0 & (1 << 14));

	UTXH0 = c;
}
