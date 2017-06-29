

#include "stm32f10x.h"
//#include "stdio.h"
#include "timer.h"
#include "led.h"

//��ʱ��3�жϷ������	 
void TIM3_IRQHandler(void)
{ 		    		  			    
	if(TIM3->SR&0X0001)//����ж�
	{
		LED1=!LED1;			    				   				     	    	
	}				   
	TIM3->SR&=~(1<<0);//����жϱ�־λ 	    
}
//ͨ�ö�ʱ���жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!
void Timerx_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<1;//TIM3ʱ��ʹ��    
 	TIM3->ARR=arr;  //�趨�������Զ���װֵ//�պ�1ms    
	TIM3->PSC=psc;  //Ԥ��Ƶ��7200,�õ�10Khz�ļ���ʱ��
	//����������Ҫͬʱ���òſ���ʹ���ж�
	TIM3->DIER|=1<<0;   //��������ж�				
//	TIM3->DIER|=1<<6;   //�������ж�	   
	TIM3->CR1|=0x01;    //ʹ�ܶ�ʱ��3
  MY_NVIC_Init(1,3,TIM3_IRQn,2);//��ռ1�������ȼ�3����2									 
}




/****************************************************************
һ����ʱ�������·��Ƶ����ͬ������ռ�ձȲ�ͬ����PWM����
���˺���ֻʵ����TIM3��CH1��CH2��·�������·������ơ�
��һ����ʱ����PWMģʽֻ�����Ƶ����ͬ��ռ�ձȿɵ�����·PWM���塿
��PWM=72M/(��ARR+1��*(PSC+1))��
****************************************************************/

void PWM_CH1_CH2(u16 arr,u16 psc)	
{	  	  
	RCC->APB1ENR|=1<<1;       //TIM3ʱ��ʹ�� 
	
	GPIOA->CRL&=0XF0FFFFFF;//PA6���
	GPIOA->CRL|=0X0B000000;//���ù������ 	  
	GPIOA->ODR|=1<<6;//PA6����
	  	
	GPIOA->CRL&=0X0FFFFFFF;//PA7���
	GPIOA->CRL|=0XB0000000;//���ù������ 	  
	GPIOA->ODR|=1<<7;//PA7����	

   
	
	TIM3->ARR=arr;//�趨�������Զ���װֵ 
	TIM3->PSC=psc;//Ԥ��Ƶ������Ƶ
	
//	TIM3->CCR1=25;
//	TIM3->CCR2=125;
	
	TIM3->CCMR1|=6<<4;  //CH1 PWM2ģʽ	  
	TIM3->CCMR1|=1<<3; //CH1Ԥװ��ʹ��
	
	TIM3->CCMR1|=6<<12;  //CH2 PWM2ģʽ	  
	TIM3->CCMR1|=1<<11; //CH2Ԥװ��ʹ��	   
	

	TIM3->CCER|=1<<0;   //OC1 ���ʹ��
	TIM3->CCER|=1<<4;   //OC2 ���ʹ��
	   
	
	TIM3->CR1|=0x0080;   //ARPEʹ�� 
	TIM3->CR1|=0x0001;   //ʹ�ܶ�ʱ��3 	   
} 
void PWM_CH3CH4(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<0;    //TIM2ʱ��ʹ��

	GPIOA->CRL&=0XFFFFFFF0;//PA0���
	GPIOA->CRL|=0X0000000B;//���ù������ 	  
	GPIOA->ODR|=1<<0;      //PA0����

	GPIOA->CRL&=0XFFFFFF0F;//PA1���
	GPIOA->CRL|=0X000000B0;//���ù������ 	  
	GPIOA->ODR|=1<<1;      //PA1����	

	GPIOA->CRL&=0XFFFFF0FF;//PA2���
	GPIOA->CRL|=0X00000B00;//���ù������ 	  
	GPIOA->ODR|=1<<2;      //PA2��2��

	GPIOA->CRL&=0XFFFF0FFF;//PA3���
	GPIOA->CRL|=0X0000B000;//���ù������ 	  
	GPIOA->ODR|=1<<3;      //PA3����	

	
	TIM2->ARR=arr;//�趨�������Զ���װֵ 
	TIM2->PSC=psc;//Ԥ��Ƶ������Ƶ
	
//	TIM2->CCR2=125;
//	TIM2->CCR1=125;	
//	TIM2->CCR3=125;
//	TIM2->CCR4=125;
	
//	
	TIM2->CCMR1|=6<<4;   //CH2 PWMģʽ	  
	TIM2->CCMR1|=1<<3;   //CH1Ԥװ��ʹ��
							  
	TIM2->CCMR1|=6<<12;   //CH2 PWMģʽ	  
	TIM2->CCMR1|=1<<11;   //CH2Ԥװ��ʹ��

	TIM2->CCMR2|=6<<4;   //CH3 PWMģʽ	  
	TIM2->CCMR2|=1<<3;   //CH3Ԥװ��ʹ��

	TIM2->CCMR2|=6<<12;   //CH3 PWMģʽ	  
	TIM2->CCMR2|=1<<11;   //CH3Ԥװ��ʹ��

	TIM2->CR1|=0x0080;   //ARPEʹ�� 
	TIM2->CR1|=0x0001;    //ʹ�ܶ�ʱ��2 

	TIM2 ->CCER  |= 1<<0; 
	TIM2 ->CCER  |= 1<<4;
	TIM2 ->CCER  |= 1<<8; 
	TIM2 ->CCER  |= 1<<12;
//	TIM2 ->CCR1 = 200;
}

void PWM_nj(u16 pwm_n,u16 pwm_j)
{
	pwm_j=pwm_j/1.8+25;
	switch(pwm_n)
	{
		case 1:
			flage_ccr1=pwm_j;
			break;
		case 2:
			flage_ccr2=pwm_j;
			break;
		case 3:
			flage_ccr3=pwm_j;
			break;
		case 4:
			flage_ccr4=pwm_j;
			break;
	}
}







