
// #include "includes.h"

// #define TX_OK   	0x20  //TX��������ж�

// #define MAX_TX  	0x10  //�ﵽ����ʹ����ж�

// u8 NRF24L01_TxPacket(u8 *txbuf);
// u8 NRF24L01_RxPacket(u8 *rxbuf);

// u8 tmp_buf[3];




// void Dealdata()
// {
// 	tmp_buf[2] = 3;
// 	tmp_buf[1] = 2;
// 	tmp_buf[0] = 1;
// 	NRF24L01_Init();    //��ʼ��NRF24L01
// 	OSTimeDlyHMSM(0, 0, 0, 10);
// 	while(NRF24L01_Check())//��ⲻ��24L01
// 	{
// 		OSTimeDlyHMSM(0, 0, 0, 10);
// 	}
// 	RX_Mode();
// 	OSTimeDlyHMSM(0, 0, 0, 3);
// 	while (1)
// 	{	
// 		if(NRF24L01_RxPacket(tmp_buf)==0)	
// 		{
// 				//if(tmp_buf[0] == 12){
// 			GPIO_SetBits(GPIOC,GPIO_Pin_6);
// 			GPIO_SetBits(GPIOC,GPIO_Pin_7);
// 			
// 			OSTimeDlyHMSM(0, 0, 0, 2);
// 		}
// 	}
// }

