#include "uart.h"
#include "LCD.h"
#include "ADC.h"
#include "Timer.h"
#include "Extern_Global_Var.h"
#include "I2C_new.h"
#include "ACC_Func.h"

int main()
  {
		unsigned int	l_Sensor_Data_Cntr = 0;
				
	//	Clocks_init();
		
		PINSEL1 = 0x00000000;
		PINSEL2 = 0x00000000;
		uart0_init();					    // Initialize UART0
	//	uart1_init();					    // Initialize UART1
		PINSEL0 |= 0x00000300;		//ADC ==> P0.5 ==> ADC0.7		
		PINSEL0	&= ~(1 << 14);
		PINSEL0 |= (1 << 15);
	//	PINSEL0 &= ~(1 << 16);
	//	PINSEL0 |= (1 << 17); // Select PWM4 output for Pin0.8
		ADC_Init();
		I2C_Init();		// Initialize I2C0
		TIMER_Init();	// Initialize Timer
		
		PWM_init();
		PWMMR2 = MIN_MOTOR_PWM_VAL;    
    PWMLER = (1<<2); //Update Latch Enable bit for PWMMR4
		
		IODIR1 = 0xFFFFFFFF;
		IODIR0 =0x80FF0800;		//LCD 16,17,18,19,20,21,22    //Switch 15,13,12,30
		lcd_init();
		
		BUZZER_OFF;

		delay_ms(1000);
		if(Page_Read(BLK_1,0x00))
		{
			uart0_puts("Read Failed");
		}
		else
		{
			uart0_putc(I2C_RD_Buf[1]);
			delay_ms(5);
			uart0_putc(I2C_RD_Buf[2]);
			g_Set_Speed = I2C_RD_Buf[1];
			g_Set_Distance = I2C_RD_Buf[2];
			
		}
		
		if((g_Set_Speed<40)||(g_Set_Speed>80))
		{
			g_Set_Speed = 50;
		}
		if((g_Set_Distance)>10)
		{
			g_Set_Distance = 5;
		}

		while(1)                           // An embedded program does not stop 
		{
			int a;
			
			char flag = 0;
			unsigned char b;
			
			Switch_Operation();
			
			Buzzer_Operation();
			
			if(g_ACC_Mode != g_Prev_ACC_Mode)
			{
					ACC_Mode_Chng_Reset_Settings();
				l_Sensor_Data_Cntr = 0;
			}
			switch(g_ACC_Mode)
			{
				case 0:				//ACC switched off
							ACC_Off_Action();
					break;
				
				case 1:				//ACC Settings
							ACC_Set_Val_Update();
					break;
						
				case 2:			//ACC ENABLE Permission
						if(g_ACC_2_Flag == 0)
						{				
							g_ACC_2_Flag = 1;
							lcd_pos(1,2);
							delay_ms(5);
							lcd_print("START ACC ?");
							if(Page_Write(BLK_1,0x01,g_Set_Speed))
							{
								uart0_puts("Write Failed");
							}
							delay_ms(2000);
							
							if(Page_Write(BLK_1,0x02,g_Set_Distance))
							{
								uart0_puts("Write Failed");
							}											

						}
					break;
				
				case 3:			//Current Speed Display
								if(l_Sensor_Data_Cntr == 0)
								{
									ACC_Run_Mode_Update();
									l_Sensor_Data_Cntr = MAX_SENSOR_READ_GAP;
								}
								else
								{
									l_Sensor_Data_Cntr = l_Sensor_Data_Cntr - 1;
								}
					break;
			}

			if(uart0_data_ready())
			{
				lcd_pos(1,0);
				a=uart0_read();
				uart0_putc(a);
				b = (unsigned char)a;
				flag = 1;
			}
			if(flag == 1)
			{
				lcd_data(b);
				flag = 0;
			}

		}
  }
	

