#ifndef _IMU_H
#define	_IMU_H
#include "board.h"

#define IMU_INTEGRAL_LIM  ( 2.0f *ANGLE_TO_RAD )

#define RtA 	  57.324841f

struct _angle{
        float pitch;
				float roll;
        float yaw;};


extern struct _angle angle;

void IMUupdate(float half_T, float gx, float gy, float gz, float ax, float ay, float az);

#endif
