
/*********************************************************************************      
* ��FILENAME����app_cfg.h
* ��FUNCTION������1�����������ջ�ռ��С�� ��2�����ȼ�ѡ�� 
*********************************************************************************/
#ifndef  __APP_CFG_H__
#define  __APP_CFG_H__

/************************************************************************/
//���ȼ�ѡ��
/************************************************************************/
#define  OS_TASK_TMR_PRIO              (OS_LOWEST_PRIO - 2)

#define  APP_TASK_START_PRIO                   3			 //��������������
#define  Signal_PRIO                           4
#define  Task_Com1_PRIO                        5
#define  APP_TASK_KBD_PRIO                     6			 //����������	 ��Ȼ��������ϵͳ����
#define  APP_TASK_USER_IF_PRIO                 10			 //��������
#define  Task_Led1_PRIO                        7

/************************************************************************/
//���������ջ�ռ��С
/************************************************************************/
#define  APP_TASK_START_STK_SIZE             128
#define  APP_TASK_USER_IF_STK_SIZE           256
#define  APP_TASK_KBD_STK_SIZE               256

#define  Task_Com1_STK_SIZE                  256
#define  Signal_STK_SIZE                     256
#define  Task_Led1_STK_SIZE                  128

//#define  APP_TASK_PROBE_STR_STK_SIZE         64
//#define  OS_PROBE_TASK_STK_SIZE              64

#endif
