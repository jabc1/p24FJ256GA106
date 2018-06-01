#ifndef _UART_FUNCTION_H
#define _UART_FUNCTION_H
#define 	UART2_BUF_SIZE         255
#define 	U2R_TIMEOUT 		   1500
#define 	UART3_BUF_SIZE         255
#define 	U3R_TIMEOUT 		   1500
#define 	UART4_BUF_SIZE         255
#define 	U4R_TIMEOUT 		   1500

//波特率发生器计算 BRGH = 1
#define 	Fosc2 				8000000*2        
#define 	BAUD2 				115200            
#define 	BRG2  				((Fosc2/BAUD2)/4)-1  
#define 	Fosc3  				8000000*2        
#define 	BAUD3  				38400            
#define 	BRG3  				((Fosc3/BAUD3)/4)-1 
#define 	Fosc4  				8000000*2        //系统时钟8MHz采用2倍频
#define 	BAUD4  				38400            //波特率采用115200bps
#define 	BRG4  				((Fosc4/BAUD4)/4)-1  //计算和定义波特率设置参数

/*
BRG = ((Fosc/BAUD)/4)-1
目标波特率 = Fosc / (4(BRG+1))
误差 = (计算波特率-目标波特率)/(目标波特率)
*/

//void U1_Hand(void);
void U2_Hand(void);
void U3_Hand(void);
//void Init_Uart1(void);
void Init_Uart2(void);
void Init_Uart3(void);
void Uart_PutChar(unsigned char Type,unsigned char Ch);
void Uart_PutString(unsigned char Type,char *string);
void  __attribute__((interrupt, shadow, no_auto_psv)) _U2RXInterrupt(void);
void  __attribute__((interrupt, shadow, no_auto_psv)) _U2TXInterrupt(void);
void  __attribute__((interrupt, shadow, no_auto_psv)) _U3RXInterrupt(void);
void  __attribute__((interrupt, shadow, no_auto_psv)) _U3TXInterrupt(void);
void  __attribute__((interrupt, shadow, no_auto_psv)) _U4RXInterrupt(void);
void  __attribute__((interrupt, shadow, no_auto_psv)) _U4TXInterrupt(void);





#endif



