#define	APLL_LOCK	(*((volatile unsigned long *)0x7e00f000))
#define	MPLL_LOCK	(*((volatile unsigned long *)0x7e00f004))
#define	EPLL_LOCK	(*((volatile unsigned long *)0x7e00f008))
#define	OTHERS		(*((volatile unsigned long *)0x7e00f900))
#define	CLK_DIV0	(*((volatile unsigned long *)0x7e00f020))
#define	APLL_CON	(*((volatile unsigned long *)0x7e00f00c))
#define	MPLL_CON	(*((volatile unsigned long *)0x7e00f010))
#define CLK_SRC		(*((volatile unsigned long *)0x7e00f01c))

#define ARM_RATIO	0
#define MPLL_RATIO	0
#define HCLKX2_RATIO	1
#define HCLK_RATIO	1
#define PCLK_RATIO	3

#define APLL_VAL	((1 << 31) | (266 << 16) | (3 << 8) | (1))
void clock_init(void)
{
	/*lock when fre is changing*/
	APLL_LOCK = 0xffff;
	MPLL_LOCK = 0xffff;
	EPLL_LOCK = 0xffff;
	
	/*set async when sys_clk != hlck*/
	OTHERS &= ~(0xc0);
	
	/*wait for async*/
	while ((OTHERS & 0xf00) != 0);

	/*set CLK_DIV*/ 
	CLK_DIV0 = (ARM_RATIO) | (MPLL_RATIO << 4) | (HCLK_RATIO << 8) | (HCLKX2_RATIO << 9) | (PCLK_RATIO << 12);

	/*set the Fout frequence*/
	APLL_CON = APLL_VAL;
	MPLL_CON = APLL_VAL;

	/*choose PLL as CLK*/
	CLK_SRC = 0x3;
}
