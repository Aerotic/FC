#ifndef _PWM_OUT_H
#define _PWM_OUT_H
#include "board.h"

#define MAX_MOTOR_PWM  8000
#define MIN_MOTOR_PWM  4000
#define STAR_MOTOR_PWM 1

struct _speed{
             float motor1;
						 float motor2;
						 float motor3;
						 float motor4;
						 };

struct _aircraft{
                u8 unlock;
								u8 lockchange;
								u8 lockchange_last;
	              u8 init_ok;
                };

extern struct _speed speed;
extern struct _aircraft aircraft;

void TIM3_PWM_Init(uint16_t freq);
void AndroidRPM(void);
void Motor_Speed_Update(void);

#endif
