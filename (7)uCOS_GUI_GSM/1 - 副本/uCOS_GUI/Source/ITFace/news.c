
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
extern const GUI_BITMAP bmbackface;

void news(void)
{
	//GUI_Init();
	GUI_SetColor(GUI_LIGHTRED);	  //	  预定义颜色   淡红	
	GUI_Clear();
	GUI_DrawBitmap(&bmbackface, 0, 0);
	while(1)
	{
		//GUI_Init();
		/************温度**************/  	
		GUI_SetBkColor(GUI_CYAN );     //背景颜色
		GUI_SetColor(GUI_RED);
		GUI_SetFont(&GUI_Font24B_1);  //设置用于文字输出的字体	 uC/GUI  显示
		GUI_DispDecAt(temp,105 , 46, 2);
		
		GUI_SetBkColor(GUI_CYAN);     //背景颜色
		GUI_SetColor(GUI_RED);
		GUI_SetFont(&GUI_Font24B_1);  //设置用于文字输出的字体	 uC/GUI  显示
		GUI_DispDecAt(temp,141 , 46, 2);
		
		/************湿度**************/  
		GUI_SetBkColor(GUI_CYAN );     //背景颜色
		GUI_SetColor(GUI_DARKRED);
		GUI_SetFont(&GUI_Font24B_1);  //设置用于文字输出的字体	 uC/GUI  显示
		GUI_DispDecAt(temp, 148, 81, 2);
		
		GUI_SetBkColor(GUI_CYAN  );     //背景颜色
		GUI_SetColor(GUI_DARKRED);
		GUI_SetFont(&GUI_Font24B_1);  //设置用于文字输出的字体	 uC/GUI  显示
		GUI_DispDecAt(temp, 186, 81, 2);
		
		/************电压**************/  
		GUI_SetBkColor(GUI_CYAN);     //背景颜色
		GUI_SetColor(GUI_RED);
		GUI_SetFont(&GUI_Font24B_1);  //设置用于文字输出的字体	 uC/GUI  显示
		GUI_DispDecAt(temp, 202, 112, 2);
		
		GUI_SetBkColor(GUI_CYAN);     //背景颜色
		GUI_SetColor(GUI_RED);
		GUI_SetFont(&GUI_Font24B_1);  //设置用于文字输出的字体	 uC/GUI  显示
		GUI_DispDecAt(temp, 242, 112, 2);
		
		/***********人体红外*************/  
		GUI_SetBkColor(GUI_CYAN);     //背景颜色
		GUI_SetColor(GUI_RED);
		GUI_SetFont(&GUI_Font24B_1);  //设置用于文字输出的字体	 uC/GUI  显示
		GUI_DispDecAt(temp, 245, 143, 2);
		
		/***********可燃气体*************/ 
		GUI_SetBkColor(GUI_CYAN);     //背景颜色
		GUI_SetColor(GUI_RED);
		GUI_SetFont(&GUI_Font24B_1);  //设置用于文字输出的字体	 uC/GUI  显示
		GUI_DispDecAt(temp, 284, 176, 2);		
		
	//	 GUIDEMO_Delay(1000);
		//	GUIDEMO_NotifyStartNext();
	//	break;

	}
	
	GUI_Clear();

}
