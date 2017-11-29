#ifndef __HCSR04_H_
#define __HCSR04_H_

#include "board.h"

#define HCSR04_TRIG_TOGGLE    HCSR04_PORT->ODR ^= TRIG_HCSR04_Pin
#define HCSR04_ECHO           HCSR04_PORT->IDR  & ECHO_HCSR04_Pin

struct _hcsr04
       {
        float start_time;
				float pulse_duration;
				float distance;
				float distance_filter;
       };
			 
extern struct _hcsr04 hcsr04;

void Hcsr04_Init(void);
void Hcsr04_Filter(void);

#endif
