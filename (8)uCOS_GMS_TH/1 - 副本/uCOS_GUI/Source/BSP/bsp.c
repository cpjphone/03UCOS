/*********************************************************************************      
* 【功能】：硬件平台的初始化 
*********************************************************************************/
#include "includes.h"


void GPIO_Config(void);					  //GPIO配置
void GPIO_Config_LED(void);
void SPI_Config(void);					  //SPI配置
void  OS_CPU_SysTickInit(void);									   
void RCC_Configuration(void);

unsigned char SPI_WriteByte(unsigned char data) ;	 
void SpiDelay(unsigned int DelayCnt);


////JTAG模式设置定义
//#define JTAG_SWD_DISABLE   0X02
//#define SWD_ENABLE         0X01
//#define JTAG_SWD_ENABLE    0X00	
////JTAG模式设置,用于设置JTAG的模式
////mode:jtag,swd模式设置;00,全使能;01,使能SWD;10,全关闭;
////CHECK OK	
////100818		  
//void JTAG_Set(u8 mode)
//{
//	u32 temp;
//	temp=mode;
//	temp<<=25;
//	RCC->APB2ENR|=1<<0;     //开启辅助时钟	   
//	AFIO->MAPR&=0XF8FFFFFF; //清除MAPR的[26:24]
//	AFIO->MAPR|=temp;       //设置jtag模式
//} 



/************************************************************************/
//系统时钟配置函数	
/************************************************************************/
void RCC_Configuration(void)
{
	 ErrorStatus HSEStartUpStatus;                    //定义外部高速晶体启动状态枚举变量
	 RCC_DeInit();                                    //复位RCC外部设备寄存器到默认值
	 RCC_HSEConfig(RCC_HSE_ON);                       //打开外部高速晶振
	 HSEStartUpStatus = RCC_WaitForHSEStartUp();      //等待外部高速时钟准备好
	 if(HSEStartUpStatus == SUCCESS)                  //外部高速时钟已经准别好
	  {
		   FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable); 	//开启FLASH预读缓冲功能，加速FLASH的读取。所有程序中必须的用法.位置：RCC初始化子函数里面，时钟起振之后
		   FLASH_SetLatency(FLASH_Latency_2);                   	 //flash操作的延时
			    		
						// RCC_HCLK  描述 
				   	    // RCC_SYSCLK_Div1   AHB时钟 =  系统时钟 
					    // RCC_SYSCLK_Div2   AHB时钟 =  系统时钟 / 2 
						// RCC_SYSCLK_Div4   AHB时钟  = 系统时钟 / 4 
						// RCC_SYSCLK_Div8   AHB时钟  =  系统时钟 / 8 
						// RCC_SYSCLK_Div16  AHB时钟  =  系统时钟 / 16 
						// RCC_SYSCLK_Div64  AHB时钟  =  系统时钟 / 64 
						// RCC_SYSCLK_Div128 AHB时钟  =  系统时钟  / 128 
						// RCC_SYSCLK_Div256 AHB时钟  =  系统时钟  / 256 
						// RCC_SYSCLK_Div512 AHB时钟  =  系统时钟  / 512 
								
		   RCC_HCLKConfig(RCC_SYSCLK_Div1);               //配置AHB(HCLK)时钟等于==SYSCLK
		   RCC_PCLK2Config(RCC_HCLK_Div1);                //配置APB2(PCLK2)钟==AHB时钟
		   RCC_PCLK1Config(RCC_HCLK_Div2);                //配置APB1(PCLK1)钟==AHB1/2时钟
		         
		   RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);  //配置PLL时钟 == 外部高速晶体时钟 * 9 = 72MHz
		   RCC_PLLCmd(ENABLE);                                   //使能PLL时钟
		   
		   while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)    //等待PLL时钟就绪
		   {
		   }
		   RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);            //配置系统时钟 = PLL时钟
		   while(RCC_GetSYSCLKSource() != 0x08)                  //检查PLL时钟是否作为系统时钟
		   {
		   }
	  }

}

/************************************************************************/
//关中断（DISABLE ALL INTERRUPTS）
/************************************************************************/
void  BSP_IntDisAll (void)
{
  // CPU_IntDis();

  /* 这其实就代码临界段：“代码的临界段也称为临界区，指处理时不可分割的代码。
  一旦这部分代码开始执行，则不允许任何中断打入。为确保临界段代码的执行，在进入临界段之前要关中断
  ，而临界段代码执行完以后要立即开中断。”
   */
}

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
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_1 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* 温湿度数据入口 */
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0; //所有GPIO为同一类型端口
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;	 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //输出的最大频率为50HZ
	GPIO_Init(GPIOA, &GPIO_InitStructure);   //初始化GPIOB端口
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;  // 选择所有脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //配置成推挽式输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //输出模式下 I/O输出速度 50M HZ
  GPIO_Init(GPIOA, &GPIO_InitStructure);  //初始化PB口
	
	/* 第2步：将USART Tx的GPIO配置为推挽复用模式 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* 第3步：将USART Rx的GPIO配置为浮空输入模式
		由于CPU复位后，GPIO缺省都是浮空输入模式，因此下面这个步骤不是必须的
		但是，我还是建议加上便于阅读，并且防止其它地方修改了这个口线的设置参数
	*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	/*  第3步已经做了，因此这步可以不做*/
}

/************************************************************************/
//串口2中断配置
/************************************************************************/
void NVIC_Configuration(void)
{

  NVIC_InitTypeDef NVIC_InitStructure;
  
   /* Set the Vector Table base location at 0x08000000 */
   NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);
  
   /* Configure the NVIC Preemption Priority Bits */  
   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
  
   /* Enable the USART1 Interrupt */
   NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;       //通道设置为串口1中断
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	   //中断响应优先级0
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		   //打开中断
   NVIC_Init(&NVIC_InitStructure); 		
 
}

/************************************************************************/
//初始化串口硬件设备，启用中断
/************************************************************************/
void USART1_Configuration(void)
{
	//GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	/* 第1步：打开GPIO和USART部件的时钟 */
	

	/* 第4步：配置USART1参数
	    - BaudRate = 115200 baud
	    - Word Length = 8 Bits
	    - One Stop Bit
	    - No parity
	    - Hardware flow control disabled (RTS and CTS signals)
	    - Receive and transmit enabled
	*/
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART2, &USART_InitStructure);

    /* 若接收数据寄存器满，则产生中断 */
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

	/* 第5步：使能 USART1， 配置完毕 */
	USART_Cmd(USART2, ENABLE);

    /* 如下语句解决第1个字节无法正确发送出去的问题 */
  USART_ClearFlag(USART2, USART_FLAG_TC);     // 清标志
}

/************************************************************************/
//GPIO配置	  （LED）
/************************************************************************/
void GPIO_Config_LED(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		 //推挽输出
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIOC ->ODR ^= GPIO_Pin_6;
}

/************************************************************************/
//SPI初始化		   SPI 2 
/************************************************************************/
/*
 T_CS PA4
 SPI1_SCK PA5
 SPI1_MISO PA6
SPI1_MOSI PA7
   T_BUSY PA8
*/

void SPI_Config(void) 
{
	GPIO_InitTypeDef  GPIO_InitStructure; 
	SPI_InitTypeDef   SPI_InitStructure; 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	//SPI1 Periph clock enable 
	// RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE); 
	//SPI2 Periph clock enable 
	RCC_APB1PeriphClockCmd( RCC_APB1Periph_SPI2, ENABLE ) ;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	//Configure SPI1 pins: SCK, MISO and MOSI 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;   //复用推挽输出
	GPIO_Init(GPIOB,&GPIO_InitStructure); 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   //上拉输入
	GPIO_Init(GPIOB,&GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   //推挽输出
	GPIO_Init(GPIOB,&GPIO_InitStructure);	
	
	// SPI1 Config  
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; 
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master; 
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b; 
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low; 
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge; 
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;   //SPI_NSS_Hard
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64; 
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; 
	SPI_InitStructure.SPI_CRCPolynomial = 7; 
	SPI_Init(SPI2,&SPI_InitStructure); 
	
	// SPI1 enable  
	SPI_Cmd(SPI2,ENABLE); 

}

/************************************************************************/
//SPI写数据
/************************************************************************/
unsigned char SPI_WriteByte(unsigned char data) 
{ 
 unsigned char Data = 0; 

   //Wait until the transmit buffer is empty 
  while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_TXE)==RESET); 
  // Send the byte  
  SPI_I2S_SendData(SPI2,data); 

   //Wait until a data is received 
  while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_RXNE)==RESET); 
  // Get the received data 
  Data = SPI_I2S_ReceiveData(SPI2); 

  // Return the shifted data 
  return Data; 
} 

/************************************************************************/
//读写专用延时函数
/************************************************************************/ 
void SpiDelay(unsigned int DelayCnt)
{
 unsigned int i;
 for(i=0;i<DelayCnt;i++);
}

/************************************************************************/
//彩屏从..读..X轴方向坐标信息（☆☆☆）
/************************************************************************/
u16 TPReadX(void)
{ 
	u16 x=0;
	TP_CS();
	SpiDelay(10);
	SPI_WriteByte(0x90);
	SpiDelay(10);
	x=SPI_WriteByte(0x00);
	x<<=8;
	x+=SPI_WriteByte(0x00);
	SpiDelay(10);
	TP_DCS(); 
	x = x>>3;
	return (x);
}

/************************************************************************/
//彩屏从..读..Y轴方向坐标信息（☆☆☆）
/************************************************************************/
u16 TPReadY(void)
{
 u16 y=0;
  TP_CS();
  SpiDelay(10);
  SPI_WriteByte(0xD0);
  SpiDelay(10);
  y=SPI_WriteByte(0x00);
  y<<=8;
  y+=SPI_WriteByte(0x00);
  SpiDelay(10);
  TP_DCS();
  y = y>>3; 
  return (y);
}

/************************************************************************/
//BSP初始化函数	  （BSP INITIALIZATION）
/************************************************************************/
void  BSP_Init(void)
{
	RCC_Configuration();  
   /* Enable GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG and AFIO clocks */
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |RCC_APB2Periph_GPIOC 
         | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOF | RCC_APB2Periph_GPIOG 
         | RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
 	OS_CPU_SysTickInit() ;
	GPIO_Config(); 
	GPIO_Config_LED();
	SPI_Config();
	
  NVIC_Configuration();
	
  USART1_Configuration();
}

