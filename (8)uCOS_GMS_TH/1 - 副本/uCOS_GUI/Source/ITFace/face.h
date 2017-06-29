
#ifndef FACE_H
#define FACE_H


#include "LCD_ConfDefaults.h"  /* valid LCD configuration */

void MainTask(void) ;
void news(void);
void change(void) ;
void GSMface(void) ;
int GUIDEMO_Delay(int t);
void GUIDEMO_NotifyStartNext(void);
int GUIDEMO_CheckCancel(void) ;
void GUIDEMO_Wait(void);
void GUIDEMO_ShowIntro(const char * s, const char * sExp);




#endif
