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
//Static routines(静态例程)
/************************************************************************/
static void _UpdateCmdWin(void) {
  #if GUI_WINSUPPORT && GUIDEMO_LARGE	 //启用可选择的视窗管理器支持
    WM_InvalidateWindow(_ahInfoWin[1]);	 //使一个指定的窗口无效
  #endif
}

/************************************************************************/
// 通知 下周 开始
/************************************************************************/
void GUIDEMO_NotifyStartNext(void) {
  _CmdNext = 0;
  _UpdateCmdWin();
  _iTestMinor++;
}

/************************************************************************/
//对话框程序
/************************************************************************/
static void _UpdateInfoWin(void) {
  #if GUI_WINSUPPORT && GUIDEMO_LARGE		 //判断可选择的视窗管理器，可以理解为：是否有画面切换
    GUI_RECT rClient;						 //写像素的客户窗口的矩形区域,
    WM_HWIN hWin;							 //hWin:窗口调用，WM_HWIN ：I16   signed short    /*   signed 16 bits. */
    GUI_CONTEXT ContextOld;
    GUI_SaveContext(&ContextOld);
    /* Update info  window（更新信息窗口） */
    WM_ShowWindow(_ahInfoWin[0]);			 //WM_ShowWindow() ：使一个指定窗口可见
    WM_ShowWindow(_ahFrameWin[0]);
    hWin = WM_SelectWindow(_ahInfoWin[0]);	 //WM_SelectWindow()：设置一个活动窗口用于绘制操作
    GUI_GetClientRect(&rClient);			 //在当前视窗，使用当前字体在指定坐标显示作为参数的字符串
    GUI_SetBkColor(GUI_WHITE);				 //透明文本，它不覆盖背景，作为反转文本，文本显示是反转的
    GUI_Clear();							 //清除当前视窗
    GUI_SetColor(GUI_BLACK);				 //设置当前前景颜色 
    GUI_SetFont(&GUI_Font13_1);				 //GUI_SetFont:设置当前字体,GUI_Font13_1:按钮文本的字体
    GUI_SetTextAlign(GUI_TA_HCENTER);		 //默认的文本对齐方式
    GUI_DispStringHCenterAt(_sInfo, (rClient.x1 - rClient.x0) / 2, 0);    // 创建编辑框控件
    GUI_SetTextAlign(GUI_TA_LEFT);			 //同上
    GUI_SetFont(&GUI_Font8_ASCII);			 //同上
    GUI_DispStringAt(_sExplain, 0, 20);		 //在指定坐标显示字符串
    WM_SelectWindow(hWin);					 //设置用于绘图操作的活动窗口
    GUI_RestoreContext(&ContextOld);		 //
  #endif
}

/************************************************************************/
// 检查取消
/************************************************************************/
int GUIDEMO_CheckCancel(void) 
{
	int c = GUI_GetKey();				//返回键缓冲区的内容
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
// GUI延时
/************************************************************************/
int GUIDEMO_Delay(int t)
{
	int r = 0;
	#if GUI_WINSUPPORT
		int tm, value;
	#if GUIDEMO_LARGE
		PROGBAR_Handle hProg;			 	    // PROGBAR_Handle：signed short 
	#endif

	WM_SetForegroundWindow(_ahButton[0]);	  	//在其同胞窗口之前放置一个窗口。
	#if GUIDEMO_LARGE
		hProg = (t >100) ? PROGBAR_CreateAsChild(10, 10, 60, 7, _ahInfoWin[1], 0,
						   WM_CF_SHOW | WM_CF_STAYONTOP| WM_CF_MEMDEV) : 0;
													/*三目运算*/
		PROGBAR_SetMinMax(hProg, 0, t);	        //设置进度条的最小和最大数值。
	#endif
	tm = GUI_GetTime();
	do 
	{
		value = GUI_GetTime() - tm;
		#if GUIDEMO_LARGE
			PROGBAR_SetValue(hProg, value);	   //设置进度条的数值	   并且显示
			WM_ExecIdle();					   	//通过执行回调函数（所有工作）重绘无效窗口
		#endif
		GUI_Delay(10);							 //框图总时间不变，这里是10MS 显示一次，总 1S
	}
	while ((value < t) && !GUIDEMO_CheckCancel());
	#if GUIDEMO_LARGE
		PROGBAR_Delete(hProg);				/* 删除进度条 */ 
	#endif
		_UpdateCmdWin();
		WM_ExecIdle();
	#else						//MS单位
		GUI_Delay(t);
	#endif
	return r;
}

/************************************************************************/
// GUI延时 4000
/************************************************************************/
void GUIDEMO_Wait(void) {
  GUIDEMO_Delay(4000);
  GUIDEMO_NotifyStartNext();
}

/************************************************************************/
// 信息显示
/************************************************************************/
void GUIDEMO_ShowInfo(const char* s) {
  _sExplain = s;
  _UpdateInfoWin();
}


/************************************************************************/
// 隐藏信息成功
/************************************************************************/
void GUIDEMO_HideInfoWin(void) {
  #if GUI_WINSUPPORT
    WM_HideWindow(_ahFrameWin[0]);				 //使一个指定窗口不可见
  #endif
}

/************************************************************************/
// GUI演示_显示简介
/************************************************************************/
void GUIDEMO_ShowIntro(const char * s, const char * sExp) 
{
	GUI_CONTEXT ContextOld;
	GUI_SaveContext(&ContextOld);		   //仅仅是定义了一个有指针变量的函数
	#if GUI_WINSUPPORT && GUIDEMO_LARGE
		_sInfo = s;
	#endif
	_sExplain = sExp;
	GUI_SetDefault();					   //设置默认

	GUIDEMO_HideInfoWin();				   //隐藏InfoWin
	GUI_SetBkColor(GUI_BLUE);			   //设置当前背景颜色 
	GUI_SetColor(GUI_WHITE);			   //设置当前前景颜色
	GUI_Clear();

	GUI_SetColor(GUI_RED);
	GUI_SetFont(&GUI_FontComic24B_ASCII);  //设置当前字体 
	GUI_DispStringHCenterAt(s, LCD_GET_XSIZE() / 2, LCD_GET_YSIZE() / 3 - 10);				//字符串中心中心显示函数
			/*void  GUI_DispStringHCenterAt(const char GUI_UNI_PTR *s, int x, int y);
			第一个变量只能是指针变量
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
		GUIDEMO_NotifyStartNext();  //通知下周开始	
		GUI_SetBkColor(GUI_RED);
		GUI_Clear();  
}

