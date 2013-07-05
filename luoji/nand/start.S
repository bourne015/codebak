.global _start
_start:
	/*perip port remap*/
	ldr	r0, =0x70000000
	orr	r0, r0, #0x13
	mcr	p15, 0, r0, c15, c2, 4

	/*disable watch dog*/
	ldr	r0, =0x7e004000
	ldr	r1, =0x0
	str	r1, [r0]

	ldr	sp, =8*1024
	bl	clock_init
	bl	uart_init
	bl	ddr_init
	
	adr	r0, _start
	ldr	r1, =_start
	ldr	r2, =bss_start
	sub	r2, r2, r1
	cmp	r0, r1
	beq	clean_bss

	bl	nand2ddr
	cmp	r0, #0
	bne	halt
/*
relocate:
	ldr	r3, [r0], #4
	str	r3, [r1], #4
	cmp	r1, r2
	bne	relocate
*/	
clean_bss:
	ldr	r0, =bss_start
	ldr	r1, =bss_end
	ldr	r2, =0x0
	cmp	r0, r1
	beq	on_ram
bss_loop:
	str	r2, [r0], #4
	cmp	r0, r1
	bne	bss_loop

on_ram:
	ldr	pc, =test
	ldr	pc, =main

halt:
	b	halt
