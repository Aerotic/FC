#include "schedule.h"
#define RadToDeg 57.295779
struct _schedule schedule;

int64_t loop_5hz;
void Loop_1000Hz(void)//1msִ��һ��
{
	
}
void Rad2Deg()
{
	phone.gyro_dps[0]=RadToDeg*phone.gyro_rps[0];
	phone.gyro_dps[1]=RadToDeg*phone.gyro_rps[1];
	phone.gyro_dps[2]=RadToDeg*phone.gyro_rps[2];
}

void Loop_500Hz(void)	//2msִ��һ��
{	
	float loop_time_500hz;
	loop_time_500hz = Get_Cycle_T(0);     /*��ȡ2ms׼ȷʱ��*/
	//Mpu6050_Read();                       /*��ȡmpu6050����*/
	//Mpu6050_Data_Prepare();               /*Ϊ��Ԫ��������׼��*/
	Control_Inner(loop_time_500hz);       /*��̬�ڻ�����*/
	Motor_Speed_Update();                 /*���µ��ת��*/
	
#ifdef SONAR_ENABLE
	HCSR04_TRIG_TOGGLE;                   /*������Trig����250hz�ķ���*/
#endif
}

void Loop_200Hz(void)	//5msִ��һ��
{
	float loop_time_200hz;
	loop_time_200hz = Get_Cycle_T(1);     									/*��ȡ5ms׼ȷʱ��*/

	Control_Outer(loop_time_200hz);       									/*��̬�⻷����*/
//	Update_Velocities_Positions_Z(loop_time_200hz); 				/*����Z�����ٶȺ�λ��*/
}

void Loop_100Hz(void)	//10msִ��һ��
{
	float loop_time_100hz;
	loop_time_100hz = Get_Cycle_T(2);     				/*��ȡ10ms׼ȷʱ��*/
	
#ifdef PPM_RC
	Get_PPM_Value(loop_time_100hz);       				/*ʹ��PPM���ջ�*/
#endif
	
//	MS5611_Update();															/*��ѹ�Ƹ߶ȸ��� cm*/
	
#ifdef SONAR
	Hcsr04_Filter();                     				  /*�������߶��˲� m*/
#endif
	
	//Get_Direction(loop_time_100hz);       				/*��ȡƫ���Ƕȣ�������*/
	
// 	Height_Acceleration_Control(loop_time_100hz); /*���ٶ����Ų�����ʵʱ���У���������*/
			
//	Update_GPS_states(loop_time_100hz);           /*����GPS״̬�����ٶȡ��ٶȡ�λ��*/
	
	RC_Check(loop_time_100hz,200);      					/*ң����ʧ�ؼ�飬��200ms��û���յ�������Ϊʧ��*/
	
//	Led_Task(loop_time_100hz);                    /*LED����*/
}

void Loop_50Hz(void)	//20msִ��һ��
{
	float loop_time_50hz;
	loop_time_50hz = Get_Cycle_T(3);						/*��ȡ20ms׼ȷʱ��*/
	
//	Height_Velocity_Control(loop_time_50hz);		/*�߶��ٶȿ���*/
	//GPSlevel_Velocity_Control(loop_time_50hz);  /*GPSˮƽ�ٶȿ���*/
	
//	RECEIVE_RADIO_DATA();                       /*��ȡleader������������*/
//	printf("ch1 is %d\nch2 is %d\nch3 is %d\nch4is %d\n",RC.CH[0],RC.CH[1],RC.CH[2],RC.CH[3]);
}

void Loop_20Hz(void)	//50msִ��һ��1
{
	float loop_time_20hz;
	loop_time_20hz = Get_Cycle_T(4);            /*��ȡ50ms��׼ȷʱ��*/
	
	Height_Position_Control(loop_time_20hz);    /*�߶�λ�ÿ���*/
	//GPSlevel_Position_Control(loop_time_20hz);  /*GPSˮƽλ�ÿ���*/
	static u8 timer_50ms = 0;//��¼50ms����
	if(++timer_50ms > 10)
	 {
		  timer_50ms = 0;
			LED_GREEN_TOGGLE;   //�����ƣ�1s��˸1��
	 }
 }
void Loop_5Hz(void)
{
	//ͨ�����ڴ�ӡһЩ��Ϣ

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
