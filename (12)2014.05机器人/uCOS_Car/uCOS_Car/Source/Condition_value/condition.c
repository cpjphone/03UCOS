/*********************************************************************************      
* ����    �ԡ���C����
* �������ܡ���(1):��ǰ�������ҵ��ٶȷ�Χ 0��100  ����
*								(2)�����ɺ����ٶ�ȡֵ��Χ -100��100���������������ǰ������Խ���ٶ�Խ��
* ����    �ڡ�: 2014/05/03
* ����    �ߡ�: Phone
*********************************************************************************/
#include "includes.h"
//#include "math.h"
#define key1  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_11)		  //ǰ��
#define key2  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_12)		  //ǰ��
#define key3  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_15)		  //����
#define key4  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_14)		  //����

#define key_Special_front  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_9)		  //����
#define key_Special_back   GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)		  //����


extern u16 countnum,memorynum;


void Delay(unsigned int Dly);
void Delay_memory(unsigned int Dly);
void car_freedom(signed char led0pwmvalone,signed char led0pwmvaltwo);
/************************************************************************/
//�������� ������ǰ;��������
/************************************************************************/

//int	statenum0;
void car_safe1(void)
{		
	if(key_Special_front)
	{
		memorynum = countnum;
		while((countnum < (memorynum + 30))|(key_Special_front))
		{
			car_freedom(-97,-97);
		}
	}
	else if (key_Special_back)
	{
		memorynum = countnum;
		while((countnum < (memorynum + 30))|(key_Special_back))
		{
			car_freedom(97,97);
		}
	}
	/***************ǰ��******************/
	else if ((key1)&(!key3)&(!key4))
	{
		memorynum = countnum;
		while((countnum < (memorynum + 35))&(!key4)&(!key3))
		{
			if(key2 == 1)	car_freedom(-97,-97);
			else car_freedom(-97,-47);
		}
		while((countnum < (memorynum + 90))&(!key4)&(!key3))
		{
			if(key2 == 1)	car_freedom(-97,-97);
			else car_freedom(-77,-50);
		}
		
		
		if((key4)&(!key1))
		{
			if(key3)
			{
				car_freedom(97,85);
				Delay_memory(21);
			}
			else
			{
				car_freedom(95,-80);
				Delay_memory(23);
			}
			car_freedom(50,50);
			Delay_memory(12);
		}
		else
		{
			//car_freedom(0,0);
			car_freedom(-50,-47);
			OSTimeDly(1);
		}
		//car_freedom(0,0);
		OSTimeDly(1);
	}
	/***************ǰ��******************/
	else if((key2)&(!key3)&(!key4))
	{
		memorynum = countnum;
		while((countnum < (memorynum + 35))&(!key4)&(!key3))
		{
			if(key1 == 1)	car_freedom(-97,-97);
			else car_freedom(-47,-97);
		}
		while((countnum < (memorynum + 90))&(!key4)&(!key3))
		{
			if(key1 == 1)	car_freedom(-97,-97);
			else car_freedom(-50,-77);
		}
		
		if((key3)&(!key2))
		{
			if(key4)
			{
				car_freedom(85,97);
				Delay_memory(21);
			}
			else
			{
				car_freedom(-80,95);
				Delay_memory(23);
			}
			car_freedom(50,50);
			Delay_memory(12);		
		}
		else
		{
			//car_freedom(0,0);
			car_freedom(-47,-50);
			OSTimeDly(1);
		}
		//car_freedom(0,0);
		OSTimeDly(1);
	}
	
	/***************����******************/
	else if((key3)&(!key1)&(!key2))
	{
		memorynum = countnum;
		while((countnum < (memorynum + 35))&(!key1)&(!key2))
		{
			if(key4 == 1)	car_freedom(97,97);
			else car_freedom(47,97);
		}
		while((countnum < (memorynum + 90))&(!key1)&(!key2))
		{
			if(key4 == 1)	car_freedom(97,97);
			else car_freedom(50,77);
		}	
		
		if((key2)&(!key3))
		{
			if(key1)
			{
				car_freedom(-85,-97);
				Delay_memory(21);
			}
			else
			{
				car_freedom(81,-96);
				Delay_memory(22);
			}
			car_freedom(-50,-50);
			Delay_memory(12);
		}
		else
		{
			//car_freedom(0,0);
			car_freedom(47,50);
			OSTimeDly(1);
		}
		//car_freedom(0,0);
		OSTimeDly(1);
	}
	
	/***************����******************/
	else if((key4)&(!key1)&(!key2))
	{
		memorynum = countnum;
		while((countnum < (memorynum + 35))&(!key1)&(!key2))
		{
			if(key3 == 1)	car_freedom(97,97);
			else car_freedom(97,47);
		}
		while((!key1)&(!key2)&(countnum < (memorynum + 90)))
		{
			if(key3 == 1)	car_freedom(97,97);
			else if(!key1) car_freedom(77,50);
		}
		
		if((key1)&(!key4))
		{
			if(key2)
			{
				car_freedom(-97,-85);
				Delay_memory(21);
			}
			else
			{
				if(!key4)
				{
					car_freedom(-95,80);
					Delay_memory(23);
				}
				else
				{
						car_freedom(-90,80);
						Delay_memory(24);
				}
			}
			car_freedom(-50,-50);
			Delay_memory(12);
		}
		else
		{
			//car_freedom(0,0);
			car_freedom(50,47);
			OSTimeDly(1);
		}
		//car_freedom(0,0);
		OSTimeDly(1);
	}
	else if((key4)&(key1))
	{
		car_freedom(-80,95);
		Delay_memory(23);
		
		car_freedom(-50,-50);
		Delay_memory(12);
	}
	else if((key2)&(key3))
	{
		car_freedom(95,-80);
		Delay_memory(21);
		
		car_freedom(-50,-50);
		Delay_memory(12);
	}
	
	else if((key2)&(key1))
	{
		car_freedom(-97,-97);
		Delay_memory(30);
		
		car_freedom(-50,-50);
		Delay_memory(12);
	}
	else if((key4)&(key3))
	{
		car_freedom(97,97);
		Delay_memory(30);
		
		car_freedom(50,50);
		Delay_memory(12);
	}
	else
	{
		car_freedom(0,0);
		OSTimeDly(1);
	}
		
}


void car_safe2(void)
{		
// 	if(key_Special_front)
// 	{
// 		memorynum = countnum;
// 		while((countnum < (memorynum + 30))|(key_Special_front))
// 		{
// 			car_freedom(-97,-97);
// 		}
// 	}
// 	else if (key_Special_back)
// 	{
// 		memorynum = countnum;
// 		while((countnum < (memorynum + 30))|(key_Special_back))
// 		{
// 			car_freedom(97,97);
// 		}
// 	}
	
	/***************ǰ��******************/
	if ((key1)&(!key3)&(!key4))
	{
		memorynum = countnum;
		while((countnum < (memorynum + 35))&(!key4)&(!key3))
		{
			if(key2 == 1)	car_freedom(-97,-97);
			else car_freedom(-97,-47);
		}
		while((countnum < (memorynum + 50))&(!key4)&(!key3))
		{
			if(key2 == 1)	car_freedom(-97,-97);
			else car_freedom(-97,-90);
		}
		memorynum = 0;
		
		
		if((key4)&(!key1))
		{
			if(key3)
			{
// 				car_freedom(97,85);
// 				Delay_memory(21);
			}
			else
			{
				car_freedom(95,-80);
				Delay_memory(23);
			}
			car_freedom(50,50);
			Delay_memory(12);
		}
		else
		{
			//car_freedom(0,0);
			car_freedom(-50,-47);
			OSTimeDly(1);
		}
		//car_freedom(0,0);
		OSTimeDly(1);
	}
	/***************ǰ��******************/
	else if((key2)&(!key3)&(!key4))
	{
		memorynum = countnum;
		while((countnum < (memorynum + 35))&(!key4)&(!key3))
		{
			if(key1 == 1)	car_freedom(-97,-97);
			else car_freedom(-47,-97);
		}
		while((countnum < (memorynum + 50))&(!key4)&(!key3))
		{
			if(key1 == 1)	car_freedom(-97,-97);
			else car_freedom(-90,-97);
		}
			memorynum = 0;
		
		
		if((key3)&(!key2))
		{
			if(key4)
			{
// 				car_freedom(85,97);
// 				Delay_memory(21);
			}
			else
			{
				car_freedom(-80,95);
				Delay_memory(23);
			}
			car_freedom(50,50);
			Delay_memory(12);		
		}
		else
		{
			//car_freedom(0,0);
			car_freedom(-47,-50);
			OSTimeDly(1);
		}
		//car_freedom(0,0);
		OSTimeDly(1);
	}
	
	/***************����******************/
	else if((key3)&(!key1)&(!key2))
	{
		memorynum = countnum;
		while((countnum < (memorynum + 35))&(!key1)&(!key2))
		{
			if(key4 == 1)	car_freedom(97,97);
			else car_freedom(47,97);
		}
		while((countnum < (memorynum + 50))&(!key1)&(!key2))
		{
			if(key4 == 1)	car_freedom(97,97);
			else car_freedom(90,97);
		}
			memorynum = 0;
		
		
		if((key2)&(!key3))
		{
			if(key1)
			{
				car_freedom(-85,-97);
				Delay_memory(21);
			}
			else
			{
				car_freedom(81,-96);
				Delay_memory(22);
			}
			car_freedom(-50,-50);
			Delay_memory(12);
		}
		else
		{
			//car_freedom(0,0);
			car_freedom(47,50);
			OSTimeDly(1);
		}
		//car_freedom(0,0);
		OSTimeDly(1);
	}
	
	/***************����******************/
	else if((key4)&(!key1)&(!key2))
	{
		memorynum = countnum;
		while((countnum < (memorynum + 35))&(!key1)&(!key2))
		{
			if(key3 == 1)	car_freedom(97,97);
			else car_freedom(97,47);
		}
		while((!key1)&(!key2)&(countnum < (memorynum + 50)))
		{
			if(key3 == 1)	car_freedom(97,97);
			else if(!key1) car_freedom(97,90);
		}
		memorynum = 0;
		
		if((key1)&(!key4))
		{
			if(key2)
			{
				car_freedom(-97,-85);
				Delay_memory(21);
			}
			else
			{
				if(!key4)
				{
					car_freedom(-95,80);
					Delay_memory(23);
				}
				else
				{
						car_freedom(-90,80);
						Delay_memory(23);
				}
			}
			car_freedom(-50,-50);
			Delay_memory(12);
		}
		else
		{
			//car_freedom(0,0);
			car_freedom(50,47);
			OSTimeDly(1);
		}
		//car_freedom(0,0);
		OSTimeDly(1);
	}
	else if((key4)&(key1))
	{
		car_freedom(-80,95);
		Delay_memory(23);
		
		car_freedom(-50,-50);
		Delay_memory(12);
	}
	else if((key2)&(key3))
	{
		car_freedom(95,-80);
		Delay_memory(21);
		
		car_freedom(-50,-50);
		Delay_memory(12);
	}
	
	else if((key2)&(key1))
	{
		car_freedom(-97,-97);
		Delay_memory(30);
		
		car_freedom(-50,-50);
		Delay_memory(12);
	}
	else if((key4)&(key3))
	{
		car_freedom(97,97);
		Delay_memory(30);
		
		car_freedom(-50,-50);
		Delay_memory(12);
	}
	else
	{
		//car_freedom(0,0);
		OSTimeDly(1);
	}
		
}


