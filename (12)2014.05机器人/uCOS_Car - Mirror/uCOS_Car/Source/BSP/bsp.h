/*********************************************************************************      
* 【功能】：BSP头文件
*********************************************************************************/

#ifndef  __BSP_H__
#define  __BSP_H__


#define TP_CS()  GPIO_ResetBits(GPIOB,GPIO_Pin_12)
#define TP_DCS() GPIO_SetBits(GPIOB,GPIO_Pin_12)

void BSP_Init(void);
void BSP_IntDisAll(void);
u16 TPReadX(void);
u16 TPReadY(void);


#endif                                                          /* End of module include.                               */
