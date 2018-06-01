#ifndef _TIME_FUNCTION_H
#define _TIME_FUNCTION_H

typedef struct{
	unsigned int ms;
	unsigned int sec;
	unsigned int min;
	unsigned int hour;
	unsigned char ms_flag;
	unsigned char sec_flag;
	unsigned char min_flag;
	unsigned char hour_falg;
}TimeNum;

typedef struct{
	unsigned int PD1_Num;
	unsigned int PD2_Num;
	unsigned int PD3_Num;
	unsigned int PD4_Num;
	unsigned int PD5_Num;
	unsigned int PD6_Num;
	unsigned int PD7_Num;
	unsigned int PD8_Num;
	unsigned int PD9_Num;
	unsigned int PD10_Num;
}PDx;

void Init_Time1(void);
void Init_Time2(void);
void Init_num(void);
void  __attribute__((interrupt, shadow, no_auto_psv)) _T1Interrupt(void);
void  __attribute__((interrupt, shadow, no_auto_psv)) _T2Interrupt(void);
void  __attribute__((interrupt, shadow, no_auto_psv)) _T3Interrupt(void);
void  __attribute__((interrupt, shadow, no_auto_psv)) _T4Interrupt(void);
void  __attribute__((interrupt, shadow, no_auto_psv)) _T5Interrupt(void);




#endif



