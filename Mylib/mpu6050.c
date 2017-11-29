#include "mpu6050.h"

struct _sensor sensor;

u8 mpu6050_buffer[12];                    //接收数据缓存区

// MPU6050, 硬件I2c地址 0x68，模拟i2c地址0xD0
#define MPU6050_ADDRESS           0xD0	  // 0x68
#define DMP_MEM_START_ADDR        0x6E
#define DMP_MEM_R_W               0x6F

#define MPU_RA_XG_OFFS_TC         0x00    //[7] PWR_MODE, [6:1] XG_OFFS_TC, [0] OTP_BNK_VLD
#define MPU_RA_YG_OFFS_TC         0x01    //[7] PWR_MODE, [6:1] YG_OFFS_TC, [0] OTP_BNK_VLD
#define MPU_RA_ZG_OFFS_TC         0x02    //[7] PWR_MODE, [6:1] ZG_OFFS_TC, [0] OTP_BNK_VLD
#define MPU_RA_X_FINE_GAIN        0x03    //[7:0] X_FINE_GAIN
#define MPU_RA_Y_FINE_GAIN        0x04    //[7:0] Y_FINE_GAIN
#define MPU_RA_Z_FINE_GAIN        0x05    //[7:0] Z_FINE_GAIN
#define MPU_RA_XA_OFFS_H          0x06    //[15:0] XA_OFFS
#define MPU_RA_XA_OFFS_L_TC       0x07
#define MPU_RA_YA_OFFS_H          0x08    //[15:0] YA_OFFS
#define MPU_RA_YA_OFFS_L_TC       0x09
#define MPU_RA_ZA_OFFS_H          0x0A    //[15:0] ZA_OFFS
#define MPU_RA_ZA_OFFS_L_TC       0x0B
#define MPU_RA_PRODUCT_ID         0x0C    // Product ID Register
#define MPU_RA_XG_OFFS_USRH       0x13    //[15:0] XG_OFFS_USR
#define MPU_RA_XG_OFFS_USRL       0x14
#define MPU_RA_YG_OFFS_USRH       0x15    //[15:0] YG_OFFS_USR
#define MPU_RA_YG_OFFS_USRL       0x16
#define MPU_RA_ZG_OFFS_USRH       0x17    //[15:0] ZG_OFFS_USR
#define MPU_RA_ZG_OFFS_USRL       0x18
#define MPU_RA_SMPLRT_DIV         0x19
#define MPU_RA_CONFIG             0x1A
#define MPU_RA_GYRO_CONFIG        0x1B
#define MPU_RA_ACCEL_CONFIG       0x1C
#define MPU_RA_FF_THR             0x1D
#define MPU_RA_FF_DUR             0x1E
#define MPU_RA_MOT_THR            0x1F
#define MPU_RA_MOT_DUR            0x20
#define MPU_RA_ZRMOT_THR          0x21
#define MPU_RA_ZRMOT_DUR          0x22
#define MPU_RA_FIFO_EN            0x23
#define MPU_RA_I2C_MST_CTRL       0x24
#define MPU_RA_I2C_SLV0_ADDR      0x25
#define MPU_RA_I2C_SLV0_REG       0x26
#define MPU_RA_I2C_SLV0_CTRL      0x27
#define MPU_RA_I2C_SLV1_ADDR      0x28
#define MPU_RA_I2C_SLV1_REG       0x29
#define MPU_RA_I2C_SLV1_CTRL      0x2A
#define MPU_RA_I2C_SLV2_ADDR      0x2B
#define MPU_RA_I2C_SLV2_REG       0x2C
#define MPU_RA_I2C_SLV2_CTRL      0x2D
#define MPU_RA_I2C_SLV3_ADDR      0x2E
#define MPU_RA_I2C_SLV3_REG       0x2F
#define MPU_RA_I2C_SLV3_CTRL      0x30
#define MPU_RA_I2C_SLV4_ADDR      0x31
#define MPU_RA_I2C_SLV4_REG       0x32
#define MPU_RA_I2C_SLV4_DO        0x33
#define MPU_RA_I2C_SLV4_CTRL      0x34
#define MPU_RA_I2C_SLV4_DI        0x35
#define MPU_RA_I2C_MST_STATUS     0x36
#define MPU_RA_INT_PIN_CFG        0x37
#define MPU_RA_INT_ENABLE         0x38
#define MPU_RA_DMP_INT_STATUS     0x39
#define MPU_RA_INT_STATUS         0x3A
#define MPU_RA_ACCEL_XOUT_H       0x3B
#define MPU_RA_ACCEL_XOUT_L       0x3C
#define MPU_RA_ACCEL_YOUT_H       0x3D
#define MPU_RA_ACCEL_YOUT_L       0x3E
#define MPU_RA_ACCEL_ZOUT_H       0x3F
#define MPU_RA_ACCEL_ZOUT_L       0x40
#define MPU_RA_TEMP_OUT_H         0x41
#define MPU_RA_TEMP_OUT_L         0x42
#define MPU_RA_GYRO_XOUT_H        0x43
#define MPU_RA_GYRO_XOUT_L        0x44
#define MPU_RA_GYRO_YOUT_H        0x45
#define MPU_RA_GYRO_YOUT_L        0x46
#define MPU_RA_GYRO_ZOUT_H        0x47
#define MPU_RA_GYRO_ZOUT_L        0x48
#define MPU_RA_EXT_SENS_DATA_00   0x49
#define MPU_RA_MOT_DETECT_STATUS  0x61
#define MPU_RA_I2C_SLV0_DO        0x63
#define MPU_RA_I2C_SLV1_DO        0x64
#define MPU_RA_I2C_SLV2_DO        0x65
#define MPU_RA_I2C_SLV3_DO        0x66
#define MPU_RA_I2C_MST_DELAY_CTRL 0x67
#define MPU_RA_SIGNAL_PATH_RESET  0x68
#define MPU_RA_MOT_DETECT_CTRL    0x69
#define MPU_RA_USER_CTRL          0x6A
#define MPU_RA_PWR_MGMT_1         0x6B
#define MPU_RA_PWR_MGMT_2         0x6C
#define MPU_RA_BANK_SEL           0x6D
#define MPU_RA_MEM_START_ADDR     0x6E
#define MPU_RA_MEM_R_W            0x6F
#define MPU_RA_DMP_CFG_1          0x70
#define MPU_RA_DMP_CFG_2          0x71
#define MPU_RA_FIFO_COUNTH        0x72
#define MPU_RA_FIFO_COUNTL        0x73
#define MPU_RA_FIFO_R_W           0x74
#define MPU_RA_WHO_AM_I           0x75

#define MPU6050_SMPLRT_DIV        0       // 8000Hz

#define MPU6050_LPF_256HZ         0
#define MPU6050_LPF_188HZ         1
#define MPU6050_LPF_98HZ          2
#define MPU6050_LPF_42HZ          3
#define MPU6050_LPF_20HZ          4
#define MPU6050_LPF_10HZ          5
#define MPU6050_LPF_5HZ           6

#define MPU6050A_2mg              ((float)0.00006103f)  // 0.00006250 g/LSB
#define MPU6050A_4mg              ((float)0.00012207f)  // 0.00012500 g/LSB
#define MPU6050A_8mg              ((float)0.00024414f)  // 0.00025000 g/LSB

#define MPU6050G_s250dps          ((float)0.0076335f)  // 0.0087500 dps/LSB
#define MPU6050G_s500dps          ((float)0.0152671f)  // 0.0175000 dps/LSB
#define MPU6050G_s2000dps         ((float)0.0609756f)  // 0.0700000 dps/LSB


//MPU6050初始化，传入参数：采样率，低通滤波频率
void Mpu6050_Init(uint16_t sample_rate, uint16_t lpf)
{
	uint8_t default_filter;
	
	switch (lpf) {
	case 5:
			default_filter = MPU6050_LPF_5HZ;
			break;
	case 10:
			default_filter = MPU6050_LPF_10HZ;
			break;
	case 20:
			default_filter = MPU6050_LPF_20HZ;
			break;
	case 42:
			default_filter = MPU6050_LPF_42HZ;
			break;
	case 98:
			default_filter = MPU6050_LPF_98HZ;
			break;
	case 188:
			default_filter = MPU6050_LPF_188HZ;
			break;
	case 256:
			default_filter = MPU6050_LPF_256HZ;
			break;
	default:
			default_filter = MPU6050_LPF_98HZ;
			break;
	}	
	
	//设备复位
	I2C_Soft_Single_Write(MPU6050_ADDRESS,MPU_RA_PWR_MGMT_1, 0x80);	
	
	DelayMs(5);
	
	//陀螺仪采样率，0x00(1000Hz)   采样率 = 陀螺仪的输出率 / (1 + SMPLRT_DIV)
	I2C_Soft_Single_Write(MPU6050_ADDRESS,MPU_RA_SMPLRT_DIV, (1000/sample_rate - 1));	
	//设置设备时钟源，陀螺仪Z轴
	I2C_Soft_Single_Write(MPU6050_ADDRESS, MPU_RA_PWR_MGMT_1, 0x03);	
	//i2c旁路模式
	I2C_Soft_Single_Write(MPU6050_ADDRESS, MPU_RA_INT_PIN_CFG, 0 << 7 | 0 << 6 | 0 << 5 | 0 << 4 | 0 << 3 | 0 << 2 | 1 << 1 | 0 << 0); 
	//INT_PIN_CFG   -- INT_LEVEL_HIGH, INT_OPEN_DIS, LATCH_INT_DIS, INT_RD_CLEAR_DIS, FSYNC_INT_LEVEL_HIGH, FSYNC_INT_DIS, I2C_BYPASS_EN, CLOCK_DIS
	//低通滤波频率，0x03(42Hz)
	I2C_Soft_Single_Write(MPU6050_ADDRESS,MPU_RA_CONFIG, default_filter);	
	//陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)
	I2C_Soft_Single_Write(MPU6050_ADDRESS, MPU_RA_GYRO_CONFIG, 0x18); 
	//加速计自检、测量范围(不自检，+-8G)			
	I2C_Soft_Single_Write(MPU6050_ADDRESS,MPU_RA_ACCEL_CONFIG, 2 << 3);	
	
}

//读取加速度
void Mpu6050_Read_Acc_Data(void)
{
	mpu6050_buffer[0] = I2C_Soft_Single_Read(MPU6050_ADDRESS,MPU_RA_ACCEL_XOUT_L); 
	mpu6050_buffer[1] = I2C_Soft_Single_Read(MPU6050_ADDRESS,MPU_RA_ACCEL_XOUT_H);
	sensor.acc.origin.x = ((((int16_t)mpu6050_buffer[1]) << 8) | mpu6050_buffer[0]) ;  //加速度X轴

	mpu6050_buffer[2] = I2C_Soft_Single_Read(MPU6050_ADDRESS,MPU_RA_ACCEL_YOUT_L);
	mpu6050_buffer[3] = I2C_Soft_Single_Read(MPU6050_ADDRESS,MPU_RA_ACCEL_YOUT_H);
	sensor.acc.origin.y = ((((int16_t)mpu6050_buffer[3]) << 8) | mpu6050_buffer[2]) ;  //加速度Y轴

	mpu6050_buffer[4] = I2C_Soft_Single_Read(MPU6050_ADDRESS,MPU_RA_ACCEL_ZOUT_L);
	mpu6050_buffer[5] = I2C_Soft_Single_Read(MPU6050_ADDRESS,MPU_RA_ACCEL_ZOUT_H);
	sensor.acc.origin.z = ((((int16_t)mpu6050_buffer[5]) << 8) | mpu6050_buffer[4]) ;  //加速度Z轴
}

//读取角速度
void Mpu6050_Read_Gyro_Data(void)
{
	mpu6050_buffer[6] = I2C_Soft_Single_Read(MPU6050_ADDRESS,MPU_RA_GYRO_XOUT_L); 
	mpu6050_buffer[7] = I2C_Soft_Single_Read(MPU6050_ADDRESS,MPU_RA_GYRO_XOUT_H);
	sensor.gyro.origin.x = ((((int16_t)mpu6050_buffer[7]) << 8) | mpu6050_buffer[6]) ;	 //陀螺仪X轴

	mpu6050_buffer[8] = I2C_Soft_Single_Read(MPU6050_ADDRESS,MPU_RA_GYRO_YOUT_L);
	mpu6050_buffer[9] = I2C_Soft_Single_Read(MPU6050_ADDRESS,MPU_RA_GYRO_YOUT_H);
	sensor.gyro.origin.y = ((((int16_t)mpu6050_buffer[9]) << 8) | mpu6050_buffer[8]) ;	 //陀螺仪Y轴

	mpu6050_buffer[10] = I2C_Soft_Single_Read(MPU6050_ADDRESS,MPU_RA_GYRO_ZOUT_L);
	mpu6050_buffer[11] = I2C_Soft_Single_Read(MPU6050_ADDRESS,MPU_RA_GYRO_ZOUT_H);
	sensor.gyro.origin.z = ((((int16_t)mpu6050_buffer[11]) << 8) | mpu6050_buffer[10]) ; //陀螺仪Z轴		
}

void Mpu6050_Read(void)
{
	I2C_FastMode = 1;
	Mpu6050_Read_Acc_Data();
	Mpu6050_Read_Gyro_Data();
}

//加速度零偏矫正
void Mpu6050_CalOffset_Acc(void)
{
	sensor.acc.offset.x =100;//前-后+    -80
	sensor.acc.offset.y =-100;//左-右+    -95
	sensor.acc.offset.z =0;
}

//陀螺仪零偏矫正
void Mpu6050_CalOffset_Gyro(void)
{
		uint16_t cnt_g =1000;
		int32_t tempgx =0, tempgy =0, tempgz =0;

		sensor.gyro.offset_max.x = -32768;
		sensor.gyro.offset_max.y = -32768;
		sensor.gyro.offset_max.z = -32768;
		sensor.gyro.offset_min.x = 32767;
		sensor.gyro.offset_min.y = 32767;
		sensor.gyro.offset_min.z = 32767;

 	  while(cnt_g--)	 
	  {
			DelayMs(2);			
			Mpu6050_Read();
		  if(sensor.gyro.origin.x>sensor.gyro.offset_max.x) 
				sensor.gyro.offset_max.x = sensor.gyro.origin.x;
			if(sensor.gyro.origin.y>sensor.gyro.offset_max.y) 
				sensor.gyro.offset_max.y = sensor.gyro.origin.y;
			if(sensor.gyro.origin.z>sensor.gyro.offset_max.z) 
				sensor.gyro.offset_max.z = sensor.gyro.origin.z;
			
			if(sensor.gyro.origin.x<sensor.gyro.offset_min.x) 
				sensor.gyro.offset_min.x = sensor.gyro.origin.x;
			if(sensor.gyro.origin.y<sensor.gyro.offset_min.y) 
				sensor.gyro.offset_min.y = sensor.gyro.origin.y;
			if(sensor.gyro.origin.z<sensor.gyro.offset_min.z) 
				sensor.gyro.offset_min.z = sensor.gyro.origin.z;
			
				tempgx += sensor.gyro.origin.x;
				tempgy += sensor.gyro.origin.y;
				tempgz += sensor.gyro.origin.z;
    }
		 
		 //1000次数据有一个异常,重新校准
		 if(sensor.gyro.offset_max.x-sensor.gyro.offset_min.x>20||
			  sensor.gyro.offset_max.y-sensor.gyro.offset_min.y>20||
		    sensor.gyro.offset_max.z-sensor.gyro.offset_min.z>20)
				Mpu6050_CalOffset_Gyro();	 
		 else
		 {
			  sensor.gyro.offset.x = (float)(tempgx)/1000;
			  sensor.gyro.offset.y = (float)(tempgy)/1000;
			  sensor.gyro.offset.z = (float)(tempgz)/1000;
			  BUZZER_ON;
			  DelayMs(200);
			  BUZZER_OFF;
		 }
}

//mpu6050数据准备
void Mpu6050_Data_Prepare(void)
{	
	u8 i;
	int32_t FILT_TMP[ITEMS] = {0};
  static int16_t FILT_BUF[ITEMS][MPU6050_FILTER_NUM] = {0};

	/* 得出校准后的数据 */
	sensor.acc.calibration.x = sensor.acc.origin.x  - sensor.acc.offset.x ;
	sensor.acc.calibration.y = sensor.acc.origin.y  - sensor.acc.offset.y ;
	sensor.acc.calibration.z = sensor.acc.origin.z  - sensor.acc.offset.z ;
	sensor.gyro.calibration.x = sensor.gyro.origin.x - sensor.gyro.offset.x ;
	sensor.gyro.calibration.y = sensor.gyro.origin.y - sensor.gyro.offset.y ;
	sensor.gyro.calibration.z = sensor.gyro.origin.z - sensor.gyro.offset.z ;
	
  for(i=MPU6050_FILTER_NUM-1;i>=1;i--)
  {
    FILT_BUF[A_X][i] = FILT_BUF[A_X][i-1];
		FILT_BUF[A_Y][i] = FILT_BUF[A_Y][i-1];
		FILT_BUF[A_Z][i] = FILT_BUF[A_Z][i-1];
		FILT_BUF[G_X][i] = FILT_BUF[G_X][i-1];
		FILT_BUF[G_Y][i] = FILT_BUF[G_Y][i-1];
		FILT_BUF[G_Z][i] = FILT_BUF[G_Z][i-1];
  }

	  FILT_BUF[A_X][0] = sensor.acc.calibration.x;
		FILT_BUF[A_Y][0] = sensor.acc.calibration.y;
		FILT_BUF[A_Z][0] = sensor.acc.calibration.z;
		FILT_BUF[G_X][0] = sensor.gyro.calibration.x;
		FILT_BUF[G_Y][0] = sensor.gyro.calibration.y;
		FILT_BUF[G_Z][0] = sensor.gyro.calibration.z;

	for(i=0;i<MPU6050_FILTER_NUM;i++)
	{
		FILT_TMP[A_X] += FILT_BUF[A_X][i];
		FILT_TMP[A_Y] += FILT_BUF[A_Y][i];
		FILT_TMP[A_Z] += FILT_BUF[A_Z][i];
		FILT_TMP[G_X] += FILT_BUF[G_X][i];
		FILT_TMP[G_Y] += FILT_BUF[G_Y][i];
		FILT_TMP[G_Z] += FILT_BUF[G_Z][i];
	}


	sensor.acc.filter.x = (float)( FILT_TMP[A_X] )/(float)MPU6050_FILTER_NUM;
	sensor.acc.filter.y = (float)( FILT_TMP[A_Y] )/(float)MPU6050_FILTER_NUM;
	sensor.acc.filter.z = (float)( FILT_TMP[A_Z] )/(float)MPU6050_FILTER_NUM;

	sensor.gyro.filter.x = (float)( FILT_TMP[G_X] )/(float)MPU6050_FILTER_NUM;
	sensor.gyro.filter.y = (float)( FILT_TMP[G_Y] )/(float)MPU6050_FILTER_NUM;
	sensor.gyro.filter.z = (float)( FILT_TMP[G_Z] )/(float)MPU6050_FILTER_NUM;
	
	sensor.gyro.dps.x = sensor.gyro.filter.x * TO_ANGLE;
	sensor.gyro.dps.y = sensor.gyro.filter.y * TO_ANGLE;
	sensor.gyro.dps.z = sensor.gyro.filter.z * TO_ANGLE;
	
	sensor.gyro.radps.x = sensor.gyro.dps.x * ANGLE_TO_RAD;
	sensor.gyro.radps.y = sensor.gyro.dps.y * ANGLE_TO_RAD;
	sensor.gyro.radps.z = sensor.gyro.dps.z * ANGLE_TO_RAD;
	
}
