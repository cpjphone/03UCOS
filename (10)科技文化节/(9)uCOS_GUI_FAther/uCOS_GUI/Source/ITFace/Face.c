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
#include "face.h"

#include "includes.h"
extern const GUI_BITMAP bmGSMback;
extern int Wface;
/*********************************************************************
*
*       MainTask
*
**********************************************************************
*/
void MainTask(void) 
{
	
  if(!Wface)
	change();
	Wface = 1;
	if(Wface == 1)
 	master();
 	if(Wface == 2)
 	news();
 	if(Wface == 3)
	news2();
	if(Wface == 4)
  GSMface();
 	GUI_Clear();

// GSMface();
} 


















