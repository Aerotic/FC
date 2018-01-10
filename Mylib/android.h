#ifndef __ANDROID_H_
#define __ANDROID_H_
#include "board.h"

//#define CHANNEL_FILTER_NUM 4
//#define RC_FILTER_NUM      10

//struct _RC{
//					int16_t CH[6];
//	        int16_t CH_LAST[6];
//	        float   CH_DIF[6];
//					uint16_t NoSignal;
//					u8 OutofControl;
//          };
struct _SENSOR{
					float acc[3];
					float gyro_rps[3];
					float gyro_dps[3];
					float deg[3];
};
extern struct _SENSOR phone;
//extern struct _RC RC;
extern u8 rx_buffer[9];
extern u8 tx_buffer[9];
void Android_Serialport_Config(void);
void DMA1_Stream3_IRQHandler(void);
void USART3_IRQHandler(void);
//void USART3_IRQHandler(void);  
void RC_Check(float T,float OutofControl_ms);
void s_bus_get_value(void);
void acc_gyro(void);
void SendToAndroid();
#endif