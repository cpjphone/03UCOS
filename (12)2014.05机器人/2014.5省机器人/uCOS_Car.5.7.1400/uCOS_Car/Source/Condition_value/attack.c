/*********************************************************************************      
* ����    �ԡ���C����
* �������ܡ���(1):��ǰ�������ҵ��ٶȷ�Χ 0��100  ����
*								(2)�����ɺ����ٶ�ȡֵ��Χ -100��100���������������ǰ������Խ���ٶ�Խ��
* ����    �ڡ�: 2014/05/03
* ����    �ߡ�: Phone
*********************************************************************************/
#include "includes.h"
//#include "math.h"
#define key_front  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2)		  //ǰ
#define key_back   GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_0)		  //��
#define key_left   GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_1)		  //��
#define key_right  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_3)		  //��

#define key_FL  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_5)		  //ǰ��
#define key_FR  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_6)		  //ǰ��
#define key_BL  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_4)		  //����
#define key_BR  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_7)		  //����

void car_freedom(signed char led0pwmvalone,signed char led0pwmvaltwo);
/************************************************************************/
//�������� ������ǰ;��������
/************************************************************************/

void attack(void)
{
	/*****ǰ********/
	if(key_front == 0)
	{
		car_freedom(60,60); 	
		OSTimeDlyHMSM(0, 0, 3, 500);
	}
	/*****��********/
	if(key_back == 0)
	{
		car_freedom(-60,-60); 	
		OSTimeDlyHMSM(0, 0, 3, 500);
	}
	/*****��********/
	if(key_left == 0)
	{
		car_freedom(-60,60); 	
		OSTimeDlyHMSM(0,0,0, 800);
	}
	/*****��********/
	if(key_right == 0)
	{
		car_freedom(60,-60); 	
		OSTimeDlyHMSM(0, 0,0, 800);
	}
	/*****��ǰ��********/
	if(key_FL == 0)
	{
		car_freedom(-60,60); 	
		OSTimeDlyHMSM(0, 0,0,500);
	}
	/*****��ǰ��********/
	if(key_right == 0)
	{
		car_freedom(60,-60); 	
		OSTimeDlyHMSM(0,0,0, 500);
	}
	/*****�Ϻ���********/
	if(key_BL == 0)
	{
		car_freedom(60,-60); 	
		OSTimeDlyHMSM(0, 0,0, 500);
	}
	/*****�Ϻ���********/
	if(key_BR == 0)
	{
		car_freedom(60,-60); 	
		OSTimeDlyHMSM(0, 0,0, 500);
	}
	
	
	

}



