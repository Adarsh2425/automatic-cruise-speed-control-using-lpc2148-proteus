#ifndef __UART_H
#define __UART_H

#include <LPC214x.H>                     /* LPC21xx definitions               */

void uart1_init (void);
void uart0_init (void);
void uart1_putc	(char);
void uart0_putc	(char);
void uart1_puts	(char *);
void uart0_puts	(char *);
int uart1_read(void);
int uart1_data_ready (void);
int uart0_read(void);
int uart0_data_ready (void);
void LCD_Print_Val_To_Ascii(unsigned char val);

#endif
