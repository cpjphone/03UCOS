
/*********************************************************************************      
* 【FILENAME】：app_cfg.h
* 【FUNCTION】：（1）设置任务堆栈空间大小， （2）优先级选择 
*********************************************************************************/
#ifndef  __APP_CFG_H__
#define  __APP_CFG_H__

/************************************************************************/
//优先级选择
/************************************************************************/
#define  OS_TASK_TMR_PRIO              (OS_LOWEST_PRIO - 2)

#define  APP_TASK_START_PRIO                   3			 //启动任务（主任务）

#define  Signal_PRIO                           4
#define  Task_Led1_PRIO                        7
#define  Task_Led2_PRIO                        11
#define  Task_Led3_PRIO                        14

/************************************************************************/
//设置任务堆栈空间大小
/************************************************************************/
#define  APP_TASK_START_STK_SIZE             512

#define  Signal_STK_SIZE                     512
#define  Task_Led1_STK_SIZE                  256
#define  Task_Led2_STK_SIZE                  256
#define  Task_Led3_STK_SIZE                  128

//#define  APP_TASK_PROBE_STR_STK_SIZE         64
//#define  OS_PROBE_TASK_STK_SIZE              64

#endif
