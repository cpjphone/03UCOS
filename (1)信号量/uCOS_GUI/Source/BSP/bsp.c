/*********************************************************************************      
* �����ܡ���Ӳ��ƽ̨�ĳ�ʼ�� 
*********************************************************************************/
#include "includes.h"


void GPIO_Config(void);					  //GPIO����
void GPIO_Config_LED(void);
void SPI_Config(void);					  //SPI����
void  OS_CPU_SysTickInit(void);									   
void RCC_Configuration(void);

unsigned char SPI_WriteByte(unsigned char data) ;	 
void SpiDelay(unsigned int DelayCnt);



/************************************************************************/
//BSP��ʼ������	  ��BSP INITIALIZATION��
/************************************************************************/
void  BSP_Init(void)
{
	RCC_Configuration();  
   /* Enable GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG and AFIO clocks */
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |RCC_APB2Periph_GPIOC 
         | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOF | RCC_APB2Periph_GPIOG 
         | RCC_APB2Periph_AFIO, ENABLE);

	GPIO_Config(); 
	GPIO_Config_LED();
	SPI_Config();
	OS_CPU_SysTickInit() ;
}

/************************************************************************/
//ϵͳʱ�����ú���	
/************************************************************************/
void RCC_Configuration(void)
{
	 ErrorStatus HSEStartUpStatus;                    //�����ⲿ���پ�������״̬ö�ٱ���
	 RCC_DeInit();                                    //��λRCC�ⲿ�豸�Ĵ�����Ĭ��ֵ
	 RCC_HSEConfig(RCC_HSE_ON);                       //���ⲿ���پ���
	 HSEStartUpStatus = RCC_WaitForHSEStartUp();      //�ȴ��ⲿ����ʱ��׼����
	 if(HSEStartUpStatus == SUCCESS)                  //�ⲿ����ʱ���Ѿ�׼���
	  {
		   FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable); 	//����FLASHԤ�����幦�ܣ�����FLASH�Ķ�ȡ�����г����б�����÷�.λ�ã�RCC��ʼ���Ӻ������棬ʱ������֮��
		   FLASH_SetLatency(FLASH_Latency_2);                   	 //flash��������ʱ
			    		
						// RCC_HCLK  ���� 
				   	    // RCC_SYSCLK_Div1   AHBʱ�� =  ϵͳʱ�� 
					    // RCC_SYSCLK_Div2   AHBʱ�� =  ϵͳʱ�� / 2 
						// RCC_SYSCLK_Div4   AHBʱ��  = ϵͳʱ�� / 4 
						// RCC_SYSCLK_Div8   AHBʱ��  =  ϵͳʱ�� / 8 
						// RCC_SYSCLK_Div16  AHBʱ��  =  ϵͳʱ�� / 16 
						// RCC_SYSCLK_Div64  AHBʱ��  =  ϵͳʱ�� / 64 
						// RCC_SYSCLK_Div128 AHBʱ��  =  ϵͳʱ��  / 128 
						// RCC_SYSCLK_Div256 AHBʱ��  =  ϵͳʱ��  / 256 
						// RCC_SYSCLK_Div512 AHBʱ��  =  ϵͳʱ��  / 512 
								
		   RCC_HCLKConfig(RCC_SYSCLK_Div1);               //����AHB(HCLK)ʱ�ӵ���==SYSCLK
		   RCC_PCLK2Config(RCC_HCLK_Div1);                //����APB2(PCLK2)��==AHBʱ��
		   RCC_PCLK1Config(RCC_HCLK_Div2);                //����APB1(PCLK1)��==AHB1/2ʱ��
		         
		   RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);  //����PLLʱ�� == �ⲿ���پ���ʱ�� * 9 = 72MHz
		   RCC_PLLCmd(ENABLE);                                   //ʹ��PLLʱ��
		   
		   while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)    //�ȴ�PLLʱ�Ӿ���
		   {
		   }
		   RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);            //����ϵͳʱ�� = PLLʱ��
		   while(RCC_GetSYSCLKSource() != 0x08)                  //���PLLʱ���Ƿ���Ϊϵͳʱ��
		   {
		   }
	  }

}

/************************************************************************/
//���жϣ�DISABLE ALL INTERRUPTS��
/************************************************************************/
void  BSP_IntDisAll (void)
{
  // CPU_IntDis();

  /* ����ʵ�ʹ����ٽ�Σ���������ٽ��Ҳ��Ϊ�ٽ�����ָ����ʱ���ɷָ�Ĵ��롣
  һ���ⲿ�ִ��뿪ʼִ�У��������κ��жϴ��롣Ϊȷ���ٽ�δ����ִ�У��ڽ����ٽ��֮ǰҪ���ж�
  �����ٽ�δ���ִ�����Ժ�Ҫ�������жϡ���
   */
}

/************************************************************************/
//ucos ϵͳ����ʱ�ӳ�ʼ��  ��ʼ����Ϊ10msһ�ν���
/************************************************************************/
void  OS_CPU_SysTickInit(void)
{
    RCC_ClocksTypeDef  rcc_clocks;
    INT32U         cnts;
    RCC_GetClocksFreq(&rcc_clocks);		                        //���ϵͳʱ�ӵ�ֵ	 
    cnts = (INT32U)rcc_clocks.HCLK_Frequency/OS_TICKS_PER_SEC;	//���ʱ�ӽ��ĵ�ֵ	
	SysTick_Config(cnts);										//����ʱ�ӽ���	     
}

/************************************************************************/
//GPIO����
/************************************************************************/
void GPIO_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		 //�������
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOD, &GPIO_InitStructure);
}

/************************************************************************/
//GPIO����	  ��LED��
/************************************************************************/
void GPIO_Config_LED(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		 //�������
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIOC ->ODR ^= GPIO_Pin_6;
}

/************************************************************************/
//SPI��ʼ��		   SPI 2 
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
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;   //�����������
	GPIO_Init(GPIOB,&GPIO_InitStructure); 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   //��������
	GPIO_Init(GPIOB,&GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   //�������
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
//SPIд����
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
//��дר����ʱ����
/************************************************************************/ 
void SpiDelay(unsigned int DelayCnt)
{
 unsigned int i;
 for(i=0;i<DelayCnt;i++);
}

/************************************************************************/
//������..��..X�᷽��������Ϣ�����
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
//������..��..Y�᷽��������Ϣ�����
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

