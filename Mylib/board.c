#include "board.h"

//滴答定时器计数变量 ,49天后溢出
volatile uint32_t sysTickUptime=0;

#define TICK_PER_SECOND 1000 
#define TICK_US	(1000000/TICK_PER_SECOND)

void SysTick_Configuration(void)
{
	RCC_ClocksTypeDef  rcc_clocks;
	uint32_t         cnts;

	RCC_GetClocksFreq(&rcc_clocks);

	cnts = (uint32_t)rcc_clocks.HCLK_Frequency / TICK_PER_SECOND;//cnts=HCLK
	cnts = cnts / 8;//cnts=HCLK/8 

	SysTick_Config(cnts);
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);//HCLK/8  set freq divider    
}

uint32_t GetSysTime_us(void) 
{
	register uint32_t ms;
	u32 value;
	ms = sysTickUptime;
	value = ms * TICK_US + (SysTick->LOAD - SysTick->VAL) * TICK_US / SysTick->LOAD;
	return value;
}

void DelayUs(uint32_t us)
{
    uint32_t now = GetSysTime_us();
    while (GetSysTime_us() - now < us);
}

void DelayMs(uint32_t ms)
{
    while (ms--)
      DelayUs(1000);
}

void FlightController_board_Init(void)
{
		/*led初始化*/
		Led_Init();
	LED_BLUE_ON;
		/*中断分组*/
		NVIC_PriorityGroupConfig(NVIC_GROUP);
		/*滴答定时器配置*/
		SysTick_Configuration();
		/*读取参数*/
		Get_parameter();
		/*Dbus遥控器配置*/
		Dbus_Config();
		
		/*蜂鸣器初始化*/
		//Buzzer_Init();
		/*模拟IIC初始化*/
		I2C_Soft_Init();
		/*等待100ms*/
		DelayMs(100);
		/*mpu6050初始化*/
		Mpu6050_Init(1000,20);
		/*定时器3配置 产生pwm控制电机*/
		TIM3_PWM_Init(400);
		/*PPM接收机*/	
		//PWM_IN_Init();
		/*串口5初始化，接GPS*/	
		Uart5_Config();
		/*ms5611初始化*/
		//MS5611_Init();
		/*hmc5883初始化*/
	//	Hmc5883_Init();
		/*超声波初始化*/
		//Hcsr04_Init();
		/*时间初始化*/
		Cycle_Time_Init();
		/*读取陀螺仪静态输出*/
		Mpu6050_CalOffset_Gyro();
		/*读取加速度水平输出*/
		Mpu6050_CalOffset_Acc();
		/*校准磁力计*/
	  //Mag_Correct();
		/*读取地面气压*/
		MS5611_CalOffset();
		/*竖直方向加速度计偏差滤波*/
		LPF2pSetCutoffFreq_1(100, 10);
		/*气压微分低通滤波*/
		LPF2pSetCutoffFreq_2(200, 10);
		/*水平x方向加速度计偏差滤波*/
		LPF2pSetCutoffFreq_3(100, 10);
		/*水平y方向加速度计偏差滤波*/
		LPF2pSetCutoffFreq_4(100, 10);
		/*参考坐标系x方向加速度计偏差滤波*/
		LPF2pSetCutoffFreq_5(100, 10);
		/*参考坐标系y方向加速度计偏差滤波*/
		LPF2pSetCutoffFreq_6(100, 10);
		/*GPS lat速度滤波*/
		LPF2pSetCutoffFreq_7(100, 10);
		/*GPS lon速度滤波*/
		LPF2pSetCutoffFreq_8(100, 10);
		/*串口1初始化,数据推送*/
	  Usart1_Config();
// 		/*nrf24l01初始化*/
// 		NRF24L01_Init();
// 		/*检测nrf24l01*/		
// 		while(NRF24L01_Check());
// 		/*nrf24l01接收模式*/			
// 		NRF24L01_RX_Mode();
		/*指示灯*/
		LED_BLUE_OFF;
		/*飞机初始化完成*/
		aircraft.init_ok=1;
}

