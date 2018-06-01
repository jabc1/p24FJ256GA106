#ifndef _AD_FUNCTION_H
#define _AD_FUNCTION_H

#define		PD1		2
#define		PD2		3
#define		PD3		4
#define		PD4		5
#define		PD5		8
#define		PD6		9
#define		PD7		10
#define		PD8		11
#define		PD9		14
#define		PD10	15
#define		wendu	13



void Init_AD(void);
unsigned int ADC(unsigned char prot);//·µ»ØADÖµ
unsigned int Adc_Count(unsigned char Type,unsigned char Count);

#endif


