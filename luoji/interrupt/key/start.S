.global _start

_start:
	b	reset
	b	halt	@undef
	b	halt	@swi
	b	halt 	@ins abt
	b	halt 	@data abt
	b	halt 	@reserve
	ldr	pc, =_irq
	b	halt 	@fiq

_irq:
	.word vector_irq

vector_irq:
	ldr	sp, =0x53000000
	sub	lr, lr, #4
	stmdb	sp!, {r0-r12, lr}

	bl	do_irq
	
	ldmia	sp!, {r0-r12, pc}^

reset:
	/*perit port setup*/
	ldr	r0, =0x70000000
	orr	r0, r0, #0x13
	mcr	p15,0,r0,c15,c2,4

	/*disable watch dog*/
	ldr	r0, =0x7e004000
	ldr	r1, =0x0
	str	r1, [r0]

	ldr	sp, =8*1024

	/*ARM=532Mhz HCLK=132, PCLK=66*/	
	bl	clock_init
	bl	ddr_init

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
	cmp	r0, r1
	beq	on_ram

bss_loop:
	str	r2, [r0], #4
	cmp	r0, r1
	bne	bss_loop

on_ram:
	bl	test1
	bl	irq_init

	mrs	r0, cpsr
	bic	r0, r0, #0x9f
	orr	r0, r0, #0x10
	msr	cpsr, r0

halt:
	b	halt
