#include <stm32f10x_lib.h>	   
//#include "led.h"

void LED_Init()
{
		RCC->APB2ENR|=1<<3;				  // ʹ��GPIOB����ʱ��	 
		RCC->APB2ENR|=1<<2;				  // ʹ��GPIOA����ʱ��
		GPIOB->CRH&=0X00000000;
		GPIOB->CRH|=0X33333333;			  // 0011ͨ������������ٶ�50MHz
		GPIOB->ODR|=0Xffff;
}
