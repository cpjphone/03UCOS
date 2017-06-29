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

//OS_EVENT  *MsgQueue;				 //������Ϣ����ָ��
//void *MsgQueueTbl[20];				 //������Ϣָ�����飬���г���Ϊ 20



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


/************************************************************************/
//��������
/************************************************************************/
static void AppTaskCreate(void);		//���񴴽�����

static void AppTaskStart(void *p_arg);	//��������
static  void Signal(void* p_arg);//��Ϣ�ɼ�����
static  void Task_Led1(void* p_arg);
static  void Task_Led2(void* p_arg);

void car_forward(u16 led0pwmval);
void car_backwards(u16 led0pwmval);
void car_left(u16 led0pwmvalone,u16 led0pwmvaltwo);
void car_right(u16 led0pwmvalone,u16 led0pwmvaltwo);
void car_freedom(signed char led0pwmvalone,signed char led0pwmvaltwo);
void car_safe(void);
void attack(void);




#define LED_LED1_ON()   GPIO_SetBits(GPIOC, GPIO_Pin_6 );  	       //LED1  ��
#define LED_LED1_OFF()  GPIO_ResetBits(GPIOC, GPIO_Pin_6 ); 	   //LED1  ��

#define LED_LED2_ON()   GPIO_SetBits(GPIOC, GPIO_Pin_7 );  	       //LED1  ��
#define LED_LED2_OFF()  GPIO_ResetBits(GPIOC, GPIO_Pin_7 ); 	   //LED1  ��

/************************************************************************/
//CPU��ʱ��������
/************************************************************************/
void Delay(unsigned int Dly)
{
  while(Dly--);
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
                                                    
	
	                                                                   
	while(DEF_TRUE)
	{  
		
		car_freedom(95,86);
		OSTimeDlyHMSM(0, 0,2,500);
		//Delay(0x7ffffff); //500ms
		car_freedom(0,0);
		AppTaskCreate(); 
 		OSTaskDel(OS_PRIO_SELF);			//ɾ������
// 		OSTaskSuspend (OS_PRIO_SELF);
//		OSQPost(MsgQueue,(void *)&one); 	  
//		OSTimeDlyHMSM(0, 0,1, 0);
//		OSQPost(MsgQueue,(void *)&two); 	  
//		OSTimeDlyHMSM(0, 0,0, 500);	
		//GPIO_ResetBits(GPIOC,GPIO_Pin_7);	
		//GPIO_ResetBits(GPIOC,GPIO_Pin_6);	
		//GPIO_Write(GPIOC,0x0000);	
		//OSTaskDelReq(OS_PRIO_SELF);
		//OSTaskDel(OS_PRIO_SELF);			//ɾ������
// 		while(1)	
//  		OSTimeDlyHMSM(0, 0, 20, 500);
// 		OSTimeDlyHMSM(0, 0, 0, 500);
// 		OSTimeDlyHMSM(0, 0, 0, 500);
		
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
		//car_safe();
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
		
		//attack();
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
		
//  		car_freedom(60,40); 
//  		OSTimeDlyHMSM(0,0,1,80);
//  		car_freedom(-40,-60); 
		OSTimeDlyHMSM(0,0,1,80);
	
	}
}

