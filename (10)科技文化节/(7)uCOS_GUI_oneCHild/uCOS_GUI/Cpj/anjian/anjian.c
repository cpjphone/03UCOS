#include "sys.h"


//ErrorStatus HSEStartUpStatus;
uint a;
#define KEY GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)

//void RCC_Configuration(void)
//{   
// //��λRCC�ⲿ�豸�Ĵ�����Ĭ��ֵ
//  RCC_DeInit();
//
//  //���ⲿ���پ���
//  RCC_HSEConfig(RCC_HSE_ON);
//
//   //�ȴ��ⲿ����ʱ��׼����
//  HSEStartUpStatus = RCC_WaitForHSEStartUp();
//
//  if(HSEStartUpStatus == SUCCESS)   //�ⲿ����ʱ���Ѿ�׼���
//  {								    
//    //����FLASH��Ԥȡ����
//    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
//
//    //FLASH�ӳ�2������
//    FLASH_SetLatency(FLASH_Latency_2);
// 	
//  //����AHB(HCLK)ʱ��=SYSCLK
//    RCC_HCLKConfig(RCC_SYSCLK_Div1);  
//  
//   //����APB2(PCLK2)��=AHBʱ��
//    RCC_PCLK2Config(RCC_HCLK_Div1); 
//
//    //����APB1(PCLK1)��=AHB 1/2ʱ��
//    RCC_PCLK1Config(RCC_HCLK_Div2);
//
//     //����PLLʱ�� == �ⲿ���پ���ʱ��*9  PLLCLK = 8MHz * 9 = 72 MHz 
//    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
//
//    //ʹ��PLLʱ��
//    RCC_PLLCmd(ENABLE);
//
//   //�ȴ�PLLʱ�Ӿ���
//    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
//    {
//    }
//
//  //����ϵͳʱ�� = PLLʱ��
//    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
//
//   //���PLLʱ���Ƿ���Ϊϵͳʱ��
//    while(RCC_GetSYSCLKSource() != 0x08)
//    {
//    }
//  }
//}

//GPIO_InitTypeDef GPIO_InitStructure;

//#define KEY1 PAin(15)
//#define KEY (1<<13)
//#define KEY1 (1<<15)
//#define KEY2 (1<<8)
//#define KEY_GET() ((GPIOA->IDR&(KEY))1:0)
//#define KEY1_GET() ((GPIOA->IDR&(KEY1))1:0)
//#define KEY2_GET() ((GPIOA->IDR&(KEY2))1:0)

void ledinit()
{
		RCC->APB2ENR|=1<<3;
		RCC->APB2ENR|=1<<2;
		GPIOB->CRH&=0X00000000;
		GPIOB->CRH|=0X33333333;
			  // 0011ͨ������������ٶ�50MHz

//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 ;  // ѡ�����н�
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //���ó�����ʽ����
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //���ģʽ�� I/O����ٶ� 50M HZ
//	GPIO_Init(GPIOA, &GPIO_InitStructure); 
}
int main()
{
	//	ledinit();
	//	GPIOB->ODR=0XFE00;
	//	GPIO_Write(GPIOB,0xff00);
		RCC->APB2ENR|=1<<3;
		RCC->APB2ENR|=1<<2;
		GPIOB->CRH&=0X00000000;
		GPIOB->CRH|=0X33333333;
		while(1)
		{

			if(KEY == 0)
			{
				//wait(0.002);
				//if(KEY == 0)
				GPIO_Write(GPIOB,0xff00);

			}
		}
		
}
