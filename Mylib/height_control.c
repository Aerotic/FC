#include "height_control.h"

struct _height_control hgt_ctrl;

void Height_Acceleration_Control(float T)
{
		/*竖直加速度低通滤波*/
	  float accel_ef_lpf = LPF2pApply_1(z_ef.accz.base);
		/*加速度pid控制，此处作用只为增大阻尼*/
	  hgt_ctrl.acc.out_p = -accel_ef_lpf*hgt_ctrl.acc.kp;
	  hgt_ctrl.acc.out = hgt_ctrl.acc.out_p;
}

void Height_Velocity_Control(float T)
{
		hgt_ctrl.vel.err = hgt_ctrl.pos.out-z_ef.velz.base;
		hgt_ctrl.vel.err = LIMIT( hgt_ctrl.vel.err,-150.0f,150.0f);
		hgt_ctrl.vel.out_p = hgt_ctrl.vel.err*hgt_ctrl.vel.kp;
		hgt_ctrl.vel.out = hgt_ctrl.vel.out_p;
}

void Height_Position_Control(float T)
{
		/*定高模式发生变化*/
    if(RC.CH[4]!=RC.CH_LAST[4])
		{
       if(RC.CH[4]==1)  hgt_ctrl.pos.exp = z_ef.posz.base;//cm
    }
    /*气压定高*/		
		if(RC.CH[4]==1)
		{
			LED_BLUE_ON;
			if(thr.value>600)
			hgt_ctrl.pos.exp += (thr.value-600)*T*0.25f;
			if(thr.value<400)
			hgt_ctrl.pos.exp += (thr.value-400)*T*0.25f;	
			
			if(RC.CH[5]==1)
			hgt_ctrl.pos.exp = gps.leader_hight + 500;
			
			hgt_ctrl.pos.err = hgt_ctrl.pos.exp-z_ef.posz.base;//cm

			hgt_ctrl.pos.out_i += hgt_ctrl.pos.ki*hgt_ctrl.pos.err*T;

			hgt_ctrl.pos.inc_max = ABS(hgt_ctrl.pos.err);
			hgt_ctrl.pos.inc_max = LIMIT(hgt_ctrl.pos.inc_max,20,50);
			hgt_ctrl.pos.out_i = LIMIT( hgt_ctrl.pos.out_i,-hgt_ctrl.pos.inc_max,hgt_ctrl.pos.inc_max);

			hgt_ctrl.pos.out_p = hgt_ctrl.pos.err*hgt_ctrl.pos.kp;
			hgt_ctrl.pos.out = hgt_ctrl.pos.out_p + hgt_ctrl.pos.out_i;
		}
		/*姿态模式，保证速度不会太大*/
		if(RC.CH[4]==3||RC.CH[4]==0)//0 ppm接收机
		{
			LED_BLUE_OFF;
			hgt_ctrl.pos.out_i = 0;
			hgt_ctrl.pos.out = (thr.value-450)*0.5f;
			hgt_ctrl.pos.out = LIMIT( hgt_ctrl.pos.out,-250.0f,250.0f);
    }
		RC.CH_LAST[4]=RC.CH[4];
}
