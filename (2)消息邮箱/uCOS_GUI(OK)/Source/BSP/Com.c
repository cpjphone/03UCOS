#include "includes.h"


void USART_Config(USART_TypeDef* USARTx,u32 baud){
  USART_InitTypeDef USART_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;

  //PA9,PA10 ����IO�ڹ����������ô��ڡ����Ҫʹ��AFIO�����ù���IO��ʱ�ӡ�
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 		//���ܸ���IOʱ��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);		    //USART1ʱ��
  
  //usart_init----------------------------------------------------
  /* Configure USART1 Rx (PA.10) as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		  //��������ģʽ	   
  GPIO_Init(GPIOA, &GPIO_InitStructure);					 
  
  /* Configure USART1 Tx (PA.09) as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;			  //�����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  
  USART_InitStructure.USART_BaudRate =baud;						//����115200bps
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;		//����λ8λ
  USART_InitStructure.USART_StopBits = USART_StopBits_1;			//ֹͣλ1λ
  USART_InitStructure.USART_Parity = USART_Parity_No;				//��У��λ
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;   //��Ӳ������
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;					//�շ�ģʽ

  /* Configure USART1 */
  USART_Init(USARTx, &USART_InitStructure);							//���ô��ڲ�������
 
  
  /* Enable USART1 Receive and Transmit interrupts */
  USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);                    //ʹ�ܽ����ж�
  /*
  	Table 722. USART_ITֵ
	USART_IT  ����
	USART_IT_PE  ��ż�����ж�
	USART_IT_TXE  �����ж�
	USART_IT_TC  ��������ж�
	USART_IT_RXNE  �����ж�
	USART_IT_IDLE  ���������ж�
	USART_IT_LBD  LIN�жϼ���ж�
	USART_IT_CTS  CTS�ж�
	USART_IT_ERR  �����ж�
	����
		Enables the USART1 transmit interrupt  
		USART_ITConfig(USART1, USART_IT_Transmit ENABLE); 
  
  */
  //USART_ITConfig(USARTx, USART_IT_TXE, ENABLE);				    //ʹ�ܷ��ͻ�����ж�

  
  /* Enable the USART1 */
  USART_Cmd(USARTx, ENABLE);					 //ʹ�ܻ�ʧ��USART����

  //USART_ClearFlag(USARTx, USART_FLAG_TXE);     /* �巢����ɱ�־��Transmission Complete flag */
}
