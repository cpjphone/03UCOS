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

#define key_Mirror_front  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)		  //后左
#define key_Mirror_back   GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)		  //后右


void car_freedom(signed char led0pwmvalone,signed char led0pwmvaltwo);
void Delay_memory(unsigned int Dly);

extern u32 countnum,memorynum;

/************************************************************************/
//自由配置 正——前;负——后
/************************************************************************/

void attack1(void)
{
//	OSTimeDlyHMSM(0, 0, 0, 5);
	/*****左前********/
	if((!key_front)&(!key_FL))
	{
		car_freedom(85,97); 			
		OSTimeDlyHMSM(0, 0, 0, 500);
		car_freedom(97,97); 	
		while(!key_front);		
		car_freedom(-40,-20);
	}
	/*****右前********/
	else if((!key_front)&(!key_FR))
	{
		car_freedom(97,85); 	
		OSTimeDlyHMSM(0, 0, 0, 500);
		car_freedom(97,97); 	
		while(!key_front);	
		car_freedom(-20,-40);
	}
	
	/*****左后********/
	else if((!key_back)&(!key_BL))
	{
		car_freedom(-85,-97); 	
		OSTimeDlyHMSM(0, 0, 0, 500);
		car_freedom(-97,-97); 	
		while(!key_back);		
		car_freedom(40,20); 
	}
	
	/*****右后********/
	else if((!key_back)&(!key_BR))
	{
		car_freedom(-97,-85); 	
		OSTimeDlyHMSM(0, 0, 0, 500);
		car_freedom(-97,-97); 	
		while(!key_back);	
		car_freedom(20,40); 
	}
	
	/*****前********/
	if(key_front == 0)
	{
		car_freedom(97,97); 	
		while(!key_front);
		OSTimeDlyHMSM(0, 0, 0, 500);
		car_freedom(-20,-40);
	}
	/*****后********/
	else if(key_back == 0)
	{
		car_freedom(-97,-97); 	
		while(!key_back);
		OSTimeDlyHMSM(0, 0, 0, 500);
		car_freedom(20,40);
	}
	 
/**********镜面************/
		/*****前********/
	
// 		memorynum = countnum;
// 			while(countnum < memorynum + 12)
// 			{
// 				  OSTimeDly(1);

// 			}
// 					
		
// 	else if(key_Mirror_front)
// 	{
// 		memorynum = countnum;
// 		while((countnum < memorynum + 100)&((!key1)|(!key2))&(!key_Special_front))
// 		{
// 			//OSTimeDly(1);
// 			car_freedom(77,97); 
// 			Delay_memory(2);
// 			car_freedom(97,77); 
// 			Delay_memory(2);			
// 		}		 	
// 	  car_freedom(-50,-50); 
// 	}
// 	/*****后********/
// 	else if(key_Mirror_back)
// 	{
// 		memorynum = countnum;
// 		while((countnum < memorynum + 100)&((!key3)|(!key4))&(!key_Special_back))
// 		{
// 			//OSTimeDly(1);
// 			car_freedom(-77,-97); 
// 			Delay_memory(2);
// 			car_freedom(-97,-77); 
// 			Delay_memory(2);			
// 		}		 	
// 	  car_freedom(50,50); 
// 	}

	else 
	{
		OSTimeDlyHMSM(0, 0, 0, 1);
	}
}

void attack2(void)
{

}




