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

	/*setup the clock*/
	bl	clock_init
	bl	uart_init
	
	/*init uart, then r/t char*/
	bl	main
	bl	test
	bl	test_uart
halt:
	b 	halt
