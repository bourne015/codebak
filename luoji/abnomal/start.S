.global	_start

_start:
	b	reset
	ldr	pc, =undefined_instruction
	ldr	pc, _vector_swi
	b	halt

_vector_swi:
	.word	vector_swi

vector_swi:
	ldr	sp, =0x55000000
	stmdb	sp!, {r0-r12, lr}

	bl	test_swi
	
	ldmia	sp!, {r0-r12, pc}^

undefined_instruction:
	ldr	sp, =0x56000000
	stmdb	sp!, {r0-r12, lr}

	bl	test_undef

	ldmia	sp!, {r0-r12, lr}


reset:
	/*perit port setup*/
	ldr	r0, =0x70000000
	orr	r0, r0, #0x13
	mcr	p15, 0, r0, c15, c2, 4

	/*disable watch dog*/
	ldr	r0, =0x7e004000
	ldr	r1, =0x0
	str	r1, [r0]

	ldr	sp, =8*1024
	
	bl	clock_init
	bl	ddr_init
	bl	uart_init

	/*copy code to ddr*/
	adr	r0, _start
	ldr	r1, =_start
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
	ldr	r1, =bss_end
	ldr	r2, =0x0
bss_loop:
	cmp	r0, r1
	beq	on_ram
	str	r2, [r0], #4

on_ram:
	mrs	r0, cpsr
	bic	r0, r0, #0x1f
	orr	r0, r0, #0x10
	msr	cpsr, r0

	ldr	sp, =0x57000000

	bl	main
	
	swi	0
unde:
	.word 0xff000000

halt:
	b	halt	
