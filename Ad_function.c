#include "Ad_function.h"
#include "Time_function.h"
#include "Init_function.h"
#include "p24FJ256GA106.h"
#define		uint		unsigned int
#define 	uchar		unsigned char
extern 		PDx			PDx_Delay_start;
void Init_AD(void)
{
//设置管脚为输入
	TRISBbits.TRISB2 = 1;//RB2-->AN2-->C1
	TRISBbits.TRISB3 = 1;//RB3-->AN3-->C2
	TRISBbits.TRISB4 = 1;//RB4-->AN4-->C3
	TRISBbits.TRISB5 = 1;//RB5-->AN5-->C4
	TRISBbits.TRISB6 = 1;//RB6-->AN6-->C5
	TRISBbits.TRISB7 = 1;//RB7-->AN7-->C6
	TRISBbits.TRISB8 = 1;//RB8-->AN8-->C7
	TRISBbits.TRISB9 = 1;//RB9-->AN9-->C8
	TRISBbits.TRISB10 = 1;//RB10-->AN10-->C9
	TRISBbits.TRISB11 = 1;//RB11-->AN11-->C10
	TRISBbits.TRISB12 = 1;//RB12-->AN12
	TRISBbits.TRISB13 = 1;//RB13-->AN13
//设置为模拟输入
	AD1PCFGLbits.PCFG2 = 0;//
	AD1PCFGLbits.PCFG3 = 0;//
	AD1PCFGLbits.PCFG4 = 0;//
	AD1PCFGLbits.PCFG5 = 0;//
	AD1PCFGLbits.PCFG6 = 0;//
	AD1PCFGLbits.PCFG7 = 0;//
	AD1PCFGLbits.PCFG8 = 0;//
	AD1PCFGLbits.PCFG9 = 0;//
	AD1PCFGLbits.PCFG10 = 0;//
	AD1PCFGLbits.PCFG11 = 0;//
	AD1PCFGLbits.PCFG12 = 0;//
	AD1PCFGLbits.PCFG13 = 0;//
	AD1CON1 = 0x80E0;
	AD1CON1bits.ADSIDL=0;//模块在空闲模式下继续工作	
	AD1CON2 = 0;
	AD1CON3 = 0x0F04;
	AD1CSSL = 0;//
}
unsigned int ADC(unsigned char prot)//返回AD值
{
	unsigned long Result;
	unsigned int Ad_Result;
	ClrWdt(); 
	AD1CHS0 = prot;  
	DISICNT = 0x3FFF; /* disable interrupts */      
	asm("nop");
	AD1CON1bits.SAMP = 1;
	while(!AD1CON1bits.DONE){
		Nop();
	}
	Result = (long) ADC1BUF0; 
	Ad_Result = (int)Result;////////
	Result = 0;
	DISICNT = 0x0000; /* enable interrupts */
	return (unsigned int)Ad_Result;
}
unsigned int Adc_Count(unsigned char Type,unsigned char Count)
{
/*
	多次采集AD并对多次的值求平均
*/
	volatile unsigned char temp;
	uchar i;
	unsigned  int Sum=0;//long
	uint Summax=0,Summin=0,SumTemp=0;
	temp = Type;
	for(i=0 ; i<Count + 2 ; i++)
	{
		IVC102S2 = 1;
		if(temp == PD5){
			PDx_Delay_start.PD5_Num = 1;
			while(PDx_Delay_start.PD5_Num);
		}
		if(temp == PD6){
			PDx_Delay_start.PD6_Num = 1;
			while(PDx_Delay_start.PD6_Num);
		}
		SumTemp = ADC(Type);
		IVC102S2 = 0;
		Delay_ms(5);
	 	if(i==0)
	 	{
	 		Summax = SumTemp;
	 		Summin = SumTemp;//get the first 
	 	}
	 	if(Summax<SumTemp)Summax = SumTemp;//get the Max adc	 		
	 	if(Summin>SumTemp)Summin = SumTemp;//get the Min adc	 		
	 	Sum += SumTemp;
	}
	temp = 0;//将变量清零
    SumTemp = Sum - Summax - Summin;
	Sum     = SumTemp/(uint)(Count);//del the Max and Min
	return(Sum);
}
















