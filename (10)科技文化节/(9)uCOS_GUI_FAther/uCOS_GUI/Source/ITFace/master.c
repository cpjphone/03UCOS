
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

extern const GUI_BITMAP bmmasterback;
extern int fire1,fire2;
BUTTON_Handle hButton[3];
int Wface;
//extern int fire1,fire2;
int t = 0;
void master(void)
{
	GUI_DrawBitmap(&bmmasterback, 0, 0);
	GUI_SetFont(&GUI_Font24B_1); 
	
	GUI_SetBkColor(GUI_CYAN);     //背景颜色
	while(1)
	{	
		hButton[0] = BUTTON_Create(30, 119, 111, 76, GUI_ID_BUTTON1, WM_CF_SHOW); 
		BUTTON_SetBkColor(hButton[0],0, GUI_BLUE);
		BUTTON_SetBkColor(hButton[0],1, GUI_RED);
		BUTTON_SetText(hButton[0],"A"); 

		hButton[1] = BUTTON_Create(178, 119, 111, 76, GUI_ID_BUTTON9, WM_CF_SHOW); 
		BUTTON_SetBkColor(hButton[1],0, GUI_BLUE);
		BUTTON_SetBkColor(hButton[1],1, GUI_RED);
		BUTTON_SetText(hButton[1],"B"); 
		GUI_SetBkColor(GUI_CYAN);
	//	WM_ExecIdle();		
		//GUI_ClearKeyBuffer();
		
		while(!t)
		{
			/*可放显示函数*/
			t = GUI_GetKey();
			if(fire1 || fire2) t = 99;
			GUI_SetBkColor(GUI_CYAN);     //背景颜色
			//if(fire1 || fire2) { Wface = 4; break;}
			GUI_Delay(50);
		}
		GUI_ClearKeyBuffer();
		switch(t)
		{
			case GUI_ID_BUTTON1 : Wface = 2;break;
			case GUI_ID_BUTTON9 : Wface = 3;break;
			case 99 :             Wface = 4;break;
			default : Wface = 1;
		}
		t = 0;
		BUTTON_Delete(hButton[0]);
		BUTTON_Delete(hButton[1]);
		break;
	}	
	
	GUI_Clear();
}



