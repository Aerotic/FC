#ifndef __PARAMETER_H
#define	__PARAMETER_H
#include "board.h"

struct _attitude_pid{   
									  float kp;
									  float ki;
									  float kd;
										};

struct _cascade{   
							 struct _attitude_pid pit;
							 struct _attitude_pid rol;
							 struct _attitude_pid yaw;
               };

struct _parameter{   
								 struct _cascade outer;
								 struct _cascade inner;
								 };

extern struct _parameter parameter;

void Get_parameter(void);
u8 Param_Save(void);
u8 Param_Read(void);
#endif
