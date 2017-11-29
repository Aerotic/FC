#include "parameter.h"

struct _parameter parameter;

void Get_parameter(void)
{
//姿态外环参数
		parameter.outer.pit.kp = 0.8;//0.5
		parameter.outer.pit.ki = 0.11;
		parameter.outer.pit.kd = 2.0;//2.0

		parameter.outer.rol.kp = 0.8;//0.5
		parameter.outer.rol.ki = 0.11;
		parameter.outer.rol.kd = 2.0;//2.0

	  parameter.outer.yaw.kp = 1.0;
		parameter.outer.yaw.ki = 0.0;
		parameter.outer.yaw.kd = 0.0;
	
//姿态内环参数	
	  parameter.inner.pit.kp = 0.40;
	  parameter.inner.pit.ki = 0.0;
		parameter.inner.pit.kd = 0.02;

		parameter.inner.rol.kp = 0.40;
		parameter.inner.rol.ki = 0.0;
		parameter.inner.rol.kd = 0.02;

	  parameter.inner.yaw.kp = 0.6;
		parameter.inner.yaw.ki = 0.0;
		parameter.inner.yaw.kd = 0.035;
		
		ctrl.inner.FB = 0.06;

//气压定高参数
/*加速度控制，P控制，单独控制*/
		hgt_ctrl.acc.kp = 0.35;

/*速度控制，P控制*/
		hgt_ctrl.vel.kp = 2.5;

/*位置控制，PI控制*/
		hgt_ctrl.pos.kp = 1.0;
		hgt_ctrl.pos.ki = 0.10;//0.10
		hgt_ctrl.pos.inc_max = 10.0;//运行时需要变化
		
//gps定点参数		
/*速度环，PD控制*/
		gpslevelcon.vel_x.kp = 0.07;//0.04		
		gpslevelcon.vel_y.kp = 0.07;//0.04
		
		gpslevelcon.vel_x.kd = 0.02;
		gpslevelcon.vel_y.kd = 0.02;

/*位置环，PI控制*/
		gpslevelcon.pos_x.kp = 0.3;//0.3
		gpslevelcon.pos_y.kp = 0.3;//0.3
		
		gpslevelcon.pos_x.ki = 0.20;//0.3
		gpslevelcon.pos_y.ki = 0.20;//0.3
}


u8 Param_Save(void)
{
	u8 act_page_num = 255;	//可以使用的页码
	uint32_t act_page_start = 0;	//该页起始地址
	uint16_t data_cnt = 0;
	
	act_page_num = GetActPage();
	if(act_page_num>(PAGE_NUM-2))
	{
		if(ClearDataFlash())
			act_page_num = 0;
		else
			return False;	//擦除失败
	}
	
	act_page_start = FLASH_USER_START_ADDR + (act_page_num * PAGE_BYTES);
	FLASH_Unlock();
	
	if(!WriteInt(act_page_start, data_cnt++, mag.max.x)) return False;	//写入失败
	if(!WriteInt(act_page_start, data_cnt++, mag.max.y)) return False;	//写入失败
	if(!WriteInt(act_page_start, data_cnt++, mag.max.z)) return False;	//写入失败
	if(!WriteInt(act_page_start, data_cnt++, mag.min.x)) return False;	//写入失败
	if(!WriteInt(act_page_start, data_cnt++, mag.min.y)) return False;	//写入失败
	if(!WriteInt(act_page_start, data_cnt++, mag.min.z)) return False;	//写入失败

	FLASH_Lock(); 

	return True;
}

u8 Param_Read(void)
{
	u8 act_page_num = 255;	//可以使用的页码
	uint32_t act_page_start = 0;	//该页起始地址
	uint16_t data_cnt = 0;
	
	act_page_num = GetActPage();
	if(act_page_num==0)
		return False;
	else
		act_page_num -= 1;
	act_page_start = FLASH_USER_START_ADDR + (act_page_num * PAGE_BYTES);
	
	mag.max.x = ReadInt(act_page_start, data_cnt++);
	mag.max.y = ReadInt(act_page_start, data_cnt++);
	mag.max.z = ReadInt(act_page_start, data_cnt++);
	mag.min.x = ReadInt(act_page_start, data_cnt++);
	mag.min.y = ReadInt(act_page_start, data_cnt++);
	mag.min.z = ReadInt(act_page_start, data_cnt++);

	return True;
}
