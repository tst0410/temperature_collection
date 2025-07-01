#include "DS18B20.h"
#include "delay.h"


//PG9 00 输入 01 输出
void DS18B20_IO_OUT(void)
{
	GPIOG->MODER  &= ~(03<<(9*2));
	GPIOG->MODER  |= 1<<9*2;
}
void DS18B20_IO_IN(void)
{
	GPIOG->MODER &= ~(3<<(9*2));
}
u8 DS18B20_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG,ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;
	GPIO_Init(GPIOG,&GPIO_InitStructure);
	DS18B20_Rst();
	return DS18B20_Check();
	
}

void DS18B20_Rst(void)
{
		DS18B20_IO_OUT();
		DS18B20_DQ_OUT =0;
		delay_us(600);
		DS18B20_DQ_OUT =1;
		delay_us(15);
	
	
}
u8 DS18B20_Check(void)//0 ok
{
	u16 i=0;
	DS18B20_IO_IN();
	while(DS18B20_DQ_IN  &&i<200)
	{
		delay_us(1);
		i++;
	}
	if(i==200) 
	{

		return 1;
	}
	else
		i= 0;
	while(!DS18B20_DQ_IN && i<240)
	{
		delay_us(1);
		i++;
	}
	if(i== 240) 
	{

		return 1;
	}
	else
		return 0;
	
}
void DS18B20_Write_Byte(uint8_t data)
{
	uint8_t i;
	uint8_t testb;
	DS18B20_IO_OUT();
	for(i=0;i<8;i++)
	{
		testb=data&0x1;
		data=data>>1;
		if(testb)
		{
			DS18B20_DQ_OUT=0;
			delay_us(2);
			DS18B20_DQ_OUT=1;
			delay_us(60);
			
		}
		else
		{
	  	DS18B20_DQ_OUT=0;
			delay_us(60);
			DS18B20_DQ_OUT=1;
			delay_us(2);
			
		}
	}
}
uint8_t DS18B20_Read_Bit(void)
{
	uint8_t testb;
	DS18B20_IO_OUT();
	DS18B20_DQ_OUT =0;
	delay_us(2);
	DS18B20_DQ_OUT =1;
	delay_us(12);
	DS18B20_IO_IN();
	
	if(DS18B20_DQ_IN) testb=1;
	else testb=0;
	delay_us(50);
	return testb;
}
uint8_t DS18B20_Read_Byte(void)
{
	uint8_t i,j;
	uint8_t data;
	for(i=0;i<8;i++)
	{
		j= DS18B20_Read_Bit();
		data=(j<<7)|(data>>1);
	}
	return data;
}
void DS18B20_Start(void)
{
	DS18B20_Rst();
	DS18B20_Check();
	DS18B20_Write_Byte(0xCC);
	DS18B20_Write_Byte(0x44);
}
short DS18B20_GrtTemperature(void)//放大10倍
{
	uint8_t TL,TH;
	uint8_t sflag;//zhengfu biaozhi
	short tem;
	DS18B20_Start();
	DS18B20_Rst();
	DS18B20_Check();
	DS18B20_Write_Byte(0xCC);
	DS18B20_Write_Byte(0xBE);
	
	TL=DS18B20_Read_Byte();
	TH=DS18B20_Read_Byte();
	if(TH>7)//fushu
	{
		TH=~TH;
		TL=~TL;
		sflag=1;
		
	}
	else
	{
		sflag=0;
	}
	tem =(TH<<8)+TL;
	tem =tem*0.625;
	return tem;
}









