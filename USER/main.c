#include "stm32f4xx.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "DS18B20.h"


// ʵ�� DS18B20_GetTemperature ����
short DS18B20_GetTemperature(void)
{
    // ������ӻ�ȡ�¶ȵ�ʵ�ʴ���
    return 315; // ��ʱ����һ����ֵ��ʵ��Ӧ������Ҫ�滻Ϊ��ȷ���¶�ֵ
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
