
#include "sys.h"

//#define TRUE  1
//#define FALSE 0
//
//enum BOOL{FALSE,TRUE} ; 
//typedef enum{error = 0,
//success =!error}Errorstatus;
//typedef enum { ���Ľ����ο�����Ӣ�İ��ͻ�ģ���Ӣ�İ�Ϊ׼
//				FALSE = 0, 
//				TRUE = !FALSE 
//			  } bool;

unsigned int temp = 0xfff0;
uchar temp2 = 0,temp3 = 0;

NVIC_InitTypeDef NVIC_InitStructure;
TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;	   /*����Ϊ��Ӧ�Ľṹ��*/

void timer_init(u16 arr,u16 psc)
{
//		RCC->APB1ENR|=1<<1; //TIM3ʱ��ʹ��    
//	 	TIM3->ARR=arr;  	//�趨�������Զ���װֵ//�պ�1ms    
//		TIM3->PSC=psc;  	//Ԥ��Ƶ��7200,�õ�10Khz�ļ���ʱ��
//							//����������Ҫͬʱ���òſ���ʹ���ж�
//		TIM3->DIER|=1<<0;   //��������ж�				
//	 	TIM3->DIER|=1<<6;   //�������ж�	   
//		TIM3->CR1|=0x01;    //ʹ�ܶ�ʱ��3
//		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
//		NVIC_InitStructure.NVIC_IRQChannel =TIM3_IRQn;
//	    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =0;
//	    NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;  
//	    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	    NVIC_Init(&NVIC_InitStructure);

		RCC->APB1ENR|=1<<2; //TIM4ʱ��ʹ��    					        û����һ���жϲ�������
	 	TIM4->ARR=arr;  	//�趨�������Զ���װֵ//�պ�1ms   ,����ʱ6.5536 s 
		TIM4->PSC=psc;  	//Ԥ��Ƶ��7200,�õ�10Khz�ļ���ʱ��
							//����������Ҫͬʱ���òſ���ʹ���ж�
		TIM4->DIER|=1<<0;   //��������ж�							   	û����һ���жϲ�������
	 	TIM4->DIER|=1<<6;   //�������ж�	   
		TIM4->CR1|=0x01;    //ʹ�ܶ�ʱ��3								û����һ���жϲ�������
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
		NVIC_InitStructure.NVIC_IRQChannel =TIM4_IRQn;
	    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =0;	  //��ռ���ȼ�
	    NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;  			  //��Ӧ���ȼ�
	    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	    NVIC_Init(&NVIC_InitStructure);
}

void timer_init3(u16 arr,u16 psc)
{
		RCC->APB1ENR|=1<<1; //TIM3ʱ��ʹ��    					   ��
	 	TIM3->ARR=arr;  	//�趨�������Զ���װֵ//�պ�1ms    
		TIM3->PSC=psc;  	//Ԥ��Ƶ��7200,�õ�10Khz�ļ���ʱ��
							//����������Ҫͬʱ���òſ���ʹ���ж�
	//	TIM3->DIER|=1<<0;   //��������ж�					       ��
							//����ر��жϵ�ʱ���ã� TIM3->DIER|=0<<0;		��
	 	TIM3->DIER|=1<<6;   //�������ж�	   					   ��
		TIM3->CR1|=0x01;    //ʹ�ܶ�ʱ��3						   ��
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
		NVIC_InitStructure.NVIC_IRQChannel =TIM3_IRQn;		//     ��
	    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =0;
	    NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;  
	    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	    NVIC_Init(&NVIC_InitStructure);
}

int main()
{	
	void LED_Init();			//����	
	LED_Init();		  		    //���ã���ʼ����LED���ӵ�Ӳ���ӿ�
	delay_init(72);	     	    //���ã���ʱ��ʼ��
	timer_init(5,71);	    //1000Khz��1000000Hz�ļ���Ƶ�ʣ�������5Ϊ5us  	  ������ʱ��Ƶ�ʣ�CK_CNT�� = ��fCK_PSC(72M) / PSC[15��0](���Ϊ2��16�η�) + 1������ʱ = 72M/��7199 + 1��= 10k
	timer_init3(20000,7199);	
	GPIOB->ODR|=0Xffff;
	temp3 = 1;
	TIM3->DIER|=1<<0;
	while(1)
	{
		//while(!temp)
		//RCC->APB1ENR|=1<<1;
		TIM3->DIER|=0<<0;
		PBout(7) = temp3;
		//	GPIO_ResetBits(GPIOB,GPIO_Pin_8); 
		//GPIOB->ODR=0Xffff;
		//GPIO_Write(GPIOA,0X00ff);
		
	//	GPIO_WriteBit(GPIOB, GPIO_Pin_0, temp2);
	//	GPIO_WriteBit(GPIOB, GPIO_Pin_1, temp3);
//		PAout(0) = temp2;
//		PAout(1) = temp3;		
		//PBout(8) = 1;	
	}
}

void TIM4_IRQHandler(void)
{
		if(TIM4->SR&0X0001)		 //����ж�   	   ʱ�䵽�ˣ�
		{
				//PBout(8) = 0;
				//	GPIO_SetBits(GPIOB,GPIO_Pin_8); 
			//	GPIO_Write(GPIOB,temp);
			temp++;
			temp = 0;
			//temp2 = ~temp2;
				//PBout(8) = 0;				
				//PBout(9) = 1;
				 // GPIOB->ODR=0x00ff;
				//PBout(9) = 1;
				//GPIOB->ODR=0Xf0<<8;
				// delay_ms(1050);
				//wait(2.100);	 //SysTick д�Ŀ������ӳ�ʱ�亯��
		}
		TIM4->SR&=~(1<<0);		//����жϱ�־λ 
}
void TIM3_IRQHandler(void)
{
		if(TIM3->SR&0X0001)		 //����ж�   	   ʱ�䵽�ˣ�
		{
				//PBout(8) = 0;
				//	GPIO_SetBits(GPIOB,GPIO_Pin_8); 
			//	GPIO_Write(GPIOB,temp);
			
			temp3 = ~temp3;
			
				//PBout(8) = 0;				
				//PBout(9) = 1;
				 // GPIOB->ODR=0x00ff;
				//PBout(9) = 1;
				//GPIOB->ODR=0Xf0<<8;
				// delay_ms(1050);
				//wait(2.100);	 //SysTick д�Ŀ������ӳ�ʱ�亯��
		}
		TIM3->DIER|=0<<0;
		TIM3->SR&=~(1<<0);		//����жϱ�־λ 
}

