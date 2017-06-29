/*********************************************************************************      
* 【功能】：硬件平台的初始化 
*********************************************************************************/
#include "includes.h"


void GPIO_Config(void);					  //GPIO配置
void GPIO_Config_LED(void);
void OS_CPU_SysTickInit(void);									   
//void RCC_Configuration(void);

/************************************************************************/
//系统时钟配置函数	
/************************************************************************/
//void RCC_Configuration(void)
//{
//	 ErrorStatus HSEStartUpStatus;                    //定义外部高速晶体启动状态枚举变量
//	 RCC_DeInit();                                    //复位RCC外部设备寄存器到默认值
//	 RCC_HSEConfig(RCC_HSE_ON);                       //打开外部高速晶振
//	 HSEStartUpStatus = RCC_WaitForHSEStartUp();      //等待外部高速时钟准备好
//	 if(HSEStartUpStatus == SUCCESS)                  //外部高速时钟已经准别好
//	  {
//		   FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable); 	//开启FLASH预读缓冲功能，加速FLASH的读取。所有程序中必须的用法.位置：RCC初始化子函数里面，时钟起振之后
//		   FLASH_SetLatency(FLASH_Latency_2);                   	 //flash操作的延时
//			    		
//						// RCC_HCLK  描述 
//				   	    // RCC_SYSCLK_Div1   AHB时钟 =  系统时钟 
//					    // RCC_SYSCLK_Div2   AHB时钟 =  系统时钟 / 2 
//						// RCC_SYSCLK_Div4   AHB时钟  = 系统时钟 / 4 
//						// RCC_SYSCLK_Div8   AHB时钟  =  系统时钟 / 8 
//						// RCC_SYSCLK_Div16  AHB时钟  =  系统时钟 / 16 
//						// RCC_SYSCLK_Div64  AHB时钟  =  系统时钟 / 64 
//						// RCC_SYSCLK_Div128 AHB时钟  =  系统时钟  / 128 
//						// RCC_SYSCLK_Div256 AHB时钟  =  系统时钟  / 256 
//						// RCC_SYSCLK_Div512 AHB时钟  =  系统时钟  / 512 
//								
//		   RCC_HCLKConfig(RCC_SYSCLK_Div1);               //配置AHB(HCLK)时钟等于==SYSCLK
//		   RCC_PCLK2Config(RCC_HCLK_Div1);                //配置APB2(PCLK2)钟==AHB时钟
//		   RCC_PCLK1Config(RCC_HCLK_Div2);                //配置APB1(PCLK1)钟==AHB1/2时钟
//		         
//		   RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);  //配置PLL时钟 == 外部高速晶体时钟 * 9 = 72MHz
//		   RCC_PLLCmd(ENABLE);                                   //使能PLL时钟
//		   
//		   while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)    //等待PLL时钟就绪
//		   {
//		   }
//		   RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);            //配置系统时钟 = PLL时钟
//		   while(RCC_GetSYSCLKSource() != 0x08)                  //检查PLL时钟是否作为系统时钟
//		   {
//		   }
//	  }

//}

/************************************************************************/
//ucos 系统节拍时钟初始化  初始设置为10ms一次节拍
/************************************************************************/
void  OS_CPU_SysTickInit(void)
{
    RCC_ClocksTypeDef  rcc_clocks;
    INT32U         cnts;
    RCC_GetClocksFreq(&rcc_clocks);		                        //获得系统时钟的值	 
    cnts = (INT32U)rcc_clocks.HCLK_Frequency/OS_TICKS_PER_SEC;	//算出时钟节拍的值	
	  SysTick_Config(cnts);										//设置时钟节拍	     
}

/************************************************************************/
//GPIO配置
/************************************************************************/
void GPIO_Config(void)
{


}

/************************************************************************/
//串口2中断配置
/************************************************************************/
void NVIC_Configuration(void)
{


}

/************************************************************************/
//GPIO配置	  （LED）
/************************************************************************/
void GPIO_Config_LED(void)
{

}

/************************************************************************/
//BSP初始化函数	  （BSP INITIALIZATION）
/************************************************************************/
void  BSP_Init(void)
{
//	RCC_Configuration();  
   /* Enable GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG and AFIO clocks */
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |RCC_APB2Periph_GPIOC 
//         | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOF | RCC_APB2Periph_GPIOG 
//         | RCC_APB2Periph_AFIO, ENABLE);
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
// 	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	
 	OS_CPU_SysTickInit() ;
	GPIO_Config(); 
	GPIO_Config_LED();

  NVIC_Configuration();
}

