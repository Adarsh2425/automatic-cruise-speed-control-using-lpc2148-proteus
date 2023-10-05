
#include "delay.h"

void Delay(unsigned char j)
{  
 unsigned int  i;
 for(;j>0;j--)
 {
  for(i=0; i<60000; i++);
 } 
}
/*
void delay(int count)
{
  int j=0,i=0;

  for(j=0;j<count;j++)
  {
    // At 60Mhz, the below loop introduces
    //delay of 10 us 
    for(i=0;i<35;i++);
  }
}
*/
void Delay_Small(unsigned char j)
{
 unsigned int  i;
 for(;j>0;j--)
 {
  for(i=0; i<1000; i++);
 } 
}

void delay_fv(unsigned int x,int y)
 {
	unsigned int i,j;
	for(i=0;i<x;i++)
	for(j=0;j<y;j++);
 }
 
void delay_ms(int count)
{
  int j=0,i=0;
  for(j=0;j<count;j++)
  {
    //At 60Mhz, the below loop introduces
   // delay of 10 us 
    for(i=0;i<150;i++);
  }
}	


