
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
//	GUI_SetColor(GUI_LIGHTRED);	  //	  Ԥ������ɫ   ����	
//	GUI_Clear();
	GUI_DrawBitmap(&bmGSMback, 0, 0);
	while(1)
	{
		
		/************�źŵ�·**************/  
		if(Esign == 2)
		{			
			GUI_SetBkColor(GUI_YELLOW);     //������ɫ
			GUI_SetColor(GUI_DARKRED);
			GUI_SetFont(&GUI_Font32_1);  //���������������������	 uC/GUI  ��ʾ
			//GUI_DispDecAt(temp, 200, 85, 2);
			GUI_DispStringAt("OK", 200, 85);		
		}
		/***********�Ƿ���*************/  
		if(Fsign == 2)
		{
			GUI_SetBkColor(GUI_LIGHTYELLOW);     //������ɫ
			GUI_SetColor(GUI_RED);
			GUI_SetFont(&GUI_Font32_1);  //���������������������	 uC/GUI  ��ʾ
			//GUI_DispDecAt(temp, 200, 129, 2);
			GUI_DispStringAt("OK", 200,129);
		}
		
		/***********�Ƿ����*************/ 
		if(Jsign == 2)
		{
			GUI_SetBkColor(GUI_DARKYELLOW);     //������ɫ
			GUI_SetColor(GUI_RED);
			GUI_SetFont(&GUI_Font32_1);  //���������������������	 uC/GUI  ��ʾ
			//GUI_DispDecAt(temp, 200, 174, 2);	
			GUI_DispStringAt("OK", 200, 174);	
		}
		
		 //GUIDEMO_Delay(1000);
		//	GUIDEMO_NotifyStartNext();
	}
}
