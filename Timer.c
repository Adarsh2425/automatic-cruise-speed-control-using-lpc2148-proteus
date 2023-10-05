#include<lpc214x.h>
#include "Type.h"
#include "Timer.h"

void Clocks_init(void)
{
 PLL0CON = 0x01;   //Enable PLL
 PLL0CFG = 0x24;   //Multiplier and divider setup
 PLL0FEED = 0xAA;  //Feed sequence
 PLL0FEED = 0x55;

 while(!(PLL0STAT & 0x00000400)); //is locked?

 PLL0CON  = 0x03; //Connect PLL after PLL is locked
 PLL0FEED = 0xAA; //Feed sequence
 PLL0FEED = 0x55;
 VPBDIV   = 0x02; //PCLK is same as CCLK i.e.60 MHz
}

void PWM_init(void)
{
 PWMPCR = 0x0; //Select Single Edge PWM - by default its single Edged so this line can be removed
 PWMPR = 15-1; // 1 micro-second resolution
 PWMMR0 = 10000; // 10ms period duration
 PWMMR2 = 500; // 0.5ms - pulse duration i.e width (Brigtness level)
 PWMMCR = (1<<1); // Reset PWMTC on PWMMR0 match
 PWMLER = (1<<0)|(1<<4); // update MR0 and MR4
 PWMPCR = (1<<10); // enable PWM output
 PWMTCR = (1<<1) ; //Reset PWM TC & PR
 //Now , the final moment - enable everything
 PWMTCR = (1<<0) | (1<<3); // enable counters and PWM Mode
 //PWM Generation goes active now - LED must be 25% Bright after boot!!
 //Now you can get the PWM output at Pin P0.8!
}
void TIMER_Init (void)
{
	// Power ON timer peripheral 
	PCONP	|= 0x00000006;

	// TPC: Timer Prescaler counter
	// the counter is incremented once every TPC+1 cycles of PCLK

	T0PR	= PRESCALER0;
	//T1PR	= PRESCALER1;	

	// TCR: Timer  Control Register
	// 2: reset counters (both timer and prescaler)
	// 1: enable counting

	T0TCR=2;
	//T1TCR=2;

}

/*
waits for next tick in timer
*/
void TIMER_WaitForNextTick (void)
{
	uint32 start=T0TC;
	
	while (T0TC==start) {}	// wait until timer counter changes, then leave
}
