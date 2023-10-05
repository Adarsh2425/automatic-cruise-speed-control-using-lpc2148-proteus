#include "LCD.h"

void lcd_data(unsigned char data)  // lcd display funtion
  {
		unsigned int temp;    //initilize variable
		delay_ms(10);        // calling delay
		IOCLR0|=(RS|EN|LCD); // clearing rs, rw,en and lcd pins
		temp=(data>>4)&0x0f;   // rotating value of x by 4 and anding with 0x0f
		IOSET0|=(temp<<19);  //put value of temp at on lcd pins
		IOSET0|=RS;    // set re pin
		IOSET0|=EN;    // set enable pin
		delay_ms(10); // hault for some time
		IOCLR0|=EN;   // clear enable pin
		
		delay_ms(20);
		IOCLR0|=(RS|EN|LCD); // clearing rs, rw,en and lcd pins
		temp=data&0x0f;    // anding value of x with 0x0f
		IOSET0|=(temp<<19); // putting value of temp on lcd data pin
			IOSET0|=RS;  // set re pin 
			IOSET0|=EN;  // set enable pin
		delay_ms(10); // hault for some time
			IOCLR0|=EN;  // clear enable pin
		delay_ms(20); // calling delay function
  }

void lcd_cmd(unsigned char cmd)   // lcd command funtion
  {
	unsigned int temp;      //initilize variable
	IOCLR0|=(RS|EN|LCD); // clearing rs, rw,en and lcd pins
	temp=(cmd>>4)&0x0f;   // rotating value of x by 4 and anding with 0x0f
	IOSET0|=(temp<<19);  //put value of temp at on lcd pins
	IOCLR0|=RS;  // clear re pin
	IOSET0|=EN;  // set enable pin
	delay_ms(10); // hault for some time
	IOCLR0|=EN;  // clear enable pin
		
	delay_ms(20);
	IOCLR0|=(RS|EN|LCD);  // clearing rs, rw,en and lcd pins
	temp=cmd&0x0f;     // anding value of x with 0x0f
	IOSET0|=(temp<<19);  // putting value of temp on lcd data pin
	IOCLR0|=RS;  // clear re pin 
	IOSET0|=EN;  // set enable pin
	delay_ms(10); // hault for some time
	IOCLR0|=EN; // clear enable pin
	delay_ms(20);
 }


 
 void lcd_init(void)   // lcd initilization function
 {
		lcd_cmd(0X02);	//Initialize Cursor to Home Position
	 delay_ms(100);
		lcd_cmd(0X28);  //to initialize LCD in 2 lines, 5X7 dots and 4bit mode.
	 delay_ms(100);
		lcd_cmd(0x0C);  // cursor OFF
	 delay_ms(100);
		lcd_cmd(0X06);  // entry mode
	 delay_ms(100);	
		lcd_cmd(0X01);  // clear lcd
	 delay_ms(400);
		lcd_cmd(0X80);  // cursor indicating first line first position
	 delay_ms(200);
		lcd_pos(2,4);
	 delay_ms(5);
		lcd_print("WELCOME");
	 delay_ms(5000);
		lcd_cmd(0X01);  // clear lcd
	 delay_ms(100);
		
	 //	delay_ms(1000);
  }
	
void lcd_pos(int line, int pos)
  {
    if(line==1)
	     lcd_cmd(0x80+pos);
    else if(line==2)
	     lcd_cmd(0xc0+pos);
  }
	
void lcd_print(unsigned char *str)  // funtion to write sting on lcd
{
	 while(*str!='\0')  // check str for NULL
		 {
				lcd_data(*str);  // write one characture from string
		delay_ms(10);
				str++;     // increament string
		 }
}
	

void LCD_Print_Val_To_Ascii(unsigned char val)
{
		unsigned char i= 0,j,Data_For_LCD[4];
	
		while(val!=0)
		{
			Data_For_LCD[i] = (val % 10) + 0x30;
			val = val /10;
			i++;
		}
		
		i=i-1;
		for(j=0;j<=i;j++)
		{
			lcd_data(Data_For_LCD[i-j]);
			delay_ms(5);
		}
}
