#include "stm32f10x_lib.h"

/*硬件相关的宏定义*/
/********************************************************************************/
#define Set_Cs  //GPIO_SetBits(GPIOC,GPIO_Pin_4);//GPIOC->BSRR  = 0x00000010;
#define Clr_Cs  //GPIO_ResetBits(GPIOC,GPIO_Pin_4);//GPIOC->BRR   = 0x00000010;

#define Set_Rs  //GPIO_SetBits(GPIOA,GPIO_Pin_3);	//GPIOC->BSRR  = 0x00002000;
#define Clr_Rs  //GPIO_ResetBits(GPIOA,GPIO_Pin_3);//GPIOC->BRR   = 0x00002000;

#define Set_nWr //GPIO_SetBits(GPIOC,GPIO_Pin_7);	//GPIOC->BSRR  = 0x00004000;
#define Clr_nWr //GPIO_ResetBits(GPIOC,GPIO_Pin_7);//GPIOC->BRR   = 0x00004000;

#define Set_nRd //GPIO_SetBits(GPIOC,GPIO_Pin_6);	//GPIOC->BSRR  = 0x00008000;
#define Clr_nRd //GPIO_ResetBits(GPIOC,GPIO_Pin_6);//GPIOC->BRR   = 0x00008000;
/********************************************************************************/

void Lcd_Configuration(void);
void ili9320_Initializtion(void);
void ili9320_WriteRegister(u16 index,u16 dat);
void ili9320_SetCursor(u16 x,u16 y);
void ili9320_SetWindows(u16 StartX,u16 StartY,u16 EndX,u16 EndY);
void ili9320_DrawPicture(u16 StartX,u16 StartY,u16 EndX,u16 EndY,u16 *pic);
void ili9320_SetPoint(u16 x,u16 y,u16 point);
void ili9320_PutChar(u16 x,u16 y,u8 c,u16 charColor,u16 bkColor);
void ili9320_Clear(u16 dat);
void ili9320_Delay(u32 nCount);
void ili9320_Test(void);
u16 ili9320_GetCode(void);
void ili9320_WriteData(u16 dat);
void ili9320_WriteIndex(u16 idx);

u16 ili9320_BGR2RGB(u16 c);

u16 ili9320_GetPoint(u16 x,u16 y);
u16 ili9320_ReadData(void);
u16 ili9320_ReadRegister(u16 index);

u16 GUI_Color565(u32 RGB);  // RGB颜色转为16位(565)

void GUI_Text(u16 x, u16 y, u8 *str, u16 len,u16 Color, u16 bkColor);
void GUI_Line(u16 x0, u16 y0, u16 x1, u16 y1,u16 color);  // 画线
void GUI_Circle(u16 cx,u16 cy,u16 r,u16 color,u8 fill);  // 画园
void GUI_Rectangle(u16 x0, u16 y0, u16 x1, u16 y1,u16 color,u8 fill); // 画矩形
void GUI_Square(u16 x0, u16 y0, u16 with, u16 color,u8 fill);  // 画正方形


void Touch_Initializtion(void);
u16  Touch_GetPhyX(void);
u16  Touch_GetPhyY(void);
u16  Touch_MeasurementX(void);
u16  Touch_MeasurementY(void);


