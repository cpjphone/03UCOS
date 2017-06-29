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
//#define GLOBALS

#include "includes.h"

//OS_EVENT  *MsgQueue;				 //������Ϣ����ָ��
//void *MsgQueueTbl[20];				 //������Ϣָ�����飬���г���Ϊ 20

int temp;

/************************************************************************/
//���������ջ
/************************************************************************/
static OS_STK AppTaskStartStk[APP_TASK_START_STK_SIZE];		  
												   //��������������
static OS_STK AppTaskUserIFStk[APP_TASK_USER_IF_STK_SIZE];
												   //��������
static OS_STK AppTaskKbdStk[APP_TASK_KBD_STK_SIZE];
												   //����������
static  OS_STK Task_Com1Stk[Task_Com1_STK_SIZE];
													 //��������
static OS_STK SignalStk[Signal_STK_SIZE];

static OS_STK Task_Led1Stk[Task_Led1_STK_SIZE];
													 //LED ����


/************************************************************************/
//��������
/************************************************************************/
static void AppTaskCreate(void);		//���񴴽�����
static void AppTaskStart(void *p_arg);	//��������
static void AppTaskUserIF(void *p_arg);	//��������
static void AppTaskKbd(void *p_arg);	//����������
static  void Task_Com1(void* p_arg);
static  void Signal(void* p_arg);//��Ϣ�ɼ�����

void MainTask(void) ;
void GSM(void) ;
void ReadDHT11(void);

static  void Task_Led1(void* p_arg);

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
                                                                         
	AppTaskCreate();                                                                    
	while(DEF_TRUE)
	{  
//		OSQPost(MsgQueue,(void *)&one); 	  
//		OSTimeDlyHMSM(0, 0,1, 0);
//		OSQPost(MsgQueue,(void *)&two); 	  
//		OSTimeDlyHMSM(0, 0,0, 500);	
		//GPIO_ResetBits(GPIOC,GPIO_Pin_7);	
		//GPIO_ResetBits(GPIOC,GPIO_Pin_6);	
		//GPIO_Write(GPIOC,0x0000);	
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
//  MsgQueue=OSQCreate(&MsgQueueTbl[0],20);		                 //������Ϣ����

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
										
//����1���ռ���������---------------------------------------------------------    
   OSTaskCreateExt(Task_Com1,									  //ָ����������ָ��
										(void *)0,									  //����ʼִ��ʱ�����ݸ�����Ĳ�����ָ��
										(OS_STK *)&Task_Com1Stk[Task_Com1_STK_SIZE-1],//���������Ķ�ջ��ջ��ָ��   �Ӷ����µݼ�
										Task_Com1_PRIO,								  //�������������ȼ�
										Task_Com1_PRIO,								  //Ԥ�����Ժ�汾�������ʶ���������а汾ͬ�������ȼ�
										(OS_STK *)&Task_Com1Stk[0],					  //ָ�������ջջ�׵�ָ�룬���ڶ�ջ�ļ���
										Task_Com1_STK_SIZE,							  //ָ����ջ�����������ڶ�ջ�ļ���
										(void *)0,									  //ָ���û����ӵ��������ָ�룬������չ�����������ƿ�
										OS_TASK_OPT_STK_CHK|OS_TASK_OPT_STK_CLR);	  //ѡ�ָ���Ƿ������ջ���飬�Ƿ񽫶�ջ��0,�����Ƿ�Ҫ���и�������ȵȡ�
   
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
		OSTimeDlyHMSM(0,0,0,5);   // �����ʱ�ز�����OSTimeDly
		OSTimeDly(50);
		GUI_TOUCH_Exec(); 		   // GUI_TOUCH_Exec ()�����ؼ��Ӻ�ˢ�´�����,��ʱ10ms���ȡһ�δ�������
//	
		if(tick&0x10)
		{	
			GPIOC ->ODR ^= GPIO_Pin_6|GPIO_Pin_7;          //6��7ȡ��
			tick = 0;		   
			temp++;
			if(temp >100)temp = 0;
//			//GPIO_SetBits(GPIOC,GPIO_Pin_6);		 				   // ��1��
//			GPIO_ResetBits(GPIOC,GPIO_Pin_7);						   // ��0��
//			
		}
	}
}

/************************************************************************/
//COM1��������
/************************************************************************/
static  void Task_Com1(void *p_arg)
{    
	INT8U err;	
	(void)p_arg;	  				  
	while(1)
	{
			GSM();
	} 
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
		 ReadDHT11();
		 //OSTimeDlyHMSM(0,0,0,70);
// 		OSTimeDlyHMSM(0,0,0,100);
// 		//ReadDHT11();
// 	//	wait(1.5);
// 		GPIO_SetBits(GPIOC,GPIO_Pin_6);	
// 		OSTimeDlyHMSM(0,0,0,100);
// 	//	wait(1.5);
//   //  GPIO_ResetBits(GPIOC,GPIO_Pin_6);			
// 		OSTaskDel(OS_PRIO_SELF);
	} 
}
/************************************************************************/
//LED1��˸����
/************************************************************************/
static  void Task_Led1(void* p_arg)
{
	INT8U err;
//	INT8U *msg;
	(void) p_arg;	    
	while (1)
	{
	
	}
}

