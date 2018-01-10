#ifndef __BOARD_H__
#define __BOARD_H__

#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"

//#define PPM_RC          //PPM 接收机
#define SONAR_ENABLE		//声纳
#define ESC_CORRECT     //电调校准

/***************LED GPIO定义******************/
#define  RCC_LED           RCC_AHB1Periph_GPIOC
#define  LED_PORT          GPIOC
#define  RED_LED_Pin       GPIO_Pin_5 
#define  GREEN_LED_Pin     GPIO_Pin_4
#define  BLUE_LED_Pin      GPIO_Pin_12

#define  RCC_OUT_LED       RCC_AHB1Periph_GPIOB
#define  OUT_LED_PORT      GPIOB
#define  OUT_RED_Pin			 GPIO_Pin_14
#define  OUT_GREEN_Pin		 GPIO_Pin_5

/***************HCSR04 GPIO定义******************/
#define  RCC_HCSR04           			 	RCC_AHB1Periph_GPIOC
#define  HCSR04_PORT          				GPIOC
#define  TRIG_HCSR04_Pin      			 	GPIO_Pin_3 
#define  ECHO_HCSR04_Pin      			 	GPIO_Pin_4
#define  EXTI_HCSR04_LINE     			 	EXTI_Line4
#define  EXTI_HCSR04_CHANNEL  			  EXTI4_IRQn;

/*************BUZZER GPIO定义****************/
#define RCC_BUZZER	  RCC_AHB1Periph_GPIOB
#define BUZZER_PORT   GPIOB
#define BUZZER_Pin    GPIO_Pin_15

/***************I2C GPIO定义******************/
#define RCC_I2C	      RCC_AHB1Periph_GPIOB
#define I2C_PORT      GPIOB
#define I2C_Pin_SCL   GPIO_Pin_0
#define I2C_Pin_SDA   GPIO_Pin_1

/***************硬件中断分组******************/
#define NVIC_GROUP   NVIC_PriorityGroup_3

#include "usart1.h"
#include "android.h"
#include "dbus.h"

#include "softiic.h"
#include "mpu6050.h"
#include "hmc5883.h"
#include "ms5611.h"

#include "led.h"
#include "schedule.h"
#include "height_control.h"
#include "time.h"
#include "control.h"
#include "math.h"
#include "mymath.h"
#include "parameter.h"
#include "imu.h"
#include "data_send.h"
#include "buzzer.h"
#include "pwm_out.h"
#include "pwm_in.h"
#include "filter.h"
#include "stdint.h"
#include "hcsr04.h"
#include "uart5.h"
#include "gps.h"
#include "inertialNav.h"
#include "spi.h"
#include "24l01.h"
#include "flash.h"

void SysTick_Configuration(void);
uint32_t GetSysTime_us(void);
void DelayUs(uint32_t us);
void DelayMs(uint32_t ms);
void FlightController_board_Init(void);

extern volatile uint32_t sysTickUptime;

#endif /* __BOARD_H__ */

