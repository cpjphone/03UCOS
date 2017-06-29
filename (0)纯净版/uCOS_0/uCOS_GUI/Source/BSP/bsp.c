/*********************************************************************************      
* �����ܡ���Ӳ��ƽ̨�ĳ�ʼ�� 
*********************************************************************************/
#include "includes.h"


void GPIO_Config(void);					  //GPIO����
void GPIO_Config_LED(void);
void  OS_CPU_SysTickInit(void);									   
void RCC_Configuration(void);


////JTAGģʽ���ö���
//#define JTAG_SWD_DISABLE   0X02
//#define SWD_ENABLE         0X01
//#define JTAG_SWD_ENABLE    0X00	
////JTAGģʽ����,��������JTAG��ģʽ
////mode:jtag,swdģʽ����;00,ȫʹ��;01,ʹ��SWD;10,ȫ�ر�;
////CHECK OK	
////100818		  
//void JTAG_Set(u8 mode)
//{
//	u32 temp;
//	temp=mode;
//	temp<<=25;
//	RCC->APB2ENR|=1<<0;     //��������ʱ��	   
//	AFIO->MAPR&=0XF8FFFFFF; //���MAPR��[26:24]
//	AFIO->MAPR|=temp;       //����jtagģʽ
//} 



/************************************************************************/
//ϵͳʱ�����ú���	
/************************************************************************/
//void RCC_Configuration(void)
//{
//	 ErrorStatus HSEStartUpStatus;                    //�����ⲿ���پ�������״̬ö�ٱ���
//	 RCC_DeInit();                                    //��λRCC�ⲿ�豸�Ĵ�����Ĭ��ֵ
//	 RCC_HSEConfig(RCC_HSE_ON);                       //���ⲿ���پ���
//	 HSEStartUpStatus = RCC_WaitForHSEStartUp();      //�ȴ��ⲿ����ʱ��׼����
//	 if(HSEStartUpStatus == SUCCESS)                  //�ⲿ����ʱ���Ѿ�׼���
//	  {
//		   FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable); 	//����FLASHԤ�����幦�ܣ�����FLASH�Ķ�ȡ�����г����б�����÷�.λ�ã�RCC��ʼ���Ӻ������棬ʱ������֮��
//		   FLASH_SetLatency(FLASH_Latency_2);                   	 //flash��������ʱ
//			    		
//						// RCC_HCLK  ���� 
//				   	    // RCC_SYSCLK_Div1   AHBʱ�� =  ϵͳʱ�� 
//					    // RCC_SYSCLK_Div2   AHBʱ�� =  ϵͳʱ�� / 2 
//						// RCC_SYSCLK_Div4   AHBʱ��  = ϵͳʱ�� / 4 
//						// RCC_SYSCLK_Div8   AHBʱ��  =  ϵͳʱ�� / 8 
//						// RCC_SYSCLK_Div16  AHBʱ��  =  ϵͳʱ�� / 16 
//						// RCC_SYSCLK_Div64  AHBʱ��  =  ϵͳʱ�� / 64 
//						// RCC_SYSCLK_Div128 AHBʱ��  =  ϵͳʱ��  / 128 
//						// RCC_SYSCLK_Div256 AHBʱ��  =  ϵͳʱ��  / 256 
//						// RCC_SYSCLK_Div512 AHBʱ��  =  ϵͳʱ��  / 512 
//								
//		   RCC_HCLKConfig(RCC_SYSCLK_Div1);               //����AHB(HCLK)ʱ�ӵ���==SYSCLK
//		   RCC_PCLK2Config(RCC_HCLK_Div1);                //����APB2(PCLK2)��==AHBʱ��
//		   RCC_PCLK1Config(RCC_HCLK_Div2);                //����APB1(PCLK1)��==AHB1/2ʱ��
//		         
//		   RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);  //����PLLʱ�� == �ⲿ���پ���ʱ�� * 9 = 72MHz
//		   RCC_PLLCmd(ENABLE);                                   //ʹ��PLLʱ��
//		   
//		   while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)    //�ȴ�PLLʱ�Ӿ���
//		   {
//		   }
//		   RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);            //����ϵͳʱ�� = PLLʱ��
//		   while(RCC_GetSYSCLKSource() != 0x08)                  //���PLLʱ���Ƿ���Ϊϵͳʱ��
//		   {
//		   }
//	  }

//}

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

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
// 	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_1 | GPIO_Pin_11;
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		 //�������
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_Init(GPIOA, &GPIO_InitStructure);
// 	
// 	/* ��ʪ��������� */
// 	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_1; //����GPIOΪͬһ���Ͷ˿�
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;	 //�������
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //��������Ƶ��Ϊ50HZ
// 	GPIO_Init(GPIOA, &GPIO_InitStructure);   //��ʼ��GPIOB�˿�
// 	
// 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;  // ѡ�����н�
//   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //���ó�����ʽ���
//   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //���ģʽ�� I/O����ٶ� 50M HZ
//   GPIO_Init(GPIOA, &GPIO_InitStructure);  //��ʼ��PB��
// 	
// 	/* ��2������USART Tx��GPIO����Ϊ���츴��ģʽ */
// 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_Init(GPIOA, &GPIO_InitStructure);
// 	
// 	/* ��3������USART Rx��GPIO����Ϊ��������ģʽ
// 		����CPU��λ��GPIOȱʡ���Ǹ�������ģʽ���������������費�Ǳ����
// 		���ǣ��һ��ǽ�����ϱ����Ķ������ҷ�ֹ�����ط��޸���������ߵ����ò���
// 	*/
// 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
// 	GPIO_Init(GPIOA, &GPIO_InitStructure);
// 	/*  ��3���Ѿ����ˣ�����ⲽ���Բ���*/
// 	
// 	//����USARTx_TxΪ�����������
//   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
//   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//   GPIO_Init(GPIOA, &GPIO_InitStructure);

//   //���� USARTx_Rx Ϊ��������
//   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
//   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//   GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/************************************************************************/
//����2�ж�����
/************************************************************************/
void NVIC_Configuration(void)
{

//   NVIC_InitTypeDef NVIC_InitStructure;
//   
//    /* Set the Vector Table base location at 0x08000000 */
//    NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);
//   
//    /* Configure the NVIC Preemption Priority Bits */  
//    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
//   
//    /* Enable the USART1 Interrupt */
//    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;       //ͨ������Ϊ����1�ж�
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	   //�ж���Ӧ���ȼ�0
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		   //���ж�
//    NVIC_Init(&NVIC_InitStructure); 		
 
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
	  //GPIOC ->ODR ^= GPIO_Pin_6;
}

/************************************************************************/
//BSP��ʼ������	  ��BSP INITIALIZATION��
/************************************************************************/
void  BSP_Init(void)
{
//	RCC_Configuration();  
   /* Enable GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG and AFIO clocks */
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |RCC_APB2Periph_GPIOC 
         | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOF | RCC_APB2Periph_GPIOG 
         | RCC_APB2Periph_AFIO, ENABLE);
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
// 	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	
 	OS_CPU_SysTickInit() ;
	GPIO_Config(); 
	GPIO_Config_LED();

  NVIC_Configuration();
}

