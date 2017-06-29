
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
#include "face.h"

extern int temp;
extern char Esign,Fsign,Jsign;
extern const GUI_BITMAP bmGSMback;

void GSMface(void)
{
	//GUI_Init();
//	GUI_SetColor(GUI_LIGHTRED);	  //	  预定义颜色   淡红	
//	GUI_Clear();
	GUI_DrawBitmap(&bmGSMback, 0, 0);
	while(1)
	{
		
		/************信号电路**************/  
		if(Esign == 2)
		{			
			GUI_SetBkColor(GUI_YELLOW);     //背景颜色
			GUI_SetColor(GUI_DARKRED);
			GUI_SetFont(&GUI_Font32_1);  //设置用于文字输出的字体	 uC/GUI  显示
			//GUI_DispDecAt(temp, 200, 85, 2);
			GUI_DispStringAt("OK", 200, 85);		
		}
		/***********是否发送*************/  
		if(Fsign == 2)
		{
			GUI_SetBkColor(GUI_LIGHTYELLOW);     //背景颜色
			GUI_SetColor(GUI_RED);
			GUI_SetFont(&GUI_Font32_1);  //设置用于文字输出的字体	 uC/GUI  显示
			//GUI_DispDecAt(temp, 200, 129, 2);
			GUI_DispStringAt("OK", 200,129);
		}
		
		/***********是否接收*************/ 
		if(Jsign == 2)
		{
			GUI_SetBkColor(GUI_DARKYELLOW);     //背景颜色
			GUI_SetColor(GUI_RED);
			GUI_SetFont(&GUI_Font32_1);  //设置用于文字输出的字体	 uC/GUI  显示
			//GUI_DispDecAt(temp, 200, 174, 2);	
			GUI_DispStringAt("OK", 200, 174);	
		}
		
		 //GUIDEMO_Delay(1000);
		//	GUIDEMO_NotifyStartNext();
	}
}
