#ifndef _SOFT_I2C_H__
#define _SOFT_I2C_H__

#include "board.h"

#define SCL_H         I2C_PORT->BSRRL = I2C_Pin_SCL
#define SCL_L         I2C_PORT->BSRRH = I2C_Pin_SCL
#define SDA_H         I2C_PORT->BSRRL = I2C_Pin_SDA
#define SDA_L         I2C_PORT->BSRRH = I2C_Pin_SDA
#define SDA_read      I2C_PORT->IDR  & I2C_Pin_SDA

void I2C_Soft_Init(void);
void I2C_Soft_Delay(void);
int I2C_Soft_Start(void);
void I2C_Soft_Stop(void);
void I2C_Soft_Ack(void);
void I2C_Soft_NoAck(void);
int I2C_Soft_WaitAck(void); 	 //·µ»Ø:=1ÓÐACK,=0ÎÞACK
void I2C_Soft_SendByte(u8 SendByte);
u8 I2C_Soft_ReadByte(void);

int I2C_Soft_Single_Write(u8 SlaveAddress,u8 REG_Address,u8 REG_data);
int I2C_Soft_Single_Read(u8 SlaveAddress,u8 REG_Address);
int I2C_Soft_Mult_Read(u8 SlaveAddress,u8 REG_Address,u8 * ptChar,u8 size);

extern u8 I2C_FastMode;

#endif
