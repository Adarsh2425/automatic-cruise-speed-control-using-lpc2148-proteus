#include <LPC214X.H>
#include "Extern_Global_Var.h"
#include "LCD.h"
#include "ADC.h"
#include "Timer.h"
#include "uart.h"
void Switch_Operation()
{
	if(!SWITCH_1 && !g_Switch_1_Pressed)
	{
		delay_ms(SWITCH_DEBOUNCE_DELAY);
		if(!SWITCH_1)
		{
			g_Switch_1_Pressed = 1;
			g_ACC_Mode = g_ACC_Mode + 1;
			if(g_ACC_Mode > MAX_COUNT_OF_MODE)
			{
				g_ACC_Mode = 0;
			}
		}
	}
	else if(SWITCH_1)
	{
		g_Switch_1_Pressed = 0;
	}
	
	//decrementing option 
	if(!SWITCH_2 && !g_Switch_2_Pressed)
	{
		delay_ms(SWITCH_DEBOUNCE_DELAY);
		if(!SWITCH_2)
		{
			g_Switch_2_Pressed = 1;
			if(g_Display_Counter > 1)
			{
				g_Display_Counter = 0;
			}
			g_Display_Counter = g_Display_Counter + 1;
		}
	}
	else if(SWITCH_2)
	{
		g_Switch_2_Pressed = 0;
	}
	
	//Incrementing Value selected
	if(!SWITCH_3 && !g_Switch_3_Pressed)
	{
		delay_ms(SWITCH_DEBOUNCE_DELAY);
		if(!SWITCH_3)
		{
			g_Switch_3_Pressed = 1;
			switch(g_Display_Counter)
			{
				case 1:
							if(g_Set_Speed >= MAX_SPEED_SET)
							{
								g_Set_Speed = MAX_SPEED_SET;
								//Buzzer
							}
							else
							{
								g_Set_Speed = g_Set_Speed + SPEED_INC_DEC_FACTOR;
							}
					break;
				case 2:
							if(g_Set_Distance >= MAX_DISTANCE_SET)
							{
								g_Set_Distance = MAX_DISTANCE_SET;
								//Buzzer
							}
							else
							{
								g_Set_Distance = g_Set_Distance + DISTANCE_INC_DEC_FACTOR;
							}
					break;			
				default:
					
					break;
				}
		}
	}
	else if(SWITCH_3)
	{
		g_Switch_3_Pressed = 0;
	}
	
	//Decrementing Value selected
	if(!SWITCH_4 && !g_Switch_4_Pressed)
	{
		delay_ms(SWITCH_DEBOUNCE_DELAY);
		if(!SWITCH_4)
		{
			g_Switch_4_Pressed = 1;

			switch(g_Display_Counter)
			{
				case 1:
							if(g_Set_Speed <= MIN_SPEED_SET)
							{
								g_Set_Speed = MIN_SPEED_SET;
								//Buzzer
							}
							else
							{
								g_Set_Speed = g_Set_Speed - SPEED_INC_DEC_FACTOR;
							}
					break;
				case 2:
							if(g_Set_Distance <= MIN_DISTANCE_SET)
							{
								g_Set_Distance = MIN_DISTANCE_SET;
								//Buzzer
							}
							else
							{
								g_Set_Distance = g_Set_Distance - DISTANCE_INC_DEC_FACTOR;
							}
					break;			
				default:
					
					break;
			}
		}
	}
	else if(SWITCH_4)
	{
		g_Switch_4_Pressed = 0;
	}
}

void Buzzer_Operation(void)
{
	if(g_Buzzer_Counter == 0)
	{
		if(g_Beep_Counter > 0)
		{	
			g_Buzzer_Counter = g_Old_Buzzer_Counter;
			if((g_Beep_Counter %2) == 0)
			{
				BUZZER_OFF;
			}
			else
			{
				BUZZER_ON;
			}
			g_Beep_Counter = g_Beep_Counter - 1;
		}
		else
		{
			BUZZER_OFF;
		}
	}
	else if(g_Buzzer_Counter > 0)
	{
		g_Buzzer_Counter = g_Buzzer_Counter - 1;
	}
}

void ACC_Mode_Chng_Reset_Settings(void)
{

	lcd_cmd(0X01);  // clear lcd
	delay_ms(100);
	lcd_cmd(0x0C);  // cursor OFF
	delay_ms(10);
	g_Prev_ACC_Mode = g_ACC_Mode;
	g_Default_Display_Set = 0;
	g_Prev_Dsplay_Counter = 0;
	g_Prev_Set_Speed = 0;
	g_Prev_Set_Distance= 0;
	g_Display_Counter = 0;
	g_ACC_0_Flag = 0;
	g_ACC_2_Flag = 0;
	
	BUZZER_ON;
	g_Buzzer_Counter = SWTCH_PRESS_BUZZ_TIME;
	
}

void ACC_Off_Action(void)
{
	if(g_ACC_0_Flag == 0)
	{
		g_ACC_0_Flag = 1;
		delay_ms(5);
		lcd_pos(1,4);
		delay_ms(5);
		lcd_print("ACC OFF");
		PWMMR2 = MIN_MOTOR_PWM_VAL;
		BUZZER_ON;
		g_Buzzer_Counter = ACC_OFF_BUZZ_TIME;
		g_Beep_Counter = ACC_OFF_BEEP_COUNT;
		g_Old_Buzzer_Counter = ACC_OFF_BUZZ_TIME;
	}
}

void ACC_Run_Mode_Update(void)
{

		unsigned char i=0,j=0;
		unsigned char ADC_Val_Char[4];
		unsigned int Sensor_Data = 0;
		unsigned int Specified_Dis_Val = 0;
	
		g_Sensor_Data = ADC_Conversion(CHANNEL6);
		
		Sensor_Data = g_Sensor_Data;
		while(Sensor_Data)
		{
				ADC_Val_Char[i] = Sensor_Data%10 +0x30;
				Sensor_Data = Sensor_Data/10;
				i++;
		}
	
		//Transmit Data on UART conneciton
		i=i-1;
		for(j=0;j<=i;j++)
		{
			uart0_putc(ADC_Val_Char[i-j]);
			delay_ms(5);
		}
		uart0_putc(0x0D);
		delay_ms(5);
						
		
		Specified_Dis_Val = ADC_10M_VAL+((DIST_FACT-g_Set_Distance)*ADC_VAL_CHNG_FACTOR);
		if(g_Sensor_Data > Specified_Dis_Val)
		{
			//Decrease Speed
			if(g_Current_Speed <  MIN_SPEED_SET)
			{
				g_ACC_Mode = 0;
			}
			else if(g_Sensor_Data > (2*Specified_Dis_Val))
			{
				g_Current_Speed = g_Current_Speed - 1.5*ACC_SPEED_DEC_FACTOR;
			}
			else
			{
				g_Current_Speed = g_Current_Speed - ACC_SPEED_DEC_FACTOR;
			}
		}
		else if(g_Sensor_Data < Specified_Dis_Val)
		{
			if(g_Current_Speed <  g_Set_Speed)
			{
				g_Current_Speed = g_Current_Speed + ACC_SPEED_INC_FACTOR;
			}
		}
		
//		Specified_Dis_Val = ADC_1M_VAL+((g_Set_Distance)*ADC_VAL_CHNG_FACTOR);
//		if(g_Sensor_Data < Specified_Dis_Val)
//		{
//			//Decrease Speed
//			if(g_Current_Speed <  MIN_SPEED_SET)
//			{
//				g_ACC_Mode = 0;
//			}
//			else if(g_Sensor_Data<(2*Specified_Dis_Val))
//			{
//				g_Current_Speed = g_Current_Speed - 1.5*ACC_SPEED_DEC_FACTOR;
//			}
//			else
//			{
//				g_Current_Speed = g_Current_Speed - ACC_SPEED_DEC_FACTOR;
//			}
//		}
//		else if(g_Sensor_Data > Specified_Dis_Val)
//		{
//			if(g_Current_Speed <  g_Set_Speed)
//			{
//				g_Current_Speed = g_Current_Speed + ACC_SPEED_INC_FACTOR;
//			}
//		}
		
		if(g_Prev_Current_Speed != g_Current_Speed)					
		{
			g_Prev_Current_Speed = g_Current_Speed;
			lcd_pos(1,2);
			delay_ms(5);
			lcd_print("CURRENT SPEED ");
			delay_ms(5);
			lcd_pos(2,5);
			delay_ms(5);
			LCD_Print_Val_To_Ascii(g_Current_Speed);

			PWMMR2 = g_Current_Speed * 100;    
			PWMLER = (1<<2); //Update Latch Enable bit for PWMMR4
				BUZZER_ON;
			g_Buzzer_Counter = PER_SPEED_CHG_BUZZ_TIME;
			
		}
}

void ACC_Set_Val_Update(void)
{
	if(g_Default_Display_Set != 1)
	{
		g_Default_Display_Set = 1;
		lcd_pos(1,1);
		delay_ms(5);
		lcd_print("SET SPEED");
		delay_ms(5);
		lcd_pos(2,1);
		delay_ms(5);
		lcd_print("SET DIST ");
		delay_ms(5);
	}
	if(g_Display_Counter != g_Prev_Dsplay_Counter)
	{
		g_Prev_Dsplay_Counter = g_Display_Counter;
		if(g_Display_Counter == 1)
		{
			lcd_pos(1,11);
		}
		else
		{
			lcd_pos(2,11);
		}
		delay_ms(10);
		lcd_cmd(0x0F);  
		delay_ms(10);
	}
	
	if(g_Set_Speed !=	g_Prev_Set_Speed)	
	{
		g_Prev_Set_Speed = g_Set_Speed;
		lcd_pos(1,12);
		delay_ms(5);
		LCD_Print_Val_To_Ascii(g_Set_Speed);
	}
	
	if(g_Set_Distance !=	g_Prev_Set_Distance)	
	{
		g_Prev_Set_Distance = g_Set_Distance;
		lcd_pos(2,13);
		delay_ms(5);
		lcd_data(0x20);
		delay_ms(5);
		lcd_pos(2,12);
		delay_ms(5);
		LCD_Print_Val_To_Ascii(g_Set_Distance);
	}
}
