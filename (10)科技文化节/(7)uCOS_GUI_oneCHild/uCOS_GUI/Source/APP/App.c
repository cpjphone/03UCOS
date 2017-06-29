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

extern u8 tdata[4];
INT8U cut;
int fire1;
int man1;
extern u8 tdata[4];

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
static  void Task_Led1(void* p_arg);

void MainTask(void) ;
void GSM(void) ;
void wifi(void) ;
void ReadDHT11(void);



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
		//OSTaskDel(OS_PRIO_SELF);			//ɾ������
		
		cut = 2;
		OSTimeDlyHMSM(0, 0, 0, 500);
		cut = 12;
		OSTimeDlyHMSM(0, 0, 0, 500);
		
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
		//OSTimeDly(50);
		GUI_TOUCH_Exec(); 		   // GUI_TOUCH_Exec ()�����ؼ��Ӻ�ˢ�´�����,��ʱ10ms���ȡһ�δ�������
	}
}

/************************************************************************/
//COM1��������
/************************************************************************/
static  void Task_Com1(void *p_arg)
{    
	INT8U err;	
	(void)p_arg;	 
	GPIO_SetBits(GPIOA,GPIO_Pin_1);	
	GPIO_ResetBits(GPIOA,GPIO_Pin_3);	
	while(1)
	{
		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) == 0) 
		{
			fire1 = 1;
		}
		else 
		{
			fire1 = 0;
		}
		GPIO_ResetBits(GPIOA,GPIO_Pin_3);
		OSTimeDlyHMSM(0,0,0,80); 
		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3) == 1) 
		{
			man1 = 1;
		}
		else 
		{
			man1 = 0;
		}
		OSTimeDlyHMSM(0,0,0,500); 
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
	//	wifi();
		// OSTimeDlyHMSM(0,0,0,70);
 		 //OSTimeDlyHMSM(0,0,0,3);
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

	INT8U tmp_buf[33]; 
	INT8U tmp_buf2[33]; 
	int temp1,temp2,temp3,temp4;

	//tmp_buf[0] = 12; 
	// 	tmp_buf[1] = 32; 
	//tdata[2]
	//tmp_buf[5] = 17; 
	// 	tmp_buf[1] = 32; 

	//	INT8U *msg;
	(void) p_arg;	  
	NRF24L01_Init();  
	GPIO_SetBits (GPIOA,GPIO_Pin_11);
	while (1)
	{
		OSTimeDlyHMSM(0,0,0,100);
		while(NRF24L01_Check())//��ⲻ��24L01
		{} 
		
		if (cut > 10)
		{	
			//OSTimeDly(1);
			RX_Mode();			
			OSTimeDlyHMSM(0,0,0,8);
			
			if(NRF24L01_RxPacket(tmp_buf)==0)		//������յ��������,tmp_buf���յ�������
			{
				
				
				temp1=tmp_buf[0];
				temp2=tmp_buf[1];
				// 			temp3=tmp_buf[2];
				// 			temp4=tmp_buf[3];

				if(temp1 == 1)
				{	
					GPIO_ResetBits(GPIOA,GPIO_Pin_11);
					OSTimeDlyHMSM(0,0,0,2);
				}
				else 		
				{
					GPIO_SetBits(GPIOA,GPIO_Pin_11);
					OSTimeDlyHMSM(0,0,0,2);
				}
				
			}
			//OSTimeDlyHMSM(0,0,0,180);
		}
		if (cut < 10)
		{	
			//OSTimeDly(1);
			TX_Mode();
			tmp_buf2[0] = tdata[0]; 
	 	  tmp_buf2[1] = tdata[1];
			
			tmp_buf2[2] = tdata[2]; 
	 	  tmp_buf2[3] = tdata[3];
			
			tmp_buf2[4] = fire1 + 6; 
	 	  tmp_buf2[5] = man1 + 6;

			
// 			tmp_buf2[7] = 0; 
// 	 	  tmp_buf2[8] = 0;
// 		
// 			tmp_buf2[9] = 0; 
// 	 	  tmp_buf2[10] =0;
// 			
// 			tmp_buf2[11] = 0; 
// 	 	  tmp_buf2[12] = 0;

			OSTimeDlyHMSM(0,0,0,8);
			if(NRF24L01_TxPacket(tmp_buf2)==0x10)	//��������ȥ�������tmp_buf�����ȥ������
			
			OSTimeDlyHMSM(0,0,0,2);
// 			GPIO_SetBits (GPIOC,GPIO_Pin_6);
// 			GPIO_SetBits (GPIOC,GPIO_Pin_7);
			
			//GPIO_ResetBits (GPIOA,GPIO_Pin_8);
		}
	}
}

