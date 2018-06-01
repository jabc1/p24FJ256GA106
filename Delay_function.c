#include "Delay_function.h"
#include "p24FJ256GA106.h"
//延时大于等于3时基本准确
void Delay_us(unsigned int num)
{
	unsigned int i;
	for(i=num;i>0;i--){
		Nop();Nop();Nop();Nop();Nop();
	}
}
void Delay_ms(unsigned int num)
{
	unsigned int i,j;
	for(i=num;i>0;i--)
		for(j=800*5;j>0;j--);
}
#if 0
void delay_1us()
{
	Nop();Nop();Nop();Nop();Nop();Nop();
}
void delay_2us()
{
	Nop();Nop();Nop();Nop();Nop();Nop();
	Nop();Nop();Nop();Nop();Nop();Nop();
	Nop();Nop();Nop();Nop();Nop();Nop();
	Nop();Nop();Nop();Nop();
}
void delay_3us()
{
	unsigned int i;
	for(i=3;i>0;i--){
		Nop();Nop();Nop();Nop();
	}
	
}
void delay_4us()
{
	unsigned int i;
	for(i=4;i>0;i--){
		Nop();Nop();Nop();Nop();
	}
}

#else
void delay_1us()
{
	unsigned int i;
	for(i=4;i>0;i--){
		Nop();Nop();Nop();Nop();
	}
}
void delay_2us()
{
	unsigned int i;
	for(i=4;i>0;i--){
		Nop();Nop();Nop();Nop();
	}
}
void delay_3us()
{
	unsigned int i;
	for(i=4;i>0;i--){
		Nop();Nop();Nop();Nop();
	}
	
}
void delay_4us()
{
	unsigned int i;
	for(i=4;i>0;i--){
		Nop();Nop();Nop();Nop();
	}
}
#endif




