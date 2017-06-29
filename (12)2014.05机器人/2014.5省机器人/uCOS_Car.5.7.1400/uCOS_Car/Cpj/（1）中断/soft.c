#include "stm32f10x.h"
//#include "key.h"
#define uint unsigned int
#define uchar unsigned char
#define key1 EXTI_GetITStatus(EXTI_Line1)
#define key2 EXTI_GetITStatus(EXTI_Line5)

NVIC_InitTypeDef NVIC_InitStructure;
ErrorStatus HSEStartUpStatus;
TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
u16 yang[]={0xff3f,0xff06,0xff5b,0xff4f,0xff66,0xff6d,0xff7d,0xff07,0xff7f,0xff6f,0xff40};
//u16 yin[]={0xc0ff,0xf9ff,0xa4ff,0xb0ff,0x99ff,0x92ff,0x82ff,0xf8ff,0x80ff,0x90ff};
uchar i,j,sec,min,hour,count=0,flag=0,k;
u16 temp,timer[8];
void delay(uint n);
//void timer_init(u16 arr,u16 psc);
// void ledinit()
// {
// 		RCC->APB2ENR|=1<<3;
// 		RCC->APB2ENR|=1<<2;
// 		GPIOB->CRH&=0X00000000;
// 		GPIOB->CRH|=0X33333333;
// }
void timer_init(u16 arr,u16 psc)
{
		RCC->APB1ENR|=1<<1;
		TIM3->ARR=arr;
		TIM3->PSC=psc;
		TIM3->DIER|=1<<0;
		TIM3->DIER|=1<<6;
		TIM3->CR1=0X01;
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
		NVIC_InitStructure.NVIC_IRQChannel =TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;  
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
	}

void delay(uint n)
{
		for (;n>0;n--);
}
void GPIO_Configuration()
{
			GPIO_InitTypeDef GPIO_InitStructure;
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA
                         | RCC_APB2Periph_AFIO, ENABLE);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       //��������
			GPIO_Init(GPIOB, &GPIO_InitStructure);
			GPIO_Init(GPIOA, &GPIO_InitStructure);

// 			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_5;
// 			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	  //���ø�������
// 			GPIO_Init(GPIOB, &GPIO_InitStructure);
				
}
/*******************************************************************************
*                           ����RCC
*******************************************************************************/
void RCC_Configuration(void)
{   
 //��λRCC�ⲿ�豸�Ĵ�����Ĭ��ֵ
  RCC_DeInit();

  //���ⲿ���پ���
  RCC_HSEConfig(RCC_HSE_ON);

   //�ȴ��ⲿ����ʱ��׼����
  HSEStartUpStatus = RCC_WaitForHSEStartUp();

  if(HSEStartUpStatus == SUCCESS)   //�ⲿ����ʱ���Ѿ�׼���
  {								    
    //����FLASH��Ԥȡ����
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

    //FLASH�ӳ�2������
    FLASH_SetLatency(FLASH_Latency_2);
 	
  //����AHB(HCLK)ʱ��=SYSCLK
    RCC_HCLKConfig(RCC_SYSCLK_Div1);  
  
   //����APB2(PCLK2)��=AHBʱ��
    RCC_PCLK2Config(RCC_HCLK_Div1); 

    //����APB1(PCLK1)��=AHB 1/2ʱ��
    RCC_PCLK1Config(RCC_HCLK_Div2);

     //����PLLʱ�� == �ⲿ���پ���ʱ��*9  PLLCLK = 8MHz * 9 = 72 MHz 
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

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
}

void NVIC_Configuration()
{
			EXTI_InitTypeDef EXTI_InitStructure;
			NVIC_InitTypeDef NVIC_InitStructure;
	
				EXTI_InitStructure.EXTI_Line = EXTI_Line1|EXTI_Line5;
				EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
				EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½��ش���
				EXTI_InitStructure.EXTI_LineCmd = ENABLE; //�ж���ʹ��
				EXTI_Init(&EXTI_InitStructure); //��ʼ���ж�

				
	
			NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
			NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn; //�ж�ͨ��
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =  2;  //ǿռ���ȼ�
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;//�����ȼ�
				EXTI_GenerateSWInterrupt(EXTI_Line1);
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  //ͨ���ж�ʹ��
			NVIC_Init(&NVIC_InitStructure);//��ʼ���ж�
	
			NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
			NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn; //�ж�ͨ��
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =  1;  //ǿռ���ȼ�
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;//�����ȼ�
			EXTI_GenerateSWInterrupt(EXTI_Line5);
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  //ͨ���ж�ʹ��
			NVIC_Init(&NVIC_InitStructure);//��ʼ���ж�
}

void display ()
{
			temp=0x7fff;
			timer[0]=sec%10;
			timer[1]=sec/10;
			timer[3]=min%10;
			timer[4]=min/10;
			timer[6]=hour%10;
			timer[7]=hour/10;
			timer[2]=10;
			timer[5]=10;
			for (i=0;i<8;i++)
			{
				GPIO_Write (GPIOB,temp);
				GPIO_Write (GPIOA,yang[timer[i]]);
				delay (0x7ff);
				temp=(temp>>1) | 0x8000;
			}
}

void led_init ()
{
	if (flag==2)
	{
		GPIO_ResetBits (GPIOB,GPIO_Pin_0);
		flag=0;
	}
}
int main()
{
		GPIO_Configuration(); 
		RCC_Configuration();
		NVIC_Configuration();	//NVIC����
		timer_init(10000,7199);
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource1);
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource5);
		while(1)
		{
			//GPIO_Write(GPIOB,yin[sec%10]);
			led_init ();
			display ();
			if (sec%3==0)
			{
				GPIO_SetBits (GPIOB,GPIO_Pin_1);
				GPIO_SetBits (GPIOB,GPIO_Pin_5);
			}
			if (sec%5==0)
			{
				GPIO_ResetBits (GPIOB,GPIO_Pin_1);
				GPIO_ResetBits (GPIOB,GPIO_Pin_5);
			}
		}
}
void TIM3_IRQHandler(void)
{
		if(TIM3->SR&0X0001)
		{
				flag++;
				sec++;
				if (sec>59)
				{
						sec=0;
						min++;
						if (min>59)
						{
							min=0;
							hour++;
							if (hour>23)
							{
									hour=0;
							}
						}
				}
		}
		TIM3->SR&=~(1<<0);
}

void EXTI1_IRQHandler(void)
{
		if (key1==1)
		{
				min+=5;
				if (min>59)
					min-=60;
				EXTI_ClearITPendingBit(EXTI_Line1);
				
		}			
}
void EXTI9_5_IRQHandler(void)
{
		if (key2==1)
		{
				hour+=3;
				if (hour>23)
					hour-=24;
				EXTI_ClearITPendingBit(EXTI_Line5);
				
		}			
}

