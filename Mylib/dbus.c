#include "dbus.h"

struct _RC RC;
struct _SENSOR phone;


u8 rx_buffer[32];
int32_t cnter=0;


union char2float{
	char buf[4];
	float dest;
}bf;
void s_bus_get_value(void)
{
	u8 cnt;
	//get orientation x
	for(cnt=0;cnt<4;cnt++) bf.buf[cnt]=rx_buffer[cnt];
	angle.yaw=bf.dest;
	//get orientation y
	for(cnt=4;cnt<8;cnt++) bf.buf[cnt-4]=rx_buffer[cnt];
	angle.roll=bf.dest;
	//get orientation z
	for(cnt=8;cnt<12;cnt++) bf.buf[cnt-8]=rx_buffer[cnt];
	angle.pitch=bf.dest;
	//
	for(cnt=12;cnt<16;cnt++) bf.buf[cnt-12]=rx_buffer[cnt];
	phone.gyro_dps[0]=bf.dest;
	for(cnt=16;cnt<20;cnt++) bf.buf[cnt-16]=rx_buffer[cnt];
	phone.gyro_dps[1]=bf.dest;
	for(cnt=20;cnt<24;cnt++) bf.buf[cnt-20]=rx_buffer[cnt];
	phone.gyro_dps[2]=bf.dest;
//	if((angle.yaw==1.0f)&&(angle.roll==2.0f)&&(angle.pitch==3.0f)&&(phone.gyro_dps[0]==4.0f)&&(phone.gyro_dps[1]==5.0f)&&(phone.gyro_dps[2]==6.0f))
//		LED_BLUE_TOGGLE;
//	else
//		cnter++;
	
	
	
	
	
	//printf("the received data is %f\n",bf.dest);
}

void Dbus_Config()
{
	  USART_InitTypeDef USART_InitStructure;
	  GPIO_InitTypeDef  GPIO_InitStructure;
    NVIC_InitTypeDef  NVIC_InitStructure;
    DMA_InitTypeDef   DMA_InitStructure;
	
	    
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_DMA1,ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
		
		GPIO_PinAFConfig(GPIOC,GPIO_PinSource11 ,GPIO_AF_USART3);
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 ;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	
		//USART_DeInit(USART2);
		USART_InitStructure.USART_BaudRate = 460800;   //SBUS 100K baudrate
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No ;
		USART_InitStructure.USART_Mode = USART_Mode_Rx;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_Init(USART3,&USART_InitStructure);
    
		USART_Cmd(USART3,ENABLE);
		USART_DMACmd(USART3,USART_DMAReq_Rx,ENABLE);
		
		//USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);
    
    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    		
		
		DMA_DeInit(DMA1_Stream1);
    DMA_InitStructure.DMA_Channel= DMA_Channel_4;
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&(USART3->DR);
    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)rx_buffer;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
    DMA_InitStructure.DMA_BufferSize = 24;
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


    DMA_ITConfig(DMA1_Stream1,DMA_IT_TC,ENABLE);
    DMA_Cmd(DMA1_Stream1,ENABLE);	
		
}
void DMA1_Stream1_IRQHandler(void)
{
	if(DMA_GetITStatus(DMA1_Stream1, DMA_IT_TCIF1))
	{
		DMA_ClearFlag(DMA1_Stream1, DMA_FLAG_TCIF1);
		DMA_ClearITPendingBit(DMA1_Stream5, DMA_IT_TCIF1);
		s_bus_get_value();
  }
}
//void USART3_IRQHandler(void)  
//{
//	
//	uint8_t num_1;
//	uint16_t data_len_1;
//	data_len_1 = 128 - DMA_GetCurrDataCounter(DMA1_Stream1);
//  num_1 = USART3->SR;
//  num_1 = USART3->DR;
//	DMA_Cmd(DMA1_Stream1, DISABLE);   
//  DMA_ClearFlag(DMA1_Stream1,DMA_FLAG_TEIF1 | DMA_FLAG_TCIF1 | DMA_FLAG_DMEIF1 | DMA_FLAG_HTIF1 | DMA_FLAG_FEIF1);
//	
//	s_bus_get_value();
//	
//	DMA_SetCurrDataCounter(DMA1_Stream1,128);
//  USART_ClearITPendingBit(USART3,USART_IT_IDLE);
//  DMA_Cmd(DMA1_Stream1, ENABLE);
//}
