#include "hcsr04.h"

struct _hcsr04 hcsr04;

void Hcsr04_Init(void)
{
  GPIO_InitTypeDef   GPIO_InitStructure; 
	EXTI_InitTypeDef   EXTI_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;
    
	RCC_AHB1PeriphClockCmd(RCC_HCSR04 , ENABLE );
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = TRIG_HCSR04_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(HCSR04_PORT,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = ECHO_HCSR04_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(HCSR04_PORT,&GPIO_InitStructure);
	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC,GPIO_PinSource4);
  EXTI_InitStructure.EXTI_Line = EXTI_HCSR04_LINE;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI_HCSR04_CHANNEL;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

void EXTI4_IRQHandler(void)
{
	{
		if(GPIO_ReadInputDataBit(HCSR04_PORT, ECHO_HCSR04_Pin)==1)
			hcsr04.start_time = GetSysTime_us()/1000000.0f;
		else		
		{
			hcsr04.pulse_duration = GetSysTime_us()/1000000.0f - hcsr04.start_time;
			hcsr04.distance = hcsr04.pulse_duration*340/2;
			hcsr04.distance = MIN(hcsr04.distance,1.2f);
		}
			EXTI_ClearITPendingBit(EXTI_Line4);
	}
}

void Hcsr04_Filter(void)
{
		hcsr04.distance_filter = KalmanFilter_d(hcsr04.distance,KALMAN_QD,KALMAN_RD);
}
