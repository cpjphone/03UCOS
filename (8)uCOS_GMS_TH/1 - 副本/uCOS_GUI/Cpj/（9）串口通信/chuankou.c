#include "stm32f10x.h"
#define uint unsigned int
// 			����һ���ַ�
u8 Uart1_PutChar(u8 ch)
{
    USART_SendData(USART1, (u8) ch);
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
   {
   }
   return ch;
}
void delay(uint n)
{
		for(;n>0;n--);
}
void GPIO_Configuration()
{
		  GPIO_InitTypeDef GPIO_InitStructure;

  //����AFIOʱ��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

   //����USARTx_TxΪ�����������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  //���� USARTx_Rx Ϊ��������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}
//    ����һ���ַ���
void Uart1_PutString(u8* buf , u8 len)
{   u8 i;
    for(i=0;i<len;i++)
    {
        Uart1_PutChar(*buf++);
    }
}
int main()
{
		USART_InitTypeDef USART_InitStructure;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
		GPIO_Configuration();
	  //�������ã� ������ 115200 ����λ 8 ֹͣλ 1  ��żλ NONE
		  USART_InitStructure.USART_BaudRate = 115200;
			USART_InitStructure.USART_WordLength = USART_WordLength_8b;
			USART_InitStructure.USART_StopBits = USART_StopBits_1;
			USART_InitStructure.USART_Parity =  USART_Parity_No ;
			USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
			USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
				//��ʼ������
			USART_Init(USART1, &USART_InitStructure);
			//��������
			USART_Cmd(USART1, ENABLE);
			  while (1)
			{  
				Uart1_PutString("���Ʒ� ��ARM/51�ۺϰ��������32λ��������" ,50 );
				delay(0x00ffff);
			}
}

