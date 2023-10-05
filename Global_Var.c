//Global variable decalaration
#include "Common.h"

volatile unsigned char g_Switch_1_Pressed = 0;
volatile unsigned char g_Switch_2_Pressed = 0;
volatile unsigned char g_Switch_3_Pressed = 0;
volatile unsigned char g_Switch_4_Pressed = 0;


volatile unsigned char g_ACC_Mode = 0;

volatile char g_Display_Counter = 0;

unsigned char g_Prev_Set_Speed = 0;
unsigned char g_Prev_Set_Distance = 0;
unsigned char g_Prev_Dsplay_Counter = 0;
unsigned char g_Prev_ACC_Mode = 4;
unsigned char g_Default_Display_Set = 0;
unsigned char g_Prev_Current_Speed = 0;
unsigned char g_ACC_0_Flag = 0;
unsigned char g_ACC_2_Flag = 0;


volatile unsigned char g_Set_Speed = MIN_SPEED_SET;
volatile unsigned char g_Set_Distance = MAX_DISTANCE_SET;
volatile unsigned int g_Sensor_Data = 0;
volatile unsigned char g_Current_Speed = 30;
volatile  long int g_Buzzer_Counter = 0;
volatile unsigned char g_Beep_Counter=0;
volatile unsigned long int g_Old_Buzzer_Counter = 0;

unsigned int g_Current_PWM_Val = MIN_MOTOR_PWM_VAL;


//unsigned char I2C_WR_Buf[MAX_BUFFER_SIZE]={"  Nex Robotics  "};
unsigned char I2C_RD_Buf[MAX_BUFFER_SIZE];
unsigned char Status=0;
unsigned char Status_Flag=0;

