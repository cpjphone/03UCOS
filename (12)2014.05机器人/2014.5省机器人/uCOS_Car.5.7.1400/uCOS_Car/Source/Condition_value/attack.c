/*********************************************************************************      
* 【语    言】：C语言
* 【程序功能】：(1):向前、后、左、右的速度范围 0到100  递增
*								(2)：自由函数速度取值范围 -100到100，负数向后正数向前，数字越大速度越快
* 【日    期】: 2014/05/03
* 【作    者】: Phone
*********************************************************************************/
#include "includes.h"
//#include "math.h"
#define key_front  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2)		  //前
#define key_back   GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_0)		  //后
#define key_left   GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_1)		  //左
#define key_right  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_3)		  //右

#define key_FL  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_5)		  //前左
#define key_FR  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_6)		  //前右
#define key_BL  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_4)		  //后左
#define key_BR  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_7)		  //后右

void car_freedom(signed char led0pwmvalone,signed char led0pwmvaltwo);
/************************************************************************/
//自由配置 正——前;负——后
/************************************************************************/

void attack(void)
{
	/*****前********/
	if(key_front == 0)
	{
		car_freedom(60,60); 	
		OSTimeDlyHMSM(0, 0, 3, 500);
	}
	/*****后********/
	if(key_back == 0)
	{
		car_freedom(-60,-60); 	
		OSTimeDlyHMSM(0, 0, 3, 500);
	}
	/*****左********/
	if(key_left == 0)
	{
		car_freedom(-60,60); 	
		OSTimeDlyHMSM(0,0,0, 800);
	}
	/*****右********/
	if(key_right == 0)
	{
		car_freedom(60,-60); 	
		OSTimeDlyHMSM(0, 0,0, 800);
	}
	/*****上前左********/
	if(key_FL == 0)
	{
		car_freedom(-60,60); 	
		OSTimeDlyHMSM(0, 0,0,500);
	}
	/*****上前右********/
	if(key_right == 0)
	{
		car_freedom(60,-60); 	
		OSTimeDlyHMSM(0,0,0, 500);
	}
	/*****上后左********/
	if(key_BL == 0)
	{
		car_freedom(60,-60); 	
		OSTimeDlyHMSM(0, 0,0, 500);
	}
	/*****上后右********/
	if(key_BR == 0)
	{
		car_freedom(60,-60); 	
		OSTimeDlyHMSM(0, 0,0, 500);
	}
	
	
	

}



