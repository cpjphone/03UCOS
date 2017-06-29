/*********************************************************************************      
* 【语    言】：C语言
* 【编译环境】：Keil4  
* 【程序功能】：通过uCOS_GUI，一个按键控制LED灯亮灭
* 【技术支持】：uCOS_GUI 核				
* 【晶    振】: RCC 8*9=72MHz		
* 【芯    片】: stm32f103c8 
* 【日    期】: 2013/12/12
* 【修改日期】: 
* 【作    者】: Phone
* 【编程理念】: 死东西活用，活东西套用。
*********************************************************************************/
//#define GLOBALS

#include "includes.h"

//OS_EVENT  *MsgQueue;				 //定义消息队列指针
//void *MsgQueueTbl[20];				 //定义消息指针数组，队列长度为 20

int temp;

/************************************************************************/
//开辟任务堆栈
/************************************************************************/
static OS_STK AppTaskStartStk[APP_TASK_START_STK_SIZE];		  
												   //启动任务（主任务）
static OS_STK AppTaskUserIFStk[APP_TASK_USER_IF_STK_SIZE];
												   //界面任务
static OS_STK AppTaskKbdStk[APP_TASK_KBD_STK_SIZE];
												   //触摸屏任务
static  OS_STK Task_Com1Stk[Task_Com1_STK_SIZE];
													 //串口任务
static OS_STK SignalStk[Signal_STK_SIZE];

static OS_STK Task_Led1Stk[Task_Led1_STK_SIZE];
													 //LED 任务


/************************************************************************/
//函数声明
/************************************************************************/
static void AppTaskCreate(void);		//任务创建函数
static void AppTaskStart(void *p_arg);	//启动任务
static void AppTaskUserIF(void *p_arg);	//界面任务
static void AppTaskKbd(void *p_arg);	//触摸屏任务
static  void Task_Com1(void* p_arg);
static  void Signal(void* p_arg);//信息采集任务

void MainTask(void) ;
void GSM(void) ;
void ReadDHT11(void);

static  void Task_Led1(void* p_arg);

#define LED_LED1_ON()   GPIO_SetBits(GPIOC, GPIO_Pin_6 );  	       //LED1  亮
#define LED_LED1_OFF()  GPIO_ResetBits(GPIOC, GPIO_Pin_6 ); 	   //LED1  灭

#define LED_LED2_ON()   GPIO_SetBits(GPIOC, GPIO_Pin_7 );  	       //LED1  亮
#define LED_LED2_OFF()  GPIO_ResetBits(GPIOC, GPIO_Pin_7 ); 	   //LED1  灭

/************************************************************************/
//CPU延时函数声明
/************************************************************************/
void Delay(unsigned int Dly)
{
  while(Dly--);
}

/************************************************************************/
//主函数
/************************************************************************/
int  main (void)
{
 	INT8U  err;	
	/* Set the Vector Table base location at 0x08000000,禁止所有中断 */ 

 	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);  
	/*设置向量表的位置和偏移与前者相比多一个头文件("stm32f10x_nvic.h") */ 
	                  
	OSInit();				
	/*操作系统初始化函数 (硬件平台初始化)*/

	OSTaskCreateExt(AppTaskStart,(void *)0,
					(OS_STK *)&AppTaskStartStk[APP_TASK_START_STK_SIZE-1],
					APP_TASK_START_PRIO,APP_TASK_START_PRIO,
					(OS_STK *)&AppTaskStartStk[0],APP_TASK_START_STK_SIZE,
					(void *)0,OS_TASK_OPT_STK_CHK|OS_TASK_OPT_STK_CLR);	
																  
	#if (OS_TASK_NAME_SIZE > 13)
	    OSTaskNameSet(APP_TASK_START_PRIO, "Start Task", &err);
	#endif													    
	/*这样写 任务的稳定性更高*/

	OSTimeSet(0);			 //ucosII的节拍计数器清0    节拍计数器是0-4294967295  
    OSStart();               //启动系统初始化函数
	return (0); 	  
}

/************************************************************************/
//启动任务函数
/************************************************************************/

static  void  AppTaskStart (void *p_arg)
{
	
	
	(void)p_arg;			
	BSP_Init(); 
	
#if (OS_TASK_STAT_EN > 0)

	OSStatInit();                			//----统计任务初始化函数                                 
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
		OSTaskDel(OS_PRIO_SELF);			//删除任务
		//OSTimeDlyHMSM(0, 0, 0, 1000);
	}
}

/************************************************************************/
//创建其他任务函数
/************************************************************************/

static  void  AppTaskCreate(void)
{
  INT8U  err;
//  MsgQueue=OSQCreate(&MsgQueueTbl[0],20);		                 //建立消息队列

  OSTaskCreateExt(AppTaskUserIF,(void *)0,(OS_STK *)&AppTaskUserIFStk[APP_TASK_USER_IF_STK_SIZE-1],APP_TASK_USER_IF_PRIO,APP_TASK_USER_IF_PRIO,(OS_STK *)&AppTaskUserIFStk[0],
                    APP_TASK_USER_IF_STK_SIZE,
                    (void *)0,
                    OS_TASK_OPT_STK_CHK|OS_TASK_OPT_STK_CLR); //界面任务


#if (OS_TASK_NAME_SIZE > 8)
  OSTaskNameSet(APP_TASK_USER_IF_PRIO, "User I/F", &err);
#endif


  OSTaskCreateExt(AppTaskKbd,(void *)0,(OS_STK *)&AppTaskKbdStk[APP_TASK_KBD_STK_SIZE-1],APP_TASK_KBD_PRIO,APP_TASK_KBD_PRIO,(OS_STK *)&AppTaskKbdStk[0],
                    APP_TASK_KBD_STK_SIZE,
                    (void *)0,
                    OS_TASK_OPT_STK_CHK|OS_TASK_OPT_STK_CLR); //触摸屏任务

#if (OS_TASK_NAME_SIZE > 8)
  OSTaskNameSet(APP_TASK_KBD_PRIO, "Keyboard", &err);
#endif

//LED1 闪烁任务------------------------------------------------------
   OSTaskCreateExt(Task_Led1,(void *)0,(OS_STK *)&Task_Led1Stk[Task_Led1_STK_SIZE-1],Task_Led1_PRIO,Task_Led1_PRIO,(OS_STK *)&Task_Led1Stk[0],
                    Task_Led1_STK_SIZE,
                    (void *)0,
                    OS_TASK_OPT_STK_CHK|OS_TASK_OPT_STK_CLR);
										
//串口1接收及发送任务---------------------------------------------------------    
   OSTaskCreateExt(Task_Com1,									  //指向任务代码的指针
										(void *)0,									  //任务开始执行时，传递给任务的参数的指针
										(OS_STK *)&Task_Com1Stk[Task_Com1_STK_SIZE-1],//分配给任务的堆栈的栈顶指针   从顶向下递减
										Task_Com1_PRIO,								  //分配给任务的优先级
										Task_Com1_PRIO,								  //预备给以后版本的特殊标识符，在现行版本同任务优先级
										(OS_STK *)&Task_Com1Stk[0],					  //指向任务堆栈栈底的指针，用于堆栈的检验
										Task_Com1_STK_SIZE,							  //指定堆栈的容量，用于堆栈的检验
										(void *)0,									  //指向用户附加的数据域的指针，用来扩展任务的任务控制块
										OS_TASK_OPT_STK_CHK|OS_TASK_OPT_STK_CLR);	  //选项，指定是否允许堆栈检验，是否将堆栈清0,任务是否要进行浮点运算等等。
   
//信息采集任务---------------------------------------------------------    
   OSTaskCreateExt(Signal,									  //指向任务代码的指针
										(void *)0,									  //任务开始执行时，传递给任务的参数的指针
										(OS_STK *)&SignalStk[Signal_STK_SIZE-1],//分配给任务的堆栈的栈顶指针   从顶向下递减
										Signal_PRIO,								  //分配给任务的优先级
										Signal_PRIO,								  //预备给以后版本的特殊标识符，在现行版本同任务优先级
										(OS_STK *)&SignalStk[0],					  //指向任务堆栈栈底的指针，用于堆栈的检验
										Signal_STK_SIZE,							  //指定堆栈的容量，用于堆栈的检验
										(void *)0,									  //指向用户附加的数据域的指针，用来扩展任务的任务控制块
										OS_TASK_OPT_STK_CHK|OS_TASK_OPT_STK_CLR);
}


/************************************************************************/
//界面任务函数
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
//触摸屏任务函数
/************************************************************************/

static  void  AppTaskKbd (void *p_arg)
{
	u8 tick=0;
	(void)p_arg;
	  
	while(DEF_TRUE) 
	{
		tick++;	 
		OSTimeDlyHMSM(0,0,0,5);   // ☆此延时必不可少OSTimeDly
		OSTimeDly(50);
		GUI_TOUCH_Exec(); 		   // GUI_TOUCH_Exec ()连续地监视和刷新触摸板,延时10ms会读取一次触摸坐标
//	
		if(tick&0x10)
		{	
			GPIOC ->ODR ^= GPIO_Pin_6|GPIO_Pin_7;          //6、7取反
			tick = 0;		   
			temp++;
			if(temp >100)temp = 0;
//			//GPIO_SetBits(GPIOC,GPIO_Pin_6);		 				   // “1”
//			GPIO_ResetBits(GPIOC,GPIO_Pin_7);						   // “0”
//			
		}
	}
}

/************************************************************************/
//COM1处理任务
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
//信息采集任务
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
//LED1闪烁任务
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

