
#include "includes.h"

#define uint unsigned int
#define uchar unsigned char

#define Send_ENGLISH_key GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)		  //发短信
#define Send_CALLING_key GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)

#define MAXCHAR 81
char  aa[MAXCHAR];

uchar ATE0[]="ATE0\r\n";
uchar CREG_CMD[]="AT+CREG?\r\n";
uchar SMS_send[]="AT+CMGS=18\r\n";
uchar ATCN[]="AT+CNMI=2,1\r\n";
uchar CMGF0[]="AT+CMGF=0\r\n";
uchar CMGF1[]="AT+CMGF=1\r\n";
uchar CMGR[12]="AT+CMGR=1\r\n";
uchar CMGD[12]="AT+CMGD=1\r\n";

uchar Esign = 0,Fsign = 0,Jsign = 0;
//康佳俊 ： 18439893663   8134893966F3
//冯吉春： 18239932500		8132992305F0

/****************亚飞**********************/
// #define CALL_YOU_TELNUMBER "ATD15238643714;\r\n"      //填入你手上的手机号码 不是板子的
// #define SEND_MESSA_TO_YOUR "at+cmgs=\"15238643714\"\r\n"    //填入你手上的手机号码 不是板子的
// #define SEND_MESSA_CONTENT "tpytongxin.taobao.com"
// #define CALL_YOU_TELNUMBER "ATD15238643714;\r\n"    //填入你手上的手机号码 不是板子的
// //#define CALL_YOU_TELNUMBER "ATD15238643714;\r\n"    //填入你手上的手机号码 不是板子的

// /****************亚飞**********************/
// #define CALL_YOU_TELNUMBER "ATD18439893663;\r\n"      //填入你手上的手机号码 不是板子的
// #define SEND_MESSA_TO_YOUR "at+cmgs=\"18439893663\"\r\n"    //填入你手上的手机号码 不是板子的
// #define SEND_MESSA_CONTENT "tpytongxin.taobao.com"
// #define CALL_YOU_TELNUMBER "ATD18439893663;\r\n"    //填入你手上的手机号码 不是板子的
// //#define CALL_YOU_TELNUMBER "ATD15238643714;\r\n"    //填入你手上的手机号码 不是板子的

/****************小春*********************/
#define CALL_YOU_TELNUMBER "ATD18239932500;\r\n"      //填入你手上的手机号码 不是板子的
#define SEND_MESSA_TO_YOUR "at+cmgs=\"18239932500\"\r\n"    //填入你手上的手机号码 不是板子的
#define SEND_MESSA_CONTENT "tpytongxin.taobao.com"
#define CALL_YOU_TELNUMBER "ATD18239932500;\r\n"    //填入你手上的手机号码 不是板子的

//uchar  Sms2_Pdu[]="0891683108200205F011000B818134893966F30008A704521B601D";   //佳俊
uchar  Sms2_Pdu[]="0891683108200205F011000B818132992305F00008A704521B601D";   //小春
//uchar tab[] = "00.0";
uchar tab[] = "A:T:00.00C/R:00.00RH/U:000V/door:000/Danger:000/";
uchar tab2[4] ="YES";
uchar tab3[4] ="N O";
//char tab[1] = "0";

uchar a,j=0,flag=0;
int g_timeout=0;

extern u8 tdata[4];
extern u8 tdata2[4];
extern int fire1,fire2;
extern int man1,man2;
extern int danger1,danger2;

/************************************************************************/
//STM32向串口2发送1字节   
/************************************************************************/
void Print_Char(u8 ch)
{
  USART_SendData(USART2, (u8) ch);
  while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
}

/************************************************************************/
//发送一个字符串
/************************************************************************/
void Print_Str(u8* buf )
{   
	while(*buf!='\0')
	{ 
		Print_Char(*buf);
		OSTimeDlyHMSM(0, 0, 0, 4);
		buf++;
	}
}

/************************************************************************/
//清除自定缓冲区
/************************************************************************/
void clearBuff(void)
{
	for(j=0;j<MAXCHAR;j++)
	{
		aa[j]=0x00;
	}
	j=0;
}

/************************************************************************/
//检测单片机和模块的连接
/************************************************************************/
int Hand()
{
	OSTimeDlyHMSM(0, 0, 0, 10);
	if(strstr(aa,"OK")!=NULL)             //检测单片机和模块的连接
	{
		g_timeout=0;
		return 1;
	}
	if(g_timeout>50)
	{
		OSTimeDlyHMSM(0, 0, 0, 10);
		g_timeout=0;
		return -1;
	}
	g_timeout++;
	return 0;
}

/************************************************************************/
//GSM 初始化 
/************************************************************************/
void AT(void)
{
	clearBuff();
	Print_Str(ATE0);
	OSTimeDlyHMSM(0, 0, 0, 50);

	while(strstr(aa,"OK")==NULL)		//模块连接【..】
	{
		OSTimeDlyHMSM(0, 0, 0, 50);   
		clearBuff();
		Print_Str(ATE0);
		OSTimeDlyHMSM(0, 0, 0, 5); 
	}
	/*********** 模块连接【OK】*************************/
	Print_Str(ATCN);
	OSTimeDlyHMSM(0, 0, 0, 50);

	clearBuff();
	Print_Str(CREG_CMD);
	OSTimeDlyHMSM(0, 0, 0, 50);  
	if(((aa[10]=='0')&&(aa[12]=='1'))||((aa[10]=='0')&&(aa[12]=='5')))//模块注册【OK】
	{
		clearBuff();
		
	}
	else   //模块注册【..】
	{
		clearBuff();
		OSTimeDlyHMSM(0, 0, 0, 50);  
	}		
}

/************************************************************************/
//打电话
/************************************************************************/
void send_call()
{
    clearBuff();
    OSTimeDlyHMSM(0, 0, 0, 100);
    Print_Str(CALL_YOU_TELNUMBER); //打电话
    clearBuff();
    OSTimeDlyHMSM(0, 0, 0, 300);
}
/************************************************************************/
//发送英文短信
/************************************************************************/
void send_english()
{
	clearBuff();
	Print_Str(CMGF1);
	OSTimeDlyHMSM(0, 0, 0, 100);
	Print_Str(SEND_MESSA_TO_YOUR);
	OSTimeDlyHMSM(0, 0, 0, 500);
	Print_Str(tab);  //发短信内容
	OSTimeDlyHMSM(0, 0, 0, 10);
	Print_Char(0x1A);      //发送结束符号
	OSTimeDlyHMSM(0, 0, 0, 300);
	clearBuff();
}

/************************************************************************/
//发送中午短信
/************************************************************************/
void send_pdu()
{
	clearBuff();
	Print_Str(CMGF0);
	OSTimeDlyHMSM(0, 0, 0, 100);
	Print_Str(SMS_send);  //发送中文短信
	OSTimeDlyHMSM(0, 0, 0, 500);
	Print_Str(Sms2_Pdu);  //发短信内容
	Print_Char(0x1A);      //发送结束符号
	OSTimeDlyHMSM(0, 0, 0, 500);
	//led(0x04);
	clearBuff();
}

/************************************************************************/
//发送温度
/************************************************************************/
void send_18B20()
{

}

void GSM(void)
{	
	int i = 0;
	GPIO_SetBits(GPIOA,GPIO_Pin_11); 
	GPIO_SetBits(GPIOA,GPIO_Pin_4); 	
 	clearBuff();
	AT();		   //初始化模块
	Esign = 2;
	OSTimeDlyHMSM(0, 0, 0, 4);
	Print_Str(CMGD);
	OSTimeDlyHMSM(0, 0, 0, 50);
	while(Hand()==0);
	clearBuff();

	Print_Str(CMGF1);
	OSTimeDlyHMSM(0, 0, 0, 30);

	Print_Str(ATCN);
	OSTimeDlyHMSM(0, 0, 0, 30);
	
	while(1)
	{
		if(fire1)     //打电话按键
		{	  
			OSTimeDlyHMSM(0, 0, 0, 80);
			if(fire1)
			{

				//v_Lcd12864PutString_f( 1,1, "给你电话【..】") ;
				send_call();
				
				tab[4] = 0x30 + tdata[2]/10;
				tab[5] = 0x30 + tdata[2]%10;
				tab[7] = 0x30 + tdata[3]/10;
				tab[8] = 0x30 + tdata[3]%10;
				
				tab[13] = 0x30 + tdata[0]/10;
				tab[14] = 0x30 + tdata[0]%10;
				tab[16] = 0x30 + tdata[1]/10;
				tab[17] = 0x30 + tdata[1]%10;
				
				tab[23] = 0x30 + 0;
				tab[24] = 0x30 + 0;
				tab[25] = 0x30 + 5;
				
				if(man1)
				{
 					tab[33] = tab2[0];
 					tab[34] = tab2[1];
 					tab[35] = tab2[2];
 				}
					tab[33] = tab3[0];
 					tab[34] = tab3[1];
 					tab[35] = tab3[2];
				
				if(fire1)
				{
 					tab[44] = tab2[0];
 					tab[45] = tab2[1];
 					tab[46] = tab2[2];
 				}
					tab[44] = tab3[0];
 					tab[45] = tab3[1];
 					tab[46] = tab3[2];

				if(!i)
					
				{
					send_english();//发英文TEXT短信按键
					i = 1;
				}
				
				Fsign = 2;
				OSTimeDlyHMSM(0, 0, 0, 7);
			}
			//v_Lcd12864PutString_f( 1,1, "给你电话【OK】") ;

		}

		if(strstr(aa,"RING")!=NULL)
		{
			//FENGMINGQI=0;
			OSTimeDlyHMSM(0, 0, 0, 4);
			GPIO_ResetBits(GPIOA,GPIO_Pin_11);
			//GPIO_ResetBits(GPIOA,GPIO_Pin_11);
			//		v_Lcd12864PutString_f( 1,1, "电话来了【亲】") ;
			Jsign = 2;
			danger1 = 1;
			if(fire2) danger2 = 1;
			OSTimeDlyHMSM(0, 0, 0, 7);
			clearBuff();
	 }	
		OSTimeDlyHMSM(0, 0, 0, 5);
	} 
	

}

/************************************************************************/
//中断服务函数
/************************************************************************/
void USART2_IRQHandler(void)
{  
	if(USART_GetITStatus(USART2, USART_IT_RXNE)==SET)
	{  
		aa[j] = USART_ReceiveData(USART2);  	                                  			   
		USART_ClearITPendingBit(USART2,USART_IT_RXNE);
		j++; 
	}

	//溢出-如果发生溢出需要先读SR,再读DR寄存器则可清除不断入中断的问题[牛人说要这样]
	if(USART_GetFlagStatus(USART2,USART_FLAG_ORE)==SET)
	{
		USART_ClearFlag(USART2,USART_FLAG_ORE);
	}
}



