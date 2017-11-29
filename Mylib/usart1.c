#include "usart1.h"

#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
////定义_sys_exit()以避免使用半主机模式    
//_sys_exit(int x) 
//{ 
//	x = x; 
//} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 

void Usart1_Config(void)
{
		USART_InitTypeDef USART_InitStructure;
		GPIO_InitTypeDef  GPIO_InitStructure;
		
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_DMA2,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
		
		GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);
		GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1); 
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_Init(GPIOA,&GPIO_InitStructure);

		USART_InitStructure.USART_BaudRate = 512000;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No;
		USART_InitStructure.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_Init(USART1,&USART_InitStructure);
  	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
		USART_Cmd(USART1,ENABLE);
}

void Usart1_SendChar(unsigned char b)
{
   while (USART_GetFlagStatus(USART1,USART_FLAG_TC) == RESET);
	 USART_SendData(USART1,b);
}
