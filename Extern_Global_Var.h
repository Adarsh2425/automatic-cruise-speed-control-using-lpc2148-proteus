#include "Common.h"

extern volatile unsigned char g_Switch_1_Pressed;
extern volatile unsigned char g_Switch_2_Pressed;
extern volatile unsigned char g_Switch_3_Pressed;
extern volatile unsigned char g_Switch_4_Pressed;


extern volatile unsigned char g_ACC_Mode;

extern volatile char g_Display_Counter;

extern unsigned char g_Prev_Set_Speed;
extern unsigned char g_Prev_Set_Distance;
extern unsigned char g_Prev_Dsplay_Counter;
extern unsigned char g_Prev_ACC_Mode;
extern unsigned char g_Default_Display_Set;
extern unsigned char g_Prev_Current_Speed;
extern unsigned char g_ACC_0_Flag;
extern unsigned char g_ACC_2_Flag;


extern volatile unsigned char g_Set_Speed;
extern volatile unsigned char g_Set_Distance ;
extern volatile unsigned int g_Sensor_Data;
extern volatile unsigned char g_Current_Speed ;
extern volatile  long int g_Buzzer_Counter;
extern volatile unsigned char g_Beep_Counter;
extern volatile unsigned long int g_Old_Buzzer_Counter;

extern unsigned int g_Current_PWM_Val;

//extern unsigned char I2C_WR_Buf[];
extern unsigned char I2C_RD_Buf[];
extern unsigned char Status;
extern unsigned char Status_Flag;
