
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
extern u8 ReadDHT11(void);
extern u8 tdata[4];
extern int fire1;
extern int man1;

void news(void)
{
	//GUI_Init();
	GUI_SetColor(GUI_LIGHTRED);	  //	  Ԥ������ɫ   ����	
	GUI_Clear();
	GUI_DrawBitmap(&bmbackface, 0, 0);
	while(1)
	{
		//ReadDHT11();
		//GUI_Init();
		/************�¶�**************/  	
		GUI_SetBkColor(GUI_CYAN );     //������ɫ
		GUI_SetColor(GUI_RED);
		GUI_SetFont(&GUI_Font24B_1);  //���������������������	 uC/GUI  ��ʾ
		GUI_DispDecAt(tdata[2],105 , 46, 2);
		
		GUI_SetBkColor(GUI_CYAN);     //������ɫ
		GUI_SetColor(GUI_RED);
		GUI_SetFont(&GUI_Font24B_1);  //���������������������	 uC/GUI  ��ʾ
		GUI_DispDecAt(tdata[3],141 , 46, 2);
		
		/************ʪ��**************/  
		GUI_SetBkColor(GUI_CYAN );     //������ɫ
		GUI_SetColor(GUI_DARKRED);
		GUI_SetFont(&GUI_Font24B_1);  //���������������������	 uC/GUI  ��ʾ
		GUI_DispDecAt(tdata[0], 148, 81, 2);
		
		GUI_SetBkColor(GUI_CYAN  );     //������ɫ
		GUI_SetColor(GUI_DARKRED);
		GUI_SetFont(&GUI_Font24B_1);  //���������������������	 uC/GUI  ��ʾ
		GUI_DispDecAt(tdata[1], 186, 81, 2);
		
		/************��ѹ**************/  
		GUI_SetBkColor(GUI_CYAN);     //������ɫ
		GUI_SetColor(GUI_RED);
		GUI_SetFont(&GUI_Font24B_1);  //���������������������	 uC/GUI  ��ʾ
		GUI_DispDecAt(05, 202, 112, 2);
		
		GUI_SetBkColor(GUI_CYAN);     //������ɫ
		GUI_SetColor(GUI_RED);
		GUI_SetFont(&GUI_Font24B_1);  //���������������������	 uC/GUI  ��ʾ
		GUI_DispDecAt(00, 242, 112, 2);
		
		/***********�������*************/  
		GUI_SetBkColor(GUI_CYAN);     //������ɫ
		GUI_SetColor(GUI_RED);
		GUI_SetFont(&GUI_Font24B_1);  //���������������������	 uC/GUI  ��ʾ
		
		if(man1 == 1)
		{
			GUI_DispStringAt("Yes", 245, 143);		
		}
		else
		{
			GUI_DispStringAt("N O", 245, 143);
		}
		
		//GUI_DispDecAt(temp, 245, 143, 2);
		
		/***********��ȼ����*************/ 
		GUI_SetBkColor(GUI_CYAN);     //������ɫ
		GUI_SetColor(GUI_RED);
		GUI_SetFont(&GUI_Font24B_1);  //���������������������	 uC/GUI  ��ʾ
		if(fire1 == 1)
		{
			GUI_DispStringAt("Yes", 284, 176);		
		}
		else
		{
			GUI_DispStringAt("N O", 284, 176);
		}
		//GUI_DispStringAt("OK", 200, 85);
	//	 GUIDEMO_Delay(1000);
		//	GUIDEMO_NotifyStartNext();
	//	break;
	}
	
	GUI_Clear();

}
