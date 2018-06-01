#include "Init_function.h"
#include "p24FJ256GA106.h"

System_variable		Sys_temp;
void Init_IO()
{
	setLED3 = 0;//设置输出
	LED3 = 0;
	setLED4 = 0;
	LED4 = 1;
	setBEEP = 0;
	BEEP = 0;
	setHot = 0;
	Hot = 0;
	setIVC102S1 = 0;
	IVC102S1 = 0;
	setIVC102S2 = 0;
	IVC102S2 = 0;
	setNear_S0 = 0;
	Near_S0 = 1;
	setNear_S1 = 0;
	Near_S1 = 1;
	setNear1 = 1;//设置输入
	setNear2 = 1;
	setNear3 = 1;
	setNear4 = 1;
	setNear5 = 1;
	setNear6 = 1;
	setNear7 = 1;
	setNear8 = 1;
	setNear9 = 1;
	setNear10 = 1;
	Sys_temp.Count = 0;
	Sys_temp.flag = 0;
	Sys_temp.Num = 0;
}












