#include "stm32f10x.h"

#define TX_OK   	0x20  //TX��������ж�

#define MAX_TX  	0x10  //�ﵽ����ʹ����ж�

#define KEY1 GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_13)
#define KEY2 GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_15)

ErrorStatus HSEStartUpStatus;

u8 NRF24L01_TxPacket(u8 *txbuf);
/*******************************************************************************
* 
*            RCC����
* 
*******************************************************************************/
void RCC_Configuration(void)
{
  //��λRCC�ⲿ�豸�Ĵ�����Ĭ��ֵ
  RCC_DeInit();  

  //���ⲿ���پ���
  RCC_HSEConfig(RCC_HSE_ON); 

 //�ȴ��ⲿ����ʱ��׼����
  HSEStartUpStatus = RCC_WaitForHSEStartUp(); 

  //�ⲿ����ʱ���Ѿ�׼���
  if(HSEStartUpStatus == SUCCESS)  
  {
    
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

   
    FLASH_SetLatency(FLASH_Latency_2);
  
   //����AHB(HCLK)ʱ��=SYSCLK
    RCC_HCLKConfig(RCC_SYSCLK_Div1);
  
    //����APB2(PCLK2)��=AHBʱ��
    RCC_PCLK2Config(RCC_HCLK_Div1); 

    //����APB1(PCLK1)��=AHB 1/2ʱ��
    RCC_PCLK1Config(RCC_HCLK_Div2);  

    //����ADCʱ��=PCLK2 1/4
    RCC_ADCCLKConfig(RCC_PCLK2_Div4); 
  
    //����PLLʱ�� == �ⲿ���پ���ʱ��*9
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9); 
    
	//����ADCʱ��= PCLK2/4
    RCC_ADCCLKConfig(RCC_PCLK2_Div4);

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

  /* TIM1, GPIOA and GPIOB clock enable */
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC |
                         RCC_APB2Periph_GPIOE, ENABLE);
}


void GPIO_Configuraction ()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIOC ->ODR ^= GPIO_Pin_6;

}

int main ()
{
	u8 mode;
	u8 tmp_buf[3];
	tmp_buf[2] = 3;
	tmp_buf[1] = 2;
	tmp_buf[0] = 1;

	RCC_Configuration ();
	GPIO_Configuraction ();
	NRF24L01_Init();    //��ʼ��NRF24L01
	while(NRF24L01_Check())//��ⲻ��24L01
	{


		//GPIO_SetBits (GPIOA,GPIO_Pin_8);
		//GPIO_ResetBits (GPIOA,GPIO_Pin_8);
	}
	RX_Mode();
	//tmp_buf[15] = 0x20;	
	//GPIO_SetBits(GPIOC,GPIO_Pin_7);
	GPIO_ResetBits(GPIOC,GPIO_Pin_6);	 //	
	//GPIO_SetBits(GPIOC,GPIO_Pin_6);
	while (1)
	{	
		if(NRF24L01_RxPacket(tmp_buf)==0)	
		{
				if(tmp_buf[0] == 12){
			
			GPIO_SetBits(GPIOC,GPIO_Pin_6);
			GPIO_SetBits(GPIOC,GPIO_Pin_7);
				}
		}
	}
}

