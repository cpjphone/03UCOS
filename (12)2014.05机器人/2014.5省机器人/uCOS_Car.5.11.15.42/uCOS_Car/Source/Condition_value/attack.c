/*********************************************************************************      
* 【语    言】：C语言
* 【程序功能】：(1):向前、后、左、右的速度范围 0到100  递增
*								(2)：自由函数速度取值范围 -100到100，负数向后正数向前，数字越大速度越快
* 【日    期】: 2014/05/03
* 【作    者】: Phone
*********************************************************************************/
#include "includes.h"
//#include "math.h"
#define key_front  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_0)		  //前
#define key_back   GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2)		  //后

#define key_FL  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_7)		  //前左
#define key_FR  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_4)		  //前右
#define key_BL  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_6)		  //后左
#define key_BR  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_5)		  //后右

void car_freedom(signed char led0pwmvalone,signed char led0pwmvaltwo);
/************************************************************************/
//自由配置 正——前;负——后
/************************************************************************/

void attack(void)
{
	/*****左前********/
	if((!key_front)&(!key_FL))
	{
		car_freedom(85,95); 	
		OSTimeDlyHMSM(0, 0, 0, 500);
	}
	/*****右前********/
	else if((!key_front)&(!key_FR))
	{
		car_freedom(95,85); 	
		OSTimeDlyHMSM(0, 0, 0, 500);
	}
	
	/*****左后********/
	else if((!key_back)&(!key_BL))
	{
		car_freedom(-85,-95); 	
		OSTimeDlyHMSM(0, 0, 0, 500);
	}
	
	/*****右后********/
	else if((!key_back)&(!key_BR))
	{
		car_freedom(-95,-85); 	
		OSTimeDlyHMSM(0, 0, 0, 500);
	}
	
	/*****前********/
	else if(key_front == 0)
	{
		car_freedom(97,97); 	
		OSTimeDlyHMSM(0, 0, 0, 500);
	}
	/*****后********/
	else if(key_back == 0)
	{
		car_freedom(-97,-97); 	
		OSTimeDlyHMSM(0, 0, 0, 500);
	}
	else 
	{
		OSTimeDlyHMSM(0, 0, 0, 1);
	}
}



