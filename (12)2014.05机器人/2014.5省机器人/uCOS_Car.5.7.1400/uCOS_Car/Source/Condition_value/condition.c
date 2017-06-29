/*********************************************************************************      
* 【语    言】：C语言
* 【程序功能】：(1):向前、后、左、右的速度范围 0到100  递增
*								(2)：自由函数速度取值范围 -100到100，负数向后正数向前，数字越大速度越快
* 【日    期】: 2014/05/03
* 【作    者】: Phone
*********************************************************************************/
#include "includes.h"
//#include "math.h"
#define key1  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_13)		  //前左
#define key2  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_15)		  //前右
#define key3  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_10)		  //后右
#define key4  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_12)		  //后左



void Delay(unsigned int Dly);
void car_freedom(signed char led0pwmvalone,signed char led0pwmvaltwo);
/************************************************************************/
//自由配置 正——前;负——后
/************************************************************************/

int	statenum0;
void car_safe(void)
{
	if(key1 == 1)
	{
		car_freedom(-40,-40);
		Delay(0x7ffffff); //500ms
		if((key2)|(key3))
		{
			car_freedom(-40,-70);
			Delay(0x7ffffff); //500ms
		}
		if((key1)|(key4))
		{
			car_freedom(-70,-40);
			Delay(0x7ffffff); //500ms
		}

	}
	
	
	
	/*****左电机********/
// 	if(key1 == 1)
// 	{
// 		statenum0 = 2 ;
// 	}
// 	
// 	else if(key2 == 1)
// 	{
// 		statenum0 = 3 ;
// 	}
// 	
// 	else if(key3 == 1)
// 	{
// 		statenum0 = 4 ;
// 	}
// 	
// 	else if(key4 == 1)
// 	{
// 		statenum0 = 5 ;
// 	}
// 	
// 	else if( (key1 == 1) && (key2 == 1) )
// 	{
// 		statenum0 = 6 ;
// 	}
// 	
// 	else if( (key1 == 1) && (key4 == 1) )
// 	{
// 		statenum0 = 7 ;
// 	}
// 	
// 	else if( (key3 == 1) && (key2 == 1) )
// 	{
// 		statenum0 = 8 ;
// 	}
// 	
// 	else if( (key1 == 1) && (key4 == 1) )
// 	{
// 		statenum0 = 9 ;
// 	}
// 	
// 	else 
// 	{
// 		statenum0 = 0;
// 		OSTimeDlyHMSM(0, 0, 0, 3);
// 	}
// 	
// 	switch(statenum0)
// 	{
// 		case 2 : car_freedom(-40,-35); ;Delay(100000);break;
// 		case 3 : car_freedom(-35,-40); ;Delay(100000);break;
// 		case 4 : car_freedom(35,40);   ;Delay(100000);break;
// 		case 5 : car_freedom(40,35);   ;Delay(100000);break;
// 		case 6 : car_freedom(40,40);   ;Delay(50000);break;
// 		case 7 : car_freedom(40,-30);  ;Delay(50000); car_freedom(90,90); ;Delay(50000);break;
// 		case 8 : car_freedom(-30,40);  ;Delay(50000); car_freedom(90,90); ;Delay(50000);break;
// 		case 9 : car_freedom(40,40);   ;Delay(50000);break;
// 		default :OSTimeDly(1); 
// 	}
}



