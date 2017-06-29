/***************************���пƼ� www.prechin.com****************************
	                           LED����˸ʵ��
 ʵ��Ŀ�ģ� ��Ϥ�˽�STM32GPIO�Ĳ����Ϳ⺯����ʹ��
 ���ӷ����� JP10��J12  JP11��JP1  J14����ֱ�ӽ�GND Ҳ���Զ̽���P1.1����
            BOTT1��Ҫ�Ͽ�
 ʵ������	ÿ��һ��ʱ����˸

*******************************************************************************/

#include "sys.h"

#define led PBout(0) 

uint64_t i,j;

/******************************** �������� ---------------------------------------------------------*/
GPIO_InitTypeDef GPIO_InitStructure;
ErrorStatus HSEStartUpStatus;

/*********************************�������� -----------------------------------------------*/
void RCC_Configuration(void);
void NVIC_Configuration(void);
void Delay(vu32 nCount);


/*******************************************************************************
                                  ������
*******************************************************************************/
int main(void)
{


  RCC_Configuration(); //ϵͳʱ�����ú���    

  NVIC_Configuration();	 //NVIC���ú���

  //ʹ��APB2��������ʱ��			 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);  //�رյ��� �˿�����ӳ��  ʹ�÷���������ʱ�������ô���	    

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;  // ѡ�����н�			  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //���ó�����ʽ���
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; //���ģʽ�� I/O����ٶ� 50M HZ
  GPIO_Init(GPIOA, &GPIO_InitStructure);  //��ʼ��PA��
  GPIO_Init(GPIOB, &GPIO_InitStructure);  //��ʼ��PB��															 
  delay_init(72);
  GPIO_Write(GPIOB, 0xffff);																												
  while (1)
  { 
  		for(i=0; i<10000; i++)
		{
			for(j=0; j<1; j++)
			{
				led = 0;
				delay_ms(10*i);
				led = 1;
				delay_ms(10000-10*i);
			}
		}

		for(i=0;i<10000;i++)
		{
			for(j=0;j<1;j++)
			{
				led = 0;
				delay_ms(10000-i);
				led = 1;
				delay_ms(10*i);
			}
		}
}
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
    RCC_PCLK2Config(RCC_HCLK_Div8); 

    //����APB1(PCLK1)��=AHB 1/2ʱ��
    RCC_PCLK1Config(RCC_HCLK_Div8);

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

/*******************************************************************************
*                             NVIC���ú���
*******************************************************************************/
void NVIC_Configuration(void)
{
#ifdef  VECT_TAB_RAM  
  /* Set the Vector Table base location at 0x20000000 */ 
  NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0); 
#else  /* VECT_TAB_FLASH  */
  /* Set the Vector Table base location at 0x08000000 */ 
  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);   
#endif
}

