#include "imu.h"
struct _angle angle;

#define Kp 0.6f                           // proportional gain governs rate of convergence to accelerometer/magnetometer
#define Ki 0.1f                           // integral gain governs rate of convergence of gyroscope biases

float q0 = 1, q1 = 0, q2 = 0, q3 = 0;     // quaternion elements representing the estimated orientation
float exInt = 0, eyInt = 0, ezInt = 0;    // scaled integral error

float ux, uy, uz;//(r系到b系的第一列)
float wx, wy, wz;//(r系到b系的第二列)
float vx, vy, vz;//(r系到b系的第三列)

void IMUupdate(float half_T, float gx, float gy, float gz, float ax, float ay, float az)
{
  float norm;
  float ex, ey, ez;
		
	//acc数据归一化
  norm = my_sqrt(ax*ax + ay*ay + az*az);       
  ax = ax / norm;
  ay = ay / norm;
  az = az / norm;

  // estimated direction of gravity and flux (v and w)              估计重力方向和流量/变迁
  vx = 2*(q1*q3 - q0*q2);												//四元素中xyz的表示
  vy = 2*(q0*q1 + q2*q3);
  vz = 1 - 2*(q1*q1 + q2*q2);
	
  // error is sum of cross product between reference direction of fields and direction measured by sensors
  ex = (ay*vz - az*vy) ;                           					 //向量外积在相减得到差分就是误差
  ey = (az*vx - ax*vz) ;
  ez = (ax*vy - ay*vx) ;

  exInt = exInt + ex *Ki *2 *half_T;								  //对误差进行积分
  eyInt = eyInt + ey *Ki *2 *half_T;
  ezInt = ezInt + ez *Ki *2 *half_T;
	
  // 积分限幅
	exInt = LIMIT(exInt, - IMU_INTEGRAL_LIM ,IMU_INTEGRAL_LIM );
	exInt = LIMIT(exInt, - IMU_INTEGRAL_LIM ,IMU_INTEGRAL_LIM );
	exInt = LIMIT(exInt, - IMU_INTEGRAL_LIM ,IMU_INTEGRAL_LIM );
	
  // adjusted gyroscope measurements
  gx = gx + Kp *(ex + exInt);					   						
  gy = gy + Kp *(ey + eyInt);				   							
  gz = gz + Kp *(ez + ezInt);					   					  							
	
  // integrate quaternion rate and normalise						   //四元素的微分方程
  q0 = q0 + (-q1*gx - q2*gy - q3*gz) *half_T;
  q1 = q1 + ( q0*gx + q2*gz - q3*gy) *half_T;
  q2 = q2 + ( q0*gy - q1*gz + q3*gx) *half_T;
  q3 = q3 + ( q0*gz + q1*gy - q2*gx) *half_T;

  // normalise quaternion
  norm = my_sqrt(q0*q0 + q1*q1 + q2*q2 + q3*q3);
  q0 = q0 / norm;
  q1 = q1 / norm;
  q2 = q2 / norm;
  q3 = q3 / norm;

  angle.yaw = fast_atan2(2*q1*q2+2*q0*q3, -2*q2*q2-2*q3*q3+1) *57.3f;
  angle.roll = fast_atan2(2*q2*q3 + 2*q0*q1, -2*q1*q1 - 2*q2*q2 + 1) *57.3f;
  angle.pitch = asin(-2*q1*q3 + 2*q0*q2) *57.3f; 	
	
	ux = 1 - 2*(q2*q2 + q3*q3);
	uy = 2*(q1*q2 - q0*q3);
	uz = 2*(q1*q3 + q0*q2);
	
	wx = 2*(q1*q2 + q0*q3);
	wy = 1-2*(q1*q1 + q3*q3);
	wz = 2*(q2*q3 - q0*q1);
}
