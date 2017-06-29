/*********************************************************************************      
* ¡¾Óï    ÑÔ¡¿£ºCÓïÑÔ
* ¡¾³ÌÐò¹¦ÄÜ¡¿£º(1):ÏòÇ°¡¢ºó¡¢×ó¡¢ÓÒµÄËÙ¶È·¶Î§ 0µ½100  µÝÔö
*								(2)£º×ÔÓÉº¯ÊýËÙ¶ÈÈ¡Öµ·¶Î§ -100µ½100£¬¸ºÊýÏòºóÕýÊýÏòÇ°£¬Êý×ÖÔ½´óËÙ¶ÈÔ½¿ì
* ¡¾ÈÕ    ÆÚ¡¿: 2014/05/03
* ¡¾×÷    Õß¡¿: Phone
*********************************************************************************/
#include "includes.h"
//#include "math.h"
#define key_front  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_0)		  //Ç°
#define key_back   GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2)		  //ºó

#define key_FL  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_7)		  //Ç°×ó
#define key_FR  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_4)		  //Ç°ÓÒ
#define key_BL  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_6)		  //ºó×ó
#define key_BR  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_5)		  //ºóÓÒ

#define key1  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_11)		  //Ç°×ó
#define key2  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_12)		  //Ç°ÓÒ
#define key3  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_15)		  //ºóÓÒ
#define key4  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_14)		  //ºó×óó

#define key_Special_front  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_9)		  //ºóÓÒ
#define key_Special_back   GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)		  //ºó×ó

#define key_Mirror_front  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)		  //ºó×ó
#define key_Mirror_back   GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)		  //ºóÓÒ


void car_freedom(signed char led0pwmvalone,signed char led0pwmvaltwo);
void Delay_memory(unsigned int Dly);

extern u16 countnum,memorynum;

/************************************************************************/
//×ÔÓÉÅäÖÃ Õý¡ª¡ªÇ°;¸º¡ª¡ªºó
/************************************************************************/

void attack1(void)
{
	
	/*****ÉÏÇ°×ó********/
		if(key_FL == 0)
		{
			car_freedom(-35,90); 	
			OSTimeDlyHMSM(0, 0,0,300);			
			car_freedom(97,97);
			OSTimeDlyHMSM(0, 0,1,0);
		}
		
		/*****ÉÏÇ°ÓÒ********/
		if(key_FR == 0)
		{
			car_freedom(90,-35); 	
			OSTimeDlyHMSM(0, 0,0,300);
			car_freedom(97,97);
			OSTimeDlyHMSM(0, 0,1,0); 
		}
		
			/*****ÉÏºó×ó********/
		if(key_BL == 0)
		{
			car_freedom(-35,-90); 	
			OSTimeDlyHMSM(0, 0,0,300);
			car_freedom(-97,-97);
			OSTimeDlyHMSM(0, 0,1,0); 
		}
		
		/*****ÉÏºóÓÒ********/
		if(key_BR == 0)
		{
			car_freedom(-90,-35); 	
			OSTimeDlyHMSM(0, 0,0,300);
			car_freedom(-97,-97);
			OSTimeDlyHMSM(0, 0,1,0); 
		}
	
	

	 
/**********¾µÃæ************/
		/*****Ç°********/
	
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
	/*****ºó********/
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




