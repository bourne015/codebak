.global _start

_start:
	/*perit port setup*/
	ldr	r0, =0x70000000
	orr	r0, r0, #0x13
	mcr	p15, 0, r0, c15, c2, 4

	/*disable watch_dog*/
	ldr	r0, =0x7e004000
	ldr	r1, =0x00
	str	r1, [r0]
	
	/*setup the stack*/
	ldr	sp, =8*1024

	/*ARM=532Mhz HCLK=133Mhz PCLK=66Mhz*/
	bl	clock_init
	bl	uart_init
	bl	test_no_copy
	bl	ddr_init	

	adr	r0, _start
	ldr	r1, =_start
	ldr	r2, =bss_start
	/*sub	r2, r2, r1*/
	cmp	r0, r1
	beq	clean_bss
	
	/*bl	nand2ddr*/

copy_loop:
	ldr	r3, [r0], #4
	str	r3, [r1], #4
	cmp	r1, r2
	bne	copy_loop

clean_bss:
	ldr	r0, =bss_start
	ldr	r1, =bss_end
	ldr	r2, =0x0
clean_loop:
	str	r2, [r0], #4
	cmp	r0, r1
	ble	clean_bss

on_ram:
	#bl	test
	bl	main
halt:
	b 	halt
