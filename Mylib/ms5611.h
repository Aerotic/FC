#ifndef _MS5611_H
#define	_MS5611_H

#include "board.h"

#define MS5611_ADDR             0xee // 0x77

#define CMD_RESET               0x1E // ADC reset command
#define CMD_ADC_READ            0x00 // ADC read command
#define CMD_ADC_CONV            0x40 // ADC conversion command
#define CMD_ADC_D1              0x00 // ADC D1 conversion
#define CMD_ADC_D2              0x10 // ADC D2 conversion
#define CMD_ADC_256             0x00 // ADC OSR=256
#define CMD_ADC_512             0x02 // ADC OSR=512
#define CMD_ADC_1024            0x04 // ADC OSR=1024
#define CMD_ADC_2048            0x06 // ADC OSR=2048
#define CMD_ADC_4096            0x08 // ADC OSR=4096
#define CMD_PROM_RD             0xA0 // Prom read command
#define PROM_NB                 8
#define MS5611_OSR							0x08	//CMD_ADC_4096

#define PROM_NB	8

#define MS5611_FILTER_NUM 100

struct _ms5611
         {
					int32_t baroAlt;
					int32_t pressure;
					int32_t temperature;
					int32_t baro_Offset_max;
					int32_t baro_Offset_min; 
					int32_t baro_Offset;
					uint32_t ms5611_ut;  // static result of temperature measurement
					uint32_t ms5611_up;  // static result of pressure measurement 
					float height_last;
					float height_dif;
         };
				 
extern struct _ms5611 ms5611;
	

void MS5611_Reset(void);
u8 MS5611_Read_Prom(void);
void MS5611_Init(void);
void MS5611_Read_Adc_T(void);
void MS5611_Read_Adc_P(void);
void MS5611_Start_T(void);
void MS5611_Start_P(void);
void MS5611_Update(void);
void MS5611_BaroAltCalculate(void);
int32_t MS5611_Get_BaroAlt(void);
void MS5611_CalOffset(void);

#endif
