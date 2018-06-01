#include "Uart_function.h"
#include "p24FJ256GA106.h"
#include "Init_function.h"
#include "Delay_function.h"


volatile unsigned int Uart2_rtimer = 0;
volatile unsigned char Rx2_Buff[UART2_BUF_SIZE],*Rx2_Ptrend,*Rx2_ptr,RX2_BUFFLEN=0;
volatile unsigned char Tx2_Buff[UART2_BUF_SIZE],*Tx2_Ptrend,*Tx2_ptr,TX2_BUFFLEN=0;

volatile unsigned int Uart3_rtimer = 0;
volatile unsigned char Rx3_Buff[UART3_BUF_SIZE],*Rx3_Ptrend,*Rx3_ptr,RX3_BUFFLEN=0;
volatile unsigned char Tx3_Buff[UART3_BUF_SIZE],*Tx3_Ptrend,*Tx3_ptr,TX3_BUFFLEN=0;

volatile unsigned int Uart4_rtimer = 0;
volatile unsigned char Rx4_Buff[UART4_BUF_SIZE],*Rx4_Ptrend,*Rx4_ptr,RX4_BUFFLEN=0;
volatile unsigned char Tx4_Buff[UART4_BUF_SIZE],*Tx4_Ptrend,*Tx4_ptr,TX4_BUFFLEN=0;



void U2_Hand()
{
	unsigned int i;
	unsigned char commd_type,commd;
	commd_type = Rx2_Buff[0];
	//�����յ������ݽ��ж�Ӧ���̵Ĵ���
	switch(commd_type)
	{
		case 1:
			LED3 = 0;
			break;
		case 2:
			LED4 = 0;
			break;
		case 3:
			LED3 = 1;
			LED4 = 1;
			break;
		default:
			break;
	}
	//������һ�ν�������������
	for(i = 0;i < UART2_BUF_SIZE; i++)
	{
		Rx2_Buff[i] = 0x00;	   
	}
	Rx2_ptr = &Rx2_Buff[0];
}
void U3_Hand()
{
	unsigned int i;
	unsigned char commd_type,commd;
	//�����յ������ݽ��ж�Ӧ���̵Ĵ���
	commd_type = Rx3_Buff[0];
	switch(commd_type)
	{
		case 6: 
			LED3 = 0;
			//Delay_ms(5);
			LED4 = 0;
			break;
		case 7:	
			LED3 = 0;
			//Delay_ms(5);
			LED4 = 1;
			break;
		case 8:	
			LED3 = 1;
			//Delay_ms(5);
			LED4 = 0;
			break;
		case 9: 			
			LED3 = 1;
			//Delay_ms(5);
			LED4 = 1;
			break;
		default:
			break;
	}
	//������һ�ν�������������
	for(i = 0;i < UART3_BUF_SIZE; i++)
	{
		Rx3_Buff[i] = 0x00;	   
	}
	Rx3_ptr = &Rx3_Buff[0];
}

void Init_Uart2()
{
	unsigned int i;
	//���ڳ�ʼ��
	U2MODE = 0xa808;
	U2MODEbits.BRGH = 1;
	U2BRG = BRG2; 
	U2STA = 0;

	_U2RXIF = 0;			  //�������жϱ�־״̬λ
	_U2TXIF = 0;			  //�������жϱ�־״̬λ

	_U2RXIP = 4;			  //�ж����ȼ�
	_U2TXIP = 4;			  //�ж����ȼ�

	U2MODEbits.UARTEN = 1;//���ڽ���ʹ��
	U2STAbits.UTXEN = 1;//���ڷ���ʹ��

	U2MODEbits.LPBACK = 0;

	_U2RXIE = 1;			  //�ж�����λ
	_U2TXIE = 0;			  //�ж�����λ

 	 //���ùܽ�
	TRISFbits.TRISF4 = 1;	  //u2rx ����
	Nop();
	TRISFbits.TRISF5 = 0;    //u2tx ���
	Nop();
	
	Rx2_ptr         = &Rx2_Buff[0]; 
	Rx2_Ptrend      = Rx2_ptr;
	
    Tx2_ptr         = &Tx2_Buff[0];        
    Tx2_Ptrend      = Tx2_ptr;  //  UART1PutChar(0x00

	for(i=0;i<UART2_BUF_SIZE;i++)//��ʼ�����պͷ�������
	{
		Rx2_Buff[i] = 0;
		Tx2_Buff[i] = 0; 
	}
	Uart2_rtimer = 0;

}
void Init_Uart3()
{
	unsigned int i;
	//���ڳ�ʼ��
	U3MODE = 0xa808;
	U3MODEbits.BRGH = 1;
	U3BRG = BRG3; 
	U3STA = 0;

	_U3RXIF = 0;			  //�������жϱ�־״̬λ
	_U3TXIF = 0;			  //�������жϱ�־״̬λ

	_U3RXIP = 4;			  //�ж����ȼ�
	_U3TXIP = 4;			  //�ж����ȼ�

	U3MODEbits.UARTEN = 1;//���ڽ���ʹ��
	U3STAbits.UTXEN = 1;//���ڷ���ʹ��

	U3MODEbits.LPBACK = 0;

	_U3RXIE = 1;			  //�ж�����λ
	_U3TXIE = 0;			  //�ж�����λ

 	 //���ùܽ�
	TRISGbits.TRISG6 = 0;    //u3tx ���
	Nop();
	TRISGbits.TRISG7 = 1;	  //u3rx ����
	Nop();
	
	Rx3_ptr         = &Rx3_Buff[0]; 
	Rx3_Ptrend      = Rx3_ptr;
	
    Tx3_ptr         = &Tx3_Buff[0];        
    Tx3_Ptrend      = Tx3_ptr;  //  UART1PutChar(0x00

	for(i=0;i<UART3_BUF_SIZE;i++)//��ʼ�����պͷ�������
	{
		Rx3_Buff[i] = 0;
		Tx3_Buff[i] = 0; 
	}
	Uart3_rtimer = 0;

}
void Init_Uart4()
{
	unsigned int i;
	//���ڳ�ʼ��
	U4MODE = 0xa808;
	U4MODEbits.BRGH = 1;
	U4BRG = BRG4; 
	U4STA = 0;

	_U4RXIF = 0;			  //�������жϱ�־״̬λ
	_U4TXIF = 0;			  //�������жϱ�־״̬λ

	_U4RXIP = 4;			  //�ж����ȼ�
	_U4TXIP = 4;			  //�ж����ȼ�

	U4MODEbits.UARTEN = 1;//���ڽ���ʹ��
	U4STAbits.UTXEN = 1;//���ڷ���ʹ��

	U4MODEbits.LPBACK = 0;

	_U4RXIE = 1;			  //�ж�����λ
	_U4TXIE = 0;			  //�ж�����λ

 	 //���ùܽ�
	TRISDbits.TRISD10 = 0;    //u4tx ���
	Nop();
	TRISDbits.TRISD11 = 1;	  //u4rx ����
	Nop();
	
	Rx4_ptr         = &Rx4_Buff[0]; 
	Rx4_Ptrend      = Rx4_ptr;
	
    Tx4_ptr         = &Tx4_Buff[0];        
    Tx4_Ptrend      = Tx4_ptr;  //  UART1PutChar(0x00

	for(i=0;i<UART4_BUF_SIZE;i++)//��ʼ�����պͷ�������
	{
		Rx4_Buff[i] = 0;
		Tx4_Buff[i] = 0; 
	}
	Uart4_rtimer = 0;

}
void  __attribute__((interrupt, shadow, no_auto_psv)) _U2RXInterrupt(void)
{

	DISICNT = 0x3FFF; 
	
	_U2RXIF = 0;//���жϱ�־λ
	unsigned char ch;
	
	while(U2STAbits.URXDA == 1) 
	{
		//�жϽ��պ���
		ch = U2RXREG;
		if(Rx2_ptr < &Rx2_Buff[UART2_BUF_SIZE])
		{
			*Rx2_ptr++ = ch;
			*Rx2_ptr = 0;
		}
		Uart2_rtimer =  U2R_TIMEOUT;//�����жϺ���ʵ�ִ��ڽ��յ�ʱ��ĸ�ֵ
		
        //RX2_BUFFLEN= Rx2_ptr - Rx2_Ptrend;
		
	}
	DISICNT = 0x0000; 

}
void  __attribute__((interrupt, shadow, no_auto_psv)) _U2TXInterrupt(void)
{

	//���ڷ��ͺ���
	DISICNT = 0x3FFF; 
	
	_U2TXIF = 0;//���жϱ�־λ
	//while(U2STAbits.TRMT == 0);
	if((TX2_BUFFLEN != 0) && (Tx2_ptr < &Tx2_Buff[UART2_BUF_SIZE])) 
	{
	
		//�жϷ��ͺ���
		U2TXREG = *Tx2_ptr++;	
		TX2_BUFFLEN--;
		
	}
	else{
		while(U2STAbits.TRMT == 0);
		_U2TXIE = 0;
	}
	//U2TXREG = 0xbb;
	DISICNT = 0x0000;

}
void  __attribute__((interrupt, shadow, no_auto_psv)) _U3RXInterrupt(void)
{
	 
	DISICNT = 0x3FFF; 
	unsigned char ch;
	_U3RXIF = 0;//���жϱ�־λ

	while(U3STAbits.URXDA == 1) 
	{
		//�жϽ��պ���
		ch = U3RXREG;
		U1TXREG = ch;
		//U3TXREG = ch;
		if(Rx3_ptr < &Rx3_Buff[UART3_BUF_SIZE])
		{
			*Rx3_ptr++ = ch;
			*Rx3_ptr = 0;
		}
		Uart3_rtimer =  U3R_TIMEOUT;//�����жϺ���ʵ�ִ��ڽ��յ�ʱ��ĸ�ֵ
		//Uart3_rtimer = 100;
        //RX3_BUFFLEN= Rx3_ptr - Rx3_Ptrend;
	}
	DISICNT = 0x0000; 

}
void  __attribute__((interrupt, shadow, no_auto_psv)) _U3TXInterrupt(void)
{

	//���ڷ��ͺ���
	DISICNT = 0x3FFF; 
	
	_U3TXIF = 0;//���жϱ�־λ
	//while(U3STAbits.TRMT == 0);
	if((TX3_BUFFLEN != 0) && (Tx3_ptr < &Tx3_Buff[UART3_BUF_SIZE])) 
	{
		//�жϷ��ͺ���
		U3TXREG = *Tx3_ptr++;	
		TX3_BUFFLEN--;
		//U3RXREG = U3TXREG;
	}
	else{
		while(U3STAbits.TRMT == 0);
		_U3TXIE = 0;
	}
	//U3TXREG = 0xbb;
	DISICNT = 0x0000;

}

void  __attribute__((interrupt, shadow, no_auto_psv)) _U4RXInterrupt(void)
{

	DISICNT = 0x3FFF; 
	
	_U4RXIF = 0;//���жϱ�־λ
//	unsigned char ch;
	

	DISICNT = 0x0000; 

}
void  __attribute__((interrupt, shadow, no_auto_psv)) _U4TXInterrupt(void)
{

	//���ڷ��ͺ���
	DISICNT = 0x3FFF; 
	_U1TXIF = 0;//���жϱ�־λ
	
	DISICNT = 0x0000;

}


void Uart_PutChar(unsigned char Type,unsigned char Ch)
{
	switch(Type){
		case 1:
			while(U1STAbits.UTXBF);
			U1TXREG = Ch;
			break;
		case 2:
			while(U2STAbits.UTXBF);
			U2TXREG = Ch;
			break;
		case 3:
			while(U3STAbits.UTXBF);
			U3TXREG = Ch;
			break;
		case 4:
			while(U4STAbits.UTXBF);
			U4TXREG = Ch;
			break;
		default:
			break;
	}
}


void Uart_PutString(unsigned char Type,char *string)
{
	while(*string){
		Uart_PutChar(Type , *string);
		string++;
	}
}

void UARTtranstart(unsigned char Type)
{ 
	unsigned char Buff[5],num,i;
	num = 0;
	Buff[num++] = 0x61;   
	Buff[num++] = 0x62;            
	Buff[num++] = 0x63;   
	Buff[num++] = 0x64;
	Buff[num++] = '\n'; 
	
	for(i=0;i<num;i++)
		Tx3_Buff[i] = Buff[i];
	Tx3_Ptrend = &Tx3_Buff[i];
	UARTtranstart(3);
	
	switch(Type){
		case 1:
			break;
		case 2:
			TX2_BUFFLEN = Tx2_Ptrend - &Tx2_Buff[1];
			Tx2_ptr = &Tx2_Buff[1];
		    
			U2TXREG = Tx2_Buff[0];//ͨ�����ڷ���������Ϣ
			_U2TXIE = 1;//ʹ���жϷ���
			break;
		case 3:
			TX3_BUFFLEN = Tx3_Ptrend - &Tx3_Buff[1];
			Tx3_ptr = &Tx3_Buff[1];
		    
			U3TXREG = Tx3_Buff[0];//ͨ�����ڷ���������Ϣ
			_U3TXIE = 1;//�����жϷ���
			break;
		case 4:
			break;
		default:
			break;
	}
	
}




