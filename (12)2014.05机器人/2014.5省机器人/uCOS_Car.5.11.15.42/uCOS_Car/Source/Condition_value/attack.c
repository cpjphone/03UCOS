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

void car_freedom(signed char led0pwmvalone,signed char led0pwmvaltwo);
/************************************************************************/
//�������� ������ǰ;��������
/************************************************************************/

void attack(void)
{
	/*****��ǰ********/
	if((!key_front)&(!key_FL))
	{
		car_freedom(85,95); 	
		OSTimeDlyHMSM(0, 0, 0, 500);
	}
	/*****��ǰ********/
	else if((!key_front)&(!key_FR))
	{
		car_freedom(95,85); 	
		OSTimeDlyHMSM(0, 0, 0, 500);
	}
	
	/*****���********/
	else if((!key_back)&(!key_BL))
	{
		car_freedom(-85,-95); 	
		OSTimeDlyHMSM(0, 0, 0, 500);
	}
	
	/*****�Һ�********/
	else if((!key_back)&(!key_BR))
	{
		car_freedom(-95,-85); 	
		OSTimeDlyHMSM(0, 0, 0, 500);
	}
	
	/*****ǰ********/
	else if(key_front == 0)
	{
		car_freedom(97,97); 	
		OSTimeDlyHMSM(0, 0, 0, 500);
	}
	/*****��********/
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



