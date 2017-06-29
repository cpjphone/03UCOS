/*********************************************************************************      
* ����    �ԡ���C����
* �����뻷������Keil4  
* �������ܡ���ͨ���ж����󰴼�����LED������
* ������֧�֡���				
* ����    ��: RCC 8*9=72MHz		
* ��о    Ƭ��: stm32f103c8 
* ����    �ڡ�: 2013/6/03
* ���޸����ڡ�: 2013/10/06
* ����    �ߡ�: Phone
* ��������: ���������ã�������á�
*********************************************************************************/

#include "stm32f10x.h"							//����ͷ�ļ�
#include <stdio.h>

/************************************************************************/
//�������RCCʱ�����ú���
/************************************************************************/
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

/*******************************************************************************
* Function Name   : NVIC_Configuration
* Description        : Configures NVIC and Vector Table base location.
* Input                    : None
* Output                 : None
* Return                 : None
*******************************************************************************/
void NVIC_Configuration(void)
{
   NVIC_InitTypeDef NVIC_InitStructure;				   
   				//NVIC_InitStruct��ָ��ṹNVIC_InitTypeDef(һ���ṹ��)��ָ�룬����������GPIO��������Ϣ
  
   /* Set the Vector Table base location at 0x08000000 */
   NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);		    //�����������λ�ú�ƫ��
  
   /* Configure the NVIC Preemption Priority Bits */  
   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);		   
  
   /* Enable the USART1 Interrupt */
   NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;       //ͨ������Ϊ����1�ж�
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	   //�ж���Ӧ���ȼ�0
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		   //���ж�
   NVIC_Init(&NVIC_InitStructure); 						   //��ʼ��
}

/*******************************************************************************
	��������USART1_Configuration
	��  ��:
	��  ��:
	����˵����
	��ʼ������Ӳ���豸�������ж�
	���ò��裺
	(1)��GPIO��USART1��ʱ��
	(2)����USART1�����ܽ�GPIOģʽ
	(3)����USART1���ݸ�ʽ�������ʵȲ���
	(4)ʹ��USART1�����жϹ���
	(5)���ʹ��USART1����
*/
void USART1_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	/* ��1������GPIO��USART������ʱ�� */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);			//  USART1ʱ��ʹ��

	/* ��2������USART Tx��GPIO����Ϊ���츴��ģʽ */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;			 //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* ��3������USART Rx��GPIO����Ϊ��������ģʽ
		����CPU��λ��GPIOȱʡ���Ǹ�������ģʽ���������������費�Ǳ����
		���ǣ��һ��ǽ�����ϱ����Ķ������ҷ�ֹ�����ط��޸���������ߵ����ò���
	*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	/*  ��3���Ѿ����ˣ�����ⲽ���Բ���
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	*/
	GPIO_Init(GPIOA, &GPIO_InitStructure);


	/* ��4��������USART1����
	    - BaudRate(������) = 115200 baud (����)
	    - Word Length = 8 Bits
	    - One Stop Bit
	    - No parity	   (��żУ��)
	    - Hardware flow control disabled (RTS and CTS signals)
	    - Receive and transmit enabled
	*/
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	//Ӳ��������ģʽʹ�ܻ���ʧ��
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);

    /* ���������ݼĴ�������������ж� */
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
		//ʹ�ܻ���ʧ��ָ����USART�ж�; USARTx��x������1��2����3����ѡ��USART����
	/* ��5����ʹ�� USART1�� ������� */
	USART_Cmd(USART1, ENABLE);

    /* �����������1���ֽ��޷���ȷ���ͳ�ȥ������ */
    USART_ClearFlag(USART1, USART_FLAG_TC);     // ���־
	//���USARTx�Ĵ������־λ
}

/*******************************************************************/
/*                                                                 */
/* STM32�򴮿�1����1�ֽ�                                           */
/*                                                                 */
/*                                                                 */
/*******************************************************************/
void Uart1_PutChar(u8 ch)
{
  USART_SendData(USART1, (u8) ch);
  while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

/*******************************************************************/
/*                                                                 */
/* STM32�ڴ���1����1�ֽ�                                           */
/* ˵��������1�����ж�                                             */
/*                                                                 */
/*******************************************************************/
void USART1_IRQHandler(void)            //���жϷ�������У�����������Ӧ�ж�ʱ����֪�����ĸ��ж�Դ�����ж�������˱������жϷ�������ж��ж�Դ�����б�Ȼ��ֱ���д�����Ȼ�����ֻ�漰��һ���ж������ǲ����������б�ġ���������ʲô������������б��Ǹ���ϰ��
{
  u8 dat;
   
  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)    //���������ݼĴ�����
  {     
    dat = USART_ReceiveData(USART1);  
         
     if(dat == 0x63)                    
	 {  			
	  dat = 0;      
                   
      Uart1_PutChar(0x77); 		  //����
	  Uart1_PutChar(0x97);                             			  
	 }                                          			   
  }
} 

/*************************************************
����: int main(void)
����: main������
����: ��
����: ��
**************************************************/
int main(void)
{
  RCC_Configuration();
  NVIC_Configuration();
  USART1_Configuration();

  while(1);
}
