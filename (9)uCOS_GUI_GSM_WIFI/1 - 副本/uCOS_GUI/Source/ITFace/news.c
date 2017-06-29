
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

extern int temp;
extern const GUI_BITMAP bmbackface;
extern u8 ReadDHT11(void);
extern u8 tdata[4];

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
		GUI_DispDecAt(tdata[1],141 , 46, 2);
		
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
		GUI_DispDecAt(temp, 202, 112, 2);
		
		GUI_SetBkColor(GUI_CYAN);     //������ɫ
		GUI_SetColor(GUI_RED);
		GUI_SetFont(&GUI_Font24B_1);  //���������������������	 uC/GUI  ��ʾ
		GUI_DispDecAt(temp, 242, 112, 2);
		
		/***********�������*************/  
		GUI_SetBkColor(GUI_CYAN);     //������ɫ
		GUI_SetColor(GUI_RED);
		GUI_SetFont(&GUI_Font24B_1);  //���������������������	 uC/GUI  ��ʾ
		GUI_DispDecAt(temp, 245, 143, 2);
		
		/***********��ȼ����*************/ 
		GUI_SetBkColor(GUI_CYAN);     //������ɫ
		GUI_SetColor(GUI_RED);
		GUI_SetFont(&GUI_Font24B_1);  //���������������������	 uC/GUI  ��ʾ
		GUI_DispDecAt(temp, 284, 176, 2);		
		
	//	 GUIDEMO_Delay(1000);
		//	GUIDEMO_NotifyStartNext();
	//	break;
	}
	
	GUI_Clear();

}
