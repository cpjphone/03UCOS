/*********************************************************************************      
* ����    �ԡ���C����
* �������ܡ���(1):��ǰ�������ҵ��ٶȷ�Χ 0��100  ����
*								(2)�����ɺ����ٶ�ȡֵ��Χ -100��100���������������ǰ������Խ���ٶ�Խ��
* ����    �ڡ�: 2014/05/03
* ����    �ߡ�: Phone
*********************************************************************************/
#include "includes.h"
//#include "math.h"
#define key_front  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_0)		  //ǰ
#define key_back   GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2)		  //��

#define key_FL  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_7)		  //ǰ��
#define key_FR  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_4)		  //ǰ��
#define key_BL  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_6)		  //����
#define key_BR  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_5)		  //����

#define key_Mirror_front  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)		  //����
#define key_Mirror_back   GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)		  //����


void car_freedom(signed char led0pwmvalone,signed char led0pwmvaltwo);
void Delay_memory(unsigned int Dly);

extern u32 countnum,memorynum;

/************************************************************************/
//�������� ������ǰ;��������
/************************************************************************/

void attack1(void)
{
//	OSTimeDlyHMSM(0, 0, 0, 5);
	/*****��ǰ********/
	if((!key_front)&(!key_FL))
	{
		car_freedom(85,97); 			
		OSTimeDlyHMSM(0, 0, 0, 500);
		car_freedom(97,97); 	
		while(!key_front);		
		car_freedom(-40,-20);
	}
	/*****��ǰ********/
	else if((!key_front)&(!key_FR))
	{
		car_freedom(97,85); 	
		OSTimeDlyHMSM(0, 0, 0, 500);
		car_freedom(97,97); 	
		while(!key_front);	
		car_freedom(-20,-40);
	}
	
	/*****���********/
	else if((!key_back)&(!key_BL))
	{
		car_freedom(-85,-97); 	
		OSTimeDlyHMSM(0, 0, 0, 500);
		car_freedom(-97,-97); 	
		while(!key_back);		
		car_freedom(40,20); 
	}
	
	/*****�Һ�********/
	else if((!key_back)&(!key_BR))
	{
		car_freedom(-97,-85); 	
		OSTimeDlyHMSM(0, 0, 0, 500);
		car_freedom(-97,-97); 	
		while(!key_back);	
		car_freedom(20,40); 
	}
	
	/*****ǰ********/
	if(key_front == 0)
	{
		car_freedom(97,97); 	
		while(!key_front);
		OSTimeDlyHMSM(0, 0, 0, 500);
		car_freedom(-20,-40);
	}
	/*****��********/
	else if(key_back == 0)
	{
		car_freedom(-97,-97); 	
		while(!key_back);
		OSTimeDlyHMSM(0, 0, 0, 500);
		car_freedom(20,40);
	}
	 
/**********����************/
		/*****ǰ********/
	
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
// 	/*****��********/
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




