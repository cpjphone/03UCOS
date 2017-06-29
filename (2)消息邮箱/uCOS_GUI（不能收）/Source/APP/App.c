/****************************************************************************
* Copyright (C), 2012 奋斗嵌入式工作室 www.ourstm.com
*
* 本例程在 奋斗版STM32开发板V2,2.1,V3,MINI上调试通过           
* QQ: 9191274, 旺旺：sun68, Email: sun68@163.com 
* 淘宝店铺：ourstm.taobao.com  
*
* 文件名: app.c
* 内容简述:
*       本例程操作系统采用ucos2.86a版本， 建立了5个任务
			任务名											 优先级
			APP_TASK_START_PRIO                               2	        主任务	  		
            Task_Com1_PRIO                                    4			COM1通信任务
            Task_Led1_PRIO                                    7			LED1 闪烁任务
            Task_Led2_PRIO                                    8			LED2 闪烁任务
            Task_Led3_PRIO                                    9			LED3 闪烁任务
		 当然还包含了系统任务：
		    OS_TaskIdle                  空闲任务-----------------优先级最低
			OS_TaskStat                  统计运行时间的任务-------优先级次低
*
  建立一个消息邮箱，通过串口1，将接收到的led闪烁控制信息通过消息邮箱传递给串口接收任务，并修改相应LED的闪烁间隔。
* 文件历史:
* 版本号  日期       作者    说明
* v0.1    2012-11-08 sun68  创建该文件
*
*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/
#define GLOBALS

//#include "stdarg.h"
 
#include "includes.h"
#include "globals.h"

OS_EVENT* Com1_SEM;
OS_EVENT* Com1_MBOX;  

void USART_OUT(USART_TypeDef* USARTx, uint8_t *Data,...);
char *itoa(int value, char *string, int radix);
//extern void fun_para(void);

/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/



/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/

static  OS_STK App_TaskStartStk[APP_TASK_START_STK_SIZE];

static  OS_STK Task_Com1Stk[Task_Com1_STK_SIZE];
static  OS_STK Task_Led1Stk[Task_Led1_STK_SIZE];
static  OS_STK Task_Led2Stk[Task_Led2_STK_SIZE];
static  OS_STK Task_Led3Stk[Task_Led3_STK_SIZE];
		

/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/
static  void App_TaskCreate(void);

static  void App_TaskStart(void* p_arg);

static  void Task_Com1(void* p_arg);
static  void Task_Led1(void* p_arg);
static  void Task_Led2(void* p_arg);
static  void Task_Led3(void* p_arg);

//
//static  void App_TaskJoystick(void* p_arg);
#define LED_LED1_ON()   GPIO_SetBits(GPIOB, GPIO_Pin_5 );  	       //LED1  亮
#define LED_LED1_OFF()  GPIO_ResetBits(GPIOB, GPIO_Pin_5 ); 	   //LED1  灭

#define LED_LED2_ON()   GPIO_SetBits(GPIOD, GPIO_Pin_6 );  	       //LED2  亮
#define LED_LED2_OFF()  GPIO_ResetBits(GPIOD, GPIO_Pin_6 ); 	   //LED2  灭

#define LED_LED3_ON()   GPIO_SetBits(GPIOD, GPIO_Pin_3 );  	       //LED3  亮
#define LED_LED3_OFF()  GPIO_ResetBits(GPIOD, GPIO_Pin_3 ); 	   //LED3  灭
/*
*********************************************************************************************************
*                                                main()
*
* Description : This is the standard entry point for C code.  It is assumed that your code will call
*               main() once you have performed all necessary initialization.
*
* Argument : none.
*
* Return   : none.
*********************************************************************************************************
*/

int main(void)
{
   CPU_INT08U os_err;

   //禁止CPU中断
   CPU_IntDis();
   
   //UCOS 初始化
   OSInit();                                                   /* Initialize "uC/OS-II, The Real-Time Kernel".         */
   
   //硬件平台初始化
   BSP_Init();                                                 /* Initialize BSP functions.  */
   
   //默认LED闪烁间隔500ms
   milsec1=500,milsec2=500,milsec3=500;

   USART_OUT(USART1,"****(C) COPYRIGHT 2010 奋斗嵌入式开发工作室 *******\r\n");    	  //向串口1发送开机字符。
   USART_OUT(USART1,"*                                                 *\r\n");    	
   USART_OUT(USART1,"*         奋斗版STM32开发板 LED闪烁实验           *\r\n");  
   USART_OUT(USART1,"*                                                 *\r\n");    	  	
   USART_OUT(USART1,"*             基于 uCOSII2.86                     *\r\n");    	
   USART_OUT(USART1,"*                                                 *\r\n");    	
   USART_OUT(USART1,"*LED1闪烁间隔：1ms--65535ms  指令L1 1F--L1 65535F *\r\n");    	
   USART_OUT(USART1,"*LED2闪烁间隔：1ms--65535ms  指令L2 1F--L1 65535F *\r\n");    
   USART_OUT(USART1,"*LED3闪烁间隔：1ms--65535ms  指令L3 1F--L1 65535F *\r\n"); 
   USART_OUT(USART1,"*                                                 *\r\n");    	   
   USART_OUT(USART1,"*  奋斗STM32论坛：ourstm.5d6d.com                 *\r\n");   
   USART_OUT(USART1,"*                                                 *\r\n");    	 	
   USART_OUT(USART1,"***************************************************\r\n"); 
   USART_OUT(USART1,"\r\n"); 
   USART_OUT(USART1,"\r\n");    	
   
   //建立主任务， 优先级最高  建立这个任务另外一个用途是为了以后使用统计任务
   os_err = OSTaskCreate((void (*) (void *)) App_TaskStart,	  		  		//指向任务代码的指针
                          (void *) 0,								  		//任务开始执行时，传递给任务的参数的指针
               (OS_STK *) &App_TaskStartStk[APP_TASK_START_STK_SIZE - 1],	//分配给任务的堆栈的栈顶指针   从顶向下递减
               (INT8U) APP_TASK_START_PRIO);								//分配给任务的优先级
   
   //ucos的节拍计数器清0    节拍计数器是0-4294967295    对于节拍频率100hz时， 每隔497天就重新计数 
   OSTimeSet(0);
   OSStart();                                                  /* Start multitasking (i.e. give control to uC/OS-II).  */
                                                 /* Start multitasking (i.e. give control to uC/OS-II).  */
 
   return (0);
}




/*
*********************************************************************************************************
*                                          App_TaskStart()
*
* Description : The startup task.  The uC/OS-II ticker should only be initialize once multitasking starts.
*
* Argument : p_arg       Argument passed to 'App_TaskStart()' by 'OSTaskCreate()'.
*
* Return   : none.
*
* Caller   : This is a task.
*
* Note     : none.
*********************************************************************************************************
*/

static  void App_TaskStart(void* p_arg)
{
   


   (void) p_arg;

   //初始化ucos时钟节拍
   OS_CPU_SysTickInit();                                       /* Initialize the SysTick.       */

//使能ucos 的统计任务
#if (OS_TASK_STAT_EN > 0)
   //----统计任务初始化函数  
   OSStatInit();                                               /* Determine CPU capacity.                              */
#endif
   //建立其他的任务
   App_TaskCreate();

   while (1)
   {
      //1秒一次循环
	  OSTimeDlyHMSM(0, 0,1, 0);

   }
}


//LED1闪烁任务----------------------------------------
static  void Task_Led1(void* p_arg)
{
   


   (void) p_arg;	    
   while (1)
   {
      LED_LED1_ON();
      OSTimeDlyHMSM(0, 0, 0, milsec1);
      
      LED_LED1_OFF();
      OSTimeDlyHMSM(0, 0, 0, milsec1);	
   }
}

//LED2闪烁任务----------------------------------------
static  void Task_Led2(void* p_arg)
{
   


   (void) p_arg;	    
   while (1)
   {
      LED_LED2_ON();
      OSTimeDlyHMSM(0, 0, 0, milsec2);
      
      LED_LED2_OFF();
      OSTimeDlyHMSM(0, 0, 0, milsec2);	
   }
}

//LED3闪烁任务----------------------------------------
static  void Task_Led3(void* p_arg)
{
   


   (void) p_arg;	    
   while (1)
   {
      LED_LED3_ON();
      OSTimeDlyHMSM(0, 0, 0, milsec3);
      
      LED_LED3_OFF();
      OSTimeDlyHMSM(0, 0, 0, milsec3);	
   }
}
/*
*********************************************************************************************************
*                                            App_TaskCreate()
*
* Description : Create the application tasks.
*
* Argument : none.
*
* Return   : none.
*
* Caller   : App_TaskStart().
*
* Note     : none.
*********************************************************************************************************
*/

static  void App_TaskCreate(void)
{
   //CPU_INT08U os_err;
 
   //Com1_SEM=OSSemCreate(1);		     //建立串口1中断的信号量
   Com1_MBOX=OSMboxCreate((void *) 0);		     //建立串口1中断的消息邮箱
   

   
   
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

  
   
}



//++++++++++++COM1处理任务++++++++++++++++++++++++++
static  void Task_Com1(void *p_arg){    
   INT8U err;	
   unsigned char * msg;
   (void)p_arg;	  				  
   while(1){
   	 
      //OSSemPend(Com1_SEM,0,&err); 		  //等待串口接收指令成功的信号量
	  msg=(unsigned char *)OSMboxPend(Com1_MBOX,0,&err); 		  //等待串口接收指令成功的邮箱信息
	  //USART_OUT(USART1,&TxBuffer1[0]);
   	  if(msg[0]=='L'&&msg[1]==0x31){
	  	 milsec1=atoi(&msg[3]);               //LED1 的延时毫秒  (mini and V3)
	     USART_OUT(USART1,"\r\n");
	  	 USART_OUT(USART1,"LED1: %d ms 间隔闪烁",milsec1);		 
	  }
	  else if(msg[0]=='L'&&msg[1]==0x32){
	  	 milsec2=atoi(&msg[3]);		   //LED2 的延时毫秒  (only V3)
		 USART_OUT(USART1,"\r\n");
	  	 USART_OUT(USART1,"LED2: %d ms 间隔闪烁",milsec2);
	  }
	  else if(msg[0]=='L'&&msg[1]==0x33){
	  	  milsec3=atoi(&msg[3]);		   //LED3 的延时毫秒  (only V3)
		  USART_OUT(USART1,"\r\n");
	  	  USART_OUT(USART1,"LED3: %d ms 间隔闪烁",milsec3);
	  } 
   } 
}


int SendChar (int ch)  {                /* Write character to Serial Port     */

  USART_SendData(USART1, (unsigned char) ch);
  while (!(USART1->SR & USART_FLAG_TXE));
  return (ch);
}


/******************************************************
		格式化串口输出函数
        "\r"	回车符	   USART_OUT(USART1, "abcdefg\r")   
		"\n"	换行符	   USART_OUT(USART1, "abcdefg\r\n")
		"%s"	字符串	   USART_OUT(USART1, "字符串是：%s","abcdefg")
		"%d"	十进制	   USART_OUT(USART1, "a=%d",10)
**********************************************************/
void USART_OUT(USART_TypeDef* USARTx, uint8_t *Data,...){ 

	const char *s;
    int d;
   
    char buf[16];
    va_list ap;
    va_start(ap, Data);

	while(*Data!=0){				                          //判断是否到达字符串结束符
		if(*Data==0x5c){									  //'\'
			switch (*++Data){
				case 'r':							          //回车符
					USART_SendData(USARTx, 0x0d);	   

					Data++;
					break;
				case 'n':							          //换行符
					USART_SendData(USARTx, 0x0a);	
					Data++;
					break;
				
				default:
					Data++;
				    break;
			}
			
			 
		}
		else if(*Data=='%'){									  //
			switch (*++Data){				
				case 's':										  //字符串
                	s = va_arg(ap, const char *);
                	for ( ; *s; s++) {
                    	USART_SendData(USARTx,*s);
						while(USART_GetFlagStatus(USARTx, USART_FLAG_TC)==RESET);
                	}
					Data++;
                	break;
            	case 'd':										  //十进制
                	d = va_arg(ap, int);
                	itoa(d, buf, 10);
                	for (s = buf; *s; s++) {
                    	USART_SendData(USARTx,*s);
						while(USART_GetFlagStatus(USARTx, USART_FLAG_TC)==RESET);
                	}
					Data++;
                	break;
				default:
					Data++;
				    break;
			}		 
		}
		else USART_SendData(USARTx, *Data++);
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TC)==RESET);
	}
}

/******************************************************
		整形数据转字符串函数
        char *itoa(int value, char *string, int radix)
		radix=10 标示是10进制	非十进制，转换结果为0;  

	    例：d=-379;
		执行	itoa(d, buf, 10); 后
		
		buf="-379"							   			  
**********************************************************/
char *itoa(int value, char *string, int radix)
{
    int     i, d;
    int     flag = 0;
    char    *ptr = string;

    /* This implementation only works for decimal numbers. */
    if (radix != 10)
    {
        *ptr = 0;
        return string;
    }

    if (!value)
    {
        *ptr++ = 0x30;
        *ptr = 0;
        return string;
    }

    /* if this is a negative value insert the minus sign. */
    if (value < 0)
    {
        *ptr++ = '-';

        /* Make the value positive. */
        value *= -1;
    }

    for (i = 10000; i > 0; i /= 10)
    {
        d = value / i;

        if (d || flag)
        {
            *ptr++ = (char)(d + 0x30);
            value -= (d * i);
            flag = 1;
        }
    }

    /* Null terminate the string. */
    *ptr = 0;

    return string;

} /* NCL_Itoa */


/*
*********************************************************************************************************
*********************************************************************************************************
*                                          uC/OS-II APP HOOKS
*********************************************************************************************************
*********************************************************************************************************
*/

#if (OS_APP_HOOKS_EN > 0)
/*
*********************************************************************************************************
*                                      TASK CREATION HOOK (APPLICATION)
*
* Description : This function is called when a task is created.
*
* Argument : ptcb   is a pointer to the task control block of the task being created.
*
* Note     : (1) Interrupts are disabled during this call.
*********************************************************************************************************
*/

void App_TaskCreateHook(OS_TCB* ptcb)
{
}

/*
*********************************************************************************************************
*                                    TASK DELETION HOOK (APPLICATION)
*
* Description : This function is called when a task is deleted.
*
* Argument : ptcb   is a pointer to the task control block of the task being deleted.
*
* Note     : (1) Interrupts are disabled during this call.
*********************************************************************************************************
*/

void App_TaskDelHook(OS_TCB* ptcb)
{
   (void) ptcb;
}

/*
*********************************************************************************************************
*                                      IDLE TASK HOOK (APPLICATION)
*
* Description : This function is called by OSTaskIdleHook(), which is called by the idle task.  This hook
*               has been added to allow you to do such things as STOP the CPU to conserve power.
*
* Argument : none.
*
* Note     : (1) Interrupts are enabled during this call.
*********************************************************************************************************
*/

#if OS_VERSION >= 251
void App_TaskIdleHook(void)
{
}
#endif

/*
*********************************************************************************************************
*                                        STATISTIC TASK HOOK (APPLICATION)
*
* Description : This function is called by OSTaskStatHook(), which is called every second by uC/OS-II's
*               statistics task.  This allows your application to add functionality to the statistics task.
*
* Argument : none.
*********************************************************************************************************
*/

void App_TaskStatHook(void)
{
}

/*
*********************************************************************************************************
*                                        TASK SWITCH HOOK (APPLICATION)
*
* Description : This function is called when a task switch is performed.  This allows you to perform other
*               operations during a context switch.
*
* Argument : none.
*
* Note     : 1 Interrupts are disabled during this call.
*
*            2  It is assumed that the global pointer 'OSTCBHighRdy' points to the TCB of the task that
*                   will be 'switched in' (i.e. the highest priority task) and, 'OSTCBCur' points to the
*                  task being switched out (i.e. the preempted task).
*********************************************************************************************************
*/

#if OS_TASK_SW_HOOK_EN > 0
void App_TaskSwHook(void)
{
}
#endif

/*
*********************************************************************************************************
*                                     OS_TCBInit() HOOK (APPLICATION)
*
* Description : This function is called by OSTCBInitHook(), which is called by OS_TCBInit() after setting
*               up most of the TCB.
*
* Argument : ptcb    is a pointer to the TCB of the task being created.
*
* Note     : (1) Interrupts may or may not be ENABLED during this call.
*********************************************************************************************************
*/

#if OS_VERSION >= 204
void App_TCBInitHook(OS_TCB* ptcb)
{
   (void) ptcb;
}
#endif

#endif
