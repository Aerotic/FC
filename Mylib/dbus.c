#include "dbus.h"

struct _RC RC;

unsigned char sbus_rx_buffer[25];
int16_t sbus_decode_buffer[15];


void RC_Check(float T,float OutofControl_ms)
{
	  if(OutofControl_ms < 15) return;

	  if(MIN(RC.NoSignal++, 60000)*T > OutofControl_ms/1000)
		{
			RC.OutofControl = 1;
		}
		if(RC.OutofControl == 1)
		{
			/*ʧ��ʱԭ�ؽ���*/
			RC.CH[0] = 0;
			RC.CH[1] = 0;
			RC.CH[2] = 0;
			RC.CH[3] = -260;//����34.2% 54cm/s�½�
			RC.CH[4] = 3;
			RC.CH[5] = 2;	
		}
}


void s_bus_get_value(void)
{
	float dbus_loop_time;
		dbus_loop_time = Get_Cycle_T(5); 

		RC.CH_LAST[0] = RC.CH[0];
		RC.CH_LAST[1] = RC.CH[1];
		RC.CH_LAST[2] = RC.CH[2];
		RC.CH_LAST[3] = RC.CH[3];
		//�ձ���

		//��ҡ�˺���  ��Χ+-660
		sbus_decode_buffer[0] = (sbus_rx_buffer[0]| (sbus_rx_buffer[1] << 8)) & 0x07ff; //!< Channel 0
		RC.CH[0] = (my_deathzoom(sbus_decode_buffer[0]-1024, 5));
		//��ҡ������   ��Χ+-660
		sbus_decode_buffer[1] = ((sbus_rx_buffer[1] >> 3) | (sbus_rx_buffer[2] << 5)) & 0x07ff;
		RC.CH[3] = (my_deathzoom(sbus_decode_buffer[1]-1024, 5));
		//��ҡ�˺���   ��Χ+-660
		sbus_decode_buffer[2]= ((sbus_rx_buffer[2] >> 6) | (sbus_rx_buffer[3] << 2) | (sbus_rx_buffer[4] << 10)) & 0x07ff; //!< Channel 2
		RC.CH[2] = my_deathzoom(sbus_decode_buffer[2]-1024, 5);
		//��ҡ������   ��Χ+-660
		sbus_decode_buffer[3] = ((sbus_rx_buffer[4] >> 1) | (sbus_rx_buffer[5] << 7)) & 0x07ff; //!< Channel 3
		RC.CH[1] = (my_deathzoom(sbus_decode_buffer[3]-1024, 5));
		//��߿���  132 ������
		RC.CH[4] = ((sbus_rx_buffer[5] >> 4)& 0x000C) >> 2; //!< Switch left
		//�ұ߿���  132 ������
		RC.CH[5] = ((sbus_rx_buffer[5] >> 4)& 0x0003); //!< Switch right9 / 9  
		
				if(RC.CH[5]==2)
		{
			aircraft.unlock = 0;
		}
		RC.CH_DIF[0] = MIN((float)(RC.CH[0] - RC.CH_LAST[0])/dbus_loop_time ,1000);
		RC.CH_DIF[1] = MIN((float)(RC.CH[1] - RC.CH_LAST[1])/dbus_loop_time ,1000);
		RC.CH_DIF[2] = MIN((float)(RC.CH[2] - RC.CH_LAST[2])/dbus_loop_time ,1000);
		RC.CH_DIF[3] = MIN((float)(RC.CH[3] - RC.CH_LAST[3])/dbus_loop_time ,1000);
		
		RC.NoSignal = 0;
		RC.OutofControl = 0;
//		if(RC.CH[4]==1)
//				LED_BLUE_ON;
//		else
//				LED_BLUE_OFF;
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
		USART_InitStructure.USART_BaudRate = 100000;   //SBUS 100K baudrate
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No ;
		USART_InitStructure.USART_Mode = USART_Mode_Rx;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		
		USART_Init(USART3,&USART_InitStructure);
    USART_DMACmd(USART3,USART_DMAReq_Rx,ENABLE);
		USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);
    
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    		
		
		DMA_DeInit(DMA1_Stream1);
    DMA_InitStructure.DMA_Channel= DMA_Channel_4;
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&(USART3->DR);
    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)sbus_rx_buffer;
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
		USART_Cmd(USART3,ENABLE);
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
	
	s_bus_get_value();
	
	DMA_SetCurrDataCounter(DMA1_Stream1,128);
  USART_ClearITPendingBit(USART3,USART_IT_IDLE);
  DMA_Cmd(DMA1_Stream1, ENABLE);
}
