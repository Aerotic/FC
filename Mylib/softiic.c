#include "softiic.h"

u8 I2C_FastMode;

//模拟IIC初始化
void I2C_Soft_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure; 
	
  RCC_AHB1PeriphClockCmd(RCC_I2C , ENABLE );
  GPIO_InitStructure.GPIO_Pin =  I2C_Pin_SCL | I2C_Pin_SDA;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(I2C_PORT, &GPIO_InitStructure);
}


void I2C_Soft_Delay(void)
{
	__nop();__nop();__nop();
	__nop();__nop();__nop();
	__nop();__nop();__nop();
	
	if(!I2C_FastMode)
	{
		u8 i = 15;
		while(i--);
	}
}

int I2C_Soft_Start(void)
{
	SDA_H;
	SCL_H;
	I2C_Soft_Delay();
	if(!SDA_read)return 0;	//SDA线为低电平则总线忙,退出
	SDA_L;
	I2C_Soft_Delay();
	if(SDA_read) return 0;	//SDA线为高电平则总线出错,退出
	SDA_L;
	I2C_Soft_Delay();
	return 1;	
}

void I2C_Soft_Stop(void)
{
	SCL_L;
	I2C_Soft_Delay();
	SDA_L;
	I2C_Soft_Delay();
	SCL_H;
	I2C_Soft_Delay();
	SDA_H;
	I2C_Soft_Delay();
} 

void I2C_Soft_Ack(void)
{	
	SCL_L;
	I2C_Soft_Delay();
	SDA_L;
	I2C_Soft_Delay();
	SCL_H;
	I2C_Soft_Delay();
	SCL_L;
	I2C_Soft_Delay();
}   

void I2C_Soft_NoAck(void)
{	
	SCL_L;
	I2C_Soft_Delay();
	SDA_H;
	I2C_Soft_Delay();
	SCL_H;
	I2C_Soft_Delay();
	SCL_L;
	I2C_Soft_Delay();
} 

int I2C_Soft_WaitAck(void) 	 //返回为:=1有ACK,=0无ACK
{
	SCL_L;
	I2C_Soft_Delay();
	SDA_H;			
	I2C_Soft_Delay();
	SCL_H;
	I2C_Soft_Delay();
	if(SDA_read)
	{
      SCL_L;
			I2C_Soft_Delay();
      return 0;
	}
	SCL_L;
	I2C_Soft_Delay();
	return 1;
}

void I2C_Soft_SendByte(u8 SendByte)
{
    u8 i=8;
    while(i--)
    {
        SCL_L;
        I2C_Soft_Delay();
      if(SendByte&0x80)
        SDA_H;  
      else 
        SDA_L;   
        SendByte<<=1;
        I2C_Soft_Delay();
				SCL_H;
				I2C_Soft_Delay();
    }
    SCL_L;
}  

u8 I2C_Soft_ReadByte(void)  //数据从高位到低位//
{ 
    u8 i=8;
    u8 ReceiveByte=0;

    SDA_H;				
    while(i--)
    {
      ReceiveByte<<=1;      
      SCL_L;
      I2C_Soft_Delay();
			SCL_H;
      I2C_Soft_Delay();	
      if(SDA_read)
      {
        ReceiveByte|=0x01;
      }
    }
    SCL_L;
    return ReceiveByte;
} 

//单字节写入
int I2C_Soft_Single_Write(u8 SlaveAddress,u8 REG_Address,u8 REG_data)		
{
  	if(!I2C_Soft_Start())return 0;
    I2C_Soft_SendByte(SlaveAddress);   //发送设备地址+写信号//I2C_SendByte(((REG_Address & 0x0700) >>7) | SlaveAddress & 0xFFFE);//设置高起始地址+器件地址 
    if(!I2C_Soft_WaitAck()){I2C_Soft_Stop(); return 0;}
    I2C_Soft_SendByte(REG_Address );   //设置低起始地址      
    I2C_Soft_WaitAck();	
    I2C_Soft_SendByte(REG_data);
    I2C_Soft_WaitAck();   
    I2C_Soft_Stop(); 
    return 1;
}

//单字节读取
int I2C_Soft_Single_Read(u8 SlaveAddress,u8 REG_Address)
{   
		unsigned char REG_data;     	
		if(!I2C_Soft_Start())return 0;
    I2C_Soft_SendByte(SlaveAddress); //I2C_SendByte(((REG_Address & 0x0700) >>7) | REG_Address & 0xFFFE);//设置高起始地址+器件地址 
    if(!I2C_Soft_WaitAck())
		{
			I2C_Soft_Stop();
			return 0;
		}
    I2C_Soft_SendByte((u8) REG_Address);   //设置低起始地址      
    I2C_Soft_WaitAck();
    I2C_Soft_Start();
    I2C_Soft_SendByte(SlaveAddress+1);
    I2C_Soft_WaitAck();

		REG_data= I2C_Soft_ReadByte();
    I2C_Soft_NoAck();
    I2C_Soft_Stop();
	  return REG_data;
}	

//多字节读取
int I2C_Soft_Mult_Read(u8 SlaveAddress,u8 REG_Address,u8 * ptChar,u8 size)
{
    uint8_t i;
    
    if(size < 1)
			return 0;
    if(!I2C_Soft_Start())
			return 0;
    I2C_Soft_SendByte(SlaveAddress);
    if(!I2C_Soft_WaitAck())
		{
			I2C_Soft_Stop();
			return 0;
		}
    I2C_Soft_SendByte(REG_Address);    
    I2C_Soft_WaitAck();
    
    I2C_Soft_Start();
    I2C_Soft_SendByte(SlaveAddress+1);
    I2C_Soft_WaitAck();
    
    for(i=1;i<size; i++)
    {
        *ptChar++ = I2C_Soft_ReadByte();
        I2C_Soft_Ack();
    }
    *ptChar++ = I2C_Soft_ReadByte();
    I2C_Soft_NoAck();
    I2C_Soft_Stop();
    return 1;    
}	
