#ifndef _IIC_H_
#define _IIC_H_

#define		 	IIC_Diver//IIC驱动
#define 		DS1631AU//时钟芯片
#define 		DS1340Z//温控芯片
#define 		LTC3207EUF//ULED控制芯片
#define			AT24C1024//存储芯片
#define		uint		unsigned int
#define 	uchar		unsigned char
typedef struct //系统时间结构体
{
	unsigned char year;
	unsigned char month;
	unsigned char week;
	unsigned char day;
	unsigned char hour;
	unsigned char min;
	unsigned char sec;
}DATE_TIME;

#ifdef IIC_Diver
#define SCL 			PORTGbits.RG2
#define SDA 			PORTGbits.RG3
#define setSCL 			TRISGbits.TRISG2
#define setSDA 			TRISGbits.TRISG3
void IIC_Init(void);
void I2C_Start(void);
void I2C_Stop(void);
void ack(void);
void nack(void);
unsigned char ReadByte(void);
unsigned char check(void);
void WriteByte(unsigned char data);
#endif//IIC_Diver


#ifdef DS1631AU
#define ds1631_WriteCtrolByte 	0x90
#define ds1631_ReadCtrolByte 	0x91
#define WR_commandbyte			0xac//读写控制字
#define master_write_command	0x02
#define master_TH_command		0xa1
#define master_TL_command		0xa2
#define ds1631_hot_start		0x51//开始加热
#define ds1631_hot_end			0x22//停止加热
unsigned char ds1631_ReadByte(void);
void ds1631_T(unsigned char hot_flag);
unsigned int ds1631_read_TH_TL(unsigned char comm);
void ds1631_write_TH_TL(unsigned char comm,unsigned char TH,unsigned char TL);
unsigned char ds1631_read_config(void);
void ds1631_write_config(unsigned char D);
void ds1631(void);
uchar DS1631_over_flag(void);
#endif//DS1631AU


#ifdef DS1340Z
#define	WriteRTC_CtrolByte	0Xd0  //控制字:写准备(器件地址000)
#define	ReadRTC_CtrolByte	0Xd1  //控制字:读准备(器件地址000)
void RTC_Init(void);
void I2cRtccWriteByte(unsigned char Address,unsigned char Data);
unsigned char I2CRtccReadByte(unsigned char Address);
void SetRtccDefault(void);
void ReadRtccTime(void);
unsigned char CheckRTCVail(void);
#endif//DS1340Z

#ifdef  LTC3207EUF
#define LTC3207EUF_Add		0x34
void clear_uled_setting(void);
void uled_off_control(unsigned char pass);
void uled_on_control(unsigned char pass);
void start_uled_all(void);
#endif//LTC3207EUF



#ifdef 	AT24C1024
#define		AT24C1024_W_ADD		0XA0
#define		AT24C1024_R_ADD		0XA1

//申明存储地址内容




uchar AT24Cxx_Check(void);
void AT24C1024_W_Byte(uint add,uchar data);
uchar AT24C1024_R_Byte(uint add);
void AT24C1024_W_Word(uint add,uint date);
uint AT24C1024_R_Word(uint add);
#endif//AT24C1024


#endif//_IIC_H_






