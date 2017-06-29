#include "..\App\includes.h"
extern void USART_Config(USART_TypeDef* USARTx,u32 baud);		  //�����ⲿ����
/*
*********************************************************************************************************

*/

/*******************************************************************************
* Function Name  : RCC_Configuration
* Description    : Configures the different system clocks.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/

////////////////////////////////////////////////////////
void RCC_Configuration(void)
{	
	
	
  SystemInit(); 
	/*startup_stm32f10x_cl.s�������ļ��� �� SystemInit() ��  SetSysClock () �� SetSysClockTo72()�������ĵ�*/

}

//�رյ��Խӿڣ���GPIOʹ��
void UnableJTAG(void)
{
   
   RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;                     // enable clock for Alternate Function
   AFIO->MAPR &= ~(7UL<<24); // clear used bit
   AFIO->MAPR |= (4UL<<24); // set used bits
}

/*******************************************************************************
* Function Name  : GPIO_Configuration
* Description    : PB5: LED1 (mini and V3)
                   PD6��LED2 (only V3)
				   PD3��LED3 (only V3)
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /*�Կ���LEDָʾ�Ƶ�IO�ڽ����˳�ʼ�������˿�����Ϊ������������������ٶ�Ϊ50Mhz��PA9,PA10�˿ڸ���Ϊ����1��TX��RX��
  ������ĳ������ʱ������Ӧ�������ڵĶ˿ڵ�ʱ�ӽ���ʹ�ܡ������޷����óɹ��������õ��˶˿�B��D,E�� ���Ҫ���⼸���˿ڵ�ʱ��
  ����ʹ�ܣ�ͬʱ�����õ�����IO�ڹ����������ô��ڡ���˻�Ҫʹ��AFIO�����ù���IO��ʱ�ӡ�*/
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOB , ENABLE); 
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				                 //LED1
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);					 
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_3;		 			//LED2, LED3
  GPIO_Init(GPIOD, &GPIO_InitStructure);
}


/*******************************************************************************
* Function Name  : NVIC_Configuration
* Description    : Configures Vector Table base location.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NVIC_Configuration(void)
{

  //EXTI_InitTypeDef EXTI_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Configure one bit for preemption priority */
  #if defined (VECT_TAB_RAM)
  /* Set the Vector Table base location at 0x20000000 */ 
  NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0); 
#elif defined(VECT_TAB_FLASH_IAP)
  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x2000);
#else  /* VECT_TAB_FLASH  */
  /* Set the Vector Table base location at 0x08000000 */ 
  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);   
#endif 

  /* Configure the NVIC Preemption Priority Bits */  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

  
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;			     	//���ô���1�ж�
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
 
}

void BSP_Init(void)
{
  /* System Clocks Configuration --72M*/
  RCC_Configuration();   

  GPIO_Configuration();
  
  /* NVIC configuration */
  /*Ƕ�������жϿ����� 
      ˵����USART1��ռ���ȼ�����0�����1λ�� ���������ȼ�����0�����7λ�� */ 
  NVIC_Configuration();
  
  USART_Config(USART1,115200);		  //����1��ʼ��
  
}



////SYSTICK ���ã� 10msһ��systick�жϣ�����ucos ���Ƚ��ģ� 1KHz
void  OS_CPU_SysTickInit(void)
{
    RCC_ClocksTypeDef  rcc_clocks;
    INT32U         cnts;


    RCC_GetClocksFreq(&rcc_clocks);

    cnts = (INT32U)rcc_clocks.HCLK_Frequency/OS_TICKS_PER_SEC;

	SysTick_Config(cnts);

  
}


#ifdef  DEBUG
/*******************************************************************************
* Function Name  : assert_failed
* Description    : Reports the name of the source file and the source line number
*                  where the assert_param error has occurred.
* Input          : - file: pointer to the source file name
*                  - line: assert_param error line source number
* Output         : None
* Return         : None
*******************************************************************************/
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/

