#ifndef TYPE_H
#define TYPE_H

#ifndef NULL
#define NULL    (0)	
#endif
#ifndef FALSE
#define FALSE   (0)
#endif
#ifndef TRUE
#define TRUE    (1)
#endif

/* Arm data types */
typedef unsigned char 		uint8;	
typedef unsigned short int 	uint16;	
typedef unsigned int 		uint32; 	
typedef char 		int8;	
typedef short int 	int16;	
typedef int 		int32; 	
typedef unsigned char	BOOL;
/*
Data Type 	Actual ‘C’data type 	Bytes allocated.
uint8 		unsigned char 			1
int8 		char 					1
uint16 		unsigned short 			2
int16 		short 					2
uint32 		unsigned long 			4
int32 		long 					4
float32 	32 bit float 			4
float64 	double 					8
*/
/*
Data type	 Short form
int8 		i8
uint8 		u8
int16 		i16
uint16 		u16
int32 		i32
uint32 		u32
float32 	fl32
float64 	fl64
pointer 	ptr
bool 		b
*/
#endif  // TYPE_H 
