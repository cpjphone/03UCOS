#include "sys.h"
uint32_t i,j,temp;
uchar tab[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F};
uchar disp_buffer[9]={0,1,2,3,4,5,6,7,8};

void delayms(uint32_t m)
{
	 
	uint32_t i,j,k;
	for(i = 0; i < 35; i ++ )
	{
		for(j = 0;j < 999;j ++)
		{
			for(k = 0;k < m; k --)
			;
		}	
	}
}

void delay(uint n)
{
		for(; n>0; n--);
}



int main()
{		void Delay(vu32 nCount);
		void delayms(uint32_t m);
		void LED_Init();			//����
		LED_Init();		  		    //���ã���ʼ����LED���ӵ�Ӳ���ӿ�
		delay_init(72);	     	    //���ã���ʱ��ʼ��
		GPIOB->ODR|=0Xffff;

		while(1)
		{
			for(i = 0;i < 9;i++)
				{
					for(j=0;j<100;j++)
						{	
							GPIO_Write(GPIOB,~tab[disp_buffer[i]]<<8);
							delay(0xffff - 8000*i);			
							//delayms(9 - i);
							GPIO_Write(GPIOB,0xff<<8);
							delay(8000*i);
							//delayms(i);							
						}
				} 
				
		}
}
