#include"uart.h"
#include "S3C2440addr.h"

#define TXD0READY   (1<<2)
#define RXD0READY   (1)

#define PCLK            50000000
#define UART_CLK        PCLK
#define UART_BAUD_RATE  115200
#define UART_BRD        ((UART_CLK  / (UART_BAUD_RATE * 16)) - 1)

void uart0_init(void)
{
    rGPHCON |= 0xa0;
    rGPHUP   = 0x0c;
    rULCON0  = 0x03;
    rUCON0   = 0x05;
    rUFCON0  = 0x00;
    rUMCON0  = 0x00;
    rUBRDIV0 = UART_BRD;
}

void uart0_putc(unsigned char c)
{
    while (!(rUTRSTAT0 & TXD0READY));
    rUTXH0 = c;
}

void uart0_puts(char *str)
{
	int i = 0;
	while (str[i]){
		uart0_putc(str[i]);
		i++;
	}
}

unsigned char uart0_getc(void)
{
    while (!(rUTRSTAT0 & RXD0READY));
    return rURXH0;
}
