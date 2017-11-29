#ifndef __LED_H__
#define __LED_H__

#include "board.h"

#define  LED_GREEN_ON      LED_PORT->BSRRH = GREEN_LED_Pin
#define  LED_GREEN_OFF     LED_PORT->BSRRL = GREEN_LED_Pin
#define  LED_GREEN_TOGGLE  LED_PORT->ODR ^= GREEN_LED_Pin

#define  LED_RED_ON        LED_PORT->BSRRH = RED_LED_Pin
#define  LED_RED_OFF       LED_PORT->BSRRL = RED_LED_Pin
#define  LED_RED_TOGGLE    LED_PORT->ODR ^= RED_LED_Pin

#define  LED_BLUE_ON        LED_PORT->BSRRH = BLUE_LED_Pin
#define  LED_BLUE_OFF       LED_PORT->BSRRL = BLUE_LED_Pin
#define  LED_BLUE_TOGGLE    LED_PORT->ODR ^= BLUE_LED_Pin

#define  OUT_LED_RED_ON        OUT_LED_PORT->BSRRH = OUT_RED_Pin
#define  OUT_LED_RED_OFF       OUT_LED_PORT->BSRRL = OUT_RED_Pin
#define  OUT_LED_RED_TOGGLE    OUT_LED_PORT->ODR ^= OUT_RED_Pin

#define  OUT_LED_GREEN_ON        OUT_LED_PORT->BSRRH = OUT_GREEN_Pin
#define  OUT_LED_GREEN_OFF       OUT_LED_PORT->BSRRL = OUT_GREEN_Pin
#define  OUT_LED_GREEN_TOGGLE    OUT_LED_PORT->ODR ^= OUT_GREEN_Pin

enum  {
				LED_GREEN,
				LED_RED,
				LED_BLUE,
				OUT_LED_RED,
				OUT_LED_GREEN
			};

void Led_Init(void);
void Led_Flash(float T, u8 led_name, float cycle_ms, float duty);
void Led_Task(float T);

#endif
