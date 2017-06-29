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

#define key1  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_11)		  //ǰ��
#define key2  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_12)		  //ǰ��
#define key3  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_15)		  //����
#define key4  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_14)		  //�����

#define key_Special_front  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_9)		  //����
#define key_Special_back   GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)		  //����

#define key_Mirror_front  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)		  //����
#define key_Mirror_back   GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)		  //����


void car_freedom(signed char led0pwmvalone,signed char led0pwmvaltwo);
void Delay_memory(unsigned int Dly);

extern u16 countnum,memorynum;

/************************************************************************/
//�������� ������ǰ;��������
/************************************************************************/

void attack1(void)
{
	
	/*****��ǰ��********/
		if(key_FL == 0)
		{
			car_freedom(-35,90); 	
			OSTimeDlyHMSM(0, 0,0,300);			
			car_freedom(97,97);
			OSTimeDlyHMSM(0, 0,1,0);
		}
		
		/*****��ǰ��********/
		if(key_FR == 0)
		{
			car_freedom(90,-35); 	
			OSTimeDlyHMSM(0, 0,0,300);
			car_freedom(97,97);
			OSTimeDlyHMSM(0, 0,1,0); 
		}
		
			/*****�Ϻ���********/
		if(key_BL == 0)
		{
			car_freedom(-35,-90); 	
			OSTimeDlyHMSM(0, 0,0,300);
			car_freedom(-97,-97);
			OSTimeDlyHMSM(0, 0,1,0); 
		}
		
		/*****�Ϻ���********/
		if(key_BR == 0)
		{
			car_freedom(-90,-35); 	
			OSTimeDlyHMSM(0, 0,0,300);
			car_freedom(-97,-97);
			OSTimeDlyHMSM(0, 0,1,0); 
		}
	
	

	 
/**********����************/
		/*****ǰ********/
	
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
	/*****��********/
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




