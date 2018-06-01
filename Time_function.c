#include "Time_function.h"
#include "Init_function.h"
#include "Uart_function.h"
#include "p24FJ256GA106.h"
#include "Iic_function.h"
TimeNum 	Time1Count;
TimeNum		PDxCount;
TimeNum		Time3Count;
PDx			PDxStart_flag;
PDx			PDx_Count;
PDx			PDx_Over;
PDx			PDx_Min;
PDx			PDx_Delay_start;
PDx			PDx_Delay_end;
PDx			PDx_NUM;
void Init_num()
{
	Time1Count.ms = 0;
	Time1Count.sec = 0;
	Time1Count.min = 0;
	Time1Count.hour = 0;
	Time1Count.ms_flag = 0;
	Time1Count.sec_flag = 0;
	Time1Count.hour_falg = 0;

	PDxCount.sec = 0;
	PDxCount.sec_flag = 0;

	Time3Count.ms = 0;
	Time3Count.sec = 0;
	Time3Count.min = 0;
}
/*
定时器计算公式
中断一次时间=16M/PRx
*/

void Init_Time1()//用在记时
{
	T1CON=0;     //timer1控制寄存器
    TMR1=0;      //timer1寄存器
    PR1=16000;  //timer1周期寄存器
    
    _T1IP=4;     //中断优先级
    _T1IF=0;     //中断标志 1产生中断 0未产生中断
    T1CON=0x8000;//启动timer1 TON=1 
    _T1IE = 1;

}

void Init_Time2()
{
	T2CON=0;   
    TMR2=0;  
    PR2=16000; //1ms进一次中断
    _T2IP=4;
    _T2IF=0;
    T2CON=0x8000;
    _T2IE = 1;

}
void Init_Time3()//用于扫描接近传感器管脚
{
	T3CON=0;   
    TMR3=0;  
    PR3=16000; //1ms进一次中断
    _T3IP=4;
    _T3IF=0;
    T3CON=0x0000;//默认不开启中断
    _T3IE = 1;
}
void Init_Time4()
{
	T4CON=0;   
    TMR4=0;  
    PR4=16000; //1ms
    _T4IP=4;
    _T4IF=0;
    T4CON=0x0000;//默认不开启中断
    _T4IE = 1;
}
void Init_Time5()
{
	T5CON=0;   
    TMR5=0;  
    PR5=16000; //1ms进一次中断
    _T5IP=5;
    _T5IF=0;
    T5CON=0x0000;//默认不开启中断
    _T5IE = 1;
}
void Test_Near()
{
	/*
	uchar i,PD[10];
	if(Time3Count.ms%90==0){
		
		for(i=0;i<10;i++)
			PD[i] = PORTD >> i & 0x001;
		
		if(PD[0] == 1){
			LED4 = 1;
		}
		else{
			LED4 = 0;
		}
		if(PD[1] == 1)
			BEEP = 1;
		else
			BEEP = 0;

		for(i=0;i<10;i++)
			PD[i] = 0;

	}
	*/
	Start_PDx();
	
}

void Start_PDx()
{
	unsigned char 	PD[10],i;
	if(Time3Count.ms%90==0){
		for(i=0;i<10;i++)
			PD[i] = (PORTD >> i) & 0x0001;//得到各个通道的值
			
		if(PD[0] == 1){
			PDx_Count.PD1_Num ++;
			BEEP = 1;//有物体接近时
		}
		else{
			PDx_Count.PD1_Num = 0;
			BEEP = 0;
		}
		if(PD[1] == 1){
			PDx_Count.PD2_Num ++;
		}
		else{
			PDx_Count.PD2_Num = 0;
		}	
		if(PD[2] == 1){
			PDx_Count.PD3_Num ++;
			//LED4 = 1;
		}
		else{
			PDx_Count.PD3_Num = 0;
			//LED4 = 0;
		}
		if(PD[3] == 1){
			PDx_Count.PD4_Num ++;
		}
		else{
			PDx_Count.PD4_Num = 0;
		}
		if(PD[4] == 1){
			PDx_Count.PD5_Num ++;
		}
		else{
			PDx_Count.PD5_Num = 0;
		}
		if(PD[5] == 1){
			PDx_Count.PD6_Num ++;
		}
		else{
			PDx_Count.PD6_Num = 0;
		}
		if(PD[6] == 1){
			PDx_Count.PD7_Num ++;
		}
		else{
			PDx_Count.PD7_Num = 0;
		}
		if(PD[7] == 1){
			PDx_Count.PD8_Num ++;
		}
		else{
			PDx_Count.PD8_Num = 0;
		}
		if(PD[8] == 1){
			PDx_Count.PD9_Num ++;
		}
		else{
			PDx_Count.PD9_Num = 0;
		}
		if(PD[9] == 1){
			PDx_Count.PD10_Num ++;
		}
		else{
			PDx_Count.PD10_Num = 0;
		}
	}
	for(i=0;i<10;i++)
		PD[i] = 0;


}
void PDx_Stop()
{
	if(PDx_Count.PD1_Num == 10800)
		PDx_Over.PD1_Num = 1;
}
void  __attribute__((interrupt, shadow, no_auto_psv)) _T1Interrupt(void)
{
  	DISICNT = 0x3FFF ; // disable interrupts 
    IFS0bits.T1IF = 0;//clear timer1 int flag
	if(Time1Count.ms++>=999){
		Time1Count.ms = 0;
		LED3 = !LED3;
		if( Time1Count.sec++>=60){
			Time1Count.sec= 0;
			Time1Count.min_flag = 1;
		}
		if(PDxCount.sec++>=1){
			PDxCount.sec = 0;
			PDxCount.min_flag = 1;
		}
	}	
	if(PDx_Delay_start.PD5_Num==1){
		if(PDx_NUM.PD5_Num++ >= 35){
			PDx_NUM.PD5_Num = 0;
			PDx_Delay_start.PD5_Num = 0;
		}
	}
	if(PDx_Delay_start.PD6_Num==1){
		if(PDx_NUM.PD6_Num++ >= 26){
			PDx_NUM.PD6_Num = 0;
			PDx_Delay_start.PD6_Num = 0;
		}
	}
	
    DISICNT = 0x0000 ;//enable interrupts
}
void  __attribute__((interrupt, shadow, no_auto_psv)) _T2Interrupt(void)
{
  	DISICNT = 0x3FFF ; // disable interrupts 
    IFS0bits.T2IF = 0;










	DISICNT = 0x0000 ;
}
void  __attribute__((interrupt, shadow, no_auto_psv)) _T3Interrupt(void)
{
  	DISICNT = 0x3FFF ; // disable interrupts 
    IFS0bits.T3IF = 0;
	if(Time3Count.ms++>=999){
		Time3Count.ms = 0;	
		//Start_PDx();
	}
	


	DISICNT = 0x0000 ;
}
/*
void PDx_Count_Function()
{
		if(PDxStart_flag.PD1_Num==1)
			PDx_Count.PD1_Num++;
		else
			PDx_Count.PD1_Num = 0;
}
*/
void  __attribute__((interrupt, shadow, no_auto_psv)) _T4Interrupt(void)
{
  	DISICNT = 0x3FFF ; // disable interrupts 
    IFS1bits.T4IF = 0;








	DISICNT = 0x0000 ;
}
void  __attribute__((interrupt, shadow, no_auto_psv)) _T5Interrupt(void)
{
  	DISICNT = 0x3FFF ; // disable interrupts 
    IFS1bits.T5IF = 0;




	
	DISICNT = 0x0000 ;
}




