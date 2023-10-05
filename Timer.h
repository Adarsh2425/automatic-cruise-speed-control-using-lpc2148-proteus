#ifndef __TIMER_H
#define __TIMER_H

/* Prescaler */ 
#define PERIFERAL_OPERATING_FREQUENCY_IN_HZ	14745600
#define DESIRED_COUNT_FREQ0					1000000	//1MHz


#define PRESCALER0				((PERIFERAL_OPERATING_FREQUENCY_IN_HZ/DESIRED_COUNT_FREQ0)-1)
//#define PRESCALER1				((PERIFERAL_OPERATING_FREQUENCY_IN_HZ/DESIRED_COUNT_FREQ1)-1)

#define	TIMER0_RESET()				T0TCR=2
#define	TIMER0_ENABLE()				T0TCR=1
#define	TIMER0_DISABLE()			T0TCR=0

/* Function declrations */
extern void TIMER_Init (void);
extern void TIMER_WaitForNextTick (void);
extern void PWM_init(void);
extern void Clocks_init(void);

#endif /* TIMER_H */
