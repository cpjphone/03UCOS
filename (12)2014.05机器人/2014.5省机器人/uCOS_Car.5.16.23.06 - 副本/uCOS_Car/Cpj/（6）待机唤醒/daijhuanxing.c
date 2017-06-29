#include "sys.h"
#define uint unsigned int
#define key GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)
//u8 Check_WKUP2(void);

ErrorStatus HSEStartUpStatus;


void ledinit(void);
void delay(uint n)
{
		for (;n>0;n--);
}

void WKUP_Init(void)
{
				
					EXTI_InitTypeDef EXTI_InitStructure;
					NVIC_InitTypeDef NVIC_InitStructure;
					GPIO_InitTypeDef GPIO_InitStructure;	    //�ṹ������

//					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA
//                         | RCC_APB2Periph_AFIO, ENABLE);	    //�⺯��ʹ��GPIOA,GPIOB �͸��ù���ʱ��

					RCC->APB2ENR|=1<<2;     					//�Ĵ���ʹ��GPIOA��GPIOB �͸��ù���ʱ��   
					RCC->APB2ENR|=1<<0;    						//��������ʱ��
					RCC->APB2ENR|=1<<3;
					GPIOB->CRH&=0XFFFFFFF0;
					GPIOB->CRH|=0X00000003;

					GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource7); 
															   //ѡ��GPIO�ܽ������ⲿ�ж���·
					
	
					GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING ;
															  //��������
					GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	
					EXTI_InitStructure.EXTI_Line = EXTI_Line7;
					EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
					EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; 
					EXTI_InitStructure.EXTI_LineCmd = ENABLE; 
					EXTI_Init(&EXTI_InitStructure); 
					//EXTI_GenerateSWInterrupt(EXTI_Line7);			//����һ������ж�

					NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
					NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn; 
					NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =  0; 
					NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
					NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
					NVIC_Init(&NVIC_InitStructure);
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
/*****************************************
funtion: ��������������2uA����
*****************************************/
void Sys_Standby(void)
{
	//SCB->SCR|=1<<2;//ʹ��SLEEPDEEPλ (SYS->CTRL)
	NVIC_SystemLPConfig(NVIC_LP_SLEEPDEEP,ENABLE);	   	//��仰�Ĺ��ܾ��������Ǿ�SCB->SCR �ĵڶ���SLEEPDEEP��λ��1
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);	//ʹ��PWR����ʱ��   ��Դʱ�Ӵ� 

	PWR_WakeUpPinCmd(ENABLE);  //ʹ�ܻ��ѹܽŹ���	   ʹ��ĳ�˿�  ������Ϊ��������

	/* Request to enter STANDBY mode (Wake Up flag is cleared in PWR_EnterSTANDBYMode function) */
	PWR_EnterSTANDBYMode();	  //���������STANDBY��ģʽ  STM32 �������ģʽ		 
}

int main()
{
			RCC_Configuration();
			WKUP_Init();
			while(1)
			{
						GPIO_WriteBit(GPIOA,GPIO_Pin_7,1);
							//ledinit();
						GPIO_WriteBit(GPIOB,GPIO_Pin_8,Bit_RESET);
						delay(0x7fffff);
					//	delay_ms(800);
						GPIO_WriteBit(GPIOB,GPIO_Pin_8,Bit_SET);
						delay(0x7fffff);
						GPIO_WriteBit(GPIOB,GPIO_Pin_8,Bit_RESET);
						delay(0x7fffff);
						GPIO_WriteBit(GPIOB,GPIO_Pin_8,Bit_SET);
						delay(0x7fffff);
						//PWR_WakeUpPinCmd(DISABLE);	  //ʹ�ܻ���ʧ�ܻ��ѹܽŹ���   ������

						//PWR_EnterSTANDBYMode ();	  //���������STANDBY��ģʽ

						PWR_EnterSTOPMode(PWR_Regulator_LowPower,PWR_STOPEntry_WFI);
						 //PWR_Regulator_ON  //ֹͣģʽ�µ�ѹת���� ON 
						 //PWR_Regulator_LowPower ;// ֹͣģʽ�µ�ѹת��������͹���ģʽ   
						 //PWR_STOPEntry_WFI  ;//(���ó������жϻ���)	PWR_STOPEntry_WFI  ʹ��ָ�� WFI������ֹͣģʽ
						  
						 //	Sys_Standby(); 		// �� ����
						RCC_Configuration();
						GPIO_WriteBit(GPIOB,GPIO_Pin_8,Bit_RESET);
						delay(0x7fffff);
						GPIO_WriteBit(GPIOB,GPIO_Pin_8,Bit_SET);
						delay(0x7fffff);
		 	}
}

void EXTI9_5_IRQHandler(void)
{ 		    		    				     		    
	EXTI_ClearITPendingBit(EXTI_Line7);		  
} 
