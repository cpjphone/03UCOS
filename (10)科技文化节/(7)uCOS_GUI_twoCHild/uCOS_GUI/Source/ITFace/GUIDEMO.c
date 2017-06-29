/*
******************************************************************
**                      uCGUIBuilder                            **
**                  Version:   4.0.0.0                          **
**                     2012 / 04                               **
**                   CpoyRight to: wyl                          **
**              Email:ucguibuilder@163.com                        **
**          This text was Created by uCGUIBuilder               **
******************************************************************/

#include <stddef.h>
#include "GUI.h"
#include "DIALOG.h"

#include "WM.h"
#include "BUTTON.h"
#include "CHECKBOX.h"
#include "DROPDOWN.h"
#include "EDIT.h"
#include "FRAMEWIN.h"
#include "LISTBOX.h"
#include "MULTIEDIT.h"
#include "RADIO.h"
#include "SLIDER.h"
#include "TEXT.h"
#include "PROGBAR.h"
#include "SCROLLBAR.h"
#include "LISTVIEW.h"


static int          _iTestMinor;
static BUTTON_Handle   _ahButton[2];
static FRAMEWIN_Handle _ahFrameWin[2];
static char        _CmdNext;
static const char* _sExplain;



/************************************************************************/
//Static routines(��̬����)
/************************************************************************/
static void _UpdateCmdWin(void) {
  #if GUI_WINSUPPORT && GUIDEMO_LARGE	 //���ÿ�ѡ����Ӵ�������֧��
    WM_InvalidateWindow(_ahInfoWin[1]);	 //ʹһ��ָ���Ĵ�����Ч
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

	GUI_SetColor(GUI_RED);
	GUI_SetFont(&GUI_FontComic24B_ASCII);  //���õ�ǰ���� 
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

