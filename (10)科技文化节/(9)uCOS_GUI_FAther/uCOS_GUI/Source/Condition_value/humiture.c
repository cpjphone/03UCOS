#include "includes.h"
#include "sys.h"
#include "math.h"
u8 tdata[4];
u8 sbuf,check;

#define DHT11_Out PAout(1)
#define DHT11_In  PAin(1)

/*******************************************��ʱ����**********************************/ 
void NOP()
{ vu16 i;
  for(i=0; i<100; i++); 
}

unsigned char StartDHT11(void)
{

   DHT11_Out = 0;
   //delay_ms(18);  //������ʼ,��������Ҫ����18ms
	OSTimeDlyHMSM(0,0,0,18);
  
   DHT11_Out = 1;	//�ͷ�����
   //delay_us(25);  //wait 20-40uS �ȴ�DHT11�ĵ͵�ƽ��Ӧ�ź�
   NOP();NOP();NOP();NOP();NOP();   
   if(!DHT11_In)
   {
	   	 while(!DHT11_In);//�͵�ƽ����Ӧ�źţ�80us
		   while(DHT11_In);//��������80us�ĸߵ�ƽ����׼���ź�
		   return 1;
   }
	return 0;
}
void com(void)
{
	u8 i,tt;
	tt = 0;
	for(i = 0;i<8;i++)
	{
		sbuf <<= 1;
		//delay_us(20);//���յ���Ӧ������50us�ĵ͵�ƽ��ʾ�������ݵĿ�ʼ����������С��ʱһ��
		NOP();
		while(!DHT11_In);//�ȵ��ߵ�ƽ�ĳ��֣��ߵ�ƽ��ʱ���ʾ��������λ��0��1
		//delay_us(28);//����Ϊ0���ź�ʱ��Ϊ26-28us��1��Ϊ70us�����ﳬʱ���
		NOP();NOP();
		tt = 100;
		while(tt++);
		if(DHT11_In)//�����Ϊ��
		{
			 sbuf |= 0x01;
			// delay_us(30);//�������ʱ�㹻�ˣ�40+10+30>70��
			NOP();
		}
		else //������
		{
			sbuf &= 0xfe;
		}
	}
}
void ReadDHT11(void)
{
	u8 sum,tdata1[4];
	
	if(StartDHT11())	//�ж��Ƿ��Ѿ���Ӧ
	{
		com();
		tdata1[0]=sbuf;
		com();
		tdata1[1]=sbuf;
		com();
		tdata1[2]=sbuf;		
		com();
		tdata1[3]=sbuf;
		com();
		check = sbuf;
		sum = (tdata1[0]+tdata1[1]+tdata1[2]+tdata1[3]);
	}
if((fabs(check - sum))<10)
	{
		tdata[2]=(char)tdata1[2];
		tdata[3]=(char)tdata1[3];
		tdata[0]=(char)tdata1[0];
		tdata[1]=(char)tdata1[1];
		
	}
	//else	
//	return 0;
}




