/****************************************************************************
* Copyright (C), 2012 �ܶ�Ƕ��ʽ������ www.ourstm.com
*
* �������� �ܶ���STM32������V2,2.1,V3,MINI�ϵ���ͨ��           
* QQ: 9191274, ������sun68, Email: sun68@163.com 
* �Ա����̣�ourstm.taobao.com  
*
* �ļ���: app.c
* ���ݼ���:
*       �����̲���ϵͳ����ucos2.86a�汾�� ������5������
			������											 ���ȼ�
			APP_TASK_START_PRIO                               2	        ������	  		
            Task_Com1_PRIO                                    4			COM1ͨ������
            Task_Led1_PRIO                                    7			LED1 ��˸����
            Task_Led2_PRIO                                    8			LED2 ��˸����
            Task_Led3_PRIO                                    9			LED3 ��˸����
		 ��Ȼ��������ϵͳ����
		    OS_TaskIdle                  ��������-----------------���ȼ����
			OS_TaskStat                  ͳ������ʱ�������-------���ȼ��ε�
*
  ����һ����Ϣ���䣬ͨ������1�������յ���led��˸������Ϣͨ����Ϣ���䴫�ݸ����ڽ������񣬲��޸���ӦLED����˸�����
* �ļ���ʷ:
* �汾��  ����       ����    ˵��
* v0.1    2012-11-08 sun68  �������ļ�
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
#define LED_LED1_ON()   GPIO_SetBits(GPIOB, GPIO_Pin_5 );  	       //LED1  ��
#define LED_LED1_OFF()  GPIO_ResetBits(GPIOB, GPIO_Pin_5 ); 	   //LED1  ��

#define LED_LED2_ON()   GPIO_SetBits(GPIOD, GPIO_Pin_6 );  	       //LED2  ��
#define LED_LED2_OFF()  GPIO_ResetBits(GPIOD, GPIO_Pin_6 ); 	   //LED2  ��

#define LED_LED3_ON()   GPIO_SetBits(GPIOD, GPIO_Pin_3 );  	       //LED3  ��
#define LED_LED3_OFF()  GPIO_ResetBits(GPIOD, GPIO_Pin_3 ); 	   //LED3  ��
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

   //��ֹCPU�ж�
   CPU_IntDis();
   
   //UCOS ��ʼ��
   OSInit();                                                   /* Initialize "uC/OS-II, The Real-Time Kernel".         */
   
   //Ӳ��ƽ̨��ʼ��
   BSP_Init();                                                 /* Initialize BSP functions.  */
   
   //Ĭ��LED��˸���500ms
   milsec1=500,milsec2=500,milsec3=500;

   USART_OUT(USART1,"****(C) COPYRIGHT 2010 �ܶ�Ƕ��ʽ���������� *******\r\n");    	  //�򴮿�1���Ϳ����ַ���
   USART_OUT(USART1,"*                                                 *\r\n");    	
   USART_OUT(USART1,"*         �ܶ���STM32������ LED��˸ʵ��           *\r\n");  
   USART_OUT(USART1,"*                                                 *\r\n");    	  	
   USART_OUT(USART1,"*             ���� uCOSII2.86                     *\r\n");    	
   USART_OUT(USART1,"*                                                 *\r\n");    	
   USART_OUT(USART1,"*LED1��˸�����1ms--65535ms  ָ��L1 1F--L1 65535F *\r\n");    	
   USART_OUT(USART1,"*LED2��˸�����1ms--65535ms  ָ��L2 1F--L1 65535F *\r\n");    
   USART_OUT(USART1,"*LED3��˸�����1ms--65535ms  ָ��L3 1F--L1 65535F *\r\n"); 
   USART_OUT(USART1,"*                                                 *\r\n");    	   
   USART_OUT(USART1,"*  �ܶ�STM32��̳��ourstm.5d6d.com                 *\r\n");   
   USART_OUT(USART1,"*                                                 *\r\n");    	 	
   USART_OUT(USART1,"***************************************************\r\n"); 
   USART_OUT(USART1,"\r\n"); 
   USART_OUT(USART1,"\r\n");    	
   
   //���������� ���ȼ����  ���������������һ����;��Ϊ���Ժ�ʹ��ͳ������
   os_err = OSTaskCreate((void (*) (void *)) App_TaskStart,	  		  		//ָ����������ָ��
                          (void *) 0,								  		//����ʼִ��ʱ�����ݸ�����Ĳ�����ָ��
               (OS_STK *) &App_TaskStartStk[APP_TASK_START_STK_SIZE - 1],	//���������Ķ�ջ��ջ��ָ��   �Ӷ����µݼ�
               (INT8U) APP_TASK_START_PRIO);								//�������������ȼ�
   
   //ucos�Ľ��ļ�������0    ���ļ�������0-4294967295    ���ڽ���Ƶ��100hzʱ�� ÿ��497������¼��� 
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

   //��ʼ��ucosʱ�ӽ���
   OS_CPU_SysTickInit();                                       /* Initialize the SysTick.       */

//ʹ��ucos ��ͳ������
#if (OS_TASK_STAT_EN > 0)
   //----ͳ�������ʼ������  
   OSStatInit();                                               /* Determine CPU capacity.                              */
#endif
   //��������������
   App_TaskCreate();

   while (1)
   {
      //1��һ��ѭ��
	  OSTimeDlyHMSM(0, 0,1, 0);

   }
}


//LED1��˸����----------------------------------------
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

//LED2��˸����----------------------------------------
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

//LED3��˸����----------------------------------------
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
 
   //Com1_SEM=OSSemCreate(1);		     //��������1�жϵ��ź���
   Com1_MBOX=OSMboxCreate((void *) 0);		     //��������1�жϵ���Ϣ����
   

   
   
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

  
   
}



//++++++++++++COM1��������++++++++++++++++++++++++++
static  void Task_Com1(void *p_arg){    
   INT8U err;	
   unsigned char * msg;
   (void)p_arg;	  				  
   while(1){
   	 
      //OSSemPend(Com1_SEM,0,&err); 		  //�ȴ����ڽ���ָ��ɹ����ź���
	  msg=(unsigned char *)OSMboxPend(Com1_MBOX,0,&err); 		  //�ȴ����ڽ���ָ��ɹ���������Ϣ
	  //USART_OUT(USART1,&TxBuffer1[0]);
   	  if(msg[0]=='L'&&msg[1]==0x31){
	  	 milsec1=atoi(&msg[3]);               //LED1 ����ʱ����  (mini and V3)
	     USART_OUT(USART1,"\r\n");
	  	 USART_OUT(USART1,"LED1: %d ms �����˸",milsec1);		 
	  }
	  else if(msg[0]=='L'&&msg[1]==0x32){
	  	 milsec2=atoi(&msg[3]);		   //LED2 ����ʱ����  (only V3)
		 USART_OUT(USART1,"\r\n");
	  	 USART_OUT(USART1,"LED2: %d ms �����˸",milsec2);
	  }
	  else if(msg[0]=='L'&&msg[1]==0x33){
	  	  milsec3=atoi(&msg[3]);		   //LED3 ����ʱ����  (only V3)
		  USART_OUT(USART1,"\r\n");
	  	  USART_OUT(USART1,"LED3: %d ms �����˸",milsec3);
	  } 
   } 
}


int SendChar (int ch)  {                /* Write character to Serial Port     */

  USART_SendData(USART1, (unsigned char) ch);
  while (!(USART1->SR & USART_FLAG_TXE));
  return (ch);
}


/******************************************************
		��ʽ�������������
        "\r"	�س���	   USART_OUT(USART1, "abcdefg\r")   
		"\n"	���з�	   USART_OUT(USART1, "abcdefg\r\n")
		"%s"	�ַ���	   USART_OUT(USART1, "�ַ����ǣ�%s","abcdefg")
		"%d"	ʮ����	   USART_OUT(USART1, "a=%d",10)
**********************************************************/
void USART_OUT(USART_TypeDef* USARTx, uint8_t *Data,...){ 

	const char *s;
    int d;
   
    char buf[16];
    va_list ap;
    va_start(ap, Data);

	while(*Data!=0){				                          //�ж��Ƿ񵽴��ַ���������
		if(*Data==0x5c){									  //'\'
			switch (*++Data){
				case 'r':							          //�س���
					USART_SendData(USARTx, 0x0d);	   

					Data++;
					break;
				case 'n':							          //���з�
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
				case 's':										  //�ַ���
                	s = va_arg(ap, const char *);
                	for ( ; *s; s++) {
                    	USART_SendData(USARTx,*s);
						while(USART_GetFlagStatus(USARTx, USART_FLAG_TC)==RESET);
                	}
					Data++;
                	break;
            	case 'd':										  //ʮ����
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
		��������ת�ַ�������
        char *itoa(int value, char *string, int radix)
		radix=10 ��ʾ��10����	��ʮ���ƣ�ת�����Ϊ0;  

	    ����d=-379;
		ִ��	itoa(d, buf, 10); ��
		
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
