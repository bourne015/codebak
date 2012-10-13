.global _start

_start:
	/*peri port setup*/
	ldr	r0, =0x70000000
	orr	r0, r0, #0x13
	mcr	p15, 0, r0, c15, c2, 4

	/*disable watch_dog*/
	ldr	r0, =0x7e004000
	ldr	r1, =0x00
	str	r1, [r0]
	
	bl	clock_init

	ldr	r0, =0x7f008820
	ldr	r1, =0x11111
	str	r1, [r0]

	ldr	r0, =0x7f008824
	ldr 	r1, =0xeeeeeeee

loop:
	str 	r1, [r0]

	bl	delay
	ror	r1, r1, #1

	b	loop

delay:
	ldr	r2, =500000

delay_loop:
        sub r2, r2, #1
        cmp r2, #0
        bne delay_loop
        mov pc, lr

halt:
        b halt
