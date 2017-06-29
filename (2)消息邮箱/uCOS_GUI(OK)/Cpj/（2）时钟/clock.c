#include "sys.h"
uchar XS_tab[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x40,0x80,0x00};
uchar disp_buffer[7]={0};
#define keyadd GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_13) 					//��+�������ж�����ʱ�õ�
#define keyadd2 GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_14)				//��-�������ж�����ʱ�õ�

uchar count,k,countset,flag_t,setadd = 0;	//count:��20Ϊһ�룬flag_t:����ʱ���־��setadd����5 flagadd�仯 ����
char sec,min,hour;
char shan,flagadd = 0;				//flagadd�����ӱ�־��1������

NVIC_InitTypeDef NVIC_InitStructure;
TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;	   /*����Ϊ��Ӧ�Ľṹ��*/

/***************************************************************
funtion:�������ʾ����
***************************************************************/
void display()
{
	uchar i,temp;	
	temp = 0xfe;
	for(i=0;i<8;i++)
	{		
		GPIO_Write(GPIOA,0xff00 + temp);
		GPIO_Write(GPIOB,(XS_tab[disp_buffer[i]]<<8) + 0x00ff );
		wait(0.002);
		GPIO_Write(GPIOB,0x00ff);			
		temp = (temp<<1)|0x01;	
	}
}
/*************************************************/
//������ʾ����
/*************************************************/
void displayset()
{
	uchar i,temp;
	temp = 0xfe;
	for(i=0;i<8;i++)
	{
		GPIO_Write(GPIOA,temp);
		if(flag_t == 2)		 //��ʱ
		{
			if(i == 0 || i == 1)
			{
				if(shan == 1)					
					GPIO_Write(GPIOB,XS_tab[12]<<8);
				else
					GPIO_Write(GPIOB,XS_tab[disp_buffer[i]]<<8);	
			}
			else
				GPIO_Write(GPIOB,XS_tab[disp_buffer[i]]<<8);
		}
		if(flag_t == 1)		   //����
		{
			if(i == 3 || i == 4)
			{
				if(shan == 1)
					GPIO_Write(GPIOB,XS_tab[12]<<8);
				else
					GPIO_Write(GPIOB,XS_tab[disp_buffer[i]]<<8);	
			}
			else
				GPIO_Write(GPIOB,XS_tab[disp_buffer[i]]<<8);
		}
		wait(0.002);
		GPIO_Write(GPIOB,0x00<<8);			
		temp = (temp<<=1)|0x01;	
	}
}
/****************************************************************
funtion:��1������ɨ����򣺴��в������صģ����ذ���ֵ��
		��2������5S �ƶ���,��	
****************************************************************/
uchar keyscan()
{
	uint temp,ktemp,i;
	temp = GPIO_ReadInputData(GPIOA)>>8&0xf0;
	temp=~((temp>>4)|0xF0); //������λ�Ƶ���λ������
	if(temp  == 0)
		return(0);
	delay_ms(5);
	temp = GPIO_ReadInputData(GPIOA)>>8&0xf0;
	temp=~((temp>>4)|0xF0); //������λ�Ƶ���λ������
	if(temp  == 0)
		return(0);
	while(1)
	{	
			if(flagadd == 1)
			{
				if(keyadd == 0)	   //�ж����Ӱ���Ϊ�� + ���� , ���жϱ����� while��1����
				{
					if(flag_t == 1)
					{
						min++;
						if(min > 59)
							min = 0;
					}
					if(flag_t == 2)
					{
						hour++;
						if(hour > 23)
							hour = 0;
					}					
				}
				if(keyadd2 == 0)	   //�ж����Ӱ���Ϊ�� - ���� , ���жϱ����� while��1����
				{
					if(flag_t == 1)
					{
						min--;
						if(min <= 0)
							min = 59;
					}
					if(flag_t == 2)
					{
						hour--;
						if(hour <= 0)
							hour = 24;
					}					
				}					
			}
			
			disp_buffer[1] = hour%10;
			disp_buffer[0] = hour/10;
			disp_buffer[4] = min%10;
			disp_buffer[3] = min/10;
			disp_buffer[7] = sec%10;
			disp_buffer[6] = sec/10;
			disp_buffer[2] = 10;
			disp_buffer[5] = 11;
			for(i=0;i<30;i++)
			{	
				display();
			}
		 ktemp = GPIO_ReadInputData(GPIOA)>>8&0xf0;	
		 	for(i=0;i<10;i++)
			{	
				display();
			}	
			if((ktemp | 0x0f) == 0xff)
					 break;
		
	}
	flagadd = 0;		
	return temp;
}
/************************************************************
funtion: �������ݺ���
************************************************************/
void kpro(uchar temp)
{	
	if(temp == 1)
	{
		flag_t++;
		if(flag_t > 2)
		{
			flag_t = 0;
			sec = 0;
		}
	}
	if(temp == 2)
	{
		if(flag_t == 1)
		{
			min++;
			if(min > 59)
				min = 0;
		}
		if(flag_t == 2)
		{
			hour++;
			if(hour > 23)
				hour = 0;
		}
	}
	if(temp == 4)
	{
		if(flag_t == 1)
		{
			min--;
			if(min < 0)
				min = 59;
		}
		if(flag_t == 2)
		{
			hour--;
			if(hour < 0)
				hour = 23;
		}
	}
	if(temp == 8)		 // 7 0001 1100 0
	{;}	 //���� 	
}
void timer_init(u16 arr,u16 psc)
{
		RCC->APB1ENR|=1<<2; //TIM4ʱ��ʹ��    
	 	TIM4->ARR=arr;  	//�趨�������Զ���װֵ//�պ�1ms   ,����ʱ6.5536 s 
		TIM4->PSC=psc;  	//Ԥ��Ƶ��7200,�õ�10Khz�ļ���ʱ��
							//����������Ҫͬʱ���òſ���ʹ���ж�
		TIM4->DIER|=1<<0;   //��������ж�				
	 	TIM4->DIER|=1<<6;   //�������ж�	   
		TIM4->CR1|=0x01;    //ʹ�ܶ�ʱ��3
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
		NVIC_InitStructure.NVIC_IRQChannel =TIM4_IRQn;
	    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =0;
	    NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;  
	    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	    NVIC_Init(&NVIC_InitStructure);
}

void Delay(vu32 nCount)
{
  for(; nCount != 0; nCount--);
}

int main()
{
	
		void LED_Init();			//����
		LED_Init();		  		    //���ã���ʼ����LED���ӵ�Ӳ���ӿ�
		delay_init(72);	     	    //���ã���ʱ��ʼ��
		timer_init(500,7199);	    //10Khz��10000Hz�ļ���Ƶ�ʣ�������5000Ϊ500ms  	  ������ʱ��Ƶ�ʣ�CK_CNT�� = ��fCK_PSC(72M) / PSC[15��0](���Ϊ2��16�η�) + 1������ʱ = 72M/��7199 + 1��= 10k
		GPIOB->ODR|=0Xffff;
		
		while(1)
		{
			k = keyscan();
			if(k != 0)
			kpro(k);			
				disp_buffer[2] = 10;
				disp_buffer[5] = 11;
				disp_buffer[1] = hour%10;
				disp_buffer[0] = hour/10;
				disp_buffer[4] = min%10;
				disp_buffer[3] = min/10;
				disp_buffer[7] = sec%10;
				disp_buffer[6] = sec/10;		
			if(flag_t != 0)
				displayset();
			else
				display();	
			  	
			



			//PBout(8) = 0;
			//	GPIO_ResetBits(GPIOB,GPIO_Pin_8); 
			//GPIOB->ODR=0Xffff;
			//GPIO_Write(GPIOB,temp);
			//temp = ~temp;
			//wait(0.5);
//			GPIO_Write(GPIOA, ~Val);// | read_val ); //дһ�������ݵ�PB��
//			wait(0.5); // ��ʱ
//			if(Val == 0x8000) Val = 1;
//			else Val<<=1;
	    
				
		}
}

void TIM4_IRQHandler(void)
{
	if(TIM4->SR&0X0001)		 //����ж�   	   ʱ�䵽�ˣ�
	{	 
				//PBout(8) = 0;
				//	GPIO_SetBits(GPIOB,GPIO_Pin_8); 
			//	GPIO_Write(GPIOB,temp);

		//	temp = ~temp;
				//PBout(8) = 0;				
				//PBout(9) = 1;
				 // GPIOB->ODR=0x00ff;
				//PBout(9) = 1;
				//GPIOB->ODR=0Xf0<<8;
				// delay_ms(1050);
				//wait(2.100);	 //SysTick д�Ŀ������ӳ�ʱ�亯��
		count++;
		countset++;
		if(countset>5)
			{countset = 0;shan = ~shan;}
		if(count > 19)
		{
			count = 0;
			setadd++;
			if(setadd > 3)
			{
				setadd = 0;
				flagadd = 1;
			}
			if(flag_t == 0)
				sec++;
			if(sec > 59)
			{
				sec = 0;
				min++;
				if(min > 59)
				{
					min = 0;
					hour++;
					if(hour > 23)
						hour = 0;
				}
			}	
		}	
		}
		TIM4->SR&=~(1<<0);		//����жϱ�־λ 
}

