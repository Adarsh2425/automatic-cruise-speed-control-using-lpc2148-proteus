#include "uart.h"

#define CR     0x0D

int sendchar (int ch) 
 {
  if (ch == '\n')  {
    while (!(U1LSR & 0x20));
    U1THR = CR;                          /* output CR */
  }
  while (!(U1LSR & 0x20));
  return (U1THR = ch);
}


int uart1_data_ready (void) 
 {                     /* Read character from Serial Port   */
   if((U1LSR & 0x01))
   {
    return 1;
   }
   else
    return 0;
 }

int uart1_read(void)
 {
  while(!(U1LSR & 0x01));
  return (U1RBR);
 }

int uart0_data_ready (void) 
 {                     /* Read character from Serial Port   */
   if((U0LSR & 0x01))
   {
    return 1;
   }
   else
    return 0;
 }

 int uart0_read(void)
  {
  while(!(U0LSR & 0x01));
  return (U0RBR);
  }

  


void uart1_init()
{
  PINSEL0|= 0x00050000;            /* Enable RxD1 and TxD1                     */
  U1LCR = 0x83;                   /* 8 bits, no Parity, 1 Stop bit            */
  U1DLL = 97;                     /* 9600 Baud Rate @ 15MHz VPB Clock         */
  U1LCR = 0x03;                   /* DLAB = 0                                 */
}

void uart1_putc(char c)
{
	while(!(U1LSR & 0x20)); // Wait until UART1 ready to send character     
	U1THR = c;  // Send character
}

void uart1_puts(char *p)
{
	while(*p) // Point to character
	{
		uart1_putc(*p++);   // Send character then point to next character
	}
}

void uart0_init()
{
	 unsigned int Baud16;
  PINSEL0|= 0x00000005;           /* Enable RxD0 and TxD0                     */
//  U0LCR = 0x83;                   /* 8 bits, no Parity, 1 Stop bit            */
//  U0DLL = 97;                     /* 9600 Baud Rate @ 15MHz VPB Clock         */
//  U0LCR = 0x03;                   /* DLAB = 0                                 */

  
   U0LCR = 0x83;		            // DLAB = 1
   Baud16 = (150000 / 16) / 96;  
   U0DLM = Baud16 / 256;							
   U0DLL = Baud16 % 256;						
   U0LCR = 0x03;
}

void uart0_putc(char c)
{
	while(!(U0LSR & 0x20)); // Wait until UART0 ready to send character  
	U0THR = c; // Send character
}

void uart0_puts(char *p)
{
	while(*p) // Point to character
	{
		uart0_putc(*p++);  // Send character then point to next character
	}
}
