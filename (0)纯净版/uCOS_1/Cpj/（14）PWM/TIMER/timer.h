#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"
//#include "touch.h" 
//#include "lcd.h"	
#include "led.h" 
#include "key.h"		
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//Mini STM32������
//ͨ�ö�ʱ�� ��������			   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2010/12/03
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	  

//ͨ���ı�TIM3->CCR2��ֵ���ı�ռ�ձȣ��Ӷ�����LED0������
//#define LED0_PWM_VAL TIM3->CCR2 
#define flage_ccr1 TIM2->CCR1
#define flage_ccr2 TIM2->CCR2
#define flage_ccr3 TIM2->CCR3
#define flage_ccr4 TIM2->CCR4
							  
#define PWM0 PAout(6)// PA8
#define PWM1 PDout(7)// PD2	

void PWM_CH1_CH2(u16 arr,u16 psc);
void PWM_nj(u16 pwm_n,u16 pwm_j);
void PWM_CH3CH4(u16 arr,u16 psc);

#endif























