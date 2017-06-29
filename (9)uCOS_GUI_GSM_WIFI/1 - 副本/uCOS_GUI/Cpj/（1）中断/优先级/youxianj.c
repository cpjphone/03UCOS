/*************************************/
//  GPIOB_PIN_8��ʾ
//	GPIOB_PIN_7��������
/**************************************/

#include "stm32f10x.h"
#define uint unsigned int
#define key1 EXTI_GetITStatus(EXTI_Line1)
#define key2 EXTI_GetITStatus(EXTI_Line5)

ErrorStatus HSEStartUpStatus;

void delay(uint n)
{
		for (;n>0;n--);
}
void GPIO_Configuration()
{
			GPIO_InitTypeDef GPIO_InitStructure;
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB
                         | RCC_APB2Periph_AFIO, ENABLE);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       //��������
			GPIO_Init(GPIOB, &GPIO_InitStructure);

			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_5;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	  //���ø�������
			GPIO_Init(GPIOB, &GPIO_InitStructure);
	
// 			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
// 			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	  //���ø�������
// 			GPIO_Init(GPIOB, &GPIO_InitStructure);
			
}
/*******************************************************************************
*                           ����RCC
*******************************************************************************/
void RCC_Configuration(void)
{   
 //��λRCC�ⲿ�豸�Ĵ�����Ĭ��ֵ
  RCC_DeInit();

  //���ⲿ���پ���
  RCC_HSEConfig(RCC_HSE_ON);

   //�ȴ��ⲿ����ʱ��׼����
  HSEStartUpStatus = RCC_WaitForHSEStartUp();

  if(HSEStartUpStatus == SUCCESS)   //�ⲿ����ʱ���Ѿ�׼���
  {								    
    //����FLASH��Ԥȡ����
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

    //FLASH�ӳ�2������
    FLASH_SetLatency(FLASH_Latency_2);
 	
  //����AHB(HCLK)ʱ��=SYSCLK
    RCC_HCLKConfig(RCC_SYSCLK_Div1);  
  
   //����APB2(PCLK2)��=AHBʱ��
    RCC_PCLK2Config(RCC_HCLK_Div1); 

    //����APB1(PCLK1)��=AHB 1/2ʱ��
    RCC_PCLK1Config(RCC_HCLK_Div2);

     //����PLLʱ�� == �ⲿ���پ���ʱ��*9  PLLCLK = 8MHz * 9 = 72 MHz 
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

    //ʹ��PLLʱ��
    RCC_PLLCmd(ENABLE);

   //�ȴ�PLLʱ�Ӿ���
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
    }

  //����ϵͳʱ�� = PLLʱ��
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

   //���PLLʱ���Ƿ���Ϊϵͳʱ��
    while(RCC_GetSYSCLKSource() != 0x08)
    {
    }
  }
}

void NVIC_Configuration()	  //Ƕ�������жϿ�����
{
			EXTI_InitTypeDef EXTI_InitStructure;
			NVIC_InitTypeDef NVIC_InitStructure;
	
				EXTI_InitStructure.EXTI_Line = EXTI_Line1|EXTI_Line5;
				EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
				EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½��ش���
				EXTI_InitStructure.EXTI_LineCmd = ENABLE; //�ж���ʹ��
				EXTI_Init(&EXTI_InitStructure); //��ʼ���ж�
				EXTI_GenerateSWInterrupt(EXTI_Line1);
				EXTI_GenerateSWInterrupt(EXTI_Line5);
	
// 				EXTI_InitStructure.EXTI_Line = EXTI_Line5;
// 				EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
// 				EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½��ش���
// 				EXTI_InitStructure.EXTI_LineCmd = ENABLE; //�ж���ʹ��
// 				EXTI_Init(&EXTI_InitStructure); //��ʼ���ж�
// 				EXTI_GenerateSWInterrupt(EXTI_Line5);
	
			NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
			NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn; //�ж�ͨ��
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =  0;  //ǿռ���ȼ�
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;//�����ȼ�
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  //ͨ���ж�ʹ��
			NVIC_Init(&NVIC_InitStructure);//��ʼ���ж�
			
			NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
			NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn; //�ж�ͨ��
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =  1;  //ǿռ���ȼ�
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;//�����ȼ�
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  //ͨ���ж�ʹ��
			NVIC_Init(&NVIC_InitStructure);//��ʼ���ж�
	
}
void EXTI1_IRQHandler(void)
{
			if (key1==1)
		{
				GPIO_Write(GPIOB,0xfE<<8);
				delay(0x7fffff);
				EXTI_ClearITPendingBit(EXTI_Line1);
				
		}			
}
void EXTI9_5_IRQHandler(void)
{
			if (key2==1)
		{
				GPIO_Write(GPIOB,0xFF<<8);
				delay(0x7fffff);
				EXTI_ClearITPendingBit(EXTI_Line5);
				
		}			
}
int main()
{			
				RCC_Configuration();
				NVIC_Configuration();	//NVIC����
				GPIO_Configuration(); 
				GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource1);
				GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource5);

				while (1)
				{
						GPIO_Write(GPIOB,0xf0<<8);
				}
}


