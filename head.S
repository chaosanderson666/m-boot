/******************************************************
 * m-boot: boot the linux kernel for arm920t CPU-core
 * edit time: 2013.9.5
 ******************************************************/

/* CLOCK registers */
#define CLKDIVN  0x4c000014
#define MPLLCON  0x4C000004
#define MEM_CTL_BASE 0x48000000

#define S3C2440_MPLL_400MHZ     ((0x5c<<12)|(0x01<<4)|(0x01))

.text
.global _start
_start:
	
	ldr r0, =CLKDIVN
	mov r1, #0x05;
	str r1, [r0]

	mrc	p15, 0, r1, c1, c0, 0
	orr	r1, r1, #0xc0000000
	mcr	p15, 0, r1, c1, c0, 0

	ldr r0, =MPLLCON
	ldr r1, =S3C2440_MPLL_400MHZ
	str r1, [r0]

	/* start the icatch */
	mrc p15, 0, r0, c1, c0, 0
	orr r0, r0, #(1<<12)
	mcr	p15, 0, r0, c1, c0, 0 
	
	/* init SDRAM */
	ldr r0, =MEM_CTL_BASE
	adr r1, sdram_config
	add r3, r0, #(13*4)
1:
	ldr r2, [r1], #4
	str r2, [r0], #4
	cmp r0, r3
	bne 1b
	
	ldr sp, =0x34000000
	bl disable_watch_dog
	bl uart0_init
	bl lcd_init
	bl nand_init
		
	mov r0, #0
	ldr r1, =_start
	ldr r2, =__bss_start
	sub r2, r2, r1
	bl nand_read
	bl clear_bss

	ldr lr, =halt_loop
	ldr pc, =main
	
halt_loop:
	b halt_loop

sdram_config:
	.word 0x22011110	 //BWSCON
	.long 0x00000700	 //BANKCON0
	.long 0x00000700	 //BANKCON1
	.long 0x00000700	 //BANKCON2
	.long 0x00000700	 //BANKCON3  
	.long 0x00000700	 //BANKCON4
	.long 0x00000700	 //BANKCON5
	.long 0x00018005	 //BANKCON6
	.long 0x00018005	 //BANKCON7
	.long 0x008C04F4	 //REFRESH
	.long 0x000000B1	 //BANKSIZE
	.long 0x00000030	 //MRSRB6
	.long 0x00000030	 //MRSRB7