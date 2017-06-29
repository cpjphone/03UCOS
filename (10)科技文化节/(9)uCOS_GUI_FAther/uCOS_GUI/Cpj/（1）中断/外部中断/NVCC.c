#include "stm32f10x.h"

// �ж�Դ���з��飬ȷ�����ȼ���ʲô���ӵģ�ͨ������ĺ�������ʵ��

void NVIC_Configuration(void)
{
		//  NVIC_InitStructure �ṹ�����ĸ�������
		//  NVIC_InitTypeDef NVIC_InitStructure; 
	  	//  /* Configure the Priority Grouping with 1 bit */ 
	    //  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); 
	    //  /* Enable TIM3 global interrupt with Preemption Priority 0 and Sub 
	    //  Priority as 2 */ 
	    //  1 NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQChannel; 
	    //  2 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		//  3 NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2; 
	    //  4 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	    //  NVIC_InitStructure(&NVIC_InitStructure); 
				
	  NVIC_InitTypeDef NVIC_InitStructure; 

	  /******************�ж�Դ��0����ռ���ȼ� 3 ��Ӧ���ȼ� 0 **********************/
	  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);            //���4λ��ռ���ȼ�������Ӧ���ȼ�   	
	  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;           //���ָ���ж�Դ��  �ⲿ�ж���15-10�ж�  ��1�������ⲿ�ж�Դ
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;         //���ָ����Ӧ���ȼ���1   ���ȼ���
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;  //���ǿռ���ȼ�
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	         //ʹ���ⲿ�ж�ͨ��  ʹ�ܷ���
	  NVIC_Init(&NVIC_InitStructure);

	  /******************�ж�Դ��9_5_����ռ���ȼ� 1 ��Ӧ���ȼ� 0 **********************/
	  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);             //�����ռʽ���ȼ�������Ϊ����ռ���ȼ�   	
	  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;          //���ָ���ж�Դ��  �ⲿ�ж���15-10�ж�  ��1�������ⲿ�ж�Դ
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;          //���ָ����Ӧ���ȼ���1   ���ȼ���
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =  1;  //���ǿռ���ȼ�
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	          //ʹ���ⲿ�ж�ͨ��  ʹ�ܷ���
	  NVIC_Init(&NVIC_InitStructure);
	 					 
}	//��4 ��0-15 �����ȼ�
