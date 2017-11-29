#include "led.h"

void Led_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
    
	RCC_AHB1PeriphClockCmd(RCC_LED , ENABLE );
	GPIO_InitStructure.GPIO_Pin = RED_LED_Pin | GREEN_LED_Pin | BLUE_LED_Pin ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(LED_PORT,&GPIO_InitStructure);
	
//	RCC_AHB1PeriphClockCmd(RCC_OUT_LED , ENABLE );
//	GPIO_InitStructure.GPIO_Pin = OUT_RED_Pin|OUT_GREEN_Pin;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
//	GPIO_Init(OUT_LED_PORT,&GPIO_InitStructure);
    
  LED_GREEN_OFF;
  LED_RED_ON;
	LED_BLUE_OFF;
	
//	OUT_LED_RED_OFF;
//	OUT_LED_GREEN_OFF;
}

void Led_Flash(float T, u8 led_name, float cycle_ms, float duty)
{
//  static uint16_t timer = 0;
//	if((++timer)*T*1000 > cycle_ms) timer = 0;
//	if(timer*T*1000 < cycle_ms*duty)
//	{
//     switch(led_name)
//			{
//				case OUT_LED_RED:OUT_LED_RED_ON;break;
//				case OUT_LED_GREEN:OUT_LED_GREEN_ON;break;
//				default:break;
//			}
//	}
//	else
//	{
//     switch(led_name)
//			{
//				case OUT_LED_RED:OUT_LED_RED_OFF;break;
//				case OUT_LED_GREEN:OUT_LED_GREEN_OFF;break;
//				default:break;
//			}
//	}
}

void Led_Task(float T)
{
//	if(RC.OutofControl)
//		Led_Flash(T, OUT_LED_RED, 2000, 0.5);
//	else
//		Led_Flash(T, OUT_LED_RED, 2000, 0.0);
}
