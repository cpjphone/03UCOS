/*********************************************************************************      
* ����    �ԡ���C����
* �������ܡ���(1):��ǰ�������ҵ��ٶȷ�Χ 0��100  ����
*								(2)�����ɺ����ٶ�ȡֵ��Χ -100��100���������������ǰ������Խ���ٶ�Խ��
* ����    �ڡ�: 2014/05/03
* ����    �ߡ�: Phone
*********************************************************************************/
#include "includes.h"
#include "math.h"

/************************************************************************/
//��ǰ
/************************************************************************/
void car_forward(u16 led0pwmval)
{
		led0pwmval = 100 - led0pwmval;
		TIM_SetCompare1(TIM2,led0pwmval);	
		TIM_SetCompare2(TIM2,led0pwmval);	
// 		TIM_SetCompare3(TIM2,led0pwmval);	
// 		TIM_SetCompare4(TIM2,led0pwmval);	
	
		GPIO_SetBits(GPIOA,GPIO_Pin_4);	
	  GPIO_SetBits(GPIOA,GPIO_Pin_6);	
	  GPIO_ResetBits(GPIOA,GPIO_Pin_5);	
	  GPIO_ResetBits(GPIOA,GPIO_Pin_7);	
}

/************************************************************************/
//���
/************************************************************************/
void car_backwards(u16 led0pwmval)
{
		led0pwmval = 100 - led0pwmval;
		TIM_SetCompare1(TIM2,led0pwmval);	
		TIM_SetCompare2(TIM2,led0pwmval);	
	
		GPIO_SetBits(GPIOA,GPIO_Pin_5);	
	  GPIO_SetBits(GPIOA,GPIO_Pin_7);	
	  GPIO_ResetBits(GPIOA,GPIO_Pin_4);	
	  GPIO_ResetBits(GPIOA,GPIO_Pin_6);	
}

/************************************************************************/
//����
/************************************************************************/
void car_left(u16 led0pwmvalone,u16 led0pwmvaltwo)
{
		led0pwmvalone = 100 - led0pwmvalone;
		led0pwmvaltwo = 100 - led0pwmvaltwo;
		TIM_SetCompare1(TIM2,led0pwmvalone);	
		TIM_SetCompare2(TIM2,led0pwmvaltwo);
	
	  GPIO_ResetBits(GPIOA,GPIO_Pin_4);
		GPIO_SetBits(GPIOA,GPIO_Pin_5);	
	
	  GPIO_SetBits(GPIOA,GPIO_Pin_6);	  	
	  GPIO_ResetBits(GPIOA,GPIO_Pin_7);	
}

/************************************************************************/
//����
/************************************************************************/
void car_right(u16 led0pwmvalone,u16 led0pwmvaltwo)
{
		led0pwmvalone = 100 - led0pwmvalone;
		led0pwmvaltwo = 100 - led0pwmvaltwo;
	
		TIM_SetCompare1(TIM2,led0pwmvalone);	
		TIM_SetCompare2(TIM2,led0pwmvaltwo);
	
	  GPIO_ResetBits(GPIOA,GPIO_Pin_5);
		GPIO_SetBits(GPIOA,GPIO_Pin_4);	
	
	  GPIO_SetBits(GPIOA,GPIO_Pin_7);	  	
	  GPIO_ResetBits(GPIOA,GPIO_Pin_6);	
}

/************************************************************************/
//�������� ������ǰ;��������
/************************************************************************/
void car_freedom(signed char led0pwmvalone,signed char led0pwmvaltwo)
{
	/*****����********/
	if(led0pwmvalone >= 0)
	{
		led0pwmvalone = 100 - led0pwmvalone;
		TIM_SetCompare1(TIM2,led0pwmvalone);	
		GPIO_SetBits(GPIOA,GPIO_Pin_4);	
	  GPIO_ResetBits(GPIOA,GPIO_Pin_5);	
	}
	else
	{
		led0pwmvalone = 100 + led0pwmvalone;
		//led0pwmvalone = fabs(led0pwmvalone);
		TIM_SetCompare1(TIM2,led0pwmvalone);	
		GPIO_SetBits(GPIOA,GPIO_Pin_5);	
	  GPIO_ResetBits(GPIOA,GPIO_Pin_4);	
	}
	
			/*****�ҵ��********/
	if(led0pwmvaltwo >= 0)
	{
		led0pwmvaltwo = 100 - led0pwmvaltwo;
		TIM_SetCompare2(TIM2,led0pwmvaltwo);	
		GPIO_SetBits(GPIOA,GPIO_Pin_6);	
	  GPIO_ResetBits(GPIOA,GPIO_Pin_7);
	}
	else
	{
		led0pwmvaltwo = 100 + led0pwmvaltwo;
		//led0pwmvaltwo = fabs(led0pwmvaltwo);
		TIM_SetCompare2(TIM2,led0pwmvaltwo);	
		GPIO_SetBits(GPIOA,GPIO_Pin_7);	
	  GPIO_ResetBits(GPIOA,GPIO_Pin_6);
	}

}



