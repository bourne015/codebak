#define APLL_LOCK	(*((volatile unsigned long *)0x7e00f000))
#define MPLL_LOCK	(*((volatile unsigned long *)0x7e00f004))
#define EPLL_LOCK	(*((volatile unsigned long *)0x7e00f008))

#define OTHERS		(*((volatile unsigned long *)0x7e00f900))

#define CLK_DIV0	(*((volatile unsigned long *)0x7e00f020))

#define ARM_RATIO	0 //532
#define MPLL_RATIO	0 //532	
#define PCLK_RATIO	3 //66M
#define HCLK_RATIO	1 //133
#define HCLKX2_RATIO	1 //266

#define APLL_CON	(*((volatile unsigned long *)0x7e00f00c))
#define MPLL_CON	(*((volatile unsigned long *)0x7e00f010))
#define APLL_VAL 	((1) | (3 << 8) | (266 << 16) | (1 << 31))

#define CLK_SRC		(*((volatile unsigned long *)0x7e00f01c))

void clock_init(void)
{
	/*set the lock period*/
	APLL_LOCK = 0xffff;
	MPLL_LOCK = 0xffff;
	EPLL_LOCK = 0xffff;
	
	/*set and wait async mode*/
	OTHERS &= ~0xc0;
	while ((OTHERS & 0xf00) != 0);

	CLK_DIV0 = (ARM_RATIO) | (MPLL_RATIO << 4) | (HCLK_RATIO << 8) | (HCLKX2_RATIO << 9) | (PCLK_RATIO << 12);

	APLL_CON = APLL_VAL;
	MPLL_CON = APLL_VAL;

	CLK_SRC = 0x3;
}
