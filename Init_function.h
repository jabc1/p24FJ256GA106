#ifndef _INIT_FUNCTION_H
#define _INIT_FUNCTION_H
#include "p24FJ256GA106.h"
#define		setBEEP			TRISFbits.TRISF0
#define 	BEEP			PORTFbits.RF0
#define 	setLED3 		TRISGbits.TRISG8
#define 	LED3			PORTGbits.RG8
#define 	setLED4 		TRISGbits.TRISG9
#define 	LED4			PORTGbits.RG9
#define		setIVC102S2		TRISCbits.TRISC14
#define		setIVC102S1		TRISCbits.TRISC13
#define 	IVC102S2		PORTCbits.RC14
#define 	IVC102S1		PORTCbits.RC13
#define		setHot			TRISEbits.TRISE7
#define 	Hot				PORTEbits.RE7

#define 	setNear1		TRISDbits.TRISD0
#define 	setNear2		TRISDbits.TRISD1
#define 	setNear3		TRISDbits.TRISD2
#define 	setNear4		TRISDbits.TRISD3
#define 	setNear5		TRISDbits.TRISD4
#define 	setNear6		TRISDbits.TRISD5
#define 	setNear7		TRISDbits.TRISD6
#define 	setNear8		TRISDbits.TRISD7
#define 	setNear9		TRISDbits.TRISD8
#define 	setNear10		TRISDbits.TRISD9


#define 	setNear_S0		TRISEbits.TRISE0
#define 	setNear_S1		TRISEbits.TRISE1
#define 	Near_S0			PORTEbits.RE0
#define 	Near_S1			PORTEbits.RE1

typedef struct{
	unsigned int 	Count;
	unsigned int 	Num;
	unsigned char 	flag;

}System_variable;



void Init_IO(void);



#endif



