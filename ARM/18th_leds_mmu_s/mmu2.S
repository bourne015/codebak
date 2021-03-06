#define ENABLE_DCACHE_ICACHE  1

    /*
To enable the MMU:
1) Program the translation table base and domain access control registers.
2) Program level 1 and level 2 page tables as required.
3) Enable the MMU by setting bit 0 in the control register.
     */
	/* 把页表项的基地址告诉MMU */
	/* 启动MMU */
.globl mmu_enable
mmu_enable:
	mov    r1, #0
	mcr    p15, 0, r1, c7, c7, 0    /* 使无效ICaches和DCaches */

	mcr    p15, 0, r1, c7, c10, 4   /* drain write buffer on v4 */
	mcr    p15, 0, r1, c8, c7, 0    /* 使无效指令、数据TLB */


	mcr p15, 0, r0, c2, c0, 0 /* write TTB register */
	mrc p15, 0, r1, c3, c0, 0 /* read domain 15:0 access permissions */
	orr r1, r1, #3            /* domain 0, Accesses are not checked */
	mcr p15, 0, r1, c3, c0, 0 /* write domain 15:0 access permissions */

	mrc p15, 0, r1, c1, c0, 0 /* Read control register */

#if ENABLE_DCACHE_ICACHE
	orr r1, r1, #(1<<2)       /* Data cache enable */
	orr r1, r1, #(1<<12)      /* Instruction cache enable */
	orr r1, r1, #(1<<14)      /* Round robin replacement */
#endif		
	orr r1, r1, #(1<<0)       /* MMU enable */
	
	mcr p15,0,r1,c1, c0,0     /* write control register */

	mov pc, lr

