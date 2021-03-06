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

#define key1  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_11)		  //前左
#define key2  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_12)		  //前右
#define key3  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_15)		  //后右
#define key4  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_14)		  //后左�

#define key_Special_front  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_9)		  //后右
#define key_Special_back   GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)		  //后左

#define key_Mirror_front  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)		  //后左
#define key_Mirror_back   GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)		  //后右


void car_freedom(signed char led0pwmvalone,signed char led0pwmvaltwo);
void Delay_memory(unsigned int Dly);

extern u16 countnum,memorynum;

/************************************************************************/
//自由配置 正——前;负——后
/************************************************************************/

void attack1(void)
{
	
	/*****上前左********/
		if(key_FL == 0)
		{
			car_freedom(-35,90); 	
			OSTimeDlyHMSM(0, 0,0,300);			
			car_freedom(97,97);
			OSTimeDlyHMSM(0, 0,1,0);
		}
		
		/*****上前右********/
		if(key_FR == 0)
		{
			car_freedom(90,-35); 	
			OSTimeDlyHMSM(0, 0,0,300);
			car_freedom(97,97);
			OSTimeDlyHMSM(0, 0,1,0); 
		}
		
			/*****上后左********/
		if(key_BL == 0)
		{
			car_freedom(-35,-90); 	
			OSTimeDlyHMSM(0, 0,0,300);
			car_freedom(-97,-97);
			OSTimeDlyHMSM(0, 0,1,0); 
		}
		
		/*****上后右********/
		if(key_BR == 0)
		{
			car_freedom(-90,-35); 	
			OSTimeDlyHMSM(0, 0,0,300);
			car_freedom(-97,-97);
			OSTimeDlyHMSM(0, 0,1,0); 
		}
	
	

	 
/**********镜面************/
		/*****前********/
	
	else if(key_Mirror_front)
	{
		memorynum = countnum;
		while((countnum < memorynum + 300)&((!key1)|(!key2))&(!key_Special_front))
		{
			//OSTimeDly(1);
			car_freedom(97,-50); 
			Delay_memory(25);
			car_freedom(97,97); 
			Delay_memory(125);			
		}		 	
	  car_freedom(50,20); 
	}
	/*****后********/
	else if(key_Mirror_back)
	{
		memorynum = countnum;
		while((countnum < memorynum + 300)&((!key3)|(!key4))&(!key_Special_back))
		{
			//OSTimeDly(1);
			car_freedom(50,-97); 
			Delay_memory(25);
			car_freedom(-97,-97); 
			Delay_memory(125);			
		}		 	
	  car_freedom(-50,-20); 
	}

	else 
	{
		OSTimeDlyHMSM(0, 0, 0, 1);
	}
}



void attack2(void)
{

}




