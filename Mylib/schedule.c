#include "schedule.h"
#define RadToDeg 57.295779
struct _schedule schedule;

int64_t loop_5hz;
void Loop_1000Hz(void)//1ms执行一次
{
	
}
void Rad2Deg()
{
	phone.gyro_dps[0]=RadToDeg*phone.gyro_rps[0];
	phone.gyro_dps[1]=RadToDeg*phone.gyro_rps[1];
	phone.gyro_dps[2]=RadToDeg*phone.gyro_rps[2];
}

void Loop_500Hz(void)	//2ms执行一次
{	
	float loop_time_500hz;
	loop_time_500hz = Get_Cycle_T(0);     /*获取2ms准确时间*/
	//Mpu6050_Read();                       /*读取mpu6050数据*/
	//Mpu6050_Data_Prepare();               /*为四元数做数据准备*/
	Control_Inner(loop_time_500hz);       /*姿态内环控制*/
	Motor_Speed_Update();                 /*更新电机转速*/
	
#ifdef SONAR_ENABLE
	HCSR04_TRIG_TOGGLE;                   /*超声波Trig发出250hz的方波*/
#endif
}

void Loop_200Hz(void)	//5ms执行一次
{
	float loop_time_200hz;
	loop_time_200hz = Get_Cycle_T(1);     									/*获取5ms准确时间*/

	Control_Outer(loop_time_200hz);       									/*姿态外环控制*/
//	Update_Velocities_Positions_Z(loop_time_200hz); 				/*更新Z方向速度和位置*/
}

void Loop_100Hz(void)	//10ms执行一次
{
	float loop_time_100hz;
	loop_time_100hz = Get_Cycle_T(2);     				/*获取10ms准确时间*/
	
#ifdef PPM_RC
	Get_PPM_Value(loop_time_100hz);       				/*使用PPM接收机*/
#endif
	
//	MS5611_Update();															/*气压计高度更新 cm*/
	
#ifdef SONAR
	Hcsr04_Filter();                     				  /*超声波高度滤波 m*/
#endif
	
	//Get_Direction(loop_time_100hz);       				/*获取偏北角度，磁力计*/
	
// 	Height_Acceleration_Control(loop_time_100hz); /*加速度油门补偿，实时进行，增大阻尼*/
			
//	Update_GPS_states(loop_time_100hz);           /*更新GPS状态，加速度、速度、位置*/
	
	RC_Check(loop_time_100hz,200);      					/*遥控器失控检查，在200ms内没有收到数据认为失控*/
	
//	Led_Task(loop_time_100hz);                    /*LED任务*/
}

void Loop_50Hz(void)	//20ms执行一次
{
	float loop_time_50hz;
	loop_time_50hz = Get_Cycle_T(3);						/*获取20ms准确时间*/
	
//	Height_Velocity_Control(loop_time_50hz);		/*高度速度控制*/
	//GPSlevel_Velocity_Control(loop_time_50hz);  /*GPS水平速度控制*/
	
//	RECEIVE_RADIO_DATA();                       /*读取leader发送来的数据*/
//	printf("ch1 is %d\nch2 is %d\nch3 is %d\nch4is %d\n",RC.CH[0],RC.CH[1],RC.CH[2],RC.CH[3]);
}

void Loop_20Hz(void)	//50ms执行一次1
{
	float loop_time_20hz;
	loop_time_20hz = Get_Cycle_T(4);            /*获取50ms的准确时间*/
	
	Height_Position_Control(loop_time_20hz);    /*高度位置控制*/
	//GPSlevel_Position_Control(loop_time_20hz);  /*GPS水平位置控制*/
	static u8 timer_50ms = 0;//记录50ms次数
	if(++timer_50ms > 10)
	 {
		  timer_50ms = 0;
			LED_GREEN_TOGGLE;   //呼吸灯，1s闪烁1次
	 }
 }
void Loop_5Hz(void)
{
	//通过串口打印一些信息

	//LED_BLUE_TOGGLE;
	
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
