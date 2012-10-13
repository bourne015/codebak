.text
.global _start

_start:

#define WTCON1	0x7e004000
	/*peri port setup*/
	ldr	r0, =0x70000000
	orr	r0, r0, #0x13
	mcr	p15, 0, r0, c15, c2, 4

	/*disable watch_dog*/
	ldr	r0, =WTCON1
	mov	r1, #0x00
	str	r1, [r0]

	ldr	sp, =1024*4
	
	bl	main

led_loop:
	b led_loop
