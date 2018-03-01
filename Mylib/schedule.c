#include "schedule.h"
struct _schedule schedule;

int64_t loop_5hz;
void Loop_1000Hz(void)//1ms执行一次 
{
	//LED_BLUE_ON;
}
void Rad2Deg()
{

}

void Loop_500Hz(void)	//2ms执行一次
{	
	float loop_time_500hz;
	loop_time_500hz = Get_Cycle_T(0);     /*获取2ms准确时间*/
//	
//	{
//		DMA_ClearFlag(DMA1_Stream1, DMA_FLAG_TCIF1);
//		
//	}
//	if(DMA_GetFlagStatus(DMA1_Stream1,DMA_FLAG_TCIF1))
//		DMA_ClearFlag(DMA1_Stream1, DMA_FLAG_TCIF1);
	
	//Control_Inner(loop_time_500hz);       /*姿态内环控制*/
			
	//Motor_Speed_Update();                 /*更新电机转速*/
		
}

void Loop_200Hz(void)	//5ms执行一次
{
		float loop_time_200hz;
//			loop_time_200hz = Get_Cycle_T(1);
//			/*四元数姿态解算*/
//			Control_Outer(loop_time_200hz);       									/*姿态外环控制*/
//			Update_Velocities_Positions_Z(loop_time_200hz); 				/*更新Z方向速度和位置*/
}

void Loop_100Hz(void)	//10ms执行一次
{
	float loop_time_100hz;
	loop_time_100hz = Get_Cycle_T(2);     				/*获取10ms准确时间*/
//	MS5611_Update();
//	
// 	Height_Acceleration_Control(loop_time_100hz); /*加速度油门补偿，实时进行，增大阻尼*/
			

	
	RC_Check(loop_time_100hz,200);      					/*遥控器失控检查，在200ms内没有收到数据认为失控*/
	

}

void Loop_50Hz(void)	//20ms执行一次
{
//	float loop_time_50hz;
//	loop_time_50hz = Get_Cycle_T(3);						/*获取20ms准确时间*/
//	
//	Height_Velocity_Control(loop_time_50hz);		/*高度速度控制*/
}

void Loop_20Hz(void)	//50ms执行一次1
{
	float loop_time_20hz;
	loop_time_20hz = Get_Cycle_T(4);            /*获取50ms的准确时间*/
	
//	Height_Position_Control(loop_time_20hz);    /*高度位置控制*/
	static u8 timer_50ms = 0;//记录50ms次数
	if(++timer_50ms > 10)
	 {
		  timer_50ms = 0;
		 
			LED_RED_TOGGLE;   //呼吸灯，1s闪烁1次
	 }
 }
void Loop_5Hz(void)
{

	
}

void Loop(void)
{
	if(schedule.cnt_1ms >= 1)
	{
		Loop_1000Hz();	
		schedule.cnt_1ms = 0;
	}
	if(schedule.cnt_2ms >= 2)
	{
		Loop_500Hz();
		schedule.cnt_2ms = 0;
	}
	if(schedule.cnt_5ms >= 5)
	{
		Loop_200Hz();
		schedule.cnt_5ms = 0;
	}
	if(schedule.cnt_10ms >= 10)
	{
		Loop_100Hz();
		schedule.cnt_10ms = 0;
	}
	if(schedule.cnt_20ms >= 20)	
	{
		Loop_50Hz();
		schedule.cnt_20ms = 0;
	}
	if(schedule.cnt_50ms >= 50)
	{
		Loop_20Hz();
		schedule.cnt_50ms = 0;
	}
	
	
	///////////////////////////////////////////
	if(loop_5hz >= 1000)
	{
		Loop_5Hz();
		loop_5hz=0;
	}
}
