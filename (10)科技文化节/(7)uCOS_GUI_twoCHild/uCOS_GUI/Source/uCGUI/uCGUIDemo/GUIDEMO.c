/*
*********************************************************************************************************
*                                                uC/GUI
*                        Universal graphic software for embedded applications
*
*                       (c) Copyright 2002, Micrium Inc., Weston, FL
*                       (c) Copyright 2002, SEGGER Microcontroller Systeme GmbH
*
*              �C/GUI is protected by international copyright laws. Knowledge of the
*              source code may not be used to write a similar product. This file may
*              only be used in accordance with a license and should not be redistributed
*              in any way. We appreciate your understanding and fairness.
*
----------------------------------------------------------------------
File        : GUIDEMO.c
Purpose     : Several GUIDEMO routines
----------------------------------------------------------------------
*/

#include <stddef.h>
#include "GUI.h"
#if GUI_WINSUPPORT
#include "PROGBAR.h"
#include "LISTBOX.h"
#include "FRAMEWIN.h"
#include "BUTTON.h"
#endif
#include "GUIDEMO.h"

/*********************************************************************
*
*       Static variables
*
**********************************************************************
*/
												//���ÿ�ѡ����Ӵ�������֧�֡�
#if GUI_WINSUPPORT
  static BUTTON_Handle   _ahButton[2];			//��һ��ָ��λ�ã���ָ���Ĵ�С����һ�� BUTTON �ؼ�
  static FRAMEWIN_Handle _ahFrameWin[2];		//��һ��ָ��λ����ָ���ĳߴ紴��һ����ܴ��ڿؼ�
  static int             _ButtonSizeX,      _ButtonSizeY;
  #if GUIDEMO_LARGE
    static FRAMEWIN_Handle _ahInfoWin[2];
    static const char* _sInfo;
  #endif
#endif

static int         _iTest, _iTestMinor;
static char        _CmdNext, flag,num;
static const char* _sExplain;

//#define countof(Obj) (sizeof(Obj)/sizeof(Obj[0]))

/*********************************************************************
*
*       Routine table	  �������
*
**********************************************************************

  The routines to be called are listed here. The advantage to calling
  directly is that we can execute some code before and after.
  ��������̱���Ϊ����������ƺ����ŵ�
	ֱ�������ǿ���ִ��һЩ����֮ǰ��֮�󡣣�
*/

//typedef void fVoidVoid(void);

//static fVoidVoid * _apfTest[] = {
//  GUIDEMO_HardwareInfo,
//  GUIDEMO_Speed,
//  #if GUI_SUPPORT_MEMDEV
//    GUIDEMO_Graph,
//  #endif
//  GUIDEMO_Bitmap,					   //λͼ
//  GUIDEMO_Cursor,					   //���
//  GUIDEMO_ShowInternationalFonts,	   //����
//  GUIDEMO_ShowColorBar,				   //����
//  GUIDEMO_ShowColorList,			   //��ɫ�б�
//  GUIDEMO_DemoLUT,					   //���ƺ���   ��������������������
//  GUIDEMO_DemoPolygon,				   //�����
//  GUIDEMO_Circle,					   //��Բ
//  GUIDEMO_ShowMemoryDevice,			   //���������ڴ�����
//  GUIDEMO_Automotive,				   // �Զ���
//
//  GUIDEMO_Navigation,				   //���� ����
//
//  #if GUI_WINSUPPORT				  //���ÿ�ѡ����Ӵ�������֧�֡�
//    GUIDEMO_DemoProgBar,			  // �������ؼ�
//    GUIDEMO_DemoFrameWin,			  //��ܴ��ڿؼ� 
//    GUIDEMO_Dialog,					  //�Ի���
//    GUIDEMO_WM,						  //��ʾ��Ϣ
//    #if GUI_SUPPORT_TOUCH			  //���ÿ�ѡ��Ĵ�����֧��
//     GUIDEMO_Touch,				  //��֮��Ҫ�õ�һ������������һ���� 
//    #endif
//  #endif
//  0
//};

/************************************************************************/
//Static routines(��̬����)
/************************************************************************/
static void _UpdateCmdWin(void) {
  #if GUI_WINSUPPORT && GUIDEMO_LARGE	 //���ÿ�ѡ����Ӵ�������֧��
    WM_InvalidateWindow(_ahInfoWin[1]);	 //ʹһ��ָ���Ĵ�����Ч
  #endif
}

/************************************************************************/
//���½ǵ�Сѡ��ͼ��
/************************************************************************/
//#if (GUI_WINSUPPORT && GUIDEMO_LARGE)	 //�жϿ�ѡ����Ӵ����������������Ϊ���Ƿ��л����л�
//static void _cbCmdWin(WM_MESSAGE* pMsg)  //WM_MESSAGE:�ص�����,pMsg:��Ϣ��ָ��
//{
//  switch (pMsg->MsgId) {
//  case WM_PAINT:						 //WM_PAINT:�������ƻ��ػ�һ�����ڡ� 
//    /* Update info in command window */
//    GUI_SetBkColor(GUI_GRAY);			 //���õ�ǰ����ɫ������ֵ 
//    GUI_Clear();						 //�����Ӵ�����������ǻ�Ӵ������������������
//    GUI_DispStringAt("Demo ", 0, 0);	 //��ָ��������ʾ�ַ��� 
//    GUI_DispDecMin(_iTest + 1);		     //�ڵ�ǰ������ʾ���������ַ���ʮ������ֵ
//    GUI_DispString(".");				 //�ڵ�ǰ������ʾ�ַ��� 
//    GUI_DispDecMin(_iTestMinor);		 //�ڵ�ǰ������ʾ���������ַ���ʮ������ֵ
//    GUI_DispString("/");
//    GUI_DispDecMin(countof(_apfTest));
//  default:
//    WM_DefaultProc(pMsg);				 //������Ϣ��Ĭ�Ϻ���
//  }
//}
//#endif

/************************************************************************/
//�Ի������
/************************************************************************/
static void _UpdateInfoWin(void) {
  #if GUI_WINSUPPORT && GUIDEMO_LARGE		 //�жϿ�ѡ����Ӵ����������������Ϊ���Ƿ��л����л�
    GUI_RECT rClient;						 //д���صĿͻ����ڵľ�������,
    WM_HWIN hWin;							 //hWin:���ڵ��ã�WM_HWIN ��I16   signed short    /*   signed 16 bits. */
    GUI_CONTEXT ContextOld;
    GUI_SaveContext(&ContextOld);
    /* Update info  window��������Ϣ���ڣ� */
    WM_ShowWindow(_ahInfoWin[0]);			 //WM_ShowWindow() ��ʹһ��ָ�����ڿɼ�
    WM_ShowWindow(_ahFrameWin[0]);
    hWin = WM_SelectWindow(_ahInfoWin[0]);	 //WM_SelectWindow()������һ����������ڻ��Ʋ���
    GUI_GetClientRect(&rClient);			 //�ڵ�ǰ�Ӵ���ʹ�õ�ǰ������ָ��������ʾ��Ϊ�������ַ���
    GUI_SetBkColor(GUI_WHITE);				 //͸���ı����������Ǳ�������Ϊ��ת�ı����ı���ʾ�Ƿ�ת��
    GUI_Clear();							 //�����ǰ�Ӵ�
    GUI_SetColor(GUI_BLACK);				 //���õ�ǰǰ����ɫ 
    GUI_SetFont(&GUI_Font13_1);				 //GUI_SetFont:���õ�ǰ����,GUI_Font13_1:��ť�ı�������
    GUI_SetTextAlign(GUI_TA_HCENTER);		 //Ĭ�ϵ��ı����뷽ʽ
    GUI_DispStringHCenterAt(_sInfo, (rClient.x1 - rClient.x0) / 2, 0);    // �����༭��ؼ�
    GUI_SetTextAlign(GUI_TA_LEFT);			 //ͬ��
    GUI_SetFont(&GUI_Font8_ASCII);			 //ͬ��
    GUI_DispStringAt(_sExplain, 0, 20);		 //��ָ��������ʾ�ַ���
    WM_SelectWindow(hWin);					 //�������ڻ�ͼ�����Ļ����
    GUI_RestoreContext(&ContextOld);		 //
  #endif
}

/************************************************************************/
// Exported routines�����������̣��졢��
/************************************************************************/
GUI_COLOR GUIDEMO_SetBkColor(GUI_COLOR Color) //GUI_COLOR��U32 unsigned long   /* unsigned 32 bits. */
{
  GUI_COLOR r;
  if (GUI_ColorIsAvailable(GUI_RED)) {
    r = Color;
  } else {
    r = GUI_BLACK;
  }
  GUI_SetBkColor(r);
  return r;
}

/************************************************************************/
// Exported routines�����������̣��졢��
/************************************************************************/
GUI_COLOR GUIDEMO_SetColor(GUI_COLOR Color) {
  GUI_COLOR r;
  if (GUI_ColorIsAvailable(GUI_RED)) {
    r = Color;
  } else {
    r = GUI_WHITE;
  }
  GUI_SetColor(r);
  return r;
}

/************************************************************************/
// GUI��ʱ
/************************************************************************/
int GUIDEMO_Delay(int t)
{
	int r = 0;
	#if GUI_WINSUPPORT
		int tm, value;
	#if GUIDEMO_LARGE
		PROGBAR_Handle hProg;			 	    // PROGBAR_Handle��signed short 
	#endif

	WM_SetForegroundWindow(_ahButton[0]);	  	//����ͬ������֮ǰ����һ�����ڡ�
	#if GUIDEMO_LARGE
		hProg = (t >100) ? PROGBAR_CreateAsChild(10, 10, 60, 7, _ahInfoWin[1], 0,
						   WM_CF_SHOW | WM_CF_STAYONTOP| WM_CF_MEMDEV) : 0;
													/*��Ŀ����*/
		PROGBAR_SetMinMax(hProg, 0, t);	        //���ý���������С�������ֵ��
	#endif
	tm = GUI_GetTime();
	do 
	{
		value = GUI_GetTime() - tm;
		#if GUIDEMO_LARGE
			PROGBAR_SetValue(hProg, value);	   //���ý���������ֵ	   ������ʾ
			WM_ExecIdle();					   	//ͨ��ִ�лص����������й������ػ���Ч����
		#endif
		GUI_Delay(10);							 //��ͼ��ʱ�䲻�䣬������10MS ��ʾһ�Σ��� 1S
	}
	while ((value < t) && !GUIDEMO_CheckCancel());
	#if GUIDEMO_LARGE
		PROGBAR_Delete(hProg);				/* ɾ�������� */ 
	#endif
		_UpdateCmdWin();
		WM_ExecIdle();
	#else						//MS��λ
		GUI_Delay(t);
	#endif
	return r;
}

/************************************************************************/
// GUI��ʱ 4000
/************************************************************************/
void GUIDEMO_Wait(void) {
  GUIDEMO_Delay(4000);
  GUIDEMO_NotifyStartNext();
}

/************************************************************************/
// ���ȡ��
/************************************************************************/
int GUIDEMO_CheckCancel(void) 
{
	int c = GUI_GetKey();				//���ؼ�������������
	#if GUI_WINSUPPORT
		WM_ExecIdle();
	#endif
	if ((c == 'n') || (c=='N'))
		_CmdNext =1;
	if ((c == 's') || (c=='S'))
	{
		GUI_Delay(500);
		do 
		{
			GUI_Delay(10);
			#if GUI_WINSUPPORT
				WM_ExecIdle();
			#endif
			c = GUI_GetKey();
		}
		while (!c);
	}
	return _CmdNext;
}

/************************************************************************/
// ��Ϣ��ʾ
/************************************************************************/
void GUIDEMO_ShowInfo(const char* s) {
  _sExplain = s;
  _UpdateInfoWin();
}

/************************************************************************/
// ������Ϣ�ɹ�
/************************************************************************/
void GUIDEMO_HideInfoWin(void) {
  #if GUI_WINSUPPORT
    WM_HideWindow(_ahFrameWin[0]);				 //ʹһ��ָ�����ڲ��ɼ�
  #endif
}

/************************************************************************/
// ֪ͨ ���� ��ʼ
/************************************************************************/
void GUIDEMO_NotifyStartNext(void) {
  _CmdNext = 0;
  _UpdateCmdWin();
  _iTestMinor++;
}

/************************************************************************/
// �ȴ�ʱ�̺���
/************************************************************************/
int GUIDEMO_WaitKey(void) {
  int r = 0;
  int tMax = GUI_GetTime() + 4000;					 //GUI_GetTime()�����ص�ǰ��ϵͳʱ��
  int tDiff; 
  #if GUI_WINSUPPORT								 //�жϿ�ѡ����Ӵ����������������Ϊ���Ƿ��л����л�
    PROGBAR_Handle hProg = PROGBAR_Create(LCD_GetXSize() - 70, 		 
                                          LCD_GetYSize() - 40, 
                                          80, 5, WM_CF_SHOW);
  #endif
  while (tDiff = tMax-GUI_GetTime(), (tDiff > 0) && !GUIDEMO_CheckCancel()) {
    if ((r = GUI_GetKey()) != 0)
      break;
  }
  #if GUI_WINSUPPORT
    PROGBAR_Delete(hProg);
    WM_ExecIdle();
  #endif
  return r;
}											   

/************************************************************************/
// GUI��ʾ_��ʾ���
/************************************************************************/
void GUIDEMO_ShowIntro(const char * s, const char * sExp) 
{
	GUI_CONTEXT ContextOld;
	GUI_SaveContext(&ContextOld);		   //�����Ƕ�����һ����ָ������ĺ���
	#if GUI_WINSUPPORT && GUIDEMO_LARGE
		_sInfo = s;
	#endif
	_sExplain = sExp;
	GUI_SetDefault();					   //����Ĭ��

	GUIDEMO_HideInfoWin();				   //����InfoWin
	GUI_SetBkColor(GUI_BLUE);			   //���õ�ǰ������ɫ 
	GUI_SetColor(GUI_WHITE);			   //���õ�ǰǰ����ɫ
	GUI_Clear();

	GUI_SetFont(&GUI_FontComic18B_ASCII);  //���õ�ǰ���� 
	GUI_DispStringHCenterAt(s, LCD_GET_XSIZE() / 2, LCD_GET_YSIZE() / 3 - 10);				//�ַ�������������ʾ����
			/*void  GUI_DispStringHCenterAt(const char GUI_UNI_PTR *s, int x, int y);
			��һ������ֻ����ָ�����
			*/


	if (_sExplain)
	{
		GUI_SetFont(&GUI_Font8_ASCII);
		GUI_DispStringHCenterAt(_sExplain, LCD_GET_XSIZE() / 2, LCD_GET_YSIZE() / 2 - 10);
	}
 	GUIDEMO_Delay(_sExplain ? 2000 : 4000);
	#if GUI_WINSUPPORT
		_UpdateInfoWin();
		_UpdateCmdWin();
	#endif
		GUI_RestoreContext(&ContextOld);
	#if GUI_WINSUPPORT
		WM_ExecIdle();
	#endif
		GUIDEMO_NotifyStartNext();  //֪ͨ���ܿ�ʼ	
		GUI_SetBkColor(GUI_RED);
		GUI_Clear();  
}

/************************************************************************/
//(������ɺ���)
/************************************************************************/


/************************************************************************/
//GUIDEMO_main(): Large version of the demo
// (��汾����ʾ)
/************************************************************************/
void GUIDEMO_main(void) 
{

	
}

