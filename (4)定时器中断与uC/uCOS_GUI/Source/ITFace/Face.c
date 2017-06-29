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


//extern temp; 


//EventsFunctionList
//EndofEventsFunctionList


/*********************************************************************
*
*       static data
*
**********************************************************************
*/



/*********************************************************************
*
*       Dialog resource
*
* This table conatins the info required to create the dialog.
* It has been created by ucGUIbuilder.
*/

static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
    { FRAMEWIN_CreateIndirect,  "Caption",           0,                       0,  0,  320,240,FRAMEWIN_CF_MOVEABLE,0},
    { EDIT_CreateIndirect,      "0",                 GUI_ID_EDIT1,            100,46, 30, 22, 0,0},
    { TEXT_CreateIndirect,      "Tem :",             GUI_ID_TEXT0,            22, 39, 72, 30, 0,0},
    { TEXT_CreateIndirect,      "o",                 GUI_ID_TEXT1,            145,30, 11, 16, 0,0},
    { TEXT_CreateIndirect,      "C",                 GUI_ID_TEXT2,            162,46, 47, 23, 0,0}
};



/*****************************************************************
**      FunctionName:void PaintDialog(WM_MESSAGE * pMsg)
**      Function: to initialize the Dialog items
**                                                      
**      call this function in _cbCallback --> WM_PAINT
*****************************************************************/

void PaintDialog(WM_MESSAGE * pMsg)
{
    WM_HWIN hWin = pMsg->hWin;

}



/*****************************************************************
**      FunctionName:void InitDialog(WM_MESSAGE * pMsg)
**      Function: to initialize the Dialog items
**                                                      
**      call this function in _cbCallback --> WM_INIT_DIALOG
*****************************************************************/

void InitDialog(WM_MESSAGE * pMsg)
{
    WM_HWIN hWin = pMsg->hWin;
    //
    //FRAMEWIN
    //
    FRAMEWIN_SetClientColor(hWin,0x7fff00);
    FRAMEWIN_SetTitleVis(hWin,0);
    //
    //GUI_ID_EDIT1
    //
    EDIT_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_EDIT1),0,0x0000ff);
    EDIT_SetFont(WM_GetDialogItem(hWin,GUI_ID_EDIT1),&GUI_Font16B_1);
    EDIT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_EDIT1),GUI_TA_VCENTER|GUI_TA_RIGHT);
    EDIT_SetDecMode(WM_GetDialogItem(hWin,GUI_ID_EDIT1),0,0,100,0,0);
//	EDIT_SetValue(WM_GetDialogItem(hWin,GUI_ID_EDIT1),temp);
    //
    //GUI_ID_TEXT0
    //
    TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT0),0x7fff00);
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT0),&GUI_Font24B_ASCII);
    TEXT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_TEXT0),GUI_TA_VCENTER|GUI_TA_CENTER);
    //
    //GUI_ID_TEXT1
    //
    TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT1),0x7fff00);
    TEXT_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_TEXT1),0xff0000);
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT1),&GUI_Font13_1);
    TEXT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_TEXT1),GUI_TA_BOTTOM|GUI_TA_LEFT);
    //
    //GUI_ID_TEXT2
    //
    TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT2),0x7fff00);
    TEXT_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_TEXT2),0xff0000);
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT2),&GUI_Font24_ASCII);

}




/*********************************************************************
*
*       Dialog callback routine
*/
static void _cbCallback(WM_MESSAGE * pMsg) 
{
    int NCode, Id;
    WM_HWIN hWin = pMsg->hWin;
    switch (pMsg->MsgId) 
    {
        case WM_PAINT:
            PaintDialog(pMsg);
            break;
        case WM_INIT_DIALOG:
            InitDialog(pMsg);
            break;
        case WM_KEY:
            switch (((WM_KEY_INFO*)(pMsg->Data.p))->Key) 
            {
                case GUI_KEY_ESCAPE:
                    GUI_EndDialog(hWin, 1);
                    break;
                case GUI_KEY_ENTER:
                    GUI_EndDialog(hWin, 0);
                    break;
            }
            break;
        case WM_NOTIFY_PARENT:
            Id = WM_GetId(pMsg->hWinSrc); 
            NCode = pMsg->Data.v;        
            switch (Id) 
            {
                case GUI_ID_OK:
                    if(NCode==WM_NOTIFICATION_RELEASED)
                        GUI_EndDialog(hWin, 0);
                    break;
                case GUI_ID_CANCEL:
                    if(NCode==WM_NOTIFICATION_RELEASED)
                        GUI_EndDialog(hWin, 0);
                    break;

            }
            break;
        default:
            WM_DefaultProc(pMsg);
    }
}


/*********************************************************************
*
*       MainTask
*
**********************************************************************
*/
void MainTask(void) 
{ 
    GUI_Init();
    WM_SetDesktopColor(GUI_WHITE);      /* Automacally update desktop window */
    WM_SetCreateFlags(WM_CF_MEMDEV);  /* Use memory devices on all windows to avoid flicker */
    //PROGBAR_SetDefaultSkin(PROGBAR_SKIN_FLEX);
    //FRAMEWIN_SetDefaultSkin(FRAMEWIN_SKIN_FLEX);
    //PROGBAR_SetDefaultSkin(PROGBAR_SKIN_FLEX);
    //BUTTON_SetDefaultSkin(BUTTON_SKIN_FLEX);
    //CHECKBOX_SetDefaultSkin(CHECKBOX_SKIN_FLEX);
    //DROPDOWN_SetDefaultSkin(DROPDOWN_SKIN_FLEX);
    //SCROLLBAR_SetDefaultSkin(SCROLLBAR_SKIN_FLEX);
    //SLIDER_SetDefaultSkin(SLIDER_SKIN_FLEX);
    //HEADER_SetDefaultSkin(HEADER_SKIN_FLEX);
    //RADIO_SetDefaultSkin(RADIO_SKIN_FLEX);
    GUI_ExecDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), &_cbCallback, 0, 0, 0);
}

