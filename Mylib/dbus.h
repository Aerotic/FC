#ifndef _Dbus_H
#define _Dbus_H

//#include "board.h"

////#define CHANNEL_FILTER_NUM 4
////#define RC_FILTER_NUM      10

////struct _RC{
////					int16_t CH[6];
////	        int16_t CH_LAST[6];
////	        float   CH_DIF[6];
////					uint16_t NoSignal;
////					u8 OutofControl;
////          };
//struct _SENSOR{
//					float acc[3];
//					float gyro_rps[3];
//					float gyro_dps[3];
//					float deg[3];
//};
//extern struct _SENSOR phone;
////extern struct _RC RC;
//extern u8 rx_buffer[32];
//void Dbus_Config(void);
//void DMA1_Stream1_IRQHandler(void);
////void USART3_IRQHandler(void);  
//void RC_Check(float T,float OutofControl_ms);
//void s_bus_get_value(void);
//void acc_gyro(void);
#include "board.h"
//void Phone_Config(void);
//void get_value(void);
//void DMA1_Stream5_IRQHandler(void);
#define CHANNEL_FILTER_NUM 4
#define RC_FILTER_NUM      10

struct _RC{
					int16_t CH[6];
	        int16_t CH_LAST[6];
	        float   CH_DIF[6];
					uint16_t NoSignal;
					u8 OutofControl;
        };
extern struct _RC RC;

void Dbus_Config(void);
void RC_Check(float T,float OutofControl_ms);
void dbus_get_value(void);
void Dbus_Configuration(void);
void DMA1_Stream5_IRQHandler(void);
#endif /*_Dbus_H*/
