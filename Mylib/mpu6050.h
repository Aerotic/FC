#ifndef _MPU6050_H
#define	_MPU6050_H

#include "board.h"

#define ANGLE_TO_RAD 0.01745329f

#define TO_ANGLE     0.061036f

#define MPU6050_FILTER_NUM   10

#define A_X    0
#define A_Y    1
#define A_Z    2
#define G_X    3
#define G_Y    4
#define G_Z    5																	

#define ITEMS  6

struct _float{
	      float x;
	 	    float y;
		    float z;
             };

struct _int16{
         int16_t x;
	       int16_t y;
	       int16_t z;
             };		

struct _trans{
       struct _int16 origin;      //原始值
			 struct _float offset_max;  //零偏值最大值
			 struct _float offset_min;  //零偏值最小值	
	     struct _float offset;      //零偏值 
		   struct _float calibration; //校准值
	     struct _float filter;      //滑动平均滤波值
	     struct _float dps;         //度每秒 
	     struct _float radps;       //弧度每秒
              };

struct _sensor{   
	   struct _trans acc;
	   struct _trans gyro;
              };

extern struct _sensor sensor;


//初始化6050
void Mpu6050_Init(uint16_t sample_rate, uint16_t lpf);
//读取加速度
void Mpu6050_Read_Acc_Data(void);
//读取角速度
void Mpu6050_Read_Gyro_Data(void);
//读取加速度和角速度数据
void Mpu6050_Read(void);
//加速度零偏矫正
void Mpu6050_CalOffset_Acc(void);
//陀螺仪零偏矫正
void Mpu6050_CalOffset_Gyro(void);
//mpu6050数据准备
void Mpu6050_Data_Prepare(void);


#endif
