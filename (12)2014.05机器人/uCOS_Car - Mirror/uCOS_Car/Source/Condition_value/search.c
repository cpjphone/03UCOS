/*********************************************************************************      
* 【语    言】：C语言
* 【程序功能】：(1):向前、后、左、右的速度范围 0到100  递增
*								(2)：自由函数速度取值范围 -100到100，负数向后正数向前，数字越大速度越快
* 【日    期】: 2014/05/03
* 【作    者】: Phone
*********************************************************************************/
#include "includes.h"
//#include "math.h"
#define key_front   GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_0)		  //前
#define key_back    GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2)		  //后
#define key_left1   GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_3)		  //左
#define key_right1  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_1)		  //右
#define key_left2   GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_9)		  //左
#define key_right2  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_8)		  //右

#define key_FL  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_7)		  //前左
#define key_FR  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_4)		  //前右
#define key_BL  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_6)		  //后左
#define key_BR  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_5)		  //后右

void car_freedom(signed char led0pwmvalone,signed char led0pwmvaltwo);

extern u16 countnum,memorynum;
int move_sign;
/************************************************************************/
//自由配置 正——前;负——后
/************************************************************************/
// void search(void)

// {
// 	while((!key_left1)|(!key_right1)|(!key_left2)|(!key_right2)|(!key_FL)|(!key_FR)|(!key_BL)|(!key_BR))
// 	{
// 		
// 		car_freedom(30,30); 
// 	}
// 	
// car_freedom(0,0); 
// }


void search(void)
{
	
	if((key_front)&(key_back))
	{
		/*****上前左********/
		if(key_FL == 0)
		{
			car_freedom(-35,90); 	
			OSTimeDlyHMSM(0, 0,0,300);			
			car_freedom(30,40);
			//car_freedom(0,0); 
		}
		
		/*****上前右********/
		if(key_FR == 0)
		{
			car_freedom(90,-35); 	
			OSTimeDlyHMSM(0, 0,0,300);
			car_freedom(40,30);
			//car_freedom(0,0); 
		}
		
			/*****上后左********/
		if(key_BL == 0)
		{
			car_freedom(-35,-90); 	
			OSTimeDlyHMSM(0, 0,0,300);
			car_freedom(-30,-40);
			//car_freedom(0,0); 
		}
		
		/*****上后右********/
		if(key_BR == 0)
		{
			car_freedom(-90,-35); 	
			OSTimeDlyHMSM(0, 0,0,300);
			car_freedom(-40,-30);
			//car_freedom(0,0); 
		}
 		
		/*****从左前过来********/
		if((!key_left1)&(!key_left2))
		{
			//move_sign = 2;       	//正左
			car_freedom(-97,97);
			while((!key_left1)|(!key_left2))
			OSTimeDlyHMSM(0,0,0,230);
			car_freedom(0,0);
		}
		
		if((!key_left1)&(key_left2))
		{
			//if(!key_left2) move_sign = 2;       	//正左
			
			memorynum = countnum;
			while(countnum < memorynum + 12)
			{
				  OSTimeDly(1);
					if(!key_left2)
					{
						move_sign = 3;							    //向左后
					}
			}	
		}
		
		/*****从左后过来********/
		if((!key_left2)&(key_left1))
		{
			//if(!key_left1) move_sign = 2;       	//正左
			
			memorynum = countnum;
			while(countnum < memorynum + 12)
			{
				  OSTimeDly(1);
					if(!key_left1)
					{
						move_sign = 4;							    //向左前
					}
			}	
		}
		
		/*****从右前过来********/
		if((!key_right1)&(!key_right2))
		{
			//move_sign = 5;       	//正右
			car_freedom(97,-97);
			while((!key_right1)|(!key_right2))
			OSTimeDlyHMSM(0,0,0,230);
			car_freedom(0,0);
		}
		
		if((!key_right1)&(key_right2))
		{
			//if(!key_right2) move_sign = 5;       	//正右
			
			memorynum = countnum;
			while(countnum < memorynum + 12)
			{
				  OSTimeDly(1);
					if(!key_right2)
					{
						move_sign = 6;							    //向右后
					}
			}	
		}
		
		/*****从左后过来********/
		if((!key_right2)&(key_right1))
		{
			//if(!key_right1) move_sign = 5;       	//正右
			
			memorynum = countnum;
			while(countnum < memorynum + 12)
			{
				  OSTimeDly(1);
					if(!key_right1)
					{
						move_sign = 7;							    //向右前
					}
			}	
		}	
		
		switch(move_sign)
		{
			case 2 : car_freedom(-97,97); OSTimeDlyHMSM(0,0,0,230);car_freedom(0,0);break;			//正左
			case 3 : car_freedom(-80,95); OSTimeDlyHMSM(0,0,0,230);car_freedom(0,0);break;			//向左后
			case 4 : car_freedom(80,-95); OSTimeDlyHMSM(0,0,0,230);car_freedom(0,0);break;			//向左前
			
			case 5 : car_freedom(97,-97); OSTimeDlyHMSM(0,0,0,230);car_freedom(0,0);break;			//正右
			case 6 : car_freedom(95,-80); OSTimeDlyHMSM(0,0,0,230);car_freedom(0,0);break;			//向右后
			case 7 : car_freedom(-95,80); OSTimeDlyHMSM(0,0,0,230);car_freedom(0,0);break;	    //向右前
			default :OSTimeDly(1); 
		}
		//car_freedom(0,0);
		move_sign = 0; 
	}
	else
	{
	//	car_freedom(0,0);
		OSTimeDlyHMSM(0,0,0,2);	
	}
	
	
	
// 	/*****前********/
// 	if(key_front == 0)
// 	{
// 		car_freedom(60,60); 	
// 		OSTimeDlyHMSM(0, 0, 3, 500);
// 	}
// 	/*****后********/
// 	if(key_back == 0)
// 	{
// 		car_freedom(-60,-60); 	
// 		OSTimeDlyHMSM(0, 0, 3, 500);
// 	}
// 	/*****左********/
// 	if(key_left == 0)
// 	{
// 		car_freedom(-60,60); 	
// 		OSTimeDlyHMSM(0,0,0, 800);
// 	}
// 	/*****右********/
// 	if(key_right == 0)
// 	{
// 		car_freedom(60,-60); 	
// 		OSTimeDlyHMSM(0, 0,0, 800);
// 	}
// 	/*****上前左********/
// 	if(key_FL == 0)
// 	{
// 		car_freedom(-60,60); 	
// 		OSTimeDlyHMSM(0, 0,0,500);
// 	}
// 	/*****上前右********/
// 	if(key_right == 0)
// 	{
// 		car_freedom(60,-60); 	
// 		OSTimeDlyHMSM(0,0,0, 500);
// 	}
// 	/*****上后左********/
// 	if(key_BL == 0)
// 	{
// 		car_freedom(60,-60); 	
// 		OSTimeDlyHMSM(0, 0,0, 500);
// 	}
// 	/*****上后右********/
// 	if(key_BR == 0)
// 	{
// 		car_freedom(60,-60); 	
// 		OSTimeDlyHMSM(0, 0,0, 500);
// 	}
	
}



