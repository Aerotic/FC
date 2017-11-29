#ifndef _HEIGHT_CONTROL_H
#define	_HEIGHT_CONTROL_H

#include "board.h"

#define filter_K  0.70f

struct _height_con{
								float exp;
								float err;
								float err_last;
								float err_dif;
								float err_inc;
								float inc_max;
								float out_p;
								float out_i;
								float out_d;
								float out;
	              float kp;
	              float ki;
	              float kd;
				          };

struct _height_control{
										struct _height_con acc;
										struct _height_con vel;
										struct _height_con pos;
											};

extern struct _height_control hgt_ctrl;

void Height_Acceleration_Control(float T);
void Height_Velocity_Control(float T);
void Height_Position_Control(float T);

#endif
