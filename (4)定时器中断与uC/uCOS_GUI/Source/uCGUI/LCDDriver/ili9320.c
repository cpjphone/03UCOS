#include "stm32f10x_lib.h"
#include "ili9320.h"
#include "ili9320_font.h"

#define     __IO    volatile                  /*!< defines 'read / write' permissions   */
typedef unsigned short     int uint16_t;
typedef unsigned           int uint32_t;
#define Bank1_LCD_D    ((uint32_t)0x60020000)    //disp Data ADDR	 显示区地址
#define Bank1_LCD_C    ((uint32_t)0x60000000)	 //disp Reg ADDR 	 命令寄存器来写一些指令	 写入的对象不同还以也是不一样的

u16 DeviceCode;
void Lcd_Configuration(void)
{ 
	GPIO_InitTypeDef GPIO_InitStructure;
	/*开启相应时钟 */
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB , ENABLE); 	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC , ENABLE);
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA , ENABLE);
		 
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); 
	GPIOB ->ODR = 0XFFFF; 

		/*控制脚*/
    								 //TPCS       CS         IOR        IOW         CMD/RS	 INT0
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8;//GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure); GPIOC->ODR=0;
	/*所有Lcd引脚配置为推挽输出*/
	/*16位数据低8位*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;//GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	/*16位数据高8位*/

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_4 | GPIO_Pin_3;//led | TPCS
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIOA ->ODR =0;
	/*背光控制*/
//	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_13;
//	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

/****************************************************************************
* 名    称：void ili9320_Initializtion()
* 功    能：初始化 ILI9320 控制器
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：ili9320_Initializtion();
****************************************************************************/
#define LCD_WR_REG  ili9320_WriteIndex 
#define LCD_WR_Data ili9320_WriteData
void FSMC_LCD_Init(void)
{
  FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
  FSMC_NORSRAMTimingInitTypeDef  p;
  GPIO_InitTypeDef  GPIO_InitStructure; 

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);	   //使能FSMC接口时钟
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;			   //背光控制	       
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		   //通用推挽输出模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		   //输出模式最大速度50MHz
  GPIO_Init(GPIOD, &GPIO_InitStructure);    
  GPIO_SetBits(GPIOD, GPIO_Pin_13);			               //打开背光


  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;                //TFT 复位脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		   //通用推挽输出模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		   //输出模式最大速度50MHz
  GPIO_Init(GPIOE, &GPIO_InitStructure);  
  
  	
  /*  启用FSMC复用功能， 定义FSMC D0---D15及nWE, nOE对应的引脚  */
  /* 设置 PD.00(D2), PD.01(D3), PD.04(nOE), PD.05(nWE), PD.08(D13), PD.09(D14), PD.10(D15),
     PD.14(D0), PD.15(D1) 为复用上拉 */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 |
                                GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_14 | 
                                GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		   //最大速度50MHz
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		   //复用模式
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  /* 设置 PE.07(D4), PE.08(D5), PE.09(D6), PE.10(D7), PE.11(D8), PE.12(D9), PE.13(D10),
     PE.14(D11), PE.15(D12) 为复用上拉 */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | 
                                GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | 
                                GPIO_Pin_15;
  GPIO_Init(GPIOE, &GPIO_InitStructure); 


  
  /* FSMC  NE1 配置 PD7 */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; 
  GPIO_Init(GPIOD, &GPIO_InitStructure);
  
  /* FSMC RS配置 PD11-A16 */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 ; 
  GPIO_Init(GPIOD, &GPIO_InitStructure); 

  p.FSMC_AddressSetupTime = 0x02;
  p.FSMC_AddressHoldTime = 0x00;
  p.FSMC_DataSetupTime = 0x05;
  p.FSMC_BusTurnAroundDuration = 0x00;
  p.FSMC_CLKDivision = 0x00;
  p.FSMC_DataLatency = 0x00;
  p.FSMC_AccessMode = FSMC_AccessMode_B;

  FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM1;
  FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
  FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_NOR;
  FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
  FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
  FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
  FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
  FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
  FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &p;
  FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &p;

  FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure); 

  /* 使能FSMC BANK1_SRAM 模式 */
  FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);  
}
void ili9320_Test(void)
{
     u16 i,j;
   //	u32 temp;
	 //	LCD_WR_CMD(0x0044,0xEF00);    
    //	LCD_WR_CMD(0x0045,0x0000);    
    //	LCD_WR_CMD(0x0046,0x013F);

	//	*(__IO uint16_t *) (Bank1_LCD_C)= 0x0022;

  for(i=0;i<320;i++)
    for(j=0;j<240;j++)
    {
      if(i>279)LCD_WR_Data(0x0000);
      else if(i>239)LCD_WR_Data(0x001f);
      else if(i>199)LCD_WR_Data(0x07e0);
      else if(i>159)LCD_WR_Data(0x07ff);
      else if(i>119)LCD_WR_Data(0xf800);
      else if(i>79)LCD_WR_Data(0xf81f);
      else if(i>39)LCD_WR_Data(0xffe0);
      else LCD_WR_Data(0xffff);
    }

/*
while(1) {

   LCD_WR_Data(Red); ili9320_Delay(5000);
   LCD_WR_Data(Green); ili9320_Delay(5000);
   LCD_WR_Data(Blue); ili9320_Delay(5000);  
}*/
}
void ili9320_Initializtion()
{
  /*****************************
  **    硬件连接说明          **
  ** STM32         ili9320    **
  ** PE0~15 <----> DB0~15     **
  ** PD15   <----> nRD        **
  ** PD14   <----> RS         **
  ** PD13   <----> nWR        **
  ** PD12   <----> nCS        **
  ** PD11   <----> nReset     **
  ** PC0    <----> BK_LED     **
  ******************************/
 	u16 i; 

 FSMC_LCD_Init();
  	ili9320_WriteData(0xffff);
	Set_nWr;
	Set_Cs;
	Set_Rs;
	Set_nRd;
  for(i=50000;i>0;i--);
  for(i=50000;i>0;i--);
  for(i=50000;i>0;i--);
  ili9320_WriteRegister(0x0000,0x0001);ili9320_Delay(10000);
  for(i=50000;i>0;i--);
  for(i=50000;i>0;i--);
  DeviceCode = ili9320_ReadRegister(0x0000);
 // printf("a",DeviceCode);
  if(DeviceCode < 0xff || DeviceCode == 0xffff)
  {
  	  LCD_WR_REG(0XD3);
	  ili9320_ReadData();
	  ili9320_ReadData();
	  DeviceCode = ili9320_ReadData();
	   DeviceCode <<= 8;
	   DeviceCode |= ili9320_ReadData();
  } 


//  DeviceCode =0x9341;// 0x1505;//0x9320;
   if(DeviceCode == 0x9341){
				   //FSMC TFT接口初始化     
LCD_WR_REG(0xEF);
LCD_WR_Data (0x03);
LCD_WR_Data(0x80);
LCD_WR_Data (0X02);

LCD_WR_REG(0xCF);
LCD_WR_Data (0x00);
LCD_WR_Data (0xBA);
LCD_WR_Data (0XB0);

LCD_WR_REG(0xED);
LCD_WR_Data (0x67);
LCD_WR_Data(0x03);
LCD_WR_Data(0X12);
LCD_WR_Data (0X81);

LCD_WR_REG(0xE8);
LCD_WR_Data (0x85);
LCD_WR_Data (0x11);
LCD_WR_Data (0x79);

LCD_WR_REG(0xCB);
LCD_WR_Data (0x39);
LCD_WR_Data (0x2C);
LCD_WR_Data (0x00);
LCD_WR_Data (0x34);
LCD_WR_Data (0x06);

LCD_WR_REG(0xF7);
LCD_WR_Data (0x20);

LCD_WR_REG(0xEA);
LCD_WR_Data (0x00);
LCD_WR_Data (0x00);

LCD_WR_REG(0xC0); //Power control
LCD_WR_Data (0x1D); //VRH[5:0]

LCD_WR_REG(0xC1); //Power control
LCD_WR_Data (0x12); //SAP[2:0];BT[3:0]

LCD_WR_REG(0xC5); //VCM control
LCD_WR_Data (0x44);
LCD_WR_Data(0x3c);

LCD_WR_REG(0xC7); //VCM control
LCD_WR_Data (0x9E);

LCD_WR_REG(0x3A); // Memory Access Control
LCD_WR_Data (0x55);

LCD_WR_REG(0x36); // Memory Access Control
LCD_WR_Data (0x48);

LCD_WR_REG(0xB1);
LCD_WR_Data (0x00);
LCD_WR_Data (0x17);

LCD_WR_REG(0xB6); // Display Function Control
LCD_WR_Data (0x0A);
LCD_WR_Data(0x82);//A2	

LCD_WR_REG(0xF2); // 3Gamma Function Disable
LCD_WR_Data (0x00);

LCD_WR_REG(0x26); //Gamma curve selected
LCD_WR_Data (0x01);

LCD_WR_REG(0xE0); //Set Gamma
LCD_WR_Data (0x0F);
LCD_WR_Data (0x22);
LCD_WR_Data(0x1C);
LCD_WR_Data (0x1B);
LCD_WR_Data(0x08);
LCD_WR_Data(0x0F);
LCD_WR_Data (0x48);
LCD_WR_Data(0xB8);
LCD_WR_Data (0x34);
LCD_WR_Data(0x05);
LCD_WR_Data (0x0C);
LCD_WR_Data(0x09);
LCD_WR_Data(0x0F);
LCD_WR_Data (0x07);
LCD_WR_Data(0x00);

ili9320_WriteIndex(0XE1); //Set Gamma
LCD_WR_Data (0x00);
LCD_WR_Data (0x23);
LCD_WR_Data (0x24);
LCD_WR_Data (0x07);
LCD_WR_Data (0x10);
LCD_WR_Data (0x07);
LCD_WR_Data (0x38);
LCD_WR_Data (0x47);
LCD_WR_Data (0x4B);
LCD_WR_Data (0x0A);
LCD_WR_Data (0x13);
LCD_WR_Data (0x06);
LCD_WR_Data (0x30);
LCD_WR_Data (0x38);
LCD_WR_Data (0x0F);
ili9320_WriteIndex(0x11); //Exit Sleep
 ili9320_Delay(500);
ili9320_WriteIndex(0x29); //Display on

ili9320_WriteIndex(0x2c);

 ili9320_SetPoint(1,1,0x001f);
  ili9320_SetPoint(5,10, 0x07e0);
   ili9320_SetPoint(10,10, 0x07e0);
 //while(1);

//ili9320_Test();	

//GpioConfigurationLed();


	   GPIOC ->ODR = GPIO_Pin_6;	   //熄灭(LED共阳极)
	   GPIOC ->ODR &= ~GPIO_Pin_7;
	 ili9320_Delay(0x543210);
	   GPIOC ->ODR &= ~GPIO_Pin_6;	   //点亮(LED共阳极)
	   GPIOC ->ODR = GPIO_Pin_7;
	


   
   }
    if(DeviceCode == 0x5408 ) {
	
	   ili9320_WriteRegister(0x0000,0x0000); 
      ili9320_WriteRegister(0x0001,0x0100);     
       ili9320_WriteRegister(0x0002,0x0700);             //power on sequence                      
       ili9320_WriteRegister(0x0003,0x1020 );    //65K        (1<<12)|(1<<5)|(1<<4)
        ili9320_WriteRegister(0x0004,0x0000);                                   
        ili9320_WriteRegister(0x0008,0x0202);              
        ili9320_WriteRegister(0x0009,0x0000);         
        ili9320_WriteRegister(0x000a,0x0000);             //display setting          
       ili9320_WriteRegister(0x000c,0x0000);            //display setting           
       ili9320_WriteRegister(0x000d,0x0000);             //0f3c          
       ili9320_WriteRegister(0x000f,0x0000);
      ili9320_WriteRegister(0x0007,0x0000);
        //Power On sequence //
       ili9320_WriteRegister(0x0010,0x12b0);   
       ili9320_WriteRegister(0x0011,0x0007);
       ili9320_WriteRegister(0x0012,0x01bb);                                                                  
       ili9320_WriteRegister(0x0013,0x1c00);
      ili9320_WriteRegister(0x0017,0x0001); 

        ili9320_WriteRegister(0x0029,0x0009);
        ili9320_WriteRegister(0x002a,0x0009);
      ili9320_WriteRegister(0x00a4,0x0000);
        
      ili9320_WriteRegister(0x0050,0x0000);                                                             
       ili9320_WriteRegister(0x0051,0x00ef);           
       ili9320_WriteRegister(0x0052,0x0000);   
      ili9320_WriteRegister(0x0053,0x013f);
        ili9320_WriteRegister(0x0060,0x2700);
        ili9320_WriteRegister(0x0061,0x0001); 
        ili9320_WriteRegister(0x006a,0x0000);

       ili9320_WriteRegister(0x0080,0x0000);
       ili9320_WriteRegister(0x0081,0x0000);
       ili9320_WriteRegister(0x0082,0x0000);
       ili9320_WriteRegister(0x0083,0x0000);
       ili9320_WriteRegister(0x0084,0x0000);
        ili9320_WriteRegister(0x0085,0x0000);

        ili9320_WriteRegister(0x0090,0x0010);     
        ili9320_WriteRegister(0x0092,0x0000);  
        ili9320_WriteRegister(0x0093,0x0003);
        ili9320_WriteRegister(0x0095,0x0110);
      ili9320_WriteRegister(0x0097,0x0000);    
      ili9320_WriteRegister(0x0098,0x0000);
       ili9320_WriteRegister(0x0007,0x0173);   
      
     ili9320_WriteIndex(0x0022); 
     ili9320_WriteRegister(0x0020,0x0000);
        ili9320_WriteRegister(0x0021,0x0000);
	}
	if(DeviceCode==0x9325||DeviceCode==0x9328)
	{
  		ili9320_WriteRegister(0x00e7,0x0010);      
        ili9320_WriteRegister(0x0000,0x0001);  			//start internal osc
        ili9320_WriteRegister(0x0001,0x0100);     
        ili9320_WriteRegister(0x0002,0x0700); 				//power on sequence                     
        ili9320_WriteRegister(0x0003,(1<<12)|(1<<5)|(1<<4) ); 	//65K 
        ili9320_WriteRegister(0x0004,0x0000);                                   
        ili9320_WriteRegister(0x0008,0x0207);	           
        ili9320_WriteRegister(0x0009,0x0000);         
        ili9320_WriteRegister(0x000a,0x0000); 				//display setting         
        ili9320_WriteRegister(0x000c,0x0001);				//display setting          
        ili9320_WriteRegister(0x000d,0x0000); 				//0f3c          
        ili9320_WriteRegister(0x000f,0x0000);
//Power On sequence //
        ili9320_WriteRegister(0x0010,0x0000);   
        ili9320_WriteRegister(0x0011,0x0007);
        ili9320_WriteRegister(0x0012,0x0000);                                                                 
        ili9320_WriteRegister(0x0013,0x0000);                 
        for(i=50000;i>0;i--);
		for(i=50000;i>0;i--);
        ili9320_WriteRegister(0x0010,0x1590);   
        ili9320_WriteRegister(0x0011,0x0227);
        for(i=50000;i>0;i--);
		for(i=50000;i>0;i--);
        ili9320_WriteRegister(0x0012,0x009c);                  
        for(i=50000;i>0;i--);
		for(i=50000;i>0;i--);
        ili9320_WriteRegister(0x0013,0x1900);   
        ili9320_WriteRegister(0x0029,0x0023);
        ili9320_WriteRegister(0x002b,0x000e);
        for(i=50000;i>0;i--);
		for(i=50000;i>0;i--);
        ili9320_WriteRegister(0x0020,0x0000);                                                            
        ili9320_WriteRegister(0x0021,0x0000);           
///////////////////////////////////////////////////////      
        for(i=50000;i>0;i--);
		for(i=50000;i>0;i--);
        ili9320_WriteRegister(0x0030,0x0007); 
        ili9320_WriteRegister(0x0031,0x0707);   
        ili9320_WriteRegister(0x0032,0x0006);
        ili9320_WriteRegister(0x0035,0x0704);
        ili9320_WriteRegister(0x0036,0x1f04); 
        ili9320_WriteRegister(0x0037,0x0004);
        ili9320_WriteRegister(0x0038,0x0000);        
        ili9320_WriteRegister(0x0039,0x0706);     
        ili9320_WriteRegister(0x003c,0x0701);
        ili9320_WriteRegister(0x003d,0x000f);
        for(i=50000;i>0;i--);
		for(i=50000;i>0;i--);
        ili9320_WriteRegister(0x0050,0x0000);        
        ili9320_WriteRegister(0x0051,0x00ef);   
        ili9320_WriteRegister(0x0052,0x0000);     
        ili9320_WriteRegister(0x0053,0x013f);
        ili9320_WriteRegister(0x0060,0xa700);        
        ili9320_WriteRegister(0x0061,0x0001); 
        ili9320_WriteRegister(0x006a,0x0000);
        ili9320_WriteRegister(0x0080,0x0000);
        ili9320_WriteRegister(0x0081,0x0000);
        ili9320_WriteRegister(0x0082,0x0000);
        ili9320_WriteRegister(0x0083,0x0000);
        ili9320_WriteRegister(0x0084,0x0000);
        ili9320_WriteRegister(0x0085,0x0000);
      
        ili9320_WriteRegister(0x0090,0x0010);     
        ili9320_WriteRegister(0x0092,0x0000);  
        ili9320_WriteRegister(0x0093,0x0003);
        ili9320_WriteRegister(0x0095,0x0110);
        ili9320_WriteRegister(0x0097,0x0000);        
        ili9320_WriteRegister(0x0098,0x0000);  
         //display on sequence     
        ili9320_WriteRegister(0x0007,0x0133);
    
        ili9320_WriteRegister(0x0020,0x0000);                                                            
        ili9320_WriteRegister(0x0021,0x0000);
	}
	else if(DeviceCode==0x9320)
	{
		ili9320_WriteRegister(0x00,0x0000);
		ili9320_WriteRegister(0x01,0x0100);	//Driver Output Contral.
		ili9320_WriteRegister(0x02,0x0700);	//LCD Driver Waveform Contral.
//		ili9320_WriteRegister(0x03,0x1030);	//Entry Mode Set.
		ili9320_WriteRegister(0x03,0x1018);	//Entry Mode Set.
	
		ili9320_WriteRegister(0x04,0x0000);	//Scalling Contral.
		ili9320_WriteRegister(0x08,0x0202);	//Display Contral 2.(0x0207)
		ili9320_WriteRegister(0x09,0x0000);	//Display Contral 3.(0x0000)
		ili9320_WriteRegister(0x0a,0x0000);	//Frame Cycle Contal.(0x0000)
		ili9320_WriteRegister(0x0c,(1<<0));	//Extern Display Interface Contral 1.(0x0000)
		ili9320_WriteRegister(0x0d,0x0000);	//Frame Maker Position.
		ili9320_WriteRegister(0x0f,0x0000);	//Extern Display Interface Contral 2.
	
		for(i=50000;i>0;i--);
		for(i=50000;i>0;i--);
		ili9320_WriteRegister(0x07,0x0101);	//Display Contral.
		for(i=50000;i>0;i--);
		for(i=50000;i>0;i--);
	
		ili9320_WriteRegister(0x10,(1<<12)|(0<<8)|(1<<7)|(1<<6)|(0<<4));	//Power Control 1.(0x16b0)
		ili9320_WriteRegister(0x11,0x0007);								//Power Control 2.(0x0001)
		ili9320_WriteRegister(0x12,(1<<8)|(1<<4)|(0<<0));					//Power Control 3.(0x0138)
		ili9320_WriteRegister(0x13,0x0b00);								//Power Control 4.
		ili9320_WriteRegister(0x29,0x0000);								//Power Control 7.
	
		ili9320_WriteRegister(0x2b,(1<<14)|(1<<4));
		
		ili9320_WriteRegister(0x50,0);		//Set X Start.
		ili9320_WriteRegister(0x51,239);	//Set X End.
		ili9320_WriteRegister(0x52,0);		//Set Y Start.
		ili9320_WriteRegister(0x53,319);	//Set Y End.
	
		ili9320_WriteRegister(0x60,0x2700);	//Driver Output Control.
		ili9320_WriteRegister(0x61,0x0001);	//Driver Output Control.
		ili9320_WriteRegister(0x6a,0x0000);	//Vertical Srcoll Control.
	
		ili9320_WriteRegister(0x80,0x0000);	//Display Position? Partial Display 1.
		ili9320_WriteRegister(0x81,0x0000);	//RAM Address Start? Partial Display 1.
		ili9320_WriteRegister(0x82,0x0000);	//RAM Address End-Partial Display 1.
		ili9320_WriteRegister(0x83,0x0000);	//Displsy Position? Partial Display 2.
		ili9320_WriteRegister(0x84,0x0000);	//RAM Address Start? Partial Display 2.
		ili9320_WriteRegister(0x85,0x0000);	//RAM Address End? Partial Display 2.
	
		ili9320_WriteRegister(0x90,(0<<7)|(16<<0));	//Frame Cycle Contral.(0x0013)
		ili9320_WriteRegister(0x92,0x0000);	//Panel Interface Contral 2.(0x0000)
		ili9320_WriteRegister(0x93,0x0001);	//Panel Interface Contral 3.
		ili9320_WriteRegister(0x95,0x0110);	//Frame Cycle Contral.(0x0110)
		ili9320_WriteRegister(0x97,(0<<8));	//
		ili9320_WriteRegister(0x98,0x0000);	//Frame Cycle Contral.

	
		ili9320_WriteRegister(0x07,0x0173);	//(0x0173)
	}
	else if(DeviceCode==0x9919)
	{
		//------POWER ON &RESET DISPLAY OFF
		 ili9320_WriteRegister(0x28,0x0006);
		
		 ili9320_WriteRegister(0x00,0x0001);
		
		 ili9320_WriteRegister(0x10,0x0000);
		
		 ili9320_WriteRegister(0x01,0x72ef);

		 ili9320_WriteRegister(0x02,0x0600);

		 ili9320_WriteRegister(0x03,0x6a38);
		
		 ili9320_WriteRegister(0x11,0x6874);//70
		
		 
		     //  RAM WRITE DATA MASK
		 ili9320_WriteRegister(0x0f,0x0000); 
		    //  RAM WRITE DATA MASK
		 ili9320_WriteRegister(0x0b,0x5308); 
		
		 ili9320_WriteRegister(0x0c,0x0003);
		
		 ili9320_WriteRegister(0x0d,0x000a);
		
		 ili9320_WriteRegister(0x0e,0x2e00);  //0030
		
		 ili9320_WriteRegister(0x1e,0x00be);
		
		 ili9320_WriteRegister(0x25,0x8000);
		
		 ili9320_WriteRegister(0x26,0x7800);
		
		 ili9320_WriteRegister(0x27,0x0078);
		
		 ili9320_WriteRegister(0x4e,0x0000);
		
		 ili9320_WriteRegister(0x4f,0x0000);
		
		 ili9320_WriteRegister(0x12,0x08d9);
		
		 // -----------------Adjust the Gamma Curve----//
		 ili9320_WriteRegister(0x30,0x0000);	 //0007
		
		 ili9320_WriteRegister(0x31,0x0104);	   //0203
		
		 ili9320_WriteRegister(0x32,0x0100);		//0001

		 ili9320_WriteRegister(0x33,0x0305);	  //0007

		 ili9320_WriteRegister(0x34,0x0505);	  //0007
		
		 ili9320_WriteRegister(0x35,0x0305);		 //0407
		
		 ili9320_WriteRegister(0x36,0x0707);		 //0407
		
		 ili9320_WriteRegister(0x37,0x0300);		  //0607
		
		 ili9320_WriteRegister(0x3a,0x1200);		 //0106
		
		 ili9320_WriteRegister(0x3b,0x0800);		 

		 ili9320_WriteRegister(0x07,0x0033);
	} 
	else if(DeviceCode==0x9331)
	{
	 	/*********POWER ON &RESET DISPLAY OFF*/
		/************* Start Initial Sequence **********/
		ili9320_WriteRegister(0x00E7, 0x1014);
		ili9320_WriteRegister(0x0001, 0x0100); // set SS and SM bit   0x0100
		ili9320_WriteRegister(0x0002, 0x0200); // set 1 line inversion
		ili9320_WriteRegister(0x0003, 0x1030); // set GRAM write direction and BGR=1.     0x1030
		ili9320_WriteRegister(0x0008, 0x0202); // set the back porch and front porch
		ili9320_WriteRegister(0x0009, 0x0000); // set non-display area refresh cycle ISC[3:0]
		ili9320_WriteRegister(0x000A, 0x0000); // FMARK function
		ili9320_WriteRegister(0x000C, 0x0000); // RGB interface setting
		ili9320_WriteRegister(0x000D, 0x0000); // Frame marker Position
		ili9320_WriteRegister(0x000F, 0x0000); // RGB interface polarity
		//*************Power On sequence ****************//
		ili9320_WriteRegister(0x0010, 0x0000); // SAP, BT[3:0], AP, DSTB, SLP, STB
		ili9320_WriteRegister(0x0011, 0x0007); // DC1[2:0], DC0[2:0], VC[2:0]
		ili9320_WriteRegister(0x0012, 0x0000); // VREG1OUT voltage
		ili9320_WriteRegister(0x0013, 0x0000); // VDV[4:0] for VCOM amplitude
		ili9320_Delay(200); // Dis-charge capacitor power voltage
		ili9320_WriteRegister(0x0010, 0x1690); // SAP, BT[3:0], AP, DSTB, SLP, STB
		ili9320_WriteRegister(0x0011, 0x0227); // DC1[2:0], DC0[2:0], VC[2:0]
		ili9320_Delay(50); // Delay 50ms
		ili9320_WriteRegister(0x0012, 0x000C); // Internal reference voltage= Vci;
		ili9320_Delay(50); // Delay 50ms
		ili9320_WriteRegister(0x0013, 0x0800); // Set VDV[4:0] for VCOM amplitude
		ili9320_WriteRegister(0x0029, 0x0011); // Set VCM[5:0] for VCOMH
		ili9320_WriteRegister(0x002B, 0x000B); // Set Frame Rate
		ili9320_Delay(50); // Delay 50ms
		ili9320_WriteRegister(0x0020, 0x0000); // GRAM horizontal Address
		ili9320_WriteRegister(0x0021, 0x0000); // GRAM Vertical Address
		// ----------- Adjust the Gamma Curve ----------//
		ili9320_WriteRegister(0x0030, 0x0000);
		ili9320_WriteRegister(0x0031, 0x0106);
		ili9320_WriteRegister(0x0032, 0x0000);
		ili9320_WriteRegister(0x0035, 0x0204);
		ili9320_WriteRegister(0x0036, 0x160A);
		ili9320_WriteRegister(0x0037, 0x0707);
		ili9320_WriteRegister(0x0038, 0x0106);
		ili9320_WriteRegister(0x0039, 0x0707);
		ili9320_WriteRegister(0x003C, 0x0402);
		ili9320_WriteRegister(0x003D, 0x0C0F);
		//------------------ Set GRAM area ---------------//
		ili9320_WriteRegister(0x0050, 0x0000); // Horizontal GRAM Start Address
		ili9320_WriteRegister(0x0051, 0x00EF); // Horizontal GRAM End Address
		ili9320_WriteRegister(0x0052, 0x0000); // Vertical GRAM Start Address
		ili9320_WriteRegister(0x0053, 0x013F); // Vertical GRAM Start Address
		ili9320_WriteRegister(0x0060, 0x2700); // Gate Scan Line
		ili9320_WriteRegister(0x0061, 0x0001); // NDL,VLE, REV
		ili9320_WriteRegister(0x006A, 0x0000); // set scrolling line
		//-------------- Partial Display Control ---------//
		ili9320_WriteRegister(0x0080, 0x0000);
		ili9320_WriteRegister(0x0081, 0x0000);
		ili9320_WriteRegister(0x0082, 0x0000);
		ili9320_WriteRegister(0x0083, 0x0000);
		ili9320_WriteRegister(0x0084, 0x0000);
		ili9320_WriteRegister(0x0085, 0x0000);
		//-------------- Panel Control -------------------//
		ili9320_WriteRegister(0x0090, 0x0010);
		ili9320_WriteRegister(0x0092, 0x0600);
		ili9320_WriteRegister(0x0007,0x0021);		
		ili9320_Delay(50);
		ili9320_WriteRegister(0x0007,0x0061);
		ili9320_Delay(50);
		ili9320_WriteRegister(0x0007,0x0133);  // 262K color and display ON
		ili9320_Delay(50);
	}  
	else if(DeviceCode==0x7783)
	{
		// Start Initial Sequence
		ili9320_WriteRegister(0x00FF,0x0001);
		ili9320_WriteRegister(0x00F3,0x0008);
		ili9320_WriteRegister(0x0001,0x0100);
		ili9320_WriteRegister(0x0002,0x0700);
		ili9320_WriteRegister(0x0003,0x1030);  //0x1030
		ili9320_WriteRegister(0x0008,0x0302);
		ili9320_WriteRegister(0x0008,0x0207);
		ili9320_WriteRegister(0x0009,0x0000);
		ili9320_WriteRegister(0x000A,0x0000);
		ili9320_WriteRegister(0x0010,0x0000);  //0x0790
		ili9320_WriteRegister(0x0011,0x0005);
		ili9320_WriteRegister(0x0012,0x0000);
		ili9320_WriteRegister(0x0013,0x0000);
		ili9320_Delay(50);
		ili9320_WriteRegister(0x0010,0x12B0);
		ili9320_Delay(50);
		ili9320_WriteRegister(0x0011,0x0007);
		ili9320_Delay(50);
		ili9320_WriteRegister(0x0012,0x008B);
		ili9320_Delay(50);
		ili9320_WriteRegister(0x0013,0x1700);
		ili9320_Delay(50);
		ili9320_WriteRegister(0x0029,0x0022);
		
		//################# void Gamma_Set(void) ####################//
		ili9320_WriteRegister(0x0030,0x0000);
		ili9320_WriteRegister(0x0031,0x0707);
		ili9320_WriteRegister(0x0032,0x0505);
		ili9320_WriteRegister(0x0035,0x0107);
		ili9320_WriteRegister(0x0036,0x0008);
		ili9320_WriteRegister(0x0037,0x0000);
		ili9320_WriteRegister(0x0038,0x0202);
		ili9320_WriteRegister(0x0039,0x0106);
		ili9320_WriteRegister(0x003C,0x0202);
		ili9320_WriteRegister(0x003D,0x0408);
		ili9320_Delay(50);
		
		
		ili9320_WriteRegister(0x0050,0x0000);		
		ili9320_WriteRegister(0x0051,0x00EF);		
		ili9320_WriteRegister(0x0052,0x0000);		
		ili9320_WriteRegister(0x0053,0x013F);		
		ili9320_WriteRegister(0x0060,0xA700);		
		ili9320_WriteRegister(0x0061,0x0001);
		ili9320_WriteRegister(0x0090,0x0033);				
		ili9320_WriteRegister(0x002B,0x000B);		
		ili9320_WriteRegister(0x0007,0x0133);
		ili9320_Delay(50);
	} 
	else if(DeviceCode==0x4531)
	{		
		// Setup display
		ili9320_WriteRegister(0x00,0x0001);
	    ili9320_WriteRegister(0x10,0x0628);
	    ili9320_WriteRegister(0x12,0x0006);
	    ili9320_WriteRegister(0x13,0x0A32);
	    ili9320_WriteRegister(0x11,0x0040);
	    ili9320_WriteRegister(0x15,0x0050);
	    ili9320_WriteRegister(0x12,0x0016);
	    ili9320_Delay(15);
	    ili9320_WriteRegister(0x10,0x5660);
	    ili9320_Delay(15);
	    ili9320_WriteRegister(0x13,0x2A4E);
	    ili9320_WriteRegister(0x01,0x0100);
	    ili9320_WriteRegister(0x02,0x0300);
	
	    ili9320_WriteRegister(0x03,0x1030);
//	    ili9320_WriteRegister(0x03,0x1038);
	
	    ili9320_WriteRegister(0x08,0x0202);
	    ili9320_WriteRegister(0x0A,0x0000);
	    ili9320_WriteRegister(0x30,0x0000);
	    ili9320_WriteRegister(0x31,0x0402);
	    ili9320_WriteRegister(0x32,0x0106);
	    ili9320_WriteRegister(0x33,0x0700);
	    ili9320_WriteRegister(0x34,0x0104);
	    ili9320_WriteRegister(0x35,0x0301);
	    ili9320_WriteRegister(0x36,0x0707);
	    ili9320_WriteRegister(0x37,0x0305);
	    ili9320_WriteRegister(0x38,0x0208);
	    ili9320_WriteRegister(0x39,0x0F0B);
	    ili9320_Delay(15);
	    ili9320_WriteRegister(0x41,0x0002);
	    ili9320_WriteRegister(0x60,0x2700);
	    ili9320_WriteRegister(0x61,0x0001);
	    ili9320_WriteRegister(0x90,0x0119);
	    ili9320_WriteRegister(0x92,0x010A);
	    ili9320_WriteRegister(0x93,0x0004);
	    ili9320_WriteRegister(0xA0,0x0100);
//	    ili9320_WriteRegister(0x07,0x0001);
	    ili9320_Delay(15);
//	    ili9320_WriteRegister(0x07,0x0021); 
	    ili9320_Delay(15);
//	    ili9320_WriteRegister(0x07,0x0023);
	    ili9320_Delay(15);
//	    ili9320_WriteRegister(0x07,0x0033);
	    ili9320_Delay(15);
	    ili9320_WriteRegister(0x07,0x0133);
	    ili9320_Delay(15);
	    ili9320_WriteRegister(0xA0,0x0000);
	    ili9320_Delay(20);
	} 						 
	
	else if(DeviceCode==0x1505)
	{
// second release on 3/5  ,luminance is acceptable,water wave appear during camera preview
        ili9320_WriteRegister(0x0007,0x0000);
        ili9320_Delay(5);
        ili9320_WriteRegister(0x0012,0x011C);//0x011A   why need to set several times?
        ili9320_WriteRegister(0x00A4,0x0001);//NVM
    //
        ili9320_WriteRegister(0x0008,0x000F);
        ili9320_WriteRegister(0x000A,0x0008);
        ili9320_WriteRegister(0x000D,0x0008);
       
  //GAMMA CONTROL/
        ili9320_WriteRegister(0x0030,0x0707);
        ili9320_WriteRegister(0x0031,0x0007); //0x0707
        ili9320_WriteRegister(0x0032,0x0603); 
        ili9320_WriteRegister(0x0033,0x0700); 
        ili9320_WriteRegister(0x0034,0x0202); 
        ili9320_WriteRegister(0x0035,0x0002); //?0x0606
        ili9320_WriteRegister(0x0036,0x1F0F);
        ili9320_WriteRegister(0x0037,0x0707); //0x0f0f  0x0105
        ili9320_WriteRegister(0x0038,0x0000); 
        ili9320_WriteRegister(0x0039,0x0000); 
        ili9320_WriteRegister(0x003A,0x0707); 
        ili9320_WriteRegister(0x003B,0x0000); //0x0303
        ili9320_WriteRegister(0x003C,0x0007); //?0x0707
        ili9320_WriteRegister(0x003D,0x0000); //0x1313//0x1f08
        ili9320_Delay(5);
        ili9320_WriteRegister(0x0007,0x0001);
        ili9320_WriteRegister(0x0017,0x0001);   //Power supply startup enable
        ili9320_Delay(5);
  
  //power control//
        ili9320_WriteRegister(0x0010,0x17A0); 
        ili9320_WriteRegister(0x0011,0x0217); //reference voltage VC[2:0]   Vciout = 1.00*Vcivl
        ili9320_WriteRegister(0x0012,0x011E);//0x011c  //Vreg1out = Vcilvl*1.80   is it the same as Vgama1out ?
        ili9320_WriteRegister(0x0013,0x0F00); //VDV[4:0]-->VCOM Amplitude VcomL = VcomH - Vcom Ampl
        ili9320_WriteRegister(0x002A,0x0000);  
        ili9320_WriteRegister(0x0029,0x000A); //0x0001F  Vcomh = VCM1[4:0]*Vreg1out    gate source voltage??
        ili9320_WriteRegister(0x0012,0x013E); // 0x013C  power supply on
           //Coordinates Control//
        ili9320_WriteRegister(0x0050,0x0000);//0x0e00
        ili9320_WriteRegister(0x0051,0x00EF); 
        ili9320_WriteRegister(0x0052,0x0000); 
        ili9320_WriteRegister(0x0053,0x013F); 
    //Pannel Image Control//
        ili9320_WriteRegister(0x0060,0x2700); 
        ili9320_WriteRegister(0x0061,0x0001); 
        ili9320_WriteRegister(0x006A,0x0000); 
        ili9320_WriteRegister(0x0080,0x0000); 
    //Partial Image Control//
        ili9320_WriteRegister(0x0081,0x0000); 
        ili9320_WriteRegister(0x0082,0x0000); 
        ili9320_WriteRegister(0x0083,0x0000); 
        ili9320_WriteRegister(0x0084,0x0000); 
        ili9320_WriteRegister(0x0085,0x0000); 
  //Panel Interface Control//
        ili9320_WriteRegister(0x0090,0x0013); //0x0010 frenqucy
        ili9320_WriteRegister(0x0092,0x0300); 
        ili9320_WriteRegister(0x0093,0x0005); 
        ili9320_WriteRegister(0x0095,0x0000); 
        ili9320_WriteRegister(0x0097,0x0000); 
        ili9320_WriteRegister(0x0098,0x0000); 
  
        ili9320_WriteRegister(0x0001,0x0100); 
        ili9320_WriteRegister(0x0002,0x0700); 
        ili9320_WriteRegister(0x0003,0x1030); 
        ili9320_WriteRegister(0x0004,0x0000); 
        ili9320_WriteRegister(0x000C,0x0000); 
        ili9320_WriteRegister(0x000F,0x0000); 
        ili9320_WriteRegister(0x0020,0x0000); 
        ili9320_WriteRegister(0x0021,0x0000); 
        ili9320_WriteRegister(0x0007,0x0021); 
        ili9320_Delay(20);
        ili9320_WriteRegister(0x0007,0x0061); 
        ili9320_Delay(20);
        ili9320_WriteRegister(0x0007,0x0173); 
        ili9320_Delay(20);
	}							 			  
	else if(DeviceCode==0x8989)
	{
		ili9320_WriteRegister(0x0000,0x0001);    ili9320_Delay(50000);  //打开晶振
    	ili9320_WriteRegister(0x0003,0xA8A4);    ili9320_Delay(50000);   //0xA8A4
    	ili9320_WriteRegister(0x000C,0x0000);    ili9320_Delay(50000);   
    	ili9320_WriteRegister(0x000D,0x080C);    ili9320_Delay(50000);   
    	ili9320_WriteRegister(0x000E,0x2B00);    ili9320_Delay(50000);   
    	ili9320_WriteRegister(0x001E,0x00B0);    ili9320_Delay(50000);   
    	ili9320_WriteRegister(0x0001,0x2B3F);    ili9320_Delay(50000);   //驱动输出控制320*240  0x6B3F
    	ili9320_WriteRegister(0x0002,0x0600);    ili9320_Delay(50000);
    	ili9320_WriteRegister(0x0010,0x0000);    ili9320_Delay(50000);
    	ili9320_WriteRegister(0x0011,0x6070);    ili9320_Delay(50000);        //0x4030           //定义数据格式  16位色 		横屏 0x6058
    	ili9320_WriteRegister(0x0005,0x0000);    ili9320_Delay(50000);
    	ili9320_WriteRegister(0x0006,0x0000);    ili9320_Delay(50000);
    	ili9320_WriteRegister(0x0016,0xEF1C);    ili9320_Delay(50000);
    	ili9320_WriteRegister(0x0017,0x0003);    ili9320_Delay(50000);
    	ili9320_WriteRegister(0x0007,0x0233);    ili9320_Delay(50000);        //0x0233       
    	ili9320_WriteRegister(0x000B,0x0000);    ili9320_Delay(50000);
    	ili9320_WriteRegister(0x000F,0x0000);    ili9320_Delay(50000);        //扫描开始地址
    	ili9320_WriteRegister(0x0041,0x0000);    ili9320_Delay(50000);
    	ili9320_WriteRegister(0x0042,0x0000);    ili9320_Delay(50000);
    	ili9320_WriteRegister(0x0048,0x0000);    ili9320_Delay(50000);
    	ili9320_WriteRegister(0x0049,0x013F);    ili9320_Delay(50000);
    	ili9320_WriteRegister(0x004A,0x0000);    ili9320_Delay(50000);
    	ili9320_WriteRegister(0x004B,0x0000);    ili9320_Delay(50000);
    	ili9320_WriteRegister(0x0044,0xEF00);    ili9320_Delay(50000);
    	ili9320_WriteRegister(0x0045,0x0000);    ili9320_Delay(50000);
    	ili9320_WriteRegister(0x0046,0x013F);    ili9320_Delay(50000);
    	ili9320_WriteRegister(0x0030,0x0707);    ili9320_Delay(50000);
    	ili9320_WriteRegister(0x0031,0x0204);    ili9320_Delay(50000);
    	ili9320_WriteRegister(0x0032,0x0204);    ili9320_Delay(50000);
    	ili9320_WriteRegister(0x0033,0x0502);    ili9320_Delay(50000);
    	ili9320_WriteRegister(0x0034,0x0507);    ili9320_Delay(50000);
    	ili9320_WriteRegister(0x0035,0x0204);    ili9320_Delay(50000);
    	ili9320_WriteRegister(0x0036,0x0204);    ili9320_Delay(50000);
    	ili9320_WriteRegister(0x0037,0x0502);    ili9320_Delay(50000);
    	ili9320_WriteRegister(0x003A,0x0302);    ili9320_Delay(50000);
    	ili9320_WriteRegister(0x003B,0x0302);    ili9320_Delay(50000);
    	ili9320_WriteRegister(0x0023,0x0000);    ili9320_Delay(50000);
    	ili9320_WriteRegister(0x0024,0x0000);    ili9320_Delay(50000);
    	ili9320_WriteRegister(0x0025,0x8000);    ili9320_Delay(50000);
    	ili9320_WriteRegister(0x004f,0);        //行首址0
    	ili9320_WriteRegister(0x004e,0);        //列首址0
	}  
  for(i=50000;i>0;i--);
  //ili9320_Clear(0x00f8);
 // ili9320_Clear(0xf800);

}

/****************************************************************************
* 名    称：void ili9320_SetCursor(u16 x,u16 y)
* 功    能：设置屏幕座标
* 入口参数：x      行座标
*           y      列座标
* 出口参数：无
* 说    明：
* 调用方法：ili9320_SetCursor(10,10);
****************************************************************************/
__inline void ili9320_SetCursor(u16 x,u16 y)
{
	if(DeviceCode==0x8989)
	{
	 	ili9320_WriteRegister(0x004e,y);        //行
    	ili9320_WriteRegister(0x004f,0x13f-x);  //列
	}
	else if(DeviceCode==0x9919)
	{
		ili9320_WriteRegister(0x004e,x); // 行
  		ili9320_WriteRegister(0x004f,y); // 列	
	}
	else if(DeviceCode == 0x9341) {	 /*
		 	ili9320_WriteIndex(0x2a);    
	        ili9320_WriteData(x>>8); 	ili9320_WriteData(x&0xff); 
			ili9320_WriteIndex(0x2b);    
	        ili9320_WriteData(y>>8); 	ili9320_WriteData(y&0xff); */

		   //	ili9320_WriteIndex(0x2a);  	        ili9320_WriteData(0);	        ili9320_WriteData(x);
			//ili9320_WriteIndex(0x2b); 			ili9320_WriteData(0);	        ili9320_WriteData(319-y);
		//	x = 319-x;
 		 	ili9320_WriteIndex(0x2b); 
	        ili9320_WriteData(x>>8); 
			ili9320_WriteData(x&0xff); 
 		 	ili9320_WriteIndex(0x2a);   
			y=239-y;	  
	        ili9320_WriteData(y>>8); 	
			ili9320_WriteData(y&0xff); 


	//	ili9320_WriteRegister(0x2a,0);  
	//	ili9320_WriteRegister(0x2a,x);        //行
		    //	ili9320_WriteRegister(0x2b,0);  //列
    	//ili9320_WriteRegister(0x2b,0x13f-y);  //列
	}
	else 
	{
  		ili9320_WriteRegister(0x0020,y); // 行
  		ili9320_WriteRegister(0x0021,0x13f-x); // 列
	}
}

/****************************************************************************
* 名    称：void ili9320_SetWindows(u16 StartX,u16 StartY,u16 EndX,u16 EndY)
* 功    能：设置窗口区域
* 入口参数：StartX     行起始座标
*           StartY     列起始座标
*           EndX       行结束座标
*           EndY       列结束座标
* 出口参数：无
* 说    明：
* 调用方法：ili9320_SetWindows(0,0,100,100)；
****************************************************************************/
__inline void ili9320_SetWindows(u16 StartX,u16 StartY,u16 EndX,u16 EndY)
{
  ili9320_SetCursor(StartX,StartY);
  ili9320_WriteRegister(0x0050, StartX);
  ili9320_WriteRegister(0x0052, StartY);
  ili9320_WriteRegister(0x0051, EndX);
  ili9320_WriteRegister(0x0053, EndY);
}

/****************************************************************************
* 名    称：void ili9320_Clear(u16 dat)
* 功    能：将屏幕填充成指定的颜色，如清屏，则填充 0xffff
* 入口参数：dat      填充值
* 出口参数：无
* 说    明：
* 调用方法：ili9320_Clear(0xffff);
****************************************************************************/
void ili9320_Clear(u16 dat)
{
  u32  i;

  ili9320_SetCursor(0x0000, 0x0000);  
  Clr_Cs; 
  ili9320_WriteIndex(0x0022);    
  for(i=0;i<76800;i++)
  {
    ili9320_WriteData(dat);
  }
  Set_Cs;
}

/****************************************************************************
* 名    称：u16 ili9320_GetPoint(u16 x,u16 y)
* 功    能：获取指定座标的颜色值
* 入口参数：x      行座标
*           y      列座标
* 出口参数：当前座标颜色值
* 说    明：
* 调用方法：i=ili9320_GetPoint(10,10);
****************************************************************************/
//u16 ili9320_GetPoint(u16 x,u16 y)
//{
//  ili9320_SetCursor(x,y);
//  return (ili9320_BGR2RGB(ili9320_ReadRegister(0x0022)));
//}


u16 ili9320_GetPoint(u16 x,u16 y)
{
  u16 temp;
  ili9320_SetCursor(x,y);
  Clr_Cs;
  ili9320_WriteIndex(0x0022);  
	temp = ili9320_ReadData(); //dummy
	temp = ili9320_ReadData(); 	
   Set_Cs;
//   if(DeviceCode!=0x7783||DeviceCode!=0x9919)
//   	  temp=ili9320_BGR2RGB(temp);
   return (temp);
}

/****************************************************************************
* 名    称：void ili9320_SetPoint(u16 x,u16 y,u16 point)
* 功    能：在指定座标画点
* 入口参数：x      行座标
*           y      列座标
*           point  点的颜色
* 出口参数：无
* 说    明：
* 调用方法：ili9320_SetPoint(10,10,0x0fe0);
****************************************************************************/
void ili9320_SetPoint(u16 x,u16 y,u16 point)
{
  //if ( (x>320)||(y>240) ) return;
  ili9320_SetCursor(x,y);

 // Clr_Cs;
  ili9320_WriteIndex(0x2c);
  ili9320_WriteData(point);
//  Set_Cs;
}

/****************************************************************************
* 名    称：void ili9320_DrawPicture(u16 StartX,u16 StartY,u16 EndX,u16 EndY,u16 *pic)
* 功    能：在指定座标范围显示一副图片
* 入口参数：StartX     行起始座标
*           StartY     列起始座标
*           EndX       行结束座标
*           EndY       列结束座标
            pic        图片头指针
* 出口参数：无
* 说    明：图片取模格式为水平扫描，16位颜色模式
* 调用方法：ili9320_DrawPicture(0,0,100,100,(u16*)demo);
****************************************************************************/
void ili9320_DrawPicture0(u16 StartX,u16 StartY,u16 EndX,u16 EndY,u16 *pic)
{
  u16  i;
  ili9320_SetWindows(StartX,StartY,EndX,EndY);
  ili9320_SetCursor(StartX,StartY);
  
 // Clr_Cs;

  ili9320_WriteIndex(0x2c);
  for (i=0;i<(EndX*EndY);i++)
  {
      ili9320_WriteData(*pic++);
  }     
 // Set_Cs;
}

/****************************************************************************
* 名    称：void ili9320_PutChar(u16 x,u16 y,u8 c,u16 charColor,u16 bkColor)
* 功    能：在指定座标显示一个8x16点阵的ascii字符
* 入口参数：x          行座标
*           y          列座标
*           charColor  字符的颜色
*           bkColor    字符背景颜色
* 出口参数：无
* 说    明：显示范围限定为可显示的ascii码
* 调用方法：ili9320_PutChar(10,10,'a',0x0000,0xffff);
****************************************************************************/
void ili9320_PutChar(u16 x,u16 y,u8 c,u16 charColor,u16 bkColor)
{
  u16 i=0;
  u16 j=0;
  
  u8 tmp_char=0;

  for (i=0;i<16;i++)
  {
    tmp_char=ascii_8x16[((c-0x20)*16)+i];
    for (j=0;j<8;j++)
    {
      if ( (tmp_char >> 7-j) & 0x01 == 0x01)
        {
          ili9320_SetPoint(x+j,y+i,charColor); // 字符颜色
        }
        else
        {
          ili9320_SetPoint(x+j,y+i,bkColor); // 背景颜色
        }
    }
  }
}

/****************************************************************************
* 名    称：void ili9320_Test()
* 功    能：测试液晶屏
* 入口参数：无
* 出口参数：无
* 说    明：显示彩条，测试液晶屏是否正常工作
* 调用方法：ili9320_Test();
****************************************************************************/
void ili9320_Test0()
{
  u8  R_data,G_data,B_data,i,j;

	ili9320_SetCursor(0x00, 0x0000);
	ili9320_WriteRegister(0x0050,0x00);//水平 GRAM起始位置
	ili9320_WriteRegister(0x0051,239);//水平GRAM终止位置
	ili9320_WriteRegister(0x0052,0);//垂直GRAM起始位置
	ili9320_WriteRegister(0x0053,319);//垂直GRAM终止位置  
	Clr_Cs; 
	ili9320_WriteIndex(0x0022);
    R_data=0;G_data=0;B_data=0;     
    for(j=0;j<50;j++)//红色渐强条
    {
        for(i=0;i<240;i++)
            {R_data=i/8;ili9320_WriteData(R_data<<11|G_data<<5|B_data);
		}
    }
    R_data=0x1f;G_data=0x3f;B_data=0x1f;
    for(j=0;j<50;j++)
    {
        for(i=0;i<240;i++)
            {
            G_data=0x3f-(i/4);
            B_data=0x1f-(i/8);
            ili9320_WriteData(R_data<<11|G_data<<5|B_data);
			}
    }
//----------------------------------
    R_data=0;G_data=0;B_data=0;
    for(j=0;j<50;j++)//绿色渐强条
    {
        for(i=0;i<240;i++)
            {G_data=i/4;
			ili9320_WriteData(R_data<<11|G_data<<5|B_data);
}
    }

    R_data=0x1f;G_data=0x3f;B_data=0x1f;
    for(j=0;j<50;j++)
    {
        for(i=0;i<240;i++)
            {
            R_data=0x1f-(i/8);
            B_data=0x1f-(i/8);
            ili9320_WriteData(R_data<<11|G_data<<5|B_data);
		}
    }
//----------------------------------
 
    R_data=0;G_data=0;B_data=0;
    for(j=0;j<60;j++)//蓝色渐强条
    {
        for(i=0;i<240;i++)
            {B_data=i/8;ili9320_WriteData(R_data<<11|G_data<<5|B_data);
			}
    } 

    B_data=0; 
    R_data=0x1f;G_data=0x3f;B_data=0x1f;

    for(j=0;j<60;j++)
    {
        for(i=0;i<240;i++)
            {
            G_data=0x3f-(i/4);
            R_data=0x1f-(i/8);
            ili9320_WriteData(R_data<<11|G_data<<5|B_data);
		}
    }	  
	Set_Cs;
}

/****************************************************************************
* 名    称：u16 ili9320_BGR2RGB(u16 c)
* 功    能：RRRRRGGGGGGBBBBB 改为 BBBBBGGGGGGRRRRR 格式
* 入口参数：c      BRG 颜色值
* 出口参数：RGB 颜色值
* 说    明：内部函数调用
* 调用方法：
****************************************************************************/
u16 ili9320_BGR2RGB(u16 c)
{
  u16  r, g, b, rgb;

  b = (c>>0)  & 0x1f;
  g = (c>>5)  & 0x3f;
  r = (c>>11) & 0x1f;
  
  rgb =  (b<<11) + (g<<5) + (r<<0);

  return( rgb );
}

/****************************************************************************
* 名    称：void ili9320_WriteIndex(u16 idx)
* 功    能：写 ili9320 控制器寄存器地址
* 入口参数：idx   寄存器地址
* 出口参数：无
* 说    明：调用前需先选中控制器，内部函数
* 调用方法：ili9320_WriteIndex(0x0000);
****************************************************************************/
__inline void ili9320_WriteIndex(u16 idx)
{
	*(__IO uint16_t *) (Bank1_LCD_C)= idx;
}

/****************************************************************************
* 名    称：void ili9320_WriteData(u16 dat)
* 功    能：写 ili9320 寄存器数据
* 入口参数：dat     寄存器数据
* 出口参数：无
* 说    明：向控制器指定地址写入数据，调用前需先写寄存器地址，内部函数
* 调用方法：ili9320_WriteData(0x1030)
****************************************************************************/
void ili9320_WriteData(u16 data)
{
	*(__IO uint16_t *) (Bank1_LCD_D)= data; //先强制类型转换，再取地址里面的内容
}

/****************************************************************************
* 名    称：u16 ili9320_ReadData(void)
* 功    能：读取控制器数据
* 入口参数：无
* 出口参数：返回读取到的数据
* 说    明：内部函数
* 调用方法：i=ili9320_ReadData();
****************************************************************************/
__inline u16 ili9320_ReadData(void)
{
//========================================================================
// **                                                                    **
// ** nCS       ----\__________________________________________/-------  **
// ** RS        ------\____________/-----------------------------------  **
// ** nRD       -------------------------\_____/---------------------  **
// ** nWR       --------\_______/--------------------------------------  **
// ** DB[0:15]  ---------[index]----------[data]-----------------------  **
// **                                                                    **
//========================================================================
	unsigned short val = 0;
val =	*(__IO uint16_t *) (Bank1_LCD_D);
	return val;
}

/****************************************************************************
* 名    称：u16 ili9320_ReadRegister(u16 index)
* 功    能：读取指定地址寄存器的值
* 入口参数：index    寄存器地址
* 出口参数：寄存器值
* 说    明：内部函数
* 调用方法：i=ili9320_ReadRegister(0x0022);
****************************************************************************/
__inline u16 ili9320_ReadRegister(u16 index)
{ 
 // 	Clr_Cs;
	ili9320_WriteIndex(index);  ili9320_Delay(0X54321);   
	index = ili9320_ReadData();      	
//	Set_Cs;
	return index;
}

/****************************************************************************
* 名    称：void ili9320_WriteRegister(u16 index,u16 dat)
* 功    能：写指定地址寄存器的值
* 入口参数：index    寄存器地址
*         ：dat      寄存器值
* 出口参数：无
* 说    明：内部函数
* 调用方法：ili9320_WriteRegister(0x0000,0x0001);
****************************************************************************/
__inline void ili9320_WriteRegister(u16 index,u16 dat)
{
 /************************************************************************
  **                                                                    **
  ** nCS       ----\__________________________________________/-------  **
  ** RS        ------\____________/-----------------------------------  **
  ** nRD       -------------------------------------------------------  **
  ** nWR       --------\_______/--------\_____/-----------------------  **
  ** DB[0:15]  ---------[index]----------[data]-----------------------  **
  **                                                                    **
  ************************************************************************/
 //   Clr_Cs;

	ili9320_WriteIndex(index);    
	ili9320_WriteData(dat);    
//	Set_Cs; 
}

/****************************************************************************
* 名    称：void ili9320_Delay(vu32 nCount)
* 功    能：延时
* 入口参数：nCount   延时值
* 出口参数：无
* 说    明：
* 调用方法：ili9320_Delay(10000);
****************************************************************************/
void ili9320_Delay(vu32 nCount)
{
  for(; nCount != 0; nCount--);
}
