/*********************************************************************************      
* 【语    言】：C语言
* 【编译环境】：Keil4  
* 【程序功能】：通过uCOS_GUI，一个按键控制LED灯亮灭
* 【技术支持】：uCOS_GUI 核				
* 【晶    振】: RCC 8*9=72MHz		
* 【芯    片】: stm32f103c8 
* 【日    期】: 2014/05/03
* 【修改日期】: 
* 【作    者】: Phone
* 【编程理念】: 死东西活用，活东西套用。
*********************************************************************************/
//#define GLOBALS

#include "includes.h"
#define key1  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_11)		  //前左
#define key2  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_12)		  //前右
#define key3  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_13)		  //后右
#define key4  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_10)		  //后左

#define key_front   GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_0)		  //前
#define key_back    GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2)		  //后
#define key_left1   GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_3)		  //左
#define key_right1  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_1)		  //右
#define key_left2   GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_9)		  //左
#define key_right2  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_8)		  //右

#define key_FL  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_7)		  //前左
#define key_FR  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_4)		  //前右
#define key_BL  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_6)		  //后左
#define key_BR  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_5)		  //后右

#define key_Special_front  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_9)		  //后右
#define key_Special_back   GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)		  //后左

//OS_EVENT  *MsgQueue;				 //定义消息队列指针
//void *MsgQueueTbl[20];				 //定义消息指针数组，队列长度为 20
u32 countnum,memorynum;



/************************************************************************/
//开辟任务堆栈
/************************************************************************/
static OS_STK AppTaskStartStk[APP_TASK_START_STK_SIZE];		  
												   //启动任务（主任务）
static OS_STK SignalStk[Signal_STK_SIZE];

static OS_STK Task_Led1Stk[Task_Led1_STK_SIZE];
													 //LED 任务
static OS_STK Task_Led2Stk[Task_Led2_STK_SIZE];
													 //LED 任务
static OS_STK Task_Led3Stk[Task_Led3_STK_SIZE];
//LED 任务


/************************************************************************/
//函数声明
/************************************************************************/
static void AppTaskCreate(void);		//任务创建函数

static void AppTaskStart(void *p_arg);	//启动任务
static  void Signal(void* p_arg);//信息采集任务
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
//CPU延时函数声明
/************************************************************************/
void Delay(unsigned int Dly)
{
  while(Dly--);
}

/************************************************************************/
//CPU记时延时   //最小10ms
/************************************************************************/
void Delay_memory(unsigned int Dly)
{
	memorynum = countnum;
	while(countnum < (memorynum + Dly));
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
 //		OSTaskDel(OS_PRIO_SELF);			//删除任务
// 		OSTaskSuspend (OS_PRIO_SELF);
	}
}

/************************************************************************/
//创建其他任务函数
/************************************************************************/

static  void  AppTaskCreate(void)
{
  INT8U  err;
//  MsgQueue=OSQCreate(&MsgQueueTbl[0],20);		                 //建立消息队列


//LED1 闪烁任务------------------------------------------------------
   OSTaskCreateExt(Task_Led1,(void *)0,(OS_STK *)&Task_Led1Stk[Task_Led1_STK_SIZE-1],Task_Led1_PRIO,Task_Led1_PRIO,(OS_STK *)&Task_Led1Stk[0],
                    Task_Led1_STK_SIZE,
                    (void *)0,
                    OS_TASK_OPT_STK_CHK|OS_TASK_OPT_STK_CLR);
	
//LED2 闪烁任务------------------------------------------------------
   OSTaskCreateExt(Task_Led2,(void *)0,(OS_STK *)&Task_Led2Stk[Task_Led2_STK_SIZE-1],Task_Led2_PRIO,Task_Led2_PRIO,(OS_STK *)&Task_Led2Stk[0],
                    Task_Led2_STK_SIZE,
                    (void *)0,
                    OS_TASK_OPT_STK_CHK|OS_TASK_OPT_STK_CLR);
	
//LED3 闪烁任务------------------------------------------------------
 OSTaskCreateExt(Task_Led3,(void *)0,(OS_STK *)&Task_Led3Stk[Task_Led3_STK_SIZE-1],Task_Led3_PRIO,Task_Led3_PRIO,(OS_STK *)&Task_Led3Stk[0],
									Task_Led3_STK_SIZE,
									(void *)0,
									OS_TASK_OPT_STK_CHK|OS_TASK_OPT_STK_CLR);
									
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
//信息采集任务
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
//LED1闪烁任务
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
//LED2闪烁任务
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
//LED3闪烁任务
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

