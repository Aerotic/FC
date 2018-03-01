#include "android.h"
#define RadToDeg 57.295779
struct _RC RC;
struct _SENSOR phone;


u8 tx_buffer[9];
u8 rx_buffer[9];
int32_t cnter=0;

union char2float{
	char buf[2];
	short dest;
}bf;
void Android_Serialport_get_value(void)
{
//	u8 cnt;
//	//get orientation x
//	for(cnt=0;cnt<2;cnt++) bf.buf[cnt]=rx_buffer[cnt];
//	angle.yaw=bf.dest;
//	//get orientation y
//	for(cnt=2;cnt<4;cnt++) bf.buf[cnt-4]=rx_buffer[cnt];
//	angle.roll=bf.dest;
//	//get orientation z
//	for(cnt=4;cnt<6;cnt++) bf.buf[cnt-8]=rx_buffer[cnt];
//	angle.pitch=bf.dest;
//	//
//	for(cnt=6;cnt<8;cnt++) bf.buf[cnt-12]=rx_buffer[cnt];
//	phone.gyro_dps[0]=bf.dest;
//	for(cnt=16;cnt<20;cnt++) bf.buf[cnt-16]=rx_buffer[cnt];
//	phone.gyro_dps[1]=bf.dest;
//	for(cnt=20;cnt<24;cnt++) bf.buf[cnt-20]=rx_buffer[cnt];
//	phone.gyro_dps[2]=bf.dest;

}
void acc_gyro(void)//acc in m/s^2  gyro in rad/s
{
	u8 cnt;
	//get acceleration x
	for(cnt=0;cnt<4;cnt++) bf.buf[cnt]=rx_buffer[cnt];
	phone.acc[0]=bf.dest;
	//get acceleration y
	for(cnt=4;cnt<8;cnt++) bf.buf[cnt-4]=rx_buffer[cnt];
	phone.acc[1]=bf.dest;
	//get acceleration z
	for(cnt=8;cnt<12;cnt++) bf.buf[cnt-8]=rx_buffer[cnt];
	phone.acc[2]=bf.dest;
	for(cnt=12;cnt<16;cnt++) bf.buf[cnt-12]=rx_buffer[cnt];
	phone.gyro_rps[0]=bf.dest;
	for(cnt=16;cnt<20;cnt++) bf.buf[cnt-16]=rx_buffer[cnt];
	phone.gyro_rps[1]=bf.dest;
	for(cnt=20;cnt<24;cnt++) bf.buf[cnt-20]=rx_buffer[cnt];
	phone.gyro_rps[2]=bf.dest;
	phone.gyro_dps[0]=RadToDeg*phone.gyro_rps[0];
	phone.gyro_dps[1]=RadToDeg*phone.gyro_rps[1];
	phone.gyro_dps[2]=RadToDeg*phone.gyro_rps[2];
}
void Android_Serialport_Config(void)
{
	  USART_InitTypeDef USART_InitStructure;
	  GPIO_InitTypeDef  GPIO_InitStructure;
    NVIC_InitTypeDef  NVIC_InitStructure;
    DMA_InitTypeDef   DMA_InitStructure;
	
	    
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_DMA1,ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
		
		GPIO_PinAFConfig(GPIOC,GPIO_PinSource11 ,GPIO_AF_USART3);
	  GPIO_PinAFConfig(GPIOC,GPIO_PinSource10 ,GPIO_AF_USART3);
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 |  GPIO_Pin_10;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	
		//USART_DeInit(USART2);
		USART_InitStructure.USART_BaudRate = 512000;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No ;
		USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_Init(USART3,&USART_InitStructure);
    
		USART_Cmd(USART3,ENABLE);
		USART_DMACmd(USART3,USART_DMAReq_Tx,ENABLE);
		USART_DMACmd(USART3,USART_DMAReq_Rx,ENABLE);
    
    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
		
    		
		//DMA_USART3_Tx
		DMA_DeInit(DMA1_Stream3);
    DMA_InitStructure.DMA_Channel= DMA_Channel_4;
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&(USART3->DR);
    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)tx_buffer;
    DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
    DMA_InitStructure.DMA_BufferSize = 9;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;
    DMA_InitStructure.DMA_MemoryBurst = DMA_Mode_Normal;
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
    DMA_Init(DMA1_Stream3,&DMA_InitStructure);


    DMA_ITConfig(DMA1_Stream3,DMA_IT_TC,ENABLE);
    DMA_Cmd(DMA1_Stream3,DISABLE);	
		
		
		//DMA_USART3_Rx
		USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);
    
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    		
		
		DMA_DeInit(DMA1_Stream1);
    DMA_InitStructure.DMA_Channel= DMA_Channel_4;
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&(USART3->DR);
    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)rx_buffer;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
    DMA_InitStructure.DMA_BufferSize = 128;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;
    DMA_InitStructure.DMA_MemoryBurst = DMA_Mode_Normal;
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
    DMA_Init(DMA1_Stream1,&DMA_InitStructure);


    //DMA_ITConfig(DMA1_Stream5,DMA_IT_TC,ENABLE);
    DMA_Cmd(DMA1_Stream1,ENABLE);	
}
void DMA1_Stream3_IRQHandler(void)
{
	if(DMA_GetITStatus(DMA1_Stream3, DMA_IT_TCIF3))
	{
		DMA_ClearFlag(DMA1_Stream3, DMA_FLAG_TCIF3);
		DMA_ClearITPendingBit(DMA1_Stream3, DMA_IT_TCIF3);
		
  }
}
void USART3_IRQHandler(void)  
{
	uint8_t num_1;
	uint16_t data_len_1;
	data_len_1 = 128 - DMA_GetCurrDataCounter(DMA1_Stream1);
  num_1 = USART3->SR;
  num_1 = USART3->DR;
	DMA_Cmd(DMA1_Stream1, DISABLE);   
  DMA_ClearFlag(DMA1_Stream1,DMA_FLAG_TEIF1 | DMA_FLAG_TCIF1 | DMA_FLAG_DMEIF1 | DMA_FLAG_HTIF1 | DMA_FLAG_FEIF1);
	DMA_SetCurrDataCounter(DMA1_Stream1,128);
  USART_ClearITPendingBit(USART3,USART_IT_IDLE);
	AndroidRPM();
  DMA_Cmd(DMA1_Stream1, ENABLE);
}
void SendToAndroid()
{
	DMA_Cmd(DMA1_Stream3,DISABLE);
	tx_buffer[0] = (u8)(0x0ff&(RC.CH[0]>>8));
	tx_buffer[1] = (u8)(0x0ff&(RC.CH[0]));
	tx_buffer[2] = (u8)(0x0ff&(RC.CH[1]>>8));
	tx_buffer[3] = (u8)(0xff&(RC.CH[1]));
	tx_buffer[4] = (u8)(0x0ff&(RC.CH[2]>>8));
	tx_buffer[5] = (u8)(0x0ff&(RC.CH[2]));
	tx_buffer[6] = (u8)(0x0ff&(RC.CH[3]>>8));
	tx_buffer[7] = (u8)(0x0ff&(RC.CH[3]));
	tx_buffer[8] = (u8)(0x0ff&(RC.CH[4]));
	tx_buffer[8] |= (u8)(0x0ff&(RC.CH[5]<<2));
	DMA_SetCurrDataCounter(DMA1_Stream3,9);
	DMA_Cmd(DMA1_Stream3,ENABLE);
	
	
}
