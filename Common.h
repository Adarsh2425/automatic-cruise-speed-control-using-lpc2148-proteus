#ifndef __COMMON_H
#define __COMMON_H


#define SWITCH_1			(IOPIN0 & 0x00008000)					//pin P0.15  0x08000000
#define SWITCH_2			(IOPIN0 & 0x00002000)					//pin P0.13		(IOPIN0 & 0x10000000)
#define SWITCH_3			(IOPIN0 & 0x00001000)					//pin P0.12	(IOPIN0 & 0x20000000)
#define SWITCH_4			(IOPIN0 & 0x40000000)					//pin P0.30

#define SWITCH_DEBOUNCE_DELAY		10
//	#define SWITCH_1			(IOPIN0 & 0x08000000)					//pin P0.15  0x08000000
//	#define SWITCH_2			(IOPIN0 & 0x10000000)					//pin P0.13		(IOPIN0 & 0x10000000)
//	#define SWITCH_3			(IOPIN0 & 0x20000000)					//pin P0.12	(IOPIN0 & 0x20000000)
//	#define SWITCH_4			(IOPIN0 & 0x40000000)					//pin P0.30

#define MAX_SPEED_SET							80
#define MIN_SPEED_SET							40
#define SPEED_INC_DEC_FACTOR			5
#define MAX_DISTANCE_SET 					10		
#define MIN_DISTANCE_SET					1
#define DISTANCE_INC_DEC_FACTOR		1
#define MAX_SENSOR_READ_GAP				60000
#define ACC_SPEED_DEC_FACTOR 			10
#define ACC_SPEED_INC_FACTOR 			5
#define MAX_COUNT_OF_MODE					3

#define BUZZER_ON			IOCLR0|=(1<<11)
#define BUZZER_OFF		IOSET0|=(1<<11)

#define SWTCH_PRESS_BUZZ_TIME			150
#define LIMIT_RCHD_BUZZ_TIME			200
#define PER_SPEED_CHG_BUZZ_TIME		300
#define ACC_OFF_BUZZ_TIME					6000
#define ACC_OFF_BEEP_COUNT				6

#define MIN_MOTOR_PWM_VAL 1000


#define MAX_BUFFER_SIZE 16
#define DEVICE_ADDR 0xA0
#define BLK_0 0x00
#define BLK_1 0x02
#define MAX_BLOCK_SIZE 256

#endif
