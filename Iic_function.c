#include "Iic_function.h"
#include "Delay_function.h"
#include "p24FJ256GA106.h"
#include "Init_function.h"

uchar Time_array[7] = {0x01,0x01,0x08,0x07,0x01,0x0a,0x17};
//Ĭ��ʱ��2017��10��1��08ʱ01��01�� ������

DATE_TIME Rtc_time;
DATE_TIME Check_time;

#ifdef IIC_Diver
void IIC_Init()
{
	unsigned char i;
	setSCL=0;//�����
	delay_2us();
	setSDA=0;
	for(i=0;i<10;i++)
	{
		SCL=0;
		delay_4us();
		SCL=1;
		delay_4us();
	}
}
void I2C_Start(void)//��ʼ�ź�
{
	setSDA=0;
	setSCL=0;//�����
	delay_4us();
	SDA=1;
	delay_4us();
	SCL=1;
	delay_4us();
	SDA=0;
	delay_2us();
	SCL=0;
	delay_4us();
}

void I2C_Stop(void)//ֹͣ�ź�
{
	setSCL=0;//�����
	setSDA=0;
	SCL=0;
	SDA=0;
	delay_4us();
	SCL=1;
	delay_4us();
	SDA=1;
	delay_2us();
}
void ack(void)//���ͼ������ź�
{ 
	setSCL = 0;
	setSDA = 0;
    SDA=0;
    SCL=0;
    SCL=1;
	delay_2us();
    SCL=0;
}    
void nack(void)//ֹͣ������
{ 
    SDA=1;
    SCL=0;
    SCL=1;
	delay_2us();
	SCL=0;
}

unsigned char ReadByte(void)//������
{
	unsigned char i,data=0x00;
	setSCL=0;//�����
	setSDA=1;//������
//	SDA = 1;
	SCL=0;
	for(i=0;i<8;i++)
	{	
		SCL=1;
		delay_2us();
		data=data<<1;	
		if(SDA)data|=0x01;
		else data&=0xfe;	
		SCL=0;
		delay_2us();
	}
	return data;
}
unsigned char check(void)//���Ӧ���ź�
{  
	unsigned int ucErrTime;
	setSCL=0;//�����
	setSDA=1;//������
	SCL=0;
	SDA=1;delay_4us();
	SCL=1;delay_4us();	
	ucErrTime=0;
	while(SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			I2C_Stop();
			//LED3 =! LED3;
			return 1;
		}
	}
    SCL=0;
    return 0;	
}

void WriteByte(unsigned char data)//��������
{
	unsigned char i,temp;
	setSCL=0;//�����
	setSDA=0;
	temp = data;
	for(i=0;i<8;i++)
	{	
		SCL=0;
		//delay_2us();
		/*
		if(temp&0x80)   
		{
		   SDA=1;          //���� 1		            
		}  
		else 
		{
		   SDA=0;          //���� 0
		}*/
		SDA = (temp&0x80)>>7;
		temp<<=1;
		SCL=1;
		delay_2us();
		SCL=0;
		delay_2us();
	}
}

#endif
#ifdef DS1340Z
//RTCʱ���ַ00h-06h
//sec --> 00h
//min --> 01h
//hour --> 02h
//week --> 03h
//day --> 04h
//month --> 05h
//year --> 06h
void RTC_Init()
{
	ReadRtccTime();//������һ��ʱ��
	if( !CheckRTCVail() )//����Ƿ���ڷǷ�ʱ��
	{
		Time_array[0] = 0x00;//��
		Time_array[1] = 0x08;//��
		Time_array[2] = 0x08;//ʱ
		Time_array[3] = 0x07;//����
		Time_array[4] = 0x01;//��
		Time_array[5] = 0x0a;//��
		Time_array[6] = 0x17;//��
		SetRtccDefault();
	}
}
void I2cRtccWriteByte(unsigned char Address,unsigned char Data) 
{
	I2C_Start();				
	WriteByte(WriteRTC_CtrolByte);	
	delay_2us();
	check();			
	WriteByte(Address);			
	delay_2us();
	delay_4us();
	check();				
	WriteByte(Data);		
	delay_2us();
	check();				
	I2C_Stop();	
}
unsigned char I2CRtccReadByte(unsigned char Address)
{
	uint i,j;
	uchar data;
	I2C_Start();				
	WriteByte(WriteRTC_CtrolByte);
	check();				
	WriteByte(Address);		
	check();				
	I2C_Start();			
	WriteByte(ReadRTC_CtrolByte);
	check();			
	data=ReadByte();
	nack();
	I2C_Stop();			
	return data;
}
void SetRtccDefault(void)
{
	unsigned char i;
	for(i=0;i<7;i++)I2cRtccWriteByte(i,Time_array[i]);	
}
void ReadRtccTime(void)
{
	uchar i,TimeTemp[7];
	uchar temp_rtc[7];
	for(i=0;i<7;i++)TimeTemp[i]=I2CRtccReadByte(i);
	TimeTemp[0] = TimeTemp[0]&0x7f;//sec
	TimeTemp[1] = TimeTemp[1]&0x7f;//min
	TimeTemp[2] = TimeTemp[2]&0x3f;//hour
	TimeTemp[3] = TimeTemp[3]&0x07;//week
	TimeTemp[4] = TimeTemp[4]&0x3f;//day
	TimeTemp[5] = TimeTemp[5]&0x1f;//month
	TimeTemp[6] = TimeTemp[6];//year
			
	Rtc_time.year  = (TimeTemp[6] >> 4)*10 + (TimeTemp[6] & 0x0f);//��
	Rtc_time.month = (TimeTemp[5] >> 4)*10 + (TimeTemp[5] & 0x0f);//��
	Rtc_time.day   = (TimeTemp[4] >> 4)*10 + (TimeTemp[4] & 0x0f);//��
	Rtc_time.week  = (TimeTemp[3] >> 4)*10 + (TimeTemp[3] & 0x0f);//����
	Rtc_time.hour  = (TimeTemp[2] >> 4)*10 + (TimeTemp[2] & 0x0f);//ʱ
	Rtc_time.min   = (TimeTemp[1] >> 4)*10 + (TimeTemp[1] & 0x0f);//��
	Rtc_time.sec   = (TimeTemp[0] >> 4)*10 + (TimeTemp[0] & 0x0f);//��

}
unsigned char CheckRTCVail(void)
{
	if ( Rtc_time.year > 99 ) 
		return 0;
	if ( (Rtc_time.month == 0) || ( Rtc_time.month > 12 ) ) 
		return 0;
	if ( (Rtc_time.day == 0) || ( Rtc_time.day  > 31 ) ) 
		return 0;
	if ( Rtc_time.hour > 23 ) 
		return 0;
	if ( Rtc_time.min > 59 ) 
		return 0;
	if ( Rtc_time.sec > 59 ) 
		return 0;
	if ( Rtc_time.week > 7 ) 
		return 0;
    return 1;
}
#endif



#ifdef DS1631AU
//ds1631au�߾��������¶ȼƺ��¶ȼ����
/*
�¶ȱ�ʾ����  ���¶��Ǹ�ֵʱ
TH ����ȡ����ʾ��������
TL ����ȡ����һ��ʾС������
*/
/*
	�¶ȿ�����60������2��
	temp0 = ds1631_read_TH_TL(0XAA);
	temp = (temp0) / 256;//�¶ȸ�λ
	temp1 = temp0 & 0xff;
	if(temp>=0x80) //if sign char is set, then temp is negative
		temp_c = (float)(temp0 - 65536) * 0.0625;
	else
		temp_c = (float)(temp0 * 0.00390625);


*/
uchar DS1631_over_flag()
{
	uint temp;
	float Temperature;
	temp = ds1631_read_TH_TL(0xaa);
	if(temp>=0x80) //if sign char is set, then temp is negative
		Temperature = (float)(temp - 65536) * 0.0625;
	else
		Temperature = (float)(temp * 0.00390625);
	
	if(Temperature>=60.0)//ʵ���¶ȴ�����
		return 1;
	else 
		return 0;
}
unsigned int ds1631_read_TH_TL(unsigned char comm)
{
	unsigned int temp;
	unsigned char dataH,dataL;
	I2C_Start();
	WriteByte(ds1631_WriteCtrolByte);
	check();
	WriteByte(comm);
	check();
	I2C_Start();
	WriteByte(ds1631_ReadCtrolByte);
	check();
	dataH = ds1631_ReadByte();
	ack();
	dataL = ds1631_ReadByte();
	nack();
	I2C_Stop();
	temp = dataH << 8 | dataL;
	return temp;
}
void ds1631_T(unsigned char hot_flag)
{
	I2C_Start();
	WriteByte(ds1631_WriteCtrolByte);
	check();
	WriteByte(hot_flag);
	check();
	I2C_Stop();	
}
void ds1631_write_config(unsigned char D)
{
	unsigned char data;
	data = D;
	I2C_Start();
	WriteByte(ds1631_WriteCtrolByte);
	check();
	WriteByte(0xac);
	check();
	WriteByte(data);
	check();
	I2C_Stop();
}
unsigned char ds1631_read_config()
{
	unsigned char data;
	data = 0;
	I2C_Start();
	WriteByte(ds1631_WriteCtrolByte);
	check();
	WriteByte(0xac);
	check();
	I2C_Start();
	WriteByte(ds1631_ReadCtrolByte);
	check();
	data = ds1631_ReadByte();
	nack();
	I2C_Stop();
	return data;
}
void ds1631_write_TH_TL(unsigned char comm,unsigned char TH,unsigned char TL)
{
	I2C_Start();
	WriteByte(ds1631_WriteCtrolByte);
	check();
	WriteByte(comm);
	check();
	WriteByte(TH);
	check();
	WriteByte(TL);
	check();
	I2C_Stop();
}

unsigned char ds1631_ReadByte(void)//������
{
	unsigned char i,data;
	data=0x00;
	setSCL=0;//�����
	setSDA=1;//������
	SCL=0;
	for(i=0;i<8;i++)
	{	
		SCL=1;
		delay_1us();
		data<<=1;
        if(SDA)data++;  
		SCL=0;
		delay_2us();
	}
	return data;
}

void ds1631()
{
	I2C_Start();
	WriteByte(ds1631_WriteCtrolByte);
	check();
	
	WriteByte(WR_commandbyte);
	check();
	
	WriteByte(0x02);//����ת��ģʽ
	check();
	I2C_Stop();	
	delay_3us();
	I2C_Start();
	WriteByte(ds1631_WriteCtrolByte);
	check();
	WriteByte(0xa1);
	check();

	WriteByte(0x64);//�¶��������ָ�8λ	TH  58��
	check();
	WriteByte(0x00);//û��ʹ��
	check();
	I2C_Stop();	
	delay_3us();
	I2C_Start();
	WriteByte(ds1631_WriteCtrolByte);
	check();
	WriteByte(0xa2);
	check();
	WriteByte(0xe0);//�¶�С������  TL
	check();
	WriteByte(0x00);//�¶�С������û��ʹ��
	check();
	I2C_Stop();	
	delay_3us();
	I2C_Start();
	WriteByte(ds1631_WriteCtrolByte);
	check();
	WriteByte(0x51);
	check();
	I2C_Stop();	
}







#endif

#ifdef  LTC3207EUF

void clear_uled_setting()
{
	unsigned char i;
	for(i=1;i<11;i++)
	{
		I2C_Start();
		WriteByte(LTC3207EUF_Add);//������ַ
		check();
		WriteByte(0x00);//Sub-Address
		check();
		WriteByte(0x00);//data
		check();
		I2C_Stop();	
	}	

}
void uled_on_control(unsigned char pass)
{
	I2C_Start();
	WriteByte(LTC3207EUF_Add);//������ַ
	check();
	WriteByte(pass);//Sub-Address
	check();
	WriteByte(0x0b);//data
	check();
	I2C_Start();
	WriteByte(LTC3207EUF_Add);//������ַ
	check();
	WriteByte(0x0f);//Sub-Address
	check();
	WriteByte(0x00);//data
	check();
	I2C_Stop();	
}
void uled_off_control(unsigned char pass)
{
	I2C_Start();
	WriteByte(LTC3207EUF_Add);//������ַ
	check();
	WriteByte(pass);//Sub-Address
	check();
	WriteByte(0x00);//data
	check();
	I2C_Start();
	WriteByte(LTC3207EUF_Add);//������ַ
	check();
	WriteByte(0x0f);//Sub-Address
	check();
	WriteByte(0x00);//data
	check();
	I2C_Stop();	

}

void start_uled_all()
{
	char i;
	I2C_Start();
	WriteByte(LTC3207EUF_Add);//������ַ
	check();
	WriteByte(0x0f);//Sub-Address
	check();
	WriteByte(0x20);//data
	check();
	for(i=1;i<11;i++){
		I2C_Start();
		WriteByte(LTC3207EUF_Add);//������ַ
		check();
		WriteByte(i);//Sub-Address
		check();
		WriteByte(0x4b);//data
		check();
	}
		I2C_Stop();	
}
void Setting_Uled_A()
{
char i;
for(i=1;i<11;i++){
	I2C_Start();
	WriteByte(LTC3207EUF_Add);
	check();
	WriteByte(i);
	check();
	WriteByte(0x0f);
	check();
	I2C_Stop();	
	}
}

void ULED_ON(char num,unsigned char q)
{
	I2C_Start();
	WriteByte(LTC3207EUF_Add);//������ַ
	check();
	WriteByte(num);//Sub-Address
	check();
	WriteByte(q);//data
	check();
	I2C_Stop();	
}
void set_uled(char num,char p)
{
	I2C_Start();
	WriteByte(LTC3207EUF_Add);//������ַ
	check();
	WriteByte(0x01);//Sub-Address
	check();
	WriteByte(0x8b);//data
	check();
	I2C_Start();
	WriteByte(LTC3207EUF_Add);//������ַ
	check();
	WriteByte(0x07);//Sub-Address
	check();
	WriteByte(0x8b);//data
	check();
	I2C_Start();
	WriteByte(LTC3207EUF_Add);//������ַ
	check();
	WriteByte(0x00);//Sub-Address
	check();
	WriteByte(0x01);//data
	check();
	I2C_Stop();	
}
#endif

#ifdef AT24C1024
/*
��ַ0x0000���ڼ��eeprom�Ƿ���������д
��ַ��Χ:0x0001----0x1ffff
*/
uchar AT24Cxx_Check()
{
	uchar temp;
	temp = 0;
	temp = AT24C1024_R_Byte(0x00);
	if(temp == 0x45)
		return 0;
	else{
		AT24C1024_W_Byte(0x0000,0x45);
		temp = AT24C1024_R_Byte(0x00);
		if(temp == 0x45)
			return 0;
	}
	return 1;
}
void AT24C1024_W_Byte(uint add,uchar data)
{
	uchar addh,addl;
	addh = add >> 8;
	addl = add & 0xff;
	I2C_Start();
	WriteByte(AT24C1024_W_ADD);//������ַ
	check();
	WriteByte(addh);
	check();
	WriteByte(addl);
	check();
	WriteByte(data);
	check();
	I2C_Stop();	
	Delay_ms(20);
}
uchar AT24C1024_R_Byte(uint add)
{
	uchar data,addh,addl;
	addh = add >> 8;
	addl = add & 0xff;
	data = 0;
	I2C_Start();				//��ʼ�ź�
	WriteByte(AT24C1024_W_ADD);	//����������ַ A2
	check();				//�ȴ�Ӧ��
	WriteByte(addh);
	check();				//�ȴ�Ӧ��
	WriteByte(addl);
	check();				//�ȴ�Ӧ��
	I2C_Start();				//��ʼ������
	WriteByte(AT24C1024_R_ADD);	//����������ַ A3
	check();				//�ȴ�Ӧ��
	data=ReadByte();
	nack();
	I2C_Stop();					//ֹͣ�ź�
	return data;

}
void AT24C1024_W_Word(uint add,uint date)
{
	uchar addh,addl,dateh,datel;
	addh = add >> 8;
	addl = add & 0xff;
	dateh = date >> 8;
	datel = date & 0xff;
	I2C_Start();
	WriteByte(AT24C1024_W_ADD);
	check();
	WriteByte(addh);
	check();
	WriteByte(addl);
	check();
	WriteByte(dateh);
	check();
	WriteByte(datel);
	check();
	I2C_Stop();	
	Delay_ms(20);
}
uint AT24C1024_R_Word(uint add)
{
	uchar addh,addl,datah,datal;
	uint temp;
	temp = 0;
	addh = add >> 8;
	addl = add & 0xff;
	I2C_Start();				//��ʼ�ź�
	WriteByte(AT24C1024_W_ADD);	//����������ַ A2
	check();				//�ȴ�Ӧ��
	WriteByte(addh);
	check();				//�ȴ�Ӧ��
	WriteByte(addl);
	check();				//�ȴ�Ӧ��
	I2C_Start();				//��ʼ������
	WriteByte(AT24C1024_R_ADD);	//����������ַ A3
	check();				//�ȴ�Ӧ��
	datah = ds1631_ReadByte();
	ack();
	datal = ds1631_ReadByte();
	nack();
	I2C_Stop();
	temp = addh << 8 | addl ;
	return temp;
}
/*
void AT24C1024_W_Page(uchar addh,uchar addl,uchar len,uchar *buff)
{
//	uchar i;
//	i = 255;
	I2C_Start();
	WriteByte(AT24C1024_W_ADD);//������ַ
	check();
	WriteByte(addh);
	check();
	WriteByte(addl);
	check();
	while(len--){
		WriteByte(*buff);
		check();
		buff++;
	}
	I2C_Stop();	
}
*/
#endif//AT24C1024













