#include "ms5611.h"

struct _ms5611 ms5611;
uint16_t ms5611_prom[PROM_NB];  // on-chip ROM
uint8_t t_rxbuf[3],p_rxbuf[3];

void MS5611_Reset(void)
{
  I2C_Soft_Single_Write(MS5611_ADDR, CMD_RESET, 1);
}

u8 MS5611_Read_Prom(void)
{
	uint8_t rxbuf[2] = { 0, 0 };
	u8 check = 0;
	u8 i;

	for (i = 0; i < PROM_NB; i++)
	{
		check += I2C_Soft_Mult_Read(MS5611_ADDR, CMD_PROM_RD + i * 2, rxbuf, 2); // send PROM READ command
		ms5611_prom[i] = rxbuf[0] << 8 | rxbuf[1];
	}

	if(check==PROM_NB)
		return 1;
	else
		return 0;
}

void MS5611_Init(void)
{
	DelayMs(10);
	//传感器复位
	MS5611_Reset();
	DelayMs(3);
	MS5611_Read_Prom();
	//开始读取温度
	MS5611_Start_T();
}

void MS5611_Read_Adc_T(void)
{
	I2C_Soft_Mult_Read(MS5611_ADDR, CMD_ADC_READ, t_rxbuf, 3); // read ADC
}

void MS5611_Read_Adc_P(void)
{
	I2C_Soft_Mult_Read(MS5611_ADDR, CMD_ADC_READ, p_rxbuf, 3); // read ADC
}

void MS5611_Start_T(void)
{
	I2C_Soft_Single_Write(MS5611_ADDR, CMD_ADC_CONV + CMD_ADC_D2 + MS5611_OSR, 1); // D2 (temperature) conversion start!
}

void MS5611_Start_P(void)
{
  I2C_Soft_Single_Write(MS5611_ADDR, CMD_ADC_CONV + CMD_ADC_D1 + MS5611_OSR, 1); // D1 (pressure) conversion start!
}


void MS5611_Update(void)
{
	static int state = 0;
	
	I2C_FastMode = 0;
	
	if (state) {
			MS5611_Read_Adc_P();
			MS5611_Start_T();
			MS5611_BaroAltCalculate();
			state = 0;
	} else {
			MS5611_Read_Adc_T();
			MS5611_Start_P();
			state = 1;
	}
}

void MS5611_BaroAltCalculate(void)
{
    int32_t off2 = 0, sens2 = 0, delt;
		int32_t dT;
		int64_t off,sens;
	
		ms5611.ms5611_ut = (t_rxbuf[0] << 16) | (t_rxbuf[1] << 8) | t_rxbuf[2];
		ms5611.ms5611_up = (p_rxbuf[0] << 16) | (p_rxbuf[1] << 8) | p_rxbuf[2];
		
    dT = ms5611.ms5611_ut - ((uint32_t)ms5611_prom[5] << 8);
    off = ((uint32_t)ms5611_prom[2] << 16) + (((int64_t)dT * ms5611_prom[4]) >> 7);
    sens = ((uint32_t)ms5611_prom[1] << 15) + (((int64_t)dT * ms5611_prom[3]) >> 8);
    ms5611.temperature = 2000 + (((int64_t)dT * ms5611_prom[6]) >> 23);

    if (ms5611.temperature < 2000) // temperature lower than 20degC 
		{ 
        delt = ms5611.temperature - 2000;
        delt = delt * delt;
        off2 = (5 * delt) >> 1;
        sens2 = (5 * delt) >> 2;
        if (ms5611.temperature < -1500) // temperature lower than -15degC
				{ 
            delt = ms5611.temperature + 1500;
            delt = delt * delt;
            off2  += 7 * delt;
            sens2 += (11 * delt) >> 1;
        }
    }
    off  -= off2; 
    sens -= sens2;
    ms5611.pressure = (((ms5611.ms5611_up * sens ) >> 21) - off) >> 15;
		ms5611.pressure = (int)((1.0f - pow(ms5611.pressure / 101325.0f, 0.190295f)) * 4433000.0f); // centimeter
		if(!(ms5611.baro_Offset == 0))
		ms5611.baroAlt = ms5611.pressure - ms5611.baro_Offset;
}

int32_t MS5611_Get_BaroAlt(void)
{
		return ms5611.baroAlt;
}

void MS5611_CalOffset(void)
{
		uint16_t cnt_ms =200;
		int32_t tempms =0;

		ms5611.baro_Offset_max = -32768;
		ms5611.baro_Offset_min = 32767;

 	  while(cnt_ms--)	 
	  {
			DelayMs(10);			
			MS5611_Update();
		  if(ms5611.pressure>ms5611.baro_Offset_max) 
				ms5611.baro_Offset_max = ms5611.pressure;

			if(ms5611.pressure<ms5611.baro_Offset_min) 
				ms5611.baro_Offset_min = ms5611.pressure;

				tempms += ms5611.pressure;
    }
				 
		// 200次数据有一个异常,再次校准
// 		 if(ms5611.baro_Offset_max-ms5611.baro_Offset_min>500)
// 				MS5611_CalOffset();	 
// 		 else
		 {
			  ms5611.baro_Offset = (float)(tempms)/200;
			  BUZZER_ON;
			  DelayMs(300);
			  BUZZER_OFF;
		 }
}

