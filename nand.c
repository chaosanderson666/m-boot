#include "nand.h"
#include "S3C2440addr.h"

void nand_reset(void)
{
    nand_select_chip();
    write_cmd(0xff);
    wait_idle();
    nand_deselect_chip();
}

void wait_idle(void)
{
    int i;
    while(!(rNFSTAT & BUSY))
        for(i=0; i<10; i++);
}

void nand_select_chip(void)
{
    int i;
    rNFCONT &= ~(1<<1);
    for(i=0; i<10; i++); 
}

void nand_deselect_chip(void)
{
    rNFCONT |= (1<<1);
}

void write_cmd(int cmd)
{
    rNFCMD = cmd;
}

void write_addr(unsigned int addr)
{
	int i;
	int col, page;

	col = addr & NAND_BLOCK_MASK_LP;
	page = addr / NAND_SECTOR_SIZE_LP;
	
	rNFADDR = col & 0xff;			/* Column Address A0~A7 */
	for(i=0; i<10; i++);		
	rNFADDR = (col >> 8) & 0x0f; 	/* Column Address A8~A11 */
	for(i=0; i<10; i++);
	rNFADDR = page & 0xff;			/* Row Address A12~A19 */
	for(i=0; i<10; i++);
	rNFADDR = (page >> 8) & 0xff;	/* Row Address A20~A27 */
	for(i=0; i<10; i++);
	rNFADDR = (page >> 16) & 0x03;	/* Row Address A28~A29 */
	for(i=0; i<10; i++);
}

unsigned char read_data(void)
{
    return rNFDATA;
}

void nand_init(void)
{
	rNFCONF = (TACLS<<12)|(TWRPH0<<8)|(TWRPH1<<4);
	rNFCONT = (1<<4)|(1<<1)|(1<<0);
    
    nand_reset();
}

void nand_read(unsigned long source, unsigned char *destination, int size)
{
	int i, j;

	nand_select_chip();

	for(i = source; i < (source + size);){
		write_cmd(0);
		write_addr(i);
		write_cmd(0x30);
		wait_idle();
		
		for(j = 0; j < NAND_SECTOR_SIZE_LP; j++, i++) {
			*destination = read_data();
			destination++;
		}
	}
	nand_deselect_chip();
	return ;
}
