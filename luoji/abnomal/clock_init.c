#define APLL_LOCK	(*((volatile unsigned long *)0x7e00f000))
#define MPLL_LOCK	(*((volatile unsigned long *)0x7e00f004))
#define EPLL_LOCK	(*((volatile unsigned long *)0x7e00f008))

#define OTHERS		(*((volatile unsigned long *)0x7e00f900))

#define CLK_DIV0	(*((volatile unsigned long *)0x7e00f020))

#define APLL_CON	(*((volatile unsigned long *)0x7e00f00c))
#define APLL_VAL	((1) | (3 << 8) | (266 << 16) | (1 << 31))
#define MPLL_CON	(*((volatile unsigned long *)0x7e00f010))

#define CLK_SRC		(*((volatile unsigned long *)0x7e00f01c))

#define ARM_RATIO	0
#define HCLKX2_RATIO	1
#define HCLK_RATIO	1
#define PCLK_RATIO	3
#define MPLL_RATIO	0

void clock_init(void)
{
	APLL_LOCK = 0xffff;
	MPLL_LOCK = 0xffff;
	EPLL_LOCK = 0xffff;

	/*set async mode when cpu fre != HCLK*/
	OTHERS &= ~0xc0;

	/*wait for async mode*/
	while ((OTHERS & 0xf00) != 0);

	/*set the clk_div*/
	CLK_DIV0 = (ARM_RATIO) | (MPLL_RATIO << 4) | (HCLK_RATIO << 8) | (HCLKX2_RATIO << 9) | (PCLK_RATIO << 12);

	/*set the init Fin*/
	APLL_CON = APLL_VAL;	//532Mhz
	MPLL_CON = APLL_VAL;

	/*set the clk_src to choose pll*/
	CLK_SRC = 0X03;

}
