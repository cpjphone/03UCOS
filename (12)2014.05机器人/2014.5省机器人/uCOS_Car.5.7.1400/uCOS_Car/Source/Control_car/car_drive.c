/*********************************************************************************      
* 【语    言】：C语言
* 【程序功能】：(1):向前、后、左、右的速度范围 0到100  递增
*								(2)：自由函数速度取值范围 -100到100，负数向后正数向前，数字越大速度越快
* 【日    期】: 2014/05/03
* 【作    者】: Phone
*********************************************************************************/
#include "includes.h"
#include "math.h"

/************************************************************************/
//向前
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
//向后
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
//向左
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
//向右
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
//自由配置 正——前;负——后
/************************************************************************/
void car_freedom(signed char led0pwmvalone,signed char led0pwmvaltwo)
{
	/*****左电机********/
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
	
			/*****右电机********/
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



