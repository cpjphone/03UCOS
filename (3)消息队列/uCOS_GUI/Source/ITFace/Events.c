#include <stddef.h>
#include "GUI.h"
#include "DIALOG.h"
#include "includes.h"


extern OS_EVENT  *MsgQueue;				 //定义消息队列指针

void led1_ON(WM_MESSAGE * pMsg)
{
	char led1_ON='1';	
	OSQPost(MsgQueue,(void *)&led1_ON); 
	OSTimeDlyHMSM(0, 0,0, 1);
}

void led2_ON(WM_MESSAGE * pMsg)
{
	char led2_ON='3';
	OSQPost(MsgQueue,(void *)&led2_ON); 
	OSTimeDlyHMSM(0, 0,0, 1);
}

void led1_OFF(WM_MESSAGE * pMsg)
{
	char led1_OFF='2';
	OSQPost(MsgQueue,(void *)&led1_OFF); 
	OSTimeDlyHMSM(0, 0,0, 1);
}

void led2_OFF(WM_MESSAGE * pMsg)
{
	char led2_OFF='4';
	OSQPost(MsgQueue,(void *)&led2_OFF); 
	OSTimeDlyHMSM(0, 0,0, 1);
}

