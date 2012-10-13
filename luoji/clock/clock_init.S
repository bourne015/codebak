.global clock_init

clock_init:
	/*set the clock time*/
	ldr	r0, =0x7e00f000 /*APLL_CLOCK*/
	ldr	r1, =0xffff
	str	r1, [r0]

	str	r1, [r0, #0x4]	/*MPLL_CLOCK*/
	str	r1, [r0, #0x8]	/*EPLL_CLOCK*/

	/*set sync mode*/
	ldr	r0, =0x7e00f900	/*OTHERS*/
	ldr	r1, [r0]
	bic	r1, #0xc0
	str	r1, [r0]
	
	/*wait for sync mode*/
loop1:
	ldr	r0, =0x7e00f900
	ldr	r1, [r0]
	and	r1, #0xf00
	cmp	r1, #0x00
	bne	loop1

	/*set the DIV*/
	#define ARM_RATIO	0 /*ARM_CLK=DOUTAPLL / (ARM_RATIO + 1)*/
	#define MPLL_RATIO	0 /*DOUTMPLL = MOUTMPLL / (MPLL_RATIO + 1)*/
	#define HCLK_RATIO	1 /*HCLK = HCLKX2 / (HCLK_RATIO + 1)*/
	#define HCLKX2_RATIO	1 /*HCLKX2 = HCLKX2IN / (HCLKX2_RATIO + 1)*/
	#define PCLK_RATIO	3 /*PCLK = HCLKX2 / (PCLK_RATIO + 1) <=66Mhz*/

	ldr	r0, =0x7e00f020		/*CLK_DIV0*/
	ldr	r1, =(ARM_RATIO) | (MPLL_RATIO << 4) | (HCLK_RATIO << 8) | (HCLKX2_RATIO << 9) | (PCLK_RATIO << 12)
	str	r1, [r0]
	
	/*init the frequence*/
	#define SDIV	1
	#define PDIV	3
	#define MDIV	266 /*final 532Mhz*/

	ldr	r0, =0x7e00f00c /*APLL_CON*/
	ldr	r1, =(1 << 31) | (MDIV << 16) | (PDIV << 8) | (SDIV)
	str	r1, [r0]
	
	ldr	r0, =0x7e00f010 /*MPLL_CON*/
	str	r1, [r0]

	/*set the clk_src to choose pll but not xttpll*/
	ldr	r0, =0x7e00f01c
	ldr	r1, =0x03
	str	r1, [r0]
	
	mov	pc, lr
