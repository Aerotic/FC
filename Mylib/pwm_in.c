#include "board.h"

float RC_PPM_CH[8];

void PWM_IN_Init(void)
{
GPIO_InitTypeDef   GPIO_InitStructure;
  //TIM_ICInitTypeDef  TIM_ICInitStructure;
	//NVIC_InitTypeDef   NVIC_InitStructure;

/*---------------------定时器4-----------------------------*/
 /* RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	//GPIO_InitTypeDef         GPIO_InitStructure;
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		TIM_OCInitTypeDef        TIM_OCInitStructure;
		
		
		GPIO_PinAFConfig(GPIOB,GPIO_PinSource6,GPIO_AF_TIM3); 
		GPIO_PinAFConfig(GPIOB,GPIO_PinSource7,GPIO_AF_TIM3); 
		GPIO_PinAFConfig(GPIOB,GPIO_PinSource8,GPIO_AF_TIM3); 
		GPIO_PinAFConfig(GPIOB,GPIO_PinSource9,GPIO_AF_TIM3); 
		
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
		TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);
		
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
		
		TIM_OC1Init(TIM4, &TIM_OCInitStructure);
		TIM_OC2Init(TIM4, &TIM_OCInitStructure);
		TIM_OC3Init(TIM4, &TIM_OCInitStructure);
		TIM_OC4Init(TIM4, &TIM_OCInitStructure);
		
		TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable); 
		TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable); 
		TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable); 
		TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable); 
		TIM_ARRPreloadConfig(TIM4, ENABLE);
		*/
		//TIM_Cmd(TIM4, ENABLE); 
	/*NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);	 
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_TIM4);
  
	TIM4->PSC = 18-1;
	
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_BothEdge;
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICFilter = 0x0;
  TIM_ICInit(TIM4, &TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_BothEdge;
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICFilter = 0x0;
  TIM_ICInit(TIM4, &TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_3;
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_BothEdge;
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICFilter = 0x0;
  TIM_ICInit(TIM4, &TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_4;
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_BothEdge;
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICFilter = 0x0;
  TIM_ICInit(TIM4, &TIM_ICInitStructure);
  */
  /* TIM enable counter */
  //TIM_Cmd(TIM4, ENABLE);

  /* Enable the CC2 Interrupt Request */
  /*TIM_ITConfig(TIM4, TIM_IT_CC1, ENABLE);
	TIM_ITConfig(TIM4, TIM_IT_CC2, ENABLE);
	TIM_ITConfig(TIM4, TIM_IT_CC3, ENABLE);
	TIM_ITConfig(TIM4, TIM_IT_CC4, ENABLE);*/
	
/*---------------------定时器5-----------------------------*/
 /* RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);	 
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_TIM5);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_TIM5);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_TIM5);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_TIM5);
  
	TIM5->PSC = 18-1;
	
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_BothEdge;
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICFilter = 0x0;
  TIM_ICInit(TIM5, &TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_BothEdge;
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICFilter = 0x0;
  TIM_ICInit(TIM5, &TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_3;
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_BothEdge;
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICFilter = 0x0;
  TIM_ICInit(TIM5, &TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_4;
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_BothEdge;
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICFilter = 0x0;
  TIM_ICInit(TIM5, &TIM_ICInitStructure);*/
  
  /* TIM enable counter */
  //TIM_Cmd(TIM5, ENABLE);

  /* Enable the CC2 Interrupt Request */
/*  TIM_ITConfig(TIM5, TIM_IT_CC1, ENABLE);
	TIM_ITConfig(TIM5, TIM_IT_CC2, ENABLE);
	TIM_ITConfig(TIM5, TIM_IT_CC3, ENABLE);
	TIM_ITConfig(TIM5, TIM_IT_CC4, ENABLE);*/
}
/*
void TIM4_IRQHandler(void)		
{
	static u16 temp_cnt[4][2]={0};//    [x通道][0上升沿，1时间长]

	if(TIM4->SR & TIM_IT_CC1) 
	{
		TIM4->SR = ~TIM_IT_CC1;//TIM_ClearITPendingBit(TIM4, TIM_IT_CC1);
		TIM4->SR = ~TIM_FLAG_CC1OF;
		if(GPIOB->IDR & GPIO_Pin_6)
		{
			temp_cnt[0][0] = TIM4->CCR1;			
		}
		else
		{
      temp_cnt[0][1] = TIM4->CCR1 - temp_cnt[0][0];
			RC_PPM_CH[0] = 0.3683 * temp_cnt[0][1] - 2572.976;
		}
	}
	
	if(TIM4->SR & TIM_IT_CC2) 
	{
		TIM4->SR = ~TIM_IT_CC2;//TIM_ClearITPendingBit(TIM4, TIM_IT_CC2);
		TIM4->SR = ~TIM_FLAG_CC1OF;
		if(GPIOB->IDR & GPIO_Pin_7)
		{
			temp_cnt[1][0] = TIM4->CCR2;			
		}
		else
		{
      temp_cnt[1][1] = TIM4->CCR2 - temp_cnt[1][0];
			RC_PPM_CH[1] = -0.3683 * temp_cnt[1][1] + 2583.817;
		}
	}
	
	if(TIM4->SR & TIM_IT_CC3) 
	{
		TIM4->SR = ~TIM_IT_CC3;//TIM_ClearITPendingBit(TIM4, TIM_IT_CC3);
		TIM4->SR = ~TIM_FLAG_CC1OF;
		if(GPIOB->IDR & GPIO_Pin_8)
		{
			temp_cnt[2][0] = TIM4->CCR3;			
		}
		else
		{
      temp_cnt[2][1] = TIM4->CCR3 - temp_cnt[2][0];
			RC_PPM_CH[2] = 0.3683 * temp_cnt[2][1] - 2550.9824;
		}
	}
	
	if(TIM4->SR & TIM_IT_CC4) 
	{
		TIM4->SR = ~TIM_IT_CC4;//TIM_ClearITPendingBit(TIM4, TIM_IT_CC4);
		TIM4->SR = ~TIM_FLAG_CC1OF;
		if(GPIOB->IDR & GPIO_Pin_9)
		{
			temp_cnt[3][0] = TIM4->CCR4;			
		}
		else
		{
      temp_cnt[3][1] = TIM4->CCR4 - temp_cnt[3][0];
			RC_PPM_CH[3] = -0.3683 * temp_cnt[3][1] + 2572.976;
		}
	}
}

void TIM5_IRQHandler(void)		
{
	static u16 temp_cnt[4][2]={0};//    [x通道][0上升沿，1时间长]

	if(TIM5->SR & TIM_IT_CC1) 
	{
		TIM5->SR = ~TIM_IT_CC1;//TIM_ClearITPendingBit(TIM5, TIM_IT_CC1);
		TIM5->SR = ~TIM_FLAG_CC1OF;
		if(GPIOA->IDR & GPIO_Pin_0)
		{
			temp_cnt[0][0] = TIM5->CCR1;			
		}
		else
		{
      temp_cnt[0][1] = TIM5->CCR1 - temp_cnt[0][0];
			
			if(temp_cnt[0][1]>4400&&temp_cnt[0][1]<5300)
			 RC_PPM_CH[4] = 1;
			else if(temp_cnt[0][1]>8000&&temp_cnt[0][1]<9000)		
			 RC_PPM_CH[4] = 2;
			else RC_PPM_CH[4] = 3;
		}
	}
	
	if(TIM5->SR & TIM_IT_CC2) 
	{
		TIM5->SR = ~TIM_IT_CC2;//TIM_ClearITPendingBit(TIM5, TIM_IT_CC2);
		TIM5->SR = ~TIM_FLAG_CC1OF;
		if(GPIOA->IDR & GPIO_Pin_1)
		{
			temp_cnt[1][0] = TIM5->CCR2;			
		}
		else
		{
      temp_cnt[1][1] = TIM5->CCR2 - temp_cnt[1][0];
			RC_PPM_CH[5] = -0.3683 * temp_cnt[1][1] + 2476.817;
		}
	}
	
	if(TIM5->SR & TIM_IT_CC3) 
	{
		TIM5->SR = ~TIM_IT_CC3;//TIM_ClearITPendingBit(TIM5, TIM_IT_CC3);
		TIM5->SR = ~TIM_FLAG_CC1OF;
		if(GPIOA->IDR & GPIO_Pin_2)
		{
			temp_cnt[2][0] = TIM5->CCR3;			
		}
		else
		{
      temp_cnt[2][1] = TIM5->CCR3 - temp_cnt[2][0];

			if(temp_cnt[2][1]>4400&&temp_cnt[2][1]<5300)
			 RC_PPM_CH[6] = 1;
			else if(temp_cnt[2][1]>8000&&temp_cnt[2][1]<9000)		
			 RC_PPM_CH[6] = 2;
			else RC_PPM_CH[6] = 3;
			
		}
	}
	
	if(TIM5->SR & TIM_IT_CC4) 
	{
		TIM5->SR = ~TIM_IT_CC4;//TIM_ClearITPendingBit(TIM5, TIM_IT_CC4);
		TIM5->SR = ~TIM_FLAG_CC1OF;
		if(GPIOA->IDR & GPIO_Pin_3)
		{
			temp_cnt[3][0] = TIM5->CCR4;			
		}
		else
		{
      temp_cnt[3][1] = TIM5->CCR4 - temp_cnt[3][0];
			RC_PPM_CH[7] = -0.3683 * temp_cnt[3][1] + 2474.976;
		}
	}
}

void Get_PPM_Value(float T)
{
		RC.CH_LAST[0] = RC.CH[0];
		RC.CH_LAST[1] = RC.CH[1];
		RC.CH_LAST[2] = RC.CH[2];
		RC.CH_LAST[3] = RC.CH[3];
		
		//右摇杆横向  范围+-660
		RC.CH[0] = my_deathzoom(RC_PPM_CH[1], 5);
		//右摇杆纵向   范围+-660
		RC.CH[1] = my_deathzoom(RC_PPM_CH[3], 5);
		//左摇杆横向   范围+-660
		RC.CH[2] = my_deathzoom(RC_PPM_CH[0], 5);
		//左摇杆纵向   范围+-660
		RC.CH[3] = RC_PPM_CH[2];
	
	  RC.CH[4] = RC_PPM_CH[4];
		RC.CH[5] = RC_PPM_CH[6];
		
		RC.CH_DIF[0] = MIN((float)(RC.CH[0] - RC.CH_LAST[0])/T ,1000);
		RC.CH_DIF[1] = MIN((float)(RC.CH[1] - RC.CH_LAST[1])/T ,1000);
		RC.CH_DIF[2] = MIN((float)(RC.CH[2] - RC.CH_LAST[2])/T ,1000);
		RC.CH_DIF[3] = MIN((float)(RC.CH[3] - RC.CH_LAST[3])/T ,1000);
}
*/