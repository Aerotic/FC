#ifndef _CONTROL_H
#define	_CONTROL_H

#include "board.h"

#define MAX_CTRL_ANGLE        25.0f       //最大姿态角度
#define ANGLE_TO_MAX_AS 		  30.0f				//角度误差N时，期望角速度达到最大（可以通过外环的P值调整）
#define MAX_CTRL_ASPEED 	 	  220.0f			//ROL,PIT允许的最大控制角速度
#define MAX_CTRL_YAW_SPEED 	  150.0f			//YAW允许的最大控制角速度


#define CTRL_OUTER_INC_LIMIT 	0.5f *MAX_CTRL_ANGLE		//外环积分幅度
#define CTRL_INNER_INC_LIMIT  0.5f *MAX_CTRL_ASPEED

#define READY_THR             100         //怠速油门10%
#define MAX_THR               1000         //最大油门80%
#define MAX_INNER_OUT         200

struct _terms{
							float x;
							float y;
							float z;
             };

struct _attitude_con{
	          struct _terms exp;
						struct _terms err;
	          struct _terms err_weight;
						struct _terms err_last;
	          struct _terms err_dif;
						struct _terms err_dif_f;
	          struct _terms err_inc;
	          struct _terms err_p;
						struct _terms err_i;
						struct _terms err_d;
	          struct _terms eliminate_i;
						struct _terms out;
		        float  FB;
				   };

struct _control{
                struct _attitude_con inner;
	              struct _attitude_con outer;
               };


struct _throttle{
								 float value;
								 float lpf;
	               float weight;
	               float comp;
								};


extern struct _control ctrl;
extern struct _throttle thr;

void Control_Outer(float T);
void Control_Inner(float T);
void Thr_Control(float T);

#endif
