#include "ADC.h"

void ADC_Init(void)			//This function inits ADC peripheral
{
	PCONP |= (unsigned long)(0x00000001) << 12;	// Enable Power/Clock to ADC0
	AD0CR = 0x00200E80;		// SEL = 1 	ADC0 channel 1	Channel 1
						// CLKDIV = Fpclk / 1000000 - 1 ;1MHz
						// BURST = 0   // CLKS = 0  // PDN = 1 
 						// START = 1   // EDGE = 0 (CAP/MAT)
} 
                           

unsigned int ADC_Conversion(unsigned char Channel)
{
 unsigned int Temp=0;

	AD0CR = (AD0CR&0xFFFFFF00) | Channel;			   //Select AD0.1 for conversion
	AD0CR|=(1 << 24);							   //Trigger conversion
	while(!(AD0GDR & 0x80000000));			   //Wait for the conversion to be completed
	Temp = AD0GDR;						   //Store converted data
	Temp = (Temp>>6) & 0x3FF;
		
	AD0CR &= 0xF8FFFFFF; //Deactivate ADC Module (No Start) ie START = 000 (Bits 26:24)
	return(Temp);
}
