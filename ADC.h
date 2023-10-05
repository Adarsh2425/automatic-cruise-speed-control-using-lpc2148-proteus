#ifndef __ADC_H
#define __ADC_H

#include <LPC214x.H> 

#define CHANNEL6							0x40
#define ADC_10M_VAL						155//900//440//900
#define ADC_1M_VAL						800//650//800//650
#define DIST_FACT							10
#define ADC_VAL_CHNG_FACTOR		((ADC_1M_VAL - ADC_10M_VAL)/DIST_FACT)	

void ADC_Init(void);
unsigned int ADC_Conversion(unsigned char Channel);

#endif
