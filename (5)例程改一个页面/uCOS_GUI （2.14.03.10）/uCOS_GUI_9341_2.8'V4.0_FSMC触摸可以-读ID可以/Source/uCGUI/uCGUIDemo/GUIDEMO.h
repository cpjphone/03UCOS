/*
*********************************************************************************************************
*                                                uC/GUI
*                        Universal graphic software for embedded applications
*
*                       (c) Copyright 2002, Micrium Inc., Weston, FL
*                       (c) Copyright 2002, SEGGER Microcontroller Systeme GmbH
*
*              µC/GUI is protected by international copyright laws. Knowledge of the
*              source code may not be used to write a similar product. This file may
*              only be used in accordance with a license and should not be redistributed
*              in any way. We appreciate your understanding and fairness.
*
----------------------------------------------------------------------
File        : GUIDEMO.h
Purpose     : Multiple choice for emWin GSC
----------------------------------------------------------------------
*/


#ifndef GUIDEMO_H
#define GUIDEMO_H

#include "LCD_ConfDefaults.h"  /* valid LCD configuration */


#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif


extern const GUI_BITMAP bmMicriumLogo;



#define GUIDEMO_LARGE ((LCD_XSIZE >= 240) && (LCD_YSIZE >= 200))
#define GUIDEMO_TINY  ((LCD_XSIZE <  140) || (LCD_YSIZE <  100))

#if defined(__cplusplus)
  }
#endif

#endif

