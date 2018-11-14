#ifndef _UART_H_
#define _UART_H_

void uart0_init(void);
void uart0_putc(unsigned char c);
void uart0_puts(char *str);
unsigned char uart0_getc(void);

#endif /* _UART_H_ */
