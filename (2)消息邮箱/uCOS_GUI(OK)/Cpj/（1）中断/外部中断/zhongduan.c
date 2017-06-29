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
	
#include "sys.h"							//����ͷ�ļ�

#define uint unsigned int					//�궨�� ��������
#define uchar unsigned char

/************************************************************************/
//��ʱ����
/************************************************************************/

//void delay(uint n)
//{
//		for (;n>0;n--);
//}

/************************************************************************/
//GPIO_Configuration	Configuration:���ã��ṹ������
//(�������������Ը���������)
/************************************************************************/
void GPIO_Configuration(void)
{
     GPIO_InitTypeDef GPIO_InitStructure;
	 
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB 
	 						| RCC_APB2Periph_GPIOA 
							| RCC_APB2Periph_AFIO , ENABLE);		//  ����ʱ��

	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_5;	 
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING ;	 	 	//  ����            ����
	 GPIO_Init(GPIOA, &GPIO_InitStructure);	                 		//  PD10 


	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
 	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_Init(GPIOB, &GPIO_InitStructure);
	 
}

/************************************************************************/
//�ж����ú���
//(�������������Ը���������)
/************************************************************************/
void EXTI_Configuration(void)
{
	 EXTI_InitTypeDef EXTI_InitStructure;
				
	
	// EXTI_ClearITPendingBit(EXTI_Line0);                  		// �����У����EXTI��·����λ���������жϹ���λ����Ժ��أ�һ�������жϾͲ��ܲ���
	
	 EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;    		// ����EXTI��·Ϊ�ж�����
	 EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;		    // ����Ϊ��·�½���λ�ж�����
	 EXTI_InitStructure.EXTI_Line = EXTI_Line0 | EXTI_Line5;		//(����) �Ǹ�L����Ϊ�ж�����	(����)
	 EXTI_InitStructure.EXTI_LineCmd = ENABLE;						// �ж��ǲ���ʹ��
	 EXTI_Init(&EXTI_InitStructure);                    		    // ����	 ��ʼ���ж�
	 EXTI_GenerateSWInterrupt(EXTI_Line0);							// (����)����һ������ж�
	 EXTI_GenerateSWInterrupt(EXTI_Line5);							
	 GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0); 	// ��ʲô����ƾ仰����ѡ�񣬺��棨1�������6���˿� ���ڽ���ѡ��
	 GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource5);	//(����)

}

/************************************************************************/
//��������ж�0������
/************************************************************************/
void EXTI0_IRQHandler(void)  			
{ 


		     //����жϴ������
		if (Exti0 == 1)
		{
				GPIO_Write(GPIOB,0xfffc);
			//	GPIO_ResetBits(GPIOB,GPIO_Pin_0);
				wait(2.55);
				
				EXTI_ClearITPendingBit(EXTI_Line0);
				
		}
			 
			  
			//	GPIO_Write(GPIOB,0x00);
			//	delay(0x7fffff);
			//		GPIO_Write(GPIOB,0xff);
			//		delay(0x7fffff);
			//	GPIO_ResetBits(GPIOB,  GPIO_Pin_0 );
			///	EXTI_ClearITPendingBit(EXTI_Line10);
			
}

/************************************************************************/
//��������ж�9_5������
/************************************************************************/
void EXTI9_5_IRQHandler(void)
{	
	if (Exti5 == 1)
	{
		GPIO_Write(GPIOB,0xfffe);
	//	GPIO_ResetBits(GPIOB,GPIO_Pin_0);
		wait(1.55);
	
		EXTI_ClearITPendingBit(EXTI_Line5);	
	
	}
}

/************************************************************************/
//�������������
/************************************************************************/
int main(void)
{
	void NVIC_Configuration(void) ;     //�Ժ�����������
	void RCC_Configuration(void);

	delay_init(72);	     	    //���ã���ʱ��ʼ��	,����Ҫ��		�δ�ʱ��
	GPIO_Configuration();				//����
	NVIC_Configuration();
	EXTI_Configuration();

	
    while (1)
	//	GPIO_Write(GPIOB,0xffff);
		;
	//GPIO_Write(GPIOB,0xff);
}
