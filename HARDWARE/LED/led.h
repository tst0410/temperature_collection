#ifndef __LED_H
#define __LED_H
#include "sys.h"
#include "stm32F4xx_gpio.h"


#define LED0 PFout(9)
#define LED1 PFout(10)

void Led_Init(void);



#endif
