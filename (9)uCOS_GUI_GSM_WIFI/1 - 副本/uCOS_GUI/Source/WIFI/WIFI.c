

#include "includes.h"

#define uint unsigned int
#define uchar unsigned char
#define MAXCHAR1 81
char  bb[MAXCHAR1];

uchar n=0;

u8 tempt[13]="#SERVERSDATA#";
u8 temp_1[2]="C#";
u8 temp_2[2]="%#";


// 			����һ���ַ�
u8 Uart1_PutChar(u8 ch)
{
    USART_SendData(USART1, (u8) ch);
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
   {
   }
   return ch;
}

//    ����һ���ַ���
void Uart1_PutString(u8* buf , u8 len)
{   
	u8 i;
    for(i=0;i<len;i++)
    {
        Uart1_PutChar(*buf++);
    }
}

/************************************************************************/
//����Զ�������
/************************************************************************/
void clearBuff2(void)
{
	for(n=0;n<MAXCHAR1;n++)
	{
		bb[n]=0x00;
	}
	n=0;
}

void wifi()
{
		unsigned char k[8];
		clearBuff2();
	
		k[0]=0+0x30;
		k[1]=0+0x30;
		k[2]=0+0x30;
		k[3]=0+0x30;
	
	
// 	GPIO_SetBits(GPIOC,GPIO_Pin_6);	
// 	GPIO_SetBits(GPIOC,GPIO_Pin_7);	
// 	GPIO_ResetBits(GPIOC,GPIO_Pin_6);	
		while (1)
		{
			//Print_Str(ATE0);
			
			Uart1_PutString (tempt,13);
			Uart1_PutString (&k[0],1);
			Uart1_PutString (&k[1],1);
			Uart1_PutString (temp_1,2);
			
			Uart1_PutString (&k[2],1);
			Uart1_PutString (&k[3],1);
			Uart1_PutString (temp_2,2);
			k[0]++;
			k[1]++;
			k[2]++;
			k[3]++;
			//Uart1_PutString ("#SERVERSDATA#12C#35%#",21);
			OSTimeDlyHMSM(0,0,0,80);
			if ((k[0]>9+0x30) || (k[1]>9+0x30) || (k[2]>9+0x30) || (k[3]>9+0x30))
			{
				k[0]=0+0x30;
				k[1]=0+0x30;
				k[2]=0+0x30;
				k[3]=0+0x30;
			}
			if(strstr(bb,"A")!=NULL)
		{
		//	GPIO_SetBits(GPIOC,GPIO_Pin_6);	
			GPIO_ResetBits(GPIOC,GPIO_Pin_7);	
			clearBuff2();
	  }	
			if(strstr(bb,"B")!=NULL)
		{
			GPIO_SetBits(GPIOC,GPIO_Pin_6);	
		//	GPIO_SetBits(GPIOC,GPIO_Pin_7);	
			clearBuff2();
	  }
		}
}

/*******************************************************************/
/*                                                                 */
/* STM32�ڴ���1����1�ֽ�                                           */
/* ˵��������1�����ж�                                             */
/*                                                                 */
/*******************************************************************/
void USART1_IRQHandler(void)            //���жϷ�������У�����������Ӧ�ж�ʱ����֪�����ĸ��ж�Դ�����ж�������˱������жϷ�������ж��ж�Դ�����б�Ȼ��ֱ���д�����Ȼ�����ֻ�漰��һ���ж������ǲ����������б�ġ���������ʲô������������б��Ǹ���ϰ��
{  
  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)    //���������ݼĴ�����
  {     
    bb[n] = USART_ReceiveData(USART1);          
		USART_ClearITPendingBit(USART2,USART_IT_RXNE);
		n++;		
  }
	
	if(USART_GetFlagStatus(USART1,USART_FLAG_ORE)==SET)
	{
		USART_ClearFlag(USART1,USART_FLAG_ORE);
	}
}

