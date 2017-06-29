#include <stddef.h>
#include "GUI.h"
#include "DIALOG.h"
#include "includes.h"
void on(WM_MESSAGE * pMsg)
{
	extern OS_EVENT* Led_on_SEM;
	OSSemPost(Led_on_SEM);

}

void off(WM_MESSAGE * pMsg)
{
	extern OS_EVENT* Led_off_SEM;
	OSSemPost(Led_off_SEM);  
}
