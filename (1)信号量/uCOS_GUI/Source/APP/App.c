/*********************************************************************************      
* ����    �ԡ���C����
* �����뻷������Keil4  
* �������ܡ���ͨ��uCOS_GUI��һ����������LED������
* ������֧�֡���uCOS_GUI ��				
* ����    ��: RCC 8*9=72MHz		
* ��о    Ƭ��: stm32f103c8 
* ����    �ڡ�: 2013/12/12
* ���޸����ڡ�: 
* ����    �ߡ�: Phone
* ��������: ���������ã�������á�
*********************************************************************************/

#include "includes.h"

OS_EVENT* Led_on_SEM;
OS_EVENT* Led_off_SEM;

/************************************************************************/
//���������ջ
/************************************************************************/
static OS_STK AppTaskStartStk[APP_TASK_START_STK_SIZE];		  
												   //��������������
static OS_STK AppTaskUserIFStk[APP_TASK_USER_IF_STK_SIZE];
												   //��������
static OS_STK AppTaskKbdStk[APP_TASK_KBD_STK_SIZE];
												   //����������
static OS_STK Task_Led1Stk[Task_Led1_STK_SIZE];


/************************************************************************/
//��������
/************************************************************************/
static void AppTaskCreate(void);		//���񴴽�����
static void AppTaskStart(void *p_arg);	//��������
static void AppTaskUserIF(void *p_arg);	//��������
static void AppTaskKbd(void *p_arg);	//����������
void MainTask(void) ;
static  void Task_Led1(void* p_arg);

#define LED_LED1_ON()   GPIO_SetBits(GPIOC, GPIO_Pin_6 );  	       //LED1  ��
#define LED_LED1_OFF()  GPIO_ResetBits(GPIOC, GPIO_Pin_6 ); 	   //LED1  ��

#define LED_LED2_ON()   GPIO_SetBits(GPIOC, GPIO_Pin_7 );  	       //LED1  ��

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
                                                                         
	AppTaskCreate();                                                                    
	while(DEF_TRUE)
	{  
		OSTaskDel(OS_PRIO_SELF);			//ɾ������
		//OSTimeDlyHMSM(0, 0, 0, 1000);
	}
}

/************************************************************************/
//��������������
/************************************************************************/

static  void  AppTaskCreate(void)
{
  INT8U  err;

  Led_on_SEM=OSSemCreate(1);		                 //����Led1���ź��� 
  Led_off_SEM=OSSemCreate(1);		                 //����Led1���ź��� 

  OSTaskCreateExt(AppTaskUserIF,(void *)0,(OS_STK *)&AppTaskUserIFStk[APP_TASK_USER_IF_STK_SIZE-1],APP_TASK_USER_IF_PRIO,APP_TASK_USER_IF_PRIO,(OS_STK *)&AppTaskUserIFStk[0],
                    APP_TASK_USER_IF_STK_SIZE,
                    (void *)0,
                    OS_TASK_OPT_STK_CHK|OS_TASK_OPT_STK_CLR); //��������


#if (OS_TASK_NAME_SIZE > 8)
  OSTaskNameSet(APP_TASK_USER_IF_PRIO, "User I/F", &err);
#endif


  OSTaskCreateExt(AppTaskKbd,(void *)0,(OS_STK *)&AppTaskKbdStk[APP_TASK_KBD_STK_SIZE-1],APP_TASK_KBD_PRIO,APP_TASK_KBD_PRIO,(OS_STK *)&AppTaskKbdStk[0],
                    APP_TASK_KBD_STK_SIZE,
                    (void *)0,
                    OS_TASK_OPT_STK_CHK|OS_TASK_OPT_STK_CLR); //����������

#if (OS_TASK_NAME_SIZE > 8)
  OSTaskNameSet(APP_TASK_KBD_PRIO, "Keyboard", &err);
#endif

//LED1 ��˸����------------------------------------------------------
   OSTaskCreateExt(Task_Led1,(void *)0,(OS_STK *)&Task_Led1Stk[Task_Led1_STK_SIZE-1],Task_Led1_PRIO,Task_Led1_PRIO,(OS_STK *)&Task_Led1Stk[0],
                    Task_Led1_STK_SIZE,
                    (void *)0,
                    OS_TASK_OPT_STK_CHK|OS_TASK_OPT_STK_CLR);
}


/************************************************************************/
//����������
/************************************************************************/

static  void  AppTaskUserIF (void *p_arg)
{
 
 (void)p_arg;
  while(DEF_TRUE) 
    {
		MainTask() ;

    }
}

/************************************************************************/
//������������
/************************************************************************/

static  void  AppTaskKbd (void *p_arg)
{
	u8 tick=0;
	(void)p_arg;
	  
	while(DEF_TRUE) 
	{
		tick++;	 
		OSTimeDlyHMSM(0,0,0,5);   // �����ʱ�ز�����
		GUI_TOUCH_Exec(); 		   // GUI_TOUCH_Exec ()�����ؼ��Ӻ�ˢ�´�����,��ʱ10ms���ȡһ�δ�������
	
		if(tick&0x10)
		{	
			//GPIOC ->ODR ^= GPIO_Pin_6|GPIO_Pin_7; tick = 0;		   //6��7ȡ��
			//GPIO_SetBits(GPIOC,GPIO_Pin_6);		 				   // ��1��
			GPIO_ResetBits(GPIOC,GPIO_Pin_7);						   // ��0��
			
		}
	}
}

//LED1��˸����----------------------------------------
static  void Task_Led1(void* p_arg)
{
	INT8U err;
	(void) p_arg;
		    
	while (1)
	{	
		GPIO_ResetBits(GPIOC,GPIO_Pin_6); 
		OSSemPend(Led_off_SEM,0,&err); 		           //�ȴ�Led1�ź���  
		LED_LED1_OFF();
		OSSemPend(Led_on_SEM,0,&err); 		           //�ȴ�Led1�ź���  
		LED_LED1_ON();   
		OSTimeDlyHMSM(0, 0,0,500);    

		/*�ź�����⣺��1����ֹͣ�ڵȴ��ź�����䴦�����³����ݲ����У�
		��2�������ź����Ĵ��������Լ����������´����������Ѿ������˵�*/
		    
	}
}

