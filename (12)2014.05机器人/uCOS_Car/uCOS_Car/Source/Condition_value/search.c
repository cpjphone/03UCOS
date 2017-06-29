/*********************************************************************************      
* ����    �ԡ���C����
* �������ܡ���(1):��ǰ�������ҵ��ٶȷ�Χ 0��100  ����
*								(2)�����ɺ����ٶ�ȡֵ��Χ -100��100���������������ǰ������Խ���ٶ�Խ��
* ����    �ڡ�: 2014/05/03
* ����    �ߡ�: Phone
*********************************************************************************/
#include "includes.h"
//#include "math.h"
#define key_front   GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_0)		  //ǰ
#define key_back    GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2)		  //��
#define key_left1   GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_3)		  //��
#define key_right1  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_1)		  //��
#define key_left2   GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_9)		  //��
#define key_right2  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_8)		  //��

#define key_FL  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_7)		  //ǰ��
#define key_FR  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_4)		  //ǰ��
#define key_BL  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_6)		  //����
#define key_BR  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_5)		  //����

void car_freedom(signed char led0pwmvalone,signed char led0pwmvaltwo);

extern u16 countnum,memorynum;
int move_sign;
/************************************************************************/
//�������� ������ǰ;��������
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
		/*****��ǰ��********/
		if(key_FL == 0)
		{
			car_freedom(-35,90); 	
			OSTimeDlyHMSM(0, 0,0,300);			
			car_freedom(30,40);
			//car_freedom(0,0); 
		}
		
		/*****��ǰ��********/
		if(key_FR == 0)
		{
			car_freedom(90,-35); 	
			OSTimeDlyHMSM(0, 0,0,300);
			car_freedom(40,30);
			//car_freedom(0,0); 
		}
		
			/*****�Ϻ���********/
		if(key_BL == 0)
		{
			car_freedom(-35,-90); 	
			OSTimeDlyHMSM(0, 0,0,300);
			car_freedom(-30,-40);
			//car_freedom(0,0); 
		}
		
		/*****�Ϻ���********/
		if(key_BR == 0)
		{
			car_freedom(-90,-35); 	
			OSTimeDlyHMSM(0, 0,0,300);
			car_freedom(-40,-30);
			//car_freedom(0,0); 
		}
 		
		/*****����ǰ����********/
		if((!key_left1)&(!key_left2))
		{
			//move_sign = 2;       	//����
			car_freedom(-97,97);
			while((!key_left1)|(!key_left2))
			OSTimeDlyHMSM(0,0,0,230);
			car_freedom(0,0);
		}
		
		if((!key_left1)&(key_left2))
		{
			//if(!key_left2) move_sign = 2;       	//����
			
			memorynum = countnum;
			while(countnum < memorynum + 12)
			{
				  OSTimeDly(1);
					if(!key_left2)
					{
						move_sign = 3;							    //�����
					}
			}	
		}
		
		/*****��������********/
		if((!key_left2)&(key_left1))
		{
			//if(!key_left1) move_sign = 2;       	//����
			
			memorynum = countnum;
			while(countnum < memorynum + 12)
			{
				  OSTimeDly(1);
					if(!key_left1)
					{
						move_sign = 4;							    //����ǰ
					}
			}	
		}
		
		/*****����ǰ����********/
		if((!key_right1)&(!key_right2))
		{
			//move_sign = 5;       	//����
			car_freedom(97,-97);
			while((!key_right1)|(!key_right2))
			OSTimeDlyHMSM(0,0,0,230);
			car_freedom(0,0);
		}
		
		if((!key_right1)&(key_right2))
		{
			//if(!key_right2) move_sign = 5;       	//����
			
			memorynum = countnum;
			while(countnum < memorynum + 12)
			{
				  OSTimeDly(1);
					if(!key_right2)
					{
						move_sign = 6;							    //���Һ�
					}
			}	
		}
		
		/*****��������********/
		if((!key_right2)&(key_right1))
		{
			//if(!key_right1) move_sign = 5;       	//����
			
			memorynum = countnum;
			while(countnum < memorynum + 12)
			{
				  OSTimeDly(1);
					if(!key_right1)
					{
						move_sign = 7;							    //����ǰ
					}
			}	
		}	
		
		switch(move_sign)
		{
			case 2 : car_freedom(-97,97); OSTimeDlyHMSM(0,0,0,230);car_freedom(0,0);break;			//����
			case 3 : car_freedom(-80,95); OSTimeDlyHMSM(0,0,0,230);car_freedom(0,0);break;			//�����
			case 4 : car_freedom(80,-95); OSTimeDlyHMSM(0,0,0,230);car_freedom(0,0);break;			//����ǰ
			
			case 5 : car_freedom(97,-97); OSTimeDlyHMSM(0,0,0,230);car_freedom(0,0);break;			//����
			case 6 : car_freedom(95,-80); OSTimeDlyHMSM(0,0,0,230);car_freedom(0,0);break;			//���Һ�
			case 7 : car_freedom(-95,80); OSTimeDlyHMSM(0,0,0,230);car_freedom(0,0);break;	    //����ǰ
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
	
	
	
// 	/*****ǰ********/
// 	if(key_front == 0)
// 	{
// 		car_freedom(60,60); 	
// 		OSTimeDlyHMSM(0, 0, 3, 500);
// 	}
// 	/*****��********/
// 	if(key_back == 0)
// 	{
// 		car_freedom(-60,-60); 	
// 		OSTimeDlyHMSM(0, 0, 3, 500);
// 	}
// 	/*****��********/
// 	if(key_left == 0)
// 	{
// 		car_freedom(-60,60); 	
// 		OSTimeDlyHMSM(0,0,0, 800);
// 	}
// 	/*****��********/
// 	if(key_right == 0)
// 	{
// 		car_freedom(60,-60); 	
// 		OSTimeDlyHMSM(0, 0,0, 800);
// 	}
// 	/*****��ǰ��********/
// 	if(key_FL == 0)
// 	{
// 		car_freedom(-60,60); 	
// 		OSTimeDlyHMSM(0, 0,0,500);
// 	}
// 	/*****��ǰ��********/
// 	if(key_right == 0)
// 	{
// 		car_freedom(60,-60); 	
// 		OSTimeDlyHMSM(0,0,0, 500);
// 	}
// 	/*****�Ϻ���********/
// 	if(key_BL == 0)
// 	{
// 		car_freedom(60,-60); 	
// 		OSTimeDlyHMSM(0, 0,0, 500);
// 	}
// 	/*****�Ϻ���********/
// 	if(key_BR == 0)
// 	{
// 		car_freedom(60,-60); 	
// 		OSTimeDlyHMSM(0, 0,0, 500);
// 	}
	
}



