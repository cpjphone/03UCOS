/*
*********************************************************************************************************
*                                                uC/GUI
*                        Universal graphic software for embedded applications
*
*                       (c) Copyright 2002, Micrium Inc., Weston, FL
*                       (c) Copyright 2002, SEGGER Microcontroller Systeme GmbH
*
*              礐/GUI is protected by international copyright laws. Knowledge of the
*              source code may not be used to write a similar product. This file may
*              only be used in accordance with a license and should not be redistributed
*              in any way. We appreciate your understanding and fairness.
*
----------------------------------------------------------------------
File        : GUIDEMO_Bitmap.c
Purpose     : Draws bitmaps with and without compression
----------------------------------------------------------------------
*/

#include "GUI.h"
#include "face.h"
#include <math.h>

//#if GUI_WINSUPPORT
//  #include "WM.h"
//#endif
extern const GUI_BITMAP bmidea;
#define PI4 12.5663706f

#define PICture bmidea 

/*********************************************************************
*
*       GUIDEMO_Bitmap
*
**********************************************************************
*/

void change(void) 
{
	
	int XSize = LCD_GetXSize();
	int YSize = LCD_GetYSize();
	
	
	GUIDEMO_ShowIntro("iDea",
					"Showing"
					"\nsimple and cheap "
					"\ncapacity"
					"\nhome furnishing");
	GUI_SetBkColor(GUI_BLUE);
	GUI_Clear();

		GUI_DispStringAt("our mark ", 10, 10);
		GUI_DrawBitmap(&PICture, 20, 50);
		GUIDEMO_Delay(500);
		GUIDEMO_NotifyStartNext();
		/* Tile display with image */
		{ 
			int ix, iy;
			for (ix = 0; ix < XSize / PICture.XSize + 1; ix++)
			{
				for (iy = 0; iy < YSize / PICture.YSize + 1; iy++)
				{
					GUI_DrawBitmap(&PICture, 
					PICture.XSize * ix , 
					PICture.YSize * iy);
				}
			}
		}
		GUIDEMO_Delay(1000);
		GUIDEMO_NotifyStartNext();
	//	GUIDEMO_ShowInfo("Bitmaps may also be\nmagnified and rotated");
		GUI_SetTextMode(GUI_TM_TRANS);	   //设置文本绘图模式
		GUI_SetFont(&GUI_Font16_1);
		{
			int i, tm;
			double xMul, Angle;
			for (i = 200; (i < 3000) && !GUIDEMO_CheckCancel();) 
			{
				tm = GUI_GetTime();
				GUI_DrawBitmapEx(&PICture, XSize / 2, YSize / 2, PICture.XSize / 2, PICture.YSize / 2, i, i);
			//	GUI_DispStringHCenterAt("Bitmaps can be magnified...", XSize / 2, 100);
				GUI_Exec();
				while ((GUI_GetTime() < (tm + 10)) && !GUIDEMO_CheckCancel());
				i += (GUI_GetTime() - tm) * 6;
			}
			GUIDEMO_Delay(2000);
			GUIDEMO_NotifyStartNext();
			GUI_Clear();
			GUI_DispStringHCenterAt("Warmth Offer", XSize / 2, ((YSize + PICture.YSize) >> 1) + 5);
			for (Angle = 0; Angle < PI4 && !GUIDEMO_CheckCancel();) 
			{
				tm = GUI_GetTime();
				xMul = cos(Angle) * 1000;
				GUI_ClearRect((XSize - PICture.XSize) >> 1, (YSize - PICture.YSize) >> 1, (XSize + PICture.XSize) >> 1, (YSize + PICture.YSize) >> 1);
				//在当前视窗的指定位置绘一反相的矩形区域
				GUI_DrawBitmapEx(&PICture, XSize / 2, YSize / 2, PICture.XSize / 2, PICture.YSize / 2, xMul, 1000);
				GUI_Exec();
				while ((GUI_GetTime() < (tm + 10)) && !GUIDEMO_CheckCancel());
				Angle += (GUI_GetTime() - tm) / 250.0f;
			}
			GUI_DrawBitmapEx(&PICture, XSize / 2, YSize / 2, PICture.XSize / 2, PICture.YSize / 2, 1000, 1000);
			GUIDEMO_Delay(1000);
		//	facenum = 2;
		    GUI_SetTextMode(GUI_TM_NORMAL);
			GUI_Clear();
			
			//GUIDEMO_Delay(1000);

		}
	
			                                    
}
