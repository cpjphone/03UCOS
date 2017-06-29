#include "stm32f10x.h"
#include "key.h"
//#define uint unsigned int
//#define uchar unsigned char
uint a;
uchar bb[]={0x01,0xf3,0x52,0x96,0x24,0x6c,0x98,0xf9};
void delay(uint n);
void ledinit()
{
		RCC->APB2ENR|=1<<3;
		RCC->APB2ENR|=1<<2;
		GPIOB->CRH&=0X00000000;
		GPIOB->CRH|=0X33333333;
}
int main()
{
		ledinit();
		WKUP_Init();
		//GPIOB->ODR=0XFEFF;
		while(1)
		{
			if(KEY==0)
			{
			//ledinit();
			GPIOB->ODR=0XFEFF;
			for(a=0;a<8;a++)
			{
					//GPIO_Write(GPIOB,bb[a]<<8);
					GPIOB->ODR<<=1;
					delay(0x8fffff);
			}
		}
		}
}
void delay(uint n)
{
		for(; n>0; n--);
}
void Sys_Standby(void)
{
	SCB->SCR|=1<<2;//ʹ��SLEEPDEEPλ (SYS->CTRL)	   
  	RCC->APB1ENR|=1<<28;     //ʹ�ܵ�Դʱ��	    
 	PWR->CSR|=1<<8;          //����WKUP���ڻ���
	PWR->CR|=1<<2;           //���Wake-up ��־
	PWR->CR|=1<<1;           //PDDS��λ		  
	WFI_SET();				 //ִ��WFIָ��		 
}
