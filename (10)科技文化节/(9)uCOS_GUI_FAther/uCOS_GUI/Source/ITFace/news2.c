
#include "includes.h"
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

extern const GUI_BITMAP bmbackface;
extern u8 tdata2[4];
extern int fire1,fire2;
extern int man2;

extern int Wface;
BUTTON_Handle chButton;
void news2(void)
{
	GUI_SetColor(GUI_LIGHTRED);	  //	  预定义颜色   淡红	
	GUI_Clear();
	GUI_DrawBitmap(&bmbackface, 0, 0);
	GUI_SetFont(&GUI_Font8x16);

	while(1)
	{
		chButton = BUTTON_Create(28, 177, 80, 50, GUI_ID_BUTTON5, WM_CF_SHOW); 
		BUTTON_SetBkColor(chButton,0, GUI_BLUE);
		BUTTON_SetBkColor(chButton,1, GUI_RED);
  	BUTTON_SetText(chButton,"return"); 
	//	WM_ExecIdle();		
		while(GUI_GetKey()!= GUI_ID_BUTTON5)
		{	
			/************温度**************/  	
			GUI_SetBkColor(GUI_CYAN );     //背景颜色
			GUI_SetColor(GUI_RED);
			GUI_SetFont(&GUI_Font24B_1);  //设置用于文字输出的字体	 uC/GUI  显示
			GUI_DispDecAt(tdata2[2],105 , 46, 2);
			
			GUI_SetBkColor(GUI_CYAN);     //背景颜色
			GUI_SetColor(GUI_RED);
			GUI_SetFont(&GUI_Font24B_1);  //设置用于文字输出的字体	 uC/GUI  显示
			GUI_DispDecAt(tdata2[1],141 , 46, 2);
			
			/************湿度**************/  
			GUI_SetBkColor(GUI_CYAN );     //背景颜色
			GUI_SetColor(GUI_DARKRED);
			GUI_SetFont(&GUI_Font24B_1);  //设置用于文字输出的字体	 uC/GUI  显示
			GUI_DispDecAt(tdata2[0], 148, 81, 2);
			
			GUI_SetBkColor(GUI_CYAN  );     //背景颜色
			GUI_SetColor(GUI_DARKRED);
			GUI_SetFont(&GUI_Font24B_1);  //设置用于文字输出的字体	 uC/GUI  显示
			GUI_DispDecAt(tdata2[1], 186, 81, 2);
			
			/************电压**************/  
			GUI_SetBkColor(GUI_CYAN);     //背景颜色
			GUI_SetColor(GUI_RED);
			GUI_SetFont(&GUI_Font24B_1);  //设置用于文字输出的字体	 uC/GUI  显示
			GUI_DispDecAt(05, 202, 112, 2);
			
			GUI_SetBkColor(GUI_CYAN);     //背景颜色
			GUI_SetColor(GUI_RED);
			GUI_SetFont(&GUI_Font24B_1);  //设置用于文字输出的字体	 uC/GUI  显示
			GUI_DispDecAt(00, 242, 112, 2);
			
			/***********人体红外*************/  
			GUI_SetBkColor(GUI_CYAN);     //背景颜色
			GUI_SetColor(GUI_RED);
			GUI_SetFont(&GUI_Font24B_1);  //设置用于文字输出的字体	 uC/GUI  显示
			
			if(man2)
			{
				GUI_DispStringAt("Yes", 245, 143);		
			}
			else
			{
				GUI_DispStringAt("N O", 245, 143);
			}
			
			//GUI_DispDecAt(temp, 245, 143, 2);
			
			/***********可燃气体*************/ 
			GUI_SetBkColor(GUI_CYAN);     //背景颜色
			GUI_SetColor(GUI_RED);
			GUI_SetFont(&GUI_Font24B_1);  //设置用于文字输出的字体	 uC/GUI  显示
			if(fire2)
			{
				GUI_DispStringAt("Yes", 284, 176);		
			}
			else if(fire1) break;
			else
			{
				GUI_DispStringAt("N O", 284, 176);
			}
			GUI_Delay(50); 
		}
				BUTTON_Delete(chButton);		    
				if((fire1)||(fire2)) Wface = 4;
				else Wface = 1;
				GUI_ClearKeyBuffer();
				break;
	}	
	GUI_Clear();
}



