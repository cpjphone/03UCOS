/*********************************************************************************      
* 【语    言】：C语言
* 【程序功能】：(1):向前、后、左、右的速度范围 0到100  递增
*								(2)：自由函数速度取值范围 -100到100，负数向后正数向前，数字越大速度越快
* 【日    期】: 2014/05/03
* 【作    者】: Phone
*********************************************************************************/
#include "includes.h"
//#include "math.h"
#define key1  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_10)		  //前左
#define key2  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_12)		  //前右
#define key3  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_13)		  //后右
#define key4  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_15)		  //后左

extern u32 countnum,memorynum;


void Delay(unsigned int Dly);
void Delay_memory(unsigned int Dly);
void car_freedom(signed char led0pwmvalone,signed char led0pwmvaltwo);
/************************************************************************/
//自由配置 正——前;负——后
/************************************************************************/

//int	statenum0;
void car_safe(void)
{		
	/***************前左******************/
	if((key1)&(!key3)&(!key4))
	{
		memorynum = countnum;
		while((countnum < (memorynum + 20))&(!key4)&(!key3))
		{
			if(key2 == 1)	car_freedom(-80,-80);
			else car_freedom(-90,-40);
		}
		while((countnum < (memorynum + 50))&(!key4)&(!key3))
		{
			if(key2 == 1)	car_freedom(-80,-80);
			else car_freedom(-70,-55);
		}
		
		if((key4)&(!key1))
		{
			if(key3)
			{
				car_freedom(95,70);
				Delay_memory(21);
			}
			else
			{
				car_freedom(95,-80);
				Delay_memory(21);
			}
			car_freedom(60,60);
			Delay_memory(12);
		}
		else
		{
			//car_freedom(0,0);
			OSTimeDly(1);
		}
		//car_freedom(0,0);
		OSTimeDly(1);
	}
	/***************前右******************/
	else if((key2)&(!key3)&(!key4))
	{
		memorynum = countnum;
		while((countnum < (memorynum + 20))&(!key4)&(!key3))
		{
			if(key1 == 1)	car_freedom(-80,-80);
			else car_freedom(-40,-90);
		}
		while((countnum < (memorynum + 70))&(!key4)&(!key3))
		{
			if(key1 == 1)	car_freedom(-80,-80);
			else car_freedom(-55,-70);
		}
		
		if((key3)&(!key2))
		{
			if(key4)
			{
				car_freedom(70,95);
				Delay_memory(21);
			}
			else
			{
				car_freedom(-10,95);
				Delay_memory(21);
			}
			car_freedom(60,60);
			Delay_memory(12);		
		}
		else
		{
			//car_freedom(0,0);
			OSTimeDly(1);
		}
		//car_freedom(0,0);
		OSTimeDly(1);
	}
	
	/***************后右******************/
	else if((key3)&(!key1)&(!key2))
	{
		memorynum = countnum;
		while((countnum < (memorynum + 20))&(!key1)&(!key2))
		{
			if(key4 == 1)	car_freedom(80,80);
			else car_freedom(40,90);
		}
		while((countnum < (memorynum + 70))&(!key1)&(!key2))
		{
			if(key4 == 1)	car_freedom(80,80);
			else car_freedom(55,70);
		}
		
		if((key2)&(!key3))
		{
			if(key1)
			{
				car_freedom(-70,-95);
				Delay_memory(21);
			}
			else
			{
				car_freedom(80,-95);
				Delay_memory(21);
			}
			car_freedom(-60,-60);
			Delay_memory(12);
		}
		else
		{
			//car_freedom(0,0);
			OSTimeDly(1);
		}
		//car_freedom(0,0);
		OSTimeDly(1);
	}
	
	/***************后左******************/
	else if((key4)&(!key1)&(!key2))
	{
		memorynum = countnum;
		while((countnum < (memorynum + 30))&(!key1)&(!key2))
		{
			if(key3 == 1)	car_freedom(80,80);
			else car_freedom(90,20);
		}
		while((!key1)&(!key2)&(countnum < (memorynum + 100)))
		{
			if(key3 == 1)	car_freedom(80,80);
			else car_freedom(60,45);
		}
		
		if((key1)&(!key4))
		{
			if(key2)
			{
				car_freedom(-95,-70);
				Delay_memory(21);
			}
			else
			{
				if(!key4)
				{
					car_freedom(-95,80);
					Delay_memory(21);
				}
				else
				{
						car_freedom(-95,20);
						Delay_memory(22);
				}
			}
			car_freedom(-60,-60);
			Delay_memory(12);
		}
		else
		{
			//car_freedom(0,0);
			OSTimeDly(1);
		}
		//car_freedom(0,0);
		OSTimeDly(1);
	}
	else if((key4)&(key1))
	{
		car_freedom(-80,95);
		Delay_memory(21);
	}
	else if((key2)&(key3))
	{
		car_freedom(95,-80);
		Delay_memory(21);
	}
	
	else
	{
		OSTimeDly(1);
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



