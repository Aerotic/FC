#include "data_send.h"


void Uart_Wave_Send(void)
{
	  u8 usart1_tx_buffer[32]={0};
		int32_t data_int32;
		uint32_t data_uint32;
		u8 i,sum=0;

		usart1_tx_buffer[0]=0x88;
		usart1_tx_buffer[1]=0xA1;
		usart1_tx_buffer[2]=28;

		data_uint32 = GetSysTime_us();
		usart1_tx_buffer[3]=BYTE3(data_uint32);
		usart1_tx_buffer[4]=BYTE2(data_uint32);	
		usart1_tx_buffer[5]=BYTE1(data_uint32);
		usart1_tx_buffer[6]=BYTE0(data_uint32);

    data_int32 = gps.leader_lat*10000000;
		usart1_tx_buffer[7]=BYTE3(data_int32);
		usart1_tx_buffer[8]=BYTE2(data_int32);	
		usart1_tx_buffer[9]=BYTE1(data_int32);
		usart1_tx_buffer[10]=BYTE0(data_int32);

    data_int32 = gps.leader_lon*10000000;
		usart1_tx_buffer[11]=BYTE3(data_int32);
		usart1_tx_buffer[12]=BYTE2(data_int32);	
		usart1_tx_buffer[13]=BYTE1(data_int32);
		usart1_tx_buffer[14]=BYTE0(data_int32);

    data_int32 = gps.lat*10000000;
		usart1_tx_buffer[15]=BYTE3(data_int32);
		usart1_tx_buffer[16]=BYTE2(data_int32);	
		usart1_tx_buffer[17]=BYTE1(data_int32);
		usart1_tx_buffer[18]=BYTE0(data_int32);

    data_int32 = gps.lon*10000000;
		usart1_tx_buffer[19]=BYTE3(data_int32);
		usart1_tx_buffer[20]=BYTE2(data_int32);	
		usart1_tx_buffer[21]=BYTE1(data_int32);
		usart1_tx_buffer[22]=BYTE0(data_int32);		

    for(i=0;i<31;i++)
		{
			sum+=usart1_tx_buffer[i];
		}
		usart1_tx_buffer[31]=sum;
		for(i=0;i<32;i++) 
		Usart1_SendChar(usart1_tx_buffer[i]); 
}

void Uart_Attitude_Send(void)
{
	  u8 usart1_tx_buffer[32]={0};
	  int data_int;
		u8 i,sum=0;
	
		usart1_tx_buffer[0]=0x88;
		usart1_tx_buffer[1]=0xAF;
		usart1_tx_buffer[2]=28;  

		data_int = sensor.acc.filter.x;
		usart1_tx_buffer[3]=BYTE1(data_int);
		usart1_tx_buffer[4]=BYTE0(data_int);

		data_int = sensor.acc.filter.y;
		usart1_tx_buffer[5]=BYTE1(data_int);
		usart1_tx_buffer[6]=BYTE0(data_int);

		data_int = sensor.acc.filter.z;
		usart1_tx_buffer[7]=BYTE1(data_int);
		usart1_tx_buffer[8]=BYTE0(data_int);

		data_int = sensor.gyro.dps.x;
		usart1_tx_buffer[9]=BYTE1(data_int);
		usart1_tx_buffer[10]=BYTE0(data_int);

		data_int = sensor.gyro.dps.y;
		usart1_tx_buffer[11]=BYTE1(data_int);
		usart1_tx_buffer[12]=BYTE0(data_int);

		data_int = sensor.gyro.dps.z;
		usart1_tx_buffer[13]=BYTE1(data_int);
		usart1_tx_buffer[14]=BYTE0(data_int);
			
		//15 16 17 18 19 20	mag
			
		data_int=angle.roll*100;
		usart1_tx_buffer[21]=BYTE1(data_int);
		usart1_tx_buffer[22]=BYTE0(data_int);
		
		data_int=angle.pitch*100;
		usart1_tx_buffer[23]=BYTE1(data_int);
		usart1_tx_buffer[24]=BYTE0(data_int);
		
		data_int=angle.yaw*10;
		usart1_tx_buffer[25]=BYTE1(data_int);
		usart1_tx_buffer[26]=BYTE0(data_int);

		for(i=0;i<31;i++)
		{
			sum+=usart1_tx_buffer[i];
		}
		usart1_tx_buffer[31]=sum;
		for(i=0;i<32;i++) 
		Usart1_SendChar(usart1_tx_buffer[i]); 
}


void Uart_RC_Motor_Send(void)
{
	  u8 usart1_tx_buffer[32]={0};
	  int data_int;
    int aux_value;
		u8 i,sum=0;
		usart1_tx_buffer[0] = 0x88;
		usart1_tx_buffer[1] = 0xAE;
		usart1_tx_buffer[2] = 28;
	
		data_int = thr.value + 1000;
		usart1_tx_buffer[3] = BYTE1(data_int);
		usart1_tx_buffer[4] = BYTE0(data_int);
	
		data_int = RC.CH[2]*500/660 + 1500;
		usart1_tx_buffer[5] = BYTE1(data_int);
		usart1_tx_buffer[6] = BYTE0(data_int);
	
		data_int = RC.CH[0]*500/660 + 1500;
		usart1_tx_buffer[7] = BYTE1(data_int);
		usart1_tx_buffer[8] = BYTE0(data_int);
	
		data_int = RC.CH[1]*500/660 + 1500;
		usart1_tx_buffer[9] = BYTE1(data_int);
		usart1_tx_buffer[10] = BYTE0(data_int);
		
		switch(RC.CH[4])
		{
       case 1:aux_value=1000;break;
			 case 3:aux_value=1500;break;
			 case 2:aux_value=2000;break;
    }
		usart1_tx_buffer[11] = BYTE1(aux_value);
		usart1_tx_buffer[12] = BYTE0(aux_value);
		
		switch(RC.CH[5])
		{
       case 1:aux_value=1000;break;
			 case 3:aux_value=1500;break;
			 case 2:aux_value=2000;break;
    }
		usart1_tx_buffer[13] = BYTE1(aux_value);
		usart1_tx_buffer[14] = BYTE0(aux_value);
		
		data_int = speed.motor1/10;
		usart1_tx_buffer[21] = BYTE1(data_int);
		usart1_tx_buffer[22] = BYTE0(data_int);
		
		data_int = speed.motor2/10;
		usart1_tx_buffer[23] = BYTE1(data_int);
		usart1_tx_buffer[24] = BYTE0(data_int);
		
		data_int = speed.motor3/10;
		usart1_tx_buffer[25] = BYTE1(data_int);
		usart1_tx_buffer[26] = BYTE0(data_int);
		
 		data_int = speed.motor4/10;
 		usart1_tx_buffer[27] = BYTE1(data_int);
 		usart1_tx_buffer[28] = BYTE0(data_int);
	
		for(i=0;i<31;i++)
		{
			sum+=usart1_tx_buffer[i];
		}
		usart1_tx_buffer[31]=sum;
		for(i=0;i<32;i++) 
		Usart1_SendChar(usart1_tx_buffer[i]); 	
}
