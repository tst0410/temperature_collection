#ifndef __DS18B20_H
#define __DS18B20_H
#include "sys.h"
#include "stm32f4xx_gpio.h"

#define DS18B20_DQ_IN PGin(9)
#define DS18B20_DQ_OUT PGout(9)
void DS18B20_IO_OUT(void);
void DS18B20_IO_IN(void);
uint8_t DS18B20_Init(void);
void DS18B20_Rst(void);
uint8_t DS18B20_Check(void);//0 ok
void DS18B20_Write_Byte(uint8_t data);
uint8_t DS18B20_Read_Bit(void);
uint8_t DS18B20_Read_Byte(void);
void DS18B20_Start(void);
short DS18B20_GrtTemperature(void);



#endif
