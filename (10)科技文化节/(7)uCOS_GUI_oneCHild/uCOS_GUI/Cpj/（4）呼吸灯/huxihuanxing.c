#include "stm32f10x.h"
#define uint unsigned int
#define uchar unsigned char

#define key GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)
#define key2 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)
#define key3 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)

#define key1 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)

uint a,i,j,k,count=0;
uchar flag=0,flag_x=0;

//u8 Check_WKUP2(void);

ErrorStatus HSEStartUpStatus;


void ledinit(void);

void delay(uint n)
{
		for (;n>0;n--);
}

void ledinit()
{
		RCC->APB2ENR|=1<<3;
		GPIOB->ODR|=0Xffff;
		GPIOB->CRH&=0X00000000;
		GPIOB->CRH|=0X33333333;

		
}

void huxi_8()
{
			u16 temp=0xfeff;
			GPIOB->ODR=temp;			//GPIOB->ODR=0XFEFF
			for(a=0;a<8;a++)
			{
					for (k=0;k<10;k++)
					{
							for (i=0;i<20*a;i++)
							{
									GPIOB->ODR=temp;
							}
							for (j=0;j<160-20*a;j++)
							{
									GPIOB->ODR=0xffff;
							}
					}
						temp=temp<<=1;
						delay(0xff);
			}
			temp=0xfeff;
}
void huxi_shan()
{
				RCC->APB2ENR|=1<<3;
				GPIOB->CRH&=0X0ffffff0;
				GPIOB->CRH|=0X30000003;
				if (flag_x==0)
				{
				for(k=0;k<1000;k++)
				{
					for (i=0;i<count;i++)
					{
						//GPIOB->ODR&=0<<8;
						//GPIOB->ODR&=0<<15;
						GPIO_Write(GPIOB,0XFE<<8);
					}
					for (j=0;j<50-count;j++)
					{
						//GPIOB->ODR|=1<<8;
						//GPIOB->ODR|=1<<15;
						GPIO_Write(GPIOB,0XFF<<8);
					}
				}
					if (count<50)
					count++;
					else
					{
						count=0;
						flag_x=1;
					}
				}
				if (flag_x==1)
				{
				for(k=0;k<1000;k++)
				{
					for (i=0;i<count;i++)
					{
						//GPIOB->ODR&=0<<8;
						//GPIOB->ODR&=0<<15;
						GPIO_Write(GPIOB,0XFf<<8);
					}
					for (j=0;j<50-count;j++)
					{
						//GPIOB->ODR|=1<<8;
						//GPIOB->ODR|=1<<15;
						GPIO_Write(GPIOB,0XFe<<8);
					}
				}
					if (count<50)
					count++;
					else
					{
						count=0;
						flag_x=0;
					}
				}
}


void keyscan()
{
		if (key1==0)
		{
			delay(10);
			if (key1==0)
			flag=1;
		}
		if(key2==0)
		{
			delay(10);
			if (key2==0)
			flag=2;
		}
		if(key3==0)
		{
			delay(10);
			if (key3==0)
			flag=3;
		}
		if (key==0)
		{
				delay(10);
				if (key==0)
					flag=4;
		}
}

void WKUP_Init(void)
{
					EXTI_InitTypeDef EXTI_InitStructure;
					NVIC_InitTypeDef NVIC_InitStructure;
					GPIO_InitTypeDef GPIO_InitStructure;
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA
                         | RCC_APB2Periph_AFIO, ENABLE);
					RCC->APB2ENR|=1<<2;     //��ʹ������IO PORTAʱ��    
					RCC->APB2ENR|=1<<0;     //��������ʱ��
	
	
					GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource7); 
	
					RCC->APB2ENR|=1<<3;
					GPIOB->CRH&=0XFFFFFFF0;
					GPIOB->CRH|=0X00000003;
	
					GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
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
int main()
{
			RCC_Configuration();
			WKUP_Init();
			ledinit();
			while(1)
			{
						keyscan();
						if (flag==1)
							huxi_8();
						if (flag==2)
							huxi_shan();
						if (flag==3)
							//ledinit();
// 						GPIO_WriteBit(GPIOB,GPIO_Pin_8,Bit_RESET);
// 						delay(0x7fffff);
// 						GPIO_WriteBit(GPIOB,GPIO_Pin_8,Bit_SET);
// 						delay(0x7fffff);
// 						GPIO_WriteBit(GPIOB,GPIO_Pin_8,Bit_RESET);
// 						delay(0x7fffff);
// 						GPIO_WriteBit(GPIOB,GPIO_Pin_8,Bit_SET);
// 						delay(0x7fffff);
						PWR_EnterSTOPMode(PWR_Regulator_LowPower,PWR_STOPEntry_WFI);
						if (key == 0)
						{
						RCC_Configuration();
						GPIO_WriteBit(GPIOB,GPIO_Pin_8,Bit_RESET);
						}
// 						delay(0x7fffff);
// 						GPIO_WriteBit(GPIOB,GPIO_Pin_8,Bit_SET);
// 						delay(0x7fffff);
		 	}
}

void EXTI9_5_IRQHandler(void)
{ 		    		    				     		    
	EXTI_ClearITPendingBit(EXTI_Line7);		  
} 
