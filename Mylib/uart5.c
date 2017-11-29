#include "uart5.h"

void Uart5_Config(void)
{
	  USART_InitTypeDef USART_InitStructure;
	  GPIO_InitTypeDef  GPIO_InitStructure;
    NVIC_InitTypeDef  NVIC_InitStructure;
    DMA_InitTypeDef   DMA_InitStructure;
	
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_DMA1,ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,ENABLE);
		
		GPIO_PinAFConfig(GPIOC,GPIO_PinSource12 ,GPIO_AF_UART5);
		GPIO_PinAFConfig(GPIOD,GPIO_PinSource2 ,GPIO_AF_UART5);
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_Init(GPIOC,&GPIO_InitStructure);
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_Init(GPIOD,&GPIO_InitStructure);
    
		USART_DeInit(UART5);
		USART_InitStructure.USART_BaudRate = 9600;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No;
		USART_InitStructure.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_Init(UART5,&USART_InitStructure);			
		USART_Cmd(UART5,ENABLE);

//GPS 波特率修改为115200
		DelayMs(100);
		Uart5_SendChar(0xB5);
		Uart5_SendChar(0x62);
		Uart5_SendChar(0x06);
		Uart5_SendChar(0x00);
		Uart5_SendChar(0x14);
		Uart5_SendChar(0x00);
		Uart5_SendChar(0x01);
		Uart5_SendChar(0x00);
		Uart5_SendChar(0x00);
		Uart5_SendChar(0x00);
		Uart5_SendChar(0xD0);
		Uart5_SendChar(0x08);
		Uart5_SendChar(0x00);
		Uart5_SendChar(0x00);
		Uart5_SendChar(0x00);
		Uart5_SendChar(0xC2);
		Uart5_SendChar(0x01);
		Uart5_SendChar(0x00);
		Uart5_SendChar(0x07);
		Uart5_SendChar(0x00);
		Uart5_SendChar(0x03);
		Uart5_SendChar(0x00);
		Uart5_SendChar(0x00);
		Uart5_SendChar(0x00);
		Uart5_SendChar(0x00);
		Uart5_SendChar(0x00);
		Uart5_SendChar(0xC0);
		Uart5_SendChar(0x7E);
		DelayMs(100);
		
		USART_Cmd(UART5,DISABLE);
		USART_DeInit(UART5);
		USART_InitStructure.USART_BaudRate = 115200;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No;
		USART_InitStructure.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_Init(UART5,&USART_InitStructure);			
		USART_Cmd(UART5,ENABLE);

//GPS 刷新频率10hz
		DelayMs(100);
		Uart5_SendChar(0xB5);
		Uart5_SendChar(0x62);
		Uart5_SendChar(0x06);
		Uart5_SendChar(0x08);
		Uart5_SendChar(0x06);
		Uart5_SendChar(0x00);
		Uart5_SendChar(0x64);
		Uart5_SendChar(0x00);
		Uart5_SendChar(0x01);
		Uart5_SendChar(0x00);
		Uart5_SendChar(0x01);
		Uart5_SendChar(0x00);
		Uart5_SendChar(0x7A);
		Uart5_SendChar(0x12);
		DelayMs(100);
					
		USART_ITConfig(UART5,USART_IT_IDLE,ENABLE);
		   
    USART_DMACmd(UART5,USART_DMAReq_Rx,ENABLE);
 
    NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
 
    DMA_DeInit(DMA1_Stream0);
    DMA_InitStructure.DMA_Channel= DMA_Channel_4;
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&(UART5->DR);
    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)gps_rx_buffer;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
    DMA_InitStructure.DMA_BufferSize = GPS_BUF_LEN;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;
    DMA_InitStructure.DMA_MemoryBurst = DMA_Mode_Normal;
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
    DMA_Init(DMA1_Stream0,&DMA_InitStructure);

    DMA_Cmd(DMA1_Stream0,ENABLE);
}

void Uart5_SendChar(unsigned char b)
{
   while (USART_GetFlagStatus(UART5,USART_FLAG_TC) == RESET);
	 USART_SendData(UART5,b);
}

float gps_loop_time;
void UART5_IRQHandler(void)
{
	u16 i;
	if(USART_GetITStatus(UART5, USART_IT_IDLE) != RESET)
	{
		  DMA_Cmd(DMA1_Stream0,DISABLE);
		
			gps_loop_time = Get_Cycle_T(6);
		
			i = UART5->SR;  
			i = UART5->DR; 
		
		  GPS_Read();
			DMA1_Stream0->NDTR = GPS_BUF_LEN;
			USART_ClearITPendingBit(UART5, USART_IT_IDLE);
		  DMA_Cmd(DMA1_Stream0,ENABLE);
	}
}


