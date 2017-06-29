#include "stm32f10x.h"
#define uint unsigned int
#define key2 EXTI_GetITStatus(EXTI_Line7)
void delay(uint n)
{
		for (;n>0;n--);
}
void GPIO_Configuration()
{
				  GPIO_InitTypeDef GPIO_InitStructure;
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB
                         | RCC_APB2Periph_AFIO, ENABLE);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       //��������
			GPIO_Init(GPIOB, &GPIO_InitStructure);

			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	  //���ø�������
			GPIO_Init(GPIOB, &GPIO_InitStructure);
// 				RCC->APB2ENR|=1<<3;
// 				GPIOB->CRH&=0XFFFFFFF0;
// 				GPIOB->CRH|=0X00000003;
// 	
// 				GPIOB->CRL&=0X0FFFFFFF;
// 				GPIOB->CRL|=0X70000000;
// 	
// 				GPIOB->ODR|=1<<8;
// 				GPIOB->IDR|=1<<7;
			
}
void NVIC_Configuration()
{
			NVIC_InitTypeDef NVIC_InitStructure;
			NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
			NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn; //�ж�ͨ��
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =  0;  //ǿռ���ȼ�
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;//�����ȼ�
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  //ͨ���ж�ʹ��
			NVIC_Init(&NVIC_InitStructure);//��ʼ���ж�
}
void EXTI9_5_IRQHandler(void)
{
			if (key2==1)
		{

				GPIO_Write(GPIOB,0x00<<8);
				delay(0x7fffff);
				GPIO_Write(GPIOB,0xff<<8);
				delay(0x7fffff);
				EXTI_ClearITPendingBit(EXTI_Line7);
				
		}			
}
int main()
{
				EXTI_InitTypeDef EXTI_InitStructure;
				NVIC_Configuration();	//NVIC����
				GPIO_Configuration(); 
				GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource7); 
				EXTI_InitStructure.EXTI_Line = EXTI_Line7;
				EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
				EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½��ش���
				EXTI_InitStructure.EXTI_LineCmd = ENABLE; //�ж���ʹ��
				EXTI_Init(&EXTI_InitStructure); //��ʼ���ж�
				EXTI_GenerateSWInterrupt(EXTI_Line7);
				while (1)
				{}
}

