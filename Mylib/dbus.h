#ifndef _Dbus_H
#define _Dbus_H

#include "board.h"

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
void DMA1_Stream1_IRQHandler(void);
void RC_Check(float T,float OutofControl_ms);
void s_bus_get_value(void);


#endif /*_Dbus_H*/
