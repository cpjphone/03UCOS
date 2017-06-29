/*********************************************************************************      
* ����    �ԡ���C����
* �����뻷������Keil4  
* �������ܡ���ͨ��uCOS_GUI��һ����������LED������
* ������֧�֡���uCOS_GUI ��				
* ����    ��: RCC 8*9=72MHz		
* ��о    Ƭ��: stm32f103c8 
* ����    �ڡ�: 2014/05/03
* ���޸����ڡ�: 
* ����    �ߡ�: Phone
* ��������: ���������ã�������á�
*********************************************************************************/
//#define GLOBALS

#include "includes.h"
#define key1  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_11)		  //ǰ��
#define key2  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_12)		  //ǰ��
#define key3  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_13)		  //����
#define key4  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_10)		  //����

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

#define key_Special_front  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_9)		  //����
#define key_Special_back   GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)		  //����

//OS_EVENT  *MsgQueue;				 //������Ϣ����ָ��
//void *MsgQueueTbl[20];				 //������Ϣָ�����飬���г���Ϊ 20
u32 countnum,memorynum;



/************************************************************************/
//���������ջ
/************************************************************************/
static OS_STK AppTaskStartStk[APP_TASK_START_STK_SIZE];		  
												   //��������������
static OS_STK SignalStk[Signal_STK_SIZE];

static OS_STK Task_Led1Stk[Task_Led1_STK_SIZE];
													 //LED ����
static OS_STK Task_Led2Stk[Task_Led2_STK_SIZE];
													 //LED ����
static OS_STK Task_Led3Stk[Task_Led3_STK_SIZE];
//LED ����


/************************************************************************/
//��������
/************************************************************************/
static void AppTaskCreate(void);		//���񴴽�����

static void AppTaskStart(void *p_arg);	//��������
static  void Signal(void* p_arg);//��Ϣ�ɼ�����
static  void Task_Led1(void* p_arg);
static  void Task_Led2(void* p_arg);
static  void Task_Led3(void* p_arg);

void car_forward(u16 led0pwmval);
void car_backwards(u16 led0pwmval);
void car_left(u16 led0pwmvalone,u16 led0pwmvaltwo);
void car_right(u16 led0pwmvalone,u16 led0pwmvaltwo);
void car_freedom(signed char led0pwmvalone,signed char led0pwmvaltwo);

void car_safe1(void);
void car_safe2(void);

void attack1(void);
void attack2(void);

void search(void);


/************************************************************************/
//CPU��ʱ��������
/************************************************************************/
void Delay(unsigned int Dly)
{
  while(Dly--);
}

/************************************************************************/
//CPU��ʱ��ʱ   //��С10ms
/************************************************************************/
void Delay_memory(unsigned int Dly)
{
	memorynum = countnum;
	while(countnum < (memorynum + Dly));
}

/************************************************************************/
//������
/************************************************************************/
int  main (void)
{
 	INT8U  err;	
	/* Set the Vector Table base location at 0x08000000,��ֹ�����ж� */ 

 	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);  
	/*�����������λ�ú�ƫ����ǰ����ȶ�һ��ͷ�ļ�("stm32f10x_nvic.h") */ 
	                  
	OSInit();				
	/*����ϵͳ��ʼ������ (Ӳ��ƽ̨��ʼ��)*/

	OSTaskCreateExt(AppTaskStart,(void *)0,
					(OS_STK *)&AppTaskStartStk[APP_TASK_START_STK_SIZE-1],
					APP_TASK_START_PRIO,APP_TASK_START_PRIO,
					(OS_STK *)&AppTaskStartStk[0],APP_TASK_START_STK_SIZE,
					(void *)0,OS_TASK_OPT_STK_CHK|OS_TASK_OPT_STK_CLR);	
																  
	#if (OS_TASK_NAME_SIZE > 13)
	    OSTaskNameSet(APP_TASK_START_PRIO, "Start Task", &err);
	#endif													    
	/*����д ������ȶ��Ը���*/

	OSTimeSet(0);			 //ucosII�Ľ��ļ�������0    ���ļ�������0-4294967295  
    OSStart();               //����ϵͳ��ʼ������
	return (0); 	  
}

/************************************************************************/
//����������
/************************************************************************/

static  void  AppTaskStart (void *p_arg)
{
	
	
	(void)p_arg;			
	BSP_Init(); 
	
#if (OS_TASK_STAT_EN > 0)

	OSStatInit();                			//----ͳ�������ʼ������                                 
#endif  

//  while((key_left1)|(key_left2)|(key_right1)|(key_right2));
// 	car_freedom(96,96);
// 	OSTimeDlyHMSM(0, 0,1,120);   
// 	car_freedom(97,75);
// 	OSTimeDlyHMSM(0, 0,1,100); 
// 	car_freedom(65,97);
// 	OSTimeDlyHMSM(0, 0,0,200); 
// 	
// 	car_freedom(-97,-97);
// 	OSTimeDlyHMSM(0, 0,0,10);
   AppTaskCreate();
//  	car_freedom(0,0);	
// 	car_freedom(40,40);
	while(DEF_TRUE)
	{  
		//Delay(0x7ffffff); //500ms	
		OSTimeDlyHMSM(0,0,0,10);
		countnum++;
		if(countnum > 40000000000) countnum = 0;
 //		OSTaskDel(OS_PRIO_SELF);			//ɾ������
// 		OSTaskSuspend (OS_PRIO_SELF);
	}
}

/************************************************************************/
//��������������
/************************************************************************/

static  void  AppTaskCreate(void)
{
  INT8U  err;
//  MsgQueue=OSQCreate(&MsgQueueTbl[0],20);		                 //������Ϣ����


//LED1 ��˸����------------------------------------------------------
   OSTaskCreateExt(Task_Led1,(void *)0,(OS_STK *)&Task_Led1Stk[Task_Led1_STK_SIZE-1],Task_Led1_PRIO,Task_Led1_PRIO,(OS_STK *)&Task_Led1Stk[0],
                    Task_Led1_STK_SIZE,
                    (void *)0,
                    OS_TASK_OPT_STK_CHK|OS_TASK_OPT_STK_CLR);
	
//LED2 ��˸����------------------------------------------------------
   OSTaskCreateExt(Task_Led2,(void *)0,(OS_STK *)&Task_Led2Stk[Task_Led2_STK_SIZE-1],Task_Led2_PRIO,Task_Led2_PRIO,(OS_STK *)&Task_Led2Stk[0],
                    Task_Led2_STK_SIZE,
                    (void *)0,
                    OS_TASK_OPT_STK_CHK|OS_TASK_OPT_STK_CLR);
	
//LED3 ��˸����------------------------------------------------------
 OSTaskCreateExt(Task_Led3,(void *)0,(OS_STK *)&Task_Led3Stk[Task_Led3_STK_SIZE-1],Task_Led3_PRIO,Task_Led3_PRIO,(OS_STK *)&Task_Led3Stk[0],
									Task_Led3_STK_SIZE,
									(void *)0,
									OS_TASK_OPT_STK_CHK|OS_TASK_OPT_STK_CLR);
									
//��Ϣ�ɼ�����---------------------------------------------------------    
   OSTaskCreateExt(Signal,									  //ָ����������ָ��
										(void *)0,									  //����ʼִ��ʱ�����ݸ�����Ĳ�����ָ��
										(OS_STK *)&SignalStk[Signal_STK_SIZE-1],//���������Ķ�ջ��ջ��ָ��   �Ӷ����µݼ�
										Signal_PRIO,								  //�������������ȼ�
										Signal_PRIO,								  //Ԥ�����Ժ�汾�������ʶ���������а汾ͬ�������ȼ�
										(OS_STK *)&SignalStk[0],					  //ָ�������ջջ�׵�ָ�룬���ڶ�ջ�ļ���
										Signal_STK_SIZE,							  //ָ����ջ�����������ڶ�ջ�ļ���
										(void *)0,									  //ָ���û����ӵ��������ָ�룬������չ�����������ƿ�
										OS_TASK_OPT_STK_CHK|OS_TASK_OPT_STK_CLR);
}

/************************************************************************/
//��Ϣ�ɼ�����
/************************************************************************/
static  void Signal(void *p_arg)
{    
	INT8U err;	
	(void)p_arg;	
	while(1)
	{
		car_safe1();
 		OSTimeDlyHMSM(0,0,0,1);
	} 
}
/************************************************************************/
//LED1��˸����
/************************************************************************/
static  void Task_Led1(void* p_arg)
{
	INT8U err;


	//	INT8U *msg;
//	u8 dir=1;
//	u16 led0pwmval = 0;
	(void) p_arg;	  
	//NRF24L01_Init();  
	while (1)
	{
		
	//  attack1();
		//attack2();
		//car_backwards(50);
		OSTimeDlyHMSM(0,0,0,2);

	}
}


/************************************************************************/
//LED2��˸����
/************************************************************************/
static  void Task_Led2(void* p_arg)
{
	INT8U err;


	//	INT8U *msg;
//	u8 dir=1;
//	u16 led0pwmval = 0;
	(void) p_arg;	  
	//NRF24L01_Init();  
	while (1)
	{
	//	search();
		
//  		car_freedom(80,60); 
//  		OSTimeDlyHMSM(0,0,2,80);
//  		car_freedom(-60,-80); 
		OSTimeDlyHMSM(0,0,0,1);
	
	}
}

/************************************************************************/
//LED3��˸����
/************************************************************************/
static  void Task_Led3(void* p_arg)
{
	INT8U err;


	//	INT8U *msg;
//	u8 dir=1;
//	u16 led0pwmval = 0;
	(void) p_arg;	  
	//NRF24L01_Init();  
	while (1)
	{
// 		if((!key_Special_front)&(!key_Special_back)&(!key1)&(!key2)&(!key3)&(!key4)&(key_front)&(key_back)&(key_left1)&(key_right1)&(key_left2)&(key_right2)&(key_FL)&(key_FR)&(key_BL)&(key_BR))
//  		car_freedom(40,20); 
//  		OSTimeDlyHMSM(0,0,3,0);
// 		if((!key_Special_front)&(!key_Special_back)&(!key1)&(!key2)&(!key3)&(!key4)&(key_front)&(key_back)&(key_left1)&(key_right1)&(key_left2)&(key_right2)&(key_FL)&(key_FR)&(key_BL)&(key_BR))
//  		car_freedom(-20,-40); 
// 		car_freedom(40,40); 
		OSTimeDlyHMSM(0,0,3,0);	
	}
}

