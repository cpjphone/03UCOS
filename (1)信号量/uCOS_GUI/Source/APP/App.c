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

#include "includes.h"

OS_EVENT* Led_on_SEM;
OS_EVENT* Led_off_SEM;

/************************************************************************/
//开辟任务堆栈
/************************************************************************/
static OS_STK AppTaskStartStk[APP_TASK_START_STK_SIZE];		  
												   //启动任务（主任务）
static OS_STK AppTaskUserIFStk[APP_TASK_USER_IF_STK_SIZE];
												   //界面任务
static OS_STK AppTaskKbdStk[APP_TASK_KBD_STK_SIZE];
												   //触摸屏任务
static OS_STK Task_Led1Stk[Task_Led1_STK_SIZE];


/************************************************************************/
//函数声明
/************************************************************************/
static void AppTaskCreate(void);		//任务创建函数
static void AppTaskStart(void *p_arg);	//启动任务
static void AppTaskUserIF(void *p_arg);	//界面任务
static void AppTaskKbd(void *p_arg);	//触摸屏任务
void MainTask(void) ;
static  void Task_Led1(void* p_arg);

#define LED_LED1_ON()   GPIO_SetBits(GPIOC, GPIO_Pin_6 );  	       //LED1  亮
#define LED_LED1_OFF()  GPIO_ResetBits(GPIOC, GPIO_Pin_6 ); 	   //LED1  灭

#define LED_LED2_ON()   GPIO_SetBits(GPIOC, GPIO_Pin_7 );  	       //LED1  亮

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

  Led_on_SEM=OSSemCreate(1);		                 //建立Led1的信号量 
  Led_off_SEM=OSSemCreate(1);		                 //建立Led1的信号量 

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
		OSTimeDlyHMSM(0,0,0,5);   // ☆此延时必不可少
		GUI_TOUCH_Exec(); 		   // GUI_TOUCH_Exec ()连续地监视和刷新触摸板,延时10ms会读取一次触摸坐标
	
		if(tick&0x10)
		{	
			//GPIOC ->ODR ^= GPIO_Pin_6|GPIO_Pin_7; tick = 0;		   //6、7取反
			//GPIO_SetBits(GPIOC,GPIO_Pin_6);		 				   // “1”
			GPIO_ResetBits(GPIOC,GPIO_Pin_7);						   // “0”
			
		}
	}
}

//LED1闪烁任务----------------------------------------
static  void Task_Led1(void* p_arg)
{
	INT8U err;
	(void) p_arg;
		    
	while (1)
	{	
		GPIO_ResetBits(GPIOC,GPIO_Pin_6); 
		OSSemPend(Led_off_SEM,0,&err); 		           //等待Led1信号量  
		LED_LED1_OFF();
		OSSemPend(Led_on_SEM,0,&err); 		           //等待Led1信号量  
		LED_LED1_ON();   
		OSTimeDlyHMSM(0, 0,0,500);    

		/*信号量理解：（1）可停止在等待信号量语句处，以下程序暂不运行；
		（2）发送信号量的次数可以自己存起来，下次来临则是已经触发了的*/
		    
	}
}

