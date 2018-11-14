#include "mboot.h"
#include "uart.h"
#include "tag.h"
#include "nand.h"
#include "S3C2440addr.h"

#define MACH_TYPE_S3C2440       168
#define BOOT_PARAMS				0x30000100

extern void lcd_clear( U16 c);
extern void lcd_printf(U16 x, U16 y,U16 back_color,U16 char_color,S8 *p_str);

int main(void)
{
	void (*theKernel)(int zero, int arch, unsigned int params);

	lcd_clear(RGB(0x00,0xff,0x00));

	lcd_printf(200,120,RGB(0x00,0xff,0x00),RGB(0xff,0x00,0x00),"Loading...");
	lcd_printf(390,240,RGB(0x00,0xff,0x00),RGB(0xff,0x00,0x00),"Makefile");
	lcd_printf(384,256,RGB(0x00,0xff,0x00),RGB(0xff,0x00,0x00),"2013.11.25");
	
	uart0_puts("\n\r\n\rCopy the kernel from nand to sdram...\n\r");
	nand_read(0x00200000, (unsigned char *)0x30008000, 0x300000);

	setup_start_tag();
	setup_memory_tags();
	setup_commandline_tag("noinitrd root=/dev/mtdblock2 init=/linuxrc console=ttySAC0");
	setup_end_tag();

	lcd_clear( RGB(0x00,0xff,0x00) );
	lcd_printf(216,120,RGB(0x00,0xff,0x00),RGB(0xff,0x00,0x00),"Done.");
	uart0_puts("Done.\n\r");
	
	theKernel = (void (*)(int, int, unsigned int))0x30008000;
	theKernel(0, MACH_TYPE_S3C2440, BOOT_PARAMS);

	/* if everything is ok, we will never come to here. */
	uart0_puts("boot the kernel failed.\n\r");
	return -1;
}
