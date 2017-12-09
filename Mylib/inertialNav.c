#include "inertialNav.h"

struct _z_ef z_ef;

extern float vx, vy, vz;//(r系到b系的第三列)

int32_t baroAlt_buff[15];

void Update_Velocities_Positions_Z(float T)
{
		float baroAlt_dif;
	  static u16 run_times = 0;
	  static float accz_correction_i=0;
	
/***************Z方向速度和位置 START***************/			

		/*气压计放入数组*/
		Push_baroAlt();
		/*气压计微分*/
		baroAlt_dif = (ms5611.baroAlt - baroAlt_buff[14])/(14*T);
		/*气压微分低通滤波*/		
		baroAlt_dif = LPF2pApply_2(baroAlt_dif);
		/*加速度校准量积分*/
		accz_correction_i += (baroAlt_dif - z_ef.velz.base)*0.1f*T;
		/*加速度校准量积分限幅*/
		accz_correction_i = LIMIT(accz_correction_i,-30,30);
		/*加速度校准量*/
		z_ef.accz.correction = (baroAlt_dif - z_ef.velz.base)*0.2f + accz_correction_i;
		/*速度校准量在[-1m/s,1/s]*/
		z_ef.velz.correction = LIMIT(z_ef.velz.correction,-100,100);
		/*得到地球坐标系（earth frame）下的竖直加速度*/    /*竖直方向加速度状态*/
//		z_ef.accz.base = (sensor.acc.filter.x*vx + sensor.acc.filter.y*vy + sensor.acc.filter.z*vz)*980.0f/4096.0f-INTERTIALNAV_GRAVITY;
		z_ef.accz.base = 100.0f*(phone.acc[0]*vx+phone.acc[1]*vy+phone.acc[2]*vz) - INTERTIALNAV_GRAVITY;
				/*速度增量*/
	  z_ef.velz.increase = (z_ef.accz.base+z_ef.accz.correction) * T;
		/*高度更新 x(k+1)=v(k)*t+0.5*a*t^2  */    /*竖直方向高度状态*/
	  z_ef.posz.base += (z_ef.velz.base + z_ef.velz.correction + z_ef.velz.increase * 0.5f) * T;
		/*速度更新 v(k+1)=v(k)+a*t  */    /*竖直方向速度状态*/
		z_ef.velz.base += z_ef.velz.increase;
/***************Z方向速度和位置 END***************/
}

void Push_baroAlt(void)
{
		u8 i;
	  for(i=14;i>0;i--)
			baroAlt_buff[i] = baroAlt_buff[i-1]; 
		baroAlt_buff[0] = ms5611.baroAlt;
}
