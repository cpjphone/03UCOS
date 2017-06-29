

#include "stm32f10x.h"
	  

/**********************************************************************
* ��    �ƣ�Delay()
* ��    �ܣ���ʱ
* ��ڲ�����cnt
* ���ڲ�����
-----------------------------------------------------------------------
* ˵����
***********************************************************************/
void Delay(vu16 cnt) 
{
  u16 i,j;

  for (i=0;i<cnt;i++)
  { 
    for (j=0;j<1000;j++)
    { 
	}
  }
}

/*************************************************
����: void RCC_Configuration(void)
����: ����ϵͳʱ��
����: ��
����: ��
**************************************************/
void RCC_Configuration(void)
{
  ErrorStatus HSEStartUpStatus;                    //�����ⲿ���پ�������״̬ö�ٱ���
  RCC_DeInit();                                    //��λRCC�ⲿ�豸�Ĵ�����Ĭ��ֵ
  RCC_HSEConfig(RCC_HSE_ON);                       //���ⲿ���پ���
  HSEStartUpStatus = RCC_WaitForHSEStartUp();      //�ȴ��ⲿ����ʱ��׼����
  if(HSEStartUpStatus == SUCCESS)                  //�ⲿ����ʱ���Ѿ�׼���
  {
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable); //����FLASHԤ�����幦�ܣ�����FLASH�Ķ�ȡ�����г����б�����÷�.λ�ã�RCC��ʼ���Ӻ������棬ʱ������֮��
    FLASH_SetLatency(FLASH_Latency_2);                    //flash��������ʱ
      	
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




/**********************************************************************
* ��    �ƣ�GPIO_Configuration()
* ��    �ܣ������������
* ��ڲ����� 
* ���ڲ�����
-----------------------------------------------------------------------
* ˵����
***********************************************************************/
void GPIO_Configuration(void)
{

  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);	//��GPIOA��GPIOB�ṩʱ��

  /*����PB0Ϊ���*/
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_All;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);


  
}


void Sys_Standby(void)
{
	SCB->SCR|=1<<2;//ʹ��SLEEPDEEPλ (SYS->CTRL)
	NVIC_SystemLPConfig(NVIC_LP_SLEEPDEEP,ENABLE);	   	//��仰�Ĺ��ܾ��������Ǿ�SCB->SCR �ĵڶ���SLEEPDEEP��λ��1
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);	//ʹ��PWR����ʱ��   ��Դʱ�Ӵ� 

	PWR_WakeUpPinCmd(ENABLE);  //ʹ�ܻ��ѹܽŹ���	   ʹ��ĳ�˿�  ������Ϊ��������

	/* Request to enter STANDBY mode (Wake Up flag is cleared in PWR_EnterSTANDBYMode function) */
	PWR_EnterSTANDBYMode();	  //���������STANDBY��ģʽ  STM32 �������ģʽ		 
}

/*************************************************
����: int main(void)
����: main������
����: ��
����: ��
**************************************************/
int main (void) 
{

  RCC_Configuration();                      
  GPIO_Configuration(); 

  while(1)
  {
    GPIO_WriteBit(GPIOB, GPIO_Pin_0,(BitAction)1);//��1
    Delay(10000);
    GPIO_WriteBit(GPIOB, GPIO_Pin_0,(BitAction)0);//��0
    Delay(10000);
    GPIO_WriteBit(GPIOB, GPIO_Pin_0,(BitAction)1);//��1
    Delay(10000);
    GPIO_WriteBit(GPIOB, GPIO_Pin_0,(BitAction)0);//��0
    Delay(10000);
    GPIO_WriteBit(GPIOB, GPIO_Pin_0,(BitAction)1);//��1
    Delay(10000);
    GPIO_WriteBit(GPIOB, GPIO_Pin_0,(BitAction)0);//��0
    Delay(10000);
   	GPIO_WriteBit(GPIOB, GPIO_Pin_0,(BitAction)1);//��1
    Delay(10000);
    GPIO_WriteBit(GPIOB, GPIO_Pin_0,(BitAction)0);//��0
    Delay(10000);
	Sys_Standby();  // �����С�ƾͲ���˸�� ������PA0 ��WK_UP����һ�������ش���	  ��STM32�ֽ���	 ����ģʽ	
  }
}


