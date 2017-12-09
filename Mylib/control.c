#include "control.h"
struct _control ctrl;
struct _throttle thr;

/*
   name:void Control_Outer(float T)
   function:姿态外环控制
*/
void Control_Outer(float T)
{
	if(thr.value>=240)
	ctrl.outer.exp.z += -RC.CH[2]*0.0006f;
	if(ctrl.outer.exp.z>180) ctrl.outer.exp.z-=360;
	if(ctrl.outer.exp.z<-180) ctrl.outer.exp.z+=360;
	

		ctrl.outer.exp.x = RC.CH[0]*MAX_CTRL_ANGLE/660;
		ctrl.outer.exp.y = RC.CH[1]*MAX_CTRL_ANGLE/660;
  /* 得到角度误差 */
	ctrl.outer.err.x = ctrl.outer.exp.x - angle.roll ;
	ctrl.outer.err.y = ctrl.outer.exp.y - angle.pitch ;
	ctrl.outer.err.z = ctrl.outer.exp.z - angle.yaw ;
	ctrl.outer.err.z = To_180_degrees(ctrl.outer.err.z);
	/* 计算角度误差权重 */
	ctrl.outer.err_weight.x = ABS(ctrl.outer.err.x)/ANGLE_TO_MAX_AS;
	ctrl.outer.err_weight.y = ABS(ctrl.outer.err.y)/ANGLE_TO_MAX_AS;
	ctrl.outer.err_weight.z = ABS(ctrl.outer.err.z)/ANGLE_TO_MAX_AS;
	/* 角度误差微分（跟随误差曲线变化）*/
	ctrl.outer.err_dif.x = 10 *parameter.outer.rol.kd *(- angle.roll  - ctrl.outer.err_last.x + RC.CH_DIF[0]*T*MAX_CTRL_ANGLE/600) *( 0.005f/T ) *( 0.65f + 0.35f *ctrl.outer.err_weight.x );
	ctrl.outer.err_dif.y = 10 *parameter.outer.pit.kd *(- angle.pitch - ctrl.outer.err_last.y + RC.CH_DIF[1]*T*MAX_CTRL_ANGLE/600) *( 0.005f/T ) *( 0.65f + 0.35f *ctrl.outer.err_weight.y );
	ctrl.outer.err_dif.z = 10 *parameter.outer.yaw.kd *(ctrl.outer.err.z - ctrl.outer.err_last.z ) *( 0.005f/T ) *( 0.65f + 0.35f *ctrl.outer.err_weight.z );
	
  /* 角度误差积分 */
	ctrl.outer.err_inc.x += parameter.outer.rol.ki *ctrl.outer.err.x *T;
	ctrl.outer.err_inc.y += parameter.outer.pit.ki *ctrl.outer.err.y *T;
	ctrl.outer.err_inc.z += parameter.outer.yaw.ki *ctrl.outer.err.z *T;
	/* 角度误差积分分离 */
	ctrl.outer.eliminate_i.x = thr.weight *CTRL_OUTER_INC_LIMIT;
	ctrl.outer.eliminate_i.y = thr.weight *CTRL_OUTER_INC_LIMIT;
	ctrl.outer.eliminate_i.z = thr.weight *CTRL_OUTER_INC_LIMIT;
	/* 角度误差积分限幅 */
	ctrl.outer.err_inc.x = LIMIT( ctrl.outer.err_inc.x, -ctrl.outer.eliminate_i.x ,ctrl.outer.eliminate_i.x );
	ctrl.outer.err_inc.y = LIMIT( ctrl.outer.err_inc.y, -ctrl.outer.eliminate_i.y ,ctrl.outer.eliminate_i.y );
	ctrl.outer.err_inc.z = LIMIT( ctrl.outer.err_inc.z, -ctrl.outer.eliminate_i.z ,ctrl.outer.eliminate_i.z );
	/* 对用于计算比例项输出的角度误差限幅 */
	ctrl.outer.err.x = LIMIT( ctrl.outer.err.x, -90, 90 );
	ctrl.outer.err.y = LIMIT( ctrl.outer.err.y, -90, 90 );
	ctrl.outer.err.z = LIMIT( ctrl.outer.err.z, -90, 90 );
	/* 角度PID输出 */
	ctrl.outer.out.x = parameter.outer.rol.kp *( ctrl.outer.err.x + ctrl.outer.err_dif.x + ctrl.outer.err_inc.x );
	ctrl.outer.out.y = parameter.outer.pit.kp *( ctrl.outer.err.y + ctrl.outer.err_dif.y + ctrl.outer.err_inc.y );
	ctrl.outer.out.z = parameter.outer.yaw.kp *( ctrl.outer.err.z + ctrl.outer.err_dif.z + ctrl.outer.err_inc.z );
	/* 记录历史数据 */	
	ctrl.outer.err_last.x = - angle.roll;
	ctrl.outer.err_last.y = - angle.pitch;
	ctrl.outer.err_last.z = - angle.yaw;
}

/*
   name:void Control_Inner(float T)
   function:姿态内环控制
*/
void Control_Inner(float T)
{
	/* 给期望（目标）角速度 */
	ctrl.inner.exp.x = MAX_CTRL_ASPEED *(ctrl.outer.out.x/ANGLE_TO_MAX_AS);
	ctrl.inner.exp.y = MAX_CTRL_ASPEED *(ctrl.outer.out.y/ANGLE_TO_MAX_AS);
	ctrl.inner.exp.z = MAX_CTRL_ASPEED *(ctrl.outer.out.z/ANGLE_TO_MAX_AS);
	
	/* 期望角速度限幅 */
	ctrl.inner.exp.x = LIMIT(ctrl.inner.exp.x, -MAX_CTRL_ASPEED,MAX_CTRL_ASPEED );
	ctrl.inner.exp.y = LIMIT(ctrl.inner.exp.y, -MAX_CTRL_ASPEED,MAX_CTRL_ASPEED );
	ctrl.inner.exp.z = LIMIT(ctrl.inner.exp.z, -MAX_CTRL_ASPEED,MAX_CTRL_ASPEED );
	/* 角速度误差 */
	ctrl.inner.err.x =  ctrl.inner.exp.x - phone.gyro_dps[0] ;
	ctrl.inner.err.y =  ctrl.inner.exp.y - phone.gyro_dps[1] ;
	ctrl.inner.err.z =  ctrl.inner.exp.z - phone.gyro_dps[2] ;
	/* 角速度误差权重 */
	ctrl.inner.err_weight.x = ABS(ctrl.inner.err.x)/MAX_CTRL_ASPEED;
	ctrl.inner.err_weight.y = ABS(ctrl.inner.err.y)/MAX_CTRL_ASPEED;
	ctrl.inner.err_weight.z = ABS(ctrl.inner.err.z)/MAX_CTRL_YAW_SPEED;
	/* 角速度微分 */
	ctrl.inner.err_dif.x = -parameter.inner.rol.kd * ( phone.gyro_dps[0] - ctrl.inner.err_last.x)/T;
	ctrl.inner.err_dif.y = -parameter.inner.pit.kd * ( phone.gyro_dps[1] - ctrl.inner.err_last.y)/T;
	ctrl.inner.err_dif.z = -parameter.inner.yaw.kd * ( phone.gyro_dps[2] - ctrl.inner.err_last.z)/T;
	/* 角速度误差积分 */
	ctrl.inner.err_inc.x += parameter.inner.rol.ki *(ctrl.inner.err.x - ctrl.inner.err_dif.x) *T;
	ctrl.inner.err_inc.y += parameter.inner.pit.ki *(ctrl.inner.err.y - ctrl.inner.err_dif.y) *T;
	ctrl.inner.err_inc.z += parameter.inner.yaw.ki *(ctrl.inner.err.z - ctrl.inner.err_dif.z) *T;
	/* 角速度误差积分分离 */
	ctrl.inner.eliminate_i.x = thr.weight *CTRL_INNER_INC_LIMIT ;
	ctrl.inner.eliminate_i.y = thr.weight *CTRL_INNER_INC_LIMIT ;
	ctrl.inner.eliminate_i.z = thr.weight *CTRL_INNER_INC_LIMIT ;
	/* 角速度误差积分限幅 */
	ctrl.inner.err_inc.x = LIMIT( ctrl.inner.err_inc.x, -ctrl.inner.eliminate_i.x,ctrl.inner.eliminate_i.x );
	ctrl.inner.err_inc.y = LIMIT( ctrl.inner.err_inc.y, -ctrl.inner.eliminate_i.y,ctrl.inner.eliminate_i.y );
	ctrl.inner.err_inc.z = LIMIT( ctrl.inner.err_inc.z, -ctrl.inner.eliminate_i.z,ctrl.inner.eliminate_i.z );
	/* 角速度PID输出 */
	ctrl.inner.out.x = 3 *( ctrl.inner.FB *LIMIT((0.45f + 0.55f*ctrl.inner.err_weight.x),0,1)*ctrl.outer.exp.x + ( 1 - ctrl.inner.FB ) *parameter.inner.rol.kp *( ctrl.inner.err.x + ctrl.inner.err_dif.x + ctrl.inner.err_inc.x ) );
										
	ctrl.inner.out.y = 3 *( ctrl.inner.FB *LIMIT((0.45f + 0.55f*ctrl.inner.err_weight.y),0,1)*ctrl.outer.exp.y + ( 1 - ctrl.inner.FB ) *parameter.inner.pit.kp *( ctrl.inner.err.y + ctrl.inner.err_dif.y + ctrl.inner.err_inc.y ) );
						
	ctrl.inner.out.z = 3 *( ctrl.inner.FB *LIMIT((0.45f + 0.55f*ctrl.inner.err_weight.z),0,1)*ctrl.outer.exp.z + ( 1 - ctrl.inner.FB ) *parameter.inner.yaw.kp *( ctrl.inner.err.z + ctrl.inner.err_dif.z + ctrl.inner.err_inc.z ) );
	
	/* 内环输出限幅 */
	ctrl.inner.out.x = LIMIT(ctrl.inner.out.x,-MAX_INNER_OUT,MAX_INNER_OUT);
	ctrl.inner.out.y = LIMIT(ctrl.inner.out.y,-MAX_INNER_OUT,MAX_INNER_OUT);
	ctrl.inner.out.z = LIMIT(ctrl.inner.out.z,-MAX_INNER_OUT,MAX_INNER_OUT);
	
	/* 记录历史数据 */
	ctrl.inner.err_last.x =  phone.gyro_dps[0] ;
	ctrl.inner.err_last.y =  phone.gyro_dps[1] ;
	ctrl.inner.err_last.z =  phone.gyro_dps[2] ;
	
	/* 油门控制 */
	Thr_Control(T);
}

/*
   name:void Thr_Control(float T)
   function:遥控器控制油门
*/
void Thr_Control(float T)
{
	/* 飞机已经解锁 */
	if(aircraft.unlock)
		{
			thr.value = 0.6061*RC.CH[3]+500;
			thr.value = LIMIT(thr.value, READY_THR, MAX_THR);
		}
		
  /* 飞机上锁油门为0 */
	else thr.value = 0;
	
	/* 油门低通滤波 */
	thr.lpf += 10 *3.14f *T *(thr.value/400.0f - thr.lpf);
		
	/* 油门权重，用于角度误差积分分离 */
	thr.weight = LIMIT(thr.lpf,0,1);    
}
