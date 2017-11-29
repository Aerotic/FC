#ifndef __GPS_H
#define __GPS_H

#include "board.h"

#define GPS_BUF_LEN      2048
#define LATLON_TO_CM     11319500       //纬度（度）转厘米   PI*RADIUS_OF_EARTH/180  
#define FILTER_K1        0.2f

#define MAX_GPS_SPEED    250.0f

struct _gps 
{		
	double lat;			//纬度
	double lon;			//经度
	double homelat; //家纬度
	double homelon; //家经度
	double rellat;  //纬度相对坐标
	double rellon;  //经度相对坐标
	double leader_lat;//leader的纬度
	double leader_lon;//leader的经度
	double disx_cm_to_leader;//和leader的x距离
	double disy_cm_to_leader;//和leader的y距离
	double rellat_aim;//目标相对纬度
	double rellon_aim;//目标相对经度
	double speed;   //移动速率
	double azimuth; //移动方向
	float  latacc;  //纬度方向加速度
	float  lonacc;	//经度方向加速度
	float  latvel;  //纬度方向速度
	float  lonvel;  //经度方向速度
	float  leader_pitch;//leader俯仰
	float  leader_roll; //leader横滚
	float  leader_yaw;  //leader偏航
	float  leader_latvel;//leader纬度方向的速度
	float  leader_lonvel;//leader经度方向的速度
	float  leader_hight; //leader高度
	u8 homeisok;		//家位置确定				 
};
		
struct _GPSINFO
{
	u8 UtcTime[11]; 	//时间
	u8 Statue;   			//定位状态
	u8 Latitude[10];	//纬度
	u8 LatitudeNS; 		//纬度半球
	u8 Longitude[11];	//经度
	u8 LongitudeEW;		//经度半球
	u8 Speed[6];	    //地面速率
	u8 Azimuth[6];	  //航向
	u8 UtcData[7]; 		//日期  
	u8 Altitude[8];   //高度
};

struct _xy_efdata
			 {
				 double base;
				 double dis_cm;
				 double dif;
       };
			 
struct _xy_ef
			 {
				 struct _xy_efdata accx;
				 struct _xy_efdata accy;
				 struct _xy_efdata velx;
				 struct _xy_efdata vely;
         struct _xy_efdata posx;
				 struct _xy_efdata posy;
			 };
			 		 
struct _gps_control
			{
				float exp;
				float err;
				float out_p;
				float out_i;
				float out_d;
				float out;
				float kp;
				float ki;
				float kd;
				float inc_max;
				double rc;
			};

struct _gps_pid_level
      {
         struct _gps_control vel_x;
				 struct _gps_control vel_y;
				 struct _gps_control pos_x;
				 struct _gps_control pos_y;
				 float PITCH_OUT;
				 float ROLL_OUT;
      };
			
extern struct _gps_pid_level gpslevelcon;
extern struct _gps gps;
extern struct _GPSINFO GpsInfo;
extern struct _xy_ef xy_ef;			 
			 
extern u8 gps_rx_buffer[GPS_BUF_LEN];

u16 FindStr(u8 *str,u8 *ptr);
void GPSParse(void);
double LatToRad(void);
double LonToRad(void);
double GetSpeed(void);
double GetAzimuth(void);
void GPS_Read(void);
void Update_GPS_states(float T);
void Push_Pos_Dis(double x ,double y);
void Cal_Distance_to_Leader(void);
void Update_Leader_State(float T);			
void GPSlevel_Velocity_Control(float T);
void GPSlevel_Position_Control(float T);		
		

#endif
