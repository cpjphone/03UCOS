#include "stm32f10x.h"



void RCC_Configuration(void)
{
	 ErrorStatus HSEStartUpStatus;                    //�����ⲿ���پ�������״̬ö�ٱ���
	 RCC_DeInit();                                    //��λRCC�ⲿ�豸�Ĵ�����Ĭ��ֵ
	 RCC_HSEConfig(RCC_HSE_ON);                       //���ⲿ���پ���
	 HSEStartUpStatus = RCC_WaitForHSEStartUp();      //�ȴ��ⲿ����ʱ��׼����
	 if(HSEStartUpStatus == SUCCESS)                  //�ⲿ����ʱ���Ѿ�׼���
	  {
		   FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable); 	//����FLASHԤ�����幦�ܣ�����FLASH�Ķ�ȡ�����г����б�����÷�.λ�ã�RCC��ʼ���Ӻ������棬ʱ������֮��
		   FLASH_SetLatency(FLASH_Latency_2);                   	 //flash��������ʱ
			    		
						// RCC_HCLK  ���� 
				   	    // RCC_SYSCLK_Div1   AHBʱ�� =  ϵͳʱ�� 
					    // RCC_SYSCLK_Div2   AHBʱ�� =  ϵͳʱ�� / 2 
						// RCC_SYSCLK_Div4   AHBʱ��  = ϵͳʱ�� / 4 
						// RCC_SYSCLK_Div8   AHBʱ��  =  ϵͳʱ�� / 8 
						// RCC_SYSCLK_Div16  AHBʱ��  =  ϵͳʱ�� / 16 
						// RCC_SYSCLK_Div64  AHBʱ��  =  ϵͳʱ�� / 64 
						// RCC_SYSCLK_Div128   AHBʱ��  =  ϵͳʱ��  / 128 
						// RCC_SYSCLK_Div256   AHBʱ��  =  ϵͳʱ��  / 256 
						// RCC_SYSCLK_Div512  AHBʱ��  =  ϵͳʱ��  / 512 
								
		   RCC_HCLKConfig(RCC_SYSCLK_Div1);               //����AHB(HCLK)ʱ�ӵ���==SYSCLK
		   RCC_PCLK2Config(RCC_HCLK_Div1);                //����APB2(PCLK2)��==AHBʱ��
		   RCC_PCLK1Config(RCC_HCLK_Div2);                //����APB1(PCLK1)��==AHB1/2ʱ��
		         
		   RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);  //����PLLʱ�� == �ⲿ���پ���ʱ�� * 9 = 72MHz
		   RCC_PLLCmd(ENABLE);                                   //ʹ��PLLʱ��
		   
		   while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)    //�ȴ�PLLʱ�Ӿ���
		   {
		   }
		   RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);            //����ϵͳʱ�� = PLLʱ��
		   while(RCC_GetSYSCLKSource() != 0x08)                  //���PLLʱ���Ƿ���Ϊϵͳʱ��
		   {
		   }
	  }

}
