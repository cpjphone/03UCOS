///*
//*********************************************************************************************************
//*                                                uC/GUI
//*                        Universal graphic software for embedded applications
//*
//*                       (c) Copyright 2002, Micrium Inc., Weston, FL
//*                       (c) Copyright 2002, SEGGER Microcontroller Systeme GmbH
//*
//*              礐/GUI is protected by international copyright laws. Knowledge of the
//*              source code may not be used to write a similar product. This file may
//*              only be used in accordance with a license and should not be redistributed
//*              in any way. We appreciate your understanding and fairness.
//*
//----------------------------------------------------------------------
//File        : GUIDEMO_Intro.c
//Purpose     : Introduction for 礐/GUI generic demo
//              (This is also a good file to demo and explain basic
//              uC/GUI features by setting breakpoints)
//----------------------------------------------------------------------
//*/
//
//#include "GUI.H"
//#include "GUIDEMO.H"
//#include <string.h>
//
///*********************************************************************
//*
//*       GUIDEMO_Intro
//*
//**********************************************************************
//*/
//
//#if GUIDEMO_LARGE
//
//void GUIDEMO_Intro(void)
//{
//	int xCenter = LCD_GET_XSIZE() / 2;
//	int y;
//	char acText[50] = "Version of 礐/GUI: ";
//	strcat(acText, GUI_GetVersionString());  //返回一个字符串包含当前μC/GUI的版本
//	GUI_SetBkColor(GUI_BLUE);     //背景颜色
//	GUI_SetColor(GUI_LIGHTRED);	  //	  预定义颜色   淡红 
//	GUI_Clear();
//
//	GUI_SetFont(&GUI_Font32B_1);  //设置用于文字输出的字体	 uC/GUI  显示
//
//
//	GUI_DispStringHCenterAt("礐/GUI", xCenter, y= 15);
//	GUI_SetColor(GUI_WHITE);	  //设置当前前景颜色 
//	GUI_SetFont(&GUI_Font13H_ASCII);
//	GUI_DispStringHCenterAt("Universal graphic software"
//	"\nfor embedded applications"
//	, xCenter, y += 30);
//	GUI_SetColor(GUI_LIGHTRED);
//	GUI_SetFont(&GUI_Font16_ASCII);
//	GUI_DispStringHCenterAt("Any CPU - Any LCD - Any Application"
//	, xCenter, y += 40);
//	GUI_SetFont(&GUI_Font10S_ASCII);
//	GUI_DispStringHCenterAt("Compiled " __DATE__ " "__TIME__, xCenter, y += 25);
//	GUI_SetFont(&GUI_Font13HB_1);
//	GUI_SetColor(GUI_WHITE);
//	GUI_DispStringHCenterAt(acText, xCenter, y += 21);			
//	GUI_SetFont(&GUI_FontComic18B_1);
//	GUI_SetColor(GUI_RED);
//	GUI_DispStringHCenterAt("www.PowerRAM.com", LCD_GET_XSIZE() / 2, LCD_GET_YSIZE() - 40);	
//	GUI_DrawBitmap(&bmMicriumLogo, (LCD_GET_XSIZE() - bmMicriumLogo.XSize) / 2, 150);
//					//在当前视窗的指定位置绘一幅位图
//	GUI_SetColor(GUI_WHITE);
//	GUI_SetFont(&GUI_Font10S_ASCII);
//	GUI_DispStringAt("GUI _OS: ",3,210); GUI_DispDecMin(GUI_OS);	 //左下角文字 GUI_DispDecMin：在当前坐标显示最少数量字符的十进制数值,GUI_OS:	激活多任务支持的启用
//	GUI_DispStringAt("GUI_ALLOC_SIZE: ",3, 220); GUI_DispDecMin(GUI_ALLOC_SIZE); //			GUI_ALLOC_SIZE:	定义可选择的动态存储器的尺寸
//	GUI_DispStringAt("Compiler:"
//	#ifdef _MSC_VER
//	"Microsoft"
//	#elif defined (NC308)
//	"Mitsubishi NC308"
//	#elif defined (NC30)
//	"Mitsubishi NC30"
//	#elif defined (__TID__)
//	#if (((__TID__ >>8) &0x7f) == 48)            /* IAR MC80 */
//	"IAR M32C"
//	#elif (((__TID__ >>8) &0x7f) == 85)          /* IAR V850 */
//	"IAR V850"
//	#else                                        /* IAR MC16 */
//	"IAR M32C"
//	#endif
//	#else
//	"RealViewMDK 3.40"
//	#endif
//	,0, 230);
//	GUIDEMO_Delay(5000);
//}
//
//#else
//
//void GUIDEMO_Intro(void) {
//  int xCenter = LCD_GET_XSIZE() / 2;
//  int y;
//  char acText[50] = "Version of 礐/GUI: ";
//  strcat(acText, GUI_GetVersionString());
//  GUI_SetBkColor(GUI_BLUE);
//  GUI_SetColor(GUI_YELLOW);
//  GUI_Clear();
//  GUI_SetFont(&GUI_Font13B_1);
//  GUI_DispStringHCenterAt("礐/GUI", xCenter, y= 10);
//  GUI_SetFont(&GUI_Font10_ASCII);
//  GUI_SetColor(GUI_WHITE);
//  GUI_DispStringHCenterAt("Universal graphic software"
//                          "\nfor embedded applications"
//                          , xCenter, y += 20);
//  GUI_SetFont(&GUI_Font10S_ASCII);
//  GUI_DispStringHCenterAt("Compiled " __DATE__ " "__TIME__, xCenter, y += 25);
//  GUI_DispStringHCenterAt(acText, xCenter, y += 16);
//  GUIDEMO_Delay(5000);
//
//  GUI_Clear();
//  GUI_DrawBitmap(&bmMicriumLogo, (LCD_GET_XSIZE() - bmMicriumLogo.XSize) / 2, 6);
//  GUI_SetFont(&GUI_Font13B_1);
//  GUI_DispStringHCenterAt("www.PowerAVR.com", LCD_GET_XSIZE() / 2, LCD_GET_YSIZE() - 50);
//  GUIDEMO_Delay(5000);
//
//
//}
//
//#endif
