/*********************************************************************************      
* °æπ¶ƒ‹°ø£∫”≤º˛∆ΩÃ®µƒ≥ı ºªØ 
*********************************************************************************/
#include "includes.h"


void GPIO_Config(void);					  //GPIO≈‰÷√
void GPIO_Config_LED(void);
void SPI_Config(void);					  //SPI≈‰÷√
void  OS_CPU_SysTickInit(void);									   
void RCC_Configuration(void);

unsigned char SPI_WriteByte(unsigned char data) ;	 
void SpiDelay(unsigned int DelayCnt);


////JTAGƒ£ Ω…Ë÷√∂®“Â
//#define JTAG_SWD_DISABLE   0X02
//#define SWD_ENABLE         0X01
//#define JTAG_SWD_ENABLE    0X00	
////JTAGƒ£ Ω…Ë÷√,”√”⁄…Ë÷√JTAGµƒƒ£ Ω
////mode:jtag,swdƒ£ Ω…Ë÷√;00,»´ πƒ‹;01, πƒ‹SWD;10,»´πÿ±’;
////CHECK OK	
////100818		  
//void JTAG_Set(u8 mode)
//{
//	u32 temp;
//	temp=mode;
//	temp<<=25;
//	RCC->APB2ENR|=1<<0;     //ø™∆Ù∏®÷˙ ±÷”	   
//	AFIO->MAPR&=0XF8FFFFFF; //«Â≥˝MAPRµƒ[26:24]
//	AFIO->MAPR|=temp;       //…Ë÷√jtagƒ£ Ω
//} 



/************************************************************************/
//œµÕ≥ ±÷”≈‰÷√∫Ø ˝	
/************************************************************************/
void RCC_Configuration(void)
{
	 ErrorStatus HSEStartUpStatus;                    //∂®“ÂÕ‚≤ø∏ﬂÀŸæßÃÂ∆Ù∂Ø◊¥Ã¨√∂æŸ±‰¡ø
	 RCC_DeInit();                                    //∏¥ŒªRCCÕ‚≤ø…Ë±∏ºƒ¥Ê∆˜µΩƒ¨»œ÷µ
	 RCC_HSEConfig(RCC_HSE_ON);                       //¥Úø™Õ‚≤ø∏ﬂÀŸæß’Ò
	 HSEStartUpStatus = RCC_WaitForHSEStartUp();      //µ»¥˝Õ‚≤ø∏ﬂÀŸ ±÷”◊º±∏∫√
	 if(HSEStartUpStatus == SUCCESS)                  //Õ‚≤ø∏ﬂÀŸ ±÷”“—æ≠◊º±∫√
	  {
		   FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable); 	//ø™∆ÙFLASH‘§∂¡ª∫≥Âπ¶ƒ‹£¨º”ÀŸFLASHµƒ∂¡»°°£À˘”–≥Ã–Ú÷–±ÿ–Îµƒ”√∑®.Œª÷√£∫RCC≥ı ºªØ◊”∫Ø ˝¿Ô√Ê£¨ ±÷”∆’Ò÷Æ∫Û
		   FLASH_SetLatency(FLASH_Latency_2);                   	 //flash≤Ÿ◊˜µƒ—” ±
			    		
						// RCC_HCLK  √Ë ˆ 
				   	    // RCC_SYSCLK_Div1   AHB ±÷” =  œµÕ≥ ±÷” 
					    // RCC_SYSCLK_Div2   AHB ±÷” =  œµÕ≥ ±÷” / 2 
						// RCC_SYSCLK_Div4   AHB ±÷”  = œµÕ≥ ±÷” / 4 
						// RCC_SYSCLK_Div8   AHB ±÷”  =  œµÕ≥ ±÷” / 8 
						// RCC_SYSCLK_Div16  AHB ±÷”  =  œµÕ≥ ±÷” / 16 
						// RCC_SYSCLK_Div64  AHB ±÷”  =  œµÕ≥ ±÷” / 64 
						// RCC_SYSCLK_Div128 AHB ±÷”  =  œµÕ≥ ±÷”  / 128 
						// RCC_SYSCLK_Div256 AHB ±÷”  =  œµÕ≥ ±÷”  / 256 
						// RCC_SYSCLK_Div512 AHB ±÷”  =  œµÕ≥ ±÷”  / 512 
								
		   RCC_HCLKConfig(RCC_SYSCLK_Div1);               //≈‰÷√AHB(HCLK) ±÷”µ»”⁄==SYSCLK
		   RCC_PCLK2Config(RCC_HCLK_Div1);                //≈‰÷√APB2(PCLK2)÷”==AHB ±÷”
		   RCC_PCLK1Config(RCC_HCLK_Div2);                //≈‰÷√APB1(PCLK1)÷”==AHB1/2 ±÷”
		         
		   RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);  //≈‰÷√PLL ±÷” == Õ‚≤ø∏ﬂÀŸæßÃÂ ±÷” * 9 = 72MHz
		   RCC_PLLCmd(ENABLE);                                   // πƒ‹PLL ±÷”
		   
		   while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)    //µ»¥˝PLL ±÷”æÕ–˜
		   {
		   }
		   RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);            //≈‰÷√œµÕ≥ ±÷” = PLL ±÷”
		   while(RCC_GetSYSCLKSource() != 0x08)                  //ºÏ≤ÈPLL ±÷” «∑Ò◊˜Œ™œµÕ≥ ±÷”
		   {
		   }
	  }

}

/************************************************************************/
//πÿ÷–∂œ£®DISABLE ALL INTERRUPTS£©
/************************************************************************/
void  BSP_IntDisAll (void)
{
  // CPU_IntDis();

  /* ’‚∆‰ µæÕ¥˙¬Î¡ŸΩÁ∂Œ£∫°∞¥˙¬Îµƒ¡ŸΩÁ∂Œ“≤≥∆Œ™¡ŸΩÁ«¯£¨÷∏¥¶¿Ì ±≤ªø…∑÷∏Óµƒ¥˙¬Î°£
  “ªµ©’‚≤ø∑÷¥˙¬Îø™ º÷¥––£¨‘Ú≤ª‘ –Ì»Œ∫Œ÷–∂œ¥Ú»Î°£Œ™»∑±£¡ŸΩÁ∂Œ¥˙¬Îµƒ÷¥––£¨‘⁄Ω¯»Î¡ŸΩÁ∂Œ÷Æ«∞“™πÿ÷–∂œ
  £¨∂¯¡ŸΩÁ∂Œ¥˙¬Î÷¥––ÕÍ“‘∫Û“™¡¢º¥ø™÷–∂œ°£°±
   */
}

/************************************************************************/
//ucos œµÕ≥Ω⁄≈ƒ ±÷”≥ı ºªØ  ≥ı º…Ë÷√Œ™10ms“ª¥ŒΩ⁄≈ƒ
/************************************************************************/
void  OS_CPU_SysTickInit(void)
{
    RCC_ClocksTypeDef  rcc_clocks;
    INT32U         cnts;
    RCC_GetClocksFreq(&rcc_clocks);		                        //ªÒµ√œµÕ≥ ±÷”µƒ÷µ	 
    cnts = (INT32U)rcc_clocks.HCLK_Frequency/OS_TICKS_PER_SEC;	//À„≥ˆ ±÷”Ω⁄≈ƒµƒ÷µ	
	SysTick_Config(cnts);										//…Ë÷√ ±÷”Ω⁄≈ƒ	     
}

/************************************************************************/
//GPIO≈‰÷√
/************************************************************************/
void GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		 //Õ∆ÕÏ ‰≥ˆ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_1 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		 //Õ∆ÕÏ ‰≥ˆ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* Œ¬ ™∂» ˝æ›»Îø⁄ */
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_1; //À˘”–GPIOŒ™Õ¨“ª¿‡–Õ∂Àø⁄
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;	 //Õ∆ÕÏ ‰≥ˆ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 // ‰≥ˆµƒ◊Ó¥Û∆µ¬ Œ™50HZ
	GPIO_Init(GPIOA, &GPIO_InitStructure);   //≥ı ºªØGPIOB∂Àø⁄
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;  // —°‘ÒÀ˘”–Ω≈
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //≈‰÷√≥…Õ∆ÕÏ Ω ‰≥ˆ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // ‰≥ˆƒ£ Ωœ¬ I/O ‰≥ˆÀŸ∂» 50M HZ
  GPIO_Init(GPIOA, &GPIO_InitStructure);  //≥ı ºªØPBø⁄
	
	/* µ⁄2≤Ω£∫Ω´USART TxµƒGPIO≈‰÷√Œ™Õ∆ÕÏ∏¥”√ƒ£ Ω */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* µ⁄3≤Ω£∫Ω´USART RxµƒGPIO≈‰÷√Œ™∏°ø’ ‰»Îƒ£ Ω
		”…”⁄CPU∏¥Œª∫Û£¨GPIO»± °∂º «∏°ø’ ‰»Îƒ£ Ω£¨“Ú¥Àœ¬√Ê’‚∏ˆ≤Ω÷Ë≤ª «±ÿ–Îµƒ
		µ´ «£¨Œ“ªπ «Ω®“Èº”…œ±„”⁄‘ƒ∂¡£¨≤¢«“∑¿÷π∆‰À¸µÿ∑Ω–ﬁ∏ƒ¡À’‚∏ˆø⁄œﬂµƒ…Ë÷√≤Œ ˝
	*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	/*  µ⁄3≤Ω“—æ≠◊ˆ¡À£¨“Ú¥À’‚≤Ωø…“‘≤ª◊ˆ*/
	
	//≈‰÷√USARTx_TxŒ™∏¥∫œÕ∆ÕÏ ‰≥ˆ
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  //≈‰÷√ USARTx_Rx Œ™∏°ø’ ‰»Î
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/************************************************************************/
//¥Æø⁄2÷–∂œ≈‰÷√
/************************************************************************/
void NVIC_Configuration(void)
{

  NVIC_InitTypeDef NVIC_InitStructure;
  
   /* Set the Vector Table base location at 0x08000000 */
   NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);
  
   /* Configure the NVIC Preemption Priority Bits */  
   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
  
   /* Enable the USART1 Interrupt */
   NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;       //Õ®µ¿…Ë÷√Œ™¥Æø⁄1÷–∂œ
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	   //÷–∂œœÏ”¶”≈œ»º∂0
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		   //¥Úø™÷–∂œ
   NVIC_Init(&NVIC_InitStructure); 		
 
}

/************************************************************************/
//¥Æø⁄1÷–∂œ≈‰÷√
/************************************************************************/
void NVIC_Configuration2(void)
{
   NVIC_InitTypeDef NVIC_InitStructure;
  
   /* Set the Vector Table base location at 0x08000000 */
   NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);
  
   /* Configure the NVIC Preemption Priority Bits */  
   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
  
   /* Enable the USART1 Interrupt */
   NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;       //Õ®µ¿…Ë÷√Œ™¥Æø⁄1÷–∂œ
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	   //÷–∂œœÏ”¶”≈œ»º∂0
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		   //¥Úø™÷–∂œ
   NVIC_Init(&NVIC_InitStructure); 						   //≥ı ºªØ
}

/************************************************************************/
//≥ı ºªØ¥Æ2⁄”≤º˛…Ë±∏£¨∆Ù”√÷–∂œ
/************************************************************************/
void USART2_Configuration(void)
{
	//GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	/* µ⁄1≤Ω£∫¥Úø™GPIO∫ÕUSART≤øº˛µƒ ±÷” */
	

	/* µ⁄4≤Ω£∫≈‰÷√USART1≤Œ ˝
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

    /* »ÙΩ” ’ ˝æ›ºƒ¥Ê∆˜¬˙£¨‘Ú≤˙…˙÷–∂œ */
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

	/* µ⁄5≤Ω£∫ πƒ‹ USART1£¨ ≈‰÷√ÕÍ±œ */
	USART_Cmd(USART2, ENABLE);

    /* »Áœ¬”Ôæ‰Ω‚æˆµ⁄1∏ˆ◊÷Ω⁄Œﬁ∑®’˝»∑∑¢ÀÕ≥ˆ»•µƒŒ Ã‚ */
  USART_ClearFlag(USART2, USART_FLAG_TC);     // «Â±Í÷æ
}

/************************************************************************/
//≥ı ºªØ¥Æ1⁄”≤º˛…Ë±∏£¨∆Ù”√÷–∂œ
/************************************************************************/
void USART1_Configuration ()
{
	USART_InitTypeDef USART_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	//¥Æø⁄≈‰÷√£∫ ≤®Ãÿ¬  115200  ˝æ›Œª 8 Õ£÷πŒª 1  ∆Ê≈ºŒª NONE
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity =  USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
	/* »ÙΩ” ’ ˝æ›ºƒ¥Ê∆˜¬˙£¨‘Ú≤˙…˙÷–∂œ */
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

    /* »Áœ¬”Ôæ‰Ω‚æˆµ⁄1∏ˆ◊÷Ω⁄Œﬁ∑®’˝»∑∑¢ÀÕ≥ˆ»•µƒŒ Ã‚ */
    USART_ClearFlag(USART1, USART_FLAG_TC);     // «Â±Í÷æ
	//≥ı ºªØ¥Æø⁄
	USART_Init(USART1, &USART_InitStructure);
	//∆Ù∂Ø¥Æø⁄
	USART_Cmd(USART1, ENABLE);
	
	
}

/************************************************************************/
//GPIO≈‰÷√	  £®LED£©
/************************************************************************/
void GPIO_Config_LED(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		 //Õ∆ÕÏ ‰≥ˆ
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOC, &GPIO_InitStructure);
	  //GPIOC ->ODR ^= GPIO_Pin_6;
}

/************************************************************************/
//SPI≥ı ºªØ		   SPI 2 
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
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;   //∏¥”√Õ∆ÕÏ ‰≥ˆ
	GPIO_Init(GPIOB,&GPIO_InitStructure); 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   //…œ¿≠ ‰»Î
	GPIO_Init(GPIOB,&GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   //Õ∆ÕÏ ‰≥ˆ
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
//SPI–¥ ˝æ›
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
//∂¡–¥◊®”√—” ±∫Ø ˝
/************************************************************************/ 
void SpiDelay(unsigned int DelayCnt)
{
 unsigned int i;
 for(i=0;i<DelayCnt;i++);
}

/************************************************************************/
//≤ ∆¡¥”..∂¡..X÷·∑ΩœÚ◊¯±Í–≈œ¢£®°Ó°Ó°Ó£©
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
//≤ ∆¡¥”..∂¡..Y÷·∑ΩœÚ◊¯±Í–≈œ¢£®°Ó°Ó°Ó£©
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
//BSP≥ı ºªØ∫Ø ˝	  £®BSP INITIALIZATION£©
/************************************************************************/
void  BSP_Init(void)
{
	RCC_Configuration();  
   /* Enable GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG and AFIO clocks */
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |RCC_APB2Periph_GPIOC 
         | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOF | RCC_APB2Periph_GPIOG 
         | RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
 	OS_CPU_SysTickInit() ;
	GPIO_Config(); 
	GPIO_Config_LED();
	SPI_Config();
	
  NVIC_Configuration();
  USART1_Configuration();
	
	NVIC_Configuration2();
  USART2_Configuration();
		GUI_Init();
}

