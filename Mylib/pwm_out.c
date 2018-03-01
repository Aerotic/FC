/*********************************************
              ②     ①
                 \ /
                 / \
              ③     ④
**********************************************/
#include "pwm_out.h"

struct _speed speed;
struct _aircraft aircraft;
int32_t cnt;
void TIM3_PWM_Init(uint16_t freq)
{	
		GPIO_InitTypeDef         GPIO_InitStructure;
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		TIM_OCInitTypeDef        TIM_OCInitStructure;
		
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
		
		GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM3); 
		GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_TIM3); 
		GPIO_PinAFConfig(GPIOC,GPIO_PinSource8,GPIO_AF_TIM3); 
		GPIO_PinAFConfig(GPIOC,GPIO_PinSource9,GPIO_AF_TIM3); 
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9; 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_Init(GPIOC,&GPIO_InitStructure);
			
		TIM_TimeBaseStructure.TIM_Prescaler=20;
		TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
		TIM_TimeBaseStructure.TIM_Period=10000;
		TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
		TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
		TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
		
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
		
		TIM_OC1Init(TIM3, &TIM_OCInitStructure);
		TIM_OC2Init(TIM3, &TIM_OCInitStructure);
		TIM_OC3Init(TIM3, &TIM_OCInitStructure);
		TIM_OC4Init(TIM3, &TIM_OCInitStructure);
		
		TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable); 
		TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable); 
		TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable); 
		TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable); 
		TIM_ARRPreloadConfig(TIM3, ENABLE);
		
		TIM_Cmd(TIM3, ENABLE); 

#ifdef ESC_CORRECT
		TIM3->CCR1=MAX_MOTOR_PWM;
		TIM3->CCR2=MAX_MOTOR_PWM;
		TIM3->CCR3=MAX_MOTOR_PWM;
		TIM3->CCR4=MAX_MOTOR_PWM;
		DelayMs(2000);
#endif

		TIM3->CCR1=MIN_MOTOR_PWM;
		TIM3->CCR2=MIN_MOTOR_PWM;
		TIM3->CCR3=MIN_MOTOR_PWM;
		TIM3->CCR4=MIN_MOTOR_PWM;
		DelayMs(2000);	
}

extern float q0, q1, q2, q3;
void AndroidRPM(void)
{
		if(RC.CH[5]==2)
		{
			TIM3->CCR1=(int16_t)(4000);
			TIM3->CCR2=(int16_t)(4000);
			TIM3->CCR3=(int16_t)(4000);
			TIM3->CCR4=(int16_t)(4000);
		}
		else
		{
			TIM3->CCR1=(int16_t)((rx_buffer[0]<<8) | rx_buffer[1]);
			TIM3->CCR2=(int16_t)((rx_buffer[2]<<8) | rx_buffer[3]);
			TIM3->CCR3=(int16_t)((rx_buffer[4]<<8) | rx_buffer[5]);
			TIM3->CCR4=(int16_t)((rx_buffer[6]<<8) | rx_buffer[7]);
		}

}
void Motor_Speed_Update(void)
{
	if( RC.CH[3]<=-650)
	{
		
		if(cnt>500)
		{
			aircraft.lockchange = 1;
			
			cnt=0;
		}
		else
			cnt++;
	}
	else
		aircraft.lockchange = 0;
	//遥控内八 飞机锁状态需要改变
	/*
	if(RC.CH[2]>=650 && RC.CH[3]<=-650)
		aircraft.lockchange = 1;
	else
		aircraft.lockchange = 0;
	*/
	//飞机锁状态改变完成
	if(aircraft.lockchange == 0 && aircraft.lockchange_last == 1)
	{
    if(aircraft.unlock) aircraft.unlock = 0;//飞机上锁
		else 
		{
			aircraft.unlock = 1;									//解锁
			ctrl.outer.exp.z = 0;                 //期望偏航角为当前偏航角
			q0 = 1; q1 = 0; q2 = 0; q3 = 0;
		}
  }
	aircraft.lockchange_last = aircraft.lockchange;
	
	if(aircraft.init_ok)
	{
			//飞机解锁 最低怠速
			if(aircraft.unlock)
			{
				thr.comp = thr.value/cos(angle.pitch/RtA)/cos(angle.roll/RtA);
				speed.motor1 = thr.comp - ctrl.inner.out.x - ctrl.inner.out.y - ctrl.inner.out.z + (hgt_ctrl.acc.out + hgt_ctrl.vel.out)/cos(angle.pitch/RtA)/cos(angle.roll/RtA);
				speed.motor2 = thr.comp + ctrl.inner.out.x - ctrl.inner.out.y + ctrl.inner.out.z + (hgt_ctrl.acc.out + hgt_ctrl.vel.out)/cos(angle.pitch/RtA)/cos(angle.roll/RtA);
				speed.motor3 = thr.comp + ctrl.inner.out.x + ctrl.inner.out.  y - ctrl.inner.out.z + (hgt_ctrl.acc.out + hgt_ctrl.vel.out)/cos(angle.pitch/RtA)/cos(angle.roll/RtA);
				speed.motor4 = thr.comp - ctrl.inner.out.x + ctrl.inner.out.y + ctrl.inner.out.z + (hgt_ctrl.acc.out + hgt_ctrl.vel.out)/cos(angle.pitch/RtA)/cos(angle.roll/RtA);
				
			
//				speed.motor1=1.2*speed.motor1;
//				speed.motor2=1.2*speed.motor2;
//				speed.motor3=1.2*speed.motor3;
//				speed.motor4=1.2*speed.motor4;
				
				
				
				speed.motor1 = LIMIT(speed.motor1, READY_THR*0.8f, MAX_THR *1.1f);
				speed.motor2 = LIMIT(speed.motor2, READY_THR*0.8f, MAX_THR *1.1f);
				speed.motor3 = LIMIT(speed.motor3, READY_THR*0.8f, MAX_THR *1.1f);
				speed.motor4 = LIMIT(speed.motor4, READY_THR*0.8f, MAX_THR *1.1f);
			}
			//飞机上锁 电机停止
			else
			{ 
				speed.motor1 = 0;
				speed.motor2 = 0;
				speed.motor3 = 0;
				speed.motor4 = 0;
			}
				
				TIM3->CCR1 = (int16_t)(MIN_MOTOR_PWM + 4*speed.motor1);
				TIM3->CCR2 = (int16_t)(MIN_MOTOR_PWM + 4*speed.motor2);
				TIM3->CCR3 = (int16_t)(MIN_MOTOR_PWM + 4*speed.motor3);
				TIM3->CCR4 = (int16_t)(MIN_MOTOR_PWM + 4*speed.motor4);
				
  }
}//RC.CH[3]



