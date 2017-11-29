#ifndef _PWM_IN_H_
#define _PWM_IN_H_

#include "board.h"

void PWM_IN_Init(void);
void TIM4_IRQHandler(void);
void TIM5_IRQHandler(void);
void Get_PPM_Value(float T); 

extern float RC_PPM_CH[8];
#endif
