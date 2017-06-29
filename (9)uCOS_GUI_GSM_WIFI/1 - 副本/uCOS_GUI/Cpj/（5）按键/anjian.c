/*********************************************************************************      
* ����    �ԡ���C����
* �����뻷������Keil4  
* �������ܡ���ͨ���ж����󰴼�����LED������
* ������֧�֡���				
* ����    ��: RCC 8*9=72MHz		
* ��о    Ƭ��: stm32f103VET6 
* ����    �ڡ�: 2013/6/03
* ���޸����ڡ�: 2013/10/06-10
* ����    �ߡ�: Phone
* ��������: ���������ã�������á�
*********************************************************************************/

#include "sys.h"								              //����ͷ�ļ�

uchar flag,k,temp,count,flag_t,
	  shan1 = 0,shan = 0,setadd = 0,flagadd = 0;
char sec,min,hour;						                      
															  //���� ����
#define keyadd  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)		  //��+�������ж�����ʱ�õ�
#define keyadd2 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_9)		  //��-�������ж�����ʱ�õ�

NVIC_InitTypeDef NVIC_InitStructure;
TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;	              //����Ϊ��Ӧ�Ľṹ��

/************************************************************************/
//�����������ɵ�������
/************************************************************************/
uchar XS_tab[] = {
	0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x40,0x80,0x00}
	;

/************************************************************************/
//���������ʾ����
/************************************************************************/
uchar disp_buffer[8] ={0}; 

/************************************************************************/
//�������ʾ����
/************************************************************************/
void display()
{
	uchar i,temp;	
	temp = 0xfe;
	for(i=0;i<8;i++)
	{		
		GPIO_Write(GPIOA, temp+0xff00);
		GPIO_Write(GPIOB,XS_tab[disp_buffer[i]]<<8);
		wait(0.002);
		GPIO_Write(GPIOB,0x00<<8);			
		temp = (temp<<1)|0x01;	
	}
}

/************************************************************************/
//������ʾ����
/************************************************************************/
void displayset()	
{
	uchar i,temp;
	temp = 0xfe;
	for(i=0;i<8;i++)
	{
		//P2 = temp;
		GPIO_Write(GPIOA, temp+0xff00);
		if(flag_t == 2)		 //��ʱ
		{
			if(i == 0 || i == 1)
			{
				if(shan != 0)
					//P1 = tab[12];
					GPIO_Write(GPIOB,XS_tab[12]<<8);
				else
					//P1 = tab[disp_buffer[i]];
					GPIO_Write(GPIOB,XS_tab[disp_buffer[i]]<<8);	
			}
			else
				//P1 = tab[disp_buffer[i]];
				GPIO_Write(GPIOB,XS_tab[disp_buffer[i]]<<8);
		}
		if(flag_t == 1)		   //����
		{
			if(i == 3 || i == 4)
			{
				if(shan != 0)
					//P1 = tab[12];
					GPIO_Write(GPIOB,XS_tab[12]<<8);
				else
					//P1 = tab[disp_buffer[i]];
					GPIO_Write(GPIOB,XS_tab[disp_buffer[i]]<<8);	
			}
			else
				//P1 = tab[disp_buffer[i]];
				GPIO_Write(GPIOB,XS_tab[disp_buffer[i]]<<8);
		}
		wait(0.002);
		//P1 = 0x00;
		GPIO_Write(GPIOB,0x00<<8);
		//temp = _crol_(temp,1);
		temp = (temp<<1)|0x01;	
	}
}

/************************************************************************/
//�������뺯��
/************************************************************************/
uchar keyscan()
{
	uchar temp,ktemp;
	temp = GPIO_ReadInputData(GPIOA)>>8&0x0f;
	temp=~(temp|0xf0); 
	if(temp  == 0)
		return(0);
	delay_ms(5);
	temp = GPIO_ReadInputData(GPIOA)>>8&0x0f;
	temp=~(temp|0xf0); 
	if(temp  == 0)
		return(0);
	while(1)
	{			
		ktemp = GPIO_ReadInputData(GPIOA)>>8&0x0f;
		PBout(1) = 0;			 		
		if((ktemp | 0xf0) == 0xff)	
			break;		
	}
		PBout(1) = 1;	
	return temp;
}

/************************************************************************/
//funtion:��1������ɨ����򣺴��в������صģ����ذ���ֵ��
//	   	  ��2������5S �ƶ���,��	
/************************************************************************/
uchar keyscan2()
{
	uchar temp,ktemp;
	temp = GPIO_ReadInputData(GPIOA)>>8&0x0f;
	temp=~(temp|0xf0); 
	if(temp  == 0)
		return(0);
	delay_ms(20);
	temp = GPIO_ReadInputData(GPIOA)>>8&0x0f;
	temp=~(temp|0xf0); 
	if(temp  == 0)
		return(0);
	flagadd = 0;
	shan1 = 0;
	while(1)
	{
		if((flagadd == 1)&(shan1 != 0))
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
			display();		
		//ktemp = P3;
		ktemp = GPIO_ReadInputData(GPIOA)>>8&0x0f;
		//display();
		//if((ktemp | 0xc3) == 0xff)
		if((ktemp | 0xf0) == 0xff)
			break;
	}
	flagadd = 0;
	shan1 = 0;		
	return temp;
}
/************************************************************************/
//�������봦����
/************************************************************************/
void kpro(uchar temp)
{
	if(temp == 1)
		flag = 1;
	if(temp == 2)
		flag = 2;
	if(temp == 4)
		flag = 3;
	if(temp == 8)
		flag = 4;
//	else
//		flag = 0;		  
}

/************************************************************************/
//�������봦����
/************************************************************************/
void kpro2(uchar temp)
{
	if(temp == 1)
	//	flag = 1;
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

	if(temp == 2)
	//	flag = 2;
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
				hour = 23;
		}
	}

	if(temp == 4)
	//	flag = 3;
	{
		flag_t++;
		if(flag_t > 2)
		{
			flag_t = 0;
			sec = 0;
		}
	}

//	if(temp == 8)
	//	flag = 4;
//	else
//		flag = 0;		  
}

/************************************************************************/
//��ʱ��4�ж����ú���
/************************************************************************/
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
/************************************************************************/
//��ʱ��3�ж����ú���
/************************************************************************/
void timer_init3(u16 arr,u16 psc)
{
		RCC->APB1ENR|=1<<1; //TIM3ʱ��ʹ��    
	 	TIM3->ARR=arr;  	//�趨�������Զ���װֵ//�պ�1ms    
		TIM3->PSC=psc;  	//Ԥ��Ƶ��7200,�õ�10Khz�ļ���ʱ��
							//����������Ҫͬʱ���òſ���ʹ���ж�
		TIM3->DIER|=1<<0;   //��������ж�				
	 	TIM3->DIER|=1<<6;   //�������ж�	   
		TIM3->CR1|=0x01;    //ʹ�ܶ�ʱ��3
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
		NVIC_InitStructure.NVIC_IRQChannel =TIM3_IRQn;
	    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =0;
	    NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;  
	    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	    NVIC_Init(&NVIC_InitStructure);
}
/************************************************************************/
//CPU��ʱ����
/************************************************************************/
void Delay(vu32 nCount)
{
  for(; nCount != 0; nCount--);
}

/************************************************************************/
//������
/************************************************************************/
int main()
{	
	void LED_Init();			//����
	LED_Init();		  		    //���ã���ʼ����LED���ӵ�Ӳ���ӿ�
	delay_init(72);	     	    //���ã���ʱ��ʼ��
	timer_init(10000,7199);	    //10Khz��10000Hz�ļ���Ƶ�ʣ�������5000Ϊ500ms  	  ������ʱ��Ƶ�ʣ�CK_CNT�� = ��fCK_PSC(72M) / PSC[15��0](���Ϊ2��16�η�) + 1������ʱ = 72M/��7199 + 1��= 10k
	timer_init3(2000,7199);
	GPIOA->ODR|=0Xffff;
	GPIOB->ODR|=0Xffff;
	while(1)
	{
//		if(shan != 0)
//	    PBout(0) = 0; 
//		if(shan == 0)
//		PBout(0) = 1; 
//		PBout(1) = ~shan;
		k = keyscan2();
		if(k != 0)	
		kpro2(k)
		;		
		disp_buffer[2] = 10;
		disp_buffer[5] = 11;
		disp_buffer[1] = hour%10;
		disp_buffer[0] = hour/10;
		disp_buffer[4] = min%10;
		disp_buffer[3] = min/10;
		disp_buffer[7] = sec%10;
		disp_buffer[6] = sec/10;
//		for(i=0;i<228;i++)
//		display();
		if(flag_t != 0)					//�ж��Ƿ����
			displayset();				//����ʱ ����λ����˸
		else
			display();
//		if(1 == flag)
//			PBout(0) = 0;
//		else 
//			PBout(0) = 1;
		
		//	GPIO_ResetBits(GPIOB,GPIO_Pin_8); 
		//GPIOB->ODR=0Xffff;
		//GPIO_Write(GPIOB,temp);
		//temp = ~temp;
		//wait(0.5);
		//			GPIO_Write(GPIOA, ~Val);// | read_val ); //дһ�������ݵ�PB��
		//			wait(0.5); // ��ʱ
		//			if(Val == 0x8000) Val = 1;
		//			else Val<<=1;
		//	GPIO_Write(GPIOA, 0x0000);			
	}
}

/************************************************************************/
//��ʱ��4�жϷ�����
/************************************************************************/
void TIM4_IRQHandler(void)
{
	if(TIM4->SR&0X0001)		    //����ж�   	   ʱ�䵽�ˣ�
	{	 
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
			if(min >59)
			{
				min = 0;
				hour ++;
				if(hour > 23)
				{
					hour = 0;
				}
			}		
		}			
	}
		TIM4->SR&=~(1<<0);		//����жϱ�־λ 
}

/************************************************************************/
//��ʱ��3�жϷ�����
/************************************************************************/
void TIM3_IRQHandler(void)
{
	if(TIM3->SR&0X0001)		    //����ж�   	   ʱ�䵽�ˣ�
	{
		shan1 = ~shan1;
		count++;
		if(count >= 2)
		{
			count = 0;
			shan = ~shan;		
		}
				
	}
	TIM3->SR&=~(1<<0);		   //����жϱ�־λ 
}

/************************************************************************/
//successful
/************************************************************************/
