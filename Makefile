# MPLAB IDE generated this makefile for use with GNU make.
# Project: 111Demo_Project.mcp
# Date: Thu Nov 30 14:04:58 2017

AS = pic30-as.exe
CC = pic30-gcc.exe
LD = pic30-ld.exe
AR = pic30-ar.exe
HX = pic30-bin2hex.exe
RM = rm

111Demo_Project.hex : 111Demo_Project.cof
	$(HX) "111Demo_Project.cof"

111Demo_Project.cof : main.o Ad_function.o Delay_function.o Init_function.o Time_function.o Iic_function.o Gprs_function.o Test_function.o Uart_function.o
	$(CC) -mcpu=24FJ256GA106 "main.o" "Ad_function.o" "Delay_function.o" "Init_function.o" "Time_function.o" "Iic_function.o" "Gprs_function.o" "Test_function.o" "Uart_function.o" -o"111Demo_Project.cof" -Wl,--script="p24FJ256GA106.gld",--defsym=__MPLAB_BUILD=1,-Map="111Demo_Project.map",--report-mem

main.o : Gprs_function.h Test_function.h Iic_function.h p24FJ256GA106.h Ad_function.h Delay_function.h Uart_function.h Time_function.h p24FJ256GA106.h Init_function.h Includeh.h c:/program\ files\ (x86)/microchip/mplab\ c30/include/yvals.h c:/program\ files\ (x86)/microchip/mplab\ c30/include/stdio.h main.c
	$(CC) -mcpu=24FJ256GA106 -x c -c "main.c" -o"main.o" -g -Wall

Ad_function.o : p24FJ256GA106.h p24FJ256GA106.h Init_function.h Ad_function.h Ad_function.c
	$(CC) -mcpu=24FJ256GA106 -x c -c "Ad_function.c" -o"Ad_function.o" -g -Wall

Delay_function.o : p24FJ256GA106.h Delay_function.h Delay_function.c
	$(CC) -mcpu=24FJ256GA106 -x c -c "Delay_function.c" -o"Delay_function.o" -g -Wall

Init_function.o : p24FJ256GA106.h p24FJ256GA106.h Init_function.h Init_function.c
	$(CC) -mcpu=24FJ256GA106 -x c -c "Init_function.c" -o"Init_function.o" -g -Wall

Time_function.o : Iic_function.h p24FJ256GA106.h Uart_function.h p24FJ256GA106.h Init_function.h Time_function.h Time_function.c
	$(CC) -mcpu=24FJ256GA106 -x c -c "Time_function.c" -o"Time_function.o" -g -Wall

Iic_function.o : p24FJ256GA106.h Init_function.h p24FJ256GA106.h Delay_function.h Iic_function.h Iic_function.c
	$(CC) -mcpu=24FJ256GA106 -x c -c "Iic_function.c" -o"Iic_function.o" -g -Wall

Gprs_function.o : p24FJ256GA106.h Uart_function.h Gprs_function.h Gprs_function.c
	$(CC) -mcpu=24FJ256GA106 -x c -c "Gprs_function.c" -o"Gprs_function.o" -g -Wall

Test_function.o : Gprs_function.h Test_function.h Iic_function.h p24FJ256GA106.h Ad_function.h Delay_function.h Uart_function.h Time_function.h p24FJ256GA106.h Init_function.h Includeh.h Test_function.c
	$(CC) -mcpu=24FJ256GA106 -x c -c "Test_function.c" -o"Test_function.o" -g -Wall

Uart_function.o : Delay_function.h p24FJ256GA106.h Init_function.h p24FJ256GA106.h Uart_function.h Uart_function.c
	$(CC) -mcpu=24FJ256GA106 -x c -c "Uart_function.c" -o"Uart_function.o" -g -Wall

clean : 
	$(RM) "main.o" "Ad_function.o" "Delay_function.o" "Init_function.o" "Time_function.o" "Iic_function.o" "Gprs_function.o" "Test_function.o" "Uart_function.o" "111Demo_Project.cof" "111Demo_Project.hex"

