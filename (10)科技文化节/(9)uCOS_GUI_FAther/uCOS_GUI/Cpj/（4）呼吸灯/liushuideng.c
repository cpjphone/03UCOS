#include "sys.h"
unsigned char temp,count = 0;

NVIC_InitTypeDef NVIC_InitStructure;
TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;	   /*����Ϊ��Ӧ�Ľṹ��*/

int main()
{
	
		void LED_Init();			//����
		LED_Init();		  		    //���ã���ʼ����LED���ӵ�Ӳ���ӿ�
		delay_init(72);	     	    //���ã���ʱ��ʼ��
		//timer_init(500,7199);	    //10Khz��10000Hz�ļ���Ƶ�ʣ�������5000Ϊ500ms  	  ������ʱ��Ƶ�ʣ�CK_CNT�� = ��fCK_PSC(72M) / PSC[15��0](���Ϊ2��16�η�) + 1������ʱ = 72M/��7199 + 1��= 10k
		RCC->APB1ENR|=1<<2; //TIM4ʱ��ʹ��    
	 	TIM4->ARR=1;  	//�趨�������Զ���װֵ//�պ�1ms   ,����ʱ6.5536 s 
		TIM4->PSC=3599;  	//Ԥ��Ƶ��7200,�õ�10Khz�ļ���ʱ��
							//����������Ҫͬʱ���òſ���ʹ���ж�
		TIM4->DIER|=1<<0;   //��������ж�				
	 	TIM4->DIER|=1<<6;   //�������ж�	   
		//TIM4->CR1|=0x01;    //ʹ�ܶ�ʱ��3
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
		NVIC_InitStructure.NVIC_IRQChannel =TIM4_IRQn;
	    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =0;
	    NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;  
	    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	    NVIC_Init(&NVIC_InitStructure);
		GPIOB->ODR|=0Xffff;
		while(1)
		{	
			GPIO_Write(GPIOB,0xff<<8);
			TIM4->CR1|=0x01;    //ʹ�ܶ�ʱ��3
			if(count > 0)
			GPIO_Write(GPIOB,0xfe<<8);
			if(count >25)
			GPIO_Write(GPIOB,0xfc<<8);
			if(count >50)
			GPIO_Write(GPIOB,0xf8<<8);
			if(count > 75)
			GPIO_Write(GPIOB,0xf0<<8);
			if(count > 100)
			GPIO_Write(GPIOB,0xe0<<8);
			if(count >125)
			GPIO_Write(GPIOB,0xc0<<8);
			if(count > 150)
			GPIO_Write(GPIOB,0x80<<8);
			if(count > 175)
			GPIO_Write(GPIOB,0x00<<8);
				
		}
}

void TIM4_IRQHandler(void)
{
		if(TIM4->SR&0X0001)		 //����ж�   	   ʱ�䵽�ˣ�
		{
			count++;
			if(count >200)
			{
				count = 0;
			}	
	  	 }
		TIM4->SR&=~(1<<0);		//����жϱ�־λ 
}

