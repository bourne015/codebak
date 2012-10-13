.globl _start
_start:

	/* Peri port setup */
	ldr	r0, =0x70000000
	orr	r0, r0, #0x13
	mcr	p15,0,r0,c15,c2,4
    
	/*disable watch_dog*/
	ldr	r0, =0x7E004000
	mov	r1, #0
	str	r1, [r0]
	
	bl	clock_init
	/*init the ddr for link_address*/
	ldr	sp, =8*1024
	bl	ddr_init

	/*copy the code to link_address*/
	adr 	r0, _start
	ldr 	r1, =_start
	ldr	r2, =bss_start
	cmp	r0, r1
	beq	clean_bss

copy_loop:
	ldr	r3, [r0], #4
	str	r3, [r1], #4
	cmp	r1, r2
	bne	copy_loop

clean_bss:
	ldr	r0, =bss_start
	ldr	r1, = bss_end
	ldr	r2, =0x0
clean_loop:
	str	r2, [r0], #4
	cmp	r0, r1;
	bne	clean_loop

	/*test link_address*/
	#bl	main
	ldr	pc, =main
