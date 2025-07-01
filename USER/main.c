#include "stm32f4xx.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "DS18B20.h"


// 实现 DS18B20_GetTemperature 函数
short DS18B20_GetTemperature(void)
{
    // 这里添加获取温度的实际代码
    return 315; // 暂时返回一个假值，实际应用中需要替换为正确的温度值
}
int main(void)
{
	u32 t=0;
	u8 ret=0;
	short temper;
	delay_init(168);
	Led_Init();
	uart_init(115200);
	DS18B20_Init();
	while(1)
	{
		delay_ms(500);
		GPIO_ResetBits(GPIOF,GPIO_Pin_9 | GPIO_Pin_10);
		delay_ms(500);
		GPIO_SetBits(GPIOF,GPIO_Pin_9 | GPIO_Pin_10);
		printf("t= %d\r\n",t);
		t++;
		//ret = DS18B20_Init();
		temper = DS18B20_GetTemperature();
		printf("temper = %d,temper/10=%lf\r\n",temper,(float)temper/10.0);
	}
	
}
