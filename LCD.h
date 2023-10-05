#ifndef __LCD_H
#define __LCD_H

#include <LPC214x.H>       
#include "delay.h"

#define LCD (0xf<<19)
#define RS (1<<16)
#define EN (1<<18)


void lcd_init(void);     // LCD initilization function
void lcd_print(unsigned char *temp);  // function to write string on lcd
void lcd_cmd(unsigned char cmd);     // lcd command function
void lcd_data(unsigned char data);
void lcd_pos(int line, int pos);

#endif
