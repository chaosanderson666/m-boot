#ifndef _NAND_H_
#define _NAND_H_

#define TACLS   0
#define TWRPH0  3
#define TWRPH1  0
#define BUSY    1
#define NAND_SECTOR_SIZE_LP    2048
#define NAND_BLOCK_MASK_LP     (NAND_SECTOR_SIZE_LP - 1)

void nand_init(void);
void nand_read(unsigned long start_addr, unsigned char *buf, int size);

void nand_reset(void);
void wait_idle(void);
void nand_select_chip(void);
void nand_deselect_chip(void);
void write_cmd(int cmd);
void write_addr(unsigned int addr);
unsigned char read_data(void);

#endif /* _NAND_H_ */
